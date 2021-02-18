//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkInfoProvider.h $
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
#ifndef __ILinkInfoProvider__
#define __ILinkInfoProvider__

#include "IPMUnknown.h"
#include "LinksID.h"

class ILink;
class ILinkResource;
class IObserver;
class IDocument;

/**	This interface provides some information about an ILink, ILinkResource, or ILinkObject. It's typically added to a service boss with the kLinkInfoServiceImpl, so that it can be found by using the service registry.

Class
	{
		kLinkInfoNameProviderBoss,
		kInvalidClass,
		{
			IID_IK2SERVICEPROVIDER, kLinkInfoServiceImpl,
			IID_ILINKINFOPROVIDER, kLinkInfoNameProviderImpl,
		}
	},

*/

class ILinkInfoProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKINFOPROVIDER };

	/** This returns a key string description of the info itself, like 'Name' or 'ColorSpace' */
	virtual PMString GetInfoDescriptionString() const = 0;
	
	/** This returns an icon description of the info itself, like a little page. The returned PMRsrcID is expected to refer to a PNG icon resource */
	virtual PMRsrcID GetInfoDescriptionIcon() const = 0;
	
	/** This returns a string representing the info for this ILink or ILinkResource. Callers can request either the short form or the long form of the info string. */
	virtual PMString GetUpdatedInfoForLink(const ILink* link, const ILinkResource* linkResource, bool shortForm) const = 0;
	
	/** This returns an icon representing the info for this ILink or ILinkResource. The returned PMRsrcID is expected to refer to a PNG icon resource */
	virtual PMRsrcID GetUpdatedIconForLink(const ILink* link, const ILinkResource* linkResource) const = 0;

	/** This method should return true if this info is calculated based on something in the InDesign document. Return false if your data depends only on the file on disk. */
	virtual bool16 IsLinkInfoDynamic() const = 0;
	
	/** returns whether or not the single click action is available for this item in this column */
	virtual bool16 CanDoSingleClickAction(const ILink* link, const ILinkResource* linkResource) const = 0;
	
	/** Some columns provide an action when the user single clicks on the displayed info. For example, the page number field will 'goto link' on a single click. */
	virtual void DoSingleClickAction(const ILink* link, const ILinkResource* linkResource) = 0;

	/** returns whether or not the double click action is available for this item in this column */
	virtual bool16 CanDoDoubleClickAction(const ILink* link, const ILinkResource* linkResource) const = 0;
	
	/** Some columns provide an action when the user double clicks on the displayed info. For example, the status column will update a modified link on double click. */
	virtual void DoDoubleClickAction(const ILink* link, const ILinkResource* linkResource) = 0;
	
	/** Get string describing the double click behavior. Might be used in a tool tip. */
	virtual PMString GetDoubleClickDescription(const ILink* link, const ILinkResource* linkResource) const = 0;

	/** Default num pixels for column width. Some columns make sense wide, others narrow. */
	virtual int32 GetDefaultColumnWidth() const = 0;
	
	/** Get the alignment of the text for this column
		@return  one of {kAlignLeft,kAlignCenter,kAlignRight}, defined in WidgetDefs.h */
	virtual int16 GetInfoTextAlignment() const = 0;

	/** will only be called for info providers which indicate they are dynamic. The ILinkInfoProvider implementation should attach the observer to whatever they need to watch */
	virtual void AttachToDocument(IObserver *observer, const IDocument* newDoc) = 0;

	/** will only be called for info providers which indicate they are dynamic. The ILinkInfoProvider implementation should attach the observer to whatever they need to watch */
	virtual void DetachFromDocument(IObserver *observer, const IDocument* oldDoc) = 0;

	/** will only be called for info providers which indicate they are dynamic. The ILinkInfoProvider implementation should return true if this message might change its data. */
	virtual bool16 ShouldCauseRefreshOfInfo(const PMIID &protocol) const = 0;
	
	/** compare the values of these 2 links. Used for sorting. 0 indicates equality. -1 indicates first is < second, 1 indicates second > first*/
	virtual	int32 Compare(const ILink* link1, const ILinkResource* linkResource1,const ILink* link2, const ILinkResource* linkResource2) const = 0;


};

#endif
