//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/AdobeOnlineID.h $
//  
//  Owner: Steve Flenniken
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

#ifndef __AdobeOnlineID__
#define __AdobeOnlineID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kAdobeOnlinePrefix	RezLong(0x8d00)	 

// <Start IDC>
#define kAdobeOnlinePluginName 			"Adobe Online"
DECLARE_PMID(kPlugInIDSpace, kAdobeOnlinePluginID, kAdobeOnlinePrefix + 1)

// <Class ID>
//DECLARE_PMID(kClassIDSpace, kAdobeOnlineScriptProviderBoss_obsolete, kAdobeOnlinePrefix + 1)
DECLARE_PMID(kClassIDSpace, kAdobeOnlineMenuBoss, kAdobeOnlinePrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kAdobeOnlineStartupShutdownBoss, kAdobeOnlinePrefix + 4)
DECLARE_PMID(kClassIDSpace, kRegisterUserCmdBoss, kAdobeOnlinePrefix + 5)

// <Implementation ID>
//DECLARE_PMID(kImplementationIDSpace, kAdobeOnlineScriptProviderImpl_obsolete, kAdobeOnlinePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAdobeOnlineMenu, kAdobeOnlinePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAdobeOnlineStringRegister, kAdobeOnlinePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kToolBarEventHandler, kAdobeOnlinePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAWEDispatch, kAdobeOnlinePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAdobeOnlineStartupShutdownImpl, kAdobeOnlinePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kRegisterUserCmdImpl, kAdobeOnlinePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kAdobeOnlineDynamicMenuImpl, kAdobeOnlinePrefix + 8)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kAdobeOnlineDialogActionID, kAdobeOnlinePrefix + 1)
DECLARE_PMID(kActionIDSpace, kAdobeOnlinePrefsActionID, kAdobeOnlinePrefix + 2)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineTopIssuesActionID, kAdobeOnlinePrefix + 3)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineDownloadablesActionID, kAdobeOnlinePrefix + 4)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineOnlineRegActionID, kAdobeOnlinePrefix + 5)
DECLARE_PMID(kActionIDSpace, kAdobeCorporateNewsActionID, kAdobeOnlinePrefix + 6)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineHelpSep1ActionID, kAdobeOnlinePrefix + 7)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineHelpSep2ActionID, kAdobeOnlinePrefix + 8)

DECLARE_PMID(kActionIDSpace, kFirstAdobeRecommendedLinkActionID, kAdobeOnlinePrefix + 11)
DECLARE_PMID(kActionIDSpace, kLastAdobeRecommendedLinkActionID, kAdobeOnlinePrefix + 80)
DECLARE_PMID(kActionIDSpace, kFirstInDesignRecommendedLinkActionID, kAdobeOnlinePrefix + 81)
DECLARE_PMID(kActionIDSpace, kLastInDesignRecommendedLinkActionID, kAdobeOnlinePrefix + 150)
DECLARE_PMID(kActionIDSpace, kAdobeOnlineHelpMenuDynamicActionID, kAdobeOnlinePrefix + 151)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IAWEDISPATCH, kAdobeOnlinePrefix + 1)

// <Ignore>
// Resources with LocaleIndex set.
#define kAdobeOnlineStringsRsrcID				1000
#define kAdobeOnlineStringsNoTransRsrcID		2000

// Resource IDs
#define kAdobeOnlineActionResID			3000 


#endif
// __AdobeOnlineID__
