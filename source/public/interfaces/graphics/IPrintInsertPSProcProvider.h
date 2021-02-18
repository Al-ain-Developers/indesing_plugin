//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintInsertPSProcProvider.h $
//  
//  Owner: David Berggren
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
//  Provider interface for setting up or changing the print parameters, prior to
//  or during the printing process.
//  
//========================================================================================

#pragma once
#ifndef __IPrintInsertPSProcProvider__
#define __IPrintInsertPSProcProvider__

#include "IPMUnknown.h"
#include "IXferBytes.h"

class IPrintData;
class IOutputPages;
class IPrintJobData;
class IInkList;
class ITrapStyleListMgr;

/**  Access the PostScript stream on output through a callback mechanism
*/
class IPrintInsertPSProcProvider : public IPMUnknown
{
public:
	/** This enum is used to identify which stage of the output process is happening. 
	*/
	enum DocumentSection {
		/* Document Level */
		/** Before %%EndComments */
		kDocumentHeader = 0,
		/** Between %%Begin/EndProlog */
		kDocumentProlog,
		/** Between %%Begin/EndSetup */
		kDocumentSetup,
		/** Between %%Trailer and %EOF */
		kDocumentTrailer,

		/* Page Level */
		/** Between %%Begin/EndPageSetup */
		kPageSetup,
		/** After %%EndPageSetup */
		kBeginPageContent,
		/** Before %%PageTrailer */
		kEndPageContent,
		/** Between %%PageTrailer and %%Page (multi-page) or %%Trailer (single-page) */
		kPageTrailer
	};

	/**		Called first to allow stashing of useful pointers for later use
	
			@param iPrintData		the IPrintData containing all the print settings currently being used
			@param iOutputPages		the IOutputPages interface containing the pages to be printed
			@param iPrintJobData	the IPrintJobData interface currently being used
			@param iTrapListMgr		the ITrapStyleListMgr interface currently being used
	*/
	virtual void Setup (IPrintData *iPrintData, 
						IOutputPages *iOutputPages, 
						IPrintJobData *iPrintJobData, 
						IInkList *iInkList, 
						ITrapStyleListMgr *iTrapListMgr) = 0;

	/**		Return a unique name for the insert proc. NOTE: if the PMString is empty 
			when returned, the PrintInsertPSProc will not be called
	
			@param psProcName	proc identifier - used to identify each callback participant
	*/
	
	virtual void GetInsertPSProcName (PMString& psProcName) = 0;

	/**		This is a void* pointer that will be passed back in the callback PrintInsertPSProc
	
			@param clientData	client data pass-through that will be passed back 
								in PrintInsertPSProc NOTE: this can be nil
	*/
	virtual void GetClientData (void **clientData) = 0;

	/**		The callback method
	
			@param bReturn			return value - true means data inserted, false means no data inserted
			@param docSec			the DocumentSection defined above
			@param pre				at DocumentSection section start or end 
			@param pASCIIStream		for inserting ASCII data 
			@param pBinaryStream	for inserting Binary data NOTE: only the Write method of IXferBytes has been implemented!
			@param clientData		data defined from GetClientData() above, may be nil
	*/
	virtual void PrintInsertPSProc(	
									bool8& bReturn, 
									DocumentSection docSec, 
									bool32 pre,
									IXferBytes& pASCIIStream,
									IXferBytes& pBinaryStream,
									void *clientData
									) = 0;
};

#endif
