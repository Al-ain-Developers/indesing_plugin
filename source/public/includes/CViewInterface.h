//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CViewInterface.h $
//  
//  Owner: Mat Marcus
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
#ifndef __CViewInterface__
#define __CViewInterface__


#include "CPMUnknown.h"
#include "IViewObjectChanges.h"
#include "MetaProgramming.h"

//========================================================================================
// CViewInterface
//========================================================================================

//	
/**	Base class for snapshot view interfaces. Use of snapshot view interfaces is extremely rare in 
	the application codebase. They should only be used if absolutely necessary.
	For example, ILayoutControlData on the layout widget is a snapshot view interface. 
	The data in this interface is depended on by many other objects and must be kept 
	in tight synchronisation with the database at all times. 

	Background:

	Suppose that you have a user interface object such as a widget that has data that depends on
	model objects that persist in a database that supports undo and your data needs to be
	updated when the model objects it depends on are modified, or when modifications are undone or redone.
	You have concluded that you cannot use lazy notification to update your data because it
	must be kept up to date with changes to the model at all times.

	The state of a snapshot view interface is snapshot before it is changed, reverted on undo and
	restored on redo. It is very similar to a snapshot interface.
	The distinction is that the database a snapshot interface is associated with is fixed and is implicitly
	defined by the persistent boss it is aggregated on. A snapshot view interface on the other hand, is
	part of a user interface object and must explicitly identify the database containing the model
	objects it depends on. Also, it is not fixed to be one specific database. For example, a widget
	that tracks some state in the front document must change the target database when the front
	document changes.

	To implement a snapshot view interface:

	1. Aggregate IID_IVIEWOBJECTCHANGES on the user interface boss class and use the
	implementation, kViewObjectChangesImpl, provided by the API.

	2. Aggregate your snapshot view interface on the user interface boss class.

	3. Provide an abstract interface for your snapshot view interface that uses IPMUnknown as a base
	class, IYourViewableInterface for example.

	4. Provide an implementation of this IYourViewableInterface using the templated class
	CViewInterface. For example:
	class YourViewableInterface : public CViewInterface<IYourViewableInterface>

	5. Use CREATE_VIEW_PMINTERFACE to make your implementation class available to the
	application (instead of CREATE_PMINTERFACE).

	6. Define a SnapshotReadWrite method for your implementation class, it gets called to serialize
	snapshots of your data when needed.

	7. Call PreDirty within mutator methods before changing member variables that you serialize
	in SnapshotReadWrite.

	8. When the model objects you depend on are changed call mutator methods to modify the
	state of your interface. The application takes a snapshot of your interface, reverts the state
	on undo and restores it on redo.

	9. When your Reset method is called forcibly rebuild the data in the interface. For example,
	imagine a panel that has a snapshot view interface that tracks data from the front document.
	Consider performing a set of operations on a document with a panel closed. When the
	panel opens it refreshes and displays information from the front document. As the document
	is modified by subsequent operations the snapshot view interface tracks the changes. If the
	user performs undo on the document, to a point prior to when the panel was opened, a
	mechanism is required to forcibly rebuild the data in the snapshot view interface. The Reset
	method provides that functionality.

	10. Make sure the target database is set by calling IViewObjectChanges::SetTargetDB
		on the interface that resides on the same boss.

	@see IViewObjectChanges
*/
template <class Interface>
class CViewInterface : public Interface
{
public:
	/** @see IPMUnknown::QueryInterface() */
	IPMUnknown *QueryInterface(PMIID interfaceID) const;
	/** @see IPMUnknown::AddRef() */
	void AddRef() const;
	/** @see IPMUnknown::Release() */
	void Release() const;

	/**	For internal use
		@param prop 
		@param allowModification 
	 */
	void PreDirty(ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

	/*fViewIFaceConsistencyChecker is used only to produce compiler errors 
		if people by mistake to not use CREATE_VIEW_PMINTERFACE to go along with CViewInterface
	*/ 
	void* fViewIFaceConsistencyChecker;
protected:
	explicit CViewInterface(IPMUnknown *boss);	
	HelperInterface fHelperInterface;
};


template <class Interface>
CViewInterface<Interface>::CViewInterface(IPMUnknown *boss) :
fHelperInterface(boss), fViewIFaceConsistencyChecker(nil)
{
}

template <class Interface>
void CViewInterface<Interface>::AddRef() const
{
	fHelperInterface.AddRef();
}
	
template <class Interface>
void CViewInterface<Interface>::Release() const
{
	fHelperInterface.Release();
}

template <class Interface>
IPMUnknown* CViewInterface<Interface>::QueryInterface(PMIID interfaceID) const
{
#ifdef DEBUG
	if (interfaceID == IID_IGETINTERFACEIMPL)
		return const_cast<CViewInterface<Interface> *>(this);
#endif
		
	return fHelperInterface.QueryInterface(interfaceID);
}

template <class Interface>
void CViewInterface<Interface>::PreDirty(ImplementationID prop, bool16 allowModification)
{
	InterfacePtr<IViewObjectChanges>viewObjectChanges (this, UseDefaultIID());
	if (viewObjectChanges)
	{
		InterfacePtr<IControllingUnknown>boss(this, IID_IUNKNOWN);
		viewObjectChanges->SetDirty(boss, this, prop, allowModification);
	}
}

#endif //__CViewInterface__
