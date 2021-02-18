//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SVGExportID.h $
//  
//  Owner: Greg St. Pierre
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __SVGExportID__
#define __SVGExportID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSVGExportPrefix						RezLong(0x12700)

#define kSVGExportPluginName					"SVG Export Filter"
DECLARE_PMID(kPlugInIDSpace,			kSVGExportPluginID,					kSVGExportPrefix + 81)

// <Start IDC>

// <Class ID>
// Class IDs
//DECLARE_PMID(kClassIDSpace,				kSVGExportProviderBoss,					kSVGExportPrefix + 81)
//gap
DECLARE_PMID(kClassIDSpace,				kSVGExportViewPortBoss,					kSVGExportPrefix + 83)
DECLARE_PMID(kClassIDSpace,				kSVGExportCommandBoss,					kSVGExportPrefix + 84)
DECLARE_PMID(kClassIDSpace,				kSVGExportSetPrefsCommandBoss,			kSVGExportPrefix + 85)
DECLARE_PMID(kClassIDSpace,				kSVGExportPageItemsCommandBoss,			kSVGExportPrefix + 86)
// gap
DECLARE_PMID(kClassIDSpace,				kSVGExportBackStorePortBoss,			kSVGExportPrefix + 88)
//DECLARE_PMID(kClassIDSpace,				kSVGExportReadZipStreamBoss,			kSVGExportPrefix + 89)
//DECLARE_PMID(kClassIDSpace,				kSVGExportWriteZipStreamBoss,			kSVGExportPrefix + 90)
//DECLARE_PMID(kClassIDSpace,				kSVGExportPrefsScriptProviderBoss,		kSVGExportPrefix + 91)
//gap
DECLARE_PMID(kClassIDSpace,				kSVGOutputPagesBoss,		            kSVGExportPrefix + 95)
//gap
DECLARE_PMID(kClassIDSpace,				kSVGSchemaConversionBoss,				kSVGExportPrefix + 97)
//gap
DECLARE_PMID(kClassIDSpace,				kSVGExporterBoss,						kSVGExportPrefix + 99)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGWRITERACCESS,					kSVGExportPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTCOMMANDDATA,				kSVGExportPrefix + 82)
//DECLARE_PMID(kInterfaceIDSpace,		IID_ISVGEXPORTFILENAMEGENERATOR_Obsolete,		kSVGExportPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTPREFERENCES,				kSVGExportPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTSETPREFSCMDDATA,			kSVGExportPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTCONTROLLER,				kSVGExportPrefix + 86)
//DECLARE_PMID(kInterfaceIDSpace,			IID_IZIPSTREAMDATA,						kSVGExportPrefix + 87)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IVIRTUALIMAGESTREAMDATA_Obsolete,			kSVGExportPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGDRAWINGMONITOR,					kSVGExportPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGFILECUSTODIAN,					kSVGExportPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTSUITE,					kSVGExportPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGTEXPORTUTILS,					kSVGExportPrefix + 92)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGEXPORTER,						kSVGExportPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISVGSESSIONDRAWPREFS,				kSVGExportPrefix + 94)

// <Implementation ID>
// Implementation IDs
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportProviderImpl,					kSVGExportPrefix + 81)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportGraphicsPortImpl,				kSVGExportPrefix + 82)
DECLARE_PMID(kImplementationIDSpace,	kSVGWriterAccessImpl,					kSVGExportPrefix + 83)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportCommandImpl,					kSVGExportPrefix + 84)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportCommandDataImpl,				kSVGExportPrefix + 85)
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportFileNameGeneratorImpl_Obsolete,		kSVGExportPrefix + 86)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportPreferencesImpl,				kSVGExportPrefix + 87)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportSetPrefsCommandImpl,			kSVGExportPrefix + 88)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportSetPrefsCommandDataImpl,		kSVGExportPrefix + 89)
DECLARE_PMID(kImplementationIDSpace,	kSVGViewPortAttributesImpl,				kSVGExportPrefix + 90)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportControllerImpl,				kSVGExportPrefix + 91)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportPageItemsCommandImpl,			kSVGExportPrefix + 92)
// gap
/*
// Reason why we are removing these Impls: Refer SVGExportClass.fr or CL:1048804
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportReadZipStreamImpl,			kSVGExportPrefix + 95)
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportWriteZipStreamImpl,			kSVGExportPrefix + 96)
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportZipStreamDataImpl,			kSVGExportPrefix + 97)
*/
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportPrefsScriptProviderImpl,		kSVGExportPrefix + 98)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportUtilsImpl,					kSVGExportPrefix + 99)
//gap
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportVirtualImageStreamImpl_Obsolete,		kSVGExportPrefix + 101)
//DECLARE_PMID(kImplementationIDSpace,	kSVGExportVirtualImageStreamDataImpl,	kSVGExportPrefix + 102)
DECLARE_PMID(kImplementationIDSpace,	kSVGDrawingMonitorImpl,					kSVGExportPrefix + 103)
DECLARE_PMID(kImplementationIDSpace,	kSVGFileCustodianImpl,					kSVGExportPrefix + 104)
// gap
DECLARE_PMID(kImplementationIDSpace,	kSVGExportSuiteASBImpl,					kSVGExportPrefix + 106)
DECLARE_PMID(kImplementationIDSpace,	kSVGExportSuiteLayoutCSBImpl,			kSVGExportPrefix + 107)

DECLARE_PMID(kImplementationIDSpace,	kSVGExporterImpl,						kSVGExportPrefix + 108)
DECLARE_PMID(kImplementationIDSpace,	kSVGSessionDrawPrefsImpl,				kSVGExportPrefix + 109)
DECLARE_PMID(kImplementationIDSpace,	kSVGDrawEventHandlerImpl,				kSVGExportPrefix + 110)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kSVGExportPreferenceObjectScriptElement, kSVGExportPrefix + 85)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kSGVExportPreferencePropertyScriptElement, kSVGExportPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kEmbedImagesPropertyScriptElement, kSVGExportPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kFontSubsettingPropertyScriptElement, kSVGExportPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kReadersSpreadsPropertyScriptElement, kSVGExportPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kRealPrecisionPropertyScriptElement, kSVGExportPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kRenderingStylePropertyScriptElement, kSVGExportPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kSVGFileEncodingPropertyScriptElement, kSVGExportPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kStyleFormatPropertyScriptElement, kSVGExportPrefix + 108)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kSVGFontSubsettingEnumScriptElement, kSVGExportPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kSVGRenderingStyleEnumScriptElement, kSVGExportPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kSVGFileEncodingEnumScriptElement, kSVGExportPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kSVGStyleFormatEnumScriptElement, kSVGExportPrefix + 133)

#endif // __SVGExportID__
