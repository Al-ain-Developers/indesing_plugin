//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDialog.h $
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
#ifndef __IDialog__
#define __IDialog__

#include "IPMUnknown.h"
#include "IControlView.h"
#include "ICursorMgr.h"
#include "widgetid.h"

/**	Main interface for dialogs. This interface is usually on the same boss as the dialog window, which is a parent of the dialog controller boss. @see IDialogMgr
*/
class IDialog : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIALOG };

	/** Dialog Type */
	enum DialogType 
	{ 
		/** Modal dialog which is not movable. Stops all user action until dismissed. */
		kModal = 0, 
		/** Modal dialog which is movable. This is the most common type. Stops all user action until dismissed */
		kMovableModal,
		/** Modeless dialog. Similar to a palette. User can interact with other UI while this type of dialog is displayed */
		kModeless
	};
	
	/** Set the type of the dialog. No effect if called after the dialog has been shown
	*/
	virtual void				SetDialogType(DialogType dialogType) = 0;
	
	/**	Get the type of the dialog
	*/
	virtual DialogType			GetDialogType() const = 0;

	/**	Place the dialog on the screen. You can pass in the owner panel (i.e. the panel who opens the dialog). This will make the panel
		available in the dialog controller.  OpenWithModalCursorType allows for non standard modal cursor behavior to be specified.
		Open by default now calls WaitForDialog(kFalse) i.e. not supressing the scheduled commands.
		@param ownerPanel The panel which opened this dialog.
		@param doWait kFalse if you want to override the default wait behavior, and call WaitForDialog yourself.
	*/
	virtual void				Open(IControlView* ownerPanel = nil, bool16 doWait = kTrue) = 0;

	/**	Place the dialog on the screen. OpenWithModalCursorType allows for non standard modal cursor behavior to be specified.
		@param modalCursorType A constant indicating which modal cursor to use. @see ICursorMgr
		@param ownerPanel The panel which opened this dialog.
	*/
	virtual void				OpenWithModalCursorType(int16 modalCursorType, IControlView* ownerPanel = nil) = 0;

	/**	Remove the dialog from the screen.
	*/
	virtual void				Close() = 0;

	/** WaitForDialog takes control of the event loop until the dialog is dismissed. In other words, once WaitForDialog is called,
		control will not be returned until the dialog is dismissed. This actually starts up another event loop. Use sparingly.
	    @param bSuppressScheduled Set to true to supress the processing of scheduled commands in the event loop, which in 
	      some cases could help supress processing and/or dialogs that have been scheduled but are unwanted while the current dialog
	      is being displayed.
	*/
	virtual void				WaitForDialog(bool16 bSupressScheduled = kFalse) = 0;

	/**	Check if we should buffer commands for this dialog. @see SetBufferCommands
	*/					
	virtual bool16				GetBufferCommands() const = 0;

	/**	This function helps in converting a panel into a modal dialog. Most of the controls in a panel have an observer that fires off a command
		when the control is actuated. When a panel is converted into a modal dialog, the developer would have to remove each of these
		observers and create a dialog observer that fires off a command when the user hits the dialog's ok button.	
		In order to save the developer a lot of time, simply call this function BEFORE calling Open.  The result will be that the dialog	
		command manager will buffer all the commands fired off by the individual commands.  If the user hits "ok", all the commands	
		will be combined into a single compound command and executed.	
		@param bufferCommands Should we buffer commands for this dialog?
	*/					
	virtual void				SetBufferCommands(bool16 bufferCommands) = 0;

	/** Dialog Position enums 
		kNoPosition doesn't move the dialog at all on open. Client must specify position.
		kAutoCenter centers the dialog on the main monitor. Default for first time dialog comes up.
		kCenterNearTop centers the dialog near top of screen (1/4 of the way down). Use for progress bars.
		kRememberPosition is the default positioning algorithm if one is not specified before opening the dialog. 
			If dialog has never been moved by user, or first time dialog opens, kAutoCenter logic is used. 
	*/
	enum DialogPosition { kNoPosition = 0, kAutoCenter, kCenterNearTop, kRememberPosition };
	
	/**	You must call this function BEFORE calling Open() if you want to change the window positioning algorithm used when we open the dialog window.
	*/
	virtual void				SetDialogPositioningAlgorithm(DialogPosition dialogPosition) = 0;

	/**	Check the dialog positioning algorthim.
	*/
	virtual DialogPosition		GetDialogPositioningAlgorithm() const = 0;

	/**	Dialog Item Focus 
		kFirstTextBox is the default focusing algorithm. This means that when the dialog
		is opened, the first visible enabled textbox (if there is one) will get the
		keyboard focus. kNoAutoFocus tells the dialog not to grab the keyboard focus at all.
	*/	
	enum DialogFocus { kNoAutoFocus = 0, kFirstTextBox };

	
	/**	You must call this function BEFORE calling Open() if you want to change the key focus algorithm used when we open the dialog window.
	*/
	virtual void				SetDialogFocusingAlgorithm(DialogFocus dialogFocus) = 0;
	
	/** 	Check the current dialog keyfocus algorithm
	*/								
	virtual DialogFocus			GetDialogFocusAlgorithm() const = 0;

	/**	Returns true if the dialog is currently open
	*/
	virtual bool16			IsOpen() const = 0;
							
	/**	Returns true if the dialog has a preview button
	*/
	virtual bool16			HasPreviewButton() const = 0;
	
	/**	Returns the main dialog panel installed in the dialog window. You can use the returned controlview to get to your
		dialog observer and controller.
	*/
	virtual IControlView*	GetDialogPanel() const = 0;

	/**	Associate default action to push button. Usual values for actionButUsually called like so:
		<pre>
		iDialog->SetDefaultButton(kMyCustomOKButtonWidgetID);
		</pre>
		@param buttonID WidgetID of the newdefault button for the specified action
		@return old default button widget ID
	*/
	virtual WidgetID		SetDefaultButton(const WidgetID buttonID) = 0;

	/**	Check which widget a default action is assigned to
	 @return WidgetID of the default button for the specified action
	 */
	virtual WidgetID		GetDefaultButton() const = 0;
	
	
	/** Press the default button, if any. If none, simply cancel and close the dialog.
	*/
	virtual void			PressDefaultButton() = 0 ;

	/** Called before the dialog is closed. Custom dialog impls can do clean up in this method
	*/
	virtual void			CleanUpBeforeClose() = 0;

	/** Called after the dialog is closed. Custom dialog impls can do clean up in this method
	*/
	virtual void			CleanUpAfterClose() = 0;

	/** Internal use only
	*/
	virtual void			SetDialogPanelID(const WidgetID panelID) = 0;
	
	/**	Called if the dialog was cancelled. Custom dialog impls can implement this to do cleanup.
	*/
	virtual void			DialogCancelled() = 0;


	/**	If this is called with kTrue, the dialog is completely deleted out of saved data when the dialog is closed. This is used when creating the 2..nth copies of
		 an open dialog. Rarely needed by client code.
	*/
	virtual void			SetDeleteOnClose(bool16 deleteOnClose) = 0;

	/**	Returns the flag set by SetDeleteOnClose. By default, this function returns kFalse.
	*/
	virtual bool16			GetDeleteOnClose() const = 0;

	/* Internal Use */
	virtual void			PostDelayedWaitForDialog() const = 0;

	/** Adds the gripper icon at corners for resizable dialogs
	*/
	virtual void AddResizingGripperIcon() = 0;
};

#endif
