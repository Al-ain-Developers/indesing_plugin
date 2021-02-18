//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PaletteRefUtils.h $
//  
//  Owner: Dave Burnard
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
#ifndef __PaletteRefUtils__
#define __PaletteRefUtils__

#include "PaletteRef.h"
#include "IUserInterfacePreferences.h"

class IDocumentPresentation;

/**
	PaletteRefUtils is here to allow you to walk and manipulate the palette hierarchy. Most client code will not need to
	use PaletteRefUtils at all, because the IPanelMgr interface generally provides everything you need. If you do need 
	to manipulate the palette containers directly, this collection of APIs should allow you to do that.
	
	For a description of the palette hierarchy (whcih changed substantially with OWL 2.0 see PaletteRef.h.
 
	IMPORTANT: OWL2 performs palette layout asynchronously, and only for visible palettes. When layout is pending or in progress
		many of the routines below used to get palette sizes, positions, etc. Way return values that will be different after the layout completes.

	
*/
class WIDGET_DECL PaletteRefUtils
{
	// ======== PaletteRef API ========		
	public:

	/** The edge to which a dock anchors itself.
	@see GetDockLocation
	*/
	enum DockLocation
	{
		kLeft_DockLocation = 1,			
		kTop_DockLocation,					
		kRight_DockLocation,					
		kBottom_DockLocation,				
		kFloating_DockLocation,				
		kAppContainer_DockLocation					
	};

	/** The various modes in which a dock can exist.
	In this version of InDesign (CS3) only expanded mode is supported.
	@see GetDockMode, SetDockMode
	*/
	enum DockMode
	{
		kExpanded_DockMode = 1,				
		kConcealed_DockMode,				
		kRevealed_DockMode				
	};

	/** The various modes in which a tab pane can exist.
		In Expanded mode, the palette content shows and the user interacts with the contents of the palette,
		in Icon mode, the palettes are collapsed to thier icon and optional text, and the user interacts with the palette content in a drawer.
	@see GetTabPaneMode, SetTabPaneMode
	*/
	enum TabPaneMode
	{
		kExpanded_TabPaneMode = 1,	
		kIcon_TabPaneMode			
	};
	
	/** The layout modes in which a tab pane can exist. 
		In Autoflow mode the height of the tabpane always fills the available vertical space,
		in manual mode the tabPane's height is defermined by the height of the tab groups it contains. 
	@see GetTabPaneLayoutMode, SetTabPaneLayoutMode
	*/
	enum TabPaneLayoutMode
	{
		kAutoFlow_TabPaneLayoutMode = 1,	
		kManual_TabPaneLayoutMode		
	};
	
	
	/** The toolbars size variants, two vertically oriented sizes and one horizontally oriented size.
	@see GetToolbarSizeVariant, SetToolbarSizeVariant
	*/
	enum ToolbarSizeVariant
	{
		kVerticalWide_ToolbarSizeVariant = 1,		
		kVerticalNarrow_ToolbarSizeVariant,		
		kHorizontal_ToolbarSizeVariant
	};

	//
	// ----- Methods to test the type of a Palette.
	//
	/** Is this the Root node of the Palette hierarchy.	*/
	static bool16			IsRootPaletteNode(const PaletteRef& whichPalette);

	/** Is this an application container (only one in CS4, could be more later on).	*/
	static bool16			IsApplicationContainer(const PaletteRef& whichPalette);

	/** Is this a dock.	*/
	static bool16			IsDock(const PaletteRef& whichPalette);

	/** Is this a tab group cluster.	OBSOLETE */
	//static bool16			IsTabGroupCluster(const PaletteRef& whichPalette);
	
	/** Is this a dock that can contain tabbed palettes and toolbars. (a sub category of docks)*/
	static bool16			IsTabbedPaletteDock(const PaletteRef& whichPalette);

	/** Is this a dock that can contain documents. (a sub category of docks)*/
	static bool16			IsDocumentDock(const PaletteRef& whichPalette);

	/** Is this a floating dock that can contain tabbed palettes and toolbars. (a sub category of docks)*/
	static bool16			IsFloatingTabbedPaletteDock(const PaletteRef& whichPalette);

	/** Is this a floating dock that can contain documents. (a sub category of docks)*/
	static bool16			IsFloatingDocumentDock(const PaletteRef& whichPalette);

	/** Is this a tab pane.	*/
	static bool16			IsTabPane(const PaletteRef& whichPalette);

	/** Is this a ControlBar pane. NOTE: ControlBarPanes are only supported in InCopy */
	static bool16			IsControlBarPane(const PaletteRef& whichPalette);

	/** Is this a tab group.	*/
	static bool16			IsTabGroup(const PaletteRef& whichPalette);

	/** Is this a tool bar.	*/
	static bool16			IsToolbar(const PaletteRef& whichPalette);

	/** Is this a control bar.	*/
	static bool16			IsControlBar(const PaletteRef& whichPalette);

	/** Is this a tabbed palette (panel container).	*/
	static bool16			IsTabPanelContainer(const PaletteRef& whichPalette);

	/** Is this a document (document presentation).	*/
	static bool16			IsDocumentPresentation(const PaletteRef& whichPalette);

	/** Is this at the top level (child of the root node).	
			OBSOLETE: Removed for CS4, since it's meaning was unclear. See IsPaletteFloating, IsFloatingTabbedPaletteDock, IsFloatingDocumentDock instead.
	*/
	//static bool16			IsTopLevelPalette(const PaletteRef& whichPalette);
	
	/** Is this palette floating (not docked). */
	static bool16			IsPaletteFloating(const PaletteRef& whichPalette);

	/** Given a bare OWL control - wrap it up in a PaletteRef */
	static PaletteRef	GetPaletteRefFromOWLPalette(OWLControlRef owlControl);
	
	/** Given a PaletteRef for an OWLDocument, retrieve the corresponding IDocumentPresentation interface.
			Used to bridge between the OWL palette world and InDesign object model notion of a document view.
	*/
	static  IDocumentPresentation*	GetDocumentPresentationFromPaletteRef(const PaletteRef& presentationRef);

	/** Given a IDocumentPresentation interface, retrieve the corresponding PaletteRef for an OWLDocument.
			Used to bridge between the OWL palette world and InDesign object model notion of a document view.
	*/
	static  PaletteRef	GetPaletteRefFromDocumentPresentation(const IDocumentPresentation* pres);

	//
	// ----- Palette hierarchy enumeration methods.
	// Use these methods to traverse the palette hierarchy.
	//
	/** Get the root palete node */
	static PaletteRef		GetRootPaletteNode();

	/** Get the Application Container */
	static PaletteRef		GetApplicationContainer();

	/** INTERNAL USE ONLY: Set the Application Container */
	static void					SetApplicationContainer(OWLControlRef owlControl);

	/** Get the Application Container's Document Dock
		returns an invalid PaletteRef when AppFrame is disabled.
	*/
	static PaletteRef		GetApplicationContainerDocumentDock();

	/** Get the number of children of the given palette */
	static uint16				GetChildCountOfPalette(const PaletteRef& parentPalette);

	/** Get the nth child of the given palette */
	static PaletteRef		GetNthChildOfPalette(const PaletteRef& parentPalette, uint16 inIndex);

	/** Get the reference to the parent of the given palette */
	static PaletteRef		GetParentOfPalette(const PaletteRef& whichPalette);

	/** Palette reparenting 
			An invalid parent/child combination will trigger an assert in the debug build.
			
			@param whichPalette IN the palette to be reparented.
			@param newParent IN the new parent.
			@param beforeSibling IN insert before an existing sibling (pass PaletteRef() to add to the end of the parents list).
	*/
	static void					ReparentPalette(const PaletteRef& whichPalette, const PaletteRef& newParent, const PaletteRef& beforeSibling);

	/** Palette reparenting (special case for making a docked toolbar or controlbar float)
			@param whichPalette IN the palette to be reparented.
	*/
	static void					FloatPalette(const PaletteRef& whichPalette);

#if MACINTOSH	
	//
	// ----- AppFrame Embedding. 
	//
	/** Return true if the user can dock UI or documents into an application container.
		By default this value is set to true, but the host can set it to false to obtain
		a legacy (CS3) style workspace where anchored docks are glued to the edges of the
		main display rather than into the application container.
	*/
	static bool16				IsAppFrameEmbeddingOnMacEnabled();
	/** Change whether or not users can embed UI and documents into an application container.
		Hosts can pass false to get a CS3 OSX legacy experience. In the legacy mode
		the application container acts like a control bar.
		Note that when this value is changed, Owl will reconfigure the document
		containment hierarchy.
		The legacy, non-application container mode is only supported on OSX
	-------
	*/
	static void					SetAppFrameEmbeddingOnMacEnabled(bool16 enabledState = kTrue);
#endif

	//
	// ----- Finding the TopLevel Palettes (i.e. not contained in another palette type). 
	//
	/**		A convenient shortcut - equivalent to GetChildCountOfPalette(GetRootPaletteNode()) */
	static uint16				GetTopLevelPaletteCount();
	/**		A convenient shortcut - equivalent to GetNthChildOfPalette(GetRootPaletteNode(),...) */
	static PaletteRef		GetNthTopLevelPalette(uint16 inIndex);

	//
	// ----- Finding the Docks. 
	//
	/** How Many Docks are there. */
	static uint16				GetDockCount();
	/** Get a particular dock 
			Note that you can now ask for the RHS dock, instead of iterating over the docks and checking their DockLocation 
	*/
	static PaletteRef		GetNthDock(uint16 inIndex);
	/** Get a particular dock, by location (only works for top, left, bottom and right docked palette docks)
	*/
	static PaletteRef		FindDockByLocation(DockLocation whichLocation);

	//
	// ----- Finding Floating TabbedPalette Docks. 
	//
	/** How many are there. */
	static uint16				GetFloatingTabbedPaletteDockCount();
	/** Get a particular one */
	static PaletteRef		GetNthFloatingTabbedPaletteDock(uint16 inIndex);

	//
	// ----- Finding Floating Document Docks. 
	//
	/** How many are there. */
	static uint16				GetFloatingDocumentDockCount();
	/** Get a particular one */
	static PaletteRef		GetNthFloatingDocumentDock(uint16 inIndex);
	/** Find the one containing a particular document */
	static PaletteRef		GetFloatingDocumentDockParentOfDocument(PaletteRef whichDocument);
	
	//
	// ----- Dock Accessors. 
	//
	/** Where is the dock located */
	static DockLocation	GetDockLocation(const PaletteRef& whichDock);
	/** What is the state of the dock */
	static DockMode			GetDockMode(const PaletteRef& whichDock);
	/** Change the state of the dock */
	static void					SetDockMode(const PaletteRef& whichDock, DockMode newMode);
	/** Get the preferred origin of a floating dock */
	static SysPoint			GetFloatingDockPreferredPosition(const PaletteRef& whichDock);
	/** Set the preferred origin of a floating dock */
	static void		SetFloatingDockPreferredPosition(const PaletteRef& whichDock, SysPoint& where);
	/** Set the bounds of the window containing this document */
	static void		SetFloatingDocumentWindowBounds(const PaletteRef& documentRef, SysRect newBounds);
	/** Set the bounds of the document. Window will be slightly larger to accomodate window trim */
	static void		SetFloatingDocumentBounds(const PaletteRef& documentRef, SysPoint newDimensions);

	//
	// ----- Finding the TabPanes. 
	//				TabPanes are found by enumerating the children of a dock and testing with IsTabPane 
	//
	/** What is the state of the tabpane */
	static TabPaneMode	GetTabPaneMode(const PaletteRef& whichTabPane);
	/** Change the state of the tabpane */
	static void				SetTabPaneMode(const PaletteRef& whichTabPane, TabPaneMode newMode);

	/** What is the layout mode of the tabpane (manual or autoflow) */
	static TabPaneLayoutMode	GetTabPaneLayoutMode(const PaletteRef& whichTabPane);
	/** Change the layout mode of the tabpane */
	static void				SetTabPaneLayoutMode(const PaletteRef& whichTabPane, TabPaneLayoutMode newLayoutMode);

	/** Get the preferred width of a tabpane when in icon mode. */
	static float	GetTabPanePreferredIconicWidth(const PaletteRef& whichTabPane);
	/** Change the preferred width of the tabpane when in icon mode */
	static void		SetTabPanePreferredIconicWidth(const PaletteRef& whichTabPane, float newWidth);

	//
	// ----- Finding the Toolbars and ControlBars. 
	//				There are a bit trickier to find since they can be either floating or docked. 
	//				So enumerate the appropriate parent and check each child with IsToolbar or IsControlBar
	//

	//
	// ----- Toolbar Accessors. 
	//
	/** Which size variant is the toolbar currently displaying */
	static ToolbarSizeVariant	GetToolbarSizeVariant(const PaletteRef& whichToolbar);
	/** Change the size variant that the toolbar will display */
	static void				SetToolbarSizeVariant(const PaletteRef& whichToolbar, ToolbarSizeVariant newVariant);
	/** Change the size variant that the toolbar will display */
	static void				SetToolbarSizeVariant(const PaletteRef& toolbarRef, IUserInterfacePreferences::ToolboxState newState);
	
	/** INTERNAL USE ONLY: Utility routine to offset the ID panel wrapper within its toolbar parent so that it draws properly. */
	static void				FixupToolbarContentOrigin(const PaletteRef& toolbarRef);

	//
	// ----- Palette Labels. 
	//
	/** Enum of labels associated with a tabbed panel. */
	enum PanelLabel {
		kTitle_PanelLabel = 0,	// Title (e.g. used for tabs)
		kTooltip_PanelLabel,	// Tooltip
	};
	
	/** Get/Set a label associated with a tabbed palette. Valid only for tabbed palettes.
		NOTE: OWL2 performs palette layout asynchronously, and only for visible palettes, calling GetPaletteLabel on a palette
			that has never been visible may return empty label strings.
			
			@precondition whichPalette must a TabPanelContainer. 
	*/
	static PMString		GetPaletteLabel(const PaletteRef& whichPalette, PanelLabel whichLabel = kTitle_PanelLabel);
	static void			SetPaletteLabel(const PaletteRef& whichPalette, const PMString& labelstr, PanelLabel whichLabel = kTitle_PanelLabel);

	//
	// ----- Palette Positioning (always global coordinates). 
	//
	/** Get the location (top/left global coordinate) of the given palette
			Note: whichPalette
			
			@precondition whichPalette can be either a Floating Dock, TabPane, Toolbar or ControlBar. 
	*/
	static SysPoint		GetPalettePosition (const PaletteRef& whichPalette);
	
	/** Set the location (top/left global coordinate) of the given palette
			Note: whichPalette
			
			@precondition  whichPalette must be a floating palette (Dock, Toolbar or ControlBar). 
	*/
	static void				SetPalettePosition (const PaletteRef& whichPalette, SysCoord left, SysCoord top);

	
	/** Get the bounds of the given palette in global coordinates			
			@precondition whichPalette can be either a Floating Dock, TabPane, Toolbar or ControlBar. 
	*/
	static SysRect		GetPaletteBounds (const PaletteRef& whichPalette);

	/** Request a new size for the given palette. Due to layout constraints, the requested size may not be possible.			
			@precondition whichPalette must be a resizable TabPanelContainer
			@param whichPalette the tab panel container object you want to resize
			@param newDimensions the desired new size for the TabPanelContainer
	*/
	static void SetPaletteSize (const PaletteRef& whichPalette, SysPoint newDimensions);
	
	/** Get the optical bounds of the given palette in global coordinates. The optical bounds should return the bounding box of what the user actually perceives as being the palette, without any drop shadow, extra drop zone, etc.			
			@precondition whichPalette can be either a Floating Dock, TabPane, Toolbar or ControlBar. 
	*/
	static SysRect		GetOpticalPaletteBounds (const PaletteRef& whichPalette);
	

	//
	// ----- Palette Visibility
	//
	/** Return true if this view's visible flag is set. (Latent visibility) */
	static bool16			GetVisibleState (const PaletteRef& whichPalette);
	/** Return true if this view is visible. A view is visible if its visible flag is set and all of its ancestors are visible. (Effective visibility)*/
	static bool16			IsPaletteVisible (const PaletteRef& whichPalette);

	/** Returns true if the palette is minimized. only valid to call on tab panel containers. */
	static bool16			IsPaletteMinimized (const PaletteRef& whichPalette);
	/** Sets the minimize state of the palette. only valid to call on tab panel containers. */
	static void				ChangePaletteMinimization (const PaletteRef& whichPalette, bool16 minimize);
	
	/** Palette visibility actions */
	enum PaletteVisibilityChange { kShowPalette = 0, kHidePalette };
	
	/** Show or hide the entire palette system. 
			Use sparingly - generally only if you're doing something like rearranging all the palettes for some reason 
	*/
	static void				ShowHideEntirePaletteSystem(PaletteVisibilityChange show);
	
	/** Discover if the entire palette system has been hidden. 
	*/
	static bool16			IsEntirePaletteSystemHidden();
	
	/** Force the entire palette system to perform layout (which is typically done asynchronously)
			Use sparingly - generally only if you're doing something like writing test code where layout must complete before proceeding. 
	*/
	static void				ForcePaletteSystemToPerformLayout();

	
	/** Show or hide a specific PaletteRef. 
			Each PaletteRef in the hierarchy has a visible flag. Calling hide on a PaletteRef sets the visible flag for that PaletteRef to false.
			Parent PaletteRefs will not be shown on screen if they contain no visible child PaletteRefs. 
			Calling Show on a child PaletteRef will show all its parent PaletteRefs so it will actually appear on screen 
	*/
	static void				ShowHidePalette (const PaletteRef& whichPalette, PaletteVisibilityChange show);
	
	/** Bring a specific palette, and it's containers, to the front. */
	static void				BringPaletteToFront(const PaletteRef& whichPalette);
	
	/** Move a specific palette to be centered on the main screen.
			@precondition  any palette type can passed, algorithm will do the appropriate things to do the centering. 
	*/
	static void				CenterPaletteOnScreen(const PaletteRef& whichPalette);

	//
	// ----- Palette Creation Shortcuts.
	//					@see IPaletteFactory
	//
	/** Create a new TabPane in the specified dock, before a particular sibling (pass PaletteRef() to add to end of dock) */
	static PaletteRef	NewTabPaneInDock(const PaletteRef& dockParent, TabPaneMode mode, const PaletteRef& beforeOptionalSibling);

	/** InCopy Only: Create a new ControlBarPane in the specified dock, before a particular sibling (pass PaletteRef() to add to end of dock) */
	static PaletteRef	NewControlBarPaneInDock(const PaletteRef& dockParent, const PaletteRef& beforeOptionalSibling);

	/** Create a new FloatingTabGroupContainer (a pane in a floatig dock) */
	static PaletteRef	NewFloatingTabGroupContainerPalette();

	/** Create a new TabGroup in the speficied parent */
	static PaletteRef	NewTabGroupPalette(const PaletteRef& tabGroupClusterOrTabPaneParent); 

	/** Create a new (floating) Toolbar. To dock it afterwards call ReparentPalette */
	static PaletteRef	NewToolbarPalette();

	/** Create a new (floating) ControlBar. To dock it afterwards call ReparentPalette */
	static PaletteRef	NewControlbarPalette();
	
	//
	// ----- Palette Closed state.
	//				The closed state reflects how a palette is marked when the user clicks on the close box of a palette.
	//				It is included in the effective visibility calculation.
	//
	/** Return true if the palette can be closed. */
	static bool16			CanClose(const PaletteRef& paletteRef);
	/** Return the closed state of the palette. */
	static bool16			GetIsClosed(const PaletteRef& paletteRef);
	/** Change the closed state of the palette. */
	static void				ChangeIsClosed(const PaletteRef& paletteRef, bool16 close = kTrue);
		
	/** Called when AppFrame changes size, Monitor resolution changes, or after Workspace changes.
			 replaces AdjustPalettesToClientArea */
	static void				AdjustClientAreaToPalettes();
	
	/** Utility routine that causes the entire palette system to invalidate and redraw. */
	static void				InvalidateAllPalettes();

#ifdef DEBUG
	/** Returns string describing palette. Useful for debugging */
	static char* GetPaletteTypeString(PaletteRefType palType);
	/** dumps out palette hierarchy via TRACE messages */
	static void				DumpPaletteHierarchy(const PaletteRef& pal);
	/** dumps out palette hierarchy via OWL logging */
	static void				DumpOWLWidgetHierarchy();
#endif

	/** Palette ShowHide levels */
	enum ShowHideLevel {
		/** Show/hide only the floating tab palettes */
		kShowHideFloatingTabPalettes,
		/** Show/hide all palettes */
		kShowHideAllPalettes
	};
	
	/** Show or hide the palettes, used when the user hits the tab key or shift+tab key.
		@param paletteShowHideLevel IN if kShowHideFloatingTabPalettes, then only floating tabbed palettes will be hidden.
			Floating non-tabbed palettes(i.e. toolbox) will not be hidden, nor will toolbars be hidden.
	*/
	static void				ShowHidePalettes(ShowHideLevel paletteShowHideLevel = kShowHideAllPalettes);
	
	/** WhichTabPanes specifiers */
	enum WhichTabPanes {
		/** none of the them */
		kNoTabPanes,
		/** those on the LHS of the screen */
		kLHSTabPanes,
		/** those on the RHS of the screen */
		kRHSTabPanes,
		/** all of them */
		kAllTabPanes
	};
	
	/** Retrieves the state of the tab panes as of the last call to OpenCloseTabPanes.
		@param whichOnes IN which tab panes to check
	*/
	static bool16			AreTabPanesOpen(WhichTabPanes whichOnes = kAllTabPanes);
	/** Open or close tab panes (reveal or conceal panel content).
		@param whichOnes IN which tab panes to open
		@param open IN true to open the tab panes, false to close them
	*/
	static void				OpenCloseTabPanes(WhichTabPanes whichOnes = kAllTabPanes, bool16 open = kTrue);	
		
	static IXMLGenerator* QueryXMLGenerator(PaletteRefType paletteType);
	static IPaletteFactory* QueryPaletteFactory(PaletteRefType paletteType);
	
	/** INTERNAL USE ONLY: Called to send notification to panels that they're being closed. 
			Client code should not need to call these methods.
			
			@see kAboutToClosePaletteMsg (notification contains pointer to panel being closed)
	*/
	static void NotifyPaletteIsClosing(PaletteRef owlPalette);

	/** INTERNAL USE ONLY: Called to send notification to panels that on if it's containers is being closed. 
			Client code should not need to call these methods .
			
			@see kAboutToClosePaletteMsg (notification contains pointer to panel being closed)
	*/
	static void NotifyPaletteContainerIsClosing(PaletteRef owlPalette);

	/** Move a specific palette on the main screen at distance from left edge of screen.
		@precondition  any palette type can passed, algorithm will do the appropriate things to do the moving.
		@param whichPalette IN palette to be moved
		@param distanceFromLeftOnScreenInPercentage IN distance from left edge of screen in percentage where the palette has to be placed (centered)
	*/
	static void PositionPaletteOnScreen(const PaletteRef& whichPalette, PMReal distanceFromLeftOnScreenInPercentage);

private:

	static bool16 fgAllTabPanesOpen;
	static bool16 fgRHSTabPanesOpen;
	static bool16 fgLHSTabPanesOpen;
	
	static PaletteRef fgApplicationContainer;
};

#endif // __PaletteRefUtils__
