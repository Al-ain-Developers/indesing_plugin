//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StoryListNodeID.h $
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

#ifndef __StoryListNodeID__
#define __StoryListNodeID__


#include "NodeID.h"
#include "IPMStream.h"
#include "IAssignmentMgr.h"
#include "AssignmentUIID.h"

//========================================================================================
// class StoryListNodeID 
//========================================================================================
class StoryListNodeID : public NodeIDClass
{
public:
	enum { kNodeType = kStoryListNodeIDClass }; //We just use the tree view widget for convenience
	enum { kInvalidIndex = -1 };
	typedef enum { kRootNodeType = 0x0001, 
				   kDocNodeType = 0x0010,
				   kAssignmentNodeType = 0x0100,
				   kStoryNodeType = 0x1000,
				   kAllNodeType = 0x1110 } StoryListType;
/* 
	assignment node has	: AssignmentName, AssignmentWriter
	document node has	: AssignmentName, AssignmentWriter, IAssignedDocument
	story node has		: AssignmentName, Assignmentwriter, IAssignedDocument, StoryName, StoryFilePath
*/
	
	static	NodeID_rv	Create() {return new StoryListNodeID(UIDRef::gNull, kRootNodeType);}
	
	static	NodeID_rv	Create(const UIDRef& itemRef, StoryListType type)
						{ return new StoryListNodeID(itemRef, type); }
	
	virtual ~StoryListNodeID() { }
	
	virtual	NodeType		GetNodeType() const { return kNodeType; }
	
	virtual int32			Compare(const NodeIDClass* NodeID) const;
	virtual NodeIDClass*	Clone() const;
	virtual void			Read(IPMStream*	stream);
	virtual void			Write(IPMStream*	stream) const;
	
	virtual void			GetAssignmentPath(PMString& name) const;
	virtual UIDRef			GetContentRef() const;
	virtual void			GetUIDRef(UIDRef& ref) const;
	virtual UIDRef			GetUIDRef() const;
	virtual UIDRef			GetRawUIDRef() const;
	virtual void			GetStoryPath(PMString& name) const;

	virtual	StoryListType	GetStoryListType() const { return fType; }
	virtual	PMString		GetDescription() const ;
			
private:
	StoryListNodeID(const UIDRef& ref, const StoryListType type);

	int32 CompareUIDRefs(const UIDRef& one, const UIDRef& two) const;

	StoryListType				fType;
	UIDRef						fUIDRef;

};

#endif
