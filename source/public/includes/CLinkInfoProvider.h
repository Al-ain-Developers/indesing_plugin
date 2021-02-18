//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CLinkInfoProvider.h $
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

#ifndef __CLinkInfoProvider__
#define __CLinkInfoProvider__

// ----- Interface files
#include "ILinkInfoProvider.h"
#include "PMTypes.h"
#include "WidgetDefs.h"


class PUBLIC_DECL CLinkInfoProvider : public CPMUnknown<ILinkInfoProvider>
{
	public:

	CLinkInfoProvider(IPMUnknown * boss);
	virtual ~CLinkInfoProvider();
			
	virtual bool16 IsLinkInfoDynamic() const {  return kFalse; }
	virtual PMRsrcID GetInfoDescriptionIcon() const  { PMRsrcID defaultRsrc; return defaultRsrc; }
	virtual int32 GetDefaultColumnWidth() const { return 50; }
	virtual int16 GetInfoTextAlignment() const { return kAlignLeft; }
	virtual PMRsrcID GetUpdatedIconForLink(const ILink*, const ILinkResource*) const { PMRsrcID defaultRsrc; return defaultRsrc; }
	virtual void AttachToDocument(IObserver *observer, const IDocument* newDoc);
	virtual void DetachFromDocument(IObserver *observer, const IDocument* oldDoc);
	virtual bool16 ShouldCauseRefreshOfInfo(const PMIID &protocol) const;
	virtual bool16 CanDoSingleClickAction(const ILink*, const ILinkResource*) const { return kFalse; }
	virtual void DoSingleClickAction(const ILink* link, const ILinkResource* linkResource);
	virtual bool16 CanDoDoubleClickAction(const ILink*, const ILinkResource*) const { return kFalse; }
	virtual void DoDoubleClickAction(const ILink* link, const ILinkResource* linkResource);
	virtual PMString GetDoubleClickDescription(const ILink* link, const ILinkResource* linkResource) const;
	
	virtual	int32 Compare(const ILink* link1, const ILinkResource* linkResource1,const ILink* link2, const ILinkResource* linkResource2) const;

};

#endif