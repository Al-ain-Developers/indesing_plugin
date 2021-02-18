//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkSourceAltDestination.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __ILinkSourceAltDestination__
#define __ILinkSourceAltDestination__

#include "HyperlinkID.h"

/**
	This interface adds extra information to hyperlink. It is mainly used to provide extra information to
	page destination. Currently used by HTML export since there is no page concept in HTML.
*/
class ILinkSourceAltDestination : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKSOURCEALTDESTINATION };

	enum AltDestType
	{
		kNone = 0,

		kIndexMarker,
		kTOCTextAnchor,
	};

	/**	Get this destination type
	 */
	virtual AltDestType	GetDestType() const = 0;

	/**	Set destination type
	 */
	virtual void SetDestType(AltDestType type) = 0;

	// data for index marker
	/**	Get unique id of index marker. Id is unqiue within document.
		@return uint32 index marker id
	 */
	virtual uint32 GetIndexMarkerID() const = 0;	

	/**	SetGet unique id of index marker.
		@param id index marker id
	 */
	virtual void SetIndexMarkerID(uint32 id) = 0;	

	// data for toc text anchor
	/**	Get TOC text anchor name.
		@return PMString text anchor name
	 */
	virtual PMString GetTextAnchorName() const = 0;	

	/**	Set TOC text anchor name.
		@param name TOC text anchor name
	 */
	virtual void SetTextAnchorName(const PMString & name) = 0;

	/**	Get TOC page number string.
		@return PMString TOC page number string
	 */
	virtual WideString GetTOCPageNumberString() const = 0;	

	/**	Set TOC page number string.
		@param pageNumberStr TOC page number string
	 */
	virtual void SetTOCPageNumberString(const WideString & pageNumberStr) = 0;

	/**	Get TOC entry level.
		@return int32 TOC entry level.
	 */
	virtual int32 GetTOCEntryLevel() const = 0;	

	/**	Set TOC entry level.
		@param level TOC entry level
	 */
	virtual void SetTOCEntryLevel(int32 level) = 0;
};

#endif // __ILinkSourceAltDestination__
