//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IAutoCorrectPrefs.h $
//  
//  Owner: Heath Horton
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

#ifndef _H_IAutoCorrectPrefs__
#define _H_IAutoCorrectPrefs__

#include "SpellingServiceID.h"
#include "AutoCorrect.h"

class AutoCorrectItem;
class AutoCorrectList;


class IAutoCorrectPrefs : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IAUTOCORRECTPREFS };

	virtual bool16 	GetAutoCorrect() const = 0;
	virtual void 	SetAutoCorrect(bool16 autoCorrect) = 0;

	virtual bool16 	GetAutoCorrectCapitalizationErrors() const = 0;
	virtual void 	SetAutoCorrectCapitalizationErrors(bool16 autoCorrectCapitalizationErrors) = 0;

	virtual const AutoCorrectList& GetAutoCorrectList() const = 0;
	virtual void 	SetAutoCorrectList(const AutoCorrectList& list) = 0;

	virtual void	Set(bool16 ac, bool16 accw, const AutoCorrectList& list) = 0;
};

#endif //__IAutoCorrectPrefs__