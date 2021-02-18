//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GraphicPanelsID.h $
//  
//  Owner: Michel Hutinel
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

#ifndef __GraphicPanelsID__
#define __GraphicPanelsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGraphicPanelsPrefix	 RezLong(0x2B00)
#define kGraphicPanelsPrefix2	 RezLong(0x21E00)

// PluginID
DECLARE_PMID(kPlugInIDSpace, kGraphicPanelsPluginID, kGraphicPanelsPrefix + 1)
#define kStrokePanelPluginID 				kGraphicPanelsPluginID
#define kAttributesPanelPluginID 			kGraphicPanelsPluginID
#define kCornerShapeDialogPluginID			kGraphicPanelsPluginID

#define kGraphicPanelsPluginName	 		"Graphic Panels"
#define kStrokePanelPluginName				kGraphicPanelsPluginName
#define kAttributesPanelPluginName 			kGraphicPanelsPluginName
#define kCornerShapeDialogPluginName		kGraphicPanelsPluginName


// <Start IDC>
// <Class ID>
// ClassIDs
	// GraphicPanels plugin
//gap
	//	Stroke Panel
DECLARE_PMID(kClassIDSpace, kDV_StrokePanel,			kGraphicPanelsPrefix + 224)

DECLARE_PMID(kClassIDSpace, kStrokePanel, kGraphicPanelsPrefix + 2)
DECLARE_PMID(kClassIDSpace, kStrokeEditorTypePopupBoss, kGraphicPanelsPrefix + 3)
DECLARE_PMID(kClassIDSpace, kStrokePanelMenuComponentBoss, kGraphicPanelsPrefix + 4)
DECLARE_PMID(kClassIDSpace, kStrokePanelWeightComboBoss, kGraphicPanelsPrefix + 5)
DECLARE_PMID(kClassIDSpace, kStrokePanelMiterEditBoss, kGraphicPanelsPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLineCapClusterPanelBoss, kGraphicPanelsPrefix + 7)
DECLARE_PMID(kClassIDSpace, kJoinTypeClusterPanelBoss, kGraphicPanelsPrefix + 8)
//gap
DECLARE_PMID(kClassIDSpace, kStrokeAlignClusterPanelBoss, kGraphicPanelsPrefix + 11)
DECLARE_PMID(kClassIDSpace, kArrowHeadAlignClusterPanelBoss, kGraphicPanelsPrefix + 12)


	// Attributes Panel
DECLARE_PMID(kClassIDSpace, kAttributesPanel,    kGraphicPanelsPrefix + 51)

//gap
DECLARE_PMID(kClassIDSpace, kOverPrintCheckBoxBoss, kGraphicPanelsPrefix + 54)
DECLARE_PMID(kClassIDSpace, kNonPrintCheckBoxBoss, kGraphicPanelsPrefix + 55)
	// Corner Shape Dialog
DECLARE_PMID(kClassIDSpace, kCornerShapeDialogBoss, kGraphicPanelsPrefix + 101)
//gap
DECLARE_PMID(kClassIDSpace, kCornerShapeDialogMenuActionBoss, kGraphicPanelsPrefix + 103)
//gap
DECLARE_PMID(kClassIDSpace, kCornerRadiusControlStripBoss, kGraphicPanelsPrefix + 105)

// Graphic Frame Options Panel
DECLARE_PMID(kClassIDSpace, kGraphicFramePanelBoss, kGraphicPanelsPrefix + 130)
DECLARE_PMID(kClassIDSpace, kGraphicFrameFittingProxyBoss, kGraphicPanelsPrefix + 131)
DECLARE_PMID(kClassIDSpace, kObjStylesFrameFittingOptionsPanelWidgetBoss, kGraphicPanelsPrefix + 132)
DECLARE_PMID(kClassIDSpace, kObjectFCFrameFittingOptionsPanelWidgetBoss, kGraphicPanelsPrefix + 133)
DECLARE_PMID(kClassIDSpace, kOFCGraphicFrameFittingProxyBoss, kGraphicPanelsPrefix + 134)

	//	Control Strip
DECLARE_PMID(kClassIDSpace, kControlStripStrokeRegisterBoss, kGraphicPanelsPrefix + 150)
DECLARE_PMID(kClassIDSpace, kStrokeControlStripBoss, kGraphicPanelsPrefix + 151)
DECLARE_PMID(kClassIDSpace, kStrokeTableControlStripBoss, kGraphicPanelsPrefix + 152)

	//	Stroke and Fill UI
DECLARE_PMID(kClassIDSpace, kStrokeEditorDialogBoss, kGraphicPanelsPrefix + 160)
DECLARE_PMID(kClassIDSpace, kStrokeEditorPreviewBoss, kGraphicPanelsPrefix + 161)
DECLARE_PMID(kClassIDSpace, kDashedStrokeSliderTrackerBoss, kGraphicPanelsPrefix + 162)
DECLARE_PMID(kClassIDSpace, kDashedStrokePanelBoss, kGraphicPanelsPrefix + 163)
DECLARE_PMID(kClassIDSpace, kDashedStrokeSliderBoss, kGraphicPanelsPrefix + 164)
DECLARE_PMID(kClassIDSpace, kClassKeyedSwitchablePanelBoss, kGraphicPanelsPrefix + 165)
DECLARE_PMID(kClassIDSpace, kInstStrokeFillTrackerRegisterBoss, kGraphicPanelsPrefix + 166)
DECLARE_PMID(kClassIDSpace, kDashedPanelBoss, kGraphicPanelsPrefix + 167)
DECLARE_PMID(kClassIDSpace, kStrokeStyleManagerDialogBoss, kGraphicPanelsPrefix + 168)
DECLARE_PMID(kClassIDSpace, kInstStrokeFillMenuComponentBoss, kGraphicPanelsPrefix + 169)
//gap
DECLARE_PMID(kClassIDSpace, kDottedStrokeSliderBoss, kGraphicPanelsPrefix + 171)
DECLARE_PMID(kClassIDSpace, kDottedStrokeMeasureViewBoss, kGraphicPanelsPrefix + 172)
DECLARE_PMID(kClassIDSpace, kDottedStrokePanelBoss, kGraphicPanelsPrefix + 173)
DECLARE_PMID(kClassIDSpace, kDottedStrokeSliderTrackerBoss, kGraphicPanelsPrefix + 174)
DECLARE_PMID(kClassIDSpace, kDottedStrokeMeasureTrackerBoss, kGraphicPanelsPrefix + 175)
// gap
DECLARE_PMID(kClassIDSpace, kDeleteStrokeDialogBoss, kGraphicPanelsPrefix + 178)
DECLARE_PMID(kClassIDSpace, kDashedStrokeMeasureViewBoss, kGraphicPanelsPrefix + 179)
DECLARE_PMID(kClassIDSpace, kDashedStrokeMeasureTrackerBoss, kGraphicPanelsPrefix + 180)

DECLARE_PMID(kClassIDSpace, kInstStrokeFillTestMenuBoss, kGraphicPanelsPrefix + 181)

// ---- Move from Scoth rules plug-in
DECLARE_PMID(kClassIDSpace, kStripedStrokePanelBoss, kGraphicPanelsPrefix + 182)
DECLARE_PMID(kClassIDSpace, kStripedStrokeSliderBoss, kGraphicPanelsPrefix + 183)
DECLARE_PMID(kClassIDSpace, kStripedStrokeMeasureWidgetBoss, kGraphicPanelsPrefix + 184)
DECLARE_PMID(kClassIDSpace, kStripedStrokeTrackerRegisterBoss, kGraphicPanelsPrefix + 185)
DECLARE_PMID(kClassIDSpace, kStripedStrokeSliderTrackerBoss, kGraphicPanelsPrefix + 186)
DECLARE_PMID(kClassIDSpace, kStripedStrokeMeasureTrackerBoss, kGraphicPanelsPrefix + 187)
DECLARE_PMID(kClassIDSpace, kScotchRulesTestMenuBoss, kGraphicPanelsPrefix + 188)
// ---- end move.

// ---- Move from Graphics Style plug-in
DECLARE_PMID(kClassIDSpace, kStrokeFillProxyToolBoss, kGraphicPanelsPrefix + 189)
DECLARE_PMID(kClassIDSpace, kStrokeFillProxyToolContainerBoss, kGraphicPanelsPrefix + 190)
DECLARE_PMID(kClassIDSpace, kStrokeFillActionComponentBoss, kGraphicPanelsPrefix + 191)
DECLARE_PMID(kClassIDSpace, kTextLayoutTypeIconFieldWidgetBoss, kGraphicPanelsPrefix + 193)
DECLARE_PMID(kClassIDSpace, kBoss_ApplyCurrentColorTool, kGraphicPanelsPrefix + 194)
DECLARE_PMID(kClassIDSpace, kBoss_ApplyCurrentGradientTool, kGraphicPanelsPrefix + 195)
DECLARE_PMID(kClassIDSpace, kBoss_ClearFillStrokeTool, kGraphicPanelsPrefix + 196)
DECLARE_PMID(kClassIDSpace, kTBPopoutRenderingObjectBoss, kGraphicPanelsPrefix + 197)
DECLARE_PMID(kClassIDSpace, kControlStripCornerShapeRegisterBoss, kGraphicPanelsPrefix + 198)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kObjectExportOptionsActionComponentBoss, kGraphicPanelsPrefix + 199)
DECLARE_PMID(kClassIDSpace, kObjectExportOptionsDlgBoss, kGraphicPanelsPrefix + 200)
DECLARE_PMID(kClassIDSpace, kObjectExportCommonOptionsPanelBoss, kGraphicPanelsPrefix + 201)
DECLARE_PMID(kClassIDSpace, kObjectExportPDFOptionsPanelBoss, kGraphicPanelsPrefix + 202)
DECLARE_PMID(kClassIDSpace, kObjectExportEPUBOptionsPanelBoss, kGraphicPanelsPrefix + 203)
DECLARE_PMID(kClassIDSpace, kOEOptionsDDListWidgetBoss, kGraphicPanelsPrefix + 204)
DECLARE_PMID(kClassIDSpace, kOEOptionsTextEditWidgetBoss, kGraphicPanelsPrefix + 205)
DECLARE_PMID(kClassIDSpace, kOEOptionsCheckBoxWidgetBoss, kGraphicPanelsPrefix + 206)
DECLARE_PMID(kClassIDSpace, kOEOptionsRealEditBoxWidgetBoss, kGraphicPanelsPrefix + 207)
DECLARE_PMID(kClassIDSpace, kOEOptionsPanelWithClusterButtonFocusWidgetBoss, kGraphicPanelsPrefix + 208)
DECLARE_PMID(kClassIDSpace, kObjStylesObjectExportCommonOptionsPanelBoss,	kGraphicPanelsPrefix + 228)
DECLARE_PMID(kClassIDSpace, kObjStylesObjectExportPDFOptionsPanelBoss,	kGraphicPanelsPrefix + 229)
DECLARE_PMID(kClassIDSpace, kObjStylesObjectExportEPUBOptionsPanelBoss,	kGraphicPanelsPrefix + 230)
DECLARE_PMID(kClassIDSpace, kObjectFCObjectExportEPUBOptionsPanelBoss,	kGraphicPanelsPrefix + 231)
DECLARE_PMID(kClassIDSpace, kObjectFCObjectExportCommonOptionsPanelBoss,	kGraphicPanelsPrefix + 232)
DECLARE_PMID(kClassIDSpace, kObjectFCObjectExportPDFOptionsPanelBoss,	kGraphicPanelsPrefix + 233)

DECLARE_PMID(kClassIDSpace, kEpubTypePopupWidgetBoss, kGraphicPanelsPrefix + 235 )
DECLARE_PMID(kClassIDSpace, kEpubTypeEditBoxWidgetBoss, kGraphicPanelsPrefix + 236 )
DECLARE_PMID(kClassIDSpace, kStrokeTouchPanel, kGraphicPanelsPrefix + 237)
DECLARE_PMID(kClassIDSpace, kIntegerPercentEditBoxWidgetBoss, kGraphicPanelsPrefix + 238)
DECLARE_PMID(kClassIDSpace, kStrokePopupPanelBoss, kGraphicPanelsPrefix + 239)
DECLARE_PMID(kClassIDSpace, kAltTextMultilineEditBoxBoss, kGraphicPanelsPrefix + 240)
DECLARE_PMID(kClassIDSpace, kActaulTextMultilineEditBoxBoss, kGraphicPanelsPrefix + 241)

// <Interface ID>
// IIDs
	//	Stroke Panel
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEPANELVALUES, kGraphicPanelsPrefix + 1)
//gap
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEPANELWIDGETSOBSERVER, kGraphicPanelsPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSIDLISTDATA, kGraphicPanelsPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONGROUPVALUE, kGraphicPanelsPrefix + 6)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEPANELOPTIONS, kGraphicPanelsPrefix + 8)

	// Attributes Panel
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTESPANELVALUES, kGraphicPanelsPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTESVALUES, kGraphicPanelsPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERPRINTVALUE, kGraphicPanelsPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTESPANELWIDGETSOBSERVER, kGraphicPanelsPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_INONPRINTVALUE, kGraphicPanelsPrefix + 55)

	//Control Strip
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPSTROKEPANELSUITE, kGraphicPanelsPrefix + 100)

	// Stroke and Fill UI
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEEDITORDIALOGDATA, kGraphicPanelsPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSKEYEDSWITCHABLEPANELDATA, kGraphicPanelsPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEEDITORPANELDATA, kGraphicPanelsPrefix + 112)

DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKERUIUTILS, kGraphicPanelsPrefix + 113)

// ---- Move from Scoth rules plug-in
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKESLIDERCONTROLDATA, kGraphicPanelsPrefix + 114)
// ---- end move.

// ---- Move from Graphic Styles plug-in
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEFILLOBSERVER, kGraphicPanelsPrefix + 115)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATEOBSERVER, kGraphicPanelsPrefix + 116)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLBOXRENDERING_GFXSTATEOBS, kGraphicPanelsPrefix + 117)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPCORNERSHAPESUITE, kGraphicPanelsPrefix + 118)
// ---- end move.
DECLARE_PMID(kInterfaceIDSpace, IID_IOEOPTIONSDIALOGUIUTILS, kGraphicPanelsPrefix + 119)

// <Implementation ID>
// Implementation IIDs
	// GraphicPanels plugin
//DECLARE_PMID(kImplementationIDSpace, kGraphicPanelsRegister, kGraphicPanelsPrefix + 1)
	//	Stroke Panel
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokePanelMenuComponent, kGraphicPanelsPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kStrokePanelOptions, kGraphicPanelsPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kStrokePanelView, kGraphicPanelsPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kClassIDListData, kGraphicPanelsPrefix + 6)
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokePanelValues, kGraphicPanelsPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokePanelDetailControllerImpl, kGraphicPanelsPrefix + 11)

DECLARE_PMID(kImplementationIDSpace, kStrokePanelGraphicStateObserver, kGraphicPanelsPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kStrokePanelWidgetsObserver, kGraphicPanelsPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kOSFrameFittingPanelObserverImpl, kGraphicPanelsPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kLineCapValue, kGraphicPanelsPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kJoinTypeValue, kGraphicPanelsPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFrameFittingOptionsPanelCreatorImpl, kGraphicPanelsPrefix + 24)
//gap
//DECLARE_PMID(kImplementationIDSpace, kStrokeTypeOwnerDrawDDItemImpl_obsolete, kGraphicPanelsPrefix + 26)	
DECLARE_PMID(kImplementationIDSpace, kStrokeAlignButtonGroupValueImpl, kGraphicPanelsPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kObjectFCFrameFittingOptionsPanelCreatorImpl, kGraphicPanelsPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kOFCFrameFittingPanelObserverImpl, kGraphicPanelsPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFrameFittingOptionsPanelDataImpl, kGraphicPanelsPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kArrowHeadAlignButtonGroupValueImpl, kGraphicPanelsPrefix + 31)

	// Attributes Panel
DECLARE_PMID(kImplementationIDSpace, kDV_AttributesPanelView,	kGraphicPanelsPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAttributesPanelView,		kGraphicPanelsPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kAttributesPanelValues, kGraphicPanelsPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAttributesValues, kGraphicPanelsPrefix + 55)

DECLARE_PMID(kImplementationIDSpace, kAttributesPanelGraphicStateObserver, kGraphicPanelsPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kAttributesPanelWidgetsObserver, kGraphicPanelsPrefix + 57)

DECLARE_PMID(kImplementationIDSpace, kOverprintValue, kGraphicPanelsPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kNonPrintValue, kGraphicPanelsPrefix + 59)
	// Corner Shape Dialog
DECLARE_PMID(kImplementationIDSpace, kCornerShapeDialogObserver, kGraphicPanelsPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kCornerShapeDialogController, kGraphicPanelsPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kCornerShapeDialogMenuAction, kGraphicPanelsPrefix + 104)

DECLARE_PMID(kImplementationIDSpace, kCornerShapeControlStripObserverImpl, kGraphicPanelsPrefix + 105)

	//	ControlStrip
DECLARE_PMID(kImplementationIDSpace, kControlStripStrokeSuiteImpl, kGraphicPanelsPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kControlStripStrokeRegisterImpl, kGraphicPanelsPrefix + 151)

	// Stroke and Fill UI
DECLARE_PMID(kImplementationIDSpace, kStrokeEditorDialogControllerImpl, kGraphicPanelsPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kStrokeEditorDialogObserverImpl, kGraphicPanelsPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kStrokeEditorPreviewViewImpl, kGraphicPanelsPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeSliderTrackerImpl, kGraphicPanelsPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeSliderControlDataImpl, kGraphicPanelsPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeSliderViewImpl, kGraphicPanelsPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokePanelControllerImpl, kGraphicPanelsPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokePanelObserverImpl, kGraphicPanelsPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeStrokeEditorPanelDataImpl, kGraphicPanelsPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kInstStrokeFillTrackerRegisterImpl, kGraphicPanelsPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kClassKeyedSwitchablePanelDataImpl, kGraphicPanelsPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kInstStrokeFillActionComponentImpl, kGraphicPanelsPrefix + 171)
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokeStyleMgrDlgObserverImpl, kGraphicPanelsPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kStrokeStyleMgrDlgControllerImpl, kGraphicPanelsPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kDeleteStrokeDlgControllerImpl, kGraphicPanelsPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeMeasureViewImpl, kGraphicPanelsPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kDashedStrokeMeasureTrackerImpl, kGraphicPanelsPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokeStrokeEditorPanelDataImpl, kGraphicPanelsPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokeMeasureViewImpl, kGraphicPanelsPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokePanelControllerImpl, kGraphicPanelsPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokeSliderViewImpl, kGraphicPanelsPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokeSliderTrackerImpl, kGraphicPanelsPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokePanelObserverImpl, kGraphicPanelsPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kDottedStrokeMeasureTrackerImpl, kGraphicPanelsPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kStrokeEditorDialogDataImpl, kGraphicPanelsPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kStrokeStyleManagerListBoxEHImpl, kGraphicPanelsPrefix + 186)
// gap
DECLARE_PMID(kImplementationIDSpace, kInstStrokeFillTestMenuImpl, kGraphicPanelsPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kPathStrokerUIUtilsImpl, kGraphicPanelsPrefix + 190)

// ---- Move from Scoth rules plug-in
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeSliderViewImpl, kGraphicPanelsPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeControlDataImpl, kGraphicPanelsPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeMeasureViewImpl, kGraphicPanelsPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeTrackerRegisterImpl, kGraphicPanelsPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeSliderTrackerImpl, kGraphicPanelsPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeMeasureTrackerImpl, kGraphicPanelsPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kScotchRulesTestMenuImpl, kGraphicPanelsPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeObserverImpl, kGraphicPanelsPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeDialogControllerImpl, kGraphicPanelsPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kStripedStrokeStrokeEditorPanelDataImpl, kGraphicPanelsPrefix + 200)
// ---- end move.

// ---- Move from Graphics Style plug-in
DECLARE_PMID(kImplementationIDSpace, kStrokeFillProxyToolImpl, kGraphicPanelsPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kToolboxROButtonGfxStateObsImpl, kGraphicPanelsPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillToolSizerImpl, kGraphicPanelsPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillActionComponentImpl, kGraphicPanelsPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kSolidColorToolImpl, kGraphicPanelsPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kToolboxRenderingObjectControlViewImpl, kGraphicPanelsPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kColorStateToolSizerImpl, kGraphicPanelsPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kGradientToolImpl, kGraphicPanelsPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kNoneToolImpl, kGraphicPanelsPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kTBPopoutRenderingObjectViewImpl, kGraphicPanelsPrefix + 214)
//gap
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kGraphicFrameOptionsControllerImpl, kGraphicPanelsPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kGFProxyEventHandlerImpl, kGraphicPanelsPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kGraphicFrameDlgObserverImpl, kGraphicPanelsPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kOFCGFProxyEventHandlerImpl,kGraphicPanelsPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kControlStripCornerShapeRegisterImpl,kGraphicPanelsPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kControlStripCornerShapeSuiteImpl,kGraphicPanelsPrefix + 225)


DECLARE_PMID(kImplementationIDSpace, kOEOptionsActionComponentImpl, kGraphicPanelsPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsTabbedDialogCreatorImpl, kGraphicPanelsPrefix + 227)
//gap
DECLARE_PMID(kImplementationIDSpace, kOECommonOptionsPanelCreatorImpl, kGraphicPanelsPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kOECommonOptionsPanelObserverImpl, kGraphicPanelsPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kOECommonOptionsPanelControllerImpl, kGraphicPanelsPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kOEPDFOptionsPanelCreatorImpl, kGraphicPanelsPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kOEPDFOptionsPanelObserverImpl, kGraphicPanelsPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kOEPDFOptionsPanelControllerImpl, kGraphicPanelsPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kOEEPUBOptionsPanelCreatorImpl, kGraphicPanelsPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kOEEPUBOptionsPanelObserverImpl, kGraphicPanelsPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kOEEPUBOptionsPanelControllerImpl, kGraphicPanelsPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsSelectionObserverImpl, kGraphicPanelsPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsDropDownListEHImpl, kGraphicPanelsPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsTextEditBoxEHImpl, kGraphicPanelsPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsDialogEHImpl, kGraphicPanelsPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsCheckBoxWidgetEHImpl, kGraphicPanelsPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsDialogUIUtilsImpl, kGraphicPanelsPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsDialogObserverImpl, kGraphicPanelsPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsGroupButtonPanelEHImpl, kGraphicPanelsPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExptCommonOptsDataImpl, kGraphicPanelsPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpCommonPanelCreatorImpl, kGraphicPanelsPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpCommonPanelObserverImpl, kGraphicPanelsPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExptPDFOptsDataImpl, kGraphicPanelsPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpPDFPanelCreatorImpl, kGraphicPanelsPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpPDFPanelObserverImpl, kGraphicPanelsPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExptEPUBOptsDataImpl, kGraphicPanelsPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpEPUBPanelCreatorImpl, kGraphicPanelsPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kObjStylesObjExpEPUBPanelObserverImpl, kGraphicPanelsPrefix + 254)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpEPUBPanelCreatorImpl, kGraphicPanelsPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpEPUBPanelObserverImpl, kGraphicPanelsPrefix2 + 2)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpCommonPanelCreatorImpl, kGraphicPanelsPrefix2 + 3)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpCommonPanelObserverImpl, kGraphicPanelsPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpPDFPanelCreatorImpl, kGraphicPanelsPrefix2 + 5)
DECLARE_PMID(kImplementationIDSpace, kObjectFCObjExpPDFPanelObserverImpl, kGraphicPanelsPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kIntegerPercentEditBoxValidationImpl, kGraphicPanelsPrefix2 + 8)
DECLARE_PMID(kImplementationIDSpace, kAltTextMultilineTextBoxEHImpl, kGraphicPanelsPrefix2 + 9)

//gap

// <Widget ID>
// Widget IDs
	//	Stroke Panel
DECLARE_PMID(kWidgetIDSpace, kWeightWidgetId, kGraphicPanelsPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kWeightNudgeWidgetId, kGraphicPanelsPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kWeightComboWidgetId, kGraphicPanelsPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kMiterWidgetId, kGraphicPanelsPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kMiterNudgeWidgetId, kGraphicPanelsPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kMiterTextWidgetId, kGraphicPanelsPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kLineCapStaticTextWidgetId, kGraphicPanelsPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kLineCapClusterWidgetId, kGraphicPanelsPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kButCapIconWidgetId, kGraphicPanelsPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kRoundCapIconWidgetId, kGraphicPanelsPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kProjectingCapIconWidgetId, kGraphicPanelsPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kJoinTypeClusterWidgetId, kGraphicPanelsPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kMiterJoinIconWidgetId, kGraphicPanelsPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kRoundedJoinIconWidgetId, kGraphicPanelsPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kBevelJoinIconWidgetId, kGraphicPanelsPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kStrokeTypePopupWidgetId, kGraphicPanelsPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kLineEndEndPopupWidgetId, kGraphicPanelsPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kLineEndStartPopupWidgetId, kGraphicPanelsPrefix + 18)

	// Attributes Panel
DECLARE_PMID(kWidgetIDSpace, kOverPrintFillWidgetId, kGraphicPanelsPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kOverPrintStrokeWidgetId, kGraphicPanelsPrefix + 20)
	// Corner Shape Dialog
DECLARE_PMID(kWidgetIDSpace, kCornerEffectPopupWidgetId, kGraphicPanelsPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kRadiusEditWidgetId, kGraphicPanelsPrefix + 22)

DECLARE_PMID(kWidgetIDSpace, kAttributesParentWidgetId, kGraphicPanelsPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kCornerShapeParentWidgetId, kGraphicPanelsPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kEffectTextWidgetId, kGraphicPanelsPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kCornerSizeTextWidgetId, kGraphicPanelsPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kStrokeParentWidgetId, kGraphicPanelsPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kWeightTextWidgetId, kGraphicPanelsPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kMiterStaticTextWidgetId, kGraphicPanelsPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kJoinTextWidgetId, kGraphicPanelsPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kStrokeSeparatorWidgetId, kGraphicPanelsPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kStrokeTextWidgetId, kGraphicPanelsPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kStartTextWidgetId, kGraphicPanelsPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kEndTextWidgetId, kGraphicPanelsPrefix + 34)

DECLARE_PMID(kWidgetIDSpace, kStrokeSubPanel1Id, kGraphicPanelsPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kStrokeSubPanel2Id, kGraphicPanelsPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kStrokeSubPanel3Id, kGraphicPanelsPrefix + 37)

DECLARE_PMID(kWidgetIDSpace, kWeightComboWidget2Id, kGraphicPanelsPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kLineCapHiliteWidgetId, kGraphicPanelsPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kJoinTypeHiliteWidgetId, kGraphicPanelsPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kXTextWidgetId, kGraphicPanelsPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kWeightNudgeWidget2Id, kGraphicPanelsPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kNonPrintWidgetId, kGraphicPanelsPrefix + 43)

// Table Stroke ID's
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSubPanel1Id, kGraphicPanelsPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kTableWeightTextWidget1Id, kGraphicPanelsPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kTableWeightComboWidget1Id, kGraphicPanelsPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kTableWeightNudgeWidget1Id, kGraphicPanelsPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kTableCellSelectionWidget1Id, kGraphicPanelsPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeTextWidget1Id, kGraphicPanelsPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kTableLineStyleWidget1Id, kGraphicPanelsPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSubPanel2d, kGraphicPanelsPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kTableWeightTextWidget2Id, kGraphicPanelsPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kTableWeightComboWidget2Id, kGraphicPanelsPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kTableWeightNudgeWidget2Id, kGraphicPanelsPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSubPanel2Id, kGraphicPanelsPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeTextWidget2Id, kGraphicPanelsPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kTableLineStyleWidget2Id, kGraphicPanelsPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSubPanel3Id, kGraphicPanelsPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kTableCellSelectionWidget3Id, kGraphicPanelsPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSeparatorWidget3Id, kGraphicPanelsPrefix + 61)

DECLARE_PMID(kWidgetIDSpace, kCSLabelPanelWidgetID, kGraphicPanelsPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kCSControlsPanelWidgetID, kGraphicPanelsPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kCSButtonsPanelWidgetID, kGraphicPanelsPrefix + 64)

DECLARE_PMID(kWidgetIDSpace, kStrokeAlignStaticWidgetID, kGraphicPanelsPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignClusterWidgetID, kGraphicPanelsPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignCenterIconWidgetID, kGraphicPanelsPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignInsideIconWidgetID, kGraphicPanelsPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignOutsideIconWidgetID, kGraphicPanelsPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kStrokeSeparator2WidgetID, kGraphicPanelsPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kStrokeAlignHiliteWidgetID, kGraphicPanelsPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kGapColorStaticWidgetID, kGraphicPanelsPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kGapColorDropDownWidgetID, kGraphicPanelsPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kGapTintStaticWidgetID, kGraphicPanelsPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kGapTintEditWidgetID, kGraphicPanelsPrefix + 75)

// Attribute panel part 2
DECLARE_PMID(kWidgetIDSpace, kAPOverPrintGapWidgetID, kGraphicPanelsPrefix + 76)

DECLARE_PMID(kWidgetIDSpace, kGapColorStaticWidget3ID, kGraphicPanelsPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kGapColorDropDownWidget3ID, kGraphicPanelsPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kGapTintStaticWidget3ID, kGraphicPanelsPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kGapTintEditWidget3ID, kGraphicPanelsPrefix + 80)


DECLARE_PMID(kWidgetIDSpace, kCornerRadiusWidgetId, kGraphicPanelsPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kCornerRadiusIconWidgetId, kGraphicPanelsPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kCornerRadiusEditNudgeWidgetId, kGraphicPanelsPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kCornerRadiusEditWidgetId, kGraphicPanelsPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kCornerEffectControlStripPopupWidgetId, kGraphicPanelsPrefix + 85)

DECLARE_PMID(kWidgetIDSpace, kDesignLibrarySubPanel2Id, kGraphicPanelsPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kDLEmbeddedWindowContainerWidgetId, kGraphicPanelsPrefix + 87)

// Stroke and Fill UI
DECLARE_PMID(kWidgetIDSpace, kDashedPanelWidgetId, kGraphicPanelsPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kDashEditBox1WidgetId, kGraphicPanelsPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kDashEditBox2WidgetId, kGraphicPanelsPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kDashEditBox3WidgetId, kGraphicPanelsPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kGapEditBox1WidgetId, kGraphicPanelsPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kGapEditBox2WidgetId, kGraphicPanelsPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kGapEditBox3WidgetId, kGraphicPanelsPrefix + 96)

DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID0, kGraphicPanelsPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID1, kGraphicPanelsPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID2, kGraphicPanelsPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID3, kGraphicPanelsPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID4, kGraphicPanelsPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID5, kGraphicPanelsPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID6, kGraphicPanelsPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kInstStrokeWidgetID7, kGraphicPanelsPrefix + 104)

DECLARE_PMID(kWidgetIDSpace, kCornerAdjustmentWidgetId, kGraphicPanelsPrefix + 105)

// Stroke Editor Dialog
DECLARE_PMID(kWidgetIDSpace, kStrokeEditorDialogID, kGraphicPanelsPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kSEDNameLabelWidgetID, kGraphicPanelsPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kSEDNameWidgetID, kGraphicPanelsPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kSEDTypeLabelWidgetID, kGraphicPanelsPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kSEDTypeDropDownWidgetID, kGraphicPanelsPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kSEDAttributesGroupWidgetID, kGraphicPanelsPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kSEDAttributesTitleWidgetID, kGraphicPanelsPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kSEDSubpanelHolderWidgetID, kGraphicPanelsPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewGroupWidgetID, kGraphicPanelsPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewTitleWidgetID, kGraphicPanelsPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewSizeLabelWidgetID, kGraphicPanelsPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewSizeNudgeWidgetID, kGraphicPanelsPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewSizeWidgetID, kGraphicPanelsPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kSEDPreviewWidgetID, kGraphicPanelsPrefix + 119)

// Dash stroke panel
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokePanelID, kGraphicPanelsPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kSEDAddButtonWidgetID, kGraphicPanelsPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeSliderWidgetID, kGraphicPanelsPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeLengthLabelWidgetID, kGraphicPanelsPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeLengthNudgeWidgetID, kGraphicPanelsPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeLengthWidgetID, kGraphicPanelsPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeCornersLabelWidgetID, kGraphicPanelsPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeCornersWidgetID, kGraphicPanelsPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeCapLabelWidgetID, kGraphicPanelsPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeCapGroupID, kGraphicPanelsPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeCapClusterID, kGraphicPanelsPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeButtCapWidgetID, kGraphicPanelsPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeRoundCapWidgetID, kGraphicPanelsPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeSquareCapWidgetID, kGraphicPanelsPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeStartLabelWidgetID, kGraphicPanelsPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeStartNudgeWidgetID, kGraphicPanelsPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeStartWidgetID, kGraphicPanelsPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeWidthLabelWidgetID, kGraphicPanelsPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeWidthNudgeWidgetID, kGraphicPanelsPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeWidthWidgetID, kGraphicPanelsPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeMeasureWidgetID, kGraphicPanelsPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kSEDDashedStrokeSliderPanelWidgetID, kGraphicPanelsPrefix + 141)

// Stroke style manager dialog
DECLARE_PMID(kWidgetIDSpace, kStrokeStyleManagerDialogID, kGraphicPanelsPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kSSMDStyleListLabelWidgetID, kGraphicPanelsPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kSSMDStyleListWidgetID, kGraphicPanelsPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kSSMDSettingsLabelWidgetID, kGraphicPanelsPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kSSMDSettingsGroupWidgetID, kGraphicPanelsPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kSSMDSettingsTextWidgetID, kGraphicPanelsPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kSSMDSettingsScrollWidgetID, kGraphicPanelsPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kSSMDNewButtonWidgetID, kGraphicPanelsPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kSSMDEditButtonWidgetID, kGraphicPanelsPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kSSMDDeleteButtonWidgetID, kGraphicPanelsPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kSSMDImportButtonWidgetID, kGraphicPanelsPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kSSMDExportButtonWidgetID, kGraphicPanelsPrefix + 153)

// Delete stroke dialog
DECLARE_PMID(kWidgetIDSpace, kDeleteStrokeDialogWidgetID, kGraphicPanelsPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kDSDLabelWidgetID, kGraphicPanelsPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kDSDPopupWidgetID, kGraphicPanelsPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kDSDWarningIconWidgetID, kGraphicPanelsPrefix + 157)

DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokePanelID, kGraphicPanelsPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeSliderPanelWidgetID, kGraphicPanelsPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeMeasureWidgetID, kGraphicPanelsPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeSliderWidgetID, kGraphicPanelsPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeCenterLabelWidgetID, kGraphicPanelsPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeCenterNudgeWidgetID, kGraphicPanelsPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeCenterWidgetID, kGraphicPanelsPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeLengthLabelWidgetID, kGraphicPanelsPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeLengthNudgeWidgetID, kGraphicPanelsPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeLengthWidgetID, kGraphicPanelsPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeCornersLabelWidgetID, kGraphicPanelsPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kSEDDottedStrokeCornersWidgetID, kGraphicPanelsPrefix + 169)

// ---- Moved from Scotch Rules plug-in
DECLARE_PMID(kWidgetIDSpace, kStripedStrokePanelID, kGraphicPanelsPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kStripeSliderWidgetID, kGraphicPanelsPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kStripeStartLabelWidgetID, kGraphicPanelsPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kStripeStartValueWidgetID, kGraphicPanelsPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kStripeStartPctWidgetID, kGraphicPanelsPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kStripeWidthLabelWidgetID, kGraphicPanelsPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kStripeWidthValueWidgetID, kGraphicPanelsPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kStripeWidthPctWidgetID, kGraphicPanelsPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kStripeSliderPanelWidgetID, kGraphicPanelsPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kStripeSliderMeasureWidgetID, kGraphicPanelsPrefix + 179)
// ---- end move.

// ---- Moved from Graphic Styles plug-in
DECLARE_PMID(kWidgetIDSpace, kWidgetID_StrokeFillProxy, kGraphicPanelsPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillWidgetId, kGraphicPanelsPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillSwitchIconWidgetId, kGraphicPanelsPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillDefaultIconWidgetId, kGraphicPanelsPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kSolidColorToolWidgetId, kGraphicPanelsPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kGradientColorToolWidgetId, kGraphicPanelsPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kNoneColorToolWidgetId, kGraphicPanelsPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillProxyToolWidgetId, kGraphicPanelsPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kTextLayoutTypeWidgetId, kGraphicPanelsPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kLayoutSwitchIconWidgetId, kGraphicPanelsPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kTextLayoutSwitchIconWidgetId, kGraphicPanelsPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kTextSwitchIconWidgetId, kGraphicPanelsPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kSwapTextLayoutSeparatorID, kGraphicPanelsPrefix + 192)
// ---- end move.

// for EVE
DECLARE_PMID(kWidgetIDSpace,	kSSMControlsPanelWidgetID,			kGraphicPanelsPrefix + 193) 
DECLARE_PMID(kWidgetIDSpace,	kSSMButtonsPanelWidgetID,			kGraphicPanelsPrefix + 194) 

// --- Graphic Frame Options Panel
DECLARE_PMID(kWidgetIDSpace, kAutoFitButtonWidgetID, kGraphicPanelsPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kAutoFitPanelWidgetId, kGraphicPanelsPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kAutoFitNoteIconWidgetID, kGraphicPanelsPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kAutoFitNoteTextWidgetID, kGraphicPanelsPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kGraphicFramePanelWidgetID, kGraphicPanelsPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kAlignmentTitleWidgetID, kGraphicPanelsPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kReferencePointTextWidgetID, kGraphicPanelsPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kGFFittingProxyWidgetID, kGraphicPanelsPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kGraphicFrameOptPosGroupWidgetId, kGraphicPanelsPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kCropAmountsTitleTextWidgetID, kGraphicPanelsPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kGFCropTopTextWidgetID, kGraphicPanelsPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kCropTopEditWidgetID, kGraphicPanelsPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kGFCropBottomTextWidgetID, kGraphicPanelsPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kCropBottomEditWidgetID, kGraphicPanelsPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kCropTopNudgeWidgetID, kGraphicPanelsPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kCropBottomNudgeWidgetID, kGraphicPanelsPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kGFOptionsCropChainWidgetID, kGraphicPanelsPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kGFCropLeftTextWidgetID, kGraphicPanelsPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kCropLeftEditWidgetID, kGraphicPanelsPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kGFCropRightTextWidgetID, kGraphicPanelsPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kCropRightEditWidgetID, kGraphicPanelsPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kCropLeftNudgeWidgetID, kGraphicPanelsPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kCropRightNudgeWidgetID, kGraphicPanelsPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kGFFittingGroupWidgetId, kGraphicPanelsPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kGFFittingTitleWidgetId, kGraphicPanelsPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kGFFittingTextWidgetID, kGraphicPanelsPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kGFFittingDropdownWidgetId, kGraphicPanelsPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kGraphicFrameButtonsPanelWidgetID, kGraphicPanelsPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kGraphicFrameOnlyButtonsPanelWidgetID, kGraphicPanelsPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kGraphicFrameAlignmentGroupWidgetId, kGraphicPanelsPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kGFOptMiscGroupWidgetId, kGraphicPanelsPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGFOptionsPanelWidgetID, kGraphicPanelsPrefix + 226)

// --- link buttons in stroke styles dialog
DECLARE_PMID(kWidgetIDSpace, kSSMDJBXUIUpdateLinkButtonWidgetID, kGraphicPanelsPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kSSMDJBXUIUnlinkButtonWidgetID,	 kGraphicPanelsPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kSSMDJBXUIRelinkButtonWidgetID,	 kGraphicPanelsPrefix + 229)

// --- Various nudge buttons
DECLARE_PMID(kWidgetIDSpace, kRadiusEditNudgeWidgetId,			kGraphicPanelsPrefix + 230)

// ---- Part of Corner Effects (Four Nudge buttons) ---
DECLARE_PMID(kWidgetIDSpace, kRadiusTopLeftEditNudgeWidgetId,	 kGraphicPanelsPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kRadiusBottomLeftEditNudgeWidgetId, kGraphicPanelsPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kRadiusBottomRightEditNudgeWidgetId,kGraphicPanelsPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kRadiusTopRightEditNudgeWidgetId,	 kGraphicPanelsPrefix + 234)


DECLARE_PMID(kWidgetIDSpace, kRadiusTopLeftEditWidgetId,    kGraphicPanelsPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kRadiusBottomLeftEditWidgetId, kGraphicPanelsPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kRadiusBottomRightEditWidgetId,kGraphicPanelsPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kRadiusTopRightEditWidgetId,   kGraphicPanelsPrefix + 238)


DECLARE_PMID(kWidgetIDSpace, kCornerEffectTopLeftPopupWidgetId,    kGraphicPanelsPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kCornerEffectBottomLeftPopupWidgetId, kGraphicPanelsPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kCornerEffectBottomRightPopupWidgetId,kGraphicPanelsPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kCornerEffectTopRightPopupWidgetId,   kGraphicPanelsPrefix + 242)

DECLARE_PMID(kWidgetIDSpace, kCornerAffectChainWidgetID,    kGraphicPanelsPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kCSButtonsPanel2WidgetID,    kGraphicPanelsPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kCornerEffectDialogStaticWID,    kGraphicPanelsPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kCSFirstRowWidgetId,    kGraphicPanelsPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kCSSecondRowWidgetId,    kGraphicPanelsPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kCSTopLeftIconWidgetId,    kGraphicPanelsPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kCSTopRightIconWidgetId,    kGraphicPanelsPrefix + 249)
DECLARE_PMID(kWidgetIDSpace, kCSBottomLeftIconWidgetId,    kGraphicPanelsPrefix + 250)
DECLARE_PMID(kWidgetIDSpace, kCSBottomRightIconWidgetId,    kGraphicPanelsPrefix + 251)
//gap
// Object Export Options dialog ids
DECLARE_PMID(kWidgetIDSpace, kObjectExportOptionsTabbedDlgWID, kGraphicPanelsPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace, kObjectExportCommonOptionsDlgWID, kGraphicPanelsPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace, kAltTextSourceLabelWidgetID, kGraphicPanelsPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace, kAltTextSourceTypeWidgetID, kGraphicPanelsPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace, kAltTextWidgetID, kGraphicPanelsPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace, kAltTextXMPLabelWidgetID, kGraphicPanelsPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kAltTextXMPPropertyWidgetID, kGraphicPanelsPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace, kObjectExportPDFOptionsDlgWID, kGraphicPanelsPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace, kApplyTagLabelWidgetID, kGraphicPanelsPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace, kApplyTagTypeWidgetID, kGraphicPanelsPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace, kActualTextSourceLabelWidgetID, kGraphicPanelsPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace, kActualTextSourceTypeWidgetID, kGraphicPanelsPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, kActualTextWidgetID, kGraphicPanelsPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, kActualTextXMPLabelWidgetID, kGraphicPanelsPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, kActualTextXMPPropertyWidgetID, kGraphicPanelsPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace, kObjectExportEPUBOptionsDlgWID, kGraphicPanelsPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace, kCustomImageConvCheckboxWidgetID, kGraphicPanelsPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace, kSizeStaticTextWidgetID, kGraphicPanelsPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace, kSizeDropDownWidgetID, kGraphicPanelsPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace, kResolutionStaticTextWidgetID, kGraphicPanelsPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace, kResolutionDropDownWidgetID, kGraphicPanelsPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace, kFormatStaticTextWidgetID, kGraphicPanelsPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace, kFormatDropDownWidgetID, kGraphicPanelsPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace, kQualityStaticTextWidgetID, kGraphicPanelsPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace, kQualityDropDownWidgetID, kGraphicPanelsPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace, kMethodStaticTextWidgetID, kGraphicPanelsPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace, kFormatMethodDropDownWidgetID, kGraphicPanelsPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace, kPaletteStaticTextWidgetID, kGraphicPanelsPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace, kPaletteDropDownWidgetID, kGraphicPanelsPrefix2 + 29)
DECLARE_PMID(kWidgetIDSpace, kInterlacedCheckboxWidgetID, kGraphicPanelsPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace, kCustomLayoutCheckboxWidgetID, kGraphicPanelsPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace, kIconOEOptsAlignLeftWidgetId, kGraphicPanelsPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace, kIconOEOptsAlignCenterWidgetId, kGraphicPanelsPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace, kIconOEOptsAlignRightWidgetId, kGraphicPanelsPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace, kIconOEOptsSpaceBeforeWidgetId, kGraphicPanelsPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace, kOEOptsSpaceBeforeNudgeWidgetId, kGraphicPanelsPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace, kOEOptsSpaceBeforeObserverWidgetId, kGraphicPanelsPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace, kIconOEOptsSpaceAfterWidgetId, kGraphicPanelsPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace, kOEOptsSpaceAfterNudgeWidgetId, kGraphicPanelsPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace, kOEOptsSpaceAfterObserverWidgetId, kGraphicPanelsPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace, kCSSUnitTypeStaticTextWidgetID, kGraphicPanelsPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace, kInsertPageBreakWidgetID, kGraphicPanelsPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace, kImagePageBreakDropDownWidgetID, kGraphicPanelsPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace, kActualTextGenericPanelWidgetID, kGraphicPanelsPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace, kCustomLayoutTypeDropDownWidgetID, kGraphicPanelsPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace, kCustomContentConvCheckboxWidgetID, kGraphicPanelsPrefix2 + 46)
DECLARE_PMID(kWidgetIDSpace, kCustomConvStaticTextWidgetID, kGraphicPanelsPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace, kCustomConvDropDownWidgetID, kGraphicPanelsPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace, kSVGExportTypeDropDownWidgetID, kGraphicPanelsPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace, kStrokeStyleListPanelWidgetID, kGraphicPanelsPrefix2 + 50)
DECLARE_PMID(kWidgetIDSpace, kStrokeTypePopupElementWidgetID, kGraphicPanelsPrefix2 + 51)
DECLARE_PMID(kWidgetIDSpace, kCSSUnitTypeSpaceBeforeStaticTextWidgetID, kGraphicPanelsPrefix2 + 52)
DECLARE_PMID(kWidgetIDSpace, kCustomLayoutGenericWidgetId, kGraphicPanelsPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace, kUseOriginalImageCheckboxWidgetID, kGraphicPanelsPrefix2 + 54)

DECLARE_PMID(kWidgetIDSpace, kCustomSizeStaticTextWidgetID, kGraphicPanelsPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace, kCustomSizeTypeDropDownWidgetID, kGraphicPanelsPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace, kEditBoxCustomSizeWidgetId, kGraphicPanelsPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace, kAllSVGsCheckboxWidgetID, kGraphicPanelsPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace, kSVGFormatDropDownWidgetID, kGraphicPanelsPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace, kSVGExportTypeStaticTextWidgetID, kGraphicPanelsPrefix2 + 60)
// -- GAP -- 

DECLARE_PMID(kWidgetIDSpace, kEpubTypeStaticTextWidgetID, kGraphicPanelsPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace, kEpubTypeEditWidgetID, kGraphicPanelsPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace, kEpubTypeFlyOutWidgetID, kGraphicPanelsPrefix2 + 67)

// stroke touch panel
DECLARE_PMID(kWidgetIDSpace, kWeightComboTouchWidgetId, kGraphicPanelsPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace, kStrokeTouchWeightSliderWidgetId, kGraphicPanelsPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace, kStrokeTypeTouchPopupWidgetId, kGraphicPanelsPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadStartScaleEditBoxWidgetID, kGraphicPanelsPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadStartScaleNudgeWidgetID, kGraphicPanelsPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadEndScaleEditBoxWidgetID, kGraphicPanelsPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadEndScaleNudgeWidgetID, kGraphicPanelsPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace, kStrokeSeparator3WidgetID, kGraphicPanelsPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace, kStrokeSubPanel4Id, kGraphicPanelsPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace, kScaleTextWidgetId, kGraphicPanelsPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace, kConstrainArrowHeadScaleWidgetID, kGraphicPanelsPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace, kAlignArrowHeadStaticTextWidgetID, kGraphicPanelsPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadSwapIconWidgetID, kGraphicPanelsPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadAlignClusterWidgetId, kGraphicPanelsPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadAlignOutsideIconWidgetID, kGraphicPanelsPrefix2 + 82)
DECLARE_PMID(kWidgetIDSpace, kArrowHeadAlignInsideIconWidgetID, kGraphicPanelsPrefix2 + 83)
DECLARE_PMID(kWidgetIDSpace, kStrokePopupWidgetId, kGraphicPanelsPrefix2 + 84)
DECLARE_PMID(kWidgetIDSpace, kStrokePopupMenuButtonWidgetID, kGraphicPanelsPrefix2 + 85)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kShowStrokeOptionsActionID, kGraphicPanelsPrefix + 1)
DECLARE_PMID(kActionIDSpace, kStrokeWeightAffectsBoundingBoxActionID, kGraphicPanelsPrefix + 2)
DECLARE_PMID(kActionIDSpace, kStrokePanelActionID, kGraphicPanelsPrefix + 3)
DECLARE_PMID(kActionIDSpace, kAttributesPanelActionID, kGraphicPanelsPrefix + 4)
DECLARE_PMID(kActionIDSpace, kCornerShapeActionID, kGraphicPanelsPrefix + 5)
DECLARE_PMID(kActionIDSpace, kCornerShapeSepActionID, kGraphicPanelsPrefix + 6)
DECLARE_PMID(kActionIDSpace, kPathCornerShapeSepActionID, kGraphicPanelsPrefix + 7)
DECLARE_PMID(kActionIDSpace, kGraphicCornerShapeSepActionID, kGraphicPanelsPrefix + 8)
DECLARE_PMID(kActionIDSpace, kTextCornerShapeSepActionID, kGraphicPanelsPrefix + 9)

// ---- Moved from Scotch Rules plug-in
DECLARE_PMID(kActionIDSpace, kNewStripedPathStrokerActionID, kGraphicPanelsPrefix + 10)
// ---- end move.

// ---- Moved from Graphic Styles plug-in
DECLARE_PMID(kActionIDSpace, kToggleFillAndStrokeActionID, kGraphicPanelsPrefix +	11)
DECLARE_PMID(kActionIDSpace, kSwapFillAndStrokeActionID, kGraphicPanelsPrefix +	12)
DECLARE_PMID(kActionIDSpace, kApplyDefaultFillAndStrokeActionID, kGraphicPanelsPrefix +	13)
DECLARE_PMID(kActionIDSpace, kApplyCurrentColorToolActionID, kGraphicPanelsPrefix +	14)
DECLARE_PMID(kActionIDSpace, kApplyCurrentGradientToolActionID, kGraphicPanelsPrefix +	15)
DECLARE_PMID(kActionIDSpace, kClearFillStrokeToolActionID, kGraphicPanelsPrefix +	16)
DECLARE_PMID(kActionIDSpace, kToggleTextAndObjectActionID, kGraphicPanelsPrefix +	17)
// ---- end move.
DECLARE_PMID(kActionIDSpace, kObjectExportOptionsActionID, kGraphicPanelsPrefix + 18)


// epub-type
DECLARE_PMID(kActionIDSpace, kETCoverActionID, kGraphicPanelsPrefix + 19)
DECLARE_PMID(kActionIDSpace, kETFrontmatterActionID, kGraphicPanelsPrefix + 20)
DECLARE_PMID(kActionIDSpace, kETBodymatterActionID, kGraphicPanelsPrefix + 21)
DECLARE_PMID(kActionIDSpace, kETBackmatterActionID, kGraphicPanelsPrefix + 22)

DECLARE_PMID(kActionIDSpace, kETVolumeActionID, kGraphicPanelsPrefix + 23)
DECLARE_PMID(kActionIDSpace, kETPartActionID, kGraphicPanelsPrefix + 24)
DECLARE_PMID(kActionIDSpace, kETChapterActionID, kGraphicPanelsPrefix + 25)
DECLARE_PMID(kActionIDSpace, kETSubchapterActionID, kGraphicPanelsPrefix + 26)
DECLARE_PMID(kActionIDSpace, kETDivisionActionID, kGraphicPanelsPrefix + 27)


DECLARE_PMID(kActionIDSpace, kETForewordActionID, kGraphicPanelsPrefix + 28)
DECLARE_PMID(kActionIDSpace, kETPrefaceActionID, kGraphicPanelsPrefix + 29)
DECLARE_PMID(kActionIDSpace, kETPrologueActionID, kGraphicPanelsPrefix + 30)
DECLARE_PMID(kActionIDSpace, kETIntroductionActionID, kGraphicPanelsPrefix + 31)
DECLARE_PMID(kActionIDSpace, kETPreambleActionID, kGraphicPanelsPrefix + 32)
DECLARE_PMID(kActionIDSpace, kETConclusionActionID, kGraphicPanelsPrefix + 33)
DECLARE_PMID(kActionIDSpace, kETEpilogueActionID, kGraphicPanelsPrefix + 34)
DECLARE_PMID(kActionIDSpace, kETAfterwordActionID, kGraphicPanelsPrefix + 35)
DECLARE_PMID(kActionIDSpace, kETEpigraphActionID, kGraphicPanelsPrefix + 36)
DECLARE_PMID(kActionIDSpace, kETNoticeActionID, kGraphicPanelsPrefix + 37)
//DECLARE_PMID(kActionIDSpace, kETWarningActionID, kGraphicPanelsPrefix + 38)

DECLARE_PMID(kActionIDSpace, kETTocActionID, kGraphicPanelsPrefix + 39)
//DECLARE_PMID(kActionIDSpace, kETLoaActionID, kGraphicPanelsPrefix + 40)
DECLARE_PMID(kActionIDSpace, kETLoiActionID, kGraphicPanelsPrefix + 41)
DECLARE_PMID(kActionIDSpace, kETLotActionID, kGraphicPanelsPrefix + 42)
//DECLARE_PMID(kActionIDSpace, kETLovActionID, kGraphicPanelsPrefix + 43)
DECLARE_PMID(kActionIDSpace, kETAppendixActionID, kGraphicPanelsPrefix + 44)
DECLARE_PMID(kActionIDSpace, kETIndexActionID, kGraphicPanelsPrefix + 45)
DECLARE_PMID(kActionIDSpace, kETColophonActionID, kGraphicPanelsPrefix + 46)
DECLARE_PMID(kActionIDSpace, kETLandmarksActionID, kGraphicPanelsPrefix + 47)
DECLARE_PMID(kActionIDSpace, kETGlossaryActionID, kGraphicPanelsPrefix + 48)
DECLARE_PMID(kActionIDSpace, kETGlosstermActionID, kGraphicPanelsPrefix + 49)
DECLARE_PMID(kActionIDSpace, kETGlossdefActionID, kGraphicPanelsPrefix + 50)
DECLARE_PMID(kActionIDSpace, kETBibliographyActionID, kGraphicPanelsPrefix + 51)
DECLARE_PMID(kActionIDSpace, kETBiblioentryActionID, kGraphicPanelsPrefix + 52)

DECLARE_PMID(kActionIDSpace, kETTitlepageActionID, kGraphicPanelsPrefix + 53)
DECLARE_PMID(kActionIDSpace, kETHalftitlepageActionID, kGraphicPanelsPrefix + 54)
DECLARE_PMID(kActionIDSpace, kETCopyrightpageActionID, kGraphicPanelsPrefix + 55)
DECLARE_PMID(kActionIDSpace, kETAcknowldegmentsActionID, kGraphicPanelsPrefix + 56)
DECLARE_PMID(kActionIDSpace, kETImprintActionID, kGraphicPanelsPrefix + 57)
DECLARE_PMID(kActionIDSpace, kETImprimaturActionID, kGraphicPanelsPrefix + 58)
DECLARE_PMID(kActionIDSpace, kETContributorsActionID, kGraphicPanelsPrefix + 59)
DECLARE_PMID(kActionIDSpace, kETOthercreditsActionID, kGraphicPanelsPrefix + 60)
DECLARE_PMID(kActionIDSpace, kETErrataActionID, kGraphicPanelsPrefix + 61)
DECLARE_PMID(kActionIDSpace, kETDedicationActionID, kGraphicPanelsPrefix + 62)
DECLARE_PMID(kActionIDSpace, kETRevisionhistoryActionID, kGraphicPanelsPrefix + 63)

DECLARE_PMID(kActionIDSpace, kETHelpActionID, kGraphicPanelsPrefix + 64)
//DECLARE_PMID(kActionIDSpace, kETMarginaliaActionID, kGraphicPanelsPrefix + 65)
//DECLARE_PMID(kActionIDSpace, kETSidebarActionID, kGraphicPanelsPrefix + 66)

DECLARE_PMID(kActionIDSpace, kETHalftitleActionID, kGraphicPanelsPrefix + 67)
DECLARE_PMID(kActionIDSpace, kETFulltitleActionID, kGraphicPanelsPrefix + 68)
DECLARE_PMID(kActionIDSpace, kETCovertitleActionID, kGraphicPanelsPrefix + 69)
DECLARE_PMID(kActionIDSpace, kETTitleActionID, kGraphicPanelsPrefix + 70)
DECLARE_PMID(kActionIDSpace, kETSubtitleActionID, kGraphicPanelsPrefix + 71)
// gap
//DECLARE_PMID(kActionIDSpace, kETHeadingnumberActionID, kGraphicPanelsPrefix + 73)

DECLARE_PMID(kActionIDSpace, kETAssessmentActionID, kGraphicPanelsPrefix + 74)
// gap
//DECLARE_PMID(kActionIDSpace, kETPracticeActionID, kGraphicPanelsPrefix + 78)
//DECLARE_PMID(kActionIDSpace, kETPracticesActionID, kGraphicPanelsPrefix + 79)
//DECLARE_PMID(kActionIDSpace, kETQnaActionID, kGraphicPanelsPrefix + 80)
//DECLARE_PMID(kActionIDSpace, kETStandardActionID, kGraphicPanelsPrefix + 81)

//DECLARE_PMID(kActionIDSpace, kETAnnotationActionID, kGraphicPanelsPrefix + 82)
//DECLARE_PMID(kActionIDSpace, kETNoteActionID, kGraphicPanelsPrefix + 83)
DECLARE_PMID(kActionIDSpace, kETFootnoteActionID, kGraphicPanelsPrefix + 84)
DECLARE_PMID(kActionIDSpace, kETRearnoteActionID, kGraphicPanelsPrefix + 85)
DECLARE_PMID(kActionIDSpace, kETFootnotesActionID, kGraphicPanelsPrefix + 86)
DECLARE_PMID(kActionIDSpace, kETRearnotesActionID, kGraphicPanelsPrefix + 87)

//gap

//DECLARE_PMID(kActionIDSpace, kETFigureActionID, kGraphicPanelsPrefix + 100)


				
// Service IDs
DECLARE_PMID(kServiceIDSpace, kObjectExportOptionsDialogService, kGraphicPanelsPrefix + 1)

#endif // __GraphicPanelsID__
