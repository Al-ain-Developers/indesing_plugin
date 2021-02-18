//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizPanelXMLGenerator.cpp $
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

#include "BasePanelXMLGenerator.h"
//#include "IWindow.h"
#include "IXMLOutStream.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IPagesPanelPrefs.h"
#include "IDCLSizPanelOptions.h"

// ----- Implementation Includes -----

#include "DCLSizID.h"
#include "IDCLSizPanelOptions.h"
//#include "PaletteWorkspaceDefs.h"

//========================================================================================
// Class DCLSizPanelXMLGenerator
//========================================================================================

class DCLSizPanelXMLGenerator : public BasePanelXMLGenerator
{
public:
	DCLSizPanelXMLGenerator(IPMUnknown *boss);
	virtual ~DCLSizPanelXMLGenerator();

	virtual void GenerateContent(IXMLOutStream *s, int32 beforeChildIndex = 0);
};


//========================================================================================
// METHODS DCLSizPanelXMLGenerator
//========================================================================================
CREATE_PMINTERFACE(DCLSizPanelXMLGenerator, kDCLSizPanelXMLGeneratorImpl)

DCLSizPanelXMLGenerator::DCLSizPanelXMLGenerator(IPMUnknown *boss) :
	BasePanelXMLGenerator(boss)
{
}

DCLSizPanelXMLGenerator::~DCLSizPanelXMLGenerator()
{
}

//----------------------------------------------------------------------------------------
// GenerateContent
//----------------------------------------------------------------------------------------
void DCLSizPanelXMLGenerator::GenerateContent(IXMLOutStream *s, int32 beforeChildIndex)
{
	BasePanelXMLGenerator::GenerateContent(s, beforeChildIndex);

	IXMLOutStream::AttributeList attrs;

	InterfacePtr<IDCLSizPanelOptions> iDCLSizPanelPrefs(this, IID_IDCLSizPanelOptions);

	// write out the list size option
	PushBool( attrs, kDCLSizPanelListSizeXMLAttributeName, iDCLSizPanelPrefs->Get());
	
	PMString dclSizPanelOptionsTag( kDCLSizPanelOptionsXMLTag );
	s->PushWithAttributes( dclSizPanelOptionsTag.GrabWString(), attrs, kTrue );				
	
	s->Pop( kTrue );		
}


