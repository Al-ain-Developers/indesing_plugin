//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEditBoxAttributes.h $
//  
//  Owner: Lance Bushore
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
#ifndef __IEditBoxAttributes__
#define __IEditBoxAttributes__

#include "IPMUnknown.h"
#include "widgetid.h"

#ifdef MACINTOSH
	const int32 kEndOfRange = 32767;
#endif
#ifdef WINDOWS
	const int32 kEndOfRange = -1;
#endif

/**	Interface which maintains current editbox settings.
*/
class  IEditBoxAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEDITBOXATTRIBUTES };

/**	Set the widget ID for the associated nudge button widget
	@param nudgeButton the nudge button that goes with this editbox.
*/
	virtual void SetNudgeButtonWidgetID(const WidgetID& nudgeButton) = 0;

/**	Get the widget ID for the associated nudge button widget
	@return the nudge button that goes with this editbox.
*/
	virtual WidgetID GetNudgeButtonWidgetID() const = 0;

/**	Set the small nudge amount to use for the associated nudge button widget. Note that for editboxes
	which use a measurement system, the measurement system defines it's own large and small nudge amount,
	so this number is used as a multiplier of the base UOM nudge amount. @see IUnitOfMeasure
	@param increment small nudge amount to use.
*/
	virtual void SetSmallNudgeAmount(const PMReal& increment) = 0;

/**	Get the small nudge amount to use for the associated nudge button widget. Note that for editboxes
	which use a measurement system, the measurement system defines it's own large and small nudge amount,
	so this number is used as a multiplier of the base UOM nudge amount. @see IUnitOfMeasure
	@return small nudge amount to use.
*/
	virtual PMReal GetSmallNudgeAmount() const = 0;
	
/**	Set the large nudge amount to use for the associated nudge button widget. Note that for editboxes
	which use a measurement system, the measurement system defines it's own large and small nudge amount,
	so this number is used as a multiplier of the base UOM nudge amount. @see IUnitOfMeasure
	@param increment large nudge amount to use.
*/
	virtual void SetLargeNudgeAmount(const PMReal& increment) = 0;

/**	Get the large nudge amount to use for the associated nudge button widget. Note that for editboxes
	which use a measurement system, the measurement system defines it's own large and small nudge amount,
	so this number is used as a multiplier of the base UOM nudge amount. @see IUnitOfMeasure
	@return large nudge amount to use.
*/
	virtual PMReal GetLargeNudgeAmount() const = 0;

/**	Get the max number of characters which can be input into this editbox. The editbox will prevent users from entering more than this number of characters.
	@return max allowed characters
*/
	virtual CharCounter GetMaxNumChars() const = 0;

/**	Set the max number of characters which can be input into this editbox. The editbox will prevent users from entering more than this number of characters.
	@param maxNumCharsnew maximum allowed characters
*/
	virtual void	SetMaxNumChars(const CharCounter& maxNumChars) = 0;

/**	Check if this editbox is read only. Users cannot type in editboxes which are marked read-only.
	@return kTrue if this editbox is read only.
*/
	virtual bool16 IsEditboxReadOnly() const = 0;

/**	Set if this editbox is read only. Users cannot type in editboxes which are marked read-only.
	@param readOnly kTrue if this editbox is now read only.
*/
	virtual void	SetEditboxReadOnly(const bool16& readOnly) = 0;

/**	Check if this editbox needs to notify after every keystroke. Usually editboxes only notify that their text has changed when the editbox looses the text focus.
	If a particular observer cares to enable/disable or do something else based on every keystroke, you need to turn this flag on.
	@return kTrue if this editbox is notifying on every keystroke.
*/
	virtual bool16	ShouldNotifyEveryStroke() const = 0;

/**	Set if this editbox needs to notify after every keystroke. Usually editboxes only notify that their text has changed when the editbox looses the text focus.
	If a particular observer cares to enable/disable or do something else based on every keystroke, you need to turn this flag on.
	@param flag kTrue if this editbox should notify after every keystroke.
*/
	virtual void	SetNotifyEveryStroke(const bool16& flag) = 0;
	
/**	Select a range of text in the editbox.
	@param startOfRange the beginning index for the new selection.
	@param endOfRange the ending index for the new selection.
*/
	virtual void SelectRange(const CharCounter& startOfRange, const CharCounter& endOfRange = kEndOfRange) = 0;
	
	
/**	Get the beginning index of the selected text
	@return the beginning index for the selection in the editbox.
*/
	virtual CharCounter GetStartOfSelection() const = 0;

/**	Get the end index of the selected text
	@return the end index for the selection in the editbox.
*/
	virtual CharCounter GetEndOfSelection() const = 0;

/**	Check if this editbox supports multiple lines. Most editboxes do not.
	@return kTrue if this editbox does support multiple lines.
*/
	virtual bool16 IsMultiLine() const = 0;
};	

#endif // __IEditBoxAttributes__
