//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVOwnerDrawMenu.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __DVOwnerDrawMenu__
#define __DVOwnerDrawMenu__

#include "IDVOwnerDrawMenu.h"
#include <map>

class IControlView;

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

class DV_WIDGET_DECL DVOwnerDrawMenu : public CPMUnknown<IDVOwnerDrawMenu>
{
public:
	DVOwnerDrawMenu(IPMUnknown* boss);
	
	virtual void DrawMenuItem(IGraphicsContext *oc, ActionID menuActionID, const SysRect& itemRect, bool16 isCurrentlySelectedItem, int16 actionState);

	virtual void MeasureItem(ActionID menuActionID,  uint16* outItemWidth, uint16* outItemHeight);

	virtual void AddMenuWidget( ActionID menuActionID,  IControlView* widget );
	virtual void RemoveMenuWidget( ActionID menuActionID, bool16 deleteUID = kTrue );
	virtual void RemoveAllMenuWidgets( bool16 deleteUID = kTrue );

	virtual bool16 IsValidActionID(ActionID actionID);
	
	virtual PMReal GetMenuViewScale();
	virtual void SetMenuViewScale(PMReal scale);

	virtual void ReadWrite(IPMStream *s, ImplementationID prop);

protected:
	IControlView *GetWidgetForAction(ActionID menuActionID);
	virtual void DrawHilite(dvaui::drawbot::Drawbot *drawbotP, IControlView* menuView, bool16 isCurrentlySelectedItem);
	virtual void HandleEnablement(IControlView* menuView, int16 actionState);

private:
	std::map<ActionID, int32>	fActionToIndexMap;
	PMReal fScale;
};

#pragma export off

#endif //__DVOwnerDrawMenu__
