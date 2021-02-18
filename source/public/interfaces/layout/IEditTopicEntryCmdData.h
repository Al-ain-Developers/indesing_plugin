//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IEditTopicEntryCmdData.h $
//  
//  Owner: Bertrand Lechevalier
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
//  Purpose: Interface data for deleting a topic Entry
//  
//========================================================================================

#pragma once
#ifndef __IEditTopicEntryCmdData__
#define __IEditTopicEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 

class IndexTopicEntry;

/** Command data interface used for editing a topic entry.
	@ingroup layout_index
*/
class IEditTopicEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IEDITTOPICENTRYCMDDATA };

		/**	Retrieves the topic list property.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/**	Sets the topic list property.
			@param topicListUIDRef [IN] - UIDRef of the topic list.
		 */
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUIDRef) = 0;

		/**	Retrieves the initial topic property.
			@return the initial topic. 
		 */
		virtual const	IndexTopicEntry& GetFromTopicEntry() const = 0;

		/**	Sets the initial topic property.
			@param fromTopicEntry [IN] - the initial topic property.
		 */
		virtual void	SetFromTopicEntry(const IndexTopicEntry& fromTopicEntry) = 0;

		/**	Retrieves the final topic property.
			@return the final topic.
		 */
		virtual const	IndexTopicEntry& GetToTopicEntry() const = 0;

		/**	Sets the final topic property.
			@param toTopicEntry [IN] - the final topic entry.
		 */
		virtual void	SetToTopicEntry(const IndexTopicEntry& toTopicEntry) = 0;

		/**	Retrieves the UIDRef of the altered page reference during edit (if any).
			@return UIDRef of the attached page reference (if any).
		 */
		virtual const UIDRef&	GetEditedPRef() const = 0;

		/**	Sets the UIDRef of the altered page reference during edit (if any).
			Called by the command to signal callers that the page reference
			associated with the topic changed.
			@param editedPRef [IN] - UIDRef of the page reference.
		 */
		virtual void			SetEditedPRef(const UIDRef& editedPRef) = 0;
};

#endif	// __IEditTopicEntryCmdData__