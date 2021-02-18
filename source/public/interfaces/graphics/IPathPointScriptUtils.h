//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathPointScriptUtils.h $
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
#ifndef __IPathPointScriptUtils__
#define __IPathPointScriptUtils__

#include "SplineID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IPageItemScriptUtils.h"

class ICommand ;
class IPathGeometry ;
class IScriptRequestData;

/**
	Utility methods related to path and path point proxy objects in scripting.
	<pre>
	Utils&lt;IPathPointScriptUtils&gt;()->QueryNthPath(...) ;
	</pre>
	@ingroup layout_util
*/

class IPathPointScriptUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHPOINTSCRIPTUTILS } ;

	/**
		Create a new path proxy object
		@param data is the script event data
		@param pageitem is the parent page item
		@param n is the 0-based index of the path
		@return the new proxy path object
	*/
	virtual IScript* QueryNthPath( const IScriptRequestData* data, IScript* pageitem, int32 n ) const = 0 ;
	/**
		Create a new path point proxy object
		@param data is the script event data
		@param path is the parent path
		@param n is the 0-based index of the path point
		@return the new proxy path point object
	*/
	virtual IScript* QueryNthPoint( const IScriptRequestData* data, IScript* path, int32 n ) const = 0 ;

	/**
		Query parents up the hierarchy until a specified interface is found
		@see IHierarchy
		@param script is the child object of which to query the parents
		@param iid is the desired interface
		@param context provides the scripting context for this request IN
		@return the desired interface on a parent, or nil if no parent with the specified interface is found
	*/
	virtual IPMUnknown* QueryParentForInterface( IScript* script, PMIID iid, const RequestContext& context ) const = 0 ;

	/**
		Determine the 0-based index of the path that is represented by a proxy script object
		@param pathOrPoint is the proxy script object
		@return the index
	*/
	virtual int32 GetPathIndex( IScript* pathOrPoint ) const = 0 ;
	/**
		Determine the 0-based index of the path point that is represented by a proxy script object
		@param point is the proxy script object
		@return the index
	*/
	virtual int32 GetPointIndex( IScript* point ) const = 0 ;

	/**
		Get the coordinates of a path point
		@param data is the script event data
		@param pathGeom is the page item IN
		@param pathIndex is the path index IN
		@param pointIndex is the point index IN
		@param ptIndex is the handle within the point IN
		@param offsetPoint is the spread offset IN
		@param scriptData is the coordinates of the path point OUT
		@return kSuccess if the coordinates were found, kFailure otherwise
	*/
	virtual ErrorCode AccessPoint_Get( IScriptRequestData* data,
										IPathGeometry* pathGeom, 
										int32 pathIndex, 
										int32 pointIndex, 
										PathPointIndex ptIndex, 
										const PMPoint& offsetPoint,
										ScriptData& scriptData ) const = 0 ;
	/**
		Set the coordinates of a path point
		@param data is the script event data
		@param pathGeom is the page item IN
		@param pathIndex is the path index IN
		@param pointIndex is the point index IN
		@param ptIndex is the handle within the point IN
		@param offsetPoint is the spread offset IN
		@param scriptData is the coordinates of the path point IN
		@return the return code of the command to set the coordinates
	*/
	virtual ErrorCode AccessPoint_Set( IScriptRequestData* data, 
										IPathGeometry* pathGeom, 
										int32 pathIndex, 
										int32 pointIndex, 
										PathPointIndex ptIndex, 
										const PMPoint& offsetPoint,
										const ScriptData& scriptData ) const = 0 ;

	/**
		Create a command to modify a path point's type
		@param pathGeom is the page item IN
		@param pathIndex is the path index IN
		@param pointIndex is the point index IN
		@param type is the new type IN
		@param symmetrical if kTrue and type is kCS, the make the two direction lines the same length IN
		@return the unexecuted command
	*/
	virtual ICommand* CreateModifyTypeCmd( IPathGeometry* pathGeom, 
											int32 pathIndex, 
											int32 pointIndex, 
											PMPathPointType type,
											bool16 symmetrical = kFalse) const = 0 ;
	/**
		Create a command to modify the coordinates of a path point
		@param pathGeom is the page item IN
		@param pathIndex is the path index IN
		@param pointIndex is the point index IN
		@param ptIndex is the handle within the point IN
		@param pt is the new coordinates IN
		@return the unexecuted command
	*/
	virtual ICommand* CreateModifyPointCmd( IPathGeometry* pathGeom, 
											int32 pathIndex, 
											int32 pointIndex, 
											PathPointIndex ptIndex, 
											const PBPMPoint& pt ) const = 0 ;

	/**
		Create a command to modify all the points on a path
		@param data is the script event data
		@param pathGeom is the page item IN
		@param pathIndex is the path index IN
		@param offsetPoint is the spread offset IN
		@param listData is the new coordinates for the path's points IN
		@return the unexecuted command
	*/
	virtual ICommand* CreateSetPathAnchorsCmd( IScriptRequestData* data, 
												IPathGeometry* pathGeom, 
												int32 pathIndex, 
												const PMPoint& offsetPoint,
												ScriptListData& listData ) const = 0 ;
} ;

#endif	// __IPathPointScriptUtils__
