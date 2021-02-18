//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexPageEntryCmdData.h $
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
//  Purpose: Interface data for creating, editing an Index Page Entry
//  
//========================================================================================

#pragma once
#ifndef __IIndexPageEntryCmdData__
#define __IIndexPageEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h"
#include "IIndexPageEntryData.h"

class IndexTopicEntry;

/** Command data interface for creating and editing an index page entry.
	@see IIndexPageEntryData.
	@ingroup layout_index
*/
class IIndexPageEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXPAGEENTRYCMDDATA };

		/**	Retrieves the type of the page range for the entry.
			@param type [OUT] - the page range for this entry.
			@param nextStyleUID [OUT] - the UID of the next style if type is kToNextUseOfStyle.
			@param nParOrPage [OUT] - the number of paragraphs or pages if the type
			is kForNextNParagraphs or kForNextNPages
		 */
		virtual void		GetPageRangeType(IIndexPageEntryData::PageRangeType& type, UID& nextStyleUID, int32& nParOrPage) const = 0;		

		/**	Sets the page range type for this entry.
			This method is used in conjuction with SetPageRange.
			@param type [IN] - the page range for this entry.
			@param nextStyleUID [IN] - the UID of the next style if type is kToNextUseOfStyle.
			@param nParOrPage [IN] - the number of paragraphs or pages if the type
			is kForNextNParagraphs or kForNextNPages
		 */
		virtual void		SetPageRangeType(const IIndexPageEntryData::PageRangeType type, const UID nextStyleUID, const int32 nParOrPage) = 0;

		/**	Retrieves the style for the page entry.
			@return UID of the style.
		 */
		virtual UID			GetStyleUID() const = 0;

		/**	Sets the style for the page entry.
			@param styleUID [IN] - the UID of the style for the page entry.
		 */
		virtual void		SetStyleUID(const UID styleUID) = 0;

		/**	Retrieves the page range for this entry.
			@param startPage [OUT] - the index (0-based) of start page.
			@param endPage [OUT] - the index (0-based) of end page.
		 */
		virtual void		GetPageRange(int32& startPage, int32& endPage) const = 0;

		/**	Sets the page range for this entry.
			This method is used in conjuction with SetPageRangeType.
			@param startPage [IN] - the start page.
			@param endPage [IN] - the end page.
		 */
		virtual void		SetPageRange(const int32 startPage, const int32 endPage) = 0;

		/**	Retrieves the place of the index marker.
			Used when updating the page entries in the index.
			@see IIndexPageEntryData for the definition of marker place.
			@param place [OUT] - location of the index marker.
		 */
		virtual void		GetMarkerPlace(IIndexPageEntryData::MarkerPlace& place) const = 0;

		/**	Sets the location of the index marker.
			@see IIndexPageEntryData for the definition of marker place.
			@param place [IN] - location of the index marker.
		 */
		virtual void		SetMarkerPlace(const IIndexPageEntryData::MarkerPlace place) = 0;
};

#endif	// __IIndexPageEntryCmdData__