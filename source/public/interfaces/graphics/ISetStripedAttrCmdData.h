//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISetStripedAttrCmdData.h $
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
//  Defines the interface by which a stroker determines its parameters, which
//  
//  for now include start and width pairs (each is a percentage of the stroke width)
//  
//========================================================================================

#pragma once
#ifndef __ISetStripedAttrCmdData__
#define __ISetStripedAttrCmdData__

#include "ScotchRulesID.h"

/**
 Interface defining data to be used by the SetStripedAttribute command.

 Stores parameters used by the striped stroker. Each parameter consists of
 a pair of values: one that specifies the start position as a percentage of the
 stroke weight, and one that specifies the width (also as a percentage).
 */
class ISetStripedAttrCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETSTRIPEDATTRCMDDATA };

	/**
	 Returns the number of parameters stored in command data

	 @return The number of parameters stored
	 */
	virtual uint32 GetParamCount() const = 0;
	
	/**
	 Sets the number of parameters to be stored. If count is greater than 
	 current length, the additional parameters are defaulted to zeroes. If
	 count is less than current length, existing values are truncated.

	 @param count	IN New count of parameters for command data
	 */
	virtual void SetParamCount(uint32 count) = 0;
	
	/**
	 Retrieves the n'th parameter's start and width. If n identifies a valid
	 index in the command data, the start and width out parameters are set to
	 the values of the n'th parameter. Otherwise, start and width are undefined.

	 @param n		IN Index of parameter to retrieve
	 @param start	OUT Parameter's start value
	 @param width	OUT Parameter's width value
	 */
	virtual void GetNthParam(uint32 n, PMReal &start, PMReal &width) const = 0;
	
	/**
	 Sets the n'th parameter's start and width values. If n identifies a valid
	 index in the command data, its start and width are set accordingly. Other-
	 wise, the method silently fails.

	 @param n		IN Index of parameter to set
	 @param start	IN New start value for parameter
	 @param width	IN New width value for parameter
	 */
	virtual void SetNthParam(uint32 n, PMReal const &start, PMReal const &width) = 0;
};

#endif //!def __ISetStripedAttrCmdData__
