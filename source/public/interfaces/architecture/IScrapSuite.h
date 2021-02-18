//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScrapSuite.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IScrapSuite__
#define __IScrapSuite__

#include "IPMUnknown.h"
#include "IControlView.h"
#include "PMPoint.h"
#include "K2Vector.h"
#include "ShuksanID.h"
#include "PMFlavorTypes.h"

//========================================================================================
// Forward declarations
//========================================================================================

class IClipboardController;
class IDataExchangeController;
class ICommand;
class UIDList;
class IDataExchangeHandler;

//========================================================================================
// CLASS IScrapSuite
//========================================================================================
/**	IID_ISCRAPSUITE interface; This interface reside both on page item specifers and
	selection suites. Normally these method apply on specific item first, then on 
	selections, however, usage of specifier is obseleting.
 */
class IScrapSuite : public IPMUnknown
{
// ----- Abilities
public:
	enum { kDefaultIID = IID_ISCRAPSUITE };

	/**	Can the (selected) pageitem(s) be cleared?
		@param none
		@return  
	 */
	virtual bool16	CanClear() = 0;

	/**	Can the (selected) pageitem(s) be copied?
		@param clipboard the clipboard the items copied to
		@return  
	 */
	virtual bool16	CanCopy(IClipboardController* clipboard) = 0;

	/**	Can the (selected) pageitem(s) be cut?
		@param clipboard the clipboard the items copied to 
		@return  
	 */
	virtual bool16	CanCut(IClipboardController* clipboard) = 0;

	/**	Can the pageitem(s) in the clipboard be pasted (selection accept paste)?
		@param clipboard the clipboard stores the items
		@return  
	 */
	virtual bool16	CanPaste(IClipboardController* clipboard) = 0;

	/**	Can the pageitem(s) in the clipboard be pasted inside to selection?
		@param clipboard the clipboard stores the items
		@param view Control view for the point. Use nil to use selection for paste inside.
		@param thePoint point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis.
		@return  
	 */
	virtual bool16	CanPasteInside(IClipboardController* clipboard, IControlView* view = nil, const PBPMPoint& point = kInvalidPoint) = 0;

	/**	Can the (selected) pageitem(s) be duplicated?
		@param none
		@return bool16 
	 */
	virtual bool16 	CanDuplicate() = 0;

	/**	Can the (selected) pageitem(s) all be deselected?
		@param none
		@return bool16 
	 */
	virtual bool16 	CanDeselectAll() = 0;

	// Does current selection support Copy/Paste (part of the answer to CanXXX() operations, above)

	/**	Can current selection be copied?
		@param none
		@return  
	 */
	virtual bool16	CanSelectionBeCopied() const = 0;

	/**	Does current selection accept paste?
		@param none
		@return kTrue if selection can accept paste, kFalse otherwise. 
	 */
	virtual bool16	CanSelectionAcceptPaste() const = 0;

	/**	Does current selection accept pasteinside?
		@param none
		@return kTrue if selection can accept paste inside, kFalse otherwise. 
	 */
	virtual bool16	CanSelectionAcceptPasteInside() const = 0;


	/**	Does current selection accept pasteinside?
		@param view Control view paste to(ususally front view; active context's view) 
		@return kTrue if this point location can accept paste inside, kFalse otherwise. 
	 */
	virtual bool16	CanPasteInsideAtPoint(IControlView* view, const PBPMPoint& point) const = 0;

	// Get the external flavors that can be Externalized (Copy), or Internalized (Paste)
public:

	/**	Get the external flavors that can be Externalized(Copy)
		@param dataController Data exchange controller, such as clipboard, dragdrop, libraryscrapcontroller etc.
		@param flavorList [IN/OUT] flavor list, store result
		@return  
	 */
	virtual void		BuildFlavorListForExternalize(IDataExchangeController* dataController, OrderedFlavorList& flavorList) const = 0;

	/**	Get the external flavors that can be Internalized (Paste)
		@param dataController  Data exchange controller, such as clipboard, dragdrop, libraryscrapcontroller etc.
		@param flavorList  [IN/OUT] flavor list, store result
		@return  
	 */
	virtual void		BuildFlavorListForInternalize(IDataExchangeController* dataController, OrderedFlavorList& flavorList) const = 0;

// ----- Manipulators
public:

	/**	Clear (delete) the selection
		@param none
		@return  Command sequence processing result
	 */
	virtual ErrorCode	Clear() = 0;

	/**	Copy item or selection to clipboard
		@param clipboard the clipboard the items copied to
		@return  Command sequence processing result
	 */
	virtual ErrorCode	Copy(IClipboardController* clipboard) = 0;

	/**	Copy item or selection to clipboard and delete it.
		@param clipboard the clipboard the items copied to
		@return  Command sequence processing result
	 */
	virtual ErrorCode	Cut(IClipboardController* clipboard) = 0;

	/**	Paste item from the clipboard to the view
		@param clipboard the clipboard the items pasted from
		@param view Control view paste to(ususally front view; active context's view) 
		@param ignoreAttributes Ignore the attributes when pasting, default to kFalse
		@return  Command sequence processing result
	 */
	virtual ErrorCode	Paste(IClipboardController* clipboard, IControlView* view, bool16 ignoreAttributes = kFalse) = 0;

	/**	Duplicate a page item 
		@param offset offset relative to original item
		@param view Control view to duplicate item to(ususally front view; active context's view) 
		@param selectDuplicate if kTrue (default), select the duplicated item
		@return  Command sequence processing result
	 */
	virtual ErrorCode	Duplicate(const PBPMPoint& offset, IControlView* view, bool8 selectDuplicate = kTrue) = 0;

	/**	Deselect all page items or selections
		@param none
		@return Command sequence processing result 
	 */
	virtual ErrorCode	DeselectAll() = 0;


	/**	Paste item on the clipboard inside to selected item (first of selected items)
		@param clipboard the clipboard the items pasted from
		@param view Control view paste to(ususally front view; active context's view) 
		@param thePoint point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis.
		@return  Command sequence processing result
	 */
	virtual ErrorCode	PasteInside(IClipboardController* clipboard, IControlView* view, const PBPMPoint& point = kInvalidPoint) = 0;

	/**	Copy item or selection to scrap (specified by dataController)
		@param dataController Data exchange controller, such as clipboard, dragdrop, libraryscrapcontroller etc.
		@return  Command sequence processing result
	 */
	virtual ErrorCode	CopyToScrap(IDataExchangeController* dataController) = 0;

	/**	Paste item from scrap (specified by dataController) to the view
		@param dataController Data exchange controller, such as clipboard, dragdrop, libraryscrapcontroller etc.
		@param view Control view to paste item to(ususally front view; active context's view) 
		@param ignoreAttributes Ignore the attributes when pasting from scrap, default to kFalse
		@return   Command sequence processing result
	 */
	virtual ErrorCode	PasteFromScrap(IDataExchangeController* dataController, IControlView* view, bool16 ignoreAttributes = kFalse) = 0;

	/**	Paste item from scrap (specified by dataController) insdie to the selected item in the view
		@param dataController Data exchange controller, such as clipboard, dragdrop, libraryscrapcontroller etc.
		@param view Control view to paste item to(ususally front view; active context's view) 
		@param thePoint point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis.
		@return Command sequence processing result
	 */
	virtual ErrorCode	PasteInsideFromScrap(IDataExchangeController* dataController, IControlView* view, const PBPMPoint& point = kInvalidPoint) = 0;

};

#endif
