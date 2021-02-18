//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPlugPlug.cpp $
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
//  Copyright 2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
#include "VCPlugInHeaders.h"

// Interface includes:
#include "FileTypeRegistry.h"

// Snippet runner includes
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "Utils.h"
#include "ISnipRunParameterUtils.h"
#include "ICSXSPlugPlugExtensions.h"

/**
  * \li Opens or closes an extension (HTML or Flash) using its bundle ID.
  *
  * @ingroup sdk_snippet
  */
class SnpPlugPlug
{
	public:
		// Constructor.
		SnpPlugPlug() {}

		// Destructor.
		virtual ~SnpPlugPlug() {}
};

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpPlugPlug available to the SnippetRunner framework.
  *
  * @ingroup sdk_snippet_run
  */
class _SnpPlugPlug : public SnpRunnable
{
	public:
		// Constructor.
		_SnpPlugPlug();

		// Destructor.
		virtual			~_SnpPlugPlug();

		/** Return kTrue if the snippet can run.
		  * @param runnableContext see ISnpRunnableContext for documentation.
		  * @return kTrue if snippet can run, kFalse otherwise
		  */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
		  *	@param runnableContext see ISnpRunnableContext for documentation
		  * @return kSuccess on success, other ErrorCode otherwise.
		  */
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
		  * get the snippet context
		  * @return eSnpRunContextType for this snippet
		  */
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* 
 * Describes this snippet to the snippet runner framework - 
 * common to all snippets.
 */
_SnpPlugPlug::_SnpPlugPlug() : SnpRunnable("PlugPlug")
{	
	this->SetDescription("Opens or closes an extension (HTML or Flash) with a given bundle ID.");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

_SnpPlugPlug::~_SnpPlugPlug()
{
}

/* 
 * Check if your snippet's preconditions are met here.
 * For this particular snippet there are no preconditions
 * so we always return kTrue.
 */
bool16 _SnpPlugPlug::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* 
 * The main functionality of the snippet.
 */
ErrorCode _SnpPlugPlug::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do {
        Utils<ISnipRunParameterUtils> parameterUtils;

        K2Vector<PMString> choices;
		choices.push_back(PMString("Open an extension"));
		choices.push_back(PMString("Close an extension"));

		int choice = parameterUtils->GetChoice(PMString("What do you want to do?"),  choices);
		if (parameterUtils->WasDialogCancelled())
        {
			break;
		}
        
        PMString bundleId = parameterUtils->GetPMString("Bundle ID of extension:");
        if (parameterUtils->WasDialogCancelled())
        {
            break;
        }
        
        InterfacePtr<ICSXSPlugPlugExtensions> plugPlug(GetExecutionContextSession(), UseDefaultIID());
        if (!plugPlug)
		{
            break;
        }
  
        if (choice == 0)
        {
            // open an extension
            plugPlug->LoadExtension(bundleId);
        }
        else
        {
            // close an open extension
            plugPlug->UnloadExtension(bundleId);
        }
       
        status = kSuccess;

	} while(false);

	return status;
}

/*	
 * This is boilerplate code used by all snippets to register an 
 * instance of the snippet with the snippet runner framework.
 */
static _SnpPlugPlug instance_SnpPlugPlug;

DEFINE_SNIPPET(_SnpPlugPlug)