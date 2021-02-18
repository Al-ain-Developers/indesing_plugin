//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/INavigationPoints.h $
//  
//  Owner: wtislar
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
#ifndef __INavigationPoints__
#define __INavigationPoints__

#include "IPMUnknown.h"
#include "MediaID.h"

class NamedUint32AttributeList;

/**
	This interface provides access to navigation point data for a movie page item. 
	
	A navigation point is a seek point associated with a movie page item. It consists of a time
	(in the range of from zero to the movie length), a name (e.g., "Chapter 1"), and a unique
	identifier. A navigation point is defined for a movie so that an action may be defined to
	seek to a specific time frame in the movie. For example, given a navigation point named
	"Chapter 1", one can create a button that begins playing the movie at the time associated with
	Chapter 1.
	
	Navigation points are created by the INavigationPoints::AddPoint() method via scripting, the UI
	or during placement of a movie into a layout. For the latter case, the movie is first encoded
	with navigation cue points. When the movie file is placed into an InDesign layout, the cue points
	are extracted by the movie filter and are automatically added to the movie page item using this
	interface.
*/

class INavigationPoints : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_INAVIGATIONPOINTS };
	
	enum { kInvalidTime = 0xffffffff };
	enum { kInvalidNavigationPointId = 0xffffffff };
	
	typedef K2Vector<uint32> NavigationPointsIndexList;
	
	/** This class encapsulates non-persistent data for a single navigation point. */
	class NavigationPoint
	{
		public:

		NavigationPoint()
		: fId(kInvalidNavigationPointId), fTime(kInvalidTime) {}

		NavigationPoint( uint32 id, const PMString & displayName, uint32 time )
		:	fId(id),
			fDisplayName(displayName),
			fTime(time){}

		/** Copy constructor. */
		NavigationPoint( const NavigationPoint& orig ) { Set( orig ); }

			//----------OPERATORS---------------
		
		/** Assignment operator for NavigationPoint variables. */		
		NavigationPoint& operator = (const NavigationPoint &copy)
			{ Set(copy); return *this; }

		/** Equivalence operator for NavigationPoint variables. */
		inline bool operator == (const NavigationPoint &np) const
			{ return fId == np.fId &&
					 fDisplayName == np.fDisplayName &&
					 fTime == np.fTime; }

		/** Non-equivalence operator for NavigationPoint variables. */
		inline bool operator != (const NavigationPoint &np) const
			{ return (!(*this == np)); }
		
		/** Available NavigationPoint data */		
		uint32		fId;			// Identifier unique to the list.
		PMString	fDisplayName;	// Name to display in the UI.
		uint32		fTime;			// A video time in 1/100s seconds.
		
	private:
		void Set( const NavigationPoint & copy )
			{ fId = copy.fId; fDisplayName = copy.fDisplayName; fTime = copy.fTime; }	
	}; // end NavigationPoint class	

	
	/** Adds a new navigation point entry to the current list in increasing-time order.
		@param time is the in 1/100s seconds.
		@param atEnd if true then the new navigation point is appended to the list regardless
			of the time value.
		@return the non-negative index of the navigation point that was added; -1 if there was a failure.
	*/
	virtual int32 AddPoint( uint32 time, bool16 atEnd = kFalse ) = 0;
	
	/** Test is a navigation point can be removed from the list.
		@param indexAt specifies the index of an existing navigation point.
		@return true if the navigation point can be removed; false otherwise.
	*/
	virtual bool CanRemovePoint( int32 indexAt ) const = 0;

	/** Tests if a navigation point for a specified navigation point ID exists.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@return true if a navigation point exists for the ID; otherwise returns false.
	*/
	virtual bool DoesNavigationPointExist( uint32 navPointID ) const = 0;

	/** Retrieves the NavigationPoint.fDisplayName for a specified navigation point ID.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@param outDisplayName is populated with the NavigationPoint.fDisplayName.
		@return true if the displayName exists for the ID; otherwise returns false.
	*/	
	virtual bool GetDisplayName( uint32 navPointID, PMString & outDisplayName ) const = 0;
		
	/** Retrieves a navigation point for a specified NavigationPoint.fId.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@param outNavPoint is populated with the navigation point data.
	*/
	virtual bool GetNavigationPointById( uint32 navPointID, INavigationPoints::NavigationPoint & outNavPoint ) const = 0;

	/** Retrieves the next navigation point or none if iteration has passed the end of the list.
		Caution: this method is not guaranteed to be undo/redo safe! If an undo/redo is done that
		affects navigation points, ResetIterator() must be called before calling this method. (In
		most normal uses of this method, such as refreshing UI or exporting, undo/redo conflicts
		will not occur during iteration.)
		@param outNavPoint is populated with the next navigation point data.
		@return true if the next navigation point was available; otherwise returns false.
	*/
	virtual bool GetNextNavigationPoint( INavigationPoints::NavigationPoint & outNavPoint ) = 0;

	/** Retrieves a navigation point by index. Navigation point indices begin at 0.
		@param index is a number from 0 to GetNumberOfNavigationPoints() - 1.
		@param outNavPoint is populated with the next navigation point data.
		@return true if the indexed navigation point was available; otherwise returns false.
	*/
	virtual bool GetNthNavigationPoint( uint32 index, INavigationPoints::NavigationPoint & outNavPoint ) const = 0;

	/** Retrieves a navigation point time by index. Navigation point indices begin at 0.
		@param index is a number from 0 to GetNumberOfNavigationPoints() - 1.
		@param outTime is populated with the time value with a precision of .01 seconds.
		@return true if the indexed navigation point and time are available; otherwise returns false.
	*/	
	virtual bool GetNthNavigationPointTime( uint32 index, PMReal & outTime ) const = 0;
				
	/** Retrieves the number of NavigationPoint entries (objects) currently in the list.
		@return an integer >= 0;
	*/
	virtual uint32 GetNumberOfNavigationPoints() const = 0;

	/** Retrieves the time value for a specified navigation point ID.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@return a valid time value if the navigation point exists for the ID; otherwise returns INavigationPoints::kInvalidTime.
	*/
	virtual uint32 GetTime( uint32 navPointID ) const = 0;
		
	/** Removes one or more NavigationPoint entries from the list.
		@param indexList is a list of iterator indices of the navigation points to remove. An iterator index
			is not the same as the NavigationPoint.fId. E.g., a list of 0,2,3 removes the first, third
			and fourth navigation points.
		@return kSuccess if the navigation points were removed; kFalse otherwise.
	*/
	virtual ErrorCode RemovePoints( const INavigationPoints::NavigationPointsIndexList & indexList ) = 0;

	/** Resets the list iterator so that the next call to GetNextNavigationPoint() returns the
		first navigation point in the list.
	*/
	virtual void ResetIterator() = 0;
	
	/** Sets the display name for a navigation point.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@param inDisplayName is the new display name.
		@return kSuccess if the display name was set; otherwise returns an error code.
	*/
	virtual ErrorCode SetDisplayName( uint32 navPointID, const PMString & inDisplayName ) = 0;

	/** Sets the time for a navigation point.
		@param navPointID specifies an existing NavigationPoint.fId. IDs begin at 0.
		@param time is the new time value. It is up to the caller to assure that the time falls within the
			range of the video.
		@return kSuccess if the time was set; otherwise returns an error code.
	*/	
	virtual ErrorCode SetTime( uint32 navPointID, PMReal time ) = 0;
	
	/** This method is for internal scripting use **/
	virtual ErrorCode ResetId( uint32 oldNavPointID, uint32 newNavPointID ) = 0;
	
	/** Adds new navigation points from a NamedUint32AttributeList. Adds only those points
	    that have unique time values (i.e., if a list entry has a time value that already exits,
	    it is not added).
		@param list list of cue points.	
		@return kSuccess if the list was added; otherwise returns an error code.
	*/
	virtual ErrorCode AddPoints( NamedUint32AttributeList & list ) = 0;	
	
}; // end INavigationPoints interface


#endif // __INavigationPoints__