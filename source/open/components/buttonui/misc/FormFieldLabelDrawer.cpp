//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/misc/FormFieldLabelDrawer.cpp $
//  
//  Owner: Mark VerMurlen
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

#include "IFormFieldLabelDrawer.h"
#include "IAnimationAdornmentDrawer.h"
#include "IShape.h"
#include "IGeometry.h"
#include "IGfxCapturePort.h"
#include "IGraphicsPort.h"
#include "IHandleShape.h"
#include "IFontMgr.h"
#include "ISession.h"
#include "IHierarchy.h"
#include "IDocument.h"
#include "IPathGeometry.h"
#include "IPMFont.h"
#include "IFontInstance.h"
#include "IInterfaceFonts.h"
#include "IControlView.h"
#include "IRasterPort.h"
#include "ISpreadLayer.h"
#include "ITransform.h"
#include "IDocumentLayer.h"
#include "IPDFLibraryUtilsPublic.h"
#include "IGraphicStyleDescriptor.h"
#include "IFormField.h"

// ----- Implementation Includes -----

//#include "AGMTypes.h"
#include "AutoGSave.h"
#include "iuicolorutils.h"
#include "TransformUtils.h"
#include "PMMatrix.h"
#include "PreferenceUtils.h"
#include "ILayoutUIUtils.h"
#include "widgetid.h"
#include "StringUtils.h"
#include "TextChar.h"
#include "FormFieldID.h"
#include "MediaID.h"
#include "AttributesUtils.h"
#include "ColorizedIcon.h"
#include "FormFieldUIID.h"

// ----------------------------------------------------------------------------------------

const PMReal kLabelPointSize = 12.0;
const PMReal kLabelVerticalGap = 4.0;
const PMReal kLabelSpace = 3.0;

const PMReal kIconWidth = 20.0;
const PMReal kIconHeight = 16.0;

// ----------------------------------------------------------------------------------------

class FormFieldLabelDrawer : public CPMUnknown<IFormFieldLabelDrawer>
{

public:
	FormFieldLabelDrawer(IPMUnknown *boss) : CPMUnknown<IFormFieldLabelDrawer>(boss) {}
	
	virtual void Draw
		(
			IShape* 							iShape,		// owning page item
			IAdornmentShape::AdornmentDrawOrder	drawOrder,	// for items that registered for more than one order
			GraphicsData*						gd,
			int32								flags
		);

private:
	bool16		HaveRoomForName( PMRect bounds );
	void		FitStringToWidth(IFontInstance *fontInstance, PMString &StringToFit, PMReal width) const;
	
};

// ----------------------------------------------------------------------------------------

CREATE_PMINTERFACE(FormFieldLabelDrawer, kFormFieldLabelDrawerImpl)

// ----------------------------------------------------------------------------------------

void FormFieldLabelDrawer::Draw
	(
		IShape* 							shape,		// owning page item
		IAdornmentShape::AdornmentDrawOrder	drawOrder,	// for items that registered for more than one order
		GraphicsData*						gd,
		int32								flags
	)
{
	
	if (gd == nil) {
	
		ASSERT_FAIL("FormFieldLabelDrawer::Draw: gd invalid");
		return;
	}
	
	if ( !(flags & IShape::kDrawFrameEdge) || (flags & IShape::kPreviewMode))
		return;
		
	if ( flags & IShape::kPrinting )
		return;

	//twright 10/30/2001
	//We don't need to do any of this when exporting to PDF.  And the icon stuff breaks
	//(while trying to set up the context for doing the bitmap, at least on the Mac)

	Utils<IPDFLibraryUtilsPublic const> utils;
	if (utils.Exists() && utils->IsPDFExportPort(gd->GetGraphicsPort()))
		return;

	InterfacePtr<IHierarchy> itemHier(shape, IID_IHIERARCHY);
	if (itemHier == nil)
	{
		ASSERT_FAIL("FormFieldLabelDrawer::Draw: hierachy unavailable");
		return;
	}

	InterfacePtr<IPMPersist> persist(itemHier, IID_IPMPERSIST);
	IDataBase* theDB = persist->GetDataBase();
	InterfacePtr<IDocument> theDoc(theDB, theDB->GetRootUID(), IID_IDOCUMENT);
	if (theDoc == nil)
	{
		ASSERT_FAIL("FormFieldLabelDrawer::Draw: doc database invalid");
		return;
	}

	PMReal iconOffset = 0;
	InterfacePtr<IAnimationAdornmentDrawer> iAdornmentDrawer (shape, UseDefaultIID ());
	if (iAdornmentDrawer)
	{
		iconOffset = iAdornmentDrawer->DrawAnimationAdornment (shape, drawOrder, gd, flags);
	}

	bool showIcon = true;
	bool showName = false;

	PMString formFieldName;
	
	//InterfacePtr<IGraphicStyleDescriptor> styleDescriptor(shape, ::UseDefaultIID());
	//formFieldName = AttributesUtils::GetStringValue( styleDescriptor,  kFormNameAttrBoss );
	//showName = !formFieldName.IsEmpty();


	// The graphics port is the port that the page item is currently drawing to.
	// That could be the screen, a printer, a PDF, or some other port:

	IGraphicsPort * gPort = gd->GetGraphicsPort();
	if (gPort == nil)
	{
		ASSERT_FAIL("FormFieldLabelDrawer::Draw: view port invalid");
		return;
	}

	InterfacePtr<IGeometry> itemGeometry(shape, IID_IGEOMETRY);
	if (itemGeometry == nil )
	{
		ASSERT_FAIL("FormFieldLabelDrawer::Draw: font or geometry unavailable");
		return;
	}
	
	// Get the current transformation matrix for this object
	PMMatrix xformMatrix;
	InterfacePtr<ITransform> xform(shape, IID_ITRANSFORM);
	xform->GetInnerToRootMatrix( &xformMatrix );
	PMReal xScale = 1.0;
	PMReal yScale = 1.0;
	PMReal rotAngle = 0.0;
	xformMatrix.GetMatrixInfo( &rotAngle, nil, &xScale, &yScale);
	PMReal xyRatio = abs(yScale/xScale);
	
	// Get the scale factor for the view port
	PMReal viewPortScale = 1.0;
	IRasterPort *rasterPort = gd->GetRasterPort();	
	if ( rasterPort ) {
		PMMatrix viewPortMatrix;
		rasterPort->currentmatrix(&viewPortMatrix);
		viewPortScale = abs(viewPortMatrix.GetXScale());
	}
	
	// Check if the view port scale has gotten so small we shouldn't display the adornment
	PMRect pageItemBBox = itemGeometry->GetPathBoundingBox();
	if ( pageItemBBox.Width()*viewPortScale < 10.0 || pageItemBBox.Height()*viewPortScale*xyRatio < 10.0 )
		return;
	
	PMPoint labelAnchorPoint;
	// Get the starting point for the label
	PMPoint labelPoint;
	PMMatrix labelMatrix;
#if DRAW_LABEL_TOP_LEFT
	if ( yScale >= 0.0 ) {
		if ( rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0 ) {
			labelPoint = PMPoint( pageItemBBox.Left(),  pageItemBBox.Top() );
		}
		else {
			labelPoint = PMPoint( pageItemBBox.Right(),  pageItemBBox.Bottom() );
			labelMatrix = PMMatrix( -1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
		}
	}
	else {
		if ( rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0 ) {
			labelPoint = PMPoint( pageItemBBox.Left(),  pageItemBBox.Bottom() );
			labelMatrix = PMMatrix( 1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
		}
		else {
			labelPoint = PMPoint( pageItemBBox.Right(),  pageItemBBox.Top() );
			labelMatrix = PMMatrix( -1.0, 0.0, 0.0, 1.0, 0.0, 0.0 );
		}
	}
	labelAnchorPoint = labelPoint;
#else
	// draw adornment in bottom right corner by default.
	if ( yScale >= 0.0 ) {
		if ( rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0 ) {
			labelPoint = PMPoint( pageItemBBox.Right() - 1.5 * (kIconWidth+iconOffset)/viewPortScale,  pageItemBBox.Bottom() - 1.5 * kIconHeight/viewPortScale);
			labelAnchorPoint = PMPoint(pageItemBBox.Right(),pageItemBBox.Bottom());
		}
		else {
			labelPoint = PMPoint( pageItemBBox.Left() + 1.5 * (kIconWidth+iconOffset)/viewPortScale,  pageItemBBox.Top() + 1.5 * kIconHeight/viewPortScale);
			labelMatrix = PMMatrix( -1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
			labelAnchorPoint = PMPoint(pageItemBBox.Left(),pageItemBBox.Top());
		}
	}
	else {
		if ( rotAngle >= -90.0 && rotAngle <= 90.0 || rotAngle >= 270.0 ) {
			labelPoint = PMPoint( pageItemBBox.Right() - 1.5 * (kIconWidth+iconOffset)/viewPortScale,  pageItemBBox.Top() + 1.5 * kIconHeight/viewPortScale);
			labelMatrix = PMMatrix( 1.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
			labelAnchorPoint = PMPoint(pageItemBBox.Right(),pageItemBBox.Top());
		}
		else {
			labelPoint = PMPoint( pageItemBBox.Left() + 1.5 * (kIconWidth+iconOffset)/viewPortScale,  pageItemBBox.Bottom() - 1.5 * kIconHeight/viewPortScale);
			labelMatrix = PMMatrix( -1.0, 0.0, 0.0, 1.0, 0.0, 0.0 );
			labelAnchorPoint = PMPoint(pageItemBBox.Left(),pageItemBBox.Bottom());
		}
	}
#endif
	// Check if there's room for the icon and name and if they should also be shown
	PMRect scaledBBox(0.0, 0.0, pageItemBBox.Width()*viewPortScale, pageItemBBox.Height()*viewPortScale*xyRatio);
	bool doShowName = showName && HaveRoomForName(scaledBBox);
	
	// Save the current graphics state
	gPort->gsave();
	
	// Turn on anti-aliasing for smooth text at wierd angles
	//int32 antialias = (kAGMOptionAAText | kAGMOptionAAGraphics);
	int32 antialias = (1 | 2);
	if (rasterPort)
		rasterPort->setantialiaspolicy(&antialias);	// Returns previous antialias value
	
	//twright 1/26/2001 Set the color to the layer's color...
	// Just use black, it's more visible
	ColorArray layerColor(3, 0.0);	// 3 values, all 0.0 for R, G, B
#if 0
	InterfacePtr<ISpreadLayer> itemSpreadLayer(theDB, itemHier->GetLayerUID(), IID_ISPREADLAYER);
	InterfacePtr<IDocumentLayer> itemDocLayer(itemSpreadLayer->QueryDocLayer());
	layerColor = Utils<IUIColorUtils>()->GetRGBColorValue( ::GetDataBase(itemDocLayer), itemDocLayer->GetColorUID() );
#else
	gPort->setopacity(0.6, kFalse);
#endif
	gPort->setrgbcolor(layerColor[0], layerColor[1], layerColor[2]);

	PMReal vt = std::max(((2.5 * kIconWidth)+iconOffset)/scaledBBox.Width(), 1.5 * kIconHeight/scaledBBox.Height());

	InterfacePtr<IGfxCapturePort> capturePort(gPort,UseDefaultIID()); 
	if(capturePort) 
		capturePort->BeginFixedSizeGraphix(labelAnchorPoint,vt); 

		
	// Transform to the starting point for the label
	gPort->concat( PMMatrix(1.0, 0.0, 0.0, 1.0, labelPoint.X(), labelPoint.Y()) );
	gPort->concat( PMMatrix(1.0/(viewPortScale), 0.0, 0.0, 1.0/(viewPortScale*xyRatio), 0.0, 0.0) );
	gPort->concat( labelMatrix );
	
	if (showIcon)
	{
		InterfacePtr<IFormField> formField(shape, IID_IFORMFIELD);
		if (formField)
		{
			PMRsrcID rsrcID;
			formField->GetIconRsrcID(&rsrcID);

			if (rsrcID.fId != 0 && rsrcID.fPluginId != kInvalidPlugin)
			{
				PMPoint iconTopLeft( kLabelSpace, kLabelVerticalGap );
				
				ColorizedIcon icon( rsrcID );
				bool drawIcon = capturePort || ( scaledBBox.Width() > ((2.5 * kIconWidth)+iconOffset) ) && ( scaledBBox.Height() > 1.5 * kIconHeight );
				if ( drawIcon) 
				{
					// erase the area behind the icon
					gPort->gsave();
					gPort->newpath();
					gPort->setlinewidth(0);
					gPort->moveto( iconTopLeft.X() - 1.0, iconTopLeft.Y() - 1.0 );
					gPort->lineto( iconTopLeft.X() + kIconWidth + 1.0, iconTopLeft.Y() - 1.0 );
					gPort->lineto( iconTopLeft.X() + kIconWidth + 1.0, iconTopLeft.Y() + kIconHeight + 1.0 );
					gPort->lineto( iconTopLeft.X() - 1.0, iconTopLeft.Y() + kIconHeight + 1.0 );
					gPort->closepath();

					if ( layerColor[0] > 0.95 && layerColor[1] > 0.95 && layerColor[2] > 0.95 )
						gPort->setrgbcolor(0.0, 0.0, 0.0);
					else
						gPort->setrgbcolor(1.0, 1.0, 1.0);
					gPort->eofill();
					gPort->grestore();

					gPort->gsave();
					gPort->newpath();
					gPort->moveto( iconTopLeft.X() - 1.0, iconTopLeft.Y() - 1.0 );
					gPort->lineto( iconTopLeft.X() + kIconWidth + 1.0, iconTopLeft.Y() - 1.0 );
					gPort->lineto( iconTopLeft.X() + kIconWidth + 1.0, iconTopLeft.Y() + kIconHeight + 1.0 );
					gPort->lineto( iconTopLeft.X() - 1.0, iconTopLeft.Y() + kIconHeight + 1.0 );
					gPort->closepath();
					gPort->eoclip();

					// Draw the Icon
					icon.Draw( gPort, iconTopLeft, layerColor );
					gPort->grestore();
				}
				else
					showIcon = false;
			}
		}
	}
 
	if (doShowName)
	{
		InterfacePtr<IFontMgr> fontMgr( GetExecutionContextSession(), IID_IFONTMGR );
		InterfacePtr<IPMFont> theFont(fontMgr->QueryFont(fontMgr->GetDefaultFontName()));
		PMReal fontSize = kLabelPointSize;
		
		PMMatrix matrix( fontSize, 0.0, 0.0,  fontSize, 0.0, 0.0 );
	    InterfacePtr<IFontInstance> fontInst( fontMgr->QueryFontInstance( theFont, matrix ) );
		PMReal descent = fontInst->GetDescent();
    
		gPort->selectfont(theFont, fontSize);
		
		PMPoint position;
		if ( showIcon ) {
			position = PMPoint(kLabelSpace + kIconWidth + 3.0,  fontSize + kLabelVerticalGap);
		}
		else {
			position = PMPoint(kLabelSpace, fontSize + kLabelVerticalGap);
		}
		
		PMString name( formFieldName );
		FitStringToWidth(fontInst, name, scaledBBox.Right() - position.X() - 4.0);

		// Knock out around the text with white (or black if the text color is white)
		if ( layerColor[0] > 0.95 && layerColor[1] > 0.95 && layerColor[2] > 0.95 )
			gPort->setrgbcolor(0.0, 0.0, 0.0);
		else
			gPort->setrgbcolor(1.0, 1.0, 1.0);
		gPort->show( position.X()-1.0, position.Y() - descent,       name.WCharLength(), name.GrabWString());
		gPort->show( position.X()-1.0, position.Y() - descent + 1.0, name.WCharLength(), name.GrabWString());
		gPort->show( position.X()    , position.Y() - descent - 1.0, name.WCharLength(), name.GrabWString());
		gPort->show( position.X()-1.0, position.Y() - descent - 1.0, name.WCharLength(), name.GrabWString());
		gPort->show( position.X()+1.0, position.Y() - descent,       name.WCharLength(), name.GrabWString());
		gPort->show( position.X()+1.0, position.Y() - descent + 1.0, name.WCharLength(), name.GrabWString());
		gPort->show( position.X()    , position.Y() - descent + 1.0, name.WCharLength(), name.GrabWString());
		gPort->show( position.X()+1.0, position.Y() - descent - 1.0, name.WCharLength(), name.GrabWString());
	    
		// Draw the label text
	    gPort->setrgbcolor(layerColor[0], layerColor[1], layerColor[2]);
	    gPort->show( position.X(), position.Y() - descent, name.WCharLength(), name.GrabWString());
	}

	if (rasterPort)
		rasterPort->setantialiaspolicy(&antialias);	// Restore previous antialias value

	if(capturePort) 
		capturePort->EndFixedSizeGraphix();

	gPort->grestore();

}

// -----------------------------------------------------------------------------
 
bool16 FormFieldLabelDrawer::HaveRoomForName( PMRect bounds )
{
	// Do a quick check
	if ( bounds.Width() < 5.0 || bounds.Height() < 5.0 )
		return kFalse;
	
	InterfacePtr<IFontMgr> fontMgr( GetExecutionContextSession(), IID_IFONTMGR );
	InterfacePtr<IPMFont> theFont(fontMgr->QueryFont(fontMgr->GetDefaultFontName()));
	PMReal fontSize = kLabelPointSize;
	
	PMMatrix matrix( fontSize, 0.0, 0.0,  fontSize, 0.0, 0.0 );
    InterfacePtr<IFontInstance> fontInst( fontMgr->QueryFontInstance( theFont, matrix ) );
    
	PMPoint dim = bounds.Dimensions();
	return ( dim.X() > 5*fontInst->GetXHeight() ) && ( dim.Y() > 2.0*fontInst->GetXHeight() + 2*kLabelVerticalGap );
} // end MediaFrameAdornment::HaveRoomForName()

// -----------------------------------------------------------------------------

void FormFieldLabelDrawer::FitStringToWidth(IFontInstance *fontInstance, PMString &StringToFit, PMReal width) const
{
	// determine width of original string
	PMReal stringWidth;
	fontInstance->MeasureWText(StringToFit, stringWidth);

	// does the string fit in available space or does it need to be truncated?
	if (stringWidth > width)
	{
		// string doesn't fit, will need to append ellipse to indicate truncated string
		textchar ellipse = kTextChar_Ellipse;
		PMString dotDotDot("");
		dotDotDot.AppendW(ellipse);
	
		// determine the size of the ellipse string that will be appended to the StringToFit
		PMReal ellipseWidth;
		fontInstance->MeasureWText(dotDotDot, ellipseWidth);

		// adjust the width to account for the width of the ellipse
		width -= ellipseWidth;

		// do - while there are still elements in the string and the string + ellipse is too wide
		do
		{
			// remove a character from the string
			StringToFit.Truncate(1);

			// determine new width of string
			fontInstance->MeasureWText(StringToFit, stringWidth);
		}
		while (!StringToFit.IsEmpty() && stringWidth > width);

		// add the ellipse to truncated string
		StringToFit.Append(dotDotDot);
	}
}

