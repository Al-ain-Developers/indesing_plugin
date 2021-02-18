//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSwatchView.cpp $
//  
//  Owner: Brendan O'Shea
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

#include "IDocument.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "LayerPanelUtils.h"
#include "IBoolData.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "LayerPanelDefs.h"
#include "LayerTreeUIDNodeID.h"
#include "PersistUtils.h"
#include "ISpreadLayer.h"
#include "IHierarchy.h"
#include "iuicolorutils.h"
#include "LayerPanelID.h"
#include "DVControlView.h"
#include "DVPublicUtilities.h"

//----------------------------------------------------------------------------------------
// Class LayerSwatchView
//----------------------------------------------------------------------------------------

class LayerSwatchView : public DVControlView
{
	typedef DVControlView inherited;
public:
			 LayerSwatchView(IPMUnknown *boss) : inherited(boss) { ; }
	virtual ~LayerSwatchView() { ; }
	
protected:	 
	virtual void DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;
};

#pragma mark LayerSwatchView implementation

CREATE_PERSIST_PMINTERFACE(LayerSwatchView, kLayerSwatchViewImpl)

void LayerSwatchView::DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const
{
	ColorArray	color = LayerPanelUtils::GetLayerColorForWidget(const_cast<LayerSwatchView*>(this));
	PMRect		swatchRt( this->GetInnerContentFrame() );

	RealAGMColor background(ToFloat(color[IUIColorUtils::kRed]), ToFloat(color[IUIColorUtils::kGreen]), ToFloat(color[IUIColorUtils::kBlue]));
	swatchRt.Inset(1, 1);

	dv_utils::DVFillRect( drawbotP, background, swatchRt );

}
