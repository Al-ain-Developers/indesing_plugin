//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextReferences.h $
//  
//  Owner: ekenning
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
#ifndef __ITextReferences__
#define __ITextReferences__

#include "IPMUnknown.h"
#include "TextID.h"

class PMString;

/** Used to track of usage of UIDs. Example is kTextStoryBoss.
	@ingroup text_story
*/
class ITextReferences : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTREFERENCES };

		/**	Number of IFontFamily uids used.
			Looks for any of these font family class ids -
				kTextAttrFontUIDBoss,
				kTARubyFontUIDBoss,
				kTAKentenFontFamilyBoss,
				kBNBulletFontUIDBoss

			@return int32	count of IFontFamily uids
		 */
		virtual int32 CountUsedFontFamilies() = 0;

		/**	Get nth font family uid
			@param n	get nth used font family. must be < CountUsedFontFamilies()
			@return UID	IFontFamily uid.
		 */
		virtual UID GetUsedFontFamily(int32 n) = 0;

		/**	Get number of used font styles for this font family uid
			@param family	font family uid to get number of styles for
			@return int32	number of used font styles for this font family uid
		 */
		virtual int32 CountUsedFontVariants(UID family) = 0;

		/**	Get nth used font style.
			@param family	font family uid
			@param n		nth style to get style name for
			@return			font style name
		 */
		virtual const PMString* GetUsedFontVariant(UID family, int32 n) = 0;

		/**	Count used missing fonts.
			@return int32	number of used missing fonts
		 */
		virtual int32 CountMissingFonts() = 0;

		/**	Get nth used missing font UID and style name
			@param n		nth used missing font. must be < CountMissingFonts()
			@param family	OUT font family UID
			@param setMe	OUT missing font style name
		 */
		virtual void GetMissingFont(int32 n, UID *family, PMString& setMe) = 0;
		

		/**	Number of used paragraph styles
			@return int32	count of used paragraph styles
		 */
		virtual int32 CountUsedParaStyles() = 0;

		/**	Get nth used paragraph style
			@param n		nth used paragraph style. must be < CountUsedParaStyles()
			@return UID		paragraph style UID
		 */
		virtual UID GetUsedParaStyle(int32 n) = 0;
		
		/**	Number of used character styles
			@return int32	count of used character styles
		 */
		virtual int32 CountUsedCharStyles() = 0;

		/**	Get nth used character style
			@param n		nth used character style. must be < CountUsedCharStyles()
			@return UID		character style UID
		 */
		virtual UID GetUsedCharStyle(int32 n) = 0;


		/**	Number of used colors
			@return int32	count of used colors
		 */
		virtual int32 CountUsedColors() = 0;

		/**	Get nth used color
			@param n		nth used color. must be < CountUsedColors()
			@return UID		color UID
		 */
		virtual UID GetUsedColor(int32 n) = 0;

		/**	Number of used conditions
			@return int32	count of used conditions
		 */
		virtual int32 CountUsedConditions() = 0;

		/**	Get nth used condition
			@param n		nth used color. must be < CountUsedConditions()
			@return UID		condition UID
		 */
		virtual UID GetUsedCondition(int32 n) = 0;

		/**	Invalidate the references. Next call to get reference will recalculate the references.
		 */
		virtual void Invalidate() = 0;
};


#endif
		// __TextReferences__
		