//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INotePaletteUtils.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __INOTEPALETTEUTILS__
#define __INOTEPALETTEUTILS__

#include "IPMUnknown.h"
#include "UIDList.h"
#include "NoteID.h"

//-----------------------------------
//	Forward References
//
class IPanelControlData;
class ITextLines;
class RangeData;
class IControlView;

class INotePaletteUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INOTEPALETTEUTILS };
	
	/** Display the given note to the note palette, content and other note information. 
		@param setSelection kTrue if resulting note is to receive active text focus.
		@param range to be used if valid, to set the selection in note palette
	 */
	virtual void SetNoteToPalette(UIDRef docRef, UIDRef storyRef, UID noteDataUID, bool16 setSelection = kTrue, const RangeData* range = nil) = 0;
	
	/** Initialize the ITextLine structure for display of text in the writingView */
	virtual void TextLineInit(IControlView* writingView, UIDRef storyRef) = 0;
				
	/** Reset note palette, First clear all info widgets.  Then to clear the writing panel with favor of
	 reseting the story data or the document data, or both. 
	 @param resetDocument reset view to current document
	 @param deactivatePalette specifies an explicit deactivation of the note palette
	 @param this is an internal undo/redo detail external users would pass kFalse (use default).
	*/
	virtual void ResetNotePalette( bool16 resetDocument /*= kFalse*/, bool16 deactivatePalette /*= kFalse*/, bool16 callingDuringResetView = kFalse) = 0;
		
	/** Resset a particular widget in the button section of the palette */
	virtual void ClearOneButtonWidget(IPanelControlData* containerPanelData, WidgetID thisWidgetID) = 0;
				
	/** set a string to this widget only */
	virtual void SetOneInfoWidget(IPanelControlData* containerPanelData, WidgetID thisWidget, const PMString& thisString) = 0;		

	/** get the writing view from the note palette,
		If the note palette is not opened, it returns nil.  If the note palette is opened but its
		view is empty (not being used for viewing), it also returns nil.
		If the note palette is opened and its view data is valid, then it returns the view. */
	virtual IControlView* GetNoteWritingPad() = 0;

	/** Return the note UID ref that is being viewed in the note palette
		If the note palette is not viewing any note data, it returns UIDRef::gNull. */
	virtual	UIDRef GetNotePaletteUIDRef() = 0;

	/** Return the story reference of the note being viewed in the note palette.
		If no note is viewed then it returns UIDRef::gNull. */
	virtual	UIDRef GetNotePaletteStoryRef() = 0;	 
		
	/**	return the note palettepanel itself */
	virtual IControlView* GetNotePanel() = 0;
	
	virtual bool16 IsNotePanelVisible() = 0;
	virtual bool16 ShowNotePanel(bool16 show = kTrue) = 0;
		
	/** Setup note information into palette widget and compose textlines*/
	virtual bool16 InitializePaletteData() = 0;
				 
	/**	Return kTrue if the displayed note has an active selection.
		Return kFalse if the displayed note does not have an active selection.  */
	virtual bool16 DisplayedNoteActive() = 0;
	
	/** Update note palette buttons */
	virtual void UpdatePaletteButtons(bool16 collapsed) = 0;			

	/** Update the story label widget */
	virtual void UpdateStoryLabel() = 0;				

	/** Update the total notes widget */
	virtual void UpdateTotalNotesDisplay() = 0;
				
	/** Update the modify time if noteDataRef == displayed note */
	virtual void UpdatePaletteNoteModifyTime(UIDRef noteDataRef) = 0;
				
	/** Initialize all the fields in the note palette with the given noteRef
		If no note is supplied, or storyRef is UIDRef::gNull, or noteRef is UIDRef::gNull, then reset note palette */
	virtual	void InitPaletteWidgets(UIDRef storyRef, UIDRef docRef, UIDRef noteRef = UIDRef::gNull) = 0;

	/** SetNoteToPalette() will not display the note if SuspendDisplay is set */
	virtual void SuspendDisplay() = 0;
				
	/** SetNoteToPalette() will resume display Note.*/
	virtual void ResumeDisplay() = 0;				

};

#endif // __INOTEPALETTEUTILS__
