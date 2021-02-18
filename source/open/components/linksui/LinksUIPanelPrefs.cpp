//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelPrefs.cpp $
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

// ----- Interface files
#include "ILinksUIPanelPrefs.h"
#include "ILinkResource.h"
#include "ILink.h"
#include "IPMStream.h"
#include "ILinkInfoProvider.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISubject.h"
#include "IWorkspace.h"

// ----- ID files
#include "LinksID.h"
#include "LinksUIID.h"
#include "LinksUIResDefs.h"
#include "k2VectorStreaming.h"
#include "ListLazyNotificationData.h"
#include "StdHeightWidthConstants.h"

class LinksUIPanelPrefs : public CPMUnknown<ILinksUIPanelPrefs>
{
	public:

	LinksUIPanelPrefs(IPMUnknown * boss);
	virtual ~LinksUIPanelPrefs();
			
	virtual IDataBase* GetCurrentDocDB() const { return fCurrentDocDB; }
	virtual void SetCurrentDocDB(IDataBase* newDocDB) { fCurrentDocDB = newDocDB; }

	virtual int32 GetCurrentRowHeight() const { return fCurrentRowHeight; }
	virtual void SetCurrentRowHeight(int32 newHeight);

	virtual int32 GetNumInfoProviders() const;
	virtual ILinkInfoProvider* QueryNthInfoProvider(int32 nth) const;

	virtual int32 GetNumShowingInfoColumns() const;
	virtual ILinkInfoProvider* QueryNthShowingInfoColumn(int32 nth) const;
	virtual void SetShowingInfoColumns(const K2Vector<ILinkInfoProvider*> columnProviders);
	virtual int32 GetNthColumnWidth(int32 nth) const;
	virtual void SetColumnWidths(const K2Vector<int32>& columnWidths);
	virtual void GetColumnWidths(K2Vector<int32>& columnWidths) const;
	
	virtual int32 GetNumMoreInfoProviders() const;
	virtual ILinkInfoProvider* QueryNthMoreInfoProvider(int32 nth) const;
	virtual void SetMoreInfoProviders(const K2Vector<ILinkInfoProvider*> infoProviders);

	virtual void SetSortLinksAscending(bool16 ascend);
	virtual bool16 GetSortLinksAscending() const { return fSortAscending; }
	
	virtual void SetShowLinkThumbnail(bool16 showThumbnail);
	virtual bool16 GetShowLinkThumbnail() const { return fShowThumbnail; }
	
	virtual void SetShowLinkInfoThumbnail(bool16 showThumbnail);
	virtual bool16 GetShowLinkInfoThumbnail() const { return fShowInfoThumbnail; }
	
	virtual void SetCollapseMultipleLinksToSameResource(bool16 collapse);
	virtual bool16 GetCollapseMultipleLinksToSameResource() const { return fCollapseMultiple; }

	virtual const ILinkInfoProvider* GetSortInfoProvider() const { return fSortProvider; }
	virtual const ILinkInfoProvider* GetSecondarySortInfoProvider() const { return fSecondarySortProvider; }
	virtual void SetSortInfoProvider(const ILinkInfoProvider* newSorter);

	virtual void SetLinkInfoAutoSizes(bool16 autoSize);
	virtual bool16 GetLinkInfoAutoSizes() const { return fAutoSizeLinkInfo; }

	private:
		void NotifyLinksUIPrefChange(ClassID whichChange) const;
		
		const ILinkInfoProvider* fSortProvider;
		const ILinkInfoProvider* fSecondarySortProvider;
		IDataBase* fCurrentDocDB;
		bool16 fSortAscending;
		bool16 fShowThumbnail;
		bool16 fShowInfoThumbnail;
		bool16 fAutoSizeLinkInfo;
		bool16 fCollapseMultiple;
		int32 fCurrentRowHeight;
		
		K2Vector<ILinkInfoProvider*> fAllInfoProviders;
		K2Vector<ILinkInfoProvider*> fCurrentColumnsInfoProviders;
		K2Vector<ILinkInfoProvider*> fCurrentMoreInfoProviders;
		K2Vector<int32> fCurrentColumnWidths;
};


CREATE_PMINTERFACE(LinksUIPanelPrefs, kLinksUIPanelPrefsImpl)

LinksUIPanelPrefs::LinksUIPanelPrefs(IPMUnknown * boss)
	: CPMUnknown<ILinksUIPanelPrefs>(boss),
	fSortProvider(nil),fSecondarySortProvider(nil),
	fSortAscending(kTrue),fCurrentRowHeight(kCC2016PanelTreeNodeHeight),
	fCurrentDocDB(nil),fAutoSizeLinkInfo(kFalse),fShowThumbnail(kTrue),fShowInfoThumbnail(false),fCollapseMultiple(kTrue)
{
	// collect all the possible info providers:
	InterfacePtr<IK2ServiceRegistry>	serviceR(GetExecutionContextSession(), UseDefaultIID());
	const int32 numHandlers = serviceR->GetServiceProviderCount(kLinkInfoService);

	K2Vector<ILinkInfoProvider*> moreInfoProviders; // will hold our default list of which providers are enabled for the 'more info' section

	// first add the important ones in the order we want:
	K2Vector<ClassID> orderedInfoClasses;
	orderedInfoClasses.push_back(kLinkInfoNameProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoStatusProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoPageNumberProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoSizeProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoColorSpaceProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoColorProfileProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoLayerOverrideProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoPPIProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoEffectivePPIProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoTransparencyProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoPixelSizeProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoScaleProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoSkewProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoRotationProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoLayerNameProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoFullPathProviderBoss);
	orderedInfoClasses.push_back(kLinkInfoInstanceNameProviderBoss);
	for(K2Vector<ClassID>::const_iterator orderedIter = orderedInfoClasses.begin(); orderedIter <  orderedInfoClasses.end(); ++orderedIter)
	{
		InterfacePtr<const IK2ServiceProvider> providerWorthSorting(serviceR->QueryServiceProviderByClassID(kLinkInfoService, *orderedIter));
		InterfacePtr<ILinkInfoProvider> infoProvider(providerWorthSorting,UseDefaultIID());
		if(infoProvider)
		{
			fAllInfoProviders.push_back(infoProvider);
			moreInfoProviders.push_back(infoProvider);
		}
	}

	TRACEFLOW("Links:LinksUI","Loading all Link Info Providers\n");
	for (int i = numHandlers - 1; i >= 0; --i) 
	{
		InterfacePtr<const IK2ServiceProvider> provider(serviceR->QueryNthServiceProvider(kLinkInfoService, i));
		ILinkInfoProvider *infoProvider = (ILinkInfoProvider*)provider->QueryInterface(IID_ILINKINFOPROVIDER);
		if(infoProvider && std::find(orderedInfoClasses.begin(),orderedInfoClasses.end(),::GetClass(infoProvider)) == orderedInfoClasses.end())
		{
#ifdef DEBUG		
			PMString debugProviderName = infoProvider->GetInfoDescriptionString();
			debugProviderName.Translate();
			TRACEFLOW("Links:LinksUI","   %s\n",debugProviderName.GetUTF8String().c_str());
#endif
			fAllInfoProviders.push_back(infoProvider);
			
			// now add most of the stuff into the 'more info providers'
			ClassID providerClass = ::GetClass(infoProvider);
			switch(providerClass.Get())
			{
				case kLinkInfoLinkTypeProviderBoss:
				case kLinkInfoFolder0ProviderBoss:
				case kLinkInfoFolder1ProviderBoss:
				case kLinkInfoFolder2ProviderBoss:
				case kLinkInfoFolder3ProviderBoss:
				case kLinkInfoFolder4ProviderBoss:
				case kLinkInfoFolder5ProviderBoss:
				case kLinkInfoFolder6ProviderBoss:
				case kLinkInfoFolder7ProviderBoss:
				case kLinkInfoFolder8ProviderBoss:
				case kLinkInfoVolumeNameProviderBoss:
				case kLinkInfoChildLinksProviderBoss:
					break; // filter these out of the more info section by default
				default:
					moreInfoProviders.push_back(infoProvider);
			}
		}
	}

	// pick some common columns to be the defaults:
	K2Vector<ILinkInfoProvider*> defaultColumnProviders;

	InterfacePtr<const IK2ServiceProvider> statusProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, kLinkInfoStatusProviderBoss));
	InterfacePtr<ILinkInfoProvider> statusInfoService(statusProvider,UseDefaultIID());
	defaultColumnProviders.push_back(statusInfoService);
	fSortProvider = statusInfoService;

	InterfacePtr<const IK2ServiceProvider> nameProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, kLinkInfoNameProviderBoss));
	InterfacePtr<ILinkInfoProvider> nameInfoService(nameProvider,UseDefaultIID());
	defaultColumnProviders.push_back(nameInfoService);
	fSecondarySortProvider = nameInfoService;

	InterfacePtr<const IK2ServiceProvider> pageProvider(serviceR->QueryServiceProviderByClassID(kLinkInfoService, kLinkInfoPageNumberProviderBoss));
	InterfacePtr<ILinkInfoProvider> pageInfoService(pageProvider,UseDefaultIID());
	defaultColumnProviders.push_back(pageInfoService);
	
	SetShowingInfoColumns(defaultColumnProviders );
	SetMoreInfoProviders(moreInfoProviders );
		
}

LinksUIPanelPrefs::~LinksUIPanelPrefs()
{
	for(K2Vector<ILinkInfoProvider*>::iterator i = fAllInfoProviders.begin(); i != fAllInfoProviders.end(); ++i)
	{
		(*i)->Release();
	}
	fAllInfoProviders.clear();
	
	// This interface is marked as non-persistent to the object model, because it persists data into the workspace xml file. Currently, it won't be destroyed until shutdown, after we've written the workspace file.
	// we'll add this assert to make sure this stays the case. If we get destroyed and recreated while running, some changes will be lost, so we'll have to adjust if this behavior ever changes.
	ASSERT_MSG(GetExecutionContextSession()->GetState() == ISession::kShuttingDown,"LinksUIPanelPrefs - might lose data destroying this before we write the workspace file");
}

void LinksUIPanelPrefs::NotifyLinksUIPrefChange(ClassID whichChange) const
{
	InterfacePtr<const IWorkspace> theWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> subject(theWorkSpace, UseDefaultIID());

	subject->ModelChange(whichChange, IID_ILINKSUIPANELPREFS, (LinksUIPanelPrefs*)this);
}

void LinksUIPanelPrefs::SetCurrentRowHeight(int32 newHeight)
{
	fCurrentRowHeight = newHeight;
	NotifyLinksUIPrefChange(kLinksUITreeRowChangeMsgBoss);
}

int32 LinksUIPanelPrefs::GetNumInfoProviders() const
{
	return K2length(fAllInfoProviders);
}

ILinkInfoProvider* LinksUIPanelPrefs::QueryNthInfoProvider(int32 nth) const
{
	ASSERT_MSG(nth >= 0 && nth < K2length(fAllInfoProviders),"LinksUIPanelPrefs::QueryNthInfoProvider asked for out of range provider");
	fAllInfoProviders[nth]->AddRef();
	return fAllInfoProviders[nth];
}

int32 LinksUIPanelPrefs::GetNthColumnWidth(int32 nth) const
{
	ASSERT_MSG(nth >= 0 && nth < K2length(fCurrentColumnWidths),"LinksUIPanelPrefs::GetNthColumnWidth asked for out of columnWidth");
	return fCurrentColumnWidths[nth];
}

void LinksUIPanelPrefs::SetColumnWidths(const K2Vector<int32>& columnWidths)
{
	ASSERT_MSG(columnWidths.size() == fCurrentColumnWidths.size(),"SetColumnWidths specifying wrong number of widths!");
	fCurrentColumnWidths.clear();
	for(K2Vector<int32>::const_iterator i = columnWidths.begin(); i != columnWidths.end(); ++i)
	{
		fCurrentColumnWidths.push_back(*i);
	}
	
	NotifyLinksUIPrefChange(kLinksUITreeRowChangeMsgBoss);
	
}

void LinksUIPanelPrefs::GetColumnWidths(K2Vector<int32>& columnWidths) const
{
	columnWidths.clear();
	for(K2Vector<int32>::const_iterator i = fCurrentColumnWidths.begin(); i != fCurrentColumnWidths.end(); ++i)
	{
		columnWidths.push_back(*i);
	}
}

int32 LinksUIPanelPrefs::GetNumShowingInfoColumns() const
{
	return K2length(fCurrentColumnsInfoProviders);
}

ILinkInfoProvider* LinksUIPanelPrefs::QueryNthShowingInfoColumn(int32 nth) const
{
	ASSERT_MSG(nth >= 0 && nth < K2length(fCurrentColumnsInfoProviders),FORMAT_ARGS("LinksUIPanelPrefs::QueryNthShowingInfoColumns asked for out of range provider(%d)",nth));
	fCurrentColumnsInfoProviders[nth]->AddRef();
	return fCurrentColumnsInfoProviders[nth];
}

void LinksUIPanelPrefs::SetShowingInfoColumns(const K2Vector<ILinkInfoProvider*> columnProviders)
{
	fCurrentColumnsInfoProviders.clear();
	fCurrentColumnWidths.clear();
	for(K2Vector<ILinkInfoProvider*>::const_iterator i = columnProviders.begin(); i != columnProviders.end(); ++i)
	{
		fCurrentColumnsInfoProviders.push_back(*i);
		fCurrentColumnWidths.push_back((*i)->GetDefaultColumnWidth());
	}
	
	NotifyLinksUIPrefChange(kLinksUIPrefTreeStructureChangeMsgBoss);
	
}

int32 LinksUIPanelPrefs::GetNumMoreInfoProviders() const
{
	return K2length(fCurrentMoreInfoProviders);
}

ILinkInfoProvider* LinksUIPanelPrefs::QueryNthMoreInfoProvider(int32 nth) const
{
	ASSERT_MSG(nth >= 0 && nth < K2length(fCurrentMoreInfoProviders),"LinksUIPanelPrefs::QueryNthMoreInfoColumns asked for out of range provider");
	fCurrentMoreInfoProviders[nth]->AddRef();
	return fCurrentMoreInfoProviders[nth];
}

void LinksUIPanelPrefs::SetMoreInfoProviders(const K2Vector<ILinkInfoProvider*> columnProviders)
{
	fCurrentMoreInfoProviders.clear();
	for(K2Vector<ILinkInfoProvider*>::const_iterator i = columnProviders.begin(); i != columnProviders.end(); ++i)
	{
		fCurrentMoreInfoProviders.push_back(*i);
	}
	
	NotifyLinksUIPrefChange(kLinksUIPrefInfoPaneChangeMsgBoss);
	
}

void LinksUIPanelPrefs::SetSortInfoProvider(const ILinkInfoProvider* newSorter)
{
	if(newSorter != fSortProvider)
	{
		fSecondarySortProvider = fSortProvider;
		fSortProvider = newSorter;

		NotifyLinksUIPrefChange(kLinksUIPrefTreeStructureChangeMsgBoss);
	}
}


void LinksUIPanelPrefs::SetSortLinksAscending(bool16 ascend)
{
	fSortAscending = ascend;

	NotifyLinksUIPrefChange(kLinksUIPrefTreeStructureChangeMsgBoss);
}
void LinksUIPanelPrefs::SetLinkInfoAutoSizes(bool16 autoSize)
{
	fAutoSizeLinkInfo = autoSize;
}

void LinksUIPanelPrefs::SetShowLinkThumbnail(bool16 showThumbnail)
{
	fShowThumbnail = showThumbnail;
	NotifyLinksUIPrefChange(kLinksUITreeRowChangeMsgBoss);
}

void LinksUIPanelPrefs::SetShowLinkInfoThumbnail(bool16 showThumbnail)
{
	fShowInfoThumbnail = showThumbnail;
	NotifyLinksUIPrefChange(kLinksUIPrefInfoPaneChangeMsgBoss);
}

void LinksUIPanelPrefs::SetCollapseMultipleLinksToSameResource(bool16 collapse)
{
	fCollapseMultiple = collapse;
	NotifyLinksUIPrefChange(kLinksUIPrefTreeStructureChangeMsgBoss);
}



