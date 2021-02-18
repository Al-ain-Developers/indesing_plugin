//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IUsedFontList.h $
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
#ifndef __IUsedFontList__
#define __IUsedFontList__

#include "IPMUnknown.h"
#include "PMString.h"
#include "FontMgrID.h"

// Note: DocFontList.cpp implementation uses this interface

/** List of fonts used in the document.
	@ingroup text_font
*/
class IUsedFontList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IUSEDFONTLIST };
	
		/**	Counts number of IFontFamily UIDs used in the document
			@return int32 number of font families used in document
		 */
		virtual int32 CountUsedFontFamilies() = 0;

		/**	Gets the nth IFontFamily UID in list. Use this with	CountUsedFontFamilies to
			iterate through all used IFontFamilies
			@param n	Index into Used font list. Starts at 0.
			@return UID		IFontFamily UID
		 */
		virtual UID GetUsedFontFamily(int32 n) = 0;

		/**	Counts the number of font styles for a given IFontFamily that are used in the
			document
			@param family UID of IFontFamily
			@return int32	number of style variants found
		 */
		virtual int32 CountUsedFontVariants(UID family) = 0;

		/**	Gets the nth font style for a given IFontFamily that is used in the document.
			Use this with CountUsedFontVariants to iterate through all used font styles
			in an IFontFamily.
			@param family	UID of IFontFamily
			@param n	Index into IFontFamily font style list
			@return PMString Non native style name of nth font style
		 */
		virtual const PMString* GetUsedFontVariant(UID family, int32 n) = 0;


		/**	Count the number of missing fonts.
			@param recalculate	If kTrue we recalculate missing fonts 
			@return int32	number of missing fonts
		 */
		virtual int32 CountMissingFonts(bool16 recalculate = kTrue) = 0;

		/**	Get nth missing font. Use this with CountMissingFonts to iterate through
			all missing fonts in the document.

			@param n	Index into missing font list
			@param *family OUT nth missing IFontFamily UID of this missing font
			@param setMe OUT font style of this missing font
			@param *oldTech OUT IPMFont::FontType of missing font
			@param *newTech OUT IPMFont::FontType of missing font. This will be different
				than oldTech if the document was open when a different FontType of this font
				was available.
			@param recalculate	recalculate missing fonts. 
		 */
		virtual void GetMissingFont(int32 n, UID *family, PMString& setMe,
			int32 *oldTech = nil, int32 *newTech = nil, bool16 recalculate = kTrue) = 0;
		
		/**	Recalculates the list. Calling this will cause the missing font list to be
			recalculated by	looking at all stories in the pub. Please use sparingly.
		 */
		virtual void ForceRecalculateAll() = 0;

		/**	Updates document's IFontFamily UIDs and font style names after fixing
			dysfunctional fonts. This is used when we open old documents that have
			an old font style names that refers to a postscript name that now is reffered
			to by a different style name.
			@param familyUID	old dysfunctional IFontFamily UID
			@param familyReplacement	new IFontFamily UID to use
		 */
		virtual void Add_NeedToProcessReferencesto_UsedToBe_DysfunctionalFont(UID familyUID,
			UID familyReplacement) = 0;		

		/**	Attempt to auto activate missing fonts.
		 */
		virtual void AttemptAutoActivation() = 0;
};


#endif
		// __IUsedFontList__