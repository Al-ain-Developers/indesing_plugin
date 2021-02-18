//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/OutputMiscUIID.h $
//  
//  Owner: Gang Xiao
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

#ifndef __OUTPUTMISCUIID_H__
#define __OUTPUTMISCUIID_H__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kOutputMiscUIPrefix		RezLong(0x10A00)			// Must be unique for this plug-in.

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------
#define kOutputMiscUITitle			"OutputMiscUIPlugIn"	// Basic name of plug-in. 
DECLARE_PMID(kPlugInIDSpace, kOutputMiscUIPlugInID, kOutputMiscUIPrefix + 1)	// Use as part of other keys, not alone.

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------
//for trap style panel
DECLARE_PMID(kClassIDSpace,	kTrapStylePanelBoss,						kOutputMiscUIPrefix + 1  )
//gap
DECLARE_PMID(kClassIDSpace,	kTrapStylePanelMenuComponentBoss,			kOutputMiscUIPrefix + 4  )
//gap
DECLARE_PMID(kClassIDSpace, kNewTrapStyleButtonBoss,					kOutputMiscUIPrefix + 7  )
DECLARE_PMID(kClassIDSpace, kDeleteTrapStyleButtonBoss,					kOutputMiscUIPrefix + 8  )
DECLARE_PMID(kClassIDSpace,	kTrapStyleDialogBoss,						kOutputMiscUIPrefix + 9  )
//gap
DECLARE_PMID(kClassIDSpace,	kTrapStylePanelListBoxWidgetBoss, 			kOutputMiscUIPrefix + 11 )
DECLARE_PMID(kClassIDSpace,	kTrapStyleListDEHandlerBoss, 				kOutputMiscUIPrefix + 12 )
DECLARE_PMID(kClassIDSpace,	kAssignTrapStyleDialogBoss, 				kOutputMiscUIPrefix + 13 )
DECLARE_PMID(kClassIDSpace,	kDeleteTrapStyleDialogBoss, 				kOutputMiscUIPrefix + 14 )

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
//for trap style panel
DECLARE_PMID(kImplementationIDSpace,	kTrapStylePanelMenuComponentImpl,			kOutputMiscUIPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace,	kTrapStyleDialogControllerImpl,				kOutputMiscUIPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace,	kNewTrapStyleButtonObserverImpl,			kOutputMiscUIPrefix + 3 )
DECLARE_PMID(kImplementationIDSpace,	kNewTrapStyleButtonDragDropTargetImpl,		kOutputMiscUIPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace,	kDeleteTrapStyleButtonObserverImpl,			kOutputMiscUIPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace,	kDeleteTrapStyleButtonDragDropTargetImpl,	kOutputMiscUIPrefix + 6 ) 
DECLARE_PMID(kImplementationIDSpace,	kTrapStyleListDragDropSourceImpl,			kOutputMiscUIPrefix + 7 )
DECLARE_PMID(kImplementationIDSpace,	kTrapStyleListDEHandlerImpl,				kOutputMiscUIPrefix + 8 )
DECLARE_PMID(kImplementationIDSpace,	kTrapStyleListBoxObserverImpl,				kOutputMiscUIPrefix + 9 )
DECLARE_PMID(kImplementationIDSpace,	kTrapStylePanelImpl,						kOutputMiscUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kAssignTrapStyleDialogControllerImpl,		kOutputMiscUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kDeleteTrapStyleDialogControllerImpl,		kOutputMiscUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kTrapStyleListboxEventHandlerImpl,			kOutputMiscUIPrefix + 13)

DECLARE_PMID(kImplementationIDSpace,	kAssignTrapStyleDialogObserverImpl,			kOutputMiscUIPrefix + 14)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
//for trap style panel
	//for panel itself
DECLARE_PMID(kWidgetIDSpace, kTrapStylePanelWidgetID,				kOutputMiscUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kDeleteTrapStyleButtonWidgetID,		kOutputMiscUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kNewTrapStyleButtonWidgetID,			kOutputMiscUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTrapStylePanelControlStripWidgetID,	kOutputMiscUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTrapStylePanelListWidgetID,			kOutputMiscUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTrapStylePanelSmallListWidgetID,		kOutputMiscUIPrefix + 6)
	//gap, for trap style dialog
DECLARE_PMID(kWidgetIDSpace, kTrapStyleDialogWidgetID,				kOutputMiscUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleNameTextWidgetID,			kOutputMiscUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleNameEditWidgetID,			kOutputMiscUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleColorReduceTextWidgetID,		kOutputMiscUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleColorReduceEditWidgetID,		kOutputMiscUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleDefaultWidgetID,				kOutputMiscUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleBlackWidthWidgetID,			kOutputMiscUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleStepLimitWidgetID,			kOutputMiscUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleBlackColorLimitWidgetID,		kOutputMiscUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleBlackDensityLimitWidgetID,	kOutputMiscUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleSlidingTrapLimitWidgetID,	kOutputMiscUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleDropDownListWidgetID,		kOutputMiscUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleObj2ImgWidgetID,				kOutputMiscUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleImg2ImgWidgetID,				kOutputMiscUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleInternalImgWidgetID,			kOutputMiscUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kTrapStyle1BitImgWidgetID,				kOutputMiscUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kJoinStyleDropDownListWidgetID,		kOutputMiscUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kEndStyleDropDownListWidgetID,			kOutputMiscUIPrefix + 28)
	//gap, for page's trap style dialog
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleDialogWidgetID,		kOutputMiscUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleTextWidgetID,			kOutputMiscUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStylePopupWidgetID,			kOutputMiscUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleAssignButtonWidgetID,	kOutputMiscUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStylePagesTextWidgetID,		kOutputMiscUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleAllRadioBtnWidgetID,	kOutputMiscUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStylePagesGroupWidgetID,	kOutputMiscUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStylePagesRadioBtnWidgetID,	kOutputMiscUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStylePageRangeWidgetID,		kOutputMiscUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleInfoGroupWidgetID,		kOutputMiscUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleInfoTextWidgetID,		kOutputMiscUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kAssignTrapStyleTextScrollWidgetID,	kOutputMiscUIPrefix + 41)
	//gap, for delete trap style dialog
DECLARE_PMID(kWidgetIDSpace, kDeleteTrapStyleDialogWidgetID,		kOutputMiscUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kDeleteTrapStylePopupWidgetID,			kOutputMiscUIPrefix + 51)
	//starting at 75 to leave gap
//Adding Widget ID's so that trap dialog does not use invalid widget ID
DECLARE_PMID(kWidgetIDSpace, kTrapWidthGroupWidgetID,				kOutputMiscUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTrapWidthStringWidgetID,				kOutputMiscUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kTrapWidthDefaultStringWidgetID,		kOutputMiscUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kTrapWidthBlackStringWidgetID,			kOutputMiscUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kTrapAppearanceGroupWidgetID,			kOutputMiscUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kTrapAppearanceStringWidgetID,			kOutputMiscUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kTrapJoinStyleStringWidgetID,			kOutputMiscUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kTrapEndStyleStringWidgetID,			kOutputMiscUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kTrapImagesGroupWidgetID,				kOutputMiscUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kTrapImagesStringWidgetID,				kOutputMiscUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kTrapPlacementStringWidgetID,			kOutputMiscUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kTrapThreshholdGroupWidgetID,			kOutputMiscUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kTrapThreshholdStringWidgetID,			kOutputMiscUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kTrapStepStringWidgetID,				kOutputMiscUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kTrapBlackColorStringWidgetID,			kOutputMiscUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kTrapBlackDensityStringWidgetID,		kOutputMiscUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kTrapSlidingStringWidgetID,			kOutputMiscUIPrefix + 91)

// EVE Info
DECLARE_PMID(kWidgetIDSpace, kTrapStyleControlsColWidgetID,			kOutputMiscUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kTrapStyleButtonsColWidgetID,			kOutputMiscUIPrefix + 101)

//----------------------------------------------------------------------------------------
// Message identifiers
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
//for trap style panel
DECLARE_PMID(kActionIDSpace,	kTrapStylePanelActionID, 			kOutputMiscUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,	kNewTrapStyleActionID, 				kOutputMiscUIPrefix + 10)
DECLARE_PMID(kActionIDSpace,	kDuplicateTrapStyleActionID, 		kOutputMiscUIPrefix + 11)
DECLARE_PMID(kActionIDSpace,	kDeleteTrapStyleActionID, 			kOutputMiscUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,	kTrapStyleOptionsActionID, 			kOutputMiscUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,	kLoadTrapStylesActionID, 			kOutputMiscUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,	kSelectAllUnusedTrapStylesActionID, kOutputMiscUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,	kSmallTrapPaletteRowsActionID, 		kOutputMiscUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,	kAssignTrapStyleActionID,			kOutputMiscUIPrefix + 17)
DECLARE_PMID(kActionIDSpace,	kTrapStylePopupSep1ActionID,		kOutputMiscUIPrefix + 18)
DECLARE_PMID(kActionIDSpace,	kTrapStylePopupSep2ActionID,		kOutputMiscUIPrefix + 19)
DECLARE_PMID(kActionIDSpace,	kTrapStylePopupSep3ActionID,		kOutputMiscUIPrefix + 20)

#endif // __OUTPUTMISCUIID_H__
