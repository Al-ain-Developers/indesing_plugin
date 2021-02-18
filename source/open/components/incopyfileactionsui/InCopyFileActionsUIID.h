//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactionsui/InCopyFileActionsUIID.h $
//  
//  Owner: Chris Parrish
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

#ifndef __InCopyFileActionsUIID__
#define __InCopyFileActionsUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyFileActionsUIPrefix			RezLong(0x21300)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kInCopyFileActionsUIPluginName 	"InCopyFileActionsUI"
DECLARE_PMID(kPlugInIDSpace, kInCopyFileActionsUIPluginID, kInCopyFileActionsUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,		kInCopyFileActionsComponentBoss,		kInCopyFileActionsUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kInCopyMRUListBoss,						kInCopyFileActionsUIPrefix + 13)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace,		kInCopyFileActionsComponentImpl,	kInCopyFileActionsUIPrefix + 1)

DECLARE_PMID(kImplementationIDSpace,		kInCopyRecentDocsDynamicMenuImpl,	kInCopyFileActionsUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,		kInCopyRecentDocsComponentImpl,		kInCopyFileActionsUIPrefix + 13)


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,		kUpdateDesignActionID,		kInCopyFileActionsUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,		kSaveOldActionID,			kInCopyFileActionsUIPrefix + 2)

#endif // __InCopyFileActionsUIID__
