//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IEndnoteFacade.h $
//  
//  Owner: Abhishek Raj
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
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IEndnoteFacade__
#define __IEndnoteFacade__

#include "IPMUnknown.h"

#include "IEndnoteSettings.h"

namespace Facade
{
    /** A high level API for dealing with Endnotes.  To use this Facade, include
        this header file and the use the following example syntax:
        Utils<IEndnoteFacade>()->SetTitle( ... );

		@note See IEndnoteSettings for descriptions of these methods as this is a mirror interface to that.
	*/
    class IEndnoteFacade : public IPMUnknown
    {
    public:
        enum { kDefaultIID = IID_IENDNOTEFACADE };

		/** See IEndnoteSettings
		*/
		virtual WideString GetTitle(IEndnoteSettings* target) const = 0;
		virtual void SetTitle(IEndnoteSettings* target, WideString title) = 0;

		/** See IEndnoteSettings
		*/
		virtual UID GetHeaderParaStyle(IEndnoteSettings* target) const = 0;
		virtual void SetHeaderParaStyle(IEndnoteSettings* target, UID styleID) = 0;
		
		/** See IEndnoteSettings
		*/
		virtual IEndnoteSettings::RestartNumberingOptions GetRestartOption(IEndnoteSettings* target) const = 0;
		virtual void SetRestartOption(IEndnoteSettings* target, IEndnoteSettings::RestartNumberingOptions option) = 0;

		/** See IEndnoteSettings
		*/
		virtual int32 GetStartingNumber(IEndnoteSettings* target) const = 0;
		virtual void SetStartingNumber(IEndnoteSettings* target, int32 n) = 0;

		/** See IEndnoteSettings
		*/
		virtual ClassID GetNumberingMethod(IEndnoteSettings* target) const = 0;
		virtual void SetNumberingMethod(IEndnoteSettings* target, ClassID whichMethod) = 0;

		/** See IEndnoteSettings
		*/
		virtual IEndnoteSettings::MarkerPositionOptions GetMarkerPositioning(IEndnoteSettings* target) const = 0;
		virtual void SetMarkerPositioning(IEndnoteSettings* target, IEndnoteSettings::MarkerPositionOptions option) = 0;

		/** See IEndnoteSettings
		*/
		virtual UID GetMarkerStyle(IEndnoteSettings* target) const = 0;
		virtual void SetMarkerStyle(IEndnoteSettings* target, UID styleID) = 0;

		/** See IEndnoteSettings
		*/
		virtual UID GetEndnoteParagraphStyle(IEndnoteSettings* target) const = 0;
		virtual void SetEndnoteParagraphStyle(IEndnoteSettings* target, UID s) = 0;

		/** See IEndnoteSettings
		*/
		virtual const WideString& GetEndnoteSeparator(IEndnoteSettings* target) const = 0;
		virtual void  SetEndnoteSeparator(IEndnoteSettings* target, const WideString& sep) = 0;

		/** See IEndnoteSettings
		*/
		virtual IEndnoteSettings::Scope GetScope(IEndnoteSettings* target) const = 0;
		virtual void SetScope(IEndnoteSettings* target, IEndnoteSettings::Scope scope) = 0;

		/** See IEndnoteSettings
		*/
		virtual IEndnoteSettings::Place GetPlace(IEndnoteSettings* target) const = 0;
		virtual void SetPlace(IEndnoteSettings* target, IEndnoteSettings::Place place) = 0;

		/** See IEndnoteSettings
		*/
		virtual const WideString& GetMarkerPrefix(IEndnoteSettings* target) const = 0;
		virtual void SetMarkerPrefix(IEndnoteSettings* target, const WideString& pre) = 0;

		/** See IEndnoteSettings
		*/
		virtual const WideString& GetMarkerSuffix(IEndnoteSettings* target) const = 0;
		virtual void SetMarkerSuffix(IEndnoteSettings* target, const WideString& suf) = 0;

		/** See IEndnoteSettings
		*/
		virtual IEndnoteSettings::SuffixPrefixUsageOptions GetPrefixSuffixUsage(IEndnoteSettings* target) const = 0;
		virtual void SetPrefixSuffixUsage(IEndnoteSettings* target, IEndnoteSettings::SuffixPrefixUsageOptions options) = 0;

		/** See IEndnoteSettings
		*/
		virtual void SetAllSettings(IEndnoteSettings* target, const IEndnoteSettings::EndnotePrefs* settings) = 0;

		/* Returns endnote settings of a document */
		virtual IEndnoteSettings* QueryEndnoteSettings(IDataBase* db) const = 0;

		/* Returns if the passed story is an endnote story */
		virtual bool16 IsEndnoteStory(const UIDRef textModelRef) const = 0;

		/** Returns if the passed text range is an endnote text range 
			
			@param startPosition: start index of the text range
			@param endPosition: end index of the text range
			@param textModel: textModel of the text range

			@return true if the text range is endnote text range, false otherwise
		*/
		virtual bool16 IsEndnoteTextRange(const TextIndex& startPosition, const TextIndex& endPosition, const ITextModel* textModel) const = 0;

		/** Returns if the character at the given text index position is an endnote reference

		@param position: text index of the character
		@param textModel: textModel of the containing character

		@return true if the character is an endnote reference, false otherwise
		*/
		virtual bool16 IsEndnoteAnchor(TextIndex& position, const ITextModel* textModel) const = 0;

		/** Returns true if the character at the given text index is endnote text range start/end marker 
			@param position: text index of the character
			@param textModel: textModel of the containing character

			@return true if the character is endnote range marker, else returns false
		*/
		virtual bool16 IsEndnoteTextRangeMarker(const TextIndex& position, ITextModel* textModel) const = 0;

		/** Given a story containing an endnote reference/range, returns the related stories containing endnote references/ranges.
			@param modelRef: [IN}UIDRef of the story containing endnote reference/range
			@param storiesList: [OUT] list of related stories containing endnote references/ranges.
		*/
		virtual void AppendEndnoteRelatedStories(const UIDRef& modelRef, UIDList& storiesList) const = 0;
		
		/** Returns true if the given story is a story containing endnote references/ranges and is in the assignment
			@param storyRef: [IN} UIDRef of the given story
			
			@return true if the given story is a story containing endnote references/ranges and is in the assignment, else return false
		*/
		virtual bool16 IsEndnoteAnchorOrEndnoteStoryInAssignment(const UIDRef& storyRef) const = 0;

		/** Returns true if the given story is a story containing endnote references/ranges
		@param storyRef: [IN} UIDRef of the given story

		@return true if the given story is a story containing endnote references/ranges
		*/
		virtual bool16 IsEndnoteAnchorOrEndnoteStory(const UIDRef& storyRef) const = 0;

		/** Returns UIDList of all the stories containing endnote references corresponding to story
		containing endnote ranges

		@param endnoteStoryRef: [IN} UIDRef of the story containing endnote ranges

		@return UIDList of all the stories containing endnote references
		*/
		virtual UIDList GetEndnoteAnchorStories(UIDRef endnoteStoryRef) const = 0;

		/** Returns count of all the endnotes corresponding to story containing endnote ranges

		@param endnoteStoryRef: [IN} UIDRef of the story containing endnote ranges

		@return count of all the endnotes
		*/
		virtual int32 GetEndnoteCount(UIDRef endnoteStoryRef) const = 0;

		/** Returns UIDRef of the endnote story corresponding to story containing endnote references

		@param textModel: [IN}  story containing endnote references

		@return UIDRef of the endnote story corresponding to story containing endnote references
		*/
		virtual UIDRef GetEndnoteStoryRef(const ITextModel* textModel) const = 0;

		/** Returns true if the character at the given text index is a separator

		@param textModel: [IN}  story containing the character

		@return true if the character is a separator, else returns false
		*/
		virtual bool16 IsSeparatorChar(const UIDRef textModelRef, const TextIndex index) const = 0;

		/** ADOBE INTERNAL USE ONLY */
		virtual void MoveEndnoteRange(const UIDRef& storyRef) = 0;

		/** ADOBE INTERNAL USE ONLY*/
		virtual void DeleteEndnoteRangesInStory(ITextModel* model, TextIndex start, TextIndex end) const = 0;

		/** ADOBE INTERNAL USE ONLY */
		virtual void CopyEndnoteDataFromSourceStoryToDestStory(UIDRef sourceEndnoteStoryRef, UIDRef destEndnoteStoryRef) = 0;
};
}  // namespace Facade

#endif	// __IEndnoteFacade__
