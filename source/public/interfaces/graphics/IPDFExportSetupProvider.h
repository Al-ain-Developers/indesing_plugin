//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFExportSetupProvider.h $
//  
//  Owner: DBerggren
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
//  Purpose:
//  Provider interface for setting up or changing the PDF parameters, prior to
//  and during the PDF export process.
//  
//========================================================================================

#pragma once
#ifndef __IPDFExportSetupProvider__
#define __IPDFExportSetupProvider__

#include "PDFID.h"
#include "IPMUnknown.h"
#include "IPDFExportController.h"

/**
   Provider interface for setting up or changing the PDF parameters, prior to
   and during the PDF export process.
*/
class IPDFExportSetupProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFEXPORTSETUPPROVIDER };

	/**
	 Called from the PDF export controller prior to each export event. See IPDFExportController.h
	 for a list of the PDF export events. Register for the kPDFExportSetupService to use this.
	 @param pdfExportEvent	IN the current event - see IPDFExportController for events and
								the PDFExportEvent structure.
	 @param pageNum			IN the current page based index for the event, zero based.
	 @return: true to continue with the default processing for the event, 
				false to skip the default processing for the event.
	 */
	virtual bool16 PDFProcessEvent (
			PDFExportEvent*		pdfExportEvent,
			int32				pageNum
			) = 0;

};

#endif
