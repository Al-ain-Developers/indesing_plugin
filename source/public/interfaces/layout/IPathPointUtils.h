//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathPointUtils.h $
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
#ifndef __IPathPointUtils__
#define __IPathPointUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"


#include "PMRect.h"
#include "ITransform.h"
#include "PMPathPoint.h"

class PathSelectionList;
class ICommand;
class UIDList;
class PMMatrix;
class IPathGeometry;
class IPathSelectionSuite;

/**
	Utility methods related to path point transformations.
	<pre>
	Utils&lt;IPathPointUtils&gt;()->PreStorePathPoints(...) ;
	</pre>
	@ingroup layout_util
*/
class IPathPointUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHPOINTUTILS };

	/**
		Use prior to a path point transformation to store existing points for undo
		@param list is the path point selection to store IN
		@param storage is the container for storing the path points OUT
		@param ignoreSegments if kTrue, ignores selected segments IN
	*/
	virtual void PreStorePathPoints( const PathSelectionList& list, PMPathPointList& storage, bool16 ignoreSegments = kFalse ) const = 0;
	/**
		Use after a path point transformation to restore pre-existing points.
		Presumes same args from matching call to PreStorePathPoints.
		@param list is the path point selection to restore IN
		@param storage contains the stored path points IN
		@param ignoreSegments if kTrue, ignores selected segments IN
	*/
	virtual void RestorePathPoints( const PathSelectionList& list, PMPathPointList& storage, bool16 ignoreSegments = kFalse ) const = 0;
};

#endif	// __IPathPointUtils__
