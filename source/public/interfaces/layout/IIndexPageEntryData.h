//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexPageEntryData.h $
//  
//  Owner: Michel Hutinel
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
//  Comments: This interface saves the informations about an Index Page Entry.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXPAGEENTRYDATA__
#define __IINDEXPAGEENTRYDATA__

#include "IPMUnknown.h"
#include "IndexingID.h"

class WideString;

/** Data interface that aggregates information about an index page entry.
	@ingroup layout_index
*/
class IIndexPageEntryData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXPAGEENTRYDATA };
		
		/** The type of the page range for the entry */
		enum PageRangeType {	kNoPageRange = 0,			// SuppressPageNumber
								kCurrentPage = 1,
								kToNextStyleChange = 2,
								kToNextUseOfStyle = 3,		// nextStyleUID must be filled
								kToEndOfStory = 4,
								kToEndOfDocument = 5,
								kToEndOfSection = 6,
								kForNextNParagraphs = 7,	// nParOrPage must be filled
								kForNextNPages = 8 };

		/** Specifies the location of the index marker */
		enum MarkerPlace	 {	kPage = 1,
								kPasteboard = 2,
								kMasterPage = 4,
								kOverset = 8,
								kHiddenLayer = 16,
								kUnplacedFrame = 32,
								kFootnote = 64,
								kNote = 128,
								kHiddenText = 256,
								kHiddenState = 512,
								kDummyValue = 0xFFFFFFFF};
							
							
		// Get/Set methods

		/**	Retrieves the type of the page range for the entry.
			@param type [OUT] - the page range for this entry.
			@param nextStyleUID [OUT] - the UID of the next style if type is kToNextUseOfStyle.
			@param nParOrPage [OUT] - the number of paragraphs or pages if the type
			is kForNextNParagraphs or kForNextNPages
		 */
		virtual void	GetPageRangeType(PageRangeType& type, UID& nextStyleUID, int32& nParOrPage) const = 0;		

		/**	Sets the page range type for this entry.
			This method is used in conjuction with SetPageRange.
			@param type [IN] - the page range for this entry.
			@param nextStyleUID [IN] - the UID of the next style if type is kToNextUseOfStyle.
			@param nParOrPage [IN] - the number of paragraphs or pages if the type
			is kForNextNParagraphs or kForNextNPages
		 */
		virtual void	SetPageRangeType(const PageRangeType type, const UID nextStyleUID, const int32 nParOrPage) = 0;

		/**	Retrieves the style for the page entry.
			@return UID of the style.
		 */
		virtual UID		GetStyleUID() const = 0;

		/**	Sets the style for the page entry.
			@param styleUID [IN] - the UID of the style for the page entry.
		 */
		virtual void	SetStyleUID(const UID styleUID) = 0;

		/**	Retrieves the page range for this entry.
			@param startPage [OUT] - the start page.
			@param endPage [OUT] - the end page.
		 */
		virtual void	GetPageRange(int32& startPage, int32& endPage) const = 0;

		/**	Sets the page range for this entry.
			This method is used in conjuction with SetPageRangeType.
			@param startPage [IN] - the start page.
			@param endPage [IN] - the end page.
		 */
		virtual void	SetPageRange(const int32 startPage, const int32 endPage) = 0;

		/**	Retrieves the place of the index marker.
			Used when updating the page entries in the index.
			@param place [OUT] - location of the index marker.
		 */
		virtual void	GetMarkerPlace(MarkerPlace& place) const = 0;

		/**	Sets the location of the index marker.
			@param place [IN] - location of the index marker.
		 */
		virtual void	SetMarkerPlace(const MarkerPlace place) = 0;

		/**	Gets ID of index marker. This number should be unique within document. It is used to 
			create hyperlink when export index to HTML and EPUB
		 */
		virtual uint32 GetMarkerUniqueID() const = 0;
};

#endif // __IINDEXPAGEENTRYDATA__