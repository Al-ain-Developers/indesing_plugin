//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IObjectModel.h $
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
//========================================================================================

#pragma once
#ifndef __IOBJECTMODEL__
#define __IOBJECTMODEL__


#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "InterfaceTrackingUtils.h"

class IClassInfo;
class IObjectModelIterator;
class ITagRegistry;
class IInterfaceRegistry;
class InterfaceProxyRegistry;
class ReadWriteObject;
class ObjectModel;
class BossConstructorList;


/** This is an interface to the object model (kObjectModelBoss), which is responsible 
	for managing boss classes, implementation factories, supplied by plug-ins and the application.

	@ingroup arch_om
	@see kObjectModelBoss
*/
class IObjectModel : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IOBJECTMODEL };

	//-------------------------------------------------------------------------------
	/**@name 	Iterate the registered classes	*/
	//@{-----------------------------------------------------------------------------

		/** Return the number of registered classes. See GetClassID()
        @return The number of boss installed classes in the system.
		*/
	virtual uint32 CountClasses() const = 0;

		/** Return the ClassID of the n'th class. See CountClasses()
        @return The ClassID of the n'th class.
		*/
	virtual ClassID GetClassID(uint32 indexCount) const = 0;

		/** Return the meta-info for the requested class. The caller must Release when done with it.
		@param theClass		The class we want to find out about
        @return The class's meta-data.
		*/
	virtual IClassInfo *QueryClassInfo(ClassID theClass) const = 0;

		/** Returns an iterator for all the classes registered as supporting the "iid" interface.
		@param iid		The interface we want a list of classes for
        @return An iterator that will iterate over all the classes that implement the iid.
		*/
	virtual IObjectModelIterator * NewObjectModelIterator(PMIID iid) const  = 0;
	//@}-----------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------------
	/**@name 	Get the name of an ID	*/
	//@{-----------------------------------------------------------------------------
		
		/** Get the name of an ID, given an ID-space and unique hex value
		@param idSpace		The ID-space of id : kClassIDSpace, kServiceIDSpace, etc.
		@param id			The ID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(int32 idSpace, int32 id) const = 0;

		/** Get the name of a ClassID
		@param id			The ClassID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(ClassID id) const = 0;

		/** Get the name of a PMIID
		@param id			The PMIID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(PMIID id) const = 0;

		/** Get the name of an ImplementationID
		@param id			The ImplementationID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(ImplementationID id) const = 0;

		/** Get the name of a PluginID
		@param id			The PluginID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(PluginID id) const = 0;

		/** Get the name of a ServiceID
		@param id			The ServiceID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(ServiceID id) const = 0;

		/** Get the name of a WidgetID
		@param id			The WidgetID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(WidgetID id) const = 0;

		/** Get the name of a ActionID
		@param id			The ActionID we want to get the name of
        @return A C++ nul-terminated char* containing the name of the ID
		*/
	virtual const char* GetIDName(ActionID id) const = 0;
	//@}-----------------------------------------------------------------------------
		
		/** Creates a new instance of the boss class and returns it. This is usually called from the helper function, CreateObject.
		@param theClass		The boss class we want to create an instance of
		@param iid			The interface of the instance to return
		@return A pointer to the new object, or nil if it could not be created, or if the interface isn't supported.
		*/
	virtual IPMUnknown *ConstructObject(ClassID theClass, PMIID iid) const = 0;

		/** Return the implementation's ReadWrite function. The ref-count of the plug-in is
		   incremented in the QueryReadWrite, and decremented by ReleaseReadWrite(); so 
		   calls to QueryReadWrite MUST be matched with corresponding calls to ReleaseReadWrite
		   unless the ReadWrite function returned is nil. If there is a ReadWrite function
		   registered for the implementation, but the plug-in is not loaded, QueryReadWrite will
		   load the plug-in and then return function. 
		@param faceID		The implementation we want the ReadWrite function for
		@return The ReadWrite function associated with the implementation, if there is one, 
		nil otherwise.
		*/
	virtual ReadWriteObject QueryReadWrite(ImplementationID faceID) const = 0;

		/** Release the ReadWriteObject that was returned by a previous call to QueryReadWrite().
		@param releaseThis		The ReadWriteObject to be released.
		*/
	virtual void ReleaseReadWrite(const ReadWriteObject& releaseThis) const = 0;

	virtual ReadWriteObject QueryInterfaceSnapshotReadWrite(ImplementationID faceID) const = 0;

	virtual InterfaceResetViewFun QueryInterfaceResetViewFun(ImplementationID prop) const = 0;

	virtual void ReleaseInterfaceResetViewFun (ImplementationID prop) const = 0;

	//-------------------------------------------------------------------------------
	/**@name 	For Internal Use Only	*/
	//@{-----------------------------------------------------------------------------

		// Register a new ID.
	virtual void RegisterID(PluginID ownerComponent, int32 IDSpaceID, const char* name, int32 id) = 0;

		// Tells the object model how to create an instance of the class.
	virtual void AddClassFactory(PluginID ownerComponent, ClassID id, BossConstructor construct) = 0;
		// Tells the object model how to create a given interface implementation. Factoryname is the name
		// of the implementation class.
	virtual void RegisterInterfaceFactory(PluginID ownerComponent, ImplementationID faceID) = 0;
	virtual void FillOutInterfaceFactory(PluginID ownerComponent, ImplementationID faceID, InterfaceConstructor construct, InterfaceDestructor destroyer, InterfaceSizeOf sizeofFunc, InterfaceReadWrite readWriter, InterfaceReadWrite snapshotReadWriter, InterfaceResetViewFun resetViewFun) = 0;
	virtual void AddImplementationAlias(PluginID ownerComponent, ImplementationID implID, ImplementationID basedOn) = 0;
	
		// Return a pointer to the tags registry.
	virtual ITagRegistry *GetTagRegistry() = 0;

		// Return the ID of the plugin that supplies the implementation.
	virtual PluginID GetOwner(ImplementationID implID) const = 0;
		// Return the ID of the plugin that supplies the aliased implementation.
	virtual PluginID GetOwnerAlias(ImplementationID implID) const = 0;
	
	virtual IInterfaceRegistry *GetInterfaceRegistry() const = 0;
	
	virtual BossConstructor GetClassConstructor(const ClassID theClass) const = 0;
	
	
#ifdef INTERFACEPROXIES_SUPPORTED	
	virtual IPMUnknown* CreateProxyObject ( const PMIID faceID, 
											IPMUnknown *ptheInterfaceImpl, 
  											const int32 proxyID,
  											IPMUnknown *boss) = 0;
  											
	virtual InterfaceReadWrite GetNonProxyReadWriter(ImplementationID faceID) const = 0;
	virtual InterfaceReadWrite GetNonProxySnapshotReadWriter(ImplementationID faceID) const = 0;
	virtual InterfaceResetViewFun GetNonProxyInterfaceResetViewFun(ImplementationID faceID) const = 0;

	virtual bool16 InterfaceIsTracked(const PMIID faceID) const = 0;
	virtual void TrackInterface(const PMIID interfaceID, const ClassID clsid) = 0;	
	virtual bool16 BossIsTracked(const ClassID id) const = 0;
	virtual void TrackBoss(const ClassID id) = 0;
#endif

#ifdef DEBUG
#ifdef INTERFACEPROXIES_SUPPORTED
	virtual bool16 	IsBossTrackingOn(void) const = 0;
#endif
	virtual void	XferSavedDataStuff(IPMStream*) = 0;
#endif

	//@}-----------------------------------------------------------------------------
	
};

/** Obsolete
*/
class ReadWriteObject {
	public:

#ifdef DEBUG
		ReadWriteObject(InterfaceReadWrite readWrite, ImplementationID implID = kInvalidImpl) :
			fImplID(implID),
#else
		ReadWriteObject(InterfaceReadWrite readWrite) :
#endif
			fReadWrite(readWrite)
			{}
		InterfaceReadWrite GetReadWrite() const	{ return fReadWrite; }
	private:
		InterfaceReadWrite fReadWrite;
#ifdef DEBUG
	public:
		ImplementationID GetImplementationID() const
			{ return fImplID; }
	private:
		ImplementationID fImplID;
#endif
};


/** Obsolete
*/
class StackBasedSnapshotReadWritePtr
{
public:
		StackBasedSnapshotReadWritePtr(const IObjectModel *om, ImplementationID implID) : 
			fObjectModel(om),
			fSnapshotReadWrite(om->QueryInterfaceSnapshotReadWrite(implID))
			{}
		
		~StackBasedSnapshotReadWritePtr()
			{
				fObjectModel->ReleaseReadWrite(fSnapshotReadWrite);
			}
		
		operator InterfaceReadWrite() const
			{ return fSnapshotReadWrite.GetReadWrite(); }
		InterfaceReadWrite GetSnapshotReadWrite() const
			{ return fSnapshotReadWrite.GetReadWrite(); }
		
private:
	ReadWriteObject fSnapshotReadWrite;
	const IObjectModel *fObjectModel;
};

/** Obsolete
*/
class StackBasedReadWritePtr
{
public:
		StackBasedReadWritePtr(const IObjectModel *om, ImplementationID implID) : 
			fObjectModel(om),
			fReadWrite(om->QueryReadWrite(implID))
			{}
		
		~StackBasedReadWritePtr()
			{
				fObjectModel->ReleaseReadWrite(fReadWrite);
			}
		
		operator InterfaceReadWrite() const
			{ return fReadWrite.GetReadWrite(); }
		InterfaceReadWrite GetReadWrite() const
			{ return fReadWrite.GetReadWrite(); }
		
private:
	ReadWriteObject fReadWrite;
	const IObjectModel *fObjectModel;
};

/** Retrieves the Object Model instance for the calling thread.
	This method of accessing the OM is a bit faster than calling GetExecutionContextSession and then QueryInterface on the session.
	@return a NON-AddRef'ed pointer to the Object Model. The returned pointer should be used locally and not stored.
*/
PUBLIC_DECL IObjectModel* GetObjectModelInstance();



#endif // __IOBJECTMODEL__
