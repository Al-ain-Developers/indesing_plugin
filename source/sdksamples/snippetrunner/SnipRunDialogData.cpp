//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunDialogData.cpp $
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

#include "VCPlugInHeaders.h"

// Project includes:
#include "SnipRunID.h"
#include "ISnipRunDialogData.h"

/** Implementation of ISnipRunDialogData.

	@ingroup snippetrunner
	
	@see ISnipRunDialogData
 */
class SnipRunDialogData : public CPMUnknown<ISnipRunDialogData>
{
	public:
		/**	Constructor.
			@param boss 
		 */
		SnipRunDialogData(IPMUnknown* boss);

		/**	Destructor.
		 */
		virtual ~SnipRunDialogData();

		/**	See ISnipRunDialogData::EnableTranslation
		 */
		virtual void						EnableTranslation(const bool16 enable) {fIsTranslationEnabled = enable;}

		/**	See ISnipRunDialogData::SetMode
		 */		
		virtual void						SetMode(SnipRunDialogMode mode) {fMode = mode;}

		/**	See ISnipRunDialogData::GetMode
		 */	
		virtual const SnipRunDialogMode&	GetMode() const {return fMode;}

		/**	See ISnipRunDialogData::SetPrompt
		 */
		virtual void						SetPrompt(const PMString& value) {SetString(fPrompt, value);}

		/**	See ISnipRunDialogData::GetPrompt
		 */
		virtual	const PMString&				GetPrompt() const {return fPrompt;}

		/**	See ISnipRunDialogData::SetTypeInfo
		 */
		virtual void						SetTypeInfo(const PMString& value) {SetString(fTypeInfo, value);}

		/**	See ISnipRunDialogData::GetTypeInfo
		 */
		virtual	const PMString&				GetTypeInfo() const {return fTypeInfo;}

		/**	See ISnipRunDialogData::SetPMString
		 */
		virtual void						SetPMString(const PMString& value) {SetString(fPMString, value);}

		/**	See ISnipRunDialogData::GetPMString
		 */
		virtual	const PMString&				GetPMString() const {return fPMString;}

		/**	See ISnipRunDialogData::SetInt32
		 */
		virtual void						SetInt32(const int32 value) {fInt32 = value;}

		/**	See ISnipRunDialogData::GetInt32
		 */
		virtual const int32&				GetInt32() const {return fInt32;}

		/**	See ISnipRunDialogData::SetPMReal
		 */
		virtual void						SetPMReal(const PMReal& value) {fPMReal = value;}

		/**	See ISnipRunDialogData::GetPMReal
		 */
		virtual const PMReal&				GetPMReal() const {return fPMReal;}

		/**	See ISnipRunDialogData::SetChoiceIndex
		 */
		virtual void						SetChoiceIndex(const int32 value) {fChoiceIndex = value;}

		/**	See ISnipRunDialogData::GetChoiceIndex
		 */
		virtual const int32&				GetChoiceIndex() const {return fChoiceIndex;}

		/**	See ISnipRunDialogData::SetChoices
		 */
		virtual void						SetChoices(const K2Vector<PMString>& choices);

		/**	See ISnipRunDialogData::GetChoices
		 */
		virtual const K2Vector<PMString>&	GetChoices() const {return fChoices;}

		/**	See ISnipRunDialogData::SetLowerLimit
		 */
		virtual void						SetLowerLimit(const PMReal& lowerLimit) {fLowerLimit = lowerLimit;}

		/**	See ISnipRunDialogData::GetLowerLimit
		 */
		virtual const PMReal&				GetLowerLimit() const {return fLowerLimit;}

		/**	See ISnipRunDialogData::SetUpperLimit
		 */
		virtual void						SetUpperLimit(const PMReal& upperLimit) {fUpperLimit = upperLimit;}

		/**	See ISnipRunDialogData::GetUpperLimit
		 */
		virtual const PMReal&				GetUpperLimit() const {return fUpperLimit;}		

		/**	See ISnipRunDialogData::SetWasCancelled
		 */
		virtual void						SetWasCancelled(const bool16 value) {fWasCancelled = value;}

		/**	See ISnipRunDialogData::GetWasCancelled
		 */
		virtual const bool16&				GetWasCancelled() const {return fWasCancelled;}

	private:
		ISnipRunDialogData::SnipRunDialogMode fMode;
		PMString fPMString;
		int32 fInt32;
		PMReal fPMReal;
		int32 fChoiceIndex;
		K2Vector<PMString> fChoices;
		PMReal fLowerLimit;
		PMReal fUpperLimit;
		PMString fPrompt;
		bool16 fWasCancelled;
		PMString fTypeInfo;
		bool16 fIsTranslationEnabled;

	private:	

		/**	Copies source to target and calls SetTranslatable(kFalse) if
			the strings passing through the interface are not translatable.
			target 
			@param target 
			@param source 
		 */
		void							SetString(PMString& target, const PMString& source);
};

/*
*/
CREATE_PMINTERFACE(SnipRunDialogData, kSnipRunDialogDataImpl)

/*
*/
SnipRunDialogData::SnipRunDialogData(IPMUnknown* boss) : CPMUnknown<ISnipRunDialogData>(boss),
fMode(ISnipRunDialogData::kSnipRunStringMode),
fPMString(""),
fInt32(0),
fPMReal(0.0),
fChoiceIndex(0),
fLowerLimit(0.0),
fUpperLimit(0.0),
fPrompt(""),
fWasCancelled(kFalse),
fTypeInfo(""),
fIsTranslationEnabled(kTrue)
{
}

/*
*/
SnipRunDialogData::~SnipRunDialogData()
{
}

/*
*/
void SnipRunDialogData::SetString(PMString& target, const PMString& source)
{
	target = source;
	if (fIsTranslationEnabled == kFalse && target.HasTranslated() == kFalse) {
		target.SetTranslatable(kFalse);
	}
}

/*
*/
void SnipRunDialogData::SetChoices(const K2Vector<PMString>& choices)
{
	fChoices = choices;
	if (fIsTranslationEnabled == kFalse) {
		K2Vector<PMString>::iterator iter;
		for (iter = fChoices.begin(); iter < fChoices.end(); iter++) {
			if (iter->HasTranslated() == kFalse) {
				iter->SetTranslatable(kFalse);
			}
		}
	}
}

// End SnipRunDialogData.cpp
