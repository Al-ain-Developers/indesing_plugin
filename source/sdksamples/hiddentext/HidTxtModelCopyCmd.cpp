//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtModelCopyCmd.cpp $
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
#include "IUIDData.h"
#include "IXReferenceUID.h"
#include "IScrapUtils.h"

// General includes:
#include "Command.h"
#include "CmdUtils.h"
#include "CommandID.h"
#include "Utils.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/** Command implementation that copies a kHidTxtModelBoss object to another
	story. 
	
	Note that this command does not copy the range of text in the text model
	that stores the actual hidden text, it just copies the kHidTxtModelBoss
	object.

	
	@ingroup hiddentext
 */
class HidTxtModelCopyCmd : public Command
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtModelCopyCmd(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtModelCopyCmd();	
		
	protected:
		/** This command's item list refers to the object to be copied.
			The command's IUIDData interface gives the database into
			which the object is to be copied. So we have to override
			SetUpTarget to target the database given by the IUIDData
			data interface.
		 */
		virtual void		SetUpTarget();
		
		/** Copy the object using IScrapUtils::CopyObject.
		 */
		virtual void		Do();
		
		/** No notification is currently performed for this operation.
		 */
		virtual void		DoNotify();
		
		/** @return the name of the command.
		 */
		virtual PMString*	CreateName();
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(HidTxtModelCopyCmd, kHidTxtModelCopyCmdImpl)

/*
*/
HidTxtModelCopyCmd::HidTxtModelCopyCmd(IPMUnknown* boss) : Command(boss)
{
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::Constructor()-->In/Out\n");
}

/*
*/
HidTxtModelCopyCmd::~HidTxtModelCopyCmd()
{
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::Destructor()-->In/Out\n");
}

/*
*/
void HidTxtModelCopyCmd::SetUpTarget()
{
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::SetUpTarget()-->In\n");
	IDataBase* target = nil;
	InterfacePtr<IUIDData> toStoryUIDData(this, IID_IHIDTXTTOSTORYUIDDATA);
	if (toStoryUIDData != nil) {
		target = toStoryUIDData->GetRef().GetDataBase();
	}
	ASSERT(target != nil);
	if (target != nil) {
		this->SetTarget(target);
	}
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::SetUpTarget()-->Out target=0x%x\n", target);
}

/*
*/
void HidTxtModelCopyCmd::Do()
{
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::Do()-->In\n");
	ErrorCode status = kFailure;
	do {
		// Validate parameters.
		const UIDList& itemList = this->GetItemListReference();
		ASSERT(itemList.Length() == 1);
		if (itemList.Length() != 1) {
			break;
		}
		UIDRef fromHidTxtModelUIDRef = itemList.GetRef(0);
		this->SetItemList(UIDList(UIDRef(nil,kInvalidUID))); // clear the returned reference so if we fail the caller gets a bad UIDRef back
		InterfacePtr<IHidTxtModel> fromHidTxtModel(fromHidTxtModelUIDRef, UseDefaultIID());
		ASSERT(fromHidTxtModel != nil);
		if (fromHidTxtModel == nil) {
			break;
		}
		InterfacePtr<IUIDData> toStoryUIDData(this, IID_IHIDTXTTOSTORYUIDDATA);
		ASSERT(toStoryUIDData != nil);
		if (toStoryUIDData == nil) {
			break;
		}
		UIDRef toStoryUIDRef = toStoryUIDData->GetRef();
		InterfacePtr<ITextModel> toTextModel(toStoryUIDRef, UseDefaultIID());
		ASSERT(toTextModel != nil);
		if (toTextModel == nil) {
			break;
		}

		// Create a copy of the source object in the destination database.
		BeginEnd_XrefSession xRefSession(fromHidTxtModelUIDRef.GetDataBase(), toStoryUIDRef.GetDataBase());
		UID newHidTxtModelUID = Utils<IScrapUtils>()->CopyObject(fromHidTxtModelUIDRef, toStoryUIDRef.GetDataBase());
		ASSERT(newHidTxtModelUID.IsValid());
		if (newHidTxtModelUID.IsValid() == kFalse) {
			break;
		}

		// Initialise the copied object.
		UIDRef newHidTxtModelUIDRef(toStoryUIDRef.GetDataBase(), newHidTxtModelUID);
		InterfacePtr<IHidTxtModel> newHidTxtModel(newHidTxtModelUIDRef, UseDefaultIID());
		ASSERT(newHidTxtModel != nil);
		if (newHidTxtModel == nil) {
			break;
		}
		newHidTxtModel->SetConnectedToTextContent(kFalse);

		// Return reference to new copy of the object to the caller.
		this->SetItemList(UIDList(newHidTxtModelUIDRef));

		status = kSuccess;

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::Do()-->Out status=%d\n", status);
}

/*
*/
void HidTxtModelCopyCmd::DoNotify()
{
	TRACEFLOW("HiddenText", "HidTxtModelCopyCmd::DoNotify()-->In/Out\n");
}

/*
*/
PMString* HidTxtModelCopyCmd::CreateName()
{
	return new PMString(kHidTxtModelCopyCmdStringKey);
}

// End, HidTxtModelCopyCmd.cpp
