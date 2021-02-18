//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMeasurementSystem.h $
//  
//  Owner: psorrick
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
#ifndef __IMeasurementSystem__
#define __IMeasurementSystem__

#include "IPMUnknown.h"
#include "MeasurementSystemID.h"
#include "RequestContext.h"

class IUnitOfMeasure;

/** IMeasurementSystem is an interface through which units of measure can be accessed.
	A unit of measure boss is any boss that implements the IUnitOfMeasure interface.
	Units of measure loaded by interating over the object model, which is why this
	interface only has methods for accessing units of measure.
*/
class IMeasurementSystem : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEASUREMENTSYSTEM };

	/** The points unit of measure must be installed first. */
	enum { kPointMeasure = 0 };

	/** Return the index of the measurement system whose class id
		is specified in 'classId'. */
	virtual int32			Location(const ClassID& classId) const = 0;

	/** Count the number of IUnitOfMeasure systems available. */
	virtual int32			GetNumberOfUnits() const = 0;

	/** Given measurement system index, query for the unit of
		measure corresponding to that index. */
	virtual IUnitOfMeasure*	QueryUnitOfMeasure(int32 index) const = 0;

	/** Returns the unit of measure associated with a script ID 
		in a particular scripting DOM */
	virtual IUnitOfMeasure* QueryUnitOfMeasure( const ScriptID& id, const ScriptInfo::RequestContext& context ) const = 0;

	/** Internal Use Only: Clean up the measurement system on shutdown */
	virtual void			Cleanup() = 0;
};

#endif
