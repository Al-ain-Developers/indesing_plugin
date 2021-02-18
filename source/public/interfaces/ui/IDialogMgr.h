//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDialogMgr.h $
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
#ifndef __IDialogMgr_h__
#define __IDialogMgr_h__

#include "IPMUnknown.h"
#include "IDialog.h"
#include "ShuksanID.h"

class IResourceAccess;
class RsrcSpec;
class IWindow;

/** Interface for the Dialog manager.
		The Dialog Manager interface is found on the Application boss object.

		@see IDialog
*/
class IDialogMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIALOGMGR };
		
		/** The following are const parameters for the CreateNewDialog method. Description
		    of how the parmeters function can be found in the documentation for CreateNewDialog.
			@see CreateNewDialog
		 */
	enum
	{
			kAllowMultipleCopies		= kTrue,
			kDontAllowMultipleCopies	= kFalse,
		
			kCacheDialog				= kTrue,
			kDontCacheDialog			= kFalse,
		
			kAllowUserResize			= kTrue,
			kDontAllowUserResize		= kFalse,
	};

	/** CreateNewDialog will create the specified dialog and return a pointer to the dialog. 
			Don't "AddRef" the pointer, the dialog will take care of destructing itself when the dialog is closed. 
			
			If "allowMultipleCopies" is true, this function will create another copy of the dialog if a previous copy of the dialog is currently open. 
			If "allowMultipleCopies" is false and the dialog is already open, the existing dialog is returned. 
			If the dialog is modeless, only one copy of the dialog can be opened at a time, regardless of the value of allowMultipleCopies.
		
			If okToCacheDialog is true, a cached copy of the dialog will be returned, if one exists. 
			If okToCacheDialog is false, the dialog will be reread from the specified resource.

		@param spec IN locator for the resource description
		@param dialogType IN the type of the dialog (kModal, kMovableModal, or kModeless)
		@param allowMultipleCopies IN can multiple copies of the dialog exist simultaneously
		@param okToCacheDialog IN can this dialog be cached, or must it be reread from disk.
		@param allowResize IN can this dialog be resized
		@return the dialog, or nil.
	*/
	virtual IDialog*	CreateNewDialog(const RsrcSpec& spec,
										const IDialog::DialogType& dialogType,
										bool16 allowMultipleCopies = kAllowMultipleCopies, 
										bool16 okToCacheDialog = kCacheDialog,
										bool16 allowResize = kDontAllowUserResize) = 0;

	/** Same as above version except specify the window class ID in addition to the dialog type (why? there is a 1 to 1 mapping)
	 
	 @param windowClass IN window class ID for the window (kModalWindowBoss, kMovableModalWindowBoss, or kModelessWindowBoss)
	 @param spec IN locator for the resource description
	 @param dialogType IN the type of the dialog (kModal, kMovableModal, or kModeless)
	 @param allowMultipleCopies IN can multiple copies of the dialog exist simultaneously
	 @param okToCacheDialog IN can this dialog be cached, or must it be reread from disk.
	 @param allowResize IN can this dialog be resized
	 @return the dialog, or nil.
	 */
	virtual IDialog*	CreateNewDialog(ClassID windowClass, const RsrcSpec& spec,
										const IDialog::DialogType& dialogType,
										bool16 allowMultipleCopies = kAllowMultipleCopies, 
										bool16 okToCacheDialog = kCacheDialog,
										bool16 allowResize = kDontAllowUserResize) = 0;
	
			/** @return kTrue if a modal dialog is current open (i.e. being displayed) */
	virtual bool16		IsModalDialogOpen() const = 0;

			/** @return kTrue if a modeless dialog is currently the frontmost window */
	virtual bool16		IsModelessDialogInFront() const = 0;
							
			/** @return kTrue if any type of dialog is currently the frontmost window */
	virtual bool16		IsAnyDialogInFront() const = 0;

			/** @return the IWindow of the frontmost dialog. If there are no dialogs,
				this function returns nil. */
	virtual IWindow*	GetFrontmostDialogWindow() const = 0;

	// ----- Internal Use -----
	virtual void		IncrementModalDialogCnt() = 0;
	virtual void		DecrementModalDialogCnt() = 0;
	virtual uint16		GetModalDialogCnt() const = 0;

			/** Suppress display of dialogs (by auto-pressing the default button).
				Does not suppress progress bars.
				@param suppress specifies whether to suppress dialogs
			*/
	virtual void		SetSuppressDialogs( bool16 suppress ) = 0 ;

			/** @return kTrue if dialogs are suppressed, kFalse otherwise
			*/
	virtual bool16		GetSuppressDialogs() const = 0 ;
	
#ifdef WINDOWS
	// Following set of APIs should be used by users to mark the opening and closing of clients own platform defined dialog.
	// While opening the dialog, clients should call PlatformWindowOpening and while closing the dialog PlatformWindowClosed.
	virtual void		PlatformWindowOpening() = 0;
	virtual void		PlatformWindowClosed() = 0;
	virtual bool16		IsPlatformWindowOpen() = 0;

	// Following APIs are used internally in Indesign to save the current focus control in the platform windows control.
	// And restore focus to the saved control
	// Clients should use this functions only if they want to save and restore the focus.
	virtual bool16		HasSavedFocusedPlatformWindow() = 0;
	virtual void		SaveFocusedPlatformWindow() = 0;
	virtual void		RestoreFocusToPlatformWindow() = 0;
#endif

	/* Internal Use */
	virtual uint64		ClearDialogInstanceList(bool16 reportMemoryUsed=kFalse) = 0;
	virtual bool16		CanProcessDelayedWaitForDialog(IDialog *iDialog) = 0;
	virtual void		ClearDialogFromInstanceList(IDialog* iDialog) = 0;
#ifdef WINDOWS
	virtual void		SaveFocusedExternalWindow() = 0;
	virtual void		RestoreFocusToExternalWindow() = 0;
#endif
};

#endif
