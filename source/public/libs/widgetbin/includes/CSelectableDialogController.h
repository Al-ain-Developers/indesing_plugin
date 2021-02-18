//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CSelectableDialogController.h $
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
#ifndef __CSelectableDialogController__
#define __CSelectableDialogController__

#include "CDialogController.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class IActiveContext;
class WIDGET_DECL CSelectableDialogController : public CDialogController
{
public:
	// ----- Initialization -----
	
						CSelectableDialogController(IPMUnknown *boss);
	virtual				~CSelectableDialogController();
	
	// ----- Dialog protocol -----

	virtual void		ResetDialogFields(IActiveContext* myContext);
							
	virtual WidgetID	ValidateDialogFields(IActiveContext* myContext);
							// This function is called when the user clicks the "ok" (or equivalent)
							// button.  Override ValidateFields to check that the data in each
							// dialog control is valid and within limits.  It's up to the subclass
							// to display an alert.  If one or more of the fields have invalid data,
							// return the WidgetID of the dialog item to select.  If all fields are
							// valid, return kDefaultWidgetId.  When all fields are valid, the 
							// "ApplyFields" function will be called.
	
	virtual void		ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);
							// Should be overridden to retrieve data from the widgets in the
							// dialog and apply it. The widget that caused the apply is passed
							// in 'widgetId. By default the widget with id kOKButtonWidgetID causes
							// an apply. Override Update to have others call ApplyFields.
	
	virtual void		UserCancelled(); 
							// This function is called when the user clicks the "cancel" button.
							// Override if the dialog needs to know when this happens.

	virtual void		ClosingDialog(IActiveContext* lastChanceToUseMyContext);
							// In ClosingDialog, we unload any panels that were not auto loaded..

	// ----- Dialog helper methods -----

	virtual void		SelectDialogWidget(const WidgetID& widgetId);
};

#pragma export off

#endif
