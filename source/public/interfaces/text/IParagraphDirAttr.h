//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IParagraphDirAttr.h $
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

#ifndef __IPARAGRAPHDIRATTR__
#define __IPARAGRAPHDIRATTR__

#include "IPMUnknown.h"
#include "WorldReadyID.h"
#include "ICompositionStyle.h"


/**	IParagraphDirAttr is a simple data interface that is used to hold the
	paragraph's default writing direction used by the world ready composer.
	@ingroup text_attr
	@see IDrawingStyleME
*/
class IParagraphDirAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPARAGRAPHDIRATTR };

		typedef ICompositionStyle::ParagraphDirection		ValueType;

		/** Set the paragraph's writing direction.
		@param val is the writing direction.
		*/
		virtual void Set(ValueType val) = 0;

		/** Get the paragraph's writing direction.
		@return the writing direction.
		*/
		virtual ValueType Get() const = 0;
};

#endif


