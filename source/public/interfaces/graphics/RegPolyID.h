//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/RegPolyID.h $
//  
//  Owner: Paul Sorrick
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

#ifndef __RegPolyID__
#define __RegPolyID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kRegPolyPrefix	 RezLong(0x5000) 

// <Start IDC>
// PluginID
// These no longer exist, combined with BasicTools plug-in.
// Access via kZoomToolPlugInName and kZoomToolPluginID
// #define kRegPolyPluginName 				"RegPoly"
// DECLARE_PMID(kPlugInIDSpace, kRegPolyPluginID, kRegPolyPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kRegPolyToolBoss, kRegPolyPrefix + 2)
DECLARE_PMID(kClassIDSpace, kRegPolyTrackerBoss, kRegPolyPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kRegPolyTrackerRegisterBoss, kRegPolyPrefix + 5)
//gap
DECLARE_PMID(kClassIDSpace, kRegPolyDialogBoss, kRegPolyPrefix + 9)
//gap
DECLARE_PMID(kClassIDSpace, kRegPolyFrameToolBoss, kRegPolyPrefix + 12)
DECLARE_PMID(kClassIDSpace, kRegPolyFrameTrackerBoss, kRegPolyPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCreatePolygonDialogBoss, kRegPolyPrefix + 14)


// <Interface ID>
// IIDs
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IREGPOLYSIZEPREFS, kRegPolyPrefix + 4)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kRegPolyToolImpl, kRegPolyPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kRegPolyTrackerImpl, kRegPolyPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kRegPolyTrackerRegisterImpl, kRegPolyPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kSessionRegPolyPrefsImpl_Obsolete, kRegPolyPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDocRegPolyPrefsImpl_Obsolete, kRegPolyPrefix + 12)
// gap
DECLARE_PMID(kImplementationIDSpace, kRegPolyDialogControllerImpl, kRegPolyPrefix + 15)
//gap
DECLARE_PMID(kImplementationIDSpace, kRegPolyFrameToolImpl, kRegPolyPrefix + 17 )
DECLARE_PMID(kImplementationIDSpace, kRegPolyFrameTrackerImpl, kRegPolyPrefix + 18 )
DECLARE_PMID(kImplementationIDSpace, kCreatePolygonDialogControllerImpl, kRegPolyPrefix + 19 )

// <Widget ID>
// Widget IDs for Regular Polygon dialog
DECLARE_PMID(kWidgetIDSpace, kRegPolySidesEditWidgetID, kRegPolyPrefix + 1 )
DECLARE_PMID(kWidgetIDSpace, kRegPolySidesNudgeWidgetID, kRegPolyPrefix + 2 )
DECLARE_PMID(kWidgetIDSpace, kRegPolyInsetEditWidgetID, kRegPolyPrefix + 3 )
DECLARE_PMID(kWidgetIDSpace, kRegPolyInsetNudgeWidgetID, kRegPolyPrefix + 4 )
DECLARE_PMID(kWidgetIDSpace, kRegPolySidesTextWidgetID, kRegPolyPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kRegPolyInsetTextWidgetID, kRegPolyPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRegPolyParentWidgetID, kRegPolyPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kRegPolyToolWidgetId, kRegPolyPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kRegPolyFrameToolWidgetId, kRegPolyPrefix + 9)

DECLARE_PMID(kWidgetIDSpace, kCreatePolygonParentWidgetId, kRegPolyPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kCreatePolygonMainPanelWidgetID, kRegPolyPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCreatePolygonGroupWidgetId, kRegPolyPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kPolygonSizeGroupTextWidgetID, kRegPolyPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kPolygonSizeLabelsPanelWidgetID, kRegPolyPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPolygonSizeWidthStaticTextWidgetID, kRegPolyPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPolygonWidthEditWidgetID, kRegPolyPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPolygonSizeHeightStaticTextWidgetID, kRegPolyPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPolygonHeightEditWidgetID, kRegPolyPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPolygonSizeEditPanelWidgetID, kRegPolyPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPolygonWidthEditPanelWidgetID, kRegPolyPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kCreatePolygonGroup2WidgetId, kRegPolyPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPolygonSettingsGroupTextWidgetID, kRegPolyPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPolygonSettingsLabelPanelWidgetID, kRegPolyPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPolygonSettingsEditPanelWidgetID, kRegPolyPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPolygonSettingsSidesEditPanelWidgetID, kRegPolyPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPolygonSettingsInsetsEditPanelWidgetID, kRegPolyPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kCreatePolygonButtonsPanelWidgetID, kRegPolyPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kCreatePolygonPanelWidgetID, kRegPolyPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPolygonHeightEditPanelWidgetID, kRegPolyPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPolygonOptionsGroupTextWidgetID, kRegPolyPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPolygonOptionsGroupWidgetId, kRegPolyPrefix + 32)

// <Action ID>
// Action IDs for Regular Polygon 
DECLARE_PMID(kActionIDSpace, kRegPolyToolActionID, kRegPolyPrefix + 1 )
DECLARE_PMID(kActionIDSpace, kRegPolyFrameToolActionID, kRegPolyPrefix + 2 )

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPolygonPrefsObjectScriptElement,			kRegPolyPrefix + 20)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPolygonPrefsPropertyScriptElement,		kRegPolyPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kInsetPercentagePropertyScriptElement,		kRegPolyPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kNumSidesPropertyScriptElement,			kRegPolyPrefix + 122)

//Enums


//GUIDS
// {496F0BE4-7834-11d2-AAF0-00C04FA37726}
#define kPolygonPref_CLSID { 0x496f0be4, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }


#endif


