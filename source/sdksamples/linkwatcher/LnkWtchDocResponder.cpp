//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchDocResponder.cpp $
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
#include "IClassIDData.h"
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "IObserver.h"
#include "IPMStream.h"

// General  includes:
#include "CResponder.h"
#include "Trace.h"
#include "IDFile.h"
#include "StreamUtil.h"
#include "FileUtils.h"

// Project includes:
#include "LnkWtchID.h"
#include "ILnkWtchCache.h"

/** Attaches and detaches LnkWtchCacheManager as documents are
	created, opened and closed. On close write each entry in
	the cache to this plug-in's log. The log file is created 
	in the defaults folder for the application. 
	For example, for InDesign CS3 the log file can be found
	at the locations below:
	<pre>
	On Windows:
	"C:\Documents and Settings\<user>\Application Data\Adobe\InDesign\Version 5.0\LinkWatcher.txt"

	On Macintosh:
	"/Users/<user>/Library/Preferences/Adobe InDesign/Version 5.0/LinkWatcher.txt"
	</pre>

	@see LnkWtchCacheManager
	@see ILnkWtchCache
	@ingroup linkwatcher
*/
class LnkWtchDocResponder : public CResponder
{
public:
	/** Constructor.
	@param boss object this object is aggregated on.
	*/
	LnkWtchDocResponder(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~LnkWtchDocResponder() {}

	/** Attaches LnkWtchCacheManager when documents are created
		or opened, detaches it on close.
		@param signalMgr provides information about the signal.
	*/
	virtual void Respond(ISignalMgr* signalMgr);

private:
	/** Opens a log in the application defaults folder and writes
		each entry in ILnkWtchCache to the log.
		@param documentUIDRef document containing cache to be traced in the log.
	*/
	void LogCacheContent(const UIDRef& documentUIDRef);

	/**	Writes a line to this plug-in's log file.
		@param stream for log output
		@param line to be written out to the log
	*/
	void WriteLine(IPMStream* stream, const std::string& line);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(LnkWtchDocResponder, kLnkWtchDocResponderImpl)

/*
*/
LnkWtchDocResponder::LnkWtchDocResponder(IPMUnknown* boss) :
CResponder(boss)
{
}

/*
*/
void LnkWtchDocResponder::Respond(ISignalMgr* signalMgr)
{
	do {
		// Get a reference to the document. 
		InterfacePtr<IDocumentSignalData> documentSignalData(signalMgr, UseDefaultIID());
		ASSERT(documentSignalData != nil);
		if (documentSignalData == nil) {
			break;
		}
		UIDRef documentUIDRef = documentSignalData->GetDocument();

		// Get the service ID from the signal manager
		ServiceID serviceID = signalMgr->GetServiceID();

		// Take action based on the service ID
		switch (serviceID.Get()) 
		{
		case kDuringNewDocSignalResponderService:
		case kDuringOpenDocSignalResponderService: 
			{
				InterfacePtr<IObserver> docObserver(documentUIDRef, IID_ILNKWTCHCACHEMANAGER);
				if (docObserver != nil) {
					docObserver->AutoAttach();
				}
				break;
			}
		case kBeforeCloseDocSignalResponderService:
			{
				InterfacePtr<IObserver> docObserver(documentUIDRef, IID_ILNKWTCHCACHEMANAGER);
				if (docObserver != nil) {
					docObserver->AutoDetach();
				}
				this->LogCacheContent(documentUIDRef);
				break;
			}
		default:
			break;
		}
	} while(false);
}

/*	This plug-in simply logs each file linked to the document
	since it was created or opened. Third parties could extend this
	to copy the linked files back to a server for example.
*/
void LnkWtchDocResponder::LogCacheContent(const UIDRef& documentUIDRef)
{
	do {
		// Open the log.
		IDFile logFilePath;
		FileUtils::GetAppLocalCachedDataFolder(&logFilePath, PMString("LinkWatcher.txt"));
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(logFilePath, kOpenOut | kOpenApp, 'CWIE', 'TEXT'));
		if (stream == nil)
		{
			ASSERT_FAIL("Couldn't create stream for log");
			break;
		}
		// Write each entry in the cache to the log.
		InterfacePtr<ILnkWtchCache> cache(documentUIDRef, UseDefaultIID());
		if (cache != nil && cache->Get().size() > 0) {
			PMString kNewLine;
			kNewLine.AppendW('\n');
			const ILnkWtchCache::Entries& entries = cache->Get();
			ILnkWtchCache::Entries::const_iterator iter;
			for (iter = entries.begin(); iter < entries.end(); iter++)
			{
				if (iter->fRemoved == kFalse)
				{
					PMString name = cache->GetName(*iter, kTrue);
					if (!name.IsEmpty())
					{
						this->WriteLine(stream, name.GetPlatformString());
					}
				}
			}
		}
		// Close the log.
		stream->Flush();
		stream->Close();
	} while(false);
}

/*
*/
void LnkWtchDocResponder::WriteLine(IPMStream* stream, const std::string& line)
{
	uchar ch;
	std::string::const_iterator iter=line.begin();
	while (iter != line.end() && stream->GetStreamState() == kStreamStateGood) 
	{
		ch = (uchar)*iter;
		stream->XferByte(ch);
		iter++;
	}
	stream->XferByte((uchar*)"\r\n", 2);
}

// End, LnkWtchDocResponder.cpp.


