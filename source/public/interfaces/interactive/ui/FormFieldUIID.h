//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/FormFieldUIID.h $
//  
//  Owner: Mark VerMurlen
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
//  Contains IDs used by the FormFieldUI plug-in
//  
//========================================================================================

#ifndef __FormFieldUIID__
#define __FormFieldUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kFormFieldUIPrefix	 RezLong(0x14600)

// PluginID
#define kFormFieldUIPluginName				"FormFieldUI"
#define kFormFieldUIPluginID 				kFormFieldUIPrefix + 1

// Format Numbers

// Anna
#define kFormFieldUIAnnaRemoveImpls		kAnnaInitialMinorFormatNumber

// Add one of these for each product version.
#define kFormFieldUILastAnnaMinorFormat	kFormFieldUIAnnaRemoveImpls

// Overall numbers.
#define	kFormFieldUILatestMajorFormat		kAnnaMajorFormatNumber
#define	kFormFieldUILatestMinorFormat		kFormFieldUILastAnnaMinorFormat

// ClassIDs (Boss IDs)
DECLARE_PMID(kClassIDSpace, kFormFieldUIComponentBoss,			kFormFieldUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kFormFieldUITrackerRegisterBoss,	kFormFieldUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kToggleStatesButtonBoss,			kFormFieldUIPrefix + 4)


DECLARE_PMID(kClassIDSpace, kFormToolBoss, 						kFormFieldUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kFormTrackerBoss, 					kFormFieldUIPrefix + 11)

DECLARE_PMID(kClassIDSpace, kPushButtonToolBoss, 				kFormFieldUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPushButtonTrackerBoss, 			kFormFieldUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCheckBoxToolBoss, 					kFormFieldUIPrefix + 14) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kCheckBoxTrackerBoss, 				kFormFieldUIPrefix + 15) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kRadioButtonToolBoss, 				kFormFieldUIPrefix + 16) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kRadioButtonTrackerBoss, 			kFormFieldUIPrefix + 17) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextFieldToolBoss, 				kFormFieldUIPrefix + 18) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextFieldTrackerBoss, 				kFormFieldUIPrefix + 19) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kListBoxToolBoss, 					kFormFieldUIPrefix + 20) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kListBoxTrackerBoss, 				kFormFieldUIPrefix + 21) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kComboBoxToolBoss, 					kFormFieldUIPrefix + 22) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kComboBoxTrackerBoss, 				kFormFieldUIPrefix + 23) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kSignatureFieldToolBoss, 			kFormFieldUIPrefix + 24) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kSignatureFieldTrackerBoss, 		kFormFieldUIPrefix + 25) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kConvertToButtonButtonBoss, 		kFormFieldUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kConvertToObjectButtonBoss, 		kFormFieldUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kFormChoiceListBoxBoss, 			kFormFieldUIPrefix + 28) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormTextColorDialogBoss, 			kFormFieldUIPrefix + 29) 		// Reserved for possible future implementation, do not use

	//Appearance Panel
DECLARE_PMID(kClassIDSpace, kAppearancePanelBoss,				kFormFieldUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kStateListBoxBoss,					kFormFieldUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kNewStateButtonBoss,				kFormFieldUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kDeleteStateButtonBoss,				kFormFieldUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kAppearancePanelActiveBoss,			kFormFieldUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kStateListElementBoss,				kFormFieldUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kAppearancePanelElementEyeballBoss, kFormFieldUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kAppearancePanelElementPencilBoss,	kFormFieldUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kAppearancePanelElementNameBoss,	kFormFieldUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kAppearancePanelEyeballBoss,		kFormFieldUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kAppearancePanelPencilBoss,			kFormFieldUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kAppearancePanelThumbnailBoss,		kFormFieldUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kAppearancePanelNameBoss,			kFormFieldUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kAppearancePanelSelectionProxyBoss, kFormFieldUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kStateProxyDEHandlerBoss,			kFormFieldUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kAppearancePanelMenuComponentBoss,	kFormFieldUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kStateEyeDEHandlerBoss,				kFormFieldUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kButtonEventChoicesWidgetBoss,		kFormFieldUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kListBoxDEHandlerBoss, 				kFormFieldUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kPlaceIntoStateButtonBoss, 			kFormFieldUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kDeleteStateContentButtonBoss, 		kFormFieldUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kActionChoicesWidgetBoss,			kFormFieldUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kActionEnableWidgetBoss,			kFormFieldUIPrefix + 57)

//Misc Dialogs
DECLARE_PMID(kClassIDSpace, kAppearancePanelPrefsDialogBoss, 	kFormFieldUIPrefix + 70)
DECLARE_PMID(kClassIDSpace, kPreviewButtonBoss,					kFormFieldUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kStatePropertiesDialogBoss, 		kFormFieldUIPrefix + 72)

//Tab/Calc Order
DECLARE_PMID(kClassIDSpace, kCalculationOrderDialogBoss, 		kFormFieldUIPrefix + 80)
DECLARE_PMID(kClassIDSpace, kTabOrderDialogBoss, 				kFormFieldUIPrefix + 81)
DECLARE_PMID(kClassIDSpace, kOrderListBoxBoss, 					kFormFieldUIPrefix + 82)

//Field Settings Data Panels
DECLARE_PMID(kClassIDSpace, kFormFieldSettingsHolderPanelBoss, 	kFormFieldUIPrefix + 83)
DECLARE_PMID(kClassIDSpace, kCheckBoxDataPanelBoss, 			kFormFieldUIPrefix + 84) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kListBoxDataPanelBoss, 				kFormFieldUIPrefix + 85) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kRadioButtonDataPanelBoss, 			kFormFieldUIPrefix + 86) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextFieldDataPanelBoss, 			kFormFieldUIPrefix + 87) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kComboBoxDataPanelBoss, 			kFormFieldUIPrefix + 88) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kFormOptionsDialogBoss, 			kFormFieldUIPrefix + 90)
DECLARE_PMID(kClassIDSpace, kActionHolderPanelWidgetBoss, 		kFormFieldUIPrefix + 91)
DECLARE_PMID(kClassIDSpace, kActionsWidgetBoss,					kFormFieldUIPrefix + 92)
DECLARE_PMID(kClassIDSpace, kAddActionIconPopUpBoss,			kFormFieldUIPrefix + 93)
DECLARE_PMID(kClassIDSpace, kRemoveActionButtonBoss,			kFormFieldUIPrefix + 94)
DECLARE_PMID(kClassIDSpace, kShowFieldButtonBoss,				kFormFieldUIPrefix + 95)
DECLARE_PMID(kClassIDSpace, kHideFieldButtonBoss,				kFormFieldUIPrefix + 96)
DECLARE_PMID(kClassIDSpace, kIgnoreFieldButtonBoss,				kFormFieldUIPrefix + 97)
DECLARE_PMID(kClassIDSpace, kGoToURLComboBoxWidgetBoss,			kFormFieldUIPrefix + 98)

DECLARE_PMID(kClassIDSpace, kMSOPanelBoss,			kFormFieldUIPrefix + 99)
DECLARE_PMID(kClassIDSpace, kMSOPanelMenuActionBoss,	kFormFieldUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, kMSOPanelStatusAreaWidgetBoss,		kFormFieldUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kNewMSOStateButtonBoss,				kFormFieldUIPrefix + 102)
DECLARE_PMID(kClassIDSpace, kDeleteMSOStateButtonBoss,			kFormFieldUIPrefix + 103)
DECLARE_PMID(kClassIDSpace, kMSOPanelTreeWidgetBoss,			kFormFieldUIPrefix + 104)
DECLARE_PMID(kClassIDSpace, kMSOPanelStateThumbnailBoss,		kFormFieldUIPrefix + 105)
DECLARE_PMID(kClassIDSpace, kMSOPanelStateNameILEBoss,		kFormFieldUIPrefix + 106)
DECLARE_PMID(kClassIDSpace, kMSOPanelTreeViewNodeWidgetBoss,	kFormFieldUIPrefix + 107)
DECLARE_PMID(kClassIDSpace, kMSOPanelStateDNDHandlerBoss,	kFormFieldUIPrefix + 108)
DECLARE_PMID(kClassIDSpace, kMSOSelectionIconBoss,	kFormFieldUIPrefix + 109)


DECLARE_PMID(kClassIDSpace, kMSOStateDDLElementWidgetBoss,	kFormFieldUIPrefix + 111)
DECLARE_PMID(kClassIDSpace, kPasteIntoMSOStateButtonBoss,	kFormFieldUIPrefix + 112)
DECLARE_PMID(kClassIDSpace, kAddToMSOStateButtonBoss,		kFormFieldUIPrefix + 113)
DECLARE_PMID(kClassIDSpace, kPDFOptionsWidgetBoss,			kFormFieldUIPrefix + 114)
DECLARE_PMID(kClassIDSpace, kAddListOptionButtonBoss,		kFormFieldUIPrefix + 115)
DECLARE_PMID(kClassIDSpace, kRemoveListOptionButtonBoss,	kFormFieldUIPrefix + 116)
DECLARE_PMID(kClassIDSpace, kListItemsTreeViewWidgetBoss,	kFormFieldUIPrefix + 117)
DECLARE_PMID(kClassIDSpace, kListItemsNodeWidgetBoss,		kFormFieldUIPrefix + 118)
DECLARE_PMID(kClassIDSpace, kListItemsDDHandlerBoss,		kFormFieldUIPrefix + 119)
DECLARE_PMID(kClassIDSpace, kFontSizeComboBoxWidgetBoss,	kFormFieldUIPrefix + 120)
DECLARE_PMID(kClassIDSpace, kListItemEditBoxWidgetBoss, kFormFieldUIPrefix + 121)
DECLARE_PMID(kClassIDSpace, kFormsTypeaheadTextCBWidgetObserverBoss, kFormFieldUIPrefix + 122)

// IIDs (Interface IDs)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDUISELECTIONOBSERVER,	kFormFieldUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDUIWIDGETSOBSERVER,		kFormFieldUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGFORMATTRIBUTES,			kFormFieldUIPrefix + 3)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPUSHBUTTONPREFS,				kFormFieldUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHECKBOXPREFS,					kFormFieldUIPrefix + 7) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_IRADIOBUTTONPREFS,				kFormFieldUIPrefix + 8) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFIELDPREFS,				kFormFieldUIPrefix + 9) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXPREFS,					kFormFieldUIPrefix + 10) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMBOBOXPREFS,					kFormFieldUIPrefix + 11) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ISIGNATUREFIELDPREFS,			kFormFieldUIPrefix + 12) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDPREFS,				kFormFieldUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMTHUMBNAIL,				kFormFieldUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDUIFACTORY,			kFormFieldUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWHIDEBUTTONSOBSERVER, kFormFieldUIPrefix + 16)


// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kFormFieldUIComponentImpl,				kFormFieldUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kFormFieldUITrackerRegisterImpl,		kFormFieldUIPrefix + 2)

DECLARE_PMID(kImplementationIDSpace, kAppearancePlaceBehaviorUIImpl,	kFormFieldUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kToggleStatesButtonObserverImpl,	kFormFieldUIPrefix + 6)

DECLARE_PMID(kImplementationIDSpace, kPushButtonToolImpl, 			kFormFieldUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPushButtonTrackerImpl, 		kFormFieldUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCheckBoxToolImpl, 			kFormFieldUIPrefix + 12) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kCheckBoxTrackerImpl, 			kFormFieldUIPrefix + 13) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kRadioButtonToolImpl, 			kFormFieldUIPrefix + 14) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kRadioButtonTrackerImpl, 		kFormFieldUIPrefix + 15) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldToolImpl, 			kFormFieldUIPrefix + 16) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldTrackerImpl, 		kFormFieldUIPrefix + 17) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxToolImpl, 				kFormFieldUIPrefix + 18) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxTrackerImpl, 			kFormFieldUIPrefix + 19) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxToolImpl, 			kFormFieldUIPrefix + 20) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxTrackerImpl, 			kFormFieldUIPrefix + 21) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldToolImpl, 		kFormFieldUIPrefix + 22) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldTrackerImpl,	kFormFieldUIPrefix + 23) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kImplementationIDSpace, kChoiceListObserverImpl, 		kFormFieldUIPrefix + 24) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kChoiceListControlDataImpl, 	kFormFieldUIPrefix + 25) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kChoiceListBoxListZOrderDDTargetImpl, kFormFieldUIPrefix + 26) // Reserved for possible future implementation, do not use

DECLARE_PMID(kImplementationIDSpace, kTextAttributesTargetServerImpl,kFormFieldUIPrefix + 31)

 

	//Appearance Panel
DECLARE_PMID(kImplementationIDSpace, kStateListBoxControllerImpl,		kFormFieldUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelObserverImpl,		kFormFieldUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kNewStateButtonObserverImpl,		kFormFieldUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kDeleteStateButtonObserverImpl,	kFormFieldUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelMenuComponentImpl, kFormFieldUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelEyeballObserverImpl, kFormFieldUIPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kAppearancePanelNameObserverImpl,	kFormFieldUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelProxyObserverImpl, kFormFieldUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kStateListElementViewImpl,			kFormFieldUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kStateListElementDataImpl,			kFormFieldUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kStateThumbnailViewImpl,			kFormFieldUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kBehaviorsTreeViewEHImpl,			kFormFieldUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPlaceIntoStateButtonObserverImpl,	kFormFieldUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDeleteStateContentButtonObserverImpl,	kFormFieldUIPrefix + 51)
// gap
DECLARE_PMID(kImplementationIDSpace, kStateDuplicateDragDropTargetImpl, kFormFieldUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAPProxyViewDragDropSourceImpl, kFormFieldUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kGoToURLComboBoxObserverImpl, kFormFieldUIPrefix + 56)
// gap
DECLARE_PMID(kImplementationIDSpace, kStateProxyDEHandlerImpl, kFormFieldUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kStateDeleteDragDropTargetImpl, kFormFieldUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kStateEyeDragDropSourceImpl, kFormFieldUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kStateEyeDragDropTargetImpl, kFormFieldUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kStateEyeDEHandlerImpl, kFormFieldUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kStateEyeDragDropSourceEHImpl, kFormFieldUIPrefix + 66)
// gap
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelResizeRuleImpl, kFormFieldUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kAppearancePalettePanelImpl, kFormFieldUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kStateElementResizeRuleImpl, kFormFieldUIPrefix + 74)
// gap
DECLARE_PMID(kImplementationIDSpace, kStateCellWidgetFactoryImpl, kFormFieldUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kStateListBoxControlDataImpl, kFormFieldUIPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kStateCellWidgetControllerImpl, kFormFieldUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kStateWidgetListBoxHelperImpl, kFormFieldUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelElementObserverImpl, kFormFieldUIPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelDetailControllerImpl,kFormFieldUIPrefix + 83)


// list box drag and drop (reordering)
DECLARE_PMID(kImplementationIDSpace, kListBoxListZOrderDDSourceImpl, kFormFieldUIPrefix + 90) //gap
DECLARE_PMID(kImplementationIDSpace, kListBoxDEHandlerImpl, kFormFieldUIPrefix + 92)

//Appearance Panel Prefs Dialog (thumbnail size)
DECLARE_PMID(kImplementationIDSpace, kAppearancePanelPrefsDialogControllerImpl,kFormFieldUIPrefix + 94)

//Tab/Calculation order dialogs.

DECLARE_PMID(kImplementationIDSpace, kTabOrderDialogControllerImpl, 		kFormFieldUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kOrderListObserverImpl, 				kFormFieldUIPrefix + 102)

DECLARE_PMID(kImplementationIDSpace, kOrderListControlDataImpl, 			kFormFieldUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kOrderListBoxListZOrderDDTargetImpl,	kFormFieldUIPrefix + 104)

DECLARE_PMID(kImplementationIDSpace, kTextFieldUIObserverImpl, 				kFormFieldUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kListBoxUIObserverImpl, 				kFormFieldUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kStateListBoxObserverImpl, 			kFormFieldUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kConvertToButtonObserverImpl, 			kFormFieldUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kConvertToObjectObserverImpl, 			kFormFieldUIPrefix + 109)

DECLARE_PMID(kImplementationIDSpace, kComboBoxUIFactoryImpl,		kFormFieldUIPrefix + 150) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kCheckBoxUIFactoryImpl,		kFormFieldUIPrefix + 151) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxUIFactoryImpl,			kFormFieldUIPrefix + 152) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kPushButtonUIFactoryImpl,		kFormFieldUIPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kRadioButtonUIFactoryImpl,		kFormFieldUIPrefix + 154) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldUIFactoryImpl,	kFormFieldUIPrefix + 155) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldUIFactoryImpl, 		kFormFieldUIPrefix + 156) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kGenericFieldUIFactoryImpl,	kFormFieldUIPrefix + 157)
//gap 
DECLARE_PMID(kImplementationIDSpace, kFormOptionsDialogCreatorImpl,	kFormFieldUIPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kGeneralPanelCreatorImpl,	kFormFieldUIPrefix + 160)

DECLARE_PMID(kImplementationIDSpace, kFormFieldLabelDrawerImpl,	kFormFieldUIPrefix + 161)

DECLARE_PMID(kImplementationIDSpace, kMSOPanelViewImpl, kFormFieldUIPrefix + 162) 
DECLARE_PMID(kImplementationIDSpace, kMSOPanelMenuActionImpl, kFormFieldUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewObserverImpl, kFormFieldUIPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewAdapterImpl, kFormFieldUIPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewWidgetMgrImpl, kFormFieldUIPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelObserverImpl, kFormFieldUIPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateThumbnailViewImpl, kFormFieldUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateNameILEObserverImpl, kFormFieldUIPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateNameILEEditingAttributesImpl, kFormFieldUIPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateNameTextValidationImpl, kFormFieldUIPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kMSOSelectionIconEHImpl, kFormFieldUIPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelPointyHandCursorProviderImpl, kFormFieldUIPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kNewMSOStateButtonObserverImpl, kFormFieldUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kDeleteMSOStateButtonObserverImpl, kFormFieldUIPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelDetailControllerImpl, kFormFieldUIPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewControllerImpl, kFormFieldUIPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewEHImpl, kFormFieldUIPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTipsImpl, kFormFieldUIPrefix + 179)
//gap
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateDNDHandlerImpl, kFormFieldUIPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelStateDNDSourceImpl, kFormFieldUIPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kDeleteMSOStateButtonDNDTargetImpl, kFormFieldUIPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kNewMSOStateButtonDNDTargetImpl, kFormFieldUIPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewDNDTargetImpl, kFormFieldUIPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kMSOPanelTreeViewNodeEHImpl, kFormFieldUIPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kBhvrTargetChoicesTipsImpl, kFormFieldUIPrefix + 187)
//gap
DECLARE_PMID(kImplementationIDSpace, kMSOStateDDLElementViewImpl, kFormFieldUIPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kMSOStateOwnerDrawDDItemImpl, kFormFieldUIPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kPasteIntoMSOStateButtonObserverImpl,	kFormFieldUIPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kAddToMSOStateButtonObserverImpl,	kFormFieldUIPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kPDFOptionsDetailControllerImpl,	kFormFieldUIPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kListItemsTreeViewAdapterImpl,		kFormFieldUIPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kListItemsTreeViewMgrImpl,			kFormFieldUIPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kRemoveListOptionButtonObserverImpl,			kFormFieldUIPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kListItemsTreeObserverImpl,		kFormFieldUIPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kAddListOptionButtonObserverImpl,	kFormFieldUIPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kListItemsTreeEHImpl,				kFormFieldUIPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kListItemsDDSourceImpl,			kFormFieldUIPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kListItemsTreeViewDDTargetImpl,	kFormFieldUIPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kListItemsDDHandlerImpl,			kFormFieldUIPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kFontSizeTextValidationImpl,		kFormFieldUIPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kFontSizeTextValueImpl,			kFormFieldUIPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kListItemsNodeEventHandlerImpl,	kFormFieldUIPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kListItemsEditBoxEHImpl, kFormFieldUIPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kFormsFontComboboxViewImpl, kFormFieldUIPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kFormsFontObserverImpl, kFormFieldUIPrefix + 209)



// Widget IDs
	//Properties Dialog(s)
DECLARE_PMID(kWidgetIDSpace, kFormFieldUIDialogWID,		kFormFieldUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kNameEditWID,				kFormFieldUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kVisibleCheckBoxWID,		kFormFieldUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kNameStaticWID,			kFormFieldUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kIconSuiteWID,				kFormFieldUIPrefix + 5)

DECLARE_PMID(kWidgetIDSpace, kFormFieldUIPanelWID, 		kFormFieldUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kFormTypePopupWID, 		kFormFieldUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPDFVisiblityStaticWID, 	kFormFieldUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPDFVisiblityPopupWID, 	kFormFieldUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kReadyOnlyWID, 			kFormFieldUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kExportWID, 				kFormFieldUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kRequiredForExportWID, 	kFormFieldUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDescriptionStaticWID, 	kFormFieldUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kDescriptionEditWID, 		kFormFieldUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kExportNameStaticWID, 		kFormFieldUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kExportNameEditWID, 		kFormFieldUIPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kFormFieldSettingsHolderWID, 	kFormFieldUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kToggleStatesButtonWidgetID, 	kFormFieldUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kToggleStatesTextWidgetID, 	kFormFieldUIPrefix + 19)


DECLARE_PMID(kWidgetIDSpace, kFieldOptionsGroupWID,			kFormFieldUIPrefix + 35) //gap
DECLARE_PMID(kWidgetIDSpace, kFieldOptionsGroupStaticWID,	kFormFieldUIPrefix + 36)

DECLARE_PMID(kWidgetIDSpace, kWidthStaticWID, 			kFormFieldUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kWidthEditWID, 			kFormFieldUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kHeightStaticWID, 			kFormFieldUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kHeightEditWID, 			kFormFieldUIPrefix + 40)

DECLARE_PMID(kWidgetIDSpace, kPushButtonToolWidgetId, 	kFormFieldUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kCheckBoxToolWidgetId, 	kFormFieldUIPrefix + 42) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kRadioButtonToolWidgetId, 	kFormFieldUIPrefix + 43) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kTextFieldToolWidgetId, 	kFormFieldUIPrefix + 44) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxToolWidgetId, 		kFormFieldUIPrefix + 45) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kComboBoxToolWidgetId, 	kFormFieldUIPrefix + 46) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kSignatureFieldToolWidgetId, kFormFieldUIPrefix + 47) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kWidgetIDSpace, kFormTypeStaticWID, 			kFormFieldUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kFormTypeStaticSettingWID, 	kFormFieldUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kFormShadingTypeStaticWID, 	kFormFieldUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kFormShadingStylePopupWID, 	kFormFieldUIPrefix + 51)

DECLARE_PMID(kWidgetIDSpace, kCommonSettingsGroupWID,		kFormFieldUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kCommonSettingsGroupStaticWID,	kFormFieldUIPrefix + 53)

//Check Box Options

DECLARE_PMID(kWidgetIDSpace, kCheckBoxPanelWID,				kFormFieldUIPrefix + 54) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kCheckExportValueEditWID,		kFormFieldUIPrefix + 55) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kCheckExportValueStaticWID,	kFormFieldUIPrefix + 56) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kDefaultIsCheckedWID,			kFormFieldUIPrefix + 57) 		// Reserved for possible future implementation, do not use

//Radio Button Options

DECLARE_PMID(kWidgetIDSpace, kRadioButtonPanelWID,			kFormFieldUIPrefix + 58) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kDefaultIsSelectedWID,			kFormFieldUIPrefix + 59) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kRadioExportValueEditWID,		kFormFieldUIPrefix + 60) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kRadioExportValueStaticWID,	kFormFieldUIPrefix + 61) 		// Reserved for possible future implementation, do not use

//Text Field Options
DECLARE_PMID(kWidgetIDSpace, kTextFieldPanelWID,				kFormFieldUIPrefix + 62) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kDefaultTextStaticWID,				kFormFieldUIPrefix + 63) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kDefaultTextEditWID,				kFormFieldUIPrefix + 64) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kMultilineWID,						kFormFieldUIPrefix + 65) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kScrollWID,						kFormFieldUIPrefix + 66) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kCharLimitWID,						kFormFieldUIPrefix + 67) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kCharLimitEditWID,					kFormFieldUIPrefix + 68) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kCharLimitStaticWID,				kFormFieldUIPrefix + 69) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kPasswordWID,						kFormFieldUIPrefix + 70) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kForFileSelectionWID,				kFormFieldUIPrefix + 71) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kTextFieldSpellCheckWID,			kFormFieldUIPrefix + 72) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kTextFieldAlignStaticWID,			kFormFieldUIPrefix + 73) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kTextFieldAlignPopupWID,			kFormFieldUIPrefix + 74) 		// Reserved for possible future implementation, do not use


//List Box/Combo Box Options
DECLARE_PMID(kWidgetIDSpace, kListBoxPanelWID,				kFormFieldUIPrefix + 76) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxItemStaticWID,			kFormFieldUIPrefix + 77) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxItemEditWID,			kFormFieldUIPrefix + 78) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxExportValueStaticWID,	kFormFieldUIPrefix + 79) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxExportValueEditWID,	kFormFieldUIPrefix + 80) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxListWidgetID,			kFormFieldUIPrefix + 81) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxAddWidgetID,			kFormFieldUIPrefix + 82) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxDeleteWidgetID,		kFormFieldUIPrefix + 83) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxChangeWidgetID,		kFormFieldUIPrefix + 84) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxSortItemsWID,			kFormFieldUIPrefix + 85) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxMultipleSelectionWID,	kFormFieldUIPrefix + 86) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxEditableWID,			kFormFieldUIPrefix + 87) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxSpellCheckWID,			kFormFieldUIPrefix + 88) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kListBoxSelectedIsDefaultStaticWID, kFormFieldUIPrefix + 89) 	// Reserved for possible future implementation, do not use

DECLARE_PMID(kWidgetIDSpace, kFormTextColorButtonWID,		kFormFieldUIPrefix + 90) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kWidgetIDSpace, kFormTextColorButton2WID,		kFormFieldUIPrefix + 91) 		// Reserved for possible future implementation, do not use

	//Appearance Panel
DECLARE_PMID(kWidgetIDSpace, kActionOptionsGroupWidgetId,		kFormFieldUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kActionsDataHolderWidgetID,		kFormFieldUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kEventStaticWID,					kFormFieldUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kButtonEventChoicesWidgetID,		kFormFieldUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kActionTitleWidgetId,				kFormFieldUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kActionChoicesWidgetID,			kFormFieldUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kStateListBoxesContainerWidgetID,	kFormFieldUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kFittedStateListBoxesContainer,	kFormFieldUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kStateDeleteButtonWidgetID,		kFormFieldUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kStateNewButtonWidgetID,			kFormFieldUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kStateListSmallWidgetID,			kFormFieldUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kStateListMediumWidgetID,			kFormFieldUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kStateListLargeWidgetID,			kFormFieldUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kStateListExtraLargeWidgetID,		kFormFieldUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kStateStatusWidgetID,				kFormFieldUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kStateListElementEyeballWidgetID,	kFormFieldUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kStateListElementNameWidgetID,		kFormFieldUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kStateListElementThumbnailWidgetID,kFormFieldUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kStatePlaceIntoButtonWidgetID,		kFormFieldUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kStateDeleteContentButtonWidgetID,	kFormFieldUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kStateControlStripWidgetID,		kFormFieldUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kAppearanceParentWidgetId,			kFormFieldUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kStateListParentWidgetId,			kFormFieldUIPrefix + 114)

DECLARE_PMID(kWidgetIDSpace, kStyleStaticWID, 					kFormFieldUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kStylePopupWID, 					kFormFieldUIPrefix + 116)

DECLARE_PMID(kWidgetIDSpace, kCreateFormUIDialogWID,			kFormFieldUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kCreateFormGroupWID,				kFormFieldUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kCreateFormGroupStaticWID,			kFormFieldUIPrefix + 119)

	//Form Text Color Dialog...
DECLARE_PMID(kWidgetIDSpace, kFormTextColorDialogWID,			kFormFieldUIPrefix + 120)

	//Tab/Calc Order Dialogs...
DECLARE_PMID(kWidgetIDSpace, kListBoxMoveUpWidgetID,			kFormFieldUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kListBoxMoveDownWidgetID,			kFormFieldUIPrefix + 126)


	//Appearance Panel Prefs Dialog
DECLARE_PMID(kWidgetIDSpace, kAppearancePanelPrefsDialogWID,	kFormFieldUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kSizeGroupWID,						kFormFieldUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kSizeGroupLabelWID,				kFormFieldUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kSizeRadioButtonClusterWID,		kFormFieldUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kSmallSizeRadioButtonWID,			kFormFieldUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kMediumSizeRadioButtonWID,			kFormFieldUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kLargeSizeRadioButtonWID,			kFormFieldUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kExtraLargeSizeRadioButtonWID,		kFormFieldUIPrefix + 137)

DECLARE_PMID(kWidgetIDSpace, kMediumThumbnailPictWID,			kFormFieldUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kLargeThumbnailPictWID,			kFormFieldUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kExtraLargeThumbnailPictWID,		kFormFieldUIPrefix + 140)

DECLARE_PMID(kWidgetIDSpace, kFormOptionsWID,					kFormFieldUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kFormOptionsGroupWidgetID,				kFormFieldUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kFormOptionsLabelWidgetID,				kFormFieldUIPrefix + 143)

// New appearance widgets
DECLARE_PMID(kWidgetIDSpace, kActionsListStaticWID,				kFormFieldUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kActionsTreeBorderWidgetID,		kFormFieldUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kActionsTreeWidgetID,				kFormFieldUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kEmptyActionNodeWidgetId,			kFormFieldUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kActionNodeWidgetId,				kFormFieldUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kActionOnOffButtonWidgetID,		kFormFieldUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kShowFieldButtonWidgetID,			kFormFieldUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kHideFieldButtonWidgetID,			kFormFieldUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kIgnoreFieldButtonWidgetID,		kFormFieldUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kConvertToButtonButtonWidgetID,	kFormFieldUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kConvertToObjectButtonWidgetID,	kFormFieldUIPrefix + 154)

// States panel
DECLARE_PMID(kWidgetIDSpace, kMSOPanelWidgetID,					kFormFieldUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kMSONameStaticWidgetID,			kFormFieldUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kMSONameEditWidgetID,				kFormFieldUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelControlStripWidgetID,		kFormFieldUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelStatusAreaWidgetID,		kFormFieldUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kNewMSOStateButtonWidgetID,		kFormFieldUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kDeleteMSOStateButtonWidgetID,		kFormFieldUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kMSOTreeBorderPanelWidgetID,		kFormFieldUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelTreeWidgetID,				kFormFieldUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelTreeViewNodeWidgetID,		kFormFieldUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelStateThumbnailWidgetID,	kFormFieldUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelStateAnimatedIconWidgetID,kFormFieldUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kMSOPanelNameStripWidgetID,		kFormFieldUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kMSOMixedStaticWidgetID,			kFormFieldUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kMSOStateSelectionIconWidgetID,		kFormFieldUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kMSOSelectionIconWidgetID,			kFormFieldUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kHiddenUntilCheckBoxWidgetID,		kFormFieldUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kPasteIntoMSOStateButtonWidgetID,	kFormFieldUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kAddToMSOStateButtonWidgetID,		kFormFieldUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kNoActionsAddedTextWidgetID,		kFormFieldUIPrefix + 174)
//gap
DECLARE_PMID(kWidgetIDSpace, kButtonPDFOptionsDialogWID,		kFormFieldUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kButtonPDFDescriptionWID,			kFormFieldUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kButtonPDFPrintableCheckBoxWID,	kFormFieldUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kVisibleRadioButtonWID,			kFormFieldUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kHiddenRadioButtonWID,				kFormFieldUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kShowPreviewButtonWidgetID,		kFormFieldUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kFormFieldChoicesWidgetID,			kFormFieldUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kFormsListStaticWID,				kFormFieldUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsGroupWidgetID,			kFormFieldUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsExpanderWidgetID,		kFormFieldUIPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kPDFOPtionsLabelWidgetID,			kFormFieldUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsSubPanelGroupWidgetID,	kFormFieldUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kReadOnlyCheckBoxWidgetID,			kFormFieldUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kRequiredCheckBoxWidgetID,			kFormFieldUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kSelectedByDefaultCheckBoxWidgetID,	kFormFieldUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kMultilineCheckBoxWidgetID,		kFormFieldUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kPasswordCheckBoxWidgetID,			kFormFieldUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kScrollableCheckBoxWidgetID,		kFormFieldUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kListItemsLabelWidgetID,			kFormFieldUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kAddListOptionButtonWidgetID,		kFormFieldUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kRemoveListOptionButtonWidgetID,	kFormFieldUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kListItemsBorderWidgetID,			kFormFieldUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kListItemsWidgetID,				kFormFieldUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kListItemsNodeWidgetId,			kFormFieldUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kListItemTextNodeWID,				kFormFieldUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kMultipleSelectionCheckBoxWidgetID,	kFormFieldUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kItemOptionWidgetId,				kFormFieldUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kFontSizeEditBoxWidgetID,			kFormFieldUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kFontSizeStaticWID,				kFormFieldUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kSortItemsCheckBoxWidgetID,		kFormFieldUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionLabelWID,			kFormFieldUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kMERTLOptionCheckBoxWidgetID,		kFormFieldUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kExportValueStaticWID,				kFormFieldUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kExportValueEditWidgetID,			kFormFieldUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kFontSizePanelWID,					kFormFieldUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kListOptionsPanelWidgetID,			kFormFieldUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kPDFOptionsPanelWID,				kFormFieldUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kFormFontFamilyWidgetID,			kFormFieldUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kFormFontStyleWidgetID,			kFormFieldUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kFormFontsPanelWidgetID,			kFormFieldUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kFormFontSizeSubPanelWidgetID,		kFormFieldUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kFontPropertiesPanelWID,			kFormFieldUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kFontStaticWID,					kFormFieldUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kFontSizeNudgeWidgetID,			kFormFieldUIPrefix + 223)


	//Some other dialogs...
DECLARE_PMID(kClassIDSpace, kStatePropertiesDialogWID, 			kFormFieldUIPrefix + 160)
DECLARE_PMID(kClassIDSpace, kStatePopupLabelWID, 				kFormFieldUIPrefix + 161)
DECLARE_PMID(kClassIDSpace, kStatePopupWID, 					kFormFieldUIPrefix + 162)
DECLARE_PMID(kClassIDSpace, kStateEnabledWID, 					kFormFieldUIPrefix + 163)

// Action IDs

DECLARE_PMID(kActionIDSpace, kFormFieldPropertiesActionID, 	kFormFieldUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kCreateButtonActionID, 		kFormFieldUIPrefix + 2)

DECLARE_PMID(kActionIDSpace, kPushButtonToolActionID, 	kFormFieldUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCheckBoxToolActionID, 	kFormFieldUIPrefix + 4) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kActionIDSpace, kRadioButtonToolActionID, 	kFormFieldUIPrefix + 5) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kActionIDSpace, kTextFieldToolActionID, 	kFormFieldUIPrefix + 6) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kActionIDSpace, kListBoxToolActionID, 		kFormFieldUIPrefix + 7) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kActionIDSpace, kComboBoxToolActionID, 	kFormFieldUIPrefix + 8) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kActionIDSpace, kSignatureFieldToolActionID, kFormFieldUIPrefix + 9) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kActionIDSpace, kFormFramePrefsActionID,		kFormFieldUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kStatePropertiesActionID,		kFormFieldUIPrefix + 12) 

DECLARE_PMID(kActionIDSpace, kSetTabOrderActionID,			kFormFieldUIPrefix + 13) 
DECLARE_PMID(kActionIDSpace, kSetCalculationOrderActionID,	kFormFieldUIPrefix + 14)
 
DECLARE_PMID(kActionIDSpace, kFormFieldProperties2ActionID, kFormFieldUIPrefix + 15)

	//Appearance Panel

DECLARE_PMID(kActionIDSpace, kAppearancePanelActionID, 		kFormFieldUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kAppearancePalettePrefsActionID, kFormFieldUIPrefix + 21)

DECLARE_PMID(kActionIDSpace, kPlaceIntoStateActionID,		kFormFieldUIPrefix + 94)
DECLARE_PMID(kActionIDSpace, kDeleteStateContentActionID, 	kFormFieldUIPrefix + 95)
DECLARE_PMID(kActionIDSpace, kNewStateActionID,				kFormFieldUIPrefix + 96)
DECLARE_PMID(kActionIDSpace, kDeleteStateActionID, 			kFormFieldUIPrefix + 97)


//These are not present in any menu right now....
DECLARE_PMID(kActionIDSpace, kAboutFormFieldsActionID, 		kFormFieldUIPrefix + 98)


DECLARE_PMID(kActionIDSpace, kFormFieldUISepActionID, 	kFormFieldUIPrefix + 99)
DECLARE_PMID(kActionIDSpace, kFormFieldUISep2ActionID, 	kFormFieldUIPrefix + 100)
DECLARE_PMID(kActionIDSpace, kFormFieldUISep3ActionID,	kFormFieldUIPrefix + 101)
DECLARE_PMID(kActionIDSpace, kFormFieldUISep4ActionID,	kFormFieldUIPrefix + 102)

//gap
DECLARE_PMID(kActionIDSpace, kGoToFirstPageBehaviorActionID,	kFormFieldUIPrefix + 122)
DECLARE_PMID(kActionIDSpace, kGoToAnchorBehaviorActionID,		kFormFieldUIPrefix + 123)
DECLARE_PMID(kActionIDSpace, kGoToLastPageBehaviorActionID, 	kFormFieldUIPrefix + 124)
DECLARE_PMID(kActionIDSpace, kGoToNextPageBehaviorActionID, 	kFormFieldUIPrefix + 125)
DECLARE_PMID(kActionIDSpace, kGoToNextViewBehaviorActionID, 	kFormFieldUIPrefix + 126)
DECLARE_PMID(kActionIDSpace, kGoToPreviousPageBehaviorActionID, kFormFieldUIPrefix + 127)
DECLARE_PMID(kActionIDSpace, kGoToPreviousViewBehaviorActionID, kFormFieldUIPrefix + 128)
DECLARE_PMID(kActionIDSpace, kGoToURLBehaviorActionID,			kFormFieldUIPrefix + 129)
DECLARE_PMID(kActionIDSpace, kMovieBehaviorActionID,			kFormFieldUIPrefix + 130)
DECLARE_PMID(kActionIDSpace, kOpenFileBehaviorActionID,			kFormFieldUIPrefix + 131)
DECLARE_PMID(kActionIDSpace, kShowHideBehaviorActionID,			kFormFieldUIPrefix + 132)
DECLARE_PMID(kActionIDSpace, kSoundBehaviorActionID,			kFormFieldUIPrefix + 133)
DECLARE_PMID(kActionIDSpace, kViewZoomBehaviorActionID,			kFormFieldUIPrefix + 134)
DECLARE_PMID(kActionIDSpace, kGoToPageBehaviorActionID,			kFormFieldUIPrefix + 135)
DECLARE_PMID(kActionIDSpace, kAnimationBehaviorActionID,		kFormFieldUIPrefix + 136)

DECLARE_PMID(kActionIDSpace, kOpenButtonLibraryActionID,					kFormFieldUIPrefix + 139)
DECLARE_PMID(kActionIDSpace, kMakeVisibleInPDFActionID,						kFormFieldUIPrefix + 140)
DECLARE_PMID(kActionIDSpace, kMakeVisibleButDoesntPrintInPDFActionID,		kFormFieldUIPrefix + 141)
DECLARE_PMID(kActionIDSpace, kMakeHiddenInPDFActionID,						kFormFieldUIPrefix + 142)
DECLARE_PMID(kActionIDSpace, kMakeHiddenButPrintableInPDFActionID,			kFormFieldUIPrefix + 143)

DECLARE_PMID(kActionIDSpace, kMSOPanelActionID,					kFormFieldUIPrefix + 144)
DECLARE_PMID(kActionIDSpace, kMSOPanelSep1ActionID,				kFormFieldUIPrefix + 145)
DECLARE_PMID(kActionIDSpace, kMSOPanelSep2ActionID,				kFormFieldUIPrefix + 146)
DECLARE_PMID(kActionIDSpace, kMSOPanelSep3ActionID,				kFormFieldUIPrefix + 147)
DECLARE_PMID(kActionIDSpace, kMSOPanelSep4ActionID,				kFormFieldUIPrefix + 148)
DECLARE_PMID(kActionIDSpace, kNewMSOStateActionID,				kFormFieldUIPrefix + 149)
DECLARE_PMID(kActionIDSpace, kResetAllMSOsActionID,				kFormFieldUIPrefix + 150)
DECLARE_PMID(kActionIDSpace, kDeleteMSOStateActionID,			kFormFieldUIPrefix + 151)
DECLARE_PMID(kActionIDSpace, kPasteIntoMSOStateActionID,		kFormFieldUIPrefix + 152)
DECLARE_PMID(kActionIDSpace, kReleaseMSOStateActionID,			kFormFieldUIPrefix + 153)
DECLARE_PMID(kActionIDSpace, kReleaseAllMSOStatesActionID,		kFormFieldUIPrefix + 154)
DECLARE_PMID(kActionIDSpace, kMSOPanelOptionsActionID,			kFormFieldUIPrefix + 155)
DECLARE_PMID(kActionIDSpace, kReleaseMSOStateContextActionID,	kFormFieldUIPrefix + 156)
DECLARE_PMID(kActionIDSpace, kDeleteMSOStateContextActionID,	kFormFieldUIPrefix + 157)
DECLARE_PMID(kActionIDSpace, kSwitchToMSOStateBehaviorActionID,	kFormFieldUIPrefix + 158)
DECLARE_PMID(kActionIDSpace, kSwitchToNextMSOStateBehaviorActionID,	kFormFieldUIPrefix + 159)
DECLARE_PMID(kActionIDSpace, kSwitchToPrevMSOStateBehaviorActionID,	kFormFieldUIPrefix + 160)
DECLARE_PMID(kActionIDSpace, kSWFOnlySeparatorActionID,	kFormFieldUIPrefix + 161)
DECLARE_PMID(kActionIDSpace, kPDFOnlySeparatorActionID,	kFormFieldUIPrefix + 162)
DECLARE_PMID(kActionIDSpace, kResetAllButtonsActionID,	kFormFieldUIPrefix + 163)
DECLARE_PMID(kActionIDSpace, kButtonPDFOptionsActionID,	kFormFieldUIPrefix + 164)
DECLARE_PMID(kActionIDSpace, kPasteIntoMSOStateContextActionID,	kFormFieldUIPrefix + 165)
DECLARE_PMID(kActionIDSpace, kHiddenUntilTriggeredActionID,	kFormFieldUIPrefix + 166)
DECLARE_PMID(kActionIDSpace, kMSOPanelSep5ActionID,				kFormFieldUIPrefix + 167)
DECLARE_PMID(kActionIDSpace, kAddToMSOStateActionID,			kFormFieldUIPrefix + 168)
DECLARE_PMID(kActionIDSpace, kResetFormBehaviorActionID,			kFormFieldUIPrefix + 169)
DECLARE_PMID(kActionIDSpace, kSubmitFormBehaviorActionID,			kFormFieldUIPrefix + 170)
DECLARE_PMID(kActionIDSpace, kPrintFormBehaviorActionID,			kFormFieldUIPrefix + 171)
DECLARE_PMID(kActionIDSpace, kConvertToObjectToolActionID, kFormFieldUIPrefix + 172)

// Service ID
DECLARE_PMID(kServiceIDSpace, kFormOptionsDialogService, 	kFormFieldUIPrefix + 1)

// Message ID
DECLARE_PMID(kMessageIDSpace, kReleaseMSOStateAlertMsgID, 		kFormFieldUIPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kReleaseAllMSOStateAlertMsgID,	kFormFieldUIPrefix + 2)

// ----- Tree Node ID types -----
#define kMSOStateNodeID		kFormFieldUIPrefix + 1

#endif // __FormFieldUIID__




