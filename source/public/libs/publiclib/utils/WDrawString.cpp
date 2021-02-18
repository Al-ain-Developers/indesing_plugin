//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/WDrawString.cpp $
//  
//  Owner: Michael Burbidge
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
#include "DrawString.h"

// ----- Interface Includes -----

#include "ISession.h"
#include "IWidgetParent.h"
#include "IControlView.h"
#include "IGraphicsPort.h"
#include "IViewPort.h"
#include "IGraphicsContext.h"
#include "ITransform.h"
#include "IWorkspace.h"
#include "IInterfaceColors.h"

// ----- Impementation Includes -----

#include "PMString.h"

//========================================================================================
// DrawText
//========================================================================================

void PMDrawStringRGB (IGraphicsContext* gc, const PMPoint& pt, const PMString& strIn,
					  const InterfaceFontInfo& fontInfo, const RealAGMColor & realColor,
					  bool16 convertAmpersandToUnderline)
{
	PMString string(strIn);	// make a local copy that we can fool around with
	string.Translate();				
	HFONT newFont = ::CreateFontIndirect(&(fontInfo.GetLogFont()));
	if (newFont)
	{
		HFONT oldFont = ::SelectObject(gc->GetSysPort(), newFont);

		ASSERT_MSG(realColor.red >= 0 && realColor.red <= 1, "PMDrawStringRGB - realColor.red Value is not within expected range of 0 to 1");
		ASSERT_MSG(realColor.green >= 0 && realColor.green <= 1, "PMDrawStringRGB - realColor.green Value is not within expected range of 0 to 1");
		ASSERT_MSG(realColor.blue >= 0 && realColor.blue <= 1, "PMDrawStringRGB - realColor.blue Value is not within expected range of 0 to 1");

		RGBColor rgbColor;
		rgbColor.red = ::ToInt32(realColor.red * 255.0);
		rgbColor.green = ::ToInt32(realColor.green * 255.0);
		rgbColor.blue = ::ToInt32(realColor.blue * 255.0);

		COLORREF oldColor = ::SetTextColor(gc->GetSysPort(), RGB (rgbColor.red, rgbColor.green, rgbColor.blue));
		
		PMPoint windowPt = pt;
		gc->GetTransform().Transform(&windowPt);

		::SetBkMode(gc->GetSysPort(), TRANSPARENT);

		GDIRect gdiTextBounds;
		// Calculate the baseline of the text and draw a line.
		TEXTMETRIC textMetrics;
		bool16 textResult = ::GetTextMetrics(gc->GetSysPort(), &textMetrics);

		gdiTextBounds.left = ::ToInt32(windowPt.X());
		gdiTextBounds.top = ::ToInt32(windowPt.Y()) - textMetrics.tmAscent;
		gdiTextBounds.right = gdiTextBounds.left + 32767;
		gdiTextBounds.bottom = gdiTextBounds.top + textMetrics.tmHeight + 2;
		::SetTextAlign(gc->GetSysPort(), TA_LEFT);

		UINT formatOptions = DT_NOCLIP | DT_SINGLELINE | DT_LEFT | DT_TOP;
		if(!convertAmpersandToUnderline)
		{
			formatOptions |= DT_NOPREFIX;
		}

		int result = ::DrawTextEx(gc->GetSysPort(), string.GrabTString(), string.GetTLength(), &gdiTextBounds, formatOptions, nil);
	
		::SelectObject(gc->GetSysPort(), oldFont);
		::SetTextColor(gc->GetSysPort(), oldColor);
		K2DeleteObject(newFont);
	}
}

void PMDrawString(IGraphicsContext* gc, const PMPoint& pt, const PMString& strIn,
				  const InterfaceFontInfo& fontInfo, IInterfaceColors::InterfaceColor color,
				  bool16 convertAmpersandToUnderline)
{
	InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
	RealAGMColor realColor;
	colors->GetRealAGMColor(color, realColor);
	PMDrawStringRGB (gc, pt, strIn, fontInfo, realColor, convertAmpersandToUnderline);
}

//========================================================================================
// PMMeasureString
//========================================================================================

PMPoint PMMeasureString
	(
	IGraphicsContext*			gc, 
	const PMString&				strIn, 
	const InterfaceFontInfo&	fontInfo,
	bool16						convertAmpersandToUnderline
	)
{
	PMString string(strIn);	// make a local copy that we can fool around with
	string.Translate();

	if ( string.Length() > 0 )
	{
		GDIRect gdiCalcRect;

		HFONT newFont = ::CreateFontIndirect(&(fontInfo.GetLogFont()));
		if (newFont)
		{
			HFONT oldFont = ::SelectObject(gc->GetSysPort(), newFont);
			UINT formatOptions = DT_CALCRECT | DT_SINGLELINE;
			if(!convertAmpersandToUnderline)
				formatOptions |= DT_NOPREFIX;
			::DrawTextEx(gc->GetSysPort(), (LPTSTR) string.GrabTString(), string.GetTLength(), &gdiCalcRect, formatOptions, NULL);

			::SelectObject(gc->GetSysPort(), oldFont);
			K2DeleteObject(newFont);
			return PMPoint((gdiCalcRect.right - gdiCalcRect.left) + 1, (gdiCalcRect.bottom - gdiCalcRect.top) + 1);
		}
		else
		{
			ASSERT_FAIL("Failed to create a font to measure");
		}
	}
	return PMPoint(0.0, 0.0);
}

//========================================================================================
// PMMeasureString
//========================================================================================

PMPoint PMMeasureString
	(
	const PMString&				strIn, 
	const InterfaceFontInfo&	fontInfo,
	bool16						convertAmpersandToUnderline
	)
{
	HDC hDC = ::GetDC(NULL);
	
	PMString string(strIn);	// make a local copy that we can fool around with
	string.Translate();

	// ----- Remove the '&' before calculating string length.
	if (convertAmpersandToUnderline)
	{
		CharCounter amperIndex = string.IndexOfCharacter('&');
		if (amperIndex >= 0)
			string.Remove(amperIndex);
	}

	if ( string.Length() > 0 )
	{
		SysRect calcRect;

		HFONT newFont = ::CreateFontIndirect(&(fontInfo.GetLogFont()));
		if (newFont)
		{
			HFONT oldFont = ::SelectObject(hDC, newFont);

			::DrawTextEx(hDC, (LPTSTR) string.GrabTString(), string.GetTLength(), &calcRect, DT_CALCRECT | DT_SINGLELINE, NULL);

			::SelectObject(hDC, oldFont);
			K2DeleteObject(newFont);
			::ReleaseDC(NULL, hDC);
			return PMPoint((calcRect.right - calcRect.left) + 1, (calcRect.bottom - calcRect.top) + 1);
		}
		else
		{
			ASSERT_FAIL("Failed to create a font to measure");
		}
	}

	::ReleaseDC(NULL, hDC);

	return PMPoint(0.0, 0.0);
}
