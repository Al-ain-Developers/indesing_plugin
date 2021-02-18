//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPMUnknown.h $
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
#ifndef __CPMUnknown__
#define __CPMUnknown__


/** CPMUnknown is provided as a simple way for your interface to implement QueryInterface,
	AddRef, and Release, which are required for all interfaces (they are pure virtual 
	functions declared in IPMUnknown). In addition, it also declares and defines a helper 
	function, PreDirty, which is used for persistent interfaces only.
	
	This class provides the same functionality as the macros in HelperInterface.h; it is
	intended to be a replacement for those macros. You should not need to call methods in
	CPMUnknown yourself directly.

	See below for an example of how to use CPMUnknown:

<pre>
#include "CPMUnknown.h"

class Foo : public CPMUnknown<IFoo> {

					Foo(IPMUnknown* boss);
	virtual void	SomeMethod();
private:
    MyStruct*       fMyStruct;
};

CREATE_PMINTERFACE(Foo, kFooImpl)

Foo:Foo(IPMUnknown* boss)
	:  CPMUnknown<IFoo>(boss),
	   fMyStruct(nil)

{
}
</pre>

*/
#include "HelperInterface.h"


// Helper class for manaaging multiple PreDirty calls
class DirtyOptimizer : boost::noncopyable
{
public:

	DirtyOptimizer (IPMUnknown *face) :
		fFace (face),
		fDirtied (false)
	{
	}

	inline void PreDirty (ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue)
	{
		if (!fDirtied)
		{
			::PreDirty (fFace, prop, allowModification);
			fDirtied = true;
		}
	}

	inline void PreDirtyNoMessage (ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue)
	{
		if (!fDirtied)
		{
			::PreDirtyNoMessage (fFace, prop, allowModification);
			fDirtied = true;
		}
	}

private:

	IPMUnknown *fFace;
	bool fDirtied;
};


//========================================================================================
// CPMUnknown
//========================================================================================

template <class Interface>
class CPMUnknown : public Interface
{
public:
	/** @see IPMUnknown::QueryInterface() */
	IPMUnknown *QueryInterface(PMIID interfaceID) const;
	/** @see IPMUnknown::AddRef() */
	void AddRef() const;
	/** @see IPMUnknown::Release() */
	void Release() const;
	void PreDirty(ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);
	void PreDirtyNoMessage(ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

	// Don't allow default construction, copy construction or assignment...
    CPMUnknown() = delete;
	CPMUnknown(const CPMUnknown &) = delete;
	CPMUnknown &operator =(const CPMUnknown &) = delete;

protected:
	explicit CPMUnknown(IPMUnknown *boss);	
	HelperInterface fHelperInterface;
};

//========================================================================================
// CPMUnknown implementation
//========================================================================================

template <class Interface>
CPMUnknown<Interface>::CPMUnknown(IPMUnknown *boss) :
	fHelperInterface(boss)
{
}

template <class Interface>
void CPMUnknown<Interface>::AddRef() const
{
	fHelperInterface.AddRef();
}
	
template <class Interface>
void CPMUnknown<Interface>::Release() const
{
	fHelperInterface.Release();
}

template <class Interface>
void CPMUnknown<Interface>::PreDirty(ImplementationID prop, bool16 allowModification)
{
	::PreDirty(this, prop, allowModification);
}

template <class Interface>
void CPMUnknown<Interface>::PreDirtyNoMessage(ImplementationID prop, bool16 allowModification)
{
	::PreDirtyNoMessage(this, prop, allowModification);
}

template <class Interface>
IPMUnknown* CPMUnknown<Interface>::QueryInterface(PMIID interfaceID) const
{
#ifdef DEBUG
	if (interfaceID == IID_IGETINTERFACEIMPL)
		return const_cast<CPMUnknown<Interface> *>(this);
#endif
		
	return fHelperInterface.QueryInterface(interfaceID);
}

#endif //__CPMUnknown__
