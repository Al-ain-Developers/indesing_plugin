//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveLayoutPrefsCmdData.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it. If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Data interface for adaptive layout preference command.
//  
//========================================================================================

#pragma once
#ifndef __IAdaptiveLayoutPrefsCmdData__
#define __IAdaptiveLayoutPrefsCmdData__

#include "IPMUnknown.h"
#include "AutoLayoutID.h"

/**	Interface for setting and getting data for the kSetAdaptiveLayoutPrefsCmdBoss command.
*/
class IAdaptiveLayoutPrefsCmdData : public IPMUnknown
{
public:
	/**	Set all the values at once.
		@param doc						IN a reference to the document whose preferences are being set.
		@param bAdaptiveLayoutOn		IN kTrue to turn on, kFalse to turn off.
		@param bScaleLockedPageItems	IN kTrue to allow adjusting locked items, kFalse to disallow.
		@param bFontSizeandLeadingOn	IN kTrue to facilitate font size limit , else not.
		@param bFontSizeLimitOn			IN kTrue to facilitate minimum font size and maximum font size , else not.
		@param rFontMinimunSize			IN minimum size of the font for the doc .
		@param rFontMaximumSize			IN Maximum size of the font for the doc.
		@param bAutoAdjustMargin		IN kTrue to auto adjust the margins based on the changes in the page size. Please note that this would
											only be effective when worked through Adjust Layout dialog. 
	*/
	virtual void Set(	const	UIDRef&	doc,
						bool16 bAdaptiveLayoutOn,
						bool16 bScaleLockedPageItems,
						bool16 bFontSizeandLeadingOn,
						bool16 bFontSizeLimitOn,
						PMReal rFontMinimunSize,
						PMReal rFontMaximumSize,
						bool16 bAutoAdjustMargin) = 0;
	
	/**	Enable the Layout Adjustment feature.
		@param val IN kTrue to turn on, kFalse to turn off.
	*/
	virtual void SetAdaptiveLayoutOn(bool16 val) = 0;

	/**	Allow locked items to be adjusted by layout adjustment.
		@param val IN kTrue to allow adjusting locked items, kFalse to disallow
	*/
	virtual void SetScaleLockedPageItems(bool16 val) = 0;

	/**	Returns the document reference for which the change is to be made.
		@return	Reference to the document for which the change is to be made.
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/**	Returns the on/off state of layout adjustment.
		@return kTrue for on, kFalse for off
	*/
	virtual const bool16 GetAdaptiveLayoutOn() const = 0;

	/**	Get whether locked items can be adjusted by layout adjustment.
		@return kTrue for allow adjusting locked items, kFalse for disallow
	*/

	virtual const bool16 GetScaleLockedPageItems() const = 0;

	/**	Get value which signifies whether the text adjustment is to be turned on or not.
		@return kTrue if the text is to be adjusted.
	*/
	virtual bool16 IsFontSizeandLeadingOn()const = 0;

	/**	Returns the on/off state of Scale font Size limit.
		@return kTrue for on, kFalse for off
	*/
	virtual bool16 IsFontSizeLimitOn()const = 0;

	/**	Get the Minimum font size set by user.
		@return the minimum font size value
	*/
	virtual PMReal GetMinimumFontSize()const = 0;

	/**	Get the Maximum font size set by user.
		@return the Maximum font size value
	*/
	virtual PMReal GetMaximumFontSize()const = 0;

	/**	Sets whether text is to be adjusted or not.
		@param val IN kTrue to allow adjusting of text
	*/
	virtual void SetFontSizeandLeadingOn(bool16 val) = 0;

	/**	Sets whether a font size limit is to be enforced during the text adjustment.
		@param val IN kTrue to adjust text within the specified limits.
	*/
	virtual void SetFontSizeLimitOn(bool16 val) = 0;

	/**	Set the minimum font size to decide the limits for text adjustment.
		@param val IN value of minimum font size.
	*/
	virtual void SetMinimumFontSize(PMReal val) = 0;

	/**	Set the maximum font size to decide the limits for text adjustment.
		@param val IN value of maximum font size.
	*/
	virtual void SetMaximumFontSize(PMReal val)= 0;

	/**	Set the document reference for which the options are to be set.
		@param docRef IN	the document reference
	*/
	virtual void SetDocument(UIDRef docRef) = 0;

	/**	Set the option to adjust margin automatically based on page size changes. This will only work when triggered from the Margin and column dialog.
		@param val IN	kTrue if the option is to be turned on.
	*/
	virtual void SetAutoAdjustMargins(bool16 val) = 0;

	/** Set the value of option to adjust margin automatically based on page size changes. 
		@return kTrue if the option is to be turned on.
	*/
	virtual bool16 IsAutoAdjustMarginsOn() = 0;
};

#endif // __IDocSetupCmdData__
