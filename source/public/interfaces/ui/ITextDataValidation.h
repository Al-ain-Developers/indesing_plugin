//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITextDataValidation.h $
//  
//  Owner: ???
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
//  
//  [f************************************************************************
//  ITextDataValidation.h	 		
//  
//  f]**********************************************************************
//  
//========================================================================================

#pragma once
#ifndef __ITextDataValidation__
#define __ITextDataValidation__

#include "IPMUnknown.h"
#include "PMString.h"
#include "widgetid.h"

class ITextDataValidation : public IPMUnknown
{
public:		
	enum { kDefaultIID = IID_ITEXTDATAVALIDATION };

	/** fErrorState values set in IsEntryLegal.
	 */
	typedef enum
	{
		/** No error, initial state. 
		*/
		kNoError = 0,
		/** No entry, and IsBlankEntryAllowed doesn't return kTrue 
		*/ 
		kNoEntryWhenRequired,			
		/** Generic error code
		*/
		kInvalidValue,		
		/** Value doesn't fall within limits
		*/
		kValueOutOfRange,
		/** Bad start page value
		*/
		kInvalidStartPage,
		/** Bad end page value
		*/
		kInvalidEndPage,
		/** Bad page range value.
		*/
		kUnknownPagesInRange,
		/** Can't determine page value uniquely. More than one page in documents maps to this string
		*/
		kAmbiguousPage
	} RangeError;

	/**	Turn on (kTrue) or off (kFalse) range checking for this control.
		@param checkingOn [IN]: the boolean flag to turn on/off.
	 */
	virtual void EnableRangeChecking(const bool16& checkingOn) = 0;

	/**	Get the range checking flag for enabling range checking (kTrue) or not (kFalse).
		@return bool16 the boolean flag for range checking.
	 */
	virtual bool16 RangeCheckingEnabled() const = 0;

	/**	Get the policy for this control for allowing blank entries (kTrue) or not (kFalse).
		@return bool16 the boolean flag indicates if we allow to have blank entry or not.
	 */
	virtual bool16 IsBlankEntryAllowed() const = 0;

	/**	Set the policy for this control for allowing blank entries.
		@param blankAllowed [IN]: pass in kTrue to allow blanks, otherwise pass in kFalse.
	 */
	virtual void	AllowBlankEntry(const bool16& blankAllowed) = 0;

	/**	Check if the text value in the control is legal or not. 
		Return kTrue for valid entry, kFalse for invalid entry.
		@return bool16 indicates the legality value.
	 */
	virtual bool16 IsEntryLegal() = 0;	

	/**	Get the error string if the entry is not legal. An empty string will return if the entry is legal.
		@return PMString the error string explaining to the user what the error is.
	 */
	virtual PMString GetErrorString() = 0;	

	/**	Get the upper limit value for this control. The control's value must be <= this value.
		@return PMReal the upper limit for the value
	 */
	virtual PMReal GetUpperLimit() const = 0;

	/**	Set the upper limit value for this control.
		@param limit [IN]: the new upper limit for this control.
	 */
	virtual void	SetUpperLimit(const PMReal& limit) = 0;

	/**	Get the lower limit for this control. The control's value must be >= this value.
		@return PMReal the lower limit value for this control.
	 */
	virtual PMReal GetLowerLimit() const = 0;

	/**	Set the lower limit value for this control.
		@param limit [IN]: the new lower limit for this control.
	 */
	virtual void	SetLowerLimit(const PMReal& limit) = 0;

	/**	Get the boolean flag indicates if we should restore the last good value of this control or not when an error occurs. 
		For example, when IsEntryLegal() returns kFalse, we might check this to see if he last good value should be restored or not.
		@return bool16 kTrue indicates  control wants to restore last good value, otherwise return kFalse.
	 */
	virtual bool16 GetRestoreLastValueOnError() const = 0;

	/**	Set the boolean value for the control indicates that it wants to restore last good value if there is error.
		@param restoreValue [IN]: passin kTrue to restore last good value on error, otherwise pass in kFalse. Default value is set as kTrue in CTextDataValidation.cpp.
	 */
	virtual void	SetRestoreLastValueOnError(const bool16& restoreValue) = 0;
};	



#endif // __ITextDataValidation__
