//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ClassFactory.h $
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
//  Virtual constructors."
//  
//  Allows you to register a constructor function, keyed by class ID.
//  Which in turns allows you to create a new object given a class ID.
//  
//========================================================================================

#ifndef __CLASSFACTORY__
#define __CLASSFACTORY__

#ifndef __ODFRC__
#include "OMFactoryCtor.h"

class IDataBase;

/** By default, all bosses are implemented using pre-supplied implementations of IControllingUnknown.
	You can supply your own implementation for your boss if you supply a class factory that will
	create the boss on demand from the object model. You should try this only if you know what you're
	doing -- it's not a recommended way to fix problems, and solutions using this method are
	inherently fragile. You've been warned.
	
	If you must do it, here's how it works.
	First declare a factory function, based on the name of the boss.
	<pre>
		void *CreateMyBoss(ClassID clsID)
			{	return new MyControllingUnknown(clsID);	}
  	</pre>
	Then use this macro to declare a dummy usage for your Create function, so the factory won't get 
	stripped out by the linker:
	<pre>
	  	CREATE_CLASSFACTORY(MyBoss, kMyBoss)
  	</pre>
	If you don't have one already, make a ClassFactoryList.h file, similar to a FactoryList.h 
	file. Add a line to the file that declares your special boss type:
	<pre>
	  	REGISTER_CLASSFACTORY(MyBoss, kMyBoss)
  	</pre>
	Your Class.fr file should include a resource declaring the boss. This declares to the object model
	that when it gets a request to create your boss, it should use your factory function. You can do 
	this as follows:
	<pre>
		resource FactoryList (129)
		{
			kClassIDSpace,
			{
				 #include "MyClassFactoryList.h" 
			}
		};
  	</pre>
*/
class ClassFactory	{
public:
	ClassFactory(ClassID id, BossConstructor classFact = nil);
		
	static void InstallClasses(PluginID ownerComponent);
	
	ClassID GetClassID()	{ return fID; }
	BossConstructor GetFactory() 	{ return fFactory; }
	
private:
	ClassID fID;
	BossConstructor fFactory;
	ClassFactory *fNext;
	static ClassFactory *gFirstClass;
};


#define CREATE_CLASSFACTORY(className, clsID)	\
	ClassFactory g##className##Factory(clsID, Create##className);	\
	ClassFactory *Get##className##Factory();	\
	ClassFactory *Get##className##Factory()		{	return &g##className##Factory;	}


#define REGISTER_CLASSFACTORY(className, clsID)	\
	ClassFactory *Get##className##Factory();	\
	Get##className##Factory();

#else		// is ODFRC
#define REGISTER_CLASSFACTORY(ClassName, clsID)	\
	clsID
#endif

#endif 	// __CLASSFACTORY__
