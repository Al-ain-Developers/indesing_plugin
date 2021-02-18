//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkChangeServiceXMLImportPrefsCmd.cpp $
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
#include "IBoolData.h"
#include "IClassIDData.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IWorkspace.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"

// General includes:
#include "CmdUtils.h"
#include "Command.h"
#include "ErrorUtils.h"
// Project includes
#include "XDocBkID.h"

/** Implementation of command to change the preferences persisted 
	to the session workspace through our IXDocBkOptions interface.
	@ingroup xdocbookworkflow
*/
class XDocBkChangeServiceXMLImportPrefsCmd : public Command
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.*/
	XDocBkChangeServiceXMLImportPrefsCmd(IPMUnknown* boss);

protected:
	
	/** 
	 	@see Command::Do
	*/
	virtual void Do();
	
	/** 
	 	@see Command::CreateName
	*/
	virtual PMString* CreateName();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XDocBkChangeServiceXMLImportPrefsCmd, kXDocBkChangeServiceXMLImportPrefsCmdImpl)

/* Constructor
*/
XDocBkChangeServiceXMLImportPrefsCmd::XDocBkChangeServiceXMLImportPrefsCmd(IPMUnknown* boss) : 
	Command(boss)
{
}

/* Do
*/
void XDocBkChangeServiceXMLImportPrefsCmd::Do()
{
	ErrorCode status = kFailure;
	do                      
	{
		const UIDList* itemList= this->GetItemList();
		ASSERT(itemList);
		if(!itemList) {
			break;
		}
		
		//Itemlist has the workspace of interest
		UIDRef workspaceUIDRef = itemList->GetRef(0);
		InterfacePtr<IWorkspace> workspace(workspaceUIDRef, UseDefaultIID());
		ASSERT(workspace);
		if(!workspace) {
			break;
		}

		InterfacePtr<IClassIDData> classIDData(this, UseDefaultIID());
		ASSERT(classIDData);
		if(!classIDData) {
			break;
		}
		ClassID classID = classIDData->GetClassID();

		InterfacePtr<IIntData> serviceIDData(this, IID_IXDOCBKSERVICEIDINTDATA);
		ASSERT(serviceIDData);
		if(!serviceIDData) {
			break;
		}
		ServiceID serviceID = serviceIDData->Get();

		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		if (!serviceRegistry) {
			break;
		}
		InterfacePtr<IK2ServiceProvider> serviceProvider(
			serviceRegistry->QueryServiceProviderByClassID(serviceID, 
				classID));
		ASSERT(serviceProvider);
		if (!serviceProvider) {
			break;
		}

		InterfacePtr<IXMLImportPreferences> targetXMLImportPrefs(serviceProvider, UseDefaultIID());
		ASSERT(targetXMLImportPrefs);
		if(!targetXMLImportPrefs) {
			break;
		}
		InterfacePtr<IBoolData> boolData(this, UseDefaultIID());
		ASSERT(boolData);
		if(!boolData) {
			break;
		}
		InterfacePtr<IIntData> intData(this, UseDefaultIID());
		ASSERT(intData);
		if(!intData) {
			break;
		}
		int32 nPref = intData->Get();
		InterfacePtr<IXMLImportOptionsPool> prefsPool(workspaceUIDRef, UseDefaultIID());
		ASSERT(prefsPool);
		if(!prefsPool) {
			break;
		}
	
		XMLImportPreferencesInitializer initializer(targetXMLImportPrefs, prefsPool);
		targetXMLImportPrefs->SetNthPref(nPref,boolData->Get());
		targetXMLImportPrefs->CommitChanges();
		status = kSuccess;

	} while (kFalse);       

	// Handle any errors
	if (status != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(status);
	}
}

/* CreateName
*/
PMString* XDocBkChangeServiceXMLImportPrefsCmd::CreateName()
{
	return new PMString(kXDocBkChangeServiceXMLImportPrefsCmdKey);
}

// End, XDocBkChangeServiceXMLImportPrefsCmd.cpp.


