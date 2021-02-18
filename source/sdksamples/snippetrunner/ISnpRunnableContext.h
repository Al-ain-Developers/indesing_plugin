//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/ISnpRunnableContext.h $
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

#ifndef __ISnpRunnableContext__
#define __ISnpRunnableContext__

#include "IActiveContext.h"

/** From SDK sample; interface that provides a code snippet with the context in which it is to run and can 
	used to get the selection target, the active document and other
	contextual information. 

	Code snippet's SnpRunnable::CanRun and SnpRunnable::Run methods get passed
	the ISnpRunnableContext interface in a parameter called runnableContext.
	ISnpRunnableContext is aggregated onto each concrete selection boss class
	in the application and can be queried for the selection target and for 
	suites on a concrete selection.

	The code below queries runnableContext for the layout selection target:
	<pre>
	InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
	if (layoutTarget) {
		// a layout selection exists, do something.
	}
	else {
		// a layout selection is not available, do nothing.
	}
	</pre>
	To get the selection target (ILayoutTarget, ITextTarget, ITableTarget, 
	IXMLNodeTarget etc.) query the runnableContext parameter for the 
	target you want to work with. Note that it is recommended that your 
	snippet only targets one selection format.
	
	Note the access to the selection's target lets you prototype code for a 
	custom suite quickly and efficiently using the SnippetRunner framework.
	Remember though that it is a prototyping tool and you must move
	your code into a custom suite when it is ready.

	The code below shows how to use ISnpRunnableContext to discover the 
	a suite, the active document, workspace, view and more:
	<pre>

	// How do I get a suite from ISnpRunnableContext?
	InterfacePtr<IFooSuite> fooSuite(runnableContext, UsedefaultIID());
	if (fooSuite) {
		// you can use the suite.
	}

	// How do I get the active document from ISnpRunnableContext?
	IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();

	// How do I get the active workspace from ISnpRunnableContext?
	IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();

	// How do I get the active view from ISnpRunnableContext
	IControlView* controlView = runnableContext->GetActiveContext()->GetContextView();

	// How do I get the active layout control data from ISnpRunnableContext?
	InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());

	// How do I get the active selection manager from ISnpRunnableContext?
	ISelectionManager* selectionManager = runnableContext->GetActiveContext()->GetContextSelection(); 

	// How do I get a suite via the active selection manager from ISnpRunnableContext?
	InterfacePtr<IBarSuite> barSuite(runnableContext->GetActiveContext->GetContextSelection(), UseDefaultIID()); 
	// Note that this call is different from the IFooSuite code described previously. The call
	// shown here queries the suite via the active ISelectionManager. 
  </pre>

	The code below shows how your SnpRunnable::CanRun method can check which product or language 
	feature set your snippet is running under. Normally you won't need to check but if you do:
	<pre>
	#include "FeatureSets.h"
	#include "LocaleSetting.h"

	bool16 isInCopyProductFS = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);
	bool16 isInDesignProductFS = LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS);
	bool16 isRomanLanguageFS = LocaleSetting::GetLocale().IsLanguageFS(kRomanLanguageFS);
	bool16 isJapaneseLanguageFS = LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS);
	</pre>

 */
class ISnpRunnableContext : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_ISNPRUNNABLECONTEXT };

		/** Return the active context from which the active
			document, view, workspace and selection manager
			can be obtained.
			@return the active context.
		*/
		virtual IActiveContext* GetActiveContext() const = 0;
};

#endif // __ISnpRunnableContext__

