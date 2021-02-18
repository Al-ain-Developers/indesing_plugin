//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizPanelSAXHandler.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "BasePanelSAXHandler.h"
#include "ISAXServices.h"
#include "IDCLSizPanelOptions.h"
#include "IPanelControlData.h"
#include "ITreeViewWidgetMgr.h"
#include "TreeViewDefs.h"


// ----- Implementation Includes -----

#include "DCLSizID.h"

//========================================================================================
// Class DCLSizPanelSAXHandler
//========================================================================================

class DCLSizPanelSAXHandler : public BasePanelSAXHandler
{
public:
	DCLSizPanelSAXHandler(IPMUnknown *boss);
	virtual ~DCLSizPanelSAXHandler();

	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer);
    virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);
	virtual bool16 HandlesSubElements() const { return kTrue; }
};


//========================================================================================
// METHODS DCLSizPanelSAXHandler
//========================================================================================
CREATE_PMINTERFACE(DCLSizPanelSAXHandler, kDCLSizPanelSAXHandlerImpl)

DCLSizPanelSAXHandler::DCLSizPanelSAXHandler(IPMUnknown *boss) :
	BasePanelSAXHandler(boss)
{
}

DCLSizPanelSAXHandler::~DCLSizPanelSAXHandler()
{
}

//----------------------------------------------------------------------------------------
// Register
//----------------------------------------------------------------------------------------
void DCLSizPanelSAXHandler::Register(ISAXServices* saxServices, IPMUnknown *importer)
{
	saxServices->RegisterElementHandler( WideString(""), WideString(kDCLSizPanelOptionsXMLTag), this );

	// -- Cache this interface
	if (fSAXServices)
		fSAXServices->Release();

	fSAXServices = saxServices;
	fSAXServices->AddRef();
}

//----------------------------------------------------------------------------------------
// StartElement
//----------------------------------------------------------------------------------------
void DCLSizPanelSAXHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{
	if (qname == WideString(kDCLSizPanelOptionsXMLTag))
	{
		// Get the current prefs
		InterfacePtr<IDCLSizPanelOptions> iDCLSizPanelPrefs(this, IID_IDCLSizPanelOptions);
		if (!iDCLSizPanelPrefs)
			return;

		bool16 bCurListSize = iDCLSizPanelPrefs->Get();
		// List size
		bool16 bNewListSize = GetAttributeBool( attrs, kDCLSizPanelListSizeXMLAttributeName, bCurListSize);

		if (bNewListSize != bCurListSize)
			iDCLSizPanelPrefs->Set(bNewListSize);

		//Set small/large row here
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		IControlView* treeWidget = panelData->FindWidget(kDCLSizListBoxWidgetID);
		ASSERT_MSG(treeWidget, "Could not get tree view widget!");
		if(treeWidget) 
		{
			InterfacePtr<ITreeViewWidgetMgr> treeMgr(treeWidget, UseDefaultIID());

			if(!bNewListSize && (treeMgr->GetStyle() == kLargePaletteRowsTreeStyle))
			{
				treeMgr->SetStyle(kSmallPaletteRowsTreeStyle);
			}
			else if(bNewListSize && (treeMgr->GetStyle() == kSmallPaletteRowsTreeStyle))
			{
				treeMgr->SetStyle(kLargePaletteRowsTreeStyle);
			}
		}

	} else
		ASSERT_FAIL("DCLSizPanelSAXHandler called for an element it didn't register to receive");
}

//----------------------------------------------------------------------------------------
// EndElement
//----------------------------------------------------------------------------------------
void DCLSizPanelSAXHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname)
{
}
