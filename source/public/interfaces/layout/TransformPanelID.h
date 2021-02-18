//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/TransformPanelID.h $
//  
//  Owner: Richard Rodseth
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
//  Purpose:	IDs for Transform Panel
//  
//========================================================================================

#ifndef __TransformPanelID__
#define __TransformPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTransformPanelPrefix	RezLong(0x7600)

// <Start IDC>
// PluginID
#define kTransformPanelPluginName	 			"Transform Panel"
DECLARE_PMID(kPlugInIDSpace, kTransformPanelPluginID, kTransformPanelPrefix + 1)

// <Class ID>
// ClassIDs

DECLARE_PMID(kClassIDSpace, kTransformPanelBoss, kTransformPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTransformControlSetBoss, kTransformPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kFlipRotateControlSetBoss, kTransformPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTransformPanelMenuComponentBoss, kTransformPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTPProxyWidgetBoss, kTransformPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kHorizontalLocationEditBoxBoss, kTransformPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kVerticalLocationEditBoxBoss, kTransformPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kHorizontalSizeEditBoxBoss, kTransformPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kVerticalSizeEditBoxBoss, kTransformPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kChildAngleEditBoxBoss, kTransformPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kChildPercentageWidthEditBoxBoss, kTransformPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kTransformXYWHControlSetBoss, kTransformPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kGeometryPanelWidgetBoss, kTransformPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kTransformationsPanelWidgetBoss, kTransformPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kTransformXFormControlSetBoss, kTransformPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kAngleComboBoxBoss, kTransformPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTransformPanelScaleHeightComboBoxBoss, kTransformPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kControlStripTransformRegisterBoss, kTransformPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kControlStripMiniTransformRegisterBoss, kTransformPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kTransformStateBoss, kTransformPanelPrefix + 20)
//gap
DECLARE_PMID(kClassIDSpace, kChildPercentageHeightEditBoxBoss, kTransformPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kTransformPanelScaleWidthComboBoxBoss, kTransformPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kTransformPageSizePresetControlSetBoss, kTransformPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kControlStripSpreadTransformRegisterBoss, kTransformPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kTransformOrientationControlSetBoss, kTransformPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kTransformPanelPPIComboBoxBoss, kTransformPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPropertiesPanelTransformPanelBoss, kTransformPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kPropertiesPanelTransformExpandedBoss, kTransformPanelPrefix + 29)


// <Interface ID>
// IIDs

DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELVALUES, kTransformPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTERNATETEXTVALUE, kTransformPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIMENSIONVALUES, kTransformPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMVALUES, kTransformPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IADJUSTEDVALUE, kTransformPanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELSELECTIONOBSERVER, kTransformPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELXYWHEDITBOXOBSERVER, kTransformPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELREFERENCEPOINTOBSERVER, kTransformPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELSPREADOBSERVER, kTransformPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELPREFSOBSERVER, kTransformPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELXFORMEDITBOXOBSERVER, kTransformPanelPrefix + 12)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBERATTRIBUTES, kTransformPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMSTATETEXTCONTROLDATA, kTransformPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ITPCONTROLMANAGER, kTransformPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ITPDRAGDROPOBSERVER, kTransformPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPTRANSFORMPANELSUITE, kTransformPanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPMINITRANSFORMPANELSUITE, kTransformPanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMSTATEDATA, kTransformPanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPSPREADTRANSFORMPANELSUITE, kTransformPanelPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELPAGESIZEDDOBSERVER, kTransformPanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELORIENTATIONOBSERVER, kTransformPanelPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPANELORIENTATIONSELOBSERVER, kTransformPanelPrefix + 24)


// <Implementation ID>
// Implementation IIDs

// gap
DECLARE_PMID(kImplementationIDSpace, kTransformPanelMenuComponentImpl, kTransformPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTransformStateEHImpl, kTransformPanelPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kProxyViewEventHandlerImpl, kTransformPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMouseInfoThreadImpl, kTransformPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kHorizontalLocationValueImpl, kTransformPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kVerticalLocationValueImpl, kTransformPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kHorizontalSizeValueImpl, kTransformPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kVerticalSizeValueImpl, kTransformPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPercentageValueImpl, kTransformPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kAngleValueImpl, kTransformPanelPrefix + 13)

DECLARE_PMID(kImplementationIDSpace, kTransformPanelValuesImpl, kTransformPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kFlipRotateObserverImpl, kTransformPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDimensionValuesImpl, kTransformPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTransformValuesImpl, kTransformPanelPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kTransformPanelSelectionObserverImpl, kTransformPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelXYWHEditBoxObserverImpl, kTransformPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelPrefsObserverImpl, kTransformPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelSpreadObserverImpl, kTransformPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelReferencePointObserverImpl, kTransformPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelXFormEditBoxObserverImpl, kTransformPanelPrefix + 23)
// gap
DECLARE_PMID(kImplementationIDSpace, kNumberAttributesImpl, kTransformPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kProxyWidgetAttributesImpl, kTransformPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCAdjustedValueImpl, kTransformPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kTPControlManagerImpl, kTransformPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kTPDropTargetCallBackImpl, kTransformPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kTransformStateTipImpl, kTransformPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTPDragDropObserverImpl, kTransformPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTPAngleCBAttributesImpl, kTransformPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTPAngleNudgeObserverImpl, kTransformPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTPPercentageHeightCBAttributesImpl, kTransformPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPPIValueImpl, kTransformPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelObserversImpl, kTransformPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kControlStripTransformRegisterImpl, kTransformPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kControlStripTransformSuiteImpl, kTransformPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kControlStripMiniTransformRegisterImpl, kTransformPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kControlStripMiniTransformSuiteImpl, kTransformPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelScaleTextValueImpl, kTransformPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kTransformStateViewImpl, kTransformPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kTransformStateDataImpl, kTransformPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTPPercentageWidthCBAttributesImpl, kTransformPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kControlStripSpreadTransformSuiteImpl, kTransformPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kControlStripSpreadTransformRegisterImpl, kTransformPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPageSizeDimensionValuesImpl, kTransformPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelPageSizeDDObserverImpl, kTransformPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelOrientationObserverImpl, kTransformPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTPOrientationSelectionObserverImpl, kTransformPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kTransformStateDebugPanoramaImpl, kTransformPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kTransformPanelPropPnlActiveKitImpl, kTransformPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kTransformExpandedPropPnlActiveKitImpl, kTransformPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kPropPnlExpandedTransformPnlObsImpl, kTransformPanelPrefix + 55)

// <Widget ID>
// Widget IDs

DECLARE_PMID(kWidgetIDSpace, kProxyWidgetID, kTransformPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kFlipRotateButtonsWidgetID, kTransformPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kXLocationNudgeWidgetID, kTransformPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kXLocationTextWidgetID, kTransformPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kXLocationStaticWidgetID, kTransformPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kRotateCWButtonWidgetID, kTransformPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kYLocationNudgeWidgetID, kTransformPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kYLocationTextWidgetID, kTransformPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kYLocationStaticWidgetID, kTransformPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kRotateCCWButtonWidgetID, kTransformPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kWidthNudgeWidgetID, kTransformPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kWidthTextWidgetID, kTransformPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kWidthStaticWidgetID, kTransformPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kFlipVerticalButtonWidgetID, kTransformPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kHeightNudgeWidgetID, kTransformPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kHeightTextWidgetID, kTransformPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kHeightStaticWidgetID, kTransformPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kFlipHorizontalButtonWidgetID, kTransformPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kRotateAngleNudgeWidgetID, kTransformPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kRotateAngleTextWidgetID, kTransformPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kRotateAngleIconWidgetID, kTransformPanelPrefix + 21)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPPITextWidgetID, kTransformPanelPrefix + 22)
#endif
DECLARE_PMID(kWidgetIDSpace, kSkewXNudgeWidgetID, kTransformPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kSkewXTextWidgetID, kTransformPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kSkewXIconWidgetID, kTransformPanelPrefix + 25)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPPINudgeWidgetID, kTransformPanelPrefix + 26)
#endif
DECLARE_PMID(kWidgetIDSpace, kScaleXNudgeWidgetID, kTransformPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kScaleXTextWidgetID, kTransformPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kScaleXStaticWidgetID, kTransformPanelPrefix + 29)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPPIStaticWidgetID, kTransformPanelPrefix + 30)
#endif
DECLARE_PMID(kWidgetIDSpace, kScaleYNudgeWidgetID, kTransformPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kScaleYTextWidgetID, kTransformPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kScaleYStaticWidgetID, kTransformPanelPrefix + 33)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPPIScaleStaticWidgetID, kTransformPanelPrefix + 34)
#endif
DECLARE_PMID(kWidgetIDSpace, kMoveDistanceNudgeWidgetID, kTransformPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kMoveDistanceTextWidgetID, kTransformPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kMoveDistanceStaticWidgetID, kTransformPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kTransformCursorInfoWidgetID, kTransformPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kMoveAngleNudgeWidgetID, kTransformPanelPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kMoveAngleTextWidgetID, kTransformPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kMoveAngleStaticWidgetID, kTransformPanelPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kTransPanelPanelWidgetID, kTransformPanelPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kLengthNudgeWidgetID, kTransformPanelPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kLengthTextWidgetID, kTransformPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kLengthStaticWidgetID, kTransformPanelPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kTransformPanelWidgetID, kTransformPanelPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kTransXYWHPanelWidgetID, kTransformPanelPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kTransRotateScalePanelWidgetID, kTransformPanelPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kGeometryPanelWidgetID, kTransformPanelPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kTransformationsPanelWidgetID, kTransformPanelPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kTransXLocPanelWidgetID, kTransformPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kTransYLocPanelWidgetID, kTransformPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kTransWidthPanelWidgetID, kTransformPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kTransLengthPanelWidgetID, kTransformPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kTransHeightPanelWidgetID, kTransformPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kTransSeperatorWidgetID, kTransformPanelPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kTransTransPanelWidgetID, kTransformPanelPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kTransRotatePanelWidgetID, kTransformPanelPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kTransSkewPanelWidgetID, kTransformPanelPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kTransScaleXPanelWidgetID, kTransformPanelPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kTransScaleYPanelWidgetID, kTransformPanelPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kXContentOffsetStaticWidgetID, kTransformPanelPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kYContentOffsetStaticWidgetID, kTransformPanelPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kTransXLoc2PanelWidgetID, kTransformPanelPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kTransYLoc2PanelWidgetID, kTransformPanelPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kTransWidth2PanelWidgetID, kTransformPanelPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kTransLength2PanelWidgetID, kTransformPanelPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kTransHeight2PanelWidgetID, kTransformPanelPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kTransTrans2PanelWidgetID, kTransformPanelPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kTransRotate2PanelWidgetID, kTransformPanelPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kTransSkew2PanelWidgetID, kTransformPanelPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kTransScaleX2PanelWidgetID, kTransformPanelPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kTransScaleY2PanelWidgetID, kTransformPanelPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kConstrainWidthHeightWidgetID, kTransformPanelPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kConstrainScaleXYWidgetID, kTransformPanelPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTransformStateWidgetID, kTransformPanelPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kTransPageSizePresetPanelWidgetID, kTransformPanelPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kTransPresetPopupWidgetID, kTransformPanelPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kTransPageOrientationPanelWidgetID, kTransformPanelPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kTransPageTallIconWidgetID, kTransformPanelPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kTransPageWideIconWidgetID, kTransformPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kTransformPanelLevel2WidgetID, kTransformPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kPageSelectionRangeComboBoxWidgetID, kTransformPanelPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kPageSelectionNewButtonWidgetID, kTransformPanelPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kPageSelectionDeleteButtonWidgetID, kTransformPanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kMarginsColumnsButtonWidgetID, kTransformPanelPrefix + 86)

#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kTransPPIPanelWidgetID, kTransformPanelPrefix + 82)
#endif

// <Message ID>
// Messages moved to SpreadID.h

// <Action ID>
// Action IDs

DECLARE_PMID(kActionIDSpace, kShowTransformOptionsActionID, kTransformPanelPrefix + 1)
// gap
DECLARE_PMID(kActionIDSpace, kDisplaySpreadActionID, kTransformPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kDisplayParentActionID, kTransformPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kDisplayGlobalActionID, kTransformPanelPrefix + 8)
// gap
DECLARE_PMID(kActionIDSpace, kShowStrokeBoundsActionID, kTransformPanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kHorizontalPaletteActionID, kTransformPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kTransformPanelActionID, kTransformPanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kTransformSep1ActionID, kTransformPanelPrefix + 13)
DECLARE_PMID(kActionIDSpace, kTransformSep2ActionID, kTransformPanelPrefix + 14)
DECLARE_PMID(kActionIDSpace, kTransformSep3ActionID, kTransformPanelPrefix + 15)
// gap
DECLARE_PMID(kActionIDSpace, kShowContentOffsetActionID, kTransformPanelPrefix + 19)
DECLARE_PMID(kActionIDSpace, kScaleStrokesActionID, kTransformPanelPrefix + 20)
DECLARE_PMID(kActionIDSpace, kTransformSep0ActionID, kTransformPanelPrefix + 21)
DECLARE_PMID(kActionIDSpace, kScaleXPEffectsActionID, kTransformPanelPrefix + 22)
// gap

#endif // __TransformPanelID__




