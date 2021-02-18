//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndChangeEntityMappingCmd.cpp $
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
#include "IXCatHndEntityMapping.h"

// General includes:
#include "CmdUtils.h"
#include "Command.h"
#include "ErrorUtils.h"

// Project includes
#include "XCatHndID.h"

/** Implementation of command to change entity map (IXCatHndEntityMapping) 
	stored in a workspace (IWorkspace).

	@ingroup xmlcataloghandler
	@see IXCatHndEntityMapping
*/
class XCatHndChangeEntityMappingCmd : public Command
{
public:
	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.*/
	XCatHndChangeEntityMappingCmd(IPMUnknown* boss);
	
protected:
	/** @see Command::Do
	 */
	virtual void Do();

	/** @see Command::CreateName
	 */
	virtual PMString* CreateName();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XCatHndChangeEntityMappingCmd, kXCatHndChangeEntityMappingCmdImpl)

/* 
*/
XCatHndChangeEntityMappingCmd::XCatHndChangeEntityMappingCmd(IPMUnknown* boss) : Command(boss)	
{
	this->SetUndoability(kAutoUndo);
}

/* 
*/
void XCatHndChangeEntityMappingCmd::Do()
{
	ErrorCode retval = kFailure;
	do
	{
		const UIDList* itemList= this->GetItemList();
		ASSERT(itemList);
		
		InterfacePtr<IXCatHndEntityMapping> inboundEntityMapping(this, UseDefaultIID());
		ASSERT(inboundEntityMapping);
		if (!inboundEntityMapping) {
			break;
		}

		UIDRef uidRef = itemList->GetRef(0);
		InterfacePtr<IXCatHndEntityMapping> targetEntityMapping(uidRef, UseDefaultIID());
		ASSERT(targetEntityMapping);
		if (!targetEntityMapping) {
			break;
		}
		targetEntityMapping->Copy(inboundEntityMapping);	
		retval = kSuccess;

	} while (kFalse);

	if (retval != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
	}
}

/* 
*/
PMString* XCatHndChangeEntityMappingCmd::CreateName()
{
	return new PMString(kXCatHndChangeEntityMappingKey);
}


// End, XCatHndChangeEntityMappingCmd.cpp.
