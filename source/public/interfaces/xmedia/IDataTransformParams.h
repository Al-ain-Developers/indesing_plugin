//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IDataTransformParams.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IDataTransformParams_h__
#define __IDataTransformParams_h__

#include "IPMUnknown.h"
#include "DataServicesID.h"

class ISAXAttributes;
class IDataServicesOptions;

/**
	Class responsible for retrieving data transform parameters from a stream
	holding the data transformation specification. e.g. the XSL stylesheet, when the 
	transformation is and XSL transformation.
*/

class IDataTransformParams : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATATRANSFORMPARAMS };

/**
   Inspects the transform specification in stream for transform parameters. Any parameters
   that are found are returned.
   @param options IN Contains the transformation options currently in effect.
   @param stream IN The stream holding the transform specification.
   @return The list of parameters to the transform.
 */
	virtual ISAXAttributes* QueryForParamValues(IDataServicesOptions* options, IPMStream* stream) const = 0;
};

#endif	// __IDataTransformParams_h__
