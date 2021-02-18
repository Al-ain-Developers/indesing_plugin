//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/InteractivePDFID.h $
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
//========================================================================================

#ifndef __InteractivePDFID_h__
#define __InteractivePDFID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInteractivePDFPrefix	 		RezLong(0x15500)

// ----- Plug-in ID -----

#define kInteractivePDFPluginName 		"Interactive PDF"
DECLARE_PMID(kPlugInIDSpace,			kInteractivePDFPluginID,				kInteractivePDFPrefix + 1)

// ----- Class IDs -----

DECLARE_PMID(kClassIDSpace,				kStartPDFDocumentResponderBoss,			kInteractivePDFPrefix + 1)
DECLARE_PMID(kClassIDSpace,				kEndPDFDocumentResponderBoss,			kInteractivePDFPrefix + 2)
DECLARE_PMID(kClassIDSpace,				kStartPDFPageResponderBoss,				kInteractivePDFPrefix + 3)
DECLARE_PMID(kClassIDSpace,				kEndPDFPageResponderBoss,				kInteractivePDFPrefix + 4)
DECLARE_PMID(kClassIDSpace,				kCheckInteractiveItemProviderBoss,		kInteractivePDFPrefix + 5)

// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace,			IID_IMEDIAPORT,							kInteractivePDFPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOVIEPORT,							kInteractivePDFPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_IFORMSPORT,							kInteractivePDFPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISOUNDPORT,							kInteractivePDFPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,			IID_IACTIONDICTGENERATOR,				kInteractivePDFPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,			IID_IINTERACTIVEPDFDATA,				kInteractivePDFPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,			IID_IKEYDOWNACTIONDICTGENERATOR,		kInteractivePDFPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,			IID_IINTERACTIVEPDFLIB,					kInteractivePDFPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPDFANOTTIMESTAMP,					kInteractivePDFPrefix + 9)

// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace,	kMediaPortImpl,							kInteractivePDFPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kMoviePortImpl,							kInteractivePDFPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kFormsPortImpl,							kInteractivePDFPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kSoundPortImpl,							kInteractivePDFPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kMovieActionDictGeneratorImpl,			kInteractivePDFPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kGoToPositionBehaviorGeneratorImpl,		kInteractivePDFPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kGoToURLBehaviorGeneratorImpl,			kInteractivePDFPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kShowHideFieldsBhvrGeneratorImpl,		kInteractivePDFPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kImportDataBehaviorGeneratorImpl,		kInteractivePDFPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kResetFormBehaviorGeneratorImpl,		kInteractivePDFPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kSubmitFormBehaviorGeneratorImpl,		kInteractivePDFPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kOpenFileBehaviorGeneratorImpl,			kInteractivePDFPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kCloseBehaviorGeneratorImpl,			kInteractivePDFPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kExitBehaviorGeneratorImpl,				kInteractivePDFPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kJavaScriptBehaviorGeneratorImpl,		kInteractivePDFPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kPDFResponderImpl,						kInteractivePDFPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kPDFSpyImpl,							kInteractivePDFPrefix + 17)

DECLARE_PMID(kImplementationIDSpace,	kFormatNumberBehaviorGeneratorImpl,			kInteractivePDFPrefix + 20)
DECLARE_PMID(kImplementationIDSpace,	kFormatPercentBehaviorGeneratorImpl,		kInteractivePDFPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,	kFormatDateBehaviorGeneratorImpl,			kInteractivePDFPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,	kFormatTimeBehaviorGeneratorImpl,			kInteractivePDFPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,	kFormatSpecialBehaviorGeneratorImpl,		kInteractivePDFPrefix + 24)

DECLARE_PMID(kImplementationIDSpace,	kKeystrokeNumberBehaviorGeneratorImpl,		kInteractivePDFPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,	kKeystrokePercentBehaviorGeneratorImpl,		kInteractivePDFPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,	kKeystrokeDateBehaviorGeneratorImpl,		kInteractivePDFPrefix + 27)
DECLARE_PMID(kImplementationIDSpace,	kKeystrokeTimeBehaviorGeneratorImpl,		kInteractivePDFPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kKeystrokeSpecialBehaviorGeneratorImpl,		kInteractivePDFPrefix + 29)

DECLARE_PMID(kImplementationIDSpace,	kFormulaBehaviorGeneratorImpl,				kInteractivePDFPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kMarkReadOnlyBehaviorGeneratorImpl,			kInteractivePDFPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kValidateRangeBehaviorGeneratorImpl,		kInteractivePDFPrefix + 32)

DECLARE_PMID(kImplementationIDSpace,	kGoToAnchorBehaviorGeneratorImpl,			kInteractivePDFPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kViewZoomBehaviorGeneratorImpl,				kInteractivePDFPrefix + 34)

DECLARE_PMID(kImplementationIDSpace,	kSoundActionDictGeneratorImpl,				kInteractivePDFPrefix + 35)

DECLARE_PMID(kImplementationIDSpace,	kPDFAnotTimeStampImpl_obsolete,				kInteractivePDFPrefix + 36)

DECLARE_PMID(kImplementationIDSpace,	kCheckInteractiveItemProviderImpl,			kInteractivePDFPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,	kPrintFormBehaviorGeneratorImpl,			kInteractivePDFPrefix + 38)

// ----- Widget IDs -----

// ----- Action IDs -----

// ----- Service IDs -----

//DECLARE_PMID(kServiceIDSpace,			kInteractivePDFOpsService,				kInteractivePDFPrefix + 1)

// ----- Error IDs -----

DECLARE_PMID(kErrorIDSpace,				kVerifyPDFButtonActionsDontShowAgainID,		kInteractivePDFPrefix + 1)


#endif // __InteractivePDFID_h__
