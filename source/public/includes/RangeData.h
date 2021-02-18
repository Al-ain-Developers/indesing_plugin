//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RangeData.h $
//  
//  Owner: sheridan
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __RangeData__
#define __RangeData__


#include "BaseType.h"
#include "K2Assert.h"
#include <algorithm> //for std::min, std::max, std::swap

//forward declarations
class RangeData;
inline RangeData Join( const RangeData& x, const RangeData& y, const RangeData* clip = nil);
inline RangeData SlideForward( const RangeData& x, int32 y, const RangeData* clip = nil);
inline RangeData AdvanceEnd(   const RangeData& x, int32 y, const RangeData* clip = nil);
inline RangeData RecedeStart(  const RangeData& x, int32 y, const RangeData* clip = nil);
inline bool16 operator==(const RangeData& lhs, const RangeData& rhs);
inline RangeData EndLocation( const RangeData& x);
inline RangeData StartLocation( const RangeData& x);


class PUBLIC_DECL RangeData
{
public:
	//types
	typedef base_type data_type; //K2Vector requirement
	enum Lean { kLeanForward = 0, kLeanForth = kLeanForward, kLeanBack = 1, kLeanBackward = kLeanBack};
	enum {kDontConsiderLean = 0, kIgnoreLean = kDontConsiderLean, kConsiderLean = 1};

	//Constructors
    RangeData( const RangeData& r) noexcept = default;
    RangeData( RangeData&& r) noexcept = default;
	RangeData( const RangeData& r, const RangeData* clip);
	RangeData( TextIndex start, TextIndex end, const RangeData* clip = nil);
	RangeData( TextIndex caret, Lean lean, const RangeData* clip = nil);
	RangeData( TextIndex start, TextIndex end, Lean lean, const RangeData* clip = nil);

    RangeData &operator =(const RangeData &) noexcept = default;
    RangeData &operator =(RangeData &&) noexcept = default;

	//Accessors
	TextIndex Start(Lean* lean) const { if(lean) *lean = fLean; return fStart;}
	TextIndex End() const { return fEnd;}
	int32 Length() const { return fEnd - fStart;}

	//Predicates
	int32  OverlapWith( const RangeData& other) const;
	bool16 StartsBefore( const RangeData& other, bool16 consideringLean = kIgnoreLean) const;
	bool16 EndsAfter( const RangeData& other, bool16 consideringLean = kIgnoreLean) const;
	bool16 Precedes( const RangeData& other) const;
	bool16 Leads( const RangeData& other) const;
	bool16 Succeeds( const RangeData& other) const;
	bool16 Follows( const RangeData& other) const;
	bool16 CompletelyPrecedes( const RangeData& other) const { return fEnd <= other.fStart;}
	bool16 Contains( const RangeData& other, bool16 consideringLean = kIgnoreLean) const;
	bool16 Contains(TextIndex index) const;
	bool16 Matches( const RangeData& other, bool16 consideringLean = kConsiderLean) const;
	bool16 Begins( const RangeData& other) const;
	bool16 Ends( const RangeData& other) const;
	bool16 Anchors( const RangeData& other) const;


private:
	TextIndex fStart;
	TextIndex fEnd;
	Lean fLean;

	enum {kLeanTowardOriginal = 0, kLeanIntoClip = 1};
	void Check()
	{
		ASSERT_MSG( 0 <= fStart && fStart <= fEnd && (fLean == kLeanForward || fEnd > 0),
			FORMAT_ARGS("Bad RangeData(%d,%d,%s) constructed", fStart, fEnd, fLean == kLeanForward ? "kLeanForward" : "kLeanBack"));
		//repair after assert with the hope that we can proceed
		if( fStart < 0) fStart = 0;
		if( fEnd < fStart) fEnd = fStart;
		if( fLean == kLeanBackward && fEnd == 0) fLean = kLeanForward;
	}
	void ClipTo( const RangeData* clip, bool16 leanInside){ if( clip) ClipTo_( *clip, leanInside); else Check();}
	void ClipTo_( const RangeData& clip, bool16 leanInside); //only non-inlined member function
	friend RangeData Join( const RangeData& x, const RangeData& y, const RangeData* clip);
	friend RangeData SlideForward( const RangeData& x, int32 y, const RangeData* clip);
	friend RangeData AdvanceEnd(   const RangeData& x, int32 y, const RangeData* clip);
	friend RangeData RecedeStart(  const RangeData& x, int32 y, const RangeData* clip);
};



//inline constructors
/**
	Description
	To construct a zero-length RangeData you must specify a lean.
	For example:
		RangeData( 34, RangeData::kLeanBack);
	Think of the specified range as representing the interval start + epsilon .. end - epsilon.  That is, the start of the range leans forward and the end leans back.
	But, when start == end, you _must_ specify a lean as many api's require it.  Some examples include hit-testing text, drawing the insertion point in text when the
	text index is at a line break, calculating which parcel contains a given selection, and complex scenarios when navigating through text in the story editor/galley view
	when two story threads are composed juxtaposed on the same line but are at some distance from each other in the model (inline notes, deleted text).
	RangeData( 34, RangeData::kLeanBack); //ok
	RangeData( 34, 35); //ok
	RangeData( 34, 34); //incorrect
	@param
 */
inline RangeData::RangeData( const RangeData& r, const RangeData* clip)
		: fStart(r.fStart), fEnd(r.fEnd), fLean(r.fLean)
{
	ClipTo(clip, kLeanIntoClip);
}

/**
	Description
	To construct a zero-length RangeData you must specify a lean.
	For example:
		RangeData( 34, RangeData::kLeanBack);
	Think of the specified range as representing the interval start + epsilon .. end - epsilon.  That is, the start of the range leans forward and the end leans back.
	But, when start == end, you _must_ specify a lean as many api's require it.  Some examples include hit-testing text, drawing the insertion point in text when the
	text index is at a line break, calculating which parcel contains a given selection, and complex scenarios when navigating through text in the story editor/galley view
	when two story threads are composed juxtaposed on the same line but are at some distance from each other in the model (inline notes, deleted text).
	RangeData( 34, RangeData::kLeanBack); //ok
	RangeData( 34, 35); //ok
	RangeData( 34, 34); //incorrect
	@param
 */
inline RangeData::RangeData( TextIndex start, TextIndex end, const RangeData* clip)
		: fStart(start), fEnd(end), fLean(kLeanForward)
{
	// should zero width clip mean RangeData( clip.fStart, std::numeric_limits<TextIndex>::max()) or
	// RangeData( std::numeric_limits<TextIndex>::max(), clip.fStart) depending on clip.fLean??
	ASSERT( fStart < fEnd); //wait for clip before Check()
	ClipTo( clip, kLeanIntoClip);
}

inline RangeData::RangeData( TextIndex caret, Lean lean, const RangeData* clip)
		: fStart(caret), fEnd(caret), fLean(lean)
{
	ClipTo( clip, kLeanIntoClip);
}

/**
	Description
	To construct a zero-length RangeData you must specify a lean.
	For example:
		RangeData( 34, RangeData::kLeanBack);
	Think of the specified range as representing the interval start + epsilon .. end - epsilon.  That is, the start of the range leans forward and the end leans back.
	But, when start == end, you _must_ specify a lean as many api's require it.  Some examples include hit-testing text, drawing the insertion point in text when the
	text index is at a line break, calculating which parcel contains a given selection, and complex scenarios when navigating through text in the story editor/galley view
	when two story threads are composed juxtaposed on the same line but are at some distance from each other in the model (inline notes, deleted text).
	RangeData( 34, RangeData::kLeanBack); //ok
	RangeData( 34, 35); //ok
	RangeData( 34, 34); //incorrect
	@param
 */
inline RangeData::RangeData( TextIndex start, TextIndex end, Lean lean, const RangeData* clip)
		: fStart(start), fEnd(end), fLean(start == end ? lean : kLeanForward)
{
	ClipTo( clip, kLeanIntoClip);
}


//inlines member functions
inline int32 RangeData::OverlapWith( const RangeData& other) const
{
	// OverlapWith returns zero if ranges are juxtaposed, positive if
	// they overlap, negative if separated by at least one character.
	return other.Length() + Length() - Join(other,*this).Length();
}

inline bool16 RangeData::StartsBefore( const RangeData& other, bool16 consideringLean) const
{
	return fStart < other.fStart
		|| (consideringLean && fStart == other.fStart && fLean == kLeanBack && other.fLean == kLeanForward);
}

inline bool16 RangeData::EndsAfter( const RangeData& other, bool16 consideringLean ) const
{
	return fEnd > other.fEnd
		|| (consideringLean && fStart == other.fEnd && fLean == kLeanForward
			&& (other.fLean == kLeanBack || other.fStart < other.fEnd));
}

inline bool16 RangeData::Precedes( const RangeData& other) const
{
	RangeData::Lean myLean, otherLean;
	int32 myEnd = EndLocation(*this).Start( &myLean);
	int32 otherStart = StartLocation(other).Start( &otherLean);

	if( myEnd < otherStart)
		return kTrue;
	else if( myEnd > otherStart)
		return kFalse;
	else
		return myLean == RangeData::kLeanBack && otherLean == RangeData::kLeanForward;
}

inline bool16 RangeData::Leads( const RangeData& other) const
{
	return Precedes( other);
}

inline bool16 RangeData::Succeeds( const RangeData& other) const
{
	return EndLocation( other).Precedes( StartLocation( *this));
}

inline bool16 RangeData::Follows( const RangeData& other) const
{
	return Succeeds( other);
}


inline bool16 RangeData::Matches( const RangeData& other, bool16 consideringLean) const
{
	return fStart == other.fStart && fEnd == other.fEnd && (!consideringLean || fLean == other.fLean);
}

inline bool16 RangeData::Begins( const RangeData& other) const
{
	return fStart == other.fStart && fEnd <= other.fEnd;
}

inline bool16 RangeData::Ends( const RangeData& other) const
{
	return fEnd == other.fEnd && fStart >= other.fStart;
}

inline bool16 RangeData::Anchors( const RangeData& other) const
{
	return Begins(other) || Ends(other);
}

inline bool16 RangeData::Contains( const RangeData& other, bool16 consideringLean) const
{
	if( consideringLean){
		if( fStart == fEnd) //if I'm a caret
			return *this == other; //checks if fLean matches
		if( other.fStart == other.fEnd){ //if other is a caret
			if( other.fStart == fStart)
				return other.fLean == kLeanForward;
			else if( other.fEnd == fEnd)
				return other.fLean == kLeanBack;
			//else fall through
		}
	}
	return fStart <= other.fStart && other.fEnd <= fEnd;
}

inline bool16 RangeData::Contains(TextIndex index) const
{
	return RangeData::Contains( RangeData(index, index + 1), kDontConsiderLean);
}




//operators with friend access

inline RangeData Join( const RangeData& x, const RangeData& y, const RangeData* clip) //union
{
	return RangeData(
			std::min(x.fStart, y.fStart),
			std::max(x.fEnd, y.fEnd),
			x.fLean || y.fLean ? RangeData::kLeanBack : RangeData::kLeanForward,
			clip);
}

inline RangeData AdvanceEnd( const RangeData& x, int32 y, const RangeData* clip) //move end forward by
{
	TextIndex end = x.End() + y;
	TextIndex start = x.Start(nil);
	return RangeData( std::min( start, end), std::max( start, end), x.fLean, clip);
}

inline RangeData RecedeStart( const RangeData& x, int32 y, const RangeData* clip) //move start back by
{
	TextIndex end = x.End();
	TextIndex start = x.Start(nil) - y;
	return RangeData( std::min( start, end), std::max( start, end), x.fLean, clip);
}

inline RangeData SlideForward( const RangeData& x, int32 y, const RangeData* clip)
{
	return RangeData( x.fStart + y, x.fEnd + y, x.fLean, clip);
}



//operators using public access

PUBLIC_DECL void Disjoin( RangeData& lhs, RangeData& rhs); //return two ranges that are the XOR of the originals
	//only non-inlined operator

inline bool16 operator<( const RangeData& x, const RangeData& y) //an ordering for sorting
{
	 return x.Start(nil) < y.Start(nil) || (x.Start(nil) == y.Start(nil) && x.End() < y.End());
}

inline RangeData operator+( const RangeData& x, const RangeData& y) //union
{
	return Join(x, y);
}

inline RangeData SlideBackward( const RangeData& x, int32 y, const RangeData* clip = nil)
{
	return SlideForward( x, -y, clip);
}

inline RangeData operator>>( const RangeData& x, int32 y)
{
	return SlideForward( x, y);
}

inline RangeData operator<<( const RangeData& x, int32 y)
{
	return SlideBackward( x, y);
}

inline RangeData EndLocation( const RangeData& x)
{
	return x.Length() == 0 ? x : RangeData( x.End(), RangeData::kLeanBack);
}

inline RangeData StartLocation( const RangeData& x)
{
	return x.Length() == 0 ? x : RangeData( x.Start(nil), RangeData::kLeanForward);
}

inline RangeData NewEndLocation(const RangeData& x, TextIndex end, const RangeData* clip = nil)
{
	return AdvanceEnd(x, end-x.End(), clip);
}

inline RangeData NewStartLocation(const RangeData& x, TextIndex start, const RangeData* clip = nil)
{
	return RecedeStart(x, x.Start(nil)-start, clip);
}

inline RangeData RecedeEnd( const RangeData& x, int32 y, const RangeData* clip = nil) //move end backward by
{
	return AdvanceEnd( x, -y, clip);
}

inline RangeData operator+( const RangeData& x, int32 y) //move end forward by
{
	return AdvanceEnd( x, y);
}

inline RangeData MidPoint( const RangeData& x)
{
	return x.Length() == 0 ? x : RangeData( (x.Start(nil) + x.End())/2, RangeData::kLeanForward);
}

inline RangeData AdvanceStart( const RangeData& x, int32 y, const RangeData* clip = nil)
{
	return RecedeStart( x, -y, clip);
}

inline RangeData operator-( const RangeData& x, int32 y) //move start back by
{
	return RecedeStart( x, y);
}

inline RangeData Clip( const RangeData& r, const RangeData& clip) //like intersection but with specific behavior when the intersection is empty
{
	return RangeData( r, &clip);
}

inline bool16 operator==(const RangeData& lhs, const RangeData& rhs)
{
	return lhs.Matches(rhs, RangeData::kConsiderLean);
}

inline bool16 operator!=(const RangeData& lhs, const RangeData& rhs)
{
	return !(lhs == rhs);
}

inline RangeData NewLean( const RangeData& r, RangeData::Lean lean)
{
	return RangeData( r.Start(nil), r.End(), lean);
}

inline RangeData NewLean( const RangeData& r, const RangeData& copyLean)
{
	RangeData::Lean lean;
	(void)copyLean.Start(&lean);
	return NewLean( r, lean);
}

inline RangeData LeanForward( const RangeData& r)
{
	return NewLean( r, RangeData::kLeanForward);
}

inline RangeData LeanBack( const RangeData& r)
{
	return NewLean( r, RangeData::kLeanBack);
}



//temporary adaptor--StoryRange shouldn't be used for new code

namespace Text {
	class StoryRange : public RangeData //adaptor for now
	{
		public:
            StoryRange( const StoryRange& r) noexcept = default;
            StoryRange( StoryRange&& r) noexcept = default;
			StoryRange( const RangeData& r) : RangeData(r) {}
			StoryRange( TextIndex start, TextIndex end, Lean lean = kLeanForward) : RangeData(start, end, lean) {}
            StoryRange &operator =( const StoryRange& r) noexcept = default;
            StoryRange &operator =( StoryRange&& r) noexcept = default;
			TextIndex GetEnd() const { return End();}
			TextIndex GetStart( RangeData::Lean* lean = nil) const { return Start(lean);}
	};

	typedef K2Vector<StoryRange>	StoryRangeList;
}

using Text::StoryRange;
using Text::StoryRangeList;

class UIDRef;

/** A range with a story - it is merely a coupling of a UIDRef and a RangeData making a single complete reference to a text range within a document */
class ModelRange
{
public:
	typedef object_type data_type;

	/** */
	ModelRange(const UIDRef& s, const RangeData& r) : storyRef(s), range(r)
		{ }

	/** */
	ModelRange(const UIDRef& s, TextIndex b, TextIndex e, RangeData::Lean lean = RangeData::kLeanForward) : storyRef(s), range(b, e, lean)
		{ }

	/** */
	ModelRange(const UIDRef& s, TextIndex o) : storyRef(s), range(o, o, RangeData::kLeanForward)
		{ }

	/** */
	ModelRange() : range(0, 0, RangeData::kLeanForward)
		{ }

	/** */
	TextIndex GetEnd() const { return range.End();}
	/** */
	TextIndex GetStart( RangeData::Lean* lean = nil) const { return range.Start(lean);}

	/** The story this Model Range is associated with */
	UIDRef	storyRef;
	/** The actual range within the associated story. */
	RangeData	range;
};


#endif
