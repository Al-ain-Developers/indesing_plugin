//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/IXCatHndFacade.h $
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

#ifndef __IXCatHndFacade_H_DEFINED__
#define __IXCatHndFacade_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "XCatHndID.h"



/** Facade interface defining utility methods used by disparate objects
	within this plug-in, and also offers API to a potential UI plug-in to interact
	this model plug-in.

	@ingroup xmlcataloghandler
*/
class IXCatHndFacade : public IPMUnknown
{

public:

	/** Default interface identifier for UseDefaultIID 
		@see UseDefaultIID
	*/
	enum { kDefaultIID = IID_IXCATHNDFACADE };


	/**	Adds another entry to stored mapping between PUBLIC and SYSTEM ids
		@sees IXCatHndEntityMapping::AddMapping
		@param publicId 
		@param uri 
		@return ErrorCode 
	 */
	virtual ErrorCode AddPublicToUriMapping(const WideString& publicId, const WideString& uri)=0;


	/**	Given a public identifier, find associated URI referring to local system
		@param publicId 
		@return WideString 
	 */
	virtual WideString ResolvePublicToUri(const WideString& publicId)=0;


	/**	Load a catalog by file identifier
		@param catalogName 
		@return ErrorCode 
	 */
	virtual ErrorCode LoadCatalog(const IDFile& catalogName) const = 0;


	/**	Get identifier for the default XML catalog to load (for instance on startup)
		@return IDFile 
	 */
	virtual  IDFile GetDefaultXMLCatalogFile() const = 0;

	/** 
		@return kTrue if on
	*/
	virtual bool16 IsUsingAcquirerFilter() const = 0;


	/**	Get size of list of xml:base paths stored
		@param none
		@return int32 
		@see IXCatHndEntityMapping
	 */
	virtual int32 GetXMLBaseCount() const = 0;


	/**	Get an xml:base by index
		@param n 
		@return WideString 
	 */
	virtual WideString GetNthXMLBase(int32 n) const = 0;


	/**	Add another xml:base to list stored
		@param xmlBase 
		@return ErrorCode 
	 */
	virtual ErrorCode AddXMLBase(const WideString& xmlBase) =0;


	/**	Load a catalog that is in same folder as XML file to import
		@param xmlFile 
		@return ErrorCode 
	 */
	virtual ErrorCode LoadPeerCatalog(const IDFile& xmlFile) = 0;
 
	virtual  WideString TranslateURIToPlatformSpec(const WideString& uri) const = 0;

};

#endif // __IXCatHndFacade_H_DEFINED__

