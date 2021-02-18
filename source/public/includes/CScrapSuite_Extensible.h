//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScrapSuite_Extensible.h $
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
//========================================================================================

#pragma once
#ifndef __CScrapSuite_Extensible__
#define __CScrapSuite_Extensible__

#include "IK2ServiceProvider.h"
#include "IScrapSuite.h"
#include "CPMUnknown.h"

class IScrapSuitePasteHelper;


/** Extensible implementation of the IScrapSuite interface used for clipboard paste operations.
		Implementors of IScrapSuite will usually derive from CScrapSuite_Extensible, unless they have a good reason to avoid extensibility.

		@see IScrapSuite, IScrapSuitePasteHelper
 */
class PUBLIC_DECL CScrapSuite_Extensible : public CPMUnknown<IScrapSuite>
{
	public:
						CScrapSuite_Extensible(IPMUnknown *boss);
		virtual			~CScrapSuite_Extensible();
		
		/** @name eActionType
				enumeration of the different actions an IScrapSuitePasteHelper can be called upon to perform
		*/
		enum eActionType {
			/** paste from the clipboard */
			kPasteAction = 0, 
			/** paste inside from the clipboard */
			kPasteInsideAction, 
			/** paste from a controller other than the clipboard (i.e. a library) */
			kPasteFromScrapAction, 
			/** paste inside from a controller other than the clipboard (i.e. a library) */
			kPasteInsideFromScrapAction, 
			kActionType_Max = kPasteInsideFromScrapAction 
		};
		
		// ----- Abilities
		virtual bool16			CanClear() = 0;
		virtual bool16			CanCopy(IClipboardController* clipboard) = 0;
		virtual bool16 			CanDuplicate() = 0;

		virtual bool16			CanSelectionBeCopied() const = 0;
		virtual bool16			CanSelectionAcceptPaste() const = 0;
		virtual bool16			CanSelectionAcceptPasteInside() const = 0;
		virtual bool16			CanPasteInsideAtPoint(IControlView* view, const PBPMPoint& point) const = 0;

		/** @name Extensible Abilities
				The following methods have been overridden to delegate to the paste helpers associated with this scrap suite.
				Framework use only - subclasses should not override these methods.
		*/
		//@{
		/**  */
		virtual bool16			CanPaste(IClipboardController* clipboard);
		/**  */
		virtual bool16			CanPasteInside(IClipboardController* clipboard, IControlView* view = nil, const PBPMPoint& point = kInvalidPoint);
		/**  */
		virtual bool16			CanCut(IClipboardController* clipboard);
		//@}

		/** Provides the default implementation of Copy followed by Clear */
		virtual ErrorCode		Cut(IClipboardController* clipboard);
		
		// ----- Manipulators
		virtual ErrorCode		Clear() = 0;
		virtual ErrorCode		Copy(IClipboardController* clipboard) = 0;
		virtual ErrorCode		Duplicate(const PBPMPoint& offset, IControlView* view, bool8 selectDuplicate = kTrue) = 0;

		virtual ErrorCode		CopyToScrap(IDataExchangeController* dataController) = 0;
		
		// Get the external flavors that can be Externalized (Copy), or Internalized (Paste)
		virtual void				BuildFlavorListForExternalize(IDataExchangeController* dataController, OrderedFlavorList& flavorList) const = 0;
		
		/** Overridden to delegate to the paste helpers associated with this scrap suite. */
		virtual void				BuildFlavorListForInternalize(IDataExchangeController* dataController, OrderedFlavorList& flavorList) const;

		/** @name Extensible Manipulators
				The following methods methods have been overridden to delegate to the paste helpers associated with this scrap suite.
				Framework use only - subclasses should not override these methods.
		*/
		//@{
		/**  */
		virtual ErrorCode				Paste(IClipboardController* clipboard, IControlView* view, bool16 ignoreAttributes);
		/**  */
		virtual ErrorCode				PasteInside(IClipboardController* clipboard, IControlView* view, const PBPMPoint& point = kInvalidPoint);
		/**  */
		virtual ErrorCode				PasteFromScrap(IDataExchangeController* dataController, IControlView* view, bool16 ignoreAttributes);
		/**  */
		virtual ErrorCode				PasteInsideFromScrap(IDataExchangeController* dataController, IControlView* view, const PBPMPoint& point = kInvalidPoint);
		//@}

		// ----- Extensibility
		/** Override this to return the service ID that paste helpers for this suite will respond to. 
		*/
		virtual ServiceID 		GetScrapSuitePasteHelperServiceID() const = 0;

	private:
		IScrapSuitePasteHelper*	GetActiveScrapSuitePasteHelper(eActionType action) const;
		IScrapSuitePasteHelper*	QueryHelper_ForAction(eActionType action, IDataExchangeController* dataController, IControlView* view = nil, const PBPMPoint& point = kInvalidPoint) const;

		IScrapSuitePasteHelper*	fActiveScrapSuitePasteHelpers[kActionType_Max];	
			// Lifetime does not extend beyond duration of an atomic CanPaste,  Paste or PasteFromScrap call.	
};

#endif //__CDragDropSource__

