//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IRecomposedFrames.h $
//  
//  Owner: zwilliam
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
#ifndef __IRecomposedFrames__
#define __IRecomposedFrames__

#include "IPMUnknown.h"
#include "TextID.h"


/** IRecomposedFrames is used to buffer up a list of text frames that have
	undergone some kind of recomposition, so that at the end of the composition
	operation, we can broadcast on all of them at once. Things like the paragraph
	composer, keeps fuctionality, and footnotes can all cause more frames to be
	operated on than initially expected.
	Each IFrameList has this interface.
	@see IFrameList
	@ingroup text_comp
*/
class IRecomposedFrames : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRECOMPOSEDFRAMES };

	/** Add the specified text frame to the list of frames affected by composition.
		@param frameUID is the UID of the text frame that was affected.
	*/
	virtual void AddFrameToList(UID frameUID) = 0;

	/** Remove a text frame from the list, if it is there.
		Generally used when text frames are deleted, since the broadcast clears the normal case.
		@param frameUID is the text frame to remove.
	*/
	virtual void RemoveFrameFromList(UID frameUID) = 0;

	/** Used for iteration through the list, get an indexed text frame.
		May not handle bad indices.
		@param i is the index within this interface's list.
		@return the correct Text Frame's UID.
	*/
	virtual UID GetNthFrameUID(int32 i) = 0;

	/** Used for iteration through the list, get the number of text frames.
		@return the number of text frame UIDs on this list.
	*/
	virtual int32 GetFrameCount() = 0;

	/** Broadcast the recomposition message for the frames
		and clear the list. Also may do the screen inval.
	*/
	virtual void BroadcastRecompositionComplete() = 0;
};

#endif
