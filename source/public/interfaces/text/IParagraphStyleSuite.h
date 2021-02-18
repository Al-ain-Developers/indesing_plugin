//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IParagraphStyleSuite.h $
//  
//  Owner: Zak Williamson
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
//  Notes:
//  
//========================================================================================

#pragma once
#ifndef __IParagraphStyleSuite__
#define __IParagraphStyleSuite__

#include "ICharacterStyleSuite.h"

/** 
	IParagraphStyleSuite exists solely to provide unique IIDs for the ICharacterStyleSuite
	and IParagraphStyleSuite interfaces of a selection.  The methods of the two interfaces
	are identical.  See ICharacterStyleSuite for descriptions of the methods.
	
	@ingroup text_suite
	@ingroup text_style
*/
class IParagraphStyleSuite : public ICharacterStyleSuite
{
public:
	enum { kDefaultIID = IID_IPARAGRAPHSTYLESUITE };
};

#endif

