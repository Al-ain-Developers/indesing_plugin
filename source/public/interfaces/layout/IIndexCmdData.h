//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexCmdData.h $
//  
//  Owner: Yves Carbonneaux
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
//  Purpose: This is generic interface for setting/getting command data during creating and generating Index.
//  
//========================================================================================

#pragma once
#ifndef __IIndexCmdData__
#define __IIndexCmdData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "IndexingID.h"


class WideString;

/** Command data interface used during index generation.
	@ingroup layout_index
*/
class IIndexCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXCMDDATA };

		/**	Retrieves the target location (usually the doc workspace) where the index will be placed.
			@return the UIDRef of the target.
		 */
		virtual const UIDRef& GetTargetItemRef() const = 0;

		/**	Sets the target location (usually the doc workspace) of the index.
			@param sourceItem [IN] - UIDRef of the target.
		 */
		virtual void SetTargetItemRef(const UIDRef& sourceItem) = 0;

		/**	Specifies the destination text frame.
			Used by GenerateIndexCmd after it creates the new text frame.
			@param textFrameItem [IN] - the UIDRef of the text frame.
		 */
		virtual void SetTextFrameRef(const UIDRef& textFrameItem) = 0;

		/**	Retrieves the destination text frame.
			@return UIDRef of the text frame.
		 */
		virtual UIDRef GetTextFrameRef() const = 0;
		
		/**	Retrieves the "replace existing index" flag.
			@return the flag value.
		 */
		virtual const bool16 GetReplaceExistingIndexFlag() const = 0;

		/**	Sets the "replace existing index" flag.
			A kTrue value will cause an existing index to be replaced with the new one.
			@param replaceExistingIndex [IN] - flag value.
		 */
		virtual void SetReplaceExistingIndexFlag(bool16 replaceExistingIndex) = 0; 

		/**	Specifies if the index frame should be vertical or horizontal (default).
			Used for the J version of InDesign.
			@see IIndexOptions::FrameType
			@return kTrue if the index frame is vertical.
		 */
		virtual const bool16 GetVerticalFlag() const = 0;

		/**	Specifies if the index frame should be vertical or horizontal (default).
			Used for the J version of InDesign.
			@see IIndexOptions::FrameType
			@param bVertical [IN] - flag value.
		 */
		virtual void SetVerticalFlag(bool16 bVertical) = 0;

		/**	Sets the topic list used for the index.
			@param topicListRef [IN] - the UIDRef of the topic list.
		 */
		virtual void SetTopicListRef(const UIDRef& topicListRef) = 0;

		/**	Retrieves the topic list used for the index.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef GetTopicListRef() const = 0;
		
		/**	Sets the text model property.
			@param textModelRef [IN] - UIDRef of the text model.
		 */
		virtual void SetTextModelRef(const UIDRef& textModelRef) = 0;

		/**	Retrieves the text model property.
			@return UIDRef of the text model. 
		 */
		virtual const UIDRef GetTextModelRef() const = 0;

		/**	Retrieves the title of the index instance.
			@return the title.
		 */
		virtual const WideString& GetTitle() const = 0;

		/**	Sets the title of the index instance.
			@param indexTitle [IN] - the new title.
		 */
		virtual void SetTitle(const WideString& indexTitle) = 0;

		// --- Get/Set include overset flag

		/**	Retrieves the "include overset text" flag.
			@return the flag value. 
		 */
		virtual const bool16& GetIncludeOversetFlag() const = 0;

		/**	Sets the "include overset text" flag.
			@param includeOverset [IN] - the flag value.
		 */
		virtual void SetIncludeOversetFlag(const bool16& includeOverset) = 0;
};

#endif	// __IIndexCmdData__