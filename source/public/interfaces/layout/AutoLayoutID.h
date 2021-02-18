//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/AutoLayoutID.h $
//  
//  Owner: Rich Gartland
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
//  Contains IDs used by the AutoLayout plugin
//  
//========================================================================================

#ifndef __AutoLayoutID__
#define __AutoLayoutID__
#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kAutoLayoutPrefix	RezLong(0x7000) 


#define kMaxAutoSnapZone    12 
#define kMinFontSize		0.1
#define kMaxFontSize		1296

// PluginID
#define kAutoLayoutPluginName 		"Layout Adjustment"
DECLARE_PMID(kPlugInIDSpace, kAutoLayoutPluginID, kAutoLayoutPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kAutoLayoutBoss, kAutoLayoutPrefix + 1)
DECLARE_PMID(kClassIDSpace, kAutoLayoutCompoundCmdBoss, kAutoLayoutPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSetAutoLayoutPrefsCmdBoss, kAutoLayoutPrefix + 3)
DECLARE_PMID(kClassIDSpace, kALSpreadBoss, kAutoLayoutPrefix + 4)
DECLARE_PMID(kClassIDSpace, kALVerGuideBoss, kAutoLayoutPrefix + 5)
DECLARE_PMID(kClassIDSpace, kALHorGuideBoss, kAutoLayoutPrefix + 6)
DECLARE_PMID(kClassIDSpace, kALPageBoss, kAutoLayoutPrefix + 7)
DECLARE_PMID(kClassIDSpace, kALColumnBoss, kAutoLayoutPrefix + 8)
DECLARE_PMID(kClassIDSpace, kALPageItemBoss, kAutoLayoutPrefix + 9)
//gap
DECLARE_PMID(kClassIDSpace, kAutoLayoutStartupShutdownBoss, kAutoLayoutPrefix + 11)
DECLARE_PMID(kClassIDSpace, kAutoLayoutNewDocResponderBoss, kAutoLayoutPrefix + 12)
DECLARE_PMID(kClassIDSpace, kAutoLayoutOpenDocResponderBoss, kAutoLayoutPrefix + 13)
DECLARE_PMID(kClassIDSpace, kAutoLayoutConversionProviderBoss, kAutoLayoutPrefix + 14)

DECLARE_PMID(kClassIDSpace, kLayoutAdjustPrefsScriptProviderBoss, kAutoLayoutPrefix + 15)			//jwb 4/30/02 Moved from ScriptingID.h
DECLARE_PMID(kClassIDSpace, kSetAdaptiveLayoutPrefsCmdBoss, kAutoLayoutPrefix + 16)
DECLARE_PMID(kClassIDSpace, kAdaptiveLayoutPrefsScriptProviderBoss, kAutoLayoutPrefix + 17)
DECLARE_PMID(kClassIDSpace, kAdaptiveLayoutScriptMethodsProviderBoss, kAutoLayoutPrefix + 18)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOLAYOUTPREFERENCES, kAutoLayoutPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOLAYOUTPREFSCMDDATA, kAutoLayoutPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOLAYOUTCOLUMNSHANDLER, kAutoLayoutPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOLAYOUTPAGESIZEHANDLER, kAutoLayoutPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOLAYOUTAPPLYMSTRHANDLER, kAutoLayoutPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IALSPREAD, kAutoLayoutPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IALGUIDE, kAutoLayoutPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IALPAGE, kAutoLayoutPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IALCOLUMN, kAutoLayoutPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IALPAGEITEM, kAutoLayoutPrefix + 10)
// Not really Interfaces
DECLARE_PMID(kInterfaceIDSpace, IID_IALSAVEDSUBJECT, kAutoLayoutPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IALSAVEDOBSERVER, kAutoLayoutPrefix + 12)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTPREFERENCES, kAutoLayoutPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTPREFSCMDDATA, kAutoLayoutPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICANTRIGGERADAPTIVELAYOUT, kAutoLayoutPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTUTILS, kAutoLayoutPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUT, kAutoLayoutPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVETRANSFORM, kAutoLayoutPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVEHELPER, kAutoLayoutPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVECORE, kAutoLayoutPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVEDATA, kAutoLayoutPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVERESIZEONGOING, kAutoLayoutPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVEHIDDENITEMFOUND, kAutoLayoutPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVETRANSIENTDATA, kAutoLayoutPrefix + 26)


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutImpl, kAutoLayoutPrefix + 1 )
//DECLARE_PMID(kImplementationIDSpace, kFrameworkObserverImpl, kAutoLayoutPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kAutoLayoutServiceProviderImpl, kAutoLayoutPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutCompoundCmdImpl, kAutoLayoutPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCAutoLayoutPrefsImpl, kAutoLayoutPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDocAutoLayoutPrefsImpl, kAutoLayoutPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSessionAutoLayoutPrefsImpl, kAutoLayoutPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutPrefsCmdDataImpl, kAutoLayoutPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kSetAutoLayoutPrefsCmdImpl, kAutoLayoutPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutColumnsHandlerImpl, kAutoLayoutPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutPageSizeHandlerImpl, kAutoLayoutPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutApplyMstrHandlerImpl, kAutoLayoutPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kALSpreadImpl, kAutoLayoutPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kALSpreadRuleableImpl, kAutoLayoutPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kALVerGuideImpl, kAutoLayoutPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kALVerGuideRuleableImpl, kAutoLayoutPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kALHorGuideImpl, kAutoLayoutPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kALHorGuideRuleableImpl, kAutoLayoutPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kALPageImpl, kAutoLayoutPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kALPageRuleableImpl, kAutoLayoutPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kALColumnImpl, kAutoLayoutPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kALColumnRuleableImpl, kAutoLayoutPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kALPageItemImpl, kAutoLayoutPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kALPageItemRuleableImpl, kAutoLayoutPrefix + 24)
//gap
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutStartupShutdownImpl, kAutoLayoutPrefix + 26)
//DECLARE_PMID(kImplementationIDSpace, kAutoLayoutDocResponderImpl, kAutoLayoutPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kLayoutAdjustPrefsScriptProviderImpl, kAutoLayoutPrefix + 28)
//gap
DECLARE_PMID(kImplementationIDSpace, kCAdaptiveLayoutPrefsImpl, kAutoLayoutPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kDocAdaptiveLayoutPrefsImpl, kAutoLayoutPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSessionAdaptiveLayoutPrefsImpl, kAutoLayoutPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutPrefsCmdDataImpl, kAutoLayoutPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetAdaptiveLayoutPrefsCmdImpl, kAutoLayoutPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutUtilsImpl, kAutoLayoutPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutImpl, kAutoLayoutPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPageItemAdaptiveTransformImpl, kAutoLayoutPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kFrameItemAdaptiveTransformImpl, kAutoLayoutPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kImageItemAdaptiveTransformImpl, kAutoLayoutPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kGroupItemAdaptiveTransformImpl, kAutoLayoutPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kMultiStateObjectItemAdaptiveTransformImpl, kAutoLayoutPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kTableItemAdaptiveTransformImpl, kAutoLayoutPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kTOPItemAdaptiveTransformImpl, kAutoLayoutPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveHelperImpl, kAutoLayoutPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveCoreImpl, kAutoLayoutPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kInlineAdaptiveTransformImpl, kAutoLayoutPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kEPSItemAdaptiveTransformImpl, kAutoLayoutPrefix + 48)
//DECLARE_PMID(kImplementationIDSpace, kAdaptiveTransformDataImpl, kAutoLayoutPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutPrefsScriptProviderImpl, kAutoLayoutPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutScriptMethodsProviderImpl, kAutoLayoutPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kGuideItemAdaptiveTransformImpl, kAutoLayoutPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveTransientDataImpl, kAutoLayoutPrefix + 53)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kLayoutAdjustPrefsObjectScriptElement,				kAutoLayoutPrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kEnableLayoutAdjustPropertyScriptElement,			kAutoLayoutPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kLASnapZonePropertyScriptElement,					kAutoLayoutPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kLAAllowGraphicsResizePropertyScriptElement,		kAutoLayoutPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kLAAllowRulerGuidesMovePropertyScriptElement,		kAutoLayoutPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kLAIgnoreRulerGuideAlignmentsPropertyScriptElement,kAutoLayoutPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kLAIgnoreObjectLayerlocksPropertyScriptElement,	kAutoLayoutPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutAdjustPrefsPropertyScriptElement,			kAutoLayoutPrefix + 8)
//gap
//AdaptiveLayout scripting elements
DECLARE_PMID(kScriptInfoIDSpace, kAdaptiveLayoutPrefsObjectScriptElement,			kAutoLayoutPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kAdaptiveLayoutPrefsPropertyScriptElement,			kAutoLayoutPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kEnableAdaptiveLayoutPropertyScriptElement,		kAutoLayoutPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kALAdjustLockedObjectsPropertyScriptElement,		kAutoLayoutPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kALAdjustFontSizeAndLeadingPropertyScriptElement,	kAutoLayoutPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kALFontSizeLimitationPropertyScriptElement,		kAutoLayoutPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kALMinimumFontSizePropertyScriptElement,			kAutoLayoutPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kALMaximumFontSizePropertyScriptElement,			kAutoLayoutPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kAdjustLayoutMethodScriptElement,                  kAutoLayoutPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kEnableAutoAdjustMarginPropertyScriptElement,		kAutoLayoutPrefix + 19)

//Enums


//GUIDS
// {A207F3F4-A8AB-11d6-AA90-00C04F603A14}
#define kLayoutAdjustPref_CLSID { 0xa207f3f4, 0xa8ab, 0x11d6, { 0xaa, 0x90, 0x0, 0xc0, 0x4f, 0x60, 0x3a, 0x14 } }
// {A821DA08-7507-444A-BAB3-DFEE5F397ED4}
#define kAdaptiveLayoutPref_CLSID { 0xa821da08, 0x7507, 0x444a,{ 0xba, 0xb3, 0xdf, 0xee, 0x5f, 0x39, 0x7e, 0xd4 } }


//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kFrameworkObserverInvalHandlerID, kAutoLayoutPrefix + 1)

#endif // __AutoLayoutID__
