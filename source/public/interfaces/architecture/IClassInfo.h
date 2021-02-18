//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IClassInfo.h $
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
//  Review Date:
//  
//========================================================================================

#pragma once
#ifndef __ICLASSINFO__
#define __ICLASSINFO__

#include "ShuksanID.h"
#include "IControllingUnknown.h"
#include <utility>

// Forward declare
class InterfaceInfo;

/** IClassInfo represents meta-class information for a boss class, allowing callers to iterate
	through interfaces and implementations of a boss class. You can get an IClassInfo interface
	for a particular boss class from IObjectModel. It provides generic information about all 
	boss objects of a given class: what interfaces they support, what implementations they use, etc.
	@ingroup arch_om
	@see IObjectModel
*/
class IClassInfo : public IControllingUnknown	{
public:
		/** Return the total number of interfaces supported by the class.
        @return number of interfaces supported by the class.
	    */
	virtual int32 CountInterfaces() const = 0;
		
		/** Return the n'th supported interface. Used together with
		   CountInterfaces, this allows callers to iterate over
		   the interfaces.	
 	    @param index	the index of the interface within the boss
        @return n'th supported interface.
		*/
	virtual PMIID GetInterface(int32 index) const = 0;
		
		/** Given the interfaceID (IID), find the corresponding ImplementationID
 	    @param whichInterface	the IID of the interface within the boss
        @return the ImplementationID used to implement the interface, or kInvalidImpl
		*/
	virtual ImplementationID GetImplementation(PMIID whichInterface) const = 0;
	
		/** Given the index of an interfaceID (IID), find the corresponding ImplementationID
 	    @param interfaceIndex	the index of the interface within the boss(probably from calling GetIndex previously)
        @return the ImplementationID used to implement the interface, or kInvalidImpl
		*/
	virtual ImplementationID GetImplementationByIndex(int32 interfaceIndex) const = 0;
		
		/** Given the implementationID, find the corresponding IID.
 	    @param whichInterface	the ImplementationID of the interface we want to find out about
        @return the IID (InterfaceID) of the interface, or IID_IUNKNOWN
		*/
	virtual PMIID GetIID(ImplementationID whichInterface) const = 0;
		
		/** Return the ID of the class that this classinfo represents.
        @return the ClassID of the class
		*/
	virtual ClassID GetClass() const = 0;

		/** Return the parent (base) class that this class is derived from, 
			or kInvalidClass if there is no parent.
        @return the ClassID of the parent (base) class
		*/
	virtual ClassID GetParentClass() const = 0;

		/** Return the ID of the plug-in that registered the class.
 	    @param forWhat	the interface we want to find out about (or nothing to find out the owner of the class)
        @return the PluginID of the plug-in that added the interface into the boss (or supplied the boss itself, if IID_IUNKNOWN)
		*/
	virtual PluginID GetOwnerComponent(PMIID forWhat = IID_IUNKNOWN) const = 0;
	
	

	////////////////////////////////////////////////////////////////////////
	//					For Internal Use Only
	////////////////////////////////////////////////////////////////////////

#ifdef USE_ALLOCATE_WITH_BOSS
		// Return the size in bytes to allocate for the boss.
	virtual int32 LengthInBytes() const = 0;
#endif
    
		// Create a new instance of the interface. The instance is
		// completely blank, and will require initialization by the
		// caller (for instance, to specify the boss).
	virtual IPMUnknown *CreateInterface(InterfaceInfo const* interfaceInfo, IControllingUnknown *boss) const = 0;

		// Delete the interface/
	virtual void DestructInterface(int32 index, IPMUnknown *obj) const = 0;

		// Return the index where PMIID is found, or -1 if there is none.
	virtual int32 GetIndex(PMIID interfaceID) const = 0;

#ifdef USE_ALLOCATE_WITH_BOSS
		// Return the offset within the boss block of the n'th interface, or 0 if the
		// interface is indepenedently allocated.
	virtual int32 GetOffset(int32 i) const = 0;

		// Return true if all interfaces are allocated in the same memory block as the boss.
	virtual bool16 IsAtomic() const = 0;
#endif
    
	virtual void Init(ClassID clsID) = 0;
	
	// Set the UID of the object model that owns this class info.
	//virtual void SetObjectModel(UID objectModel) = 0;

	// Set the ClassID of the class that this classinfo represents. Invalid if
		// the class already has a ClassID.
	//virtual void SetClass(ClassID clsID) = 0;

		// Set the parent (base) class. Does nothing if the owner or parent has 
		// already been set.
	virtual void SetParentClass(ClassID parentClass) = 0;

		// Sets the owner as specified. Does nothing if the owner has already been set.
	virtual void SetOwnerComponent(PluginID owner) = 0;

		// Add a new interface to the class. The interface is identified
		// by the interfaceID, and instances of it can be created
		// with the factory.
	virtual void AddInterface(PMIID interfaceID, ImplementationID faceID, PluginID owner, bool16 asAddin = kFalse) = 0;
	
	/** Looks up the InterfaceInfo asociated with the specified PMIID.
		Returns a pair of the InterfaceInfo pointer and interface index.
		The pair is useful when the caller needs to know the index of this PMIID as well (it avoids and extra lookup).
		If the class info doesn't support this interface returns a pair of (nil, -1).
	*/
	virtual std::pair<InterfaceInfo const*, int32> FindInterfaceInfo(PMIID interfaceID) const = 0;

	/** Forces the Class Info to finalize. Used internally during the first startup.
		Should not be called by regular code.
	*/
	virtual void FinalizeClassInfo() = 0;

	virtual void Unregister(PluginID owner) = 0;
	
	// Keep track of how many bosses are currently instantiated for this class
#ifdef DEBUG
public:
	virtual void ConstructedBoss() const = 0;
	virtual void DestructedBoss() const = 0;
	virtual int32 CurrentInstanceCount() const = 0;
	virtual int32 InstanceCount() const = 0;
	virtual int32 HighWaterMark() const = 0;
#endif

#ifdef DEBUG
	virtual void QueriedInterface(int32 index) = 0;
#endif

	virtual IPMUnknown *ConstructBoss() const = 0;
};


#endif // __ICLASSINFO__
