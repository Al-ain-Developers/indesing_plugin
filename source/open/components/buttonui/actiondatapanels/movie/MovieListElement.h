//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/movie/MovieListElement.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __MovieListElement_h__
#define __MovieListElement_h__

#include "K2Pair.h"
#include "UIDRef.h"

//========================================================================================
// CLASS MovieListElement
//========================================================================================

class MovieListElement
{
public:
	typedef object_type data_type;

	MovieListElement(const UIDRef& movie) :
		fMovie(movie)
	{
	}
	
	MovieListElement(const MovieListElement& other) :
		fMovie(other.fMovie)
	{
	}
	
	MovieListElement& operator=(const MovieListElement& other)
	{
		if (this != &other)
			fMovie = other.fMovie;
		
		return *this;
	}

	UIDRef GetMovieRef() const
	{
		return fMovie;
	}
	
public:
	UIDRef		fMovie;
};

typedef K2Pair<UIDRef, uint32> MovieNavPointListElement;

#endif // __MovieListElement_h__
