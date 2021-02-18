//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IStyleGroupListControlData.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __IStyleGroupListControlData_h__
#define __IStyleGroupListControlData_h__

#include "widgetid.h"

//========================================================================================
// CLASS TEMPLATE IStyleGroupListControlData
//========================================================================================

class IStyleGroupListControlData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISTYLEGROUPLISTCONTROLDATA };

	// Initialization	
	/** Sets the workspace that will be used to fill up this style set list, If not set
		Active workspace will be used.
		@param	workpsace [IN]	workspace to setup.
	*/
	virtual void		SetupWorkspace(const UIDRef& workspace) = 0;

	/** Adds the interfaceID of the style set manager to be used for this style set list.
		You can add more than one style set manager id by calling this method more than once
		@param whichInterface [IN] style set manager interface id. e.g. IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER, etc.
	*/
	virtual void		AppendInterfaceID(const PMIID& whichInterface) = 0;

	/** Removes the interfaceID, which has been added in previous call
		@param	whichInterface [IN] style set manager interface id to remove.
	*/
	virtual void		RemoveInterfaceID(const PMIID& whichInterface) = 0;

	/** Set the style which will be selected by default.
		@param selectedStyle [IN] style to be selected by default.
	*/
	virtual void		SetupSelectedStyle(UID selectedStyle) = 0;

	/** Returns the workspace which has been setup. The active workpsace is returned it has not be setup.
		@return The workpace for the style set list.
	*/
	virtual UIDRef		GetWorkspace() const = 0;

	/** Returns the style set manager interface id.
		@return The style set manager interface id. e.g. IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER, etc.
	*/
	virtual K2Vector<PMIID>	GetInterfaceIDList() const = 0;
	
	/**	Select a particular style
		@param whichStyle - UID of the style to select (kInvalidUID will select nothing in the list)
		@return none
	 */
	virtual void		Select(UID whichStyle, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**	Get the UID of the selected style
		@param none
		@return UID - UID of the selected style
	 */
	virtual UID			GetSelectedStyle() const = 0;

	/** Builds the Style set list based on the currently setup workspace and Style set manager id.
		@param	skipRootStyle [IN] Pass kTrue if root style needs to be skipped
	*/
	virtual void		BuildList(bool16 skipRootStyle = kFalse) = 0;

	/** Sets if the styles icons resource to be shown for styles 
		@param ssmIID [IN] the style set manager id for which the icon is to be set
		@param styleIcon [IN] The style icon resource id
	*/
	virtual void SetStyleIconResource(const PMIID& ssmIID, const PMRsrcID& styleIcon) = 0;

	/** Returns the sytle icon resource styles icons will be shown.
		@param ssmIID [IN] The style set manager id
		@return the style icon resource id.
	*/
	virtual PMRsrcID GetStyleIconResource(const PMIID& ssmIID) const = 0;

	/** Returns kTrue if the list has been built already by BuildList(), kFalse otherwise
	*/
	virtual bool16 IsListSetup() const = 0;

	/** Adds a custom element to the list, These are not part of the style set hierarchy,
		@param	elementName [IN] the element name to add.
		@param addAtTop [IN] pass kTrue if the custome element is to be added at top, kFalse if 
									element is to be added at bottom.
		@param	iconRsrcId [IN] icon resource id if any icon need to be displayed with this custome element
		@param	iconPluginId [IN] plugin id of the icon resource.
	*/
	virtual void	AddCustomElement(const PMString& elementName,bool16 addAtTop = kTrue, RsrcID iconRsrcId = 0, PluginID iconPluginId = kInvalidPlugin) = 0;
	
	/** Remove the custom element from the list.
		@param	elementName [IN] the element to be removed.
	*/
	virtual bool16	RemoveCustomElement(const PMString& elementName) = 0;

	/** Returns the custom element name if one is selected. 
		If normal style is selected then it returns Empty String.
		@return Selected Custom element name.
	*/
	virtual PMString GetSelectedCustomElement() const = 0;

	/** Selects a custom element
		@param elementName [IN] custom element name to select
	*/
	virtual void	SelectCustomElement(const PMString& elementName, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Get the icon resource for the cusom element if set.
	*/
	virtual PMRsrcID GetCustomElementIconResource(const PMString& elementName) const = 0;

	/** Resets all the previous info. Will need to set everything again to build it.
	*/
	virtual void	ResetAll() = 0;

	/** Adds a child type to the hierarchy which is searched while building the tree
	*/
	virtual void	AppendChildTypeIID(const PMIID& childType) = 0;
};

#endif // __IStyleGroupListControlData_h__
