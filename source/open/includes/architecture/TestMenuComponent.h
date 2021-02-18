//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/TestMenuComponent.h $
//  
//  Owner: robin briggs
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
//  A test menu item adds a line to the Test menu, and associates it with
//  two functions. The first function is called when the user selects the item
//  on the menu. The second is called to disable, check, or rename the menu item. 
//  
//  How to add an item or group of items to the test menu:
//  (1) Make an IMenuComponent for it. Inherit from TestMenuComponent 
//  and call AddTestMenu in the derived constructor to add items to the 
//  test menu. 
//  (2) Declare a Shuksan class for the menu component in the PlugInClass.r
//  file. The new class has the menu component defined in (1).
//  
//  Example:
//  in the .cpp file:
//  class FooTest : public TestMenuComponent
//  
//  FooTest(IPMUnknown *boss) : TestMenuComponent(boss)
//  
//  AddTestMenu("Foo", "Test Foo Function", Foo);
//  
//  static void Foo() {}
//  
//  CREATE_PERSIST_PMINTERFACE(FooTest, kFooTestImpl);
//  
//  in the .fr file:
//  Class
//  
//  kFooTestMenuComponentBoss,
//  kInvalidClass,
//  
//  IID_IACTIONCOMPONENT, 	kFooTestImpl,
//  IID_IK2SERVICEPROVIDER, kActionRegisterProviderImpl,
//  IID_IACTIONREGISTER, kTestMenuRegisterImpl,
//  IID_IPMPERSIST, kPMPersistImpl,
//  
//========================================================================================

#pragma once
#ifndef __TestMenuComponent__
#define __TestMenuComponent__

#include "CActionComponent.h"
#include "K2Vector.h"
#include "ActionDefs.h"

typedef void (*TestFuncPtr)();
typedef void (*TestFuncPtr2)(IActiveContext*);
typedef int16 (*UpdateFuncPtr)(int16 actionState);
typedef int16 (*UpdateFuncPtr2)(int16 actionState, IActiveContext*);

class TestItem;

#pragma export on

class WIDGET_DECL TestMenuComponent : public CActionComponent 
{
public:
	TestMenuComponent(IPMUnknown *boss);
	virtual ~TestMenuComponent();
		
	virtual void	ReadWrite(IPMStream *s, ImplementationID prop);
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	Register_Debug_Actions();

	virtual void	DoAction(ActionID ) { ASSERT_FAIL("Shouldn't be called"); }
	virtual void	UpdateActionStates(IActionStateList *){ ASSERT_FAIL("Shouldn't be called"); }
		
protected:
	void AddTestMenu(const PMString& suiteName, const PMString& caseName, TestFuncPtr testFunc, int16 enablingType = kAlwaysEnabled, bool16 isObsolete = kTrue);
	void AddTestMenu(const PMString& suiteName, const PMString& caseName, TestFuncPtr2 testFunc, int16 enablingType = kAlwaysEnabled, bool16 isObsolete = kTrue);

	// Use the methods below if custom enabling of a test menu item is required.
	// The UpdateFuncPtr function is called to get the current menu item state.
	void AddTestMenu(const PMString& suiteName, const PMString& caseName, TestFuncPtr testFunc, UpdateFuncPtr updateFunc, bool16 isObsolete = kTrue);
	void AddTestMenu(const PMString& suiteName, const PMString& caseName, TestFuncPtr2 testFunc, UpdateFuncPtr2 updateFunc, bool16 isObsolete = kTrue);

	/**
		Add a test menu item
		@param newItem - ownership of ptr passes to TestMenuComponent, which will delete it
	*/
	void AddTestMenu( TestItem* newItem ) ;

private:
	ActionID fFirstActionID;
	int32 fActionIndex;
	K2Vector<TestItem*> fTestItems;
};

/**
	Stores information about a test menu item. Subclass this if you need
	to create test menu items at runtime that have dynamic (rather than
	static) behavior when the menu item is invoked.
*/
class TestItem
{
public:
	TestItem(const PMString& suiteName, const PMString& caseName, TestFuncPtr testFuncPtr, UpdateFuncPtr updateFuncPtr, int16 enable) :
		fSuiteName(suiteName), 
		fCaseName(caseName), 
		fTestFuncPtr(testFuncPtr),
		fUpdateFuncPtr(updateFuncPtr),
		fPassContext(kFalse),
		fEnablingType(enable)
		{
		}
		
	TestItem(const PMString& suiteName, const PMString& caseName, TestFuncPtr2 testFuncPtr, UpdateFuncPtr2 updateFuncPtr, int16 enable) :
		fSuiteName(suiteName), 
		fCaseName(caseName), 
		fTestFuncPtr((TestFuncPtr)testFuncPtr),
		fUpdateFuncPtr((UpdateFuncPtr)updateFuncPtr),
		fPassContext(kTrue),
		fEnablingType(enable)
		{
		}

		virtual ~TestItem() {}
		
	const PMString& GetSuiteName()		{return fSuiteName;}
	const PMString& GetCaseName()		{return fCaseName;}
	int16 GetEnablingType()				{return fEnablingType;}

	virtual void RunTestFunction( IActiveContext* ac )
	{
		ASSERT(fTestFuncPtr != nil);
		if ( fTestFuncPtr != nil )
		{
			if ( fPassContext )
				((TestFuncPtr2)fTestFuncPtr)(ac);
			else
				((TestFuncPtr)fTestFuncPtr)();
		}
	}

	virtual int16 GetUpdatedActionState( int16 actionState, IActiveContext* ac )
	{
		ASSERT(fUpdateFuncPtr != nil);
		if ( fUpdateFuncPtr != nil )
		{
			if ( fPassContext )
				return ((UpdateFuncPtr2)fUpdateFuncPtr)(actionState, ac);
			else
				return ((UpdateFuncPtr)fUpdateFuncPtr)(actionState);
		}
		return actionState ;
	}

private:
	PMString 		fSuiteName;
	PMString 		fCaseName;
	TestFuncPtr		fTestFuncPtr;
	UpdateFuncPtr	fUpdateFuncPtr;
	int16 			fEnablingType;
	bool16			fPassContext;
};

#pragma export off

#endif // __TestMenuComponent__
