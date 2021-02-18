//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IWidgetIDData.h $
//  
//  Owner: Yeming Liu
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
//  Purpose:	Interface for handling widget id.
//  
//========================================================================================

#pragma once
#ifndef __IWIDGETIDDATA__
#define __IWIDGETIDDATA__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "widgetid.h"

/**
   This is a data interface to allow clients to get/set widget id.
*/
class IWidgetIDData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWIDGETIDDATA };
		
		/**
		   Set the widget id as the new widget id passed in.

           @param WidgetID The new widget id to be set.
		*/
		virtual void Set(const WidgetID& id) = 0;

		/**
		   Get the cached widget id.

           @return WidgetID cached in the data.
		*/
		virtual WidgetID GetWidgetID() const = 0;
};

#endif //__IWIDGETIDDATA__
