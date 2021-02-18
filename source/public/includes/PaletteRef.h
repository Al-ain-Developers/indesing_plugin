//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PaletteRef.h $
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
//  
//  This file contains the type used to represent various Palette entities in the OWL Palette world
//  
//========================================================================================

#pragma once
#ifndef __PaletteRef__
#define __PaletteRef__

// Preprocessor macros/constants
#define FIXME_OWL(comment) {ASSERT_FAIL(FORMAT_ARGS("FIXME_OWL: %s\n", comment));}

//Types
#if MACINTOSH
	#if ID_COCOA_ENABLE
		#include <Cocoa/Cocoa.h>
		typedef NSObject*	OWLControlRef;
		typedef NSView*		OWLLeafControlRef;
		typedef NSView*		OSViewRef;
	#else
		typedef HIViewRef	OWLControlRef;
		typedef HIViewRef	OWLLeafControlRef;
		typedef HIViewRef	OSViewRef;
	#endif
#elif WINDOWS
	typedef HWND			OWLControlRef;
	typedef HWND			OWLLeafControlRef;
	typedef HWND			OSViewRef;
#endif

class IXMLGenerator;
class IPaletteFactory;
class IControlView;

/** OWL Palette Types. Representing the various containers in the palette hierarchy

	A brief overview of the palette hierachy: See PaletteRefUtils
	
	=== OWL1.0 ===
	At the top of the hierarchy is the Palette workspace, aka palette root node.
	Children of the root node are one of:
		Docks(4 total, one per edge)
		Control bars(if they are 'floating')
		Tool bars(if they are 'floating')
		Tab group clusters(also 'floating')
		
	Children of docks can be one of:
		Control bars(non floating)
		Tool bars(non floating)
		Tab Panes
		ControlBar Panes (InCopy only)
		
	Children of TabGroupClusters can be:
		TabGroups	
			
	Children of TabGroups can be:
		TabPalettes aka TabPanelContainers
		
	Children of TabPanes can be:
		TabGroups		
							
	Control bars do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.
	Tool bars do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.
	TabPalettes/TabPanelContainers do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.
		
	=== OWL2.0 ===
	Changes include the introduction of the ApplicationContainer as well as Documents, also TabGroupClusters have been eliminated, and are replaced by floating (palette-based) Docks
	At the top of the hierarchy is the Palette workspace, aka palette root node.
	Children of the root node are one of:
		Monitor Edge (palette-based) Docks(4 total, one per edge of the main screen)
		Control bars(if they are 'floating')
		Floating Docks(also called flotillas - both palette-based or document-based)
		ApplicationContainer (only one)
		
	Children of (palette-based) docks are:
		Control bars(non floating - horizontal docks only)
		Tool bars(floating or vertical docks only))  If the toolbar is floating, it's floating dock now!
		Tab Panes
			TabGroups
				TabPanelContainers
		ControlBar Panes (InCopy only - horizontal docks only)
			Control bars(non floating - horizontal docks only)
		
	Children of (document-based) docks are:
		TabPanes
			TabGroups
				DocumentPresentations
		
	Children of the ApplicationContainer are:
		AppContainerEdge (palette-based) Docks(4 total, one per edge)
		Document (document-based) Dock
		
	Children of TabGroups can be either (depending on containing dock):
		TabPalettes aka TabPanelContainers, or
		DocumentPresentations
		
	Children of TabPanes can be:
		TabGroups		
							
	Control bars do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.
	Tool bars do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.
	TabPalettes/TabPanelContainers do not have palette children. You can ask the IPanelMgr for their InDesign panel to continue down.

	@see PaletteRef, PaletteRefUtils
*/
enum PaletteRefType
{
	kUnknownPaletteType,
	
	/** root node of palette hierarchy (parent for docks and all floating palette types) */
	kRootPaletteNode = 1,
	
	/** floating container for TabGroups - OBSOLETE no longer a unique palette type*/
	kTabGroupClusterType_OBSOLETE, //keep so we don't disrupt the id values
	
	/** container for TabPanes and, when docked, Toolbars and ControlBars */
	kDockType,
	
	/** toolbar/toolbox - contains an ID/IC panel via a platform wrapper */
	kToolbarType,
	
	/** control bar or control strip, or InCopy mini controlbar - contains an ID/IC panel via a platform wrapper */
	kControlBarType,
	
	/** docked container for TabGroups */
	kTabPaneType,
	
	/** container for group of TabPanelContainers */
	kTabGroupType, 
	
	/** container for a panel that can live in a TabGroup - contains an ID/IC panel via a platform wrapper */
	kTabPanelContainerType,
	
	/** docked container for InCopy controlbars */
	kControlBarPaneType,
	
	// New types for OWL2
	
	/** application container */
	kApplicationContainerType,
	
	/** presentation for a document - contains an ID/IC document panel via a platform wrapper */
	kDocumentPresentationType
	
};

/** Definition of the PaletteRef class, used to represent various Palette entities in the OWL Palette world.
	
		@see PaletteRefUtils, IPanelMgr
 */
class PaletteRef
{
	public:
		typedef base_type data_type;

		PaletteRef(PaletteRefType type, OWLControlRef ref) : fRef(ref), fType(type) {}
		PaletteRef(PaletteRefType type) : fRef(NULL), fType(type) {}
		PaletteRef() : fRef(NULL), fType(kUnknownPaletteType) {}
		
		/** Validation */
		bool16 IsValid() const {return fRef != NULL && fType != kUnknownPaletteType;}		

		/** Palette type access */
		PaletteRefType GetPaletteRefType() const {return fType;}		

		/** Platform control access */
		OWLControlRef GetOWLControl() const {return fRef;}
		OWLLeafControlRef GetOWLLeafControl() const {return (OWLLeafControlRef) fRef;}

		/** Comparison */
		bool16 operator==(const PaletteRef& other) const { return fType == other.fType && fRef == other.fRef; }
		bool16 operator!=(const PaletteRef& other) const { return fType != other.fType || fRef != other.fRef; }
		
	private:
		PaletteRefType	fType;
		OWLControlRef	fRef;
};

#endif  // __PaletteRef__
