//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfacePtr.h $
//  
//  Owner: Zak Williamson and Mat Marcus
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
//  depot/branches/cw8/source/public/Includes/InterfacePtr.h#1 - branch change 154605 (ktext)
//  
//  Provides a template class that acts like a pointer to an interface
//  but adds the funcationality of automatically calling QueryInterface
//  and Release as needed.
//  
//  The following is a simple smart pointer implementation
//  that automates the mundane QueryInterface, use, Release pattern.
//  For example, code like the following:
//  
//  IShape * shape = pmInterfacePtr->QueryInterface(IID_ISHAPE);
//  ASSERT_MSG(shape != nil, "shape is nil!");
//  shape->Draw();
//  shape->Release();
//  
//  becomes:
//  
//  InterfacePtr<IShape> shape(pmInterfacePtr, UseDefaultIID());
//  shape->Paint();
//  
//  OR:
//  
//  InterfacePtr<IShape> shape(pmInterfacePtr, IID_ISHAPE);
//  shape->Paint();
//  
//  If only const members will be called then use:
//  
//  InterfacePtr<const IShape> shape(pmInterfacePtr, UseDefaultIID());
//  shape->Paint();
//  
//  More importantly, releasing interfaces is automatic (via the
//  InterfacePtr destructor).  There's no need to check all the return's
//  in a method to be sure they call Release and we'll be better prepared
//  for backing out via exception handling.
//  
//  The constructor performs the QueryInterface, the indirection
//  operator performs the Assert, and the destructor performs the Release.
//  Assignment of InterfacePtrs is also possible -- see notes below.
//  
//  Caveats
//  You can use an InterfacePtr in place of the corresponding "real" pointer
//  in a function call.  The implicit conversion operator will see that the
//  real" pointer is passed.
//  
//========================================================================================

#pragma once
#ifndef __InterfacePtr__
#define __InterfacePtr__

#include "IPMUnknown.h"
#include "OMTypes.h"		// for PMIID

#include "IDataBase.h"
#include "UIDRef.h"

// -------------------------------------------------------------
// Class UseDefaultIID
// -------------------------------------------------------------

// Passing one of the InterfacePtr constructors an anonymous UseDefaultIID()
// as the trailing parameter (instead of a PMIID) causes a special constructor
// to be called. This special constructor assumes that the interface IFace
// has defined a default ID with the name kDefaultIID. If such an ID has not
// been defined then the compiler will complain. A good way to satisfy the
// compiler is to then add the definition to the offending Interface. Or
// one could just use the "old style" call to InterfacePtr.

/****** EXAMPLE  *****

* ----------
* IMyInterface.h:
*
* #include "xxxID.h"
*
* class IMyInterface : public IPMUnknown
* {
* public:
* 	enum { kDefaultIID = kMyInterfaceID};
* ...
* };
*
* ----------
* Some Client of IMyInterface:
*
*  ...
* 	InterfacePtr<IMyInterface> myInterface(foo, UseDefaultIID());
*
******* END EXAMPLE *****/

/** This is a dummy tag class. It is used only to drive the type system.
*/
class UseDefaultIID {
// This is a dummy tag class. It is used only to drive the type system.
};

// -------------------------------------------------------------
// Class InterfacePtr
// -------------------------------------------------------------

/** InterfacePtr is a smart pointer class that simplifies the work with interface pointers.
	It guarantees that Release() will be called on an acquired interface and AddRef() when sharing the ownership.
*/
template <class IFace>
class InterfacePtr {
public:

	/** Allows containment of InterfacePtr in K2Vector.
	*/
	typedef object_type data_type; // Allows containment of InterfacePtr in K2Vector.

// -------------------------------------------------------------
// Build from a dumb pointer
// -------------------------------------------------------------


	/** This constructor will take ownership of the specified interface. AddRef is NOT called, but
	Release will be called in the destructor. This functionality is best described as an Attach().
    Most of the time, you do not want to use this constructor, but the ones with two parameters
	which do call AddRef. Do not use p after this call since it may be invalid after the
	InterfacePtr goes out of scope.
	Use this constructor when you've called a function that returns an
	AddRef'd pointer -- e.g., QuerySpread(), QueryApplication(), etc.

	@param p [IN] - interface pointer that we attach to.
	*/
	explicit  InterfacePtr(IFace* p)
		: fFace(p) 
#ifdef ID_ENABLE_DEBUGGING
		, fDebugLastIIDQueried(kInvalidInterfaceID), fDebugLastBossQueried(kInvalidClass)
#endif
	{
		(void)
		static_cast<const IPMUnknown*>(p);
	}


	/** Use this constructor if you have one interface on a boss and want another one. Addref is called
	on the boss, so it is still safe to use the p after the InterfacePtr goes out of scope.
	@param p [IN] - interface to use for query.
	@param iid [IN] - IID of the interface we want.
	*/
	InterfacePtr(const IPMUnknown* p, PMIID iid)
		:  fFace(QueryInterface_(p, iid)) 
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
				SaveOffDebugInfo(p,iid);
#endif
		}


	/** This constructor is similar to the one directly above.
		It is more convenient but will only compile if IFace::kDefaultIID is defined
		@param p [IN] - interface to use for query.
	*/
	InterfacePtr(const IPMUnknown* p, const UseDefaultIID&)
		:  fFace(QueryInterface_(p, IFace::kDefaultIID)) 
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
				SaveOffDebugInfo(p,IFace::kDefaultIID);
#endif
		}

	/** Default constructor: construct a nil InterfacePtr
	*/
	InterfacePtr(void)
		: fFace(nil) 
#ifdef ID_ENABLE_DEBUGGING
		, fDebugLastIIDQueried(kInvalidInterfaceID), fDebugLastBossQueried(kInvalidClass)
#endif
		{}

private:
	// $$$ Could implement operator= in a way that generates a better error message at compile time

	/** Prohibit assignment of a plain (dumb) pointer to an InterfacePtr by declaring operator= as private.
	*/
		template <class OtherType>
		InterfacePtr<IFace>& operator=(OtherType* p); // intentionally unimplemented

public:

// -------------------------------------------------------------
// Build from a smart pointer
// -------------------------------------------------------------

	// These single argument constructors will call AddRef on p.
	// Release will be called in the destructor.


	/** Constructor that enables InterfacePtr<const IFoo> to be constructed from an InterfacePtr<IFoo>.
	*/
	template <class OtherType>
		InterfacePtr(const InterfacePtr<OtherType>& p)
		:fFace(AddRef_(p.get()))
#ifdef ID_ENABLE_DEBUGGING
		, fDebugLastIIDQueried(p.fDebugLastIIDQueried), fDebugLastBossQueried(p.fDebugLastBossQueried)
#endif
	{ /* Implementation Note: we use a template member fucntion here to do the right thing
	  when an InterfacePtr<const IFoo> is constructed from an InterfacePtr<IFoo> */
	}

	/** Copy constructor. Increments the ref count of p by one. We define this to prevent the
	compiler from generating a bitwise copying version (template members do not suffice).
	@param p [IN] - InterfacePtr to be copied.
	*/
	InterfacePtr(const InterfacePtr<IFace>& p)
		:fFace(AddRef_(p.get()))  
#ifdef ID_ENABLE_DEBUGGING
		, fDebugLastIIDQueried(p.fDebugLastIIDQueried),fDebugLastBossQueried(p.fDebugLastBossQueried)
#endif
		{ }

	InterfacePtr(InterfacePtr<IFace>&& p) noexcept
		:fFace(p.fFace)
#ifdef ID_ENABLE_DEBUGGING
		, fDebugLastIIDQueried(p.fDebugLastIIDQueried), fDebugLastBossQueried(p.fDebugLastBossQueried)
#endif
	{
		p.fFace = nil;
	}

	/** Assigment operator. Increments the ref count of p by one.
	This one enables InterfacePtr<const IFoo> = InterfacePtr<IFoo>
	@param p [IN] - InterfacePtr to be copied.
	*/
	template <class OtherType>
		InterfacePtr<IFace>& operator=(const InterfacePtr<OtherType>& p)
	{
		// Take ownership of p
		reset(AddRef_(p.get()));
#ifdef ID_ENABLE_DEBUGGING
		fDebugLastIIDQueried = p.fDebugLastIIDQueried;
		fDebugLastBossQueried = p.fDebugLastBossQueried;
#endif
		return *this;
		/* Implementation Note: we use a template member function here to do the right thing
		when an InterfacePtr<const IFoo> is constructed from an InterfacePtr<IFoo> */
	}

	/** Assigment operator. Increments the ref count of p by one.
	This one enables copying of InterfacePtr of the same types.
	@param p [IN] - InterfacePtr to be copied.
	*/
	InterfacePtr<IFace>& operator=(const InterfacePtr<IFace>& p)
	{
		// Take ownership of p
		reset(AddRef_(p.get()));
#ifdef ID_ENABLE_DEBUGGING
		fDebugLastIIDQueried = p.fDebugLastIIDQueried;
		fDebugLastBossQueried = p.fDebugLastBossQueried;
#endif
		return *this;
	}

	InterfacePtr<IFace>& operator=(InterfacePtr<IFace>&& p) noexcept
	{
		this->swap(p);
		return *this;
	}


// -------------------------------------------------------------
// Build from a database
// -------------------------------------------------------------
	// use these constructors to instantiate from a database

	/** Constructs an InterfacePtr from an object from a database.
	@param db [IN] - Database to instantiate from
	@param uid [IN] - UID of the boss.
	@param iid [IN] - IID of the desired interface from the boss.
	*/
	InterfacePtr(IDataBase *db, UID uid, PMIID iid)
		: fFace(Instantiate_(db, uid, iid))  
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
			{
				fDebugLastIIDQueried = iid;
				if(db)
					fDebugLastBossQueried = db->GetClass(uid);
				else
					fDebugLastBossQueried = kInvalidClass;
			}
#endif
		}

	/** Constructs an InterfacePtr from an object from a database. This version is more
	convenient but will only compile if IFace::kDefaultIID is defined.
	@param db [IN] - Database to instantiate from
	@param uid [IN] - UID of the boss.
	*/
	InterfacePtr(IDataBase *db, UID uid, const UseDefaultIID&)
		: fFace(Instantiate_(db, uid, IFace::kDefaultIID)) 
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
			{
				fDebugLastIIDQueried = IFace::kDefaultIID;
				if(db)
					fDebugLastBossQueried = db->GetClass(uid);
				else
					fDebugLastBossQueried = kInvalidClass;
			}
#endif
		}

	/** Constructs an InterfacePtr from an object from a database.
	@param ref [IN] - UIDRef of the boss object
	@param iid [IN] - IID of the desired interface from the boss.
	*/
	InterfacePtr(const UIDRef& ref, PMIID iid)
		: fFace(Instantiate_(ref, iid)) 
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
			{
				fDebugLastIIDQueried = iid;
				if(ref.GetDataBase())
					fDebugLastBossQueried = ref.GetDataBase()->GetClass(ref.GetUID());
				else
					fDebugLastBossQueried = kInvalidClass;
			}
#endif
		}

	/** Constructs an InterfacePtr from an object from a database.
	This version is more convenient but will only compile if IFace::kDefaultIID is defined.
	@param ref [IN] - UIDRef of the boss object
	@param iid [IN] - IID of the desired interface from the boss.
	*/
	InterfacePtr(const UIDRef& ref, const UseDefaultIID&)
		: fFace(Instantiate_(ref, IFace::kDefaultIID)) 
		{
#ifdef ID_ENABLE_DEBUGGING
			if(!fFace)
			{
				fDebugLastIIDQueried = IFace::kDefaultIID;
				if(ref.GetDataBase())
					fDebugLastBossQueried = ref.GetDataBase()->GetClass(ref.GetUID());
				else
					fDebugLastBossQueried = kInvalidClass;
			}
#endif
		}

// -------------------------------------------------------------
// Destroy
// -------------------------------------------------------------
	~InterfacePtr();

// -------------------------------------------------------------
// Use the pointer
// -------------------------------------------------------------
	/** Implicit conversion operator. Allows implicit conversion between InterfacePtr<IFace> and IFace*.
	@return the contained pointer.
	*/
	operator IFace*() const { return fFace; }
	// We allow the cast operator to return a nil pointer
	// since it is valid to test against nil and may be valid
	// to pass a nil pointer to some methods.

	/** Indirection operator. If the pointer is nil, it will ASSERT in Debug builds and will
	have unspecified behavior in the Release builds.
	@return the contained pointer
	*/
	IFace * operator ->() const
	{
		#ifdef ID_ENABLE_DEBUGGING
		if(!fFace)
			AssertAboutUsingNilPtr();
		#endif
		return fFace;
	}

	/** Boolean test operator (Null test).
	@return kTrue if the contained pointer is nil.
	*/
	bool16 operator!() const { return fFace == nil; }

	/** Detaches from the owned interface and transfers the ownership to the caller.
	Note: The signature of this function makes it error-prone: if the caller doesn't take
	ownership of the interface (doesn't assign the result) the interface will be leaked.
	@return the owned interface
	*/
	IFace* forget() // was release
	{
		IFace* result = fFace;
		fFace = 0;
#ifdef ID_ENABLE_DEBUGGING
		fDebugLastIIDQueried = kInvalidInterfaceID;
		fDebugLastBossQueried = kInvalidClass;
#endif
		return result;
	}

	/** Accessor for the owned pointer.
	@return the contained pointer
	*/
	IFace* get() const { return fFace; }

	/** Releases the ownership for the current interface and attaches to the new one.
	Note: the reference count of p will NOT be changed (AddRef is not called).
	@param p [IN] - new interface pointer to take ownership of
	*/
	void reset(IFace* p = 0)
	{
		IFace* oldFace = fFace;
		fFace = p;
#ifdef ID_ENABLE_DEBUGGING
		fDebugLastIIDQueried = kInvalidInterfaceID;
		fDebugLastBossQueried = kInvalidClass;
#endif
		Release_(oldFace);
	}

	void swap(InterfacePtr<IFace>& other) noexcept
	{
		using std::swap;
		swap(fFace, other.fFace);
#ifdef ID_ENABLE_DEBUGGING
		swap(fDebugLastBossQueried, other.fDebugLastBossQueried);
		swap(fDebugLastIIDQueried, other.fDebugLastIIDQueried);
#endif
	}

private:

	template <class T>
	static IFace* AddRef_(const T* p) { if(p) p->AddRef(); return static_cast<IFace*>(const_cast<T*>(p));}

	static void Release_(IFace* p)
		{ if(p) p->Release(); }

	static IFace* QueryInterface_(const IPMUnknown* p, PMIID id)
		{ return p? static_cast<IFace*>(p->QueryInterface(id)) : nil; }

	static IFace* Instantiate_(IDataBase* db, UID uid, PMIID iid)
		{ return db ? static_cast<IFace*>(db->Instantiate(uid, iid)) : nil; }

	static IFace* Instantiate_(const UIDRef& ref, PMIID iid)
		{ IDataBase* db = ref.GetDataBase(); return db ? static_cast<IFace*>(db->Instantiate(ref.GetUID(), iid)) : nil; }

#ifdef ID_ENABLE_DEBUGGING
	void AssertAboutUsingNilPtr() const;
	void SaveOffDebugInfo(const IPMUnknown* p, PMIID iid);
#endif

#ifdef ID_ENABLE_DEBUGGING
	public: // ick - this has to be public so I can use it for the IntefacePtrs containing <OtherType>
	ClassID fDebugLastBossQueried;
	PMIID fDebugLastIIDQueried;
	private:
#endif
	IFace * fFace;
};

template <class T>
inline void swap(InterfacePtr<T> &a, InterfacePtr<T> &b) noexcept
{
	a.swap(b);
}

#ifdef ID_ENABLE_DEBUGGING
#include "IControllingUnknown.h"

template <class T> void InterfacePtr<T>::SaveOffDebugInfo(const IPMUnknown* p, PMIID iid) 
{
	fDebugLastIIDQueried = iid;
	fDebugLastBossQueried = kInvalidClass;
	if(p)
	{
		IControllingUnknown *boss = (IControllingUnknown*)p->QueryInterface(IID_ICONTROLLINGUNKNOWN);
		if(boss)
		{
			fDebugLastBossQueried = boss->GetClass();
			boss->Release();
		}
			
	}
}

#include "DebugClassUtils.h"
template <class T> void InterfacePtr<T>::AssertAboutUsingNilPtr() const
{
	DebugClassUtilsBuffer idBuf1,idBuf2;
	ASSERT_FAIL(FORMAT_ARGS("About to use nil interface ptr! Queried IID was %s, on Boss %s",DebugClassUtils::GetIDName(&idBuf1,fDebugLastIIDQueried),DebugClassUtils::GetIDName(&idBuf2,fDebugLastBossQueried)));
}
#endif


//#if MACINTOSH
#if 0
void DestroyInterfacePtr(); // shouldn't be cross toc

template <class T>
asm InterfacePtr<T>::~InterfacePtr()
 {
	nofralloc
	b	       DestroyInterfacePtr
}
#else

template <class T>
inline InterfacePtr<T>::~InterfacePtr()
{
	Release_(fFace);
}
#endif // MACINTOSH

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_1("interfaceptr:indesign:adobe",InterfacePtr<T0>)

#endif // __InterfacePtr__

