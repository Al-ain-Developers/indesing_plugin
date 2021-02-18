//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IInterfaceIDData.h $
//  
//  Owner: Roey Horns
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
#ifndef __IINTERFACEIDDATA__
#define __IINTERFACEIDDATA__

#include "ShuksanID.h"
#include "IPMUnknown.h"

/** Data interface that stores an interface identifier (PMIID).
	@ingroup arch_coredata 
*/
class IInterfaceIDData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINTERFACEIDDATA };
		
		/** Set the interface ID. 
			@param id	new value for the PMIID
		*/
		virtual void Set(PMIID id) = 0;

		/** Return the interface ID.
			@return	The interfaceID
		*/
		virtual PMIID GetInterfaceID() const = 0;
};

#endif
