//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpHelloBridgeTalk.cpp $
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

//BridgeTalk include
#include "IBridgeTalkUtils.h"

/**
  * \li Opens Illustrator using BridgeTalk.
  *
  * @ingroup sdk_snippet
  */
class SnpHelloBridgeTalk
{
	public:
		// Constructor.
		SnpHelloBridgeTalk() {}

		// Destructor.
		virtual ~SnpHelloBridgeTalk() {}
};

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpHelloBridgeTalk available to the SnippetRunner framework.
  *
  * @ingroup sdk_snippet_run
  */
class _SnpHelloBridgeTalk : public SnpRunnable
{
	public:
		// Constructor.
		_SnpHelloBridgeTalk();

		// Destructor.
		virtual			~_SnpHelloBridgeTalk();

		/** Return kTrue if the snippet can run.
		  * @param runnableContext see ISnpRunnableContext for documentation.
		  * @return kTrue if snippet can run, kFalse otherwise
		  */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
		  *	@param runnableContext see ISnpRunnableContext for documentation.
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
_SnpHelloBridgeTalk::_SnpHelloBridgeTalk() : SnpRunnable("HelloBridgeTalk")
{	
	this->SetDescription("Opens Illustrator using BridgeTalk");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

_SnpHelloBridgeTalk::~_SnpHelloBridgeTalk()
{

}

/* 
 * Check if your snippet's preconditions are met here.
 * For this particular snippet there are no preconditions
 * so we always return kTrue.
 */
bool16 _SnpHelloBridgeTalk::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* 
 * The main functionality of the snippet. 
 * This is where we create a string containing JavaScript
 * and send it using BridgeTalk.
 */
ErrorCode _SnpHelloBridgeTalk::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do {
        if (!Utils<IBridgeTalkUtils>().Exists())
        {
            break;
        }
        
        // This same script can be run using ExtendScript Toolkit:
        /*
         var bt = new BridgeTalk;
         bt.target = "illustrator";
         if (BridgeTalk.isRunning("illustrator"))
         {
            BridgeTalk.bringToFront("illustrator");
         }
         else
         {
            bt.body = "app.bringToFront();";
         }
         
         bt.send();
        */
        
        PMString bridgeTalkMessage;
		bridgeTalkMessage.Append("var bt = new BridgeTalk; bt.target = \"illustrator\"; ");
		bridgeTalkMessage.Append("if( BridgeTalk.isRunning('illustrator') ) {");
		bridgeTalkMessage.Append(" BridgeTalk.bringToFront('illustrator');");
		bridgeTalkMessage.Append("} else");
		bridgeTalkMessage.Append(" bt.body = \"app.bringToFront();\"; ");
		bridgeTalkMessage.Append("bt.send();");
		bridgeTalkMessage.SetTranslated();
        
        status = Utils<IBridgeTalkUtils>()->PostMessageToBridgeTalk(bridgeTalkMessage) ;

	} while(false);

	return status;
}

/*	
 * This is boilerplate code used by all snippets to register an 
 * instance of the snippet with the snippet runner framework.
 */
static _SnpHelloBridgeTalk instance_SnpHelloBridgeTalk;
DEFINE_SNIPPET(_SnpHelloBridgeTalk) 	