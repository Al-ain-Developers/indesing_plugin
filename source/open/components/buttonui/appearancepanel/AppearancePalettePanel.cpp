//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePalettePanel.cpp $
//  
//  Owner: Mark VerMurlen
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
//  
//  Based on LayerPalettePanel.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IApplication.h"
#include "ICursorMgr.h"
#include "ICursorProvider.h"
#include "ICursorRegion.h"
#include "IPMStream.h"
#include "IPanelControlData.h"
#include "ISession.h"
#include "IPalettePanelUtils.h"

// Includes:
#include "CIDErasablePanelView.h"
#include "FormFieldUIDefs.h"
#include "FormFieldUIID.h"
#include "AssetLibUtils.h"

// -------------------------------------------------------------------------------------				

class  AppearancePalettePanel : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;
public:
			 AppearancePalettePanel(IPMUnknown* boss) : inherited(boss)  { ; }
	virtual ~AppearancePalettePanel() { ; }
	
	virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;
};

// -------------------------------------------------------------------------------------				

#pragma mark AppearancePalettePanel implementation

CREATE_PERSIST_PMINTERFACE(AppearancePalettePanel, kAppearancePalettePanelImpl)

// -------------------------------------------------------------------------------------				

#define kAppearancePalTopAreaHeight	220
#define	kMinAppearancePalWidth		270
#define	kMaxAppearancePalWidth		300
#define	kMinAppearancePalHeight		350		// nothing selected and expanded
#define	kMaxAppearancePalHeight		542		// expanded in case of list box.

// -------------------------------------------------------------------------------------				

PMPoint AppearancePalettePanel::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinAppearancePalWidth, kMinAppearancePalHeight, kMaxAppearancePalWidth, kMaxAppearancePalHeight) );
	
	return constrainedDim;
}			
