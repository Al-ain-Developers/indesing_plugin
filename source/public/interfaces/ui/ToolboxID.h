//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ToolboxID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the tool box
//  
//========================================================================================

#ifndef __ToolboxID__
#define __ToolboxID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kToolboxPrefix	 RezLong(0x1100)

// <Start IDC>
// PluginID
#define kToolboxPluginName	 			"Tool Box"
DECLARE_PMID(kPlugInIDSpace, kToolboxPluginID, kToolboxPrefix + 1)

// <Class ID>
// ClassIDs		----------------------------------------
DECLARE_PMID(kClassIDSpace, kToolBoxBoss,				kToolboxPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kToolBoxPanelRegisterBoss, kToolboxPrefix + 3)
DECLARE_PMID(kClassIDSpace, kToolBoxTestMenuBoss, kToolboxPrefix + 4)
DECLARE_PMID(kClassIDSpace, kToolboxConversionProviderBoss, kToolboxPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGenericToolBoss, kToolboxPrefix + 6)
DECLARE_PMID(kClassIDSpace, kToolGroupBoss, kToolboxPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kToolSubGroupBoss, kToolboxPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPopoutToolPanelBoss, kToolboxPrefix + 10)
DECLARE_PMID(kClassIDSpace, kToolBoxShortcutBoss, kToolboxPrefix + 11)
DECLARE_PMID(kClassIDSpace, kToolboxMenuRegisterBoss, kToolboxPrefix + 12)
DECLARE_PMID(kClassIDSpace, kToolboxMenuComponentBoss, kToolboxPrefix + 13)
DECLARE_PMID(kClassIDSpace, kToolboxScriptProviderBoss, kToolboxPrefix + 14)
DECLARE_PMID(kClassIDSpace, kToolboxActionRegisterBoss, kToolboxPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTBPopoutSelectionProxyBoss, kToolboxPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTBPopoutIconSuiteBoss, kToolboxPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTBPopoutStaticTextBoss, kToolboxPrefix + 18)
DECLARE_PMID(kClassIDSpace, kTBPopoutCellBoss, kToolboxPrefix + 19)
DECLARE_PMID(kClassIDSpace, kBeveledToolGroupBoss, kToolboxPrefix + 20)
DECLARE_PMID(kClassIDSpace, kTBPopoutShortcutStaticTextBoss, kToolboxPrefix + 21)

// <Interface ID>
// IIDs		----------------------------------------
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_SHOULDCLOSEPOPOUTBOOLDATA, kToolboxPrefix +1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLBOXOBSERVER, kToolboxPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLSIZER, kToolboxPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHORTCUTSTRING, kToolboxPrefix + 4)

// <Implementation ID>
// ImplementationIDs  ----------------------------------------
DECLARE_PMID(kImplementationIDSpace, kToolboxMenuComponentImpl, kToolboxPrefix + 1)
//gap
DECLARE_PMID(kImplementationIDSpace, kToolEventHandlerImpl, kToolboxPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kToolBoxPaletteWindow_reuse, kToolboxPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kToolBoxEventHandlerImpl, kToolboxPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kToolsContextObserverImpl, kToolboxPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kToolboxOrientationObserverImpl, kToolboxPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kToolboxPreferencesImpl_obsolete, kToolboxPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kToolBoxPanelRegisterImpl, kToolboxPrefix + 9 )
//gap
DECLARE_PMID(kImplementationIDSpace, kPanelToolSizerImpl, kToolboxPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPopoutPanelEHImpl, kToolboxPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kToolBoxKBSCComponentImpl, kToolboxPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kToolTextWidgetTipImpl, kToolboxPrefix + 14)
//gap
DECLARE_PMID(kImplementationIDSpace, kToolBoxTestMenuImpl, kToolboxPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kToolBoxActionRegisterImpl, kToolboxPrefix + 17)
//gap
DECLARE_PMID(kImplementationIDSpace, kToolboxSizeInfoImpl, kToolboxPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kToolBoxKitImpl, kToolboxPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kKSToolBoxKitImpl, kToolboxPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPopoutIconEHImpl, kToolboxPrefix + 22)
//gap
DECLARE_PMID(kImplementationIDSpace, kPopoutIconViewImpl, kToolboxPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPopoutStaticTextViewImpl, kToolboxPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kPopoutMouseTrackThreadImpl, kToolboxPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPopoutMouseTrackEventWatcherImpl, kToolboxPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kToolboxScriptProviderImpl, kToolboxPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPanelPtrOwnerImpl, kToolboxPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kToolboxScriptImpl, kToolboxPrefix + 30)
//gap
//DECLARE_PMID(kImplementationIDSpace, kDV_ToolEventHandlerImpl,				kToolboxPrefix + 32)


DECLARE_PMID(kImplementationIDSpace, kDV_ToolPopupWindowImpl,				kToolboxPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kDV_ToolPopupPanelControlDataImpl,		kToolboxPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kDV_PopoutSelectionProxyViewImpl,		kToolboxPrefix + 35)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_ToolControlEventHandlerImpl,		kToolboxPrefix + 38)


// <Widget ID>
// WidgetIDs  ----------------------------------------
DECLARE_PMID(kWidgetIDSpace, kRootToolBoxWidgetId, kToolboxPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kRootToolBoxPopoutWidgetId, kToolboxPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kToolBoxGroupWidgetId, kToolboxPrefix + 3)
//gap
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutCellWidgetId, kToolboxPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutSelectionWidgetId, kToolboxPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutIconWidgetId, kToolboxPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutNameWidgetId, kToolboxPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutShortcutWidgetId, kToolboxPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kToolBoxPopoutSeparatorWidgetId, kToolboxPrefix + 10)


// <Message ID>        // note - message ids conflict with class id space. 
DECLARE_PMID(kMessageIDSpace, kToolChangedToolBoxMessage, kToolboxPrefix + 21)

// <Global ID>
DECLARE_PMID(kActionIDSpace, kShowHideToolsActionID, kToolboxPrefix + 1)
DECLARE_PMID(kActionIDSpace, kShowHideToolsSepActionID, kToolboxPrefix + 2)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kToolBoxObjectScriptElement,				kToolboxPrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kToolBoxPropertyScriptElement,				kToolboxPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentToolPropertyScriptElement,			kToolboxPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentToolNamePropertyScriptElement,		kToolboxPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentToolHintPropertyScriptElement,		kToolboxPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentToolIconFilePropertyScriptElement,		kToolboxPrefix + 54)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kToolBoxEnumScriptElement,					kToolboxPrefix + 100)

//GUIDS
// {60108F34-0D73-48fe-A8B3-F2D3B015B0F2}
#define kToolBox_CLSID { 0x60108f34, 0xd73, 0x48fe, { 0xa8, 0xb3, 0xf2, 0xd3, 0xb0, 0x15, 0xb0, 0xf2 } }

#endif // __ToolboxID__










