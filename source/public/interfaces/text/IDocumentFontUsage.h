//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDocumentFontUsage.h $
//  
//  Owner: lance bushore
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
#ifndef __IDocumentFontUsage__
#define __IDocumentFontUsage__

#include "IPMUnknown.h"
#include "FontMgrID.h"
#include "FontUsageDialogID.h"

/** Interface off the document that contains all the font family UIDs and font faces
	used in a document.
	First call to UpdateFontList() on the same interface to make sure the fonts are up to date.
	Use this interface rather than IUsedFontList is to gain access to information about
	fonts in graphics.

	@ingroup text_font
*/
class IDocumentFontUsage : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDOCUMENTFONTUSAGE };
	
		/**
			Gets number of missing fonts
		
			@return	int32		number of missing fonts
		*/
		virtual int32 GetNumMissingFonts() const = 0;
		/**
			Get nth missing font family display name.
		
			@param	index		0 based index. must be less than value returned by GetNumMissingFonts
			@return	PMString&	font family display name
		*/
		virtual const PMString& GetNthMissingFontString(int32 index) const = 0;
		/**
			Get nth missing font face display name.
		
			@param	index		0 based index. must be less than value returned by GetNumMissingFonts
			@return	PMString&	font face display name
		*/
		virtual const PMString& GetNthMissingFontFaceString(int32 index) const = 0;
		/**
			Get nth missing font family UID. This is an IFontFamily UID
		
			@param	index		0 based index. must be less than value returned by GetNumMissingFonts
			@return	UID			font family UID
		*/
		virtual UID GetNthMissingFontUID(int32 index) const = 0; // returns UID of IFontFamily

		/**
			Gets number of used fonts. Does not include missing fonts.
		
			@return	int32		number of used fonts
		*/
		virtual int32 GetNumUsedFonts() const = 0;
		/**
			Get nth used font family display name.
		
			@param	index		0 based index. must be less than value returned by GetNumUsedFonts
			@return	PMString&	font family display name
		*/
		virtual const PMString& GetNthUsedFontString(int32 index) const = 0;
		/**
			Get nth used font face display name.
		
			@param	index		0 based index. must be less than value returned by GetNumUsedFonts
			@return	PMString&	font face display name
		*/
		virtual const PMString& GetNthUsedFontFaceString(int32 index) const = 0;
		/**
			Get nth used font family UID. This is an IFontFamily UID
		
			@param	index		0 based index. must be less than value returned by GetNumUsedFonts
			@return	UID			font family UID
		*/
		virtual UID GetNthUsedFontUID(int32 index) const = 0;
		/**
			Get nth font face index. This is the index used to call APIs like IFontFamily::AppendStyleName
		
			@param	index		0 based index. must be less than value returned by GetNumUsedFonts.
			@return	int32		index into IFontFamily to get font.
								WARNING: If the font face is a document-installed font, then this result will be
								less than 0 and will not work in IFontFamily::AppendStyleName and similar scenarios.
								You must instead use PMString queries such as IFontFamily::GetFaceNativeName.
		*/
		virtual int32 GetNthUsedFontFaceIndex(int32 index) const = 0;
				
		/**
			Gets number of fonts used in graphics.

			@return	int32		number of fonts used in graphics
		*/
		virtual int32 GetNumGraphicFonts() const = 0;
		/**
			Get nth graphic font face display name.
		
			@param	index		0 based index. must be less than value returned by GetNumGraphicFonts
			@return	PMString&	font face display name
		*/
		virtual const PMString& GetNthGraphicFontString(int32 index) const = 0;
		/**
			Get graphic page UID of nth graphic font.
		
			@param	index		0 based index. must be less than value returned by GetNumGraphicFonts
			@return	UID			graphic page item UID
		*/
		virtual UID GetNthGraphicFontPageItemUID(int32 index) const = 0;
		/**
			Get embedded state of nth graphic font.
		
			@param	index		0 based index. must be less than value returned by GetNumGraphicFonts
			@return	bool16		kTrue if font is embedded
		*/
		virtual bool16 GetNthGraphicFontEmbedded(int32 index) const = 0;
		/**
			Get missing state of nth graphic font.
		
			@param	index		0 based index. must be less than value returned by GetNumGraphicFonts
			@return	bool16		kTrue if font is missing
		*/
		virtual bool16 GetNthGraphicFontMissing(int32 index) const = 0;
				
		/**
			Update font list. Calling this will cause the font list to be recalculated by
			looking at all stories and graphics in the pub. Please use sparingly.
		*/
		virtual void UpdateFontList() = 0;
};


#endif
		// __IDocumentFontUsage__