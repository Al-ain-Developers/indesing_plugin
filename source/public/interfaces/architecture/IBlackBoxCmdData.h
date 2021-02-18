//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBlackBoxCmdData.h $
//  
//  Owner: robin briggs
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
#ifndef __IBlackBoxCmdData__
#define __IBlackBoxCmdData__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"	// for IID_IBLACKBOXCMDDATA
#include "IBlackBoxData.h"	// for BlackBoxKey

class XMLReference;
class UIDRef;
class IBlackBoxData;

/**	Data interface for Black Box Commands. Normally you should go through
	IBlackBoxCommands.
	@see IBlackBoxCommands
*/
class IBlackBoxCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBLACKBOXCMDDATA };

	/** Set the value of the data. Applies to UID-based elements.
		@param obj - object where the data is applied
		@param clsID - key the data is stored under
		@param buffer - buffer to hold the data
		@param length - length of the data in the buffer
	*/
	virtual void Set(const UIDRef& obj, BlackBoxKey clsID, void *buffer = nil, int32 length = 0) = 0;

	/** Set the value of the data. Applies to XML Elements.
		@param obj - object where the data is applied
		@param clsID - key the data is stored under
		@param buffer - buffer to hold the data
		@param length - length of the data in the buffer
	*/
	virtual void Set(const XMLReference& obj, BlackBoxKey clsID, void *buffer = nil, int32 length = 0) = 0;

	/**	Return the object data is applied to
		@return IBlackBoxData * pointer to the instantiated object
	*/
	virtual IBlackBoxData *QueryTarget() const = 0;

	/**	Return the key the data is stored under
		@return the key the data is stored under
	*/
	virtual BlackBoxKey GetKey() const = 0;

	/**	Return the buffer to hold the data
		@return the buffer containing the data
	*/
	virtual void *GetBuffer() const = 0;
	
	/**	Return the length of the data in the buffer
		@return the length of the data in the buffer
	*/
	virtual int32 GetLength() const = 0;
};

#endif	// __IBlackBoxCmdData__
