//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDeleteIndexPageEntryCmdData.h $
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
//  Purpose: Interface data for deleting an Index Page Entry
//  
//========================================================================================

#pragma once
#ifndef __IDeleteIndexPageEntryCmdData__
#define __IDeleteIndexPageEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"

/** Command data interface used for deleting an index page entry.
	@ingroup layout_index
*/
class IDeleteIndexPageEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDELETEINDEXPAGEENTRYCMDDATA };

		/**	Retrieves the "delete marker" flag value.
			@return the flag's value.
		 */
		virtual bool16	GetDeleteMarkerFlag() const = 0;

		/**	Sets the "delete marker" flag for the command.
			If set to kTrue it will delete the index marker from the story.
			@param deleteMarker [IN] - the flag's value.
		 */
		virtual void	SetDeleteMarkerFlag(bool16 deleteMarker) = 0;

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16	GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			@param notify [IN] - value of the flag.
		 */
		virtual void	SetDoNotifyFlag(bool16 notify) = 0;

		/**	Retrieves the topic list property.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/**	Sets the topic list property.
			No need to SetTopicListUIDRef outside of Indexing plugin.
			@param topicListUID [IN] - UIDRef of the topic list.
		 */		
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUID) = 0;

		/**	Retrieves the topic section UID property.
			(Only used by Indexing and Indexing Panel).
			@return UID of the topic section.
		 */
		virtual const UID	GetTopicSectionUID() const = 0;

		/**	Sets the topic section UID property.
			(Only used by Indexing and Indexing Panel).
			@param topicSectionUID [IN] - UID of the topic section.
		 */
		virtual void		SetTopicSectionUID(const UID topicSectionUID) = 0;

		/**	Retrieves the topic node id.
			(Only used by Indexing and Indexing Panel).
			@return the topic node id.
		 */
		virtual int32	GetTopicNodeId() const = 0;

		/**	Sets the topic node id.
			(Only used by Indexing and Indexing Panel).
			@param indexTopicNodeId [IN] - the topic node id. 
		 */
		virtual void	SetTopicNodeId(int32 indexTopicNodeId) = 0;

};

#endif	// __IDeleteIndexPageEntryCmdData__