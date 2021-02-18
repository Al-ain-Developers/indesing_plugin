//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMUnknown.h $
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
//  Purpose:
//  Base class for interfaces. Provides mechanism for querying interfaces, and for
//  ref-counting objects.
//  
//========================================================================================

#pragma once
#ifndef __IPMUNKNOWN__
#define __IPMUNKNOWN__


// On Metrowerks on the Mac, in order to force COM compatible vtables we have to 
// inherit from SingleObject.
#if defined(MACINTOSH) && defined(__MWERKS__) && !defined(__MACH__)
#define INHERITFROM :public SingleObject
#else
#define INHERITFROM
#endif

/** IPMUnknown is the root class that all interfaces inherit from.
	It provides the base functionality available to all interfaces.
	@ingroup arch_om
*/

class IPMUnknown  INHERITFROM {
public:	
		/** Return the requested interface, if the object supports
			it. If the interface is not available, returns nil. 
			QueryInterface will call AddRef on the interface for
			you; you should call Release when you are done with it.
			Usually you do not need to call either QueryInterface
			or Release directly; this is something that InterfacePtr
			will do for you.
		*/
	virtual IPMUnknown *QueryInterface(PMIID interfaceID) const  = 0;
			
		/** Increase the ref count by one. Normally you do not need
			to do this, since QueryInterface does this for you. But
			if you are passed a pointer to an interface, and wish to
			acquire the reference, you must call AddRef on the interface.
		*/
	virtual void AddRef() const = 0;
		
		/** Decrease the ref count by one. Every call to QueryInterface
			or AddRef must be matched by a call to Release. Usually you 
			do not need to call either QueryInterface or Release directly; 
			this is something that InterfacePtr will do for you.
		*/
	virtual void Release() const = 0;
};

#endif	// __IPMUNKNOWN__
