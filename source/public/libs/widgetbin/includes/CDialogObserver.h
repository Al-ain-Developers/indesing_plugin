//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CDialogObserver.h $
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
#ifndef __CDialogObserver__
#define __CDialogObserver__

#include "AbstractDialogObserver.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class IPanelControlData;
class IListControlData;

/**
	CDialogObserver should be used by the dialog which has OK/Cancel button.

	@see AbstractDialogObserver.h
*/

class WIDGET_DECL CDialogObserver : public AbstractDialogObserver
{
public:	
					CDialogObserver(IPMUnknown *boss);
	virtual			~CDialogObserver();
	
	/**
		Respond to a change in an observed subject. Just an implementation of Update function on IObserver interface.

		@see IObserver.h
	*/
	virtual void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	
	/**
		By default we attach and detach to the ok and cancel buttons.
		These are the widgets with ids kOKButtonWidgetID and kCancelButton_WidgetID.
		Override to attach to other buttons or widgets.
	*/
	virtual void	AutoAttach();
	virtual void	AutoDetach();

protected:	
	// ----- Dialog helper methods -----
	/**
		Closes the dialog window. This will release all objects associated with the dialog.

		@param windowAlreadyClosed kTrue if system window already been closed.
	*/
	virtual void	CloseDialog(bool16 windowAlreadyClosed = kFalse);

	/**
		Dialog Preview button support methods

		@param hitOK kTrue if dialog closed by click on OK button.
	*/
	virtual void	FireOffEndDialogCmd(bool16 hitOK);

	/**
		Set the dialog validation status, if bStatus true, dialog validation is failed, if bStatus false, dialog validation is fine
	*/
	void SetDialogValidationStatusFailed(bool16 bStatus = kTrue	) ;

	void SetCloseOnCancel(bool16 shouldCloseOnCancel = kTrue);

private:
	bool16			fIsDialogInitialized;
	bool16			fCloseOnCancel;
};

#pragma export off

#endif
