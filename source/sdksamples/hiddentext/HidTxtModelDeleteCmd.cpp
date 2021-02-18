//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtModelDeleteCmd.cpp $
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
#include "INewUIDCmdData.h"
#include "IRangeData.h"
#include "ITextModel.h"
#include "IPageItemUtils.h"

// General includes:
#include "Command.h"
#include "CmdUtils.h"
#include "CommandID.h"
#include "Utils.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/** Command implementation that deletes a kHidTxtModelBoss object 
	Note this does not delete range of text in the text model that
	stores the hidden text. To delete hidden text completely process
	an ITextModelCmds::DeleteCmd to delete the TextIndex on which 
	the hidden text you want to get rid of is anchored. The memento 
	(HidTxtMemento) will take care that the associated kHidTxtModelBoss 
	objects and its story thread in the text model gets deleted too.

	
	@ingroup hiddentext
 */
class HidTxtModelDeleteCmd : public Command
{
	public:
		/** Constructor.
			@param boss refers to boss class on which this interface is aggregated
	 	*/
		HidTxtModelDeleteCmd(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtModelDeleteCmd();	
		
	protected:
		/** Delete the object using kDeleteUIDCmdBoss.
		 */
		virtual void		Do();
		
		/** Notify.
		 */
		virtual void		DoNotify();

		/** @return the name of the command.
		 */
		virtual PMString*	CreateName();

	private:
		UIDRef				fHidTxtModelUIDRef;

	private:
		/** Process kDeleteUIDCmdBoss.
			@param ref refers to the object to be deleted.
		 */
		ErrorCode			ProcessDeleteUIDCmd(const UIDRef& ref);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(HidTxtModelDeleteCmd, kHidTxtModelDeleteCmdImpl)

/*
*/
HidTxtModelDeleteCmd::HidTxtModelDeleteCmd(IPMUnknown* boss) : Command(boss),
		fHidTxtModelUIDRef(nil, kInvalidUID)
{
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::Constructor()-->In/Out\n");
}

/*
*/
HidTxtModelDeleteCmd::~HidTxtModelDeleteCmd()
{
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::Destructor()-->In/Out\n");
}

/*
*/
void HidTxtModelDeleteCmd::Do()
{
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::Do()-->In\n");
	ErrorCode status = kFailure;
	do {
		// Validate parameters.
		const UIDList& itemList = this->GetItemListReference();
		ASSERT(itemList.Length() == 1);
		if (itemList.Length() != 1) {
			break;
		}
		fHidTxtModelUIDRef = itemList.GetRef(0);
		InterfacePtr<IHidTxtModel> hidTxtModel(fHidTxtModelUIDRef, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}

		// Delete the object.
		status = this->ProcessDeleteUIDCmd(fHidTxtModelUIDRef);

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::Do()-->Out status=%d\n", status);

}

/*
*/
void HidTxtModelDeleteCmd::DoNotify()
{
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::DoNotify()-->In\n");
	Utils<IPageItemUtils> pageItemUtils;
	ASSERT(pageItemUtils);
	if (pageItemUtils && fHidTxtModelUIDRef.GetDataBase()) {
		pageItemUtils->NotifyDocumentObservers(fHidTxtModelUIDRef.GetDataBase(), ::GetClass(this), IHidTxtModel::kDefaultIID, this);
	}
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::DoNotify()-->Out\n");
}

/*
*/
PMString* HidTxtModelDeleteCmd::CreateName()
{
	return new PMString(kHidTxtModelDeleteCmdStringKey);
}

/*
*/
ErrorCode HidTxtModelDeleteCmd::ProcessDeleteUIDCmd(const UIDRef& ref)
{
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::ProcessDeleteUIDCmd()-->In\n");
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> deleteUIDCmd(CmdUtils::CreateCommand(kDeleteUIDCmdBoss));
		ASSERT(deleteUIDCmd != nil);
		if (deleteUIDCmd == nil) {
			break;
		}
		deleteUIDCmd->SetItemList(UIDList(ref));
		status = CmdUtils::ProcessCommand(deleteUIDCmd);
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtModelDeleteCmd::ProcessDeleteUIDCmd()-->Out status=%d\n", status);
	return status;
}

// End, HidTxtModelDeleteCmd.cpp