//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrLineStyleList.h $
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
#ifndef __ITextAttrLineStyleList__
#define __ITextAttrLineStyleList__

#include "IPMUnknown.h"
#include "RunInLineStyleList.h"
#include "TextAttrID.h"


/** Simple data interface for holding the list of run-in styles applied to the paragraph
	@ingroup text_attr
*/
class ITextAttrLineStyleList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRLINESTYLELIST };
		enum { kMaximumNumberOfLineStyleRules = 100 };

		typedef RunInLineStyleList		ValueType;

			/** assign the RunInStyleList associated with this interface (usually as a text attribute)
				@param ValueType = standardized alias to RunInStyleList
			*/
		void Set(const ValueType& list)
			{ SetStyleList(list); }

			/** @return the RunInStyleList associated with this interface, more standardized naming */
		ValueType Get() const
			{ return GetStyleList(); }

			/** assign the RunInStyleList associated with this interface (usually as a text attribute)
				@param RunInStyleList
			*/
		virtual void SetStyleList(const RunInLineStyleList& list) = 0;

			/** @return the RunInStyleList associated with this interface */
		virtual RunInLineStyleList GetStyleList() const = 0;
};

#endif
		// __ITextAttrLineStyleList__
