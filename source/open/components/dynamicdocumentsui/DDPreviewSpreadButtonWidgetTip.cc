//========================================================================================
//  
//  $File: //depot/shuksan/source/open/components/dynamicdocumentsui/DDPreviewSpreadButtonWidgetTip.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: yeliu $
//  
//  $DateTime: 2009/09/01 14:23:58 $
//  
//  $Revision: #1 $
//  
//  $Change: 716793 $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "AbstractTip.h"

// ----- Includes -----

#include "PMString.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class DDPreviewSpreadButtonWidgetTip : public AbstractTip
{			
	public:
		DDPreviewSpreadButtonWidgetTip( IPMUnknown *boss );
		virtual ~DDPreviewSpreadButtonWidgetTip();

		virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE(DDPreviewSpreadButtonWidgetTip, kDDPreviewSpreadButtonWidgetTipImpl)

DDPreviewSpreadButtonWidgetTip::DDPreviewSpreadButtonWidgetTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
}

DDPreviewSpreadButtonWidgetTip::~DDPreviewSpreadButtonWidgetTip()
{
}

PMString DDPreviewSpreadButtonWidgetTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tip("kPreviewSpreadButtonToolTip");
	return tip;
} 

