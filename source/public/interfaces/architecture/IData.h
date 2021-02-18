//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IData.h $
//  
//  Owner: Mat Marcus
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
#ifndef __IDatah__
#define __IDatah__

#include "IPMUnknown.h"

/** Template class for properties - provides a basic mechanism for getting and setting a property (vector of properties, etc) of type T.
	The Get() and Set() methods provide a typeless interface to any property in the system.

	@note CData exists as a straightforward base class.
	@see CData
*/
template <class T>
class IData : public IPMUnknown
{
public:
	typedef T value_type;

	/** Get the value of the property.
	@return a const reference to the property.
	*/
	virtual const T& Get() const = 0;
	/** Set the value of the property.
	@param data a const reference to the property. The encapsulated property will be updated with this value.
	*/
	virtual void Set(const T& data) = 0;
};



#endif //__IDatah__
