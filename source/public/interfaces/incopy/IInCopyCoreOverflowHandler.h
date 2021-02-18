//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyCoreOverflowHandler.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IInCopyCoreOverflowHandler__
#define __IInCopyCoreOverflowHandler__

#include "IPMUnknown.h"

#include "InCopyCoreID.h"

class IFrameList;

/** An interface to allow InCopy to make estimates about the amount of overset text in a
	document and actually display the overset text in galley view. Story view does not need
	and makes no use of the information.
	@author Kevin Van Wiel
*/
class IInCopyCoreOverflowHandler : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_IINCOPYCOREOVERFLOWHANDLER };

	/**	Append a container to hold overset text. If this is done then InCopy
		can handle estimating the amount of text overset.
		@param UIDRef which is the story to append the container to.
	*/
	virtual bool16 AppendOversetContainer(UIDRef modelRef) = 0;
	
	/**	Unlink the overset container from the storylist
		@param sourceMultiColRef this frame to add the .
		@param destMultiColRef this is the frame that the source will be attached to
	*/
	virtual bool16 LinkOversetContainer(UIDRef sourceMultiColRef, UIDRef destMultiColRef) = 0;
	
	/**	Link the overset container from the storylist
		@param LastMultiColRefToKeep detach all frames past this frame in the frame list. Will end up creating
		 	a new story with all frames after the LastMultiColRefToKeep associated with it
	*/
	virtual bool16 UnLinkOversetContainer(UIDRef lastMultiColRefToKeep) = 0;
	
	/** Return the framelist index of the last non-overset type text frame
		@param IFrameList that we want to get the last non-overset frame index for
	*/
	virtual int32 GetLastNonOversetTextFrameIndex(const IFrameList *frameList) = 0;
};

#endif // __IInCopyCoreOverflowHandler__
