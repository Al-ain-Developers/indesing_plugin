//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/NodeID.h $
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

#ifndef __NodeID__
#define __NodeID__


//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
#include "IPMStream.h"
#include "K2Vector.h"

class NodeID;
class NodeID_rv;

typedef K2Vector<NodeID> NodeIDList;		// Sorted vector

void K2Read(IPMStream*	stream, NodeID& ref);
void K2Write(IPMStream*	stream, const NodeID& ref);

bool16	DV_WIDGET_DECL operator ==(const NodeID& a, const NodeID& b);
bool16	DV_WIDGET_DECL operator !=(const NodeID& a, const NodeID& b);
bool16	DV_WIDGET_DECL operator  <(const NodeID& a, const NodeID& b);
bool16	DV_WIDGET_DECL operator  >(const NodeID& a, const NodeID& b);
bool16	DV_WIDGET_DECL operator <=(const NodeID& a, const NodeID& b);
bool16	DV_WIDGET_DECL operator >=(const NodeID& a, const NodeID& b);



//========================================================================================
// class NodeIDClass 
//========================================================================================
class NodeIDClass
{
public:
	NodeIDClass() = default;
	virtual ~NodeIDClass() {};
	typedef int32 NodeType;
	
	virtual	NodeType		GetNodeType() const = 0;
	virtual int32			Compare(const NodeIDClass* NodeID) const = 0;
	virtual NodeIDClass*	Clone() const = 0;
	virtual void			Read(IPMStream*	stream) = 0;
	virtual void			Write(IPMStream*	stream) const = 0;
	
	// This is mostly a debug call so that TreeView asserts have more context information
	// Derived class should override this method to print out a description of their nodeID. 
	// For instance, a UIDNodeID may write out the UID and classID.
	virtual PMString		GetDescription() const { return PMString("Override NodeID::GetDescription() to provide useful information here"); };

	// NodeIDClass is not meant to be copied/assigned - it is meant to be cloned, hence deleting the copy constructor & copy assignment.
	NodeIDClass(const NodeIDClass &) = delete;
	NodeIDClass &operator =(const NodeIDClass &) = delete;
};

#pragma export on



// This is just a simple return value class.  It is similar to NodeID, but relinquishes control of its
// NodeIDClass ptr instead of copying it.  Its purpose is easier to see when we consider using NodeID as a 
// return value.  If NodeID is used as a return type, when the return occurs, we will create a new NodeIDClass and
// store that in the NodeID that is created.  When the return occurs, we either use operator= to assign to a new NodeID or
// use NodeID( const NodeID& ) constuctor.  In both cases, the NodeIDClass will be cloned for the new NodeID so the temporary
// NodeID that was used as the return value can destruct its NodeIDClass.  We could change the way operator= and NodeID(const NodeID&)
// work so that they relinquish control of the NodeIDClass instead of cloning, but then code like...
// NodeID x = y; //where y was a NodeID makes y invalid.  This creates bugs that are difficult to find and easy to create.  Instead,
// we create a return value class(NodeID_t).  This way, we can have a constructor NodeID(const NodeID_t& ) which will not clone but will pass
// on responsibility for the NodeIDClass.  Since NodeID_t should only be used for return values, we shouldn't run into the problems mentioned above.

class NodeID_rv
{
public:
    NodeID_rv() = delete;
    NodeID_rv(NodeIDClass* nodeID) : fNodeID(nodeID) {}

    ~NodeID_rv() { ASSERT_MSG(fNodeID == nil, "NodeID_rv::fNodeID should be nil, NodeID_rv should only be used as a return value, and it should always Relinquish() it's NodeIDClass*.  Otherwise we'll leak."); };

    NodeID_rv(const NodeID_rv& other) = delete;
    NodeID_rv &operator =(const NodeID_rv& other) = delete;

    NodeID_rv(NodeID_rv && other) noexcept : fNodeID(other.fNodeID) { other.fNodeID = nil; }
    NodeID_rv &operator =(NodeID_rv&& other) noexcept = delete;

    NodeID_rv(const NodeID& nodeID);
	
	NodeIDClass*	Relinquish() const noexcept  { NodeIDClass* tempNodeID = fNodeID; fNodeID = nil; return tempNodeID; }
	NodeIDClass*	Get() const noexcept { return fNodeID; }
	
private:

	mutable NodeIDClass*			fNodeID;
};

//========================================================================================
// class NodeID 
//========================================================================================
class DV_WIDGET_DECL NodeID
{
public:
  typedef object_type data_type;

	NodeID() : fNodeID(nil) {}
	NodeID(NodeIDClass* nodeID) { fNodeID = nodeID; }
	NodeID( const NodeID_rv& tempNodeID) { fNodeID = tempNodeID.Relinquish(); }
	NodeID( const NodeID& other);
	NodeID(NodeID &&other) noexcept:
		fNodeID(other.fNodeID)
	{
		other.fNodeID = nil;
	}
	NodeID(NodeID_rv&& tempNodeID) noexcept { fNodeID = tempNodeID.Relinquish(); }

	~NodeID() { if (fNodeID)  { delete fNodeID; } }
	
	NodeIDClass::NodeType	GetNodeType() const { if (fNodeID)	return fNodeID->GetNodeType(); else return 0; }
	bool16		IsValid() const { return fNodeID != nil; }
	void		MakeInvalid()  
	{
		if (fNodeID)
			delete fNodeID;
		fNodeID = nil;
	}
	
	
	friend inline void swap(NodeID &a, NodeID &b) noexcept
	{
		std::swap(a.fNodeID, b.fNodeID);
	}

	NodeID&	operator =(const NodeID& other);
	NodeID&	operator =(NodeID&& other) noexcept
	{
		using std::swap;
		swap(*this, other);

		return *this;
	}
	NodeID&	operator =( NodeID_rv& returnValNodeID);
		
//	operator NodeIDClass*() const { return fNodeID; }
//	const NodeIDClass*	operator->() const { return fNodeID; }
	NodeIDClass*	Get() const { return fNodeID; }
	virtual PMString	GetDescription() const { return fNodeID ? fNodeID->GetDescription() : ""; };
	
	static	void	SetNodeIDTemplate( const NodeID& templateNode );
	static	void	ClearNodeIDTemplate( );

	friend void	K2Read(IPMStream*	stream, NodeID& ref);
	friend void K2Write(IPMStream*	stream, const NodeID& ref);
	
	friend bool16	operator ==(const NodeID& a, const NodeID& b);
	friend bool16	operator !=(const NodeID& a, const NodeID& b);
	friend bool16	operator  <(const NodeID& a, const NodeID& b);
	friend bool16	operator  >(const NodeID& a, const NodeID& b);
	friend bool16	operator <=(const NodeID& a, const NodeID& b);
	friend bool16	operator >=(const NodeID& a, const NodeID& b);

private:
	NodeIDClass*			fNodeID;
	static	NodeIDClass*	sNodeIDTemplate;	//defined in CTreeViewMgr.cpp
};


extern DV_WIDGET_DECL NodeID kInvalidNodeID;

//----------------------------------------------------------------------------------------
// NodeID_rv::NodeID_rv
//----------------------------------------------------------------------------------------
inline NodeID_rv::NodeID_rv(const NodeID& nodeID)
{
	fNodeID = nodeID.Get() != nil ? nodeID.Get()->Clone() : nil; 
}
 

template <class TNode>
class TreeNodePtr
{
	public:
//	explicit TreeNodePtr(const NodeID& nodeID) { TNode::kNodeType == nodeID.GetNodeType() ? fNodeClass = static_cast<TNode*>(nodeID.Get()) : nil; }
//	explicit TreeNodePtr(const NodeID_rv& nodeID) { TNode::kNodeType == static_cast<TNode*>(nodeID.Get())->GetNodeType() ? fNodeClass = static_cast<TNode*>(nodeID.Relinquish()) : nil; }
	explicit TreeNodePtr(const NodeID& nodeID) { fNodeClass = TNode::kNodeType == nodeID.GetNodeType() ? static_cast<TNode*>(nodeID.Get()) : nil; }
	explicit TreeNodePtr(const NodeID_rv& nodeID) { fNodeClass = TNode::kNodeType == static_cast<TNode*>(nodeID.Get())->GetNodeType() ? static_cast<TNode*>(nodeID.Relinquish()) : nil; }
//	explicit TreeNodePtr(const NodeID& nodeID);
//	explicit TreeNodePtr(const NodeID_rv& nodeID);
	TNode*	operator->() const { ASSERT_MSG(fNodeClass, "About to use nil TreeNodePtr!"); return fNodeClass; }
	operator TNode*() const { return fNodeClass; }
	
	void	reset(const NodeID& nodeID) { fNodeClass = static_cast<TNode*>(nodeID.Get()); }
	private:
		TNode*	fNodeClass;
};

#pragma export reset

#endif
