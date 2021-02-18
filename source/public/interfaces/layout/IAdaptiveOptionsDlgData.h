//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveOptionsDlgData.h $
//  
//  Owner: Pooja Mangla
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2018 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IAdaptiveOptionsDlgData__
#define __IAdaptiveOptionsDlgData__

#include "IPMUnknown.h"
#include "PageSetupDialogID.h"

/**
Usage: This object exists merely to cache the settings for the adaptive options dialog.
*/
class IAdaptiveOptionsDlgData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADAPTIVEOPTIONSDLGDATA };

	/** Allow locked items to be adjusted by layout adjustment.
		@param val IN kTrue to allow adjusting locked items, kFalse to disallow
	*/
	virtual void SetScaleLockedPageItems(bool16 val) = 0;

	/**  Set the on/off state of Font Size and Leading checkbox */
	virtual void SetFontSizeandLeadingOn(bool16 val) = 0;

	/**  Set the on/off state of Font Size and Leading checkbox */
	virtual void SetFontSizeLimitOn(bool16 val) =  0;

	/**   Set the Minimum font size set by user  */
	virtual void SetMinimumFontSize(PMReal val) = 0;

	/**   Set the Maximum font size set by user */
	virtual void SetMaximumFontSize(PMReal val) = 0;

	/**  Get whether locked items can be adjusted by layout adjustment.
		@return kTrue for allow adjusting locked items,  kFalse for disallow
	*/
	virtual bool16 GetScaleLockedPageItems()  = 0;

	/**  Get the on/off state of Scale font Size limit.
		@return kTrue for on, kFalse for off
	*/
	virtual bool16 IsFontSizeandLeadingOn()  = 0;

	/**  Get the on/off state of Scale font Size limit.
		@return kTrue for on, kFalse for off
	*/
	virtual bool16 IsFontSizeLimitOn()  = 0;

	/**  Get the Minimum font size set by user.
		@return the minimum font size value
	*/
	virtual PMReal GetMinimumFontSize()  = 0;

	/**  Get the Minimum font size set by user.
		@return the minimum font size value
	*/
	virtual PMReal GetMaximumFontSize()  = 0;
};

#endif // __IAdaptiveOptionsDlgData__
