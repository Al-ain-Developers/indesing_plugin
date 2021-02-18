//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtTagChangeCmd.cpp $
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
#include "Command.h"

// Interface includes:
#include "IBoolData.h"
#include "IPageItemUtils.h"
#include "IWorkspace.h"
#include "ISubject.h"
#include "IObjectStylesUtils.h"

// General includes:
#include "PersistUIDList.h"
#include "PMString.h"
#include "ListLazyNotificationData.h"

// Project includes:
#include "CusCondTxtID.h"
#include "ICustomConditionTag.h"

class CusCondTxtTagChangeCmd : public Command
{
public:
	CusCondTxtTagChangeCmd(IPMUnknown* boss);
	~CusCondTxtTagChangeCmd();

protected:
	virtual void Do();
	virtual void DoNotify();
	virtual PMString* CreateName();

private:
};


CREATE_PMINTERFACE(CusCondTxtTagChangeCmd, kCusCondTxtTagChangeCmdImpl)

/* CusCondTxtTagChangeCmd Constructor
*/
CusCondTxtTagChangeCmd::CusCondTxtTagChangeCmd(IPMUnknown* boss): 
	Command(boss)
{
} // end constructor

/* CusCondTxtTagChangeCmd Constructor
*/
CusCondTxtTagChangeCmd::~CusCondTxtTagChangeCmd()
{
} // end destructor


/* Do
*/
void CusCondTxtTagChangeCmd::Do()
{
	InterfacePtr<ICustomConditionTag> cusConditionTag(fItemList.GetRef(0), UseDefaultIID());
	if(cusConditionTag)
	{			
		InterfacePtr<IBoolData> iPrintVisible(this, IID_ICUSCONDTXTPRINTVISIBLE);
		ASSERT_MSG(iPrintVisible, "CusCondTxtTagChangeCmd::Do, the iPrintVisible is nil");

		InterfacePtr<IBoolData> iIdmlVisible(this, IID_ICUSCONDTXTIDMLVISIBLE);
		ASSERT_MSG(iIdmlVisible, "CusCondTxtTagChangeCmd::Do, the iIdmlVisible is nil");
		
		if(cusConditionTag->IsPrintVisible() != iPrintVisible->Get())
			cusConditionTag->SetPrintVisible(iPrintVisible->Get());
			
		if(cusConditionTag->IsIdmlVisible() != iIdmlVisible->Get())
			cusConditionTag->SetIdmlVisible(iIdmlVisible->Get());
	}
} // end Do()

/* DoNotify
*/
void CusCondTxtTagChangeCmd::DoNotify()
{
	InterfacePtr<IWorkspace> workspace(Utils<IObjectStylesUtils>()->QueryWorkspaceFromDataBase(this->GetItemList()->GetDataBase()));
	InterfacePtr<ISubject> subject(workspace, IID_ISUBJECT);
	if (subject)
	{
		ListLazyNotificationData<UID> *tagCookie = new ListLazyNotificationData<UID>;
		tagCookie->ItemChanged(fItemList.GetRef(0).GetUID());
		subject->ModelChange(kCusCondTxtChangeCmdBoss, IID_ICUSTOMCONDITIONTAG, this, tagCookie);
	}
}

/* CreateName
*/
PMString* CusCondTxtTagChangeCmd::CreateName()
{
	return new PMString(kCusCondTxtCommandStringKey);
} // end CreateName()
