//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTMLEPubExportTypes.h $
//  
//  Owner: SusanCL
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
//  A Generic class that describes a line point or a Bezier knot
//  
//========================================================================================

#pragma once
#ifndef __HTMLEPubExportTypes__
#define __HTMLEPubExportTypes__

#include "AttributeBossList.h"

namespace HTMLExport {

// export preference type
enum ExportScope {
	kSelection = 0,
	kDocument
};

enum ExportOrder {
	kXMLStructure = 0,
	kLayout,
	kArticlePanel
};

enum BulletOption {
	kMapToBulletList = 0,
	kConvertBulletToText
};

enum NumberingOption {
	kMapToNumberedList = 0,
	kConvertNumberedListToText
};

enum ImageOption // not used by epub. Internally default to kOptimized
{
	kOriginal = 0, 
	kOptimized,
	kLinkToServer
};

/** SVGExportType */
typedef enum
{
	kExportAsEmbedCode = 0,
	kExportAsObjectTags
} SVGExportType;

enum ImageSize
{
	kFixed = 0, 
	kRelative
};

enum ImageAlignment
{
	kImageAlignLeft = 0,
	kImageAlignCenter,
	kImageAlignRight,
};

enum PageBreak
{
	kPageBreakBefore = 0,
	kPageBreakAfter,
	kPageBreakBeforeAndAfter
};

enum CSSUnitType
{
	kEm = 0,
	kPixel
};

enum EBookCover {
	kNoCoverImage = 0,
	kUseFirstPage,
	kExternalImageFile,
	kUseChosenPage
};

enum EBookFormat
{
	kEPub2 = 0,
	kEPub3Reflowable = 1,
	kEPub3FixedLayout = 2
};

enum XHTMLFormat
{
	kXHTMLReflowable = 0,
	kXHTMLFixedLayout = 1,	
	kLastMileLayout = 2,	
};

enum FootnotePlacement {
	kFootnoteAfterStory = 0,
	kFootnoteAfterParagraph,
	kFootnoteInsidePopup
};

/** enum to describe the type of page export to be done
	*/

enum PageRangeFormat
{
	kAllPages,
	kUseRange
};

/** enum to describe the spread control options.
	*/
enum SpreadControlOption
{
	kSpreadsBasedOnDocument,
	kSpreadsPhysical,
	kSpreadsSynthetic,
	kSpreadsNone
};

/** enum to describe the spread control options.
	*/
enum HTMLExportSpreadControl
{
	kSpreadBased,
	kPageBased
};

/** enum to describe the type of navigation style to be provided
	*/

enum NavigationStyle
{
	kNoNavigation,
	kFileNameNavigation,
	kTOCStyleNavigation,
	kBookMarkNavigation
};

// export data type

class IDStyle {
public:
	typedef object_type data_type;

	enum IDStyleType {
		kCharacterStyle = 0,
		kParagraphStyle,
		kTableStyle,
		kCellStyle,
		kObjectStyle,

		kUnknownStyle
	};

	enum IDStyleAttribute {
		kRubyAttr		= 0x0001,	// ruby attribute in style is used
		//kUnknownAttr	= 0x0002,	// 
		//kUnknownAttr	= 0x0004,	// 
		//kUnknownAttr	= 0x0008,	// 
		//kUnknownAttr	= 0x0010,	// 
		//kUnknownAttr	= 0x0020	// 
	};

	IDStyle() : fType(kUnknownStyle), fPath()  {}
	IDStyle(IDStyleType type, const PMString & fullPath)
	{
		ASSERT(type != kUnknownStyle);
		fType = type;
		fPath = fullPath;
	}

	void Reset()
	{
		fType = kUnknownStyle;
		fPath.clear();
	}

	IDStyleType GetStyleType() const { return fType; }
	PMString GetPath () const { return fPath; }

	/** IDStyle operator == */
	bool16 operator==(const IDStyle &other) const
	{
		return (fType == other.fType) && (fPath == other.fPath);
	}

	/** IDStyle operator != */
	bool16 operator!=(const IDStyle &other) const
	{
		return (fType!=other.fType) || (fPath!=other.fPath);
	}
		
	/** IDStyle operator < */
	bool16 operator <(const IDStyle & other) const
	{
		if (fType == other.fType)
			return fPath < other.fPath;
		else
			return fType < other.fType;
	}

	operator void* () const	 	// nonzero if good
	{ 
		// Require both members to be valid:
		return (fType==kUnknownStyle || fPath.empty()) ? nil : const_cast<IDStyle *>(this);
	}

private:
	IDStyleType fType;
	PMString fPath;
};

}

#endif
