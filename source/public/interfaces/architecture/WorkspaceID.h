//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/WorkspaceID.h $
//  
//  Owner: Lonnie Millett
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

#ifndef __WORKSPACEIIDS__
#define __WORKSPACEIIDS__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kWorkspacePrefix	  RezLong(0x2200)  

// <Start IDC>
// <Class ID>
DECLARE_PMID(kClassIDSpace, kWorkspaceBoss, kWorkspacePrefix + 1)
DECLARE_PMID(kClassIDSpace, kDocWorkspaceBoss, kWorkspacePrefix + 2)
DECLARE_PMID(kClassIDSpace, kStringDataBaseTableBoss, kWorkspacePrefix + 3)
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kChangeLocaleCmdBoss, kWorkspacePrefix + 4)
#endif
DECLARE_PMID(kClassIDSpace, kAboutToChangeLocaleMsgBoss, kWorkspacePrefix + 5)
DECLARE_PMID(kClassIDSpace, kNewWorkspaceSignalMgrBoss, kWorkspacePrefix + 6)
DECLARE_PMID(kClassIDSpace, kNewWorkspaceCmdBoss, kWorkspacePrefix + 7)
DECLARE_PMID(kClassIDSpace, kPanelInitializerBoss, kWorkspacePrefix + 8)
DECLARE_PMID(kClassIDSpace, kKitInitializerBoss, kWorkspacePrefix + 9)
DECLARE_PMID(kClassIDSpace, kReverseStringDataBaseTableBoss, kWorkspacePrefix + 10)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IWORKSPACE, kWorkspacePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTSFILESTARTUPDATA, kWorkspacePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACECOLORS, kWorkspacePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCALESETTING, kWorkspacePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVERSESTRINGDATABASE, kWorkspacePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGDATABASE, kWorkspacePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGDATABASETABLE, kWorkspacePrefix + 7)
#ifdef ID_DEPRECATED
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGELOCALECMDDATA, kWorkspacePrefix + 8)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_INEWWORKSPACEACTION, kWorkspacePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCALECHECKER, kWorkspacePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPALETTEMGRSERVICE, kWorkspacePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWWORKSPACESIGNALDATA, kWorkspacePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEAPPEARANCEPREFS, kWorkspacePrefix + 13)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kWorkspaceImpl, kWorkspacePrefix + 1	)
DECLARE_PMID(kImplementationIDSpace, kDefaultsFileStartupDataImpl, kWorkspacePrefix + 2)
// gap
DECLARE_PMID(kImplementationIDSpace, kLocaleSettingImpl, kWorkspacePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kReverseStringDataBaseImpl, kWorkspacePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kStringDataBaseImpl, kWorkspacePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStringDataBaseTableImpl, kWorkspacePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kChangeLocaleCmdImpl, kWorkspacePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kChangeLocaleCmdDataImpl, kWorkspacePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kChangeFeatureSetCmdImpl, kWorkspacePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kReverseStringDataBaseTableImpl, kWorkspacePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kNewWorkspaceSigRespServiceImpl, kWorkspacePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kNewWorkspaceCmdImpl, kWorkspacePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNewWorkspaceSignalDataImpl, kWorkspacePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPanelInitializerImpl, kWorkspacePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kKitInitializerImpl, kWorkspacePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kStringDataBaseProxyImpl, kWorkspacePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kReverseStringDataBaseProxyImpl, kWorkspacePrefix + 18)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kNewWorkspaceSignalResponderService, kWorkspacePrefix + 1)
DECLARE_PMID(kServiceIDSpace, kPaletteMgrService, kWorkspacePrefix + 2)
#endif 








