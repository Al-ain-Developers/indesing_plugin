//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptObject.h $
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
#ifndef __ScriptObject__
#define __ScriptObject__

#include "ScriptInfo.h"

using namespace ScriptInfo ;

/**
	A ScriptObject contains all the data necessary to construct an object specifier.
*/
class ScriptObject
{
public:
   	typedef object_type data_type;   

	/** Construct a default (invalid) specifier */
	ScriptObject() : 
		specifierData(), objectType( kInvalidScriptID ), specifierForm( kFormInvalid ), rangeData()
	{}

	/** Construct a basic specifier */
	ScriptObject( const ScriptData& inSpecifierData, const ScriptID& inObjectType, SpecifierForm inSpecifierForm ) :
		specifierData( inSpecifierData ), objectType( inObjectType ), specifierForm( inSpecifierForm ), rangeData()
	{}

	/** Construct a range specifier */
	ScriptObject( const ScriptID& inObjectType, const ScriptObject& from, const ScriptObject& to ) :
		specifierData(), objectType( inObjectType ), specifierForm( kFormRange ), rangeData()
	{
		rangeData.push_back( from ) ;
		rangeData.push_back( to ) ;
	}

	/** Equality */
	bool16 operator==(const ScriptObject& scriptObject) const
	{ 
		return ( objectType == scriptObject.objectType &&
				specifierForm == scriptObject.specifierForm &&
				specifierData == scriptObject.specifierData &&
				rangeData == scriptObject.rangeData ) ;
	}

public:
	/** The data that specifies the object, such as the name (string), the index (long), the id (long), etc. */
	ScriptData specifierData;
	/** The object type */
	ScriptID objectType;
	/** The specifier's form */
	SpecifierForm specifierForm;
	/** From and to objects for a range specifier */
	K2Vector<ScriptObject> rangeData;
};

#endif
