//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnpRunnable.h $
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

#ifndef _SnpRunnable_
#define _SnpRunnable_

// General includes:
#include "BaseType.h"

// Project includes:
#include "SnipRunID.h"
#include "IActiveContext.h"
#include "ISnpRunnableContext.h"
#include "SnpReferenceMacros.h"
#include "ISnipRunSuite.h"

/** 
	The hook used to make a snippet of code callable by the SnippetRunner
	framework and to describe the snippet in the UI. To register the
	snippet with the framework a static instance of the snippet must
	be declared. The constructor registers the snippet via SnipRunManager. 

	This registration happens each time
	the plug-in is loaded into memory. It's an approach that is ok for a
	development tool type plug-in like SnippetRunner but is not one that
	should be used for functional plug-ins.

	@ingroup snippetrunner
	
*/
class SnpRunnable
{
	public:
		/**
			Constructor adds the snippet to the dictionary maintained by SnipRunManager.
			@param name of the snippet.
		*/
		SnpRunnable(ConstCString name);

		/** 
			Destructor removes the snippet from the dictionary maintained by SnipRunManager.
		*/
		virtual ~SnpRunnable();

		/** 
			Return name of snippet.
		*/
		virtual ConstCString GetName() const {return fName;}

		/**
			Return a description of what the snippet does.
		*/
		virtual ConstCString	GetDescription() const {return fDescription;}

		/**
			Return dscription of the preconditions necessary for 
			successful execution of the snippet.
		*/
		virtual ConstCString	GetPreconditions() const {return fPreconditions;};

		/**
			Return the categories this snippet belongs to,
			formatted as a CSV string e,g, "sdk_snippet, sdk_layout".
		*/
		virtual ConstCString	GetCategories() const {return fCategories;}

		/** 
			Can the snippet run? Snippets must implement this method and
			use the given ISnpRunnableContext to figure out if they can
			run.
			@param runnableContext
			@return kTrue if preconditions for running are met, kFalse otherwise.
		*/
		virtual bool16 CanRun(ISnpRunnableContext* runnableContext) = 0;

		/**
			Run the snippet using the context given by ISnpRunnableContext.
			@param runnableContext parameters
			@return kSuccess on success, other ErrorCode otherwise
		*/
		virtual ErrorCode Run(ISnpRunnableContext* runnableContext) = 0;

		/**
			default behavior for snippet unit test
			@param runnableContext parameters, this is the same context as in the Run method
			@return kSuccess on success, other ErrorCode otherwise
		*/
		virtual ErrorCode RunUnitTest(ISnpRunnableContext* runnableContext);

		/** 
			Define this method if your snippet should only be available
			to be chosen to run under a specific product(InDesign, InCopy, etc) or 
			language (Roman, Japanese), your snippet won't be presented 
			in the framework's UI if you return kFalse. For example if you don't 
			want your snippet to be available to the user under InCopy implement 
			this method and check the product.

			Added for 1036945.

			The code below shows how your CanLoad method can detect which 
			product or language feature set your snippet is running under.
			<pre>
			#include "FeatureSets.h"
			#include "LocaleSetting.h"

			bool16 isInCopyProductFS = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);
			bool16 isInDesignProductFS = LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS);
			bool16 isRomanLanguageFS = LocaleSetting::GetLocale().IsLanguageFS(kRomanLanguageFS);
			bool16 isJapaneseLanguageFS = LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS);
			</pre>
			@return kTrue (default) if the snippet should be presented in the framework's UI, kFalse otherwise.
		*/
		virtual bool16 CanLoad() const {return kTrue;}

		/** 
			default behavior for snippet setup context

			Set up the proper InDesign context for the snippert so that it
			can be run.
			@param runnableContext
			@return kSuccess on success, other ErrorCode otherwise
		*/
		virtual ErrorCode SetupContext(ISnpRunnableContext* runnableContext);

		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void) = 0;

	protected:
		// The protected methods in this section must be called
		// by the derived class's constructor. The strings a snippet 
		// author provides will be made available via ISnipRunSuite
		// and displayed in the UI.

		/**	To be called by sub-classes in their constructor to describe
			what the snippet does.
			@param description 
		 */
		virtual void			SetDescription(ConstCString description) {fDescription = description;}
		/**	To be called by sub-classes in their constructor to describe
			the preconditions that must be met before SnpRunnable::CanRun will
			return kTrue.
			@param preconditions 
		 */
		virtual void			SetPreconditions(ConstCString preconditions) {fPreconditions = preconditions;}
		/**	To be called by sub-classes in their constructor to describe
			the categories the snippet belongs too as a CSV string of the form
			"sdk_snippet, sdk_layout".
			@param categories 
			@see sdkdoxygengroups.h for valid categories.
		 */
		virtual void			SetCategories(ConstCString categories) {fCategories = categories;}

	private:
		ConstCString fName;
		ConstCString fDescription;
		ConstCString fPreconditions;
		ConstCString fCategories;
};

#endif // SnpRunnable

// End, SnpRunnable.h

