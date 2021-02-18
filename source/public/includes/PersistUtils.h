//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistUtils.h $
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
//  Utilities for getting objects' persistent identity.
//  
//========================================================================================

#pragma once
#ifndef __PersistUtils__
#define __PersistUtils__

class IContentMgr;
class IControllingUnknown;

#include "UIDRef.h"

/** This file contains a set of useful functions for use with persistent 
	objects, and object model interactions.

*/
#pragma export on
	/** Return the object's UID, or Unique Identifier. Persistent objects 
		are usually created in a document. You can make calls on the object 
		using a pointer to the object, but in order to refer to it persistently
		or across instantiations, you need its UID. Given the UID (and the
		document or database), you can instantiate it using InterfacePtr.
		
	    @param obj the object we're interested in
		@return UID of the object, or kInvalidUID if the object is not persistent
	*/
PUBLIC_DECL UID GetUID( const IPMUnknown *obj);
	
	/** Return the database the object is in. Every document has a database
		associated with it, as does the defaults file, books, and a few other
		InDesign file types.

	    @param obj the object we're interested in
		@return IDataBase* the database the object is in, or nil if the
		object is not persistent.
	*/
PUBLIC_DECL IDataBase *GetDataBase(const IPMUnknown *obj);
	
	/** Return the UIDRef of the object. A UIDRef is the (IDataBase*,
		UID) pair that describes the object on disk. Returns a
		UIDRef with (nil, kInvalidUID) if the object is not persistent.

	    @param obj the object we're interested in
		@return UIDRef a persistent reference to the object.
	*/
PUBLIC_DECL UIDRef GetUIDRef(const IPMUnknown *obj);
	
	/** Mark the interface as dirty, which causes the object to be marked
		dirty in the database. When the object is destructed, or when the
		database is flushed, the object's IPMPersist interface will call
		the interface's registered ReadWrite function.
		The allowModification flag indicates whether dirtying this object
		should cause the database to be considered dirtied.  (In other words,
		should the user be prompted to save changes?).

	    @param pFace the interface to be dirtied
	    @param prop the ImplementationID of the interface (typically leave this blank, it 
	    will be supplied automatically)
	    @param allowModification kTrue if the database should be marked as dirty
	*/
PUBLIC_DECL void PreDirty(IPMUnknown *pFace, ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

PUBLIC_DECL void PreDirtyAllowDuplicateMessage(IPMUnknown *pFace, ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

PUBLIC_DECL void PreDirtyNoMessage(IPMUnknown *pFace, ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

PUBLIC_DECL void PreDirtyOverrideMessage(IPMUnknown *pFace, PMIID overrideIID, ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

PUBLIC_DECL void PreDirtyOverrideAllowDuplicateMessage(IPMUnknown *pFace, PMIID overrideIID, ImplementationID prop = kInvalidImpl, bool16 allowModification = kTrue);

	/** Mark the interface as dirty, which causes the object to be marked
		dirty in the database. When the object is destructed, or when the
		database is flushed, the object's IPMPersist interface will call
		the interface's registered ReadWrite function.
		The allowModification flag indicates whether dirtying this object
		should cause the database to be considered dirtied.  (In other words,
		should the user be prompted to save changes?). If you already have a 
		pointer to a boss, this is a more efficient method to call that the 
		PreDirty that takes a IPMUnknown*.

	    @param pFace the interface to be dirtied
	    @param prop the ImplementationID of the interface (typically leave this blank, it 
	    will be supplied automatically)
	    @param allowModification kTrue if the database should be marked as dirty
	*/
PUBLIC_DECL void PreDirty(IControllingUnknown *boss, IPMUnknown *p, ImplementationID prop, bool16 allowModification);

PUBLIC_DECL void PreDirtyNoMessage(IControllingUnknown *boss, IPMUnknown *p, ImplementationID prop, bool16 allowModification);

	/** Mark the view interface as dirty, which causes the object to be
		restored at undo and redo. A view interface is created with CREATE_VIEW_PMINTERFACE.
		It has a view database that it tracks at undo and redo.
	    @param pFace the interface to be dirtied
	    @param prop the ImplementationID of the interface (typically leave this blank, it 
	    will be supplied automatically)
	*/
PUBLIC_DECL void PreDirtyViewInterface(IPMUnknown *pFace, ImplementationID prop = kInvalidImpl);

/** Return the classID of the object.

	    @param obj the object we're interested in (can be any interface of the object)
		@return ClassID of the object
	*/
PUBLIC_DECL ClassID GetClass( const IPMUnknown *obj);

	/** Returns kTrue if the two classes are compatible, that is if one is based on the other
		or vica versa of they are the same class.
	*/
PUBLIC_DECL bool16 ClassesAreCompatible(const ClassID& aClass, const ClassID& bClass);

	/** Returns kTrue if ancester is a base class of descendant.
	    @param anscestor the base class
	    @param descendant the derived class
	*/
PUBLIC_DECL bool16 ClassIsDescendantOf(const ClassID& anscestor, const ClassID& descendant);

	/** Copy length bytes from the input stream to the output stream.
	    @param inStream source stream (stream we're copying from)
	    @param outStream destination stream (stream we're copying to)
	    @param length number of bytes to copy
	*/
PUBLIC_DECL void CopyData(IPMStream *inStream, IPMStream *outStream, int32 length);

	class CopyDataFunctor 
	{
	public:
		virtual bool Transfer(uchar *buffer, uint32 len) = 0;
	};

PUBLIC_DECL void CopyData(IPMStream *inStream, int32 length, CopyDataFunctor *transferOut);


	/**@name  Following functions are for internal use only */
	//@{-----------------------------------------------------------------------------


#ifdef DEBUG
// only only only for debug code!
PUBLIC_DECL int32 GetRefCount(const IPMUnknown *obj);
PUBLIC_DECL ImplementationID GetImplID(const IPMUnknown *obj, PMIID interfaceID);
#endif


// Internal Use Only
// passing nil will return the application's plug-in ID.
PUBLIC_DECL PluginID GetPluginID( const IPMUnknown *obj );

	//@}-----------------------------------------------------------------------------

#pragma export off



#endif // __PersistUtils__
