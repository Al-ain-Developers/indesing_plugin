//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISetDataCmd.cpp $
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
#include "IPageItemUtils.h"	 
#include "ISubject.h"
#include "IWorkspace.h"
#include "IHierarchy.h"

// General includes
#include "ErrorUtils.h"
#include "Utils.h"
#include "Command.h"

// Project includes
#include "BPIID.h"
#include "IBPIData.h"

/** Implements a command, ICommand based on Command, that changes the value
	of IBPIData in the objects given by the command's item list.

	The command targets the database and objects passed in 
	the command's item list. Each object referenced should have an IBPIData
	interface and the value stored there is changed. The new value to be set
	is passed via the sibling IBPIData interface on kBPISetDataCmdBoss. Note
	that the implementation used to pass the IBPIData parameter value to the
	command is not persistent. The implementation used to store the IBPIData
	value on the targeted objects is persistent.

	The command takes care of the need to make the change undoable by saving
	the current IBPIDtaa value of the objects to be changed so that these
	values can be resorted if Undo is called.

	@ingroup basicpersistinterface
	
*/
class BPISetDataCmd : public Command
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISetDataCmd(IPMUnknown* boss);

	/**
		Destructor.
	*/
	~BPISetDataCmd();

	/**
		@return kFalse don't use this command if memory is low. 
	*/
	bool16 LowMemIsOK() const { return kFalse; }

protected:
	/**
		The Do method is where all the action happens. In this case we just need to copy the 
		information from this command's IBPIData data interface to the IBPIData interface 
		on the objects targeted by the command's fItemList taking care to first preserve
		their original value should Undo be required.
	*/
	void Do();

	/**
		Notify observers about the change made by this command. Notification
		is done either on the document's subject (changes to page item's IBPIData)
		or on the workspace's subject (changes to default IBPIData).
		The first item in the command's fItemList is used to decide the
		type of notification is needed. See the implementation for the details.
	*/
	void DoNotify();

	/**
		Gives the name that shows up under the Edit menu and allows the user to undo or redo the command.

		@return pointer to a PMString allocated using the new operator. Deleted by caller.
	*/
	PMString* CreateName();

private:
	/**
		Change the value of the IBPIData of the objects targeted by the command.
	 */
	void SetBPIData();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BPISetDataCmd, kBPISetDataCmdImpl)

/* Constructor
*/
BPISetDataCmd::BPISetDataCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/* Destructor
*/
BPISetDataCmd::~BPISetDataCmd()
{
}

/*
*/
void BPISetDataCmd::Do()
{
	ErrorCode status = kFailure;
	do {
		// Validate command parameters.
		if (fItemList.Length() <= 0) {
			ASSERT_FAIL("empty item list");
			break;
		}
		InterfacePtr<IBPIData> cmdBPIData(this, UseDefaultIID());
		ASSERT(cmdBPIData);
		if (!cmdBPIData) {
			break;
		}
	
		// Change the BPIData attribute to the new value.
		this->SetBPIData();
		
		// We're done.
		status = kSuccess;
	} while(false);
	
	if (status != kSuccess) {
		ErrorUtils::PMSetGlobalErrorCode(status);
	}
}

/*
*/
void BPISetDataCmd::SetBPIData()
{
	// The value to be applied is passed
	// via a data interface on the command.
	InterfacePtr<IBPIData> cmdBPIData(this, UseDefaultIID());
	if (cmdBPIData) {
		// Copy the new value into all targeted objects.
		for(int32 itemCount = 0; itemCount <  fItemList.Length(); itemCount++) {
			InterfacePtr<IBPIData> bpiData(fItemList.GetRef(itemCount), UseDefaultIID());
			if(bpiData) {
				bpiData->Set
				(
					cmdBPIData->Get() 
				);
			}	
		}
	}
}

/*
*/
void BPISetDataCmd::DoNotify()
{
	if ( fItemList.Length() > 0) {
		// Use the first object in the command's item list to
		// decide where we need to broadcast notification of
		// this change.
		UIDRef objectRef = fItemList.GetRef(0);
		InterfacePtr<IBPIData> bpiData(objectRef, UseDefaultIID());
		InterfacePtr<IWorkspace> workspace(bpiData, UseDefaultIID());
		if (workspace) {
			// Notify change to default IBPIData through the workspace's subject.
			InterfacePtr<ISubject> subject(workspace, UseDefaultIID());
			ASSERT(subject);
			if (subject) {
				subject->ModelChange(kBPISetDataCmdBoss, IBPIData::kDefaultIID, this);
			}
			// The defaults selection boss classes
			// observe the workspace subject so in order for this plug-ins
			// selection extension to be called
			// (BPISuiteCSB::SelectionAttributeChanged)  
			// we must notify via the workspace subject when 
			// defaults change.
		}
		InterfacePtr<IHierarchy> hierarchy(bpiData, UseDefaultIID());	
		if (hierarchy) {
			// Notify change to page item IBPIData through the document's subject.
			Utils<IPageItemUtils> pageItemUtils;
			ASSERT(pageItemUtils);
			if (pageItemUtils) {
				pageItemUtils->NotifyDocumentObservers(fItemList.GetDataBase(), 
					kBPISetDataCmdBoss, 
					IBPIData::kDefaultIID, 
					this
				);
			}
			// The layout and text CSB's observe the document's subject so in order
			// for this plug-in's BPISuite::SelectionAttributeChanged
			// selection extension to be called we notify through
			// the document's subject.
		}
	}
}

/*
*/
PMString* BPISetDataCmd::CreateName()
{
	PMString* string_name = new PMString(kBPICommandStringKey);
	return string_name;
}
	
// End, BPISetDataCmd.cpp.




