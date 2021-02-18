//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexXRefLinkData.h $
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
//  Comments: This interface saves the information about a Index XRef link.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXXREFLINKDATA__
#define __IINDEXXREFLINKDATA__

#include "IPMUnknown.h"
#include "IndexingID.h"

/** Data interface used to hold information about cross-reference index links.
	The data stored contains the UID of the topic section which owns this entry and
	the UIDs of the cross-references that reference this entry.
	@ingroup layout_index
*/
class IIndexXRefLinkData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXXREFLINKDATA };
		
		/** Gets the UID of the topic section that owns this topic.
			@return the UIDRef of the topic section.
		*/
		virtual const UID		GetTopicSectionUID() const = 0;		

		/** Sets the UID of the topic section that owns this topic.
			@param topicSectionUID [IN] - the UIDRef of the topic section.
		*/
		virtual void			SetTopicSectionUID(const UID topicSectionUID) = 0;

		/** Gets the number of cross-references to this topic.
			@return the number of cross-references.
		*/
		virtual const int32		GetNumBackXRefUIDs() const = 0;

		/** Gets the UID of the cross-reference at the specified index.
			@return the UID of the cross-reference at the specified index.
		*/
		virtual const UID		GetNthBackXRefUID(int32 id) const = 0;

		/** Adds a cross-reference to this topic.
			@param backXRefUID [IN] - UID of the cross-reference that points to this topic.
			@return kTrue if the cross-reference was successfully added.
		*/
		virtual bool16			AddBackXRefUID(const UID backXRefUID) = 0;

		/** Removes a cross-reference to this topic.
			@param backXRefUID [IN] - UID of the cross-reference to be removed.
			@return kTrue if the cross-reference was successfully removed.
		*/
		virtual bool16			RemoveBackXRefUID(const UID backXRefUID) = 0;
};

#endif // __IINDEXXREFLINKDATA__