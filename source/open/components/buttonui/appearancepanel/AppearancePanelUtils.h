//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelUtils.h $
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
//========================================================================================

#pragma once
#ifndef __AppearancePanelUtils__
#define __AppearancePanelUtils__

#include "FormFieldTypes.h"

class IDocumentLayer;
class ICommand;
class IPanelControlData;
class UIDList;

void GetSelectedStates(K2Vector<int32>&,K2Vector<Form::AppearanceState>&, IPanelControlData*);

bool16 CanDeleteSelectedStates(IPanelControlData*);
bool16 CanCreateNewState();
bool16 HasStateContent(IPanelControlData* panelData);
//tw bool16 CanDuplicateSelectedLayers(IPanelControlData*);

enum LayerLocation { kOnTop, kAboveActive, kBelowActive };
void CreateNewState();
ErrorCode DuplicateStates(IPanelControlData*);
ErrorCode DeleteSelectedStates(IPanelControlData*);
ErrorCode DeleteSelectedStateContent(IPanelControlData*);
ErrorCode PlaceIntoSelectedState(IPanelControlData* inPanelData);

void InvokeStatePropertiesDialog(Form::AppearanceState inState);

bool16 CanDoStatePropertiesDialog(Form::AppearanceState inState);
void DoStatePropertiesDialog(Form::AppearanceState inState);

#endif // __AppearancePanelUtils__