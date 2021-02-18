//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/DV_WidgetID.h $
//  
//  Owner: Dave Burnard
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Contains IDs used by widgets
//  
//========================================================================================

#ifndef __DV_WidgetID__
#define __DV_WidgetID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// <Start IDC>
#define kDV_WidgetPrefix	 RezLong(0x0d00)

// PlugInIDs
DECLARE_PMID(kPlugInIDSpace, kDV_WidgetsPluginID, kDV_WidgetPrefix + 1)
#define kDV_WidgetsPluginName	"DV_Widgets"

// <Class ID>
//========================================================================================
// <Message ID>
// ----- Message IDs -----
// Messages sent by various Data Objects
// -- these are ClassIDs but have no classes!
// -- they are only used for sending messages
//========================================================================================


// <Interface ID>
//========================================================================================
// ----- Interface IDs -----
//========================================================================================

DECLARE_PMID(kInterfaceIDSpace, IID_IDV_UI_NODEREF,								kDV_WidgetPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDV_OS_WINDOWREF,							kDV_WidgetPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDV_OS_VIEWREF,								kDV_WidgetPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVOWNERDRAWMENU,							kDV_WidgetPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVFONTMENUDRAWOBJECT,						kDV_WidgetPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IISCOMPUTEDWIDTHINVALID,					kDV_WidgetPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNITEMSCONTROLDATA,					kDV_WidgetPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRECHILDEVENTHANDLER,						kDV_WidgetPrefix + 8 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGVALIDATIONFAILED,					kDV_WidgetPrefix + 9 )
DECLARE_PMID(kInterfaceIDSpace, IID_PERFORMKEYBOARDACCELERATOR,					kDV_WidgetPrefix + 10 )
DECLARE_PMID(kInterfaceIDSpace, IID_SAVEDCANCELNAME,							kDV_WidgetPrefix + 11 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITOGGLEATTRIBUTES,							kDV_WidgetPrefix + 12 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTCLOSEONCANCEL,						kDV_WidgetPrefix + 13 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRECESSEDSPLITBAR,							kDV_WidgetPrefix + 14 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLETEXTCONTROLDATA,						kDV_WidgetPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IERASEBEFOREICONDRAW,						kDV_WidgetPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONTROLDATA,							kDV_WidgetPrefix + 17)
//gap

// <Implementation ID>
//========================================================================================
// ----- Implementation IDs -----
//========================================================================================

DECLARE_PMID(kImplementationIDSpace, kDV_UI_NodeRefImpl,						kDV_WidgetPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDV_WidgetParentImpl,						kDV_WidgetPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelControlDataImpl,					kDV_WidgetPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDV_DialogPanelControlDataImpl,			kDV_WidgetPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPerformKeyboardAcceleratorImpl,			kDV_WidgetPrefix + 7)

DECLARE_PMID(kImplementationIDSpace, kDV_WindowImpl,							kDV_WidgetPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kDV_ModalDialogWindowImpl,					kDV_WidgetPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDV_DialogImpl,							kDV_WidgetPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kDV_PalettePanelViewImpl,					kDV_WidgetPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDV_ModelessDialogWindowImpl,				kDV_WidgetPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kDV_ModelessDialogImpl,					kDV_WidgetPrefix + 15)
//gap


DECLARE_PMID(kImplementationIDSpace, kDV_HostedWidgetEHImpl,					kDV_WidgetPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kDV_WindowEHImpl,							kDV_WidgetPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kDV_WindowContentEHImpl,					kDV_WidgetPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDV_ControlEventHandlerImpl,				kDV_WidgetPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelEventHandlerImpl,					kDV_WidgetPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kDV_EventHandlerImpl,						kDV_WidgetPrefix + 25)

//gap
DECLARE_PMID(kImplementationIDSpace, kDV_ClusterPanelEHImpl,					kDV_WidgetPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kDV_HostedWidgetViewImpl,		 			kDV_WidgetPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kDV_ControlViewImpl,						kDV_WidgetPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelViewImpl,							kDV_WidgetPrefix + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_DialogViewImpl,						kDV_WidgetPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kDV_ErasablePanelViewImpl,					kDV_WidgetPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelWithHiliteBorderViewImpl,			kDV_WidgetPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelWithInverseHiliteBorderViewImpl,	kDV_WidgetPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDV_ClusterPanelViewImpl,					kDV_WidgetPrefix + 48)

// Widgets
DECLARE_PMID(kImplementationIDSpace, kDV_TextControlDataImpl,					kDV_WidgetPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineTextPanoramaImpl,			kDV_WidgetPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDV_GenericButtonViewImpl,					kDV_WidgetPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kDV_ControlTextDataImpl,					kDV_WidgetPrefix + 52)

DECLARE_PMID(kImplementationIDSpace, kDV_TristateControlViewImpl,				kDV_WidgetPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kDV_TristateControlDataImpl,				kDV_WidgetPrefix + 54)

DECLARE_PMID(kImplementationIDSpace, kDV_DropDownListViewImpl,					kDV_WidgetPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kDV_DropDownListControllerImpl,			kDV_WidgetPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kDV_DropDownListControlDataImpl,			kDV_WidgetPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kDV_SearchableDropDownListViewImpl,		kDV_WidgetPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kDV_GroupPanelViewImpl,					kDV_WidgetPrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kDV_CounterControlDataImpl,				kDV_WidgetPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kDV_ScrollBarEHImpl,						kDV_WidgetPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kDV_ScrollBarViewImpl,						kDV_WidgetPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kDV_StaticMultiLineTextViewImpl,			kDV_WidgetPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kDV_StaticMultiLineTextPanoramaImpl,		kDV_WidgetPrefix + 72)

DECLARE_PMID(kImplementationIDSpace, kDV_PanelWithBorderViewImpl,				kDV_WidgetPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kDV_StaticTextLineBreakerImpl,				kDV_WidgetPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kDV_MultiLineTextControlDataImpl,			kDV_WidgetPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kDV_StaticTextLineBreakCounterImpl,		kDV_WidgetPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kDV_GenericPictureTextButtonViewImpl,		kDV_WidgetPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kDV_CreativeCloudButtonViewImpl,kDV_WidgetPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kDV_IconSuiteEventHandlerImpl,				kDV_WidgetPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kDV_SeparatorImpl,							kDV_WidgetPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kDV_RadioButtonViewImpl,					kDV_WidgetPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kDV_RadioButtonControlDataImpl,			kDV_WidgetPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kDV_RadioButtonEHImpl,						kDV_WidgetPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kDV_CheckBoxViewImpl,						kDV_WidgetPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kDV_CheckBoxControlDataImpl,				kDV_WidgetPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kDV_InLineEditViewImpl,					kDV_WidgetPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kDV_ProxyWidgetViewImpl,					kDV_WidgetPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kDV_DropDownListEventHandlerImpl,			kDV_WidgetPrefix + 88)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_RollOverPushButtonTristateDataImpl,	kDV_WidgetPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kDV_IconSuiteViewImpl,						kDV_WidgetPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kDV_IconSuiteButtonTristateControlDataImpl,kDV_WidgetPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kDV_BooleanControlDataImpl,				kDV_WidgetPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kDV_ButtonBooleanControlDataImpl,			kDV_WidgetPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kDV_SplitterWidgetViewImpl,				kDV_WidgetPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kDV_ComboBoxDDLViewImpl,					kDV_WidgetPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kDV_CellPanelControlDataImpl,				kDV_WidgetPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kDV_CellPanelViewImpl,						kDV_WidgetPrefix + 99) 

DECLARE_PMID(kImplementationIDSpace, kDV_TreeWidgetControlViewImpl,				kDV_WidgetPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kDV_TreeScrollerWidgetViewImpl,			kDV_WidgetPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDV_TreeNodeControlViewImpl,				kDV_WidgetPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kDV_ListTreeWidgetControlViewImpl,			kDV_WidgetPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kDV_ListTreeScrollerWidgetViewImpl,		kDV_WidgetPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kDV_ComboBoxDDLOpenCloseHandlerImpl,		kDV_WidgetPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kDV_ListBoxEventHandlerImpl,				kDV_WidgetPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kDV_CheckboxBooleanControlDataImpl,		kDV_WidgetPrefix + 107)

//gap
DECLARE_PMID(kImplementationIDSpace, kDV_ComboBoxDDLControlDataImpl,			kDV_WidgetPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kDV_ComboBoxDDLControllerImpl,				kDV_WidgetPrefix + 112)

DECLARE_PMID(kImplementationIDSpace, kDV_OwnerDrawDropDownListViewImpl,			kDV_WidgetPrefix + 113)
//DECLARE_PMID(kImplementationIDSpace, kDV_ColorListElementViewImpl,				kDV_WidgetPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kDV_OwnerDropDownListControllerImpl,		kDV_WidgetPrefix + 115)

DECLARE_PMID(kImplementationIDSpace, kDV_StrokeFillProxyControlViewImpl,		kDV_WidgetPrefix + 116)

DECLARE_PMID(kImplementationIDSpace, kDV_OwnerDrawStyleGroupDDListControllerImpl,	kDV_WidgetPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kDV_OwnerComboBoxDropDownViewImpl,				kDV_WidgetPrefix + 118)

//gap
//DECLARE_PMID(kImplementationIDSpace, kDV_ColorDropDownListImpl,					kDV_WidgetPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kDV_DocProgressBarControlViewImpl,			kDV_WidgetPrefix + 122)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_KitViewControlViewTabPanelImpl,		kDV_WidgetPrefix + 124)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_PathEndStrokerViewImpl,				kDV_WidgetPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kDV_LineEndDropDownListImpl,				kDV_WidgetPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kDV_StrokeTypeDropDownListImpl,			kDV_WidgetPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kDV_ComboBoxTextControlDataImpl,			kDV_WidgetPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kDV_PopupSliderComboBoxViewImpl,			kDV_WidgetPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kDV_PushButtonEventHandler,				kDV_WidgetPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kDV_TriStateControlEventHandlerImpl,		kDV_WidgetPrefix + 133)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_RollOverIconButtonTristateControlDataImpl,		kDV_WidgetPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kDV_PopupSliderComboboxAttributesImpl,		kDV_WidgetPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kDV_OwnerDrawDDListCtrlDataImpl,			kDV_WidgetPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kButtonBarViewImpl,						kDV_WidgetPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kButtonBarControllerImpl,					kDV_WidgetPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kButtonBarListDataImpl,					kDV_WidgetPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kDV_InLineEditTextControlDataImpl,			kDV_WidgetPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kDV_TreeViewMgrImpl,						kDV_WidgetPrefix + 146)
//gap
DECLARE_PMID(kImplementationIDSpace, kDataNSViewImpl,							kDV_WidgetPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kDV_FontMenuDrawObjectImpl,				kDV_WidgetPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kDV_StrokeTypeListElementViewImpl,			kDV_WidgetPrefix + 150)

DECLARE_PMID(kImplementationIDSpace, kDV_FixedSizePanelViewImpl,				kDV_WidgetPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kPageItemControlViewImpl,					kDV_WidgetPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kDV_OwnerDropDownItemsControlDataImpl,		kDV_WidgetPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kTabsViewImpl,								kDV_WidgetPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kDV_OwnerComboBoxDropDownListControllerImpl,	kDV_WidgetPrefix + 155)
//gap

DECLARE_PMID(kImplementationIDSpace, kNudgeComboboxAttributesImpl,				kDV_WidgetPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kTabsWidgetObserverImpl,					kDV_WidgetPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kTabListControllerImpl,					kDV_WidgetPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kTabListControlDataImpl,					kDV_WidgetPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kAGMDrawnButtonViewImpl,					kDV_WidgetPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kDV_SearchBoxTextControlDataImpl,			kDV_WidgetPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kDV_SearchBoxListControllerImpl,			kDV_WidgetPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kDV_SearchBoxStringListControlDataImpl,	kDV_WidgetPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kSearchMethodDropDownListControllerImpl,	kDV_WidgetPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kRoundedRampViewImpl,						kDV_WidgetPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kRoundedRampSliderControlDataImpl,			kDV_WidgetPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kColorHSBSelectorWidgetViewImpl,			kDV_WidgetPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kHSBSelectorColorControlDataImpl,			kDV_WidgetPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kRGBColorEditorViewImpl,					kDV_WidgetPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kCMYKColorEditorViewImpl,					kDV_WidgetPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kRGBEditorColorControlDataImpl,			kDV_WidgetPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kCMYKEditorColorControlDataImpl,			kDV_WidgetPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kToggleViewImpl,							kDV_WidgetPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kButtonBarItemImpl,						kDV_WidgetPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kButtonBarControlDataImpl,					kDV_WidgetPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kButtonBarAttributesImpl,					kDV_WidgetPrefix + 223)

DECLARE_PMID(kImplementationIDSpace, kDV_PanelWithCustomBorderViewImpl, kDV_WidgetPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kBorderControlAttributesInfoImpl, kDV_WidgetPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kPropsPanelButtonBarViewImpl, kDV_WidgetPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kDV_TreeBasedDropDownListControllerImpl, kDV_WidgetPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kDV_PanelViewCustomColorImpl, kDV_WidgetPrefix + 228)

// <Service ID>
//========================================================================================
// ----- Service IDs -----
//========================================================================================
//DECLARE_PMID(kServiceIDSpace, kAlertHandlerService, kWidgetPrefix + 1)

// <Widget ID>
//========================================================================================
// ----- Widget IDs -----
//========================================================================================
//DECLARE_PMID(kWidgetIDSpace, kResizePresentationWidgetID, kWidgetPrefix + 0)

// <Ignore>
//========================================================================================
// ----- Widget Attribute IDs -----
//========================================================================================

// <Ignore>
//========================================================================================
// ----- Tree Node ID types -----
//========================================================================================

//========================================================================================
// ----- Action/Menu IDs -----
//========================================================================================

//DECLARE_PMID(kActionIDSpace, kCancelActionID, kWidgetPrefix + 1)

#endif // __DV_WidgetID__

