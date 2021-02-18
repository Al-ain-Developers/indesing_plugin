//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptManager.h $
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
#ifndef __IScriptManager__
#define __IScriptManager__

#include "IPMUnknown.h"
#include "ScriptingID.h"
#include "ScriptInfo.h"

//class PMString ;
class IScriptEngine ;

using namespace ScriptInfo ;

/**
	Every scripting language supported by InDesign must implement this interface to provide
	basic information about support for the scripting language.

	Most implementations will want to inherit from CScriptManager.
*/
class IScriptManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTMANAGER } ;

	/**
		Tells the script manager to install
	*/
	virtual	ErrorCode			Install() = 0 ;
	/**
		Tells the script manager to uninstall
	*/
	virtual	ErrorCode			UnInstall() = 0 ;

	/**
		Determine whether a script is running under this manager
	*/
	virtual bool16				IsScriptActive() const = 0 ;

	/**
		Get the number of engines for this client
	*/
	virtual uint32				GetNumEngines() const = 0 ;

	/**
		Query the nth engine for this client
	*/
	virtual IScriptEngine*		QueryNthEngine( uint32 n ) const = 0 ;

	/**
		Query the default engine for this client
	*/
	virtual IScriptEngine*		QueryDefaultEngine() const = 0 ;

	/**
		Returns the policy for returning errors during a request
		@param requestID		the property or event ID for which the error policy is being requested
								(pass kInvalidScriptID to retrieve the default policy)
	*/
	virtual ErrorPolicy			GetErrorPolicy( ScriptID requestID = kInvalidScriptID ) const = 0 ;

	/**
		Returns the policy for the order to set properties when setting multiple properties at once
	*/
	virtual SetPropertiesOrderPolicy	GetSetPropertiesOrderPolicy() const = 0 ;

	/**
		Access to policies for formatting the name of script elements
		@param element is the element type for which the format name policies are being requested
		@param context for the policy
		@return the policy
	*/
	virtual FormatNamePolicy	GetFormatNamePolicy( ScriptElementType element, const RequestContext& context ) const = 0 ;

	/**
		Convert a script info type into a string representation. This is the preferred overload.
		@param ti is the type info to convert
		@param the object context for the conversion (must not be nil)
		@param includeInfo options are defined in enum TypeFormattingInfo
		@return the string representation
	*/
	virtual PMString			GetTypeAsString( const TypeInfo& ti, const ObjectScriptElement* pObjSI, int32 includeInfo ) const = 0 ;

	/**
		Convert a script info type into a string representation. Use this overload only if no ObjectScriptElement is relevant.
		@param ti is the type info to convert
		@param context for the conversion
		@param includeInfo options are defined in enum TypeFormattingInfo
		@return the string representation
	*/
	virtual PMString			GetTypeAsString( const TypeInfo& ti, const RequestContext& context, int32 includeInfo ) const = 0 ;

	/**
		@return the base for an object's index; in other words, the index
		of the first object. Typically 0 (the default) or 1.
	*/
	virtual	int32				GetBaseIndex() const = 0 ;

	/**
		Publish any information about the object model
	*/
	virtual ErrorCode			PublishDescription( const RequestContext& ) = 0 ;

	/**
		@return this client's minimum script DOM version (the first DOM version 
		supported by this client for the given product/feature set/locale)
	*/
	virtual ScriptVersion		GetMinimumDOMVersion( const PMLocaleId& locale ) const = 0 ;

	/**
		@return this client's maximum script DOM version (the last DOM version 
		supported by this client for the given product/feature set/locale)
	*/
	virtual ScriptVersion		GetMaximumDOMVersion( const PMLocaleId& locale ) const = 0 ;

	/**
		@return this client's enumerator for the kScriptLanguageEnumScriptElement (or kInvalidScriptID if not applicable)
	*/
	virtual ScriptID			GetLanguageEnumerator() const = 0 ;

	/**
		@return this client's name
	*/
	virtual PMString			GetName() const = 0 ;
} ;

#endif
