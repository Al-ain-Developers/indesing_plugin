//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IModifyPathPointsCmdData.h $
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
#ifndef __IModifyPathPointsCmdData__
#define __IModifyPathPointsCmdData__

#include "IPMUnknown.h"
#include "SplineID.h"
#include "PMMatrix.h"
	
/**  
	Specifies the points to modify in an existing page item.
	
	For Modify path and Remove path point commands, all arguments are used.
	For Add point commands, only SetStartingIndex and SetPathIndex are used.
	In the Add case the starting index indicates the place the cmd
	should insert before. i.e if index is 4 the add cmd inserts before 
	index 4. If the index is -1 the add command appends the new points.
	If the pathIndex is equal to the current number of paths the cmd
	creates a new path.  If pathIndex is -1 add points creates a new
	path, appends the points to the new path, and returns the new index
	via this interface (it changes pathIndex).  If the number of points
	to add is zero in the path geometry interface of the command, then
	add points simply creates a new path with no points.
	
	If both startingIndex and pathIndex are equal to -1, then add points
	appends all of the paths and points from the command to the pageitem.
*/
class IModifyPathPointsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMODIFYPATHPOINTSCMDDATA } ;

	/** Indicates the starting index in the pageitem's path geometry */
	virtual void SetStartingIndex (int32 startingIndex) = 0;

	/** Indicates the number of consecutive points to be modified */
	virtual void SetNumPoints (int32 numPoints) = 0;

	/** Indicates which path the modification should occur. Only
		one path per modify path points/add points/ remove points */
	virtual void SetPathIndex (int32 pathIndex) = 0;

	/** Indicates the transformation to use when adding of modifying points */
	virtual void SetTransformMatrix(const PMMatrix& transformMatrix) = 0;

	/** Returns the path the cmd should modify */
	virtual int32 GetPathIndex() const = 0 ;

	/** Returns the starting index */
	virtual int32 GetStartingIndex() const = 0 ;

	/** Returns the number of points to be modified */
	virtual int32 GetNumPoints() const = 0 ;

	/** Return the matrix used for transformations */
	virtual PMMatrix GetTransformMatrix() const = 0 ;
};

#endif	// __IModifyPathPointsCmdData__
