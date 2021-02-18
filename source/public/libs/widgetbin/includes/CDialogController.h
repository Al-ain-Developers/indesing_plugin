//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CDialogController.h $
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
#ifndef __CDialogController__
#define __CDialogController__

#include "IDialogController.h"
#include "CPMUnknown.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/** Basic implementation of the IDialogController interface, used to control dialogs. 
		Implementors of IDialogController should derive from CDialogController. 
		
		@see IDialogController
*/
class WIDGET_DECL CDialogController : public CPMUnknown<IDialogController>
{
public:
	// ----- Initialization -----
	
						CDialogController(IPMUnknown *boss);
	virtual				~CDialogController();
	
	// ----- Dialog protocol -----
private:
	friend class QAFontDlgController; //SEIssue fix this
	
	// Framework Only - Don't call or override these, they call the protected XXXFields methods below.
	virtual WidgetID ValidateDialog();
	virtual void ApplyDialog( const WidgetID& widgetId);
	virtual void ResetDialog();
	virtual void DialogClosing();
	virtual void InitializeDialog(IActiveContext* context);

	// Deprecated: These are declared here just to cause compiler errors in existing code.
	virtual int ApplyFields(const WidgetID& /*widgetId*/) const {ASSERT_FAIL("Implement ApplyDialogFields instead"); return 0;}
	virtual char* ValidateFields() const {ASSERT_FAIL("Implement ValidateDialogFields instead"); return 0;}
	virtual int ResetFields() const {ASSERT_FAIL("Implement ResetDialogFields instead"); return 0;}
	virtual int InitializeFields() const {ASSERT_FAIL("Implement InitializeDialogFields instead"); return 0;}
	
protected:
	/** Should be overriden to initialize each widget in the dialog with its default value. 
			Default implementation is empty.

		@param context IN the active context
	*/
	virtual void  InitializeDialogFields(IActiveContext* context);
	
	/** Override to be called when the user clicks the "ok" (or equivalent) button.  
			Use ValidateFields to check that the data in each dialog control is valid and within limits.  
			It's up to the subclass to display an alert if invalid data is found.  
			If one or more of the fields have invalid data, return the WidgetID of the dialog item to select.  
			If all fields are valid, return kDefaultWidgetId.  When all fields are valid, the "ApplyDialogFields" function will be called.

		@param myContext IN the active context
		@return id of the first widget with invalid data
	*/
	virtual WidgetID			ValidateDialogFields(IActiveContext* myContext);

	/** Override to retrieve data from the widgets in the dialog and apply it. 
			By default the widget with id kOKButtonWidgetID causes an apply. Override Update to have others call "ApplyDialog"

		@param myContext IN the active context
		@param widgetId IN the widget that triggered the "apply"
	*/
	virtual void				ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
	
	/** Override to modify the default Reset behavior.
			Called when the user holds down the option/alt key and the cancel button changes to "Reset" and then clicks on the reset button. 
			By default, this function simply calls InitializeDialogFields. For most dialogs, this results in the correct behavior.

		@param myContext IN the active context
	*/
	virtual void				ResetDialogFields(IActiveContext* myContext);

public:
	/** Override to be called when the user clicks the "cancel" button.
			Default implementation is empty.
	*/
	virtual void				UserCancelled();

	/** Override to be called during the process of closing the dialog, an opportunity to do some special cleanup.
			Default implementation is empty.
	*/
	virtual void				ClosingDialog(IActiveContext* lastChanceToUseMyContext);

	// ----- Dialog query methods -----

	/** Returns kTrue if InitializeFields() has been called. */
	virtual bool16				HasBeenInitialized() const;

	/** Subclasses can call this to set the initialized state, instead of calling the inherited Initialize functions. */
	virtual void				SetInitialized(bool16 initialized);

	// ----- Owner query methods -----

	/**	Set the owner panel of this dialog.
		@param ownerPanel IN the owner panel
	*/
	virtual void				SetOwner(IControlView* ownerPanel);

	/** Get the owner panel of this dialog
		@return the owner panel, may return nil
	*/
	virtual IControlView*		GetOwner() const;

	// ----- Previewable dialog methods -----

	/** Override to supply the undo/redo name for the dialog. 
			This appears in the edit menu if the user hits "OK" in a previewable dialog.
			Default implementation returns the window title of the dialog window.
	*/
	virtual void				GetName(PMString& name);

	/**@name Dialog helper methods */
	//@{

	/** Set the text of a widget that has text control data. */
	virtual void				SetTextControlData(const WidgetID& widgetId, const PMString& text, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Get the text of a widget that has text control data. */
	virtual PMString			GetTextControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const;
									
	/** Set the value of a widget with an ITextValue interface. */
	virtual void				SetTextValue(const WidgetID& widgetId, const PMReal& value, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Get the value of a widget with an ITextValue interface. */
	virtual PMReal				GetTextValue(const WidgetID& widgetId, const IPanelControlData* panel = nil, bool16 *outParsingError = nil,bool16 *outIsBlank = nil) const;
	/** Set the control-state of a widget with an ITextValue interface. */
	virtual void				SetTextValueControlState(const WidgetID& widgetId, ITextValue::TextControlState controlState, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Get the control-state of a widget with an ITextValue interface. */
	virtual ITextValue::TextControlState		GetTextValueControlState(const WidgetID& widgetId, const IPanelControlData* panel = nil) const;
									// Helper methods for easily setting and getting the value from a
									// widget(editbox) that has an ITextValue interface
	
	/** Set the value of a widget that has boolean control data. */
	virtual void				SetBooleanControlData(const WidgetID& widgetId, bool16 isChecked, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Get the value of a widget that has boolean control data. */
	virtual bool16				GetBooleanControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const;

	/** Set the value of a widget that has tristate control data. */
	virtual void							SetTriStateControlData(const WidgetID& widgetId, bool16 isSelected, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Set the value of a widget that has tristate control data. */
	virtual void							SetTriStateControlData(const WidgetID& widgetId, ITriStateControlData::TriState triState, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	/** Get the value of a widget that has tristate control data. */
	virtual ITriStateControlData::TriState	GetTriStateControlData(const WidgetID& widgetId, const IPanelControlData* panel = nil) const;
	
	/** Get the selected widget in a cluster */								
	virtual WidgetID			GetSelectedClusterWidget(WidgetID cluster, const IPanelControlData* panel = nil);
	/** Set the selected widget in a cluster */								
	virtual void				SetSelectedClusterWidget(WidgetID clusterId, WidgetID widgetToSelect, const IPanelControlData* panel = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);

	/** Query for the list control data from a widget */								
	virtual IStringListControlData*	QueryListControlDataInterface(const WidgetID& widgetId, const IPanelControlData* panel = nil) const;

	/** Internal utility routine to do what it sez. */	
	virtual IPanelControlData*	QueryIfNilElseAddRef(const IPanelControlData* panel) const;

	/** This method is typically used in conjuntion with Validate() to
		select the widget that has "illegal" values.
	*/
	virtual void				SelectDialogWidget(const WidgetID& widgetId);

	/** Get the value of the "Preview Mode On" flag (used to be in CDialogObserver). */
	virtual bool16				GetPreviewModeOn();
	/** Set the value of the "Preview Mode On" flag (used to be in CDialogObserver). */
	virtual	void				SetPreviewModeOn(bool16 bOn);

	/** Query for the dialog context established when the dialog was initialized */
	virtual IActiveContext*		QueryDialogContext();
	//@}

private:
	bool16						fInitialized;
	IControlView*				fOwner;
	PMString					fName;
	bool16						fPreviewModeOn;
	IActiveContext*				fDialogContext;
};

#pragma export off

#endif
