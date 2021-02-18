//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/OwnerDrawMenu.h $
//  
//  Owner: Matt Joss
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
#ifndef __OwnerDrawMenu__
#define __OwnerDrawMenu__

#include "IOwnerDrawMenu.h"
#include <map>

class IControlView;

class WIDGET_DECL OwnerDrawMenu : public CPMUnknown<IOwnerDrawMenu>
{
public:
	OwnerDrawMenu(IPMUnknown* boss);
	
	virtual void 			DrawMenuItem(IViewPort* viewPort, ActionID menuActionID, const SysRect& itemRect, bool16 isCurrentlySelectedItem, int16 actionState);

	virtual void 			MeasureItem(ActionID menuActionID,  uint16* outItemWidth, uint16* outItemHeight);

	virtual void			AddMenuWidget( ActionID menuActionID,  IControlView* widget );
	virtual void			RemoveMenuWidget( ActionID menuActionID, bool16 deleteUID = kTrue );
	virtual void 			RemoveAllMenuWidgets( bool16 deleteUID = kTrue );

	virtual bool16			IsValidActionID(ActionID actionID);

	virtual void ReadWrite(IPMStream *s, ImplementationID prop);

protected:
	IControlView*	GetWidgetForAction(ActionID menuActionID);
	virtual void	DrawHilite(SysPort port, IControlView* menuView, bool16 isCurrentlySelectedItem);
	virtual void	HandleEnablement(IControlView* menuView, int16 actionState);

private:
	std::map<ActionID, int32>	fActionToIndexMap;
};

#endif //__OwnerDrawMenu__
