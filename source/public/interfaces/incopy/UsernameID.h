//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/UsernameID.h $
//  
//  Owner: Jon Pugh
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

#ifndef __USERNAMEID__
#define __USERNAMEID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kUsernamePrefix	 RezLong(0x18300)	// reserved in AdobePrefix.h


//---------------------------------------------------------------
// <PlugInID>
//---------------------------------------------------------------
#define kUsernamePlugInName					"Username"
DECLARE_PMID(kPlugInIDSpace,			kUsernamePlugInID,					kUsernamePrefix + 1)

//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace,				kUsernameComponentBoss,				kUsernamePrefix + 2)
DECLARE_PMID(kClassIDSpace,				kOpenUsernameDialogCmdBoss,			kUsernamePrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace,				kInCopyUserDialogBoss,				kUsernamePrefix + 5)

//---------------------------------------------------------------
// <Interface ID>
//---------------------------------------------------------------

//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace,	kUsernameComponentImpl,				kUsernamePrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kInCopyUserDlgControllerImpl,		kUsernamePrefix + 2)
// gap
DECLARE_PMID(kImplementationIDSpace,	kOpenUsernameDialogCmdImpl,			kUsernamePrefix + 4)

//---------------------------------------------------------------
// <Action ID>
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace,			kUserActionID,						kUsernamePrefix + 1)
DECLARE_PMID(kActionIDSpace,			kUserSepActionID,					kUsernamePrefix + 2)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace,			kInCopyUserDialogId,				kUsernamePrefix + 1)
DECLARE_PMID(kWidgetIDSpace,			kInCopyUserNameStaticWidgetID,		kUsernamePrefix + 2)
DECLARE_PMID(kWidgetIDSpace,			kInCopyUserNameWidgetID,			kUsernamePrefix + 3)
DECLARE_PMID(kWidgetIDSpace,			kInCopyUserNameTextWidgetID,		kUsernamePrefix + 4)
DECLARE_PMID(kWidgetIDSpace,			kUserColorStaticWidgetId,			kUsernamePrefix + 5)
DECLARE_PMID(kWidgetIDSpace,			kUserColorDropDownWidgetId,			kUsernamePrefix + 6)
DECLARE_PMID(kWidgetIDSpace,			kUserNameRequiredWidgetId,			kUsernamePrefix + 7)


//Script identifiers
DECLARE_PMID(kScriptInfoIDSpace,		kUserNamePropertyScriptElement,		kUsernamePrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace,		kUserColorPropertyScriptElement,	kUsernamePrefix + 21)

#endif // __USERNAMEID__



