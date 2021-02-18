//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IHTMLPageItemSuite.h $
//  
//  Owner: Dave Stephens
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
//  Comments:	Selection suite for multimedia page items
//  
//========================================================================================

#pragma once
#ifndef _IHTMLPageItemSuite_
#define _IHTMLPageItemSuite_

#include "HTMLPGTID.h"

/** Selection suite for manipulating HTML page items.
	
*/
class IHTMLPageItemSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTMLPAGEITEMSUITE};

		
	/** Tests the current selection for HTML page items.
		@return true if the selection is a single HTML page item or its container; false otherwise.
	*/
	virtual bool32 IsHTMLSelection() const = 0;
	
	/** Users cannot edit placed HTML. This routine let's the client know if the HTML is editable.
		@return Whether or not the HTML can be edited.
	 */
	virtual bool32 CanEditHTML() const = 0;
	
	/** Get the HTML assigned to the currently selected HTML page item.
		@return The HTML contained in the page item.
	*/
	virtual WideString GetHTML() const = 0;
	
	/** Set the provided HTML code into the currently selected HTML page item.
		@param html [IN] the new HTML code to set.
		@return kSuccess if the HTML was successfully assigned to the page item; kFailure or some other errorcode otherwise.
			Note that some HTML page items cannot have their HTML edited. Placed/linked HTML is the main example.
	*/
	virtual ErrorCode SetHTML(const WideString& html) const = 0;
	
	/** Force the poster image and the page item's geometry to update based on the current HTML. 
		*/
	virtual void Refresh() const = 0;
	
	/** Can we insert an HTML page item onto the layout and optionally open the "Edit HTML..." dialog for the page item?
		@return kTrue if we can insert the default HTML page item into the layout.
	 */
	virtual bool32 CanInsertHTMLPageItem() const = 0;
	
	/** Insert a default HTML page item and optionally open the "Edit HTML..." dialog for that page item.
		@param openEditDialog [IN]: pass kTrue to open the "Edit HTML..." dialog after creating the page item.
		@return An error code indicating kSuccess or some failure.
	 */
	virtual ErrorCode InsertHTMLPageItem(bool32 openEditDialog) const = 0;
	
};


#endif // _IHTMLPageItemSuite_