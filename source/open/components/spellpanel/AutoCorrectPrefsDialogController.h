//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectPrefsDialogController.h $
//  
//  Owner: Heath Horton
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
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef _H_AutoCorrectPrefsDialogController
#define _H_AutoCorrectPrefsDialogController

#include "CDialogController.h"

class ICommand;

class AutoCorrectPrefsDialogController : public CDialogController
{
public:
	// ----- Initialization -----
	
						AutoCorrectPrefsDialogController(IPMUnknown *boss);
	virtual				~AutoCorrectPrefsDialogController();
	
	// ----- Dialog protocol -----

	virtual void		InitializeDialogFields(IActiveContext* context);
	virtual WidgetID	ValidateDialogFields(IActiveContext* myContext);
	virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};


#endif