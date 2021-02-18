//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/HelpID.h $
//  
//  Owner: Tom Taylor
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
//  
//  Contains common IDs used by the Help plugin.
//  
//========================================================================================

#ifndef __HelpID__
#define __HelpID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kHelpPrefix	RezLong(0x9700)

// <Start IDC>
// PluginID
#define kHelpPluginName 				"Help"
DECLARE_PMID(kPlugInIDSpace, kHelpPluginID, kHelpPrefix + 1)

// <Class ID>
// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kHelpMenuComponentBoss, kHelpPrefix + 2 )
DECLARE_PMID(kClassIDSpace, kHelpLibraryStartupShutdownBoss, kHelpPrefix + 3 )

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kHelpStringRegisterImpl, kHelpPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHelpMenuComponentImpl, kHelpPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kHelpLibraryStartupShutdownImpl, kHelpPrefix + 3 )

//gap
DECLARE_PMID(kImplementationIDSpace, kHelpUtilsImpl, kHelpPrefix + 4 )

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IHELPUTILS, kHelpPrefix + 1)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kHelpContentsActionID, kHelpPrefix + 1)
DECLARE_PMID(kActionIDSpace, kHelpSepActionID, kHelpPrefix + 2)
DECLARE_PMID(kActionIDSpace, kHelpOnlineSupportActionID, kHelpPrefix + 3)
DECLARE_PMID(kActionIDSpace, kHelpUserVoiceActionID, kHelpPrefix + 4)
DECLARE_PMID(kActionIDSpace, kHelpInDesignForumActionID, kHelpPrefix + 5)

#endif // __HelpID__
