//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/IRelinkUtils.h $
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
#ifndef __IRelinkUtils__
#define __IRelinkUtils__

// ----- Includes -----
#include "IPMUnknown.h"
#include "ILink.h"
#include "ILinkResource.h"
#include "ImportExportUIID.h"
 
/**
	Utility interface to interact with links panel. Provides access to various routines that may be generally useful.
	@see ILinkInfoProvider, ILinksUIPanelPrefs
 */
class IRelinkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRELINKUTILS };
	
	/* Allow the user to choose a folder to relink the passed in links to */
	virtual void DoRelinkToFolder(const UIDList& targetLinks) const = 0;
		
	/* Allow the user to choose an extension to relink the passed in links to */
	virtual void DoRelinkFileExtension(const UIDList& targetLinks) const = 0;
		
	/* Relink the passed in links, by presenting the user with a browse to file dialog. returns true if it worked, false if not. false usually indicates user cancel. 
	@param targetLinks - a list of ILink UIDs you want the user to relink.
	@param appendToTitleStr - a string to append to the default title of the relink dialog(the default title is the path to the original link resource)
	@param resultingLinks - a UIDList to hold the new ILink UIDs.
	*/
	virtual bool16 DoRelinkSelectedLinks(const UIDList& targetLinks,LinkClientID whichClientID, UIDList* resultingLinks = nil, const PMString& appendToTitleStr = kNullString) const = 0;
	
	/* Relink the passed in LinkResource, by presenting the user with a browse to file dialog. returns true if it worked, false if not. false usually indicates user cancel. */
	virtual bool16 DoRelinkSelectedLinkResources(const UIDList& targetResources,LinkClientID whichClientID, const PMString& appendToTitleStr=kNullString) const = 0;
    
	/* Relink the passed in LinkResource with a cloud asset by presenting the CC Libraries panel in the mode where user can select an asset to relink to*/
	virtual bool16 DoRelinkSelectedLinkResourcesWithCloudAssets(const UIDList& targetResources, LinkClientID whichClientID) const = 0;
    
	/* Relink the passed in links with a cloud asset by presenting the CC Libraries panel in the mode where user can select an asset to relink to.
	@param targetLinks - a list of ILink UIDs you want the user to relink.
	*/
	virtual bool16 DoRelinkSelectedLinksWithCloudAssets(const UIDList& targetLinks, LinkClientID whichClientID) const = 0;
	
	/* Relink the passed in link/linkResource with the cloud asset which is represented by the elementRef passed as an argument.
	@param elementRef - unique identifier of the cloud asset to relink to.
	@param link - the link which is to be relinked. If NULL, then the resource is to be relinked.
	@param linkResource - the resource which is to be relinked.
	@return - whether the relink was successful or not.
	*/
	virtual bool16 DoRelinkWithCloudAsset(const std::string& elementRef, ILink* link, ILinkResource* linkResource) const = 0;

    
    /* Relink the passed in link/linkResource with the AAL asset which is represented by the elementRef passed as an argument.
     @param elementRef - unique identifier of the AAL asset to relink to.
     @param link - the link which is to be relinked. If NULL, then the resource is to be relinked.
     @param linkResource - the resource which is to be relinked.
     @return - whether the relink was successful or not.
     */
    virtual bool16 DoRelinkWithAALAsset(const std::string& elementRef, ILink* link, ILinkResource* linkResource) const = 0;

    
    /* Relink the passed in LinkResource with linked assets by presenting the AAL (Adobe Asset Link) panel in the mode where user can select an asset to relink to*/
    virtual bool16 DoRelinkSelectedLinkResourcesWithAALAssets(const UIDList& targetResources, LinkClientID whichClientID) const = 0;
    
    /* Relink the passed in links with an AAL asset by presenting the AAL (Adobe Asset Link) panel in the mode where user can select an asset to relink to.
     @param targetLinks - a list of ILink UIDs you want the user to relink.
     */
    virtual bool16 DoRelinkSelectedLinksWithAALAssets(const UIDList& targetLinks, LinkClientID whichClientID) const = 0;
    
};

#endif 
