//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelViewObserver.cpp $
//  
//  Owner: Swati Garg
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

// ----- Interfaces -----
#include "IControlView.h"
#include "IDialogController.h"
#include "IPanelControlData.h"

// ----- Includes -----
#include "CObserver.h"

// ----- Utility files -----
#include "IAEMLinkUtils.h"

// ----- ID.h files -----
#include "LinksUIID.h"


class LinksUIPanelViewObserver : public CObserver
{
	public:
		LinksUIPanelViewObserver(IPMUnknown *boss);
		virtual ~LinksUIPanelViewObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
};


CREATE_PMINTERFACE(LinksUIPanelViewObserver, kLinksUIPanelViewObserverImpl)

LinksUIPanelViewObserver::LinksUIPanelViewObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

LinksUIPanelViewObserver::~LinksUIPanelViewObserver()
{
}

void LinksUIPanelViewObserver::AutoAttach()
{
    InterfacePtr<IPanelControlData> panelData(this,UseDefaultIID());
    IControlView* relinkButtonsWithAAL = panelData->FindWidget(kRelinkWidgetsWithAALID);
    IControlView* relinkButtonsWithoutAAL = panelData->FindWidget(kRelinkWidgetsWithoutAALID);
    if (relinkButtonsWithAAL && relinkButtonsWithoutAAL)
    {
        bool16 isAALExtensionPresent = Utils<IAEMLinkUtils>()->ShouldShowAALRelinkAction();
        if (isAALExtensionPresent)
        {
            relinkButtonsWithAAL->ShowView();
            relinkButtonsWithoutAAL->HideView();
        } else
        {
            relinkButtonsWithAAL->HideView();
            relinkButtonsWithoutAAL->ShowView();
        }
    }
}

void LinksUIPanelViewObserver::AutoDetach()
{
	
}

void LinksUIPanelViewObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	
}

