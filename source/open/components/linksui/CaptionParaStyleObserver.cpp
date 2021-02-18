//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/CaptionParaStyleObserver.cpp $
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

#include "IStyleGroupListControlData.h"	
#include "IWorkspace.h"
#include "IStyleInfo.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "ILayoutUIUtils.h"
#include "CObserver.h"
#include "LinksUIID.h"
#include "ILinkCaptionPrefs.h"
#include "PreferenceUtils.h"

class CaptionParaStyleObserver : public CObserver
{
public:
					CaptionParaStyleObserver(IPMUnknown *boss);
		virtual void	AutoAttach();
		virtual void	AutoDetach();

		virtual 	void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

protected:
		virtual bool16 	SetupDropDownListBox( );

};


//===============================================================
// CLASS CaptionParaStyleObserver
//===============================================================

CREATE_PMINTERFACE( CaptionParaStyleObserver, kCaptionParaStyleObserverImpl)

//---------------------------------------------------------------
// CaptionParaStyleObserver constructor 
//---------------------------------------------------------------

CaptionParaStyleObserver::CaptionParaStyleObserver(IPMUnknown *boss) :
	CObserver(boss)
{

}

void CaptionParaStyleObserver::AutoAttach( ) 
{
	
	this->SetupDropDownListBox( );
	CObserver::AutoAttach();

}


void CaptionParaStyleObserver::AutoDetach( ) 
{
	
	CObserver::AutoDetach();

}


void CaptionParaStyleObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	#pragma unused(theChange,theSubject,protocol,changedBy)
}
	

//---------------------------------------------------------------
// CaptionParaStyleObserver::SetupDropDownListBox
//---------------------------------------------------------------

bool16 CaptionParaStyleObserver::SetupDropDownListBox( )
{
	InterfacePtr<IStyleGroupListControlData>pListControlData ( this, UseDefaultIID() );
	ASSERT(pListControlData);

	if( !pListControlData )
		return kFalse;
	
	InterfacePtr<IWorkspace> pWorkSpace( Utils<ILayoutUIUtils>()->QueryActiveWorkspace() );
	InterfacePtr<IStyleGroupManager> styleMgr( pWorkSpace, IID_IPARASTYLEGROUPMANAGER);
	if( !styleMgr )
		return kFalse;


	//Set up the style list
	pListControlData->ResetAll();
	pListControlData->AppendInterfaceID(IID_IPARASTYLEGROUPMANAGER);

	InterfacePtr<const ILinkCaptionPrefs> linkCaptionPrefs((ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, GetExecutionContextSession()->GetActiveContext()));

	//if the to be selected uid is part of the style hierarchy
	UID captionStyleUID = linkCaptionPrefs->GetCaptionParagraphStyleUID();
	
	if(!styleMgr->IsHierarchyMember(captionStyleUID))
	{
		captionStyleUID = styleMgr->GetRootStyleUID(); //default style to be selected
	}

	pListControlData->SetupSelectedStyle(captionStyleUID);

	pListControlData->BuildList();

	return kTrue;
}

