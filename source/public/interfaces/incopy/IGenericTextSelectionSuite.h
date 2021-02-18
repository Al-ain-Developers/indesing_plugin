//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGenericTextSelectionSuite.h $
//  
//  Owner: Ben Park
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __IGenericTextSelectionSuite__
#define __IGenericTextSelectionSuite__

//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
#include "ShuksanID.h"
#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "ICTextNavigationSuite.h" // For TextSelectionIndex

class ITextFocus;
class RangeData;
class SelectionExtension;

/**	
	CLASS DECLARATION 
	For Adobe internal use only and should not be used by external developers.
*/

class IGenericTextSelectionSuite : public IPMUnknown
{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		//enum { kDefaultIID = IID_IGALLEYTEXTSELECTION_SUITE };
		enum { kDefaultIID = IID_IGENERICTEXTSELECTION_SUITE };
		
		enum ViewType { kStandard, kNote };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//________________________________________________________________________________________
		//	DESCR:		Select the specified text range.
		//________________________________________________________________________________________
		
		/**
			Method to set a text selection.
			@param range Text range to set a text selection on
			@param storyRef UID reference of story to set selection in
			@param extendToUIDPair If want adjacent track changes to be included in the highlight must set the UID of the track change owned item.
						this is mainly an internal implementation detail.
			@return kTrue if selection was set.
		*/	
		virtual bool16 	SetSelection( RangeData r, const UIDRef& storyRef/* = kInvalidUIDRef*/, SelectionExtension *extendToUIDPair = nil) = 0;
		enum DrawChoice { kDontDrawSelection, kDrawSelection};
		
		/**
			Method to set a text selection (should go away eventually it's not suggested this be used externally)
			@param range Text range to set a text selection on
			@param storyRef UID reference of story to set selection in
			@param extendToUIDPair If want adjacent track changes to be included in the highlight must set the UID of the track change owned item.
						this is mainly an internal implementation detail.
			@param drawIt true if the selection should be drawn
			@return kTrue if selection was set.
		*/	
		virtual bool16 	SetSelectionHmm( RangeData r, const UIDRef& storyRef, SelectionExtension extendToUIDPair, DrawChoice drawIt) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Deselect everything in the selection.
		//________________________________________________________________________________________
		virtual void 	DeselectAll() = 0;
	
		//________________________________________________________________________________________
		//	DESCR:		Gets the selection - returns it in nStart and nLength
		//________________________________________________________________________________________
		virtual RangeData 	GetSelection( UIDRef* story = nil) const = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Checks to see if text is editable at current selection location. Returns true if editing is allowed.
		//________________________________________________________________________________________
		virtual bool16	CanEditText() = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Used to pseudo extend selection to deleted text. Makes no difference to behavior only ui appearance
		//________________________________________________________________________________________
//		virtual void SetSelectionIsExtendedToDeletedUID(UID extendToUID) = 0;
		
		/**
			Method to get track changed deleted text highlight extension information
			@return SelectionExtension left and right track change extension information values for left and right extension
					are kInvalidUID if no extension.
		*/	
		virtual SelectionExtension GetSelectionIsExtendedToDeletedUID() = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Return an instance of the current text focus
		//________________________________________________________________________________________
		virtual ITextFocus *QueryTextFocus() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Set the current parent widget for this selection
		//________________________________________________________________________________________		
		virtual void SetWidgetParent_(IPMUnknown *parent) = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Notify that selection changed doesn't notify suites. Used in SelectGalleyTextCmd and SelectNoteTextCmd
		//________________________________________________________________________________________		
//		virtual void SelectionChangedNotify() const = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Return the type of view associated with this selection
		//________________________________________________________________________________________		
		virtual ViewType GetSelectionViewType() = 0;
		
		//________________________________________________________________________________________
		//	DESCR:		Set the selection text model to value
		//________________________________________________________________________________________		
		virtual void TempSetSelectionTextModel(const UIDRef &storyRef) = 0;
		
};

#endif // __IGenericTextSelectionSuite__
