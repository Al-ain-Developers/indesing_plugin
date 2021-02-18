//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/TrackChangesUIID.h $
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

#ifndef __TRACKCHANGESUIID__
#define __TRACKCHANGESUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTrackChangesUIPrefix	 RezLong(0xa500)	// reserved in AdobePrefix.h

//PlugInID
#define kTrackChangesUIPlugInName		"TrackChangesUI"
DECLARE_PMID(kPlugInIDSpace, kTrackChangesUIPlugInID, kTrackChangesUIPrefix + 1)

//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kChangesDialogBoss, 					kTrackChangesUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kChangesDialogMenuActionBoss, 			kTrackChangesUIPrefix + 3)
/// Gap - DECLARE_PMID(kClassIDSpace, kSelectDeletedTextCmdBoss, 				kTrackChangesUIPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kShowChangeButtonBoss,					kTrackChangesUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAcceptChangeButtonBoss,				kTrackChangesUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kRejectChangeButtonBoss,				kTrackChangesUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPrevChangeButtonBoss,					kTrackChangesUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kNextChangeButtonBoss,					kTrackChangesUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kChangesCommandbarBoss,					kTrackChangesUIPrefix + 12)
/// GAP - DECLARE_PMID(kClassIDSpace, kChangesKitRegisterBoss,				kTrackChangesUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kChangesInfoBoss,						kTrackChangesUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kAcceptAllChangeButtonBoss,				kTrackChangesUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kRejectAllChangeButtonBoss,				kTrackChangesUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTrackInCurrentButtonBoss,				kTrackChangesUIPrefix + 17)


//---------------------------------------------------------------
//	Widget IDs
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kChangesParentWidgetId,			kTrackChangesUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogUserName,			kTrackChangesUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogUserData,			kTrackChangesUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogTimeName,			kTrackChangesUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogTimeData,			kTrackChangesUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogTypeName,			kTrackChangesUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogTypeData,			kTrackChangesUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kChangeInfoTitleText,				kTrackChangesUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogDoneBtn,				kTrackChangesUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogNextBtn,				kTrackChangesUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogAcceptBtn,			kTrackChangesUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogRejectBtn, 			kTrackChangesUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogAcceptAllBtn,		kTrackChangesUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogRejectAllBtn,		kTrackChangesUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogSearchName,			kTrackChangesUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kChangesDialogSearchDropdown,		kTrackChangesUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kChangesShowAllCheckboxWidgetId,	kTrackChangesUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kShowChangeButtonWidgetID,			kTrackChangesUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kAcceptChangeButtonWidgetID,		kTrackChangesUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kRejectChangeButtonWidgetID,		kTrackChangesUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPrevChangeButtonWidgetID,			kTrackChangesUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kNextChangeButtonWidgetID,			kTrackChangesUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kChangesCommandbarHBarViewWidgetID, kTrackChangesUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kChangesCommandbarTablessViewWidgetID, kTrackChangesUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kChangesCommandbarVBarViewWidgetID, kTrackChangesUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kShowChangesControlSetWidgetID,	kTrackChangesUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kNavChangesControlSetWidgetID,		kTrackChangesUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kAcceptRejectControlSetWidgetID,	kTrackChangesUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kChangesCommandbarPanelWidgetID,	kTrackChangesUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kChangesInfoPanelWidgetID,			kTrackChangesUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kChangeUserIconWidgetID,			kTrackChangesUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kChangeUserInfoWidgetID,			kTrackChangesUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kChangeDateIconWidgetID,			kTrackChangesUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kChangeDateInfoWidgetID,			kTrackChangesUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kChangeTypeIconWidgetID,			kTrackChangesUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kChangeTypeInfoWidgetID,			kTrackChangesUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kChangesInfoHBarViewWidgetID,		kTrackChangesUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kChangesInfoTabViewWidgetID,		kTrackChangesUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kAcceptAllChangeButtonWidgetID,	kTrackChangesUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kRejectAllChangeButtonWidgetID,	kTrackChangesUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kAcceptAllChangesWarningID,		kTrackChangesUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kAcceptAllSomeHiddenChangesWarningID,	kTrackChangesUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kRejectAllChangesWarningID,		kTrackChangesUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kRejectAllSomeHiddenChangesWarningID,	kTrackChangesUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kTrackInCurrentButtonWidgetID,		kTrackChangesUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTrackingControlSetWidgetID,		kTrackChangesUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kChangeUserBorderWidgetID,			kTrackChangesUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kChangeDateBorderWidgetID,			kTrackChangesUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kChangeTypeBorderWidgetID,			kTrackChangesUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kTCCommandsControlSetWidgetID,		kTrackChangesUIPrefix + 80)

//---------------------------------------------------------------
//	Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGESSELECTIONOBSERVER, 			kTrackChangesUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDTEXTNAVIGATIONOBSERVER, 	kTrackChangesUIPrefix + 2)
/// Gap - DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTDELETEDTEXTCMDDATA, 			kTrackChangesUIPrefix + 3)
/// Gap - DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGESCMDBARTEXTOBSERVER_REUSE,	kTrackChangesUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGEINFOSUITE,					kTrackChangesUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGESREVIEWSUITE,				kTrackChangesUIPrefix + 6)

//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------
/// Gap - DECLARE_PMID(kImplementationIDSpace, kTrackChangesUIStringRegImpl,			kTrackChangesUIPrefix + 1)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kChangesDialogObserverImpl,			kTrackChangesUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kChangesDialogMenuActionImpl,			kTrackChangesUIPrefix + 3)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kChangesDialogControllerImpl,			kTrackChangesUIPrefix + 4)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kChangesDialogControlViewImpl,			kTrackChangesUIPrefix + 6)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kSelectDeletedTextCmdImpl,				kTrackChangesUIPrefix + 7)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kSelectDeletedTextCmdDataImpl,			kTrackChangesUIPrefix + 8)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kDeletedTextNavigationObserverImpl,	kTrackChangesUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kShowChangeButtonObserverImpl,			kTrackChangesUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAcceptChangeButtonObserverImpl,		kTrackChangesUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kRejectChangeButtonObserverImpl,		kTrackChangesUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPrevChangeButtonObserverImpl,			kTrackChangesUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNextChangeButtonObserverImpl,			kTrackChangesUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kChangesCommandbarTipImpl,				kTrackChangesUIPrefix + 15)
/// Gap - DECLARE_PMID(kImplementationIDSpace, kChangesCmdBarTextObserverImpl_Reuse,	kTrackChangesUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kChangeInfoSuiteASBImpl,				kTrackChangesUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kChangeInfoSuiteGalleyCSBImpl,			kTrackChangesUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kChangesInfoObserverImpl,				kTrackChangesUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kAcceptAllChangeButtonObserverImpl,	kTrackChangesUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kRejectAllChangeButtonObserverImpl,	kTrackChangesUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kChangesReviewSuiteASBImpl,			kTrackChangesUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kChangesReviewSuiteGalleyCSBImpl,		kTrackChangesUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTrackInCurrentButtonObserverImpl,		kTrackChangesUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kChangesReviewSuiteLayoutCSBImpl,		kTrackChangesUIPrefix + 25)

//---------------------------------------------------------------
//	Message IDs
//---------------------------------------------------------------
DECLARE_PMID(kMessageIDSpace, kChangesDialogActivatedMsg, 		kTrackChangesUIPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kChangesDialogDeactivatedMsg, 	kTrackChangesUIPrefix + 2)

//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator1MAID, 			kTrackChangesUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator2MAID, 			kTrackChangesUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator3MAID, 			kTrackChangesUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator4MAID, 			kTrackChangesUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptMenuMAID, 		kTrackChangesUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectMenuMAID, 		kTrackChangesUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kTrackChangesPreviousMenuMAID, 	kTrackChangesUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kTrackChangesNextMenuMAID, 		kTrackChangesUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kChangesPanelActionID,				kTrackChangesUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kChangesInfoPanelActionID,			kTrackChangesUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptAllMenuMAID, 	kTrackChangesUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectAllMenuMAID, 	kTrackChangesUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kTrackChangesMenuMAID,			 	kTrackChangesUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kShowChangesMenuMAID,			 	kTrackChangesUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kShowChangesMenuSeparatorMAID,	 	kTrackChangesUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kChangesSearchStoryActionID,	 	kTrackChangesUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kChangesSearchAllStoryActionID,	 kTrackChangesUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kAllStoriesEnableActionID, 		kTrackChangesUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kAllStoriesDisableActionID, 		kTrackChangesUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator5MAID,	 	kTrackChangesUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptAllStoriesMenuMAID,	 	kTrackChangesUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectAllStoriesMenuMAID,	 	kTrackChangesUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptAndNextMenuMAID,	 	kTrackChangesUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectAndNextMenuMAID,	 	kTrackChangesUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptAllByUserMenuMAID,	 	kTrackChangesUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectAllByUserMenuMAID,	 	kTrackChangesUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kTrackChangesAcceptAllStoriesByUserMenuMAID,	 	kTrackChangesUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kTrackChangesRejectAllStoriesByUserMenuMAID,	 	kTrackChangesUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kTCMenuSeparator6MAID,	 	kTrackChangesUIPrefix + 29)

#endif // __TRACKCHANGESUIID__




