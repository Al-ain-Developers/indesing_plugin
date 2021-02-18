//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/utils/CColorContext.cpp $
//  
//  Owner: Mouhammad Fakhoury
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

#include "DV_VCWidgetHeaders.h"

#include "CColorContext.h"

CColorContext::CColorContext()
{
	fIInterfaceColors = (IInterfaceColors*)GetExecutionContextSession()->QueryInterface( IID_IINTERFACECOLORS );
}


CColorContext::~CColorContext()
{
	if( fIInterfaceColors )
		fIInterfaceColors->Release();
}


bool16 CColorContext::GetRGBColor(const IInterfaceColors::InterfaceColor index, RGBColor& rgbColor)const
{
	return fIInterfaceColors->GetRGBColor(index, rgbColor);
}


bool16 CColorContext::GetRealAGMColor(const IInterfaceColors::InterfaceColor index, RealAGMColor& realAGMColor)const
{
	return fIInterfaceColors->GetRealAGMColor(index, realAGMColor);
}

