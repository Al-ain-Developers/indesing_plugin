//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PDFLPlugInID.h $
//  
//  Owner: Michael Jordan
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

#ifndef __PDFLPLUGINID__
#define __PDFLPLUGINID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kPDFLPlugInPrefix					RezLong( 0x9A00 )

//----------------------------------------------------------------------------------------
//
// PluginID
//

//#define kPDFLPlugInName						"PDF Library"
//DECLARE_PMID(kPlugInIDSpace, kPDFLPluginID, kPDFLPlugInPrefix + 1)


// <Start IDC>
// <Class ID>
//----------------------------------------------------------------------------------------
//
// Boss ids

//

//DECLARE_PMID(kClassIDSpace, kPDFL_Sample_Boss, kPDFLPlugInPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kPDFLPlugInTestMenuBoss, kPDFLPlugInPrefix + 255)	// Keep this debug boss at the end - Moved to PDFUI

// <Interface ID>
//----------------------------------------------------------------------------------------
//
// Interface ids
//

DECLARE_PMID(kInterfaceIDSpace, IID_IPDFLIBRARY, kPDFLPlugInPrefix + 1)


// <Implementation ID>
//----------------------------------------------------------------------------------------
//
// Implementation ids
//

DECLARE_PMID(kImplementationIDSpace, kCPDFLibraryImpl, kPDFLPlugInPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kPDFLPlugInTestMenuImpl, kPDFLPlugInPrefix + 255)		// Keep this debug implementation at the end - Moved to PDFUI

// <Message ID>

DECLARE_PMID(kMessageIDSpace, kPDFThreadReferenceMsg, kPDFLPlugInPrefix + 1)

//----------------------------------------------------------------------------------------
//
// Service IDs
//DECLARE_PMID(kServiceIDSpace, kPDFL_Sample_Service, kPDFLPlugInPrefix + 1)

// <Error ID>
//----------------------------------------------------------------------------------------
//
// Error Codes
//DECLARE_PMID(kServiceIDSpace, kPDFLLibraryError, kPDFLPlugInPrefix + 1)
//DECLARE_PMID(kServiceIDSpace, kPDFLLibraryNotPresentError, kPDFLPlugInPrefix + 2)


#endif // __PDFLPLUGINID__
