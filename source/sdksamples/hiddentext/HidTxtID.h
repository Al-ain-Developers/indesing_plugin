//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtID.h $
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
//========================================================================================

#ifndef __HidTxtID_h__
#define __HidTxtID_h__

#include "SDKDef.h"

// Company:
#define kHidTxtCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kHidTxtCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kHidTxtPluginName	"HiddenText"			// Name of this plug-in.
#define kHidTxtPrefixNumber	0x670a0 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kHidTxtVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kHidTxtAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kHidTxtPrefixNumber above to modify the prefix.)
#define kHidTxtPrefix		RezLong(kHidTxtPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kHidTxtStringPrefix	SDK_DEF_STRINGIZE(kHidTxtPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kHidTxtMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kHidTxtMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kHidTxtPluginID, kHidTxtPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kHidTxtActionComponentBoss,	kHidTxtPrefix + 0)
//Obsoleted by InDesign CS: DECLARE_PMID(kClassIDSpace, kHidTxtStringRegisterBoss,	kHidTxtPrefix + 1)
//Obsoleted by InDesign CS: DECLARE_PMID(kClassIDSpace, kHidTxtMenuRegisterBoss,		kHidTxtPrefix + 2)
//Obsoleted by InDesign CS: DECLARE_PMID(kClassIDSpace, kHidTxtActionRegisterBoss,	kHidTxtPrefix + 3)
DECLARE_PMID(kClassIDSpace, kHidTxtAnchorTextAdornmentBoss,	kHidTxtPrefix + 4)

DECLARE_PMID(kClassIDSpace, kHidTxtModelBoss,	kHidTxtPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHidTxtTextModelMementoBoss,	kHidTxtPrefix + 7)
DECLARE_PMID(kClassIDSpace, kHidTxtModelCreateCmdBoss,	kHidTxtPrefix + 8)
DECLARE_PMID(kClassIDSpace, kHidTxtModelModifyTextCmdBoss,	kHidTxtPrefix + 9)
// TODO: DECLARE_PMID(kClassIDSpace, kHidTxtModelModifyStyleCmdBoss,	kHidTxtPrefix + 10)
DECLARE_PMID(kClassIDSpace, kHidTxtModelDeleteCmdBoss,	kHidTxtPrefix + 11)
DECLARE_PMID(kClassIDSpace, kHidTxtModelCopyCmdBoss,	kHidTxtPrefix + 12)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTMODEL,	kHidTxtPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTOWNEDITEMUIDDATA,	kHidTxtPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTTOSTORYUIDDATA,	kHidTxtPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTSHOWADORNMENTBOOLDATA,	kHidTxtPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTFACADE,	kHidTxtPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDTXTSUITE,	kHidTxtPrefix + 11)

// ImplementationIDs:

DECLARE_PMID(kImplementationIDSpace, kHidTxtModelImpl, kHidTxtPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHidTxtStoryThreadDictImpl,		kHidTxtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kHidTxtStoryThreadImpl,		kHidTxtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHidTxtOwnedItemImpl, kHidTxtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kHidTxtMementoImpl, kHidTxtPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kHidTxtParcelListImpl, kHidTxtPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kHidTxtParcelListDataImpl, kHidTxtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kHidTxtParcelListComposerImpl, kHidTxtPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kHidTxtModelCreateCmdImpl, kHidTxtPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kHidTxtModelModifyTextCmdImpl, kHidTxtPrefix + 11)
// TODO: DECLARE_PMID(kImplementationIDSpace, kHidTxtModelModifyStyleCmdImpl, kHidTxtPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kHidTxtModelDeleteCmdImpl, kHidTxtPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kHidTxtModelCopyCmdImpl,	kHidTxtPrefix + 14)

DECLARE_PMID(kImplementationIDSpace, kHidTxtFacadeImpl,	kHidTxtPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kHidTxtSuiteASBImpl,	kHidTxtPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kHidTxtSuiteTextCSBImpl,	kHidTxtPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kHidTxtAnchorTextAdornmentImpl,	kHidTxtPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kHidTxtSuiteTextCSBSelectionExtImpl, kHidTxtPrefix + 20)

// Command name string keys:
#define kHidTxtModelCreateCmdStringKey		kHidTxtStringPrefix "kHidTxtModelCreateCmdStringKey"
#define kHidTxtModelModifyTextCmdStringKey	kHidTxtStringPrefix "kHidTxtModelModifyTextCmdStringKey"
#define kHidTxtModelDeleteCmdStringKey		kHidTxtStringPrefix "kHidTxtModelDeleteCmdStringKey"
#define kHidTxtModelCopyCmdStringKey		kHidTxtStringPrefix "kHidTxtModelCopyCmdStringKey"

// Command sequence string keys:
#define kHidTxtCreateHiddenTextStringKey		kHidTxtStringPrefix "kHidTxtCreateHiddenTextStringKey"
#define kHidTxtModifyHiddenTextStringKey		kHidTxtStringPrefix "kHidTxtModifyHiddenTextStringKey"
#define kHidTxtDeleteHiddenTextStringKey		kHidTxtStringPrefix "kHidTxtDeleteHiddenTextStringKey"

#define kHidTxtStoryThreadDictKey 0

// Initial data format version numbers: the persistent data for this plug-in
// introduced in the InDesign 2.0 SDK
#define kHidTxtInitialMajorFormat		4
#define kHidTxtInitialMinorFormat		1

// Data format version numbers for the PluginVersion resource 
#define kHidTxtLastMajorFormatChange	kHidTxtInitialMajorFormat		// Most recent major format change
#define kHidTxtLastMinorFormatChange	kHidTxtInitialMinorFormat		// Most recent minor format change

#endif // __HidTxtID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, HidTxtID.h.


