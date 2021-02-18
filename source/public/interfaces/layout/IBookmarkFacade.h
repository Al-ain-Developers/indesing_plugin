//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookmarkFacade.h $
//  
//  Owner: Jianlan Song
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
//  
//  Note: UI facade for hyperlink feature.
//  
//========================================================================================

#pragma once

#include "Utils.h"

// ----- Interfaces -----

// ----- ID.h files -----
#include "HyperlinkID.h"

namespace Facade
{
	/** A high level API for dealing with bookmark objects.  To use this Facade, include
		this header file and use the following example syntax:
		result = Utils<Facade::IBookmarkFacade>()->CreateBookmark( ... );

	     @author Jianlan Song
	*/
	class IBookmarkFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IBOOKMARKFACADE };

		/**	Creates a new bookmark.
		
			@param destination - destination associated with the new bookmark.
			@param parentBookmark - Parent of the bookmark. 
			@param newBookmark - [OUT] Returns newly created bookmark if pointer is non-nil. 
			@param bookmarkName - name of the bookmark. Default to be empty string in which case a unique name will be generated.
			@param indentLevel - Indent level of the bookmark. Default to be 0 which is the topmost level.  

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateBookmark
							(
								UIDRef destination,
								UID parentBookmark,
								UIDRef* newBookmark = nil,
								const PMString& bookmarkName = "",
								int32 indentLevel = 0
							) = 0;
		
		/**	Deletes bookmarks.
		
			@param bookmarks - Bookmarks to be deleted. 
			@param deleteDest - kTrue if delete destinations as well. kFalse otherwise.
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode DeleteBookmark
							(
								UIDList bookmarks,
								bool16 deleteDest = kTrue
							) = 0;

		/**	Moves bookmark.
		
			@param bookmark - Bookmark to be moved. 
			@param newParent - New parent to move the bookmark to.
			@param newIndex - New index inside the parent to insert the bookmark.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode MoveBookmark
							(
								UIDRef bookmark,
								UIDRef newParent,
								int32 newIndex
							) = 0;

		/**	Rename a bookmark.
		
			@param bookmark - Bookmark to be renamed. 
			@param newName - new name for the bookmark.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameBookmark
							(
								UIDRef bookmark,
								const PMString& newName
							) = 0;
	};
}



