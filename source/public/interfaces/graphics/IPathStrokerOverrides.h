//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStrokerOverrides.h $
//  
//  Owner: Greg St. Pierre
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPathStrokerOverrides__
#define __IPathStrokerOverrides__

#include "InstStrokeFillID.h"

/**
 Interface for controlling overrides to graphic attributes on a per-path 
 stroker basis. This is used by the stroke palette to disable controls that 
 should be set to hard-coded values when a particular stroker is selected.
 For instance, the dotted stroker requires that round caps and joins be used.

 @see IPathStroker
 */
class IPathStrokerOverrides : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKEROVERRIDES };

	/**
	 Accessor for whether line cap is to be overridden for this stroker.
	 Implementation should return kTrue if the cap should be overridden,
	 else kFalse.

	 @return A boolean indicating override status
	 */
	virtual bool16 GetOverridesLineCap() const = 0;

	/**
	 Accessor for hard-coded line cap to use for this path stroker. This
	 method will only be called when GetOverridesLineCap returns kTrue.
	 
	 @return Line cap to use for this stroker
	 @see Enum in GraphicTypes.h
	 */ 
	virtual int32 GetLineCap() const = 0;

	/**
	 Accessor for whether line join is to be overridden for this stroker.
	 Implementation should return kTrue if the join should be overridden,
	 else kFalse.

	 @return A boolean indicating override status
	 */
	virtual bool16 GetOverridesLineJoin() const = 0;

	/**
	 Accessor for hard-coded line join to use for this path stroker. This
	 method will only be called when GetOverridesLineJoin returns kTrue.
	 
	 @return Line cap to use for this stroker
	 @see Enum in GraphicTypes.h
	 */ 
	virtual int32 GetLineJoin() const = 0;
};

#endif //!def __IPathStrokerOverrides__
