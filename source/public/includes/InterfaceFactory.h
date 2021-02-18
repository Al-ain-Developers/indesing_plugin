//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfaceFactory.h $
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
//  Allows objects to be instantiated by name, rather than 
//  requiring a compiled in C++ class.
//  
//  The factory_construct function is placed in a dictionary, keyed
//  by the name. When constructing by ID, the factory looks up
//  the key name, finds the associated factory_construct function,
//  and calls it.
//  
//========================================================================================

#ifndef __INTERFACEFACTORY__
#define __INTERFACEFACTORY__


#include "OMFactoryCtor.h"


#ifdef __clang__
/**YIKES! new clang barfs on our factory declarations! Work-around by adding -Wno-vexing-parse to warning list, or, better suppress that warning from InterfaceFactory.h so it only applies to our FactoryList.h compilations.
		In file included from /Development/__Skunkworks/build/mac/prj/../../../source/omlib/libcore/ObjectModelMWHacks.cpp:44:
		../../../source/omlib/includes/CoreLibFactoryList.h:31:2: error: empty parentheses interpreted as a function declaration [-Werror,-Wvexing-parse]
			REGISTER_PMINTERFACE(CSession, kCSessionImpl)
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvexing-parse"
#endif

/** This class handles the virtual construction of interface implementations. Every implementation
	has a factory function for construction, a deletion function for destruction, and a sizeof function
	to return the allocation size of the implementation (for new). In addition, persistent implementations
	have a ReadWrite function. A few implementations require a snapshot function for handling automatic
	state restoration after Undo or Redo (most implementation handle this with ReadWrite). These functions
	are defined in the CREATE_PMINTERFACE or CREATE_PERSIST_PMINTERFACE macros. The InterfaceFactory class
	associates an ImplementationID with set of functions for that implementation.

	At plug-in load time, a set of static InterfaceFactory objects are generated, which contain the implementations
	that are linked into the plug-in. This is used by the Object Model to construct implementations, etc.

	You should not ever need to handle an InterfaceFactory directly in your plug-in; this is something the
	object model manages for you.
*/
class InterfaceFactory	{
public:
	/** Constructor function, normally called as part of CREATE_PMINTERFACE or CREATE_PERSIST_PMINTERFACE.
		@param faceID	The ID of the implementation
		@param faceFact	The factory function for constructing the implementation.
		@param faceDestroy	The function for destructing the implementation.
		@param faceSizeOf	The function for getting the sizeof the implementation.
		@param faceReadWrite	The ReadWrite function for the implementation (optional)
		@param faceSnapshotReadWrite	The Snapshot function for the implementation (optional)
		@param faceRestVIewFun	The ResetView function for the implementation (optional)
	*/
	InterfaceFactory(ImplementationID faceID, 
					InterfaceConstructor faceFact, 
					InterfaceDestructor faceDestroy, 
					InterfaceSizeOf faceSizeOf, 
					InterfaceReadWrite faceReadWrite = nil, 
					InterfaceReadWrite faceSnapshotReadWrite = nil,
					InterfaceResetViewFun  resetViewFun = nil);
		
	//-------------------------------------------------------------------------------
	/**@name 	For Internal Use Only	*/
	//@{-----------------------------------------------------------------------------

	static void InstallInterfaces(PluginID ownerComponent);
	
	const ImplementationID GetID()	{ return fID; }
	const InterfaceConstructor GetFactory() 	{ return fFactory; }
	const InterfaceDestructor GetDestructor() 	{ return fDestructor; }
	const InterfaceSizeOf GetSizeOf() 	{ return fSizeOf; }
	const InterfaceReadWrite GetReadWrite() 	{ return fReadWrite; }	
	const InterfaceReadWrite GetSnapshotReadWrite() 	{ return fSnapshotReadWrite; }
	const InterfaceResetViewFun GetInterfaceResetViewFun() 	{ return fInterfaceResetViewFun;}
	//@}-----------------------------------------------------------------------------

	//@}-----------------------------------------------------------------------------

private:
	const ImplementationID fID;
	const InterfaceConstructor fFactory;
	const InterfaceDestructor fDestructor;
	const InterfaceSizeOf fSizeOf;
	const InterfaceReadWrite fReadWrite;
	const InterfaceReadWrite fSnapshotReadWrite;
	const InterfaceResetViewFun fInterfaceResetViewFun;
	InterfaceFactory *fNext;
#ifdef DEBUG
	const char *fName;
#endif
	
private:
	static InterfaceFactory *gFirstInterface;
};



	//-------------------------------------------------------------------------------
	/**@name 	For Internal Use Only	*/
	//@{-----------------------------------------------------------------------------

#ifdef USE_ALLOCATE_WITH_BOSS
#define PRIVATE_DECLARE_PMINTERFACE(idstring) 	\
	extern "C" { void* Create##idstring(void *memoryBuffer, IPMUnknown *boss); 	\
				 void Destroy##idstring(void *facePtr);  \
				 int SizeOf##idstring(); } 
#else
#define PRIVATE_DECLARE_PMINTERFACE(idstring) 	\
    extern "C" { void* Create##idstring(IPMUnknown *boss); 	\
                 void Destroy##idstring(void *facePtr);  \
                 int SizeOf##idstring(); }
#endif
	// Creates a function declaration for the factory_construct and destructor
	// functions.
	
#define PRIVATE_HACK_PMINTERFACE(idstring)	\
	InterfaceFactory *Get##idstring##InterfaceFactory();	\
	InterfaceFactory *Get##idstring##InterfaceFactory()	{ return &g##idstring##Factory; }
	// Hack to make sure the static g## doesn't get stripped on link.

#ifdef USE_ALLOCATE_WITH_BOSS
#define PRIVATE_DEFINE_PMINTERFACE(cn, idstring) 	\
	extern "C" { void* Create##idstring(void *memoryBuffer, IPMUnknown *boss)	\
					{ 	\
					return new (memoryBuffer) cn(boss);		\
					} 	\
				 void Destroy##idstring(void *facePtr)		\
					{ reinterpret_cast<cn*>(facePtr)->~cn();  } 	\
				int SizeOf##idstring()	\
					{ return sizeof (cn); } }
#else
#define PRIVATE_DEFINE_PMINTERFACE(cn, idstring) 	\
    extern "C" { void* Create##idstring(IPMUnknown *boss)	\
                    { 	\
                    return new cn(boss);		\
                    } 	\
                 void Destroy##idstring(void *facePtr)		\
                    { delete reinterpret_cast<cn*>(facePtr);  } 	\
				int SizeOf##idstring()	\
                    { return sizeof (cn); } }
#endif

	// Creates a function definition for the factory_construct function.

	
#ifdef USE_ALLOCATE_WITH_BOSS
#define PRIVATE_DEFINE_VIEWINTERFACE(id, cn, idstring) 	\
	extern "C" { void* Create##idstring(void *memoryBuffer, IPMUnknown *boss)	\
					{ 	\
					cn* face = new (memoryBuffer) cn(boss);		\
					/*fViewIFaceConsistencyChecker is used only to produce compiler errors \
					if people use the wrong helper method declaraton type \
					while using CREATE_VIEW_PMINTERFACE*/ \
					face->fViewIFaceConsistencyChecker = nil;\
					return face;\
					} 	\
				 void Destroy##idstring(void *facePtr)		\
					{ reinterpret_cast<cn*>(facePtr)->~cn();  } 	\
				int SizeOf##idstring()	\
					{ return sizeof (cn); } }
#else
#define PRIVATE_DEFINE_VIEWINTERFACE(id, cn, idstring) 	\
    extern "C" { void* Create##idstring(IPMUnknown *boss)	\
                    { 	\
                    cn* face = new cn(boss);		\
                    /*fViewIFaceConsistencyChecker is used only to produce compiler errors \
                    if people use the wrong helper method declaraton type \
                    while using CREATE_VIEW_PMINTERFACE*/ \
                    face->fViewIFaceConsistencyChecker = nil;\
                    return face;\
                    } 	\
                void Destroy##idstring(void *facePtr)		\
                    { delete reinterpret_cast<cn*>(facePtr);  } 	\
                int SizeOf##idstring()	\
                    { return sizeof (cn); } }
#endif

#ifdef USE_ALLOCATE_WITH_BOSS
#define PRIVATE_DEFINE_PERSIST_DONTSNAPSHOT_PMINTERFACE(cn, idstring) 	\
	extern "C" { void* Create##idstring(void *memoryBuffer, IPMUnknown *boss)	\
					{ 	\
					cn* face = new (memoryBuffer) cn(boss);		\
					/*fDontSnapshotIFaceConsistencyChecker is used only to produce compiler errors \
					if people use the wrong helper method declaraton type \
					while using CREATE_PERSIST_DONTSNAPSHOT_PMINTERFACE*/ \
					face->fDontSnapshotIFaceConsistencyChecker = nil;\
					return face;\
					} 	\
				 void Destroy##idstring(void *facePtr)		\
					{ reinterpret_cast<cn*>(facePtr)->~cn();  } 	\
				int SizeOf##idstring()	\
					{ return sizeof (cn); } }
#else
#define PRIVATE_DEFINE_PERSIST_DONTSNAPSHOT_PMINTERFACE(cn, idstring) 	\
    extern "C" { void* Create##idstring(IPMUnknown *boss)	\
                    { 	\
                    cn* face = new cn(boss);		\
                    /*fDontSnapshotIFaceConsistencyChecker is used only to produce compiler errors \
                    if people use the wrong helper method declaraton type \
                    while using CREATE_PERSIST_DONTSNAPSHOT_PMINTERFACE*/ \
                    face->fDontSnapshotIFaceConsistencyChecker = nil;\
                    return face;\
                    } 	\
                 void Destroy##idstring(void *facePtr)		\
                    { delete reinterpret_cast<cn*>(facePtr);  } 	\
                int SizeOf##idstring()	\
                    { return sizeof (cn); } }
#endif


#define PRIVATE_REGISTER_PMINTERFACE(id, idstring)	\
	static InterfaceFactory g##idstring##Factory(id, Create##idstring, (InterfaceDestructor)Destroy##idstring, (InterfaceSizeOf)SizeOf##idstring);	


#define PRIVATE_DECLARE_READWRITE(cn, idstring)	\
	void ReadWrite##idstring(cn *obj, IPMStream *s, ImplementationID prop, int32 length);
	// Creates a function declaration for the ReadWrite function.
	
#define PRIVATE_DECLARE_SNAPSHOTREADWRITE(cn, idstring)	\
	void SnapshotReadWrite##idstring(cn *obj, IPMStream *s, ImplementationID prop, int32 length);
	// Creates a function declaration for the SnapshotReadWrite function.

#define PRIVATE_DECLARE_RESETVIEWFUN(cn, idstring)	\
	void ResetViewFun##idstring(cn *obj, ImplementationID prop);
	// Creates a function declaration for the ResetView function.

#define PRIVATE_DEFINE_READWRITE(cn, idstring)	\
	void ReadWrite##idstring(cn *obj, IPMStream *s, ImplementationID prop, int32 /*length*/)	\
		{ obj->ReadWrite(s, prop); }
	// Creates a function definition for the ReadWrite function
	
#define PRIVATE_DEFINE_SNAPSHOTREADWRITE(cn, idstring)	\
	void SnapshotReadWrite##idstring(cn *obj, IPMStream *s, ImplementationID prop, int32 /*length*/)	\
		{ obj->SnapshotReadWrite(s, prop); }
	// Creates a function definition for the SnapshotReadWrite function

#define PRIVATE_DEFINE_RESETVIEWFUN(cn, idstring)	\
	void ResetViewFun##idstring(cn *obj, ImplementationID prop)	\
		{ obj->ResetView(prop); }
	// Creates a function definition for the ResetView function

#define PRIVATE_REGISTER_PERSIST_PMINTERFACE(id, idstring)	\
	static InterfaceFactory g##idstring##Factory(id, Create##idstring, (InterfaceDestructor)Destroy##idstring, (InterfaceSizeOf)SizeOf##idstring, (InterfaceReadWrite)ReadWrite##idstring, (InterfaceReadWrite)nil, (InterfaceResetViewFun)nil);

#define PRIVATE_REGISTER_PERSIST_SNAPSHOT_PMINTERFACE(id, idstring)	\
 	static InterfaceFactory g##idstring##Factory(id, Create##idstring, (InterfaceDestructor)Destroy##idstring, (InterfaceSizeOf)SizeOf##idstring, (InterfaceReadWrite)ReadWrite##idstring,  (InterfaceReadWrite)SnapshotReadWrite##idstring, (InterfaceResetViewFun)nil);	

#define PRIVATE_REGISTER_SNAPSHOT_PMINTERFACE(id, idstring)	\
	static InterfaceFactory g##idstring##Factory(id, Create##idstring, (InterfaceDestructor)Destroy##idstring, (InterfaceSizeOf)SizeOf##idstring, (InterfaceReadWrite) nil,  (InterfaceReadWrite)SnapshotReadWrite##idstring, (InterfaceResetViewFun)nil);

#define PRIVATE_REGISTER_VIEW_PMINTERFACE(id, idstring)	\
	static InterfaceFactory g##idstring##Factory(id, Create##idstring, (InterfaceDestructor)Destroy##idstring, (InterfaceSizeOf)SizeOf##idstring, (InterfaceReadWrite) nil,  (InterfaceReadWrite)SnapshotReadWrite##idstring, (InterfaceResetViewFun)ResetViewFun##idstring);

#define BUILD_PMINTERFACE(idstring)		\
	InterfaceFactory *Get##idstring##InterfaceFactory();	\
	Get##idstring##InterfaceFactory();

	//@}-----------------------------------------------------------------------------

/** REGISTER_PMINTERFACE -- a macro used for declaring an interface. Each plug-in should have a
	XXXFactory.h file which has declarations for the implementations it contains.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#ifdef __ODFRC__
#define REGISTER_PMINTERFACE(cn, id)	\
	id
#else 
#define REGISTER_PMINTERFACE(cn, id)	\
	BUILD_PMINTERFACE(id##_)
#endif

	//-------------------------------------------------------------------------------
	/**@name 	For Internal Use Only	*/
	//@{-----------------------------------------------------------------------------

#define REFERENCE_PMINTERFACE(id)	\
	BUILD_PMINTERFACE(id##_)

	//@}-----------------------------------------------------------------------------

/** CREATE_PMINTERFACE -- a macro used for declaring an implementation to the object model.
	This is the default way to declare your implementation.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DEFINE_PMINTERFACE(cn, id##_)	\
	PRIVATE_REGISTER_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

/** CREATE_PERSIST_PMINTERFACE -- a macro used for declaring a persistent implementation to the 
	object model. Use this if your implementation has a ReadWrite method.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_PERSIST_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DECLARE_READWRITE(cn, id##_) \
	PRIVATE_DEFINE_PMINTERFACE(cn, id##_)	\
	PRIVATE_DEFINE_READWRITE(cn, id##_)	\
	PRIVATE_REGISTER_PERSIST_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

/** CREATE_PERSIST_SNAPSHOT_PMINTERFACE -- a macro used for declaring a persistent implementation to the 
	object model, that has both a snapshot method and a ReadWrite method. This is a rare case.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_PERSIST_SNAPSHOT_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DECLARE_READWRITE(cn, id##_) \
	PRIVATE_DECLARE_SNAPSHOTREADWRITE(cn, id##_) \
	PRIVATE_DEFINE_PMINTERFACE(cn, id##_)	\
	PRIVATE_DEFINE_READWRITE(cn, id##_)	\
	PRIVATE_DEFINE_SNAPSHOTREADWRITE(cn, id##_)	\
	PRIVATE_REGISTER_PERSIST_SNAPSHOT_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

/** CREATE_SNAPSHOT_PMINTERFACE -- a macro used for declaring a non-persistent implementation to the 
	object model, that has a snapshot method but no ReadWrite method. This is a rare case.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_SNAPSHOT_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DECLARE_SNAPSHOTREADWRITE(cn, id##_) \
	PRIVATE_DEFINE_PMINTERFACE(cn, id##_)	\
	PRIVATE_DEFINE_SNAPSHOTREADWRITE(cn, id##_)	\
	PRIVATE_REGISTER_SNAPSHOT_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

/** CREATE_VIEW_PMINTERFACE -- a macro used for declaring a non-persistent implementation to the 
	object model, that has a snapshot method, no ReadWrite method, and a ResetView. This is a rare case.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_VIEW_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DECLARE_SNAPSHOTREADWRITE(cn, id##_) \
	PRIVATE_DECLARE_RESETVIEWFUN(cn, id##_) \
	PRIVATE_DEFINE_VIEWINTERFACE(id, cn, id##_)	\
	PRIVATE_DEFINE_SNAPSHOTREADWRITE(cn, id##_)	\
	PRIVATE_DEFINE_RESETVIEWFUN(cn, id##_)	\
	PRIVATE_REGISTER_VIEW_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

	//-------------------------------------------------------------------------------
	/**@name 	For Internal Use Only	*/
	//@{-----------------------------------------------------------------------------

#define EXPORT_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DEFINE_PMINTERFACE(cn, id##_)	

#define IMPORT_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_REGISTER_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	

	//@}-----------------------------------------------------------------------------


/** Private for internal use only; 
	CREATE_PERSIST_DONTSNAPSHOT_PMINTERFACE -- a macro used for declaring a persistent implementation to the 
	object model, where the implementation should not be snapshot. This is a rare case.
	@param cn	C++ class used for the implementation
	@param id	ImplementationID of  the implementation
*/
#define CREATE_PERSIST_DONTSNAPSHOT_PMINTERFACE(cn, id) 	\
	PRIVATE_DECLARE_PMINTERFACE(id##_) \
	PRIVATE_DECLARE_READWRITE(cn, id##_) \
	PRIVATE_DEFINE_PERSIST_DONTSNAPSHOT_PMINTERFACE(cn, id##_)	\
	PRIVATE_DEFINE_READWRITE(cn, id##_)	\
	PRIVATE_REGISTER_PERSIST_PMINTERFACE(id, id##_)	\
	PRIVATE_HACK_PMINTERFACE(id##_)	
#endif // __INTERFACEFACTORY__

