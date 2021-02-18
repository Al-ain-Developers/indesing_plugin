//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDeletePageItemCmd.cpp $
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

// Interface includes
#include "IUIDData.h"
#include "IDocument.h"
#include "ISubject.h"

// API includes
#include "ErrorUtils.h"
#include "IPageItemUtils.h"	 
#include "Command.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes
#include "PstLstID.h"
#include "IPstLstData.h"
#include "IPstLstUIDList.h"

/** 

	This command is similar to PstLstDeleteDataCmd, but it is used when a page item is
	deleted, we need to delete ALL the data boss we added to the item, also we need to 
	restore them in the event of undo deleting page item.  So unlike PstLstDeleteDataCmd,
	which only deletes the current selected UID and its associated data boss for each
	selected page item, this command delete EVERY one that's carried by a page item.
	
	PstLstDeletePageItemCmd implements ICommand based on the partial implementation Command. 
	
	@ingroup persistentlist
	
*/
class PstLstDeletePageItemCmd : public Command
{
	public:
		/**
			Constructor, we initialize all the private members and pass the boss pointer to 
			the parent class (Command).
		*/
		PstLstDeletePageItemCmd(IPMUnknown* boss);

		/**
			Destructor
		*/
		~PstLstDeletePageItemCmd();

		/**
			Don't execute this command if the memory is low.
		*/
		bool16 LowMemIsOK() const { return kFalse; }

	protected:
		/**
			Loop thru all the selected page items, delete all items' kPstLstDataBoss UID from 
			the database, also remove all corresponding entries in the IPstLstUIDList of the 
			item.
		*/
		void Do();

		/**
			Notify all the document observers that a change to the page item's IPstLstData
			has happened.
		*/
		void DoNotify();

		/**
			Gives the name that shows up under the Edit menu and allows the user to undo or redo the command.

			@return pointer to a PMString allocated using the new operator. Deleted by caller.
		*/
		PMString* CreateName();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstDeletePageItemCmd, kPstLstDeletePageItemCmdImpl)

/*	PstLstDeletePageItemCmd::Constructor
*/
PstLstDeletePageItemCmd::PstLstDeletePageItemCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/*	PstLstDeletePageItemCmd::Destructor
*/
PstLstDeletePageItemCmd::~PstLstDeletePageItemCmd()
{
}

/*	PstLstDeletePageItemCmd::Do
*/
void PstLstDeletePageItemCmd::Do()
{
	ErrorCode err = kSuccess;

	int32	items = fItemList.Length();
	
	// We have to loop thru all selected page items to delete all IPstLstData stored in its IPstLstUIDList.
	for (int32 i = 0; i < items; i++)
	{
		InterfacePtr<IPstLstUIDList> iPstLstList(fItemList.GetRef(i), UseDefaultIID());
		if (iPstLstList != nil)
		{
			// remove EVERY UID from the IPstLstUIDList, also from the database
			const UIDList* pstLstDataItems = iPstLstList->GetUIDList();
			for (int32 k = 0; k < pstLstDataItems->Length(); k++)
			{
				UID uid = (*pstLstDataItems)[k];
				iPstLstList->Remove(uid);
				fItemList.GetDataBase()->DeleteUID(uid);
			}
		}
		else
			err = kFailure;
	}	
	
	//Handle errors
	if (err != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(err);
	}
}


/*	PstLstDeletePageItemCmd::DoNotify
*/
void PstLstDeletePageItemCmd::DoNotify()
{
	// For notification we'll let IPageItemUtils->NotifyDocumentObservers do the work.
	// Since this is the changed on the IPstLstData, we use its interface ID and the 
	// this command boss'd id as parameter to go into the Change() 
	Utils<IPageItemUtils>()->NotifyDocumentObservers
	(
		fItemList.GetDataBase(), 
		kPstLstDeletePageItemCmdBoss, 
		IPstLstData::kDefaultIID, 
		this
	);
}

/*	PstLstDeletePageItemCmd::CreateName
*/
PMString* PstLstDeletePageItemCmd::CreateName()
{
	PMString* str = new PMString(kPstLstDeleteStringKey);
	return str;
}
	
// End, PstLstDeletePageItemCmd.cpp.


