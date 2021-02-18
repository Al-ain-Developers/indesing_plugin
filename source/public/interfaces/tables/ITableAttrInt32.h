//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrInt32.h $
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
#ifndef __ITableAttrInt32__
#define __ITableAttrInt32__

#include "IPMUnknown.h"
#include "TablesID.h"

/** Data interface for an integer (int32) table attribute.
*/
class ITableAttrInt32 : public IPMUnknown
{
public:
		enum  { kDefaultIID = IID_ITABLEATTRINT32 };

		typedef  int32 value_type;

		/** Accessor. */
		virtual value_type	Get() const = 0;
		/** Mutator. */
		virtual void		Set(value_type val) = 0;
};

#endif	// __ITableAttrInt32__
