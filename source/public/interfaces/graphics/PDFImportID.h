//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PDFImportID.h $
//  
//  Owner: Dave Burris
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

#ifndef __PDFIMPORTID__
#define __PDFIMPORTID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPDFImportPrefix 				RezLong( 0x9100 )	// Official & Registered.

//----------------------------------------------------------------------------------------
//
// PluginID
//

#define kPDFImportPluginName 			"PDF Import"
DECLARE_PMID(kPlugInIDSpace, kPDFImportPluginID, kPDFImportPrefix + 1)

//----------------------------------------------------------------------------------------
//
// <Class ID>
//

DECLARE_PMID(kClassIDSpace, kPDFImportItem, kPDFImportPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPDFImportProviderBoss, kPDFImportPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPDFImportCmdBoss, kPDFImportPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPDFImageReadFormatBoss, kPDFImportPrefix + 4)


//----------------------------------------------------------------------------------------
//
// <Interface ID>
//

DECLARE_PMID(kInterfaceIDSpace, IID_IPDFIMPORT, kPDFImportPrefix + 1)

//----------------------------------------------------------------------------------------
//
// <Implementation ID>
//

DECLARE_PMID(kImplementationIDSpace, kPDFImportProvider, kPDFImportPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPDFImportCmd, kPDFImportPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCPDFImport, kPDFImportPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPDFImageReadFormatInfo, kPDFImportPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPDFImageReadFormat, kPDFImportPrefix + 5)
// gap
DECLARE_PMID(kImplementationIDSpace, kPDFImportAttributes, kPDFImportPrefix + 7)

#endif // __PDFID__
