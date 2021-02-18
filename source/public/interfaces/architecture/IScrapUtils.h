//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScrapUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IScrapUtils__
#define __IScrapUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "UIDRef.h"

class UIDList;


/** IID_ISCRAPUTILS interface; Uitlity functions that helps make a copy of 
    item(s) adding to destination database. 
	The parameter IPMUnknown* pmobject = nil has root to as early as 1998 (change list #6), but not sure
	what it is exactly for; Our current code base has just a few instance of usage, I will list
	the usage instead.
*/
class IScrapUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRAPUTILS };


	/**  Makes a copy of each of the items on the source list. The new item is added to the destItems list. 
	       The target database for the new items is the database passed in with destItems.
		@param srcItems IN Items to copy.
		@param destItems OUT New copied items.
		@param pmobject IN ?. No usage in core code base
	*/
	virtual void CopyObjects(const UIDList *srcItems, UIDList *destItems, IPMUnknown* pmobject = nil) = 0;
		
	
	/**  Makes a copy of the source item in the target database. 
		@param srcItem IN Item to copy.
		@param *targetDB IN Target DB.
		@param pmobject IN ?.Passed in from IReferenceConverter::ConvertReference
	*/
	virtual UID CopyObject(const UIDRef& srcItem, IDataBase *targetDB, IPMUnknown* pmobject = nil) = 0;

	/**  Makes a copy of the source item in the target database. Use this function only if you are copying an object (during mapping) which is being mapped.
			This doesn't use IXReferenceUID to keep track of copy context, rather uses IMappingSession for that purpose.
		@param srcItem IN Item to copy.
		@param *targetDB IN Target DB.
		@param pmobject IN ?.Passed in from IReferenceConverter::ConvertReference
	*/
	virtual UID CopyMappedObject(const UIDRef& srcItem, IDataBase *targetDB, IPMUnknown* pmobject = nil) = 0;

	/**  Writes the source item into a temporary stream and then reads the stream into the destination item. 
		@param sourceItem IN Source item.
		@param destinationItem OUT Destination item.
		@param dirtyDestination IN Should the destination item be dirtied.
	*/
	virtual void CopyObjectInto (IPMUnknown* sourceItem, IPMUnknown* destinationItem, bool16 dirtyDestination) = 0;

	/**  Makes a copy of each of the pageitems on the srcItems. The new item is added to the destItems list. 
	       The target database for the new pageitems is the database passed in with destItems.
		@param srcItems IN Items to copy.
		@param destItems OUT Items copied.
		@param pmobject IN ?. Only usage in PasteGraphicItemCmd, pass in this pointer of Command
	*/
	virtual void CopyPageItemObjects(const UIDList *srcItems, UIDList *destItems, IPMUnknown* pmobject = nil) = 0;

	/**  Makes a copy of the source item in the target database, ignoring the IHierarchy interface
		@param srcItem IN Item to copy.
		@param *targetDB IN Target DB.
		@param pmobject IN ? No usage except called by CopyPageItemObjects.
	*/
	virtual UID CopyPageItemObject(const UIDRef& srcItem, IDataBase *targetDB, IPMUnknown* pmobject = nil) = 0;

	/**  Returns Used to check to see if a given database is the scrap database.
		@param db IN IDatabase to test.
		@return kTrue if db is the scrap database
	*/
	virtual bool16 IsScrapDB(IDataBase * db) = 0;


	/**  Internal use only - please do not use this
		Update the original layer information, which was there in the source before grouping items after the paste/drop is completed
		@param newItems IN list of pasted items.
		@return none.
	*/
	virtual void UpdateOriginalLayerOnPaste(const UIDList& items) = 0;

};


#endif	// __IScrapUtils__
