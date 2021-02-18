//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/ISnipRunDialogData.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ISNIPRUNDIALOGDATA__
#define __ISNIPRUNDIALOGDATA__

class PMString;
class PMReal;

/** From SDK sample; data interface to exchange information between 
	parameter dialog (kSnipRunDialogBoss) and client code
	that uses it.

	@ingroup snippetrunner
	
	@see ISnipRunDialogData
	@see kSnipRunDialogBoss
	@see SnipRunDialogController
 */
class ISnipRunDialogData : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_ISNIPRUNDIALOGDATA };

		/**	Allows the client to indicate whether PMString's passed through this interface 
			to the dialog are translatable or not.
			@param enable kTrue(default) if strings passing are translatable, kFalse otherwise.
		 */
		virtual void						EnableTranslation(const bool16 enable) = 0;

		/** Mode indicating type of data (PMString, int32 etc.) the dialog
			is to gather and return to the caller.
		 */
		typedef enum { kSnipRunStringMode, kSnipRunIntMode, kSnipRunHexMode, kSnipRunRealMode, kSnipRunChoiceMode } SnipRunDialogMode;

		/**	Set the type of data the dialog is to gather.
			@param mode 
		 */
		virtual void						SetMode(SnipRunDialogMode mode) = 0;

		/**	@return the mode.
		 */
		virtual const SnipRunDialogMode&	GetMode() const = 0;

		/**	Set the prompt that describes what the data the user is being 
			requested to enter is (displayed at the top of the dialog).
			@param value 
		 */
		virtual void						SetPrompt(const PMString& value) = 0;

		/**	@return the prompt.
		 */
		virtual	const PMString&				GetPrompt() const = 0;

		/**	Set the TypeInfo that describes the data type and its range
			(for example "int32 1:10" displayed at the bottom of the dialog).
			@param value 
		 */
		virtual void						SetTypeInfo(const PMString& value) = 0;

		/**	@return the typeInfo.
		 */
		virtual	const PMString&				GetTypeInfo() const = 0;


		/**	Set PMString data
			@param value 
		 */
		virtual void						SetPMString(const PMString& value) = 0;

		/**	@return PMString data value
		 */
		virtual	const PMString&				GetPMString() const = 0;

		/**	Set int32 data
			@param value 
		 */
		virtual void						SetInt32(const int32 value) = 0;

		/**	@return int32 data value
		 */
		virtual const int32&				GetInt32() const = 0;

		/**	Set PMReal data
			@param value 
		 */
		virtual void						SetPMReal(const PMReal& value) = 0;

		/**	@return PMReal data value
		 */
		virtual const PMReal&				GetPMReal() const = 0;

		/**	Set ChoiceIndex data
			@param value index into ISnipRunDialogData::GetChoices of chosen string.
		 */
		virtual void						SetChoiceIndex(const int32 value) = 0;

		/**	@return ChoiceIndex data value
		 */
		virtual const int32&				GetChoiceIndex() const = 0;

		/**	Set Choices data
			@param choices 
		 */
		virtual void						SetChoices(const K2Vector<PMString>& choices) = 0;

		/**	@return Choices data value
		 */
		virtual const K2Vector<PMString>&	GetChoices() const = 0;

		/** Set lower limit for range checked data value.
			@param lowerLimit
		 */
		virtual void						SetLowerLimit(const PMReal& lowerLimit) = 0;

		/**	@return LowerLimit data value
		 */
		virtual const PMReal&				GetLowerLimit() const = 0;

		/** Set upper limit for range checked data value.
			@param upperLimit
		 */
		virtual void						SetUpperLimit(const PMReal& upperLimit) = 0;

		/**	@return UpperLimit data value
		 */
		virtual const PMReal&				GetUpperLimit() const = 0;

		/** Set flag that indicates the user cancelled the dialog.
			@param value kTrue if dialog was cancelled, kFalse otherwise.
		 */
		virtual void						SetWasCancelled(const bool16 value) = 0;

		/**	@return kTrue if dialog was cancelled, kFalse otherwise.
		 */
		virtual const bool16&				GetWasCancelled() const = 0;
};	

#endif // __ISNIPRUNDIALOGDATA__

