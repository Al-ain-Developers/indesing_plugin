//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CGraphicFrameShape.cpp $
//  
//  Owner: Lonnie Millett
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
//  
//  Required legal notice, per Peter Ullmann:
//  
//  Adobe Patent or Adobe Patent Pending Invention Included Within this File
//  
//  Adobe patent application tracking P496, entitled Showing Clipped Portions Of An Image During Image Manipulation, inventors: Stephens
//  
//========================================================================================

#include "VCPublicHeaders.h"

// ----- Interfaces -----

#include "IControlView.h"
#include "IDrwEvtDispatcher.h"
#include "IDrawMgr.h"
#include "IDynamicDocumentsContext.h"
#include "IGeometry.h"
#include "IGraphicBounds.h"
#include "IGraphicFrameData.h"
#include "IGraphicsPort.h"
#include "IGraphicStyleDescriptor.h"
#include "IHierarchy.h"
#include "ILayoutScrollingInfo.h"
#include "IPageItemAdornmentList.h"
#include "IPathGeometry.h"
#include "IPathPageItem.h"
#include "IRasterPort.h"
#include "ISelectionDataSuite.h"
#include "ISelectionUtils.h"
#include "IShape.h"
#include "ISpreadLayer.h"
#include "ITransform.h"
#include "IViewPort.h"
#include "IViewPortAttributes.h"
#include "IXPAttributeUtils.h"
#include "ITouchWSSwitcher.h"

// ----- Includes -----

#include "AutoGSave.h"
#include "CGraphicFrameShape.h"
#include "GPortOutlineInfo.h"
#include "GraphicTypes.h"
#include "GraphicsData.h"
#include "ShuksanBravo.h"	//for kAGMOptionAAText and kAGMOptionNone
#include "Trace.h"

// ----- Utility files -----

#include "ErrorUtils.h"
#include "KeyStates.h"
#include "IGraphicAttributeUtils.h"
#include "IImageUtils.h"
#include "ILayoutUIUtils.h"
#include "TransformUtils.h"
#include "ISwatchUtils.h"
#include "DocumentContextID.h"
#include "XPID.h"

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(CGraphicFrameShape, kCGraphicFrameShapeImpl)

//----------------------------------------------------------------------------------------
// static IsGraphicTextFrame()
//----------------------------------------------------------------------------------------

static bool16 IsGraphicTextFrame( const IGraphicFrameData *pGraphicFrame )
{
	if( !pGraphicFrame )
		return kFalse;
	
	return (pGraphicFrame->GetTextContentUID() != kInvalidUID);
}

//----------------------------------------------------------------------------------------
// static HaveFill()
//----------------------------------------------------------------------------------------

static bool32 HaveFill(IShape *shape)
{
	bool32 bHaveFill = kFalse;
	
	InterfacePtr<IGraphicStyleDescriptor> graphicDesc(shape, IID_IGRAPHICSTYLE_DESCRIPTOR);
	UID fillRenderingUID = kInvalidUID;
	if ( graphicDesc && Utils<IGraphicAttributeUtils>()->GetFillRenderingUID (fillRenderingUID, graphicDesc) == kSuccess)
	{
		
		bHaveFill = ( fillRenderingUID != kInvalidUID && fillRenderingUID != Utils<ISwatchUtils>()->GetNoneSwatchUID (::GetDataBase(shape)) );
	}
	
	return bHaveFill;
}

//----------------------------------------------------------------------------------------
// static FillMayBeTransparent()
//----------------------------------------------------------------------------------------

static bool32 FillMayBeTransparent(IShape *iShape)
{
	Utils<IXPAttributeUtils> iXPUtils;
	InterfacePtr<IGraphicStyleDescriptor> iGfxDesc(iShape, UseDefaultIID());
	if (!iGfxDesc) return kFalse;

	IXPAttributeSuite::AttributeValue av;

	iXPUtils->GetAttributeValue(IXPAttributeSuite::kFillBlendingOpacity, av, iGfxDesc);
	if (av.GetReal() < 100.) return kTrue;

	iXPUtils->GetAttributeValue(IXPAttributeSuite::kFillFeatherMode, av, iGfxDesc);
	if (av.GetPMVignetteMode() != kVTMNone) return kTrue;

	iXPUtils->GetAttributeValue(IXPAttributeSuite::kFillDirectionalFeatherApply, av, iGfxDesc);
	if (av.GetBoolean()) return kTrue;

	iXPUtils->GetAttributeValue(IXPAttributeSuite::kFillGradientFeatherApply, av, iGfxDesc);
	if (av.GetBoolean()) return kTrue;

	return kFalse;
}

//----------------------------------------------------------------------------------------
// class AutoAntiAliasContext 
// (Use to create stack-safe antialias configuration of port.)
//----------------------------------------------------------------------------------------

class AutoAntiAliasContext
{
	IRasterPort* iRPort;
	int32 fAntiAlias;

public:
	AutoAntiAliasContext(GraphicsData* gd, IShape* iShape) : iRPort(gd->GetRasterPort()), fAntiAlias(kAGMOptionNone)
	{
		if (iRPort)
		{
			iRPort->setantialiaspolicy(&fAntiAlias);	// Returns previous antialias value
			
			DrawOptionsSet drawOptions = gd->GetDrawOptions(iShape);
			
			if (drawOptions.antiAlias)
			{
				// Note: This is intentional to avoid turning off AA flags someone else already set
				int32 aaFlags = fAntiAlias | (kAGMOptionAAGraphics | kAGMOptionLinearizeAAOnly);

#ifdef AA_IMAGES				
				aaFlags |= (kAGMOptionOverscanImage | kAGMOptionAAImages);
#endif
				
				iRPort->setantialiaspolicy(&aaFlags);
			}
			else 
			{
				// #2987040 - allow use of kAGMOptionOverscanImage when not anti-aliasing.
				// this permits SnapshotUtils to work around an AGM bug that can result in white horizontal
				// lines with scaling of almost 1.0
				int32 useFlags = fAntiAlias & kAGMOptionOverscanImage;
				if ( useFlags ) iRPort->setantialiaspolicy(&useFlags);
			}
		}
	}

	~AutoAntiAliasContext()
	{
		if (iRPort) iRPort->setantialiaspolicy(&fAntiAlias);	// Returns previous antialias value
	}
};

//========================================================================================
// CLASS CGraphicFrameShape
//========================================================================================

//----------------------------------------------------------------------------------------
// CGraphicFrameShape constructor 
//----------------------------------------------------------------------------------------

CGraphicFrameShape::CGraphicFrameShape(IPMUnknown *boss)
	: CPathShape(boss)
{
	fFrameData = (IGraphicFrameData*) QueryInterface (IID_IGRAPHICFRAMEDATA);
	if ( fFrameData )
		fFrameData->Release();
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape destructor 
//----------------------------------------------------------------------------------------

CGraphicFrameShape::~CGraphicFrameShape()
{
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::IsGraphicFrame 
//----------------------------------------------------------------------------------------

bool16 CGraphicFrameShape::IsGraphicFrame() const
{
	if (fFrameData != nil)
		return fFrameData->IsGraphicFrame();
	else
		return kFalse;
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::DrawShape 
//----------------------------------------------------------------------------------------

void CGraphicFrameShape::DrawShape(GraphicsData* gd, int32 flags)
{
#ifdef TRANSFORM_DEBUG
	InterfacePtr<IGeometry> geometry(this, UseDefaultIID());
	PMRect bb = geometry->GetPathBoundingBox();
	InterfacePtr<ITransform> transform(this, UseDefaultIID());
	PMMatrix ctm(transform->CurrentMatrix());

	TRACEFLOW_OBSOLETE("DrawShape", "\nCGraphicFrameShape([%f %f %f %f], [%f %f %f %f %f %f])\n",
		bb.Left(), bb.Bottom(), bb.Right(), bb.Top(),
		ctm.GetRotationAngle(), ctm.GetXSkewAngle(), ctm.GetXScale(), ctm.GetYScale(), ctm.GetXTranslation(), ctm.GetYTranslation());
	PMMatrix itopb;
	transform->GetInnerToRootMatrix(&itopb); 
	TRACEFLOW_OBSOLETE("DrawShape", "      itopb([%f %f %f %f %f %f])\n",
		itopb.GetRotationAngle(), itopb.GetXSkewAngle(), itopb.GetXScale(), itopb.GetYScale(), itopb.GetXTranslation(), itopb.GetYTranslation());
#endif

	IDrawMgr *iDrawMgr = gd->GetDrawManager();

	// Installs AA state into RPort and undoes it on (possibly early) exit
	AutoAntiAliasContext aa(gd, this); 

	// Put the path in gstate and then do the fill within a gsave/grestore so the path
	// is still in gstate when we stroke. (There are exceptions; see kXPNeedPathReissueVPAttr.) 

	fPathPageItem->CopyPath(gd->GetGraphicsPort());
	
	DrawShape_Fill(gd, flags);

	if ((iDrawMgr && iDrawMgr->WasDrawAborted()) || ErrorUtils::PMGetGlobalErrorCode() != kSuccess )
		return;

	DrawShape_Hierarchy(gd, flags);
	
	if ((iDrawMgr && iDrawMgr->WasDrawAborted()) || ErrorUtils::PMGetGlobalErrorCode() != kSuccess )
		return;

	DrawShape_Stroke(gd, flags);
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::DrawShape_Fill
//----------------------------------------------------------------------------------------

void CGraphicFrameShape::DrawShape_Fill(GraphicsData* gd, int32 flags)
{
	IGraphicsPort* gPort = gd->GetGraphicsPort();
	IViewPortAttributes* iAttrs = gd->GetViewPortAttributes();
	IDrwEvtDispatcher* iDispatcher = gd->GetDrawEventDispatcher();
	
	if (!iDispatcher->ProcessDrawEvent(kBeginFrameFillDrawMessage, this, gd, flags))
	{
		AutoGSave autoGSave(gPort);

		//Draw kBeforeFill Adornments
		// Note: gstate depth and even the port itself may change in this call; it's not 
		// required to be symmetric. For example transparency effects can gsave or swap in
		// a new port at this point. However, gstate MUST return to the same level after the 
		// corresponding kAfterFill below.
		DrawPageItemAdornments(gd, flags, IAdornmentShape::kBeforeFill);

		// For various reasons it may be required to re-establish the path after adornments
		// are drawn.  This occurs primarily for transparency operations, thus the VPAttr here.
		// Note that this vpattr is dynamically set by the adornments so don't store this off 
		// in a local and reuse it later.
		if (iAttrs->GetAttr(kXPNeedPathReissueVPAttr))
			fPathPageItem->CopyPath( gPort ) ;

		InterfacePtr<IDynamicDocumentsContext> iDDContext(gPort, UseDefaultIID());

#ifdef PRERELEASE
		bool16 isGraphicTextFrame(kFalse);
		if (iDDContext && (isGraphicTextFrame = ::IsGraphicTextFrame( fFrameData )))
			iDDContext->BeginGraphicTextFrameFill();
#endif

		bool isGraphicFrame(kFalse);
		if (iDDContext && (isGraphicFrame = (fFrameData != nil)))
			iDDContext->BeginGraphicFrameFill(::GetUID(fFrameData));

		fPathPageItem->Fill( gPort ) ;

		if (isGraphicFrame)
			iDDContext->EndGraphicFrameFill();

#ifdef PRERELEASE
		if (isGraphicTextFrame)
			iDDContext->EndGraphicTextFrameFill();
#endif
		
		//Draw kAfterFill Adornments
		// As suggested above this may be asymmetric wrt gstate but if so it is to restore the
		// gstack level back to before the kBeforeFill.
		DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterFill);
	}
	iDispatcher->ProcessDrawEvent(kEndFrameFillDrawMessage, this, gd, flags);
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::DrawShape_Hierarchy
//----------------------------------------------------------------------------------------

void CGraphicFrameShape::DrawShape_Hierarchy(GraphicsData* gd, int32 flags)
{
	IDrwEvtDispatcher* iDispatcher = gd->GetDrawEventDispatcher();
	
	if (!iDispatcher->ProcessDrawEvent(kBeginFrameHierarchyDrawMessage, this, gd, flags))
	{
		if ( fHierarchy->GetChildCount() > 0 )
		{
			IGraphicsPort* gPort = gd->GetGraphicsPort();

			// MJP: A logical next step is to move the ghosting code into a draw event.

			// ***Adobe patent application tracking number P496, entitled Showing Clipped Portions Of An Image During Image Manipulation, inventors: Stephens
			InterfacePtr<ILayoutScrollingInfo> iLayoutScrollingInfo(gd->GetView(), UseDefaultIID());
			ILayoutScrollingInfo::ScrollingState scrollState = ILayoutScrollingInfo::kNormalScroll;
			bool32 doDrawGhostedImage = kFalse;
			
			if (fHierarchy->GetChildCount() == 1 && (flags & IShape::kPatientUser))
			{
				InterfacePtr<IGraphicBounds> iGraphicBounds(::GetDataBase(this), fHierarchy->GetChildUID(0), IID_IGRAPHICBOUNDS);
				if ( iGraphicBounds && Utils<IImageUtils>()->IsGraphic(iGraphicBounds) ) 
				{
					// Get some info on what is selected and what action is taking place
					InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryViewSelectionManager(gd->GetView()));
					InterfacePtr<const ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite (IID_ISELECTIONDATASUITE, selectionManager)));
					bool16 bDirectSelectMode = Utils<ILayoutUIUtils>()->GetPathSelectionMode();
					bool16 bDynamicResizing = ((flags & IShape::kDrawResizeDynamic) && !::IsCommandKeyPressed());
					bool16 bFrameAndContentMoving = ((flags & IShape::kDrawMoveDynamic) && ::IsCommandKeyPressed());
					int32 numItems = iSelectionDataSuite ? iSelectionDataSuite->GetSelectionCount() : 0;
					bool16 bFrameSelected = iSelectionDataSuite ? iSelectionDataSuite->IsItemSelected(this) : kFalse;
					bool16 bImageSelected = iSelectionDataSuite ? iSelectionDataSuite->IsItemSelected(iGraphicBounds) : kFalse;

					//check if this is an image selected in touch workspace. if yes, we
					//want to show ghosted image
					bool16 bImageSelectedInTouch(kFalse);
					if (bImageSelected && !bFrameSelected)
					{
						InterfacePtr<ITouchWSSwitcher> twsSwitcher(GetExecutionContextSession(), UseDefaultIID());
						bImageSelectedInTouch = twsSwitcher->GetCurrentWSMode() == ITouchWSSwitcher::kWorkspaceModeTouch;
					}

					// Show transparency effect if image is selected OR
					// or when in direct select mode (except when moving frame and content) OR
					// or when frame is selected and it is resizing (except if content is also resizing).
					if (numItems == 1 && (
						bImageSelected || 
						(bFrameSelected && bDirectSelectMode && !bFrameAndContentMoving) || 
						(bFrameSelected && bDynamicResizing) ||
						bImageSelectedInTouch))
					{
						InterfacePtr<IPathGeometry> clipPath(iGraphicBounds, IID_IPATHGEOMETRY);
						if ( clipPath && clipPath->GetNumPaths() > 0 )
							doDrawGhostedImage = kTrue;
						else {
							InterfacePtr<IGeometry> frameGeometry(this, IID_IGEOMETRY);
							if ( frameGeometry ) {
								PBPMRect frameBounds = frameGeometry->GetStrokeBoundingBox(::InnerToPasteboardMatrix(this));

								// We want to use the graphicbounds and not the geometry because the geometry may
								// only report the visible portion of the image where as the graphicbounds is guaranteed
								// to be the entire image.
								PBPMRect childBounds = iGraphicBounds->Get();
								::InnerToPasteboardMatrix(iGraphicBounds).Transform(&childBounds);

								// #2345079, in direct select mode we always want to ghost (except when duplicating, #2355725)
								if ( (bDirectSelectMode && !::IsOptionAltKeyPressed())
									|| childBounds.Left() < frameBounds.Left()
									|| childBounds.Top() < frameBounds.Top()
									|| childBounds.Right() > frameBounds.Right()
									|| childBounds.Bottom() > frameBounds.Bottom()
									)
								{
									// We have a cropped portion which needs to be drawn.
									doDrawGhostedImage = kTrue;
								}
							}
						}
					}
				}
			}

			if ( doDrawGhostedImage ) 
			{
				// We have a cropped portion which needs to be drawn unclipped.
				AutoGSave autoGSave(gPort);

				// If this frame contains a graphic and the frame or the graphic is selected,
				// and the graphic is cropped, then draw the cropped portion of the image
				// at 25% opacity.
				PMReal opacity(0.40);

				gPort->setopacity(opacity, kFalse);
				gPort->setblendingmode(kPMBlendNormal);

				// Make sure we do not draw the image in high quality mode
				if ( iLayoutScrollingInfo )
				{
					scrollState = iLayoutScrollingInfo->GetState();
					if ( scrollState == ILayoutScrollingInfo::kNormalScroll )
					{
						iLayoutScrollingInfo->Mute(kTrue);
						iLayoutScrollingInfo->SetState(ILayoutScrollingInfo::kOptimizedScroll);
					}
				}

				DrawHierarchy(gd, flags | IShape::kDrawingClippedOutImageData);
			}

			if ( doDrawGhostedImage && iLayoutScrollingInfo && scrollState == ILayoutScrollingInfo::kNormalScroll )
			{
				// A muted state allows to preserve the 'modified draw' objects which are touched by the dragged object, when
				// going back to normal scroll. At the end of drag, these objects are invalidated to get them re-drawn properly.
				iLayoutScrollingInfo->SetState(ILayoutScrollingInfo::kNormalScroll);
				iLayoutScrollingInfo->Mute(kFalse);
			}

			if ( doDrawGhostedImage && iLayoutScrollingInfo && scrollState == ILayoutScrollingInfo::kNormalScroll )
			{
				iLayoutScrollingInfo->Mute(kTrue);
				iLayoutScrollingInfo->SetState(ILayoutScrollingInfo::kOptimizedScroll);
			}

			// If we are generating a drop shadow or feather mask for a filled frame which
			// is clipping its content, then do not bother drawing the contents because it
			// will not affect the mask.  Note that this only applies if masking the whole
			// page item and not the frame content.  And you can't have fill opacity or else
			// the clipping really isn't complete.
			bool32 drawChildren = doDrawGhostedImage
				|| !(gd->GetViewPortAttributes()->GetAttr(kXPIsMaskPortVPAttr) 
					&& gd->GetViewPortAttributes()->GetAttr(kXPMaskingTargetVPAttr) != (int32)IXPAttributeSuite::kTargetContent)
				|| ::IsGraphicTextFrame( fFrameData ) 
				|| !HaveFill(this)
				|| FillMayBeTransparent(this);
				
			if ( drawChildren )
			{
				// Now draw the children
				AutoGSave autoGSave(gPort);
				
				// BP 12/04/97: #238222 Text that falls outside the graphic frame is clipped
				if ( !::IsGraphicTextFrame( fFrameData ) )
					fPathPageItem->Clip (gPort);
					
				DrawHierarchy(gd, flags);
			}
			
			if ( doDrawGhostedImage && iLayoutScrollingInfo && scrollState == ILayoutScrollingInfo::kNormalScroll )
			{
				iLayoutScrollingInfo->SetState(ILayoutScrollingInfo::kNormalScroll);
				iLayoutScrollingInfo->Mute(kFalse);
			}
		}
	}

	iDispatcher->ProcessDrawEvent(kEndFrameHierarchyDrawMessage, this, gd, flags);
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::DrawShape_Stroke
//----------------------------------------------------------------------------------------

void CGraphicFrameShape::DrawShape_Stroke(GraphicsData* gd, int32 flags)
{
	IDrwEvtDispatcher* iDispatcher = gd->GetDrawEventDispatcher();
	
	if (!iDispatcher->ProcessDrawEvent(kBeginFrameStrokeDrawMessage, this, gd, flags))
	{
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		IViewPortAttributes* iAttrs = gd->GetViewPortAttributes();

		//Draw kBeforeStroke Adornments
		// Note: gstate depth and even the port itself may change in this call; it's not 
		// required to be symmetric. For example transparency effects can gsave or swap in
		// a new port at this point. However, gstate MUST return to the same level after the 
		// corresponding kAfterStroke below.
		DrawPageItemAdornments(gd, flags, IAdornmentShape::kBeforeStroke);

		//Stroke the shape and leave it in the gPort
		// DStephens 6/5/2001 : Don't leave it in the port. Nobody needs the path
		// after it has been stroked.
		//	gPort->gsave();

		// For various reasons it may be required to re-establish the path after adornments
		// are drawn.  This occurs primarily for transparency operations, thus the VPAttr here.
		if (iAttrs->GetAttr(kXPNeedPathReissueVPAttr))
			fPathPageItem->CopyPath( gPort ) ;

		InterfacePtr<IDynamicDocumentsContext> iDDContext(gPort, UseDefaultIID());

#ifdef PRERELEASE
		bool16 isGraphicTextFrame(kFalse);
		if (iDDContext && (isGraphicTextFrame = ::IsGraphicTextFrame( fFrameData )))
			iDDContext->BeginGraphicTextFrameStroke();
#endif

		bool isGraphicFrame(kFalse);
		if (iDDContext && (isGraphicFrame = (fFrameData != nil)))
			iDDContext->BeginGraphicFrameStroke(::GetUID(fFrameData));

		fPathPageItem->Stroke( gPort ) ;
		//	gPort->grestore();

		if (isGraphicFrame)
			iDDContext->EndGraphicFrameStroke();

#ifdef PRERELEASE
		if (isGraphicTextFrame)
			iDDContext->EndGraphicTextFrameStroke();
#endif

		//Draw kAfterStroke Adornments
		// As suggested above this may be asymmetric wrt gstate but if so it is to restore the
		// gstack level back to before the kBeforeStroke.
		DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterStroke);
	}

	iDispatcher->ProcessDrawEvent(kEndFrameStrokeDrawMessage, this, gd, flags);
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::GetPaintedBBox
//----------------------------------------------------------------------------------------

PBPMRect CGraphicFrameShape::GetPaintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace)
{
	PBPMRect paintBounds(CPathShape::GetPaintedBBox( theMatrix, coordinateSpace));

	// BP 02/13/98: #229084 Text redraw problems after changing character attributes
	const UID textFrameUID = fFrameData->GetTextContentUID();

	if ( textFrameUID != kInvalidUID )
	{
		PMMatrix childMatrix = theMatrix;
		Transform::CoordinateSpace childCoordinateSpace = coordinateSpace;

		if( coordinateSpace == Transform::InnerCoordinates()){//Coordinate_Compare_OK
			childCoordinateSpace = Transform::ParentCoordinates(coordinateSpace.final_space);
		}else if( coordinateSpace == Transform::ParentCoordinates()){//Coordinate_Compare_OK
			InterfacePtr<ITransform> myTransform( this, UseDefaultIID());
			PMMatrix m = myTransform->GetInnerToParentMatrix();
			m.PermuteRightPast(coordinateSpace.final_space); //could just: childCoordinateSpace = Transform::ParentCoordinates(m*coordinateSpace.final_space);
			childMatrix.PreConcat( m);//instead of bringing m out to childMatrix
		}

		InterfacePtr<IShape> frameShape(::GetDataBase(this), textFrameUID, IID_ISHAPE);
		PMRect childBounds = frameShape->GetPaintedBBox (childMatrix, childCoordinateSpace);

		paintBounds.Union (childBounds);
	}
	
	return paintBounds;
}

//----------------------------------------------------------------------------------------
// CGraphicFrameShape::GetPrintedBBox
//----------------------------------------------------------------------------------------

PBPMRect CGraphicFrameShape::GetPrintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace, bool32 includeAdornments)
{
	PBPMRect paintBounds(CPathShape::GetPrintedBBox( theMatrix, coordinateSpace, includeAdornments));

	// BP 02/13/98: #229084 Text redraw problems after changing character attributes
	const UID textFrameUID = fFrameData->GetTextContentUID();

	if ( textFrameUID != kInvalidUID )
	{
		PMMatrix childMatrix = theMatrix;
		Transform::CoordinateSpace childCoordinateSpace = coordinateSpace;

		if( coordinateSpace == Transform::InnerCoordinates()){//Coordinate_Compare_OK
			childCoordinateSpace = Transform::ParentCoordinates(coordinateSpace.final_space);
		}else if( coordinateSpace == Transform::ParentCoordinates()){//Coordinate_Compare_OK
			InterfacePtr<ITransform> myTransform( this, UseDefaultIID());
			PMMatrix m = myTransform->GetInnerToParentMatrix();
			m.PermuteRightPast(coordinateSpace.final_space); //could just: childCoordinateSpace = Transform::ParentCoordinates(m*coordinateSpace.final_space);
			childMatrix.PreConcat( m);//instead of bringing m out to childMatrix
		}

		InterfacePtr<IShape> frameShape(::GetDataBase(this), textFrameUID, IID_ISHAPE);
		PMRect childBounds = frameShape->GetPrintedBBox (childMatrix, childCoordinateSpace, includeAdornments);

		paintBounds.Union (childBounds);
	}
	
	return paintBounds;
}

