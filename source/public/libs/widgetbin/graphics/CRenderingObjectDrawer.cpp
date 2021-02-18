//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/graphics/CRenderingObjectDrawer.cpp $
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
//========================================================================================

#include "VCWidgetHeaders.h"

#include "CRenderingObjectDrawer.h"

#include "IGraphicsPort.h"
#include "IWidgetParent.h"
#include "IControlView.h"
#include "IInterfaceFonts.h"
#include "IListBoxAttributes.h"
#include "IWidgetUtils.h"
#include "IRenderingObject.h"

#ifdef REMOVED_JBX_FOR_CS3
#include "IJBXLinkUtils.h"
#endif

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "DrawStringUtils.h"
#include "LocaleSetting.h"
#include "PlatformIconClass.h"
#include "ISwatchUtils.h"
#include "SysControlIds.h"
#include "DVOwnerDrawDropDownListView.h"
#include "DVUtilities.h"

CRenderingObjectDrawer::CRenderingObjectDrawer(IPMUnknown *boss) :
	CPMUnknown<IRenderingObjectDrawer>(boss)
{
}

CRenderingObjectDrawer::~CRenderingObjectDrawer()
{
}

void CRenderingObjectDrawer::DrawRenderObjectUI ( IViewPort* viewPort, IControlView* controlView, SysRgn updateRgn, PMRect frame ) const
{
	AGMGraphicsContext gc(viewPort, controlView, updateRgn);


	PMRect tempframe = frame;
	controlView->ContentToWindowTransform(&tempframe);
	SysRect	sysFrame = ToSys(tempframe);
	
	bool16 isHilited = controlView->IsHilited();
	bool16 isEnabled = controlView->IsEnabled();
	
	InterfacePtr<IGraphicsPort>		gPort(gc.GetViewPort(), IID_IGRAPHICSPORT);
	AutoGSave autoGSave(gPort);
	
	// Draw background
	bool16 bInsetHilite = kTrue;
	PMReal borderWidth = 1.0;
	InterfacePtr<IWidgetParent> widgetParent(controlView, IID_IWIDGETPARENT);
	InterfacePtr<IListBoxAttributes> listBoxAttr((IListBoxAttributes*) widgetParent->QueryParentFor(IID_ILISTBOXATTRIBUTES));
	if (!listBoxAttr || (listBoxAttr && (borderWidth = listBoxAttr->GetBorderWidth()) == 0))
		bInsetHilite = kFalse;

	DrawBackground(gPort, controlView, frame, isHilited, bInsetHilite);

	// Draw swatch, centered the swatch rect kRenderObjectSwatchStart from the left
	// of the frame
	PMRect swatchRt = frame;
	swatchRt.MoveTo(kRenderObjectSwatchStart, 1 + borderWidth);
	swatchRt.Bottom() = frame.Bottom() - (2 + borderWidth);
	swatchRt.Right() = swatchRt.Left() + swatchRt.Height();
	
	dv_utils::DrawRenderObjectUISwatch(this, gPort, controlView, swatchRt);
	
	frame.Right() -= 2*frame.Height();
	
	InterfacePtr<IRenderingObject> renderingObj(this, UseDefaultIID());
	
	// Draw no pencil icon
	if ( !renderingObj->GetCanEdit() )
	{
		DrawNoEditIcon( viewPort, sysFrame );
		frame.Right() -= frame.Height();
	}

	// Draw swatch name	
	InterfacePtr<IInterfaceFonts> fonts(GetExecutionContextSession(), IID_IINTERFACEFONTS);
	const InterfaceFontInfo&	fontInfo = isHilited ? fonts->GetFont(kPaletteWindowSystemScriptHiliteFontId) : fonts->GetFont(kPaletteWindowSystemScriptFontId);

	int16	alignment = kAlignCenter;
	DrawRenderObjectUIName(&gc, fontInfo, frame, alignment, isHilited, isEnabled);
}

void CRenderingObjectDrawer::DrawRenderObjectUISwatch(IGraphicsPort* gPort, const PMRect& swatchRt) const
{
	// ----- Create a square swatch inset from the left and centered top to bottom.
	
	// ----- Fill the swatch.
	InterfacePtr<IRenderingObject> renderingObj(this, UseDefaultIID());

	{
		AutoGSave autoGSave(gPort);
		renderingObj->Install(gPort, swatchRt);

		gPort->rectpath(swatchRt);
		gPort->fill();
	}

	// ----- Frame the swatch.
	gPort->rectstroke(swatchRt);
}

void CRenderingObjectDrawer::DrawRenderObjectUIName(IGraphicsContext* gc, const InterfaceFontInfo& fontInfo, const PMRect& frame, const int16& alignment, const bool16& isHilited, const bool16& isEnabled) const
{

	// Figure out initial string position so we can compute the max possible string length.
	PMReal		swatchNameStart;
	if ( alignment == kAlignLeft || alignment == kAlignRight )
	{
		swatchNameStart = kSwatchNameStart;
	}
	else
	{
		swatchNameStart = frame.Height() + kSwatchNameStart;
	}

	IInterfaceColors::InterfaceColor color;
	if (isEnabled)
		color = isHilited ? kInterfaceHighLightText : kInterfaceTextColor;
	else
		color = kInterfaceDisabledGray;

	// Adjust swatch name string so that it will not overwrite the icons to the left.
	InterfacePtr<IRenderingObject> renderingObj(this, UseDefaultIID());
	PMReal			allowedWidth = frame.Width() - swatchNameStart - 3;
	PMString		nameString = renderingObj->GetSwatchUIName();
	if (nameString.IsEmpty())
	{
		nameString = PMString("UnnamedRenderingObject");
	}

	const bool16	kDontConvertAmpsersand = kFalse;
	nameString = StringUtils::PMEllipsizeString( gc, allowedWidth, nameString, fontInfo );
	PMPoint			dimension = StringUtils::PMMeasureString(gc, nameString, fontInfo, kDontConvertAmpsersand);
	
	PMPoint 		startPt;
	if (  alignment == kAlignRight )
		startPt = PMPoint(frame.Right() - dimension.X(), frame.GetCenter().Y() + 4);
	else
		startPt = PMPoint(frame.Left() + swatchNameStart, frame.GetCenter().Y() + 4);
	StringUtils::PMDrawString(gc, startPt, nameString, fontInfo, color, kDontConvertAmpsersand);
}

//========================================================================================
// Private Methods
//========================================================================================

void CRenderingObjectDrawer::DrawBackground(IGraphicsPort* gPort, const IControlView* widget, const PMRect& frame, const bool16& isHilited, const bool16& bInsetHilite) const
{
	RealAGMColor insetColor, background;
	InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
	
	if(isHilited)
	{
		colors->GetRealAGMColor(kInterfaceHighLight, background);

		gPort->setrgbcolor( background.red, background.green, background.blue );
		gPort->rectpath(frame);	
		gPort->fill();
	}
	else
		Utils<IWidgetUtils>()->DrawPaletteFill(widget,gPort,&frame);

	colors->GetRealAGMColor(kInterfacePaletteFill, insetColor);

	if (bInsetHilite)
	{
		PMRect insetFrame(frame.Left(), frame.Top(), frame.Right() - 1, frame.Bottom());
		gPort->setrgbcolor( insetColor.red, insetColor.green, insetColor.blue );
		gPort->rectstroke(insetFrame);	
	}

}	

void CRenderingObjectDrawer::DrawNoEditIcon(IViewPort* viewPort, const SysRect& bbox, const bool16& brightnessAware) const
{
	PlatformIconClass	theIcon;

	// pngs are in applicationUI plugin
	theIcon.LoadIcon(kApplicationRsrcPluginID, kNoPencilIcon, brightnessAware);
	
	PMRect				iconRect( bbox );
	iconRect.Right() -= (2 * kSwatchesPanelIconWidth + 5 + 2 * kIconInset); // The new icon SP_NoEdit_Xs_N.png (After icon integration) has only 1 empty pixel on the left (unlike 2 in the previous icon P_LockPencil_Sm_N.png), hence making change of 1 pixel to adjust this.
	iconRect.Left() = iconRect.Right() - iconRect.Height();
	theIcon.Draw( viewPort, ::ToSys(iconRect), kFalse );
}
