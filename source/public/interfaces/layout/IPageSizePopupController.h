//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageSizePopupController.h $
//  
//  Owner: Tommy Donovan
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

#pragma once
#ifndef __IPageSizePopupController__
#define __IPageSizePopupController__

#include "IPMUnknown.h"
#include "IControlView.h"
#include "IPageSizes.h"
#include "PageSetupDialogID.h"

//----------------------------------------------------------------------------------------
// Class PageSizePopupObserver
//----------------------------------------------------------------------------------------
class IPageSizePopupController : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPAGESIZEPOPUPCONTROLLER }; 

		virtual void InitializePopupEntries(const WidgetID& widgetId, IPageSizes::PageSizeIntent intent) = 0;
		virtual PMPageSize GetPageSizeFromWidget(const WidgetID& widgetId) = 0;
		virtual ClassID GetPageSizeClassIDFromWidget(const WidgetID& widgetId) = 0;
		virtual void SetWidgetWithPageSize(const WidgetID& widgetId, const PMPageSize& newPageSize, IPageSizes::PageSizeIntent intent, bool16 invalidate, bool16 notifyOfChange) = 0;
};

#endif	// __IPageSizePopupController__