//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicsUtils.h $
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
#ifndef __IGraphicsUtils__
#define __IGraphicsUtils__

#include "InstStrokeFillID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMPoint.h"
#include "PMRect.h"

class IPathData;
class IGraphicsPort;
class IRasterPort;
class IOffscreenPortData;
class IGraphicsContext;
class IPathPort;
class IOutlineInfo;
class PMMatrix;
class IColorSpaceMgr;
class GraphicsData;



/**	An utility interface for graphic related operations.
*/
class IGraphicsUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICSUTILS };

	/**	Copy the given path data into the graphics port.
		@param srcPath specifies the path data to copy.
		@param gPort is the graphic port.
	*/
	virtual void CopyPathToPort
		(
			const IPathData* srcPath,
			IGraphicsPort*   gPort
		) = 0;

	/**	Align the given user coordinate in the port to the center of the nearest device pixel.
	 @param rPort specifies raster port device (used to determine the device scale factor).
	 @param userCoord is the coordinate value to be aligned.
	 @return the pixel center aligned value
	 */
	virtual PMReal AlignUserCoordToDevicePixelCenter
		(
			IRasterPort*		rPort,
			const PMReal&	userCoord
		) = 0;
	
	/**	Create an anchor point path marker in the port.
		The function converts to destination coords using rPort.
		@param rPort specifies target raster port.
		@param gPort is the target graphic port.
		@param handleLocation is the location of the marker in source coordinates.
		@param size is the pixel size of the marker.
		@param doFloor is true if fractional pixel is clipped.
	*/
	virtual void CreateAnchorPointPath
		(
			IRasterPort*		rPort,
			IGraphicsPort*		gPort,
			const PMPoint&		handleLocation,
			const PMReal&		size = PMReal(4.0),
			bool16				doFloor = kTrue
		) = 0;

	/** Create a path for a rectangle's 8 anchor points in the port.
		The function converts to destination coords using rPort and draws the path using gPort.
		 @param rPort specifies target raster port.
		 @param gPort is the target graphic port.
		 @param theRect is the rectangle for which the anchor points are to be generated.
		 @param size is the pixel size of the marker.
		 @param doFloor is true if fractional pixel is clipped.
	*/
	virtual void CreateAnchorRectPaths
		(
			 IRasterPort*		rPort,
			 IGraphicsPort*		gPort,
			 const PMRect&		theRect,
			 const PMReal&		size,
			 bool16				doFloor
		 ) = 0;
	
	/**	Create an anchor point path marker in the port.
	 The function assumes rPort coords have already been set to it's native user coords (identity CTM), and will be reset by the caller.
	  This allows more complex paths to built from a series of calls to methods like this one.
	 @param rPort specifies target raster port.
	 @param gPort is the target graphic port.
	 @param sourceToUserMatrix
	 @param handleLocation is the location of the marker in source coordinates.
	 @param size is the pixel size of the marker.
	 @param doFloor is true if fractional pixel is clipped.
	 */
	virtual void CreateAnchorPointPath_UserCoords
		(
			 IRasterPort*		rPort,
			 IGraphicsPort*		gPort,
			 const PMMatrix&		sourceToUserMatrix,
			 const PMPoint&		handleLocation,
			 const PMReal&		size = PMReal(4.0),
			 bool16				doFloor = kTrue
		 ) = 0;
	
	/** Create a path for a rectangle's 8 anchor points in the port.
	 The function assumes rPort coords have already been set to it's native user  coords (identity CTM), and will be reset by the caller.
	 This allows more complex paths to built from a series of calls to methods like this one.
	 @param rPort specifies target raster port.
	 @param gPort is the target graphic port.
	 @param sourceRect is the rectangle, in source coordinates, for which the anchor points are to be generated.
	 @param size is the pixel size of the marker.
	 @param doFloor is true if fractional pixel is clipped.
	 */
	virtual void CreateAnchorRectPaths_UserCoords
		(
			 IRasterPort*		rPort,
			 IGraphicsPort*		gPort,
			 const PMMatrix&		sourceToUserMatrix,
			 const PMRect&		sourceRect,
			 const PMReal&		size,
			 bool16				doFloor = kTrue
		 ) = 0;
	
	/**	Create a direction point path marker in the port.
	 The function converts to destination coords using rPort and draws the path
	 using gPort.
	 @param rPort specifies target raster port.
	 @param gPort is the target graphic port.
	 @param handleLocation is the location of the marker in source coordinates.
	 */
	virtual void CreateDirectionPointPath
		(
			 IRasterPort*		rPort,
			 IGraphicsPort*		gPort,
			 const PMPoint&		handleLocation
		 ) = 0;
	
	/**	Create a direction point path marker in the port.
	 The function assumes rPort coords have already been set to it's native user coords (identity CTM), and will be reset by the caller.
	 This allows more complex paths to built from a series of calls to methods like this one.
	 @param rPort specifies target raster port.
	 @param gPort is the target graphic port.
	 @param handleLocation is the location of the marker in source coordinates.
	 */
	virtual void CreateDirectionPointPath_UserCoords
		(
			 IRasterPort*		rPort,
			 IGraphicsPort*		gPort,
			 const PMMatrix&		sourceToUserMatrix,
			 const PMPoint&		handleLocation
		 ) = 0;
	
	/**	Create a text link triangle marker.
		The function converts to destination coords using rPort and draws the path
		using gPort.
		@param rPort specifies target raster port.
		@param gPort is the target graphic port.
		@param handleLocation is the location of the link marker in source coordinates.
		@param bVerticalOrientation is true if drawn vertically.
	*/
	virtual void CreateTextLinkPath
		(
			IRasterPort*		rPort,
			IGraphicsPort*		gPort,
			const PMPoint&		handleLocation,
			bool16				bVerticalOrientation = kFalse,
			bool16			bRightToLeftOrientation = kFalse
		) = 0;

	/**	Create an overset "plus" marker.
		The function converts to destination coords using rPort and draws the path
		using gPort.
		@param rPort specifies target raster port.
		@param gPort is the target graphic port.
		@param handleLocation is the location of the overset marker in source coordiate.
		@param drawSelected is true if the overset marker is to be drawn.
	*/
	virtual void CreateTextOversetPath
		(
			IRasterPort*		rPort,
			IGraphicsPort*		gPort,
			const PMPoint&		handleLocation,
			bool16				drawSelected = kTrue
		) = 0;

	/**	Compute the miter adjusted point for current point.
		@param beforePt specifies the point before the current point.
		@param currentPt is the current point.
		@param afterPt specifies the point after current point.
		@param strokeWeight is the line weight.
		@param miterLimit is the miter limit.
		@return the miter adjusted point.
	*/
	virtual PMPoint ComputeMitreAdjustPoint
		(
			const PMPoint& beforePt,
			const PMPoint& currentPt,
			const PMPoint& afterPt,
			const PMReal& strokeWeight,
			const PMReal& miterLimit
		) = 0;

	/**	Compute the line's bounds taking into account its stroke weight, miter limit, join type,
		and line cap.
		@param B is the line specified by two points.
		@param strokeWeight is the line weight.
		@param xForm is the transformation matrix.
		@param miterLimit is the miter limit.
		@param joinType is the join type
		@param lineCap is the line cap.
		@param leftIsOpen is true if left end point of line is open.
		@param rightIsOpen is true if right line end point is open.
		@param previousPt is used to compute the miter if left end point is not open.
		@param xMin is the minimum bound for the line along the x-axis.
		@param xMax is the maximum bound for the line along the x-axis.
		@param yMin is the minimum bound for the line along the y-axis.
		@param yMax is the maximum bound for the line along the y-axis.
	*/
	virtual void ComputeLineBounds
		(
			const PMPointList& B, // 2 points
			const PMReal& strokeWeight,
			const PMMatrix& xForm,
			const PMReal& miterLimit,
			int32 joinType,
			int32 lineCap,
			bool16 leftIsOpen,
			bool16 rightIsOpen,
			PMPoint* previousPt, // use for miter limit
			PMReal* xMin,
			PMReal* xMax,
			PMReal* yMin,
			PMReal* yMax
		) = 0;

	/**	Return the default color space manager servic.
	*/
	virtual IColorSpaceMgr* QueryDefaultColorSpaceMgr() = 0;

	/**	Setup the rasterport by calling all RasterSetup service providers.
		@param rPort is the raster to setup.
		@return kTrue is rasterport is setup successfully.
	*/
	virtual bool8 SetupRasterPort(IRasterPort* rPort) = 0;

	/**	Return the bounding box of the clip/update rect for the specified GraphicsData.
		@param gd is the graphics data.
		@return the bounding box of the clip or update rect.
	*/
	virtual PMRect GetUpdateClipRect (GraphicsData* gd) = 0;

};


#endif	// __IGraphicsUtils__
