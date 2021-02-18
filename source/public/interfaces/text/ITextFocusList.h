//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFocusList.h $
//  
//  Owner: Yves Carbonneaux
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
#ifndef __ITextFocusList__
#define __ITextFocusList__


#include "IPMUnknown.h"
#include "TextID.h"

class ITextFocus;


/** 
	@ingroup text_focus
*/
class ITextFocusList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTFOCUSLIST };
		
		virtual bool16	GetFirstFocus(UIDRef& textModelRef,
										TextIndex& start, TextIndex& end, bool16* leanLeft = nil) = 0;

		virtual bool16	GetNextFocus(UIDRef& textModelRef,
										TextIndex& start, TextIndex& end, bool16* leanLeft = nil) = 0;

};


#endif		// __ITextFocusList__

