//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/IGTTxtEdtSnapshotInterface.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __IGTTxtEdtSnapshotInterface_h__
#define __IGTTxtEdtSnapshotInterface_h__

#include "GTTxtEdtID.h"
class	IPMUnknown;

/** 
	Maintains the last edited story position.

	@ingroup gotolasttextedit
*/
class IGTTxtEdtSnapshotInterface : public IPMUnknown
{
public:
	/**
	*/
	enum { kDefaultIID = IID_IGTTXTEDTSNAPSHOTINTERFACE };
	
	/**
		get the cached story
		@return the story.
	*/
	virtual UIDRef& GetStory() = 0;
	/**
		set the cached story
		@param story IN the story.
	*/
	virtual void SetStory(UIDRef story) = 0;
	/**
		Is the story valid?
		@return kTrue if the story is valid.
	*/
	virtual bool16 StoryValid() = 0;
	/**
		get the text index of the story.
		@return the index within the story.
	*/
	virtual TextIndex GetStoryIndex() = 0;
	/**
		Set the cached story and the index within it.
		@param story IN the story.
		@param index IN the text index.
	*/
	virtual void SetStoryAndIndex(UIDRef story, TextIndex index) = 0;
	/**
		Set the story index.
		@param index IN the index.
	*/
	virtual void SetStoryIndex(TextIndex index) = 0;
};

#endif // __IGTTxtEdtSnapshotInterface_h__

// End, IGTTxtEdtSnapshotInterface.h.




