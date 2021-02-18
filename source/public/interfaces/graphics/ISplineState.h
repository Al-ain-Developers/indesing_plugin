//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISplineState.h $
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
#ifndef __ISplineState__
#define __ISplineState__

#include "IPMUnknown.h"
#include "SplineUIID.h"

/**
	Stores whether a spline is currently in creation or motion editing mode within a document
	workspace and the active path point.
*/  
class ISplineState : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPLINESTATE } ;

	/** Values for spline editing.
	*/
	enum SplineState {
		kOff =					0x0000,	/** Not editing a spline */
		kCreation =				0x0001,	/** In process of creating a new spline, or editing a spline */
		kMotion =				0x0002,	/** In process of editing a motion path */
		kCreationAndMotion =	(kCreation | kMotion)	/** In process of editing (and creating) a motion path (e.g. extending points on the motion item) */
	};

	/** Signals that the document (or whatever item this interface is on) is in edit/creation state. */
	virtual void SetState (SplineState newState) = 0;

	/** Returns spline state for the document */
	virtual ISplineState::SplineState GetState () const = 0;

	/** Sets the UIDRef of the item being created/edited */
	virtual void SetPageItem( const UIDRef& pageitem ) = 0 ;

	/** Returns the UIDRef of the page item being created/edited */
	virtual const UIDRef& GetPageItem() const = 0 ;

	/** Sets the UIDRef of the motion page item being created/edited */
	virtual void SetMotionPageItem( const UIDRef& pageitem ) = 0 ;

	/** Sets the UIDRef of the owner page item that the motion page item refers to */
	virtual void SetMotionOwnerPageItem( const UIDRef& pageitem ) = 0 ;

	/** Returns the UIDRef of the motion page item being created/edited */
	virtual const UIDRef& GetMotionPageItem() const = 0 ;

	/** Returns the UIDRef of the owner page item that the motion item refers to */
	virtual const UIDRef& GetMotionOwnerPageItem() const = 0 ;

	/** Sets the current path and point index from which to continue creation */
	virtual void SetPathAndPointIndex (int32 pathIndex, int32 pointIndex) = 0;

	/** Get the current path index */
	virtual int32 GetPathIndex () const = 0;

	/** Get the current point index */
	virtual int32 GetPointIndex () const = 0;
};

ISplineState::SplineState& operator|=(ISplineState::SplineState& lhs, ISplineState::SplineState rhs);

#endif	// __ISplineState__
