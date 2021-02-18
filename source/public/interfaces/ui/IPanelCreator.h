//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelCreator.h $
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
#ifndef __IPanelCreator__
#define __IPanelCreator__

#include "IPMUnknown.h"
#include "K2Vector.h"

class IControlView;

/** Interface that is required to be implemented when adding panels to selectable dialog.
*/
class IPanelCreator : public IPMUnknown
{
public:
	/** Creates the panel.  
		@param dialogServiceID  the service id of
		the dialog that the panel is being created for.
	*/
	virtual IControlView*		CreatePanel(const ServiceID dialogServiceID, bool16 isDialogPanel = kFalse) = 0;
	
	/** Creates the Dialog panel (for Selectable Dialogs, etc).
	 @param dialogServiceID  the service id of
	 the dialog that the panel is being created for.
	 */
	virtual IControlView*		CreatePanelForDialog(const ServiceID dialogServiceID) = 0;
								
									
	/** Returns list of serviceIDs of selectable dialogs
		that this dialog panel can be installed in.
		@param serviceIDs OUT parameter holding list of selectable dialog service IDs that
			this panel can be installed in
	*/
	virtual void				GetServiceIDs(K2Vector<ServiceID>& serviceIDs) = 0;
								 

		
	/** Returns the resource id of the panel that is used in finding the
		service ids resource and the panel view resource.
		@return resource ID of panel for resources.
	*/
	virtual	RsrcID				GetPanelRsrcID() const = 0;
									 
		
	/** Determine whether panel created should be made visible when dialog in service ID list is shown.
	
		If AutoShowPanel returns true, the panel created by this class is
		automatically made visible whenever a selectable dialog that this class
		has registered for (via GetServiceIDs()) is opened. If AutoShowPanel
		returns false, the panel is not made visible nor is listed in the popup and it will
		have to be shown by calling ISelectableDialogSwitcher::ShowDialogPanel().
		@return kTrue if panel should be created when a dialog in the list of service IDs is
			shown
	*/
	virtual	bool16				AutoShowPanel() const = 0;
									// 
};

#endif
