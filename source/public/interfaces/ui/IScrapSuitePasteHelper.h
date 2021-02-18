//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IScrapSuitePasteHelper.h $
//  
//  Owner: Dave Burnard
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
//  Interface definition for Scrap SuitePaste extensibility
//  
//========================================================================================

#pragma once
#ifndef __IScrapSuitePasteHelper__
#define __IScrapSuitePasteHelper__

#include "DragDropConstants.h"
#include "DragDropID.h"

#include "IScrapSuite.h"

// --- Defaults for creating text frames when pasting text and dragging/dropping text.
//	An unlikely place for these constants to reside...
const PMReal kDefaultTextFrameHeight = 150.0;
const PMReal kDefaultTextFrameWidth = 150.0;

/**	IID_ISCRAPSUITEPASTEHELPER interface; This interface is used to add extensibility to IScrapSuite.
		Scrap suite extensibility requires the suite be derived from CScrapSuite_Extensible.  
		Create a new boss with an IScrapSuitePasteHelper implementation combined with a IK2ServiceProvider 
		implementation that corresponds to the service ID defined by the extensible scrap suite implementation.
	
		When the framework asks an extensible scrap suite if it could perform a paste (or paste inside), the suite 
		then asks each of it's paste helpers if they could perform a paste based on the data flavors on the clipboard. 
		One helper is chosen based on willingness to do so, and in the case of multiple helpers, 
		prioritized by helper type. The extensible suite then forwards the subsequent paste call to the chosen helper.

	@see IScrapSuite, CScrapSuite_Extensible
 */
class IScrapSuitePasteHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISCRAPSUITEPASTEHELPER };

		/** Return the type or priority of the helper.
				This is used to resolve conflicts that can arise when more than one paste helper is 
				capable of performing a paste operation. The presence of multiple helpers is not a conflict,
				a conflict would arise when one helper wants to replace or augment what another helper already does.
		
			@return helper type appropriate for this helper. Use DragDrop::kDefaultHelper by default.
		*/
		virtual DragDrop::eHelperType	
										GetHelperType() const = 0;

		// ----- Abilities
		/** Could the helper perform a paste with the current data from a data exchange controller (not necessarily the clipboard).

			@param suite IN the scrap suite this helper is assisting
			@param dataController IN the controller holding the data
			@return response from the data exchange handler that would perform any necessary conversions
		*/
		virtual DataExchangeResponse	CanPaste(const IScrapSuite*, IDataExchangeController* dataController) const = 0;
		
		/** Could the helper perform a paste inside with the current data from a data exchange controller (not necessarily the clipboard).

			@param suite IN the scrap suite this helper is assisting
			@param dataController IN the controller holding the data
			@param view IN optional active view parameter (this parameter remains for historical reasons)
			@param point IN point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis. (this parameter remains for historical reasons)
			@return response from the data exchange handler that would perform any necessary conversions
		*/
		virtual DataExchangeResponse	CanPasteInside(const IScrapSuite*, IDataExchangeController* dataController, IControlView* view = nil, const PBPMPoint& point = kInvalidPoint) const = 0;

		/** Get the external flavors that can be converted during Internalize (or Paste)
				Flavors should be added to the end of the list, in order by quality of the conversion (highest quality first).
				The helper function AppendFlavorIfUnique should be used.

			@param suite IN handler this helper is associated with
			@param dataController IN the controller (shouldn't be needed here)
			@param flavorList IN/OUT add flavors to the end of list 
		*/
		virtual void						AddInternalizeableFlavorsToList(const IScrapSuite*, IDataExchangeController*, OrderedFlavorList& flavorList) const = 0;

		// ----- Manipulators
		/** Paste item(s) from the clipboard to the active context

			@param suite IN the scrap suite this helper is assisting
			@param clipboard IN the clipboard controller
			@param view IN currently active view (this parameter remains for historical reasons)
			@param ignoreAttributes Ignore the attributes when pasting, default to kFalse
			@return DESCRIPTION
		*/
		virtual ErrorCode				Paste(const IScrapSuite*, IClipboardController* clipboard, IControlView* view, bool16 ignoreAttributes = kFalse) = 0;
		
		/** Paste item(s) on the clipboard inside the selected item (first of selected items)

			@param suite IN the scrap suite this helper is assisting
			@param clipboard IN the clipboard controller
			@param view IN currently active view (this parameter remains for historical reasons)
			@param point IN point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis. (this parameter remains for historical reasons)
			@return DESCRIPTION
		*/
		virtual ErrorCode				PasteInside(const IScrapSuite*, IClipboardController* clipboard, IControlView* view, const PBPMPoint& point = kInvalidPoint) = 0;
		
		/** Paste item(s) from a data exchange controller to the active context

			@param suite IN the scrap suite this helper is assisting
			@param dataController IN the controller holding the data
			@param view IN currently active view (this parameter remains for historical reasons)
			@param kFalse INOUT DESCRIPTION
			@return DESCRIPTION
		*/
		virtual ErrorCode				PasteFromScrap(const IScrapSuite*, IDataExchangeController* dataController, IControlView* view, bool16 ignoreAttributes = kFalse) = 0;
		
		/** Paste item(s) from a data exchange controller inside the selected item (first of selected items)

			@param suite IN the scrap suite this helper is assisting
			@param dataController IN the controller holding the data
			@param view IN currently active view (this parameter remains for historical reasons)
			@param point IN point in pasteboard coordinates to use for paste inside. Use kInvalidPoint to ignore and use selection as basis. (this parameter remains for historical reasons)
			@return DESCRIPTION
		*/
		virtual ErrorCode				PasteInsideFromScrap(const IScrapSuite*, IDataExchangeController* dataController, IControlView* view, const PBPMPoint& point = kInvalidPoint) = 0;
};

#endif
