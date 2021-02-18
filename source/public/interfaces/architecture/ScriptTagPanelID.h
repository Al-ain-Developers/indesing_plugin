//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ScriptTagPanelID.h $
//  
//  Owner: Peter Boctor
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

#ifndef __ScriptTagPanelID__
#define __ScriptTagPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kScriptTagPanelPrefix	 RezLong(0x13400)

// plug-in ID
#define kScriptTagPanelPluginName 					"ScriptTagPanel"
DECLARE_PMID(kPlugInIDSpace, kScriptTagPanelPluginID, kScriptTagPanelPrefix + 1)

// <Start IDC>
// <Class ID>
//gap
DECLARE_PMID(kClassIDSpace, kScriptTagEditBoxBoss, kScriptTagPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetScriptTagEditBoxObserverBoss, kScriptTagPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kScriptTagPanelBoss, kScriptTagPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kScriptTagPanelTestMenuBoss, kScriptTagPanelPrefix + 6)	// DEBUG
DECLARE_PMID(kClassIDSpace, kScriptTagMgrBoss, kScriptTagPanelPrefix + 7)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTTAGEDITBOXOBSERVER, kScriptTagPanelPrefix + 1)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kScriptTagEditBoxObserverImpl, kScriptTagPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSetScriptTagEditBoxObserverImpl, kScriptTagPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kScriptTagEditEHImpl, kScriptTagPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kScriptTagPanelViewImpl, kScriptTagPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kScriptTagMgrImpl, kScriptTagPanelPrefix + 5)
//gap
DECLARE_PMID(kImplementationIDSpace, kScriptPanelTestMenuImpl, 		kScriptTagPanelPrefix + 251)	// DEBUG ONLY

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kScriptTagEditBoxWidgetID, kScriptTagPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kScriptTagParentWidgetId, kScriptTagPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kScriptTagLabelWidgetID, kScriptTagPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kScriptTagControlStripWidgetID, kScriptTagPanelPrefix + 4)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kScriptTagPanelActionID, kScriptTagPanelPrefix + 1)

#endif //__SCRIPTNPANELID__
