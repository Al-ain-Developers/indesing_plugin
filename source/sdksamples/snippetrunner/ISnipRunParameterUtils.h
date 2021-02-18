//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/ISnipRunParameterUtils.h $
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

#ifndef _ISnipRunParameterUtils_
#define _ISnipRunParameterUtils_

class PMString;

/** From SDK sample; utility interface for parameter gathering that allows snippets to prompt
	for a data type value(for example PMString, int32). The normal behavour
	of this interface will be to pop a dialog and request a value to
	be entered by the user. This allows code snippets to acquire parameter
	values when they run.
	
	The code below shows how to declare and use the interface to get the 
	value of a PMString:
	<pre>
	Utils<ISnipRunParameterUtils> parameterUtils;
	PMString swatchName = parameterUtils->GetPMString("Swatch name", "Black");
	if (parameterUtils->WasDialogCancelled()) {
		// The user cancelled and you should too,
		// don't prompt for any more parameters,
	}
	</pre>

	@ingroup snippetrunner
	
*/
class ISnipRunParameterUtils : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_ISNIPRUNPARAMETERUTILS };

		/**	Return a PMString value. 
		
			The code below requests a string that represents the name of a swatch that defaults to "Black".
	<pre>
	PMString swatchName = parameterUtils->GetPMString("Swatch name", "Black");
	</pre>

			@param prompt IN describing what the string represents
			@param defaultValue IN (default "")
			@return a PMString value
		 */
		virtual PMString	GetPMString(const PMString& prompt, const PMString& defaultValue = "") const = 0;

		/**	Return an int32 value.

			The code below requests an int32 that represents a page number with a default value
			of 1 and no range checking.
	<pre>
	int32 pageNumber = parameterUtils->GetInt32("Page  number", 1);
	</pre>

			The code below checks the page number entered is in the range 1 to 9999:
	<pre>
	int32 pageNumber = parameterUtils->GetInt32("Number of pages", 1, 1, 9999);
	</pre>

			@param prompt IN describing what the int32 represents
			@param defaultValue IN (default 0)
			@param lowerLimit IN (default 0, if both lowerLimit and upperlimit are 0 range checking is switched off)
			@param upperLimit IN (default 0)
			@return an int32 value
		 */
		virtual int32		GetInt32(const PMString& prompt, const int32 defaultValue = 0, const int32 lowerLimit = 0, const int32 upperLimit = 0) const = 0;

		/**	Return a PMReal value.

			The code below requests a PMReal that represents stroke weight with a default value of 1.0
			and no range checking.
	<pre>
	PMReal strokeWeight = parameterUtils->GetPMReal("Stroke weight", 1);
	</pre>

			The code below checks the stroke weight entered is in the range 1 to 1000:
	<pre>
	int32 pageNumber = parameterUtils->GetInt32("Number of pages", 1, 1, 1000);
	</pre>

			@param prompt IN describing what the PMReal represents
			@param defaultValue IN (default 0)
			@param lowerLimit IN (default 0, if both lowerLimit and upperlimit are 0 range checking is switched off)
			@param upperLimit IN (default 0)
			@return a PMReal value
		 */
		virtual PMReal		GetPMReal(const PMString& prompt, const PMReal& defaultValue = 0, const PMReal& lowerLimit = 0, const PMReal& upperLimit = 0) const = 0;

		/**	Return the index of a selected choice from a list of choices described 
			by a vector of PMString's.

			The code below requests a choice between "DoThis" and "DoThat" to be made.
	<pre>
	K2Vector<PMString> choices;
	choices.push_back(PMString("DoThis"));
	choices.push_back(PMString("DoThat"));
	enum {kDoThis, kDoThat};
	int32 choice  = parameterUtils->GetChoice("What do you want to do.", choices);
	if (parameterUtils->WasDialogCancelled() == kFalse) {
		switch (choice) 
		{
		case kDoThis:
		case kDoThat:
		}
	}
	</pre>

			@param prompt IN describing what the choice represents
			@param choices IN vector of strings representing the choices available
			@param defaultChoiceIndex IN (default 0)
			@return the index of the selected choice
		 */
		virtual int32		GetChoice(const PMString& prompt, const K2Vector<PMString>& choices, const int32 defaultChoiceIndex = 0) const = 0;

		/**	Return kTrue if the user cancelled instead of supplying a value, kFalse otherwise.
			When cancel is detected your snippet should stop and return control to its caller, 
			don't prompt for any more values
			@return  kTrue if the user cancelled, kFalse otherwise.
		 */
		virtual bool16		WasDialogCancelled() const = 0;

	public:
		// The methods in this section are for the use of the SnippetRunner framework
		// and should be avoided.

		/** For the use of the SnippetRunner framework, please avoid.
			Controls the display of parameter dialogs(enabled by default). 
			If ISnipRunParameterUtils::IsDailogEnabled is kFalse, no parameter dialogs will be displayed. 
			In that case, ISnipRunParameterUtils calls will return the default value 
			passed into the call.

			You should not need to call this method but if you do
			please save the state of the flag before you change it 
			and restore it after you are done, thank you.

			@param enable IN kTrue to prompt the user for parameter values, kFalse otherwise.
		*/
		virtual void		EnableDialog(const bool16 enable) = 0;
	
		/** For the use of the SnippetRunner framework, please avoid.
			@return kTrue if the user should be prompted for parameter values, 
				kFalse otherwise.
		*/
		virtual bool16		IsDialogEnabled() const = 0;

		/** For the use of the SnippetRunner framework, please avoid.
			Controls whether or not PMString's passed into 
			parameter prompt calls are translatable. By default
			PMString's must be translatable.
			
			You should not need to call this method but if you do
			please save the state of the flag before you change it 
			and restore it after you are done, thank you.

			Code snippets don't have to call this method. By default
			the strings used in snippets are not translatable and the
			SnippetRunner framework will make sure this API expects
			untranslatable strings to be passed.
			
			If ISnipRunParameterUtils::IsTranslationEnabled is kFalse, 
			PMString's passed into ISnipRunParameterUtils will be marked
			as untranslatable by calling PMString::SetTranslatable(kFalse).

			@param enable IN kTrue to pass translatable strings, kFalse otherwise.
		*/
		virtual void		EnableTranslation(const bool16 enable) = 0;
	
		/** For the use of the SnippetRunner framework, please avoid.
			@return kTrue if PMString's passing through this API are
			translatable, kFalse otherwise.
		*/
		virtual bool16		IsTranslationEnabled() const = 0;

		/** Set the parameters the snippet should run with.
			@param params a CSV string containing parameter values or empty string if the user
				should be prompted for parameters.
		 */
		virtual void		SetParameters(const PMString& params) = 0;

		/** Get the parameters the snippet was run with. If the user enters parameter
			values in the parameter dialog these values are recorded and can be returned
			by this method after the snippet has run.
			@return a CSV string containing parameter values.
		 */
		virtual PMString		GetParameters() = 0;

};

#endif // _ISnipRunParameterUtils_
