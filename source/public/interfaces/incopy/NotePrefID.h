//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/NotePrefID.h $
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

#ifndef __NotePrefID__
#define __NotePrefID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kNotePrefPrefix	 RezLong(0x18000)	// reserved in AdobePrefix.h

//PlugInID
#define kNotePrefPanelPlugInName		"NotePref"

DECLARE_PMID(kPlugInIDSpace, kNotePrefPanelPlugInID, kNotePrefPrefix + 1)

// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kInCopyNotePrefPanelBoss,						kNotePrefPrefix + 2)
DECLARE_PMID(kClassIDSpace, kNotePrefMenuBoss,						kNotePrefPrefix	+ 3)
DECLARE_PMID(kClassIDSpace, kNotePrefCmdBoss,						kNotePrefPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kNotePrefsScriptProviderBoss,			kNotePrefPrefix + 8)
//gap
DECLARE_PMID(kClassIDSpace, kUIColorPreviewViewBoss,				kNotePrefPrefix + 10)
DECLARE_PMID(kClassIDSpace, kUIColorMenuBoss,						kNotePrefPrefix + 11)
DECLARE_PMID(kClassIDSpace,	kNotePrefConversionProviderBoss,		kNotePrefPrefix + 12)

// WidgetIDs (ClassIDs)
DECLARE_PMID(kWidgetIDSpace, kNotePrefParentWidgetID,				kNotePrefPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kNotePrefColorStaticWidgetId,			kNotePrefPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kNotePrefColorDropDownWidgetId,		kNotePrefPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSpellCheckNoteWidgetId,				kNotePrefPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kFindReplaceNoteWidgetId,				kNotePrefPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kShowNoteTipsWidgetId,					kNotePrefPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kApplyGalleyBGColorWidgetId,			kNotePrefPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kApplyUserBGColorWidgetId,				kNotePrefPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kBGColorChoiceWidgetId,				kNotePrefPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kNotePrefsGroupWidgetId,				kNotePrefPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kInlineNotesTitleTextWidgetID,			kNotePrefPrefix + 11)
//gap
DECLARE_PMID(kWidgetIDSpace, kNotesOptionsTitleTextWidgetID,		kNotePrefPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kInlineNoteBGColorStaticWidgetId,		kNotePrefPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kInlineNoteBGColorDropDownWidgetId,	kNotePrefPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kNotesInGalleyGroupWidgetId,			kNotePrefPrefix + 17)

DECLARE_PMID(kWidgetIDSpace, kFootnotePrefColorStaticWidgetId,		kNotePrefPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kFootnotePrefColorDropDownWidgetId,	kNotePrefPrefix + 19)


// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEPREFERENCES,				kNotePrefPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEPREFCMDDATA,				kNotePrefPrefix + 2)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kInCopyNotePrefPanelCreatorImpl,		kNotePrefPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kInCopyNotePrefPanelControllerImpl,	kNotePrefPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kNotePrefMenuImpl,				kNotePrefPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kNotePrefCmdDataImpl,			kNotePrefPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kNotePrefCmdImpl,				kNotePrefPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSessionNotePrefImpl,			kNotePrefPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kNotePrefsScriptProviderImpl,	kNotePrefPrefix + 8)
//gap
DECLARE_PMID(kImplementationIDSpace, kColorWidgetObserverImpl,	kNotePrefPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNotePrefDlgObserverImpl, kNotePrefPrefix + 14)


//////////////////////////////////////////////////////////////////////////////
// Action ID
//////////////////////////////////////////////////////////////////////////////
DECLARE_PMID(kActionIDSpace, kNotePrefPanelActionID,				kNotePrefPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNotePrefPanelSepActionID,				kNotePrefPrefix + 2)

//////////////////////////////////////////////////////////////////////////////
//Script Element IDs
//////////////////////////////////////////////////////////////////////////////

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kNotePreferencesObjectScriptElement,			kNotePrefPrefix + 40)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kNotePreferencesPropertyScriptElement,				kNotePrefPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kFindAndReplaceNoteContentsPropertyScriptElement,				kNotePrefPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kNoteBackgroundsEnumScriptElement,				kNotePrefPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kNoteBackgroundColorPropertyScriptElement,				kNotePrefPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kNoteColorPropertyScriptElement,				kNotePrefPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kShowNoteTipsPropertyScriptElement,				kNotePrefPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kSpellCheckNotesPropertyScriptElement,				kNotePrefPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kNoteColorChoicesEnumScriptElement,				kNotePrefPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kNoteColorChoicePropertyScriptElement,				kNotePrefPrefix + 148)

//Enums


//GUIDS
// {06F81BBC-A287-43ed-ABE4-C30EDBC6B9ED}
#define kNotePref_CLSID { 0x6f81bbc, 0xa287, 0x43ed, { 0xab, 0xe4, 0xc3, 0xe, 0xdb, 0xc6, 0xb9, 0xed } }

#endif // __NotePrefID__




