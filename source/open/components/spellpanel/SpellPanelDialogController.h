//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelDialogController.h $
//  
//  Owner: Cindy Chen
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

#include "CDialogController.h"

#include "SpellPanelID.h"
//========================================================================================
// CLASS SpellPanelDialogController
//========================================================================================

class SpellPanelDialogController : public CDialogController
{
public:
	
	SpellPanelDialogController(IPMUnknown* boss);	
	virtual	~SpellPanelDialogController();

    virtual void  InitializeDialogFields(IActiveContext* context);
                                    // Should be overriden to initialize each widget in the dialog
                                    // with its default value.
	virtual void ClosingDialog(IActiveContext* lastChanceToUseMyContext);
};

// End, SpellPanelDialogController.h.
