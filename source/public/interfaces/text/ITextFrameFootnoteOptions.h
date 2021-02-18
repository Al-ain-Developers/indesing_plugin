//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameFootnoteOptions.h $
//  
//  Owner: sibal
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
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef _ITextFrameFootnoteOptions_
#define _ITextFrameFootnoteOptions_

#include "IPMUnknown.h"
#include "PMReal.h"
#include "TextID.h"

class ITextFrameFootnoteOptions : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTFRAMEFOOTNOTEOPTIONS }; 

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
		virtual void SetEnableOverrides( bool16 enableOverrides) = 0;

		/**
		*/
		virtual void SetSpanFootnotesAcross( bool16 spanFootnotesAcross) = 0;
		
		/**
		*/

		virtual void SetMinimumSpacing( PMReal minimumSpacing) = 0;

		/**
		*/
		virtual void SetSpaceBetweenFootnotes(PMReal spaceBetweenFootnotes) = 0;

		/**
		*/
		virtual void CopyFrom(ITextFrameFootnoteOptions* sourceFootnoteOptions) = 0;
};

#endif	// _ITextFrameFootNoteOptions_