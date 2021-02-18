//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIStatusTextTip.cpp $
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

#include "VCPlugInHeaders.h"
#include "ITextControlData.h"
#include "AbstractTip.h"
#include "ILinksUIPanelPrefs.h"
#include "PMString.h"
#include "ILinkManager.h"
#include "LinkQuery.h"
#include "LinkResourceQuery.h"

#include "PreferenceUtils.h"
#include "CPMUnknown.h"
#include "LinksUIID.h"
#include "StringUtils.h"
#include "UIDList.h"

#include <boost/bind.hpp>

class LinksUIStatusTextTip : public AbstractTip
{			
public:
	LinksUIStatusTextTip( IPMUnknown *boss );
	virtual ~LinksUIStatusTextTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE( LinksUIStatusTextTip, kLinksUIStatusTextTipImpl )


LinksUIStatusTextTip::LinksUIStatusTextTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
} 



LinksUIStatusTextTip::~LinksUIStatusTextTip()
{
} 


PMString LinksUIStatusTextTip::GetTipText(const PMPoint& mouseLocation)
{
#pragma unused(mouseLocation)

	PMString tipString;

	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	IDataBase *docDB  = linksUIPrefs->GetCurrentDocDB();
	if(docDB)
	{
		ILinkManager::QueryResult resultUIDs;
		InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
		
		// Total links
		LinkQuery allLinksQuery; 
		allLinksQuery.SetShowInUI(kTrue);
		uint32 numLinks = linkMgr->QueryLinks(allLinksQuery, kIDLinkClientID, resultUIDs);
		
		// Unique links
		LinkResourceQuery allResourcesQuery; 
		uint32 numUnique = linkMgr->QueryResources(allResourcesQuery, kIDLinkClientID, resultUIDs);
		
		// Sublinks
		LinkQuery childLinksQuery; 
		childLinksQuery.SetLinkType(ILink::kChild); 
		childLinksQuery.SetShowInUI(kTrue);
		uint32 numChild = linkMgr->QueryLinks(childLinksQuery, kIDLinkClientID, resultUIDs);

		// Missing links
		ILinkManager::QueryResult missingLinkUIDs;
		uint32 numMissing(0);
		LinkResourceQuery missingResourcesQuery; 
		missingResourcesQuery.SetState(ILinkResource::kMissing); 
		if (linkMgr->QueryResources(missingResourcesQuery, kIDLinkClientID, resultUIDs) != 0)
		{
			LinkQuery missingLinksQuery; 
			missingLinksQuery.SetShowInUI(kTrue);
			std::for_each(resultUIDs.begin(), resultUIDs.end(), boost::bind(&LinkQuery::SetResource, &missingLinksQuery, _1));
			numMissing = linkMgr->QueryLinks(missingLinksQuery, kIDLinkClientID, missingLinkUIDs);
		}
	
		// Modified links
		ILinkManager::QueryResult modifiedLinkUIDs;
		uint32 numModified(0);
		LinkQuery modifiedLinksQuery; 
		modifiedLinksQuery.SetResourceModState(ILink::kResourceModified);
		modifiedLinksQuery.SetShowInUI(kTrue);
		if (linkMgr->QueryLinks(modifiedLinksQuery, kIDLinkClientID, modifiedLinkUIDs) != 0)
		{
			resultUIDs.clear();
			std::set_difference(modifiedLinkUIDs.begin(), modifiedLinkUIDs.end(), missingLinkUIDs.begin(), missingLinkUIDs.end(), std::back_inserter(resultUIDs));
			numModified = static_cast<uint32>(resultUIDs.size());
		}

		// Embedded links
		uint32 numEmbedded(0);
		LinkResourceQuery embeddedResourcesQuery; 
		embeddedResourcesQuery.SetStoreState(ILinkResource::kEmbedded);
		if (linkMgr->QueryResources(embeddedResourcesQuery, kIDLinkClientID, resultUIDs) != 0)
		{
			LinkQuery embeddedLinksQuery; 
			embeddedLinksQuery.SetShowInUI(kTrue);
			std::for_each(resultUIDs.begin(), resultUIDs.end(), boost::bind(&LinkQuery::SetResource, &embeddedLinksQuery, _1));
			numEmbedded = linkMgr->QueryLinks(embeddedLinksQuery, kIDLinkClientID, resultUIDs);
		}
	
		PMString numLinksStr;
		numLinksStr.AppendNumber(numLinks);
		numLinksStr.SetTranslatable(kFalse);

		// use the long status string
		tipString.SetCString("#LongLinkStatusParamStr");
		tipString.Translate();

		PMString numUniqueLinkStr;
		numUniqueLinkStr.AppendNumber(numUnique);
		numUniqueLinkStr.SetTranslatable(kFalse);

		PMString numEmbeddedLinksStr;
		numEmbeddedLinksStr.AppendNumber(numEmbedded);
		numEmbeddedLinksStr.SetTranslatable(kFalse);

		PMString numChildLinksStr;
		numChildLinksStr.AppendNumber(numChild);
		numChildLinksStr.SetTranslatable(kFalse);

		PMString numMissingLinksStr;
		numMissingLinksStr.AppendNumber(numMissing);
		numMissingLinksStr.SetTranslatable(kFalse);

		PMString numModifiedLinksStr;
		numModifiedLinksStr.AppendNumber(numModified);
		numModifiedLinksStr.SetTranslatable(kFalse);

		StringUtils::ReplaceStringParameters(&tipString, numLinksStr, numMissingLinksStr, numModifiedLinksStr, numEmbeddedLinksStr, numUniqueLinkStr, numChildLinksStr);
	}
		
	return tipString;
} 
