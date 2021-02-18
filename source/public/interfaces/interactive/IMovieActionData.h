//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMovieActionData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IMovieActionData_h__
#define __IMovieActionData_h__

#include "IBehaviorData.h"

#include "BehaviorID.h"

//========================================================================================
// CLASS IMovieActionData
//========================================================================================

/** Data interface for Play Movie Behavior.
	@see INamedPageItemList (for a way of getting candidates for SetMovie()*/
class IMovieActionData : public IBehaviorData
{
public:
	enum Operation { kPlay = 0, kStop, kPause, kResume, kPlayFromNavigationPoint, kStopAll };
	
	/** Set Operation to perform on movie (kPlay, kPlayFromNavigationPoint, kStop, kPause, kResume, or kStopAll) */
	virtual void		SetOperation(const Operation& operation) = 0;

	/** Get Operation to perform on movie (kPlay, kPlayFromNavigationPoint, kStop, kPause, kResume, or kStopAll) */
	virtual Operation	GetOperation() const = 0;
	
	/** Set UID of Movie page item to play */
	virtual void		SetMovie(const UID& movie) = 0;

	/** Get UID of Movie page item to play */
	virtual UID			GetMovie() const = 0;

	/** Set the ID of the Navigation Point to play from. This is only used for the kPlayFromNavigationPoint operation.  */
	virtual void	 	SetNavigationPointID(uint32 navPoint) = 0;

	/** Get the ID of the Navigation Point to play from. This is only used for the kPlayFromNavigationPoint operation.  */
	virtual uint32		GetNavigationPointID() const = 0;
};

#endif // __IMovieActionData_h__
