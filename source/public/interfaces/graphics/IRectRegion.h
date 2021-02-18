//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRectRegion.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IRectRegion__
#define __IRectRegion__

#include "GRRefCountedObj.h"
#include "PMRect.h"


//----------------------------------------------------------------------------------------
// Class IRectRegion
//----------------------------------------------------------------------------------------

/**
	IRectRegion has an origin PMRect from which you can substract other PMRects.
    The area that is left after substraction is stored in a PMRectCollection.
    You can also invert a IRectRegion so the rects in the PMRectCollections are 
    treated as holes to origin.	
    IRectRegion is used in the overlap management. It is designed to replace the old BandMap.	

	BP 8/2/96:
	Here are two examples that describe Subtract with a minimum height.
	You have always a choice how you divide an origin rect. If you specify
	a minimum height, Subtract() will look for a solution that avoids rects
	with a lower height. (Notice that we keep the rects, that are too small)
	The numbers shows the order of rects that are calculated by Subtract().

	This sophisticated class is used by the SpreadOverlapManager and the StandOffs
	for evaluation of text 'tiles'. Subtract and Compress have to be very fast.

*/

/*
<CODE>
	================================================================================
											+						+ 
		Origin - Rect:			nMinHeight:	|			nMinHeight:	| 
											+						| 
																	+

		+-----------+			+-----------+			+-------+---+
		|	  		|			|	  1		|			|	  	| 1	|
		|		+---+---+		+-------+---+---+		|		+-------+
		|		|XXXXXXX|		|	3	|XXXXXXX|		|	3	|XXXXXXX|	
		|		|XXXXXXX|		|		|XXXXXXX|		|		|XXXXXXX|
		|		+---+---+		+-------+---+---+		|		+-------+
		|	  		|			|	  2		|			|	  	| 2	|
		+-----------+			+-----------+			+-------+---+

	================================================================================
											+						+
		Orgin - Rect:			nMinHeight:	|			nMinHeight:	|
											+						|
													 				+
													 				
		+-----------+			+-----------+			+-----------+
		|	  		|			|	  1		|			|	  1		|	
		|	  		|			|	  		|			|			|	
		|		+---+---+		+-------+---+---+		+-------+---+---+
		|		|XXXXXXX|		|	3	|XXXXXXX|		|		|XXXXXXX|	
		|		+---+---+		+-------+---+---+		|	3	+---+---+
		|	  		|			|	  2		|			|	  	| 2	|	
		+-----------+			+-----------+			+-------+---+
							
	================================================================================
</CODE>
*/


class IRectRegion : public grRefCountedObj
{
public:

	/**
		Sets the origin of the rect region.
		@param rOrigin IN. Origin rectangle.
	*/
	virtual void				SetOrigin( const PMRect &rOrigin ) = 0;  

	/**
		Returns the origin rectangle of the rect region.
		@return the origin rectangle.
	*/
	virtual const PMRect &		GetOrigin() const = 0;

	/**
		Substracts rRect from the origin rectangle.
		@param rRect IN. Substracts rRect from the origin rectangle.
		@param nMinHeight IN. After the subtaction all rectangles must have a minimum height of nMinHeight.
	*/
	virtual void				Subtract( const PMRect &rRect, PMReal nMinHeight ) = 0;	

	/**
		Inverts the rect region in such a way that holes become rects and rects become holes.
	*/
	virtual void				Invert() = 0;						

	/**
		Optimizes and tries to reduce the number of rects and returns the number of deleted rects.
		@return number of deleted rects.
	*/
	virtual uint32 				Compress() = 0;	
	
	/**
		Returns the PMRectCollection with the rectangles that are left.
		@return PMRectCollection with the rectangles that are left.
	*/
	virtual const PMRectCollection& GetRectCollection() const = 0;					

	/**
		Copies the PMRectCollection with the rectangles that are left into pRects;
		@param pRects OUT. The rectangle to be copied to.
	*/
	virtual void				CopyRectCollection( PMRectCollection *pRects ) const = 0;	

	/**
		Returns whether the rect region has been modified or not.
		@return whether the rect region has been modified or not.
	*/
	virtual bool16				IsModified() const = 0;				
	
	/**
		Returns whether the rect region has been inverted or not.
		@return whether the rect region has been inverted or not.
	*/
	virtual bool16				IsInverted() const = 0;

	/**
		Returns whether the rect region is empty or not.
		@return whether the rect region is empty or not.
	*/
	virtual bool16				IsEmpty() const = 0;

	/**
		Returns whether the rect region is rectangular or not.
		@return whether the rect region is rectangular or not.
	*/
	virtual bool16				IsRectangular() const = 0;

	/**
		Sorts the rect region.
		@param nIndex IN. Specifies the point index for sorting.
		@param bXFirst IN. If bXFirst is true it will be sorted by PMPoint::X(). If bXFirst is false it will be sorted by PMPoint::Y().
	*/
	virtual void				Sort( PMRect::PointIndex nIndex, bool16 bXFirst ) = 0;
};

//----------------------------------------------------------------------------------------
// inline operator-=
//----------------------------------------------------------------------------------------

inline IRectRegion &operator-=( IRectRegion &rRegion, const PMRect &rRect )
{
	rRegion.Subtract( rRect, kFalse );
	return rRegion;
}

#endif

