//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstID.h $
//  
//  Owner: Adobe Developer Technologies
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
//  Defines IDs used by the PstLst plug-in.
//  
//========================================================================================

#ifndef __PstLstID_h__
#define __PstLstID_h__

#include "SDKDef.h"

// Company:
#define kPstLstCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPstLstCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPstLstPluginName	"PersistentList"			// Name of this plug-in.
#define kPstLstPrefixNumber	0x58100 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPstLstVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPstLstAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPstLstPrefixNumber above to modify the prefix.)
#define kPstLstPrefix		RezLong(kPstLstPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPstLstStringPrefix	SDK_DEF_STRINGIZE(kPstLstPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kPstLstMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kPstLstMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

START_IDS()

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPstLstPluginID, kPstLstPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPstLstActionComponentBoss_obsolete,kPstLstPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPstLstStringRegisterBoss_obsolete,	kPstLstPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPstLstMenuRegisterBoss_obsolete,	kPstLstPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPstLstActionRegisterBoss_obsolete,	kPstLstPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPstLstPanelWidgetBoss_obsolete,	kPstLstPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPstLstPanelRegisterBoss_obsolete,	kPstLstPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPstLstDataBoss,					kPstLstPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPstLstNewDataCmdBoss,				kPstLstPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPstLstDialogBoss_obsolete,			kPstLstPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPstLstModifyDataCmdBoss,			kPstLstPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPstLstDeleteDataCmdBoss,			kPstLstPrefix + 11)
DECLARE_PMID(kClassIDSpace, kkPstLstSuiteRegisterBoss_obsolete, kPstLstPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPstLstDeletePageItemCmdBoss,		kPstLstPrefix + 13)
DECLARE_PMID(kClassIDSpace, kPstLstDocResponderBoss,			kPstLstPrefix + 14)
DECLARE_PMID(kClassIDSpace, kPstLstCloseDocResponderBoss_obsolete,	kPstLstPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPstLstOpenDocResponderBoss_obsolete,	kPstLstPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPstLstReferenceConverterBoss,		kPstLstPrefix + 17)
DECLARE_PMID(kClassIDSpace, kPstLstScriptProviderBoss,			kPstLstPrefix + 18)
DECLARE_PMID(kClassIDSpace, kPstLstErrorStringServiceBoss,		kPstLstPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPstLstConversionProviderBoss,		kPstLstPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPstLstPhase2ConversionResponderBoss,		kPstLstPrefix + 21)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IPSTLSTUIDLIST, 		kPstLstPrefix + 0)	
DECLARE_PMID(kInterfaceIDSpace, IID_IPSTLSTDATA, 			kPstLstPrefix + 1)	
DECLARE_PMID(kInterfaceIDSpace, IID_IPSTLST_ISUITE, 		kPstLstPrefix + 2)	
DECLARE_PMID(kInterfaceIDSpace, IID_IPSTLSTOBSERVER, 		kPstLstPrefix + 3)	

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPstLstActionComponentImpl_obsolete,	kPstLstPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPstLstDlgControllerImpl_obsolete,		kPstLstPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPstLstDlgObserverImpl_obsolete,		kPstLstPrefix + 2) 
DECLARE_PMID(kImplementationIDSpace, kPstLstUIDListImpl,					kPstLstPrefix + 3) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDataPersistImpl,				kPstLstPrefix + 4) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDataImpl,						kPstLstPrefix + 5) 
DECLARE_PMID(kImplementationIDSpace, kPstLstNewDataCmdImpl,					kPstLstPrefix + 6) 
DECLARE_PMID(kImplementationIDSpace, kPstLstASBImpl,						kPstLstPrefix + 7) 
DECLARE_PMID(kImplementationIDSpace, kPstLstLayoutCSBImpl,					kPstLstPrefix + 8) 
DECLARE_PMID(kImplementationIDSpace, kPstLstSelectionObserverImpl_obsolete,	kPstLstPrefix + 9) 
DECLARE_PMID(kImplementationIDSpace, kPstLstModifyDataCmdImpl,				kPstLstPrefix + 11) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDeleteDataCmdImpl,				kPstLstPrefix + 12) 
DECLARE_PMID(kImplementationIDSpace, kPstLstSuiteASBSelectionExtImpl,		kPstLstPrefix + 13) 
DECLARE_PMID(kImplementationIDSpace, kPstLstSuiteLayoutSelectionExtImpl,	kPstLstPrefix + 14) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDeletePageItemCmdImpl,			kPstLstPrefix + 15) 
DECLARE_PMID(kImplementationIDSpace, kPstLstNewDocResponderImpl_obsolete,	kPstLstPrefix + 16) 
DECLARE_PMID(kImplementationIDSpace, kPstLstCloseDocResponderImpl_obsolete,	kPstLstPrefix + 17) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDocObserverImpl,				kPstLstPrefix + 18) 
DECLARE_PMID(kImplementationIDSpace, kPstLstOpenDocResponderImpl_obsolete,	kPstLstPrefix + 19) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDocServiceProviderImpl,			kPstLstPrefix + 20) 
DECLARE_PMID(kImplementationIDSpace, kPstLstDocResponderImpl,				kPstLstPrefix + 21) 
DECLARE_PMID(kImplementationIDSpace, kPstLstReferenceConverterImpl,			kPstLstPrefix + 22) 
DECLARE_PMID(kImplementationIDSpace, kPstLstScriptImpl,						kPstLstPrefix + 23) 
DECLARE_PMID(kImplementationIDSpace, kPstLstScriptProviderImpl,				kPstLstPrefix + 24) 
DECLARE_PMID(kImplementationIDSpace, kPstLstErrorStringServiceImpl,			kPstLstPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kPstLstPhase2ConversionImpl,			kPstLstPrefix + 26) 

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPstLstAboutActionID_obsolete,			kPstLstPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPstLstPanelWidgetActionID_obsolete,	kPstLstPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPstLstSeparator1ActionID_obsolete,	kPstLstPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPstLstPopupAboutThisActionID_obsolete,kPstLstPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPstLstNewActionID_obsolete,			kPstLstPrefix + 11)
DECLARE_PMID(kActionIDSpace, kPstLstModifyActionID_obsolete,		kPstLstPrefix + 12)
DECLARE_PMID(kActionIDSpace, kPstLstDeleteActionID_obsolete,		kPstLstPrefix + 13)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPstLstPanelWidgetID_obsolete,			kPstLstPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kPstLstDialogWidgetID_obsolete,		kPstLstPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kPstLstListWidgetID_obsolete,			kPstLstPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kPstLstIconSuiteWidgetID_obsolete,		kPstLstPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kPstLstStaticTextWidgetID_obsolete,	kPstLstPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kPstLstEditBoxWidgetID_obsolete,		kPstLstPrefix + 5) 
DECLARE_PMID(kWidgetIDSpace, kPstLstLabelWidgetID_obsolete,			kPstLstPrefix + 6) 
DECLARE_PMID(kWidgetIDSpace, kPstLstListLabelWidgetID_obsolete,		kPstLstPrefix + 7) 
DECLARE_PMID(kWidgetIDSpace, kPstLstListBoxWidgetID_obsolete,		kPstLstPrefix + 8) 
DECLARE_PMID(kWidgetIDSpace, kPstLstListElementRsrcID_obsolete,		kPstLstPrefix + 9) 
DECLARE_PMID(kWidgetIDSpace, kPstLstListParentWidgetId_obsolete,	kPstLstPrefix + 10) 
DECLARE_PMID(kWidgetIDSpace, kPstLstTextWidgetID_obsolete,			kPstLstPrefix + 11) 
 
// ScriptIDs:
DECLARE_PMID(kScriptInfoIDSpace, kPstLstSuiteScriptElement, 	kPstLstPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kPstLstDataObjectScriptElement, 	kPstLstPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kPstLstDataCreateMethodScriptElement, 	kPstLstPrefix + 2)

// Error codes:
DECLARE_PMID(kErrorIDSpace, kPstLstScriptProviderPreconditionError, kPstLstPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kPstLstUnsupportedObjectRequestedError, kPstLstPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kPstLstInternalError, kPstLstPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPstLstItemNotFoundInParentError, kPstLstPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kPstListParentUIDListHasInsufficientNumberOfItemsError, kPstLstPrefix + 4)

END_IDS()

// Error string keys: 
#define kPstLstScriptProviderPreconditionErrorStringKey kPstLstStringPrefix "kPstLstScriptProviderPreconditionErrorStringKey"
#define kPstLstUnsupportedObjectRequestedErrorStringKey kPstLstStringPrefix "kPstLstUnsupportedObjectRequestedErrorStringKey"
#define kPstLstInternalErrorStringKey	kPstLstStringPrefix "kPstLstScriptErrorStringKey"
#define kPstLstItemNotFoundInParentErrorStringKey kPstLstStringPrefix "kPstLstItemNotFoundInParentErrorStringKey"
#define kPstListParentUIDListHasInsufficientNumberOfItemsErrorStringKey kPstLstStringPrefix "kPstListParentUIDListHasInsufficientNumberOfItemsErrorStringKey"

// Other StringKeys:
#define kPstLstNewStringKey			kPstLstStringPrefix "kPstLstNewStringKey"
#define kPstLstModifyStringKey		kPstLstStringPrefix "kPstLstModifyStringKey"
#define kPstLstDeleteStringKey		kPstLstStringPrefix "kPstLstDeleteStringKey"
#define kPstLstSelectStringKey		kPstLstStringPrefix	"kPstLstSelectStringKey"
//#define kPstLstStaticTextKey		kPstLstStringPrefix	"kPstLstStaticTextKey"
//#define kPstLstInternalPopupMenuNameKey		kPstLstStringPrefix	"kPstLstInternalPopupMenuNameKey"
//#define kPstLstTargetMenuPath kPstLstInternalPopupMenuNameKey
//#define kPstLstDataStaticTextKey					kPstLstStringPrefix	"kPstLstDataStaticTextKey"
#define kPstLstNoValidPageItemsSelectedKey			kPstLstStringPrefix	"kPstLstNoValidPageItemsSelectedKey"
//#define kPstLstNewCmdFailedKey			kPstLstStringPrefix	"kPstLstNewCmdFailedKey"
//#define kPstLstDeleteCmdFailedKey			kPstLstStringPrefix	"kPstLstDeleteCmdFailedKey"
//#define kPstLstModifyCmdFailedKey			kPstLstStringPrefix	"kPstLstModifyCmdFailedKey"
#define kPstLstDeleteItemCmdFailedKey			kPstLstStringPrefix	"kPstLstDeleteItemCmdFailedKey"
//#define kPstLstSelectCmdFailedKey			kPstLstStringPrefix	"kPstLstSelectCmdFailedKey"
//#define kPstLstLabelTextKey							kPstLstStringPrefix	"kPstLstLabelTextKey"
//#define kPstLstNoDataTextKey							kPstLstStringPrefix	"kPstLstNoDataTextKey"
//#define kPstLstListLabelTextKey							kPstLstStringPrefix	"kPstLstListLabelTextKey"

// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kPstLstInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kPstLstInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber

// InDesign CS2 format changes
// Added back reference(UID) to parent boss in PstLstDataPersist.cpp
#define kPstLstAddParentReferenceUIDMajorFormat		kSDKDef_40_PersistMajorVersionNumber
#define kPstLstAddParentReferenceUIDMinorFormat		1

// InDesign CS3 format changes
// Remove selectedUID from PstLstUIDList.cpp
#define kRemoveSelectedUIDMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kRemoveSelectedUIDMinorFormat		1

#define kPstLstStoreWideStringMajorFormat	kRemoveSelectedUIDMajorFormat
#define kPstLstStoreWideStringMinorFormat	2

// Format IDs for the PluginVersion resource 
#define kPstLstLastMajorFormatChange	kPstLstStoreWideStringMajorFormat // Last major format change
#define kPstLstLastMinorFormatChange	kPstLstStoreWideStringMinorFormat // Last minor format change

// Resource IDs for the UserErrorTable resource 
#define kPstLstErrorStringTableRsrcID	 kSDKDefErrorStringResourceID

// default persistent list data item value
#define kPstLstDataItemNameDefault ""

#endif // __PstLstID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PstLstID.h.


