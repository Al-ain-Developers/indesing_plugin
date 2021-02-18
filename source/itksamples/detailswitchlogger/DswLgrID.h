//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/detailswitchlogger/DswLgrID.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __DswLgrID_h__
#define __DswLgrID_h__

#include "SDKDef.h"

// Company:
#define kDswLgrCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDswLgrCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDswLgrPluginName	"DetailSwitchLogger"			// Name of this plug-in.
#define kDswLgrPrefixNumber	0xAE900 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDswLgrVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kDswLgrAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDswLgrPrefixNumber above to modify the prefix.)
#define kDswLgrPrefix		RezLong(kDswLgrPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDswLgrStringPrefix	SDK_DEF_STRINGIZE(kDswLgrPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDswLgrPluginID, kDswLgrPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDswLgrActionComponentBoss, kDswLgrPrefix + 0)
DECLARE_PMID(kClassIDSpace, kDswLgrDiagLogModifierBoss, kDswLgrPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kDswLgrBoss, kDswLgrPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDSWLGRINTERFACE, kDswLgrPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDswLgrActionComponentImpl, kDswLgrPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kDswLgrDiagLogModifierImpl, kDswLgrPrefix +1 )
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kDswLgrImpl, kDswLgrPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDswLgrAboutActionID, kDswLgrPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kDswLgrActionID, kDswLgrPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kDswLgrWidgetID, kDswLgrPrefix + 25)


// "About Plug-ins" sub-menu:
#define kDswLgrAboutMenuKey			kDswLgrStringPrefix "kDswLgrAboutMenuKey"
#define kDswLgrAboutMenuPath			kSDKDefStandardAboutMenuPath kDswLgrCompanyKey

// "Plug-ins" sub-menu:
#define kDswLgrPluginsMenuKey 		kDswLgrStringPrefix "kDswLgrPluginsMenuKey"
#define kDswLgrPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kDswLgrCompanyKey kSDKDefDelimitMenuPath kDswLgrPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kDswLgrAboutBoxStringKey				kDswLgrStringPrefix "kDswLgrAboutBoxStringKey"
#define kDswLgrTargetMenuPath kDswLgrPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kDswLgrFirstMajorFormatNumber  RezLong(1)
#define kDswLgrFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kDswLgrCurrentMajorFormatNumber kDswLgrFirstMajorFormatNumber
#define kDswLgrCurrentMinorFormatNumber kDswLgrFirstMinorFormatNumber

// some pre-defined string used for comparison
#define kDswLgrActionContext		"Action"
#define kDswLgrCommandContext		"Command"
#define kDswLgrKeyDnEvent			"kLButtonUp"
#define kDswLgrClsIDAttrName		"classid"
#define kDswLgrClsIDAttrShortValue	"0x264"
#define kDswLgrClsIDAttrLongValue	"0x264(kCreateMultiColumnItemCmdBoss)"
#define kDswLgrActIDAttrName		"actionid"
#define kDswLgrActIDAttrShortValue	"0x5f1a"	
#define kDswLgrActIDAttrLongValue	"0x5f1a(kAddNewPageActionID)"



#endif // __DswLgrID_h__

//  Code generated by DollyXs code generator
