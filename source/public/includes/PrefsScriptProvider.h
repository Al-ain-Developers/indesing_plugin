//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PrefsScriptProvider.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef _H_PrefsScriptProvider
#define _H_PrefsScriptProvider

#include "CScriptProvider.h"
#include "KeyValuePair.h"

/**
	A base implementation of IScriptProvider for script providers that represent 
	singleton objects to subclass.
*/
class PUBLIC_DECL SingletonScriptProvider : public RepresentScriptProvider
{
protected:
	/**
		Subclasses of this implementation will represent their singleton object
	*/
	typedef RepresentScriptProvider Inherited ;

	/**
		Constructor
	*/
	SingletonScriptProvider( IPMUnknown* boss ) ;
	/**
		Destructor
	*/
	virtual ~SingletonScriptProvider() {}

	/**
		Override baseclass implementation to handle the one and only object on any parent
	*/
	virtual void		GetObject( IScriptRequestData* data, IScript* parent ) ;

	/**
		Returns the number of this kind of singleton object on the parent (should always == 1)
	*/
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent ) ;

	/**
		Appends the nth singleton object of the parent
	*/
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList ) ;	//0-based index

	/**
		Override baseclass implementation to handle the ParentProperty on supported parents
	*/
	virtual ErrorCode	AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**
		Call in constructor for each singleton object that the subclass implementation represents
		@param objectID - the id of the singleton object
		@param propID - the id of the property used to access the singleton object from a parent
		@param bossID - the id of the singleton object's script object boss
	*/
	void				DefineSingleton( const ScriptID& objectID, const ScriptID& propID, const ClassID& bossID ) ;

	/**
		Returns a singleton object
		@param propID - the property of the parent corresponding to the desired singleton object
		@param data - script event data for this request
		@param parent - the parent object
	*/
	virtual ErrorCode	AccessSingleton( ScriptID propID, IScriptRequestData* data, IScript* parent ) ;
	/**	
		Returns kTrue if this script provider supports the singleton object
		@param propID - the property of the parent corresponding to the desired singleton object
		@param parent - the parent object
	*/
	virtual bool16		CanAccessSingleton( ScriptID propID, IScript* parent ) const ;

	/**
		Creates a singleton object
		@param propID - the property of the parent corresponding to the desired singleton object
		@param parent - the parent object
	*/
	virtual IScript*	QuerySingleton( const IScriptRequestData* data, IScript* parent, const ScriptID& propID ) ;

private:
	struct SingletonData
	{
		ScriptID	fObjectID ;
		ClassID		fBossID ;

		SingletonData( ScriptID objectID, ClassID bossID ) : 
			fObjectID( objectID ), fBossID( bossID ) {}
		bool16 operator==( const SingletonData& other ) const
			{ return ( fObjectID == other.fObjectID && fBossID == other.fBossID ) ; }
	} ;
	typedef K2Vector< KeyValuePair<ScriptID, SingletonData> > SingletonIDs ;

	SingletonIDs		fSingletonIDs ;
};

DECLARE_BASE_TYPE( SingletonScriptProvider::SingletonData ) ;

/**
	A base implementation of IScriptProvider for script providers that represent 
	preferences objects to subclass.
*/
class PUBLIC_DECL PrefsScriptProvider : public SingletonScriptProvider
{
public:
	/**
		Subclasses of this implementation will represent their preferences object
	*/
	typedef SingletonScriptProvider Inherited ;

	/**
		Constructor
	*/
	PrefsScriptProvider( IPMUnknown* boss ) : Inherited( boss ) {}
	/**
		Destructor
	*/
	virtual ~PrefsScriptProvider() {}

protected:
	/**
		Returns the number of this kind of preferences object on the parent
	*/
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent ) ;

	/**
		Appends the nth preferences object of the parent
	*/
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList ) ;	//0-based index

	/**
		Appends every preferences object of the parent
	*/
	virtual ErrorCode	AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList ) ;

	/**
		Override baseclass implementation to handle the ParentProperty on supported parents
	*/
	virtual ErrorCode	AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**
		Call in constructor for each preferences object that the subclass implementation represents
		@param objectID - the id of the preferences object
		@param propID - the id of the property used to access the preferences object from a parent
		@param bossID - the id of the preferences objects script object boss
	*/
	void				DefinePreference( const ScriptID& objectID, const ScriptID& propID, const ClassID& bossID = kBasePrefsScriptObjectBoss ) ;

	/**
		Returns a preferences object
		@param propID - the property of the parent corresponding to the desired preferences object
		@param data - script event data for this request
		@param parent - the parent object
	*/
	virtual ErrorCode	AccessPreference( ScriptID propID, IScriptRequestData* data, IScript* parent ) ;
	/**	
		Returns kTrue if this script provider supports the preferences object
		@param propID - the property of the parent corresponding to the desired preferences object
		@param parent - the parent object
	*/
	virtual bool16		CanAccessPreference( ScriptID propID, IScript* parent ) const ;

	/**
		Creates a preferences object
		@param propID - the property of the parent corresponding to the desired preferences object
		@param parent - the parent object
	*/
	virtual IScript*	QueryPrefScript( const IScriptRequestData* data, IScript* parent, const ScriptID& propID ) ;

	/**
		Returns an interface on the preferences boss in the appropriate workspace (doc or session) containing the preferences script object
	*/
	static IPMUnknown*	QueryPreferences( const IScriptRequestData* data, const IScript* prefsScript, const PMIID& prefInterfaceID ) ;
};

#endif	/* _H_PrefsScriptProvider */
