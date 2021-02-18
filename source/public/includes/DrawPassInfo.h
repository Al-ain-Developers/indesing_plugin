//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DrawPassInfo.h $
//  
//  Owner: dwaterfa
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
#ifndef __DrawPassInfo__
#define __DrawPassInfo__

#include "K2Vector.h"
#include "IPMStream.h"


//
// The drawing of Parcels is organized through the use of DrawPassInfo
// and DrawPriorities. Standard page items get a single call to draw through
// their IShape interface and internally various logical passes are made
// across the page item for the stoke, fill, page item adornments, text, etc.
//
// The Text system requires a finer and more efficient notion of draw order
// than is available through the background, before foreground, after
// foreground, etc type of arrangement. Their system has been adapted from
// ITextAdornment.h through TextDrawPriority.h and now, hopefully, finally
// ends here.
//
// DrawPassInfo is made up of the following elements - 
//
//	Pass		This is the "pass" portion of a valid DrawPriority expressed as
//				an integer.
//
//	ClassID		This is the ClassID of the boss that optionally requires this
//				pass. If this element is equal to kInvalidClass then the pass
//				is required, not optional.
//
//				The boss of an optional pass must have an
//				IID_IGLOBALTEXTADORNMENT interface and return kTrue for
//				GetIsActive().
//
//				The idea here is that some passes across the Parcel are only
//				needed if some external state is set appropriately. If the
//				ONLY reason the pass exists is because of this boss then we
//				will not make the pass if the boss is not active.
//
//				Note that if some Parcel has two elements sharing the same
//				pass, one which is optional and one which is required, then the
//				pass will always be made without regard to the optional boss.
//
// A good example of how this is used is the GlobalTextAdornment ShowInvisibles.
// ShowInvisibles wants to draw at kPassPriForeground but by being optional,
// unless it is active we do not make the extra pass.
//
namespace Text {

class DrawPassInfo
{
public:
	typedef base_type data_type;
	//
	// Passes are expressed on a 16 bit scale with lower pass numbers having
	// a higher priority (get drawn first) than higher pass numbers (drawn
	// later).
	//
	// We have defined three well known pass numbers to assist people in
	// selecting appropriate pass values. Note that a full pass over a Parcel
	// is expensive so unless you have a special reason, most usages to use
	// one of these three pre-defined passes.
	//
	// See TextDrawPriority for more information and examples.
	//
	typedef int32	Pass;

	enum {
		kPassMax		= -32768,
		kPassBackground	= -16384,
		kPassText		= 0,
		kPassForeground	= 16384,
		kPassMin		= 32767
	};

	DrawPassInfo() :
		fPass(kPassMin)
		{ }
	DrawPassInfo(Pass pass, ClassID id) :
		fPass(pass), fID(id)
		{ }
	Pass	GetPass() const
		{ return fPass; }
	void	SetPass(Pass pass)
		{ fPass = pass; }
	ClassID	GetClassID() const
		{ return fID; }
	void	SetClassID(ClassID id)
		{ fID = id; }

	bool16	operator==(const DrawPassInfo& t) const
		{
		return ((fPass == t.fPass) && (fID == t.fID));
		}

	void	ReadWrite(IPMStream *s, ImplementationID)
		{
		s->XferInt32(fPass);
		s->XferID(fID);
		}

private:
	Pass	fPass;
	ClassID	fID;

};

typedef K2Vector<DrawPassInfo>	DrawPassInfoList;

}

#endif
