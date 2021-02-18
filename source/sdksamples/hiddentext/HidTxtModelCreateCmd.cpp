//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtModelCreateCmd.cpp $
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
#include "ITextModelCmds.h"
#include "IPageItemUtils.h"

// General includes:
#include "Command.h"
#include "CmdUtils.h"
#include "CommandID.h"
#include "TextChar.h"
#include "Utils.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/** Command implementation that creates hidden text.

	
	@ingroup hiddentext
 */
class HidTxtModelCreateCmd : public Command
{
	public:
		/** Constructor.
			@param boss refers to boss class on which this interface is aggregated 
		 */
		HidTxtModelCreateCmd(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtModelCreateCmd();	
		
	protected:
		/** Inserts a kTextChar_ZeroSpaceNoBreak at the given TextIndex as
			an anchor character for the hidden text, it creates a kHidTxtModelBoss
			object to represent the hidden text then associates the
			kHidTxtModelBoss object with the anchor character by calling
			IHidTxtModel::AttachToTextModel.
		 */
		virtual void		Do();
		
		/** Notify.
		 */
		virtual void		DoNotify();
		
		/** @return the command name.
		 */
		virtual PMString*	CreateName();

	private:
		UIDRef				fHidTxtModelUIDRef;
		UIDRef				fTextModelUIDRef;

	private:
		/** Process ITextModelCmds->InsertCmd to insert the character on 
			which the hidden text is anchored.
			@param anchorTextIndex
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode			ProcessInsertAnchorCharacterCmd(const TextIndex anchorTextIndex);
		/** Process kNewUIDCmdBoss to create a new object of the given class.
			@param db IN refers to the database the object is to be created in.
			@param bossClassID IN gives the type of object to create.
			@param bossObjectUIDRef OUT is where the reference to the created object is returned
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode			ProcessNewUIDCmd(IDataBase* db, const ClassID& bossClassID, UIDRef& bossObjectUIDRef);
};

/*
*/
CREATE_PMINTERFACE(HidTxtModelCreateCmd, kHidTxtModelCreateCmdImpl)

/*
*/
HidTxtModelCreateCmd::HidTxtModelCreateCmd(IPMUnknown* boss) : Command(boss),
		fHidTxtModelUIDRef(nil, kInvalidUID),
		fTextModelUIDRef(nil, kInvalidUID)
{
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::Constructor()-->In/Out\n");
}

/*
*/
HidTxtModelCreateCmd::~HidTxtModelCreateCmd()
{
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::Destructor()-->In/Out\n");
}

/*
*/
void HidTxtModelCreateCmd::Do()
{
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::Do()-->In\n");
	ErrorCode status = kFailure;
	do {
		// Validate parameters.
		const UIDList& itemList = this->GetItemListReference();
		ASSERT(itemList.Length() == 1);
		if (itemList.Length() != 1) {
			break;
		}
		fTextModelUIDRef = itemList.GetRef(0);
		this->SetItemList(UIDList(UIDRef(nil,kInvalidUID))); // clear the returned reference so if we fail the caller gets a bad UIDRef back
		InterfacePtr<ITextModel> textModel(fTextModelUIDRef, UseDefaultIID());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<IRangeData> rangeData(this, UseDefaultIID());
		ASSERT(rangeData != nil);
		if (rangeData == nil) {
			break;
		}
		const TextIndex anchorTextIndex = rangeData->GetStart();
		ASSERT(anchorTextIndex != kInvalidTextIndex);
		if (anchorTextIndex == kInvalidTextIndex) {
			break;
		}

		// 1) Insert anchor character for the hidden text.
		this->ProcessInsertAnchorCharacterCmd(anchorTextIndex);	

		// 2) Create a new kHidTxtModelBoss object.
		ErrorCode st1 = this->ProcessNewUIDCmd(fTextModelUIDRef.GetDataBase(), kHidTxtModelBoss, fHidTxtModelUIDRef);
		ASSERT(st1 == kSuccess);
		if (st1 != kSuccess) {
			break;
		}

		// 3) Attach the new object to the given text model anchored at the given TextIndex.
		InterfacePtr<IHidTxtModel> hidTxtModel(fHidTxtModelUIDRef, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		status = hidTxtModel->AttachToTextModel(fTextModelUIDRef.GetUID(), anchorTextIndex);
		ASSERT(status == kSuccess);
		if (status != kSuccess) {
			break;
		}

		// Return the caller a reference to new object.
		this->SetItemList(UIDList(fHidTxtModelUIDRef));

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::Do()-->Out status=%d\n", status);

}

/*
*/
void HidTxtModelCreateCmd::DoNotify()
{
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::DoNotify()-->In\n");
	Utils<IPageItemUtils> pageItemUtils;
	ASSERT(pageItemUtils);
	if (pageItemUtils && fHidTxtModelUIDRef.GetDataBase()) {
		pageItemUtils->NotifyDocumentObservers(fHidTxtModelUIDRef.GetDataBase(), ::GetClass(this), IHidTxtModel::kDefaultIID, this);
	}
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::DoNotify()-->Out\n");
}

/*
*/
PMString* HidTxtModelCreateCmd::CreateName()
{
	return new PMString(kHidTxtModelCreateCmdStringKey);
}

/*
*/
ErrorCode HidTxtModelCreateCmd::ProcessInsertAnchorCharacterCmd(const TextIndex anchorTextIndex)
{
	ErrorCode status = kFailure;
	do {

		// Insert anchor character.
		//saCS change use ITextModelCmds instead of ITextModel
		InterfacePtr<ITextModelCmds> textModelCmds(fTextModelUIDRef, UseDefaultIID());
		ASSERT(textModelCmds != nil);
		if (textModelCmds == nil) {
			break;
		}
		//saCS change use boost::shared_ptr<WideString> to pass data to text model cmds.
		boost::shared_ptr<WideString> anchor(new WideString());
		anchor->Append(kTextChar_ZeroSpaceNoBreak);
	    InterfacePtr<ICommand> insertCmd(textModelCmds->InsertCmd(anchorTextIndex, anchor));
		ASSERT(insertCmd != nil);
		if (insertCmd == nil) {
			break;
		}
		status = CmdUtils::ProcessCommand(insertCmd);
		ASSERT_MSG(status == kSuccess, "ITextModelCmds::InsertCmd failed");

	} while(false);
	return status;
}

/*
*/
ErrorCode HidTxtModelCreateCmd::ProcessNewUIDCmd(IDataBase* db, const ClassID& bossClassID, UIDRef& bossObjectUIDRef)
{
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::ProcessNewUIDCmd()-->In\n");
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> newUIDCmd(CmdUtils::CreateCommand(kNewUIDCmdBoss));
		ASSERT(newUIDCmd != nil);
		if (newUIDCmd == nil) {
			break;
		}
		InterfacePtr<INewUIDCmdData> newUIDCmdData(newUIDCmd, UseDefaultIID());
		ASSERT(newUIDCmdData != nil);
		if (newUIDCmdData == nil) {
			break;
		}
		newUIDCmdData->Set(db, bossClassID);
		status = CmdUtils::ProcessCommand(newUIDCmd);
		ASSERT(status == kSuccess);
		if (status == kSuccess) {
			bossObjectUIDRef = newUIDCmd->GetItemListReference().GetRef(0);
		}
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtModelCreateCmd::ProcessNewUIDCmd()-->Out status=%d\n", status);
	return status;
}

// End, HidTxtModelCreateCmd.cpp