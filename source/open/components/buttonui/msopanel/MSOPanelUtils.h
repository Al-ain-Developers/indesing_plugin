//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelUtils.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __MSOPanelUtils__
#define __MSOPanelUtils__

#include "IAppearanceSuite.h"

class ITreeViewMgr;
class IDocument;

namespace MSOPanelUtils
{
	void RebuildTreeViewList(ITreeViewMgr *treeViewMgr);
	bool16 SelectActiveAppearance(ITreeViewMgr *treeViewMgr = nil);
	Form::AppearanceState GetSelectedAppearance();
	void EnableSelectedStateNameILE();

	ErrorCode CreateMSO(IAppearanceSuite::MultiItemSelectionPolicy multiItemSelectionPolity = IAppearanceSuite::kHandleItemsIndividually);

	enum StateLocation { kOnTop, kAboveActive, kBelowActive };
	ErrorCode CreateNewState(StateLocation location, Form::AppearanceState wrtToThisState);

	ErrorCode DeleteState(Form::AppearanceState stateToDelete);
	ErrorCode ReleaseState(Form::AppearanceState stateToDelete);
	ErrorCode ReleaseAllStates();

	bool StateExists(const PMString& stateName);

	void AcceptMSONameIfNeeded(IAppearanceSuite *iAppearanceSuite);
}
#endif // __MSOPanelUtils__