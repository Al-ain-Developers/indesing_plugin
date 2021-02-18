//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AppPrefsListElementTypes.h $
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
//========================================================================================

#pragma once
#ifndef __AppPrefsListElementTypes__
#define __AppPrefsListElementTypes__

#include "ScriptingDefs.h"
#include <set>
#include "XPID.h"
#include "XMLID.h"

#pragma export on
/** This is a helper class that keeps a list of all standard element types that we export
*/
class PUBLIC_DECL AppPrefsListElementTypes 
{
public:
	/**
		Is the specified type a list element that we export?
	
		@param	elementType the type we are inquiring about
		@return	bool16 kTrue if this elementType is in the list, kFalse if not
	*/
	static bool16 IsTypeInList( ScriptID elementType )
	{
		const std::set<ScriptID>& elementTypes = GetListElementTypes();
		return (elementTypes.find(elementType) != elementTypes.end());
	}

	/**
		returns a list of list element types that are part of the standard export
	*/
	static const std::set<ScriptID>& GetListElementTypes();
		
};
#pragma export off

#endif //__AppPrefsListElementTypes__
