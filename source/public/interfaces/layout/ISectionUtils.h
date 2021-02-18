//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISectionUtils.h $
//  
//  Owner: Ryan Gano
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __ISectionUtils__
#define __ISectionUtils__

#include "SectionID.h"
#include "WidgetDefs.h"

class IDocument;
class ISection;

/**	Utilities related to sections.
*/
class ISectionUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISECTIONUTILS };

	/** Is the page UID the starting page of a section? Return the section index if requested.
	*/
	virtual bool16 IsPageStartOfSection(const UIDRef& pageRef, int32* sectionIndex = nil) = 0;

	/** INTERNAL USE:
		Remove an empty sections from the document. This is a section associated with page[0] in the document.
	*/	
	virtual ErrorCode RemoveEmptySection(IDocument* doc) = 0;

	/** IsLegalAlternateLayoutName
		@param doc, the document
		@param nameToCheck, the name to check for validity
		@param nameToSkip, the name to skip (e.g. the name for the section you are validating). May be kNullString to avoid this check.
		Return kFalse if name is valid, kFalse if not (e.g. empty or duplicate)
	 */
	virtual bool16 IsLegalAlternateLayoutName(IDocument* doc, const PMString& nameToCheck, const PMString& nameToSkip) = 0;

	/** Return the section and/or alternate layout names for the document (in the order they appear in the document, i.e. QueryOrderedList).
		@param doc, the document to get the names for
		@param sectionNames, a K2Vector of strings that will be the OUT paramater
		@param style, one of a PageNameStyle enum to return sections, alternate layouts, or both.
		@see ISectionList::QueryOrderedList
		@see WidgetDefs.h, use one of the PageNumStyle values: kAlternateLayoutNames, kSectionNames, or kAlternateAndSectionNames

	 */
	virtual void GetSectionNames(IDocument* doc, K2Vector<PMString>& sectionNames, PageNameStyle style) = 0;
};


#endif	// __ISectionUtils__
