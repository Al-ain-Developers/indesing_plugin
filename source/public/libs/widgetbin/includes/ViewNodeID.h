//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/ViewNodeID.h $
//  
//  Owner: Bob Freeman
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

#ifndef __VIEWNODEID__
#define __VIEWNODEID__

#include "NodeID.h"
#include "IPMStream.h"
#include "widgetid.h"
#include "IControlView.h"

class DV_WIDGET_DECL ViewNodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kViewNodeID }; 

		static	NodeID_rv		Create() { return new ViewNodeID(); }
		static	NodeID_rv		Create(IControlView* view) { return new ViewNodeID(view); }

		virtual ~ViewNodeID() {}
		
		virtual	NodeType		GetNodeType() const { return kNodeType; } 
		virtual int32			Compare(const NodeIDClass* NodeID) const;
		virtual NodeIDClass*	Clone() const;
		virtual void			Read(IPMStream*	stream);
		virtual void			Write(IPMStream* stream) const;
		virtual PMString		GetDescription() const;
		
		IControlView* GetView() const { return fView; }
	private:
		ViewNodeID():fView(nil) {}
		ViewNodeID(IControlView* theView):fView(theView) {}

		IControlView*	fView;
};

#endif //__VIEWNODEID__
