//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Utils.h $
//  
//  Owner: Matt Joss
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
//  This is a helper class for calling methods in interfaces on the kUtilsBoss.  The Utils boss is an easy way
//  to share Utils across plugins without putting them in Public.  
//  The syntax to use is...
//  Utils<IFooUtils>()->MyFooMethod()
//  
//========================================================================================

#pragma once
#ifndef __Utils__
#define __Utils__


#include "ShuksanID.h"
#include "InterfacePtr.h"
#include "IPMUnknown.h"
#include "PMTypes.h"
#ifdef DEBUG
	#include "ISession.h"
#endif

/** UtilsBoss is a static class responsible for managing the single kUtilsBoss object. This object
	is used by the Utils<> helper object to get interfaces off the UtilsBoss. Ordinarily you should
	not need to use this class directly.
*/
class PUBLIC_DECL UtilsBoss
{
public:
	/** Called when the application is shutting down to release the referenced utils boss
		object. For internal use only.
	*/
	static void Purge();
	
	/** Returns a pointer to the requested interface of the kUtilsBoss, or nil if there is none.
		@param utilsIID		IID of the requested interface
		@return 			a pointer to the requested interface of the kUtilsBoss
	*/
	static IPMUnknown *	QueryUtils( const PMIID& utilsIID );
};



/** This is a helper class for calling methods in interfaces on the kUtilsBoss.  The Utils boss is an easy way
	access common utilities interfaces. 
	
	If you want to do a one-line call on a method in a utility interface, you can do this:
		Utils<IFooUtils>()->MyFooMethod();
		
	That one line will query the utils boss for the right interface, then call the MyFooMethod() on that
	interface.
	
	If you want to use a utility interface in several places, it is more efficient to get the interface
	once, save it in an InterfacePtr, and call it from there. For example:
	
		InterfacePtr<IFooUtils> fooUtils(Utils<IFooUtils>());
		
	This does the QueryInterface() and Release just once, which is better than once per call if you are
	making many calls.
*/
template <class IFace> 
class Utils
{
public:
		/** Construct a Utils helper object, which will Query for the <IFace> Interface on the utils boss. */
	inline	Utils() { fFace = UtilsBoss::QueryUtils(IFace::kDefaultIID); }
		/** Destruct a Utils helper object, which will Release the <IFace> interface on the utils boss. */
	inline ~Utils() { if(fFace) fFace->Release(); } 
	
		/** Return a pointer to the interface. The interface is good only until the Utils object is 
			destructed, since the destructor will Release the interface. 
			@return 	pointer to the utility interface
		*/
	inline IFace * operator ->() const { return static_cast<IFace*>(fFace); }
	
		/** Return a pointer to the interface. The interface is good only until the Utils object is 
			destructed, since the destructor will Release the interface. 
			@return 	pointer to the utility interface
		*/
	inline operator IFace*() { return static_cast<IFace*>(fFace); }
	
		/** Returns true if the utility interface is present. Call this before using the utility 
			interface if it's possible that the plug-in that supplies the interface has been removed.
			@return bool	kTrue if the interface exists, kFalse otherwise
		*/
	inline bool16 Exists() const { return fFace != nil; }

		/** Returns a referenced pointer to the utility interface. Caller is resposible for calling
			Release() on the interface that is returned. Use this method if you want to get a pointer
			to a utility interface that will stay good after the Utils object has been destructed.
			Example call:
					InterfacePtr<IFace>myUtil( Utils<IFace>().QueryUtilInterface() );
			@returns	referenced pointer to the utility interface
		*/
	inline IFace *QueryUtilInterface() { fFace->AddRef(); return static_cast<IFace*>(fFace); }

private:
		Utils<IFace>& operator=(const Utils<IFace>& other); // don't support this
		Utils<IFace>(const Utils<IFace>& copy); // don't support this

	IPMUnknown*	fFace;
};



#endif //__Utils__

	
