//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TabID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __TabID__
#define __TabID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// Prefix
#define kTabPrefix		RezLong(0x6800) 	/* doublecheck with DeveloperPrefix.h */
// 0x6800 Hex == 26624 Dec

// <Start IDC>
// PluginID
#define kTextRulerPluginName 				"Text Ruler"
DECLARE_PMID(kPlugInIDSpace, kTextRulerPluginID, kTabPrefix + 1)

// <Class ID>
//////////////////////////////////////////////////////
DECLARE_PMID(kClassIDSpace, kHorzTextRulerBoss, kTabPrefix + 1		/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kVertTextRulerBoss, kTabPrefix + 2		/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kHorzTextDocRulerBoss, kTabPrefix + 3		/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kVertTextDocRulerBoss, kTabPrefix + 4		/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kHorzTabRulerBoss, kTabPrefix + 5		/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kVertTabRulerBoss, kTabPrefix + 6		/* TextRuler */)

DECLARE_PMID(kClassIDSpace, kTabTrackerRegisterBoss, kTabPrefix + 7		/* Tracker */)
DECLARE_PMID(kClassIDSpace, kTabCreationTrackerBoss, kTabPrefix + 8		/* Tracker */)
DECLARE_PMID(kClassIDSpace, kTabMoveTrackerBoss, kTabPrefix + 9		/* Tracker */)
DECLARE_PMID(kClassIDSpace, kTabRulerFirstIndentBoss, kTabPrefix + 10	/* TextRuler, CObserver, first indent */)
DECLARE_PMID(kClassIDSpace, kTabRulerLeftIndentBoss, kTabPrefix + 11	/* TextRuler, CObserver, left indent */)
DECLARE_PMID(kClassIDSpace, kTabRulerRightIndentBoss, kTabPrefix + 12	/* TextRuler, CObserver, right indent */)
//DECLARE_PMID(kClassIDSpace, kTabRulerLeftMarginBoss, kTabPrefix + 13	/* OBSOLETE: was NOP TextRuler, CObserver, left margin (=left+first indent) */)
DECLARE_PMID(kClassIDSpace, kTabRulerRightMarginBoss, kTabPrefix + 14	/* TextRuler, CObserver, right margin (=textframe's right) */)
DECLARE_PMID(kClassIDSpace, kDocRulerTrackerBoss, kTabPrefix + 15	/* TextRuler */)
DECLARE_PMID(kClassIDSpace, kTextRulerTestMenuBoss, kTabPrefix + 16	/* TextRulerPlugin.cpp */)

// classid messages 100, protocol is IID_ITABRULERDATA
DECLARE_PMID(kMessageIDSpace, kSetTabAlignMessage, kTabPrefix + 100	/* changedBy is a TabStop. TabAlignObserver (TabPanel button) -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetTabScrollLeftMessage, kTabPrefix + 101	/* changedBy is a PMReal value. TabScrollObserver (TabPanel button) -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetTabScrollRightMessage, kTabPrefix + 102	/* changedBy is a PMReal value. TabScrollObserver (TabPanel button) -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetTabLeaderMessage, kTabPrefix + 103	/* changedBy is a TabStop. TabLeaderObserver (TabPanel editbox) -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetTabRulerItemPositionMessage, kTabPrefix + 104	/* changedBy is a PMReal. TabEditPositionObserver -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kUpdateTabPositionMessage, kTabPrefix + 105	/* changedBy is a PMReal. TabRulerThread -> TabPositionObserver (TabPanel static text). */)
DECLARE_PMID(kMessageIDSpace, kClearTabsMessage, kTabPrefix + 106	/* changedBy is nil. TabPanelMenuComponent -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetFirstIndentMessage, kTabPrefix + 107	/* changedBy is a PMReal. TabMoveTracker -> TabRulerFirstIndent. */)
DECLARE_PMID(kMessageIDSpace, kSetLeftIndentMessage, kTabPrefix + 108	/* changedBy is a PMReal. TabMoveTracker -> TabRulerLeftIndent. */)
DECLARE_PMID(kMessageIDSpace, kSetRightIndentMessage, kTabPrefix + 109	/* changedBy is a PMReal. TabMoveTracker -> TabRulerLeftIndent. */)
//DECLARE_PMID(kMessageIDSpace, kSetLeftMarginMessage, kTabPrefix + 110	/* obsolete - was NOP: changedBy is a PMReal. TabMoveTracker -> TabRulerLeftMargin. */)
//DECLARE_PMID(kMessageIDSpace, kSetRightMarginMessage, kTabPrefix + 111	/* obsolete - NOT IMPL: changedBy is a PMReal. TabMoveTracker -> TabRulerRightMargin. */)
DECLARE_PMID(kMessageIDSpace, kNewTabStopMessage, kTabPrefix + 112	/* changedBy is a TabStop. TabCreationTracker -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kChangeTabRulerItemMessage, kTabPrefix + 113	/* changedBy is a TabRulerItem. TabMoveTracker -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSelectTabRulerItemMessage, kTabPrefix + 114	/* changedBy is a TabRulerItem. TabMoveTracker -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kMovedTabRulerItemMessage, kTabPrefix + 115	/* changedBy is a TabRulerItem. TabMoveTracker -> TabEditPositionObserver. */)
DECLARE_PMID(kMessageIDSpace, kDeletedTabStopMessage, kTabPrefix + 116	/* changedBy is a TabStop. TabMoveTracker -> TabEditPositionObserver. */)
DECLARE_PMID(kMessageIDSpace, kGetSelectedTabStopMessage, kTabPrefix + 117	/* changedBy is a TabStop. TabEditPositionObserver -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kGetSelectedItemMessage, kTabPrefix + 118	/* changedBy is a TabRulerItem. TabEditPositionObserver -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kQueryTabRulerDataMessage, kTabPrefix + 119	/* changedBy is a IPMUnknown**. TabEditPositionObserver -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kRepeatTabMessage, kTabPrefix + 120	/* changedBy is nil. TabPanelMenuComponent -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kScrollToLeftMarginMessage, kTabPrefix + 121	/* changedBy is nil. TabMagnetObserver -> TextRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kScrollToRightMarginMessage, kTabPrefix + 122	/* changedBy is nil. ??? -> TextRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kSetTabAlignCharMessage, kTabPrefix + 123	/* changedBy is a TabStop. TabAlignCharObserver (TabPanel editbox) -> TabRulerObserver. */)
//DECLARE_PMID(kMessageIDSpace, kCalcRightMarginMessage, kTabPrefix + 124	/* OBSOLETE: removed. changedBy is nil. kTabRightMarginObserverImpl -> kTabRulerRightMarginImpl. */)
DECLARE_PMID(kMessageIDSpace, kAutoAttachedMessage, kTabPrefix + 125	/* changedBy is ITabRulerData. kTabRulerObserver -> TabRepeatObserver, TabClearObserver. */)
DECLARE_PMID(kMessageIDSpace, kPreSelectTabRulerItemMessage, kTabPrefix + 126	/* changedBy is ITabRulerData. TabRulerData -> TabRulerObserver. */)


// <Interface ID>
/////////////////////////////////////////////////////
DECLARE_PMID(kInterfaceIDSpace, IID_IHORZTEXTRULER, kTabPrefix + 1		/* TextRuler, just a flag */)
DECLARE_PMID(kInterfaceIDSpace, IID_IVERTTEXTRULER, kTabPrefix + 2		/* TextRuler, just a flag  */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABSETTINGS, kTabPrefix + 3		/* default tab settings */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABRULERDATA, kTabPrefix + 4		/* Tracker */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABRULERTHREAD, kTabPrefix + 5		/* TextRuler */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRULERSUBJECT, kTabPrefix + 6		/* TextRuler, CSubject */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRULEROBSERVER, kTabPrefix + 7		/* kTextRulerObserverImpl */)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABRULEROBSERVER, kTabPrefix + 8		/* kTabRulerObserverImpl */)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITABRIGHTMARGINOBSERVER, kTabPrefix + 9		/* kTabRightMarginObserverImpl */)

// <Implementation ID>
/////////////////////////////////////////////////////
DECLARE_PMID(kImplementationIDSpace, kTextRulerViewImpl, kTabPrefix + 1		/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTextRulerSettingsImpl, kTabPrefix + 2		/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerViewImpl, kTabPrefix + 3		/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerEventHandlerImpl, kTabPrefix + 4		/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabSettingsImpl, kTabPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTabTrackerRegisterImpl, kTabPrefix + 6		/* Tracker */)
DECLARE_PMID(kImplementationIDSpace, kTabCreationTrackerImpl, kTabPrefix + 7		/* Tracker */)
DECLARE_PMID(kImplementationIDSpace, kTabMoveTrackerImpl, kTabPrefix + 8		/* Tracker */)
DECLARE_PMID(kImplementationIDSpace, kTabCreationToolImpl, kTabPrefix + 9		/* Tracker, fake tool id  */)
DECLARE_PMID(kImplementationIDSpace, kTabMoveToolImpl, kTabPrefix + 10	/* Tracker, fake tool id  */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerDataImpl, kTabPrefix + 11	/* Tracker */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerObserverImpl, kTabPrefix + 12	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTextRulerObserverImpl, kTabPrefix + 13	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerThreadImpl, kTabPrefix + 14	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerFirstIndentImpl, kTabPrefix + 15	/* TextRuler, CObserver, first indent */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerLeftIndentImpl, kTabPrefix + 16	/* TextRuler, CObserver, left indent */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerRightIndentImpl, kTabPrefix + 17	/* TextRuler, CObserver, right indent */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerLeftMarginImpl, kTabPrefix + 18	/* TextRuler, CObserver, left margin (=left+first indent) */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerRightMarginImpl, kTabPrefix + 19	/* TextRuler, CObserver, right margin (= textframe's right) */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerIndentObserverImpl, kTabPrefix + 20	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerPanoramaImpl, kTabPrefix + 21	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kDocRulerTrackerImpl, kTabPrefix + 22	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kDocRulerEventHandlerImpl, kTabPrefix + 23	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kTabRightMarginObserverImpl, kTabPrefix + 24	/* TextRuler */)
DECLARE_PMID(kImplementationIDSpace, kDocRulerCursorProviderImpl, kTabPrefix + 25	/* TextRulerCrsrProvider.cpp */)
DECLARE_PMID(kImplementationIDSpace, kTabRulerCursorProviderImpl, kTabPrefix + 26	/* TextRulerCrsrProvider.cpp */)
DECLARE_PMID(kImplementationIDSpace, kTextRulerTestMenuImpl, kTabPrefix + 27	/* TextRulerPlugin.cpp */)

// <Widget ID>
/////////////////////////////////////////////////////

DECLARE_PMID(kWidgetIDSpace, kHorzTextRulerWidgetID, kTabPrefix + 1		/* TextRuler */)
DECLARE_PMID(kWidgetIDSpace, kVertTextRulerWidgetID, kTabPrefix + 2		/* TextRuler */)
DECLARE_PMID(kWidgetIDSpace, kHorzTextDocRulerWidgetID, kTabPrefix + 3		/* TextRuler */)
DECLARE_PMID(kWidgetIDSpace, kVertTextDocRulerWidgetID, kTabPrefix + 4		/* TextRuler */)
DECLARE_PMID(kWidgetIDSpace, kHorzTabRulerWidgetID, kTabPrefix + 5		/* TextRuler */)
DECLARE_PMID(kWidgetIDSpace, kVertTabRulerWidgetID, kTabPrefix + 6		/* TextRuler */)

// <Ignore>
#define kTabRulerDefaultZeroX				0.0
#define kTabRulerDefaultMaxX				8640.0
#endif
