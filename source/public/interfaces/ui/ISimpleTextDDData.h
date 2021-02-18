//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISimpleTextDDData.h $
//  
//  Owner: Dave Burnard
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
#ifndef __ISimpleTextDEData__
#define __ISimpleTextDEData__

#include "IPMUnknown.h"
#include "PMFlavorTypes.h"

//========================================================================================
// CLASS ISimpleTextDEData
//========================================================================================
/** Interface to store basic ASCII text (used by a variety of data exchange handlers)
*/
class ISimpleTextDEData : public IPMUnknown
{
	public:
		/** Clear the text data */
		virtual void 				Clear() = 0;
		/** Get the length in bytes of the text data */
		virtual uint32 			GetLength() const = 0;
		/** Is there any text data? */
		virtual bool16			IsEmpty() const = 0;
		
		/** copy text into the interface */
		virtual void 				Set(const uchar* text, uint32 length) = 0;
		/** retrieve text from the interface */
		virtual const uchar* 	GetText() const = 0;
};

#endif
