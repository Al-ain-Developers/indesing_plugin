//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/RulerID.h $
//  
//  Owner: Stacy Molitor
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
//  Contains IDs used by the group item plug-in
//  
//========================================================================================

#ifndef __RulerID__
#define __RulerID__
#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kRulerPrefix	 RezLong(0x3400)

// PluginID
#define kRulerPluginName			"Rulers"
DECLARE_PMID(kPlugInIDSpace, kRulerPluginID, kRulerPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kHorzRulerWidgetBoss, kRulerPrefix + 1)
DECLARE_PMID(kClassIDSpace, kVertRulerWidgetBoss, kRulerPrefix + 2)
DECLARE_PMID(kClassIDSpace, kBaseRulerWidgetBoss, kRulerPrefix + 3)
DECLARE_PMID(kClassIDSpace, kRulerMenuActionBoss, kRulerPrefix + 4)

// gap
DECLARE_PMID(kClassIDSpace, kRulerVPopupMenuActionBoss, kRulerPrefix + 6)
DECLARE_PMID(kClassIDSpace, kRulerHPopupMenuActionBoss, kRulerPrefix + 7)
DECLARE_PMID(kClassIDSpace, kRulerWorkspaceLayoutActionBoss, kRulerPrefix + 8)
DECLARE_PMID(kClassIDSpace, kRulerCustomizeDialogBoss, kRulerPrefix + 9)
DECLARE_PMID(kClassIDSpace, kRulerCustomMSBoss_Obsolete, kRulerPrefix + 10)

// gap
DECLARE_PMID(kClassIDSpace, kRulerUOMActionRegisterBoss, kRulerPrefix + 14)
// gap
DECLARE_PMID(kClassIDSpace, kRulerKBSCMenuActionBoss, kRulerPrefix + 16)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERDATA, kRulerPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERCARET, kRulerPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERSETTINGS, kRulerPrefix + 3)
// gap
//DECLARE_PMID(kInterfaceIDSpace, IID_IRULERCARETTHREADEH, kRulerPrefix + 6) //This is unused in CS5, so I commented it out for CS6 --djb

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kHorzRulerCaretImpl, kRulerPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kVertRulerCaretImpl, kRulerPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kHorzRulerViewImpl, kRulerPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kVertRulerViewImpl, kRulerPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kRulerDataImpl, kRulerPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kRulerViewObserverImpl, kRulerPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kRulerPanoramaImpl, kRulerPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kRulerCaretThreadImpl, kRulerPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kRulerEventHandlerImpl, kRulerPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kRulerSettingsImpl, kRulerPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kRulerMenuActionImpl, kRulerPrefix + 11)
// gap
DECLARE_PMID(kImplementationIDSpace, kSessionRulerPrefsImpl_Obsolete, kRulerPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDocRulerPrefsImpl_Obsolete, kRulerPrefix + 14)
//gap
DECLARE_PMID(kImplementationIDSpace, kRulerWorkspaceLayoutActionImpl, kRulerPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kRulerDropTargetCBImpl, kRulerPrefix + 19)

// used for guide tracking b/c it's not specific to a tool
DECLARE_PMID(kImplementationIDSpace, kGuideToolImpl, kRulerPrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kRulerHPopupMenuActionImpl, kRulerPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kRulerVPopupMenuActionImpl, kRulerPrefix + 22)

DECLARE_PMID(kImplementationIDSpace, kRulerCustomDlgControllerImpl, kRulerPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kRulerCustomMSImpl_Obsolete, kRulerPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCustomUnitOfMeasureServiceImpl_Obsolete, kRulerPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kRulerCaretThreadEHImpl, kRulerPrefix + 26)

// gap
DECLARE_PMID(kImplementationIDSpace, kSessionRulerCoordinatePrefsImpl_Obsolete, kRulerPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDocRulerCoordinatePrefsImpl_Obsolete, kRulerPrefix + 29)
// gap
DECLARE_PMID(kImplementationIDSpace, kRulerUOMActionRegisterImpl, kRulerPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kRulerCaretEventWatcherImpl, kRulerPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kRulerKBSCMenuActionImpl, kRulerPrefix + 34)

// WidgetID
DECLARE_PMID(kWidgetIDSpace, kRulerCustomEditBoxWidgetID, (kRulerPrefix + 1))

DECLARE_PMID(kWidgetIDSpace, kRulerCustomizeParentWidgetID, (kRulerPrefix + 2))
DECLARE_PMID(kWidgetIDSpace, kRulerPointsTextWidgetID, (kRulerPrefix + 3))

// ActionID
DECLARE_PMID(kActionIDSpace, kShowHideRulerActionID, (kRulerPrefix + 1))
DECLARE_PMID(kActionIDSpace, kRtMouseNothingRulerSepActionID, (kRulerPrefix + 2))
// DECLARE_PMID(kActionIDSpace, kMyCoolActionID, (kRulerPrefix + 3))
DECLARE_PMID(kActionIDSpace, kPopupVertRulerSep1ActionID, (kRulerPrefix + 4))

DECLARE_PMID(kActionIDSpace, kFirstHorzUOMActionID, (kRulerPrefix + 5))
	//Global IDs between kFirstHorzUOMActionID and kLastVertUOMActionID are reserved!
DECLARE_PMID(kActionIDSpace, kLastHorzUOMActionID, (kRulerPrefix + 25))
DECLARE_PMID(kActionIDSpace, kFirstVertUOMActionID, (kRulerPrefix + 26))
	//Global IDs between kFirstVertUOMActionID and kLastVertUOMActionID are reserved!
DECLARE_PMID(kActionIDSpace, kLastVertUOMActionID, (kRulerPrefix + 46))

DECLARE_PMID(kActionIDSpace, kCustomizeHorzRulerActionID, (kRulerPrefix + 47))
DECLARE_PMID(kActionIDSpace, kCustomizeVertRulerActionID, (kRulerPrefix + 48))
DECLARE_PMID(kActionIDSpace, kHRulerSep1ActionID, (kRulerPrefix + 49))
DECLARE_PMID(kActionIDSpace, kHRulerSep2ActionID, (kRulerPrefix + 50))
DECLARE_PMID(kActionIDSpace, kHRulerSep3ActionID, (kRulerPrefix + 51))
DECLARE_PMID(kActionIDSpace, kRulerPerPageActionID, (kRulerPrefix + 52))
DECLARE_PMID(kActionIDSpace, kRulerPerSpreadActionID, (kRulerPrefix + 53))
DECLARE_PMID(kActionIDSpace, kRulerOnSplineActionID, (kRulerPrefix + 54))
DECLARE_PMID(kActionIDSpace, kPopupVertRulerSep2ActionID, (kRulerPrefix + 55))
DECLARE_PMID(kActionIDSpace, kToggleMeasurementActionID, (kRulerPrefix + 56))
DECLARE_PMID(kActionIDSpace, kHRulerSep4ActionID, (kRulerPrefix + 57))
DECLARE_PMID(kActionIDSpace, kPopupVertRulerSep3ActionID, (kRulerPrefix + 58))

#endif // __RulerID__








