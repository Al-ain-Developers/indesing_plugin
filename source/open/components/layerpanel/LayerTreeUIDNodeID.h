//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerTreeUIDNodeID.h $
//  
//  Owner: lance bushore
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

#ifndef __LayerTreeUIDNodeID__
#define __LayerTreeUIDNodeID__

#include "NodeID.h"
#include "LayerPanelID.h"

//========================================================================================
// class LayerTreeUIDNodeID 
//========================================================================================
class LayerTreeUIDNodeID : public NodeIDClass
{
public:
	enum { kNodeType = kLayerTreeNodeID }; 
	
	virtual ~LayerTreeUIDNodeID();
	
	virtual	NodeType		GetNodeType() const { return kNodeType; }
	virtual int32			Compare(const NodeIDClass* NodeID) const;
	virtual NodeIDClass*	Clone() const;
	virtual void			Read(IPMStream*	stream);
	virtual void			Write(IPMStream*	stream) const;
	virtual PMString		GetDescription() const;
	
	UID				GetUID() const;
	bool16				IsLayerEntry() const;

	static	NodeID_rv		Create( const UID& uid, bool16 isLayerEntry ) { return new LayerTreeUIDNodeID(uid, isLayerEntry); }
private:
	LayerTreeUIDNodeID( const UID& uid, bool isLayerEntry );
	LayerTreeUIDNodeID();
	LayerTreeUIDNodeID(const LayerTreeUIDNodeID& copy);

	UID fUID;
	bool16 fIsLayerEntry;
};

#endif
