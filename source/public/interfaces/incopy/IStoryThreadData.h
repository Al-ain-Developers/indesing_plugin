//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryThreadData.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __IStoryThreadData__
#define __IStoryThreadData__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "UIDRef.h"


/** 
	A specific type storage interface, used in a story related view to story information about what text story thread is currently displayed
	(as the primary text) in the view. For a view that display's the primary story as it's main text GetStoryThreadDictUID()
	will be kInvalidUID and GetStoryThreadKey() will be -1. These views may in fact display text from other story threads
	for instance inline notes may be displayed but it's the primary text a view displays that is relevant. May be reused as
	a generic container for story thread information if desired.
*/
class IStoryThreadData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTORYTHREADDATA };
		
		/**
			Get a story thread uid
			@return uid of the story thread (see ITextModel)
		**/
		virtual UID GetStoryThreadDictUID() = 0;
		
		/**
			Get a story thread key
			@return story thread key (see ITextModel)
		**/
		virtual int32 GetStoryThreadKey() = 0;
		
		/**
			Database the story lives in
			@return database story thread lives in.
		**/		
		virtual IDataBase* GetStoryThreadDatabase() = 0;
		
		/**
			Set up information returned in the above information
			@param storyThreadDict - uid of story thread (see ITextModel)
			@param storyThreadKey - key of story thread (see ITextModel)
			@param storyThreadDB - database story thread live in
			@return none
		**/		
		virtual void Set(UID storyThreadDict, int32 storyThreadKey, IDataBase* storyThreadDB) = 0;
};

#endif 		// __IStoryThreadData__