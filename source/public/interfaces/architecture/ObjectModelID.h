//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ObjectModelID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __ObjectModelID__
#define __ObjectModelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kObjectModelPrefix	 RezLong(0x16000)		// see AdobePrefix.h


// PluginID
#define kObjectModelPluginName 		"ObjectModel"
DECLARE_PMID(kPlugInIDSpace, kObjectModelPluginID, kObjectModelPrefix + 1)


/*
	BP 03/26/01: TODO: Some of InDesign's bosses and implementations will be moved to the ObjectModelPlugin plug-in:
	kSessionBoss, kCommandProcessorBoss, kCmdProcStackCmdCollectorBoss, kWorkspaceBoss, kServiceMgrBoss,
	kNewWorkspaceSignalMgrBoss, kDBStreamWriteBoss, kDBStreamReadBoss, kResourceStreamReadBoss,
	kObjectResourceStreamReadBoss, kObjectTextFileStreamWriteBoss, kShutdownNotificationServiceBoss,
	kTagRegistryBoss, kNewWorkspaceCmdBoss.	

	Those bosses are currently in the kShuksanPrefix id space. They need to be mapped to kObjectModelPrefix ids and
	declared via MoveClass BossDirectives.
*/


// <Class ID>
// ClassIDs

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IHIGHLEVELAPIPLUGINMGR,		kObjectModelPrefix + 100)

// <Widget ID>

// <Implementation ID>
// ImplementationIDs

DECLARE_PMID(kImplementationIDSpace,	kHighLevelAPIPluginMgrImpl,			kObjectModelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kPlugInListUtilsProxyImpl, kObjectModelPrefix + 104)

// <Message ID>


// <Service ID>

// Service IDs

// <Error ID>
// Error Codes
// NOTE:  The offset is used to find the corresponding error string
// Look in ApplStrings.fr for the string definitions.

// <Ignore>


// <Global ID>
// ActionIDs


#endif //__ShuskanID__







