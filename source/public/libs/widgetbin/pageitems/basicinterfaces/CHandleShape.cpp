//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/pageitems/basicinterfaces/CHandleShape.cpp $
//  
//  Owner:
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCWidgetHeaders.h"

// ----- Interfaces -----

#include "IAnchoredObjectData.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IDrawMgr.h"
#include "IFrameList.h"
#include "IGraphicFrameData.h"
#include "IGraphicsPort.h"
#include "IHierarchy.h"
#include "IItemContext.h"
#include "ILayoutController.h"
#include "IMainItemTOPData.h"
#include "IMoveTrackerData.h"
#include "IMultiColumnTextFrame.h"
#include "IOutlineInfo.h"
#include "IPageItemAdornmentList.h"
#include "IRasterPort.h"
#include "IResizeTrackerData.h"
#include "ISpreadLayer.h"
#include "ITextFrameColumn.h"
#include "ITextModel.h"
#include "ITextParcelList.h"
#include "ITool.h"
#include "ITouchWSUtils.h"
#include "ITracker.h"
#include "ITrackerFactory.h"
#include "IItemContextUtils.h"

// ----- Includes -----

#include "AutoGSave.h"
#include "CHandleShape.h"
#include "DVUtilities.h"

// ----- Utility files -----

#include "IGraphicsUtils.h"
#include "IFrameUtils.h"
#include "IGenericHandleDrawUtils.h"
#include "ILayerUtils.h"
#include "ILayoutUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemTypeUtils.h"
#include "IPageItemUtils.h"
#include "IToolBoxUtils.h"
#include "TransformUtils.h"
#include "TransformUtilsPrivate.h"
#include "iuicolorutils.h"

// ----- ID.h files -----

#include "TextEditorID.h"
#include "TextEditorImplID.h"


static void DrawAdornments(IPageItemAdornmentList* adornmentList, IHandleShape* shape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags)
{
	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			pShape->DrawAdornmentHandleShape(shape, drawOrder, gd, concreteSelection, flags);
		}
	}
}

static ITracker* QueryAdornmentTracker(IPageItemAdornmentList* adornmentList, IHandleShape* handleShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index)
{
	ITracker* iRetTracker = nil;


	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && !iRetTracker && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			iRetTracker = pShape->QueryTracker(handleShape, drawOrder, layView, where, selectionMode, index);
		}
	}
	return iRetTracker;
}

static void DrawAdornmentControlPointPath(IPageItemAdornmentList* adornmentList, IHandleShape* handleShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, int32 flags)
{
	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			pShape->DrawControlPointPath(handleShape, drawOrder, gd, flags);
		}
	}

}

static bool16 HitTestAdornment(IPageItemAdornmentList* adornmentList, IHandleShape* handleShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, const PMRect &r, PointSelector* handleIndex, bool16 bDragging)
{
	bool16 isHit = kFalse;
	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && !isHit && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			isHit = pShape->HitTest(handleShape, drawOrder, gd, r, handleIndex, bDragging);
		}
	}
	return isHit;
}

static bool16 HitTestAdornmentControlPointPath(IPageItemAdornmentList* adornmentList, IHandleShape* handleShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, const PMRect &r)
{
	bool16 isHit = kFalse;

	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && !isHit && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			isHit = pShape->HitTestControlPointPath(handleShape, drawOrder, gd, r);
		}
	}
	return isHit;
}

static PMRect GetPaintedAdornmentBounds(IPageItemAdornmentList* adornmentList, IHandleShape* handleShape, const PMRect& itemBounds, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, const PMMatrix& pbtoview)
{
	PMRect adornmentBounds;
	if (adornmentList && adornmentList->GetNumberOfHandleAdornments() > 0)
	{
		InterfacePtr<IAdornmentIterator> pIt(adornmentList->CreateIterator(drawOrder));
		IPMUnknown* punkAdorn = nil;

		while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
		{
			//Get the instance of the adornment
			InterfacePtr<IAdornmentHandleShape> pShape(punkAdorn, IID_IADORNMENTHANDLESHAPE);
			const PMRect& bBox = pShape->GetPaintedAdornmentHandleBounds(handleShape, drawOrder, itemBounds, pbtoview);

			if (!bBox.IsEmpty())
			{
				adornmentBounds.Union(bBox);
			}
		}
	}
	return adornmentBounds;
}

DEFINE_HELPER_METHODS(CHandleShape)

CHandleShape::CHandleShape(IPMUnknown *boss)
	: HELPER_METHODS_INIT(boss),
	fTextFrameUID(kInvalidUID)
{
	fGeometry = (IGeometry*) QueryInterface (IID_IGEOMETRY);
	if ( fGeometry )
		fGeometry->Release();

	fAdornmentList = (IPageItemAdornmentList*) QueryInterface (IID_IPAGEITEMADORNMENTLIST);
	if ( fAdornmentList )
		fAdornmentList->Release();
}

void CHandleShape::DrawHandleShape(GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags)
{
	if (!HandlesDisabled (gd, flags) )
	{
		InterfacePtr<IHierarchy> hierarchy(this, UseDefaultIID());

		UID layerUID = Utils<ILayerUtils>()->GetLayerUID(hierarchy);
		if( layerUID == kInvalidUID )
			return;

		IGraphicsPort* gPort = gd->GetGraphicsPort();
		AutoGSave autoGSave(gPort);

		if (!TransformFromRoot(this, gPort))
		{
			ASSERT_FAIL("TransformFromRoot failed.  OK to continue, but some handles may be positioned incorrectly.");
			gPort->grestore();
			gPort->gsave();
			PMMatrix xForm = ::InnerToPasteboardMatrix( this);
			gPort->concat(xForm);
		}

		if (flags & IShape::kUseXOR)
		{
			IRasterPort* rPort = gd->GetRasterPort();
			rPort->SetXORMode(kTrue);
		}

		SetHandleColor(gd, layerUID);
#if DEBUG
//Please leave these lines in. --shawn
//		DrawTransform( this, gd);
#endif
		DrawAdornments(IAdornmentHandleShape::kBeforeShape, gd, concreteSelection, flags);

		DrawPathImmediate(gd, flags);
		DrawHandlesImmediate(gd, concreteSelection, flags);

		int32	textflags;
		bool16 isTextFrame = Utils<IFrameUtils>()->IsTextFrame(this, &textflags);
		if (isTextFrame)
		{
			// --- Draw in/out port of text frame.
			DrawTextFrameHandles(gd, flags, textflags);
		}

		DrawAdornments(IAdornmentHandleShape::kAfterShape, gd, concreteSelection, flags);

		if (flags & IShape::kUseXOR)
		{
			IRasterPort* rPort = gd->GetRasterPort();
			rPort->SetXORMode(kFalse);
		}
	}
}

void CHandleShape::DrawControlPointPath(GraphicsData* gd, int32 flags)
{
	if (!HandlesDisabled (gd, flags) )
	{
		InterfacePtr<IHierarchy> hierarchy(this, UseDefaultIID());

		UID layerUID = Utils<ILayerUtils>()->GetLayerUID(hierarchy);
		if( layerUID == kInvalidUID )
			return;

		IGraphicsPort* gPort = gd->GetGraphicsPort();
		AutoGSave autoGSave(gPort);

		if (!TransformFromRoot(this, gPort))
		{
			ASSERT_FAIL("TransformFromRoot failed.  OK to continue, but some handles may be positioned incorrectly.");
			gPort->grestore();
			gPort->gsave();
			PMMatrix xForm = ::InnerToPasteboardMatrix( this);
			gPort->concat(xForm);
		}

		if (flags & IShape::kUseXOR)
		{
			IRasterPort* rPort = gd->GetRasterPort();
			rPort->SetXORMode(kTrue);
		}

		// if we are stroking snapped-to frames while rotating a page item, do not set the color to the layer color. [dstephens 09/19/2007]
		if ( !(flags & IShape::kDrawRotateDynamic) )
			SetHandleColor(gd, layerUID);

		DrawAdornmentControlPointPath (IAdornmentHandleShape::kBeforeShape, gd, flags);

		DrawPathImmediate(gd, flags);

		DrawAdornmentControlPointPath (IAdornmentHandleShape::kAfterShape, gd, flags);

		if (flags & IShape::kUseXOR)
		{
			IRasterPort* rPort = gd->GetRasterPort();
			rPort->SetXORMode(kFalse);
		}
	}
}


PMRect CHandleShape::GetPaintedHandleBounds(const PMMatrix& theMatrix)
{
	PMMatrix xForm = ::InnerToPasteboardMatrix( this);

	xForm.PostConcat (theMatrix);

	PMRect bounds(GetBBoxImmediate(xForm));

	PMRect txtHandleBounds(bounds);
	AddTextFrameHandleWidth (theMatrix, &txtHandleBounds); 

	GetPaintedAdornmentBounds (IAdornmentHandleShape::kAllAdornmentFlags, xForm, &bounds);
	bounds.Union(txtHandleBounds);
	
	// enlarge because our matrices and AGMs may differ slightly
	if ( !bounds.IsEmpty() )
		bounds.Inset (-1, -1);

	return bounds;
}


bool16 CHandleShape::HitTest(GraphicsData* gd, const PMRect &r, PointSelector* handleIndex, bool16 bDragging)
{
	IGraphicsPort* gPort = gd->GetGraphicsPort();
	AutoGSave autoGSave(gPort);

	PMMatrix xForm = ::InnerToPasteboardMatrix( this);
	gPort->concat(xForm);

	bool16 isHit = kFalse;

	isHit = HitTestAdornment (IAdornmentHandleShape::kAfterShape, gd, r, handleIndex, bDragging);

	if ( !isHit )
	{
		if (Utils<IFrameUtils>()->IsTextFrame(this, nil) && !bDragging)
			isHit = HitTestTextFrameHandles(gd, r, handleIndex, 0 /*textflags unused*/);

		if (!isHit)
			isHit = HitTestHandlesImmediate(gd, r, handleIndex);
	}

	if ( !isHit )
		isHit = HitTestAdornment (IAdornmentHandleShape::kBeforeShape, gd, r, handleIndex, bDragging);

	return isHit;
}


bool16 CHandleShape::HitTestControlPointPath(GraphicsData* gd, const PMRect &r)
{
	IGraphicsPort* gPort = gd->GetGraphicsPort();
	AutoGSave autoGSave(gPort);

	PMMatrix xForm = ::InnerToPasteboardMatrix( this);
	gPort->concat(xForm);

	bool16 isHit = HitTestPathImmediate( gd, r ) ;

	if ( !isHit )
		isHit = HitTestAdornmentControlPointPath (IAdornmentHandleShape::kAllAdornmentFlags, gd, r);

	return isHit;
}


void CHandleShape::Inval(GraphicsData *gd, ClassID reasonForInval, int32 flags)
{
	// The xform is set up correctly in GetPaintedBBox.
    PMRect invalRect = GetPaintedHandleBounds( gd->GetContentToViewMatrix());

	if ( !invalRect.IsEmpty() )
	{
		ILayoutController* layoutInval = gd->GetLayoutController();
		if ( layoutInval )
		{
			layoutInval->InvalidateSelection (&invalRect);
		}
	}
}

ITip* CHandleShape::QueryTip(const PointSelector* handleIndex)
{
  return nil;
}

ITracker* CHandleShape::QueryTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index)
{
	ITracker* theTracker = QueryAdornmentTracker (IAdornmentHandleShape::kAfterShape, layView, where, selectionMode, index);

	if ( theTracker )
		return theTracker;

	theTracker = QueryTextFrameTracker(layView, where, selectionMode, index);;

	if ( theTracker )
		return theTracker;

	theTracker = QueryAdornmentTracker (IAdornmentHandleShape::kBeforeShape, layView, where, selectionMode, index);

	if (!theTracker)
	{
		InterfacePtr<ITrackerFactory> factory(GetExecutionContextSession(), IID_ITRACKERFACTORY);

		// Provide the correct snap to and context (for MediaSystemen)
		InterfacePtr<IItemContext> context(Utils<IItemContextUtils>()->QueryItemContext3(layView, where));
		InterfacePtr<ISnapTo> snap(Utils<IItemContextUtils>()->QuerySnapTo(context));

		if (index.Selector() == kAnchorPt && index.PointIndex() == PMRect::kCenter && index.PathIndex() == 0)
		{
			// Query for the move tracker for this object if we have the center control point
			if (Utils<IPageItemTypeUtils>()->IsInline( this ))
			{
				// RCR 2/25/99 Resurrected ILGMoveTracker for the root inline item,
				// but not sub-selections which can still Drag and Drop
				theTracker = factory->QueryTracker(kFrameItemBoss, kILGMoveToolImpl);
			}

			if (!theTracker)
				theTracker = factory->QueryTracker(::GetClass(this), kMoveToolBoss);

			if (!theTracker)
			{
				InterfacePtr<ITool> activeTool (Utils<IToolBoxUtils>()->QueryActiveTool());
				theTracker = factory->QueryTracker(::GetClass(activeTool), kMoveToolBoss);
			}

			if ( theTracker )
			{
				theTracker->SetupSpecialTracker( layView, snap, context ) ;

				// DJB: moved IMoveTrackerData interface from Tracker over onto the LayoutWidget for DnD
				InterfacePtr<IMoveTrackerData> trackerData( layView, IID_IMOVETRACKERDATA ) ;
				if ( trackerData )
				{
					UIDList* itemList = new UIDList( ::GetUIDRef( this ) ) ;
					trackerData->Set( itemList, where, selectionMode, kTrue ) ;
				}
					
			}
		}
		else
		{
			// Query for the resize tracker for this object if we have a control point
			theTracker = factory->QueryTracker(::GetClass(this), kResizeToolBoss);
			if (theTracker)
			{
				theTracker->SetupSpecialTracker(layView, snap, context);

				InterfacePtr<IResizeTrackerData> trackerData(theTracker, IID_IRESIZETRACKERDATA);
				if (trackerData)
				{
					UIDList *itemList = new UIDList(::GetUIDRef(this));
					trackerData->Set(itemList, index);
				}
			}
		}
	}

	return theTracker;
}

ITracker* CHandleShape::QueryTextFrameTracker(IControlView *layView, const PBPMPoint& where, int32 selectionMode, const PointSelector& index)
{
	// See if we hit an in- or outport of a text frame.
	int32 textFramePartHit = Utils<IGenericHandleDrawUtils>()->HitTextFramePart(index);

	InterfacePtr<IGraphicFrameData>		gfd(this, UseDefaultIID());
	UID textFrameUID = Utils<IFrameUtils>()->GetTextFrameUID(this);
	if (textFrameUID != kInvalidUID && textFramePartHit != kNoTextFramePart && !Utils<IPageItemTypeUtils>()->IsPlacedInsideText(gfd)) {

		InterfacePtr<ITrackerFactory> factory(GetExecutionContextSession(), IID_ITRACKERFACTORY);

		ITracker* theTracker = factory->QueryTracker(kGenericToolBoss, kPrePlaceToolBoss);
		ASSERT_MSG(theTracker != nil, "nil tracker");
		theTracker->SetupTracker(layView);

		InterfacePtr<IResizeTrackerData> resizeData(theTracker, IID_IRESIZETRACKERDATA);
		if (resizeData)
		{
			UIDList *itemList = new UIDList(::GetDataBase(this), textFrameUID);
			resizeData->Set(itemList, index, kFalse);
		}

		InterfacePtr<IBoolData> boolData(theTracker, IID_IBOOLDATA);
		boolData->Set(index.PointIndex() == kTextFrameInPort);	// Can be kTextFrameInPort or kTextFrameOutPort

		return theTracker;
	}

	return nil;
}



bool16 CHandleShape::HandlesDisabled (GraphicsData* gd, int32 flags)
{
	return gd->GetGraphicsPort()->PortDrawMgr()->IsItemDisabled (::GetUID(this));
}


void CHandleShape::SetHandleColor(GraphicsData* gd, UID layerUID)
{
	IDataBase *db = ::GetDataBase(this);
	ASSERT_MSG(db != nil, "Nil Database!!!");

	// BP 03/26/99:  #299806 Inline graphics do inval when the size is ajusted larger so that the inline becomes overset
	//	I am changing this assert to a trace. You can select an inline and modify it so it will end up in overset.
	//	With my recent changes for 434@12034 the inline gets disconnected from its frame when it enters overset.
	//	But since the inline is still part of the selection it will be drawn. Getting to the layer's color requires
	//	the inline's ability to redirect to the frame.
#ifdef DEBUG
	ASSERT_MSG( layerUID != kInvalidUID || Utils<IPageItemTypeUtils>()->IsInline(this), "Current layer is Invalid!" );
	if( layerUID == kInvalidUID )
		TRACEFLOW_OBSOLETE("Old:Public",  "CHandleShape::SetHandleColor - can't get layer UID. Inline in overset?\n" );
#endif


	// BP 03/26/99: we should not crash...
	InterfacePtr<ISpreadLayer>theLayer( db, layerUID, IID_ISPREADLAYER );
	if( theLayer )
	{
		ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue( db, theLayer->GetColorUID() );

		fHandleRed = rgbColor[0];
		fHandleGreen = rgbColor[1];
		fHandleBlue = rgbColor[2];

		gd->GetGraphicsPort()->setrgbcolor(fHandleRed, fHandleGreen, fHandleBlue);
	}
}

bool16 CHandleShape::HitTestOneHandle( GraphicsData* gd, const PMRect& r, const PBPMPoint& point, PMRect::PointIndex whichPoint) const
{
	PMRect ptRect = PMRect(point);
	const PMMatrix&	theMatrix = gd->GetContentToViewMatrix() ;
	theMatrix.Transform( &ptRect ) ;
	PMReal insetAmount = kHitTestTolerance;
	if (Utils<ITouchWSUtils>()->IsAppInTouchWSMode())
		insetAmount = kHitTestTolerance_TWS * kTouchWSHitToleranceFactor;
	insetAmount *= -1;
	ptRect.Inset( /*-2.0*/ insetAmount, /*-2.0*/insetAmount);	// size = 4.0

	return ::Intersect( r, ptRect ) ;
}

static ITextModel* QueryTextModel(const IGraphicFrameData* frameData)
{
	InterfacePtr<IMultiColumnTextFrame> mcf(::GetDataBase(frameData), frameData->GetTextContentUID(), UseDefaultIID());
	if (mcf)
		return mcf->QueryTextModel();

	return nil;
}

void CHandleShape::TextFrameHandlesPath(GraphicsData* gd, int32 textflags, const PMPoint& point1, const PMPoint& point2)
{
	// BP 12/08/97: only graphic frames with text content draw text frame in/out ports.
	InterfacePtr<IGraphicFrameData>frameData(this, UseDefaultIID());
	if( !frameData || frameData->GetTextContentUID() == kInvalidUID )
		return;

	IGraphicsPort* gPort = gd->GetGraphicsPort();
	IRasterPort* rPort = gd->GetRasterPort();
	bool16 bTouchMode = Utils<ITouchWSUtils>()->IsAppInTouchWSMode();

	if (!bTouchMode)
	{
		Utils<IGraphicsUtils>()->CreateAnchorPointPath(rPort, gPort, point1, 8, kFalse);
		gPort->gsave();
		gPort->setrgbcolor(1.0, 1.0, 1.0);  // fill white unselected handles
		gPort->fill();
		gPort->grestore();

		gPort->stroke();
	}

	bool16 showOverset = kTrue;
	if (bTouchMode)
	{
		InterfacePtr<ITextModel> textModel(QueryTextModel(frameData));
		if (textModel)
		{
			InterfacePtr<IBoolData> userText(textModel, IID_IUSERTEXT);
			showOverset = userText->GetBool();
		}
	}

	if (	!bTouchMode ||	// If not in touch, create the box.
			((textflags & IFrameUtils::kTF_Overset)	&& showOverset)// If in touch, create the box only for overset case.
	   )
	{
		gPort->gsave();
		gPort->newpath();

		if (textflags & IFrameUtils::kTF_Overset)
			// THT - overset marker is always drawn in red
			gPort->setrgbcolor(1.0, 0.0, 0.0);

		Utils<IGraphicsUtils>()->CreateAnchorPointPath(rPort, gPort, point2, 8, kFalse);
		gPort->gsave();
		gPort->setrgbcolor(1.0, 1.0, 1.0);  // fill white unselected handles
		gPort->fill();
		gPort->grestore();

		gPort->stroke();

		// Restore gPort that we saved while creating the box for in-port/overset.
		gPort->grestore();
		gPort->newpath();
	}
}


void CHandleShape::DrawTextFrameHandles(GraphicsData *gd, int32 shapeflags, int32 textflags)
{
	// BP 12/08/97: only graphic frames with text content draw text frame in/out ports.
	InterfacePtr<IGraphicFrameData>frameData(this, UseDefaultIID());
	if( !frameData || frameData->GetTextContentUID() == kInvalidUID )
		return;

	IGraphicsPort* gPort = gd->GetGraphicsPort();
	IRasterPort* rPort = gd->GetRasterPort();

	bool16 bTouchMode = Utils<ITouchWSUtils>()->IsAppInTouchWSMode();

	gPort->setlinewidth(0);
	gPort->newpath();

	PMPoint	point1, point2;
	InterfacePtr<IHandleShape> pShape( this, IID_IPATHHANDLESHAPE );
	if ( pShape )
		Utils<IPageItemUtils>()->GetTextFrameHandlePositions(pShape, &point1, &point2);
	else
		Utils<IPageItemUtils>()->GetTextFrameHandlePositions(this, &point1, &point2);

	TextFrameHandlesPath(gd, textflags, point1, point2);

	// BP 12/13/97: #238779 The 'in' and 'out' text port icons are incorrectly positioned on vertically oriented frames.
	InterfacePtr<IMultiColumnTextFrame>mcf( ::GetDataBase( this ), frameData->GetTextContentUID(), UseDefaultIID() );
	InterfacePtr<IFrameList>pFrameList( mcf->QueryFrameList() );
	bool16 bVertical = kFalse;
	bool16 bRightToLeft = kFalse;

	if (pFrameList)
	{
		InterfacePtr<ITextParcelList> tpl(pFrameList, UseDefaultIID());
		bVertical = tpl->GetIsVertical();
		bRightToLeft = tpl->GetIsRightToLeft();
	}

	if (!bTouchMode && (textflags & IFrameUtils::kTF_InLink))
		Utils<IGraphicsUtils>()->CreateTextLinkPath(rPort, gPort, point1, bVertical, bRightToLeft);

	if (!bTouchMode && (textflags & IFrameUtils::kTF_OutLink))
		Utils<IGraphicsUtils>()->CreateTextLinkPath(rPort, gPort, point2, bVertical, bRightToLeft);
	else if (textflags & IFrameUtils::kTF_Overset)
	{
		bool16 showOverset = kTrue;
		if (bTouchMode)
		{
			InterfacePtr<ITextModel> textModel(QueryTextModel(frameData));
			if (textModel)
			{
				InterfacePtr<IBoolData> userText(textModel, IID_IUSERTEXT);
				showOverset = userText->GetBool();
			}
		}

		if (showOverset)
		{
			// gotta do this because we change the pen to red in CreateTextOversetPath
			AutoGSave autoGSave(gPort);

			Utils<IGraphicsUtils>()->CreateTextOversetPath(rPort, gPort, point2);
			gPort->stroke();
			gPort->newpath();
		}
	}
	gPort->stroke();
	gPort->newpath();
}


bool16 CHandleShape::HitTestTextFrameHandles(GraphicsData *gd, const PMRect &r, PointSelector *handleIndex, int32 textflags)
{
	// BP 12/08/97: only graphic frames with text content draw text frame in/out ports.
	InterfacePtr<IGraphicFrameData>frameData(this, UseDefaultIID());
	if( !frameData || frameData->GetTextContentUID() == kInvalidUID )
		return kFalse;

	// MM 01/08/98: disable ports if we are contained inline in another text frame
	if(Utils<IPageItemTypeUtils>()->IsPlacedInsideText(frameData))
		return kFalse;

	IGraphicsPort* gPort = gd->GetGraphicsPort();
	IRasterPort* rPort = gd->GetRasterPort();

	PMPoint	point1, point2;
 	InterfacePtr<IHandleShape> pShape( this, IID_IPATHHANDLESHAPE );
	if ( pShape )
		Utils<IPageItemUtils>()->GetTextFrameHandlePositions(pShape, &point1, &point2);
	else
		Utils<IPageItemUtils>()->GetTextFrameHandlePositions(this, &point1, &point2);

	Utils<IGraphicsUtils>()->CreateAnchorPointPath(rPort, gPort, point1, 6);

	bool16 isHit = ( rPort->infill( r ) != kPMNoHit ) ;
	gPort->newpath();	// clear the path

	if (!isHit)
		{
		Utils<IGraphicsUtils>()->CreateAnchorPointPath(rPort, gPort, point2, 6);
		isHit = ( rPort->infill( r ) != kPMNoHit ) ;
		gPort->newpath();	// clear the path
		if (isHit)
			handleIndex->PointIndex( kTextFrameOutPort ) ;
		}
	else
		handleIndex->PointIndex( kTextFrameInPort ) ;

	if (isHit)
		handleIndex->PathIndex( kHitTextFramePathIndex ) ;

	return isHit;
}


void CHandleShape::AddTextFrameHandleWidth (const PMMatrix& theMatrix, PMRect* itemBounds) const
{
	// 8 is the width of the text link boxes
	InterfacePtr<const IGraphicFrameData>		gfd(this, UseDefaultIID());
	bool16 checkThreads = gfd ? (gfd->GetTextContentUID() != kInvalidUID) : kFalse;
	bool16 bTextOnPath = kFalse;

	if (!checkThreads)
	{
		/*
			not sure what this can be?
			code checks for all general possibilities -  Rearchitect_Multi-Column_Frame
		*/
		InterfacePtr<const IMultiColumnTextFrame>	meFrame(this, UseDefaultIID());
		if (meFrame)
			checkThreads = kTrue;
	}

	//We could be in a Main item spline containing a TOP
	//Try to find out the TOP TextFrame
	UID		TOPSplineUID = kInvalidUID;
	if (!checkThreads)
	{
		InterfacePtr<IMainItemTOPData> mainItemTOPData(this, IID_IMAINITEMTOPDATA);
		if (mainItemTOPData)
		{
			TOPSplineUID = mainItemTOPData->GetTOPSplineItemUID();
			if (TOPSplineUID != kInvalidUID)	//It has  TOP
			{
				//Get the TOPSpline
				InterfacePtr<IHierarchy> hier(::GetDataBase(mainItemTOPData), TOPSplineUID, IID_IHIERARCHY);
				// Eric K. tells me that a text frame only as one child
				if (hier->GetChildCount() == 1) {
					InterfacePtr<IHierarchy> child(hier->QueryChild(0));
					InterfacePtr<ITextFrameColumn> tcf(child, UseDefaultIID());
					if (tcf)
					{
						checkThreads = bTextOnPath = kTrue;
					}
				}
			}
		}
		if (!checkThreads)
		{
			if (Utils<IPageItemTypeUtils>()->IsInline(this) &&
				Utils<IPageItemTypeUtils>()->GetInlinePosition(this) == IAnchoredObjectData::kAnchoredObject)
				checkThreads = kTrue;
		}
	}

	if (checkThreads)
	{
		itemBounds->Inset (-kThreadHandleSize / 2, -kThreadHandleSize / 2);

  		PMRect threadBounds;
		if(bTextOnPath)
		{
			InterfacePtr<IHandleShape> TOPSplineHandleShape(::GetDataBase(this), TOPSplineUID, IID_IHANDLESHAPE);
  			if (Utils<IFrameUtils>()->GetFrameThreadBBox(TOPSplineHandleShape, theMatrix, threadBounds))
  				itemBounds->Union(threadBounds);
		}
		else
		{
  			if (Utils<IFrameUtils>()->GetFrameThreadBBox((IHandleShape*)this, theMatrix, threadBounds))
  				itemBounds->Union(threadBounds);
		}
	}
}


void CHandleShape::DrawAdornments
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		GraphicsData* gd,
		IConcreteSelection* concreteSelection,
		int32 flags
	)
{
	::DrawAdornments(fAdornmentList, this, drawOrder, gd, concreteSelection, flags);

	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::DrawAdornments(globalAdornmentList, this, drawOrder, gd, concreteSelection, flags);
}


void CHandleShape::DrawAdornmentControlPointPath
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		GraphicsData* gd,
		int32 flags
	)
{
	::DrawAdornmentControlPointPath(fAdornmentList, this, drawOrder, gd, flags);

	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	::DrawAdornmentControlPointPath(globalAdornmentList, this, drawOrder, gd, flags);
}

bool16 CHandleShape::HitTestAdornment
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		GraphicsData* gd,
		const PMRect &r,
		PointSelector* handleIndex,
		bool16 bDragging
	)
{
	bool16 isHit = ::HitTestAdornment(fAdornmentList, this, drawOrder, gd, r, handleIndex, bDragging);
	if (!isHit)
	{
		InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
		isHit = ::HitTestAdornment(globalAdornmentList, this , drawOrder, gd, r, handleIndex, bDragging);
	}
	
	return isHit;
}

bool16 CHandleShape::HitTestAdornmentControlPointPath
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		GraphicsData* gd,
		const PMRect &r
	)
{
	bool16 isHit = ::HitTestAdornmentControlPointPath(fAdornmentList, this, drawOrder, gd, r);

	if (!isHit)
	{
		InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
		isHit = ::HitTestAdornmentControlPointPath(globalAdornmentList, this ,drawOrder, gd, r);
	}

	return isHit;
}

void CHandleShape::GetPaintedAdornmentBounds
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		const PMMatrix& pbtoview,
		PMRect* handleShapeBBox
	)
{
	PMRect itemBounds (*handleShapeBBox);

	handleShapeBBox->Union(::GetPaintedAdornmentBounds(fAdornmentList, this, itemBounds, drawOrder, pbtoview));

	InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
	handleShapeBBox->Union(::GetPaintedAdornmentBounds(globalAdornmentList, this, itemBounds, drawOrder, pbtoview));
}

ITracker* CHandleShape::QueryAdornmentTracker
	(
		IAdornmentHandleShape::AdornmentDrawOrder drawOrder,
		IControlView *layView,
		const PBPMPoint& where,
		int32 selectionMode,
		const PointSelector& index
	)
{
	ITracker* iRetTracker = nil;
	iRetTracker = ::QueryAdornmentTracker(fAdornmentList, this, drawOrder, layView, where, selectionMode, index);

	if (!iRetTracker)
	{
		InterfacePtr<IPageItemAdornmentList> globalAdornmentList(GetExecutionContextSession(), IID_IGLOBALPAGEITEMADORNMENTLIST);
		iRetTracker = ::QueryAdornmentTracker(globalAdornmentList, this, drawOrder, layView, where, selectionMode, index);
	}

	return iRetTracker;
}

bool16 CHandleShape::HasContent()
{
	InterfacePtr<IGraphicFrameData> iFrameData(this, UseDefaultIID());

	if ( !iFrameData )
		return kFalse;

	if ( iFrameData->IsGraphicFrame() )
		return kTrue;

	if ( iFrameData->GetTextContentUID() != kInvalidUID )
		return kTrue;

	return kFalse;
}


void CHandleShape::GetControlPointPathOutlineInfo (IOutlineInfo* iOutlineInfo)
{
	const PMRect& bbox = fGeometry->GetStrokeBoundingBox();

	iOutlineInfo->BeginPath();
	iOutlineInfo->moveto (bbox.Left(), bbox.Top());
	iOutlineInfo->lineto (bbox.Right(), bbox.Top());
	iOutlineInfo->lineto (bbox.Right(), bbox.Bottom());
	iOutlineInfo->lineto (bbox.Left(), bbox.Bottom());
	iOutlineInfo->closepath();
	iOutlineInfo->EndPath();
}
