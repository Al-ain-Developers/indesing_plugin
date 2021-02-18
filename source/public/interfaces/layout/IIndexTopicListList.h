//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexTopicListList.h $
//  
//  Owner: Michel Hutinel
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
//  Comments: This class keeps track of the Index Topic lists on Session/Doc workspace.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXTOPICLISTLIST__
#define __IINDEXTOPICLISTLIST__

#include "IPMUnknown.h"
#include "IndexingID.h"

class PMString;

/** Data interface that keeps track of index topic lists on the session/document workspace.
	Currently there is only one topic list. This interface was added in case we want to support
	multiple topic lists.
	@see IIndexTopicList
	@ingroup layout_index
*/
class IIndexTopicListList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXTOPICLISTLIST };

		/**	Retrieves the number of topic lists.
			@return number of topic lists. 
		*/
		virtual const int32	GetNumTopicLists() const = 0;

		/**	Gets the default topic list.
			In the initial design this was intented to manage multiple topic lists.
			Since we have only one topic list now, this will always return the first topic list.
			@return the UID of the default topic list.
		 */
		virtual const UID	GetDefaultTopicListUID() const = 0;

		/**	Sets the default topic list.
			In the initial design this was intented to manage multiple topic lists.
			Since we currently support only one topic list this method is not used.
			@param uid [IN] - the UID of the default topic list.
		 */
		virtual void		SetDefaultTopicListUID(UID uid) = 0;

		/**	Adds a topic list to the list.
			@param indexUID [IN] - the UID of the topic list to be added to the list.
		 */
		virtual void		AddTopicList(UID indexUID) = 0;

		/**	Removes a topic list from the list.
			@param indexUID [IN] - the UID of the topic list to be removed. 
		 */
		virtual void		RemoveTopicList(UID indexUID) = 0;

		/**	Retrieves the UID of the topic list at the specified index.
			@param id [IN] - index of the desired topic list.
			@return the UID of the specified topic list.
		 */
		virtual const UID	GetNthTopicList(int32 id) const = 0;
};

#endif	// __IINDEXTOPICLISTLIST__