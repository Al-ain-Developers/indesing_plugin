//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMovieAttributes.h $
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
#ifndef __IMovieAttributes__
#define __IMovieAttributes__

#include "IMediaAttributes.h"
#include "IPMUnknown.h"
#include "MovieID.h"
#include "PMRect.h"
#include "PMPoint.h"
#include "PMString.h"


// Predefined floating window positions:

static const PMPoint kMovieWindowUpperLeft		= PMPoint(0.05,0.05);
static const PMPoint kMovieWindowUpperMiddle	= PMPoint(0.5,0.05);
static const PMPoint kMovieWindowUpperRight		= PMPoint(0.95,0.05);
static const PMPoint kMovieWindowCenterLeft		= PMPoint(0.05,0.5);
static const PMPoint kMovieWindowCenter			= PMPoint(0.5,0.5);
static const PMPoint kMovieWindowCenterRight	= PMPoint(0.95,0.5);
static const PMPoint kMovieWindowLowerLeft		= PMPoint(0.05,0.95);
static const PMPoint kMovieWindowLowerMiddle	= PMPoint(0.5,0.95);
static const PMPoint kMovieWindowLowerRight		= PMPoint(0.95,0.95);


/**
	This interface provides methods for accessing movie page item attributes.
*/

class IMovieAttributes : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IMOVIEATTRIBUTES };


	/** this enum defines the movie play modes */
	enum PlayMode
	{
		/** play once, then close */
		eOnce		= 0,
		/** play once, then stay open */
		eOpen		= 1,
		/** repeat play indefinitely */
		eRepeat		= 2
	};

	/** this enum defines the size of the movie floating window, relative to the movie bounds */
	enum FloatingWindowScale
	{
		eOneFifth	= 9,
		eOneForth	= 10,
		eOneHalf	= 11,
		eFull		= 12,
		e2X			= 13,
		e3X			= 14,
		e4X			= 15,
		eMax		= 16
	};

	enum // constants
	{
		kNumberOfPlayModes = 3,
		kNumberOfFWScaleOptions = 8 
	};


	/** Retrieves the movie's bounding box. If the movie is to play in a floating window,
		the bounding box is the movie's intrinsic bounds; otherwise, it is the bounds
		of the movie page item.
		@return PMRect set to the bounds.
	*/
	virtual const PMRect GetBoundingBox() = 0;

	/** Tests if movie controls should be displayed by the PDF reader.
		@return kTrue if movie controls should be displayed, kFalse if not.
	*/
	virtual bool16 ShowControls() const = 0;

	/** Retrieves the movie PlayMode.
		@return movie PlayMode.
	*/
	virtual PlayMode GetPlayMode() const = 0;

	/** Retrieves the current FloatingWindowScale.
		@return the current FloatingWindowScale.
	*/
	virtual FloatingWindowScale	GetFloatingWindowScale() const = 0;

	/** Tests if the movie is to be shown in its own window by the PDF viewer.
		@return kTrue to show in its own window; kFalse to show within the page.
	*/
	virtual bool16 HasFloatingWindow() const = 0;

	/** Retrieves the floating window position.
		@return one of the predefined PMPoint floating window positions.
	*/
	virtual const PMPoint GetFloatingWindowPosition() = 0; 

	/** Sets the floating window position.
		@param p one of the predefined PMPoint floating window positions.
	*/
	virtual void SetFloatingWindowPosition( const PMPoint & p ) = 0;

	/** Sets the FloatingWindowScale attribute.
		@param s the FloatingWindowScale.
	*/
	virtual void SetFloatingWindowScale( FloatingWindowScale s ) = 0;

	/** Sets the show movie controls option.
		@param b kTrue to show a movie controller in the PDF viewer while the movie is
		active; kFalse to omit the movie controller.
	*/
	virtual void SetShowControls( bool16 b ) = 0;

	/** Sets the floating window option.
		@param b kTrue to show the movie in its own window by the PDF viewer; kFalse to
		show the movie on the page.
	*/
	virtual void SetHasFloatingWindow( bool16 b ) = 0;

	/** Sets the movie PlayMode attribute.
		@param m the movie PlayMode.
	*/
	virtual void SetPlayMode( PlayMode m ) = 0;

public:

	/** this enum defines the IDs of all attributes specific to movie media.
		@see IMediaAttributes.
	*/
	enum MovieAttributeID
	{
		/** Displays movie controller during play if set */
		enShowControls				= kMoviePrefix + 0,	// flag
		/** The movie PlayMode as defined above. */
		enPlayMode					= kMoviePrefix + 1,	// int16
		/** Movie FloatingWindowScale as defined above. */
		enFloatingWindowScale		= kMoviePrefix + 2,	// int16
		/** Movie is played in a floating window if set. */
		enHasFloatingWindow			= kMoviePrefix + 3,	// flag
		/** The PMPoint position of the movie's floating window. */
		enFloatingWindowPosition	= kMoviePrefix + 4	// PMPoint
	};

}; // end IMovieAttributes interface


#endif // __IMovieAttributes__