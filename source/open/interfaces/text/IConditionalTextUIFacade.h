//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IConditionalTextUIFacade.h $
//  
//  Owner: Michele Stutzman
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

#pragma once
#ifndef __ICONDITIONALTEXTUIFACADE__
#define __ICONDITIONALTEXTUIFACADE__

#include "ConditionalTextUIID.h"
#include "Utils.h"

#include "IPanelControlData.h"

namespace Facade
{
	/** The IConditionalTextFacade provides high-level access to public interfaces for displaying UI. Suggested usage:

			Utils<Facade::IConditionalTextFacade>()->method( params,... );
	*/
	class IConditionalTextUIFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICONDITIONALTEXTUIFACADE };
	
		/** This method invokes the condition options dialog to edit the options for an existing 
			condition or for creating a new condition.  The title of the dialog will
			be set appropriately.
			@param ws IN Workspace the condition to edit is in or one will be created in.
			@param conditionToEdit IN The UID of the condition to edit or kInvalidUID for new condition.
			@return ErrorCode kSuccess if the options dialog is opened successfully.
		*/
		virtual ErrorCode DoConditionOptionsDialog(IWorkspace* ws, UID conditionToEdit) = 0;

		/** This method updates the applied icons for the condition list tree nodes for given the workspace and panel control data.
			@param ws IN The workspace the condition list is in.
			@param iPanelControlData IN The panel control data the condition list tree is in.
		*/
		virtual void UpdateAppliedIcons(IWorkspace* ws, IPanelControlData* iPanelControlData) const = 0;
	
		/** This method deletes the condition(s).  If the condition(s) is used it will prompt
			the user for a replacement.  If UI is suppressed then the condition(s) is simply
			removed from the text.
			@param ws IN Workspace the condition to delete is in or one will be created in.
			@param conditionsToDelete IN A list of condition UIDs to delete.
			@param suppressUI IN Whether to prompt the user for a replacement if the condition is used.
			@return ErrorCode kSuccess if the condition is deleted successfully.
		*/
		virtual ErrorCode DeleteConditions(IWorkspace* ws, const K2Vector<UID>& conditionsToDelete, bool16 suppressUI) = 0;
	
		/** This method invokes the open dialog and then performs the load conditions operation.
			@param ws IN Workspace the conditions and sets are loaded into.
			@param loadConditionSets IN If kTrue then condition sets are loaded; otherwise, only conditions are loaded.
			@return ErrorCode kSuccess if the conditions and sets are loaded successfully.
		*/
		virtual ErrorCode LoadConditions(IWorkspace* ws, bool16 loadConditionSets = kTrue) = 0;
	
		/** This method selects all unused conditions.
			@param ws IN Workspace to examine for usage.
		*/
		virtual void SelectUnusedConditions(IWorkspace* ws) = 0;
	};
}

#endif	// define __ICONDITIONALTEXTUIFACADE__
