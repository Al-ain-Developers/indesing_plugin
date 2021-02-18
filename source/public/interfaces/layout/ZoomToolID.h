//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ZoomToolID.h $
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
//  Contains IDs used by zoom tool plug-in
//  
//========================================================================================

#ifndef __ZoomToolID__
#define __ZoomToolID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"


#define kZoomToolPrefix	 RezLong(0x1E00)

// PluginID
// Note this this plug-in was combined with the following:
// OvalTool, RectTool, LineTool, RegPolyTool, and GradientTool
// So, for example, if you want to used kOvalToolPlugInName, or
// kOvalToolPluginID, you would now use kZoomToolPluginName or
// kZoomToolPluginID instead. 
#define kZoomToolPluginName 		"Basic Tools"
DECLARE_PMID(kPlugInIDSpace, kZoomToolPluginID, kZoomToolPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kZoomToolBoss, kZoomToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kZoomToolTrackerBoss, kZoomToolPrefix + 2)
DECLARE_PMID(kClassIDSpace, kZoomTrackerRegisterBoss, kZoomToolPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kBasicToolsConversionProviderBoss, kZoomToolPrefix + 6)

//DECLARE_PMID(kClassIDSpace, kLoupeToolBoss_Obsolete, kZoomToolPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kLoupeToolTrackerBoss_Obsolete, kZoomToolPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kLoupeTrackerRegisterBoss_Obsolete, kZoomToolPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kLoupePanelBoss_Obsolete, kZoomToolPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kLoupeWindowBoss_Obsolete, kZoomToolPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kLoupeToolInfoPanelWidgetBossv, kZoomToolPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kLoupeComponentBoss_Obsolete, kZoomToolPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kLoupeDrwEvtHandlerBoss_Obsolete, kZoomToolPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kVertLoupeRulerWidgetBoss_Obsolete, kZoomToolPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kHorzLoupeRulerWidgetBoss_Obsolete, kZoomToolPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kLoupeGenericPanelBoss_Obsolete, kZoomToolPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kLoupeZeroPointWidgetBoss_Obsolete, kZoomToolPrefix + 18)
// gap
//DECLARE_PMID(kClassIDSpace, kLoupeToolDialogWidgetBoss, kZoomToolPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kLoupeToolPrefsScriptProviderBoss, kZoomToolPrefix + 21)

// InterfaceIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_ILOUPEMANAGER, kZoomToolPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNOREWINDOW, kZoomToolPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILOUPEMOUSEWATCHER, kZoomToolPrefix + 3)
// gap
//DECLARE_PMID(kInterfaceIDSpace, IID_ILOUPEOBSERVER, kZoomToolPrefix + 6)

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kZoomToolImpl,					kZoomToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kZoomToolTrackerImpl,			kZoomToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kZoomTrackerRegisterImpl,		kZoomToolPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kZoomToolCursorProviderImpl,	kZoomToolPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolImpl,				kZoomToolPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolCursorProviderImpl,	kZoomToolPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolTrackerImpl,			kZoomToolPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kLoupeTrackerRegisterImpl,		kZoomToolPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kLoupeEventWatcherImpl,		kZoomToolPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kLoupePanelViewImpl,			kZoomToolPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kLoupeWindowImpl,				kZoomToolPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kLoupeManagerImpl,				kZoomToolPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kLoupeEventHandlerImpl,		kZoomToolPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kLoupePanelCursorProviderImpl,	kZoomToolPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kLoupePanelObserverImpl,		kZoomToolPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolPanelProviderImpl,	kZoomToolPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kIgnoreableWindowImpl,			kZoomToolPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolPanelObserverImpl,	kZoomToolPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolPanelCreatorImpl,	kZoomToolPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kLoupeComponentImpl,			kZoomToolPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kLoupeMouseWatcherImpl,		kZoomToolPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kLoupeDrwEvtHandlerImpl,		kZoomToolPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kLoupeDrwEvtServiceImpl,		kZoomToolPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLoupeToolPrefsImpl_Obsolete,	kZoomToolPrefix + 26)
// gap
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolDialogControllerImpl,kZoomToolPrefix + 29)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolObserverImpl,		kZoomToolPrefix + 30)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolPrefsScriptProviderImpl,	kZoomToolPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kAnimatedZoomTimerImpl,		kZoomToolPrefix + 32)

// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kZoomToolWidgetId,				kZoomToolPrefix + 1)

// Service IDs

// ActionIDs
DECLARE_PMID(kActionIDSpace, kZoomToolActionID, kZoomToolPrefix + 1)

//
//Script Element IDs
//

//Suites

//Objects
//DECLARE_PMID(kScriptInfoIDSpace, kLoupeToolPreferenceObjectScriptElement,            kZoomToolPrefix + 10)

//Events

//Properties
//DECLARE_PMID(kScriptInfoIDSpace, kLoupeToolPrefsPropertyScriptElement,			kZoomToolPrefix + 100)
//DECLARE_PMID(kScriptInfoIDSpace, kLoupeZoomPctPropertyScriptElement,			kZoomToolPrefix + 101)
//DECLARE_PMID(kScriptInfoIDSpace, kLoupeSizePropertyScriptElement,				kZoomToolPrefix + 102)
//DECLARE_PMID(kScriptInfoIDSpace, kLoupeUseRulersPropertyScriptElement,		kZoomToolPrefix + 103)


#endif
