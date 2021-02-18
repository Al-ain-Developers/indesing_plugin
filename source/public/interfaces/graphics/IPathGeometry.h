//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathGeometry.h $
//  
//  Owner: Scott Chai
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
//  IPathGeometry is designed to support geometric data of straight and curved paths.
//  
//  Path geometry can contain multiple paths.  Each path is either open (the default) or closed.
//  The relationship between the paths is only that they exist as part of the same object
//  
//  IPathGeometry is a required interface of spline type page items.  
//  
//========================================================================================

#pragma once
#ifndef __IPathGeometry__
#define __IPathGeometry__

#include "IPMUnknown.h"
#include "GraphicsID.h"
#include "PMPathPoint.h"

class PMMatrix;
class PMRect;
class PMPathPoint;
class IOutlineInfo;

/**
	IPathGeometry is designed to support geometric data of straight and curved paths.
  
	Path geometry can contain multiple paths. Each path is either open (the default) or closed.
	The relationship between the paths is only that they exist as part of the same object.
  
	IPathGeometry is a required interface of spline type page items.  
*/
class IPathGeometry : public IPMUnknown
{
public:
	/**
		Define the default interface IID as IID_IPATHGEOMETRY.
	*/
	enum { kDefaultIID = IID_IPATHGEOMETRY } ;

	/**
		kDefaultPathSize = 8 which defines the default number of path points for each path is 8.
	*/
	enum { kDefaultPathSize = 8 };

	/**
		Get the total number of paths of this item.

		@return int32 the total number of paths.
	*/
	virtual int32 GetNumPaths() const = 0;

	/**
		Get the total number of points associated with whichPath. 
		
		@param whichPath [IN] parameter specifies the index of path on the object.
		@returns int32 total number of points, return 0 if whichPath is out of range.
	*/
	virtual int32 GetNumPoints(int32 whichPath) const = 0;

	/**
		Get the total number of actual segments associated with whichPath. 
		
		@param whichPath [IN] parameter specifies the index of path on the object.
		@return int32 total number of segments, returns 0 if whichPath is out of range.
	*/
	virtual int32 GetNumSegments(int32 whichPath) const = 0;

	/**
		Get the list of path points associated with whichPath and whichSegment.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param whichSegment [IN] parameter specified which segment within the give path.
		@param pathPtList [OUT] parameter stored the returned path point list.
		@return PMPathSegmentType type of segments that could be line, curve or no segment.
		@see PathTypes.h for the definition of PMPathSegmentType.
		@see PathPathPoint.h for the definition of PMPathPointList.
	*/
	virtual PMPathSegmentType GetNthSegment( int32 whichPath, int32 whichSegment, PMPathPointList& pathPtList ) const = 0 ;

	/**
		Get the nth point information associated with whichPath and the which point.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param n [IN] parameter specified which point.
		@return const PMPathPoint& the information of nth point on the given path.
		@see PMPathPoint.h for the definition of PMPathPoint.
	*/
	virtual const PMPathPoint& GetNthPoint(int32 whichPath, int32 n) const = 0;

	/**
		Get the path points information that make up the nth path.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param pathPtList [OUT] parameter stored the returned path point list.
		@return void.
	*/
	virtual void GetNthPath( int32 whichPath, PMPathPointList& pathPtList ) const = 0 ;

	/**
		Get the total number of points on all paths (if any).

		@return int32 the total number of points.
	*/
	virtual int32 GetTotalPoints() const = 0 ;

	/**
		Check if there are any points on any of the paths (if any).

		@return bool16 kTrue if there is no points at all, otherwise kFalse.
	*/
	virtual bool16 IsEmpty() const = 0 ;

	/**
		Check if there is only a single point in the object.
		
		@param pt [OUT] parameter that is set to the single point (if any).
		@return kTrue if there is only a single point, otherwise kFalse.
	*/
	virtual bool16 IsSinglePoint( PMPathPoint* pt = nil ) const = 0 ;

	/**
		Check if there are two or more points in the object.

		@return bool16 kTrue if there are multiple points, otherwise kFalse.
	*/
	virtual bool16 IsMultiPoint() const = 0 ;

	/**
		Appends a new path to the object. 

		@param preallocatePoints [IN] parameter an optimization which allows the IPathGeometry implementation
		to pre-allocate a large enough path if the number of points to add is known ahead of time.
		@return int32 the index of the new path in the object.
	*/
	virtual int32 AddNewPath(int32 preallocatePoints = kDefaultPathSize) = 0;

	/**
		Inserts a new path to the object.

		@param before [IN] parameter the location where we insert into.
		@param preallocatePoints [IN] param an optimization which allows the IPathGeometry implementation
		to pre-allocate a large enough path if the number of points to add is known ahead of time.
		@return void.
	*/
	virtual void InsertNewPath( int32 before, int32 preallocatePoints = kDefaultPathSize ) = 0 ;

	/**
		Remove the specified path and all associated points on the path.

		@param whichPath [IN] parameter  specifies the index of path on the object.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode RemoveNthPath(int32 whichPath) = 0;

	/**
		Remove all paths and points of the object.

		@return void.
	*/
	virtual void RemoveAllPaths() = 0;

	/**
		Remove all paths and their associated points on those path except the specified path.

		@param whichPath [IN] parameter specifies the index of path on the object that will NOT be removed.
		@return void.
	*/
	virtual void RemoveAllButNthPath( int32 whichPath ) = 0 ;

	/**
		Add the point to whichPath. The path must have been created with AddNewPath(). 
		If whichPath doesn't exist the call fails.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param pt [IN] parameter the specified path point.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode AddPoint(int32 whichPath, const PMPathPoint &pt) = 0;

	/**
		Remove the nth point from the given path. 

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param z [IN] parameter the index of point on whichPath.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode RemoveNthPoint(int32 whichPath, int32 z) = 0;

	/**
		Remove all the points of whichPath. Don't delete the path itself.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode RemoveAllPoints (int32 whichPath) = 0;

	/**
		Insert point on the path. 

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param before [IN] parameter specifies the location of the point to be inserted into.
		@param pt [IN] parameter the point information that is inserted. 
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode InsertNthPoint(int32 whichPath, int32 before, const PMPathPoint &pt) = 0;

	/**
		Modify the point on the path.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@param before [IN] parameter specifies the location of the point to be inserted into.
		@param pt [IN] parameter the point information that is inserted. 
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode ModifyNthPoint(int32 whichPath, int32 index, const PMPathPoint& pt) = 0;

	/**
		Copies all paths from fromPath to this. Implicitly removes existing paths in this before copying.

		@param fromPath [IN] parameter specifies the source path geometry information which we copy from.
		@return void.
	*/
	virtual void CopyPath (IPathGeometry* fromPath) = 0;

	/**
		Replaces a subpath in this with a subpath copied from another path object. If
		copyToPathIndex is not a valid path index in this, a new path is appended to this instead.

		@param copyToPathIndex [IN] parameter the path index of target object(this).
		@param fromPath [IN] parameter the path geometry information of the source object.
		@param copyFromPathIndex [IN] parameter the path index of source object.
		@return void.
	*/
	virtual void CopyNthPath( int32 copyToPathIndex, IPathGeometry* fromPath, int32 copyFromPathIndex ) = 0 ;

	/**
		Get the bounding box of all points and all paths with specified coordicate system. 
	
		@param theMatrix [IN] parameter indicates which coordicnate space to compute the result bounding box such as InnerToPasteboard.
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetCtrlPointsBoundingBox(const PMMatrix& theMatrix) const = 0;

	/**
		Get the bounding box of all points and all paths with inner coordinate system. 
		
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetCtrlPointsBoundingBox() const = 0;

	/**
		Set the bounding box in inner coordinate system.

		@param newPtBBox [IN] parameter specified the new bounding box.
		@return void.
	*/
	virtual void SetCtrlPointsBoundingBox (const PMRect& newPtBBox) = 0;

	/**
		Set the bounding box with the specified coordinate system.

		@param theMatrix [In] parameter that may change the transform of the item depending on the implementation of IPathGeometry.
		@param newBBox [In] parameter used to set the new bounding box.
		@return void.
	*/
	virtual void SetCtrlPointsBoundingBox (const PMMatrix& theMatrix, const PMRect& newPtBBox) = 0;

	/**
		Get the bounding box of the path excluding ctrl points.

		@param theMatrix [In] parameter indicates which space to compute the box such as InnerToPasteboard.
		@return PMRect the result bounding box. 
	*/
	virtual PMRect GetPathBoundingBox(const PMMatrix& theMatrix) const = 0;

	/**
		Get the bounding box of the path in inner coordinate system.

		@return PMRect the result bounding box. 
	*/
	virtual PMRect GetPathBoundingBox() const = 0;

	/**
		Set the bounding box of the path excluding ctrl points.

		@param theMatrix [IN] parameter indicates which space to compute the bounding box such as InnerToPasteboard.
		@param newBBox [In] parameter used to set the new bounding box.
		@return void.
	*/
	virtual void SetPathBoundingBox(const PMMatrix& theMatrix, const PMRect& newBBox) = 0;

	/**
		Set the path bounding box in inner coordinate system.

		@param newBBox [In] parameter used to set the new bounding box.
		@return void.
	*/
	virtual void SetPathBoundingBox(const PMRect& newBBox) = 0;

	/**
		Iterate over all the path and transform them based on the given matrix.

		@param theMatrix [IN] parameter indicates which coordinate system to use to transform such as InnerToPasteboard.
		@return void.
	*/
	virtual void TransformPath (const PMMatrix& theMatrix) = 0;

	/**
		Iterate over all path points and transform them based on the given matrix. Does not ignore locked item.

		@param pts [IN] parameter indicates which points should be transformed in this object.
		@param mat [IN] parameter indicates which coordinate system to use to transform such as InnerToPasteboard.
		@param ignoreSegments [IN] parameter indicates if we should exclude segments or not.
		@param permitFlips [IN] parameter indicates if we allow to flip or not.
		@return void.
	*/
	virtual void TransformPathPoints( const PointSelectorList& pts,
										   const PMMatrix& mat,
										   bool16 ignoreSegments,
										   bool16 permitFlips ) = 0;

	/**
		Get the outline information of all paths. Iterate over all paths and call back via iOutlineInfo.

		@param iOutlineInfo [IN] parameter used as the call back function.
		@return void.
	*/
	virtual void GetOutlineInfo (IOutlineInfo* iOutlineInfo) const = 0;

	/**
		Mark the path as open.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode OpenPath(int32 whichPath) = 0;

	/**
		Mark the path as closed.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode ClosePath(int32 whichPath) = 0;

	/**
	   Check if the specified path is open or not.

	   @param whichPath [IN] parameter specifies the index of path on the object.
	   @return bool16 kTrue if path is closed, otherwise kFalse.
	*/
	virtual bool16 IsPathOpen(int32 whichPath) const = 0;

	/**
		Reverse the path.

		@param whichPath [IN] parameter specifies the index of path on the object.
		@return ErrorCode result of the operation.
	*/
	virtual ErrorCode ReversePath( int32 whichPath ) = 0 ;

	/**
		Get the outline information of the given path. Iterate over a path and call back via iOutlineInfo.

		@param iOutlineInfo [IN] parameter used as the call back function.
		@param whichPath [IN] parameter specifies the index of path on the object.
	*/
	virtual void GetOutlineInfo( IOutlineInfo* iOutlineInfo, int32 whichPath ) const = 0 ;

	/**
	   Check if the specified path is closed or not.

	   @param whichPath [IN] parameter specifies the index of path on the object.
	   @return bool16 kTrue if path is closed, otherwise kFalse.
	*/
	virtual bool16 IsPathClosed( int32 whichPath ) const = 0 ;
} ;

#endif	// __IPathGeometry__
