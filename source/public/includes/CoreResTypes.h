//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CoreResTypes.h $
//  
//  Owner: Steve Pellegrin
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

#pragma once
#ifndef __CoreResTypes__
#define __CoreResTypes__

#ifdef __ODFRC__
#ifdef __WINDOWS__
#ifndef WINDOWS
#define WINDOWS 1
#endif
#else
#ifndef MACINTOSH
#define MACINTOSH 1
#endif
#endif
#endif

// ---- Core types used by ODFRC scripts.

//#define kOldClassRsrcType 		'OCLS' // use new .fr based kClassRsrcType
//#define kOldAddInClassRsrcType 	'OACL' // use new .fr based kAddInClassRsrcType
#define kInterfaceColorsType	'Colr'
#define kPErrorTableType 		'petb'
#define kUErrorTableType 		'uetb'
#define kRulerRsrcType 			'rulr'
//#define kOldPlugInDependents		'PLG0' // use new .fr based kPlugInDependents
#define kPlugInVersion			'PVER'
//#define kOldCriticalTagsRsrcType	'OCTG'// use new .fr based kCriticalTagsRsrcType
//#define kOldIgnoreTagsRsrcType		'OITG'// use new .fr based kIgnoreTagsRsrcType


// ----- Type ids for new core resources. [amb]

#define kSysControlRsrcType					'CNTL'
#define kViewRsrcType						'VIEW'
#define kPanelListRsrcType					'PLST'
#define kLocaleIndexRsrcType				'LOCR'
#define kStringTableRsrcType				'PMST'
#define kTIPSRsrcType						'TIPS'
#define kIDListRsrcType						'ILST'
#define kIDListPairRsrcType					'ILTP'
#define kToolRsrcType						'TLDF'
#define kTouchToolRsrcType					'TTLD'
#define kMenuRsrcType						'MENR'
#define kActionRsrcType						'ACTD'
#define kActionIDPoolRsrcType				'ACTP'
#define kInterfaceFontTableRsrcType			'UIFT'
#ifdef WINDOWS
#define kICCProfileRsrcType					512
#else
#define kICCProfileRsrcType					'ICCP'
#endif
#define kCustomDialogRsrcType				'DITL'		
#define kInterfaceEquivalentsRsrcType		'IFEQ' // Interface Equivalents		
#define kFactoryListRsrcType				'FACT'
#define kFeatureSetRsrcType					'FEAT'
#define kADAMRsrcType						'ADAM'
#define kEVERsrcType						'EVE_'

#define kClassRsrcType 						'CLAS'
#define kAddInClassRsrcType 				'ACLS'
#define kCriticalTagsRsrcType				'CTAG'
#define kIgnoreTagsRsrcType					'ITAG'
#define kPlugInDependents					'PLUG'
#define kProductRsrcType					'PROD'

#define kFileTypeTableRsrcType				'FTTB'
#define kApplPubFileTypeRsrcType			'APFT'
#define kClassTableRsrcType 				'CLST'
#define kServiceProviderType				'SERV'
#define kImplementationAliasRsrcType		'IALS'

#define kInterfaceEquivalentsRsrcType		'IFEQ' // Interface Equivalents		
#define kKitListRsrcType					'KLST'
#define kSelectionExtRsrcType				'ISui'

//#ifdef ID_DEPRECATED
#define kScriptElementRsrcType				'SCEI'
//#endif
#define kScriptElementRsrcType2				'SCE2'
#define kAppVersionRsrcType					'GUID'

#define kPNGArtRsrcType						'PNGA' // resource type PNGA, PNG ART! Icons Are not Localized! Regular version.
#define kPNGArtRollOverRsrcType				'PNGR' // resource type PNGR, PNG ART! Icons Are not Localized! Rollover version.
#define kPNGArtDarkRsrcType					'PNGD' // resource type PNGAD, PNG ART! Icons Are not Localized! Used in App Bar. Used in App Bar, Darker version.
#define kPNGArtRollOverDarkRsrcType			'PNGK' // resource type PNGRD, PNG ART! Icons Are not Localized! Used in App Bar. Darker rollover version.

#define kHighLevelUIFuncGroupRsrcType		'HLFG'
#define kHighLevelUIFuncWidgetSetRsrcType	'HLFW'
#define kHighLevelUIFuncMenuSetRsrcType		'HLFM'
#define kHighLevelUIFuncActionSetRsrcType	'HLFA'

#define kTemplateRsrcType					'TMPL'
#define kPackagesRsrcType					'PCKS'

#define kPNGCursorRsrcType					'PNGC'
#define kCursorHotSpotRsrcType				'HOTC'

#define kTouchControlRsrcType				'TOCL'

// ----- Type ids for schemas. [shp]

#define kSchemaRsrcType						'SCMA'
#define kSchemaListRsrcType					'SCML'
#define kBossDirectiveRsrcType				'BOSD'
#define kFormatNumberPathRsrcType			'FNPA'
#define kVersionListRsrcType				'VRLS'

#define kIDNameListRsrcType				'IDNL'
#define kExtraPluginInfoType			'IDPL'

#define kCoreResourceCompileTimeType	'CRCT'

#define kBinaryBlobType					'BBlb' //taken from DynamicDocumentsExtrasDefs


#ifdef MACINTOSH

// String for making a carriage return in a string. Useful for alerts.
// e.g. "Here is a string" kLineSeparatorString "that takes up two lines."
// Resource compiler will combine into one string with a carriage return.
#define kLineSeparatorString				"\r"

#endif

#ifdef WINDOWS

// String for making a carriage return in a string. Useful for alerts.
// e.g. "Here is a string" kLineSeparatorString "that takes up two lines."
// Resource compiler will combine into one string with a carriage return.
#define kLineSeparatorString				"\n"

#endif

#endif
