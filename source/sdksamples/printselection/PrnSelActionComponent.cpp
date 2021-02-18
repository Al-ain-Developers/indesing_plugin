//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelActionComponent.cpp $
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

// Interface includes:
#include "IActiveContext.h"
#include "IDocument.h"

// General includes:
#include "CAlert.h"
#include "CActionComponent.h"
#include "IActionStateList.h"

// Project includes:
#include "PrnSelID.h"
#include "IPrnSelUtils.h"


/** Implements the actions that are executed when plug-in menu items are selected. 
	@ingroup printselection
*/
class PrnSelActionComponent : public CActionComponent
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which interface is aggregated.
	*/
	PrnSelActionComponent(IPMUnknown* boss);

	/** Destructor.
	*/
	~PrnSelActionComponent(){}

	/**	@see IActionComponent::DoAction
	*/
	virtual void DoAction(IActiveContext* ac, 
						  ActionID actionID, 
						  GSysPoint mousePoint = kInvalidMousePoint, 
						  IPMUnknown* widget = nil);

	/** @see IActionComponent::UpdateActionStates
	*/
	virtual void UpdateActionStates(IActiveContext* ac, 
									IActionStateList* listToUpdate, 
									GSysPoint mousePoint = kInvalidMousePoint, 
									IPMUnknown* widget = nil);

private:
	/** Pops this plug-in's about box. */
	void DoAbout(void);

	/** Sets the print selection flag 
	 * 	@param ac IN Active context. 
	 * 	@see IActionComponent::DoAction
	 */
	void DoPrintSelection(IActiveContext* ac);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelActionComponent, kPrnSelActionComponentImpl)


/* Constructor
*/
PrnSelActionComponent::PrnSelActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}


/* DoAction
*/
void PrnSelActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
	case kPrnSelAboutActionID:
		{
			this->DoAbout();
			break;
		}   
	case kPrnSelPrintSelectionActionID:
		{
			this->DoPrintSelection(ac);
			break;
		}   

	default:
		{
			break;
		}
	}
}

/* UpdateActionStates
*/
void PrnSelActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do
    {
        // the menu item is disabled by default
        int16 actionState = kDisabled_Unselected;

        for (int32 i = 0; i < listToUpdate->Length(); i++)
        {
            if (listToUpdate->GetNthAction(i) == kPrnSelPrintSelectionActionID)
            {
				IDocument* doc = ac->GetContextDocument();
				if (doc != nil)
				{
					// first, enable this action
					actionState = kEnabledAction; 
					// if the flag is set, then also check the menu item
					bool16 flagValue = Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(doc);
					if (flagValue == kTrue) 
					{
						actionState |= kSelectedAction;
					}
				}
				// else if no document, disable the menu (as per default)

				// udpate the action state
                listToUpdate->SetNthActionState(i, actionState);
                // get out of for-loop, sa we are done.
                break;
            }
        }
    } while (kFalse);
}

/* DoAbout
*/
void PrnSelActionComponent::DoAbout()
{
	CAlert::ModalAlert(
					  kPrnSelAboutBoxStringKey,	  // Alert string
					  kOKString,					  // OK button
					  kNullString,					  // No second button
					  kNullString,					  // No third button
					  1,								  // Set OK button to default
					  CAlert::eInformationIcon	  // Information icon.
					  );
}

/* DoPrintSelection
*/
void PrnSelActionComponent::DoPrintSelection(IActiveContext* ac)
{
	do
	{
		if (ac == nil)
		{
			ASSERT_FAIL("IActiveContext is nil");
			break;
		}
		IDocument* doc = ac->GetContextDocument();
		if (doc == nil)
		{
			// no document -- silently exit
			break;
		}

		// get the value of the flag 
		bool16 flagValue = Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(doc);

		// selecting this menu means the user wants to toggle the flag
		bool16 newFlagValue = (flagValue == kTrue) ? kFalse : kTrue;

		// set the flag value
		ErrorCode status = Utils<IPrnSelUtils>()->_SetPrintSelectionFlag(doc, newFlagValue);
		ASSERT(status == kSuccess);

	} while (false);
}
// End, PrnSelActionComponent.cpp.




