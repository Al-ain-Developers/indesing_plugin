//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScriptManager.h $
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
#ifndef __CSCRIPTMANAGER__
#define __CSCRIPTMANAGER__

#include "CPMUnknown.h"
#include "IScriptManager.h"

#include "PMString.h"

class IScriptInfoManager ;

/** Base implementation for IScriptManager */

class PUBLIC_DECL CScriptManager : public CPMUnknown<IScriptManager>
{
	typedef CPMUnknown<IScriptManager> Inherited ;

public:
	CScriptManager( IPMUnknown* boss ) ;
	virtual ~CScriptManager();

	/**
		Tells the script manager to install. Most client-specific 
		implementations WILL want to override this method.
	*/
	virtual	ErrorCode 			Install() ;
	/**
		Tells the script manager to uninstall. Most client-specific 
		implementations WILL want to override this method.
	*/
	virtual	ErrorCode			UnInstall() ;
	/**
		Determine whether a script is running under this manager. Most client-specific 
		implementations will NOT need to override this method.
	*/
	virtual bool16				IsScriptActive() const ;
	/**
		Get the number of engines for this client
	*/
	virtual uint32				GetNumEngines() const ;
	/**
		Query the nth engine for this client
	*/
	virtual IScriptEngine*		QueryNthEngine( uint32 n ) const ;
	/**
		Query the default engine for this client
	*/
	virtual IScriptEngine*		QueryDefaultEngine() const ;
	/**
		Returns the policy for returning errors during a request. Most client-specific 
		implementations will NOT need to override this method.
	*/
	virtual ErrorPolicy			GetErrorPolicy( ScriptID requestID = kInvalidScriptID ) const ;
	/**
		Returns the policy for the order to set properties when setting multiple properties at once. Most client-specific 
		implementations will NOT need to override this method.
	*/
	virtual SetPropertiesOrderPolicy GetSetPropertiesOrderPolicy() const ;
	/**
		Access to policies for formatting the name of script elements. Some client-specific 
		implementations may want to override this method.
	*/
	virtual FormatNamePolicy	GetFormatNamePolicy( ScriptElementType element, const RequestContext& context ) const ;
	/**
		Convert a script info type into a string representation. Most client-specific 
		implementations will NOT need to override this method.
	*/
	virtual PMString			GetTypeAsString( const TypeInfo& ti, const ObjectScriptElement* pObjSI, int32 includeInfo ) const ;
	/**
		Convert a script info type into a string representation. Most client-specific 
		implementations will NOT need to override this method.
	*/
	virtual PMString			GetTypeAsString( const TypeInfo& ti, const RequestContext& context, int32 includeInfo ) const ;
	/**
		@return the base for an object's index. Some client-specific 
		implementations may want to override this method.
	*/
	virtual	int32				GetBaseIndex() const ;
	/**
		Publish any information about the object model. Some client-specific 
		implementations may want to override this method.
	*/
	virtual ErrorCode			PublishDescription( const RequestContext& ) ;
	/**
		@return this client's minimum script DOM version (the first DOM version 
		supported by this client for the given product/feature set/locale). Most client-specific 
		implementations WILL need to override this method.
	*/
	virtual ScriptVersion		GetMinimumDOMVersion( const PMLocaleId& locale ) const ;
	/**
		@return this client's maximum script DOM version (the last DOM version 
		 supported by this client for the given product/feature set/locale). 
		Most client-specific implementations will NOT need to override this method.
	*/
	virtual ScriptVersion		GetMaximumDOMVersion( const PMLocaleId& locale ) const ;
	/**
		@return this client's enumerator for the kScriptLanguageEnumScriptElement. Scripting language client 
		implementations MUST override this method.
	*/
	virtual ScriptID			GetLanguageEnumerator() const ;
	/**
		@return this client's name. Scripting language client 
		implementations MUST override this method.
	*/
	virtual PMString			GetName() const ;

protected:
	/**	Appends type as a string. Most client-specific implementations 
		will NOT need to override this method. */
	virtual void				AppendTypeAsString(			const ObjectScriptElement* pObjSI, const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends base type as a string. Most client-specific implementations 
		WILL want to override this method. */
	virtual bool16				AppendBaseTypeAsString(		const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends range data as a string. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendRangeDataAsString(	const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends default value as a string. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendDefaultValueAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends object type as a string. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendObjectTypeAsString(	const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends enum type as a string. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendEnumTypeAsString(		const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends typedef as a string. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendTypeDefAsString(		const ObjectScriptElement* pObjSI, const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends the string for an array. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendArrayString(			const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;
	/**	Appends the string for a struct. Some client-specific implementations 
		may want to override this method. */
	virtual bool16				AppendStructString(			const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const ;

	/**	Sets the default policy for returning errors */
			void				SetDefaultErrorPolicy( ErrorPolicy policy ) ;
	/**	Sets the policy for returning errors during a specific property or event */
			void				SetSpecificErrorPolicy( ScriptID requestID, ErrorPolicy policy ) ;
	/**	Sets the policy for the order to use when setting multiple properties */
			void				SetSetPropertiesOrderPolicy( SetPropertiesOrderPolicy policy ) ;

private:
	K2Vector<KeyValuePair< ScriptID, ErrorPolicy > >	fErrorPolicies ;
	SetPropertiesOrderPolicy	fSetPropertiesOrderPolicy ;
} ;

#endif
