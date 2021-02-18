//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CreateObject.h $
//  
//  Owner: rbriggs
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
#ifndef __CreateObject__
#define __CreateObject__

#include "IObjectModel.h"
#include "ISession.h"
#include "IPMUnknown.h" // for the definition of INHERITFROM


/** Functor object used for customizing object creation. Used when instantiating
	attribute boss lists, to insure that bosses of the correct type are created.
	For internal use only.
*/
class ICreateObjectFunctor INHERITFROM
{
public:
	virtual IPMUnknown *CreateObject(ClassID clsID, PMIID interfaceID) = 0;
};


#ifdef PUBLIC_BUILD
#pragma export on
#endif

class RsrcSpec;
class IResourceAccess;


	/**@name  Functions for creating bosses  */
	//@{-----------------------------------------------------------------------------

	/** Create a new non-persistent object of the specified class, and returns the requested 
		interface of the boss. Returns nil if the object cannot be created, or if the requested 
		interface does not exist. The caller is responsible for releasing the boss when done with 
		it.
		@param clsID boss class of the new object
		@param iid which interface of the boss to return
		@return the requested interface of the new boss
	*/
PUBLIC_DECL IPMUnknown* CreateObject(ClassID clsID, PMIID iid = IID_IUNKNOWN, const IObjectModel*om = GetObjectModelInstance());
	
	/** Create a new object of the specified class, and returns the requested interface of the
		boss. The new object is created persistently if db is non-nil, otherwise a 
		non-persistent object is created. Returns nil if the object cannot be created, or 
		if the requested interface does not exist. The caller is responsible for releasing 
		the boss when done with it.
		@param db database for the new object, if it's persistent
		@param id boss class of the new object
		@param iid which interface of the boss to return
		@return the requested interface of the new boss
	*/
PUBLIC_DECL IPMUnknown* CreateObject(IDataBase* db, ClassID id, PMIID iid = IID_IUNKNOWN);

	/** Create a new object from a resource description. The new object is created persistently 
		if db is non-nil, otherwise a non-persistent object is created. Returns nil if the object 
		cannot be created, or if the requested interface does not exist. The caller is responsible 
		for releasing the boss when done with it. Used for creation of widgets.
		If the boss supports IControlView, CreateObject will call DoPostCreate on the new boss.
		@param db database for the new object, if it's persistent
		@param spec resource descriptor for the resource to read from
		@return the requested interface of the new boss
	*/
PUBLIC_DECL IPMUnknown* CreateObject(IDataBase* db, const RsrcSpec& spec, PMIID iid = IID_IUNKNOWN, const IObjectModel*om = GetObjectModelInstance());

	/** Create a new object from a resource description. Exactly similar to CreateObject from a resource
		descriptor except it doesn't call DoPostCreate. The new object is created persistently 
		if db is non-nil, otherwise a non-persistent object is created. Returns nil if the object 
		cannot be created, or if the requested interface does not exist. The caller is responsible 
		for releasing the boss when done with it. Used for creation of widgets.
		@param db database for the new object, if it's persistent
		@param spec resource descriptor for the resource to read from
		@return the requested interface of the new boss
	*/
PUBLIC_DECL IPMUnknown* CreateObjectNoInit (IDataBase* db, const RsrcSpec& spec, PMIID returnIID, const IObjectModel*om = GetObjectModelInstance());

	//@}-----------------------------------------------------------------------------

// ***************************************************************************************************
// Drover based widgets created/read from resources need a context to indicate to the panel control
// data that there is an underlying UI_Node off this boss. This is so things get addref'd properly.
// During stream resource read, an extra addref on the IControlView interface keeps the drover based
// widget boss from being immediately destroyed since at present, unlike our old platform based
// widgets, we don't allow drover based widgets in the instance cache. This AddRef is compensated
// for in DVControlPanelData::ReadWrite.

namespace ResourceStreamReadContext
{
    PUBLIC_DECL bool16	IsResourceStreamReadContextActive();
}
 
// ***************************************************************************************************


#pragma export off

	/**@name  Template-based functions for creating bosses  */
	//@{-----------------------------------------------------------------------------


// These work like CreateObject(ClassID, PMIID), but you can omit the interface ID if the 
// face defines kDefaultIID and the correct face pointer is returned. Usage is like this:
// ::CreateObject2<ITableTarget>(kTableSelectionBoss).

/** Works like CreateObject(ClassID, PMIID), but you can omit the interface ID if the 
	face defines kDefaultIID and the correct face pointer is returned, already coerced
	into the correct type. Usage is like this:
	<pre>
	::CreateObject2<ITableTarget>(kTableSelectionBoss).
	</pre>
	@param clsID boss class of the new object
	@return the requested interface of the new boss
*/
template <class FACE>									
inline FACE* CreateObject2(ClassID clsID)						// do not forward declare these: CW Pro 5 won't inline them if they're forward declared...
{	
	IPMUnknown* face = CreateObject(clsID, FACE::kDefaultIID);
	
	return static_cast<FACE*>(face);
}

/** Works like CreateObject(ClassID, PMIID), but the face pointer is returned already coerced
	into the correct type. Usage is like this:
	<pre>
	::CreateObject2<IObserver>(kFooBoss, IID_IMYOBSERVER).
	</pre>
	@param clsID boss class of the new object
	@param iid which interface of the boss to return
	@return the requested interface of the new boss
*/
template <class FACE>								
inline FACE* CreateObject2(ClassID clsID, PMIID iid)
{	
	IPMUnknown* face = CreateObject(clsID, iid);
	
	return static_cast<FACE*>(face);
}

/** Works like CreateObject(IDataBase* db, ClassID id, PMIID iid), except you can omit 
	the interface ID if the face defines kDefaultIID and the correct face pointer is returned,
	already coerced into the correct type.
	@param db database for the new object, if it's persistent
	@param id boss class of the new object
	@return the requested interface of the new boss
*/
template <class FACE>									
inline FACE* CreateObject2(IDataBase* db, ClassID clsID)
{	
	IPMUnknown* face = CreateObject(db, clsID, FACE::kDefaultIID);
	
	return static_cast<FACE*>(face);
}

/** Works like CreateObject(IDataBase* db, ClassID id, PMIID iid), except the face pointer 
	is returned, already coerced into the correct type.
	@param db database for the new object, if it's persistent
	@param clsID boss class of the new object
	@param iid which interface of the boss to return
	@return the requested interface of the new boss
*/
template <class FACE>									
inline FACE* CreateObject2(IDataBase* db, ClassID clsID, PMIID iid)
{	
	IPMUnknown* face = CreateObject(db, clsID, iid);
	
	return static_cast<FACE*>(face);
}

/** Works like CreateObject(IDataBase* db, const RsrcSpec& spec, PMIID iid), except you can omit 
	the interface ID if the face defines kDefaultIID and the correct face pointer is returned,
	already coerced into the correct type.
	@param db database for the new object, if it's persistent
	@param spec resource descriptor for the resource to read from
	@return the requested interface of the new boss
*/
template <class FACE>									
inline FACE* CreateObject2(IDataBase* db, const RsrcSpec& spec)
{	
	IPMUnknown* face = CreateObject(db, spec, FACE::kDefaultIID);
	
	return static_cast<FACE*>(face);
}

	//@}-----------------------------------------------------------------------------


#endif // __CreateObject__
