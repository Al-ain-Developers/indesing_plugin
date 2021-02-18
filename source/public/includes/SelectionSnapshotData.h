//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SelectionSnapshotData.h $
//  
//  Owner: Rich Gartland
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
#ifndef __SelectionSnapshotData__
#define __SelectionSnapshotData__

#include "InterfacePtr.h"
#include "ISelectionSnapshotSuite.h"

//---------------------------------------------------------------
//
//	class SelectionSnapshotData
//
//---------------------------------------------------------------
/**
	A data container which is passed into ISelectionSnapshotSuite routines.
	This container wraps a snapshot of selection information in a way that
	specifies nothing of the selection model. It is not a Shuksan
	object model interface, but simply an abstract interface from which implementation
	classes derive.
*/
class SelectionSnapshotData INHERITFROM
{
public:
	virtual ~SelectionSnapshotData() {}

	/**
		Get the ClassID of the concrete selection boss for the selection model being snapshotted.
		@return The ClassID for the selection's csb.
	*/
	virtual ClassID GetOwningCSBClass() const = 0;

protected:
	SelectionSnapshotData() {};

private:	
	// Disallow copy & assignment to avoid possible splicing
	SelectionSnapshotData(const SelectionSnapshotData& other);
	SelectionSnapshotData& operator=(const SelectionSnapshotData& other);
};


//---------------------------------------------------------------
//
//	class SelectionSnapshotDesc
//
//---------------------------------------------------------------

/** A more specific wrapper for a selection snapshot, allowing access to its data, via
	a pointer to an ISelectionSnapshotSuite.
 */
class SelectionSnapshotDesc  : public SelectionSnapshotData {
public:
	typedef object_type data_type;
	SelectionSnapshotDesc(const ClassID owningCSBClass, const ISelectionSnapshotSuite* adoptSnapShotData) : fCSBClass(owningCSBClass), fSnapshotData(adoptSnapShotData) {}

	/**
		Get the ClassID of the concrete selection boss for the selection model being snapshotted.
		@return The ClassID for the selection's csb.
	*/
	virtual ClassID 			GetOwningCSBClass() const { return fCSBClass; }

	/**
		Get a pointer to the ISelectionSnapshotSuite associated with this snapshot.
		@return ISelectionSnapshotSuite pointer provided to this object's constructor.
	*/
	const ISelectionSnapshotSuite* GetSnapShotData() const { return fSnapshotData.get(); };

private:
	// Disallow copy & assignment to avoid possible splicing
	SelectionSnapshotDesc(const SelectionSnapshotDesc& copy);
	SelectionSnapshotDesc& operator=(const SelectionSnapshotDesc& other);

	// Data
	ClassID										fCSBClass;
	InterfacePtr<const ISelectionSnapshotSuite>	fSnapshotData;
};

#endif		// __SelectionSnapshotData__
