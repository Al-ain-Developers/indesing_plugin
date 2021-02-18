//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookData.h $
//  
//  Owner: Matt Phillips
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

#pragma once

#include "IPMUnknown.h"
#include "PreflightObjectID.h"
#include "PackageAndPreflightID.h"

class IPreflightBookContentData;
class IPreflightBookOptions;
class IBook;
class IPreflightAggregatedResults;

/**	This interface maintains the data/status for a particular book preflight operation.
	@see IPreflightBookOptions for the options used for this preflight.
	@see IPreflightBookController which is typically used to drive the process at a higher level.
*/
class IPreflightBookData: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKDATA };

public:
	/** Set the book this preflight is associated with. Note that this should only be done
		as part of initializing this interface.

		@param iBook The book interface. This interface is NOT refcounted by this method;
			only the database is recorded. This is to avoid circular references since the
			book (@see IPreflightBookRef) has a refcount on this interface.
	*/
	virtual void SetBook(IBook* iBook) = 0;

	/** Get the book this preflight is associated with.
		@return A refcounted book interface.
	*/
	virtual IBook* QueryBook() const = 0;

	/** Queries the options used for preflighting the book. This is usually just a copy of
		the persistent options for the book but will be different for, say, a package operation.
	*/
	virtual IPreflightBookOptions* QueryOptions() const = 0;

	/** Clear all of the data mapping.
	*/
	virtual void ClearData() = 0;

	/** Set the data to associate with the given content UID.

		@param contentUID IN The UID for which to set the associated data.
		@param iData IN The new data. If nil, the data is cleared (removed from the map). 
			If not nil this is refcounted and the old data is replaced with the new one.
	*/
	virtual void SetDataForContent(UID contentUID, IPreflightBookContentData* iData) = 0;

	/** Given a book content UID, get the corresponding information (if any) for the 
		preflight results/status of that content.

		@param contentUID IN The UID of the content in which you're interested.
		@return A refcounted entry or nil if there is no entry.
	*/
	virtual IPreflightBookContentData* QueryDataForContent(UID contentUID) const = 0;

	/** Create a new content data association for the book data. Erases any content
		already there. Note that this does an implicit SetDataForContent with the
		new data interface.

		@param contentUID IN The book content UID you want to create an association for.
		@return A refcounted content data interface, pre-associated to the book content.
	*/
	virtual IPreflightBookContentData* CreateDataForContent(UID contentUID) = 0;

	/** Find the content data with a given process ID.
		@param processID IN The process ID you seek.
		@return The UID of the content, or kInvalidUID if no such process was found.
	*/
	virtual UID FindContentByProcessID(uint32 processID) const = 0;

	/** Get the list of chapters/content for which we have mapping information.
		@param theList OUT Receives the list. Cleared before filling.
	*/
	virtual void GetContentList(UIDList& theList) const = 0;

	/** Create an aggregated version of the book preflight results.
		@param pList IN If not nil, provides the content UIDs to generate results for (and the order).
			If nil, all chapters with results will be included.
		@return A refcounted aggregated results, or nil if some kind of error occurs.
	*/
	virtual const IPreflightAggregatedResults* CreateAggregatedResults(const UIDList* pList) const = 0;

};

