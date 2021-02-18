//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/PageTransitionStaticTextToolTips.cpp $
//  
//  Owner: Yeming Liu
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "ITextControlData.h"
#include "AbstractTip.h"

// ----- Includes -----

#include "PMString.h"

// ----- Utils -----

#include "IMenuUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class PageTransitionStaticTextToolTips : public AbstractTip
{			
	public:
		PageTransitionStaticTextToolTips( IPMUnknown *boss );
		virtual ~PageTransitionStaticTextToolTips();

		virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE(PageTransitionStaticTextToolTips, kPageTransitionStaticTextToolTipsImpl)

PageTransitionStaticTextToolTips::PageTransitionStaticTextToolTips(IPMUnknown *boss) :
	AbstractTip( boss )
{
}

PageTransitionStaticTextToolTips::~PageTransitionStaticTextToolTips()
{
}

PMString PageTransitionStaticTextToolTips::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString("");
	InterfacePtr<ITextControlData> iData(this, UseDefaultIID()); 
	if (iData)
	{
		tipString = iData->GetString();  
	}

	return tipString;
} 

