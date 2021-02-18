//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathCorner.h $
//  
//  Owner: jargast
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
#ifndef __IPathCorner__
#define __IPathCorner__

#include "IPMUnknown.h"
#include "RequestContext.h"
#include "GraphicsID.h"

class PMPoint;
class IOutlineInfo;
class IGraphicStyleDescriptor;
class PMString;

/**
 Defines the interface for installable corners

 A, B, and C are the points determining the location of the corner
 
 <pre>
 A-------C
         |
         |
         B
 
 On input, A is the current point.
 </pre>
 */


class IPathCorner : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHCORNER };

	/**
	 Creates the corner path in pathPort.  The styleDescriptor is an 
	 interface off the path pageitem.  Don't call newpath on pathPort.
	 CreateCornerPath appends the corner to current path in pathPort.
	 
	 @param styleDescriptor		IN The pageitem's graphic style descriptor
	 @param ptA					IN The first corner point
	 @param ptB					IN The second corner point
	 @param ptC					IN The third corner point
	 @param pathPort			OUT The outline info to store the built path
	 @see IGraphicStyleDescriptor
	 @see IOutlineInfo
	 */
	virtual void CreateCornerPath
		(
			IGraphicStyleDescriptor*	styleDescriptor,
			const PMPoint& 				ptA,
			const PMPoint& 				ptB,
			const PMPoint& 				ptC,
			IOutlineInfo* 				pathPort
		) const = 0;

	/**
	 Fills in the text string that describes this type of corner.
	 @param pathCornerName		OUT The name of the corner stroker
	 */
	virtual void GetPathCornerName( PMString* pathCornerName ) const = 0;

	/** Returns the ScriptID associated with this corner effect in the given scripting DOM */
	virtual ScriptID GetScriptID( const ScriptInfo::RequestContext& context ) const = 0;
};

#endif
