//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IJustifMethodAttr.h $
//  
//  Owner: prubini
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
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __IJUSTIFMETHODATTR__
#define __IJUSTIFMETHODATTR__

#include "IPMUnknown.h"
#include "IJustificationStyle.h"
#include "WorldReadyID.h"


/**	IJustifMethodAttr is a simple data interface that is used to hold the
	desired justification style used by the world ready composer:
	kJustifMethodDefault, kJustifMethodArabic, kJustifMethodNaskh
	@ingroup text_attr
	@see IJustificationStyle
*/
class IJustifMethodAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IJUSTIFMETHODATTR };

		typedef IJustificationStyle::JustificationMethod value_type;

		/** Set the justification method used by the world ready composer.
		@param val is the justification method.
		*/
		virtual void Set(value_type val) = 0;

		/** Get the justification method used by the world ready composer.
		@return the justification method.
		*/
		virtual	value_type Get() const = 0;
};

#endif


