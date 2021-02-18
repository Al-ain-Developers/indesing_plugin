//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartID.h $
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

#ifndef __CdlChartID_h__
#define __CdlChartID_h__

#include "SDKDef.h"

// Company:
#define kCdlChartCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCdlChartPluginName		"CandleChart"				// Name of this plug-in.
// ipaterso: prev prefix ID was incorrect, this is a registered and unique one
#define kCdlChartPrefixNumber	0xb7a00 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCdlChartVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCdlChartAuthor			"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCdlChartPrefixNumber above to modify the prefix.)
#define kCdlChartPrefix		RezLong(kCdlChartPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCdlChartStringPrefix	SDK_DEF_STRINGIZE(kCdlChartPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCdlChartMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCdlChartMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCdlChartPluginID, kCdlChartPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCdlChartPageItemBoss,						kCdlChartPrefix + 6)
DECLARE_PMID(kClassIDSpace, kNewCdlChartCmdBoss,						kCdlChartPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCdlStockScriptObjectBoss,					kCdlChartPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCdlChartScriptProviderBoss,				kCdlChartPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCdlStockScriptProviderBoss,				kCdlChartPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCdlChartErrorStringServiceBoss,			kCdlChartPrefix + 11)
DECLARE_PMID(kClassIDSpace, kModifyCdlChartCmdBoss,						kCdlChartPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCdlChartConversionProviderBoss,			kCdlChartPrefix + 13)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICDLCHARTDATA,					kCdlChartPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICDLCHARTSUITE,					kCdlChartPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICDLCHARTFACADE,				kCdlChartPrefix + 4)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCdlChartShapeImpl,			kCdlChartPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCdlChartDataImpl,				kCdlChartPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kNewCdlChartCmdImpl,			kCdlChartPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCdlChartSuiteASBImpl,			kCdlChartPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCdlChartSuiteLayoutCSBImpl,	kCdlChartPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCdlChartScriptImpl,			kCdlChartPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCdlStockScriptImpl,			kCdlChartPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCdlChartScriptProviderImpl,	kCdlChartPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCdlStockScriptProviderImpl,	kCdlChartPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCdlChartErrorStringServiceImpl,	kCdlChartPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kModifyCdlChartCmdImpl,		kCdlChartPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCdlChartFacadeImpl,			kCdlChartPrefix + 15)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kCdlChartImportDataErrorCode,            kCdlChartPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kCdlChartCreatePageItemErrorCode,        kCdlChartPrefix + 1)

// Error string keys:
#define kCdlChartImportDataErrorCodeStringKey        kCdlChartStringPrefix "kCdlChartImportDataErrorCodeStringKey"
#define kCdlChartCreatePageItemErrorCodeStringKey        kCdlChartStringPrefix "kCdlChartCreatePageItemErrorCodeStringKey"

// Other StringKeys:
#define kNewCdlChartCmdStringKey				kCdlChartStringPrefix "kNewCdlChartCmdStringKey_9"
#define kModifyCdlChartCmdStringKey				kCdlChartStringPrefix "kModifyCdlChartCmdStringKey_13"

// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kCdlChartInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kCdlChartInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber
// Note: The data format has not been changed since InDesign 2.0.

// InDesign CS4 format changes
#define kCdlChartStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kCdlChartStoreWideStringMinorFormat		RezLong(1)

// Format IDs for the PluginVersion resource 
#define kCdlChartLastMajorFormatChange	kCdlChartStoreWideStringMajorFormat		// Last major format change
#define kCdlChartLastMinorFormatChange	kCdlChartStoreWideStringMinorFormat		// Last minor format change


// ScriptElementIDs:
DECLARE_PMID(kScriptInfoIDSpace, kCandleChartObjectScriptElement, kCdlChartPrefix +1)
DECLARE_PMID(kScriptInfoIDSpace, kCandleStockObjectScriptElement, kCdlChartPrefix +2)
DECLARE_PMID(kScriptInfoIDSpace, kCdlStackOpenPropertyScriptElement, kCdlChartPrefix +3)
DECLARE_PMID(kScriptInfoIDSpace, kCdlStackHighPropertyScriptElement, kCdlChartPrefix +4)
DECLARE_PMID(kScriptInfoIDSpace, kCdlStackLowPropertyScriptElement, kCdlChartPrefix +5)
DECLARE_PMID(kScriptInfoIDSpace, kCdlStackClosePropertyScriptElement, kCdlChartPrefix +6)
DECLARE_PMID(kScriptInfoIDSpace, kCdlStackVolumePropertyScriptElement, kCdlChartPrefix +7)
DECLARE_PMID(kScriptInfoIDSpace, kImportCandleChartMethodScriptElement, kCdlChartPrefix +8)

// GUIDs for script objects:
// {0DD5EB5F-9428-4410-9FFD-7FF00CDA9892}
#define kCdlChartObject_CLSID { 0xdd5eb5f, 0x9428, 0x4410, { 0x9f, 0xfd, 0x7f, 0xf0, 0xc, 0xda, 0x98, 0x92 } }
// {474BB6A1-B072-40d0-9737-FB4C95522A8B}
#define kCdlChartsObject_CLSID { 0x474bb6a1, 0xb072, 0x40d0, { 0x97, 0x37, 0xfb, 0x4c, 0x95, 0x52, 0x2a, 0x8b } }

// {69EC0956-08AB-477f-9D70-715A561A5CF5}
#define kCdlStockObject_CLSID { 0x69ec0956, 0x8ab, 0x477f, { 0x9d, 0x70, 0x71, 0x5a, 0x56, 0x1a, 0x5c, 0xf5 } }
// {459B8129-9830-4774-B76A-3DC97BC32AEB}
#define kCdlStocksObject_CLSID { 0x459b8129, 0x9830, 0x4774, { 0xb7, 0x6a, 0x3d, 0xc9, 0x7b, 0xc3, 0x2a, 0xeb } }

// ScriptIDs:
// New ScriptIDs must be registered with Adobe Developer Support to prevent conflict with other scriptable plug-ins.
// See the Making Your Plug-in Scriptable tech note.

// Object and element ScriptIDs:
enum CdlChartScriptElements
{
    c_CandleChart       = 'cdct', // The candle chart script object (See kCandleChartObjectScriptElement in CdlChart.fr)
    c_CandleCharts      = 'cdcs',  // Collection of candle chart script objects.
    c_CandleStock       = 'cdsk', // The candle stock script object (See kCandleStockObjectScriptElement in CdlChart.fr)
    c_CandleStocks      = 'cdss',  // Collection of candle stock script objects.
	p_CdlStackOpen		= 'csop',
	p_CdlStackHigh		= 'cshi',
	p_CdlStackLow		= 'cslw',
	p_CdlStackClose		= 'cscl',
	p_CdlStackVolume	= 'csvl',
	e_ImportData		= 'ipdt'
};


#endif // __CdlChartID_h__

//  Code generated by DollyXS code generator
