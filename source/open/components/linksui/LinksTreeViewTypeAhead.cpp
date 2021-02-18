//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksTreeViewTypeAhead.cpp $
//  
//  Owner: Bob Freeman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CPMUnknown.h" 
#include "ITreeViewTypeAhead.h"
#include "ILinksUIPanelPrefs.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ILinkInfoProvider.h"
#include "ILink.h"
#include "ILinkResource.h"

#include "LinksTreeUIDNodeID.h"
#include "PreferenceUtils.h"

class LinksTreeViewTypeAhead : public CPMUnknown<ITreeViewTypeAhead>
{
public:
	LinksTreeViewTypeAhead(IPMUnknown *boss):CPMUnknown<ITreeViewTypeAhead>(boss) {}

	virtual PMString	GetStringForNode( const NodeID& node ) const;

};


CREATE_PMINTERFACE(LinksTreeViewTypeAhead, kLinksTreeViewTypeAheadImpl)


PMString LinksTreeViewTypeAhead::GetStringForNode( const NodeID& node ) const
{
	// Get the name
	TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(node);

	InterfacePtr<IK2ServiceRegistry>	serviceR(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<const IK2ServiceProvider> nameProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, kLinkInfoNameProviderBoss));
	InterfacePtr<const ILinkInfoProvider> nameInfoService(nameProvider,UseDefaultIID());
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	InterfacePtr<const ILink> link(linksUIPrefs->GetCurrentDocDB(),linksUIDNode->GetLinkUIDRef().GetUID(),UseDefaultIID());
	InterfacePtr<const ILinkResource> linkRes(linksUIPrefs->GetCurrentDocDB(),linksUIDNode->GetLinkResourceUID(),UseDefaultIID());
	return nameInfoService->GetUpdatedInfoForLink(link,linkRes, true);
}

