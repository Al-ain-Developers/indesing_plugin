//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDVUINodeRef.h $
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IDVUINODEREF__
#define __IDVUINODEREF__

#include "IPMUnknown.h"
#include "DV_WidgetID.h"

#include "DVAForwardDeclarations.h"

#include "boost/cast.hpp"


/** This interface exists on the window and view bosses that wrap a drover window or control.
		These wrapper bosses bridge between InDesign views and windows, and the drover/dvaui.
*/

class IDV_UI_NodeRef : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IDV_UI_NODEREF};

	/** Get the UI_Node this boss corresponds to
	*/
	virtual dvaui::ui::UI_Node*			Get_UI_Node() const = 0;

	/** Set the UI_Node this boss corresponds to
	*/
	virtual void						Set_UI_Node(dvaui::ui::UI_Node*) = 0;


	/** Convenience methods
	*/
	template<class Target> 
	inline static Target* Get_UI_Node_As(dvaui::ui::UI_Node* node)
	{
		return ((node) ? dynamic_cast<Target*>(node) : nil);
	}

	template<class Target> 
	inline static Target* Get_UI_Node_As(IDV_UI_NodeRef* ref)
	{
		return ((ref && ref->Get_UI_Node()) ? dynamic_cast<Target*>(ref->Get_UI_Node()) : nil);
	}

	template<class Target> 
	inline static Target* Get_UI_Node_As(const IPMUnknown* ref)
	{
		InterfacePtr<IDV_UI_NodeRef> nodeRef(ref, UseDefaultIID());
		return ((nodeRef && nodeRef->Get_UI_Node()) ? dynamic_cast<Target*>(nodeRef->Get_UI_Node()) : nil );
	}

	template<class Target> 
	inline Target* Get_UI_Node_As() const
	{
		return Get_UI_Node_As<Target*>(Get_UI_Node());
	}

};

#endif
