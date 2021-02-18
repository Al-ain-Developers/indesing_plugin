//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathFinder.h $
//  
//  Owner: dstephen
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
#ifndef __IPathFinder__
#define __IPathFinder__

#include "IPMUnknown.h"
#include "GraphicTypes.h"
#include "PMReal.h"

class IPathGeometry;
class IOutlineInfo;

#include "OffsetPathID.h"

const PMReal kDefaultFlatness = 3.0;
const PMReal kMinFlatness = 0.01;
const PMReal kMaxFlatness = 100.0;

/** IPathFinder is an interface for intersecting, unioning, differencing or xoring
multiple paths.
*/
class IPathFinder : public IPMUnknown
{
public:
	/** default IID for this interface */
	enum {
		kDefaultIID = IID_IPATHFINDER
	};
	
	/** PathType is used to determine whether interior paths are holes or not.
	*/
	enum PathType {
		/** Use non-zero winding rule to determine insideness */
		kNon_zero,

		/** Use even-odd rule to determine insideness */
		kEven_odd
	};
	
	/** CombineType defines the various ways to combine multiple paths
	*/
	enum CombineType {
		kIntersect,
		kUnion,
		kDifference,
		kXOr
	};

	/** Add a path to the PathFinder engine - Call this once for each input path
		@param pathData - IN: A source path.
		@param pathType - IN: Rule used to determine insideness.
		@return ErrorCode if failure or 0 if success.
	*/
	virtual ErrorCode AddPath 
	(
		const IPathGeometry*	pathData,
		PathType				pathType = kEven_odd
	) = 0;

	/** Combine the paths supplied via AddPath() in the order supplied.
		@param result - OUT: The resulting path.
		@param combineType - IN: How you want the input paths combined.
		@param resultType - IN: Insideness rule to assign to the resulting path.
		@param flatness - IN: Postscript flatness value between kMinFlatness and kMaxFlatness 
		@return ErrorCode if failure or 0 if success.
	*/
	virtual ErrorCode Combine
	(
		IPathGeometry*			result,
		CombineType				combineType,
		PathType				resultType = kEven_odd,
		PMReal					flatness = PMReal(kDefaultFlatness)
	) = 0;

			
};

#endif
