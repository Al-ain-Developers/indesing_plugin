//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDeleteDataCmd.cpp $
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
	PstLstDeleteDataCmd will delete the selected IPstLstData object and remove its UID 
	from the IPstLstUIDList from the page item that is of interest to the user.  Note this 
	implementation actually handles more than just one page item. 
	
	PstLstDeleteDataCmd implements ICommand based on the partial implementation Command. 
	
	@ingroup persistentlist
	
*/
class PstLstDeleteDataCmd : public Command
{
	public:
		/**
			Constructor, we initialize all the private members and pass the boss pointer to 
			the parent class (Command).
		*/
		PstLstDeleteDataCmd(IPMUnknown* boss);

		/**
			Destructor
		*/
		virtual ~PstLstDeleteDataCmd();

		/**
			Don't execute this command if the memory is low.
		*/
		bool16 LowMemIsOK() const { return kFalse; }

	protected:
		/**
			Loop thru all the PstLst data items, delete the selected kPstLstDataBoss UID 
			from the database, also remove its corresponding entry in the IPstLstUIDList of 
			the item.
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
CREATE_PMINTERFACE(PstLstDeleteDataCmd, kPstLstDeleteDataCmdImpl)

/*	PstLstDeleteDataCmd Constructor
*/
PstLstDeleteDataCmd::PstLstDeleteDataCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/*	PstLstDeleteDataCmd Destructor
*/
PstLstDeleteDataCmd::~PstLstDeleteDataCmd()
{
}

/*	PstLstDeleteDataCmd::Do
*/
void PstLstDeleteDataCmd::Do()
{
	ErrorCode err = kSuccess;

	// Find out how many page items this command is going to act upon, we will delete each page item's
	// selected data object. 
	int32	items = fItemList.Length();
	IDataBase *db = fItemList.GetDataBase();

	// We have to loop thru all selected page items to delete its IPstLstData.
	for (int32 i = 0; i < items; i++)
	{
		UID uid = fItemList.At(i);
		if (uid != kInvalidUID)
		{
			InterfacePtr<IPstLstData> iPstLstData(db, uid, UseDefaultIID());
			UID parentUID = iPstLstData->GetParent();
			InterfacePtr<IPstLstUIDList> iPstLstList(db, parentUID, UseDefaultIID());
			if (iPstLstList != nil)
			{
				iPstLstList->Remove(uid);
				db->DeleteUID(uid);
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

/*	PstLstDeleteDataCmd::DoNotify
*/
void PstLstDeleteDataCmd::DoNotify()
{
	// For notfication we'll let IPageItemUtils->NotifyDocumentObservers do the work.
	// Since this is the changed on the IPstLstData, we use its interface ID and the 
	// this command boss'd id as parameter to go into the Change() 
	Utils<IPageItemUtils>()->NotifyDocumentObservers
	(
		fItemList.GetDataBase(), 
		kPstLstDeleteDataCmdBoss, 
		IPstLstData::kDefaultIID, 
		this
	);
}

/*	PstLstDeleteDataCmd::CreateName
*/
PMString* PstLstDeleteDataCmd::CreateName()
{
	PMString* str = new PMString(kPstLstDeleteStringKey);
	return str;
}
	
// End, PstLstDeleteDataCmd.cpp.


