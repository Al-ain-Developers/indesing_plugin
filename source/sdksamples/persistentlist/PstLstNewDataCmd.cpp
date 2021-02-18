//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstNewDataCmd.cpp $
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
#include "DebugClassUtils.h"

// Project includes
#include "PstLstID.h"
#include "IPstLstData.h"
#include "IPstLstUIDList.h"

/** 
	PstLstNewDataCmd will create a new IPstLstData object and add its UID to the IPstLstUIDList 
	of the page item of interest (the current selection from the popup menu).  Note the page item 
	to be added the new data object is passed in the fItemList; a data member fNewObjectList is 
	used to store the newly created IPstLstData objects' UIDs. 

	Note this implementation actually handles more than just one page item, although in this sample, 
	we only operate on one page item at a time, that is the selected item from the popup menu. so 
	the command's item list should have only one item. 
	
	PstLstNewDataCmd implements ICommand based on the partial implementation Command. 

	@ingroup persistentlist
	
*/
class PstLstNewDataCmd : public Command
{
	public:
		/**
			Constructor, we initialize all the private members and pass the boss pointer to 
			the parent class (Command).
		*/
		PstLstNewDataCmd(IPMUnknown* boss);

		/**
			Destructor
		*/
		virtual ~PstLstNewDataCmd();

		/**
			Don't execute this command if the memory is low.
		*/
		bool16 LowMemIsOK() const { return kFalse; }

	protected:
		/**
			The Do method is where we create a new IPstLstData in the page item's database, and add
			its UID to the IPstLstUIDList of the page item.  Since there may be multiple items selected,
			we have to repeat this process thru all the page items passed in the fItemList.
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
CREATE_PMINTERFACE(PstLstNewDataCmd, kPstLstNewDataCmdImpl)

/* PstLstNewDataCmd Constructor
*/
PstLstNewDataCmd::PstLstNewDataCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/* PstLstNewDataCmd Destructor
*/
PstLstNewDataCmd::~PstLstNewDataCmd()
{
}

/*	PstLstNewDataCmd::Do
*/
void PstLstNewDataCmd::Do()
{
	ErrorCode err = kSuccess;
	do
	{
		// Acquire command argument
		InterfacePtr<IPstLstData> iNewPstLstCmdData(this, UseDefaultIID());
		if (iNewPstLstCmdData == nil)
		{
			err = kFailure;
			ASSERT_FAIL("IPstLstData ptr nil, failed in Do");
			break;
		}

		// Get the database for this list of items. This is the database that will store
		// the new items too.
		IDataBase* iDatabase = fItemList.GetDataBase();

		// prepare a UIDList to return to the command client
		UIDList returnItemList(iDatabase);

		// Find out how many page items this command is going to act upon, we will create one new data object
		// for each page item.  In reality, there is only one page item passed to this command, which is the
		// current selection from the popup menu.  
		int32 numItems = fItemList.Length();
		
		// We have to loop thru all selected page items to add an data object to it.
		for (int32 i = 0; i < numItems; i++)
		{
			// storage for the newly created item
			UID newItem = kInvalidUID;
			// storage for the spline item on the item list
			UIDRef parentRef = fItemList.GetRef(i);

			// 1. Allocate a UID for the new data object (kPstLstDataBoss)
			if (err == kSuccess)
			{
				// need to create the new object in the database where the page item belongs
				if (iDatabase != nil)
				{
					newItem = iDatabase->NewUID(kPstLstDataBoss);
				}
				else
				{
					ASSERT_FAIL("PstLstNewDataCmd::Do() database is invalid");
					err = kFailure;
				}
			}

			// 2. Set the data (obtained thru command data) to the data object
			if (err == kSuccess)
			{
				// note the insert always append the new element in the last position
				InterfacePtr<IPstLstData> iPstLstData(iDatabase, newItem, UseDefaultIID());
				if (iPstLstData != nil) 
				{
					iPstLstData->SetName(iNewPstLstCmdData->GetName());
					iPstLstData->SetParent(parentRef.GetUID());
				}
				else
				{
					ASSERT_FAIL("PstLstNewDataCmd::Do() newItem does not have IPstLstData");
					err = kFailure;
				}
			}
			
			// 3. Update page item's object list (IPstLstUIDList) with the new object UID
			if (err == kSuccess)
			{
				InterfacePtr<IPstLstUIDList> iPstLstList(parentRef, UseDefaultIID());
				if (iPstLstList != nil)
				{
					// add the UID to page item's IPstLstUIDList
					iPstLstList->Append(newItem);
				}
				else
				{
					ASSERT_FAIL("PstLstNewDataCmd::Do() parent page item does not have IPstLstUIDList");
					err = kFailure;
				}
			}

			// 4. append the newly created item onto the item list to return
			if (newItem != kInvalidUID && err == kSuccess)
			{
				returnItemList.Append(newItem);
			}
		} // for (i = 0 ...)
		
		// setup the return item list
		if (err == kSuccess)
		{
			this->SetItemList(returnItemList);
		}
	} while (kFalse);
	//Handle errors
	if (err != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(err);
	}
}

/*	PstLstNewDataCmd::DoNotify
*/
void PstLstNewDataCmd::DoNotify()
{
	// For notification we'll let IPageItemUtils->NotifyDocumentObservers do the work.
	// Since this is the changed on the IPstLstData, we use its interface ID and the 
	// this command boss'd id as parameter to go into the Change() 
	Utils<IPageItemUtils>()->NotifyDocumentObservers
	(
		fItemList.GetDataBase(), 
		kPstLstNewDataCmdBoss, 
		IPstLstData::kDefaultIID, 
		this
	);
}

/* PstLstModifyDataCmd CreateName
*/
PMString* PstLstNewDataCmd::CreateName()
{
	PMString* str = new PMString(kPstLstNewStringKey);
	return str;
}
	
// End, PstLstNewDataCmd.cpp.


