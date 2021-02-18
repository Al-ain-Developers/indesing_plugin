//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxLineSubLog.h $
//  
//  Owner:
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __IWaxLineSubLog__
#define __IWaxLineSubLog__

#include "IPMUnknown.h"
#include "TextID.h"

class TEInputOutputMapping;

/** Interface for working with complex-script specific glyph data.
	This information is provided only for text composed with a
	complex-script composer. It provides additional layout information that
	is critical for the correct placement of marks & diacritics, especially
	in right-to-left writing scripts.

	@ingroup text_wax
*/
class IWaxLineSubLog : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWAXLINESUBLOG };

		/** GetLog().
		@return the character - glyph mapping.
		*/
		virtual TEInputOutputMapping&	GetLog() = 0;

		/** SetLogType().
		@param  Change Mapping Type.
		*/
		virtual void SetLogType( int mappingType) = 0;

		/** GetReversedOrder().
			If return true paragraph direction is right to left.
			If return false paragraph direction is left to right.
		@return line order is reversed.
		*/
		virtual bool16			GetReversedOrder() const = 0;

		/** SetReversedOrder().
			Set true if paragraph direction is right to left.
			Set false if paragraph direction is left to right.
		@param  b   order of line
		*/
		virtual void			SetReversedOrder(bool16 b) = 0;
};

#endif
	// __IWaxLineSubLog__

