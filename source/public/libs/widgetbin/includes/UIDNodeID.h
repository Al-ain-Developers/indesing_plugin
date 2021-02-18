//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/UIDNodeID.h $
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

#ifndef __UIDNodeID__
#define __UIDNodeID__


#include "NodeID.h"
#include "IPMStream.h"
#include "widgetid.h"

#pragma export on

//========================================================================================
// class UIDNodeID 
//========================================================================================
class DV_WIDGET_DECL UIDNodeID : public NodeIDClass
{
public:
	enum { kNodeType = kUIDNodeID }; 

	virtual ~UIDNodeID() { }
	
	virtual	NodeType		GetNodeType() const { return kNodeType; }
	virtual int32			Compare(const NodeIDClass* NodeID) const;
	virtual NodeIDClass*	Clone() const;
	virtual void			Read(IPMStream*	stream);
	virtual void			Write(IPMStream*	stream) const;
	virtual PMString		GetDescription() const;

			UID				GetUID() const { return fUID; }

	static	NodeID_rv		Create( const UID& uid ) { return new UIDNodeID(uid); }
private:
	UIDNodeID(UID uid) { fUID = uid; }
	UID			fUID;
};


#pragma export off

#endif
