//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndAcquirerFilter.cpp $
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
#include "IImportXMLData.h"
#include "IPMStream.h"
#include "ISAXEntityResolver.h"
#include "ISAXEntityResolver.h"
#include "ISysFileData.h"
#include "IXCatHndFacade.h"
#include "IXMLAcquirerFilter.h"
#include "IURIUtils.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "ILinkResource.h"

// General includes:
#include "Utils.h"
#include "SDKFileHelper.h"
#include "CPMUnknown.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"

// Project includes:
#include "XCatHndID.h"

/** Implementation of IXMLAcquirerFilter, used to direct importer to our own entity resolver.
	@ingroup xmlcataloghandler
*/
class XCatHndAcquirerFilter :
	public CPMUnknown<IXMLAcquirerFilter>
{
public:
	/** Constructor 
		@param boss interface pointer referring to boss object this implementation is associated with
	*/
	XCatHndAcquirerFilter(IPMUnknown* boss);

	/** Destructor 
	*/
	virtual ~XCatHndAcquirerFilter(void);

	/**  @see IXMLAcquirerFilter::GetFileTypeCount 
	*/
	virtual int32  GetFileTypeCount () const;
 
	/**	@see IXMLAcquirerFilter::GetNthFileType
	 */
	virtual void  GetNthFileType (int32 n, PMString *family, PMString *extension, SysOSType *type) const; 

	/**   @see IXMLAcquirerFilter::CreateStreamAndResolver
	*/
	virtual StreamResolverPair  CreateStreamAndResolver (IImportXMLData *importData, ErrorCode *errCode) const;

	/**  @see IXMLAcquirerFilter::CreateResolver
	*/
	virtual ISAXEntityResolver *  CreateResolver (IImportXMLData *importData, ErrorCode *errCode) const;

	private  :
		ErrorCode CanOpenFile(const IDFile ourFile) const;

};

CREATE_PMINTERFACE(XCatHndAcquirerFilter, kXCatHndAcquirerFilterImpl)

/*
*/
XCatHndAcquirerFilter::XCatHndAcquirerFilter(IPMUnknown* boss)
: CPMUnknown<IXMLAcquirerFilter>(boss)
{
}

/*
*/
XCatHndAcquirerFilter::~XCatHndAcquirerFilter()
{
	
}


/*
*/
int32  XCatHndAcquirerFilter::GetFileTypeCount () const
{
		if(!Utils<IXCatHndFacade>()->IsUsingAcquirerFilter()) {
		// we're not turned on, so deny any support
		return 0;
	}

	return 1;
}

/*
*/
void  XCatHndAcquirerFilter::GetNthFileType (int32 n, PMString *family, 
											 PMString *extension, SysOSType *type) const
{
	do {
		if(!Utils<IXCatHndFacade>()->IsUsingAcquirerFilter()) {
			break;
		}
		bool16 precondition = (extension && family && type);
		ASSERT(precondition);
		if(!precondition) {
			break;
		}
		// Just appear as another filter for XML import
		*extension = "xml";
		*family = "XML (with Public IDs)";
		// There appears to be a check to see if 'family' can be translated, 
		// even though it isn't translated for the UI, 
		family->SetTranslatable(kFalse);
		*type = 'TEXT';
	} while(kFalse);
}

/*
*/
StreamResolverPair XCatHndAcquirerFilter::CreateStreamAndResolver(
						IImportXMLData* importData, 
						ErrorCode* errCode) const
{
	StreamResolverPair retVal;
	if(!Utils<IXCatHndFacade>()->IsUsingAcquirerFilter()) {
		// we're not turned on
		return retVal;
	}
	ASSERT(importData);
	bool16 preconditions = importData != nil;
	if(!preconditions) {
		return retVal;
	}

	// Convert the filename into a stream
	const IDFile ourFile = importData->GetImportSource();
	ErrorCode err =  this->CanOpenFile(ourFile);
	if (err != kSuccess)
	{	
		ErrorUtils::PMSetGlobalErrorCode(err);
		*errCode = err;
		return retVal;
	}

	// Create the stream from the file by creating a link resource
	ILink * iLink = nil;
	UID resourceUID = kInvalidUID;
	IDataBase* db = importData->GetDataBase();
	// create a link. We do not know at this point if we want the link associated with the page item.
	// just create a link resource so we can get at the stream
	URI localURI;
	bool succeeded = Utils<IURIUtils>()->IDFileToURI(ourFile, localURI);
	err = Utils<Facade::ILinkFacade>()->CreateResource(db, localURI, kIDLinkClientID, PMString(), resourceUID);
	if (err==kSuccess)
	{
		InterfacePtr<ILinkResource> iLinkResource(db,resourceUID,UseDefaultIID());
		if (iLinkResource->CanQueryStream(ILinkResource::kRead))
		{
			IPMStream * newStream = iLinkResource->QueryStream(ILinkResource::kRead);
			retVal.first.reset(newStream);
		}
	}

	if (!retVal.first)
	{
		ErrorUtils::PMSetGlobalErrorCode(kImportFailedError);
		*errCode = kImportFailedError;
		return retVal;
	}
	else
	{
		retVal.second = InterfacePtr<ISAXEntityResolver> (this->CreateResolver(importData, errCode));

		if (*errCode != kSuccess)
			return StreamResolverPair();
	}

	*errCode = kSuccess;

	return retVal;

}

/*
*/
ISAXEntityResolver *  XCatHndAcquirerFilter::CreateResolver (IImportXMLData *importData, ErrorCode *errCode) const
{
	do {
		if(!Utils<IXCatHndFacade>()->IsUsingAcquirerFilter()) {
			// we're not turned on
			break;
		}
		ASSERT(importData);
		bool16 preconditions = importData != nil;
		if(!preconditions) {
			break;
		}

		// create an entity resolver
		InterfacePtr<ISAXEntityResolver> entityResolver(static_cast<ISAXEntityResolver*>(::CreateObject(kXCatHndEntityResolverBoss, ISAXEntityResolver::kDefaultIID)));
		
		InterfacePtr<ISysFileData> resolverSysFileData(entityResolver, UseDefaultIID());
		resolverSysFileData->Set(importData->GetImportSource());

		entityResolver->AddRef();

		*errCode = kSuccess;
		return entityResolver;
	} while(kFalse);
	return nil;
}


ErrorCode XCatHndAcquirerFilter::CanOpenFile(const IDFile ourFile) const 
{
	if (ourFile.Exists())
		if (ourFile.CanOpen(IDFile::kReadAccess, IDFile::kShareReadAccess))
			return kSuccess;
		else
			return kCannotOpenFileError;
	else
		return kFileNotFound;
}

