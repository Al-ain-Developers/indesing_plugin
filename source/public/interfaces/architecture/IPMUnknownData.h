//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMUnknownData.h $
//  
//  Owner: Michael_Martz
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
#ifndef _IPMUnknown_Data_
#define _IPMUnknown_Data_

#include "IPMUnknown.h"
#include "CommandID.h"	//IID_IPMUNKNOWNDATA

/** Data interface used for holding a pointer to a non-persistent boss object. For persistent
	boss objects, use the UID instead (say, store in interface of type IUIDData).
	
	The implementation of this interface owns the reference to the boss object.
	
	@see IUIDData
	@ingroup arch_coredata
*/
class IPMUnknownData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPMUNKNOWNDATA };
		
		/** Get the value of the pointer. The value returned is NOT AddRef'd, so 
			the caller is responsible for doing AddRef and (later) Release on the
			pointer.
			@return IPMUnknown* the value of the data interface
		*/
		virtual IPMUnknown*	GetPMUnknown			(void) const = 0;
		
		/** Set the value of the pointer. The old object it held, if there was one,
			is released, and the new pointer is AddRef'd.
			@param IPMUnknown* the new value of the data interface
		*/
		virtual void		SetPMUnknown			(IPMUnknown*) = 0;
};
		
#endif // _IPMUnknown_Data_
