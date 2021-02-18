//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceFactory.cpp $
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
#include "CPMUnknown.h"
#include "ILinkResourceFactory.h"

#include "IDataBase.h"
#include "ILinkResourceHandler.h"
#include "ILinkResourceStateUpdater.h"
#include "ILinkResourceFactory.h"

#include "URI.h"
#include "WideString.h"
#include "CusDtLnkID.h"


//========================================================================================
// Class CusDtLnkLinkResourceFactory
//========================================================================================
/** Implementation of ILinkResourceFactory to instantiate couple link resource related classes, 
	ILinkResourceHandler and ILinkResourceStateUpdater, both are aggregated on 
	kCusDtLnkLinkResourceHandlerBoss, and they are to handle link resource who has the URI scheme
	of 'CSVLink'
	
	@ingroup customdatalink
*/
class CusDtLnkLinkResourceFactory : public CPMUnknown<ILinkResourceFactory>
{
public:
    typedef CPMUnknown<ILinkResourceFactory> inherited;
	typedef object_type data_type;

	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkLinkResourceFactory(IPMUnknown* boss);
	/**	Destructor.
	*/
	virtual ~CusDtLnkLinkResourceFactory();

	/**
	 Returns the list of URI schemes supported by the handler, which in our case, CSVLink.
	 
	 @see ILinkResourceFactory::GetSchemes
	 @param schemes [OUT] List of supported schemes.
	 */ 
	virtual void GetSchemes(K2Vector<WideString>& schemes) const;
	/**
	 Returns the link resource handler, kCusDtLnkLinkResourceHandlerBoss, that handles our 'CSVLink' type resource.
	 
	 @see ILinkResourceFactory::GetSchemes
	 */ 
	virtual ILinkResourceHandler* QueryHandler(const URI& uri, IDataBase* db) const;

	/**
	 Returns the link resource state updater who provides status update for link resource whose URI scheme is 'CSVLink'	 
	 @see ILinkResourceFactory::QueryStateUpdater
	 */ 
	virtual ILinkResourceStateUpdater* QueryStateUpdater(const URI& uri, IDataBase* db) const;

private:
	// Prevent copy construction and assignment.
	CusDtLnkLinkResourceFactory(const CusDtLnkLinkResourceFactory&);
	CusDtLnkLinkResourceFactory& operator=(const CusDtLnkLinkResourceFactory&);
};

CREATE_PMINTERFACE(CusDtLnkLinkResourceFactory, kCusDtLnkLinkResourceFactoryImpl)


//========================================================================================
//
// CusDtLnkLinkResourceFactory Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceFactory::CusDtLnkLinkResourceFactory(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkResourceFactory::~CusDtLnkLinkResourceFactory()
{
}

//========================================================================================
// CusDtLnkLinkResourceFactory::GetSchemes
//========================================================================================
static const WideString k_fileScheme(kCusDtLnkScheme);
void CusDtLnkLinkResourceFactory::GetSchemes(K2Vector<WideString>& schemes) const
{

	schemes.clear();
	schemes.push_back(k_fileScheme);
}

//========================================================================================
// CusDtLnkLinkResourceFactory::QueryHandler
//========================================================================================
ILinkResourceHandler* CusDtLnkLinkResourceFactory::QueryHandler(const URI& uri, IDataBase* db) const
{
	return ::CreateObject2<ILinkResourceHandler>(kCusDtLnkLinkResourceHandlerBoss);
}

//========================================================================================
// FileLinkResourceFactory::QueryStateUpdater
//========================================================================================
ILinkResourceStateUpdater* CusDtLnkLinkResourceFactory::QueryStateUpdater(const URI& uri, IDataBase* db) const
{
	return ::CreateObject2<ILinkResourceStateUpdater>(kCusDtLnkLinkResourceHandlerBoss);
}
