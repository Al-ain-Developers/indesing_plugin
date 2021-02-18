//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CAlert.h $
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
#ifndef __CAlert__
#define __CAlert__

#include "PMString.h"
#include "UIDRef.h"

#pragma export on

// Common Default String Constants (Don't worry, these get automatically translated)

#define	kOKString		"OK"
#define	kCancelString	"Cancel"
#define	kYesString		"Yes"
#define kNoString		"No"

#define kNotManaged		-1

#ifdef MACINTOSH
#define	kSaveButtonString			"Save"
#define kDontSaveButtonString		"Don't Save"
#else
#define	kSaveButtonString			kYesString
#define kDontSaveButtonString		kNoString
#endif

class AlertImplementation;

/** Class providing set of static methods to display alerts and control alert behaviour.
*/
class PUBLIC_DECL CAlert
{
public:
	// ----- CAlerts -----
	
	// These functions are truly modal CAlerts.  When one of these CAlert
	// function is called, an CAlert is displayed and control isn't returned
	// to the caller until the user dismisses the CAlert.
	
	/** Initialize the alert system.
		@param alertImpl Implementation class that handles alerts.
	*/
	static void			Initialize(AlertImplementation* alertImpl);
	
	/** Modal alert, displaying text plus eInformationIcon.  CAlert is displayed and control isn't returned
		to the caller until the user dismisses the CAlert.
		@param message text to display, which will be translated unless the string has been translated already or isn't translatable
	*/
	static void			InformationAlert(const PMString& message);
	static void			InformationAlert(const PMString& message, const UIDRef& target, ErrorCode errorCode);

	/** Modal alert, displaying text plus eWarningIcon.  CAlert is displayed and control isn't returned
		to the caller until the user dismisses the CAlert.
		@param message text to display, which will be translated unless the string has been translated already  or isn't translatable
	*/
	static void			WarningAlert(const PMString& message);
	static void			WarningAlert(const PMString& message, const UIDRef& target, ErrorCode errorCode);

	/** Modal alert, displaying text plus eErrorIcon.  CAlert is displayed and control isn't returned
		to the caller until the user dismisses the CAlert.
		@param message text to display, which will be translated unless the string has been translated already  or isn't translatable
	*/
	static void			ErrorAlert(const PMString& message);
	static void			ErrorAlert(const PMString& message, const UIDRef& target, ErrorCode errorCode);
		
	// ----- Flexible Alert Function -----

	typedef enum {  eNoIcon,  eInformationIcon,  eWarningIcon,  eErrorIcon,  eQuestionIcon } eAlertIcon;
		
	/** "ModalAlert" is really the all-powerful alert function.  ModalAlert lets you build a dynamically
		sized alert (based on the length of the message) that can have an optional icon and up to three
		buttons.  Furthermore, the function lets you specify which button is the "default" button.
		
		ModalAlert can display an alert with one, two, or three buttons.  There is 
		a PMString title for each string.  Pass in "kNullString" for no button.
		DO NOT CALL TRANSLATE on any of the button strings.  ModalAlert will
		automatically Translate all of the strings, including the message.  

		WARNING for Windows only: Presently, CAlert relies on the platform alert mechanism
		to display the dialog. Windows is weak in the titles of the buttons permitted in
		the alerts.  Only the standard Yes, No, Cancel, OK buttons are supported. This
		explains why when a program crashes, you get a dialog that says something like,
		"Hit OK to quit or Cancel to debug the application" rather than an alert with
		two buttons such as "Debug" and "Quit."  
		
		Unfortunately, our Windows alert mechanism
		is saddled with these same limitations.  That means that on Windows, you can't
		use custom button strings and any custom keyboard shortcut resource is ignored.
		I suppose if we had time, we could write our own implementation of Windows alerts.
		However, it appears that Windows users are used to alerts with only limited
		button names. If this is a severe limitation, come talk to me. Tom T.
		
		Note on linefeeds: The platform will break lines in the alert where it sees fit.
		On the Mac this works pretty well. On Windows, you can get some long skinny alerts.
		If you want more control, you can compose strings with carriage returns in them. To
		do this, use the kLineSeparatorString define in CoreResTypes.h. A sample string
		in a .fr file might look like this:
		e.g. "Here is a string" kLineSeparatorString "that takes up two lines."
		Resource compiler will combine into one string with a carriage return.

		@param message text to display
		@param button1String label for the 1st button on the alert
		@param button2String label for the 2nd button on the alert, or kNullString if no button required
		@param button3String label for the 3rd button on the alert, or kNullString if no button required
		@param defaultButton pass in 1, 2, or 3 to make that button the default button 
		@param iconID icon to display in CAlert, use eAlertIcon or resource id of other icon
		@return ModalAlert returns 1, 2, or 3, depending upon which button is clicked
	*/
	static int16		ModalAlert( const PMString& message,
									const PMString& button1String,
									const PMString& button2String,
									const PMString& button3String,
									int16 defaultButton,	
									int16 iconID			 
								  );
							 
									
	/** Additional arguments for ModalAlert to support ManagedErrors
	    @param target a UIDList of all the affected page items for this error. At the least, this should
		              contain the database of the document the error is attached to.
	    @param errorCode an error code number for this error. To be added later when full managed errors
		              are added in
	*/
	static int16		ModalAlert( const PMString& message,
									const PMString& button1String,
									const PMString& button2String,
									const PMString& button3String,
									int16 defaultButton,	
									int16 iconID,			 
									const UIDRef& target,
									const ErrorCode errorCode
								  );
							 
									

	/** For an alert offering end-user the chance to suppress 
		further occurrences of same dialog.

		WarningAlertWithDontShowAgain is actually a movable modal dialog
		with an extra checkbox control with the title "Don't show again."

		Utils<IShowAlertRegistryUtils>()->GetShouldShow(alertID) is called first to
		decide whether to continue with this routine or simply return.
		If the user selects the check box control, then 
		Utils<IShowAlertRegistryUtils>()->DoSetShouldShowCmd(alertID, kFalse) will be called
		after the dialog is closed.

		@param message text to display
		@param dontShowID use your pluginID + some constant
		@param bShowCancelButton if kTrue, display a Cancel button
		@param iconID  icon to display in CAlert, currently only support Information and Warning icon
		@param title default is "Information" for CAert::eInformationIcon, others "Warning"
		@param strOK the string to use for the ok button.  Null indicates use 'OK'
		@param strCancel the string to use for the cancel button.  Null indicates use 'Cancel'
		@param returnValueIfHidden	If the "Don't show again" checkbox was checked while the
			alert corresponding to 'dontShowID' was previously shown, or all alerts have been
			disabled, then 'returnValueIfHidden' will be returned.
		@return returnValueIfHidden value if the alert was not shown.  Otherwise, 1 for OK, 
				2 for OK + don't show, 3 for Cancel, 4 if showing cancel button and
				title of cancel button is not 'Cancel' and don't show is checked.
	*/
	static int16 		WarningAlertWithDontShowAgain(const PMString& message, 
									int32 dontShowID,		
									bool8 bShowCancelButton = kFalse,
									int32 iconID = eWarningIcon,			
									const PMString& title = kNullString,
									const PMString& strOK = kNullString,
									const PMString& strCancel = kNullString,
									const int16 returnValueIfHidden = 1	// OK
									);
							
	/** For an alert offering end-user the chance to apply this choice to similar dialogs that are coming

		AlertWithApplyToAll is actually a movable modal dialog
		with an extra checkbox control with the title "Apply to All"

		@param applyAllState boolean to set the initial state of the checkbox. Filled out with the final state of the checkbox before return
		@param message text to display
		@param Button1Str the string to use for the first button. This is always the default button.
		@param Button2Str the string to use for the second button
		@param Button3Str the string to use for the third button
		@param iconID icon to display in CAlert, use eAlertIcon or resource id of other icon
		@param title default is "Information" for CAert::eInformationIcon, others "Warning"
		@return 1 if the user chose button 1, 2 for button2, 3 for button3
	*/
	static int16 	AlertWithApplyToAll(bool16 *applyAllState, // pass the initial state, and get the result of the applyall checkbox
									const PMString& message, 
									const PMString& Button1Str = kNullString,
									const PMString& Button2Str = kNullString,
									const PMString& Button3Str = kNullString,
									const PMString& title = kNullString,
									int32 iconID = eWarningIcon		
									);
							
	/** Function to control the display of alerts. Some plugins, such as scripting and testing,
		have a need to turn alerts on and off.
		If "showAlert" is kFalse, no alerts will be displayed. In that case, ModalAlert will
		always return the parameter passed into "defaultButton" as the button clicked on that
		dismissed the dialog.

		@param showAlerts specifies whether to show alerts to the user.
	*/
	static void			SetShowAlerts(bool16 showAlerts);
	
	/** @return kTrue if alerts are to be shown to the user, kFalse otherwise
	*/
	static bool16		GetShowAlerts();
	
	/** @return kTrue if it is okay to be displaying modal UI during launch (e.g. a registration dialog), or 
			kFalse otherwise.  This function will return kFalse if GetShowAlerts() returns kFalse.  If you
			place a cookie (a folder called "NoModalStartupUI") on the root volume / C: drive, this function
			will also return kFalse.
	*/
	static bool16		GetShowModalStartupUI( );

	/** @return kTrue if an alert is currently shown to the user, kFalse otherwise
	*/
	static bool16		GetIsAlertShown();

	/** Specify that the last event caused an alert.
	*/
	static void	SetLastEventCausedAlert(bool16);

	/** @return kTrue if the last event we processed caused an alert, kFalse otherwise
	*/
	static bool16	LastEventCausedAlert();
		

	/** Identical to ErrorAlert, but can be called before the object model has been initialized.
		@param message text to display
	*/
	static void			StartupErrorAlert(const PMString& message);
		 
	/**
	*/
	static void			StartupWarningAlert(const PMString& message);

	// There were only two clients of the old StartupModalAlert and the API is too complex to support
	//	given that all they needed were Yes/No and Yes/No/Cancel.
	
	/** Identical to ModalAlert, but can be called before the object model has been initialized.
	 Note that because WidgetBin/DVWidgetBin initialize later in startup,
	 alerts during the startup process have to rely on the underlying platform alert mechanisms.
	 @param message text to display
	 @param buttonConfig button configuration, limited to one the choices in eStartupAlertButtonConfig
	 @param defaultButton pass in 1, 2, or 3 to make that button the default button
	 @param icon to display in CAlert, use eAlertIcon or resource id of other icon
	 @return which button dismissed the dialog.
	 */
	enum {  eOKOnly,  eYesNo,  eOKCancel,  eYesNoCancel } eStartupAlertButtonConfig;
	
	static int16		StartupModalAlert( const PMString& message,
									int16 buttonConfig = eOKOnly,
									int16 defaultButton = 1,	
									int16 iconID = eWarningIcon		 
								  );
		

	/** Set the ignore refresh.  Allows modal dialogs in the middle
		of drawing - otherwise bad things can sometimes happen. Bug #1217680.
		Currently this is ignored for Windows.
		NOTE: Caller is responible for resetting the value!
	*/
	static void SetIgnoreRefreshEvent(bool16 val);

	/** Return 'true' if the ignore refresh flag is set.
	*/
	static bool16 GetIgnoreRefreshEvent();
public:
	static IDThreading::ThreadLocal<bool16>				tl_AlertShown;
private:
	static IDThreading::ThreadLocal<bool16>				tl_ShowAlerts;
	static IDThreading::ThreadLocal<bool16>				tl_LastEventCausedAlert;
	static bool16										ts_ShowModalStartupUICookie;
	static bool16										ts_ShowModalStartupUI;
	static IDThreading::ThreadLocal<bool16>				tl_IgnoreRefreshEvent;	
	static AlertImplementation*							ts_AlertImpl;

};

#pragma export off

#endif
