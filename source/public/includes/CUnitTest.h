//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CUnitTest.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Adds a menu to the Test menu so that individual classes can be tested.
//  
//  Usage: Subclass CUnitTest, override OnTest, and create a static object in one of your 
//  cpp files (it's important to create a static object so that UnitTestList can figure
//  out when your plugin must be loaded). The test will be automatically added to the unit 
//  test menu.
//  
//========================================================================================

#pragma once
#ifndef __CUNITTEST__
#define __CUNITTEST__

#ifdef DEBUG

#include "PMTypes.h"

#pragma export on

class IPlugIn;


// Instead of calling ASSERT or ASSERT_MSG your unit test should use this macro.
// This allows us to maintain statistics on how many tests failed and gives us
// more control over what we break into the debugger for.
#define TEST(p)		!(p) ? this->DoTestFailed(#p, __FILE__, __LINE__) : (void) 0


// If you want to put your unit test in its own file you'll need to ensure that it 
// isn't deadstripped. You can do this by using the DEFINE_UNIT_TEST in the unit test
// file and REFERENCE_UNIT_TEST in your plugin's MWHacks file.
#define DEFINE_UNIT_TEST(Class)			\
	void Reference##Class();			\
	void Reference##Class() {			\
		Class test;						\
	}

#define REFERENCE_UNIT_TEST(Class)		\
	void Reference##Class();			\
	Reference##Class()
	
	
// ===================================================================================
//	class CUnitTest
// ===================================================================================
class PUBLIC_DECL CUnitTest {

//-----------------------------------
//	Initialization/Destruction
//
public:	
	virtual				~CUnitTest();
							
						CUnitTest(const char* name, PluginID id, bool16 isObsolete = kTrue);

private:
						CUnitTest(const CUnitTest& rhs);
						
			CUnitTest& 	operator=(const CUnitTest& rhs);

//-----------------------------------
//	API
//
public:
	virtual void 		RunTest();
	virtual void RunMinimalTest();	
		// Test that gets run as part of minimal. By default, same as RunTest.
						
			const char* GetName() const								{return fName;}
			
			PluginID 	GetPlugin() const							{return fPlugin;}
			
protected:
	virtual void 		OnTest() = 0;
						// This will normally be the only function you override.

//-----------------------------------
//	Internal API
//
protected:
	virtual void 		DoTestFailed(const char* message, const char* file, int32 line) const;

//-----------------------------------
//	Member Data
//
private:
	const char*		fName;
	PluginID 		fPlugin;
};


#pragma export off

#endif	// DEBUG
#endif // __CUNITTEST__
