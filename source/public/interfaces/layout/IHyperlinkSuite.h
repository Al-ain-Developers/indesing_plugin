//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkSuite.h $
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
#ifndef __IHyperlinkSuite__
#define __IHyperlinkSuite__

// Interfaces:
#include "IPMUnknown.h"
#include "HyperlinkID.h"

class UIDList;

// Includes:
/** Defines the interface for a hyperlink-related suite to be used in the new selection architecture
	@ingroup layout_suite
	@ingroup layout_hyper
*/
class IHyperlinkSuite : public IPMUnknown
{
public:
	/**	Can any of the CSBs create a hyperlink source from the selection?
		@param none
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanCreateHyperlinkSource() const = 0;

	/**	Can any of the CSBs create an XRef source from the selection?
		@param none
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanCreateXRefSource() const = 0;

	/**	Can any of the CSBs create a hyperlink destination from the selection?
		@param none
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanCreateHyperlinkDestination() const = 0;

	/**	Can any of the CSBs create a hyperlink source from the selection?
		@param source - UIDRef of the source we want to change
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanChangeHyperlinkSource(UIDRef source) const = 0;

	/**	Can any of the CSBs change a hyperlink destination from the selection?
		@param dest - UIDRef of the dest client wants to change
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanChangeHyperlinkDestination(UIDRef dest) const = 0;

	/**	Can any of the CSBs create a bookmark from the selection?
		@param none
		@return bool16 - kTrue == Yes/kFalse == No
	 */
	virtual	bool16	CanCreateBookmark() const = 0;
	

	/**	If the selection is a hyperlink source
		@param none
		@return UID - New UID (kInvalidUID if method fails
	 */
	virtual	UID			GetHyperlinkSource() const = 0;
	
	/**	Create a hyperlink source from the selection
		@param *name - Default name to use
		@param charStyle - Character Style for the source.
		@return UID - New UID (kInvalidUID if method fails
	 */
	virtual	UID	CreateHyperlinkSource(const PMString *name, UID charStyle = kInvalidUID) const = 0;

	/**	Create a xref source from the selection
		@param *name - Default name to use
		@param format - UID of the cross reference format to use. kInvalidUID uses the default format.
		@return UID - New UID (kInvalidUID if method fails
	 */
	virtual	UID	CreateXRefSource(const PMString *name, UID format = kInvalidUID) const = 0;

	/**	Create a hyperlink source from the selection
		@param *sourceName - Default name to use
		@return UID - New UID (kInvalidUID if method fails
	 */
	virtual	UID	CreateHyperlinkDestination(const PMString *sourceName) const = 0;

	/**	Create a bookmark from the selection
		@param indentLevel - Level to indent at
		@param parentBookmark - What should be the new bookmarks parent (DocUID 
		will put it at the root level)
		@return UID - New UID (kInvalidUID if method fails)
	 */
	virtual	UID	CreateBookmark(int32 indentLevel, UID parentBookmark) const = 0;
	
	/**	Modify a hyperlink source from the selection
		@param source - UIDRef of the source to change
		@param *name - Name to use
		@return UID - New UID (kInvalidUID if method fails)
	 */
	virtual	UID	ChangeHyperlinkSource(UIDRef source, const PMString *name) const = 0;

	/**	Modify a hyperlink destination from the selection
		@param dest - Dest client wants to modify
		@param *sourceName - Default name
		@return UID - New UID (kInvalidUID if method fails)
	 */
	virtual	UID	ChangeHyperlinkDestination(UIDRef dest, const PMString *sourceName) const = 0;

	/**	Generate a new name for a hyperlink source
		@param *sourceName - Default name to use
		@param bUnique - Should the name be unique? 
	 */
	virtual void GenerateHyperlinkSourceName(PMString *sourceName, bool16 bUnique = kTrue) const = 0;

	/**	Generate a new name for a hyperlink destination
		@param *destName - Default name to use
		@param bUnique - Should the name be unique? 
	 */
	virtual void GenerateHyperlinkDestinationName(PMString *destName, bool16 bUnique = kTrue, int32 maxLength = 100) const = 0;

	/**	Return a list of UIDs to hyperlinks that are selected
		@param none
		@return UIDList - List of selected hyperlinks
	 */
	virtual UIDList GetSelectedHyperlinkSources() const = 0;
};

#endif	// __IHyperlinkSuite__

