//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunID.h $
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
//  Defines IDs used by the SnipRun plug-in.
//  
//========================================================================================

#ifndef __SnipRunID_h__
#define __SnipRunID_h__

#include "SDKDef.h"
#include "SnipRunRezDefs.h"

// Company:
#define kSnipRunCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kSnipRunCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kSnipRunPluginName	"SnippetRunner"			// Name of this plug-in.
#define kSnipRunPrefixNumber	0x5D500 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kSnipRunVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kSnipRunAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kSnipRunPrefixNumber above to modify the prefix.)
#define kSnipRunPrefix		RezLong(kSnipRunPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kSnipRunStringPrefix	SDK_DEF_STRINGIZE(kSnipRunPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
START_IDS()
DECLARE_PMID(kPlugInIDSpace, kSnipRunPluginID, kSnipRunPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kSnipRunActionComponentBoss,	kSnipRunPrefix + 0)
DECLARE_PMID(kClassIDSpace, kSnipRunStringRegisterBoss,	kSnipRunPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSnipRunMenuRegisterBoss,		kSnipRunPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSnipRunActionRegisterBoss,	kSnipRunPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSnipRunPanelWidgetBoss,		kSnipRunPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSnipRunPanelRegisterBoss,	kSnipRunPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSnipRunTipsRegisterBoss,	kSnipRunPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSnipRunDialogBoss,		kSnipRunPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSnipRunGoButtonBoss,		kSnipRunPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSnipRunRestoreLogCmdBoss,		kSnipRunPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSnipRunScriptProviderBoss, 	kSnipRunPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSnpRunnableScriptObjectBoss, 	kSnipRunPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSnpRunnableScriptProviderBoss, 	kSnipRunPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSnpRunErrorStringServiceBoss, 	kSnipRunPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSnipRunStartupShutdownBoss, 	kSnipRunPrefix + 25)
DECLARE_PMID(kClassIDSpace, kSnippetRunnerQuickApplyServiceBoss, 	kSnipRunPrefix + 26)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNSUITE, kSnipRunPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNPRUNNABLECONTEXT, kSnipRunPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNDIALOGDATA, kSnipRunPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNGOBUTTONOBSERVER, kSnipRunPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNGOSELECTIONOBSERVER, kSnipRunPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNSNIPPETNAMESTRINGDATA, kSnipRunPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNPARAMETERUTILS, kSnipRunPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNPANELVISIBILITY, kSnipRunPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPRUNPANELTRACEMODE, kSnipRunPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETNAME, kSnipRunPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETCATEGORIES, kSnipRunPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETDESCRIPTION, kSnipRunPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETPRECONDITIONS, kSnipRunPrefix + 25)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kSnipRunActionComponentImpl,		kSnipRunPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kSnipRunPanelWidgetObserverImpl,	kSnipRunPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSnipRunControlViewImpl,	kSnipRunPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSnipRunSuiteASBImpl, kSnipRunPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSnipRunSuiteCSBImpl, kSnipRunPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSnpRunnableContextCSBImpl, kSnipRunPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSnipRunDialogControllerImpl,		kSnipRunPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSnipRunDialogDataImpl,			kSnipRunPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSnipRunGoSelectionObserverImpl,			kSnipRunPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSnipRunGoButtonObserverImpl,			kSnipRunPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSnipRunParameterUtilsImpl,			kSnipRunPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSnipRunRestoreLogCmdImpl,			kSnipRunPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSnipRunScriptProviderImpl, 	kSnipRunPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSnpRunnableScriptImpl, 	kSnipRunPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSnpRunnableScriptProviderImpl, 	kSnipRunPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSnippetNameDataImpl, 	kSnipRunPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSnippetCategoriesDataImpl, 	kSnipRunPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSnippetDescriptionDataImpl, 	kSnipRunPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSnippetPreconditionsDataImpl, 	kSnipRunPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSnipRunErrorStringServiceImpl, 	kSnipRunPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSnipRunStartupShutdownImpl, 	kSnipRunPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSnippetRunnerQuickApplyServiceImpl, 	kSnipRunPrefix + 30)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kSnipRunAboutActionID,				kSnipRunPrefix + 0)
DECLARE_PMID(kActionIDSpace, kSnipRunPanelWidgetActionID,			kSnipRunPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSnipRunSeparator1ActionID,			kSnipRunPrefix + 2)
DECLARE_PMID(kActionIDSpace, kSnipRunPopupAboutThisActionID,		kSnipRunPrefix + 3)
DECLARE_PMID(kActionIDSpace, kSnipRunShowParameterBoxActionID,		kSnipRunPrefix + 12)
DECLARE_PMID(kActionIDSpace, kSnippetRunnerQuickApplyActionID,		kSnipRunPrefix + 13)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kSnipRunPanelWidgetID,				kSnipRunPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kSnipRunNameWidgetID,				kSnipRunPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kSnipRunSynopsisWidgetID,			kSnipRunPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kSnipRunParametersWidgetID,		kSnipRunPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSnipRunPreconditionsWidgetID,			kSnipRunPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kSnipRunGoWidgetID,				kSnipRunPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kSnipRunLogWidgetID,				kSnipRunPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSnipRunLogScrollBarWidgetID,		kSnipRunPrefix + 7)    
DECLARE_PMID(kWidgetIDSpace, kSnipRunClearLogWidgetID,			kSnipRunPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kSnipRunSaveLogWidgetID,			kSnipRunPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kSnipRunSnippetControlSubPanelWidgetID,	kSnipRunPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kSnipRunLogSubPanelWidgetID,		kSnipRunPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSnipRunLogControlStripWidgetID,	kSnipRunPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSnipRunTraceLogWidgetID,			kSnipRunPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kSnipRunHelpWidgetID,				kSnipRunPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSnipRunDialogWidgetID, 			kSnipRunPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSnipRunParamPromptWidgetID, 		kSnipRunPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kSnipRunParamTypeInfoWidgetID, 		kSnipRunPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kSnipRunStringParamWidgetID, 		kSnipRunPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kSnipRunIntParamWidgetID, 			kSnipRunPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSnipRunRealParamWidgetID, 		kSnipRunPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kSnipRunChoiceParamWidgetID, 		kSnipRunPrefix + 21)

// ScriptInfoIDs - SnippetRunner 
// (NOTE: These are different from the one provided with InDesign CS online training session 16)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunClearSnipLogMethodScriptElement, 		kSnipRunPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunGetSnipLogMethodScriptElement, 		kSnipRunPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunIsSnippetRegisteredMethodScriptElement, 		kSnipRunPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunObjectScriptElement, 		kSnipRunPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunObjectPropertyScriptElement, kSnipRunPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunPanelVisibilityEnumScriptElement, 		kSnipRunPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunPanelVisibilityPropertyScriptElement, 		kSnipRunPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunSaveSnipLogMethodScriptElement, 		kSnipRunPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunSuiteScriptElement, 		kSnipRunPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunTraceModeEnumScriptElement, 		kSnipRunPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kSnipRunTraceModePropertyScriptElement, 		kSnipRunPrefix + 10)
// ScriptInfoIDs - Snippet
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableCanRunSnippetMethodScriptElement, 		kSnipRunPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableCategoriesPropertyScriptElement, 		kSnipRunPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableDescriptionPropertyScriptElement, 		kSnipRunPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableNamePropertyScriptElement, 		kSnipRunPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableObjectScriptElement, 		kSnipRunPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnablePreconditionsPropertyScriptElement, 		kSnipRunPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableRunSnippetMethodScriptElement, 		kSnipRunPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kSnpRunnableSetupContextMethodScriptElement, 		kSnipRunPrefix + 18)

// ErrorCodes:
DECLARE_PMID(kErrorIDSpace, kSnipRunSnippetNotFoundErrorCode, kSnipRunPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kSnipRunEOFErrorCode, kSnipRunPrefix + 1)
// (NOTE: These are different from the one provided with InDesign CS online training session 16)
DECLARE_PMID(kErrorIDSpace, kSnipRunInvalidFilePathForSaveSnipLogErrorCode, kSnipRunPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kSnipRunCannotRunSnippetErrorCode, kSnipRunPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kSnipRunInvalidOperationWhenPanelIsInvisibleErrorCode, kSnipRunPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kSnipRunInternalError, kSnipRunPrefix + 5)

END_IDS()


// "About Plug-ins" sub-menu:
#define kSnipRunAboutMenuKey			kSnipRunStringPrefix "kSnipRunAboutMenuKey"
#define kSnipRunAboutMenuPath			kSDKDefStandardAboutMenuPath kSnipRunCompanyKey

// "Plug-ins" sub-menu:
#define kSnipRunPluginsMenuKey 		kSnipRunStringPrefix "kSnipRunPluginsMenuKey"
#define kSnipRunPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kSnipRunCompanyKey kSDKDefDelimitMenuPath kSnipRunPluginsMenuKey

// Menu item keys:
#define kSnipRunRunSnippetMenuItemKey		kSnipRunStringPrefix "kSnipRunRunSnippetMenuItemKey"
#define kSnipRunShowParameterBoxMenuItemKey		kSnipRunStringPrefix "kSnipRunShowParameterBoxMenuItemKey"
#define kSnipRunListSnippetsMenuItemKey		kSnipRunStringPrefix "kSnipRunListSnippetsMenuItemKey"

// Other StringKeys:
#define kSnipRunAboutBoxStringKey				kSnipRunStringPrefix "kSnipRunAboutBoxStringKey"
#define kSnipRunPanelTitleKey					kSnipRunStringPrefix	"kSnipRunPanelTitleKey"
#define kSnipRunStaticTextKey					kSnipRunStringPrefix	"kSnipRunStaticTextKey"
#define kSnipRunInternalPopupMenuNameKey		kSnipRunStringPrefix	"kSnipRunInternalPopupMenuNameKey"
#define kSnipRunTargetMenuPath kSnipRunInternalPopupMenuNameKey

#define kSnipRunNameStringKey kSnipRunStringPrefix "kSnipRunNameStringKey"
#define kSnipRunPreconditionsStringKey kSnipRunStringPrefix "kSnipRunPreconditionsStringKey"
#define kSnipRunParametersStringKey kSnipRunStringPrefix "kSnipRunParametersStringKey"
#define kSnipRunGoStringKey kSnipRunStringPrefix "kSnipRunGoStringKey"
#define kSnipRunLogStringKey kSnipRunStringPrefix "kSnipRunLogStringKey"
#define kSnipRunTraceLogStringKey kSnipRunStringPrefix "kSnipRunTraceLogStringKey"
#define kSnipRunGoTipStringKey kSnipRunStringPrefix "kSnipRunGoTipStringKey"
#define kSnipRunNameTipStringKey kSnipRunStringPrefix "kSnipRunNameTipStringKey"
#define kSnipRunPreconditionsTipStringKey kSnipRunStringPrefix "kSnipRunPreconditionsTipStringKey"
#define kSnipRunParametersTipStringKey kSnipRunStringPrefix "kSnipRunParametersTipStringKey"
#define kSnipRunLogTipStringKey kSnipRunStringPrefix "kSnipRunLogTipStringKey"
#define kSnipRunHelpTipStringKey kSnipRunStringPrefix "kSnipRunHelpTipStringKey"
#define kSnipRunTraceTipStringKey kSnipRunStringPrefix "kSnipRunTraceTipStringKey"
#define kSnipRunClearLogTipStringKey kSnipRunStringPrefix "kSnipRunClearLogTipStringKey"
#define kSnipRunSaveLogTipStringKey kSnipRunStringPrefix "kSnipRunSaveLogTipStringKey"
#define kSnipRunFamilyStringKey kSnipRunStringPrefix "kSnipRunFamilyStringKey"
#define kSnipRunDefaultFilenameStringKey kSnipRunStringPrefix "kSnipRunDefaultFilenameStringKey"
#define kSnipRunSaveDialogNameStringKey kSnipRunStringPrefix "kSnipRunSaveDialogNameStringKey"
#define kSnipRunSaveLogFailedStringKey kSnipRunStringPrefix "kSnipRunSaveLogFailedStringKey"

#define kSnipRunDialogTitleKey kSnipRunStringPrefix "kSnipRunDialogTitleKey"

#define kSnipRunSnippetNotFoundErrorCodeKey kSnipRunStringPrefix "kSnipRunSnippetNotFoundErrorCodeKey"
#define kSnipRunEOFErrorCodeKey kSnipRunStringPrefix "kSnipRunEOFErrorCodeKey"
#define kSnipRunCannotRunSnippetErrorCodeKey kSnipRunStringPrefix "kSnipRunCannotRunSnippetErrorCodeKey"
#define kSnipRunInvalidOperationWhenPanelIsInvisibleErrorCodeKey kSnipRunStringPrefix "kSnipRunInvalidOperationWhenPanelIsInvisibleErrorCodeKey"
#define kSnipRunInternalErrorStringKey kSnipRunStringPrefix "kSnipRunInternalErrorStringKey"
#define kSnipRunQuickApplyFilterKey kSnipRunStringPrefix "kSnipRunQuickApplyFilterKey"
#define kSnipRunQuickApplyNameKey kSnipRunStringPrefix "kSnipRunQuickApplyNameKey"


#define kSnipRunDefaultSnippetName "CreateDocument"
#define kSnipRunDefaultSnippetParameters "612 792 1 1"
#define kSnipRunHelloCSXSMessage	"kSnipRunHelloCSXSMessage"

// Menu item positions: 
#define kSnipRunShowParameterBoxMenuItemPosition			1.0	
#define	kSnipRunSeparator1MenuItemPosition			10.0
#define kSnipRunAboutThisMenuItemPosition			11.0

// Initial data format version numbers
#define kSnipRunFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kSnipRunFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kSnipRunCurrentMajorFormatNumber kSnipRunFirstMajorFormatNumber // most recent major format change
#define kSnipRunCurrentMinorFormatNumber kSnipRunFirstMinorFormatNumber // most recent minor format change

#endif // __SnipRunID_h__

// End, SnipRunID.h.
