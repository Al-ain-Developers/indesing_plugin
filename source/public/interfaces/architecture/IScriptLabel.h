//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptLabel.h $
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
#ifndef __IScriptLabel__
#define __IScriptLabel__

#include "IPMUnknown.h"
#include "KeyValuePair.h"
#include "ScriptingID.h"

/**
	Data interface for script labels
*/
class IScriptLabel : public IPMUnknown
{
public:
	enum  { kDefaultIID = IID_ISCRIPTLABEL };

	typedef PMString											ScriptLabelKey ;
	typedef PMString											ScriptLabelValue ;
	typedef KeyValuePair<ScriptLabelKey, ScriptLabelValue>		ScriptLabelKeyValuePair ;
	typedef K2Vector<ScriptLabelKeyValuePair>					ScriptLabelKeyValueList ;

	/**
		The key for the default label property
	*/
	PUBLIC_DECL static ScriptLabelKey kDefaultScriptLabelKey ;

	/**
		Set the default label property
		@param string is the label to set
	*/
	virtual void							SetTag( const ScriptLabelValue& string ) = 0 ;
	/**
		Get the default label property
	*/
	virtual ScriptLabelValue				GetTag() const = 0 ;

	/**
		Set a user-definable label
		@param key is the key
		@param value is the value
	*/
	virtual void							SetTag( const ScriptLabelKey& key, const ScriptLabelValue& value ) = 0 ;
	/**
		Get a user-definable label
		@param key is the key
		@return is the value
	*/
	virtual ScriptLabelValue				GetTag( const ScriptLabelKey& key ) const = 0 ;

	/**
		Set a list of user-definable labels
	*/
	virtual void							SetTags( const ScriptLabelKeyValueList& labels ) = 0 ;
	/**
		Get the list of all the user-definable labels
	*/
	virtual ScriptLabelKeyValueList			GetTags() const = 0 ;

	/**
		Clear all of the user-definable labels
	*/
	virtual void							ClearTags() = 0 ;
};

#endif	// __IScriptLabel__
