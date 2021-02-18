//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinksUIUtils.h $
//  
//  Owner: lance bushore
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
#ifndef __ILinksUIUtils__
#define __ILinksUIUtils__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksUIID.h"
#include "AppInfo.h"
#include "NodeID.h"

class ILink;
class ILinkResource;
class ILinkInfoProvider;
class IMetaDataAccess;
class IImageCache;

 namespace LinksUIUtils
 {
 	const int kLinksUIColumnGap = 8;
 };
 
 
/**
	Utility interface to interact with links panel. Provides access to various routines that may be generally useful.
	@see ILinkInfoProvider, ILinksUIPanelPrefs
 */
class ILinksUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKSUIUTILS };

	/** Given a list of link UIDs, select the corresponding rows in the links panel 
		@param inLinkUIDsToSelect - UID's of links to select
	*/
	virtual void SelectLinksInPanel(const UIDList& inLinkUIDsToSelect) = 0;
	
	/** Returns a list of Link UIDs corresponding to the selected rows in the links panel
		@param inDisplayOrder - in the order of their display in the links panel
		@return - list of UID's of selected links
	*/	
	virtual UIDList GetLinksSelectedInPanel(bool16 inDisplayOrder = kFalse) = 0;
	
	/** Returns a list of LinkResource UIDs corresponding to the selected rows in the links panel 
		@param inDisplayOrder - in the order of their display in the links panel
		@return - list of UID's of resources selected in the links panel
	*/	
	virtual UIDList GetLinkResourcesSelectedInPanel(bool16 inDisplayOrder = kFalse) = 0;
	
	/** if widget is in selected links, it returns the selected links, if not, it returns the link represented by the widget 
		@param widget - widget that was clicked on for the menu. This could be a row inside or outside the selection
		@param inDisplayOrder - in the order of their display in the links panel
		@return list of selected links or the link represented by widget if widget is outside the selection
	*/
	virtual UIDList GetLinksForMenuAction(IPMUnknown* widget, bool16 inDisplayOrder = kFalse) const = 0;

	/** returns true if at least one of the links in the passed in list are editable 
		@param linkList - list of UID's of links
		@return true if one or more links are editable. An example of an un-editable link would be an embedded link.
	*/
	virtual bool16 SomeCanEdit(UIDList &linkList) = 0;

	/** returns true if at least one of the links in the passed in list are openable in InDesign i.e. are SharedContent links. 
		@param linkList - list of UID's of links
		@return true if one or more links can be opened.
	*/
	virtual bool16 SomeCanGoToSource(UIDList &linkList) = 0;

	/** Examines panel selection and passed in panel widget to determine if the current panel selection + passed in widget suggests that menus should work on LinkResources, as opposed to Links 
		@param widget - Widget under the click for the menu.
		@return true if widget or selection is comprised only of link resources.
	*/
	virtual bool IsMenuActionEntirelyOnLinkResourceRows(IPMUnknown* widget) = 0;
	
	/** Gets a list of apps which might be able to edit the passed in link resources 
		@param appList - [out] list of applications registered for editing the link resource files.
		@param resources - list of UID's of link resources you want the editors for.
	*/
	virtual void GetEditOriginalEditorList(AppInfoList& appList, UIDList &resources) = 0;

	/** Attempts to edit the resource associated with the passed in link, using either the default editor or the one passed in. 
		@param link - link to edit in an external application
		@param appInfo - application to use to edit the link. if kNullAppInfo, then use the default application 
	*/
	virtual void EditOriginal(ILink *link, const AppInfo& appInfo = kNullAppInfo) = 0;

	/** Attempts to open the resource associated with the passed in link.
		@param link - link to open in InDesign.		
	*/
	virtual void GoToSource(ILink *link) const = 0;

	/** Gets the UIDRef for the link selected in the window. If there are no links selected, or multiple links selected, this returns kInvalidUIDRef 
		@return UIDRef of selected link or kInvalidUIDRef if there is 0 or multiple links selected
	*/
	virtual UIDRef GetSingleLinkUIDRefSelectedInLayout() const = 0;

	/** Gets the UIDRefs for the links selected in layout. If there are no links selected, this returns an empty list 
		@return list of UID's of links selected in the layout window. The list can be empty.
	*/
	virtual UIDList GetLinkUIDsOfSelectedItems() const = 0;

	/** Gets the UIDRefs for the resources selected in layout. It returns no duplicates. 
		@param links - links you want the resource of
		@return a list of UID's of resources associated with the links. Duplicates are removed.
	*/
	virtual UIDList GetResourcesOfLinks(UIDList &links) const = 0;

	/** Calls edit original for first link that refers to each resource in the list. 
		@param links - links to edit in an external application
		@param resources - resources associated with the links in links. use GetResourcesOfLinks to get the list of resources.
		@param appInfo - application to use to edit the links. if kNullAppInfo, then use the default applications
	*/
	virtual void EditAllOriginals(UIDList &links, UIDList &resources, const AppInfo& appInfo = kNullAppInfo) const = 0;

	/** Calls GoToSource for first link that refers to each resource in the list. 
		@param links - links to open
		@param resources - resources associated with the links in links. use GetResourcesOfLinks to get the list of resources.		
	*/
	virtual void GoToAllSources(UIDList &links, UIDList &resources) const = 0;

	/** show/hide link info section. If onlyShow bool is true, it will not toggle visible to hidden 
		@param onlyShow - if true, it only shows and doesn't hide
		@param fitSizeToAvailableInfo - true to resize based on content
	*/
	virtual void ToggleLinkInfoSectionVisibility(bool onlyShow, bool fitSizeToAvailableInfo) = 0;
	
	/** Updates the state of the link info show/hide button. The icon switches to indicate if it's showing or hiding. 
	*/
	virtual void UpdateLinkInfoSectionButtonState() = 0;
	
	/** Set a new sort provider for the links panel 
		@param newSortProvider - new sort provider
	*/
	virtual void SetPanelSortProvider(const ILinkInfoProvider* newSortProvider) = 0;
		
	/* Unembed the passed in Links, by presenting the user with a browse to file dialog. returns true if it worked, false if not. false usually indicates user cancel. 
		@param targetLinks - links to unembed
		@param updateLink - if true, update the link
		@return true if it worked, false if not. false usually indicates user cancel.
	*/
	virtual bool16 DoUnembedSelectedLinks(const UIDList& targetLinks, bool16 updateLink) const = 0;
	
	/** Query for the ILinkInfoProvider associated with this header widget. If this is not a header widget, will return nil 
		@param widget - header widget
		@return - ILinkInfoProvider for the header or nil if this isn't a header.
	*/
	virtual const ILinkInfoProvider* QueryLinkInfoProviderFromHeaderWidget(const IPMUnknown* widget) = 0;

	/** Query for the ILinkInfoProvider associated with this widget in a row in the tree. If this is not a widget in the tree row, will return nil 
		@param widget - widget in a tree row
		@return - ILinkInfoProvider for the widget or nil if this isn't in a tree row.
	*/
	virtual ILinkInfoProvider* QueryInfoProviderFromLinksUIWidget(const IPMUnknown* widget) const = 0;
	
	/** Query for the ILink associated with this widget in a row in the tree. If this is not a widget in the tree row, will return nil 
		@param widget - widget in a tree row
		@return - ILink for the widget or nil if this isn't in a tree row.
	*/
	virtual ILink* QueryLinkFromLinksUIWidget(const IPMUnknown* widget) const = 0;
	
	/** Query for the ILinkResource associated with this widget in a row in the tree. If this is not a widget in the tree row, will return nil 
		@param widget - widget in a tree row
		@return - ILinkResource for the widget or nil if this isn't in a tree row.
	*/
	virtual ILinkResource* QueryLinkResourceFromLinksUIWidget(const IPMUnknown* widget) const = 0;
	
	/** Given a link UIDRef, this creates a Node which will match the existing node in the tree for this link 
		@param linkUIDRef - UIDRef of the link to create a node for 
		@return - Node that represents the link
	*/
	virtual NodeID_rv CreateNodeFromLinkUIDRef(UIDRef linkUIDRef) = 0;

	/** Given a link UIDRef, this returns an addref'd IMetaDataAccess, if one can be found 
		@param link - UIDRef of a link
		@return IMetaDataAccess for that link or nil if not found
	*/
	virtual IMetaDataAccess* QueryMetaDataAccessFromLink(const ILink* link) const = 0;

	/** Queries for  an IImageCache for the given link,linkresource combination. May return nil. 
		@param theLink - an ILink for a link
		@param linkResource - an ILinkResource for a link resource
		@return - an IImageCache for the given link,linkresource combination. May return nil.
	*/
	virtual IImageCache* QueryThumbnailForLink(const ILink * theLink, const ILinkResource * linkResource) const = 0;

	/** Sets up a new row widget for the caption setup dialog */
	virtual void SetupCaptionRowWidget(const IPMUnknown* newRowWidget,const PMString& beforeString, const PMString& providerName,const PMString& afterString) const = 0;
	

};

#endif 