//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AdobeMenuPositions.h $
//  
//  Owner: lance bushore
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
//  This file contains positions for all the adobe menu items.
//  
//========================================================================================

#pragma once
#ifndef __AdobeMenuPositions__
#define __AdobeMenuPositions__

#pragma mark ___Main menu bar___
//main menu bar items
#define kAppleMenuPosition				10.0
#define kFileMenuPosition				20.0
#define kEditMenuPosition				30.0
#define kLayoutMenuPosition				40.0
#define kTypeMenuPosition				50.0
#define kNotesMenuPosition				55.0	// Top-level in InCopy, submenu in InDesign
#define kChangesMenuPosition	 		58.0
#define kObjectMenuPosition				60.0
#define kTableMenuPosition				70.0
// Unused #define kStructureMenuPosition		80.0
#define kViewMenuPosition				90.0
#define kPluginMenuPosition				100.0
#define kWindowMenuPosition				110.0
#define kScriptsMenuPosition			115.0
#define kHelpMenuPosition				120.0

#pragma mark ___Main menus___
// apple menu items
#ifdef MACINTOSH
#define kAboutShuksanMenuPosition		100.0
#define kPluginManagerMenuPosition		200.0
#define kExtensionManagerMenuPosition	250.0
#define kAboutPluginsMenuPosition		300.0
#define kSyncToCloudMenuPosition        350.0
#endif

// &File menu items
#define kNewMenuPosition					100.0
#define kOpenDocumentMenuPosition			200.0
#define kBrowseMenuPosition					250.0
#define kOpenRecentMenuPosition				300.0
#define kFileSeparator1MenuPosition			400.0
#define kCloseMenuPosition					500.0
#define kSaveMenuPosition					600.0
#define kSaveAsMenuPosition					700.0
#define kSaveVersionMenuPosition			820.0
#define kSaveCopyMenuPosition				840.0
#define kSaveAllMenuPosition				860.0
#define kRevertMenuPosition					900.0
#define kFileSeparator2MenuPosition			1000.0
#define kSearchAdobeStockMenuPosition		1050.0
#define kPlaceMenuPosition					1100.0
#define kPlaceFromCloudLibrariesMenuPosition	1110.0
#define kImportBuzzwordMenuPosition			1125.0
#define kImportXMLMenuPosition				1150.0
#define kImportPDFCommentsMenuPosition		1160.0
#define kImportPDFReviewMenuPosition		1175.0
#define kPlaceSepMenuPosition				1200.0
#define kPDFExportStyleMenuPosition			1300.0
#define kExportMenuPosition					1400.0
#define kLaunchSharesheetMenuPosition       1401.0
//#define kShareOnBehanceMenuPosition			1401.0
#define kPublishSepMenuPosition				1402.0
#define kPublishMenuPosition				1403.0
#define kRecentPublicationsMenuPosition		1404.0
#define kWebDashboardMenuPosition			1405.0
#define kExportBuzzwordMenuPosition			1410.0
#define kExportForMenuPosition				1425.0	
#define kExportCrossMediaSubMenuPosition	1450.0
#define kExportHTMLPreviewMenuPosition		1460.0
#define kExportSepMenuPosition				1500.0

// Good ole' InCopy stuff
#define kICBridgeEditInFileMenuPosition		(kExportSepMenuPosition + 10)
#define kICBridgeSubmitFileMenuPosition		(kExportSepMenuPosition + 20)
#define kICBridgeSubmitAllFileMenuPosition	(kExportSepMenuPosition + 30)

#define kICBridgeSeparatorRevertMenuPos		(kExportSepMenuPosition + 40)
#define kICBridgeRevertFileMenuPosition		(kExportSepMenuPosition + 50)

#define kICBridgeSeparatorFileMenuPosition	(kExportSepMenuPosition + 60)
#define kICBridgeUpdateStoryFileMenuPosition	(kExportSepMenuPosition + 70)
#define kUpdateDesignMenuPosition			(kExportSepMenuPosition + 80)
#define kFileSeparator3MenuPosition		(kExportSepMenuPosition + 90)
#define kICPackageMenuPosition			(kExportSepMenuPosition + 100)
#define kFileSeparator4MenuPosition		(kExportSepMenuPosition + 110)

#ifdef MACINTOSH
#define kPageSetupMenuPosition				1700.0
#endif
#define kDocStyleMenuPosition				1725.0
#define kDocSetupMenuPosition				1730.0
#define kAdjustLayoutMenuPosition			1740.0
#define kDocSetupSepMenuPosition			1750.0

#define kUserMenuPosition					1760.0

#define kFileInfoMenuPosition				1800.0
#define kVersionsMenuPosition				1805.0
#define kAlternatesMenuPosition				1806.0
#define kFileInfoSepMenuPosition			1810.0
#define kXPUIDocModeMenuPosition 			1825.0
#define kXPUIDocModeSepMenuPosition 		1826.0
#define kPreflightMenuPosition				1900.0
#define kPackageMenuPosition				2000.0
#define kPackageForWebMenuPosition			2050.0

// Placeholder for InBooklet (supplied by 3rd party)
#define kInBookletMenuPosition				2070.0

#define kPrinterStylesMenuPosition			2100.0
#define kPrintMenuPosition					2200.0
#define kPrintBookletMenuPosition			2250.0 //vsethi PR_BL
#define kPrintGridsMenuPosition				2300.0
#define kPrintSepMenuPosition				2400.0
#define kQuitMenuPosition					2500.0

// &Edit menu items
#define kUndoRedoDynamicMenuPosition			 90.0
#define kUndoMenuPosition						100.0
#define kRedoMenuPosition						200.0
#define kEditSeparator1MenuPosition				300.0
#define kCutMenuPosition						400.0
#define kCopyMenuPosition						500.0
#define kPasteMenuPosition						600.0
#define kPasteUnformatMenuPosition				620.0
#define kPasteIntoMenuPosition					650.0
#define kPasteInsideMenuPosition				700.0
#define kPasteUsingCJKGridComponentMenuPosition	750.0
#define kPasteWithoutCJKGridMenuPosition		775.0
#define kClearMenuPosition						800.0
#define kEditSeparator2MenuPosition				900.0
#define kApplyCJKGridMenuPostion				950.0
#define kDuplicateMenuPosition					1000.0
#define kStepRepeatMenuPosition					1100.0
#define kPlaceLinkStoryMenuPosition				1150.0
#define kStepRepeatSepMenuPosition				1200.0
#define kSelectAllMenuPosition					1300.0
#define kDeselectAllMenuPosition				1400.0
#define kEditSeparator3MenuPosition				1420.0

#define kInCopyBridgeMenuPosition				1450.0
#define kInCopyBridgeSeparatorPosition			1460.0

#define kEditOriginalCoreMenuPosition			1520.0
#define kEditOriginalWithCoreMenuPosition		1525.0
#define kGoToSourceCoreMenuPosition				1527.0
#define kOpenStoryEditorMenuPosition			1530.0
#define kOpenFastEditorMenuPosition             1533.0
#define kSearchSimilarMenuPosition				1535.0


#define kTransposeMenuSeparatorPosition			1550.0
#define kTransposeMenuPosition					1560.0
#define kSwapMacroTextMenuPosition				1565.0

#define kPositionMarkerSepMenuPosition			1570.0
#define kPositionMarkerMenuPosition				1575.0

#define kFindMenuSeparatorPosition				1590.0
#define kKillerFindMenuPosition					1595.0
#define kFindMenuPosition						1600.0
#define kFindNextMenuPosition					1700.0
#define kSpellingMenuPosition					1750.0
#define kThesaurusMenuPosition					1850.0
#define kEditSeparator4MenuPosition				1999.0
#define kXPUIBlendSpaceMenuPosition				2010.0
#define kXPUIFlattenStylesMenuPosition			2020.0
#define kXPUISeparatorMenuPosition				2099.0

#define kMigrateSettingsNowMenuPosition			2105.0
#define kSyncSettingsSep2MenuPosition			2106.0

#define kCMSUIColorSettingsMenuPosition			2110.0
#define kCMSUIAssignProfilesMenuPosition		2120.0
#define kCMSUIConvertToProfilesMenuPosition		2130.0
#define kCMSUISeparatorMenuPosition				2140.0
#define kContextObjectCMSMenuPosition			4700.0

#define kKBSCEditorMenuPosition					2150.0
#define kMenuCustomizationMenuPosition			2175.0
#ifdef WINDOWS
#define kSyncToCloudMenuPosition				2180.0
#endif
#define kPreferencesMenuPosition				2200.0

#define kSpellCheckMenuPosition					100.0		//Submenu items attached to Spelling
#define kDynamicSpellCheckMenuPosition			150.0		//Submenu items attached to Spelling
#define kAutoCorrectMenuPosition				200.0		//Submenu items attached to Spelling
#define kEditDictMenuPosition					250.0		//Submenu items attached to Spelling


// &Object menu items
#define kTransformMenuPosition			100.0
#define kTransformAgainMenuPosition		150.0
#define kArrangeMenuPosition			200.0
#define kSelectObjectMenuPosition		250.0
#define kAfterSelectObjectSepMenuPosition	300.0
#define kGroupMenuPosition				400.0
#define kUngroupMenuPosition			500.0
#define kLockMenuPosition				600.0
#define kUnlockMenuPosition				700.0
#define kUnlockAllOnSpreadMenuPosition	710.0
#define kHideMenuPosition				720.0
#define kShowAllOnSpreadMenuPosition	740.0
#define kLockSepMenuPosition			800.0

#define kInsertHTMLMenuPosition			810.0
#define kInsertHTMLSepMenuPosition		820.0

#define kCreateQRCodeMenuPosition		830.0
#define kCreateQRCodeSepMenuPosition	840.0

#define kFrameTypeMenuPosition			850.0
#define kFrameTypeSepMenuPostion		851.0
#define kFrameGridMenuPosition			899.0

#define kFrameOptionsMenuPosition		900.0
#define kAnchoredObjMenuPosition		950.0
#define kAnchoredObjSepMenuPosition		970.0

// These are a submenu
#define kAnchoredObjOptionsDlgMenuPosition	100.0
#define kAnchoredObjInsertDlgMenuPosition	200.0
#define kAnchoredObjReleaseDlgMenuPosition	300.0

#define kFittingMenuPosition			1000.0
#define kContentMenuPosition			1200.0
#define kLayoutPolicyMenuPosition		1225.0
#define kAddToContainerMenuPosition		1250.0

#define kConvertSepMenuPosition			1300.0
#define kXPUIMenuPos_ObjectEffects		1370.0
#define kCornerShapeMenuPosition		1400.0
//#define kXPUIEffectsMenuPosition		1450.0
#define kCornerShapeSepMenuPosition		1500.0

#define kImageLayerSettingMenuPosition		1600.0
#define kObjectExportOptionsMenuPosition	1625.0
#define kCaptionsSubmenuPosition			1650.0
#define kClippingPathMenuPosition			1700.0
#define kCMSUIImageSettingsMenuPosition		1800.0
#define kCMSUIImageSettingSepMenuPosition	1850.0

#define kInteractiveSettingsMenuPosition	1875.0
#define kMovieUIMovieSettingsMenuPosition	1876.0
#define kSoundUISoundSettingsMenuPosition	1877.0
#define kFormFieldSettingsMenuPosition		1878.0
#define kEBookSepMenuPosition				1879.0
#define kCreateButtonMenuPosition			1880.0
#define kCreateCheckBoxMenuPosition			1880.1
#define kCreateComboBoxMenuPosition			1880.2
#define kCreateListBoxMenuPosition			1880.3
#define kCreateRadioButtonMenuPosition		1880.4
#define kCreateSignatureFieldMenuPosition	1880.5
#define kCreateTextFieldMenuPosition		1880.6
#define kSepBeforeConvertMenuPosition		1880.7
#define kConvertToObjectMenuPosition		1880.8
#define kInteractiveAnimationUIConvertToMotionPathMenuPosition 1881.0
#define kSetTabOrderMenuPosition			1882.0

#define kCompoundPathsSepMenuPosition	1895.0
#define kCompoundPathsMenuPosition		1900.0
#define kPathsMenuPosition				1950.0
#define kPathFinderMenuPosition			2000.0
#define kConvertShapeMenuPosition		2050.0
#define kConvertPointMenuPosition		2075.0

// Clipping Path submenu
#define kClippingPathOptionsMenuPosition		100.0

// File:Cross Media export submenu
#define kExportToXMLMenuPosition		100.0

//Object:Captions submenu
#define kGenerateLinkCaptionPrefsMenuPosition		100.0
#define kGenerateLiveCaptionMenuPosition			200.0
#define kGenerateStaticCaptionMenuPosition		300.0
#define kConvertCaptionVariableToTextMenuPosition	400.0

//#define kObjectCMSSepMenuPosition		2100.0
#define kDisplayOverrideSepMenuPosition	2300.0
#define kDisplayOverrideMenuPosition	2400.0

// Frame Type menu items
#define kTextFrameTypeMenuPostion		100.0
#define kFrameGridTypeMenuPostion		200.0

// Structure menu items
#define kStructureAddElementMenuPosition			100.0
#define kStructureInsertParentMenuPosition			150.0
#define kStructureNewAttributeMenuPosition			200.0
#define kStructureNewCommentMenuPosition			300.0
#define kStructureNewPIMenuPosition					400.0
#define kStructureDeleteMenuPosition				500.0
#define kStructureEditMenuPosition					600.0
#define kStructureSeparator1MenuPosition			700.0
#define kStructureUntagMenuPosition					800.0
#define kStructureSeparator2MenuPosition			900.0
#define kStructureGoToItemMenuPosition				1000.0
#define kStructureSeparator3MenuPosition			1100.0
#define kStructureValidateRootMenuPosition			1200.0
#define kStructureValidateSelectionMenuPosition		1300.0
#define kStructureViewErrorsMenuPosition			1400.0
#define kStructureSeparator4MenuPosition			1500.0
#define kStructureImportDTDMenuPosition				1600.0
#define kStructureDeleteDTDMenuPosition				1700.0
#define kStructureDTDOptionsMenuPosition			1800.0
#define kStructureViewDTDMenuPosition				1900.0
#define kStructureSeparator5MenuPosition			2000.0
#define kStructureImportXMLMenuPosition				2100.0
#define kStructureExportXMLMenuPosition				2200.0
#define kStructureSeparator6MenuPosition			2300.0
#define kStructureShowAttributesMenuPosition		2400.0
#define kStructureShowCommentsMenuPosition			2500.0
#define kStructureShowPIsMenuPosition				2600.0
#define kStructureShowTextSnippetsMenuPosition		2700.0
#define kStructureSeparator7MenuPosition			2800.0
#define kStructureGeneratePDFStructureMenuPosition	2900.0
#define kStructureSeparator8MenuPosition			3000.0
#define kStructureMapTagsToStylesMenuPosition		3100.0
#define kStructureMapStylesToTagsMenuPosition		3200.0
#define kStructureSetTaggingPresetsMenuPosition		3300.0
#define kStructureChooseTagDialogMenuPosition		3400.0


// Table menu items
#define kInsertTableMenuPosition		100.0
#define kConvertTextToTableMenuPosition	200.0
#define kConvertTableToTextMenuPosition	300.0
#define kTableSeparator1MenuPosition	400.0

#define kTablesUITableStyleMenuPosition		425.0
#define kTablesUINewStyleMenuPos			430.0
#define kTablesUIApplyStyleMenuPos			435.0
#define kTablesUIApplyTableStyleS0MenuPos	440.0
#define kTablesUIApplyTableStyleS1MenuPos	440.1
#define kTablesUIApplyTableStyleS2MenuPos	440.2
#define kTablesUIApplyTableStyleS3MenuPos	440.3
#define kTablesUIApplyTableStyleS4MenuPos	440.4

#define kTablesUIPropMenuPostion		500.0
#define kTablesUIPropSetupMenuPostion				510.0
#define kTablesUIPropAltRowStrokesMenuPostion		520.0
#define kTablesUIPropAltColumnStrokesMenuPostion	525.0
#define kTablesUIPropAltFillPostion					530.0
#define kTablesUIPropHeaderFooterPostion			540.0
#define kTablesUICellPropMenuPostion		550.0
#define kTablesUIPropTextMenuPostion			560.0
#define kTablesUIPropGraphicMenuPostion			565.0
#define kTablesUIPropStrokesFillsMenuPostion	570.0
#define kTablesUIPropRowsColsMenuPostion		580.0
#define kTablesUIPropDiagLinesMenuPostion		590.0
#define kTableSeparator2MenuPosition	595.0
#define kTablesInsertMenuPostion		600.0
#define kTablesInsertRowMenuPostion			 610.0
#define kTablesInsertColMenuPostion			 620.0
#define kTablesDeleteMenuPostion		700.0
#define kTablesDeleteRowMenuPostion			 710.0
#define kTablesDeleteColMenuPostion			 720.0
#define kTablesDeleteTableMenuPostion		 730.0
#define kTablesSelectMenuPostion		800.0
#define kTablesSelectCellMenuPostion		 810.0
#define kTablesSelectRowMenuPostion			 820.0
#define kTablesSelectColMenuPostion			 830.0
#define kTablesSelectTableMenuPostion		 840.0
#define kTablesSelectSepMenuPosition	 	 850.0
#define kTablesSelectHeaderRowsMenuPosition	 860.0
#define kTablesSelectBodyRowsMenuPosition	 870.0
#define kTablesSelectFooterRowsMenuPosition	 880.0
#define kTableSeparator3MenuPosition	900.0
//#define kTableSeparator0MenuPosition	930.0
#define kMergeCellsMenuPosition			1000.0
#define kUnmergeCellsMenuPosition		1050.0
#define kSplitCellHorizontallyActionMenuPosition	1100.0
#define kSplitCellVerticallyActionMenuPosition		1200.0
#define kTablesMenuPasteBeforeMenuPosition	1210.0
#define kTablesMenuPasteAfterMenuPosition	1220.0
#define kConvertToGraphicCellActionMenuPosition		1230.0
#define kConvertToTextCellActionMenuPosition		1240.0
#define kConvertRowsActionMenuPosition	1250.0
#define kTableSeparator4MenuPosition	1300.0
#define kRedistributeRowsMenuPosition	1400.0
#define kRedistributeColsMenuPosition	1500.0
#define kTableSeparator5MenuPosition	1600.0
#define kTableGoToRowMenuPosition		1700.0
#define kEditHeaderMenuPosition			1710.0
#define kEditFooterMenuPosition			1720.0
//#define kTableSeparator6MenuPosition	1800.0
#define kTableHeaderMenuPosition		100.0	// these 3 are now in their own submenu
#define kTableBodyMenuPosition			200.0
#define kTableFooterMenuPosition		300.0

// &Layout menu items
#define kPageGridMenuPosition				100.0
#define kLayoutPagesMenuPosition			110.0

// Pages submenu
#define kAddPageMenuPosition				100.0
#define kInsertPagesMenuPosition			200.0
#define kMovePagesMenuPosition				300.0
#define kDuplicateSpreadMenuPosition		400.0
#define kDeleteSpreadMenuPosition			500.0
#define kDeleteSpreadSepMenuPosition		600.0
#define kPrintPagesLayoutMenuPosition		630.0
#define kRotateSpreadSepMenuPosition		700.0
#define kApplyMasterLayoutMenuPosition		800.0

// Page transitions menus on main:layout
#define kLayoutAddPageTransitionSepMenuPosition		900.0
#define kLayoutAddPageTransitionMenuPosition		950.0
#define kLayoutChoosePageTransitionMenuPosition		1000.0
#define kLayoutEditPageTransitionMenuPosition		1100.0
#define kLayoutPageTransitionSep1MenuPosition		1150.0
#define kLayoutClearAllPageTransitionMenuPosition	1200.0

// SWFPreviewPanelPopup menu
#define kSWFPreviewSelectionMenuPosition			100.0
#define kSWFPreviewSpreadMenuPosition				200.0
#define kSWFPreviewDocumentMenuPosition				300.0
#define kSWFPreviewSepMenuPosition					400.0
#define kSWFPreviewSaveSettingsMenuPosition			500.0
#define kSWFTestInBrowserMenuPosition				600.0

// HTMLPreviewPanelPopup menu
#define kHTMLTestInBrowserMenuPosition				100.0

// LiquidLayoutPanelPopup menu
#define kLayoutAdjustmentMenuPosition				100.0

// TimingPanelPopup menu
#define kTimingPanelReassignPageLoadMenuPosition	100.0
#define kTimingPanelReassignPageClickMenuPosition	200.0
#define kTimingPanelRemoveItemMenuPosition			300.0
#define kTimingPanelSepMenuPosition					400.0
#define kTimingPanelPreviewHTMLFXLMenuPosition      450.0
#define kTimingPanelPreviewSpreadMenuPosition		500.0

// AnimationPanelPopup menu
#define kAnimationUISavePresetMenuPosition			100.0
#define kAnimationUISaveAsPresetMenuPosition		200.0
#define kAnimationUIDeletePresetMenuPosition		300.0
#define kAnimationUILoadPresetMenuPosition			400.0
#define kAnimationUIManagePresetMenuPosition		450.0
#define kAnimationUISepMenuPosition					500.0
#define kAnimationUIPreviewHTMLFXLMenuPosition		550.0
#define kAnimationUIPreviewSelectionMenuPosition	600.0	
#define kAnimationUIPreviewSpreadMenuPosition		700.0
#define kAnimationUIConvertToMotionPathMenuPosition	800.0	

#define kAnimationUIOnPageLoadEventMenuPosition		100.0
#define kAnimationUIOnPageClickEventMenuPosition	200.0
#define kAnimationUIOnClickSelfEventMenuPosition	300.0
#define kAnimationUIOnRollOverSelfEventMenuPosition	400.0
#define kAnimationUISepEventMenuPosition			500.0
#define kAnimationUIOnButtonEventMenuPosition		600.0

// Rotate Spread submenu
#define kRotateSpreadBy90CWMenuPosition		100.0
#define kRotateSpreadBy90CCWMenuPosition	200.0
#define kRotateSpreadBy180MenuPosition		300.0
#define kRotateSpreadBySepMenuPosition	400.0
#define kRotateSpreadTo0MenuPosition	500.0

// page transition menus on pages panel
#define kChoosePageTransitionMenuPosition	100.0
#define kEditPageTransitionMenuPosition		200.0
#define kPageTransitionSep2MenuPosition		300.0
#define kClearAllPageTransitionMenuPosition	400.0

// page color flags submenu
#define kPageColorLabelNoneMenuPosition		10.0
#define kPageColorLabelMasterMenuPosition	20.0
#define kPageColorLabelSep1MenuPosition		30.0
#define kPageColorLabelFirstColor			100.0

// page view pages submenu
#define kPagesPanelViewPagesHorizontallyMenuPosition	100.0
#define kPagesPanelViewPagesVerticallyMenuPosition		200.0
#define kPagesPanelViewPagesByAlternateLayoutMenuPosition	300.0

// &Layout continues...
#define kLayoutPagesSepMenuPosition			120.0
#define kColumnsMarginsMenuPosition			130.0
#define kGuideOptionsMenuPosition			150.0
#define kGuideMgrMenuPosition				200.0
#define kCreateAlternateLayoutSepMenuPosition	250.0
#define kCreateAlternateLayoutMenuPosition	300.0
#define kLiquidLayoutMenuPosition			350.0
#define kLiquidLayoutSepMenuPosition		400.0
#define kFirstPageMenuPosition				500.0
#define kPrevPageMenuPosition				600.0
#define kNextPageMenuPosition				700.0
#define kLastPageMenuPosition				800.0
#define kNextSpreadMenuPosition				900.0
#define kPreviousSpreadMenuPosition			950.0
#define kPageNumSepMenuPosition				1000.0
#define kGotoPageDialogMenuPosition			1100.0
#define kSpreadHistorySepMenuPosition		1200.0
#define kSpreadHistGoBackMenuPosition		1300.0
#define kSpreadHistGoForwardMenuPosition	1400.0
#define kNumAndSectionSepMenuPosition		1500.0
#define kPageNumMenuPosition				1525.0
#define kNumAndSectionMenuPosition			1550.0
#define kTOCSepMenuPosition					1600.0
#define kCreateTOCMenuPosition				1700.0
#define kUpdateTOCMenuPosition				1800.0
#define kTOCForamtMenuPosition				1900.0
#define kAutoflowSeparatorPosition			2000.0
#define kAutoflowNewPagesMenuPosition		2100.0

// &Layout Document Status menu items
#define kDocStatusVersionsMenuPosition			100.0
#define kDocStatusSeparator1MenuPosition		200.0
#define kDocStatusCustomMenuPosition			300.0
#define kDocStatusLockForMeMenuPosition			400.0
#define kDocStatusRevertMenuPosition			500.0
#define kDocStatusSeparator2MenuPosition		600.0
#define kDocStatusRevealInOSMenuPosition		700.0
#define kDocStatusRevealInBrowserMenuPosition	800.0

//	Layout Document window preflight popup menu items
#define kPreflightUIStatusMenuOpenPanelMenuPosition			100.0
#define kPreflightUIStatusMenuProfileMenuPosition			200.0
#define kPreflightUIStatusMenuSeparatorMenuPosition			300.0
#define kPreflightUIStatusMenuDocPreflightOnOffMenuPosition	400.0
#define kPreflightUIStatusMenuDisableAllMenuPosition		500.0

// &Type menu items
#define kFontSearchMenuPosition                  90.0
#define kFontMenuPosition						100.0
#define kFontSizeMenuPosition					200.0
#define kTypeSizeSepMenuPosition				240.0

#define kWritingDirectionMenuPosition			249.0
#define kWritingDirectionSepMenuPosition		250.0

#define kTypeCharacterMenuPosition				251.0
#define kTypeParagraphMenuPosition				252.0
#define kTypeTabsMenuPosition					253.0
#define kTypeGlyphsMenuPosition					254.0
#define kTypeStoryMenuPosition					255.0

#define kTypeCharStylesSepMenuPosition			256.0
#define kTypeCharStylesMenuPosition				257.0
#define kTypeParaStylesMenuPosition				258.0
#define kNamedGridsPanelMenuPosition			259.0  // J menu
#define kTypeParaStylesSepMenuPosition			260.0

#define kCompFontDialogMenuPosition				400.0
#define kKinsokuDlgMenuMenuPosition				450.0
#define kMojiKumiDlgMenuMenuPosition			500.0

#define kCompFontSepMenuPosition				550.0

#define kCreateOutlineMenuPosition				900.0

#define kFindFontMenuPosition					1000.0
#define kChangeCaseMenuPosition					1100.0
#define kChangeCaseSepMenuPosition				1200.0

#define kTOPMenuPosition						1300.0
#define kTOPSepMenuPosition						1400.0

#define kNotesSubmenuPosition					1410.0	// Top-level in InCopy, submenu in InDesign
#define kChangesSubmenuPosition					1414.0	// Top-level in InCopy, submenu in InDesign
#define kChangesSubmenuSepMenuPosition			1415.0
#define kSpecialFootnoteMenuPosition			1420.0
#define kFootnoteSettingsMenuPosition			1430.0
#define kSpecialEndnoteMenuPosition			    1440.0
#define kEndnoteSettingsMenuPosition			1450.0
#define kFootnoteSepMenuPosition				1470.0

#define kTVSepAMenuPosition						1480.0
#define kXRefMenuPosition						1482.0
#define kTVMenuPosition							1485.0
#define kTVSepBMenuPosition						1490.0
// Advanced Numbering
#define kBulletedNumberedTypeMenuPosition		1495.0
#define kTVSepCMenuPosition						1497.0

#define kInsertCharacterMenuPosition			1500.0
#define kInsertSpecialCharMenuPosition          1520.0
#define kInsertWhiteSpaceMenuPosition			1530.0
#define kInsertBreakCharMenuPosition			1540.0
#define kFillFrameMenuPosition					1550.0

#define kShowHiddenSepMenuPosition				1800.0
#define kShowHiddenCharsMenuPosition			1850.0
#define kToggleStylePreviewModeMenuPosition		1855.0

#define kApplyOpenTypeMenuPosition				1900.0

// Text Variables Sub-Menu
#define kTVDefinePosition							100.0
#define kTVInsertMenuPosition					200.0
#define kTVCTTMenuPosition						300.0



// &Window menu items
#define kWindowArrangeMenuPosition				100.0
#define kWorkspaceMenuPosition					500.0
#define kAddonsMenuPosition						550.0
#define kWindowCommentsMenuPosition				600.0

// #define kWindowSeparator1MenuPosition			200.0
#define kWindowFirstPanelMenuPosition			600.0
#define kWindowLastPanelMenuPosition			3700.0

#define kExtensionsDefaultMenuPosition			100.0	// always use the same position in order to get alphabetical behavior

#define kOWLAppPrefsSeparatorMenuPosition		3710.0	// Mac only
#define kOWLToggleAppFrameMenuPosition			3720.0	// Mac only
#define kOWLToggleAppBarMenuPosition			3730.0	// Mac only

#define kWindowSeparator2MenuPosition			3800.0
#define kBookMenuPosition						3900.0
#define kWindowSeparator3MenuPosition			4000.0
#define kLibMenuPosition						4100.0
#define kWindowSeparator4MenuPosition			4200.0
#define kJobBagMenuPosition						4300.0
#define kOpenWindowsSeperatorMenuPosition		4400.0

// workspace menu positions
#define kUserWorkspaceBaseMenuPosition			100.0
#define kWorkspaceSeperator1MenuPosition		200.0
#define kDefaultWorkspaceBaseMenuPosition		300.0
#define kWorkspaceSeperator2MenuPosition		400.0
#define kResetActiveWorkspacePosition			500.0
#define kSaveWorkspacePosition					600.0
#define kDeleteWorkspacePosition				700.0
#define kWorkspaceSeperator3MenuPosition		800.0
#define kShowFullMenusMenuPosition			900.0

// &View menu items

#define kLayoutEnableGPUMenuPosition            50.0
#define kOverprintPreviewMenuPosition			100.0
#define kOPPSeparatorMenuPosition				200.0
#define kProofSetupMenuPosition					300.0
#define kProofColorsMenuPosition				400.0
#define kProofSeparatorMenuPosition				500.0
#define kZoomInMenuPosition						600.0
#define kZoomOutMenuPosition					700.0
#define kFitPageMenuPosition					800.0
#define kFitSpreadMenuPosition					900.0
#define kActualSizeMenuPosition					1000.0
#define kEntirePasteboardMenuPosition			1100.0
#define kZoomSepMenuPosition					1110.0
#define kMatchPasteboardToThemeMenuPosition		1115.0
#define kZoomSep2MenuPosition					1118.0

#define kGalleyViewMenuPosition					1120.0
#define kStoryEditorViewMenuPosition			1130.0
#define kLayoutViewMenuPosition					1140.0
#define kGalleySeparatorPosition1				1150.0

#define kViewRotateSpreadMenuPosition			1190.0
#define kViewRotateSpreadSepMenuPosition		1195.0

#define kScreenViewMenuPosition					1200.0
#define kDisplayPerformanceMenuPosition			1225.0
#define kScreenViewSepMenuPosition				1250.0

#define kExpandStoryMenuPosition				1260.0
#define kExpandAllStoriesMenuPosition			1270.0
#define kCollapseAllStoriesMenuPosition			1280.0
#define kGalleySeparatorPosition2				1290.0

// Screen View submenu
#define kLayoutViewModeMenuPosition				100
#define kPreviewModeMenuPosition				200
#define kPreviewToBleedModeMenuPosition			300
#define kPreviewToSlugModeMenuPosition			400
#define kPresentationSepMenuPosition			500.0
#define kPresentationMenuPosition				600.0


#define kOptimizedMenuPosition					100.0	// These are on their own now
#define kTypicalMenuPosition					200.0
#define kHighQualityMenuPosition				300.0
#define kDisplaySepMenuPosition					400.0
#define kDisplaySep2MenuPosition                490.0
#define kDisplayIgnoreMenuPosition				500.0
#define kDisplayClearDocOverridesMenuPosition	600.0
#define kDisplayInterruptMenuPosition           700.0

#define kShowStructureMenuPosition				100.0	// These are on their own now
#define kStructureShowTagMarkersMenuPosition	200.0
#define kStructureShowTaggedFramesMenuPosition	300.0

#define kShowRulersMenuPosition					2400.0
#define kShowGuideSepMenuPosition				2500.0
#define kExtrasMenuPosition						2550.0	// Submenu
#define kGridsAndGuidesMenuPosition				2600.0	// Submenu

// These are a submenu now
#define kShowGuidesMenuPosition					100.0
#define kLockGuidesMenuPosition					200.0
#define kLockColumnGuidesMenuPosition			300.0
#define kSnapToGuidesMenuPosition				400.0
#define kShowSmartGuidesMenuPosition			425.0
#define kGuidesBackMenuPosition					430.0
#define kDeleteAllGuidesMenuPosition			450.0
#define kShowGridSepMenuPosition				500.0
#define kShowBaselineGridMenuPosition			600.0
#define kShowDocGridMenuPosition				700.0
#define kSnapDocGridMenuPosition				800.0
#define kGridsBackMenuPosition					900.0
#define kLayoutGridSepMenuPosition				1000.0
#define kShowPageGridMenuPosition				1100.0
#define kSnapPageGridMenuPosition				1200.0
#define kShowCharCountSepMenuPosition			1300.0
#define kShowCharCountMenuPosition				1400.0
#define ShowFrameGridMenuPosition				1500.0

// Extras Submenu
#define kShowFrameEdgesMenuPosition				100.0
#define kShowTextThreadsMenuPosition			200.0
#define kShowAssignedFramesMenuPosition			300.0
#define kExtrasSep1MenuPosition					400.0
#define kShowHyperlinksMenuPosition				500.0
#define kIDShowNotesSeparatorPosition			600.0
#define kShowLinkedStoryStatusMenuPosition			650.0
#define kExtrasSep2MenuPosition					700.0
#define kToggleContentGrabberMenuPosition		800.0
#define kToggleLiveCornersMenuPosition			900.0
#define kToggleAnchorAdornmentMenuPosition		1000.0
#define kToggleRibbonMenuPosition				1100.0
#define kToggleStockPurchaseAdornmentMenuPosition	1200.0

#define kGalleySeparatorPosition3				3500.0
#define kStructureMenuPosition					3525.0
#define kStoryEditorMenuPosition				3550.0

//Story Editor submenu
#define kShowChangesIDMenuPosition				80.0
#define kShowChangesIDSeparatorPosition			90.0
#define kShowInfoColumnSubMenuPosition			100.0
#define kShowDepthRulerSubMenuPosition			200.0
#define kShowParagraphsSubMenuPosition			250.0
#define kStoryEditorSubMenuSeparatorPosition1	290.0
#define kCollapseAllFootnotesSubMenuPosition	300.0

#define kShowInfoColumnMenuPosition				3600.0
#define kShowLineNumbersMenuPosition			3700.0
#define kShowStylesMenuPosition					3800.0
#define kShowDepthRulerMenuPosition				3840.0
#define kShowParagraphsMenuPosition				3860.0
#define kShowNotesSeparatorPosition				3900.0
#define kShowNotesMenuPosition					4000.0
#define kShowChangesSeparatorPosition			4100.0
#define kShowChangesMenuPosition				4200.0

// Help menu items
#define kHelpTopicsMenuPosition						100.0
#define kHelpOnlineSupportMenuPosition				125.0
#define kHelpUserVoiceMenuPosition					150.0
#define kHelpCopyEditorFeedbackMenuPosition       	160.0
#define kHelpInDesignForumPosition                  175.0
#define kHelpSepMenuPosition						200.0

#ifdef WINDOWS
#define kAboutShuksanMenuPosition					300.0
#define kAboutPluginsMenuPosition					400.0
#define kPluginManagerMenuPosition					500.0
#define kExtensionManagerMenuPosition				550.0
#endif

#define kOnlineSep1MenuPosition						600.0
#define kAdobeOnlineMenuPosition					700.0
#define kOnlineSep2MenuPosition						800.0
#define kTopIssuesMenuPosition						900.0
#define kDownloadablesMenuPosition					1000.0
#define kCorpNewsMenuPosition						1100.0
#define kOnlineRegMenuPosition						1200.0
#define kAdobeLinksMenuPosition						1300.0
#define kInDesignLinksMenuPosition					1400.0
#define kNglUISep1MenuPosition					1500.0
#define kNglUISep2MenuPosition					1600.0
#define kNglUIInDesignOnlineMenuPosition		1800.0
#define kNglUISep3MenuPosition					1900.0
#define kNglUIReportABugMenuPosition			2000.0

// Managed Workflow menu
#define kCheckoutMenuPosition					100.0
#define kCheckinMenuPosition					200.0
#define kUndoCheckoutMenuPosition				300.0
#define kUpdateFromServerMenuPosition			600.0
#define kUpdateToServerMenuPosition				700.0
#define kManagedWorkFlowSep1MenuPosition		800.0
#define kUpdateDesignFromServerMenuPosition		900.0
#define kManagedWorkFlowSep2MenuPosition		1000.0
#define kAddToWorkflowMenuPosition				1100.0

#define kWFWorkflowSep0MenuPostion             2000.0
#define kWFOpenFromWorkflowMenuPosition        2100.0
#define kWFWorkflowSep1MenuPostion             2200.0
#define kWFCheckOutMenuPosition                2300.0
#define kWFCheckInMenuPosition                 2400.0
#define kWFCancelCheckOutMenuPosition          2500.0
#define kWFSaveToWorkflowMenuPostion           2600.0
#define kWFSaveAsToWorkflowMenuPosition        2700.0
#define kWFUpdateMenuPosition                  2800.0
#define kWFRevertMenuPosition                  2900.0
#define kWFWorkflowSep2MenuPosition            3000.0
#define kWFPlaceMenuPosition                   3100.0
#define kWFWorkflowSep3MenuPosition            3200.0
#define kWFVerifyStateMenuPosition             3300.0
#define kWFWorkflowSep4MenuPosition            3400.0
#define kWFLogoffAllServersMenuPosition        3500.0
#define kWFWorkOfflineMenuPosition             3600.0
#define kWFWorkflowSep5MenuPosition            3700.0
#define kWFWorkflowServersMenuPosition         3800.0

#pragma mark ___Right mouse menus___
// ZeroPoint menu items
#define kLockZeroMenuPosition							100.0
#define kZeroPointSep1MenuPosition						200.0
// Starting at 500, dynamic position for installed measurement systems.
#define kInitialContextMeasurementPosition				500.0
#define kZeroPointSep2MenuPosition						2990.0
#define kZeroPointShowRulersMenuPosition				3000.0

// RtMouse menu items.  These items are at the top of each menu
#define kContextCutMenuPosition						100.0
#define kContextCopyMenuPosition					200.0
#define kContextPasteMenuPosition					300.0
#define kContextPasteUnformatMenuPosition			350.0
#define kContextPasteIntoMenuPosition				400.0
#define kContextPasteIntoAtPointMenuPosition		450.0
#define kContextPasteInsideMenuPosition				500.0
#define kContextSearchAdobeStockSepMenuPosition		525.0
#define kContextSearchAdobeStockMenuPosition		550.0
#define kContextCopySepMenuPosition					600.0

// RtMouseText menu items
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.
#define kContextFontMenuPosition					1100.0
#define kContextSizeMenuPosition					1200.0
#define kContextClearOverridesMenuPosition			1210.0
#define kContextRestartNumberingMenuPosition		1220.0
#define kContextConvertBulletNumMenuPosition		1230.0
#define kContextTypeSepMenuPosition					1300.0

#define kContextTextWritingDirectionMenuPosition	1400.0	// J menu
#define kContextTextWritingDirSepMenuPosition		1500.0  // J menu

#define kContextFindMenuPosition					1600.0
#define kGlyphFindRtMousePosition					1610.0
#define kGlyphChangeRtMousePosition					1620.0
#define kMacSpotlightMenuPosition					1650.0
#define kContextSpellcheckMenuPosition				1700.0
#define kContextDynamicSpellcheckMenuPosition		1750.0
#define kContextSpellSepMenuPosition				1800.0

#define kContextUpdateTOCMenuPosition				1900.0
#define kContextTOCFormatMenuPosition				2000.0
#define kContextTOCSep1MenuPosition					2100.0

#define kContextFrameGridMenuPosition				2200.0  // J menu
#define kContextFrameOptionsMenuPosition			2300.0
#define kContextAnchoredObjMenuPosition				2350.0
#define kContextFrameOptionsSepMenuPosition			2400.0

#define kContextChangeCaseMenuPosition				2420.0
#define kContextTextShowInvisMenuPosition			2440.0
#define kContextShowInvisSepMenuPosition			2460.0

#define kContextTOPMenuPosition						2500.0
#define kContextCreateOutlinesMenuPosition			2600.0
#define kContextOutlinesSepMenuPosition				2700.0

#define kCJKContextTCYOnOffMenuPosition				2800.0  // J menu
#define kCJKContextWarichuMenuPosition				2900.0  // J menu
#define kCJKContextRubySubMenuPosition				3000.0  // J menu
#define kCJKContextRubyNoneMenuPosition				3010.0  // J menu
#define kCJKContextRubySeparatorMenuPosition		3020.0  // J menu
#define kCJKContextRubyPositionMenuPosition			3030.0  // J menu
#define kCJKContextRubyFontMenuPosition				3040.0  // J menu
#define kCJKContextRubyParentMenuPosition			3050.0  // J menu
#define kCJKContextRubyColorMenuPosition			3060.0  // J menu
#define kCJKContextKentenSubMenuPosition			3100.0  // J menu
#define kCJKContextKentenNoneMenuPosition			3105.0  // J menu
#define kCJKContextKentenSeparator1MenuPosition		3110.0  // J menu
#define kCJKContextKenten_1MenuPosition				3115.0  // J menu
#define kCJKContextKenten_2MenuPosition				3120.0  // J menu
#define kCJKContextKenten_3MenuPosition				3125.0  // J menu
#define kCJKContextKenten_4MenuPosition				3130.0  // J menu
#define kCJKContextKenten_5MenuPosition				3135.0  // J menu
#define kCJKContextKenten_6MenuPosition				3140.0  // J menu
#define kCJKContextKenten_7MenuPosition				3145.0  // J menu
#define kCJKContextKenten_8MenuPosition				3150.0  // J menu
#define kCJKContextKenten_9MenuPosition				3155.0  // J menu
#define kCJKContextKenten10MenuPosition				3160.0  // J menu
#define kCJKContextKentenCustomMenuPosition			3165.0  // J menu
#define kCJKContextKentenSeparator2MenuPosition		3170.0  // J menu
#define kCJKContextKentenSettingsMenuPosition		3175.0  // J menu
#define kCJKContextKentenColorMenuPosition			3180.0  // J menu
#define kCJKContextShataiMenuPosition				3200.0  // J menu
#define kCJKContextSepMenuPosition					3300.0  // J menu

#define kContextInsertFootnoteMenuPosition			3550.0
#define kContextGotoFootnoteMenuPosition			3555.0
#define kContextCollapseAllFootnotesMenuPosition	3560.0
#define kContextInsertEndnoteMenuPosition			3565.0
#define kContextGotoEndnoteMenuPosition				3567.0
#define kContextEndnoteSettingsMenuPosition			3569.0
#define kContextFootnoteSepMenuPosition				3570.0

#define kContextTVSepAMenuPosition					3582.0
#define kContextTVInsertMenuPosition				3584.0
#define kContextTVCTTMenuPosition					3586.0
#define kContextConvertCaptionVariableMenuPosition	3588.0
#define kContextTVSepCMenuPosition					3589.0

#define kContextSpecialCharMenuPosition				3600.0
#define kContextWhiteSpaceMenuPosition				3700.0
#define kContextInsertBreakMenuPosition				3800.0

#define kContextFillFrameMenuPosition				3900.0

#define kContextInsertSepMenuPosition				4000.0

#define kContextTextInsertContextMenuPostion			4200.0
#define kContextTextDeleteContextMenuPostion		4300.0
#define kContextTextSelectContextMenuPostion			4400.0

#define kContextTextEditHeaderMenuPostion			4410.0
#define kContextTextEditFooterMenuPostion			4420.0
#define kContextTextHeaderFooterSepPosition			4430.0

#define kContextTagTextSepMenuPosition				4500.0
#define kContextTagTextMenuPosition					4600.0
#define kContextUntagTextMenuPosition				4700.0
#define kContextAutoTagTextMenuPosition				4705.0
#define kContextSelectInStructureTextMenuPosition	4707.0

#define kContextTextInteractiveSepMenuPosition		4710.0
#define	kContextTextHyperlinkGroupMenuPosition		4713.0
#define kContextTextInteractiveMenuPosition			4715.0

#define kContextTextOpenStoryEditorSepMenuPosition  4725.0
#define kContextTextOpenStoryEditorMenuPosition		4750.0
#define kContextTextOpenFastEditorMenuPosition      4760.0

#define	kContextTextHyperlinkNewHLMenuPosition		100.0
#define kContextTextHyperlinkAutoHLMenuPosition		200.0
#define	kContextTextHyperlinkEditHLMenuPosition		300.0
#define	kContextTextHyperlinkSep1MenuPosition		400.0
#define	kContextTextHyperlinkGotoDestMenuPosition	500.0
#define kContextTextHyperlinkNewDestMenuPosition	600.0
#define	kContextTextHyperlinkEditDestsMenuPosition	700.0
#define	kContextTextHyperlinkSep2MenuPosition		800.0
#define	kContextTextHyperlinkNewBkmkMenuPosition	900.0

#define kContextTextInCopyGroupSepMenuPosition		5000.0
#define	kContextTextInCopyGroupMenuPosition			5100.0
#define	kContextTextInCopyExportSubMenuPosition		5150.0
#define	kContextTextInCopyExportMenuPosition		100.0
#define kContextTextInCopySaveVerMenuPosition		200.0
#define kContextTextInCopySaveSepMenuPosition		300.0
#define kContextTextInCopyEditMenuPosition			400.0
#define	kContextTextInCopySubmitMenuPosition		500.0
#define	kContextTextInCopyRevertMenuPosition		600.0
#define	kContextTextInCopyUnembedMenuPosition	700.0
#define kContextTextInCopyUpdateStoryMenuPosition	800.0

#define	kContextTextInICEditMenuPosition			5200.0
#define	kContextTextInICSaveVerMenuPosition			5220.0
#define	kContextTextInICSubmitMenuPosition			5240.0
#define	kContextTextInICRevertMenuPosition			5260.0
#define	kContextTextInICRelinkMenuPosition			5280.0

// Story editor table text context items try to get them near the bottom
#define kContextMenuTableGalleyTableSepPosition		9060.0
#define kContextTextArrangeByRowsPosition			9061.0
#define kContextTextArrangeByColumnsPosition		9062.0

// RtMouseLayout menu items
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.
#define kContextZoomGroupPosition					1100.0
#define kContextZoomInMenuPosition					100.0  // Sub menu
#define kContextZoomOutMenuPosition					200.0  // Sub menu
#define kContextActualSizeMenuPosition				300.0  // Sub menu
#define kContextEntirePasteboardMenuPosition		400.0  // Sub menu
#define kContextFitSelectionMenuPosition			500.0  // Sub menu
#define kContextViewSepMenuPosition					1200.0


#define kContextLayoutFrameGridMenuPosition			1300.0  // J menu
#define kContextLayoutFrameOptionsMenuPosition		1400.0
#define kContextLayoutAnchoredObjMenuPosition		1450.0
#define kContextLayoutFrameTypeMenuPosition			1500.0  // J menu
#define kContextLayoutFillFrameMenuPosition			1600.0
#define kContextLayoutEditStoryMenuPosition			1650.0
#define kContextLayoutFastEditMenuPosition          1660.0
#define kContextLayoutConvertBNSepMenuPosition		1670.0
#define kContextLayoutConvertBulletNumMenuPosition	1680.0
#define kContextTextFrameSepMenuPosition			1700.0

#define kContextGridViewMenuPosition				1800.0  // J menu
#define kContextZNViewMenuPosition					1900.0  // J menu
#define kContextGridAndZNViewMenuPosition			2000.0  // J menu
#define kContextAlignmentViewMenuPosition			2100.0  // J menu
#define kContextFrameSettingsSepMenuPosition		2200.0  // J menu

#define kContextTransformMenuPosition				2300.0
#define kContextTransformAgainMenuPosition			2350.0
#define kContextArrangeMenuPosition					2400.0
#define kContextSelectMenuPosition					2450.0
#define kContextSelectObjectSepMenuPosition			2500.0

#define kContextGroupMenuPosition					2600.0
#define kContextUngroupMenuPosition					2700.0
#define kContextLockPosMenuPosition					2800.0
#define kContextUnLockPosMenuPosition				2900.0
#define kContextHideMenuPosition					2910.0
#define kContextShowAllOnSpreadMenuPosition			2920.0
#define kContextAllowOverridesMenuPosition			2930.0
#define kContextPrimaryTextFrameMenuPosition		2950.0
#define kContextGroupLockSepMenuPosition			3000.0

#define kContextBaselineGridMenuPosition			3100.0
#define kContextDocGridMenuPosition					3200.0
#define kContextGuidesBackMenuPosition				3300.0
#define kContextGridsBackMenuPosition				3400.0
#define kContextLockSepMenuPosition					3500.0

#define kContextStrokeMenuPosition					3600.0
#define kContextStrokeSepMenuPosition				3700.0

#define kContextFittingMenuPosition					3800.0
#define kContextContentMenuPosition					3900.0
#define kContextLayoutPolicyMenuPosition			3925.0
#define kContextAddToContainerMenuPosition			3950.0
#define kContextContentsSepMenuPosition				4000.0

#define kContextXPUIMenuPos_DropShadow				4100.0
#define kContextXPUIMenuPos_Vignette				4200.0
#define kContextTransparencySepMenuPosition			4300.0

#define kContextLayoutUpdateTOCMenuPosition			4400.0
#define kContextCreateTOCMenuPosition				4500.0
#define kContextTOCSepMenuPosition					4600.0

#define kContextObjectImageLayerMenuPosition		4650.0
#define kContextClipToFrameMenuPosition				4700.0
#define kContextGraphicMenuPosition					4800.0
#define kGraphicCaptionsSubmenuPosition				4825.0
#define kContextEditHTMLMenuPosition				4840.0
#define kContextEditOriginalMenuPosition			4850.0
#define kContextEditOriginalWithMenuPosition		4875.0
#define kContextGoToSourceMenuPosition				4880.0
#define kContextSearchSimilarMenuPosition			4885.0
#define kContextGraphicSepMenuPosition				4900.0

#define kContextInteractiveGroupMenuPosition				4950.0
#define kContextInteractiveMovieSettingsMenuPosition		5.0
#define kContextInteractiveSoundSettingsMenuPosition		10.0
#define kContextInteractiveFormFieldSettingsMenuPosition	15.0
#define kContextInteractiveCreateButtonMenuPosition			20.0

#define kContextInteractiveCreateCheckBoxMenuPosition			20.1
#define kContextInteractiveCreateComboBoxMenuPosition			20.2
#define kContextInteractiveCreateListBoxMenuPosition			20.3
#define kContextInteractiveCreateRadioButtonMenuPosition		20.4
#define kContextInteractiveCreateSignatureFieldMenuPosition		20.5
#define kContextInteractiveCreateTextFieldMenuPosition			20.6
#define kContextInteractiveSepBefConvertMenuPosition			20.7
#define kContextInteractiveConvertToObjectMenuPosition			20.8

#define kContextInteractiveAnimationUIConvertToMotionPathMenuPosition	22.0	
#define kContextInteractiveSep1MenuPosition					25.0
#define kContextInteractiveNewHyperlinkMenuPosition			30.0
#define kContextInteractiveNewXRefMenuPosition				32.0
#define kContextInteractiveNewDestinationMenuPosition		35.0
#define kContextInteractiveSep2MenuPosition					40.0
#define kContextInteractiveNewBookmarkMenuPosition			45.0

#define kContextGeneratedGraphicMenuPosition		4960.0

#define kContextEBookSepMenuPosition				4975.0


#define kContextSelectInStructureMenuPosition		5000.0
#define kContextTagFrameMenuPosition				5100.0
#define kContextUntagFrameMenuPosition				5200.0
#define kContextAutoTagLayoutMenuPosition			5250.0
#define kContextTagFrameSepMenuPosition				5300.0

#define kContextDisplayMenuPosition					5400.0
#define kContextOptimizedMenuPosition				100.0
#define kContextTypicalMenuPosition					200.0
#define kContextHighQualityMenuPosition				300.0
#define kContextDisplaySep1MenuPosition				400.0
#define kContextLayoutEnableGPUMenuPosition         450.0
#define kContextDisplaySep4MenuPosition             490.0
#define kContextIgnoreDocOverridesMenuPosition		500.0
#define kContextInterruptDrawMenuPosition           510.0
#define kContextClearDocOverridesMenuPosition		600.0
#define kContextOptimizedOverrideMenuPosition		700.0
#define kContextTypicalOverrideMenuPosition			800.0
#define kContextHighResOverrideMenuPosition			900.0
#define kContextDisplaySep2MenuPosition				1000.0
#define kContextClearOverrideMenuPosition			1100.0
#define kContextDisplaySep3MenuPosition				5500.0

#define kContextLayoutHLGroupSepMenuPosition			5600.0
#define	kContextLayoutHyperlinkGroupMenuPosition		4940.0
#define	kContextLayoutHyperlinkNewHLMenuPosition		100.0
#define	kContextLayoutHyperlinkEditHLMenuPosition		200.0
#define	kContextLayoutHyperlinkGotoDestMenuPosition		300.0
#define	kContextLayoutHyperlinkSep1MenuPosition			400.0
#define kContextLayoutHyperlinkNewDestMenuPosition		500.0
#define	kContextLayoutHyperlinkEditDestsMenuPosition	600.0
#define	kContextLayoutHyperlinkSep2MenuPosition			700.0
#define	kContextLayoutHyperlinkNewBkmkMenuPosition		800.0

// Menus in layout context menu in InDesign (the InCopy submenu)
#define kContextLayoutInCopyGroupSepMenuPosition		5800.0
#define	kContextLayoutInCopyGroupMenuPosition			5900.0
#define	kContextLayoutInCopyExportSubMenuPosition		5950.0
#define	kContextLayoutInCopyExportMenuPosition			100.0
#define kContextLayoutInCopySaveVerMenuPosition		200.0
#define kContextLayoutInCopySaveSepMenuPosition		300.0
#define kContextLayoutInCopyEditMenuPosition				400.0
#define	kContextLayoutInCopySubmitMenuPosition			500.0
#define	kContextLayoutInCopyRevertMenuPosition			600.0
#define	kContextLayoutInCopyUnembedMenuPosition		700.0
#define kContextLayoutInCopyUpdateStoryMenuPosition		800.0

// Menus in layout context menu in InCopy
#define kContextLayoutICGroupSepMenuPosition			5600.0
#define kContextLayoutICEditMenuPosition				5610.0
#define kContextLayoutICSubmitMenuPosition				5620.0
#define kContextLayoutICRevertMenuPosition				5630.0
#define kContextLayoutICUnembedMenuPosition				5640.0
#define kContextLayoutICSaveVerMenuPosition				5650.0
#define kContextLayoutICUpdateStoryMenuPosition			5660.0


// Right mouse Table menu
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.
#define kTablesUIOptionsContextMenuPostion					1100.0
#define kTablesUIOptionsSetupContextMenuPostion				100.0
#define kTablesUIOptionsAltRowStrokeContextMenuPostion		200.0
#define kTablesUIOptionsAltColumnStrokeContextMenuPostion	300.0
#define kTablesUIOptionsAltFillContextMenuPostion			400.0
#define kTablesUIOptionsHeaderFooterContextMenuPostion			400.0
#define kTablesUICellOptionsContextMenuPostion				1200.0
#define kTablesUIOptionsTextContextMenuPostion				100.0
#define kTablesUIOptionsGraphicContextMenuPostion			110.0
#define kTablesUIOptionsStrkFllContextMenuPostion			200.0
#define kTablesUIOptionsRowColContextMenuPostion			300.0
#define kTablesUIOptionsDiagLinesContextMenuPostion			400.0
#define kTablesUIContextMenuOptionsSepPosition				1300.0

#define kTablesUIInsertContextMenuPostion					1400.0
#define kTablesUIInsertRowContextMenuPostion				100.0
#define kTablesUIInsertColContextMenuPostion				200.0
#define kTablesUIDeleteContextMenuPostion					1500.0
#define kTablesUIDeleteRowContextMenuPostion				100.0
#define kTablesUIDeleteColContextMenuPostion				200.0
#define kTablesUIDeleteTableContextMenuPostion				300.0
#define kTablesUISelectContextMenuPostion					1600.0
#define kTablesUISelectCellContextMenuPostion				100.0
#define kTablesUISelectRowContextMenuPostion				200.0
#define kTablesUISelectColContextMenuPostion				300.0
#define kTablesUISelectTableContextMenuPostion				400.0
#define kTablesUISelectSepContextMenuPostion				600.0
#define kTablesUISelectHeaderRowsContextMenuPostion			700.0
#define kTablesUISelectBodyRowsContextMenuPostion			800.0
#define kTablesUISelectFooterRowsContextMenuPostion			900.0

#define kTablesUIContextMenuSelectionSepPosition			1700.0

#define kMergeCellsContextMenuPosition						1800.0
#define kUnmergeCellsContextMenuPosition					1900.0
#define kSplitCellHorizontallyContextMenuPosition			2000.0
#define kSplitCellVerticallyContextMenuPosition				2100.0

#define kPasteBeforeContextMenuPosition						2103.0
#define kPasteAfterContextMenuPosition						2104.0

#define kConvertTographicCellContextMenuPosition			2105.0
#define kConvertToTextCellContextMenuPosition				2106.0
#define kTableHeaderContextMenuPosition						2110.0
#define kTableBodyContextMenuPosition						2120.0
#define kTableFooterContextMenuPosition						2130.0

#define kTableConvertToRowContextMenuPosition				2200.0
#define kTableContextMenuConvertToRowSepPosition			2250.0

#define kRedistributeRowsContextMenuPosition				2300.0
#define kRedistributeColsContextMenuPosition				2400.0

// lhorwitz: Cell and Table Style context menu items should go here in the id range. bfreeman 8/18/2006

#define kTablesContextTextWritingDirSepMenuPosition			2500.0  // J menu
#define kTablesContextTextWritingDirectionMenuPosition		2600.0	// J menu

#define kTablesUIContextMenuRotateSepPosition				2700.0
#define kTablesUIRotateContextMenuPostion					2800.0
#define kTablesUIRotate0ContextMenuPostion					100.0
#define kTablesUIRotate90ContextMenuPostion					200.0
#define kTablesUIRotate180ContextMenuPostion				300.0
#define kTablesUIRotate270ContextMenuPostion				400.0

#define kTablesConvertBNSepMenuPosition						2850.0
#define kTablesConvertBulletNumMenuPosition					2860.0

#define kTablesUIContextMenuRedistributeSepPosition			2900.0

#define kTableGoToRowContextMenuPosition					3000.0
#define kEditHeaderContextMenuPosition						3100.0
#define kEditFooterContextMenuPosition						3200.0

#define kTablesUIContextMenuHeaderFooterSepPosition			3300.0

#define kContextSelectInStructureTableMenuPosition			3400.0

// Context menu for table cell stroke widget
#define kContextTableStrokeSelectBorderMenuPosition			100.0
#define kContextTableStrokeSelectInnerMenuPosition			200.0
#define kContextTableStrokeSelectAllMenuPosition			300.0
#define kContextTableStrokeClearBorderMenuPosition			400.0
#define kContextTableStrokeClearInnerMenuPosition			500.0
#define kContextTableStrokeClearAllMenuPosition				600.0



// Right mouse Guides menu
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.
#define kContextGuideOptionsMenuPosition			1100.0
#define kContextGuideTypeSubMenuPosition			1150.0

#define kContextGuideTypeSnappingGuideMenuPosition	100.0
#define kContextGuideTypeSliceGuideMenuPosition		200.0
#define kContextGuideTypeMagneticGuideMenuPosition	300.0
#define kContextGuideTypeZoneGuideMenuPosition		400.0

#define kContextGuidePrefsSepMenuPosition			1200.0

#define kContextShowGuideMenuPosition				1300.0
#define kContextLockGuideMenuPosition				1400.0
#define kContextSnapToGuideMenuPosition				1450.0
#define kContextShowSmartGuideMenuPosition			1475.0
#define kGuidesContextGuidesBackMenuPosition		1500.0
#define kContextMoveGuidesMenuPosition				1600.0
#define kContextGuideSepMenuPosition				1700.0

#define kContextLockGuidePosMenuPosition			1800.0
#define kContextUnLockGuidePosMenuPosition			1900.0

#define	kContextGuideSep3PosMenuPosition			2000.0
#define	kContextGuideDeleteAllGuidesMenuPosition	2100.0

// Right mouse Default menu
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.

#define kContextDefaultZoomInMenuPosition			1100.0
#define kContextDefaultZoomOutMenuPosition			1200.0
#define kContextDefaultActualSizeMenuPosition		1300.0
#define kContextDefaultEntirePasteboardMenuPosition	1400.0
#define kContextDefaultZoomSepMenuPosition			1500.0
#define kContextDefaultMatchPasteBoardToThemeMenuPosition			1520.0
#define kContextDefaultZoomSepMenuPosition2							1540.0

#define kDefaultSelectMenuPosition					1550.0
#define kDefaultSelectSepMenuPosition				1570.0

#define kDefaultWritingDirectionMenuPosition		1600.0
#define kDefaultWritingDirectionSepMenuPosition		1700.0

#define kDefaultShowCharCountMenuPosition			1800.0
#define kDefaultShowFrameGridMenuPosition			1900.0
#define kContextFrameGridSepMenuPosition			2000.0

#define kDefaultShowRulersMenuPosition				2100.0
#define kDefaultRulersSepMenuPosition				2200.0

#define kContextGridsAndGuidesMenuPosition			2300.0
#define kContextGridSepMenuPosition					3100.0

#define kContextDefaultDisplayMenuPosition			3200.0

#define kContextDefaultHLGroupSepMenuPosition			3300.0
#define kContextDefaultHyperlinkGroupMenuPosition		3400.0
#define kContextDefaultHyperlinkNewDestMenuPosition		100.0
#define kContextDefaultHyperlinkEditDestsMenuPosition	200.0
#define kContextDefaultHyperlinkSepMenuPosition			300.0
#define	kContextDefaultHyperlinkNewBkmkMenuPosition		400.0

// Menus in layout context menu in InCopy
#define kContextDefaultICGroupSepMenuPosition			4000.0
#define kContextDefaultICEditMenuPosition				4100.0
#define kContextDefaultICSubmitMenuPosition				4200.0
#define kContextDefaultICRevertMenuPosition				4300.0
#define kContextDefaultICUnembedMenuPosition			4400.0
#define kContextDefaultICSaveVerMenuPosition			4500.0
#define kContextDefaultICUpdateStoryMenuPosition		4600.0

// Right mouse XML Attributes menu
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.

#define kContextXMLSeparator1MenuPosition				1100.0
#define kContextXMLTagElementPopupMenuPosition			1200.0
#define kContextXMLUntagElementMenuPosition				1400.0
#define kContextXMLEditMenuPosition						1500.0
#define kContextXMLDeleteMenuPosition					1600.0
#define kContextXMLSeparator2MenuPosition				1700.0
#define kContextXMLAddElementMenuPosition				1800.0
#define kContextXMLInsertParentElementPopupMenuPosition	1850.0
#define kContextXMLNewAttributeMenuPosition				1900.0
#define kContextXMLNewCommentMenuPosition				2000.0
#define kContextXMLNewPIMenuPosition					2100.0
#define kContextXMLSeparator3MenuPosition				2200.0
#define kContextXMLValidateRootMenuPosition				2300.0
#define kContextXMLValidateSelectionMenuPosition			2400.0
#define kContextXMLSeparator4MenuPosition				2500.0
#define kContextXMLGoToItemMenuPosition				2600.0
#define kContextXMLImportMenuPosition					2700.0
#define kContextXMLExportMenuPosition					2800.0
#define kContextXMLSeparator5MenuPosition				2900.0
#define kContextXMLInsertChildElementPopupMenuPosition	3000.0
#define kContextXMLInsertSiblingAfterPopupMenuPosition	3100.0
#define kContextXMLReplaceElementPopupMenuPosition	3200.0

//#define kContextXMLSeparator3MenuPosition			1800.0
//#define kContextXMLShowAttributesMenuPosition		1900.0
//#define kContextXMLShowTextSnippetsMenuPosition		2000.0
// Right mouse XML Attributes menu
// Starting at 1100.0 because this will allow for general
// items to be place at the beginning of each menu without
// duplicating their defines.

//#define kContextXMLSeparator1MenuPosition			1100.0
#define kContextXMLEditAttributeMenuPosition		1200.0
#define kContextXMLDeleteAttributeMenuPosition		1300.0

//VRuler menu items
#define kVRulerSep1MenuPosition						100.0
#define kVRulerCustomMenuPosition					200.0
#define kVRulerSep2MenuPosition						300.0
#define kVShowRulersMenuPosition					400.0
#define kVRulerSep3MenuPosition						500.0
#define kVRulerDeleteAllGuidesMenuPosition			600.0

//HRuler menu items
#define kHRulerSep1MenuPosition						100.0
#define kHRulerCustomMenuPosition					200.0
#define kHRulerSep2MenuPosition						300.0
#define kRulerPerPageMenuPosition					400.0
#define kRulerPerSpreadMenuPosition					500.0
#define kRulerOnSpineMenuPosition					600.0
#define kHRulerSep3MenuPosition						700.0
#define kHShowRulersMenuPosition					800.0
#define kHRulerSep4MenuPosition						900.0
#define kHRulerDeleteAllGuidesMenuPosition			1000.0


#pragma mark ___Popup menus___
//gradient panel popup menu
#define kShowGradOptionsMenuPosition					100.0

//stroke panel popup menu
#define kShowStrokeOptionsMenuPosition				100.0
#define kStrokePanelSepMenuPosition					200.0
#define kLineStylesMenuPosition						300.0
//Obsolete #define kStrokePanelSep2MenuPosition				900.0
//Obsolete #define kStrokeAffectsBBoxMenuPosition			1000.0

// align panel popup
#define kShowAlignOptionsMenuPosition				100.0
#define kAlignPanelSepMenuPosition					200.0
#define kAlignPanelCancelKeyObjectMenuPosition		300.0

//lib panel popup
#define kLibNewLibMenuPosition				100.0
#define kLibOpenLibMenuPosition				200.0
#define kLibCloseLibMenuPosition			300.0
#define kDocToLibMenuPosition				350.0
#define kLibSep1MenuPosition				400.0
#define kLibAddItemMenuPosition				500.0
#define kLibAddPageMenuPosition				600.0
#define kLibAddPageSeparateMenuPosition		650.0
#define kLibPlaceItemMenuPosition			700.0
#define kLibDeleteItemMenuPosition			800.0
#define kLibUpdateItemMenuPosition			875.0
#define kLibMigrateItemMenuPosition			880.0
#define kLibSep2MenuPosition				900.0
#define kLibInfoMenuPosition				1000.0
#define kLibSep3MenuPosition				1100.0
#define kLibSubsetMenuPosition				1200.0
#define kLibShowAllMenuPosition				1300.0
#define kLibSep4MenuPosition				1400.0
#define kLibListViewMenuPosition			1500.0
#define kLibViewThumbMenuPosition			1600.0
#define kLibViewLargeThumbMenuPosition		1650.0
#define kLibSep5MenuPosition				1700.0

// history panel popup
#define kHistoryUndoMenuPosition		100.0
#define kHistoryRedoMenuPosition		200.0

// GlyphPanelPopup
#define kGlyphShowOptionsMenuPosition			100.0
#define kGlyphSep1MenuPosition					200.0
#define kGlyphNewGlyphMenuPosition				300.0
#define kGlyphAddGlyphSubMenuPosition			400.0
#define kGlyphEditGlyphSubMenuPosition			500.0
#define kGlyphViewGlyphSubMenuPosition			600.0
#define kGlyphDeleteGlyphSubMenuPosition		700.0
#define kGlyphContextSepMenuPosition			750.0
#define kGlyphContextDeleteMenuPosition			800.0
#define kGlyphContextClearMRUMenuPosition		850.0
#define kGlyphSep2MenuPosition					900.0
#define kGlyphContextLoadFindSepMenuPosition	925.0
#define kGlyphContextFindMenuPosition			950.0
#define	kGlyphContextChangeMenuPosition			1000.0


// These are J-only
#define kGlyphTraditionalMenuPosition			1000.0
#define kGlyphExpertMenuPosition				1100.0
#define kGlyphJIS78MenuPosition					1150.0
#define kGlyphJIS83MenuPosition					1200.0
#define kGlyphJIS90MenuPosition					1300.0
#define kGlyphJIS04MenuPosition					1400.0
#define kGlyphNLCMenuPosition					1500.0
#define kGlyphSep3MenuPosition					1600.0
#define kGlyphMonoHalfWidthMenuPosition			1700.0
#define kGlyphThirdWidthMenuPosition			1800.0
#define kGlyphQuarterWidthMenuPosition			1900.0
#define kGlyphProportionalWidthMenuPosition		2000.0
#define kGlyphFullWidthMenuPosition				2100.0
#define kGlyphSep4MenuPosition					2200.0
#define kGlyphDefaultMenuPosition				2300.0

// These are Roman and J
#define kGlyphSep5MenuPosition					2500.0
#define kGlyphSortGlyphsSubMenuPosition			2600.0
#define kGlyphSortByCIDMenuPosition				100.0
#define kGlyphSortByUnicodeMenuPosition			200.0

// NamedGridsPanelPopup
#define kNewNamedGridMenuPosition					100.0
#define kDuplicateNamedGridMenuPosition				200.0
#define kDeleteNamedGridMenuPosition				300.0
#define kNamedGridSep1MenuPosition					400.0
#define kNamedGridOptionMenuPosition				500.0
#define kNamedGridSep2MenuPosition					600.0
#define kLoadNamedGridMenuPosition					650.0
#define kSaveNamedGridMenuPosition					660.0
#define kLoadAllNamedGridsMenuPosition				700.0
#define kUpdateNamedGridsMenuPosition				750.0
#define kNamedGridSep3MenuPosition					800.0
#define kSelectUnusedNamedGridsMenuPosition			900.0
#define kApplyCJKGridComponentMenuPosition			1000.0
#define kSmallNamedGridsPaletteRowsMenuPosition		1100.0

// CJKPanelPopup
#define kCJKRubyMenuPosition					100.0
#define kCJKKentenMenuPosition				200.0
#define kCJKTatechuyokoMenuPosition		300.0
#define kCJKWarichuMenuPosition				400.0
#define kCJKSep1MenuPosition					500.0
#define kCJKKinsokuMenuPosition				600.0
#define kCJKMojikumiMenuPosition			700.0
#define kCJKCompositeFontMenuPosition	800.0
#define kCJKSep2MenuPosition					900.0
#define kCJKHorzPaletteMenuPosition		1000.0

// SwatchesPanelPopup
#define kSwatchNewMenuPosition					100.0
#define kSwatchTintMenuPosition					200.0
#define kSwatchGradMenuPosition					300.0
#define kSwatchInkSetSwatchMenuPosition			350.0
#define kSwatchInkSetMenuPosition				360.0
#define kColorGroupMenuPosition					370.0
#define kSwatchDuplicateMenuPosition			400.0
#define kSwatchDeleteMenuPosition				500.0
#define kUngroupColorGroupMenuPosition			550.0
#define kSwatchSep1MenuPosition					600.0
#define kSwatchOptionsMenuPosition				700.0
#define kEditColorGroupMenuPosition				710.0
#define kSwatchSep2MenuPosition					800.0
#define kFindColorMenuPosition					810.0
#define kSwatchSep9MenuPosition					820.0
#define kLoadSwatchesMenuPosition				850.0
#define kSaveSwatchesMenuPosition				855.0
#define kUpdateSwatchesMenuPosition				856.0
#define kSwatchSep7MenuPosition					860.0
#define kSwatchSelectUnusedMenuPosition			900.0
#define	kSwatchAddAllUnnamedColorMenuPosition	1000.0
#define kSwatchSep3MenuPosition					1100.0
#define kSwatchNameViewMenuPosition				1200.0
#define kSwatchSmallRowsMenuPosition			1300.0
#define kSwatchSmallMenuPosition				1400.0
#define kSwatchLargeMenuPosition				1500.0
#define kSwatchSep4MenuPosition					1600.0
#define kSwatchSortMenuPosition					1700.0
#define kSortSwatchesVisuallyMenuPosition		1800.0
#define kSwatchSep8MenuPosition					1900.0
#define	kSwatchMergeSwatchesMenuPosition		2000.0
#define kSwatchSep5MenuPosition					2100.0
#define kSwatchInkMgrMenuPosition				2200.0
#define kSwatchSep6MenuPosition					2300.0
#define kSwatchShowHideMenuPosition				2400.0

#define kSwatchSortByNameSubMenuPosition		100.0
#define kSwatchSortByValuesSubMenuPosition		200.0
#define kFlyoutSwatchSortByNameSubMenuPosition		300.0
#define kFlyoutSwatchSortByValuesSubMenuPosition		400.0


//Swatches Panel Filter Menu
#define kShowAllSwatchesMenuPosition			100.0
#define kShowColorSwatchesMenuPosition			200.0
#define kShowGradientSwatchesMenuPosition		300.0
#define kShowColorGroupsMenuPosition			400.0

// ColorPickerPanelPopup menu
#define kPickerOptionsMenuPosition			100.0
#define kPickerOptionsSepMenuPosition		200.0
#define kFirstColorSpaceMenuPosition		300.0

// PagesPanelPopup menu
#define kPageNewMenuPosition				100.0
#define kMovePageMenuPosition				200.0
#define kPageDuplicateMenuPosition			300.0
#define kPageDeleteMenuPosition				400.0
#define kPageSep0MenuPosition				500.0
#define kPrintPagesMenuPosition				530.0
#define kPageSep0_5MenuPosition				590.0
#define kMasterNewMenuPosition				600.0
#define kMasterOptionsMenuPosition			700.0
#define kApplyMasterMenuPosition			800.0
#define kOverrideAllMasterMenuPosition		900.0
#define kMasterPagesSubMenuPosition			1000.0
#define kPageSep1MenuPosition				1100.0
#define kPageCreateAlternateLayoutMenuPosition 1200.0
#define kPageSectionOptionsMenuPosition		1300.0
#define kPageDeleteSectionMenuPosition		1350.0	// Only in a context menu
#define kPageSep2MenuPosition				1400.0
#define kAllowShuffleMenuPosition			1500.0
#define kKeepSpreadTogetherMenuPosition		1600.0
#define kPageSep3MenuPosition				1700.0
#define kPageAttributesSubMenuPosition		1800.0
#define kPageSep4MenuPosition				1900.0
#define kPagesPanelViewPagesMenuPosition	2000.0
#define kPagesPanelOptionsMenuPosition		2100.0

// Master Pages submenu in PagesPanelPopup
#define kSaveAsMasterMenuPosition			100.0
#define kImportMasterPageMenuPosition		200.0
#define kSelectUnusedMastersMenuPosition	300.0
#define kMasterPagesSubmenuSep1MenuPosition	400.0
#define kRemoveOverridesMenuPosition		500.0
#define kBreakMasterLinkMenuPosition		600.0
#define kAllowOverridesMenuPosition			700.0
#define kMasterPagesSubmenuSep2MenuPosition	800.0
#define kDisplayMasterItemsMenuPosition		900.0

// Page and Spread Attributes submenu in PagesPanelPopup
#define kPageColorLabelMenuPosition			100.0 
#define kPagesPanelRotateSpreadMenuPosition	200.0 
#define kPagesPanelAddPageTransitionMenuPosition	300.0 
#define kXPSpreadSettingsMenuPosition		400.0

// HyperlinksPanelPopup menu
#define kHyperlinkNewMenuPosition					100.0
#define kCreateLinkFromSelectionMenuPosition		200.0
#define kHyperlinkDeleteMenuPosition				300.0
#define kHyperlinkSep1MenuPosition					400.0
#define kHyperlinkNewDestinationMenuPosition		500.0
#define kHyperlinkSep2MenuPosition					600.0
#define kHyperlinkOptionsMenuPosition				700.0
#define kEditAllHyperlinkDestinationsMenuPosition	800.0
#define kDeleteUnusedDestinationsMenuPosition		850.0
#define kHyperlinkSep3MenuPosition					900.0
#define kHyperlinkGoToSourceMenuPosition			1000.0
#define kHyperlinkGoToDestinationMenuPosition		1100.0
#define kHyperlinkRenameHyperlinkMenuPosition		1150.0
#define kHyperlinkResetSourceMenuPosition			1200.0
#define kUpdateHyperlinkDestinationInfoMenuPosition	1300.0
#define kHyperlinkSep4MenuPosition					1400.0
#define kXRefConvertToTextMenuPosition				1600.0
#define kHyperlinkSep5MenuPosition					1700.0
#define kHyperlinkSortOptionsMenuPosition			2500.0
#define kHyperlinkSep8MenuPosition					2600.0
#define kHyperlinkSmallRowsMenuPosition				2700.0
#define kHyperlinkAutoUpdateURLsMenuPosition		2800.0

// XRefPanelPopup menu
#define kXRefNewMenuPosition						1500.0
#define kXRefOptionsMenuPosition					1800.0
#define kXRefDeleteMenuPosition						1850.0
#define kXRefUpdateMenuPosition						1900.0
#define kXRefRelinkMenuPosition						2000.0

#define kXRefSep1MenuPosition						2005.0
#define kXRefNewDestinationMenuPosition				2010.0
#define kXRefEditAllHyperlinkDestinationsMenuPosition	2015.0
#define kXRefSep2MenuPosition						2020.0

#define kXRefGoToSourceMenuPosition					2050.0
#define kXRefGoToDestinationMenuPosition			2075.0
#define kXRefSep6MenuPosition						2100.0
#define kXRefFormatDefinePanelPosition				2200.0
#define kXRefFormatLoadPanelPosition				2300.0
#define kXRefSep7MenuPosition						2400.0

// Type:XRef
#define kTypeNewHyperlinkMenuPosition				100.0
#define kTypeNewURLHyperlinkMenuPosition			200.0
#define kTypeEditHyperlinkMenuPosition				300.0
#define kTypeHLSep1MenuPosition						400.0
#define kTypeNewXRefMenuPosition					500.0	
#define kTypeEditXRefMenuPosition					600.0
//#define kTypePasteXRefMenuPosition				700.0
#define kTypeConvertXRefMenuPosition				800.0
#define kTypeUpdateXRefsMenuPosition				900.0
#define kTypeHLSep2MenuPosition						1000.0
#define kTypeHLXRefPanelMenuPosition				1100.0

// XRef Format Popup menu
#define kXRefFormatDefinePosition					100.0
#define kXRefFormatEditPosition						200.0
#define kXRefFormatCreatePosition					300.0

// XRef Format Insert Block Popup menu
#define kXRefFormatBlockPageNumberPosition			100.0
#define kXRefFormatBlockParagraphNumberPosition		200.0
#define kXRefFormatBlockParagraphTextPosition		300.0
#define kXRefFormatBlockFullParagraphPosition		400.0
#define kXRefFormatBlockPartialParagraphPosition	500.0
#define kXRefFormatBlockBookmarkNamePosition		600.0
#define kXRefFormatBlockChapterNumberPosition		700.0
#define kXRefFormatBlockFileNamePosition			800.0
#define kXRefFormatBlockCharacterStylePosition		900.0

// XRef Format Insert Special Character Popup Menu
#define kXRefFormatMetaEmDashMenuPosition				100.0
#define kXRefFormatMetaEnDashMenuPosition				200.0
#define kXRefFormatMetaSep1MenuPosition					300.0
#define kXRefFormatMetaMSpaceMenuPosition				400.0
#define kXRefFormatMetaNSpaceMenuPosition				500.0
#define kXRefFormatMetaHairSpaceMenuPosition			600.0
#define kXRefFormatMetaSixthSpaceMenuPosition			700.0
#define kXRefFormatMetaThinSpaceMenuPosition			800.0
#define kXRefFormatMetaQuarterSpaceMenuPosition			900.0
#define kXRefFormatMetaThirdSpaceMenuPosition			1000.0
#define kXRefFormatMetaPunctuationSpaceMenuPosition		1100.0
#define kXRefFormatMetaFigureSpaceMenuPosition			1200.0
#define kXRefFormatMetaFlushSpaceMenuPosition			1300.0
#define kXRefFormatMetaSep2MenuPosition					1400.0
#define kXRefFormatMetaNonBreakMenuPosition				1500.0
#define kXRefFormatMetaNonBreakFixedMenuPosition		1600.0
#define kXRefFormatMetaNonBreakHyphMenuPosition			1700.0
#define kXRefFormatMetaSep3MenuPosition					1800.0
#define kXRefFormatMetaDoubleLeftMenuPosition			1900.0
#define kXRefFormatMetaDoubleRightMenuPosition			2000.0
#define kXRefFormatMetaSingleMenuPosition				2100.0
#define kXRefFormatMetaSingleLeftMenuPosition			2200.0
#define kXRefFormatMetaDoubleQuoteMenuPosition			2300.0
#define kXRefFormatMetaSingleQuoteMenuPosition			2400.0
#define kXRefFormatMetaSep4MenuPosition					2500.0
#define kXRefFormatMetaBulletMenuPosition				2600.0
#define kXRefFormatMetaParaMenuPosition					2700.0
#define kXRefFormatMetaSectionMenuPosition				2800.0
#define kXRefFormatMetaSep5MenuPosition					2900.0
#define kXRefFormatMetaTabMenuPosition					3000.0
#define kXRefFormatMetaForcedBreakMenuPosition			3100.0
#define kXRefFormatMetaEndNestedMenuPosition			3200.0
#define kXRefFormatMetaNonJoinerMenuPosition			3300.0

// Hyperlinks Sort method sub menu
#define kHyperlinkSortManuallyMenuPosition			100.0
#define kHyperlinkSortByNameMenuPosition			200.0
#define kHyperlinkSortByTypeMenuPosition			300.0

// BookmarksPanelPopup
#define kBookmarkNewMenuPosition					100.0
#define kBookmarkDeleteMenuPosition					200.0
#define kBookmarkSep1MenuPosition					300.0
#define kBookmarkOptionsMenuPosition				400.0
#define kBookmarkSep2MenuPosition					500.0
#define kBookmarkGoToMenuPosition					600.0
#define kBookmarkSep3MenuPosition					700.0
#define kBookmarkSortMenuPosition					800.0

// PageTransitionsPanelPopup menu
#define kPageTransitionsPanelChooseMenuPosition					100.0
#define kPageTransitionsPanelApplyToAllSpreadsMenuPosition		200.0
#define kPageTransitionsPanelClearAllTransitionsMenuPosition	300.0

// ObjectStylesPanelPopup menu
#define kObjectStylesNewMenuPosition				100.0
#define kObjectStylesDuplicateMenuPosition			200.0
#define kObjectStylesDeleteMenuPosition				300.0
#define kObjectStylesSep1MenuPosition				400.0
#define kObjectStylesRedefineMenuPosition			500.0
#define kObjectStylesSep2MenuPosition				550.0
#define kObjectStylesOptionsMenuPosition			600.0
#define kObjectStylesSep3MenuPosition				650.0
#define kObjectStylesClearOverridesMenuPosition		700.0
#define kObjectStylesClearOverridesWhenApplyStyleMenuPosition			725.0
#define kObjectStylesClearOverridesNotDefinedByStyleMenuPosition		750.0
#define kObjectStylesSep4MenuPosition				800.0
#define kBreakLinkToObjectStylesMenuPosition		850.0
#define kObjectStylesSep5MenuPosition				900.0

#define kObjectChangeDefaultTStyleMenuPosition		950.0
#define kObjectChangeDefaultGStyleMenuPosition		955.0
#define kObjectChangeDefaultFStyleMenuPosition		956.0
#define kObjectStylesSep6MenuPosition				960.0
#define kLoadObjectStylesMenuPosition				1000.0
#define kSaveObjectStylesMenuPosition				1002.0
#define kUpdateObjectStylesMenuPosition				1003.0
#define kObjectStylesSep7MenuPosition				1005.0
#define kExportObjectStylesMenuPosition				1010.0
#define kImportObjectStylesMenuPosition				1020.0

#define kSelectAllUnusedObjectStylesMenuPosition	1200.0
#define kStyleEditAllObjectStyleToTagMenuPosition	1225.0
#define kObjectStylesSep8MenuPosition				1250.0
#define kNewObjectStyleGroupMenuPosition			1255.0
#define kOpenAllObjectStyleGroupsAMenuPosition		1260.0
#define kCloseAllObjectStyleGroupsMenuPosition		1265.0
#define kObjectStylesSep10MenuPosition				1270.0
#define kCopyToObjectStyleGroupPosition				1275.0
#define kCreateGroupFromObjectStylePosition			1280.0
#define kObjectStylesSep11MenuPosition				1285.0

#define kSortByNameObjectStylesMenuPosition			1300.0
#define kObjectStylesSep9MenuPosition				1350.0
#define kObjectStylesSmallListViewMenuPosition		1500.0
//#define kObjectStylesReplaceMenuPosition			1600.0
//#define kObjectStylesThumbnailViewMenuPosition	1700.0
//#define kObjectStylesLargeListViewkMenuPosition	1800.0


// ObjectStyle context menu
#define kObjStyleItemOptionsMenuPosition			100.0
#define kObjStyleItemDuplicateStyleMenuPosition		200.0
#define kObjStyleItemDeleteStyleMenuPosition		300.0
#define kObjStyleItemRedefineStyleMenuPosition		400.0
#define kObjStyleItemClearOverridesMenuPosition		450.0
#define kObjStyleItemSep1MenuPosition				500.0
#define kObjStyleItemApplyStylePosition				600.0
#define kObjStyleItemApplyStyleRemoveOPosition			700.0
#define kObjStyleItemApplyStyleWithRootPosition			800.0
#define kObjStyleItemApplyStyleWithRootAndClearPosition		850.0
#define kObjStyleItemSep2MenuPosition				900.0
#define kObjStyleItemChangeTStylePosition			1000.0
#define kObjStyleItemChangeGStylePosition			1050.0
#define kObjStyleItemChangeFStylePosition			1075.0
#define kObjStyleItemSep3MenuPosition				1100.0
#define kObjStyleItemJBXUIRelinkPosition			1200.0
#define kObjStyleItemJBXUIUpdatePosition			1300.0
#define kObjStyleItemJBXUIUnlinkPosition			1400.0
#define kObjStyleItemJBXUISepMenuPosition			1500.0

#define kCreateObjectStyleInGroupContextMenuPosition 1550.0
#define kObjectStyleGroupSep1						1575.0
#define kObjStyleGroupOptoinsContextMenuPosition	1600.0
#define kDuplicateObjStyleGroupContextMenuPosition	1700.0
#define kDeleteObjStyleGroupContextMenuPosition		1800.0
#define kObjectStyleGroupSep2						1850.0
#define kCopyToObjStyleGroupContextMenuPosition		1900.0
#define kCreateObjStyleGroupContextMenuPosition		2000.0

// StandOffPanelPopup menu
#define kStandoffPanelOptionsMenuPosition			100.0
#define kStandoffPanelActiveFromMasterMenuPosition	200.0

// ScriptPanelPopup menu
//#define kScriptPanelNewMenuPosition				100.0
#define kScriptPanelSep1MenuPosition				1000.0
#define kScriptPanelRunMenuPosition					1100.0
#define kScriptPanelEditMenuPosition				1200.0
#define kScriptPanelSep2MenuPosition				2000.0
#define kScriptPanelShowMenuPosition				2100.0
#define kScriptPanelDeleteMenuPosition				2200.0
#define kScriptPanelSep3MenuPosition				3000.0
#define kScriptPanelRedrawMenuPosition				3100.0
#define kScriptPanelEnableAttachedScriptsMenuPosition	3200.0
#define kScriptPanelSep4MenuPosition				4000.0
#define kScriptPanelDisplayUnsupportedFilesMenuPosition	4100.0
//#define kScriptPanelVersion30MenuPosition			4100.0
//#define kScriptPanelVersion40MenuPosition			4200.0

// links panel header context menu
#define kLinksUIHeaderPrefsMenuPosition			150.0
#define kLinksUIHeaderRemoveColumnMenuPosition	300.0
#define kLinksUIHeaderShowHideThumbnailMenuPosition		400.0

#define kLinkInfoShowHideThumbnailMenuPosition	100.0
#define kLinkInfoShowXMPInfoMenuPosition			200.0

// LinksPanelPopup menu( and context menu)
#define kRelinkMenuPosition					100.0
#define kRelinkToFolderMenuPosition			150.0
#define kRelinkFileExtensionMenuPosition	175.0
#define kRelinkCloudAssetMenuPosition		180.0
#define kRelinkAALAssetMenuPosition        181.0
#define kLinkSep5MenuPosition				185.0
#define kReplaceFPOWithOriginalLinkPosition      190.0
#define kReplaceAllFPOWithOriginalLinksPosition  195.0
#define kDownloadOriginalLinkPosition      	196.0
#define kDownloadAllOriginalLinksPosition   197.0
#define kLinkSep0MenuPosition				200.0
#define kUpdateLinkMenuPosition				300.0
#define kUpdateAllOutOfDateLinksMenuPosition	400.0
#define kLicenseStockAssetMenuPosition		500.0
#define kLinkSep1MenuPosition				600.0
#define kGotoLinkMenuPosition				700.0
#define kEmbedLinkMenuPosition				800.0
#define kLinksUILinkedStoryOptionsMenuPosition	850.0
#define kLinksUILinkedArticleOptionsMenuPosition	875.0
#define kLinkSep2MenuPosition				900.0
#define kEditOriginalMenuPosition				1000.0
#define kEditOriginalWithMenuPosition			1100.0
#define kGoToSourceMenuPosition					1150.0
#define kRevealLinkInOSMenuPosition			1200.0
#define kRevealLinkInBrowserMenuPosition		1300.0
#define kRevealLinkInMiniBridgeMenuPosition	1350.0
#define kRevealLinkInCloudLibrariesMenuPosition 1360.0
#define kLinkSep3MenuPosition				1400.0
#define kLinkUtilitiesMenuPosition				1500.0
#define kLinkCopyInfoMenuPosition			1550.0
#define kLinkSep4MenuPosition				1700.0
#define kLinksUIPrefsMenuPosition			1800.0

// links panel 'utilities' submenu
#define kAutoFindMissingLinksMenuPosition		200.0
#define kCopyLinkMenuPosition				300.0
#define kLinkFileInfoMenuPosition				400.0
#define kCopyLinkPathMenuPosition			500.0
#define kCopyLinkPlatformPathMenuPosition	510.0
#define kCopyLinkInfoMenuPosition			550.0
#define kGenerateLinkReportMenuPosition		600.0
#define kAutoSizeLinkInfoMenuPosition			850.0
#define kLinksUIShowHideInfoMenuPosition		900.0
#define kLinkUtilSep0MenuPosition			1000.0
#define kICBridgeEditInMenuPosition			1100.0
#define kICBridgeRevertMenuPosition			1200.0
#define kICBridgeSubmitMenuPosition			1300.0
#define kLinkUtilSep1MenuPosition			1400.0
#define kCheckinLinkMenuPosition			1500.0
#define kLinkVersionsMenuPosition			1600.0

// ParaStylePanelPopup and CharStylePanelPopup menu
#define kStyleNewMenuPosition						100.0
#define kStyleSep1PropertiesMenuPosition                150.0
#define kStyleDuplicateMenuPosition					200.0
#define kStyleDeleteMenuPosition					300.0
#define kStyleSep1MenuPosition						400.0
#define kStyleRedefineMenuPosition					500.0
#define kToggleStylePreviewModeCharMenuPosition		550.0
#define kStyleSep2MenuPosition						600.0
#define kStyleOptionsMenuPosition					700.0
#define kStyleSep3MenuPosition						800.0
#define kStyleClearOverridesPosition				900.0
#define kToggleStylePreviewModeParaMenuPosition		925.0
#define kStyleConvertBNToTextMenuPosition			950.0
#define kStyleClearCharStylesAndOverridesPosition	1000.0
#define kStyleBreakLinkPosition						1050.0
#define kStyleSep4MenuPosition						1100.0
#define kStyleLoadStyleMenuPosition					1200.0
#define kStyleSaveStyleMenuPosition					1250.0
#define kUpdateCharParaStyleMenuPosition			1275.0
#define kStyleLoadAllMenuPosition					1300.0
#define kStyleSep5MenuPosition						1400.0
#define kStyleSelectUnusedMenuPosition				1500.0
#define kStyleEditAllStyleToTagMenuPosition			1550.0
#define kStyleSep6MenuPosition						1600.0
#define kNewStyleGroupMenuPosition					1640.0
#define kOpenAllStyleGroupsAMenuPosition			1650.0
#define kCloseAllStyleGroupsMenuPosition			1660.0
#define kStyleSep9MenuPosition						1662.0
#define kCopyToStyleGroupPosition					1665.0
#define kCreateGroupFromStylePosition				1667.0
#define kStyleSep7MenuPosition						1670.0
#define kStyleSortByNameMenuPosition				1680.0
#define kStyleSep8MenuPosition						1690.0
#define kStyleSmallRowsMenuPosition					1700.0

// StyleListContextMenu
#define kStyleItemOptionsMenuPosition			100.0
#define kStyleItemDuplicateStyleMenuPosition	200.0
#define kStyleItemDeleteStyleMenuPosition		300.0
#define kStyleItemRedefineStyleMenuPosition		400.0
//#define kStyleSep2MenuPosition				600.0
#define kStyleItemApplyStylePosition			700.0
#define kStyleItemApplyStyleRemoveOPosition		800.0
#define kStyleItemApplyStyleRemoveCSPosition	900.0
#define kStyleItemApplyStyleRemoveAllPosition	1000.0
//#define kStyleSep4MenuPosition				1100.0
#define kStyleItemApplyNStylePosition			1200.0
#define kStyleItemApplyNStyleRemoveOPosition	1300.0
#define kStyleItemApplyNStyleRemoveCSPosition	1400.0
#define kStyleItemApplyNStyleRemoveAllPosition	1500.0
#define kStyleItemConvertBNSepMenuPosition		1600.0
#define kStyleItemConvertBNMenuPosition			1700.0
#define kCharParaStyleItemJBXUIRelinkPosition	1750.0
#define kCharParaStyleItemJBXUIUpdatePosition	1800.0
#define kCharParaStyleItemJBXUIUnlinkPosition	1900.0
#define kCharParaStyleItemJBXUISepMenuPosition	2000.0

//Style set context menu positions
#define kCreateStyleInGroupContextMenuPosition	2050.0
#define kStyleGroupSep1MenuPosition				2075.0
#define kStyleGroupOptoinsContextMenuPosition	2100.0
#define kDuplicateStyleGroupContextMenuPosition	2200.0
#define kDeleteStyleGroupContextMenuPosition	2300.0
#define kStyleGroupSep2MenuPosition				2350.0
#define kCopyToStyleGroupContextMenuPosition	2400.0
#define kCreateStyleGroupContextMenuPosition	2500.0

// LayerPanelPopup menu
#define kLayerNewMenuPosition				100.0
#define kLayerDuplicateMenuPosition			150.0
#define kLayerDeleteMenuPosition			200.0
#define kLayerSep1MenuPosition				300.0
#define kLayerOptionsMenuPosition			400.0
#define kLayerSep2MenuPosition				500.0
#define kLayerShowHideMenuPosition			600.0
#define kLayerUnlockMenuPosition			700.0
#define kLayerUnlockAllMenuPosition			750.0
#define kLayerSep3MenuPosition				800.0
#define kLayerUngroupRememberMenuPosition	850.0
#define kLayerPasteRememberMenuPosition		900.0
#define kLayerSep4MenuPosition				1000.0
#define kLayerMergeMenuPosition			1100.0
#define kLayerDeleteUnusedMenuPosition		1200.0
#define kLayerSelectLayerMenuPosition		1300.0
#define kLayerSep5MenuPosition				1400.0
#define kLayerPageItemSelectMenuPosition			1500.0
#define kLayerPageItemSelectAndZoomMenuPosition	1600.0
#define kLayerSep6MenuPosition				1700.0
#define kLayerSmallRowsMenuPosition			1800.0


// FindMetaCharPopupMenu and ChangeMetaCharPopupMenu
// The Insert Whitespace menu below also refers to these id's
#define kFCMetaAutoPageMenuPosition			100.0
#define kFCMetaSectionNameMenuPosition		200.0
	#define kFCMetaSep1MenuPosition					300.0
#define kFCMetaCRMenuPosition						310.0
#define kFCMetaNewLineMenuPosition				320.0
#define kFCMetaAnchoredObjectMenuPosition		330.0
#define kFCMetaFootnoteReferenceMenuPosition		340.0
#define kFCMetaIndexMarkerMenuPosition				345.0
	#define kFCMetaSep2MenuPosition				350.0
#define kFCMetaBulletMenuPosition				400.0
#define kFCMetaJBulletMenuPosition				450.0
#define kFCMetaCaretMenuPosition					500.0
#define kFCMetaCopyrightMenuPosition			600.0
#define kFCMetaEllipsisMenuPosition				700.0
#define kFCMetaParaMenuPosition					800.0
#define kFCMetaRegisterMenuPosition			900.0
#define kFCMetaSectionMenuPosition				920.0
#define kFCMetaTrademarkSymbolMenuPosition	940.0
	#define kFCMetaSep3MenuPosition 				1200.0
#define kFCMetaEmDashMenuPosition				1300.0
#define kFCMetaEnDashMenuPosition				1400.0
#define kFCMetaDiscHyphMenuPosition			1500.0
#define kFCMetaNonBreakHyphMenuPosition		1600.0
	#define kFCMetaSep4MenuPosition 				1700.0
#define kFCIdeographicSpaceMenuPosition			1750.0	// Japanese FS
#define kFCMetaIdeographicSpaceMenuPosition		1760.0
#define kFCMetaMSpaceMenuPosition				1800.0
#define kFCMetaNSpaceMenuPosition				1850.0
	#define kFCMetaSep5MenuPosition 				1860.0
#define kFCMetaNonBreakMenuPosition			1900.0
#define kFCMetaNonBreakFixedMenuPosition			1950.0
	#define kFCMetaSep6MenuPosition 				1960.0
#define kFCMetaHairSpaceMenuPosition			2000.0
#define kFCMetaSixthSpaceMenuPosition				2050.0
#define kFCMetaThinSpaceMenuPosition			2100.0
#define kFCMetaQuarterSpaceMenuPosition				2150.0
#define kFCMetaThirdSpaceMenuPosition				2200.0
#define kFCMetaPunctuationSpaceMenuPosition		2250.0
#define kFCMetaFigureSpaceMenuPosition			2300.0
#define kFCMetaFlushSpaceMenuPosition		2400.0
#define kFCMetaAnyDoubleMenuPosition		2420.0
#define kFCMetaAnySingleMenuPosition		2440.0
	#define kFCMetaSep7MenuPosition 				2500.0
#define kFCMetaDoubleMenuPosition			2800.0
#define kFCMetaDoubleLeftMenuPosition		2850.0
#define kFCMetaDoubleRightMenuPosition		2900.0
#define kFCMetaSingleMenuPosition			2950.0
#define kFCMetaSingleLeftMenuPosition		3000.0
#define kFCMetaSingleRightMenuPosition		3050.0
	#define kFCMetaSep8MenuPosition 				3200.0
#define kFCMetaTabMenuPosition						3300.0
#define kFCMetaRightEdgeTabMenuPosition	3400.0
#define kFCMetaIndentToHereMenuPosition	3500.0
	#define kFCMetaSep9MenuPosition 				3600.0
#define kFCMetaNextFormatMenuPosition			3700.0
	#define kFCMetaSep10MenuPosition 				3800.0
#define kFCMetaAnyDigitMenuPosition			3900.0
#define kFCMetaAnyLetterMenuPosition			4000.0
#define kFCMetaAnyCharMenuPosition				4100.0
#define kFCMetaWhiteSpaceMenuPosition		4200.0
#define kFCMetaAnyKanjiMenuPosition			4300.0


// TransformPanelPopup menu
#define kTPLineStylesMenuPosition					100.0	// Control Strip only (kControlStripLayoutMenuName)
#define kTPSep0MenuPosition							125.0	// Control Strip only (kControlStripLayoutMenuName)
#define kTPClearTransformationsMenuPosition			150.0
#define kTPRedefineScalingMenuPosition				175.0
#define kTPSep1MenuPosition							200.0
#define kTPRotate90CWMenuPosition					300.0
#define kTPRotate90CCWMenuPosition					400.0
#define kTPRotate180MenuPosition					500.0
#define kTPSep2MenuPosition							600.0
#define kTPFlipHorzMenuPosition						700.0
#define kTPFlipVertMenuPosition						800.0
#define kTPSep3MenuPosition							1000.0
#define kTPShowStrokeBoundsMenuPosition				1100.0
#define kTPDisplayGlobalMenuPosition				1200.0
#define kTPShowContentOffsetMenuPosition			1300.0
#define kTPScaleStrokesMenuPosition					1400.0
#define kTPScaleXPEffectsMenuPosition				1500.0


// ParaPanelPopup menu
#define kParaPanelOptionsMenuPosition				100.0
#define kParaPanelSep1MenuPosition					200.0
// CJK stuff
#define kCJKHangingSubMenuPosition					250.0
#define kCJKHangingNoneMenuPosition					300.0
#define kCJKHangingRegularMenuPosition				310.0
#define kCJKHangingForceMenuPosition				320.0
#define kCJKKinsokuSubMenuPosition					350.0
#define kCJKKinsokuPushInFirstPosition				400.0
#define kCJKKinsokuPushOutFirstPosition				500.0
#define kCJKKinsokuPushOutOnlyPosition				600.0
#define kCJKKinsokuPushInAlwaysPosition				650.0
#define kCJKBunrikinshiMenuPosition					700.0
#define kCJKAutoTatechuyokoMenuPosition				800.0
#define kCJKRensuujiMenuPosition					900.0
#define kCJKRomanRotateMenuPosition					1000.0
#define kCJKIdeoSpaceBehaviorMenuPosition			1010.0
#define kCJKWordWrapOffMenuPosition					1020.0
#define kCJKParaPopupSep2MenuPosition				1100.0

// Grid alignment submenu
#define kCJKGridAlignmentSubMenuPosition			1150.0
#define kCJKGridAlignmentNoneMenuPosition			1200.0
#define kCJKGridAlignmentTopMenuPosition			1300.0
#define kCJKGridAlignmentCenterMenuPosition			1400.0
#define kCJKGridAlignmentBaselineMenuPosition		1500.0
#define kCJKGridAlignmentBottomMenuPosition			1600.0
#define kCJKGridAlignmentICFTopMenuPosition			1700.0
#define kCJKGridAlignmentICFBottomMenuPosition		1800.0
#define kCJKGridAlignOnlyFirstLineMenuPosition		1900.0
#define kCJKParaPanelBalanceLinesMenuPosition		1925.0
#define kCJKParaGyoudoriMenuPosition				1950.0
#define kCJKParaPopupSep3MenuPosition				2000.0

#define kFirstComposerMenuPosition					3000.0
#define kFirstCJKComposerMenuPosition				3100.0
#define kCJKParaPopupSep4MenuPosition				3200.0

#define kRomanAlignOnlyFirstLineMenuPosition		3210.0
#define kRomanParaPanelBalanceLinesMenuPosition		3220.0

#define kCJKLeadingModelSubMenuPosition				3270.0
#define kCJKLeadingModelAkiBelowPosition			3271.0
#define kCJKLeadingModelCenter						3272.0
#define kCJKLeadingModelRomanBaseline				3273.0
#define kCJKLeadingModelAkiAbovePosition			3274.0
#define kParaPanelSep2MenuPosition					3400.0
#define kCJKParaSpacingMenuPosition					3500.0
#define kParaPanelJustMenuPosition					3600.0
#define kParaPanelKeepMenuPosition					3700.0
#define kParaPanelSpanMenuPosition					3750.0
#define kCJKParaHyphenFlagMenuPosition				3800.0
#define kParaPanelHyphMenuPosition					3900.0
#define kParaPanelRunInMenuPosition					3950.0
#define kParaPanelRulesMenuPosition					4000.0
#define kParaPanelBorderShadingMenuPosition			4050.0
#define kParaPanelMainSepItemPosition				4100.0
#define kParaPanelBNMenuItemPosition				4200.0
#define kParaPanelRestartNumberingItemPosition		4300.0
#define kParaPanelBNConvertItemPosition				4400.0
#define kParaPanelDefineListItemPosition			4500.0

// Align Submenu in Paragraph panel
#define kParaAlignLeftMenuPosition					4300.0
#define kParaAlignCenterMenuPosition				4400.0
#define kParaAlignRightMenuPosition					4500.0
#define kParaAlignSepMenuPosition					4600.0
#define kParaAlignJustLeftMenuPosition				4700.0
#define kParaAlignJustCenterMenuPosition			4800.0
#define kParaAlignJustRightMenuPosition				4900.0
#define kParaAlignJustFullMenuPosition				5000.0

// CharPanelPopup menu
#define kCharOptionsMenuPosition				100.0
#define kCharSep1MenuPosition						200.0
#define kCharOpenTypeMenuPosition					250.0
#define kCharAllCapsMenuPosition				300.0
#define kCharSmallCapsMenuPosition			400.0
#define kCharSuperscriptMenuPosition		500.0
#define kCharSubscriptMenuPosition			600.0
#define kCharSep2MenuPosition						700.0
#define kCharUnderlineMenuPosition			800.0
#define kCharStrikethruMenuPosition			900.0
#define kCharLigaturesMenuPosition			1000.0
#define kCharOldStyleMenuPosition				1100.0
#define kCharSep3MenuPosition						1200.0
#define kCharUnderlineOptionsMenuPosition			1210.0
#define kCharStrikethruOptionsMenuPosition			1220.0
#define kCharSep4MenuPosition						1230.0
#define kCharNoBreakMenuPosition				1300.0
#define kCharSep5MenuPosition						1400.0

// CharPanelPopup CJK menu
#define kCJKCharFullPaletteMenuPosition				100.0
#define kCJKCharMediumPaletteMenuPosition			200.0
#define kCJKCharSmallPaletteMenuPosition			300.0
#define kCJKCharPopupSep1MenuPosition					400.0
#define kCJKCharPopupOpenTypeMenuPosition					425.0
#define kCJKCharPopupSep1_5MenuPosition					450.0
#define kCJKCharTatechuyokoMenuPosition				500.0
#define kCJKCharTatechuyokoSettingMenuPosition	600.0
#define kCJKCharWarichuMenuPosition				700.0
#define kCJKCharWarichuSettingMenuPosition	800.0
#define kCJKRubySubMenuPosition							850.0
#define kCJKRubyNoneMenuPosition							900.0
#define kCJKCharPopupSep2MenuPosition					1000.0
#define kCJKRubySetting_1MenuPosition					1100.0
#define kCJKRubySetting_2MenuPosition					1200.0
#define kCJKRubySetting_3MenuPosition					1300.0
#define kCJKRubySetting_4MenuPosition					1400.0
#define kCJKKentenSubMenuPosition							1450.0
#define kCJKKentenNoneMenuPosition						1500.0
#define kCJKCharPopupSep3MenuPosition					1600.0
#define kCJKKenten_1MenuPosition							1700.0
#define kCJKKenten_2MenuPosition							1800.0
#define kCJKKenten_3MenuPosition							1900.0
#define kCJKKenten_4MenuPosition							2000.0
#define kCJKKenten_5MenuPosition							2100.0
#define kCJKKenten_6MenuPosition							2200.0
#define kCJKKenten_7MenuPosition							2300.0
#define kCJKKenten_8MenuPosition							2400.0
#define kCJKKenten_9MenuPosition							2500.0
#define kCJKKenten_10MenuPosition							2600.0
#define kCJKKentenCustomMenuPosition					2700.0
#define kCJKCharPopupSep4MenuPosition					2800.0
#define kCJKKentenSetting_1MenuPosition				2900.0
#define kCJKKentenSetting_2MenuPosition				3000.0
#define kCJKCharPopupSep5MenuPosition					3100.0
#define kCJKCharacterAlignmentSubMenuPosition				3150.0
#define kCJKCharHangEmTopMenuPosition					3200.0
#define kCJKCharHangEmCenterMenuPosition			3300.0
#define kCJKCharHangBaselineMenuPosition			3400.0
#define kCJKCharHangEmBottomMenuPosition			3500.0
#define kCJKCharHangICFTopMenuPosition				3600.0
#define kCJKCharHangICFBottomMenuPosition			3700.0
#define kScaleAffectsLineHeightMenuPosition			3800.0
#define kCJKGridTrackingPosition					3810.0
#define kCJKCharPopupSep6MenuPosition				3900.0
#define kCJKCharJObliquingMenuPosition				4000.0
#define kCJKCharUnderlineMenuPosition					4100.0
#define kCJKCharStrikethruMenuPosition				4200.0
#define kCJKCharSuperscriptMenuPosition				4300.0
#define kCJKCharSubscriptMenuPosition					4400.0
#define kCJKCharPopupSep7MenuPosition					4500.0
#define kCJKCharAllCapsMenuPosition						4600.0
#define kCJKCharSmallCapsMenuPosition					4700.0
#define kCJKCharLigaturesMenuPosition					4800.0
#define kCJKCharOldStyleMenuPosition					4900.0
#define kCJKCharPopupSep8MenuPosition					5000.0
#define kCJKCharNoBreakMenuPosition						5100.0

// TabPanelPopup menu
#define kTabClearMenuPosition						100.0
#define kTabDeleteMenuPosition						200.0
#define kTabRepeatMenuPosition						300.0
#define kTabResetIndentMenuPosition					400.0
#define kTabSeparatorMenuPosition					500.0
#define kTabTypeSubMenuPosition						600.0
#define kTabAlignLeftMenuPosition					100.0
#define kTabAlignCenterMenuPosition					200.0
#define kTabAlignRightMenuPosition					300.0
#define kTabAlignDecimalMenuPosition				400.0

// SwatchLibPanelPopup menu
#define kAddToSwatchesMenuPosition					100.0

#pragma mark ___submenus___
// Display submenu
#define kOptimizedSubMenuPosition				200.0
#define kTypicalSubMenuPosition					300.0
#define kHighResSubMenuPosition					400.0
#define kHighResSubMenuSepPosition				500.0
#define kClearOverrideSubMenuPosition			600.0

// stroke submenu
#define kStroke0MenuPosition				100.0
#define kStroke025MenuPosition				200.0
#define kStroke05MenuPosition				300.0
#define kStroke075MenuPosition				400.0
#define kStroke1MenuPosition				500.0
#define kStroke2MenuPosition				600.0
#define kStroke3MenuPosition				700.0
#define kStroke4MenuPosition				800.0
#define kStroke5MenuPosition				900.0
#define kStroke6MenuPosition				1000.0
#define kStroke7MenuPosition				1100.0
#define kStroke8MenuPosition				1200.0
#define kStroke9MenuPosition				1300.0
#define kStroke10MenuPosition				1400.0

// arrange submenu
#define kBringToFrontMenuPosition				100.0
#define kBringForwardMenuPosition				200.0
#define kSendBackwardMenuPosition				300.0
#define kSendToBackMenuPosition					400.0

// window arrange submenu
#define kTileAllVeticalPosition					100.0
#define kTileAllHorizontalPosition				200.0
#define kTile2UpHorizontalMenuPosition			300.0
#define kTile2UpVerticalMenuPosition			400.0
#define kTile3UpHorizontalMenuPosition			500.0
#define kTile3UpVerticalMenuPosition			600.0
#define kTile3UpRightMenuPosition				700.0
#define kTile4UpGridMenuPosition				800.0
#define kTile4UpVerticalMenuPosition			900.0
#define kTile4UpHorizontalMenuPosition			1000.0
#define kTile4Up2ColSplitMenuPosition			1100.0
#define kTile5Up2ColSplitMenuPosition			1200.0
#define kTile6UpGridMenuPosition				1300.0
#define kTile6Up3ColSplitMenuPosition			1400.0
#define kArrangeMenuSep3MenuPosition			1450.0
#define kCascadeMenuPosition					1500.0
#define kTileMenuPosition						1600.0
#define kArrangeMenuSep1MenuPosition			1700.0
#define kOWLMoveToFloatingWindowMenuPosition	1800.0
#define kOWLMoveAllToFloatingWindowMenuPosition 1900.0
#define kOWLConsolidateToGroupMenuPosition		2000.0
#define kArrangeMenuSep2MenuPosition			2100.0
#define kNewWindowMenuPosition					2200.0
#define kSplitWindowMenuPosition				2300.0
#define kSplitWindowOptionsSubMenuPosition		2400.0
#define kArrangeMenuSep4MenuPosition			2500.0		
#define kMinimizeWindowMenuPosition				2600.0		
#define kBringAllToFrontMenuPosition			2700.0		// Mac only

// Split Window Options submenu
#define kMatchZoomMenuPosition					100.0
#define kMatchLocationMenuPosition				200.0
#define kMatchZoomAndLocationMenuPosition		300.0
#define kSplitSepMenuPosition					400.0
#define kAlwaysMatchZoom						500.0
#define kAlwaysMatchLocation					600.0

// select submenu
#define kSelectFrontMenuPosition				100.0
#define kSelectForwardMenuPosition				200.0
#define kSelectBackwardMenuPosition				300.0
#define kSelectBackMenuPosition					400.0
#define kSelectSubmenuSepMenuPosition			500.0
#define kSelectParentFramePosition				600.0
#define kSelectContentItemMenuPosition			700.0
#define kSelectSubmenuSep2MenuPosition			750.0
#define kSelectPreviousItemMenuPosition			800.0
#define kSelectNextItemMenuPosition				900.0

// content fit submenu
#define kFillFramePropMenuPosition			100.0	// Two "filling" options first, they are most common. Matches button order in control strip
#define kFitContentPropMenuPosition			200.0
#define kAutoCropMenuPosition				300.0
#define kFittingSepMenuPosition				400.0
#define kFitFrameMenuPosition				500.0
#define kFitContentMenuPosition				600.0
#define kCenterContentMenuPosition			700.0
#define kClearFittingSepMenuPosition		750.0
#define kClearFittingOptionsMenuPosition	800.0
#define kPersistentFittingSepMenuPosition	850.0
#define kGraphicFramePropMenuPosition		900.0

// graphic content submenu
#define kContentGraphicMenuPosition			100.0
#define kContentTextMenuPosition			200.0
#define kContentContainerMenuPosition		250.0
#define kContentUnAssignedMenuPosition		300.0

// layout policy submenu
#define kSetFlowLayoutPolicyMenuPosition	100.0
#define kSetBorderLayoutPolicyMenuPosition	200.0
#define kSetNilLayoutPolicyMenuPosition		300.0

// library submenu
#define kNewLibMenuPosition					100.0
#define kOpenLibMenuPosition				200.0
#define kLibMenuSepMenuPosition				300.0

// library Convertor submenu
//#define kDocToLibMenuPosition				400.0	// Move to library panel's popup menu.

// &Type/Mojikumi Settings submenu
#define kBasicMojiKumiDlgMenuPosition		100.0
#define kDetailedMojiKumiDlgMenuPosition	200.0

// Type/Writing direction submenu
#define kHorizontalWritingMenuPosition		100.0
#define kVerticalWritingMenuPosition		200.0


// font size submenu
#define kOtherFontSizeMenuPosition			100.0
#define kFontSizeSepMenuPosition			200.0
#define kFontSize6MenuPosition				300.0
#define kFontSize7MenuPosition				325.0
#define kFontSize7Pt5MenuPosition			350.0
#define kFontSize8MenuPosition				400.0
#define kFontSize8Pt5MenuPosition			450.0
#define kFontSize9MenuPosition				500.0
#define kFontSize10MenuPosition				600.0
#define kFontSize11MenuPosition				700.0
#define kFontSize12MenuPosition				800.0
#define kFontSize13MenuPosition				850.0
#define kFontSize14MenuPosition				900.0
#define kFontSize16MenuPosition				950.0
#define kFontSize18MenuPosition				1000.0
#define kFontSize24MenuPosition				1100.0
#define kFontSize30MenuPosition				1200.0
#define kFontSize32MenuPosition				1250.0
#define kFontSize36MenuPosition				1300.0
#define kFontSize48MenuPosition				1400.0
#define kFontSize60MenuPosition				1500.0
#define kFontSize72MenuPosition				1600.0
#define kFontSize100MenuPosition			1700.0

// stroke weight menu
#define	kZeroStrokeMenuPosition				100.0
#define	kQuarterPointMenuPosition			200.0
#define	kHalfPointMenuPosition				300.0
#define	kThreeQuarterPointMenuPosition		400.0
#define	k1PointMenuPosition					500.0
#define	k2PointsMenuPosition				600.0
#define	k3PointsMenuPosition				700.0
#define	k4PointsMenuPosition				800.0
#define	k5PointsMenuPosition				900.0
#define	k6PointsMenuPosition				1000.0
#define	k7PointsMenuPosition				1100.0
#define	k8PointsMenuPosition				1200.0
#define	k9PointsMenuPosition				1300.0
#define	k10PointsMenuPosition				1400.0

#define	kZeroMMMenuPosition					1500.0
#define	kTenthMMMenuPosition				1550.0
#define	kQuarterMMMenuPosition				1600.0
#define	kPointThreeFiveMMMenuPosition		1650.0
#define	kHalfMMMenuPosition					1700.0
#define	k1MMMenuPosition					1800.0
#define	k1HalfMMMenuPosition				1900.0
#define	k2MMMenuPosition					2000.0
#define	k3MMMenuPosition					2100.0
#define	k4MMMenuPosition					2200.0
#define	k5MMMenuPosition					2300.0
#define	k10MMMenuPosition					2400.0
#define	k15MMMenuPosition					2500.0
#define	k20MMMenuPosition					2600.0

#define	k0PxMenuPosition					2700.0
#define	k1PxMenuPosition					2800.0
#define	k2PxMenuPosition					2900.0
#define	k3PxMenuPosition					3000.0
#define	k4PxMenuPosition					3100.0
#define	k5PxMenuPosition					3200.0
#define	k6PxMenuPosition					3300.0
#define	k7PxMenuPosition					3400.0
#define	k8PxMenuPosition					3500.0
#define	k9PxMenuPosition					3600.0
#define	k10PxMenuPosition					3700.0

// Preferences submenu
#define kGeneralPrefsMenuPosition				100.0	// 1. Order here should match order in GlobalPrefsDialog.fr
#define kSettingsInCloudPrefsMenuPosition		150.0	// 1. Order here should match order in GlobalPrefsDialog.fr
#define kUserInterfacePrefsMenuPosition			200.0	// 1a. Order here should match order in GlobalPrefsDialog.fr
#ifdef WINDOWS 
#define kWinUIScalingPrefsMenuPosition			210.0	// 1b. Order here should match order in GlobalPrefsDialog.fr
#endif	
#define kTouchWSPrefsMenuPosition				220.0	// 1c. Order here should match order in GlobalPrefsDialog.fr
#define kGeneralPrefsSepMenuPosition			250.0
#define kTextOptionsPrefsMenuPosition			300.0	// 2. Order here should match order in GlobalPrefsDialog.fr
#define kAdvTextOptionsPrefsMenuPosition		350.0	// 3. Order here should match order in GlobalPrefsDialog.fr
#define kCompositionPrefsMenuPosition			400.0	// 4. Order here should match order in GlobalPrefsDialog.fr
#define kCompositionPrefsSepSubMenuPosition		450.0

#define kUnitsIncrementsPrefsMenuPosition		500.0	// 5. Order here should match order in GlobalPrefsDialog.fr
#define kGridsPrefsMenuPosition					600.0	// 6. Order here should match order in GlobalPrefsDialog.fr
#define kGuidesPrefsMenuPosition				700.0	// 7. Order here should match order in GlobalPrefsDialog.fr
#define kCJKGridPrefsMenuPosition				750.0	// 8. Order here should match order in GlobalPrefsDialog.fr
#define kGuidesPrefsSepMenuPosition				775.0

#define kDictPrefsMenuPosition					800.0	// 9. Order here should match order in GlobalPrefsDialog.fr
#define kSpellPrefsMenuPosition					815.0	// 10. Order here should match order in GlobalPrefsDialog.fr
#define kAutoCorrectPrefsMenuPosition			825.0	// 11. Order here should match order in GlobalPrefsDialog.fr
#define kSpellPrefsSepMenuPosition				830.0

#define kNotePrefsMenuPosition					850.0	// 12. Order here should match order in GlobalPrefsDialog.fr
#define kTrackChangesPrefsMenuPosition			875.0	// 13. Order here should match order in GlobalPrefsDialog.fr
#define kNotePrefsSepMenuPosition				880.0

#define kGalleyPrefsMenuPosition				899.0	// 14. Order here should match order in GlobalPrefsDialog.fr
#define kPerformanceUIPrefsMenuPosition			900.0	// 15. Order here should match order in GlobalPrefsDialog.fr
#define kGPUPerformanceUIPrefsMenuPosition		905.0	// 16. Order here should match order in GlobalPrefsDialog.fr
#define kPerformanceUIPrefsSepMenuPosition		910.0

#define kBlackConversionPrefsMenuPosition		915.0	// 17. Order here should match order in GlobalPrefsDialog.fr
#define kFileHandlingPrefsMenuPosition			920.0	// 18. Order here should match order in GlobalPrefsDialog.fr
#define kClipboardPrefsMenuPosition				930.0	// 19. Order here should match order in GlobalPrefsDialog.fr

#define kMojikumiOptionsPrefsMenuPosition		1400.0	// 20. Order here should match order in GlobalPrefsDialog.fr


#define kPDFUICBPrefsMenuPosition				1600.0

// Transform submenu
#define	kTransSepMenuPosition			  	 80.0
#define kTransMoveMenuPosition				100.0
#define kTransScaleMenuPosition				200.0
#define kTransRotateMenuPosition			300.0
#define kTransShearMenuPosition				400.0

#define kTransSep1MenuPosition				500.0
#define kTransRotate90CWMenuPosition		600.0
#define kTransRotate90CCWMenuPosition		700.0
#define kTransRotate180MenuPosition			800.0
#define kTransSep2MenuPosition				900.0
#define kTransFlipHorzMenuPosition			1000.0
#define kTransFlipVertMenuPosition			1100.0
#define kTransSep3MenuPosition				1200.0
#define kTransClearTransformationsMenuPosition	1300.0

// Transform again submenu
#define	kTransLastAgainMenuPosition					100.0
#define	kTransLastAgainIndividuallyMenuPosition		200.0
#define	kTransAgainMenuPosition		  	 			300.0
#define	kTransAgainIndividuallyMenuPosition		  	400.0

//swatch lib submenu
#define kFirstSwatchLibPanelMenuPosition		100.0
#define kSwatchLibrarySepMenuPosition			200.0
#define kOtherSwatchLibraryMenuPosition			300.0

// PrintGrids submenu
#define kPrintWithGridsMenuPosition			100.0
#define kPrintOnlyGridsMenuPosition			200.0

// Path submenu
#define kJoinEndPointMenuPosition			50.0
#define kOpenPathMenuPosition				100.0
#define kClosedPathMenuPosition				200.0
#define kReversePathMenuPosition			300.0
#define kCompoundPathSepMenuPosition		400.0
#define kMakeCompoundPathMenuPosition		500.0
#define kReleaseCompoundPathMenuPosition	600.0

// Pathfinder submenu
#define kUnionPathMenuPosition					100.0
#define kDifferencePathMenuPosition				200.0
#define kIntersectPathMenuPosition				300.0
#define kXorPathMenuPosition					400.0
#define kReverseDiffPathMenuPosition			500.0

// Convert Shape submenu
#define kNormalRectMenuPosition			100.0
#define kRoundedRectMenuPosition		200.0
#define kBevelRectMenuPosition			300.0
#define kInverseRoundedRectMenuPosition	400.0
// #define kFancyRectMenuPosition		500.0	// Not in menu, not common enough
#define kEllipseMenuPosition			600.0
#define kTriangleMenuPosition			700.0
#define kPolygonMenuPosition			800.0
#define kStraightLineMenuPosition		900.0
#define kOrthogonalLineMenuPosition		1000.0

// Convert Point submenu
#define kLineEndPointMenuPosition			100.0
#define kCornerPointMenuPosition			200.0
#define kSmoothPointMenuPosition			300.0
#define kSymmetricalPointMenuPosition		400.0

// insert break submenu
#define kColumnBreakMenuPosition			100.0
#define kFrameBreakMenuPosition				200.0
#define kPageBreakMenuPosition				300.0
#define kOddPageBreakMenuPosition			400.0
#define kEvenPageBreakMenuPosition			500.0

// change case submenu
#define kCCaseUpperMenuPosition			100.0
#define kCCaseLowerMenuPosition			200.0
#define kCCaseTitleMenuPosition			300.0
#define kCCaseSentenceMenuPosition		400.0

// printerstyles submenu
#define kPrStDefineMenuPosition			100.0
#define kPrStSepMenuPosition			200.0

// DocStyles submenu
#define kDocStyleDefineMenuPosition			100.0
#define kDocStyleSepMenuPosition			200.0

// pdf submenu
#define kPDFDefineMenuPosition			100.0
#define kPDFSepMenuPosition			200.0

// pathtype(TOP) submenu
#define kTOPOptionsMenuPosition			100.0
#define kTOPDeleteMenuPosition			200.0

// library panel sort items submenu
#define kLibSortNameMenuPosition			100.0
#define kLibSortAscendDateMenuPosition		200.0
#define kLibSortDescendDateMenuPosition		300.0
#define kLibSortKindMenuPosition			400.0

// &Graphic submenu
#define kGraphicInfoMenuPosition			100.0
#define kGraphicRevealLinkInOSMenuPosition	300.0
#define kGraphicRevealLinkInBrowserMenuPosition	400.0
#define kGraphicRevealLinkInMiniBridgeMenuPosition 425.0
#define kGraphicRevealLinkInCloudLibrariesMenuPosition 450.0

// Insert Special Character Categories submenus
#define kSpecialSymbolsMenuPosition				100.0
#define kSpecialMarkersMenuPosition				200.0
#define kSpecialHyphensDashesMenuPosition		300.0
#define kSpecialQuotesMenuPosition				400.0
#define kSpecialOtherMenuPosition				500.0


// Insert Special Character submenu
#define kSpecialPageNumMenuPosition				100.0
#define kSpecialNextPageNumMenuPosition			200.0
#define kSpecialPrevPageNumMenuPosition			300.0
#define kSpecialSectionNameMenuPosition			400.0
#define kSpecialCalculatedTextBulletMenuPosition		430.0
#define kSpecialCalculatedTextNumberMenuPosition		435.0
#define kVariableSepMenuPosition							439.0
#define kSpecialFootnoteNumMenuPosition			450.0
#define kSpecialSep1MenuPosition				500.0

#define kSpecialBulletMenuPosition				900.0
#define kSpecialJBulletMenuPosition				950.0
#define kSpecialCopyrightMenuPosition			1000.0
#define kSpecialDegreeMenuPosition				1100.0
#define kSpecialEllipseMenuPosition				1200.0
#define kSpecialNewLineMenuPosition				1300.0
#define kSpecialParaMenuPosition				1400.0
#define kSpecialRegisterMenuPosition			1500.0
#define kSpecialSectionMenuPosition				1600.0
#define kSpecialTrademarkMenuPosition			1700.0
#define kSpecialSep2MenuPosition				1800.0

#define kSpecialSep3MenuPosition				1850.0

#define kSpecialEmDashMenuPosition				1900.0
#define kSpecialEnDashMenuPosition				2000.0
#define kSpecialDiscHyphenMenuPosition			2100.0
#define kSpecialNonBreakHyphMenuPosition		2200.0
#define kParaReturnMenuPosition					2240.0
#define kSpecialSep4MenuPosition				2250.0
#define kSoftReturnMenuPosition					2260.0
#define kSpecialDiscLineBreakMenuPosition		2270.0

#define kSpecialDoubleLeftMenuPosition			2375.0
#define kSpecialDoubleRightMenuPosition			2400.0
#define kSpecialSingleLeftMenuPosition			2500.0
#define kSpecialSingleRightMenuPosition			2600.0
#define kSpecialDoubleMenuPosition				2700.0
#define kSpecialSingleMenuPosition				2750.0
#define kSpecialSep5MenuPosition				2800.0

#define kSpecialInsertTabMenuPosition			2900.0
#define kSpecialRightEdgeTabMenuPosition		2940.0
#define kSpecialIndentHereMenuPosition			2950.0
#define kSpecialSep6MenuPosition				3000.0
#define kSpecialBreakRunInMenuPosition			3100.0

//File: New/Open
#define kNewDocumentMenuPosition			100.0
//#define kNewDocumentFromTemplateMenuPosition			200.0
#define kNewBookMenuPosition				300.0
#define kNewLibraryMenuPosition				400.0
#define kJBXUINewJobBagMenuPosition			500.0

// BookPanelPopup menu
#define kBookUndoMenuPosition					10.0
#define kBookRedoMenuPosition					20.0
#define kBookContentSep0MenuPosition			30.0
#define kBookContentAddMenuPosition				100.0
#define kBookContentReplaceMenuPosition			200.0
#define kBookContentDeleteMenuPosition			300.0
#define kBookContentSep1MenuPosition			400.0
#define kSaveBookPopupMenuPosition				500.0
#define kSaveAsBookPopupMenuPosition			600.0
#define kCloseBookPopupMenuPosition				700.0
#define kBookContentSep2MenuPosition			800.0
#define kPreflightBookPopupMenuPosition			900.0
#define kPackageBookPopupMenuPosition			1000.0
#define kExportBookPopupMenuPosition			1100.0
#define kExportEPubPopupMenuPosition			1199.0
#define kPrintBookPopupMenuPosition				1200.0
#define kBookContentSep3MenuPosition			1300.0
#define kBookContentFileInfoMenuPosition		1400.0
#define kBookContentRevealMenuPosition			1450.0
#define kBookContentSep4MenuPosition			1500.0
#define kSyncBookPopupMenuPosition				1600.0
#define kSyncOptionsBookPopupMenuPosition		1700.0
#define kUpdateXRefInBookMenuPosition			1850.0
#define kBookContentSep7MenuPosition			1860.0
#define kUpdateNumberingInBookMenuPosition		1880.0
#define kBookOptionsPopupMenuPosition			1900.0
#define kSectionNumberingPopupMenuPosition		2000.0
#define kBookContentSep5MenuPosition			2100.0
#define kAutoConvertDocumentPopupMenuPosition   2200.0
#define kMergeLayersPopupMenuPosition			2250.0
#define kBookContentSep6MenuPosition			2300.0
#define kBookContentSmallRowsMenuPosition		2400.0

// BookPanelPopup : Update Numbering
#define kRepaginatePopupMenuPosition			100.0
#define kUpdateChapterNumInBookMenuPosition		200.0
#define kUpdateAllNumberingInBookMenuPosition	300.0

// TOC Popup menu positions
#define kTOCSepBulletMenuPosition			100.0
#define kTOCSepTabMenuPosition				200.0
#define kTOCSepRightEdgeTabMenuPosition	300.0
#define kTOCSepForcedBreakMenuPosition		400.0
#define kTOCSepNextFormatMenuPosition		450.0
#define kTOCSepNonBreakHyphMenuPosition	4000.0
#define kTOCSepSep3MenuPosition			4100.0
#define kTOC1DotsLeaderJMenuPosition	4200.0
#define kTOC2DotsLeaderJMenuPosition	4300.0
#define kTOC3DotsLeaderJMenuPosition	4400.0


//TODO - abolish this when everything has  a position assigned.
#define kUnAssignedMenuPosition								999999.0


// XPEffects submenu
#define kXPUIDropShadowMenuPosition				100.0
#define kXPUIVignetteMenuPosition		200.0

// XMediaUI Popup Menus
#define kTagNewMenuPosition					100.0
#define kTagDeleteMenuPosition				200.0
#define kTagAutoTagTextMenuPosition			250.0
#define kTagSeparator1MenuPosition			300.0
#define kTagOptionsMenuPosition				400.0
#define kTagSeparator2MenuPosition			500.0
#define kTagMapTagsToStylesMenuPosition		600.0
#define kTagMapStylesToTagsMenuPosition		700.0
#define kTagSetTaggingPresetsMenuPosition	800.0
#define kTagDTDOptionsMenuPosition			850.0
#define kTagSeparator3MenuPosition			900.0
#define kTagLoadMenuPosition				1000.0
#define kTagSaveMenuPosition				1100.0
#define kTagImportDTDMenuPosition			1150.0
#define kTagSeparator4MenuPosition			1200.0
#define kTagSelectUnusedMenuPosition		1300.0
#define kTagSeparator5MenuPosition			1400.0
#define kTagSmallRowsMenuPosition			1500.0

// SpreadFlattenSettings submenu
#define kFlattenDocDefaultMenuPosition	100.0
#define kFlattenSep1MenuPosition			200.0
#define kFlattenNoFlattenMenuPosition	300.0
#define kFlattenSep2MenuPosition		400.0
//#define kFlattenLevel1MenuPosition	500.0
#define kFlattenCustomMenuPosition      500.0

// Trapping Style Panel Popup menu
#define kTrapStyleNewMenuPosition				100.0
#define kTrapStyleDuplicateMenuPosition			200.0
#define kTrapStyleDeleteMenuPosition			300.0
#define kTrapStyleSep1MenuPosition				400.0
#define kTrapStyleOptionsMenuPosition			500.0
#define kTrapStyleAssignTrapStyleMenuPosition	600.0
#define kTrapStyleSep2MenuPosition				700.0
#define kTrapStyleLoadStyleMenuPosition			800.0
#define kTrapStyleSelectUnusedMenuPosition		900.0
#define kTrapStyleSep3MenuPosition				1000.0
#define kTrapStyleSmallRowsMenuPosition			1100.0

// Blend Space menu
#define kXPUIBlendDocRGBMenuPosition		100.0
#define kXPUIBlendDocCMYKMenuPosition		200.0

//	Transparency Effects menu
//	Submenu is removed. Both drop shadow and feather is now
//	directly under object menu

// Thesaurus menu
#define kThesMP_Synonyms				100.0
#define kThesMP_Antonyms				200.0
#define kThesMP_ComparedWords			300.0	/* see also */
#define kThesMP_RelatedWords			400.0	/* near synonyms */
#define kThesMP_ContrastWords			500.0	/* near antonyms */

// Table Panel Flyout Menu
#define kTablePanelFlyoutMenuPosShowOpt		100.0
#define kTablePanelFlyoutMenuPosSep1		200.0
#define kTablePanelFlyoutMenuPosCellOpt		300.0
#define kTablePanelFlyoutMenuPosCellOpt1	310.0
#define kTablePanelFlyoutMenuPosCellOpt2	320.0
#define kTablePanelFlyoutMenuPosCellOpt3	330.0
#define kTablePanelFlyoutMenuPosCellOpt4	340.0
#define kTablePanelFlyoutMenuPosCellOpt5	350.0
#define kTablePanelFlyoutMenuPosTableOpt	400.0
#define kTablePanelFlyoutMenuPosTableOpt1	410.0
#define kTablePanelFlyoutMenuPosTableOpt2	420.0
#define kTablePanelFlyoutMenuPosTableOpt3	430.0
#define kTablePanelFlyoutMenuPosTableOpt4	440.0
#define kTablePanelFlyoutMenuPosTableOpt5	450.0
#define kTablePanelFlyoutMenuPosSep0		475.0
#define kTablePanelFlyoutMenuPosInsert		500.0
#define kTablePanelFlyoutMenuPosInsert1		510.0
#define kTablePanelFlyoutMenuPosInsert2		520.0
#define kTablePanelFlyoutMenuPosDelete		600.0
#define kTablePanelFlyoutMenuPosDelete1		610.0
#define kTablePanelFlyoutMenuPosDelete2		620.0
#define kTablePanelFlyoutMenuPosDelete3		630.0
#define kTablePanelFlyoutMenuPosSep2		700.0
#define kTablePanelFlyoutMenuPosMerge		800.0
#define kTablePanelFlyoutMenuPosUnmerge		805.0
#define kTablePanelFlyoutMenuPosSplitH		810.0
#define kTablePanelFlyoutMenuPosSplitV		820.0
#define kTablePanelFlyoutMenuPosConvertToGraphic	825.0
#define kTablePanelFlyoutMenuPosConvertToText		826.0
#define kTablePanelFlyoutMenuPosConvertRows	830.0
#define kTablePanelFlyoutMenuPosHeader		840.0
#define kTablePanelFlyoutMenuPosBody		850.0
#define kTablePanelFlyoutMenuPosFooter		860.0
#define kTablePanelFlyoutMenuPosSep3		900.0
#define kTablePanelFlyoutMenuPosDisRows		1000.0
#define kTablePanelFlyoutMenuPosDisCols		1010.0
#define kTablePanelFlyoutMenuPosSep4		1020.0
#define kTablePanelFlyoutMenuPosEditHeader	1100.0
#define kTablePanelFlyoutMenuPosEditFooter	1110.0

// Table and Cell Styles Flyout Menus
#define kNewTableStyleMenuItemPosition						100.0
#define kDuplicateTableStyleMenuItemPosition				200.0
#define kDeleteTableStyleMenuItemPosition					300.0
#define	kTableStyleSeparator1MenuItemPosition				400.0
#define kRedefineTableStyleMenuItemPosition					500.0
#define kTableStyleSeparator2MenuItemPosition				600.0
#define kTableStyleOptionsMenuItemPosition					700.0
#define kTableStyleSeparator3MenuItemPosition				800.0
#define kTableStyleClearOverridesMenuItemPosition			900.0
#define kClearAttrsNotDefinedByCellStyleMenuItemPosition	950.0
#define kBreakLinkToTableStyleMenuItemPosition				1000.0
#define kTableStyleSeparator4MenuItemPosition				1100.0
#define kLoadTableStylesMenuItemPosition					1200.0
#define kLoadAllTableStylesMenuItemPosition					1300.0
#define kTableStyleSeparator5MenuItemPosition				1400.0
#define	kSelectAllUnusedTableStylesMenuItemPosition			1500.0
#define kTableStyleSeparator6MenuItemPosition				1600.0
#define kNewTableStyleGroupMenuItemPosition					1700.0
#define kOpenAllTableStyleGroupsMenuItemPosition			1800.0
#define kCloseAllTableStyleGroupsMenuItemPosition			1900.0
#define kTableStyleSeparator7MenuItemPosition				2000.0
#define kCopyToTableStyleGroupMenuItemPosition				2100.0
#define kCreateGroupFromTableStylesMenuItemPosition			2200.0
#define kTableStyleSeparator8MenuItemPosition				2300.0
#define kTableStyleSortByNameMenuItemPosition				2400.0
#define kTableStyleSeparator9MenuItemPosition				2500.0
#define kTableStyleSmallPaletteRowsMenuItemPosition			2600.0

// Context menu in Table and Cell Styles menu
#define kRtClkEditTableStyleMenuItemPosition					100.0
#define kRtClkDuplicateTableStyleMenuItemPosition				200.0
#define kRtClkDeleteTableStyleMenuItemPosition				300.0
#define kRtClkRedefineTableStyleMenuItemPosition				400.0
#define kRtClkTableStyleSeparator1MenuItemPosition				500.0
#define kRtClkApplyTableStyleMenuItemPosition					600.0
#define kRtClkApplyStyleClearOverridesMenuItemPosition			700.0
#define kRtClkApplyCellStyleClearAllOverridesMenuItemPosition	750.0
#define kRtClkApplyTableStyleClearCellMenuItemPosition			800.0
#define kRtClkApplyTableStyleClearAllMenuItemPosition			900.0
#define kRtClkTableStyleSeparator2MenuItemPosition				1000.0

#define kRtClkNewTableStyleMenuItemPosition					1100.0
#define kRtClkTableStyleSeparator3MenuItemPosition			1200.0
#define kRtClkTableStyleGroupOptionsMenuItemPosition		1300.0
#define kRtClkDuplicateTableStyleGroupMenuItemPosition		1400.0
#define kRtClkDeleteTableStyleGroupMenuItemPosition			1450.0
#define kRtClkTableStyleSeparator4MenuItemPosition			1500.0
#define kRtClkCopyToTableStyleGroupMenuItemPosition			1600.0
#define kRtClkNewGroupFromTableStylesMenuItemPosition		1700.0

// Info Panel Popup Menu
#define kShowInfoOptionsMenuPosition		100.0
#define kInfoPanelFlyoutMenuPosSep1			125.0
#define kInfoPanelShowContentOffsetMenuPos  150.0
#define kInfoPanelFlyoutMenuPosSep2			200.0
#define kInfoPanelFlyoutMenuPosFileInfo		300.0

#define kInfoPanelFillColorPopupSpacePosition	100.0
#define kInfoPanelFillColorPopupSwatchNamePosition 200.0

#define kInfoPanelStrokeColorPopupSpacePosition	100.0
#define kInfoPanelStrokeColorPopupSwatchNamePosition 200.0


#define kCustomizeKitSeparatorPosition		9998.0
#define kCustomizeKitMenuPosition			9999.0

// Changes menu
#define kTrackChangesMenuPosition			100.0
#define kTCSeparatorPosition1		 		200.0
#define kAllStoriesEnableMenuPosition			300.0
#define kAllStoriesDisableMenuPosition		400.0
#define kTCSeparatorPosition2		 		500.0
#define kTrackChangesPreviousMenuPosition	600.0
#define kTrackChangesNextMenuPosition		700.0
#define kTCSeparatorPosition3		 		800.0
#define kTrackChangesAcceptMenuPosition	 	900.0
#define kTrackChangesRejectMenuPosition	 	1000.0
#define kTCSeparatorPosition4				1100.0
#define kTrackChangesAcceptAndNextMenuPosition	1200.0
#define kTrackChangesRejectAndNextMenuPosition	1300.0
#define kTCSeparatorPosition5				1400.0
#define kTrackChangesAcceptAllMenuPosition	1500.0
#define kTrackChangesRejectAllMenuPosition	1600.0
#define kTCSeparatorPosition6				1700.0
#define kTrackChangesAcceptAllByUserMenuPosition	1800.0
#define kTrackChangesRejectAllByUserMenuPosition	1900.0

// Accept/Reject All [by User] menu
#define kTrackChangesInStoryMenuPosition	100.0
#define kTrackChangesInDocumentMenuPosition	200.0

// Changes panel flyout
#define kChangesSearchStoryMenuPosition		100.0
#define kChangesSearchAllStoryMenuPosition	200.0
#define kChangesSeparator1MenuPosition		300.0
#define kChangesFilterDataTimeMenuPosition	400.0

// Control Strip menu (at the end)
#define kControlStripTextMenuOffset				10000.0
#define kControlStripSeparatorMenuPosition		19995.0
#define kControlStripDockAtTopMenuPosition		19996.0
#define kControlStripDockAtBottomMenuPosition	19997.0
#define kControlStripFloatMenuPosition			19998.0
#define kControlStripSeparator2MenuPosition		19999.0
#define kControlStripCustomizeMenuPosition		20000.0

// Bridge Button menu (in Control Strip)
#define kBridgeBrowseMenuPosition				100.0

// StoryList Panel menu - indesign
#define kSLGoToMenuPosition 					100.0
#define kSLSeparatorMenuPosition1				200.0
#define kSLOpenPackagedAssignmentMenuPosition  210.0
#define kSLSeparatorMenuPosition2				220.0
#define kSLNewAssignmentMenuPosition 			300.0
#define kSLAssignmentOptionMenuPosition 		400.0
#define kSLAddToAssignmentMenuPosition 			500.0
#define kSLAddToNewAssignmentMenuPosition 		100.0	// sub menu
#define kSLSeparatorSubMenuPosition1			200.0	// sub menu
#define kSLRelinkAssignmentMenuPosition			600.0
#define kSLRemoveMenuPosition 					700.0
#define kSLSeparatorMenuPosition3				800.0
#define kSLUpdateSelectedAssignmentsMenuPosition 900.0
#define kSLUpdateOutOfDateAssignmentsMenuPosition 950.0
#define kSLUpdateAllAssignmentsMenuPosition		1000.0
#define kSLSeparatorMenuPosition4				1010.0
#define kSLRevealInFinderMenuPosition			1020.0
#define kSLRevealInBridgeMenuPosition			1030.0
#define kSLSeparatorMenuPosition5				1040.0
#define kSLPackageAssignmentMenuPosition		1050.0
#define kSLPackageAndEmailAssignmentMenuPosition	1055.0
#define kSLCancelPackagedAssignmentMenuPosition	1060.0
#define kSLSeparatorMenuPosition6				1100.0

// StoryList Panel menu - incopy
#define kSLICGoToMenuPosition 					100.0
#define kSLICRevealInFinderMenuPosition			200.0
#define kSLICRevealInBridgeMenuPosition			300.0
#define kSLICSeparatorMenuPosition1				400.0
#define kSLICAssignmentOptionMenuPosition 		500.0
#define kSLICSeparatorMenuPosition2				600.0
#define kSLICOpenPackagedAssignmentMenuPosition  600.0
#define kSLICSeparatorMenuPosition3				800.0
#define kSLICReturnPackagedAssignmentMenuPosition	900.0
#define kSLICReturnAndEmailPackagedAssignmentMenuPosition	950.0
#define kSLICForwardPackagedAssignmentMenuPosition	1000.0
#define kSLICForwardAndEmailPackagedAssignmentMenuPosition	1050.0
#define kSLICSeparator9MenuPosition	975.0
#define kSLICSeparatorMenuPosition4				1100.0

// added to StoryList Panel menu by InCopyBridgeUI
#define kSLICBridgeEditInMenuPosition			1200.0
#define kSLICBridgeSubmitMenuPosition			1300.0
#define kSLICBridgeSubmitAllMenuPosition		1400.0
#define kSLICBridgeRevertMenuPosition			1500.0
#define kSLICBridgeSeparatorMenuPosition		1600.0
#define kSLICBridgeUpdateStoryMenuPosition		1700.0

// added to StoryList Panel menu by InCopyFileActions
#define kSLUpdateDesignMenuPosition				1800.0

// added to StoryList Panel menu by UserNameUI
#define kSLUserSeparatorMenuPosition			1900.0
#define kSLUserMenuPosition						2000.0

// added to InCopy Bridge submenu by AssignmentsUI, before kInCopyBridgeExportMenuPosition 100
#define kSLAddSelToAssignmentMenuPosition 			95
#define kSLAddLayerToAssignmentMenuPosition 		96
#define kSLAddAllStoriesToAssignmentMenuPosition 	97
#define kSLAddAllGraphicsToAssignmentMenuPosition 	98
#define kSLICBridgeSepPosition						99

// InCopy Bridge submenu - new
#define kInCopyBridgeExportMenuPosition		100.0

#define kICBridgeSep1Position				400.0
#define kSaveStoryMenuPosition				500.0

#define kICBridgeSep2Position				600.0
#define kEditInInDesignMenuPosition			700.0
#define kSubmitStoryMenuPosition			800.0
#define kSubmitAllStoriesMenuPosition		900.0

#define kICBridgeSep3Position				1000.0
#define kRevertStoryMenuPosition			1100.0

#define kICBridgeSep4Position				1200.0
#define kUpdateStoryMenuPosition			1300.0
#define kUnembedStoryMenuPosition			1400.0

// InCopy Bridge export submenu
#define kExportSelectionMenuPosition		100.0
#define kExportLayerStoriesMenuPosition		200.0
#define kExportAllStoriesMenuPosition		300.0
#define kExportAllGraphicsMenuPosition		400.0
#define kExportAllItemsMenuPosition			500.0

//	Actions Panel popup menu
#define kActionsNewMenuPosition				100.0
#define kActionsNewSetMenuPosition			200.0
#define kActionsDuplicateMenuPosition		300.0
#define kActionsDeleteMenuPosition			400.0
#define kActionsPlayMenuPosition			500.0

#define kActionsSep1MenuPosition			600.0
#define kActionsStartRecordMenuPosition		700.0
#define kActionsSep2MenuPosition			800.0
#define kActionsOptionsMenuPosition			900.0

#define kActionsPlaybackOptionsMenuPosition	1000.0
#define kActionsSep3MenuPosition			1100.0

#define kActionsClearAllMenuPosition		1200.0
#define kActionsResetMenuPosition			1300.0
#define kActionsLoadMenuPosition			1400.0
#define kActionsSaveMenuPosition			1410.0
#define kActionsSep4MenuPosition			1500.0

#define kActionsExportFileTempMenuPosition	1600.0

// Position marker submenu
#define kSetPositionMarkerMenuPosition		100.0
#define kClearPositionMarkerMenuPosition	110.0
#define kPositionMarkerSepSubMenuPosition	120.0
#define kGotoPositionMarkerMenuPosition		130.0

// FootnoteMetaCharPopupMenus
#define kFNMetaTabMenuPosition						100.0			// Separator

#define kFNMetaLeftParenMenuPosition				100.0		// Prefix
#define kFNMetaLeftBracketMenuPosition			200.0		// Prefix
#define kFNMetaHairSpaceMenuPosition				300.0		// Prefix
#define kFNMetaThinSpaceMenuPosition				400.0		// Prefix
#define kFNMetaJOpenParenMenuPosition			500.0		// Prefix
#define kFNMetaJOpenSquareBracketMenuPosition	600.0		// Prefix
#define kFNMetaJOpenSquareQuoteMenuPosition	700.0		// Prefix
#define kFNMetaJOpenThickBracketMenuPosition	800.0		// Prefix
#define kFNMetaJKomeMarkMenuPosition			900.0		// Prefix
#define kFNMetaJAsteriskMenuPosition				1000.0		// Prefix
#define kFNMetaJCircleMenuPosition					1100.0		// Prefix
#define kFNMetaJChuuMenuPosition					1200.0		// Prefix
#define kFNMetaJTradChuuMenuPosition				1300.0		// Prefix

#define kFNMetaRightParenMenuPosition				100.0		// Suffix
#define kFNMetaRightBracketMenuPosition			200.0		// Suffix
#define kFNMetaJCloseParenMenuPosition			300.0		// Suffix
#define kFNMetaJCloseSquareBracketMenuPosition	400.0		// Suffix
#define kFNMetaJCloseSquareQuoteMenuPosition	500.0		// Suffix
#define kFNMetaJCloseThickBracketMenuPosition	600.0		// Suffix

// EndnoteMetaCharPopupMenus
#define kENMetaTabMenuPosition						100.0			// Separator

#define kENMetaLeftParenMenuPosition				100.0		// Prefix
#define kENMetaLeftBracketMenuPosition			200.0		// Prefix
#define kENMetaHairSpaceMenuPosition				300.0		// Prefix
#define kENMetaThinSpaceMenuPosition				400.0		// Prefix
#define kENMetaJOpenParenMenuPosition			500.0		// Prefix
#define kENMetaJOpenSquareBracketMenuPosition	600.0		// Prefix
#define kENMetaJOpenSquareQuoteMenuPosition	700.0		// Prefix
#define kENMetaJOpenThickBracketMenuPosition	800.0		// Prefix
#define kENMetaJKomeMarkMenuPosition			900.0		// Prefix
#define kENMetaJAsteriskMenuPosition				1000.0		// Prefix
#define kENMetaJCircleMenuPosition					1100.0		// Prefix
#define kENMetaJChuuMenuPosition					1200.0		// Prefix
#define kENMetaJTradChuuMenuPosition				1300.0		// Prefix

#define kENMetaRightParenMenuPosition				100.0		// Suffix
#define kENMetaRightBracketMenuPosition			200.0		// Suffix
#define kENMetaJCloseParenMenuPosition			300.0		// Suffix
#define kENMetaJCloseSquareBracketMenuPosition	400.0		// Suffix
#define kENMetaJCloseSquareQuoteMenuPosition	500.0		// Suffix
#define kENMetaJCloseThickBracketMenuPosition	600.0		// Suffix

// JobBag (kJBXUIJobBagPanelPopup)
#define kJBXUIAddFileMenuPosition				300.0
#define kJBXUISyncWithFolderMenuPosition		500.0
#define kJBXUIRemoveSelectedMenuPosition		600.0
#define kJBXUISeparator1MenuPosition			700.0
#define kJBXUIPlaceAndLinkResourceMenuPosition	800.0
#define kJBXUIEditOriginalMenuPosition			900.0
#define kJBXUISeparator2MenuPosition			1000.0
#define kJBXUIExtractAllForEditMenuPosition		1100.0
#define kJBXUIArchiveAllMenuPosition			1200.0
#define kJBXUISeparator3MenuPosition			1300.0
#define kJBXUIRevealInBridgeMenuPosition		1400.0
#define kJBXUIRevealInFinderMenuPosition		1500.0
#define kJBXUISeparator4MenuPosition			1600.0
#define kJBXUISortByStructureMenuPosition		1700.0
#define kJBXUISortByTypeMenuPosition			1800.0
#define kJBXUISeparator5MenuPosition			1900.0
#define kJBXUIListViewMenuPosition				2000.0
#define kJBXUIThumbnailViewPosition				2100.0

// Job bag palette context menu.
#define kJBXUIAddFilePosition					100.0
#define kJBXUISyncWithFolderPosition			200.0
#define kJBXUIRemoveSelectedPosition			300.0
#define kJBXUISeparator1Position				400.0
#define kJBXUIPlaceAndLinkResourcePosition		500.0
#define kJBXUIEditOriginalPosition				600.0
#define kJBXUISeparator2Position				700.0
#define kJBXUIRevealInBridgePosition			800.0
#define kJBXUIRevealInFinderPosition			900.0

#define kTVBulletMenuPosition						200.0
#define kTVJBulletMenuPosition					300.0
#define kTVCopyrightMarkMenuPosition			400.0
#define kTVEllipseMenuPosition						500.0
#define kTVParagraphReturnMenuPosition			600.0
#define kTVRegistrationMarkMenuPosition		700.0
#define kTVSectionMarkMenuPosition				800.0
#define kTVTrademarkMenuPosition				900.0

#define kTVTESectionNameMenuPosition			3600.0

// Date popout Menu (Variables)
#define kTVDateTimeMenuPosition							100.0
#define kTVDateDayMenuPosition							200.0
#define kTVDateMonthMenuPosition						300.0
#define kTVDateYearMenuPosition							400.0

#define kTVDateTimeHourMenuPosition					100.0
#define kTVDateTimeHour01MenuPosition				200.0
#define kTVDateTimeHour24MenuPosition				300.0
#define kTVDateTimeHour024MenuPosition				400.0
#define kTVDateTimeMinuteMenuPosition				500.0
#define kTVDateTimeMenuMinute00Position				600.0
#define kTVDateTimeSecondMenuPosition				700.0
#define kTVDateTimeSecond00MenuPosition				800.0
#define kTVDateTimeampmMenuPosition					900.0
#define kTVDateTimeampmShortMenuPosition			1000.0
#define kTVDateTimeAMPMMenuPosition					1100.0
#define kTVDateTimeAMPMShortMenuPosition			1200.0
#define kTVDateTimeZoneLongPosition					1300.0
#define kTVDateTimeZoneShortPosition				1400.0

#define kTVDateDayNumberMenuPosition			100.0
#define kTVDateDayNumber01MenuPosition			200.0
#define kTVDateDayNumberRomanLowerMenuPosition	300.0
#define kTVDateDayNumberRomanUpperMenuPosition	400.0
#define kTVDateDayNameMenuPosition				500.0
#define kTVDateDayNameShortMenuPosition			600.0

#define kTVDateMonthNumberMenuPosition				100.0
#define kTVDateMonthNumber01MenuPosition			200.0
#define kTVDateMonthNameMenuPosition				300.0
#define kTVDateMonthNameShortMenuPosition			400.0

#define kTVDateYearLongMenuPosition					100.0
#define kTVDateYearShortMenuPosition					200.0
#define kTVDateYearTeenyMenuPosition					300.0
#define kTVDateYearRomanLowerMenuPosition			400.0
#define kTVDateYearRomanUpperMenuPosition			500.0
#define kTVDateYearEraShortMenuPosition				700.0


// BN Number Edit Box popup menu positions
#define kBNNumberMetaSpecialCharacterMenuPosition			100.0
#define kBNNumberMetaLevelPlaceholderMenuPosition			200.0

#define kBNNumberMetaTabMenuPosition						100.0
#define kBNNumberMetaMSpaceMenuPosition						200.0
#define kBNNumberMetaNSpaceMenuPosition						300.0
#define kBNNumberMetaEmDashMenuPosition						400.0
#define kBNNumberMetaEnDashMenuPosition						500.0

#define kBNNumberMetaSep3MenuPosition						1000.0

#define kBNNumberMetaParagraphSymbolMenuPosition			1100.0
#define kBNNumberMetaSectionSymbolMenuPosition				1200.0
#define kBNNumberMetaBulletCharacterMenuPosition			1300.0
#define kBNNumberMetaEllipsisMenuPosition					1400.0

#define kBNNumberMetaSep4MenuPosition						2000.0

#define kBNNumberMetaHairSpaceMenuPosition					2100.0
#define kBNNumberMetaThinSpaceMenuPosition					2200.0
#define kBNNumberMetaFigureSpaceMenuPosition				2300.0
#define kBNNumberMetaPunctuationSpaceMenuPosition			2400.0

#define kBNNumberMetaSep5MenuPosition						3000.0

#define kBNNumberMetaIdeographicSpaceMenuPosition		3100.0
#define kBNNumberMetaQuarterSpaceMenuPosition			3200.0

#define kBNNumberMetaJOpenParenMenuPosition				3300.0
#define kBNNumberMetaJOpenSquareBracketMenuPosition		3400.0
#define kBNNumberMetaJOpenSquareQuoteMenuPosition		3500.0
#define kBNNumberMetaJOpenThickBracketMenuPosition		3600.0
#define kBNNumberMetaJKomeMarkMenuPosition				3700.0
#define kBNNumberMetaJAsteriskMenuPosition				3800.0
#define kBNNumberMetaJCircleMenuPosition				3900.0
#define kBNNumberMetaJChuuMenuPosition					4000.0
#define kBNNumberMetaJTradChuuMenuPosition				4100.0
#define kBNNumberMetaJCloseParenMenuPosition			4200.0
#define kBNNumberMetaJCloseSquareBracketMenuPosition	4300.0
#define kBNNumberMetaJCloseSquareQuoteMenuPosition		4400.0
#define kBNNumberMetaJCloseThickBracketMenuPosition		4500.0


// Level Placeholders submenu

#define kBNNumberMetaCurrentLevelPlaceholderMenuPosition	100.0
#define kBNNumberMetaLevelPlaceholderSep1MenuPosition		200.0
#define kBNNumberMetaLevelPlaceholder1MenuPosition			300.0
#define kBNNumberMetaLevelPlaceholder2MenuPosition	        400.0
#define kBNNumberMetaLevelPlaceholder3MenuPosition		    500.0
#define kBNNumberMetaLevelPlaceholder4MenuPosition			600.0
#define kBNNumberMetaLevelPlaceholder5MenuPosition			700.0
#define kBNNumberMetaLevelPlaceholder6MenuPosition			800.0
#define kBNNumberMetaLevelPlaceholder7MenuPosition			900.0
#define kBNNumberMetaLevelPlaceholder8MenuPosition			1000.0
#define kBNNumberMetaLevelPlaceholder9MenuPosition			1100.0
#define kBNNumberMetaLevelPlaceholderSep2MenuPosition		1200.0
#define kBNNumberMetaChapterNoPlaceholderMenuPosition		1300.0

// Bulleted and Numbered List submenu
#define kApplyRemoveBulletsTypeMenuPosition				100.0
#define kApplyRemoveNumbersTypeMenuPosition				200.0
#define kRestartNumberingTypeMenuPosition				300.0
#define kConvertBNTypeMenuPosition						400.0
#define kDefineListTypeMenuPosition						500.0
//#define kContinueNumberingTypeMenuPosition				200.0

// Links Panel context menu
#define kContextRestoreLinkMenuPosition					100.0
#define kContextGotoLinkMenuPosition					200.0
#define kContextPanelEditOriginalMenuPosition			300.0
#define kContextPanelEditOriginalWithMenuPosition		350.0
#define kContextPanelGoToSourceMenuPosition				375.0
#define kContextUpdateLinkMenuPosition					400.0
#define kContextLink1SepMenuPosition					500.0
#define kContextRevealLinkInOSMenuPosition				600.0
#define kContextRevealLinkInBrowserMenuPosition			700.0
#define kContextLink2SepMenuPosition					800.0
#define kContextUnlinkMenuPosition						900.0
#define kContextLink3SepMenuPosition					1000.0
#define kContextLinkFileInfoMenuPosition				1100.0
#define kContextLinkInfoMenuPosition					1200.0
#define kContextLink4SepMenuPosition					1300.0
#define kContextLinkSortStatusMenuPosition				1400.0
#define kContextLinkSortNameMenuPosition				1500.0
#define kContextLinkSortPageMenuPosition				1600.0
#define kContextLinkSortTypeMenuPosition				1700.0

// Rules Panel flyout menu
#define kNewRuleMenuPosition							100.0
#define kNewRuleSetMenuPosition							200.0
#define kDuplicateRuleOrRuleSetMenuPosition				300.0
#define kDeleteRuleOrRuleSetMenuPosition				400.0
#define kRulesPanelSep1MenuPosition						500.0
#define kRuleOrRuleSetOptionsMenuPosition				600.0
#define kRulesPanelSep2MenuPosition						700.0
#define kApplyRuleMenuPosition							800.0
#define kApplyRuleSetMenuPosition						900.0
#define kRulesPanelSep3MenuPosition						1000.0
#define kLoadRuleSetMenuPosition						1040.0
#define kRulesPanelSep4MenuPosition						1070.0
#define kNamesOnlyMenuPosition							1100.0
#define kNamesAndRuleSetDescriptionsMenuPosition		1200.0
#define kNamesAndAllDescriptionsMenuPosition			1300.0

// Rules Panel context menu
#define kContextDuplicateRuleOrRuleSetMenuPosition		100.0
#define kContextDeleteRuleOrRuleSetMenuPosition			200.0
#define kContextRulesPanelSep1MenuPosition				300.0
#define kContextRuleOrRuleSetOptionsMenuPosition		400.0
#define kContextRulesPanelSep2MenuPosition				500.0
#define kContextApplyRuleMenuPosition					600.0
#define kContextApplyRuleSetMenuPosition				700.0

// Quick apply preferences menu
#define kQuickApplyParagraphStylePrefsMenuPosition			100.0
#define kQuickApplyCharacterStylesPrefsMenuPosition			200.0
#define kQuickApplyObjectStylesPrefsMenuPosition			300.0
#define kQuickApplyMenuActionsPrefsMenuPosition				400.0
#define kQuickApplyScriptsPrefsMenuPosition					500.0
#define kQuickApplyTableStylesPrefsMenuPosition				600.0
#define kQuickApplyTextVariablesPrefsMenuPosition			700.0
#define kQuickApplyCellStylesPrefsMenuPosition				800.0
// TODO Para, Char, and Object are not yet used
#define kQuickApplyParagraphStyleGroupsPrefsMenuPosition	900.0
#define kQuickApplyCharacterStyleGroupsPrefsMenuPosition	1000.0
#define kQuickApplyObjectStyleGroupsPrefsMenuPosition		1100.0
#define kQuickApplyTableStyleGroupsPrefsMenuPosition		1200.0
#define kQuickApplyCellStyleGroupsPrefsMenuPosition			1300.0
#define kQuickApplyConditionsPrefsMenuPosition				1310.0
#define kQuickApplyConditionSetsPrefsMenuPosition			1320.0
#define kQuickApplySeperator1MenuPosition					2000.0
#define kQuickApplyShowHiddenUIPrefsMenuPosition			2001.0

//	Basil Preflight
#define kPreflightManageProfileMenuPosition					100.0
#define	kPreflightOptionsMenuPosition						200.0
#define kPreflightSeparator1MenuPosition					300.0
#define kPreflightDocSummaryMenuPosition					400.0	//	Dropped for Basil
#define kPreflightSaveReportMenuPosition					500.0
#define kPreflightSeparator2MenuPosition					600.0
#define kPreflightErrorRowsPrefsMenuPosition				700.0
#define kPreflightSeparator3MenuPosition					800.0
#define kPreflightGlobalOffMenuPosition						900.0

// Conditional Text Panel flyout menu
#define kCondTextConditionSetOptionsMenuPosition			90.0
#define kCondTextConditionSetOptionsSeparatorMenuPosition	95.0
#define kCondTextNewConditionTagMenuPosition				120.0
#define kCondTextDeleteConditionMenuPosition				130.0
#define kCondTextEditSeparatorMenuPosition					140.0
#define kCondTextEditConditionMenuPosition					150.0
#define kCondTextShowHideSeparatorMenuPosition				160.0
#define kCondTextShowAllTagsMenuPosition					165.0
#define kCondTextHideAllTagsMenuPosition					170.0
#define kCondTextLoadSeparatorMenuPosition					200.0
#define kCondTextLoadConditionTagsMenuPosition				300.0
#define kCondTextLoadConditionTagsAndSetsMenuPosition		400.0
#define kCondTextSelectUnusedSeparatorMenuPosition			500.0
#define kCondTextSelectUnusedConditionsMenuPosition			600.0

// Condition Tag TV Node context menu
#define kCondTagItemUnapplyRtMenuPosition					100.0
#define kCondTagItemEditRtMenuPosition						200.0
#define kCondTagItemDeleteRtMenuPosition					300.0

//Article Popup Menu Positions
#define kArticlePanelNewArticleMenuPosition					100.0
#define kArticlePanelDeleteArticleMenuPosition				110.0
#define kArticlePanelSepeMenuPosition						200.0
#define kArticlePanelArticleOptionsMenuPosition				201.0
#define kArticlePanelSepe3MenuPosition						202.0
#define kArticlePanelGoToItemMenuPosition					210.0
#define kArticlePanelSepe1MenuPosition						220.0
#define kArticlePanelUseForPDFStructureOrderMenuPosition	225.0
#define kArticlePanelSepe2MenuPosition						226.0
#define kArticlePanelAddSelectionMenuPosition				230.0
#define kArticlePanelAddDocumentContentMenuPosition			240.0

//Sync Settings Sub Menu Postitons
#define kSyncSettingsSyncNowMenuPosition					90.0
#define kSyncSettingsStatusMenuPosition						100.0
#define kSyncSettingsSepMenuPosition						200.0
#define kSyncSettingsManageSettingsMenuPosition				300.0
#define kSyncSettingsManageAccountMenuPosition				400.0

#endif // __AdobeMenuPositions__

