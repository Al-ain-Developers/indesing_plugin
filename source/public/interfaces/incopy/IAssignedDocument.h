//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignedDocument.h $
//  
//  Owner: Jon Pugh
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

#pragma once
#ifndef _IAssignedDocument_
#define _IAssignedDocument_

#include "AssignmentID.h"

#include "IAssignment.h"

typedef K2Vector<PMString> AssignmentStringList;

/** This class is used to manage the list of assignments in an InDesign document.
	This object is added into kDocBoss, so you can get it from the RootUID of the IDataBase.
	
	@see IAssignment
*/
class IAssignedDocument : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNEDDOCUMENT };
	
	/**
		Add an assignment to the document.  Must be called from a command.
		@param assignment The assignment to add to the document.
	*/
	virtual void AddAssignment(IAssignment* assignment) = 0;

	/**
		Remove an assignment from the document.  Must be called from a command.
		@param assignment The assignment to remove.
	*/
	virtual void RemoveAssignment(IAssignment* assignment, bool16 deleteFile) = 0;

	/**
		Moves an assignment before another assignment.
		@param assignment - The assignment to move.
		@param beforeAssignment - The assignment to move in front of.  Pass nil to move to the end of the list.
	*/
	virtual void MoveAssignment(IAssignment* assignment, IAssignment* beforeAssignment) = 0;

	/**
		Returns the list of assignments in this document. 
		Can supply a const_iterator.
		@return A constant reference to the assignment list.
	*/
	virtual UIDList		GetAssignments() const = 0;

	/**
		Moves an assignment before another assignment.
		@param assignment - The assignment to move.
		@param beforeAssignment - The assignment to move in front of.  Pass nil to move to the end of the list.
	*/
	virtual ErrorCode MoveAssignmentCmd(IAssignment* assignment, IAssignment* beforeAssignment) = 0;

};

typedef InterfacePtr<IAssignedDocument> IAssignedDocumentPtr;
typedef K2Vector<IAssignedDocument*> IAssignedDocumentList;

#endif //_IAssignedDocument_
