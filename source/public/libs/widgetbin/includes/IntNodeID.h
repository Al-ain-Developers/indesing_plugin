//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/IntNodeID.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __IntNodeID_h__
#define __IntNodeID_h__

#include "NodeID.h"
#include "IPMStream.h"

const int kIntNodeID = 6;		// This value is not used

//========================================================================================
// CLASS BehaviorsTreeViewAdapter
//========================================================================================

class IntNodeID : public NodeIDClass
{
public:	
	enum { kNodeType = kIntNodeID };
	
	static NodeID_rv Create(int32 number)
	{
		return new IntNodeID(number);
	}
	
	virtual NodeType GetNodeType() const { return kNodeType; }

	virtual int32 Compare(const NodeIDClass* node) const
	{
		const IntNodeID* other = static_cast<const IntNodeID*>(node);

		if ( fNumber < other->fNumber)
			return -1;
		else if (fNumber > other->fNumber)
			return 1;
		else
			return 0;
	}
	
	virtual NodeIDClass* Clone() const
	{
		return new IntNodeID(fNumber);
	}
	
	virtual void Read(IPMStream* stream)
	{
		stream->XferInt32(fNumber);
	}
	
	virtual void Write(IPMStream* stream) const
	{
		stream->XferInt32(fNumber);
	}
	
	int32 Get() const
	{
		return fNumber;
	}
	
private:
	IntNodeID(int32 number) :
		fNumber(number)
	{
	};

private:
	mutable int32 fNumber;
};

#endif // __IntNodeID_h__

