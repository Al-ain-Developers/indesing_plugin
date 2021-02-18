//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMovieSuite.h $
//  
//  Owner: Bill Tislar
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
//  Comments:	Selection suite for Movie page items
//  
//========================================================================================

#pragma once
#ifndef _IMovieSuite_
#define _IMovieSuite_

#include "MovieID.h"


/** Selection suite for manipulating Movie page items.
	
*/

class IMovieSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMOVIESUITE };

	/** Obtains an existing empty frame that can be converted into a movie frame.
		@precondition A single empty frame must be selected; multiple selections are
					  not supported.
		@return UIDRef to a single empty frame.
	*/
	virtual UIDRef GetEmptyFrameRef() const = 0;

	/** Obtains the UIDRef of a single selected movie page item.
		@precondition A single movie page item must be selected; multiple selections are
					  not supported.
		@return UIDRef to a single movie page item.
	*/
	virtual UIDRef GetSelectedMovieRef() const = 0;

	/** Tests the current selection for Movie page items
		@return kTrue if selection is all Movie page items (or default selection)
	*/
	virtual bool16 IsMovieSelection() const = 0;
	
	/** Tests if the selection can be converted into a Movie page item.
		@return kTrue if the selection can be converted into a Movie page item.
	*/
	virtual bool16 CanConvertToMovie() const = 0;

	
};


#endif // _IMovieSuite_