//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDialogController.h $
//  
//  Owner: Dave Burnard (was Tom Taylor)
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
#ifndef __IDialogController__
#define __IDialogController__

#include "IPMUnknown.h"
#include "IControlView.h"
#include "ITriStateControlData.h"
#include "ITextValue.h"
#include "PMString.h"

class IStringListControlData;
class IControlView;
class IPanelControlData;
class IDialog;
class IActiveContext;

static const WidgetID kNoInvalidWidgets = 0;

/** Interface that client code should implement for dialog.
*/
class IDialogController : public IPMUnknown
{
#if 0
	friend class CSelectableDialogController;
	friend class CDialogObserver;
	friend class CDialog;
	friend class CSelectableDialogSwitcher;
#endif

public:
	enum { kDefaultIID = IID_IDIALOGCONTROLLER };
	// ---------------------------
	/**@name Dialog protocol */
	//@{

	/** Should be overridden to initialize each widget in the dialog
		with its default value.
	*/
	virtual void				InitializeDialog(IActiveContext* context) = 0;
	virtual IActiveContext*		QueryDialogContext() = 0;

	/** This function is called when the user clicks the "ok" (or equivalent)
		button.  Override ValidateFields to check that the data in each
		dialog control is valid and within limits.  It's up to the subclass
		to display an alert.  If one or more of the fields have invalid data,
		return the WidgetID of the dialog item to select.  If all fields are
		valid, return kNoInvalidWidgets.  When all fields are valid, the
		ApplyFields function will be called.
		@return WidgetID of dialog item with invalid data, or kNoInvalidWidgets if data validated successfully
	*/
	virtual WidgetID			ValidateDialog() = 0;


	/** Should be overridden to retrieve data from the widgets in the
		dialog and apply it. The widget that caused the apply is passed
		in 'widgetId. By default the widget with id kOKButtonWidgetID causes
		an apply. Override Update to have others call ApplyFields.
		@param widgetId widget that caused the apply
	*/
	virtual void				ApplyDialog(const WidgetID& widgetId) = 0;


	/** This function is called when the user holds down the option/alt
		key and the cancel button changes to "Reset" and then clicks on
		the reset button. By default, this function simply calls
		InitializeFields. For most dialogs, this results in the correct
		behavior.
	*/
	virtual void				ResetDialog() = 0;


	/**	This function is called when the user clicks the "cancel" button.
		Override if the dialog needs to know when this happens.
	*/
	virtual void				UserCancelled() = 0;

	/** This function is called during the process of closing the dialog.
		This gives subclassers an opportunity to do some special cleanup.
	*/
	virtual void				DialogClosing() = 0;


	//@}

	// --------------------------------
	/**@name Dialog query methods */
	//@{

	/** Returns kTrue if InitializeFields() has been called.
	*/
	virtual bool16				HasBeenInitialized() const = 0;
									//

	/** This method exists so that subclasses don't have to call
		the inherited InitializeFields() function.
	*/
	virtual void				SetInitialized(bool16 initialized) = 0;


	//@}

	// --------------------------------
	/**@name Owner query methods */
	//@{

	/** Set the owner panel of this dialog.
	*/
	virtual void				SetOwner(IControlView* ownerPanel) = 0;


	/** Get the owner panel of this dialog.  This function
		may return nil.
		@return reference to IControlView interface on panel boss object that owns this dialog,
		or nil if no current owner.
	*/
	virtual IControlView*		GetOwner() const = 0;
									//

	//@}

	// --------------------------------
	/**@name Previewable dialog methods */
	//@{

	/** Accessor for name.
	*/
	virtual void				GetName(PMString& name) = 0;

	//@}

	// --------------------------------
	/**@name Dialog helper methods */
	//@{

	/** Helper methods for easily setting the text of a
		widget that has text control data.
	*/
	virtual void				SetTextControlData(const WidgetID& widgetId, const PMString& text, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Helper methods for easily getting the text from a
		widget that has text control data.
	*/
	virtual PMString			GetTextControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const = 0;


	/** Sets value of a widget with an ITextValue interface.
	*/
	virtual void				SetTextValue(const WidgetID& widgetId, const PMReal& value, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Gets the value of a widget with an ITextValue interface.
	*/
	virtual PMReal				GetTextValue(const WidgetID& widgetId, const IPanelControlData* panel = nil, bool16 *outParsingError = nil,bool16 *outIsBlank = nil) const = 0;

	/** Sets the control-state of a
		widget(editbox) that has an ITextValue interface.
	*/
	virtual void				SetTextValueControlState(const WidgetID& widgetId, ITextValue::TextControlState controlState, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Gets the control-state from a
		widget(editbox) that has an ITextValue interface.
	*/
	virtual ITextValue::TextControlState		GetTextValueControlState(const WidgetID& widgetId, const IPanelControlData* panel = nil) const = 0;


	/** Helper methods for easily setting and getting the state
		of a widget that has boolean control data.
	*/
	virtual void				SetBooleanControlData(const WidgetID& widgetId, bool16 isChecked, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**
	*/
	virtual bool16				GetBooleanControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const = 0;


	/** Helper methods for easily setting the state
		of a widget that has tristate control data.
	*/
	virtual void							SetTriStateControlData(const WidgetID& widgetId, ITriStateControlData::TriState triState, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Helper methods for easily setting the state
		of a widget that has tristate control data.
	*/
	virtual void							SetTriStateControlData(const WidgetID& widgetId, bool16 isSelected, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Helper methods for easily getting the state
		of a widget that has tristate control data.
	*/
	virtual ITriStateControlData::TriState	GetTriStateControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const = 0;


	/** Helper method to get which widget in a cluster is selected
	*/
	virtual WidgetID			GetSelectedClusterWidget(WidgetID cluster, const IPanelControlData* panel = nil) = 0;

	/** Helper method to set which widget in a cluster is selected
	*/
   virtual void				SetSelectedClusterWidget(WidgetID clusterId, WidgetID widgetToSelect, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;


	/** Query for the data interface of a widget that has list control data.
	*/
	virtual IStringListControlData*	QueryListControlDataInterface(const WidgetID& widgetId, const IPanelControlData* panel = nil) const = 0;


	/**
	*/
	virtual IPanelControlData*	QueryIfNilElseAddRef(const IPanelControlData* panel) const = 0;

	/** This method is typically used in conjuntion with Validate() to
		select the widget that has "illegal" values.
	*/
	virtual void				SelectDialogWidget(const WidgetID& widgetId) = 0;

	/** Access a flag that used to be in CDialogObserver
	*/
	virtual bool16				GetPreviewModeOn() = 0;

	/** Manage a flag that used to be in CDialogObserver
	*/
	virtual	void				SetPreviewModeOn(bool16 bOn) = 0;
	//@}

};

#endif
