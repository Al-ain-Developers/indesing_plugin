//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ContribPanelID.h $
//  
//  Owner: Daniel Guenther
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
//  Contains IDs used by the XMedia UI
//  
//========================================================================================

#ifndef __ContribPanelID__
#define __ContribPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kContribPanelPrefix			RezLong(0x23300)  

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kContribPanelPluginName 	"Contributors Panel"
DECLARE_PMID(kPlugInIDSpace, kContribPanelPluginID, kContribPanelPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

//Plugin
DECLARE_PMID(kClassIDSpace,		kContribPanelPanelRegisterBoss,		kContribPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kContribPanelStringRegisterBoss,	kContribPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kContribPanelActionRegisterBoss,	kContribPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kContribPanelMenuRegisterBoss,		kContribPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kContribPanelTipsRegisterBoss,		kContribPanelPrefix + 6)


DECLARE_PMID(kClassIDSpace,		kContribPanelBoss,								kContribPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kContribTVWidgetBoss,						kContribPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kContribPanelTreeNodeWidgetBoss,	kContribPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kContribNameStaticTextBoss,					kContribPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace,		kNoteNodeWidgetBoss,						kContribPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kChangeNodeWidgetBoss,						kContribPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kContribPanelActionComponentBoss,	kContribPanelPrefix + 13)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,	IID_ISHOWUSERCOLORBOOL,		kContribPanelPrefix + 1)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

// XML Panel
DECLARE_PMID(kImplementationIDSpace, kContribPanelViewImpl,										kContribPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kContribPanelTreeViewAdapterImpl,				kContribPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kContribPanelTreeViewWidgetMgrImpl,		kContribPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kContribPanelObserverImpl,								kContribPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kContribPanelNoteViewImpl,								kContribPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kContribPanelChangeViewImpl,						kContribPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kContribPanelActionComponentImpl,				kContribPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kContribPanelContribViewImpl,						kContribPanelPrefix + 8)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

// Contrib Panel
DECLARE_PMID(kWidgetIDSpace,	kContribPanelWidgetID,					kContribPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,	kContribBorderWidgetID,					kContribPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,	kContribTVWidgetID,						kContribPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,	kContribPanelNodeWidgetId,			kContribPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,	kContribPanelSmallNodeWidgetId,	kContribPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,	kContribNodeNameWidgetID,				kContribPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,	kNoteNodeWidgetId,							kContribPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,	kNoteNodeNameWidgetID,					kContribPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,	kChangeNodeWidgetId,							kContribPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,	kChangeNodeNameWidgetID,					kContribPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,	kBranchIconWidgetID,							kContribPanelPrefix + 11)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kActionIDSpace,	kContribPanelActionID,						kContribPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace,	kContribUserColorActionID,				kContribPanelPrefix + 2)

#endif // __ContribPanelID__
