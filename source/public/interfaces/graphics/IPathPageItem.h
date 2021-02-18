//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathPageItem.h $
//  
//  Owner: Jonathan W. Brown (based on jargast)
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
//  This interface is designed to encapsulate the drawing, hit testing, 
//  and querying of path-based page items. All bosses must include an
//  IID_IGRAPHICSTYLE_DESCRIPTOR interface as well.
//  
//========================================================================================

#pragma once
#ifndef __IPathPageItem__
#define __IPathPageItem__

#include "IPMUnknown.h"
#include "GraphicsID.h"

class IOutlineInfo;
class IGraphicsPort;
class PMMatrix ;
class PMRect ;

/**
	This interface is designed to encapsulate the drawing, hit testing, 
	and querying of path-based page items. All bosses must include an
	IID_IGRAPHICSTYLE_DESCRIPTOR interface as well.
*/
class IPathPageItem : public IPMUnknown
{
public:
	/**
		Define the default interface IID as IID_IPATHPAGEITEM.
	*/
	enum { kDefaultIID = IID_IPATHPAGEITEM } ;

	/**
		Stroke creates the full path, including corners and line ends,
		and strokes it. Does not do a gsave/grestore.

		@param gPort [IN] parameter the graphics port that does stroke operation.
		@return void.
	*/
	virtual void Stroke( IGraphicsPort* gPort ) = 0 ;

	/**
		Fill creates the path, including corners and fills it.
		Does not do a gsave/grestore. Depending on the attributes
		it will use even odd or winding rule.

		@param gPort [IN] parameter the graphics port that does fill operation.
		@return void.
	*/
	virtual void Fill( IGraphicsPort* gPort ) = 0 ;

	/**
		Clip creates the path, including corners and clips it.
		Does not do a gsave/grestore. Depending on the attributes
		it will use even odd or winding rule.

		@param gPort [IN] parameter the graphics port that does clip operation.
		@return void.
	*/
	virtual void Clip( IGraphicsPort* gPort ) = 0 ;

	/**
		Copies the path into the graphicsport includes corners.

		@param gPort [IN] parameter the graphics port that source path comes from.
		@return void.
	*/
	virtual void CopyPath( IGraphicsPort* gPort ) = 0 ;

	/**
		Returns the bounding box for the entire stroked path, including
		corners and line ends. The bounding box is converted using the
		passed in matrix. This GetStrokeBoundingBox() returns the theoretical
		bounds. 

		@param theMatrix [IN] parameter the matrix that does the transformation before returning the result.
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetStrokeBoundingBox( const PMMatrix& theMatrix ) = 0 ;

	/**
		Same as GetStrokeBoundingBox except it tries to guarantee that invalidations with 
		this bounds will not leave stuff on the screen.

		@param theMatrix [IN] parameter the matrix that does the transformation before returning the result.
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetPaintedBoundingBox( const PMMatrix& theMatrix ) = 0 ;

	/**
		Check whether the given rectangle intersects the stroke. 
		The rectangle is in device space.

		@param gPort [IN] parameter the graphics port that the operation happens.
		@param r [IN] parameter the given rectangle.
		@return bool16 kTrue if the given rectangles intersects the stroke, otherwise kFalse.
	*/
	virtual bool16 InStroke( IGraphicsPort* gPort, const PMRect& r ) = 0 ;

	/**
		Check whether the given rectangle intersects the fill. 
		The rectangle is in device space.

		@param gPort [IN] parameter the graphics port that the operation happens.
		@param r [IN] parameter the given rectangle.
		@return bool16 kTrue if the given rectangles intersects the fill, otherwise kFalse.
	*/
	virtual bool16 InFill( IGraphicsPort* gPort, const PMRect& r ) = 0 ;

	/**
		Return the outline of the path including corner effects.

		@param iOutlineInfo [IN] parameter used as the call back function.
		@return void.
	*/
	virtual void GetOutlineInfo ( IOutlineInfo* iOutlineInfo ) = 0 ;

	/**
		Check whether the given rectangle intersects the fill of the given path. 
		The rectangle is in device space.

		@param gPort [IN] parameter the graphics port that the operation happens.
		@param r [IN] parameter the given rectangle.
		@param whichPath [IN] parameter the given path.
		@return bool16 kTrue if the given rectangles intersects the fill, otherwise kFalse.
	*/
	virtual bool16 InFill( IGraphicsPort* gPort, const PMRect& r, int32 whichPath ) = 0 ;
} ;

#endif	// __IPathPageItem__
