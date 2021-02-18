//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IVerticalRelatedStyle.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IVerticalRelatedStyle__
#define __IVerticalRelatedStyle__


#include "IPMUnknown.h"
#include "CJKID.h"

 
/**
	IVerticalRelatedStyle is one of the interfaces hanging off the kComposeStyleBoss object.
	As such, it is easily Queried from an IDrawingStyle interface.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text. IVerticalRelatedStyle lists character attributes
	associated with the Japanese vertical text feature.
	IVerticalRelatedStyle should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves are the primary setters of the data.
	@see IDrawingStyle
	@see IMojikumiStyle
	@ingroup text_comp_style
*/
class IVerticalRelatedStyle : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_IVERTICALRELATEDSTYLE };

		// Roman
		/**  Turns on the Rotate Roman characters to be upright in vertical feature
		@param flag [IN] kTrue means the feature is on
		*/
		virtual void SetRotateRoman(bool16 flag) = 0;
		/**  Accesses whether or not the Rotate Roman character to be upright in vertical text feature is on
		@return kTrue if feature is on
		*/
		virtual bool16 GetRotateRoman() const = 0;

		// Kumi number
		/**  Turns on the automatic Tate-chuu-yoko feature for single-byte numbers in vertical text
		@param int16 [IN] number of digits to include in auto-TCY
		*/
		virtual void SetNumOfKumiNumber(int16 num) = 0;
		/**  Accesses the number of digits of single-byte numbers will be turned into auto-TCY
		@return number of digits
		*/
		virtual int16 GetNumOfKumiNumber() const = 0;	
			
		// Kumi number with roman
		/**  Turns on the "include single-byte Roman characters in automatic Tate-chuu-yoko" feature
		@param bool16 [IN] kTrue if single-byte Roman characters should be included in auto-TCY
		*/
		virtual void SetKumiNumberWithRoman(bool16 flag) = 0;
		/**  Accesses whether or not single-byte Roman characters should be included in automatic Tate-chuu-yoko
		@return kTrue if single-byte Roman characters should be included in automatic Tate-chuu-yoko
		*/
		virtual bool16 GetKumiNumberWithRoman() const = 0;	

		// Tatechuyoko 
		/**  Turns on the Tate-chuu-yoko (horizontal-in-vertical) text feature
		@param flag [IN] kTrue if feature is on
		*/
		virtual void SetTatechuyokoFlag(bool16 flag) = 0;
		/**  Accesses whether or not the Tate-chuu-yoko (horizontal-in-vertical) text feature is on
		@return kTrue if feature is on
		*/
		virtual bool16 GetTatechuyokoFlag() const = 0;
			
		/**  Sets x-offset adjustment of TCY run
		@param r [IN] x-offset in points
		*/
		virtual void SetTatechuyokoXOffset(PMReal r) = 0;
		/**  Accesses x-offset adjustment of TCY run
		@return x-offset in points
		*/
		virtual PMReal GetTatechuyokoXOffset() const = 0;

		/**  Sets y-offset adjustment of TCY run
		@param r [IN] y-offset in points
		*/
		virtual void SetTatechuyokoYOffset(PMReal r) = 0;
		/**  Accesses y-offset adjustment of TCY run
		@return y-offset in points
		*/
		virtual PMReal GetTatechuyokoYOffset() const = 0;
};


#endif
		// __IVerticalRelatedStyle__