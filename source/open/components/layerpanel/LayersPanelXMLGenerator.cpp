//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayersPanelXMLGenerator.cpp $
//  
//  Owner: Paul Sorrick
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

#include "BasePanelXMLGenerator.h"
#include "IBoolData.h"
#include "IXMLOutStream.h"
#include "IControlView.h"
#include "IPanelControlData.h"

// ----- Implementation Includes -----

#include "LayerPanelID.h"
#include "LayersPanelWorkspaceDefs.h"

const char* LayersPanelWorkspaceDefs::kLayersPanelOptionsXMLTag = "LayerPaneOptions";
const char* LayersPanelWorkspaceDefs::kLayersPanelSmallRowsXMLTag = "SmallRows";

//========================================================================================
// Class LayersPanelXMLGenerator
//========================================================================================

class LayersPanelXMLGenerator : public BasePanelXMLGenerator
{
	typedef BasePanelXMLGenerator inherited;
	
public:
	LayersPanelXMLGenerator(IPMUnknown *boss);
	virtual ~LayersPanelXMLGenerator();

	void GenerateContent(IXMLOutStream *s, int32 beforeChildIndex);
};


//========================================================================================
// METHODS LayersPanelXMLGenerator
//========================================================================================
CREATE_PMINTERFACE(LayersPanelXMLGenerator, kLayersPanelXMLGeneratorImpl)

LayersPanelXMLGenerator::LayersPanelXMLGenerator(IPMUnknown *boss) :
	inherited(boss)
{
}

LayersPanelXMLGenerator::~LayersPanelXMLGenerator()
{
}

//----------------------------------------------------------------------------------------
// GenerateContent
//----------------------------------------------------------------------------------------
void LayersPanelXMLGenerator::GenerateContent(IXMLOutStream *s, int32 beforeChildIndex)
{
	inherited::GenerateContent(s, beforeChildIndex);

	IXMLOutStream::AttributeList attrs;

	InterfacePtr<const IPanelControlData> panelData(this, UseDefaultIID());
	const IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
	InterfacePtr<const IBoolData> rowSizeBool(treeView, IID_ISMALLPALETTEROWSBOOLDATA);
	PushBool( attrs, LayersPanelWorkspaceDefs::kLayersPanelSmallRowsXMLTag, rowSizeBool->Get());
	
	PMString layerPanelOptionsTag( LayersPanelWorkspaceDefs::kLayersPanelOptionsXMLTag );
	
	s->PushWithAttributes( layerPanelOptionsTag.GrabWString(), attrs, kTrue );				
	s->Pop( kTrue );		

}


