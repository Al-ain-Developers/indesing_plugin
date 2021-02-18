//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/AlignPanelID.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __AlignPanelID__
#define __AlignPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kAlignPanelPrefix	 RezLong(0x6500)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kAlignPanelPluginName 			"Alignment Panel"
DECLARE_PMID(kPlugInIDSpace, kAlignPanelPluginID, kAlignPanelPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,		kAlignPanelBoss, 				kAlignPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kAlignControlStripBoss,			kAlignPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kControlStripAlignRegisterBoss, kAlignPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kAlignButtonsPanelBoss,			kAlignPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kDistributeButtonsPanelBoss,	kAlignPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace,		kSpacingButtonsPanelBoss,		kAlignPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kDistributeControlStripBoss,	kAlignPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kDistributeGuidesControlStripBoss,	kAlignPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kDistributeSpreadControlStripBoss,	kAlignPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kVDistributeTopWidgetBoss, 		kAlignPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace,		kVDistributeCenterWidgetBoss, 	kAlignPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kVDistributeBottomWidgetBoss, 	kAlignPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kHDistributeLeftWidgetBoss, 	kAlignPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace,		kHDistributeCenterWidgetBoss, 	kAlignPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace,		kHDistributeRightWidgetBoss, 	kAlignPanelPrefix + 15)

DECLARE_PMID(kClassIDSpace,		kVDistributeSpaceWidgetBoss, 	kAlignPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace,		kHDistributeSpaceWidgetBoss, 	kAlignPanelPrefix + 17)

DECLARE_PMID(kClassIDSpace,		kAlignPanelMenuComponentBoss, 	kAlignPanelPrefix + 18)
//gap
DECLARE_PMID(kClassIDSpace,		kDistributeCheckBoxWidgetBoss,	kAlignPanelPrefix + 20)
//gap
DECLARE_PMID(kClassIDSpace,		kAlignControlStripIconPopUpBoss,		kAlignPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace,		kAlignControlStripMenuPopUpBoss,		kAlignPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace,		kAlignTypeCmdBoss,						kAlignPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace,		kDistributeSpaceXMeasureWidgetBoss,		kAlignPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace,		kAlignTouchPanelBoss,					kAlignPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace,		kAlignPanelPropPanelBoss,				kAlignPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace,		kDistributePanelPropPanelBoss,			kAlignPanelPrefix + 28)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNBUTTONOBSERVER, kAlignPanelPrefix + 1 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDISTRIBUTEBUTTONOBSERVER, kAlignPanelPrefix + 2 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISPACINGBUTTONOBSERVER, kAlignPanelPrefix + 3 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPALIGNSUITE, kAlignPanelPrefix + 4)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace,		kControlStripAlignSuiteImpl,		kAlignPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,		kControlStripAlignRegisterImpl,		kAlignPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,		kAlignButtonObserverImpl, 			kAlignPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,		kDistributeButtonObserverImpl, 		kAlignPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,		kSpacingButtonObserverImpl, 		kAlignPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,		kControlStripSpreadAlignSuiteImpl,	kAlignPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,		kAlignSelectionObserverImpl,        kAlignPanelPrefix + 8)
// gap

DECLARE_PMID(kImplementationIDSpace,		kAlignPanelMenuComponentImpl, 		kAlignPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace,		kDistributeCheckBoxObserverImpl, 	kAlignPanelPrefix + 21)
// gap
DECLARE_PMID(kImplementationIDSpace,		kAlignControlStripMenuComponentImpl, 	kAlignPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,		kAlignSettingsImpl_Obsolete, 		kAlignPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace,		kAlignTypeMenuPanelObserverImpl, 	kAlignPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,		kAlignTypeIconTipImpl, 				kAlignPanelPrefix + 26)
//gap
DECLARE_PMID(kImplementationIDSpace,		kDistributeXMeasureObserverImpl, 	kAlignPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,		kAlignTouchPanelObserverImpl,		kAlignPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,		kAlignPanelPropPnlActiveKitImpl,	kAlignPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,		kDistributePanelPropPnlActiveKitImpl,		kAlignPanelPrefix + 31)


//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kWidgetIDSpace,		kHAlignLeftWidgetID, 				kAlignPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,		kHAlignCenterWidgetID, 				kAlignPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,		kHAlignRightWidgetID, 				kAlignPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,		kVAlignTopWidgetID, 				kAlignPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,		kVAlignCenterWidgetID, 				kAlignPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,		kVAlignBottomWidgetID, 				kAlignPanelPrefix + 6)

DECLARE_PMID(kWidgetIDSpace,		kVDistributeTopWidgetID, 			kAlignPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,		kVDistributeCenterWidgetID, 		kAlignPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,		kVDistributeBottomWidgetID, 		kAlignPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,		kHDistributeLeftWidgetID, 			kAlignPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,		kHDistributeCenterWidgetID, 		kAlignPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,		kHDistributeRightWidgetID, 			kAlignPanelPrefix + 12)

DECLARE_PMID(kWidgetIDSpace,		kVDistributeSpaceWidgetID, 			kAlignPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,		kHDistributeSpaceWidgetID, 			kAlignPanelPrefix + 14)

DECLARE_PMID(kWidgetIDSpace,		kAlignPanelWidgetID, 				kAlignPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,		kAlignSubPanelWidgetID, 			kAlignPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,		kDistributeSubPanelWidgetID, 		kAlignPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,		kSpacingSubPanelWidgetID, 			kAlignPanelPrefix + 18)

DECLARE_PMID(kWidgetIDSpace,		kAlignObjectsTextWidgetId, 			kAlignPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,		kDistributeSeperatorWidgetId, 		kAlignPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,		kDistributeObjectsTextWidgetId, 	kAlignPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,		kSpacingSeperatorWidgetId, 			kAlignPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,		kDistributeSpacingTextWidgetId, 	kAlignPanelPrefix + 23)

DECLARE_PMID(kWidgetIDSpace,		kDSUsingSpaceCheckboxWidgetID, 		kAlignPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,		kSpaceValueWidgetId, 				kAlignPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,		kDOUsingSpaceCheckboxWidgetID, 		kAlignPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace,		kDistributeValueWidgetId,		 	kAlignPanelPrefix + 27)

DECLARE_PMID(kWidgetIDSpace,		kDistributeGroupWidgetID,		 	kAlignPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace,		kAlignTypeDropDownWidgetID,		 	kAlignPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace,		kDistributeTypeDropDownWidgetID,	kAlignPanelPrefix + 30)

DECLARE_PMID(kWidgetIDSpace,		kDistributeValueNudgeWidgetId,		kAlignPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace,		kSpaceValueNudgeWidgetId,			kAlignPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace,		kAlignTouchPanelWidgetID,			kAlignPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace,		kAlignmentTypePanelWidgetId,		kAlignPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace,		kObjectAlignmentPanelWidgetId,		kAlignPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace,		kDistributeAlignmentPanelWidgetId,	kAlignPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace,		kAlignToPageStaticWidgetId,			kAlignPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace,		kAlignmentTypeTextWidgetId,			kAlignPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace,		kAlignmentTypeSwitcherWidgetId,		kAlignPanelPrefix + 39)
DECLARE_PMID(kWidgetIDSpace,		kAlignToSelectionStaticWidgetId,	kAlignPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace,		kAlignTokeyObjectWidgetId,			kAlignPanelPrefix + 41)
//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,		kAlignPanelActionID, 		kAlignPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace,		kShowAlignOptionsActionID, 	kAlignPanelPrefix + 2)

DECLARE_PMID(kActionIDSpace,		kAlignSelectionActionID, 	kAlignPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace,		kAlignMarginsActionID, 		kAlignPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace,		kAlignPageActionID, 		kAlignPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace,		kAlignSpreadActionID, 		kAlignPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace,		kAlignKeyObjectActionID, 	kAlignPanelPrefix + 7)

DECLARE_PMID(kActionIDSpace,		kAlignPanelSepActionID, 	kAlignPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace,		kCancelKeyObjectActionID,	kAlignPanelPrefix + 9)

#endif // __AlignPanelID__

