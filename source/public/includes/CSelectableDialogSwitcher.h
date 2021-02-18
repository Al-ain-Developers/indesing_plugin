//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CSelectableDialogSwitcher.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CSelectableDialogSwitcher__
#define __CSelectableDialogSwitcher__

#include "ISelectableDialogSwitcher.h"
#include "HelperInterface.h"
#include "K2Vector.h"
#include "IStringListControlData.h"

//========================================================================================
// Class DialogPanelEntry
//========================================================================================

class DialogPanelEntry
{
public:
	typedef base_type data_type;
	DialogPanelEntry();
	DialogPanelEntry(const WidgetID dialogPanelWidgetID, int32 index, bool16 shown, bool16 autoVisible);
	DialogPanelEntry(const DialogPanelEntry& other);
	
	DialogPanelEntry& operator=(const DialogPanelEntry& other);
	bool16 operator==(const DialogPanelEntry& other) const;
	
	void			SetWidgetID(WidgetID widgetID) { fWidgetID = widgetID; }
	WidgetID		GetWidgetID() const { return fWidgetID; }
	
	void			SetIndex(int32 index) { fIndex = index; }
	int32			GetIndex() const { return fIndex; }
		
	void			SetShown(bool16 shown) { fShown = shown; }
	bool16			GetShown() const { return fShown; }

	void			SetAutoVisible(bool16 autoVisible) { fAutoVisible = autoVisible; }
	bool16			GetAutoVisible() const { return fAutoVisible; }
	
private:
	WidgetID		fWidgetID;
	int32			fIndex;
	bool16			fShown;
	bool16			fAutoVisible;
};


inline DialogPanelEntry::DialogPanelEntry() :
	fWidgetID(kInvalidWidgetID),
	fIndex(-1),
	fShown(kFalse),
	fAutoVisible(kFalse)
{
}

inline DialogPanelEntry::DialogPanelEntry(const WidgetID dialogPanelWidgetID, int32 index, bool16 shown, bool16 autoVisible) :
	fWidgetID(dialogPanelWidgetID),
	fIndex(index),
	fShown(shown),
	fAutoVisible(autoVisible)
{
}

inline DialogPanelEntry::DialogPanelEntry(const DialogPanelEntry& other) :
	fWidgetID(other.fWidgetID),
	fIndex(other.fIndex),
	fShown(other.fShown),
	fAutoVisible(other.fAutoVisible)
{
}

inline DialogPanelEntry& DialogPanelEntry::operator=(const DialogPanelEntry& other)
{
	if (&other != this)
	{
		fWidgetID = other.fWidgetID;
		fIndex = other.fIndex;
		fShown = other.fShown;
		fAutoVisible = other.fAutoVisible;
	}
	
	return *this;
}

inline bool16 DialogPanelEntry::operator==(const DialogPanelEntry& other) const
{
	return fWidgetID == other.fWidgetID && fIndex == other.fIndex && fAutoVisible == other.fAutoVisible;
}

//========================================================================================
// Class CSelectableDialogSwitcher
//========================================================================================

class WIDGET_DECL CSelectableDialogSwitcher : public ISelectableDialogSwitcher
{
public:
	// ----- Initialization -----
	
						CSelectableDialogSwitcher(IPMUnknown *boss);
	virtual				~CSelectableDialogSwitcher();

	virtual void		ReadWrite(IPMStream* s, ImplementationID prop);
	
	// ----- Selectable dialog methods -----

	virtual void				SwitchDialogPanel(int32 dialogNumber, bool16 validate = kTrue);
									// Changes the displayed dialog panel to that of dialogNumber.
	
	virtual void				SwitchDialogPanelByID(WidgetID panelsWidgetID);
									// Changes the displayed dialog panel to the panel with the specified widget id.
	
	virtual void				AddDialogPanel(IControlView* dialogPanel, const PMString& panelName, int32 at = -1, bool16 autoVisible = kTrue);
									// Adds the dialog panel to the selectable dialog. "at" specifies the position
									// of the panel relative to the others.  If "at" is -1, the panel is appended
									// to the end of the list of panels. If visible is true, the panel is added to
									// the dialog's selection list.
	
	virtual IControlView*		GetDialogPanel(WidgetID panelsWidgetID);
									// Finds the dialog panel in the selectable dialog.

	virtual void				SetDialogServiceID(const ServiceID& dialogServiceID,
												   const WidgetID dialogGroupPanelWidgetID = kDialogGroupPanelWidgetID,
												   const WidgetID dialogSelectionWidgetID = kSelectDialogSelectionWidgetID,
												   const WidgetID dialogTitleTextWidgetID = kSelectDialogTitleTextWidgetID);
									// Set the service ID for this dialog.  Used to find the sub dialog panels
									
	virtual ServiceID			GetDialogServiceID() const;
									// Gets the service ID for this dialog.

	virtual WidgetID			GetGroupPanelWidgetID() const;
									// Gets the widget ID of the group panel that holds the dialog panels.

	virtual WidgetID			GetSelectionListWidgetID() const;
									// Gets the widget ID of the list box used to select the dialog panels.

	virtual WidgetID			GetTitleTextWidgetID() const;
									// Gets the widget ID of the TextWidget that is to display the name of
									// the currently active dialog panel.

	virtual IPanelControlData*	QueryGroupPanelControlData();
									// Returns the panel control data associated with the group panel widget 
									//  The group panel widget is the widget that holds all of the dialog sub panels.

	virtual void				LoadDialogPanels();
									// Forces a dynamic load of all the dialog panels associated with this selectable dialog
	
	virtual void				ShowDialogPanel(const WidgetID panelWidgetID, const bool16 show = kTrue);
									// Call ShowDialogPanel to show a dialog panel and add its name to the selectable dialog's selection list.
	
	virtual int32				GetCurrentPanelIndex() const;
									// Returns the index of the currently displayed panel.

	virtual void				HideNonAutoShownPanels();
									// Call this function when the selectable dialog is closed to hide any non auto shown panels that
									// were made visible after the dialog was opened.

	virtual WidgetID			GetPanelWidgetID(int32 index) const;
									// Given an index to a panel, this function returns the widget id of the panel.

	virtual bool16				GetAutoResizable() const;
									// Does the parent panel auto-resize in height as you switch to each panel.

	virtual void				SetAutoResizable(const bool16 bAutoSize);
									// Sets auto-resize for parent panel.

	virtual void				RemoveDialogPanel(IControlView* dialogPanel);
									// Remove a dialog panel.

	virtual	int32				GetDialogPanelIndex (WidgetID panelWidgetID) const;
									// Given the dialog panel's WidgetID, return its current position in the
									// panel list.
	virtual	int32				GetNumDialogPanels() const;
	
	virtual void				UnloadDialogPanels();
	virtual bool16						SetKeyFocusToSelectionList();

protected:
	// ----- Implementation -----

	virtual void						ShowHideDialogPanel(int32 dialogNumber, bool16 showPanel);
	
	virtual void						SelectionWidgetAddString(const PMString& newString, int32 at = IStringListControlData::kEnd, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual void						SelectionWidgetClear(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual PMString					SelectionWidgetGetString(int32 index) const;
	virtual int32						SelectionWidgetLength() const;
	virtual void						SelectionWidgetRemoveString(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual void						SelectionWidgetSelect(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
private:	
	virtual void						InitializePanel();
protected:
	virtual void						RebuildIfNecessary();
	
	virtual void						UpdateTitleTextString(int32 dialogNumber);

	virtual int32						GetPanelIndexInDialog(const int32& panelIndex) const;
	virtual bool16						GetPanelAutoVisible(const int32& index) const;
	virtual void						GetAdjustedPanelPosition(IControlView* panel, const K2Vector<ClassID>& panelIDs, int32& panelPosition);
	virtual void						ReadWriteDialogPanel(IPMStream* s, K2Vector<DialogPanelEntry>& dialogPanelList);

	int32								fCurrentDialogPanelIndex;
	bool16								fSwitchingPanels;
	ServiceID							fDialogServiceID;
	bool16								fPanelsLoaded;
	WidgetID							fGroupPanelWidgetID;
	WidgetID							fSelectionWidgetID;
	WidgetID							fTitleTextWidgetID;
	K2Vector<DialogPanelEntry>			fDialogPanelList;
	bool16								fPanelsInitialized;
	bool16								fAutoResizable;

#ifdef DEBUG
	void								DumpPanelEntries();
#endif

DECLARE_HELPER_METHODS()
};

#endif
