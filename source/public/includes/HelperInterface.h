//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HelperInterface.h $
//  
//  Owner: Robin_Briggs
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
//  
//  The purpose of HelperInterface is to make it easier to define
//  the functions from IPMUnknown that are required for every interface.
//  HelperInterface defines a class, HelperInterface, that implements
//  QueryInterface, AddRef, and Release. HelperInterface is designed to
//  be included in the implementation class of an interface as a member
//  variable. HelperInterface defines a set of macros that allow a
//  mapping from the QueryInterface, AddRef, and Release in the implementation
//  class, and the ones in HelperInterface.
//  
//  How to use HelperInterface:
//  1. In the class's declaration, include DECLARE_HELPER_METHODS.
//  2. Where the class is defined, include DEFINE_HELPER_METHODS.
//  3. In the constructor for the class, include INIT_HELPER_METHODS.
//  
//  Example:
//  class Foo : public IFoo {
//  public:
//  Foo(IPMUnknown *boss);
//  void Bar();
//  DECLARE_HELPER_METHODS()
//  
//  DEFINE_HELPER_METHODS(Foo)
//  
//  Foo :: Foo(IPMUnknown *boss) :
//  INIT_HELPER_METHODS(boss)
//  
//========================================================================================

#pragma once
#ifndef __HelperInterface__
#define __HelperInterface__

#include "InterfaceFactory.h"
#include "IPMPersist.h"
#include "PersistUtils.h"
#include "IViewObjectChanges.h"
#include "IControllingUnknown.h"
#include "DBChangesMonitorDisabler.h"
class ObjectModel;

/** This class provides default implementations of QueryInterface, AddRef, and Release
	for implementations that inherit from IPMUnknown. You should not need to access
	this directly; normally, you just inherit from CPMUnknown to get this functionality.
	@see IPMUnknown
	@see CPMUnknown
*/
class HelperInterface
{
	friend class ObjectModelBase;

public:
	/** Constructor. */
	HelperInterface(IPMUnknown *boss) :
#ifdef DEBUG
		fInterfaceRefCount(0),
#endif
		fBoss(boss)
		{}

	/** Default implementation of QueryInterface. Calls the boss to handle the query.
		Does nothing if there is no boss.
		@see IPMUnknown::QueryInterface()
	*/
	IPMUnknown *QueryInterface(PMIID interfaceID) const
	{
#if DEBUG
		if (interfaceID == IID_IINTERFACEREFCOUNT)
			return (IPMUnknown *)fInterfaceRefCount;
#endif
		if (interfaceID == IID_ICONTROLLINGUNKNOWN && fBoss)
		{
			fBoss->AddRef();
			return fBoss;
		}

		return fBoss ? fBoss->QueryInterface(interfaceID) : nil;
	}
	/** Default implementation of AddRef. Calls the boss to handle it.
		Does nothing if there is no boss.
		@see IPMUnknown::AddRef()
	*/
	void AddRef() const
	{
		if (fBoss)
		{
#if DEBUG
		fInterfaceRefCount++;
#endif
		fBoss->AddRef();
		}
	}
	/** Default implementation of Release. Calls the boss to handle it.
		Does nothing if there is no boss.
		@see IPMUnknown::Release()
	*/
	void Release() const
	{
		if (fBoss)
		{
#if DEBUG
		fInterfaceRefCount--;
#endif
		fBoss->Release();
		}
	}

	/** Return the boss
		@return returns a pointer to the boss object (the IControllingUnknown).
	*/
	IControllingUnknown *GetBoss()
	{
		return static_cast<IControllingUnknown*>(fBoss);
	}

private:
	IPMUnknown *fBoss;

	void SetBoss(IPMUnknown *boss)
		{ fBoss = boss; }

#ifdef DEBUG
public:
	void AddRef(IPMUnknown* whichInterface) const
		{ if (fBoss) ((IControllingUnknown*)fBoss)->DebugAddRef(whichInterface); }
	void Release(IPMUnknown* whichInterface) const
		{ if (fBoss) ((IControllingUnknown*)fBoss)->DebugRelease(whichInterface); }
		// This is here for debugging. Most bosses are PMControllingUnknown,
		// but that's not guaranteed.
	mutable size_t fInterfaceRefCount;
#endif
};


/** This is the macro that goes in the class declaration of an implementation,
	so that it has declarations for the default functions. Normally this is
	done for you if you inherit from CPMUnknown.
*/
#define DECLARE_HELPER_METHODS()	\
public:	\
	IPMUnknown *QueryInterface(PMIID interfaceID) const;	\
	void AddRef() const;	\
	void Release() const;	\
	void PreDirty(ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);	\
	void PreDirtyNoMessage(ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);	\
protected:	\
	HelperInterface fHelperInterface;

#define DECLARE_VIEW_HELPER_METHODS()	\
public:	\
	/*fViewIFaceConsistencyChecker is used only to produce compiler errors \
	if people use the wrong helper method declaraton type \
	while using CREATE_VIEW_PMINTERFACE*/ \
	void* fViewIFaceConsistencyChecker;\
DECLARE_HELPER_METHODS()

#define DECLARE_PERSIST_DONTSNAPHOT_HELPER_METHODS()	\
public:	\
	/*fDontSnapshotIFaceConsistencyChecker is used only to produce compiler errors \
	if people use the wrong helper method declaraton type \
	while using CREATE_PERSIST_DONTSNAPSHOT_PMINTERFACE*/ \
	void* fDontSnapshotIFaceConsistencyChecker;\
DECLARE_HELPER_METHODS()

/** These are the definitions of the default methods used by all interfaces. This
	just tells the implementation class to defer to the HelperInterface for these
	calls. Normally you do not have to use this macro directly, it will be done for
	you if you inherit from CPMUnknown.
*/
#ifndef DEBUG
#define DEFINE_BASIC_HELPER_METHODS(cn)	\
	IPMUnknown * cn::QueryInterface( PMIID interfaceID) const	\
		{return fHelperInterface.QueryInterface(interfaceID); }	\
	void 	cn::AddRef()	const \
		{ fHelperInterface.AddRef(); }	\
	void cn::Release()	const\
		{ fHelperInterface.Release(); }
#else
#define DEFINE_BASIC_HELPER_METHODS(cn)	\
	IPMUnknown * cn::QueryInterface( PMIID interfaceID)	const	\
		{ 															\
			if (interfaceID == IID_IGETINTERFACEIMPL) 				\
		  		{return const_cast<cn*>(this);} 										\
		  return fHelperInterface.QueryInterface(interfaceID); 		\
		  }															\
	void 	cn::AddRef()		const \
		{ fHelperInterface.AddRef(); }	\
	void cn::Release()	const \
		{ fHelperInterface.Release(); }
#endif

#define DEFINE_HELPER_METHODS(cn) \
DEFINE_BASIC_HELPER_METHODS(cn)\
void cn::PreDirty(ImplementationID prop, bool16 allowModification)	\
		{ ::PreDirty(fHelperInterface.GetBoss(), this, prop, allowModification); }	\
void cn::PreDirtyNoMessage(ImplementationID prop, bool16 allowModification)	\
		{ ::PreDirtyNoMessage(fHelperInterface.GetBoss(), this, prop, allowModification); }	

#define DEFINE_VIEW_HELPER_METHODS(cn) \
DEFINE_BASIC_HELPER_METHODS(cn)\
void cn::PreDirty(ImplementationID prop, bool16 allowModification)	\
		{\
			InterfacePtr<IViewObjectChanges>viewObjectChanges (this, UseDefaultIID());\
			if (viewObjectChanges)\
				viewObjectChanges->SetDirty(fHelperInterface.GetBoss(), this, prop, allowModification);\
		} \
void cn::PreDirtyNoMessage(ImplementationID prop, bool16 allowModification)	\
	{ ASSERT_FAIL("Not appropriate for ViewInterfaces"); }

#define DEFINE_PERSIST_DONTSNAPHOT_HELPER_METHODS(cn) \
DEFINE_BASIC_HELPER_METHODS(cn)\
void cn::PreDirty(ImplementationID prop, bool16 allowModification)	\
		{\
			IDataBase* db = ::GetDataBase(fHelperInterface.GetBoss());\
			DBChangesMonitorDisabler disabler(db);\
			::PreDirty(fHelperInterface.GetBoss(), this, prop, allowModification); \
		} \
void cn::PreDirtyNoMessage(ImplementationID prop, bool16 allowModification)	\
		{\
			IDataBase* db = ::GetDataBase(fHelperInterface.GetBoss());\
			DBChangesMonitorDisabler disabler(db);\
			::PreDirtyNoMessage(fHelperInterface.GetBoss(), this, prop, allowModification);\
		}	

/** This is the macro to call in the implementation's constructor's argument list to
	initialize the HelperInterface in the implementation.
*/
#define HELPER_METHODS_INIT(boss)	fHelperInterface(boss)

/** Macro that can optionally be called for DONTSNAPSHOT implementations instead of calling HELPER_METHODS_INIT. This macro also
	initializes fDontSnapshotIFaceConsistencyChecker. */
#define DONTSNAPSHOT_HELPER_METHODS_INIT(boss)	HELPER_METHODS_INIT(boss), fDontSnapshotIFaceConsistencyChecker(nil)

#endif // __HelperInterface__
