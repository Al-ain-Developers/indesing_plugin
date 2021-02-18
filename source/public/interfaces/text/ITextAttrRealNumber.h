//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrRealNumber.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __ITextAttrRealNumber__
#define __ITextAttrRealNumber__

#include "IPMUnknown.h"
#include "TextAttrID.h"


/** Interface for a text attribute whose value is represented by a real number.
	@ingroup text_attr
*/
class ITextAttrRealNumber : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRREALNUMBER };

		typedef  PMReal				ValueType;
		typedef  PMReal				value_type;

		/** */
		virtual const value_type& Get() const = 0;
		/** A well-behaved implementation will enforce the limits, if any, returned by HasLimits().  If the value exceeds either limit, it should be set to that limit.
		*/
		virtual void Set(const value_type& val) = 0;

		/** Report whether or not this attribute has upper and/or lower limits and what they are. The limits are the same units as the value.
		@param lLim IN If the return value is kTrue, is the lower limit of valid values.  (value will always be >= the returned value)
		@param uLim IN If the return value is kTrue, is the upper limit of valid values.  (value will always be <= the returned value)
		@return if the return value is kFalse the parameter values are undefined.
		@note the caller has ultimate responsibility for enforcing the limits.  i.e. although well-behaved implementations will enforce the limits, not all are.
				Also, how the limits are enforced may vary with each implementation - i.e. some silently ignore the invalid values, some set to the nearest limit.
		*/
		virtual bool16 HasLimits(value_type& lLim, value_type& uLim) const = 0;

		/** */
		const value_type& GetRealNumber() const { return Get();}
		/** */
		void SetRealNumber(const value_type& val) { Set(val); }
};

#endif
