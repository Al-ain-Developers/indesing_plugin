//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageRange.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __PAGERANGE__
#define __PAGERANGE__

#include "PDFID.h"

/** Utility class to hold a page range.
*/
class IPageRange : public IPMUnknown
{
public:
	/** Default enum
	*/
	enum { kDefaultIID = IID_IPAGERANGE };

	/** Type of page range being held
	*/
	typedef enum {
		/**	Ignore range string, use all pages of the document.
		*/
		kAllPages = 0,
		/**	Use range string.  The string must be specified with ordinal page numbers.
		*/
		kUseRange,
		/**	By section option has been deprecated - do not use!
		*/
		kBySection,
		/**	Ignore range string, use spread with selected items in the document.
		*/
		kBySelection,
		/** Placeholder
		*/
		kLastType = kBySelection
	} RangeFormat;

	/** Set the page range format
		@param IN RangeFormat the page range format being held
	*/
	virtual void SetPageRangeFormat(RangeFormat format) = 0;
	/** Set the page range string
		@param IN PMString containing the page range
	*/
	virtual void SetPageRange(PMString range) = 0;

	/** Get the page range format being held
		@return RangeFormat the page range format being held
	*/
	virtual RangeFormat GetPageRangeFormat() = 0;
	/** Get the page range string
		@return PMString containing the page range string
	*/
	virtual PMString GetPageRange() = 0;

	/** Copies one set of prefs into another
	 @param other			IN The preferences to copy
	 */
	virtual void Copy(IPageRange *other) = 0;
};

#endif // __PAGERANGE__
