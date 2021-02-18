//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationAdormentDrawer.cpp $
//  
//  Owner: SusanCL
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
//  Adapted from FrameLabelAdornment.cpp in SDK
//  
//  Draws the Form field frame adornment which include the name, and in the future, the
//  the form fields type icon.0
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IAnimationAdornmentDrawer.h"
#include "IShape.h"
#include "IGeometry.h"
#include "IGfxCapturePort.h"
#include "IGraphicsPort.h"
#include "ISession.h"
#include "IHierarchy.h"
#include "IDocument.h"
#include "IPathGeometry.h"
#include "IControlView.h"
#include "IRasterPort.h"
#include "IHandleShape.h"
#include "ITransform.h"
#include "IGraphicStyleDescriptor.h"
#include "IPDFLibraryUtilsPublic.h"
#include "IAnimationAttributeSuite.h"
#include "IAnimationAttributeData.h"
#include "IAnimationFacade.h"
#include "IAnimationUtils.h"
#include "IMotionPresetUtils.h"
#include "IConcreteSelection.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "ISelectionDataSuite.h"
#include "ILayoutUIUtils.h"
#include "IGraphicAttributeUtils.h"
#include "ISwatchUtils.h"

// ----- Implementation Includes -----

#include "AutoGSave.h"
#include "TransformUtils.h"
#include "GPortOutlineInfo.h"
#include "PMMatrix.h"
#include "widgetid.h"
#include "ColorizedIcon.h"
#include "DynamicDocumentsID.h"
#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsUIDefs.h"

// ----------------------------------------------------------------------------------------

//	Make the adornment icon width/height the same as button/MSO even though the actual
//	size of the icon is 21 x 18.
//	Make the icon scale multipliers and left-top placement of adornment the same as button/mso.
const PMReal kAdornmentIconWidth = 20.0;
const PMReal kAdornmentIconHeight = 16.0;
const PMReal kAdornmentTop = 4.0;
const PMReal kAdornmentLeft = 3.0;
const PMReal xIconMultiplier = 1.5;
const PMReal yIconMultiplier = 1.5;
// ----------------------------------------------------------------------------------------

//	Uncomment if drawing the animation proxy as item bbox.
//#define kDrawItemBBox

class AnimationAdornmentDrawer : public CPMUnknown<IAnimationAdornmentDrawer>
{

public:
	AnimationAdornmentDrawer(IPMUnknown *boss) : CPMUnknown<IAnimationAdornmentDrawer>(boss) {}
	
	virtual PMReal DrawAnimationAdornment (IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, int32 flags)
	{
		PMReal kNoOffset = 0.0;

		//	No animation, nothing to do.
		if (!Utils<Facade::IAnimationFacade> ()->PageItemHasAnimation (::GetUIDRef (iShape))) return kNoOffset;

		ASSERT (gd != nil);
		if (gd == nil) return kNoOffset;
		
		if (!(flags & IShape::kDrawFrameEdge) || (flags & IShape::kPreviewMode) || (flags & IShape::kPrinting))
			return kNoOffset;

		Utils<IPDFLibraryUtilsPublic const> utils;
		if (utils.Exists() && utils->IsPDFExportPort(gd->GetGraphicsPort()))
			return kNoOffset;

		InterfacePtr<IHierarchy> itemHier (iShape, UseDefaultIID ());
		ASSERT (itemHier != nil);
		if (itemHier == nil) return kNoOffset;

		IGraphicsPort * gPort = gd->GetGraphicsPort();
		ASSERT (gPort != nil);
		if (gPort == nil) return kNoOffset;

		InterfacePtr<IGeometry> itemGeometry(iShape, UseDefaultIID ());
		ASSERT (itemGeometry != nil);
		if (itemGeometry == nil ) return kNoOffset;

		//	Get the current transformation matrix for this object
		//	Don't draw adornment if too small.
		InterfacePtr<ITransform> xform (iShape, UseDefaultIID ());
		PMReal xScale = xform->GetItemScaleX();
		PMReal yScale = xform->GetItemScaleY();
		PMReal xyRatio = abs(yScale/xScale);
		
		// Get the scale factor for the view port
		PMReal viewPortScale = 1.0;
		IRasterPort *rasterPort = gd->GetRasterPort();	
		if (rasterPort)
		{
			PMMatrix viewPortMatrix;
			rasterPort->currentmatrix(&viewPortMatrix);
			viewPortScale = abs(viewPortMatrix.GetXScale());
		}
		
		// Check if the view port scale has gotten so small we shouldn't display the adornment
		PMRect pageItemBBox = itemGeometry->GetPathBoundingBox();
		PMRect scaledBBox(0.0, 0.0, pageItemBBox.Width()*viewPortScale, pageItemBBox.Height()*viewPortScale*xyRatio);
		InterfacePtr<IGfxCapturePort> capturePort(gPort,UseDefaultIID()); 
		if(!capturePort)
		{
			if (pageItemBBox.Width()*viewPortScale < 10.0 || pageItemBBox.Height()*viewPortScale*xyRatio < 10.0 ) return kNoOffset;
			if (pageItemBBox.Width()*viewPortScale < 2.5*kAdornmentIconWidth || pageItemBBox.Height()*viewPortScale*xyRatio < 1.5*kAdornmentIconHeight) return kNoOffset;
		}

		PMMatrix myMatrix;
		PMReal rotAngle = xform->GetItemRotationAngle();
		PMReal itemWidth = pageItemBBox.Width ();
		PMReal itemHeight = pageItemBBox.Height ();

		//	xformPoint is the left-top position where the adornment will draw.
		PMPoint xformPoint,anchorPoint;

		if (yScale >= 0.0 )
		{
			if (rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0)
			{
				xformPoint = PMPoint (pageItemBBox.Right () - (kAdornmentIconWidth*xIconMultiplier)/viewPortScale, pageItemBBox.Bottom () - (kAdornmentIconHeight*yIconMultiplier)/viewPortScale);
				anchorPoint = PMPoint( pageItemBBox.Right(), pageItemBBox.Bottom());
			}
			else
			{
				xformPoint = PMPoint (pageItemBBox.Left () + (kAdornmentIconWidth*xIconMultiplier)/viewPortScale, pageItemBBox.Top () + (kAdornmentIconHeight*yIconMultiplier)/viewPortScale);
				myMatrix = PMMatrix( -1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
				anchorPoint = PMPoint( pageItemBBox.Left(), pageItemBBox.Top());
			}
		}
		else
		{
			if (rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0)
			{
				xformPoint = PMPoint (pageItemBBox.Right () - (kAdornmentIconWidth*xIconMultiplier)/viewPortScale, pageItemBBox.Top () + (kAdornmentIconHeight*yIconMultiplier)/viewPortScale);
				myMatrix = PMMatrix( 1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
				anchorPoint = PMPoint( pageItemBBox.Right(), pageItemBBox.Top());
			}
			else
			{
				xformPoint = PMPoint (pageItemBBox.Left()+(kAdornmentIconWidth*xIconMultiplier)/viewPortScale, pageItemBBox.Bottom()- (kAdornmentIconHeight*yIconMultiplier)/viewPortScale);
				myMatrix = PMMatrix( -1.0, 0.0, 0.0, 1.0, 0.0, 0.0 );
				anchorPoint = PMPoint( pageItemBBox.Left(), pageItemBBox.Bottom());
			}
		}

		//	Set up adornment icon to draw
		PMPoint iconLeftTop( kAdornmentLeft, kAdornmentTop );
		PMRsrcID rsrcID (kAnimationUIAnimationAdornmentIcon, kDynamicDocumentsUIPluginID);
		ColorizedIcon adornmentIcon (rsrcID);

		AutoGSave autogsave1(gPort);
		PMReal vt = std::max(((2.5 * kAdornmentIconWidth))/scaledBBox.Width(), 1.5 * kAdornmentIconHeight/(scaledBBox.Height()*xyRatio));
		if(capturePort) 
			capturePort->BeginFixedSizeGraphix(anchorPoint,vt); 

		gPort->concat( PMMatrix(1.0, 0.0, 0.0, 1.0, xformPoint.X(), xformPoint.Y()) );
		gPort->concat( PMMatrix(1.0/(viewPortScale), 0.0, 0.0, 1.0/(viewPortScale*xyRatio), 0.0, 0.0) );
		gPort->concat( myMatrix );

		//	Draw adornment (cyan-ish: 0.31, 0.6, 1.0)
		ColorArray adornmentColor;
		adornmentColor.push_back (0.0);
		adornmentColor.push_back (0.0);
		adornmentColor.push_back (0.0);
		gPort->setopacity(0.6, kFalse);

		//	Erase the area behind the icon
		{
			//	Scope this, so we auto save the port.
			AutoGSave autogsave2(gPort);
			gPort->newpath();
			gPort->setlinewidth(0);
			gPort->moveto( iconLeftTop.X() - 1.0, iconLeftTop.Y() - 1.0 );
			gPort->lineto( iconLeftTop.X() + kAdornmentIconWidth + 1.0, iconLeftTop.Y() - 1.0 );
			gPort->lineto( iconLeftTop.X() + kAdornmentIconWidth + 1.0, iconLeftTop.Y() + kAdornmentIconHeight + 1.0 );
			gPort->lineto( iconLeftTop.X() - 1.0, iconLeftTop.Y() + kAdornmentIconHeight + 1.0 );
			gPort->closepath();
			gPort->setrgbcolor(1.0, 1.0, 1.0);
			gPort->eofill();
		}

		gPort->setrgbcolor(adornmentColor[0], adornmentColor[1], adornmentColor[2]);
		adornmentIcon.Draw (gPort, iconLeftTop, adornmentColor);
		if(capturePort) 
			capturePort->EndFixedSizeGraphix();

		//	Why 2.0? well, just returning kAdornmentIconWidth makes the gap seems too large!
		return (kAdornmentIconWidth-2.0);
	}

	virtual PMRect GetPaintedProxyAdornmentHandleBounds(IHandleShape* iShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, 
			const PMRect& rItem, const PMMatrix& innertoview)
	{
		//	No animation, nothing to do.
		InterfacePtr<IControlView> iFrontView (Utils<ILayoutUIUtils> ()->QueryFrontView ());
		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryViewSelectionManager(iFrontView));
		InterfacePtr<IAnimationAttributeSuite> iAnimationSuite (selMgr, UseDefaultIID ());
		if (!iAnimationSuite || !iAnimationSuite->GetShowAnimationProxy ()) return rItem;

		if (!Utils<Facade::IAnimationFacade> ()->PageItemHasAnimation (::GetUIDRef (iShape))) return rItem;

		UIDRef pageItemRef = ::GetUIDRef(iShape);
		PMPoint proxyPosition;
		PMRect proxyBBox;
		PMReal proxyScaleX, proxyScaleY, ProxyRotation;
		if (!GetPageItemAnimationProxyValues (pageItemRef, proxyPosition, proxyBBox, proxyScaleX, proxyScaleY, ProxyRotation)) return rItem;

		//	Transform page item bbox at the proxy position, i.e. "point B".
		PMMatrix flashToInnerMx = Utils<IMotionPresetUtils> ()->FlashToInnerMatrix (pageItemRef);
		PMMatrix flashToView = flashToInnerMx*innertoview;

		flashToView.Transform(&proxyBBox);

		//	Add scale, skew, and rotation about the animation transform point.
		PMPoint animationXformPt = Utils<Facade::IAnimationFacade> ()->GetPageItemAnimationTransformOffsetPoint (pageItemRef);
		PMPoint xformAboutPoint (proxyBBox.Left ()+(proxyBBox.Width ()*animationXformPt.X ()), proxyBBox.Top ()+(proxyBBox.Height ()*animationXformPt.Y ()));

		InterfacePtr<ITransform> iTransform (iShape, UseDefaultIID ());
		PMReal xScale = iTransform->GetItemScaleX();
		PMReal yScale = iTransform->GetItemScaleY();
		PMReal skewAngle = iTransform->GetItemSkewAngle();
		PMReal rotAngle = iTransform->GetItemRotationAngle();

		PMMatrix myMatrix;
		myMatrix.ScaleFrom(xformAboutPoint, xScale*proxyScaleX, yScale*proxyScaleY);
		myMatrix.SkewFrom (xformAboutPoint, skewAngle, 0);
		myMatrix.RotateAbout(xformAboutPoint, rotAngle+ProxyRotation);
		myMatrix.Transform (&proxyBBox);

		PMRect newItemBounds = rItem;
		newItemBounds.Union (proxyBBox);

		return newItemBounds;
	}

	virtual void DrawAnimationProxy (IHandleShape* iShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags)
	{
		InterfacePtr<IAnimationAttributeData> iAnimationData (iShape, UseDefaultIID ());
		if (iAnimationData == nil || !iAnimationData->HasAnimation ()) return;
		
		InterfacePtr<IAnimationAttributeSuite> iAnimationSuite (concreteSelection, UseDefaultIID ());
		if (!iAnimationSuite || !iAnimationSuite->GetShowAnimationProxy ()) return;

		IGraphicsPort * gPort = gd->GetGraphicsPort();
		ASSERT (gPort != nil);
		if (gPort == nil) return;

		InterfacePtr<IGeometry> itemGeometry(iShape, UseDefaultIID ());
		ASSERT (itemGeometry != nil);
		if (itemGeometry == nil ) return;

		// Get the scale factor for the view port
		PMReal viewPortScale = 1.0;
		IRasterPort *rasterPort = gd->GetRasterPort();	
		if (rasterPort)
		{
			PMMatrix viewPortMatrix;
			rasterPort->currentmatrix(&viewPortMatrix);
			viewPortScale = abs(viewPortMatrix.GetXScale());
		}

		//	Don't draw a proxy if no motion path.
		UIDRef pageItemRef = ::GetUIDRef(iShape);
		PMPoint proxyPosition;
		PMRect proxyBBox;
		PMReal proxyScaleX, proxyScaleY, proxyRotation;
		if (!GetPageItemAnimationProxyValues (pageItemRef, proxyPosition, proxyBBox, proxyScaleX, proxyScaleY, proxyRotation)) return;

		PMMatrix flashToInnerMx = Utils<IMotionPresetUtils> ()->FlashToInnerMatrix (pageItemRef);

		//	At this point, the position is relative to page item coordinate (or inner).
#ifndef kDrawItemBBox
		{
			AutoGSave autogsave1(gPort);

			//	Put in flash coordinate and add scale and rotation
			gPort->concat(flashToInnerMx);

			PMMatrix myMatrix;
			PMPoint aboutPoint = PMPoint (proxyPosition.X(), proxyPosition.Y());
			myMatrix.Translate (aboutPoint.X(), aboutPoint.Y());
			myMatrix.ScaleFrom(aboutPoint, proxyScaleX, proxyScaleY);
			myMatrix.RotateAbout (aboutPoint, proxyRotation);
			gPort->concat(myMatrix);

			//	Restore to inner
			flashToInnerMx.Invert ();
			gPort->concat(flashToInnerMx);

			this->GetItemOutlineInfo (iShape, gPort, viewPortScale);
		}

#else
		{
			//	Get item transformation values.
			InterfacePtr<ITransform> iTransform (iShape, UseDefaultIID ());
			PMReal xScale = iTransform->GetItemScaleX();
			PMReal yScale = iTransform->GetItemScaleY();
			PMReal skewAngle = iTransform->GetItemSkewAngle();
			PMReal rotAngle = iTransform->GetItemRotationAngle();
			
			AutoGSave autogsave2(gPort);
			gPort->concat(flashToInnerMx);

			PMMatrix myMatrix;
			PMPoint aboutPoint (proxyPosition.X (), proxyPosition.Y ());
			myMatrix.ScaleFrom(aboutPoint, xScale*proxyScaleX, yScale*proxyScaleY);
			myMatrix.SkewFrom (aboutPoint, skewAngle, 0);
			myMatrix.RotateAbout(aboutPoint, rotAngle+proxyRotation);
			gPort->concat(myMatrix);

			gPort->setopacity(0.6, kFalse);
			gPort->newpath();
			gPort->setlinewidth(0);
			gPort->moveto( proxyBBox.Left (), proxyBBox.Top ());
			gPort->lineto( proxyBBox.Right (), proxyBBox.Top ());
			gPort->lineto( proxyBBox.Right (), proxyBBox.Bottom ());
			gPort->lineto( proxyBBox.Left (), proxyBBox.Bottom ());
			gPort->closepath();
			gPort->setrgbcolor(0.7, 0.3, 0.3);
			gPort->fill();
		}
#endif	//	#ifndef kDrawItemBBox
	}

private:

	//	Returns false if no motion path.
	bool GetPageItemAnimationProxyValues (const UIDRef& pageItemRef, PMPoint& proxyPosition, PMRect& proxyBBox, 
		PMReal& proxyScaleX, PMReal& proxyScaleY, PMReal& proxyRotation) const
	{
		std::vector<PMPoint> proxyPositions;
		std::vector<PMPoint> proxyScales;
		std::vector<PMReal> proxyRotations;
		std::vector<PMReal> proxyAlphas;
		if (!Utils<IAnimationUtils> ()->GetPageItemAnimationFirstLastKeyframeValues (pageItemRef, proxyPositions, proxyScales, proxyRotations, proxyAlphas))
			return false;

		bool hasPosition = proxyPositions.size () > 1;
		bool hasRotation = proxyRotations.size () > 1;
		bool hasScaleX = proxyScales.size () > 1;
		bool hasScaleY = proxyScales.size () > 1;

		proxyPosition = PMPoint(0,0);
		proxyRotation = 0;
		proxyScaleX = 1.0;
		proxyScaleY = 1.0;

		int32 kFirstKf = 0;
		int32 kLastKf = 1;
		AnimationOptions animateOption = Utils<Facade::IAnimationFacade> ()->GetPageItemAnimationOption (pageItemRef);
		if (animateOption == kAnimateOffset)
		{
			proxyPosition = (hasPosition) ? proxyPositions [kFirstKf] : proxyPosition;
			proxyRotation = (hasRotation) ? proxyRotations [kFirstKf] : proxyRotation;
			proxyScaleX = (hasScaleX) ? proxyScales [kFirstKf].X()/100.0 : proxyScaleX;
			proxyScaleY = (hasScaleY) ? proxyScales [kFirstKf].Y()/100.0 : proxyScaleY;
		}
		else
		{
			proxyPosition = (hasPosition) ? proxyPositions [kLastKf] : proxyPosition;
			proxyRotation = (hasRotation) ? proxyRotations [kLastKf] : proxyRotation;
			proxyScaleX = (hasScaleX) ? proxyScales [kLastKf].X()/100.0 : proxyScaleX;
			proxyScaleY = (hasScaleY) ? proxyScales [kLastKf].Y()/100.0 : proxyScaleY;
		}

		InterfacePtr<IGeometry> itemGeometry (pageItemRef, UseDefaultIID ());
		PMRect pageItemBBox = itemGeometry->GetPathBoundingBox();
		PMPoint animationXformPt = Utils<Facade::IAnimationFacade> ()->GetPageItemAnimationTransformOffsetPoint (pageItemRef);
		PMPoint leftTopPoint (proxyPosition.X ()-(pageItemBBox.Width ()*animationXformPt.X ()), proxyPosition.Y ()-(pageItemBBox.Height ()*animationXformPt.Y ()));

		proxyBBox.LeftTop (leftTopPoint);
		proxyBBox.RightBottom (PMPoint (leftTopPoint.X ()+pageItemBBox.Width (), leftTopPoint.Y ()+pageItemBBox.Height ()));
		return hasPosition;
	}
	
	void GetItemOutlineInfo (IShape* iShape, IGraphicsPort* gPort, const PMReal& viewPortScale)
	{
		GPortOutlineInfo outlineInfo (gPort); 
		InterfacePtr<IPathGeometry> itemPathGeometry(iShape, UseDefaultIID ());
		InterfacePtr<ITransform> itemTransform(iShape, UseDefaultIID ());
		if (itemPathGeometry->GetNumPaths() > 0)
		{
			AutoGSave autosave (gPort);
			gPort->setopacity(0.6, kFalse);
			gPort->setlinewidth(0);
			
			PMMatrix inner2ParentMx = itemTransform->GetInnerToParentMatrix ();
			gPort->concat (inner2ParentMx);
			
			itemPathGeometry->GetOutlineInfo (&outlineInfo);

			gPort->setrgbcolor(0.7, 0.7, 0.7);

			UID fillUID = kInvalidUID;
			InterfacePtr<IGraphicStyleDescriptor> iDescriptor (iShape, UseDefaultIID ());
			Utils<IGraphicAttributeUtils> ()->GetFillRenderingUID (fillUID, iDescriptor);

			if (itemPathGeometry->IsPathClosed (0) || fillUID != Utils<ISwatchUtils> ()->GetNoneSwatchUID (::GetDataBase (iShape)))
				gPort->eofill();
			else
			{
				PMReal strokeWeight = 0;
				Utils<IGraphicAttributeUtils> ()->GetVisibleStrokeWeight (strokeWeight, iDescriptor);
				gPort->setlinewidth(strokeWeight*viewPortScale);
				gPort->stroke();
			}
		}
		else
		{
			AutoGSave autosave (gPort);
			PMMatrix inner2ParentMx = itemTransform->GetInnerToParentMatrix ();
			gPort->concat (inner2ParentMx);

			InterfacePtr<IHierarchy> iItemHierarchy (iShape, UseDefaultIID ());
			int32 childCount = iItemHierarchy->GetChildCount ();
			for (int32 n = 0; n < childCount; ++n)
			{
				InterfacePtr<IHierarchy> iChildHier (iItemHierarchy->QueryChild (n));
				InterfacePtr<IShape> iChildShape (iChildHier, UseDefaultIID ());
				GetItemOutlineInfo (iChildShape, gPort, viewPortScale);
			}
		}
	}

	void GetItemOutlineInfo (IHandleShape* iShape, IGraphicsPort* gPort, const PMReal& viewPortScale)
	{
		GPortOutlineInfo outlineInfo (gPort); 
		InterfacePtr<IPathGeometry> itemPathGeometry(iShape, UseDefaultIID ());
		if (itemPathGeometry->GetNumPaths() > 0)
		{
			gPort->setopacity(0.6, kFalse);
			gPort->setlinewidth(0);
			
			itemPathGeometry->GetOutlineInfo (&outlineInfo);

			gPort->setrgbcolor(0.7, 0.7, 0.7);
			
			UID fillUID = kInvalidUID;
			InterfacePtr<IGraphicStyleDescriptor> iDescriptor (iShape, UseDefaultIID ());
			Utils<IGraphicAttributeUtils> ()->GetFillRenderingUID (fillUID, iDescriptor);

			if (itemPathGeometry->IsPathClosed (0) || fillUID != Utils<ISwatchUtils> ()->GetNoneSwatchUID (::GetDataBase (iShape)))
				gPort->eofill();
			else
			{
				PMReal strokeWeight = 0;	
				Utils<IGraphicAttributeUtils> ()->GetVisibleStrokeWeight (strokeWeight, iDescriptor);
				gPort->setlinewidth(strokeWeight*viewPortScale);
				gPort->stroke();
			}
		}
		else
		{
			InterfacePtr<IHierarchy> iItemHierarchy (iShape, UseDefaultIID ());
			int32 childCount = iItemHierarchy->GetChildCount ();
			for (int32 n = 0; n < childCount; ++n)
			{
				InterfacePtr<IHierarchy> iChildHier (iItemHierarchy->QueryChild (n));
				InterfacePtr<IShape> iChildShape (iChildHier, UseDefaultIID ());
				GetItemOutlineInfo (iChildShape, gPort, viewPortScale);
			}
		}
	}
};

CREATE_PMINTERFACE(AnimationAdornmentDrawer, kAnimationAdornmentDrawerImpl)

