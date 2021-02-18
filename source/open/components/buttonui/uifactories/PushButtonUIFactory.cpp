//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/uifactories/PushButtonUIFactory.cpp $
//  
//  Owner: Tim Wright
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

#include "IPanelControlData.h"
#include "IGraphicStyleAttrBossList.h"

// Project:
#include "FormFieldUIFactory.h"
#include "AttributesUtils.h"
#include "UserInterfaceUtils.h"

using namespace AttributesUtils;
using namespace UserInterfaceUtils;

//------------------------------------------------------------------------

class PushButtonUIFactory : public FormFieldUIFactory
{
public:
	PushButtonUIFactory(IPMUnknown * boss) : FormFieldUIFactory(boss){}

	ActionID GetToolActionID() const { return  kPushButtonToolActionID;}

	void InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGraphicAttrSuite );
};

CREATE_PMINTERFACE(PushButtonUIFactory, kPushButtonUIFactoryImpl)

//------------------------------------------------------------------------

void PushButtonUIFactory::InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGfxAttrSuite )
{
/* --- [amb 12-03-02] Not supported for dragontail.

	//Disable export-related controls since push buttons don't have values and therefore aren't exported.

	InterfacePtr<IGraphicStyleAttributeBossList> defaultAttrs( QueryDefaultAttributes() );

	bool kEnable = false;
	UpdateTextWidget( inPanelData, inGfxAttrSuite, kEnable, kFormExportMappingAttrBoss, kExportNameEditWID, defaultAttrs );
	UpdateCheckWidget( inPanelData, inGfxAttrSuite, kEnable, kFormExportAttrBoss, 		kExportWID, defaultAttrs);
	UpdateCheckWidget( inPanelData, inGfxAttrSuite, kEnable, kFormExportRequiredAttrBoss, kRequiredForExportWID, defaultAttrs );

	IControlView* exportNameStatic = inPanelData->FindWidget(kExportNameStaticWID);
	exportNameStatic->Enable(kEnable);
*/
}

