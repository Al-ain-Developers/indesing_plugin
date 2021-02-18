//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISelectableDialogSwitcher.h $
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
#ifndef __ISelectableDialogSwitcher__
#define __ISelectableDialogSwitcher__

#include "IPMUnknown.h"
#include "IControlView.h"

class IControlView;
class IPanelControlData;
class PMString;
class IListControlData;
class IDialog;
class IPanelCreator;

// Constants used by auto-resizing selectable dialogs.
const int32 kMinGroupBoxHeight = 130;	// Minimum height of groupbox.
const int32 kGroupBorderOffset = 15;	// Y offset between bottom of dialog panel and group border widget in main panel.
const int32 kWindowGroupOffset = 12;	// Y offset between bottom of group border widget and the window.

/**	This interface is used to maintain the various dialogs which combine to form a selectable dialog. It's rare for 3rd parties to want to implement
	this interface, but it's common to use it when opening a selectable dialog. Typically code to do that would look like so:
	<pre>
		InterfacePtr<const IPanelControlData> panelData(mySelectableDialog, UseDefaultIID());
		IControlView *dialogView = panelData->FindWidget(kMyTopLevelDialogWidgetID);
		InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher(dialogView, UseDefaultIID());
		
		dialogSwitcher->SetDialogServiceID(kMySelectableDialogServiceImpl);
		dialogSwitcher->SwitchDialogPanelByID(kMySpecialDialogPanelWidgetID);

		mySelectableDialog->Open();
	
	</pre>
	@see IDialogCreator
	@see IDialog
*/
class ISelectableDialogSwitcher : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISELECTABLEDIALOGSWITCHER };
	
	enum {kNextPanel = -1, kPreviousPanel = -2};

	/**	Changes the displayed dialog panel to that of dialogNumber. Normally, validation takes place on the panel that will get hidden.
		Validation can be turned off by passing in false.  Pass in "kNextPanel" to switch to the next panel or "kPreviousPanel"
		to go to the previous panel.
	*/
	virtual void				SwitchDialogPanel(int32 dialogNumber, bool16 validate = kTrue) = 0;
	
	/** Changes the displayed dialog panel to the panel with the specified widget id.
	*/
	virtual void				SwitchDialogPanelByID(WidgetID panelsWidgetID) = 0;
	
	/**	Adds the dialog panel to the selectable dialog. "at" specifies the position of the panel relative to the others.  If "at" is -1, the panel is appended
		to the end of the list of panels. If autoVisible is true, the panel is added to the dialog's selection list.
	*/
	virtual void				AddDialogPanel(IControlView* dialogPanel, const PMString& panelName, int32 at = -1, bool16 autoVisible = kTrue) = 0;
	
	/**	Finds the dialog panel in the selectable dialog.
	*/
	virtual IControlView*		GetDialogPanel(WidgetID panelsWidgetID) = 0;
								
	/** Set the service ID for this dialog.  Used to find the sub dialog panels 
	*/								
	virtual void				SetDialogServiceID(const ServiceID& dialogServiceID,
												   const WidgetID dialogGroupPanelWidgetID = kDialogGroupPanelWidgetID,
												   const WidgetID dialogSelectionWidgetID = kSelectDialogSelectionWidgetID,
												   const WidgetID dialogTitleTextWidgetID = kSelectDialogTitleTextWidgetID) = 0;
								
	/**	Gets the service ID for this dialog.
	*/						
	virtual ServiceID			GetDialogServiceID() const = 0;
								
	/**	Gets the widget ID of the group panel that holds the dialog panels.
	*/
	virtual WidgetID			GetGroupPanelWidgetID() const = 0;
								
	/**	Gets the widget ID of the list box used to select the dialog panels.
	*/
	virtual WidgetID			GetSelectionListWidgetID() const = 0;
									
	/**	Gets the widget ID of the TextWidget that is to display the name of the currently active dialog panel.
	*/
	virtual WidgetID			GetTitleTextWidgetID() const = 0;
								

	/**	Returns the panel control data associated with the group panel widget. The group panel widget is the widget that holds all of the dialog sub panels.
	*/
	virtual IPanelControlData*	QueryGroupPanelControlData() = 0;
	
	/** Forces a dynamic load of all the dialog panels associated with this selectable dialog
	*/
	virtual void				LoadDialogPanels() = 0;
									
	/**	Call ShowDialogPanel to show a dialog panel and add its name to the selectable dialog's selection list.
	*/
	virtual void				ShowDialogPanel(const WidgetID panelWidgetID, const bool16 show = kTrue) = 0;
									

	/**	Call this function when the selectable dialog is closed to hide any non auto shown panels that were made visible after the dialog was opened.
	*/
	virtual void				HideNonAutoShownPanels() = 0;
	
	/** Returns the index of the currently displayed panel.
	*/
	virtual int32				GetCurrentPanelIndex() const = 0;
									
	/**	Given an index to a panel, this function returns the widget id of the panel.
	*/
	virtual WidgetID			GetPanelWidgetID(int32 index) const = 0;

	/**	Does the parent panel auto-resize in height as you switch to each panel.
	*/
	virtual bool16				GetAutoResizable() const = 0;

	/** Sets auto-resize for parent panel.
	*/
	virtual void				SetAutoResizable(const bool16 bAutoSize) = 0;
								

	/**	Remove a dialog panel.
	*/
	virtual void				RemoveDialogPanel(IControlView* dialogPanel) = 0;

	/**	Given the dialog panel's WidgetID, return its current position in the panel list.
	*/
	virtual	int32				GetDialogPanelIndex(WidgetID panelWidgetID) const = 0;
								
	/**	Returns the number of selectable dialog panels.
	*/								
	virtual	int32				GetNumDialogPanels() const = 0;
								
	/** Forces a dynamic unload of all the dialog panels associated with this selectable dialog
	*/
	virtual void				UnloadDialogPanels() = 0;

	/* gives the keyboard focus to the selected list */
	virtual bool16				SetKeyFocusToSelectionList() = 0;
};

#endif
