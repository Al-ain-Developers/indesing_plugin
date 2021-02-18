//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/StringNodeID.h $
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

#ifndef __STRINGNODEID__
#define __STRINGNODEID__

#include "NodeID.h"
#include "IPMStream.h"
#include "widgetid.h"

class WIDGET_DECL StringNodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kStringNodeID }; 

		static	NodeID_rv		Create() { return new StringNodeID(); }
		static	NodeID_rv		Create(const PMString& pathListString) { return new StringNodeID(pathListString); }

		virtual ~StringNodeID() {}
		
		virtual	NodeType		GetNodeType() const { return kNodeType; } 
		virtual int32			Compare(const NodeIDClass* NodeID) const;
		virtual NodeIDClass*	Clone() const;
		virtual void			Read(IPMStream*	stream);
		virtual void			Write(IPMStream* stream) const;
		virtual PMString		GetDescription() const;
		
		const PMString& GetString() const { return fString; }
	private:
		StringNodeID() {}
		StringNodeID(PMString theString):fString(theString) {}

		PMString	fString;
};

#endif //__STRINGNODEID__
