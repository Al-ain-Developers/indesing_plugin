//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/ISnipRunSuite.h $
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

#ifndef __ISNIPRUNSUITE__
#define __ISNIPRUNSUITE__

#include "IPMUnknown.h"

class PMString;

/** From SDK sample; interface that provides information about registered code snippets and allows them
	to be run. Clients should check ISnipRunSuite::CanRun returns kTrue
	before calling ISnipRunSuite::Run.

	@ingroup snippetrunner
	
 */
class ISnipRunSuite : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_ISNIPRUNSUITE };

		/** Context Type */
		typedef enum {	
				kSnpRunNoContext,

				kSnpRunWorkspaceContext, 
				kSnpRunFrontDocContext, 
				kSnpRunLayoutTargetContext, 
				kSnpRunTextTargetContext, 
				kSnpRunTextSelectionTargetContext, 
				kSnpRunTableTargetContext,

				/** selecting custom requires overriding SetupContext in your SnpRunnable derived class */ 
				kSnpRunCustomContext} eSnpRunContextType;

		/** Name of a snippet, only one snippet of a given
			name can be registered with the framework.
		 */
		typedef PMString SnippetName;

		/** K2Vector of snippet names.
		 */
		typedef K2Vector<SnippetName> SnippetNames;

		/** A category a snippet belongs to e.g.
			"sdk_text", "sdk_layout". See header
			sdkdoxygengroups.h for the list of valid
			categories.
		 */
		typedef PMString Category;

		/** K2Vector of Categories's, a snippet can belong
			to more than one category.
		 */
		typedef K2Vector<Category> Categories;

		/** Get the names of all registered snippets.
			@param snippetNames OUT
		*/
		virtual void GetSnippetNames(SnippetNames& snippetNames) const = 0;

		/** @return kTrue if given snippet is available.
			@param snippetName IN
		*/
		virtual bool16 IsRegistered(const SnippetName& snippetName) const = 0;

		/** Get the categories a given snippet belongs to.
			@pre ISnipRunSuite::IsRegistered returns kTrue for the snippet.
			@param snippetName IN
			@param categories OUT categories the snippet registered as
				belonging to (sdk_text, sdk_layout etc.).
		*/
		virtual void GetCategories(const SnippetName& snippetName, Categories& categories) const = 0;

		/** Get the description of what the snippet does e.g. "creates a text frame".
			@pre ISnipRunSuite::IsRegistered returns kTrue for the snippet.
			@param snippetName IN
			@param description OUT informative text string describing what the snippet does.
		*/
		virtual void GetDescription(const SnippetName& snippetName, PMString& description) const = 0;

		/** Get the preconditions that must be met before the snippet can be run. In the case
			where CanRun returns kFalse this string indicates to the user what they must do
			in order to run the snippet. For example "layout selection" would indicate the user
			has to have at least one object selected by a pointer selection tool.
			@pre ISnipRunSuite::IsRegistered returns kTrue for the snippet.
			@param snippetName IN
			@param preconditions OUT informative text string describing preconditions required
				before ISnipRunSuite::CanRun will return kTrue.
		*/
		virtual void GetPreconditions(const SnippetName& snippetName, PMString& preconditions) const = 0;

		/** Can the snippet run? The snippet will check if pre-conditions it requires before
			running are met.
			@param snippetName IN.
			@return kTrue if the snippet can run, kFalse otherwise.
		*/
		virtual bool16 CanRun(const SnippetName& snippetName) const = 0;

		/** Run the snippet. 

			@param snippetName IN.
			@param parameters IN/OUT pass in an empty string to run the code snippet using its hard coded default parameter values,
				otherwise pass a string containing comma separated parameter values. If enableParameterDialog is kTrue the
				user will be given the chance to override these parameter values.  If a bad parameter value is detected and
				enableParameterDialog is kTrue the code snippet's hard coded default is taken and the user is given a chance
				to edit the parameter value. If a bad parameter is detected and enableParameterDialog is kFalse a message
				is output in the log and a failure status returned to the caller (provided that the snippet
				author respects ISnipRunParameterUtils::WasDialogCancelled after acquiring each parameter value).
				The parameter tokenisor uses a comma character , as a separator. To pass a comma in a parameter
				value enclose it in quotes e.g. "my, parameter". The parameter values used to run
				the snippet are recorded and passed back to the caller here.
			@param enableParameterDialog IN kTrue to allow the user to override the parameter values to be used, kFalse(default) otherwise.
				Note that if enableParameterDialog is kTrue the parameter values passed back in the parameters
				argument mey be different from those passed in by the caller.
			@return kSuccess on success, kCancel on cancel, other ErrorCode otherwise.
		*/
		virtual ErrorCode Run(const SnippetName& snippetName, PMString& parameters, bool16 enableParameterDialog = kFalse) const = 0;

		/** 
			Set up the proper InDesign context for the snippert so that it
			can be run.
			@param runnableContext
			@return kSuccess on success, other ErrorCode otherwise
		*/
		virtual ErrorCode SetupContext(const SnippetName& snippetName) = 0;

};	

#endif // __ISNIPRUNSUITE__

