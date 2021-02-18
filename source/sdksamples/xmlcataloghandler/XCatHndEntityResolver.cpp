//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndEntityResolver.cpp $
//  
//  Owner: Ian Paterson
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

// interface includes
#include "IPMStream.h"
#include "ISAXEntityResolver.h"
#include "IXCatHndFacade.h"
#include "ISysFileData.h"
// General includes
#include "StreamUtil.h"
#include "Utils.h"
#include "SDKFileHelper.h"
#include "CPMUnknown.h"
#include "XCatHndID.h"


/** Implementation of ISAXEntityResolver that knows how to to resolve PUBLIC identifiers
	into system identifiers, based on XML catalogs

	@ingroup xmlcataloghandler
*/
class XCatHndEntityResolver : public CPMUnknown<ISAXEntityResolver>
{
	public:

		/** Constructor
		*/
		XCatHndEntityResolver(IPMUnknown *boss);

		/**	@see ISAXEntityResolver::ResolveEntity
		 */
		virtual IPMStream* ResolveEntity(const WideString& publicID, const WideString& systemID);

};

CREATE_PMINTERFACE(XCatHndEntityResolver, kXCatHndEntityResolverImpl)


/*
*/
XCatHndEntityResolver::XCatHndEntityResolver(IPMUnknown *boss) :
	CPMUnknown<ISAXEntityResolver>(boss)
{
}

/*
*/
IPMStream* XCatHndEntityResolver::ResolveEntity(const WideString& publicID, const WideString& systemID)
{

	IPMStream* retval = nil;

	do {

		Utils<IXCatHndFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		// This object has reference to file being imported we set up ourselves
		// when we created the entity resolver for the import, so 
		// we are hoping that it has something valid
		InterfacePtr<ISysFileData> sysFileData(this, UseDefaultIID());
		ASSERT(sysFileData);
		if(!sysFileData) {
			break;
		}
		IDFile importingIDFile = sysFileData->GetSysFile();

		WideString uri = facade->ResolvePublicToUri(WideString(publicID));
#ifdef MACINTOSH
		// mac specific hack. If we have a / in the name on Windows, that's fine, Windows treats it like
		// a \ (platform char separator).
		// but at present, if we have / in a path on the Mac, it means that the file looks like it's not
		// there... so what I'm doing here is translating / to :	
		uri = Utils<IXCatHndFacade>()->TranslateURIToPlatformSpec(uri);
#endif
		if(uri.CharCount() == 0) {
			ErrorCode err = facade->LoadPeerCatalog(importingIDFile);
			// Retry;
			if(err == kSuccess) {
				uri = facade->ResolvePublicToUri(WideString(publicID));
			}
		}
		// have another look at this to see if we found something it resolves to
		if(uri.CharCount() == 0) {
			break;
		}
		IDFile aValidFile;
		bool16 foundViaXMLBase = kFalse;
		for(int32 base=0; base < facade->GetXMLBaseCount(); base++) {
			if(facade->GetNthXMLBase(base).CharCount()>0) {
				WideString tmp(facade->GetNthXMLBase(base));
				tmp.Append(uri);
				PMString tryThisUri(tmp);
				SDKFileHelper arfileHelper(tryThisUri);
					if(arfileHelper.IsExisting()) {
					// We've found a base to try
					foundViaXMLBase = kTrue;
					aValidFile = arfileHelper.GetIDFile();
					break; // out of this for loop
				}
			}
		}

		if(foundViaXMLBase) {
			InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(aValidFile));		
			ASSERT(stream);
			if(stream) {
				retval = stream.forget();
				break;
			}
		
		}

		// Perhaps the systemID is for real and we can use it,
		SDKFileHelper syFileHelper(systemID);
		if(syFileHelper.IsExisting()) {
			InterfacePtr<IPMStream> syStream(
				StreamUtil::CreateFileStreamRead(syFileHelper.GetIDFile()));		
			ASSERT(syStream);
			if(syStream) {
				retval = syStream.forget();
				break;
			}
		}

		// Finally, try looking relative to the XML file being imported.
		// We've not been passed the importer, which would know. So we have to
		// depend on having cached a reference to imported file ourselves
		SDKFileHelper importingFileHelper(importingIDFile);
		PMString originalURI(facade->ResolvePublicToUri(WideString(publicID)));
		SDKFileHelper fallbackHelper(importingFileHelper.GetAbsoluteFromRelative(originalURI));
		if(fallbackHelper.IsExisting()) {
			InterfacePtr<IPMStream> fallbackStream(
				StreamUtil::CreateFileStreamRead(fallbackHelper.GetIDFile()));		
			ASSERT(fallbackStream);
			if(fallbackStream) {
				retval = fallbackStream.forget();
				break;
			}
		}
		
	} while(kFalse);
	
	if(retval == nil) {
		// Return something in case we failed
		retval = static_cast<IPMStream*>(::CreateObject(kNewlineStreamBoss, IID_IPMSTREAM));
	}
	return retval;
}



//  Code generated by DollyXS code generator
