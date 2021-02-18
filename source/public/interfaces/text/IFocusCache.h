//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFocusCache.h $
//  
//  Owner: eric_menninga
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
//  This is an interface that assumes that it has access to an ITextFocus
//  interface. It's purpose is to cache every value for every text attribute
//  and style that is in the range described by the ITextFocus.
//  The cache, once built, is time stamped so that the system can tell
//  if the cache has changed.
//  
//========================================================================================

#pragma once
#ifndef __IFocusCache__
#define __IFocusCache__


#include "IPMUnknown.h"
#include "IPMFont.h"
#include "TextID.h"
#include "TextAttrID.h"

class PMString;
class AttributeBossList;
class ITextModel;
class IAttrReport;

//--------------------------------------------------

/** Provides necessary & sufficient data to specify a font
	@ingroup text_font
*/
struct PMFontData
{
	typedef object_type data_type;
	PMFontData() : fNumAxes(0), fIncorrectFace(0), fFamilyUID(kInvalidUID), fAxes(nil)
    {}
    ~PMFontData(){
        if(fAxes)
            delete [] fAxes;
        fAxes = nil;
    }

	/** fName when font is available or missing is the postcript name.
		That is sufficient to distinguish cases where font family is
		the same but font style is different. And that is why
		we do not look at fFaceName in this comparison. */
	int operator==(const PMFontData& other) const
		{	if (fName != other.fName || fNumAxes != other.fNumAxes)
				return kFalse;
			else
		   		return (std::memcmp(fAxes, other.fAxes, fNumAxes * sizeof(Fixed)) == 0);
		}

	PMString	fName;
	PMString	fFaceName;
	UID 		fFamilyUID;
	Fixed		*fAxes;
	int16		fNumAxes;
	bool16		fIncorrectFace;
};


/** A text range that is active (selected) with an ITextFocus on it has the FocusCache
	interface that can report back the attributes within the range. Efficient for all
	attributes, but not the best for just checking one.
	@see IComposeScanner
	@ingroup text_focus
*/
class IFocusCache : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFOCUSCACHE };

		//-------------------------------------------------------------------------------------
			/** How many different paragraph styles are selected?
				@return the number of different styles. */
		virtual int32 CountParagraphStyles() const = 0;
			/** How many different character styles are selected?
				@return the number of different styles. */
		virtual int32 CountCharacterStyles() const = 0;
			/** How many different character styles that came from run-in style attributes are selected?
				@return the number of different styles. */
		virtual int32 CountCharacterStylesFromRunIns() const = 0;

			/** Get the Nth different paragraph style in the selection. Not necessarily in any order.
				@param n specifies which paragraph style.
				@return the style UID. */
		virtual UID GetNthParagraphStyle(int32 n) const = 0;
			/** Get the Nth different character style in the selection. Not necessarily in any order.
				@param n specifies which character style.
				@return the style UID. */
		virtual UID GetNthCharacterStyle(int32 n) const = 0;
			/** Get the Nth different character style in the selection that came from run-in styles. Not necessarily in any order.
				@param n specifies which character style from the run-in style paragraph attributes.
				@return the style UID. */
		virtual UID GetNthCharacterStyleFromRunIn(int32 n) const = 0;

			/** Does the specified style have "overrides" applied? The definition of overrides
				is different for character & paragraph styles, but this routine handles both.
				@param style is the style in question.
				@return kTrue if the style has overrides. */
		virtual bool16 IsStyleOverridden(UID style) const = 0;

		//-------------------------------------------------------------------------------------
			/** How many different attribute runs were in the selection?
				@return the number of attribute runs. */
		virtual int32 CountSelectedRuns() const = 0;

			/** How many different values for a particular attribute exist? More than one indicate a mixed selection.
				@param attr specifies which text attribute.
				@return the number of different values for the attribute. */
		virtual int32 CountAttributes(const ClassID& attr) const = 0;

			/** Return a specific text attribute applied to the selection. Doesn't tunnel into styles.
				@param which specifies which of all values for the same attribute should be returned.
				@param attr specifies which text attribute.
				@param interfaceID specifies which interface to return.
				@return an addref'd attribute. */
		virtual const IPMUnknown* QueryAttributeN(int32 which, const ClassID& attr, const PMIID& interfaceID) const = 0;

		//-------------------------------------------------------------------------------------
			/**	Return the number of different fonts in the selection. These will not
				necessarily be in any particular order.
				@param fontUIDBoss which boss (default is kTextAttrFontUIDBoss).
				@return how many fonts are applied to the range? */
		virtual int32 CountFonts(ClassID fontUIDBoss = kTextAttrFontUIDBoss) const = 0;

			/** Get InDesign font data for the nth font in the selection.
				@param nthFont specifies which font.
				@param faceName is set to the Nth selected font's face name
				@param fontUIDBoss which boss (default is kTextAttrFontUIDBoss).
				@return the font family UID for the Nth selected font. */
		virtual UID GetNthFamilyUIDAndFace(int32 nthFont, PMString *faceName, ClassID fontUIDBoss = kTextAttrFontUIDBoss) const = 0;

			/** Get postscript font name information about the nth font in the selection.
				@param nthFont which font in the selection is being asked about?
				@param incorrectFace was the applied face correct for this postscript font name? If the face
									is incorrect (e.g. family = Times, face = "Ornaments") the postscript name
									will be what was used (e.g. Times-Roman).
				@param fontUIDBoss which boss (default is kTextAttrFontUIDBoss).
				@return the postscript name of the Nth font. */
		virtual const PMString& GetNthFont(int32 nthFont, bool16 *incorrectFace = nil, ClassID fontUIDBoss = kTextAttrFontUIDBoss) const = 0;

			/** Return the multiple-master data for the font.
				@param nthFont which font?
				@param numaxes returns how many axes?
				@return the multi-master axis array for the Nth font */
		virtual const Fixed* GetNthMMAxes(int32 nthFont, int32 *numaxes) const = 0;

			/** Get the list of overrides descriptions applied to the selection.
				@param overrideList: the list of overrides in the selection.
				@param getForParaStyle kTrue get for the paragraph style, kFalse, get for the character style.
				@return kTrue if the overrides are mixed. */
		virtual bool16 GetOverrideList(K2Vector<PMString>& overrideStrings, bool16 getForParaStyle) const = 0;


		//-------------------------------------------------------------------------------------
			/** invalidate the cache (called by setting attributes for instance) shouldn't be necessary to call */
		virtual void InvalidateCache() = 0;
			/** invalidate the cache (called by setting attributes for instance) used by selection sub-system
				shouldn't be necessary to call from public api */
		virtual void ResetCache_NoNotify() = 0;
			/** text was inserted in the model; may invalidate the cache; shouldn't be necessary to call.
				@param where is the location of the insert.
				@param howmuch is the number of characters inserted. */
		virtual void Inserted(TextIndex where, int32 howmuch) = 0;
			/** text was deleted fromt the model; may invalidate the cache; shouldn't be necessary to call.
				@param where is the position.
				@param howmuch specifies how many characters were deleted. */
		virtual void Deleted(TextIndex where, int32 howmuch) = 0;
			/** called automatically when the focus was adjusted,
				maybe cache needs to be invalidated, maybe not.
				@param model is the story.
				@param start is the new beginning of the selection.
				@param end is the end of the new selection.
				@param excludeCacheEnd specifies whether the very end of the selection should cause a recalculation of attributes. */
		virtual void FocusWasMoved(const ITextModel * model, TextIndex start, TextIndex end, bool16 excludeCacheEnd = kTrue) = 0;

			/** lets you check if the cache needs building (which is expensive) */
		virtual bool16 CacheAlreadyBuilt() const = 0;
			/** @return the time stamp when the cache was built, may build the cache if not already built. */
		virtual uint32 GetTimeStamp() const = 0;

			/** copies the attributes into attribute boss lists.
				@param attrList attributes that are NOT-MIXED are added to this list
				@param mixedList if non-nil, the first value of mixed attributes are added to this list. */
		virtual void CopyToAttributeLists(AttributeBossList *attrList, AttributeBossList *mixedList = nil) const = 0;

			/** checks Ruby Strand for presence of ruby, caches value.
				@return kTrue if ruby is applied. */
		virtual bool16 IsRubyApplied() const = 0;
};

#endif
	// __IFocusCache__

