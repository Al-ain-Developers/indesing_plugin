//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/ActiveView.cpp $
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

#include "LayerPanelUtils.h"
#include "IDocumentLayer.h"
#include "IControlView.h"
#include "ILayerUIUtils.h"
#include "IWidgetParent.h"
#include "IBoolData.h"

#include "CIDIconSuiteButtonView.h"
#include "LayerPanelID.h"
#include "LayerPanelDefs.h"

class ActiveView : public CIDIconSuiteButtonView
{
	typedef CIDIconSuiteButtonView inherited;
public:
	ActiveView(IPMUnknown* boss);
	virtual ~ActiveView();
	
	virtual void		PreDrawDoIconChange();
};

CREATE_PERSIST_PMINTERFACE(ActiveView, kActiveViewImpl)


ActiveView::ActiveView(IPMUnknown *boss) :
	inherited(boss)
{
}

ActiveView::~ActiveView() 
{ 
}


void ActiveView::PreDrawDoIconChange()
{
	
	bool16 isActive = kFalse;

	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	InterfacePtr<const IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));
	InterfacePtr<const IDocumentLayer> docLayer(LayerPanelUtils::QueryLayerFromPanelWidget(this));

	if (docLayer == activeLayer)
		isActive = kTrue;

	InterfacePtr<IControlView> controlView(this, UseDefaultIID());
	InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
	InterfacePtr<const IBoolData> rowSizeBool((IBoolData*)wp->QueryParentFor( IID_ISMALLPALETTEROWSBOOLDATA));
	bool16 bSmallRows = rowSizeBool->GetBool();

	if (isActive)
	{
		bool16 bLockedIcon = docLayer && (!docLayer->IsVisible() || docLayer->IsLocked());
		RsrcID iconID = bLockedIcon ?  (bSmallRows ? kLayerPenLockedSmallIcon : kLayerPenLockedIcon) : (bSmallRows ? kLayerPenSmallIcon : kLayerPenIcon);

		controlView->SetRsrcID(iconID);
	}
	else
		controlView->SetRsrcID(kLayerBlankIcon);
}


