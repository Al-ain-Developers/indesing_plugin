//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PathTypes.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __PathTypes__
#define __PathTypes__

#include "K2Vector.h"
#include "IPMStream.h"

/** Index for path point sub-points */
enum PathPointIndex
{
	/** Left direction point */
	kLeftDirPt	= 0,
	/** Anchor point */
	kAnchorPt,
	/** Right direction point */
	kRightDirPt,
	/** Both direction points (for path selection). NOT CURRENTLY IN USE AS OF 11/99 */
	kBothDirPts,
	/** Segment (for path selection) */
	kSegment
} ;
	
/** Path point type -- the type of data in PointTypeList */  
enum PMPathPointType
{
	/** Anchor point with continuing tangent. */
	kCS,
	/** Anchor point with unsmooth curve point, left->right tangent discontinue.
		The start curve point of an open path is of type "kCK". */
	kCK,
	/** Anchor point with both tangent degenerated. 
		Two consecutive kL type point form a line. */
	kL
};
DECLARE_BASE_TYPE(PMPathPointType);

/** A list of path point types */
typedef K2Vector<PMPathPointType> PointTypeList;

/** PM segment type */
enum PMPathSegmentType
{
	/** line segment */
	kLine,
	/** curve segment */
	kCurve,
	/** no segment */
	kNoSegment
} ;

/**
	Calculate index of a point.
	@param index IN
	@param total number of points
	@return the calculated index
*/
inline int32 PT_INDEX( int32 n, int32 total ) { return (n + total) % total ; }

/** Specifies a selected point */
class PointSelector
{
public:
	typedef base_type data_type;

	/** */
	PointSelector() :
		fPathIndex( -1 ),
		fPointIndex( -1 ),
		fSelector( kAnchorPt ),
		fAdornmentClass(kInvalidClass)
		{}
	/** */
	PointSelector( int32 path, int32 point, PathPointIndex flags = kAnchorPt, ClassID adornmentClass = kInvalidClass ) :
		fPathIndex( path ),
		fPointIndex( point ),
		fSelector( flags ),
		fAdornmentClass (adornmentClass)
		{}

	/** Get the path index */
	int32 PathIndex() const { return fPathIndex ; }
	/** Set the path index */
	void PathIndex( int32 pathIndex ) { fPathIndex = pathIndex ; }

	/** Get the point index */
	int32 PointIndex() const { return fPointIndex ; }
	/** Set the point index */
	void PointIndex( int32 pointIndex ) { fPointIndex = pointIndex ; }

	/** Get the selector */
	PathPointIndex Selector() const { return fSelector ; }
	/** Set the selector */
	void Selector( PathPointIndex selector ) { fSelector = selector ; }

	/** Get the adornment class */
	ClassID AdornmentClass() const { return fAdornmentClass; }
	/** Set the adornment class */
	void AdornmentClass (ClassID adornmentClass) { fAdornmentClass = adornmentClass; }
	
	/**  */
	bool16 operator==( const PointSelector& other ) const
	{
		return ( fPathIndex == other.fPathIndex && fPointIndex == other.fPointIndex && fSelector == other.fSelector ) ;
	}
	/**  */
	bool16 operator!=( const PointSelector& other ) const
	{
		return ( fPathIndex != other.fPathIndex || fPointIndex != other.fPointIndex || fSelector != other.fSelector ) ;
	}
	/**  */
	bool16 operator<( const PointSelector& other ) const
	{
		if ( fPathIndex < other.fPathIndex )
			return kTrue ;
		if ( fPathIndex > other.fPathIndex )
			return kFalse ;
		if ( fPointIndex < other.fPointIndex )
			return kTrue ;
		return kFalse ;
	}
	void ReadWrite(IPMStream *s)
	{
		s->XferInt32(fPathIndex);
		s->XferInt32(fPointIndex);
		s->XferInt32((int32&)fSelector);
		s->XferID(fAdornmentClass);
	}
private:
	int32 fPathIndex ;
	int32 fPointIndex ;
	PathPointIndex fSelector ;
	
	ClassID fAdornmentClass; // If the item hit was an adornment then this will not be kInvalidClass
} ;

/** A list of selected points */
typedef K2Vector<PointSelector> PointSelectorList ;

#endif
