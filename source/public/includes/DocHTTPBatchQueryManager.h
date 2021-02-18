//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DocHTTPBatchQueryManager.h $
//  
//  Owner: Ramnik Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __DocHTTPBatchQueryManager__
#define __DocHTTPBatchQueryManager__
#include "IDataBase.h"
#include "URI.h"
#include <set>
#include <boost/bimap.hpp>
#include "boost/bimap/set_of.hpp"
#include "URI.h"
#include "HTTPLinkSubsystemTypes.h"

/*
 AdobePatentID="P7137-US"
 */

//Forward Declaration
class DocHTTPBatchQueryHandler;

class PUBLIC_DECL DocHTTPBatchQueryManager
{
public:
	/**
	Returns singleton instance of the class. This class assists in keeping a db to guid mapping as for scenarios during document close
	db is no longer valid. So, we would work on guid instead of db for all the required processing. The singleton is valid until program termination.
	*/
	static DocHTTPBatchQueryManager* Instance();

	// Internal use only, do not call it from outside world, destroys the singleton instance
	static void TerminateInstance();

	/*
	Retrieves the corresponding guid for the database
	@param db					[IN] database whose guid is to be retrieved
	*/
	HTTPLinkSubsystemTypes::GUID GetGuid(IDataBase*) const;

	/*
	Retrieves the corresponding database for the guid
	@param guid					[IN] guid whose database is to be retrieved
	*/
	IDataBase* GetDatabase(const HTTPLinkSubsystemTypes::GUID& guid) const;

	/*
	Generates guid for the database if required and creates a db to guid mapping
	@param db					[IN] database whose guid and db to guid mapping is to be generated
	*/
	HTTPLinkSubsystemTypes::GUID GenerateGuidAndCreateMapping(IDataBase*);

	/*
	Invalidates and clears db to guid mapping
	@param db					[IN] database whose guid and db to guid mapping is to be cleared
	*/
	bool InvalidateAndClearDBGuidMapping(IDataBase* db);

	/*
	Adds the Link Resource UID for Guid and HTTP Connection URI in the map 
	@param guid					[IN] Guid to be used instead of db whose Link resource UID info is to be kept in the map.
	@param uri                  [IN] Connection URI
	@param uid					[IN] Link resource UID
	@param type					[IN] Asset/Asset Text Fragment Link Object Type
	*/
	bool AddUIDForGuidAndConnectionURI(const HTTPLinkSubsystemTypes::GUID& guid, const URI& uri, const UID& uid, HTTPLinkSubsystemTypes::BatchRequestObjectType type);

	/*
	Removes the Link Resource UID for Guid and HTTP Connection URI in the map
	@param guid					[IN] Guid to be used instead of db whose Link resource UID info is to be removed from the map.
	@param uri                  [IN] Connection URI
	@param uid					[IN] Link resource UID
	@param type					[IN] Asset/Asset Text Fragment Link Object Type
	*/
	bool RemoveUIDForGuidAndConnectionURI(const HTTPLinkSubsystemTypes::GUID& guid, const URI& uri, const UID& uid, HTTPLinkSubsystemTypes::BatchRequestObjectType type);

	/*
	Gets the number of Link Resource UIDs for Guid and HTTP Connection URI in the map
	@param guid					[IN] Guid to be used instead of db whose Link resource UID number is to be retrieved from the map.
	@param uri                  [IN] Connection URI
	@param type					[IN] Asset/Asset Text Fragment Link Object Type
	@return the number of link resource UIDs
	*/
	size_t GetNumberOfUIDsForGuidAndConnectionURI(const HTTPLinkSubsystemTypes::GUID& guid, const URI& uri, HTTPLinkSubsystemTypes::BatchRequestObjectType type);

	/*
	Gets the Link Resource UIDs for Guid and HTTP Connection URI in the map
	@param guid					[IN]  Guid to be used instead of db whose Link resource UIDs are to be retrieved from the map.
	@param uri                  [IN]  Connection URI
	@param uidSet				[OUT] Output LinkResource UIDs
	@param type					[IN]  Asset/Asset Text Fragment Link Object Type
	@return true if the operation is successful else false
	*/
	bool GetUIDsForGuidAndConnectionURI(const HTTPLinkSubsystemTypes::GUID& guid, const URI& uri, std::set<UID> &uidSet, HTTPLinkSubsystemTypes::BatchRequestObjectType type);

private:
	/// Constructor private to restrict creation to singleton 
	DocHTTPBatchQueryManager(){}
	DocHTTPBatchQueryManager(const DocHTTPBatchQueryManager &){}
	
	typedef boost::bimap<IDataBase*, HTTPLinkSubsystemTypes::GUID> DbGuidBimap;
	typedef DbGuidBimap::left_map::const_iterator DbGuidBimap_left_const_iterator;
	typedef DbGuidBimap::right_map::const_iterator DbGuidBimap_right_const_iterator;
	typedef DbGuidBimap::value_type value_type;	
	typedef std::map<HTTPLinkSubsystemTypes::GUID, boost::shared_ptr<DocHTTPBatchQueryHandler> > GuidToDocHTTPBatchQueryHandlerMap;
	typedef GuidToDocHTTPBatchQueryHandlerMap::iterator GuidToDocHTTPBatchQueryHandlerMap_iter;
	DbGuidBimap fDbToGuidMap;
	GuidToDocHTTPBatchQueryHandlerMap fGuidToDocHTTPBatchQueryHandlerMap;
	
	static DocHTTPBatchQueryManager* _pInstance;
};
#endif // __DocHTTPBatchQueryManager__