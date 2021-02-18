//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorGroupReference.h $
//  
//  Owner: ankugupt
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IColorGroupReference__
#define __IColorGroupReference__

#include "ShuksanID.h"
#include "IPMUnknown.h"
#include "ColorSystemID.h"

/** A UID data interface that holds a reference to a color group by UID only.
*/
class IColorGroupReference : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ICOLORGROUPREFERENCE};

	/** Set the value.
		@param id UID of the object
	*/
	virtual void SetUID (const UID& id) = 0;
	
	/** Get the value.
		@return UID the UID of the object.
	*/
	virtual UID GetUID () const = 0;
};


#endif //__IColorGroupReference__
