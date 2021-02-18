//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveLayoutPrefs.h $
//  
//  Owner: Sachin Singhal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2018 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it. If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IAdaptiveLayoutPrefs__
#define __IAdaptiveLayoutPrefs__

#include "IPMUnknown.h"

/**	Interface for setting and getting preferences for Adaptive Layout feature.
*/
class IAdaptiveLayoutPrefs : public IPMUnknown
{
public:	
	
	/**	Sets the value of preference which states whether the adaptive layout is turned on or not.
		@param	val	IN kTrue if adaptive layout is to be turned on.
	*/
	virtual void SetAdaptiveLayoutOn(bool16 val) = 0;

	/**	Sets the value of preference for adjusting locked items.
		@param	val	IN kTrue if locked items are to be adjusted.
	*/
	virtual void SetScaleLockedPageItems(bool16 val) = 0;

	/**	Sets the value of preference for adjusting text's font size and leading.
		@param	val	IN kTrue if text is to be adjusted.
	*/
	virtual void SetFontSizeandLeadingOn(bool16 val) = 0;

	/**	Sets the value of preference for limiting the values of font by which text's font size is controlled.
		@param	val	IN kTrue if text is to be adjusted within the limits.
	*/
	virtual void SetFontSizeLimitOn(bool16 val) = 0;

	/**	Sets the value of preference for minimum font size after adjustment.
		@param	val	IN minimum font value for setting the limits.
	*/
	virtual void SetMinimumFontSize(PMReal val) = 0;
	
	/**	Sets the value of preference for maximum font size after adjustment.
		@param	val	IN maximum font value for setting the limits.
	*/
	virtual void SetMaximumFontSize(PMReal val) = 0;

	/**	Sets the value of preference for adjusting margins automatically.
		@param	val	IN kTrue if margins are to be set automatically.
	*/
	virtual void SetAutoAdjustMargins(bool16 val) = 0;

	/**	Returns the value of preference which states whether the adaptive layout is turned on or not.
		@return	kTrue if adaptive layout is turned on.
	*/
	virtual bool16 GetAdaptiveLayoutOn() = 0;

	/**	Returns the value of preference for adjusting locked items.
		@return	kTrue if locked items are to be adjusted.
	*/
	virtual bool16 GetScaleLockedPageItems() = 0;

	/**	Returns the value of preference for adjusting text's font size and leading.
		@return	kTrue if text is to be adjusted.
	*/
	virtual bool16 IsFontSizeandLeadingOn()= 0;

	/**	Returns the value of preference for limiting the values of font by which text's font size is controlled.
		@return	kTrue if text is to be adjusted within the limits.
	*/
	virtual bool16 IsFontSizeLimitOn() = 0;

	/**	Returns the value of preference for minimum font size after adjustment.
		@return	minimum font value as per specified limits.
	*/
	virtual PMReal GetMinimumFontSize()= 0;
	
	/**	Returns the value of preference for maximum font size after adjustment.
		@return	maximum font value as per specified limits.
	*/
	virtual PMReal GetMaximumFontSize() = 0;

	/**	Returns the value of preference for adjusting margins automatically.
		@return	kTrue if margins are to be set automatically.
	*/
	virtual bool16 IsAutoAdjustMarginsOn()= 0;
	
};

#endif
