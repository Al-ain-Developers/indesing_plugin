//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/IStyleMappingsCmdData.h $
//  
//  Owner: Prakash Verma
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
// NOTICE:  All information contained herein is, and remains
// the property of Adobe Systems Incorporated and its suppliers,
// if any.  The intellectual and technical concepts contained
// herein are proprietary to Adobe Systems Incorporated and its
// suppliers and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material
// is strictly forbidden unless prior written permission is obtained
// from Adobe Systems Incorporated. 
//   
//======================================================================================== 

#ifndef __IStyleMappingsCmdData_h__ 
#define __IStyleMappingsCmdData_h__ 

//interface includes
#include "IStyleMappings.h"

//project includes
#include "SharedContentID.h"

class IStyleMappingsCmdData : public IPMUnknown
{
public:

	/**
		Standard enum to for use with GetDefaultIID() method.
	 */
	enum  { kDefaultIID = IID_ISTYLEMAPPINGSCMDDATA };

	/**
		Set the mapping rule in the command data using the passed mapping rule.
		@param inMappingRule[IN] the mapping rule which is set in the command data.
	 */
	virtual void	SetMappingRule(const IStyleMappings::MappingRule &inMappingRule) = 0;

	/**
		return the mapping rule present in the command data, as an output parameter.
		@param outMappingRule[IN] the returned mapping rule.
	 */
	virtual void	GetMappingRule(IStyleMappings::MappingRule &outMappingRule) const = 0;

	/**
		Set the mapping style type in the command data using the passed parameter.
		@param eInStyleType[IN] the style type which is set in the command data.
	 */
	virtual void	SetStyleType(const IStyleMappings::MappingStyleType &eInStyleType) = 0;

	/**
		return the style type present in the command data, as an output parameter.
		@param outMappingRule[IN] the returned style type.
	 */
	virtual void	GetStyleType(IStyleMappings::MappingStyleType &eInStyleType) const = 0;

	/**
		Set the index corresponding to the mapping rule present in the command data.
		@param index[IN] index of the mapping rule.
	 */
	virtual void	SetIndex(const int32 &index) = 0;

	/**
		returns the index corresponding to the mapping rule present in the command data.
		@return index set inside the command data
	 */
	virtual int32	GetIndex() const = 0;
};

#endif	//__IStyleMappingsCmdData_h__ 
