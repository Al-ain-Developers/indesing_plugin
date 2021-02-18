//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVPanelControlData.h $
//  
//  Owner: Dave Burnard
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVPanelControlData__
#define __DVPanelControlData__
	
#include "AbstractPanelControlData.h"

#include "DVAForwardDeclarations.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	IPanelControlData baseclass used for widgets in the Drover world.
*/

class DV_WIDGET_DECL DVPanelControlData : public AbstractPanelControlData
{
public:
	// ----- Initialization -----
	DVPanelControlData(IPMUnknown *boss); 
	virtual ~DVPanelControlData();
	
	virtual void			ReadWrite(IPMStream *s, ImplementationID prop);
		
	// ----- Maintenance -----
	virtual void			AddWidget(IControlView *w, int32 at = -1, bool16 invalidate = kTrue);
	virtual void			RemoveWidget(IControlView *w, bool16 invalidate = kTrue, bool16 deleteUID = kFalse);
	virtual void			MoveWidget(IControlView *w, int32 at, bool16 invalidate = kTrue);
	virtual void			RemoveWidget(int32 index, bool16 invalidate = kTrue, bool16 deleteUID = kFalse);
	virtual void			ReleaseAll(bool16 deleteUID = kTrue);
	
	// ----- Inquisition -----
	virtual IControlView*	GetWidget(int32 index) const;
	virtual bool16			GetWidgetVisibleState(int32 index) const;
	virtual bool16			IsWidgetInstantiated(int32 index) const;
	virtual int32			GetIndex(const IControlView *w) const;
	virtual int32			Length() const;
	

	// ----- Notification -----
	virtual void			WidgetAttributeChanged(IControlView* view, const WidgetAttributeID& id);

	// ----- UI_Node -----
	void					Set_UI_Node(dvaui::ui::UI_Node*);
	void					Release_UI_Node();

protected:
	void					AddToWidgetList(IControlView* view, int32 at = -1, bool16 invalidate = kTrue, bool16 invalidateTransform = kTrue);
	
	dvaui::ui::UI_Node*		GetUI_NodeFromWidget(const IPMUnknown *w) const;


private:	
	// When safe, Get_UI_Node will query another interface to check for IControlView initialization
	//	calling from within or ReadWrite while is not safe, but some other methods are safe.
	enum QuerySafety {eNotSafeToQuery = 0, eSafeToQuery}; 
	dvaui::ui::UI_Node*		Get_UI_Node(QuerySafety safeToQueryForUINode = eSafeToQuery) const;

	// ----- Consistency check of UI_Node's children vs our internal child widget list -----
	bool					Internal_ConsistencyCheck() const;
	bool					Internal_SizeCheck() const;

	// ----- Persistent data -----
	// We maintain a child widget list in parallel with the actual UI_Node hierarchy. This list is used for persistence.
	// Trying to persist based on the UI_Node hierarchy leads to ReadWrite problems during shutdown in the UIDCheckStream
	K2Vector<IControlView *>		fWidgetList;	 

	// ----- Non-persistent data -----
	// Private implementation class
	class PrivateImpl;
	PrivateImpl*			Impl() const {return fImpl;}
	PrivateImpl*			fImpl;
};

#pragma export off

#endif

