//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrTabSettings.h $
//  
//  Owner: Eric_Kenninga
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
#ifndef __ITextAttrTabSettings__
#define __ITextAttrTabSettings__

#include "IPMUnknown.h"
#include "TabStop.h"
#include "TextAttrID.h"


/** Text Attribute interface for tabs.  Provides access to the tab stops (via the TabStopTable) for this paragraph.
	@ingroup text_attr
	@ingroup text_tab
	@see TabStopTable
*/
class ITextAttrTabSettings : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRTABS };

		typedef const TabStopTable&		ValueType;

		/** */
		void Set(ValueType tab)
			{ SetTabStopTable(tab); }
		/** */
		ValueType Get() const
			{ return GetTabStopTable(); }

		/** */
		virtual void SetTabStopTable(const TabStopTable& tab) = 0;
		/** */
		virtual const TabStopTable& GetTabStopTable() const = 0;
};

#endif
		// __ITextAttrTabSettings__
