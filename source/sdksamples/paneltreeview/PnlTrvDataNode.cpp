//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvDataNode.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes

// Other API includes
#include "K2Vector.tpp"

// Project includes
#include "PnlTrvDataNode.h"
#include "PnlTrvUtils.h"

/**
	@ingroup paneltreeview
*/

/* Constructor
*/
PnlTrvDataNode::PnlTrvDataNode() : fParent(nil)
{
}


/* Destructor
*/
PnlTrvDataNode::~PnlTrvDataNode()
{
}


/* Copy constructor
*/
PnlTrvDataNode::PnlTrvDataNode(const PnlTrvDataNode& rhs) : fParent(nil)
{
	deepcopy(rhs);
}

/* Overloaded =
*/
PnlTrvDataNode& PnlTrvDataNode::operator=(const PnlTrvDataNode& rhs)
{
	deepcopy(rhs);
	return *this;
}


/* Overloaded ==
*/
bool PnlTrvDataNode::operator==(const PnlTrvDataNode& rhs) const
{
	return		this->fParent == rhs.fParent && 
				this->fPathData == rhs.fPathData &&
				this->fChildren == rhs.fChildren;
}


/* deepcopy
*/
void PnlTrvDataNode::deepcopy(const PnlTrvDataNode& rhs)
{
	this->fChildren.clear();
	this->fChildren.assign( rhs.fChildren.begin(), rhs.fChildren.end());
	this->fParent = rhs.fParent;
	this->fPathData = rhs.fPathData;
}


/* GetNthChild
*/
const PnlTrvDataNode& PnlTrvDataNode::GetNthChild(
	int32 indexInParent) const
{
	return this->fChildren.at(indexInParent);
}


/* AddChild
*/
void PnlTrvDataNode::AddChild(const PnlTrvDataNode& o)
{
	this->fChildren.push_back(o);
}


/* RemoveChild
*/
void PnlTrvDataNode::RemoveChild(const PnlTrvDataNode& o)
{
	K2Vector<PnlTrvDataNode>::iterator result = std::find(fChildren.begin(), 
													fChildren.end(), o);

	if(result != fChildren.end())
	{
		fChildren.erase(result);
	}
}


/* GetParent
*/
PnlTrvDataNode* PnlTrvDataNode::GetParent() const
{
	return this->fParent;
}


/* SetParent
*/
void PnlTrvDataNode::SetParent(const PnlTrvDataNode* p)
{
	this->fParent = const_cast<PnlTrvDataNode* >(p);
}


/* ChildCount
*/
int32 PnlTrvDataNode::ChildCount() const
{
	return this->fChildren.size();
}


/* SetData
*/
void PnlTrvDataNode::SetData(const PMString& data)
{
	this->fPathData = data;
}


/* GetData
*/
PMString PnlTrvDataNode::GetData() const
{
	return this->fPathData;
}

//	end, File:	PnlTrvDataNode.cpp
