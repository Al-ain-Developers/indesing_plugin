//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommandInterceptor.h $
//  
//  Owner: Roey Horns
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
//  Reviewed:	10/06/98
//  
//========================================================================================

#pragma once
#ifndef __ICOMMANDINTERCEPTOR__
#define __ICOMMANDINTERCEPTOR__

#include "CommandID.h"
#include "IPMUnknown.h"

class ICommand;
class ICommandSequence;

/**  A CommandInterceptor can be installed at the CommandProcessor in order
	to intercept any command before it is processed. The Interceptor decides
	whether the command will processed at all. There can be more than one
	CommandInterceptor at once. Use with extreme caution from third-party client code.

	@ingroup arch_cmd
*/
class ICommandInterceptor : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMMANDINTERCEPTOR };

		// Each interception method should return one of the following values.
		typedef enum
		{
			kCmdNotHandled,			// command should get passed on to other interceptors
									// 		they will decide whether to process it
			kCmdNotHandledSkipInterceptors,
									// command should get processed, other interceptors
									// 		should get skipped
			kCmdHandled				// command should not get processed, other interceptors
									//		should get skipped
		} InterceptResult;
		
		virtual InterceptResult InterceptProcessCommand(ICommand *cmd) = 0;
		virtual InterceptResult InterceptScheduleCommand(ICommand *cmd) = 0;	
		
		/** DEPRICATED
			Avoid using this function if possible - this is legacy and is deprecated.
		*/
		virtual InterceptResult InterceptExecuteDynamic(ICommand * cmd) = 0;
	
		// install/deinstall itself as command interceptor
		virtual void InstallSelf() = 0;
		virtual void DeinstallSelf() = 0;
	
		// these will eventually go away
		virtual InterceptResult InterceptExecuteImmediate(ICommand * cmd) = 0;
};

#endif // __ICOMMANDINTERCEPTOR__