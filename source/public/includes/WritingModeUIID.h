//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WritingModeUIID.h $
//  
//  Owner: Kevin Van Wiel
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

#ifndef __WritingModeUIID__
#define __WritingModeUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define WSCROLLWIDTH 16.0

//========================================================================================
//	NOTE: WritingModeUIID2.h uses this prefix+100
//========================================================================================
#define kWMUIPrefix	RezLong(0x21700)	 


// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kWritingModeUIPluginName 				"GalleyUI"
DECLARE_PMID(kPlugInIDSpace, kWritingModeUIPluginID, kWMUIPrefix + 1)

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kWritingModeWidgetBoss, kWMUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kWritingModePanelBoss, kWMUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kWritingScrollSyncBoss, kWMUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kStoryBarGhostWidgetBoss, kWMUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kStoryBarTargetWidgetBoss, kWMUIPrefix + 14)


//Print and PDFExport
 DECLARE_PMID(kClassIDSpace, kNewPrintWritingPanelCmdBoss, kWMUIPrefix + 50)
 DECLARE_PMID(kClassIDSpace, kCreatePrintGalleyViewCmdBoss, kWMUIPrefix + 52)
 //gap

// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWDATA, kWMUIPrefix + 5)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILINENUMBERDRAWER, kWMUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINESTOREDRAWDATA, kWMUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYDISPLAYDATA, kWMUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWDIVIDER, kWMUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSETTINGSOVERWRITE, kWMUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYXMLELEMENTCACHE, kWMUIPrefix + 17)

DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEGALLEYVIEWCMDDATA, kWMUIPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWPRINTWRITINGPANELCMDDATA, kWMUIPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IWRITINGSTORYLIST, kWMUIPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDIRECTIONDATA, kWMUIPrefix + 54)

// <Implementation ID>
//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kImplementationIDSpace, kWritingModeControlView, kWMUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kWritingModePanel, kWMUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kStoryBarGhostControlViewImpl, kWMUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kStoryBarTargetControlViewImpl, kWMUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDropDirectionDataImpl, kWMUIPrefix + 9)

//gap
DECLARE_PMID(kImplementationIDSpace, kWritingObserverImpl, kWMUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kWritingPanoramaImpl, kWMUIPrefix + 17)
// removed kWritingParentShapeImpl, kWMUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kWritingScrollSyncImpl, kWMUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLayoutViewDataImpl, kWMUIPrefix + 21)
//gap
DECLARE_PMID(kImplementationIDSpace, kLineNumberDrawerImpl, kWMUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kLinesToRedrawData, kWMUIPrefix + 27)
// removed kZeroTilerImpl, kWMUIPrefix + 28)
// removed font size observer kWMUIPrefix + 30
DECLARE_PMID(kImplementationIDSpace, kGalleyDisplayData, kWMUIPrefix + 31)
// removed kLayoutObserverImpl, kWMUIPrefix + 32
DECLARE_PMID(kImplementationIDSpace, kDrawDividerImpl, kWMUIPrefix + 33)

DECLARE_PMID(kImplementationIDSpace, kGalleySettingsOverwriteImpl, kWMUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kGalleyXMLElementCacheImpl, kWMUIPrefix + 43)

//print and PDFexport
 DECLARE_PMID(kImplementationIDSpace, kNewPrintWritingPanelCmdImpl, kWMUIPrefix + 60)
 DECLARE_PMID(kImplementationIDSpace, kNewPrintWritingPanelCmdDataImpl, kWMUIPrefix + 61)
 DECLARE_PMID(kImplementationIDSpace, kCreatePrintGalleyViewCmdImpl, kWMUIPrefix + 62)
// //gap
DECLARE_PMID(kImplementationIDSpace, kCreateGalleyViewCmdDataImpl, kWMUIPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, kBasicWritingStoryListImpl, kWMUIPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, kGalleyWritingStoryListImpl, kWMUIPrefix + 67)




// <Widget id>
//---------------------------------------------------------------
//	Widget id's
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kWritingPanelId,			kWMUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kWritingId,				kWMUIPrefix + 31)
// gap
DECLARE_PMID(kWidgetIDSpace, kWritingStatsCharInfo,		kWMUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kWritingStatsWordInfo,		kWMUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kWritingStatsLineInfo,		kWMUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kGalleyFontSizeId,			kWMUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kGalleyFontSizeLabelId,	kWMUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kNoteWritingID,			kWMUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kWritingPanelId2,			kWMUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kStoryBarGhostWidgetID,	kWMUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kStoryBarTargetWidgetID,	kWMUIPrefix + 42)


#endif	//__WritingModeUIID__
