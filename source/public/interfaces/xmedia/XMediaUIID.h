//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/XMediaUIID.h $
//  
//  Owner: Ryan Gano
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
//  Contains IDs used by the XMedia UI
//  
//========================================================================================

#ifndef __XMediaUIID__
#define __XMediaUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define TEXT_CONTENT_IN_WIDGET

#define kXMediaUIPrefix			RezLong(0x13300)  
#define kXMediaUIPrefix2		RezLong(0x1ef00)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kXMediaUIPluginName 	"XMedia UI"
DECLARE_PMID(kPlugInIDSpace, kXMediaUIPluginID, kXMediaUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

//Plugin
DECLARE_PMID(kClassIDSpace,		kFileNameBrowseWidgetBoss,		kXMediaUIPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kFileNameEditWidgetBoss,		kXMediaUIPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace,		kStructureMenuActionBoss,		kXMediaUIPrefix + 5)

// Tree Control
DECLARE_PMID(kClassIDSpace,		kInCopyStructureTreeViewWidgetBoss,	kXMediaUIPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kXMLElementNameBoss,			kXMediaUIPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kStructureTreeViewWidgetBoss,	kXMediaUIPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kStructureTreeNodeWidgetBoss,	kXMediaUIPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kAttributeNodeWidgetBoss,		kXMediaUIPrefix + 10)

// XML Panel
DECLARE_PMID(kClassIDSpace,		kXMLPanelBoss,					kXMediaUIPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kXMLPanelActionComponentBoss,	kXMediaUIPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kXMLNewElementButtonBoss,		kXMediaUIPrefix + 13)
DECLARE_PMID(kClassIDSpace,		kXMLDeleteButtonBoss,			kXMediaUIPrefix + 14)
DECLARE_PMID(kClassIDSpace,		kDeleteContentDialogBoss,		kXMediaUIPrefix + 15)
DECLARE_PMID(kClassIDSpace,		kXMLFittedStaticTextBoss,		kXMediaUIPrefix + 16)
DECLARE_PMID(kClassIDSpace,		kXMLDragDropDEHandlerBoss,		kXMediaUIPrefix + 17)
DECLARE_PMID(kClassIDSpace,		kStructureGroupBoss, 			kXMediaUIPrefix + 18)
DECLARE_PMID(kClassIDSpace,		kXMLElementIconBoss, 			kXMediaUIPrefix + 19)
DECLARE_PMID(kClassIDSpace,		kFontSpecStaticTextWidgetBoss, 	kXMediaUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,		kStructureTextContentWidgetBoss,	kXMediaUIPrefix + 21)
DECLARE_PMID(kClassIDSpace,		kChangeStructureViewPrefsCmdBoss,	kXMediaUIPrefix + 22)
DECLARE_PMID(kClassIDSpace,		kShowTagMarkersCmdBoss,				kXMediaUIPrefix + 23)
DECLARE_PMID(kClassIDSpace,		kXMLLayoutActionBoss,				kXMediaUIPrefix + 24)
DECLARE_PMID(kClassIDSpace,		kStructureOpenLayoutWinResponderBoss,kXMediaUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, 	kLayoutDDTargetXMLFlavorHelperBoss,	kXMediaUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, 	kXMLNewAttributeButtonBoss,			kXMediaUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, 	kXMLTextSnippetStaticTextBoss,	kXMediaUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, 	kXMLStructureMenuButtonBoss,	kXMediaUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, 	kChangeDocStructurePrefsCmdBoss,kXMediaUIPrefix + 30)

//Tag Panel
DECLARE_PMID(kClassIDSpace,		kTagPanelBoss,					kXMediaUIPrefix + 31)
DECLARE_PMID(kClassIDSpace,		kTagPanelActionComponentBoss,	kXMediaUIPrefix + 32)
DECLARE_PMID(kClassIDSpace,		kTagListWidgetBoss,				kXMediaUIPrefix + 33)
DECLARE_PMID(kClassIDSpace,		kTagOptionsDlgBoss,				kXMediaUIPrefix + 34)
DECLARE_PMID(kClassIDSpace,		kNewTagButtonBoss,				kXMediaUIPrefix + 35)
DECLARE_PMID(kClassIDSpace,		kDeleteTagButtonBoss,			kXMediaUIPrefix + 36)
DECLARE_PMID(kClassIDSpace,		kTagPanelTreeNodeWidgetBoss,	kXMediaUIPrefix + 37)
DECLARE_PMID(kClassIDSpace,		kTagPanelNameStaticTextBoss,	kXMediaUIPrefix + 38)
DECLARE_PMID(kClassIDSpace,		kUntagButtonBoss,				kXMediaUIPrefix + 39)
DECLARE_PMID(kClassIDSpace,		kDeleteTagDlgBoss,				kXMediaUIPrefix + 40)
DECLARE_PMID(kClassIDSpace,		kTagPanelRadioButtonBoss,		kXMediaUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, 	kInCopyStoryNodeWidgetBoss,		kXMediaUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, 	kProcessDeleteXMLTagsCmdBoss,	kXMediaUIPrefix + 43)

//Widgets
DECLARE_PMID(kClassIDSpace,		kEditInPlaceTextWidgetBoss,		kXMediaUIPrefix + 50)
DECLARE_PMID(kClassIDSpace,		kEditInPlaceClickOutsideEHBoss,	kXMediaUIPrefix + 51)
DECLARE_PMID(kClassIDSpace,		kEditableTagNameWidgetBoss,		kXMediaUIPrefix + 52)
DECLARE_PMID(kClassIDSpace,		kSelectableIconBoss,			kXMediaUIPrefix + 53)


// Mapping Dialog
DECLARE_PMID(kClassIDSpace,		kTagToStyleMappingDialogBoss,			kXMediaUIPrefix + 54)
DECLARE_PMID(kClassIDSpace,		kTagToStyleMappingPanelBoss,			kXMediaUIPrefix + 55)
DECLARE_PMID(kClassIDSpace,		kTagMappingListWidgetBoss,				kXMediaUIPrefix + 56)
DECLARE_PMID(kClassIDSpace,		kStyleToTagMappingDialogBoss,			kXMediaUIPrefix + 57)
DECLARE_PMID(kClassIDSpace,		kStyleToTagMappingPanelBoss,			kXMediaUIPrefix + 58)
DECLARE_PMID(kClassIDSpace,		kStyleMappingListWidgetBoss,			kXMediaUIPrefix + 59)
DECLARE_PMID(kClassIDSpace,		kTagMappingListItemWidgetBoss,			kXMediaUIPrefix + 60)
DECLARE_PMID(kClassIDSpace,		kTagMappingDropdownListWidgetBoss,		kXMediaUIPrefix + 61)
DECLARE_PMID(kClassIDSpace,		kStyleMappingDropdownListWidgetBoss,	kXMediaUIPrefix + 62)
DECLARE_PMID(kClassIDSpace,		kStyleMappingListItemWidgetBoss,		kXMediaUIPrefix + 63)
DECLARE_PMID(kClassIDSpace,		kMappingSplitterWidgetBoss,				kXMediaUIPrefix + 64)
DECLARE_PMID(kClassIDSpace,		kAutoTagButtonBoss,						kXMediaUIPrefix + 65)
//DECLARE_PMID(kClassIDSpace,		kNewRuleButtonBoss,						kXMediaUIPrefix + 66)
//DECLARE_PMID(kClassIDSpace,		kDeleteRuleButtonBoss,					kXMediaUIPrefix + 67)
//DECLARE_PMID(kClassIDSpace,		kFancyNewBoss,						kXMediaUIPrefix + 68)
DECLARE_PMID(kClassIDSpace,	 	kStyleInLineMappingDropdownListWidgetBoss, kXMediaUIPrefix + 69)
DECLARE_PMID(kClassIDSpace,		kXMLChooseTagDialogBoss,				kXMediaUIPrefix + 70)
DECLARE_PMID(kClassIDSpace,		kSetAttributeDialogBoss,				kXMediaUIPrefix + 71)
DECLARE_PMID(kClassIDSpace,		kExportXMLOptionsDialogBoss,			kXMediaUIPrefix + 72)
DECLARE_PMID(kClassIDSpace,		kXMLTagDragDropDEHandlerBoss,			kXMediaUIPrefix + 73)
DECLARE_PMID(kClassIDSpace,		kInCopyExportXMLOptionsDialogBoss,		kXMediaUIPrefix + 74)

DECLARE_PMID(kClassIDSpace,		kMappingInLineEditEventMonitorBoss,	kXMediaUIPrefix + 75)

DECLARE_PMID(kClassIDSpace,		kXMediaUISuiteRegisterBoss,					kXMediaUIPrefix + 77)
DECLARE_PMID(kClassIDSpace,	 	kTagInLineMappingDropdownListWidgetBoss,	kXMediaUIPrefix + 78)
DECLARE_PMID(kClassIDSpace,	 	kIconStaticTextWidgetBoss,					kXMediaUIPrefix + 79)


// Menus
DECLARE_PMID(kClassIDSpace,		kXMediaUIMenuActionBoss,				kXMediaUIPrefix + 80)
DECLARE_PMID(kClassIDSpace,		kChooseTagActionComponentBoss,			kXMediaUIPrefix + 81)
DECLARE_PMID(kClassIDSpace,		kInsertChildElementActionComponentBoss,	kXMediaUIPrefix + 82)
DECLARE_PMID(kClassIDSpace,		kInsertSiblingAfterActionComponentBoss,	kXMediaUIPrefix + 83)
DECLARE_PMID(kClassIDSpace,		kReplaceElementActionComponentBoss,		kXMediaUIPrefix + 84)

DECLARE_PMID(kClassIDSpace,		kXMLMarkerAdornmentBoss,			kXMediaUIPrefix + 90)
DECLARE_PMID(kClassIDSpace,		kXMLImportDialogBoss,				kXMediaUIPrefix + 91)
DECLARE_PMID(kClassIDSpace,		kShowTaggedFramesCmdBoss,			kXMediaUIPrefix + 92)
DECLARE_PMID(kClassIDSpace,		kXMLTaggedFrameAdornmentBoss,		kXMediaUIPrefix + 93)  // kTaggedFrameDrawEventServicesBoss
DECLARE_PMID(kClassIDSpace,		kXMediaUIConversionProviderBoss,	kXMediaUIPrefix + 94)
DECLARE_PMID(kClassIDSpace,		kTaggedFrameActionServicesBoss,		kXMediaUIPrefix + 95)
DECLARE_PMID(kClassIDSpace,		kStructureShortcutContextBoss,		kXMediaUIPrefix + 96)
DECLARE_PMID(kClassIDSpace,		kTagUIColorSwatchWidgetBoss,		kXMediaUIPrefix + 97)

// More XML Panel
DECLARE_PMID(kClassIDSpace, 	kXMediaUINewDocResponderBoss,				kXMediaUIPrefix + 100)
// gap
DECLARE_PMID(kClassIDSpace,		kStructureSplitterWidgetBoss,				kXMediaUIPrefix + 102)
DECLARE_PMID(kClassIDSpace,		kStructureSplitterTrackerRegisterBoss,		kXMediaUIPrefix + 103)
DECLARE_PMID(kClassIDSpace,		kXorSplitterTrackerBoss,					kXMediaUIPrefix + 104)
DECLARE_PMID(kClassIDSpace,		kXMLAttributeWidgetBoss,					kXMediaUIPrefix + 105)
DECLARE_PMID(kClassIDSpace,		kListPaletteTreeScrollerBoss,				kXMediaUIPrefix + 106)
DECLARE_PMID(kClassIDSpace,		kSelectInStructureMsg,						kXMediaUIPrefix + 107)	// changedBy is K2Vector<XMLReference>*
// gap
DECLARE_PMID(kClassIDSpace,		kStructureCreateGalleyWidgetResponderBoss,	kXMediaUIPrefix + 109)
DECLARE_PMID(kClassIDSpace,		kColorFontSpecStaticTextWidgetBoss,			kXMediaUIPrefix + 110)
// gap
DECLARE_PMID(kClassIDSpace,		kXMLValidateStructureButtonBoss,			kXMediaUIPrefix + 112)
DECLARE_PMID(kClassIDSpace,		kXMLCloseValidationButtonBoss,				kXMediaUIPrefix + 113)
DECLARE_PMID(kClassIDSpace,		kXMLNavigateLeftButtonBoss,					kXMediaUIPrefix + 114)
DECLARE_PMID(kClassIDSpace,		kXMLNavigateRightButtonBoss,				kXMediaUIPrefix + 115)
DECLARE_PMID(kClassIDSpace,		kXMLValidationPanelWidgetBoss,				kXMediaUIPrefix + 117)
DECLARE_PMID(kClassIDSpace,		kXMLDTDOptionsDialogBoss,					kXMediaUIPrefix + 118)
DECLARE_PMID(kClassIDSpace,		kPageItemDDTargetXMLFlavorHelperBoss,		kXMediaUIPrefix + 119)
DECLARE_PMID(kClassIDSpace,		kClickableStaticMultiLineTextWidgetBoss,	kXMediaUIPrefix + 120)
DECLARE_PMID(kClassIDSpace,		kXMediaNewPageItemResponderBoss,			kXMediaUIPrefix + 121)
DECLARE_PMID(kClassIDSpace,		kMapTagsToStyleErrorDialogBoss,				kXMediaUIPrefix + 122)
DECLARE_PMID(kClassIDSpace,		kSetDocTypeDialogBoss,						kXMediaUIPrefix + 123)
DECLARE_PMID(kClassIDSpace,		kViewErrorsDialogBoss,						kXMediaUIPrefix + 124)

// Scripting
DECLARE_PMID(kClassIDSpace,		kXMLViewPrefsScriptProviderBoss,			kXMediaUIPrefix + 125)

// Comment and PI dialog
DECLARE_PMID(kClassIDSpace,		kSetCommentDialogBoss,						kXMediaUIPrefix + 130)
DECLARE_PMID(kClassIDSpace,		kSetPIDialogBoss,							kXMediaUIPrefix + 131)

// Image Conversion
DECLARE_PMID(kClassIDSpace,		kExportXMLDialogBoss,						kXMediaUIPrefix + 200)
DECLARE_PMID(kClassIDSpace,		kExportXMLImageOptionsDialogBoss,			kXMediaUIPrefix + 201)
DECLARE_PMID(kClassIDSpace,		kExportCJKOptionsDialogBoss,				kXMediaUIPrefix + 202)

// Move Validation Panel
DECLARE_PMID(kClassIDSpace,		kXMLValidationPositionEditBoxWidgetBoss,	kXMediaUIPrefix + 210)
DECLARE_PMID(kClassIDSpace,		kXMLNavigateFirstButtonBoss,				kXMediaUIPrefix + 211)
DECLARE_PMID(kClassIDSpace,		kXMLNavigateLastButtonBoss,					kXMediaUIPrefix + 212)
DECLARE_PMID(kClassIDSpace,		kXMLViewErrorsDialogButtonBoss,				kXMediaUIPrefix + 213)
DECLARE_PMID(kClassIDSpace,		kXMLValidationErrorFlagsBoss,				kXMediaUIPrefix + 214)

DECLARE_PMID(kClassIDSpace,		kSelectStylesheetButtonBoss,				kXMediaUIPrefix + 216)

DECLARE_PMID(kClassIDSpace,		kXMediaUIPhase2ConversionBoss,				kXMediaUIPrefix + 220)
DECLARE_PMID(kClassIDSpace,		kXMLTextEditBoxWidgetBoss,					kXMediaUIPrefix + 221)

// View DocType dialog
DECLARE_PMID(kClassIDSpace,		kViewDocTypeDialogBoss,						kXMediaUIPrefix + 222)

// Deferred Notify observer
DECLARE_PMID(kClassIDSpace,		kDeferredNotifyStartupServiceBoss,			kXMediaUIPrefix + 223)

// SaveTagList dialog
DECLARE_PMID(kClassIDSpace,		kSaveTagListDialogBoss,						kXMediaUIPrefix + 224)

DECLARE_PMID(kClassIDSpace, kStructureDataExchHandlerDefaultHelperBoss,		kXMediaUIPrefix + 225)
DECLARE_PMID(kClassIDSpace, kStructureDataExchHandlerSnippetHelperBoss,		kXMediaUIPrefix + 226)
DECLARE_PMID(kClassIDSpace, kXMLPreferencesDialogBoss,						kXMediaUIPrefix + 227)
DECLARE_PMID(kClassIDSpace, kShowTagOptionsCmdBoss,							kXMediaUIPrefix + 228)
//DECLARE_PMID(kClassIDSpace, kFancyNewBoss, kXMediaUIPrefix + 229)


// XML Import UI
DECLARE_PMID(kClassIDSpace, kXMLImportDefaultUIServiceBoss,					kXMediaUIPrefix + 230)
DECLARE_PMID(kClassIDSpace, kXMLImportSecondUIServiceBoss,					kXMediaUIPrefix + 231)
DECLARE_PMID(kClassIDSpace, kXMLImportOptionsDialogBoss,					kXMediaUIPrefix + 232)

// ---- Moved from XML plug-in
DECLARE_PMID(kClassIDSpace, kXMLTestMenuBoss, 								kXMediaUIPrefix + 233)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kSnippetTestMenuBoss,							kXMediaUIPrefix + 234)


//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 235)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 236)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 237)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 238)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 239)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 240)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 241)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 242)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 243)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 244)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 245)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 246)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 247)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 248)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 249)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 250)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 251)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 252)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 253)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 254)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix + 255)

//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 1)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 2)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 3)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 4)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 5)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 6)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 7)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 8)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 9)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,	IID_IEDITINPLACESTATEDATA,				kXMediaUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGLAYSELECTIONOBSERVER,			kXMediaUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGALPHAUIDLISTDATA, 				kXMediaUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGSUITE, 						kXMediaUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTUREVIEWPREFS,				kXMediaUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILENAMEWIDGETCONTROLLER,			kXMediaUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCSTRUCTUREPREFS, 				kXMediaUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPREFERENCES, 					kXMediaUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLLAYOUTOBSERVER,				 	kXMediaUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMEDIAUTILS,					 	kXMediaUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTTRACKERBOOLDATA,				kXMediaUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGACTIONCOMPNENT,			 	kXMediaUIPrefix + 17)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSELECTIONHIGHLIGHTOBSERVER,		kXMediaUIPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTURESELECTIONOBSERVER,		kXMediaUIPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTURESELTRACKERSUITE,			kXMediaUIPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTURESELECTIONTRACKER,			kXMediaUIPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAPOBSERVER,						kXMediaUIPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTURENAVIGATIONSUITE,			kXMediaUIPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDRAGDROPSUITE,					kXMediaUIPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLNODEUTILS,					 	kXMediaUIPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPANDEDSTATEDATA,					kXMediaUIPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTINSTRUCTUREOBSERVER,			kXMediaUIPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTUREISSHOWNBOOLDATA,			kXMediaUIPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETECONTENTDIALOGSTATE,			kXMediaUIPrefix + 30)	
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYINFOOBSERVER,					kXMediaUIPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWMGR2,						kXMediaUIPrefix + 32)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IISVALIDSTATEBOOLDATA,				kXMediaUIPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLVALIDATIONERRORSCONTROLDATA,	kXMediaUIPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGLOCATIONDATA,					kXMediaUIPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDUID,						kXMediaUIPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLREFERENCELIST,					kXMediaUIPrefix + 38)

DECLARE_PMID(kInterfaceIDSpace, IID_IIXMLVALIDATIONERRORFLAGS,			kXMediaUIPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLICKABLESTATICMLTDATA,			kXMediaUIPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTEERRORLIST,				kXMediaUIPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEDIRTY,							kXMediaUIPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPANELCOMMANDMGROBSERVER,		kXMediaUIPrefix + 43)

DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTXMLDIALOGOBSERVER,			kXMediaUIPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_DIALOGCANCELLEDDATA,				kXMediaUIPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMARKERWAXRUNCACHE,				kXMediaUIPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMOVETABLEROW,					kXMediaUIPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMOVETABLECOLUMN,				kXMediaUIPrefix + 48)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYIID,			kXMediaUIPrefix + 49)

// XML Import UI
DECLARE_PMID(kInterfaceIDSpace, IID_IIXMLIMPORTOPTIONSSERVICE,			kXMediaUIPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTOPTIONSDIALOG,			kXMediaUIPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTOPTIONSUIMAPPER,			kXMediaUIPrefix + 52)

//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYIID, kXMediaUIPrefix + 53)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYIID, kXMediaUIPrefix + 54)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYIID, kXMediaUIPrefix + 55)


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

// XML Panel
DECLARE_PMID(kImplementationIDSpace, kStructureViewPrefsImpl,			kXMediaUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kStructureSelectionHighlightImpl,	kXMediaUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXMLPanelActionComponentImpl,		kXMediaUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kStructureTreeViewAdapterImpl,		kXMediaUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kStructureTreeViewWidgetMgrImpl,	kXMediaUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kStructureDDSourceImpl,			kXMediaUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStructureDDTargetImpl,			kXMediaUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kStructureDDTargetProviderImpl,	kXMediaUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kStructureObserverImpl,			kXMediaUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kNewStructureWinCmdImpl,			kXMediaUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCloseStructureWinCmdImpl,			kXMediaUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kXMLDragDropDEHandlerImpl,			kXMediaUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kIntoStructureDDTargetImpl,		kXMediaUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNextToStructureDDTargetImpl,		kXMediaUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteButtonObsvImpl,			kXMediaUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kFileNameTextValidationImpl,		kXMediaUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kChangeStructureViewPrefsCmdImpl,	kXMediaUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kXMLPreferencesImpl,				kXMediaUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kShowTagMarkersCmdImpl,			kXMediaUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kXMLLayoutObserverImpl,			kXMediaUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kXMLNewElementButtonObsvImpl,		kXMediaUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kStructureOpenLayoutWinRespImpl,	kXMediaUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kStructureNodeEHImpl,				kXMediaUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargetXMLFlavorHelperImpl, kXMediaUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kXMLPanelEHImpl, 					kXMediaUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kStructureViewSelectionImpl, 		kXMediaUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAttributeNodeEHImpl,		 		kXMediaUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kXMLSelectionHiliteObserverImpl, 	kXMediaUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kStructureSelectionObserverImpl, 	kXMediaUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kStructureSelTrackerTextCSBImpl, 	kXMediaUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kStructureSelTrackerASBImpl, 		kXMediaUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kStructureSelectionTrackerImpl, 	kXMediaUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kStructureSelTrackerLaytCSBImpl, 	kXMediaUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kXMLNewAttributeButtonObsvImpl, 	kXMediaUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kStructureNodeTips, 				kXMediaUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kAttributeNodeTips, 				kXMediaUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kXMLTaggedFrameAdornmentImpl,	 	kXMediaUIPrefix + 37) // kTaggedFramesDrawEventImpl
DECLARE_PMID(kImplementationIDSpace, kShowTaggedFramesCmdImpl, 			kXMediaUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kDeleteContentDialogObserverImpl,	kXMediaUIPrefix + 39)

// Tag Panel
DECLARE_PMID(kImplementationIDSpace, kTagPanelActionComponentImpl,		kXMediaUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kTagListObserverImpl,				kXMediaUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kTagOptionsDlgControllerImpl,		kXMediaUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kNewTagButtonObserverImpl,			kXMediaUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kTagPanelTreeViewAdapterImpl,		kXMediaUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTagPanelTreeViewWidgetMgrImpl,	kXMediaUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDeleteTagButtonObserverImpl,		kXMediaUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kTagSelectionObserverImpl,			kXMediaUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kTagLayoutSelectionObserverImpl,	kXMediaUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTagPanelViewImpl,					kXMediaUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kTagPanelTreeNodeEHImpl,			kXMediaUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kTagNameObserverImpl,				kXMediaUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kDeleteTagDlgControllerImpl,		kXMediaUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kXMLLayoutActionImpl,				kXMediaUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteTextCSBImpl,			kXMediaUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kUntagButtonObserverImpl,			kXMediaUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kTagNameTextValidationImpl,		kXMediaUIPrefix + 57)
// gap
DECLARE_PMID(kImplementationIDSpace, kTagPanelRadioButtonEHImpl,		kXMediaUIPrefix + 59)
// gap
DECLARE_PMID(kImplementationIDSpace, kTagPanelSwatchViewImpl,			kXMediaUIPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kTagPanelRadioTipImpl,				kXMediaUIPrefix + 62)
// gap
DECLARE_PMID(kImplementationIDSpace, kTagTreeViewMgrImpl,				kXMediaUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kNewTagDragDropTargetImpl,			kXMediaUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteTableCSBImpl, 			kXMediaUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTagNameILEEditingAttributesImpl,	kXMediaUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kPageItemDDTargetXMLFlavorHelperImpl,	kXMediaUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kDeleteContentDialogStateImpl,	kXMediaUIPrefix + 69)

//Widgets
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceViewImpl,				kXMediaUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceEHImpl,				kXMediaUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceClickOutsideEHImpl,	kXMediaUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceStateDataImpl,			kXMediaUIPrefix + 73)
//gap

//Selection
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteASBImpl,				kXMediaUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteLayoutCSBImpl,			kXMediaUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceEBAttributesImpl,		kXMediaUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteLayoutCSBExtImpl,		kXMediaUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteTextCSBExtImpl,		kXMediaUIPrefix + 79)

// Menu
DECLARE_PMID(kImplementationIDSpace, kStructureMenuActionImpl,			kXMediaUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kXMediaUIMenuActionImpl,			kXMediaUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kChooseTagMenuActionImpl,			kXMediaUIPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kChooseTagDynamicMenuImpl,			kXMediaUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kInsertChildElementMenuActionImpl,	kXMediaUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kInsertChildElementDynamicMenuImpl,kXMediaUIPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kInsertSiblingAfterMenuActionImpl,	kXMediaUIPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kInsertSiblingAfterDynamicMenuImpl,kXMediaUIPrefix + 87)



//Mapping Dialog
DECLARE_PMID(kImplementationIDSpace, kICExportXMLDialogObserverImpl,	kXMediaUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingNodeObserverImpl,			kXMediaUIPrefix + 89)
// gap
DECLARE_PMID(kImplementationIDSpace, kMappingDialogObserverImpl,		kXMediaUIPrefix + 91)
// gap
DECLARE_PMID(kImplementationIDSpace, kMappingSplitterRollOverImpl,	kXMediaUIPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTagToStyleMappingControllerImpl,	kXMediaUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kStyleToTagMappingControllerImpl,	kXMediaUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kMappingTagViewWidgetMgrImpl,		kXMediaUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kMappingListObserverImpl,			kXMediaUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kMappingStyleViewWidgetMgrImpl,	kXMediaUIPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kMappingPanelObserverImpl,			kXMediaUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kMappingStyleTreeViewAdaptorImpl,	kXMediaUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kChooseTagDialogControllerImpl,	kXMediaUIPrefix + 102)
// gap
DECLARE_PMID(kImplementationIDSpace, kXMLStructureTVControllerImpl,		kXMediaUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kXMLTagSuiteXMLCSBImpl,			kXMediaUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kSetAttributeDlgControllerImpl,	kXMediaUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kXMLMarkerAdornmentImpl,			kXMediaUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kExportXMLDialogControllerImpl,	kXMediaUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kXMediaUtilsImpl,					kXMediaUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kXMLImportDialogImpl,				kXMediaUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kIDExportXMLDialogObserverImpl,	kXMediaUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kXMLNodeUtilsImpl,					kXMediaUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kStrUIDPairDDLControlDataImpl,		kXMediaUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kXMLMarkerWaxRunCacheImpl,			kXMediaUIPrefix + 114)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kXMediaUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kSelectedStyleUIDImpl,				kXMediaUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kIconTextWidgetControllerImpl,		kXMediaUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kTagMappingNodeObserverImpl,		kXMediaUIPrefix + 118)
//gap


DECLARE_PMID(kImplementationIDSpace, kTaggedFramesActionServiceImpl,	kXMediaUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTagDropDownTypeAheadImpl, 		kXMediaUIPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kStructureShortcutContextCSBImpl, 	kXMediaUIPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kStructureNavigationSuiteCSBImpl, 	kXMediaUIPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kXMLDuplicateDDTargetImpl, 	kXMediaUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kXMLTagDDSourceImpl, 	kXMediaUIPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kTagDeleteDragDropTargetImpl, 	kXMediaUIPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kXMLTagDragDropDEHandlerImpl, 	kXMediaUIPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kIconTextWidgetAttribImpl, 	kXMediaUIPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kTagControllerImpl, 	kXMediaUIPrefix + 129)


//More XML Panel
DECLARE_PMID(kImplementationIDSpace, kXMLDragDropSuiteASBImpl,			kXMediaUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kXMLDragDropSuiteCSBImpl, 			kXMediaUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kStructureNodeViewImpl, 			kXMediaUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kXMLTextSnippetViewImpl, 			kXMediaUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kChangeDocStructurePrefsCmdImpl, 	kXMediaUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kDocStructurePrefsImpl, 			kXMediaUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kXMediaUINewDocResponderImpl, 		kXMediaUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kXMLNodeTextControlDataImpl, 		kXMediaUIPrefix + 137)

// gap
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteDDTargetImpl,			kXMediaUIPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kUnderlineStaticTextViewImpl,		kXMediaUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kStructureSplitterEHImpl,			kXMediaUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kStructureSplitterTrackerRegImpl,	kXMediaUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kXorSplitterTrackerImpl,			kXMediaUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kStructureSplitterWidgetViewImpl,	kXMediaUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kExpandedStateDataImpl,			kXMediaUIPrefix + 145)
// gap
DECLARE_PMID(kImplementationIDSpace, kEditInPlaceCmdObserverImpl,		kXMediaUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kListPaletteTreeWidgetViewImpl,	kXMediaUIPrefix + 148)
//gap
DECLARE_PMID(kImplementationIDSpace, kStructureWidgetCacheImpl,			kXMediaUIPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kStructureCSBDocumentObserverImpl,	kXMediaUIPrefix + 151)
//gap
DECLARE_PMID(kImplementationIDSpace, kSelectInStructureObserverImpl,	kXMediaUIPrefix + 153)
//gap
DECLARE_PMID(kImplementationIDSpace, kDTDOptionsDialogControllerImpl,	kXMediaUIPrefix + 155) 
DECLARE_PMID(kImplementationIDSpace, kXMediaCreateGalleySignalServiceImpl,kXMediaUIPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kStructureTreeViewEHImpl,			kXMediaUIPrefix + 158)

//InCopy Specific
DECLARE_PMID(kImplementationIDSpace, kInCopyStructureTVAdapterImpl,		kXMediaUIPrefix + 160)
// gap
DECLARE_PMID(kImplementationIDSpace, kStoryInfoObserverImpl,			kXMediaUIPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kStorySeparatorNodeViewImpl,		kXMediaUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kColorFittedStaticTextViewImpl,	kXMediaUIPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kStructureStoryNodeEHImpl,			kXMediaUIPrefix + 165)

// Validation pane
DECLARE_PMID(kImplementationIDSpace, kXMLValidateStructureButtonObsvImpl,			kXMediaUIPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kXMLCloseValidationButtonObsvImpl,				kXMediaUIPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kValidationLabelObserverImpl,					kXMediaUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationErrorsControlDataImpl,			kXMediaUIPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationNavigateLeftButtonObsvImpl,		kXMediaUIPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationNavigateRightButtonObsvImpl,		kXMediaUIPrefix + 171)
// gap
DECLARE_PMID(kImplementationIDSpace, kClickableStaticMultiLineTextObsvImpl,			kXMediaUIPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kClickableStaticMultiLineTextViewImpl,			kXMediaUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kTaggedStaticTextLineBreakerImpl,				kXMediaUIPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kTagLocationDataImpl,							kXMediaUIPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kClickableStaticMultiLineTextEHImpl,			kXMediaUIPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kXMediaNewPageItemResponderImpl,				kXMediaUIPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kAttributeErrorListImpl,						kXMediaUIPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationNavigateFirstButtonObsvImpl,		kXMediaUIPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationNavigateLastButtonObsvImpl,		kXMediaUIPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kValidationPositionEditBoxTextControlImpl,		kXMediaUIPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kViewErrorsListButtonObserverImpl,				kXMediaUIPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kXMLReferenceListImpl,							kXMediaUIPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kValidationPositionEditBoxEventHandlerImpl,	kXMediaUIPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kViewErrorsDialogObserverImpl,					kXMediaUIPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kIconTextWidgetOwnerDrawDDItemImpl,			kXMediaUIPrefix + 187)
// gap

DECLARE_PMID(kImplementationIDSpace, kProcessDeleteXMLTagsCmdImpl,	kXMediaUIPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kXMediaUIPhase2ConversionImpl,	kXMediaUIPrefix + 190)

// Scripting
DECLARE_PMID(kImplementationIDSpace, kXMLViewPrefsScriptProviderImpl,	kXMediaUIPrefix + 195)

// Image Conversion
DECLARE_PMID(kImplementationIDSpace, kExportXMLDialogCreatorImpl,		kXMediaUIPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kExportXMLDialogServiceImpl,		kXMediaUIPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kExportXMLImageControllerImpl,		kXMediaUIPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kExportXMLImageObserverImpl,		kXMediaUIPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kXMLExportOptionsPanelCreatorImpl,	kXMediaUIPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kXMLExportImagesPanelCreatorImpl,	kXMediaUIPrefix + 205)

// CJK Options
DECLARE_PMID(kImplementationIDSpace, kExportCJKOptionControllerImpl,		kXMediaUIPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kXMLExportCJKOptionPanelCreatorImpl,	kXMediaUIPrefix + 207)


// Menu (continued...)
DECLARE_PMID(kImplementationIDSpace, kReplaceElementMenuActionImpl,		kXMediaUIPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kReplaceElementDynamicMenuImpl,	kXMediaUIPrefix + 211)
// gap

DECLARE_PMID(kImplementationIDSpace, kMappingDialogSingleClickEHImpl,	kXMediaUIPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kMappingInLineEditEventMonitorEHImpl,	kXMediaUIPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kStructureSelTrackerTableCSBImpl,	kXMediaUIPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kClickableStaticMultiLineTextHandCursorProviderImpl,	kXMediaUIPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationErrorFlagsImpl,	kXMediaUIPrefix + 219)


// Comment and PI dialogs
DECLARE_PMID(kImplementationIDSpace, kSetPIDlgControllerImpl,			kXMediaUIPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kSetCommentDlgControllerImpl,		kXMediaUIPrefix + 221)


// View Doctype dialog
DECLARE_PMID(kImplementationIDSpace, kViewDocTypeControllerImpl,		kXMediaUIPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kTreeDirtyImpl,					kXMediaUIPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kCXMLPanelCommandMgrObserverImpl,	kXMediaUIPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kDeferredNotifyStartupServiceImpl,	kXMediaUIPrefix + 227)

// SaveTagList dialog
DECLARE_PMID(kImplementationIDSpace, kSaveTagListDialogImpl,			kXMediaUIPrefix + 228)

DECLARE_PMID(kImplementationIDSpace, kXMLStructureSelectionFactoryImpl,	kXMediaUIPrefix + 229)

DECLARE_PMID(kImplementationIDSpace, kXMLDEHHelperProviderImpl,			kXMediaUIPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kXMLDEHDefaultHelperImpl,			kXMediaUIPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kStructureDataExchHandlerSnippetHelperImpl, kXMediaUIPrefix + 232)

// ---- Moved from XML plug-in
DECLARE_PMID(kImplementationIDSpace, kXMLTestMenuImpl,					kXMediaUIPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kConcreteXMLStructSelectionImpl,	kXMediaUIPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kScrapSuiteStructureCSBImpl, 		kXMediaUIPrefix + 235)
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kXMLPreferencesDialogControllerImpl,	kXMediaUIPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kXMLPreferencesDialogObserverImpl,		kXMediaUIPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kAutoTagButtonObserverImpl,			kXMediaUIPrefix + 238)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix + 239)

// XML Import UI
DECLARE_PMID(kImplementationIDSpace, kXMLImportUIServiceProviderImpl,			kXMediaUIPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kXMLImportUIDefaultServiceProviderImpl,	kXMediaUIPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsDialogImpl,				kXMediaUIPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsDialogObserverImpl,		kXMediaUIPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsUIMapperImpl,				kXMediaUIPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kXMLImportUIServiceSecondProviderImpl,		kXMediaUIPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kXMLImportUISecondServiceProviderImpl,		kXMediaUIPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kShowTagOptionsCmdImpl,					kXMediaUIPrefix + 247)

DECLARE_PMID(kImplementationIDSpace, kSnippetTestMenuImpl, 						kXMediaUIPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kFileNameWidgetControllerImpl, 			kXMediaUIPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kFileNameWidgetObserverImpl,				kXMediaUIPrefix + 250)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleConditionsDialogServiceImpl,		kXMediaUIPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleActionsDialogServiceImpl,			kXMediaUIPrefix + 253)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix + 254)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix + 255)

//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	XMediaUIPrefix2 + 1)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 2)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 3)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 4)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 5)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 6)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 7)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 8)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 9)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 10)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 11)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 12)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 13)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 14)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 15)
//gap
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 25)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 26)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 27)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 28)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 29)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 30)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 31)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 32)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewBoss, kXMediaUIPrefix2 + 33)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 34)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 35)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 36)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 37)
//MapTags to style error dialog
DECLARE_PMID(kImplementationIDSpace, kMapTagsToStyleErrorDialogControllerImpl,		kXMediaUIPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kMapTagsToStyleErrorDialogObserverImpl,		kXMediaUIPrefix2 + 39)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 40)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 41)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kXMediaUIPrefix2 + 42)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 43)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 44)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 45)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,	kXMediaUIPrefix2 + 46)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

// XML Panel
DECLARE_PMID(kWidgetIDSpace,	kXMLPanelWidgetID,					kXMediaUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,	kXMLTreeWidgetID,					kXMediaUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,	kXMLNewElementButtonWidgetID,		kXMediaUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,	kXMLDeleteButtonWidgetID,			kXMediaUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNodeWidgetId,				kXMediaUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,	kStructureNodeWidgetId,				kXMediaUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,	kStructureTextContentNodeWidgetId,	kXMediaUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,	kXMLNewAttributeButtonWidgetID,		kXMediaUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,	kXMLStructureMenuButtonWidgetID,	kXMediaUIPrefix + 9)
// gap

// Tag Panel
DECLARE_PMID(kWidgetIDSpace,	kTagPanelWidgetID,					kXMediaUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,	kTagListWidgetID,					kXMediaUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace,	kTagOptionsDialogId,				kXMediaUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,	kTagNameStaticWidgetID,				kXMediaUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,	kTagNameWidgetID,					kXMediaUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,	kNewTagButtonWidgetID,				kXMediaUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagButtonWidgetID,			kXMediaUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,	kTagPanelNodeWidgetId,				kXMediaUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagDialogId,					kXMediaUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagPopupWidgetID,			kXMediaUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagStaticWidgetID,			kXMediaUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagWarningIconWidgetId,		kXMediaUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,	kTagPanelSmallNodeWidgetId,			kXMediaUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace,	kTagClusterWidgetID,				kXMediaUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,	kAddTagRadioButtonWidgetID,			kXMediaUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,	kRetagRadioButtonWidgetID,			kXMediaUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace,	kTagListBorderWidgetID,				kXMediaUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace,	kUntagButtonWidgetID,				kXMediaUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace,	kTagColorSwatchWidgetID,			kXMediaUIPrefix + 29)

// Tree
DECLARE_PMID(kWidgetIDSpace,	kBranchIconWidgetId,				kXMediaUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace,	kTOLabelPanelWidgetID,				kXMediaUIPrefix + 31) 
DECLARE_PMID(kWidgetIDSpace,	kTreeNodeDropDownWidgetID,			kXMediaUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace,	kTextSnippetWidgetID,				kXMediaUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace,	kTreeNodeImageIconWidgetID,			kXMediaUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace,	kIconStaticTextWidgetID,			kXMediaUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace,	kTagNodeLockedWidgetId,				kXMediaUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace,	kTreePanelWidgetID,					kXMediaUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace,	kTOControlsPanelWidgetID,			kXMediaUIPrefix + 38) 
DECLARE_PMID(kWidgetIDSpace,	kTOButtonsPanelWidgetID,			kXMediaUIPrefix + 39) 

DECLARE_PMID(kWidgetIDSpace,	kXMLControlStripWidgetId,					kXMediaUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace,	kTagColorStaticWidgetID,					kXMediaUIPrefix + 41)
// gap
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingIncludeOptionsWidgetID,		kXMediaUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingIncludeOptionsLabelWidgetID,	kXMediaUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingMasterStoriesWidgetID,			kXMediaUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingPasteboardStoriesWidgetID,		kXMediaUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingEmptyStoriesWidgetID,			kXMediaUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace,	kTagToStyleMappingDialogWidgetID,	kXMediaUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace,	kTagToStyleMappingPanelID,			kXMediaUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace,	kTagMappingListPanelWidgetID,		kXMediaUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace,	kTagMappingListWidgetID,			kXMediaUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace,	kStyleToTagMappingDialogWidgetID,	kXMediaUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace,	kStyleToTagMappingPanelID,			kXMediaUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingListPanelWidgetID,		kXMediaUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace,	kStyleMappingListWidgetID,			kXMediaUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace,	kLoadMappingButtonWidgetID,			kXMediaUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace,	kXMLTagsTextWidgetID,				kXMediaUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace,	kXMLStylesTextWidgetID,				kXMediaUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace,	kMapByNameButtonWidgetID,			kXMediaUIPrefix + 61)

DECLARE_PMID(kWidgetIDSpace,	kSplitterTitleOuterWidgetID,		kXMediaUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace,	kSplitterTitleInnerInnerWidgetID,			kXMediaUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace,	kLeftSplitterPanelWidgetID,	kXMediaUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace,	kRightSplitterPanelWidgetID,			kXMediaUIPrefix + 65)

DECLARE_PMID(kWidgetIDSpace,	kTagToStyleMappingListItemWidgetID,			kXMediaUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace,	kStyleToTagMappingListItemWidgetID,			kXMediaUIPrefix + 67)

DECLARE_PMID(kWidgetIDSpace,	kChooseTagDialogWidgetID,			kXMediaUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace,	kXMLTagPopupWidgetID,				kXMediaUIPrefix + 69)

DECLARE_PMID(kWidgetIDSpace,	kSetAttributeDialogID,				kXMediaUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNameStaticWidgetID,		kXMediaUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNameWidgetID,				kXMediaUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace,	kAttributeValueStaticWidgetID,		kXMediaUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace,	kAttributeValueWidgetID,			kXMediaUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace,	kXMediaUISplitterWidgetID,			kXMediaUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace,	kExportXMLOptionsDialogID,			kXMediaUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace,	kDOCTYPECaptionStaticWidgetID,		kXMediaUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace,	kReplaceSpecialCharactersCheckBoxID,kXMediaUIPrefix + 78)
//DECLARE_PMID(kWidgetIDSpace,	kCommentsScrollWidgetID,			kXMediaUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace,	kViewXMLCheckBoxID,					kXMediaUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace,	kExportFromSelectedCheckBoxID,		kXMediaUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace,	kUTFStaticWidgetID,					kXMediaUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace,	kXMLEncodingDropDownListID,			kXMediaUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace,	kUTF8RadioButtonWidgetID,			kXMediaUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace,	kUTF16RadioButtonWidgetID,			kXMediaUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace,	kDeleteTagStaticTagNameWidgetID,	kXMediaUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace,	kViewXMLDropDownListID,				kXMediaUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace,	kTagColorDropDownWidgetID,			kXMediaUIPrefix + 88)
//DECLARE_PMID(kWidgetIDSpace,	kChangeTagColorSwatchWidgetID,		kXMediaUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace,	kCorrnerSpacerWidgetID,			kXMediaUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace,	kSTTInfoIconWidgetID,						kXMediaUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace,	kSTTInfoTextWidgetID,						kXMediaUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace,	kInCopyStoryNodeWidgetID,			kXMediaUIPrefix + 93)

DECLARE_PMID(kWidgetIDSpace,	kStyleNodeNameWidgetID,			kXMediaUIPrefix + 94)
// gap
DECLARE_PMID(kWidgetIDSpace,	kDTDCaptionStaticWidgetID,	kXMediaUIPrefix + 97)

DECLARE_PMID(kWidgetIDSpace,	kMappingSplitterWidgetID,	kXMediaUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace,	kLinkMappingSplitterWidgetID,	kXMediaUIPrefix + 99)

// Validation Pane
DECLARE_PMID(kWidgetIDSpace,	kStructureViewSplitterWidgetID,			kXMediaUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace,	kTreeViewSubPanelWidgetID,				kXMediaUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace,	kValidationSubPanelWidgetID,			kXMediaUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace,	kValidateControlStripWidgetId,			kXMediaUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace,	kXMLValidateStructureButtonWidgetID,	kXMediaUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace,	kXMLCloseValidationButtonWidgetID,		kXMediaUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace,	kXMLNavigateLeftButtonWidgetID,			kXMediaUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace,	kXMLNavigateRightButtonWidgetID,		kXMediaUIPrefix + 107)
// gap
DECLARE_PMID(kWidgetIDSpace,	kValidationLabelStaticWidgetID,			kXMediaUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace,	kXMLValidationInfoWidgetID,				kXMediaUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace,	kXMLValidationScrollBarWidgetID,		kXMediaUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace,	kValidationPositionEditBoxWidgetID,		kXMediaUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace,	kXMLNavigateFirstButtonWidgetID,		kXMediaUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace,	kXMLNavigateLastButtonWidgetID,			kXMediaUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace,	kXMLViewErrorsDialogButtonWidgetID,		kXMediaUIPrefix + 115)
// gap

// Processing Instruction dialog
DECLARE_PMID(kWidgetIDSpace,	kSetPIDialogID,							kXMediaUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace,	kPITargetWidgetID,						kXMediaUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace,	kPIValueWidgetID,						kXMediaUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace,	kPITargetStaticWidgetID,				kXMediaUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace,	kPIValueStaticWidgetID,					kXMediaUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace,	kPIValueScrollWidgetID,					kXMediaUIPrefix + 125)
// gap

// Comment dialog
DECLARE_PMID(kWidgetIDSpace,	kSetCommentDialogID,					kXMediaUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace,	kCommentValueWidgetID,					kXMediaUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace,	kCommentValueStaticWidgetID,			kXMediaUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace,	kCommentValueScrollWidgetID,			kXMediaUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace,	kViewDocTypeDialogID,					kXMediaUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace,	kDocTypeTextWidgetID,					kXMediaUIPrefix + 135)
// gap

// Errors List dialog
DECLARE_PMID(kWidgetIDSpace,	kViewErrorsListDialogID,				kXMediaUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace,	kErrorsListStaticWidgetID,				kXMediaUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace,	kErrorsListWidgetID,					kXMediaUIPrefix + 142)

// Extra Options Panel
DECLARE_PMID(kWidgetIDSpace,	kExportXMLCJKOptionsPanelID,			kXMediaUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace,	kTextOptionsFrameWidgetID,				kXMediaUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace,	kTextOptionsFrameTitleWidgetID,			kXMediaUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace,	kExportRubyAsXMLWidgetID,				kXMediaUIPrefix + 148)

DECLARE_PMID(kWidgetIDSpace,	kXMLPreferencesDialogWidgetID,			kXMediaUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace,	kXMLOptionsTagListColumnWidgetID,		kXMediaUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace,	kXMLOptionsNameListColumnWidgetID,			kXMediaUIPrefix + 157)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyWidgetID,		kXMediaUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace,	kXMLTagOptionsColumnWidgetID,			kXMediaUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace,	kXMLOptionsRowWidgetID,					kXMediaUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace,	kCellTagNameWidgetID,					kXMediaUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace,	kTableTagNameWidgetID,					kXMediaUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace,	kShowAgainCheckBoxWidgetID,				kXMediaUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace,	kStoryTagNameWidgetID,					kXMediaUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace,	kAutoTagButtonWidgetID,					kXMediaUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace,	kImageTagNameWidgetID,					kXMediaUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace,	kRowTagNameWidgetID,					kXMediaUIPrefix + 167)
// gap


// ---- Stylesheet dialog.
//
DECLARE_PMID(kWidgetIDSpace,	kStylesheetDialogWidgetID,				kXMediaUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace,	kXMediaSelectFileLabelWidgetID,				kXMediaUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace,	kXMediaSelectFileWidgetID,					kXMediaUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace,	kXMediaSelectFileIconWidgetID,				kXMediaUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace,	kParametersGroupWidgetID,				kXMediaUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace,	kParametersLabelWidgetID,				kXMediaUIPrefix + 175)
// gap

// ---- The followin widget IDs must be consecutive.
//
DECLARE_PMID(kWidgetIDSpace,	kParameter1NameWidgetID,				kXMediaUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace,	kParameter1ValueWidgetID,				kXMediaUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace,	kParameter2NameWidgetID,				kXMediaUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace,	kParameter2ValueWidgetID,				kXMediaUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace,	kParameter3NameWidgetID,				kXMediaUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace,	kParameter3ValueWidgetID,				kXMediaUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace,	kParameter4NameWidgetID,				kXMediaUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace,	kParameter4ValueWidgetID,				kXMediaUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace,	kParameter5NameWidgetID,				kXMediaUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace,	kParameter5ValueWidgetID,				kXMediaUIPrefix + 189)
#define kParameterLastNameWidgetID kParameter5NameWidgetID
#define kParameterLastValueWidgetID kParameter5ValueWidgetID
//
// ---- End of consecutive widtet IDs.

// Image Conversion
DECLARE_PMID(kWidgetIDSpace,	kExportXMLDialogID,						kXMediaUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace,	kLinkOptionsFrameWidgetID,				kXMediaUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace,	kLinkOptionsFrameTitleWidgetID,			kXMediaUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace,	kCopyOriginalsWidgetID,					kXMediaUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace,	kOptimizedOriginalsWidgetID,			kXMediaUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace,	kFormattedOriginalsWidgetID,			kXMediaUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace,	kImageConversionPopupWidgetID,			kXMediaUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace,	kImageConversionTitleWidgetID,			kXMediaUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace,	kGIFFrameWidgetID,						kXMediaUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace,	kGIFFrameTitleWidgetID,					kXMediaUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace,	kGIFPalettePopupWidgetID,				kXMediaUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace,	kGIFPaletteTitleWidgetID,				kXMediaUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace,	kGIFInterlaceWidgetID,					kXMediaUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace,	kJPEGFrameWidgetID,						kXMediaUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace,	kJPEGFrameTitleWidgetID,				kXMediaUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace,	kJPEGQualityPopupWidgetID,				kXMediaUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace,	kJPEGQualityTitleWidgetID,				kXMediaUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace,	kJPEGEncodingPopupWidgetID,				kXMediaUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace,	kJPEGEncodingTitleWidgetID,				kXMediaUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace,	kGeneralOptionsFrameWidgetID,			kXMediaUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace,	kGeneralOptionsTitleWidgetID,			kXMediaUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace,	kExportXMLLinksPanelID,					kXMediaUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace,	kExportXMLImagesPanelID,				kXMediaUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace,	kExportXMLGeneralPanelID,				kXMediaUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace,	kLinkToStaticTextWidgetID,				kXMediaUIPrefix + 224)
// gap

DECLARE_PMID(kWidgetIDSpace,	kXMLFileBrowseButtonWidgetID,			kXMediaUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace,	kXMLChooseFileGroupWidgetID,			kXMediaUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace,	kXMLChooseFileCheckBoxWidgetID,			kXMediaUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace,	kXMLChooseFileTextEditWidgetID,			kXMediaUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace,	kXMLChooseFileEveGroupWidgetID,			kXMediaUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace,	kIncludeDTDCheckBoxID,					kXMediaUIPrefix + 235)

// DeleteContentWarning Dialog
DECLARE_PMID(kWidgetIDSpace,	kDeleteContentDialogId,					kXMediaUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace,	kUntagButton_WidgetID,					kXMediaUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace,	kContentMessageStaticWidgetID,			kXMediaUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace,	kStyleSheetStaticWidgetID,				kXMediaUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace,	kStyleSheetWidgetID,					kXMediaUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace,	kDontShowDeleteContentCheckBoxWidgetID,	kXMediaUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace,	kIncludeUntaggedTablesCheckBoxID,		kXMediaUIPrefix + 242)
// gap
DECLARE_PMID(kWidgetIDSpace,	kDTDOptionsGroupLabelWidgetID,				kXMediaUIPrefix + 245)
DECLARE_PMID(kWidgetIDSpace,	kXMediaUIGenericWidget1WidgetID,			kXMediaUIPrefix + 246)
DECLARE_PMID(kWidgetIDSpace,	kXMediaUIGenericWidget2WidgetID,			kXMediaUIPrefix + 247)
DECLARE_PMID(kWidgetIDSpace,	kXMediaUIGenericWidget3WidgetID,			kXMediaUIPrefix + 248)
// gap

// XML Rules
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesPanelWidgetId,							kXMediaUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesTreeViewBorderWidgetId,				kXMediaUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesTreeViewWidgetId,						kXMediaUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace,	kXMLRuleSetNodeWidgetId,						kXMediaUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace,	kXMLRuleNodeWidgetId,							kXMediaUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace,	kXMLRuleSetIconWidgetId,						kXMediaUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesNodeNameWidgetId,						kXMediaUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesNodeDescriptionWidgetId,				kXMediaUIPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace,	kXMLRuleEnableWidgetId,							kXMediaUIPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace,	kXMLRuleIconWidgetId,							kXMediaUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesControlStripWidgetId,					kXMediaUIPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesApplyRuleButtonWidgetId,				kXMediaUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesApplyRuleSetButtonWidgetId,			kXMediaUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesNewButtonWidgetId,						kXMediaUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace,	kXMLRulesDeleteButtonWidgetId,					kXMediaUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsDialogWidgetID,						kXMediaUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace,	kRuleNameEditWidgetID, 							kXMediaUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace,	kRuleNameLabelWidgetID, 						kXMediaUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsSettingsPanelWidgetID, 				kXMediaUIPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsListLabelWidgetID, 					kXMediaUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsListTreeViewBorderWidgetId, 		kXMediaUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsNewButtonWidgetID, 					kXMediaUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsDeleteButtonWidgetID, 				kXMediaUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsGroupWidgetID, 						kXMediaUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsGroupLabelWidgetID, 				kXMediaUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsLabelWidgetID, 						kXMediaUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsDropDownWidgetID, 					kXMediaUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsPaneLabelWidgetID, 					kXMediaUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace,	kRuleDescriptionLabelWidgetID, 					kXMediaUIPrefix2 + 29)
DECLARE_PMID(kWidgetIDSpace,	kRuleDescriptionEditWidgetID, 					kXMediaUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsTypeGroupWidgetID, 					kXMediaUIPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsListTreeViewWidgetId, 				kXMediaUIPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsListNodeWidgetId, 					kXMediaUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsWidgetID, 							kXMediaUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsSelectableGroupWidgetID, 			kXMediaUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsMoveUpButtonWidgetID, 				kXMediaUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsMoveDownButtonWidgetID, 			kXMediaUIPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace,	kPreviousRuleButtonWidgetID, 					kXMediaUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace,	kNextRuleButtonWidgetID, 						kXMediaUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsConditionOperatorLabelWidgetID,		kXMediaUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsConditionOperatorDropDownWidgetID,	kXMediaUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsListInfoWidgetID,					kXMediaUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace,	kRuleOptionsAddUpdateButtonWidgetID,			kXMediaUIPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace,	kRuleSetNameEditWidgetID, 						kXMediaUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace,	kRuleSetNameLabelWidgetID, 						kXMediaUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace,	kRuleSetDescriptionEditWidgetID, 				kXMediaUIPrefix2 + 46)
DECLARE_PMID(kWidgetIDSpace,	kRuleSetDescriptionLabelWidgetID, 				kXMediaUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace,	kRuleSetOptionsDialogWidgetID,					kXMediaUIPrefix2 + 48)
// gap

// Rule Conditions and Actions
DECLARE_PMID(kWidgetIDSpace,	kApplyObjectStyleActionViewWidgetId,			kXMediaUIPrefix2 + 50)
DECLARE_PMID(kWidgetIDSpace,	kApplyStyleActionViewWidgetId,					kXMediaUIPrefix2 + 51)
DECLARE_PMID(kWidgetIDSpace,	kElementPropertiesConditionViewWidgetId,		kXMediaUIPrefix2 + 52)
//gap
DECLARE_PMID(kWidgetIDSpace,	kTagNameConditionViewWidgetId,					kXMediaUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace,	kXMLCharStyleDropDownWidgetID,					kXMediaUIPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace,	kXMLParaStyleDropDownWidgetID,					kXMediaUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace,	kXMLObjStyleDropDownWidgetID,					kXMediaUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace,	kXMLCharStyleEnabledWidgetId,					kXMediaUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace,	kXMLParaStyleEnabledWidgetId,					kXMediaUIPrefix2 + 59)

//Map tags to style error dialog
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogGroupWidgetId,		kXMediaUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogMultiLineStaticTextWidgetID,	kXMediaUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogScrollBarWidgetID,	kXMediaUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogWarningSignWidgetID,	kXMediaUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogWarningMsgWidgetID,	kXMediaUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogCheckBoxWidgetID,		kXMediaUIPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogWidgetID,				kXMediaUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace,	kMapTagsToStyleErrorDialogHilitePanelWidgetID,	kXMediaUIPrefix2 + 67)

DECLARE_PMID(kWidgetIDSpace,	kTagNameCheckBoxWidgetId,						kXMediaUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace,	kTagNameComparatorPopupWidgetId,				kXMediaUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace,	kPositionCheckBoxWidgetId,						kXMediaUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace,	kPositionComparatorPopupWidgetId,				kXMediaUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace,	kPositionPopupWidgetId,							kXMediaUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNameCheckBoxWidgetId,					kXMediaUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNameComparatorPopupWidgetId,			kXMediaUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace,	kAttributeNameEditWidgetId,						kXMediaUIPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace,	kAttributeValueCheckBoxWidgetId,				kXMediaUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace,	kAttributeValueComparatorPopupWidgetId,			kXMediaUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace,	kAttributeValueEditWidgetId,					kXMediaUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace,	kContentValueCheckBoxWidgetId,					kXMediaUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace,	kContentValueComparatorPopupWidgetId,			kXMediaUIPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace,	kContentValueEditWidgetId,						kXMediaUIPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace,	kCountStaticTextWidgetId,						kXMediaUIPrefix2 + 82)
DECLARE_PMID(kWidgetIDSpace,	kCountComparatorPopupWidgetId,					kXMediaUIPrefix2 + 83)
DECLARE_PMID(kWidgetIDSpace,	kCountEditWidgetId,								kXMediaUIPrefix2 + 84)
DECLARE_PMID(kWidgetIDSpace,	kElementPropertiesAxisPopupWidgetId,			kXMediaUIPrefix2 + 85)
DECLARE_PMID(kWidgetIDSpace,	kXMLCharStyleIconWidgetId,						kXMediaUIPrefix2 + 86)
DECLARE_PMID(kWidgetIDSpace,	kXMLParaStyleIconWidgetId,						kXMediaUIPrefix2 + 87)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,	kShowMapTagsToStyleErrorActionID,		kXMediaUIPrefix + 1)
// gap

// Tag Panel
DECLARE_PMID(kActionIDSpace,	kTagPanelActionID,				kXMediaUIPrefix + 11)
DECLARE_PMID(kActionIDSpace,	kTagNewActionID,				kXMediaUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,	kTagDuplicateActionID,			kXMediaUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,	kTagDeleteActionID,				kXMediaUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,	kTagOptionsActionID,			kXMediaUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,	kTagLoadActionID,				kXMediaUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,	kTagSaveActionID,				kXMediaUIPrefix + 17)
DECLARE_PMID(kActionIDSpace,	kTagSelectUnusedActionID,		kXMediaUIPrefix + 18)
DECLARE_PMID(kActionIDSpace,	kTagSmallRowsActionID,			kXMediaUIPrefix + 19)
DECLARE_PMID(kActionIDSpace,	kTagUntagActionID,				kXMediaUIPrefix + 20)
DECLARE_PMID(kActionIDSpace,	kTagSeparator1ActionID,			kXMediaUIPrefix + 21)
DECLARE_PMID(kActionIDSpace,	kTagSeparator2ActionID,			kXMediaUIPrefix + 22)
DECLARE_PMID(kActionIDSpace,	kTagSeparator3ActionID,			kXMediaUIPrefix + 23)
DECLARE_PMID(kActionIDSpace,	kTagSeparator4ActionID,			kXMediaUIPrefix + 24)
DECLARE_PMID(kActionIDSpace,	kTagSeparator5ActionID,			kXMediaUIPrefix + 25)
DECLARE_PMID(kActionIDSpace,	kTagSeparator6ActionID,			kXMediaUIPrefix + 26)

//Structure Menu
DECLARE_PMID(kActionIDSpace,	kStructureAddElementActionID, 			kXMediaUIPrefix + 31)
DECLARE_PMID(kActionIDSpace,	kStructureRemoveElementActionID, 		kXMediaUIPrefix + 32)
DECLARE_PMID(kActionIDSpace,	kStructureNewAttributeActionID, 		kXMediaUIPrefix + 33)
DECLARE_PMID(kActionIDSpace,	kStructureEditAttributeActionID, 		kXMediaUIPrefix + 34)
DECLARE_PMID(kActionIDSpace,	kStructureDeleteAttributeActionID, 		kXMediaUIPrefix + 35)
// gap
DECLARE_PMID(kActionIDSpace,	kStructureGoToItemActionID, 			kXMediaUIPrefix + 37)
DECLARE_PMID(kActionIDSpace,	kStructureShowAttributesActionID, 		kXMediaUIPrefix + 38)
DECLARE_PMID(kActionIDSpace,	kStructureShowTextSnippetsActionID, 	kXMediaUIPrefix + 39)
DECLARE_PMID(kActionIDSpace,	kStructureGeneratePDFStructureActionID,	kXMediaUIPrefix + 40)
DECLARE_PMID(kActionIDSpace,	kStructureMapTagsToStylesActionID,	 	kXMediaUIPrefix + 41)
DECLARE_PMID(kActionIDSpace,	kStructureShowTagMarkersActionID,		kXMediaUIPrefix + 42)
DECLARE_PMID(kActionIDSpace,	kStructureMapStylesToTagsActionID,	 	kXMediaUIPrefix + 43)
DECLARE_PMID(kActionIDSpace,	kSelectInStructureActionID,				kXMediaUIPrefix + 44)
DECLARE_PMID(kActionIDSpace,	kStructureUntagActionID, 				kXMediaUIPrefix + 45)
DECLARE_PMID(kActionIDSpace,	kStructureShowTaggedFramesActionID,		kXMediaUIPrefix + 46)
DECLARE_PMID(kActionIDSpace,	kChooseTagDialogActionID,				kXMediaUIPrefix + 47)
DECLARE_PMID(kActionIDSpace,	kStructureNewCommentActionID,			kXMediaUIPrefix + 48)
DECLARE_PMID(kActionIDSpace,	kStructureNewPIActionID,				kXMediaUIPrefix + 49)
DECLARE_PMID(kActionIDSpace,	kStructureViewErrorsActionID,			kXMediaUIPrefix + 50)
DECLARE_PMID(kActionIDSpace,	kStructureViewDTDActionID,				kXMediaUIPrefix + 51)


DECLARE_PMID(kActionIDSpace,	kStructureSeparator1,				 	kXMediaUIPrefix + 52)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator2,				 	kXMediaUIPrefix + 53)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator3,				 	kXMediaUIPrefix + 54)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator4,				 	kXMediaUIPrefix + 55)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator5,				 	kXMediaUIPrefix + 56)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator6,				 	kXMediaUIPrefix + 57)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator7,				 	kXMediaUIPrefix + 58)
DECLARE_PMID(kActionIDSpace,	kStructureSeparator8,				 	kXMediaUIPrefix + 59)

// Other Menus	
DECLARE_PMID(kActionIDSpace,	kImportXMLActionID,					 	kXMediaUIPrefix + 60)
DECLARE_PMID(kActionIDSpace,	kOpenStructureWinActionID,				kXMediaUIPrefix + 61)

//Structure Navigation KBSC
DECLARE_PMID(kActionIDSpace,	kMoveXMLSelectionToNextNodeActionID,		kXMediaUIPrefix + 62)
DECLARE_PMID(kActionIDSpace,	kMoveXMLSelectionToPreviousNodeActionID,	kXMediaUIPrefix + 63)
DECLARE_PMID(kActionIDSpace,	kXMLAddNextNodeToSelectionActionID,			kXMediaUIPrefix + 64)
DECLARE_PMID(kActionIDSpace,	kXMLAddPreviousNodeToSelectionActionID,		kXMediaUIPrefix + 65)
DECLARE_PMID(kActionIDSpace,	kSelectFirstXMLNodeActionID,				kXMediaUIPrefix + 66)
DECLARE_PMID(kActionIDSpace,	kSelectLastXMLNodeActionID,					kXMediaUIPrefix + 67)
DECLARE_PMID(kActionIDSpace,	kStructurePageUpActionID,					kXMediaUIPrefix + 68)
DECLARE_PMID(kActionIDSpace,	kStructurePageDownActionID,					kXMediaUIPrefix + 69)
DECLARE_PMID(kActionIDSpace,	kStructureExpandElementActionID,			kXMediaUIPrefix + 70)
DECLARE_PMID(kActionIDSpace,	kStructureCollapseElementActionID,			kXMediaUIPrefix + 71)
DECLARE_PMID(kActionIDSpace,	kStructureExpandWithChildrenActionID,		kXMediaUIPrefix + 72)
DECLARE_PMID(kActionIDSpace,	kStructureCollapseWithChildrenActionID,		kXMediaUIPrefix + 73)
DECLARE_PMID(kActionIDSpace,	kStructureValidateElementActionID,			kXMediaUIPrefix + 74)
DECLARE_PMID(kActionIDSpace,	kXMLAddThroughFirstNodeToSelectionActionID,	kXMediaUIPrefix + 75)
DECLARE_PMID(kActionIDSpace,	kXMLAddThroughLastNodeToSelectionActionID,	kXMediaUIPrefix + 76)
DECLARE_PMID(kActionIDSpace,	kStructureDTDOptionsActionID,				kXMediaUIPrefix + 77)
DECLARE_PMID(kActionIDSpace,	kXMLValidateRootActionID,					kXMediaUIPrefix + 78)
DECLARE_PMID(kActionIDSpace,	kXMLShowNextErrorActionID,					kXMediaUIPrefix + 79)
DECLARE_PMID(kActionIDSpace,	kXMLShowPreviousErrorActionID,				kXMediaUIPrefix + 80)
DECLARE_PMID(kActionIDSpace,	kStructureViewPreviousValidationActionID,	kXMediaUIPrefix + 81)
DECLARE_PMID(kActionIDSpace,	kStructureViewNextValidationActionID,		kXMediaUIPrefix + 82)
DECLARE_PMID(kActionIDSpace,	kStructureViewDeleteTagActionID,	    	kXMediaUIPrefix + 83)
DECLARE_PMID(kActionIDSpace,	kExportXMLActionID,							kXMediaUIPrefix + 84)

// Tags in the Choose Tag menu
DECLARE_PMID(kActionIDSpace,	kChooseTagDynamicActionID,				kXMediaUIPrefix + 99)
// gap
// FOLLOWING SETS OF RANGES SHOULD BE EXACTLY 25 LONG
DECLARE_PMID(kActionIDSpace,	kBeginChooseTagPopupActionID,			kXMediaUIPrefix + 101)
// gap -- DON'T USE THIS RANGE
DECLARE_PMID(kActionIDSpace,	kLastChooseTagPopupActionID,			kXMediaUIPrefix + 125)
DECLARE_PMID(kActionIDSpace,	kBeginInsertParentTagPopupActionID,		kXMediaUIPrefix + 126)
// gap -- DON'T USE THIS RANGE
DECLARE_PMID(kActionIDSpace,	kLastInsertParentTagPopupActionID,		kXMediaUIPrefix + 150)
// insert child element menu
DECLARE_PMID(kActionIDSpace,	kInsertChildElementDynamicActionID,		kXMediaUIPrefix + 151)
DECLARE_PMID(kActionIDSpace,	kBeginInsertChildPopupActionID,			kXMediaUIPrefix + 152)
DECLARE_PMID(kActionIDSpace,	kLastInsertChildPopupActionID,			kXMediaUIPrefix + 153)
// insert sibling after element menu
DECLARE_PMID(kActionIDSpace,	kInsertSiblingAfterDynamicActionID,		kXMediaUIPrefix + 154)
DECLARE_PMID(kActionIDSpace,	kBeginInsertSiblingAfterPopupActionID,	kXMediaUIPrefix + 155)
// gap -- DON'T USE THIS RANGE
DECLARE_PMID(kActionIDSpace,	kLastInsertSiblingAfterPopupActionID,	kXMediaUIPrefix + 179)
// retag element menu
DECLARE_PMID(kActionIDSpace,	kReplaceElementDynamicActionID,			kXMediaUIPrefix + 180)
DECLARE_PMID(kActionIDSpace,	kBeginReplaceElementPopupActionID,		kXMediaUIPrefix + 181)
// gap -- DON'T USE THIS RANGE
DECLARE_PMID(kActionIDSpace,	kLastReplaceElementPopupActionID,		kXMediaUIPrefix + 205)
// gap

// More structure menus
DECLARE_PMID(kActionIDSpace,	kStructureDeleteActionID,				kXMediaUIPrefix + 210)
DECLARE_PMID(kActionIDSpace,	kStructureEditActionID,					kXMediaUIPrefix + 211)
DECLARE_PMID(kActionIDSpace,	kStructureImportDTDActionID,			kXMediaUIPrefix + 212)
DECLARE_PMID(kActionIDSpace,	kStructureDeleteDTDActionID,			kXMediaUIPrefix + 213)
DECLARE_PMID(kActionIDSpace,	kStructureShowCommentsActionID,			kXMediaUIPrefix + 214)
DECLARE_PMID(kActionIDSpace,	kStructureShowPIsActionID,				kXMediaUIPrefix + 215)
DECLARE_PMID(kActionIDSpace,	kStructureNewFlyoutActionID,			kXMediaUIPrefix + 216)
DECLARE_PMID(kActionIDSpace,	kStructureValidateRootActionID,			kXMediaUIPrefix + 217)
DECLARE_PMID(kActionIDSpace,	kStructureValidateSelectionActionID,	kXMediaUIPrefix + 218)
DECLARE_PMID(kActionIDSpace,	kChooseTagMenuActionID,					kXMediaUIPrefix + 219)
DECLARE_PMID(kActionIDSpace,	kStructureExportActionID,				kXMediaUIPrefix + 220)
DECLARE_PMID(kActionIDSpace,	kSetTaggingPresetsMenuActionID,			kXMediaUIPrefix + 221)
DECLARE_PMID(kActionIDSpace,	kStructureImportActionID,				kXMediaUIPrefix + 222)
DECLARE_PMID(kActionIDSpace,	kTagAutoTagActionID,					kXMediaUIPrefix + 223)
DECLARE_PMID(kActionIDSpace,	kInsertParentTagDynamicActionID,		kXMediaUIPrefix + 224)
DECLARE_PMID(kActionIDSpace,	kInsertParentTagMenuActionID,			kXMediaUIPrefix + 225)
DECLARE_PMID(kActionIDSpace,	kInsertParentTagDialogActionID,			kXMediaUIPrefix + 226)

DECLARE_PMID(kActionIDSpace,	kAddElementDynamicActionID,				kXMediaUIPrefix + 227)
DECLARE_PMID(kActionIDSpace,	kBeginAddElementPopupActionID,			kXMediaUIPrefix + 228)
// gap -- DON'T USE THIS RANGE
DECLARE_PMID(kActionIDSpace,	kLastAddElementPopupActionID,			kXMediaUIPrefix + 252)
DECLARE_PMID(kActionIDSpace,	kChooseTagFrameMenuActionID,			kXMediaUIPrefix + 253)
DECLARE_PMID(kActionIDSpace,	kChooseTagTextMenuActionID,				kXMediaUIPrefix + 254)
DECLARE_PMID(kActionIDSpace,	kAddElementMenuActionID,				kXMediaUIPrefix + 255)


//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

// XML Panel
DECLARE_PMID(kServiceIDSpace,	kStructureDDTargetFlavorHelperService,	kXMediaUIPrefix + 1)

// Mapping Dialog
DECLARE_PMID(kServiceIDSpace,	kXMLMappingDialogService,				kXMediaUIPrefix + 2)

DECLARE_PMID(kServiceIDSpace,	kTaggedFrameDrawServiceImpl,			kXMediaUIPrefix + 3)

// More XML panel stuff
DECLARE_PMID(kServiceIDSpace,	kXMLDataExchHandlerHelperService,		kXMediaUIPrefix + 4)

// XML Import Dialog 
DECLARE_PMID(kServiceIDSpace,	kXMLImportUIService,					kXMediaUIPrefix + 5)


// <Error ID>
//----------------------------------------------------------------------------------------
// Error Codes
//----------------------------------------------------------------------------------------
DECLARE_PMID(kErrorIDSpace, kXMLDragItemsAlreadyInStructureError,	kXMediaUIPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kUserCancelledError,					kXMediaUIPrefix + 2)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kXMediaUISuiteScriptElement,				kXMediaUIPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kXMLViewPrefsObjectScriptElement,			kXMediaUIPrefix + 10)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kXMLViewPrefsPropertyScriptElement,		kXMediaUIPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kShowStructurePropertyScriptElement,		kXMediaUIPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kShowTagMarkersPropertyScriptElement,		kXMediaUIPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kShowTaggedFramesPropertyScriptElement,	kXMediaUIPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kShowAttributesPropertyScriptElement,		kXMediaUIPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kShowTextSnippetsPropertyScriptElement,	kXMediaUIPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kXMLShowTagOptionsPropertyScriptElement,	kXMediaUIPrefix + 126)

//----------------------------------------------------------------------------------------
// Messages
//----------------------------------------------------------------------------------------


DECLARE_PMID(kMessageIDSpace, kMsgInitializeDialogFields, kXMediaUIPrefix + 1 ) /** Used in ExportXMLDialogController::InitializeDialogFields */
DECLARE_PMID(kMessageIDSpace, kMsgApplyDialogFields, kXMediaUIPrefix + 2 ) /** Used in ExportXMLDialogController::ApplyDialogFields */


//----------------------------------------------------------------------------------------
// Tree View Messages
//----------------------------------------------------------------------------------------
#define	kAddToSelectionTrackingMsg									kXMediaUIPrefix + 1
#define	kRemoveFromSelectionTrackingMsg								kXMediaUIPrefix + 2
#define	kUpdateTextSnippetMsg										kXMediaUIPrefix + 3
#define	kXMLValidationErrorsStateChangedMsg							kXMediaUIPrefix + 4
#define	kXMLValidationUserClickedMsg								kXMediaUIPrefix + 5
#define	kFileNameEnabledStateChangedMsg								kXMediaUIPrefix + 6
#define	kFileNameChangedMsg											kXMediaUIPrefix + 7

//----------------------------------------------------------------------------------------
// Don't Show Again Alert IDs
//----------------------------------------------------------------------------------------
#define	kGraphicToTextDragDropAlertID								kXMediaUIPrefix + 1
#define	kGraphicToTextButtonAlertID									kXMediaUIPrefix + 2
#define	kWarnOnDeleteAlertID										kXMediaUIPrefix + 3
#define kDeleteTagsAlertID											kXMediaUIPrefix  + 4
#define kTagGroupAlertID											kXMediaUIPrefix  + 5
#define kUntagChildrenAlertID											kXMediaUIPrefix  + 6
#define kUntagChildrenInStructureAlertID							kXMediaUIPrefix  + 7
#define kTagGuideAlertID											kXMediaUIPrefix  + 8
#define kTagLockedAlertID											kXMediaUIPrefix  + 9

// Used for cases where there is a dropdown that 
// can get filled to full if there are enough tags
const int32 kMaxItemsInDropDown = 1000;

// rgano: Desabling this option (with the choice to put it back later) 
// For right now we don't want this because dialog shows all options
// all of the time and this can be confusing. In the future we may make
// the dialog smart enough to only show the options that are currently
// applicable. In that case we would want the dialog back.
// #define kEnableShowTagOptionsDialog 1

#endif // __XMediaUIID__
