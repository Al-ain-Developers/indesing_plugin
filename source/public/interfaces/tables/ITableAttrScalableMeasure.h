//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrScalableMeasure.h $
//  
//  Owner: Joe Shankar
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
#ifndef __ITableAttrScalableMeasure__
#define __ITableAttrScalableMeasure__

#include "IPMUnknown.h"
#include "TablesID.h"

class AttributeBossList;

class ITableAttrScalableMeasure : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITABLEATTRSCALABLEMEASURE };

		/**
		Returns kTrue if the Attribute is able to scale given the specified
		scale factors but not necessarily if it would scale. 
		*/
		virtual bool16	CouldScale(const PMReal& xScale, const PMReal& yScale) const = 0;

		virtual void	ScaleMeasure(const PMReal& xScale, const PMReal& yScale,
										AttributeBossList& addToList) const = 0;
};

#endif

