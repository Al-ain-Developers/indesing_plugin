//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PrStID.h $
//  
//  Owner: Matt Phillips
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

#ifndef __PrStID__
#define __PrStID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPrStPrefix	 RezLong(0xbd00)		//Refer also to AdobePrefix.h

// <Start IDC>
// PluginID
#define kPrStPluginName 								"Printer Styles"
DECLARE_PMID(kPlugInIDSpace, kPrStPluginID, kPrStPrefix + 1)

// Conversion
// For pub conversion constants see PrStConversionID.h

// <Class ID>
// ClassIDs (i.e. bosses)
// gap
// gap
DECLARE_PMID(kClassIDSpace, kPrStStyleListMgrBoss, kPrStPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPrStStyleBoss, kPrStPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPrStSetStyleNameCmdBoss, kPrStPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPrStAddStyleCmdBoss, kPrStPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPrStDeleteStyleCmdBoss, kPrStPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPrStExportRootBoss, kPrStPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPrStEditStyleCmdBoss, kPrStPrefix + 9)
//gap
//gap
DECLARE_PMID(kClassIDSpace, kPrStConversionProviderBoss, kPrStPrefix + 12)
//gap
DECLARE_PMID(kClassIDSpace, kPrintStyleScriptProviderBoss, kPrStPrefix + 14)


// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPRSTSTYLELISTMGR, kPrStPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPRSTCMDDATA, kPrStPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPRSTSTYLELOCKINFO, kPrStPrefix + 3)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kPrStEditMenuActionImpl, kPrStPrefix + 1)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrStStyleListMgrImpl, kPrStPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPrStSetStyleNameCmdImpl, kPrStPrefix + 4	)
DECLARE_PMID(kImplementationIDSpace, kPrStAddStyleCmdImpl, kPrStPrefix + 5		)
DECLARE_PMID(kImplementationIDSpace, kPrStDeleteStyleCmdImpl, kPrStPrefix + 6		)
//DECLARE_PMID(kImplementationIDSpace, kPrStCmdDataImpl, kPrStPrefix + 7	)
DECLARE_PMID(kImplementationIDSpace, kPrStEditStyleCmdImpl, kPrStPrefix + 8	)
DECLARE_PMID(kImplementationIDSpace, kPrStStyleLockInfoImpl, kPrStPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrStyleDynamicMenuImpl, kPrStPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPrintStyleScriptImpl, kPrStPrefix + 12)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrintStyleScriptProviderImpl, kPrStPrefix + 14)
//gap

// <Widget ID>
//	Widget IDs

// <Service ID>
//	Service IDs

// <Error ID>
// Error IDs
DECLARE_PMID(kErrorIDSpace, kPrStErrIndexOutOfRange, kPrStPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kPrStErrNameConflict, kPrStPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPrStErrNullParameter, kPrStPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kPrStErrPersonalityMissing, kPrStPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kPrStErrCommandCreationError, kPrStPrefix + 5)

// <Action ID>
//gap	

// Schemas

#define kPrStV1DirectiveRsrcID				2000

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPrinterStyleObjectScriptElement,			kPrStPrefix + 10)

//Events

//Properties

//Enums

//GUIDS
// {6C10ABB1-06A5-4546-BB13-488B4075F637}
#define kPrintStyle_CLSID { 0x6c10abb1, 0x6a5, 0x4546, { 0xbb, 0x13, 0x48, 0x8b, 0x40, 0x75, 0xf6, 0x37 } }
// {6F0CB944-3A1D-4010-BE3A-CCDFF77728AB}
#define kPrintStyles_CLSID { 0x6f0cb944, 0x3a1d, 0x4010, { 0xbe, 0x3a, 0xcc, 0xdf, 0xf7, 0x77, 0x28, 0xab } }

#endif // __PrinterStylesID__


