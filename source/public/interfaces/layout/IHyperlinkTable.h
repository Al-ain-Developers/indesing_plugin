//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTable.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IHyperlinkTable__
#define __IHyperlinkTable__

#include "IPMUnknown.h"
#include "HyperlinkID.h"
#include <map>

class UIDList;

typedef std::map< int32, UID> UniqueKeyToUIDMap;

/** Interface on the document (kDocBoss) that 
	manages references to hyperlink sources, destinations and hyperlinks.

 An interface off the document, contains four lists:
\li the hyperlink sources defined in this document
\li the hyperlink destinations defined in this document
\li the hyperlinks defined in this document (the connection between the
sources & destinations)
\li the bookmarks defined in the document

Note 1 : there is no requirement that the number of sources match the number of destinations, or the
number of hyperlinks. i.e. a hyperlink is valid if either the source or destination (or both) 
is (are) valid.

Note 2 : this table manages references to hyperlink sources, destinations and hyperlinks, but does not
create or delete the sources, destinations, or hyperlink UIDs.


	@ingroup layout_hyper
	@see kHyperlinkBoss
	@see IHyperlinkSource
	@see IHyperlinkDestination
	@see IHyperlink
*/
class IHyperlinkTable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTABLE };

	/** Use this to indicate which type of object needs its cache updated */
	typedef enum {
		/** Update hyperlink names */
		kHyperlinks,
		/** Update source names */
		kSources,
		/** Update destination names */
		kDestinations,
		/** Update bookmark names */
		kBookmarks,
		/** Update cross reference format names */
		kXRefFormats,
		/** Update all names */
		kAll} WhichCache;

	/** Invalidate the name cache for items stored in this table
		You need to call this anytime the name of a hyperlink/source/destination/bookmark
		changes so that the code for generating a new name will be right.
		@param whichCache - Indicates what type of item you changed.
	*/
	virtual void InvalidateNameCache(IHyperlinkTable::WhichCache whichCache) = 0;

	/** Returns kTrue if there is any hyperlink point to external destination.
	*/
	virtual bool16 HasExternalDestination() const = 0;

	/** Sets the flag indicating if there is any hyperlink pointing to external destination.
		This method is only for conversion purpose and most time you should not set the flag manually.
	*/
	virtual void SetHasExternalDestination(bool16 fHasExternDest) = 0;
	
	//----------------------------------------------------------------------------------------------//
	// Sources:
	//----------------------------------------------------------------------------------------------//

	/**	Add a new hyperlink source
		@param hyperlinkSource - UID to add
	 */
	virtual void AddHyperlinkSource(const UID hyperlinkSource) = 0;	

	/**	remove a hyperlink source. May orphan a hyperlink destination (i.e.
		can end up with a target with no sources (in this document)
		@param hyperlinkSource - Source to remove
	 */
	virtual void RemoveHyperlinkSource(const UID hyperlinkSource) = 0;

	/**	Return the number of hyperlink sources defined in this document
		@param none
		@return int32 - Number of hyperlink sources in the Table
	 */
	virtual int32 GetHyperlinkSourceCount() const = 0;

	/**	Use for indexing through defined hyperlink sources
		@param hyperlinkIndex - Index that we want the UID for
		@return UID - UID of expected source
	 */
	virtual UID GetNthHyperlinkSource(int32 hyperlinkIndex) const = 0;

	/**	return the index of the specified hyperlink source in the table
		@param hyperlinkSourceUID - UID to get the index of
		@return int32 - Index of source
	 */
	virtual int32 GetHyperlinkSourceIndex(const UID hyperlinkSourceUID) const = 0;

	/**	Generates a unique hyperlink source name, of the form
		// "Source_1", "Source_1", ....
		@param pName - Default name to try to use
	 */
	virtual void GenerateNewHyperlinkSourceName(PMString* pName)  = 0;

	//----------------------------------------------------------------------------------------------//
	// Destinations (a.k.a. target; a.k.a. anchor):
	//----------------------------------------------------------------------------------------------//

	/**	Add a new hyperlink destination
		@param hyperlinkDestination - Destination to add
	 */
	virtual void AddHyperlinkDestination(const UID hyperlinkDestination) = 0;

	/**	Remove a hyperlink destination
		@param hyperlinkDestinationKey - Unique key of the destination to remove
	 */
	virtual void RemoveHyperlinkDestination(int32 hyperlinkDestinationKey) = 0;

	/**	Swap the UIDs of two keys in the destination map
		@param destKey1 - Unique key of the first destination
		@param destKey2 - Unique key of the second destination
	 */
	virtual void  SwapHyperlinkDestinations(int32 destKey1, int32 destKey2) = 0;
	
	/**	Return the number of hyperlink destinations defined in this document
		@param none
		@return int32 - Number of destinations in the table
	 */
	virtual int32 GetHyperlinkDestinationCount() const = 0;

	/**	Check if the index of the specified hyperlink destination is in the table
		@param hyperlinkDestinationKey
		@return bool16 - kTrue if the destination key is found in the table
	 */
	virtual bool16 IsValidHyperlinkDestinationKey(int32 hyperlinkDestinationKey) const = 0;

	/**	Given a unique key, retrieve the UID of the hyperlink destination
		@param hyperlinkKey - Unique key for the destination
		@return UID - UID of the specified destination
	 */
	virtual UID GetHyperlinkDestinationWithKey(int32 hyperlinkKey) const = 0;
	
	/**	Generates a unique hyperlink destination name, of the form
		"Anchor_1", "Anchor_1", ....
		@param pName - Default name to try to use
	 */
	virtual void GenerateNewHyperlinkDestinationName(PMString* pName)  = 0;

	/** Returns the begin iterator of destination map
	*/
	virtual UniqueKeyToUIDMap::const_iterator GetDestinationKeyToUIDMapBeginIter() const = 0;

	/** Returns the end iterator of destination map
	*/
	virtual UniqueKeyToUIDMap::const_iterator GetDestinationKeyToUIDMapEndIter() const = 0;
	
	/** Returns the reverse begin iterator of destination map
	*/
	virtual UniqueKeyToUIDMap::const_reverse_iterator GetDestinationKeyToUIDMapRBeginIter() const = 0;
	
	/** Returns the reverse end iterator of destination map
	*/
	virtual UniqueKeyToUIDMap::const_reverse_iterator GetDestinationKeyToUIDMapREndIter() const = 0;
	
	//----------------------------------------------------------------------------------------------//
	// Hyperlinks:
	//----------------------------------------------------------------------------------------------//

	/**	Add a new hyperlink
		@param hyperlink - UID of hyperlink to add
	 */
	virtual void AddHyperlink(const UID hyperlink) = 0;

	/**	Remove the hyperlink 'UID'
		@param hyperlinkUID - UID of hyperlink to remove
		@return UID of the source that used to be associated with this hyperlink
	 */
	virtual UID RemoveHyperlink(const UID hyperlinkUID) = 0;

	/**	Move a hyperlink around in the table
		@param hyperlink - UID of hyperlink to move
		@param moveBefore - UID of hyperlink we are trying to move before (kInvalidUID == move to end)
	 */
	virtual void MoveHyperlink(const UID hyperlink, const UID moveBefore) = 0;

	/**	Use for indexing through defined hyperlinks
		@param hyperlinkIndex - Index of hyperlink we want
		@return UID - UID of specified hyperlink
	 */
	virtual UID GetNthHyperlink(int32 hyperlinkIndex) const = 0;

	/**	Use for locating a specified hyperlink
		@param hyperlink - UID of hyperlink we want
		@return int32 - Index of specified hyperlink
	 */
	virtual int32 GetHyperlinkWithUID(const UID hyperlink) const = 0;

	/**	Return the number of hyperlinks defined in this document
		@param none
		@return int32 - Number of hyperlinks in this table
	 */
	virtual int32 GetHyperlinkCount() const = 0;

	/**	Generates a unique hyperlink destination name, of the form
		// "Hyperlink_1", "Hyperlink_1", ....
		@param pName - Default name to use
	 */
	virtual void GenerateNewHyperlinkName(PMString* pName)  = 0;

	/**	given the source UIDRef, return the UID of the Hyperlink that uses it. 
		@param sourceUIDRef - Source to find a hyperlink for
		@return UID - Returns kInvalidUID if the source isn't used at all.
	 */
	virtual	UID	GetHyperlinkOfSource(UIDRef sourceUIDRef) const = 0;

	//----------------------------------------------------------------------------------------------//
	// Bookmarks:
	//----------------------------------------------------------------------------------------------//

	/**	Add a new bookmark
		@param bookmark - UID of bookmark to add
	 */
	virtual void AddBookmark(const UID bookmark) = 0;

	/**	Remove the Bbookmark 'UID'
		@param bookmarkUID - UID of bookmark to remove
	 */
	virtual void RemoveBookmark(const UID bookmarkUID) = 0;

	/**	Move a bookmark to a new location
		@param bookmark - Bookmark to move
		@param newLoc - New location of the bookmark (-1 will move to the end of the list)
	 */
	virtual void MoveBookmark(const UID bookmark, int32 newLoc) = 0;

	/**	Use for indexing through defined bookmark
		@param bookmarkIndex - Index of the bookmark you want
		@return UID - UID of the specified bookmark
	 */
	virtual UID GetNthBookmark(int32 bookmarkIndex) const = 0;

	/**	Use for locating a specified bookmark
		@param bookmark - UID of the bookmark you want
		@return int32 - Index of the specified bookmark
	 */
	virtual int32 GetBookmarkWithUID(const UID bookmark) const = 0;

	/**	Return the number of bookmark defined in this document (This ignored the
		bookmark hierarchy)
		@param none
		@return int32 - Number of bookamrks in this document
	 */
	virtual int32 GetBookmarkCount() const = 0;

	/**	Generates a unique bookmark name, of the form
		// "Bookmark_1", "Bookmark_2", ....
		@param pName - Default name to try to use
	 */
	virtual void GenerateNewHyperlinkBookmarkName(PMString* pName)  = 0;

	//----------------------------------------------------------------------------------------------//
	// XRef formats:
	//----------------------------------------------------------------------------------------------//

	/**	Add a new cross reference format
		@param xRefFormat - UID of format to add
	 */
	virtual void AddXRefFormat(const UID xRefFormat) = 0;
	
	/**	Remove the cross reference format 'UID'. Only custom defined format can be removed.
		@param xRefFormat - UID of custom defined cross reference format to remove
		@return bool16 - kTrue if the format is removed successfully, kFalse otherwise. 
						We return kFalse if the format is one of the application default formats.
	 */
	virtual bool16 RemoveXRefFormat(const UID xRefFormat) = 0;

	/**	Return the number of cross reference format defined in this document 
		@return int32 - Number of cross reference formats in this document
	 */
	virtual int32 GetXRefFormatCount() const = 0;

	/**	Use for indexing through defined cross reference format
		@param formatIndex - Index of the format you want
		@return UID - UID of the specified format
	 */
	virtual UID GetNthXRefFormat(int32 formatIndex) const = 0;
	
	/**	return the index of the specified cross reference format in the table
		@param xRefFormatUID - UID to get the index of
		@return int32 - Index of format
	 */
	virtual int32 GetXRefFormatIndex(const UID xRefFormatUID) const = 0;

	/**	return kTrue if the specified format name already exists.
		@param name - x-ref format name to check
		@return bool16 - kTrue if the name exists, otherwise return kFalse.
	 */
	virtual bool16 HasXRefFormatName(const PMString& name) = 0;

	/**	return UID of the format with specified name if the namealready exists.
		@param name - x-ref format name to check
		@return bool16 - UID of the format if the name exists, otherwise kInvaludUID.
	 */
	virtual UID GetXRefFormatOfName(const PMString& name) = 0;

	/**	Generates a unique cross reference format name, of the form
		// "cross reference format_1", "cross reference format_2", ....
		@param pName - Default name to try to use
	 */
	virtual void GenerateNewXRefFormatName(PMString* pName)  = 0;
};


#endif // __IHyperlinkTable__

