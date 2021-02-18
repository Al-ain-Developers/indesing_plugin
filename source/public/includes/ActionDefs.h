//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ActionDefs.h $
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
//========================================================================================

#pragma once
#ifndef __ACTIONDEFS__
#define __ACTIONDEFS__

/**	@name Standard enabling types 
	@memo Standard enabling types - can be OR'ed together. These allow the action manager to enable/disable actions with simple
		enabling requirements.
		for example - (kNeedOpenDocument | kCustomEnabling) means the item will be disabled by the action manager
		unless there is an open document, in which case the action component will be called to finish the enabling 
**/

//@{

	/**	kAlwaysDisabled - Item is always disabled. Rarely used, but can be used by an IActionFilter to permanantly disable certain items. */
	const int16 kAlwaysDisabled 					=	0;	

	/** kCustomEnabling - If all the standard enabling returns true, this will cause IActionComponent::UpdateActionStates to be called to complete the enabling */
	const int16 kCustomEnabling 					=	1;	

	/**	kAlwaysEnabled - Action is always enabled. */
	const int16 kAlwaysEnabled 						=	2;

	/**	kDisableIfNoFrontDocument - Action is disabled if no front document exists. */
	const int16 kDisableIfNoFrontDocument 			=	4;

	/**	kDisableIfSelectionDoesNotSupportIID - Action is disabled if the current selection does not support a specific IID, which is specified seperately. */
	const int16 kDisableIfSelectionDoesNotSupportIID=	8;

	/**	kDisableIfLowMem - Action is disabled if the application is currently in a low memory state */
	const int16 kDisableIfLowMem			 		=	128;

	/**	kEnableEvenDuringDialogs - Action is enabled even when modal dialogs are up. Any action which does not specify this is automatically disabled by modal dialogs */
	const int16 kEnableEvenDuringDialogs			=	256; 

	/**	kDisableIfNoFrontLayoutView - Action is disabled if no front layout window exists. More explicit than kDisableIfNoFrontDocument (and now possible with an XML Structure view) */
	const int16 kDisableIfNoFrontLayoutView			=	512; 
	
	/** kDisableIfQuickApply - Action is disabled if the quick apply dialog is asking **/
	const int16 kDisableIfQuickApply				=	1024;

//@}

/**@name Types of actions */

//@{

	/** kNormalAction is a regular action */
	const int16 kNormalAction	=	0;		

	/** Actions of type kPreNotify only work if someone else registers the same ActionID as kNormalAction. The IActionComponent
		for the kPreNotify gets called before the IActionComponent for the regular action */
	const int16 kPreNotify		=	1;	
		
	/** Actions of type kPostNotify only work if someone else registers the same ActionID as kNormalAction. The IActionComponent
		for the kPostNotify gets called after the IActionComponent for the regular action */
	const int16 kPostNotify		=	2;		
//@}

// menu defs

/** Menu names preceeded by kDontTranslateChar won't be translated */
const textchar kDontTranslateChar = 0x002E/*kTextChar_Period*/;

/**@name Types of menu items */

//@{

	/** kNormalMenuItemType is a standard menu item */
	const int16 kNormalMenuItemType		=	0 ;

	/** kDynamicMenuItemType indicates that this menu item requires a call to 'IDynamicMenu::RebuildMenu' before menu enable/display */
	const int16 kDynamicMenuItemType 	=	1 ;

	/** kOwnerDrawMenuItemType indicates that this menu item is drawn by the IOwnerDrawItem interface on the action component instead of being drawn by platform menu code */
	const int16 kOwnerDrawMenuItemType	=	2 ;

//@}

// standard 'area names'
#define kAlertsActionArea									"KBSCE Alerts"
#define kDocumentsActionArea								"KBSCE Documents"
#define kEditMenuActionArea									"KBSCE Edit menu"
#define kEditMenuInCopyActionArea							"KBSCE Edit menu: InCopy: "
#define kEditMenuInCopyExportActionArea						"KBSCE Edit menu: InCopy: Export: "
#define kEditMenuInCopyAddSelectionToAssignmentActionArea	"KBSCE Edit menu: InCopy: Add Selection to Assignment: "
#define kEditMenuInCopyAddLayerToAssignmentActionArea		"KBSCE Edit menu: InCopy: Add Layer to Assignment: "
#define kEditMenuInCopyAddAllStoriesToAssignmentActionArea	"KBSCE Edit menu: InCopy: Add All Stories to Assignment: "
#define kEditMenuInCopyAddAllGraphicsToAssignmentActionArea	"KBSCE Edit menu: InCopy: Add All Graphics to Assignment: "
#define kEditMenuPositionMarkerActionArea		"KBSCE Edit menu: Position Marker: "
#define kEditMenuPreferencesActionArea			"KBSCE Edit menu: Preferences: "
#define kEditMenuTransparencyBlendSpaceActionArea	"KBSCE Edit menu: Transparency Blend Space: "
#define kEditMenuSpellingActionArea				"KBSCE Edit menu: Spelling: "
#define kApplicationMenuActionArea				"KBSCE Application menu"
#define kFileMenuActionArea						"KBSCE File menu"
#define kFileMenuManageWorkgroupActionArea		"KBSCE File menu: Manage Workgroup: "
#define kFileMenuNewActionArea					"KBSCE File menu: New: "
#define kFileMenuPDFStyleActionArea				"KBSCE File menu: PDF Style: "
#define kFileMenuPrinterStyleActionArea			"KBSCE File menu: Printer Style: "
#define kFileMenuDocumentPresetsActionArea		"KBSCE File menu: Document Presets: "
#define kHelpMenuActionArea						"KBSCE Help menu"
#define kAppleMenuActionArea					"KBSCE Apple menu"
#define kJapaneseTypographyActionArea			"KBSCE Japanese Typography"
#define kLayoutMenuActionArea					"KBSCE Layout menu"
#define kLayoutMenuPagesActionArea				"KBSCE Layout menu: Pages: "
#define kLinksActionArea						"KBSCE Links"
#define kNotesMenuActionArea					"KBSCE Notes menu"
#define kObjectEditingActionArea				"KBSCE Object editing"
#define kObjectMenuActionArea					"KBSCE Object menu"
#define kObjectMenuArrangeActionArea			"KBSCE Object menu: Arrange: "
#define kObjectMenuSelectObjectActionArea		"KBSCE Object menu: Select: "
#define kObjectMenuPathFinderActionArea			"KBSCE Object menu: Pathfinder: "
#define kObjectMenuConvertShapeActionArea		"KBSCE Object menu: Convert Shape: "
#define kObjectMenuCaptionActionArea		"KBSCE Object menu: Captions: "
#define kObjectMenuPathsActionArea				"KBSCE Object menu: Paths: "
#define kObjectMenuContentActionArea			"KBSCE Object menu: Content: "
#define kObjectMenuConvertPointActionArea		"KBSCE Object menu: Paths: Convert Point: "
#define kObjectMenuDisplayActionArea			"KBSCE Object menu: Display: "
#define kObjectMenuFittingActionArea			"KBSCE Object menu: Fitting: "
#define kObjectMenuTransformActionArea			"KBSCE Object menu: Transform: "
#define kObjectMenuTransformAgainActionArea		"KBSCE Object menu: Transform Again: "
#define kObjectMenuAnchoredObjectActionArea		"KBSCE Object menu: Anchored Object: "
#define kObjectMenuInteractiveActionArea		"KBSCE Object menu: Interactive: "
#define kObjectMenuEffectsActionArea			"KBSCE Object menu: Effects: "
#define kClipPathMenuActionArea					"KBSCE Object menu: Clipping Path: "
#define kOnlineActionArea						"KBSCE Online"
#define kOtherActionArea						"KBSCE Other"
#define kPaletteMenusActionArea					"KBSCE Palette Menus"
#define kPaletteMenusAlignActionArea			"KBSCE Palette Menus: Align: "
#define kPaletteMenusBookActionArea				"KBSCE Palette Menus: Book: "
#define kPaletteMenusBookmarksActionArea		"KBSCE Palette Menus: Bookmarks: "
#define kPaletteMenusCellStylesActionArea		"KBSCE Palette Menus: Cell Styles: "
#define kPaletteMenusCharacterStylesActionArea	"KBSCE Palette Menus: Character Styles: "
#define kPaletteMenusCharacterActionArea		"KBSCE Palette Menus: Character: "
#define kPaletteMenusCharacterOpenTypeActionArea	"KBSCE Palette Menus: Character: OpenType: "
#define kPaletteMenusColorActionArea			"KBSCE Palette Menus: Color: "
#define kPaletteMenusControlActionArea			"KBSCE Palette Menus: Control: "
#define kPaletteMenusControlBridgeActionArea	"KBSCE Palette Menus: Control: Bridge: "
#define kPaletteMenusGlyphActionArea			"KBSCE Palette Menus: Glyph: "
#define kPaletteMenusGradientActionArea			"KBSCE Palette Menus: Gradient: "
#define kPaletteMenusHyperlinksActionArea		"KBSCE Palette Menus: Hyperlinks: "
#define kPaletteMenusCrossReferencesActionArea	"KBSCE Palette Menus: Cross-References: "
#define kPaletteMenusPageTransitionsActionArea	"KBSCE Palette Menus: Page Transitions: "
#define kPaletteMenusHTMLPreviewActionArea		"KBSCE Palette Menus: HTML Preview: "
#define kPaletteMenusLiquidLayoutActionArea		"KBSCE Palette Menus: Liquid Layout: "
#define kPaletteMenusTimingActionArea			"KBSCE Palette Menus: Timing: "
#define kPaletteMenusMediaActionArea			"KBSCE Palette Menus: Media: "
#define kPaletteMenusAnimationUIActionArea		"KBSCE Palette Menus: Animation UI: "
#define kPaletteMenusIndexActionArea			"KBSCE Palette Menus: Index: "
#define kPaletteMenusInfoActionArea				"KBSCE Palette Menus: Info: "
#define kPaletteMenusJBXUIActionArea			"KBSCE Palette Menus: Job Bag UI: "
#define kPaletteMenusDocStatusActionArea		"KBSCE Palette Menus: Layout Window Status menu: "
#define kPaletteMenusLibraryActionArea			"KBSCE Palette Menus: Library: "
#define kPaletteMenusLinksActionArea			"KBSCE Palette Menus: Links: "
#define kPaletteMenusLinksSelectionActionArea	"KBSCE Palette Menus: Links: Selection: "
#define kPaletteMenusNamedGridsActionArea		"KBSCE Palette Menus: Named Grids: "
#define kPaletteMenusNavigatorActionArea		"KBSCE Palette Menus: Navigator: "
#define kPaletteMenusObjectStylesActionArea		"KBSCE Palette Menus: Object Styles: "
#define kPaletteMenusPagesActionArea			"KBSCE Palette Menus: Pages: "
#define kPaletteMenusPagesRotateSpreadActionArea	"KBSCE Palette Menus: Pages: Rotate Spread: "
#define kPaletteMenusPagesSpreadFlatteningActionArea	"KBSCE Palette Menus: Pages: Spread Flattening: "
#define kPaletteMenusPagesAttributesActionArea	"KBSCE Palette Menus: Pages: Attributes: "
#define kPaletteMenusParagraphStylesActionArea	"KBSCE Palette Menus: Paragraph Styles: "
#define kPaletteMenusParagraphActionArea		"KBSCE Palette Menus: Paragraph: "
#define kPaletteMenusButtonsActionArea			"KBSCE Palette Menus: Buttons: "
#define kPaletteMenusButtonsActionsActionArea	"KBSCE Palette Menus: Buttons: Actions: "
#define kPaletteMenusObjectStatesActionArea		"KBSCE Palette Menus: Object States: "
#define kPaletteMenusStrokeActionArea			"KBSCE Palette Menus: Stroke: "
#define kPaletteMenusSwatchesActionArea			"KBSCE Palette Menus: Swatches: "
#define kPaletteMenusTabActionArea				"KBSCE Palette Menus: Tab: "
#define kPaletteMenusTableStylesActionArea		"KBSCE Palette Menus: Table Styles: "
#define kPaletteMenusTableActionArea			"KBSCE Palette Menus: Table: "
#define kPaletteMenusTagActionArea				"KBSCE Palette Menus: Tag: "
#define kPaletteMenusTextWrapActionArea			"KBSCE Palette Menus: Text Wrap: "
#define kPaletteMenusTransformActionArea		"KBSCE Palette Menus: Transform: "
#define kPaletteMenusEffectsActionArea			"KBSCE Palette Menus: Effects: "
#define kPaletteMenusTrapStyleActionArea		"KBSCE Palette Menus: Trap Style: "
#define kPaletteMenusLayerActionArea			"KBSCE Palette Menus: Layer: "
#define kPaletteMenusNotesActionArea			"KBSCE Palette Menus: Notes: "
#define kPaletteMenusThesaurusActionArea		"KBSCE Palette Menus: Thesaurus: "
#define kPaletteMenusCopyfitInfoActionArea		"KBSCE Palette Menus: Copyfit Info: "
#define kPaletteMenusSepPrvActionArea			"KBSCE Palette Menus: Separations Preview: "
#define kPaletteMenusFlatPrvActionArea			"KBSCE Palette Menus: Flattener Preview: "
#define kPaletteMenusStoryListActionArea		"KBSCE Palette Menus: Assignment: "
#define kPaletteMenusStoryListAddToAssignmentActionArea	"KBSCE Palette Menus: Assignment: Add to Assignment: "
#define kPaletteMenusSuppressedUIActionArea		"KBSCE Palette Menus: Suppressed UI: "
#define kPaletteMenusDocPreflightActionArea		"KBSCE Palette Menus: Layout Window Preflight Menu: "
#define kStructureMenuActionArea				"KBSCE Structure menu"
#define kStructureNavigationActionArea			"KBSCE Structure navigation"
#define kTablesMenuActionArea					"KBSCE Table menu"
#define kTablesMenuCellOptionsActionArea		"KBSCE Table menu: Cell Options: "
#define kTablesMenuDeleteActionArea				"KBSCE Table menu: Delete: "
#define kTablesMenuInsertActionArea				"KBSCE Table menu: Insert: "
#define kTablesMenuSelectActionArea				"KBSCE Table menu: Select: "
#define kTablesMenuTableOptionsActionArea		"KBSCE Table menu: Table Options: "
#define kTestMenuActionArea						"KBSCE Test Menu"
#define kTestingActionArea						"KBSCE Testing"
#define kTextAndTablesActionArea				"KBSCE Text and Tables"
#define kTextSelectionActionArea				"KBSCE Text Selection"
#define kToolsActionArea						"KBSCE Tools"
#define kToolsLoupeActionArea					"KBSCE Tools: Magnify Tool: "
#define kTypeMenuActionArea						"KBSCE Type menu"
#define kTypeNotesMenuActionArea				"KBSCE Type menu: NotesSubmenu: "
#define kTypeChangesMenuActionArea				"KBSCE Type menu: ChangesSubmenu: "
#define kTypeAcceptAllChangesMenuActionArea				"KBSCE Type menu: ChangesSubmenu: AcceptAllSubMenu: "
#define kTypeRejectAllChangesMenuActionArea				"KBSCE Type menu: ChangesSubmenu: RejectAllSubMenu: "
#define kTypeAcceptChangesByUserMenuActionArea				"KBSCE Type menu: ChangesSubmenu: AcceptByUserSubMenu: "
#define kTypeRejectChangesByUserMenuActionArea				"KBSCE Type menu: ChangesSubmenu: RejectByUserSubMenu: "
#define kTypeMenuTextVariablesActionArea		"KBSCE Type menu: Text Variables: "
#define kTypeMenuBNListActionArea				"KBSCE Type menu: Bulleted & Numbered Lists: "
#define kTypeMenuChangeCaseActionArea			"KBSCE Type menu: Change Case: "
#define kTypeMenuInsertBreakCharacterActionArea	"KBSCE Type menu: Insert Break Character: "
#define kTypeMenuInsertSpecialSymbolsActionArea	"KBSCE Type menu: Insert Special Character: Symbols: "
#define kTypeMenuInsertSpecialMarkersActionArea	"KBSCE Type menu: Insert Special Character: Markers: "
#define kTypeMenuInsertSpecialHyphensAndDashesActionArea	"KBSCE Type menu: Insert Special Character: Hyphens and Dashes: "
#define kTypeMenuInsertSpecialQuotationMarksActionArea	"KBSCE Type menu: Insert Special Character: Quotation Marks: "
#define kTypeMenuInsertSpecialOtherActionArea	"KBSCE Type menu: Insert Special Character: Other: "
#define kTypeMenuInsertWhiteSpaceActionArea		"KBSCE Type menu: Insert White Space: "
#define kTypeMenuSizeOtherActionArea			"KBSCE Type menu: Size: Other: "
#define kTypeMenuTypeOnPathActionArea			"KBSCE Type menu: Type on Path: "
#define kViewMenuActionArea						"KBSCE View menu"
#define kViewMenuExtrasActionArea				"KBSCE View menu: ExtrasSubmenu: "
#define kViewMenuProofSetupActionArea			"KBSCE View menu: Proof Setup: "
#define kViewMenuScreenModeActionArea			"KBSCE View menu: Screen Mode: "
#define kViewMenuDisplayPerformanceActionArea	"KBSCE View menu: Display Performance: "
#define kViewMenuStructureActionArea			"KBSCE View menu: Structure: "
#define kViewMenuGridsGuidesActionArea			"KBSCE View menu: Grids Guides: "
#define kViewMenuStoryEditorActionArea			"KBSCE View menu: Story Editor: "
#define kViewsNavigationActionArea				"KBSCE Views, Navigation"
#define kViewsNavigationHRulerActionArea		"KBSCE Views, Navigation: Horizontal Ruler: "
#define kViewsNavigationVRulerActionArea		"KBSCE Views, Navigation: Vertical Ruler: "
#define kViewsNavigationVDepthRulerActionArea	"KBSCE Views, Navigation: Vertical Depth Ruler: "
#define kWindowMenuActionArea					"KBSCE Window menu"
#define kWindowMenuArrangeActionArea			"KBSCE Window menu: Arrange: "
#define kWindowMenuWorkspaceActionArea			"KBSCE Window menu: Workspace: "
#define kWindowMenuUtilitiesActionArea			"KBSCE Window menu: Utilities: "
#define kWindowMenuExtensionsActionArea			"KBSCE Window menu:ExtensionsActionArea"
#define kWindowMenuInteractiveActionArea		"KBSCE Window menu: Interactive: "
#define kWindowMenuObjectAndLayoutActionArea	"KBSCE Window menu: Object & Layout: "
#define kWindowMenuOutputActionArea				"KBSCE Window menu: Output: "
#define kWindowMenuTypeAndTablesActionArea		"KBSCE Window menu: Type & Tables: "
#define kWindowMenuStylesActionArea				"KBSCE Window menu: Styles: "
#define kWindowMenuEditorialActionArea			"KBSCE Window menu: Editorial: "
#define kWindowMenuColorActionArea				"KBSCE Window menu: Color: "
#define kScriptsMenuActionArea					"KBSCE Scripts menu"
#define kScriptsPanelMenuActionArea				"KBSCE Palette Menus: Scripts: "
#define kPaletteMenusPreflightActionArea		"KBSCE Palette Menus: Preflight: "
#define kPaletteMenusPreflightButtonsActionArea	"KBSCE Palette Menus: Preflight: Buttons: "
#define kPaletteMenusConditionalTextActionArea	"KBSCE Palette Menus: Conditional Text: "
#define kWindowMenuCommentsActionArea			"KBSCE Palette Menus: Comments: "

//The following area is for older SDK plugins that use kMiscellaneousArea.  Please do not
//use it anymore.  If a third party developer wishes to make a new area, they can.
#define kMiscellaneousArea						kOtherActionArea

#define kGalleyArea								"KBSC Galley"	// Meant only for InCopy actions, use kTextAndTablesActionArea for InDesign
#define kTextMacroActionArea					"KBSCE Text Macros"
#define kChangesMenuActionArea					"KBSCE Changes menu"
#define kAcceptAllChangesMenuActionArea				"KBSCE Changes menu: AcceptAllSubMenu"
#define kRejectAllChangesMenuActionArea				"KBSCE Changes menu: RejectAllSubMenu"
#define kAcceptChangesByUserMenuActionArea				"KBSCE Changes menu: AcceptByUserSubMenu"
#define kRejectChangesByUserMenuActionArea				"KBSCE Changes menu: RejectByUserSubMenu"
#define kPaletteChangeReviewBarActionArea		"KBSCE Palette Menus: Change Tracking Toolbar: "
#define kPaletteMenusActionsActionArea			"KBSCE Palette Menus: Actions: "
#define kPaletteMenusRulesActionArea			"KBSCE Palette Menus: Rules: "
#define kPaletteMenusArticleActionArea			"KBSCE Palette Menus: Articles: "

#endif // __ACTIONDEFS__
