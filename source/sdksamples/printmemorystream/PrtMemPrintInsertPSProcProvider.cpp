//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemPrintInsertPSProcProvider.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IPrintInsertPSProcProvider.h"

// General includes:
#include "CPMUnknown.h"
#include "IXferBytes.h"

// Project includes:
#include "PrtMemID.h"

/** Implementation of IPrintInsertPSProcProvider.
 *
 * 	@ingroup printmemorystream
 */
class PrtMemPrintInsertPSProcProvider : public CPMUnknown<IPrintInsertPSProcProvider>
{
public:
	/** Constructor
	 * 	@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	PrtMemPrintInsertPSProcProvider(IPMUnknown* boss);

	/** Destructor
	 */
	virtual ~PrtMemPrintInsertPSProcProvider(void);


	/** See IPrintInsertPSProcProvider::Setup
	 */
	virtual void Setup(IPrintData* iPrintData,
					   IOutputPages* iOutputPages,
					   IPrintJobData* iPrintJobData,
					   IInkList* iInkList,
					   ITrapStyleListMgr* iTrapListMgr);

	/**	See IPrintInsertPSProcProvider::GetInsertPSProcName
	*/
	virtual void GetInsertPSProcName(PMString& psProcName);

	/**	See IPrintInsertPSProcProvider::GetClientData
	*/
	virtual void GetClientData(void** clientData);

	/** To enable the TRACEFLOW message to be written to the TRACE sink, you must
	 * 	enable the category identified by the first parameter in the TRACEFLOW
	 * 	call. The definition:
	 *
	 * 		PrtMemPluginName kSDKDefDelimitMenuPath "PrintInsertPSProcProvider"
	 *
	 * 	expands to:
	 *
	 *  	"PrintMemoryStream:PrintInsertPSProcProvider"
	 *
	 * 	To enable this category, you must first make sure that the category
	 * 	is registered. You can either look at the TEST >> TRACE menu
	 * 	in the application and look for the submenu item PrintHook >>
	 * 	PrintInsertPSProcProvider, or look in the "Debug Settings.xml" file
	 * 	(located in the same folder as the application).
	 * 	If the category is not listed, then you must first shut down the
	 * 	application and manually add it to the "Debug Settings.xml" file,
	 * 	and then restart the application.
	 * 	Be sure to enable one or more trace sinks as well.
	 *
	 * 	See IPrintInsertPSProcProvider::PrintInsertPSProc
	 */
	virtual void PrintInsertPSProc(bool8& bReturn,
								   IPrintInsertPSProcProvider::DocumentSection docSec,
								   bool32 pre,
								   IXferBytes& pASCIIStream,
								   IXferBytes& pBinaryStream,
								   void* clientData);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PrtMemPrintInsertPSProcProvider, kPrtMemPrintInsertPSProcProviderImpl)

/* Constructor
*/
PrtMemPrintInsertPSProcProvider::PrtMemPrintInsertPSProcProvider(IPMUnknown* boss)
: CPMUnknown<IPrintInsertPSProcProvider>(boss)
{
	// do nothing.
}

/* Destructor
*/
PrtMemPrintInsertPSProcProvider::~PrtMemPrintInsertPSProcProvider(void)
{
	// do nothing.
}

/* Setup
*/
void PrtMemPrintInsertPSProcProvider::Setup(IPrintData* iPrintData,
											IOutputPages* iOutputPages,
											IPrintJobData* iPrintJobData,
											IInkList* iInkList,
											ITrapStyleListMgr* iTrapListMgr)
{
	// Nothing to do here.
	// Normally you would use the passed-in parameters
	// and cache some of them, or get specific data from them and
	// copy them into member variables.
}

/* GetInsertPSProcName
*/
void PrtMemPrintInsertPSProcProvider::GetInsertPSProcName(PMString& psProcName)
{
	// note: this PrintInsertPSProcProvider will always be enabled since we return a non-empty string
	psProcName = "PrtMemPrintInsertPSProcProvider";
}

/* GetClientData
*/
void PrtMemPrintInsertPSProcProvider::GetClientData(void** clientData)
{
	// Left as an exercise for the third party developer.
	/*
		Hints:
		You can create whatever data that you want to have passed to the
		PrintInsertPSProc callback method by creating it in this method,
		and returning it via clientData.

		For example, say you have a class called CMyPrintSettings, and
		you want to have it passed to the PrintInsertPSProc
		each time it is called.  You can do something like the following:

		CMyPrintSettings* mySettings = new CMyPrintSettings;
		// ... set mySettings
		// pass back the pointer
		*clientData = mySettings;

		Later on in the PrintInsertPSProc method, you can access this
		data as such:

		CMyPrintSettings* mySettings = (CMyPrintSettings*)clientData;

		or if CMyPrintSettings has a valid copy constructor,

		CMyPrintSettings mySettings(*((CMyPrintSettings*)clientData));

	*/
}

/* PrintInsertPSProc
*/
void PrtMemPrintInsertPSProcProvider::PrintInsertPSProc(bool8& bReturn,
                                                        IPrintInsertPSProcProvider::DocumentSection docSec,
														bool32 pre,
														IXferBytes& pASCIIStream,
														IXferBytes& pBinaryStream,
														void* clientData)
{
	const char* category = kPrtMemPluginName kSDKDefDelimitMenuPath "PrintInsertPSProcProvider";

	TRACEFLOW(category, "\t-- bReturn: %s\n", (bReturn == kTrue ? "kTrue":"kFalse"));
	TRACEFLOW(category, "\t-- pre: %d\n", pre);

	// This is string to write into the PostScript stream
	PMString comment("%% [PrtMemPrintInsertPSProcProvider::PrintInsertPSProc] ");

	// the following gets injected into the Postscript stream between
	// %ADOBeginClientInjection and %ADOEndClientInjection
	std::string scomment = comment.GetPlatformString();
	pASCIIStream.Write(reinterpret_cast<void*>(const_cast<char *>(scomment.c_str())), static_cast<uint32>(scomment.length()));

	bReturn = kTrue;
}
// End, PrtMemPrintInsertPSProcProvider.cpp.

