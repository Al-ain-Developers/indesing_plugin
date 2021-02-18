//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/cpanelcreator.h $
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
#ifndef __CPanelCreator__
#define __CPanelCreator__

#include "IPanelCreator.h"
#include "HelperInterface.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/** Partial implementation of IPanelCreator. Subclass should override GetPanelRsrcID at least.
*/
class WIDGET_DECL CPanelCreator : public IPanelCreator
{
public:
	/** Constructor.
		@param boss refers to object on which this interface is aggregated
	*/
	CPanelCreator(IPMUnknown *boss);
	
	/** Destructor
	*/
	virtual					~CPanelCreator();
	
	/** Creates the panel.  
		@param dialogServiceID  the service id of
		the dialog that the panel is being created for. 
	*/
	virtual IControlView*		CreatePanel(const ServiceID dialogServiceID, bool16 isDialog = kFalse);
	
	/** Creates the Dialog panel (for Selectable Dialogs, etc).
	 @param dialogServiceID  the service id of
	 the dialog that the panel is being created for.
	 */
	virtual IControlView*		CreatePanelForDialog(const ServiceID dialogServiceID);
							
	/** Returns list of serviceIDs of selectable dialogs
		that this dialog panel can be installed in.
		@param serviceIDs OUT parameter, holding list of IDs of selectable dialogs
	*/
	virtual void			GetServiceIDs(K2Vector<ServiceID>& serviceIDs);
								
		
	/** Returns the resource id of the panel that is used in finding the
		service ids resource and the panel view resource.
		@return resource ID containing service IDs resource and panel-view resource
	*/
	virtual	RsrcID			GetPanelRsrcID() const;
							

	/** If AutoShowPanel returns true, the panel created by this class is
		automatically made visible whenever a selectable dialog that this class
		has registered for (via GetServiceIDs()) is opened. 
		
		If AutoShowPanel
		returns false, the panel is not made visible nor is listed in the popup and it will
		have to be shown by calling ISelectableDialogSwitcher::ShowDialogPanel().
		This function returns true by default.
		@return kTrue if panel should be automatically made visible when selectable dialog in list
			that this can be located in is shown, kFalse if an explicit 
			ISelectableDialogSwitcher::ShowDialogPanel message required to show panel created by this type.
	*/
	virtual	bool16			AutoShowPanel() const	;
							

protected:
	/** Determine view resource ID given a service ID.

		Given a dialogServiceID, GetPanelViewRsrcID returns
		the corresponding resource id of the panel view that should
		be used to create the panel. If you want different views
		depending upon which dialog your panel gets installed in,
		create a IDListPair resource with the id the class of the
		panel creator.  The list pairs list the dialog service ids
		and the resource id to use when creating the panel.  If this
		resource doesn't exist or the dialog service id can't be
		found in the resource, this function returns 0.
		@param dialogServiceID
		@param rsrcID OUT parameter, holding resource ID for given dialogServiceID
		@param pluginID OUT parameter, holding plug-in ID where resource is located
	*/
	virtual void			GetPanelViewRsrcID(const ServiceID dialogServiceID, RsrcID& rsrcID, PluginID& pluginID);
							

	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
