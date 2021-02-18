//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameFootnoteOptionsData.h $
//  
//  Owner: Pooja Mangla
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IPMUnknown.h"
#include "PMRect.h"
#include "TextID.h"
#include "UIDList.h"

#pragma once
#ifndef __ITextFrameFootnoteOptionsData__
#define __ITextFrameFootnoteOptionsData__

/**
	Interface to manage columns within a text frame.

	@note Only applies to a multi-column frame boss. That boss also supports the IMultiColumnTextFrame interface. This object (the multi-column frame)
	is a container for columns. Each column also supports the ITextFrameColumn interface. The columns also appear in the associated frame
	list (IFrameList). See the Programming Guide for more information on the text frame hierarchy.

	@ingroup text_layout
*/
class ITextFrameFootnoteOptionsData : public IPMUnknown		// ##rk: replace as default Impl for ITextColumnManager (ITextColumnProvider)?
{
public:
		enum { kDefaultIID = IID_ITEXTFRAMEFOOTNOTEOPTIONSDATA };

		/**
		*/
		virtual bool16 GetEnableOverrides() const = 0;

		/**
		*/
		virtual bool16 GetSpanFootnotesAcross() const = 0;

		/**
		*/
		virtual PMReal GetMinimumSpacing() const = 0;

		/**
		*/
		virtual PMReal GetSpaceBetweenFootnotes() const = 0;

		/**
		*/
		virtual void SetEnableOverrides(bool16 enableOverrides) = 0;

		/**
		*/
		virtual void SetSpanFootnotesAcross(bool16 spanFootnotesAcross) = 0;

		/**
		*/

		virtual void SetMinimumSpacing(PMReal minimumSpacing) = 0;

		/**
		*/
		virtual void SetSpaceBetweenFootnotes(PMReal spaceBetweenFootnotes) = 0;

		/**
		*/
		virtual void CopyFrom(ITextFrameFootnoteOptionsData* sourceFootnoteOptions) = 0;
};

#endif // __ITextFrameFootnoteOptionsData__
