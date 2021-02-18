//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/WavTlID.h $
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
//  
//  Defines IDs used by the WaveTool plug-in.
//  
//========================================================================================

#ifndef __WavTlID_h__
#define __WavTlID_h__

#include "WavTlRezDefs.h"

// Company:
#define kWavTlCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kWavTlCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kWavTlPluginName	"WaveTool" // Name of this plug-in.
#define kWavTlPrefixNumber	0x47800 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kWavTlVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kWavTlAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kWavTlPrefixNumber above to modify the prefix.)
#define kWavTlPrefix		RezLong(kWavTlPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kWavTlStringPrefix	SDK_DEF_STRINGIZE(kWavTlPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kWavTlPluginID,	kWavTlPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kWavTlActionComponentBoss,	kWavTlPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kWavTlStringRegisterBoss,	kWavTlPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kWavTlMenuRegisterBoss,		kWavTlPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kWavTlActionRegisterBoss,	kWavTlPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSawWaveToolBoss,			kWavTlPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSawWaveTrackerBoss,		kWavTlPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSineWaveToolBoss,			kWavTlPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSineWaveTrackerBoss,		kWavTlPrefix + 7)
DECLARE_PMID(kClassIDSpace, kWavTlTrackerRegisterBoss,	kWavTlPrefix + 8)

// InterfaceIDs:
// None in this plug-in.

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kWavTlActionComponentImpl,	kWavTlPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kSawWaveToolImpl,			kWavTlPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSawWaveTrackerImpl,		kWavTlPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kWavTlTrackerRegisterImpl,	kWavTlPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSineWaveToolImpl,			kWavTlPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSineWaveTrackerImpl,		kWavTlPrefix + 5)

// WidgetIDs	
DECLARE_PMID(kWidgetIDSpace, kSawWaveToolWidgetID,	kWavTlPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kSineWaveToolWidgetID,	kWavTlPrefix + 1)

// ActionIDs for menu items.
DECLARE_PMID(kActionIDSpace, kWavTlAboutActionID,	kWavTlPrefix + 0)
// ActionIDs for tool shortcuts.
DECLARE_PMID(kActionIDSpace, kSawWaveToolActionID,	kWavTlPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSineWaveToolActionID,	kWavTlPrefix + 2)

// "About Plug-ins" sub-menu:
#define kWavTlAboutMenuKey			kWavTlStringPrefix "kWavTlAboutMenuKey"
#define kWavTlAboutMenuPath			kSDKDefStandardAboutMenuPath kWavTlCompanyKey

// "Plug-ins" sub-menu:
#define kWavTlPluginsMenuKey 		kWavTlStringPrefix "kWavTlPluginsMenuKey"
#define kWavTlPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kWavTlCompanyKey kSDKDefDelimitMenuPath kWavTlPluginsMenuKey

// StringKeys:
#define kWavTlAboutBoxStringKey		kWavTlStringPrefix "kWavTlAboutBoxStringKey"
#define kSineWaveToolStringKey		kWavTlStringPrefix kWavTlPluginName "kSineStringKey"
#define kSawWaveToolStringKey		kWavTlStringPrefix kWavTlPluginName "kSawStringKey"

// Initial data format version numbers
#define kWavTlFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kWavTlFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kWavTlCurrentMajorFormatNumber kWavTlFirstMajorFormatNumber // most recent major format change
#define kWavTlCurrentMinorFormatNumber kWavTlFirstMinorFormatNumber // most recent minor format change

#endif // __WavTlID_h__

// End, WavTlID.h.



