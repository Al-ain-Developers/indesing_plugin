//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ServerSettingsID.h $
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
//  
//  Description: Declares an interface for setting global server state,
//  primarily for performance benefits.  
//  
//========================================================================================

#ifndef __ServerSettingsID__
#define __ServerSettingsID__

#include "SoapServerID.h"

// <Interface ID>
START_IDS()

DECLARE_PMID(kInterfaceIDSpace, IID_ISERVERSETTINGS,		kSoapServerIDPrefix + 255)

// <Class ID>
// ClassIDs
//DECLARE_PMID(kClassIDSpace, kServerPrefsScriptProviderBoss, 				kSoapServerIDPrefix + 100)

// <Implementation ID>

DECLARE_PMID(kImplementationIDSpace, kServerSettingsImpl,	kSoapServerIDPrefix + 255)

//
//Script Element IDs
//
DECLARE_PMID(kScriptInfoIDSpace,	kServerSettingsPropertyScriptElement, 				kSoapServerIDPrefix + 100)

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace,	kServerPrefsObjectScriptElement, 					kSoapServerIDPrefix + 101)

//Properties
//DECLARE_PMID(kScriptInfoIDSpace,	kConfigurationNamePropertyScriptElement, 			kSoapServerIDPrefix + 102)	// in AppFramework
DECLARE_PMID(kScriptInfoIDSpace,	kCreatePreviewsPropertyScriptElement, 				kSoapServerIDPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace,	kUseConsolePropertyScriptElement, 					kSoapServerIDPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace,	kIORFilePropertyScriptElement, 						kSoapServerIDPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace,	kUseEventLogPropertyScriptElement,					kSoapServerIDPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace,	kMaxErrorsPropertyScriptElement, 					kSoapServerIDPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace,	kPluginPathsPropertyScriptElement, 					kSoapServerIDPrefix + 108)
//DECLARE_PMID(kScriptInfoIDSpace,	kPortNumberPropertyScriptElement, 					kSoapServerIDPrefix + 109)	// in AppFramework
DECLARE_PMID(kScriptInfoIDSpace,	kSendCrashLogsPropertyScriptElement, 				kSoapServerIDPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace,	kServerObjectPropertyScriptElement, 				kSoapServerIDPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace,	kUseErrorListPropertyScriptElement, 				kSoapServerIDPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace,	kUseSEHPropertyScriptElement, 						kSoapServerIDPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace,	kAdminPortPropertyScriptElement, 					kSoapServerIDPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace,	kHostNamePropertyScriptElement, 					kSoapServerIDPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace,	kHeatbeatUpdateIntervalPropertyScriptElement, 		kSoapServerIDPrefix + 116)
END_IDS()

#ifndef RESOURCE_NUMBER	 //avoid errors in SoapServerID.fr

enum ServerPreferencesClasses
{
   c_ServerPrefs 		=		'sprC'
};

enum ServerPreferencesProperties
{
	p_ServerPrefs		=		'sprP',
//	p_PortNumber		=		'spPt',
	p_UseConsole		=		'spCo',
//	p_ConfigurationName	=		'spCN',
	p_UseErrorList		=		'spEL',
	p_UseSEH			=		'spSE',
	p_CreatePreviews	=		'spCP',
	p_SendCrashLogs		=		'spCL',
	p_UseEventLog		=		'spEv',
	p_IORFile			=		'spIO',
	p_PluginPaths		=		'spPP',
	p_MaxErrors			=		'spME',
	p_AdminPort			=		'aprt',
	p_HostName			=		'hnam',
};

// {7BF1624E-C892-441e-8468-EB8D48BD3D52}
#define kServerPrefs_CLSID { 0x7bf1624e, 0xc892, 0x441e, { 0x84, 0x68, 0xeb, 0x8d, 0x48, 0xbd, 0x3d, 0x52 } }

#endif

#endif
