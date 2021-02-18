//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/TrackChangesPrefsID.h $
//  
//  Owner: Kevin Van Wiel
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

#ifndef __TrackChangesPrefsID__
#define __TrackChangesPrefsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTrackChangesPrefsPrefix	 RezLong(0x18100)	// reserved in AdobePrefix.h

//PlugInID
#define kTrackChangesPrefsPlugInName		"TrackChangesPrefs"
DECLARE_PMID(kPlugInIDSpace, kTrackChangesPrefsPlugInID, kTrackChangesPrefsPrefix + 1)


// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kTCPrefsPanelBoss,						kTrackChangesPrefsPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTCPrefsMenuBoss,						kTrackChangesPrefsPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kSetTrackChangesPrefsCmdBoss,			kTrackChangesPrefsPrefix + 4)
//gap
//DECLARE_PMID(kClassIDSpace, kTCPrefsScriptProviderBoss,				kTrackChangesPrefsPrefix + 8)


// WidgetIDs (ClassIDs)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsParentWidgetId,				kTrackChangesPrefsPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsColorStaticWidgetId,			kTrackChangesPrefsPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsColorDropDownWidgetId,			kTrackChangesPrefsPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsColorSwatchWidgetId,			kTrackChangesPrefsPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsShowAddedTextCBWidgetId,		kTrackChangesPrefsPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsShowDeletedTextCBWidgetId,		kTrackChangesPrefsPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsShowMovedTextCBWidgetId,		kTrackChangesPrefsPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsShowChangeBarsCBWidgetId,		kTrackChangesPrefsPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsChangeBarColorStaticWidgetId,	kTrackChangesPrefsPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsChangeBarColorDropDownWidgetId,kTrackChangesPrefsPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsChangeBarColorSwatchWidgetId,	kTrackChangesPrefsPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsShowStaticWidgetId,			kTrackChangesPrefsPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsOptionsGroupWidgetId,			kTrackChangesPrefsPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsChangeBarFittedPanelWidgetId,	kTrackChangesPrefsPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsOptionsTitleTextWidgetId,		kTrackChangesPrefsPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsSpellChkDeletedTextCBId,		kTrackChangesPrefsPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kAddedTextColorDropDownWidgetId,		kTrackChangesPrefsPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kAddedBGColorDropDownWidgetId,			kTrackChangesPrefsPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kDeletedTextColorDropDownWidgetId,		kTrackChangesPrefsPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kDeletedBGColorDropDownWidgetId,		kTrackChangesPrefsPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kMovedTextColorDropDownWidgetId,		kTrackChangesPrefsPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kMovedBGColorDropDownWidgetId,			kTrackChangesPrefsPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kAddedTextMarkingDropDownWidgetId,		kTrackChangesPrefsPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kDeletedTextMarkingDropDownWidgetId,	kTrackChangesPrefsPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kMovedTextMarkingDropDownWidgetId,		kTrackChangesPrefsPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kChangeBarLocationDropDownWidgetId,	kTrackChangesPrefsPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kChangeBarOptionsGroupWidgetId,		kTrackChangesPrefsPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kChangeBarOptionsTitleTextWidgetId,	kTrackChangesPrefsPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kTCPrefsPreventDupeColorCBWidgetId,	kTrackChangesPrefsPrefix + 29)

// Interface IIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESPREFSCMDDATA,		kTrackChangesPrefsPrefix + 1)


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kTCPrefsPanelCreatorImpl,		kTrackChangesPrefsPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTCPrefsPanelControllerImpl,	kTrackChangesPrefsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTCPrefsMenuImpl,				kTrackChangesPrefsPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kTrackChangesPrefsCmdDataImpl,	kTrackChangesPrefsPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kSetTrackChangesPrefsCmdImpl,	kTrackChangesPrefsPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kTCPrefsScriptProviderImpl,	kTrackChangesPrefsPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTCPrefsDlgObserverImpl,		kTrackChangesPrefsPrefix + 7)

// ActionIDs
DECLARE_PMID(kActionIDSpace, kTCPrefsPanelActionID,				kTrackChangesPrefsPrefix + 1)

//////////////////////////////////////////////////////////////////////////////
//Script Element IDs
//////////////////////////////////////////////////////////////////////////////

//Types

//Suites
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewSuiteScriptElement,					kTrackChangesPrefsPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kTrackChangesPreferencesObjectScriptElement,			kTrackChangesPrefsPrefix + 40)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewObjectScriptElement,			kTrackChangesPrefsPrefix + 41)

//Events
//DECLARE_PMID(kScriptInfoIDSpace, kAcceptMethodScriptElement,					kTrackChangesPrefsPrefix + 80)
//DECLARE_PMID(kScriptInfoIDSpace, kRejectMethodScriptElement,					kTrackChangesPrefsPrefix + 81)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewMethodScriptElement,					kTrackChangesPrefsPrefix + 82)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kChangeBarColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kShowAddedTextPropertyScriptElement,				kTrackChangesPrefsPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kShowChangeBarsPropertyScriptElement,				kTrackChangesPrefsPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kShowDeletedTextPropertyScriptElement,				kTrackChangesPrefsPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kShowMovedTextPropertyScriptElement,				kTrackChangesPrefsPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kTrackedChangeColorPropertyScriptElement,			kTrackChangesPrefsPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kTrackChangesPreferencesPropertyScriptElement,		kTrackChangesPrefsPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kSpellChkDeletedTextPropertyScriptElement,			kTrackChangesPrefsPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kAddedTextColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kAddedBGColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kDeletedTextColorPropertyScriptElement,			kTrackChangesPrefsPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kDeletedBGColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kMovedTextColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kMovedBGColorPropertyScriptElement,				kTrackChangesPrefsPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kAddedTextMarkingPropertyScriptElement,			kTrackChangesPrefsPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kDeletedTextMarkingPropertyScriptElement,			kTrackChangesPrefsPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kMovedTextMarkingPropertyScriptElement,			kTrackChangesPrefsPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kChangeBarLocationPropertyScriptElement,			kTrackChangesPrefsPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kAddedTextColorChoicePropertyScriptElement,		kTrackChangesPrefsPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kAddedBGColorChoicePropertyScriptElement,			kTrackChangesPrefsPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kDeletedTextColorChoicePropertyScriptElement,		kTrackChangesPrefsPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kDeletedBGColorChoicePropertyScriptElement,		kTrackChangesPrefsPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kMovedTextColorChoicePropertyScriptElement,		kTrackChangesPrefsPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kMovedBGColorChoicePropertyScriptElement,			kTrackChangesPrefsPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kPreventDupeColorPropertyScriptElement,			kTrackChangesPrefsPrefix + 164)

//Enums
//DECLARE_PMID(kScriptInfoIDSpace, kChangeKindsEnumScriptElement,	kTrackChangesPrefsPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kChangeMarkingsEnumScriptElement,					kTrackChangesPrefsPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kChangeBarLocationsEnumScriptElement,				kTrackChangesPrefsPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kChangeTextColorChoicesEnumScriptElement,			kTrackChangesPrefsPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kChangeBGColorChoicesEnumScriptElement,			kTrackChangesPrefsPrefix + 224)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewEnumScriptElement,	kTrackChangesPrefsPrefix + 225)


//GUIDS
// {02D3CB36-EE64-43ce-8408-647E0F34FCE7}
#define kTrackChangesPref_CLSID { 0x02d3cb36, 0xee64, 0x43ce, { 0x84, 0x08, 0x64, 0x7e, 0xf, 0x34, 0xfc, 0xe7 } }

#endif // __TrackChangesPrefsID__




