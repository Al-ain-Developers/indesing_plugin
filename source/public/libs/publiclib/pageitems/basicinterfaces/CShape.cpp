//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CShape.cpp $
//  
//  Owner: Jack Kirstein
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPublicHeaders.h"

// ----- Interfaces -----

#include "ICallback.h"
#include "IDrwEvtDispatcher.h"
#include "IGraphicsPort.h"
#include "IHierarchy.h"
#include "ILayoutController.h"
#include "IMainItemTOPData.h"
#include "IMultiColumnTextFrame.h"
#include "IOptionalDrawPass.h"
#include "IPageItemAdornmentList.h"
#include "IPageItemCache.h"
#include "IPageItemTypeUtils.h"
#include "IPathGeometry.h"
#include "IGeometry.h"
#include "ISelectionManager.h"
#include "IShapeGraphixCache.h"
#if DEBUG
#	include "IPDFGStateStack.h"
#	include "IRasterPort.h"
#endif
#if DEBUG && MACINTOSH
#	include "DebugClassUtils.h"
#	include "StackCrawler.h"
#endif

// ----- Includes -----

#include "AutoGSave.h"
#include "CShape.h"
#if defined(DEBUG) && defined(MACINTOSH)
#include "MResChainChecker.h"
#endif

// ----- Utility files -----

#include "IEventUtils.h"
#include "IPathUtils.h"
#include "TransformUtils.h"
#include "TransformUtilsPrivate.h"

// ----- ID.h files -----
#include "DocumentContextID.h"


static void SetInnerToParentTransform(IGraphicsPort* gPort, const IShape* shape);

static void InvalPageItemAdornments(IPageItemAdornmentList* adornmentList, IShape* shape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, ClassID reasonForInval, int32 flags)
{
	if (adornmentList)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;
		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			InterfacePtr<IAdornmentShape> pAdorn(punkAdorn, UseDefaultIID());
			pAdorn->Inval(shape, drawOrder, gd, reasonForInval, flags);
		}
	}
}

static void UnionPrintingPageItemAdornmentPaintedBBox(IPageItemAdornmentList* adornmentList, IShape* shape, const PMRect& itemBounds, PMRect &printBounds, const PMMatrix& xform)
{
	if (adornmentList)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(IAdornmentShape::kAllAdornmentFlags, kTrue));
		IPMUnknown* punkAdorn = nil;
		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			InterfacePtr<IAdornmentShape> pAdorn(punkAdorn, UseDefaultIID());
			if (pAdorn->WillPrint())
			{
				PMRect aChildRect = pAdorn->GetPrintedAdornmentBounds(shape, IAdornmentShape::kAllAdornmentFlags, itemBounds, xform);
				printBounds.Union(aChildRect);
			}
		}
	}
}

static void UnionPageItemAdornmentPaintedBBox(IPageItemAdornmentList* adornmentList, IShape* shape, const PMRect& itemBounds, PMRect &paintBounds, const PMMatrix& innertoview)
{
	if (adornmentList)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(IAdornmentShape::kAllAdornmentFlags, kTrue));
		IPMUnknown* punkAdorn = nil;
		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			InterfacePtr<IAdornmentShape> pAdorn(punkAdorn, UseDefaultIID());
			PMRect aChildRect = pAdorn->GetPaintedAdornmentBounds(shape, IAdornmentShape::kAllAdornmentFlags, itemBounds, innertoview);
			paintBounds.Union(aChildRect);
		}
	}
}

static void DrawPageItemAdornments(IPageItemAdornmentList* adornmentList, IShape* shape, GraphicsData * gd, int32 flags, IAdornmentShape::AdornmentDrawOrder paintOrderMask)
{
	// Note: Do *not* check for aborted draw here.. since page item adornments
	// are guaranteed an "after" if they were given a "before" we must dutifully
	// give them both.  So interrupted draw only occurs on the granularity of a
	// page item.  Perhaps this can be modified post-Anna to let adornments 
	// declare that they require this behavior and optimize accordingly. 
	// -MJP 7/25/2001
	if (adornmentList)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(paintOrderMask));
		IPMUnknown* punkAdorn = nil;
		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			InterfacePtr<IAdornmentShape> pAdorn(punkAdorn, UseDefaultIID());
			InterfacePtr<IOptionalDrawPass> optional(punkAdorn, IID_IOPTIONALDRAWPASS);
			if (!(optional && !optional->GetIsActive(shape, gd, flags)))
			{
				pAdorn->DrawAdornment(shape, paintOrderMask, gd, flags);
#ifdef DEBUG
				if (!(flags == IAdornmentShape::kAllAdornmentFlags || flags == IAdornmentShape::kNone))
					ASSERT_MSG((pAdorn->WillPrint() == kFalse && (pAdorn->GetDrawOrderBits() & IAdornmentShape::kAfterEndShape)) || !(pAdorn->GetDrawOrderBits() & IAdornmentShape::kAfterEndShape), "Adornments with IAdornmentShape::kAfterEndShape priority generally shouldn't print since they are outside of all page item drawing setup (e.g. opacity)");
#endif
			}
		}
	}
}

DEFINE_HELPER_METHODS(CShape)

CShape::CShape(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fDB(::GetDataBase(boss))
{
	fPageItemCache = (IPageItemCache*) QueryInterface (IID_IPAGEITEMCACHE);
	if ( fPageItemCache )
		fPageItemCache->Release(); // do this because the ref count is on the boss

	fHierarchy = (IHierarchy*) QueryInterface (IID_IHIERARCHY);
	if ( fHierarchy )
		fHierarchy->Release(); // do this because the ref count is on the boss

	fGeometry = (IGeometry*) QueryInterface (IID_IGEOMETRY);
	if ( fGeometry )
		fGeometry->Release(); // do this because the ref count is on the boss

	fHandleShape = (IHandleShape*) QueryInterface (IID_IHANDLESHAPE);
	if ( fHandleShape )
		fHandleShape->Release(); // do this because the ref count is on the boss

	fPathHandleShape = (IHandleShape*) QueryInterface (IID_IPATHHANDLESHAPE);
	if ( fPathHandleShape )
		fPathHandleShape->Release(); // do this because the ref count is on the boss

	fAdornmentList = (IPageItemAdornmentList*) QueryInterface (IID_IPAGEITEMADORNMENTLIST);
	if ( fAdornmentList )
		fAdornmentList->Release(); // do this because the ref count is on the boss
}

CShape::~CShape()
{
}

void CShape::ProcessDrawShape(GraphicsData* gd, int32 flags)
{
#if 0 && DEBUG && MACINTOSH
	DebugClassUtilsBuffer classBuf;
	char buf[1024];
	::snprintf( buf, 1024, "%s", DebugClassUtils::GetIDName( &classBuf, ::GetClass(this)));
	UID thisUID = ::GetUID( this);
#endif

	IDrwEvtDispatcher* drawEventDispatcher = gd->GetDrawEventDispatcher();
	

	if( drawEventDispatcher->ProcessDrawEvent(kAbortCheckMessage, this, gd, flags))
		return;
	if( drawEventDispatcher->ProcessDrawFilterEvent( this, gd, flags))
		return;
	if( drawEventDispatcher->ProcessDrawEvent(kDrawShapeMessage, this, gd, flags))
		return;

	if (!ShapeDisabled (gd, flags))
	{
		IGraphicsPort* gPort = gd->GetGraphicsPort();

		AutoGSave autoGSave(gPort);

		gPort->newpath();
//		SetInnerToParentTransform (gPort); XFMoveTo CShape::DrawHierarchy

		if (!drawEventDispatcher->ProcessDrawEvent(kBeginShapeMessage, this, gd, flags))
	 	{
#if defined(MACINTOSH) && defined(DEBUG)
			MResChainChecker resChecker("This CShape function changed the current resource file!");
#endif
			bool16 maskAdornments = drawEventDispatcher->ProcessDrawEvent(kDrawShapeAdornmentsMessage, this, gd, flags);
			
			if(!maskAdornments)
			{
				// Draw those adornments that want to be drawn before the shape
				DrawPageItemAdornments(gd, flags, IAdornmentShape::kBeforeShape);
			}
		
			DrawShape(gd, flags);
			
			if(!maskAdornments)
			{
				// Draw those adornments that want to be drawn after the shape
				DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterShape);
			}
		}
		
		drawEventDispatcher->ProcessDrawEvent(kEndShapeMessage, this, gd, flags);

		// Draw those adornments that want to be drawn after the kEndShapeMessage
		DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterEndShape);

//#define DEBUG_BOUNDS		
#ifdef DEBUG_BOUNDS
		PMMatrix oldMatrix;
		InterfacePtr<IRasterPort> rPort(gPort, IID_IRASTERPORT);
		rPort->currentmatrix (&oldMatrix);
		rPort->setmatrix (PMMatrix());
		
		//InterfacePtr<IGeometry> iGeometry(this, IID_IGEOMETRY);
		//PMRect paintedBox = iGeometry->GetStrokeBoundingBox (InnerToPasteboardMatrix(this)* gd->GetTransform());
		//gPort->setrgbcolor (1.0, 0.0, 0.0);
		//gPort->setlinewidth(0);
		//gPort->rectstroke(paintedBox);
		
		PMRect paintedBox = GetPaintedBBox (gd->GetTransform());
		paintedBox.Inset(1,1);
		gPort->setrgbcolor (1.0, 0.5, 1.0);
		gPort->setlinewidth(0);
		gPort->rectstroke(paintedBox);
		rPort->setmatrix (oldMatrix);
#endif
	}
}


PMRect CShape::GetPaintedBBox( const PMMatrix& viewXform, const Transform::CoordinateSpace& coordinateSpace)
{
	PMRect paintBounds;
		
	PMMatrix itoview = ::InnerToOuterMatrix( coordinateSpace, this);
	
	itoview.PostConcat (viewXform);
		
	if ( fGeometry != nil )
	{			
		paintBounds = fGeometry->GetStrokeBoundingBox(itoview);
	
		// allow for any possible rounding later
		if ( !paintBounds.IsEmpty() )
			paintBounds.Inset(-1, -1);
	}

	UnionPageItemAdornmentPaintedBBox(paintBounds, itoview);

	return paintBounds;
}



PMRect CShape::GetPrintedBBox( const PMMatrix& xform, const Transform::CoordinateSpace& coordinateSpace, bool32 includeAdornments)
{
	PMRect printBounds;
	
	if( fGeometry == nil )
		printBounds = GetPaintedBBox( xform, coordinateSpace);
	else
	{
		PMMatrix itoview = ::InnerToOuterMatrix( coordinateSpace, this);
	
		itoview.PostConcat (xform);
	
		printBounds = fGeometry->GetStrokeBoundingBox(itoview);

		if ( includeAdornments )
			UnionPrintingPageItemAdornmentPaintedBBox(printBounds, itoview);
	}
	
	return printBounds;
}




// call callback for each item in this shapes hierarchy
void CShape::IterateShapeDrawOrder_(const PMMatrix *totalMasterSpread2layoutSpreadOffset, ICallback *callbackInfo, int32 flags)
{
#if 0 && DEBUG && MACINTOSH
	UID myUID = ::GetUID(this);
	DebugClassUtilsBuffer classBuf;
	char buf[1024];
	::snprintf( buf, 1024, "%s", DebugClassUtils::GetIDName( &classBuf, ::GetClass(this)));
#endif
	
	InterfacePtr<IDrwEvtDispatcher> drawEventDispatcher(GetExecutionContextSession(), IID_IDRWEVTDISPATCHER);
	bool16 handled = kFalse;
	
	if( !handled)
		handled = drawEventDispatcher->ProcessIterateEvent(kIterateFilterCheckMessage, this, /*xform,*/ callbackInfo, flags);
	if( !handled)
		handled = drawEventDispatcher->ProcessIterateEvent(kIterateShapeMessage, this, /*xform,*/ callbackInfo, flags);
	if( !handled)
		handled = drawEventDispatcher->ProcessIterateEvent(kBeginShapeIterateMessage, this, /*xform,*/ callbackInfo, flags);

	if( !handled)
	{
		callbackInfo->ExecuteCallback( totalMasterSpread2layoutSpreadOffset, this, flags);

		if (!(flags&kSkipChildren)) {
			IterateDrawOrderHierarchy( totalMasterSpread2layoutSpreadOffset, callbackInfo, flags);
		}
	}
	
	drawEventDispatcher->ProcessIterateEvent(kEndShapeIterateMessage, this, /*xform,*/ callbackInfo, flags);
}
		
		// Another helper methods for those objects that have children.  
void CShape::IterateDrawOrderHierarchy(const PMMatrix *totalMasterSpread2layoutSpreadOffset, ICallback *callbackInfo, int32 flags)
{
	const int32 sz = fHierarchy->GetChildCount();
	for (int32 i = 0; i < sz; i++)
	{
		InterfacePtr<IShape> shape(UIDRef(fDB, fHierarchy->GetChildUID(i)), IID_ISHAPE);
		
		// If can't get the shape, probably missing plugin
		if ( shape )
			shape->IterateShapeDrawOrder_( totalMasterSpread2layoutSpreadOffset, callbackInfo, flags);

		// Now iterate TOP items if requested
		if (flags & IShape::kIncludeTOPPageItems)
		{
			InterfacePtr<IMainItemTOPData> mainItemTOPData(shape,UseDefaultIID());
			if (mainItemTOPData)
			{
			    InterfacePtr<IMultiColumnTextFrame> mcf(mainItemTOPData->QueryTOPMCTextFrame());
				InterfacePtr<IShape> mcfShape(mcf, UseDefaultIID());
				if (mcfShape)
					mcfShape->IterateShapeDrawOrder_( totalMasterSpread2layoutSpreadOffset, callbackInfo, flags);
			}
		}
	}
}

void CShape::Inval(GraphicsData *gd, ClassID reasonForInval, int32 flags)
{
	IDrwEvtDispatcher* drawEventDispatcher = gd->GetDrawEventDispatcher();
	
	// bail out if the shape is being filtered out
	if (drawEventDispatcher->ProcessInvalFilterEvent( this, gd, flags))
		return;

	if (gd->GetView() != nil)		// can't invalidate without an IControlView
	{	
		// If item not in hierarchy, don't invalidate
		if (fHierarchy && fHierarchy->GetSpreadUID() == kInvalidUID)
			return;

		PMRect invalRect = GetPaintedBBox(gd->GetContentToViewMatrix(), Transform::PasteboardCoordinates());

		IHandleShape* handleShape = fHandleShape;
		
		if ( (flags & kPathSelection) && fPathHandleShape ) {
			InterfacePtr<IPathGeometry> iPathGeometry(fPathHandleShape, IID_IPATHGEOMETRY);
			if ( iPathGeometry && iPathGeometry->GetNumPaths() > 0 )
				handleShape = fPathHandleShape;
		}
		
		if ( !invalRect.IsEmpty() )
		{
			ILayoutController* layoutInval = gd->GetLayoutController();
			
			if ( layoutInval )
			{	
				PMRect handleRect;
				Utils<IEventUtils> eventUtils;
				bool16 isTextFrame(Utils<IPageItemTypeUtils>()->IsTextFrame(this));
				bool16 invalSelection = isTextFrame;
				if ( !invalSelection )
				{
					InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryViewSelectionManager( gd->GetView()));
					invalSelection = selectionManager->SelectionExists(kInvalidClass, ISelectionManager::kAnySelection);
				}
				
				if ( invalSelection && handleShape != nil && !(eventUtils && eventUtils->IsDragOrTrackInProgress()) )
				{
					handleRect = handleShape->GetPaintedHandleBounds( gd->GetContentToViewMatrix());
				
					if ( !handleRect.IsEmpty() )
					{
						// rgano: bug #636019 - The overset indicator is drawn by both
						// the handles and the text. Unfortunately only the handles
						// admit that they draw the indicator. This means that when we
						// delete an overset text frame the inval for the content does
						// not include the indicator. This check allows us to inval a
						// large enough area while not invalling an area too large in
						// cases where the frame shape is accurate. Ideally this would
						// be removed and CShape would add the overset indicator to its
						// size. This couldn't be done now because of cached bounds
						// problems.
						if (isTextFrame)
							layoutInval->InvalidateContent (&handleRect, kTrue);
						else
							layoutInval->InvalidateSelection (&handleRect, kTrue);
					}
				}

				// Make sure drag or track is not in progress, image ghosting could be on and intersecting
				// with parent at this point would leave large portions of image on screen. No way to
				// determine for sure if image ghosting is on since the flags passed in are just inval flags, not draw flags,
				// so only kPathSelection is possibly set.
				// See bugs #0624180, #1704632, and #2428089 for more info.
				if ( !(eventUtils && eventUtils->IsDragOrTrackInProgress()) )
				{
					InterfacePtr<IHierarchy> parentHierarchy(fHierarchy->QueryParent());
					InterfacePtr<IShape> parentShape(parentHierarchy, UseDefaultIID());		

					if ( parentShape &&  Utils<IPageItemTypeUtils>()->IsGraphicFrame(parentShape) )
					{
						PMRect parentBounds = parentShape->GetPaintedBBox(gd->GetContentToViewMatrix(), Transform::PasteboardCoordinates());
						invalRect = ::Intersection(parentBounds, invalRect);
					}
				}
				
				if ( !invalRect.IsEmpty() )
				{
					layoutInval->InvalidateContent (&invalRect);
				}
			}
		}
		else
		{
			if (handleShape != nil)
				handleShape->Inval(gd, reasonForInval, flags);
		}
		
		InvalPageItemAdornments (IAdornmentShape::kAllAdornmentFlags, gd, reasonForInval, flags);

		InterfacePtr<IShapeGraphixCache> gfxCache(this,UseDefaultIID());
		if(gfxCache)
			gfxCache->Invalidate();
	}
}


/*-------------------------------------------------------------------------------------------------*/
/* Protected methods 																			   */
/*-------------------------------------------------------------------------------------------------*/
void CShape::DrawShape(GraphicsData* gd, int32 flags)
{
	// default DrawShape draws an XBox
	IGraphicsPort* gPort = gd->GetGraphicsPort();

	const PMRect r = fGeometry->GetStrokeBoundingBox();
	gPort->rectpath(r);
	gPort->gsave();
	gPort->setgray(0.6);	// [mvermurl 2/21/2008] Change gray to lighter value than 50% to avoid XOR draw problems - see Watson #1672550
	gPort->fill();
	gPort->grestore();
	gPort->moveto(r.Left(), r.Top());
	gPort->lineto(r.Right(), r.Bottom());
	gPort->moveto(r.Right(), r.Top());
	gPort->lineto(r.Left(), r.Bottom());
	gPort->setlinewidth(0);
	// (mdalton 3/3/3 - don't rely on the caller to have initialized
	// the graphics state to stroke with black.  This may be called as
	// a failure fallback and the currently installed paint server would
	// be used.  A bug is occuring where that server is an EPSPaint server
	// and not explicitly setting this causes ports to repeatedly attempt
	// to draw the contents of the paint server and puts us in and 
	// infinite loop.  Fixes bug 575320.
	gPort->setgray(0.0);
	gPort->stroke();
}

void CShape::DrawHierarchy(GraphicsData* gd, int32 flags)
{
#if 0 && DEBUG && MACINTOSH
	UID myUID = ::GetUID(this);
	DebugClassUtilsBuffer classBuf;
	char buf[1024];
	::snprintf( buf, 1024, "%s", DebugClassUtils::GetIDName( &classBuf, ::GetClass(this)));
#endif

	IGraphicsPort* gPort = gd->GetGraphicsPort();
	const int32 sz = fHierarchy->GetChildCount();
	IDrawMgr *drawMgr = gd->GetDrawManager();

	DrawPageItemAdornments(gd, flags, IAdornmentShape::kBeforeContent);

	for (int32 i = 0; i < sz; i++)
	{
		UID childUID = fHierarchy->GetChildUID(i);
		InterfacePtr<IShape> shape(UIDRef(fDB, childUID), IID_ISHAPE);

		AutoGSave autoGSave( gPort);
		::SetInnerToParentTransform( gPort, shape); //XFMoveFrom CShape::ProcessDrawShape

		// If can't get the shape, probably missing plugin
		if ( shape )
			shape->ProcessDrawShape(gd, flags);
			
		if ( drawMgr && drawMgr->WasDrawAborted() )
			break;		
	}

	DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterContent);
}


#if 0 && DEBUG && MACINTOSH
static void trace_me( const char* funcStr, const IPMUnknown* that)
{
	DebugClassUtilsBuffer buf;
	static int counter = 0;
	TRACEFLOW("CShape", "%d\t%s--%s\n", ++counter, funcStr, DebugClassUtils::GetIDName(&buf,::GetClass(that)));

	const int skip_frames = 5, show_frames = 9;
	StackCrawler::TraceStackCrawl("CShape", "CShapeStack", skip_frames, skip_frames + show_frames);

#if 0
	const int skip_frames = 4, show_frames = 6;
	int i;
	char* frameNames[show_frames + 1];
	for( i = 0; i <= show_frames; ++i) frameNames[i] = 0;
	StackCrawler::RecordStackCrawl( frameNames, skip_frames, skip_frames + show_frames);
	for( i = 0; frameNames[i]; ++i){
		char cString[4096];
		char *p = cString;
		for( int j = 2; j <= frameNames[i][0]; ++j) *p++ = frameNames[i][j];
		*p = 0;
		TRACEFLOW_OBSOLETE("TrackerStack", "\t%*s%s\n", 2*(i+1), "", cString);
	}
#endif
}
#endif



static void SetInnerToParentTransform(IGraphicsPort* gPort, const IShape* shape)
{
#if 0 && DEBUG && MACINTOSH
	trace_me( "SetInnerToParentTransform", shape);
#endif

#if 0 && DEBUG
	InterfacePtr<IPDFGStateStack const> pdfGState( gPort, UseDefaultIID());
	InterfacePtr<IRasterPort> rPort( gPort, UseDefaultIID());
	PMMatrix m1, m2, m3, m4;
	if( rPort)
		rPort->currentmatrix( &m1);
	if( pdfGState)
		m2 = pdfGState->GetCTM();
#endif

	InterfacePtr<ITransform> xform(shape, IID_ITRANSFORM);
	if (xform){
		PMMatrix m = xform->GetInnerToParentMatrix();
		gPort->concat(m);	

#if 0 && DEBUG
		if( rPort)
			rPort->currentmatrix( &m3);
		if( pdfGState)
			m4 = pdfGState->GetCTM();
#endif
	}
}




/*-------------------------------------------------------------------------------------------------*/
// Boolean checks
/*-------------------------------------------------------------------------------------------------*/
bool16 CShape::IsDynamic(int32 flags)
{
	const int32 dynamicMask = kDrawResizeDynamic + kDrawRotateDynamic + kDrawScaleDynamic + kDrawMoveDynamic + kDrawCreateDynamic;
	return (flags & dynamicMask) ? kTrue : kFalse;
}
bool16 CShape::IsPatientUser(int32 flags)
{
	return (flags & kPatientUser) != 0;
}
bool16 CShape::IsPrinting(int32 flags)
{
	return ((flags & kPrinting) != 0);
}

bool16 CShape::ShapeDisabled (GraphicsData *gd, int32 flags)
{
	return gd->GetGraphicsPort()->PortDrawMgr()->IsItemDisabled (::GetUID(this));
}

bool16 CShape::IsCacheValid() const
{
	if ( fPageItemCache )
		return fPageItemCache->IsShapeCacheValid();
	
	return kFalse;
}

void CShape::DrawPageItemAdornments(GraphicsData * gd, int32 flags, 
								   IAdornmentShape::AdornmentDrawOrder paintOrderMask)
{
	::DrawPageItemAdornments(fAdornmentList, this, gd, flags, paintOrderMask);
	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::DrawPageItemAdornments(globalAdornmentList, this, gd, flags, paintOrderMask);
}

void CShape::UnionPageItemAdornmentPaintedBBox(PMRect &paintBounds, const PMMatrix& innertoview)
{
	PMRect itemBounds (paintBounds);

	::UnionPageItemAdornmentPaintedBBox(fAdornmentList, this, itemBounds, paintBounds, innertoview);
	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::UnionPageItemAdornmentPaintedBBox(globalAdornmentList, this, itemBounds, paintBounds, innertoview);
}

void CShape::UnionPrintingPageItemAdornmentPaintedBBox(PMRect &printBounds, const PMMatrix& xform)
{
	PMRect itemBounds (printBounds);

	::UnionPrintingPageItemAdornmentPaintedBBox(fAdornmentList, this, itemBounds, printBounds, xform);
	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::UnionPrintingPageItemAdornmentPaintedBBox(globalAdornmentList, this, itemBounds, printBounds, xform);
}

void CShape::InvalPageItemAdornments 
	(
		IAdornmentShape::AdornmentDrawOrder drawOrder, 
		GraphicsData* gd, 
		ClassID reasonForInval, 
		int32 flags
	)
{
	::InvalPageItemAdornments(fAdornmentList, this, drawOrder, gd, reasonForInval, flags);
	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::InvalPageItemAdornments(globalAdornmentList, this, drawOrder, gd, reasonForInval, flags);
}
