//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAnchoredObjectAlternateFrameAlign.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IANCHOREDOBJECTALTERNRATEFRAMEALIGN__
#define __IANCHOREDOBJECTALTERNRATEFRAMEALIGN__

#include "IPMUnknown.h"
#include "TextID.h"


class IHierarchy;

/**
	IAnchoredObjectAlternateFrameAlign is an interface that allows a third party developer to change the page item
	that is used for the anchored object align to frame setting. Without this interface, the frame to which an
	anchored object will be aligned is the one that is the grandparent of the text frame column containing the anchored
	object marker (i.e. the spline). By adding this interface to the kSplineBoss, a third party can specify that a different ancestor
	page item be used when the kFrameRelativeV and kFrameRelativeH anchor point objects are in effect.
	The classic use case for this interface is if a developer wishes to implement a container page item that has
	one or more spline text frames, and wishes for the anchored object to align to the container page item rather than
	the child spline text frame.
	If this interface is present on the kSplineBoss, the implementation *must* return a non-nil IHierarchy pointer.
	Note: If the geometry of the alternate page item changes, the anchored object is not guaranteed to be realigned
	to the new page item geometry. Therefore, somewhere else in their code, implementors of this interface are also
	responsible for calling IInlineData::InlineChangeDamage() if geometry of the alignment page item frame is modified.
	@ingroup text_layout
*/
class IAnchoredObjectAlternateFrameAlign : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANCHOREDOBJECTALTERNATEFRAMEALIGN };

	/** Get the IHierarchy interface of page item whose frame the anchored object should be aligned to.
		@return an AddRef'd IHierarchy interface of the page item.
	*/
	virtual IHierarchy* QueryAlignmentFrame() = 0;
};

#endif
		// __IANCHOREDOBJECTALTERNRATEFRAMEALIGN__

