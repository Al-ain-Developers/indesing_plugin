//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexportui/InCopyExportUIID.h $
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

#ifndef __InCopyExportUIID__
#define __InCopyExportUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyExportUIPrefix	 RezLong(0x17300)		// Reserved in "AdobePrefix.h"

// <PlugInID>
#define kInCopyExportUIPluginName 			"InCopyExportUI"
DECLARE_PMID(kPlugInIDSpace, kInCopyExportUIPluginID, kInCopyExportUIPrefix + 1)

// <Class ID>
//gap
DECLARE_PMID(kClassIDSpace, kInCopyExportMenuComponentBoss, kInCopyExportUIPrefix + 2 )

// <Implementation ID>
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyExportMenuComponentImpl, kInCopyExportUIPrefix + 2 )

// <Action ID>
DECLARE_PMID(kActionIDSpace, kExportLayerToICActionID, kInCopyExportUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kLayerPanelSep6ActionID, kInCopyExportUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kExportAllStoriesToICActionID, kInCopyExportUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kICBridgeSeperatorID, kInCopyExportUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kExportAllGraphicsToICActionID, kInCopyExportUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kExportAllItemsToICActionID, kInCopyExportUIPrefix + 6)


#define kInCopyExportMenuResID					1600
#define kInCopyExportActionResID				1700

#endif
