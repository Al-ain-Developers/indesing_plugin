//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptArgs.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __IScriptArgs_h__
#define __IScriptArgs_h__

#include "IPMUnknown.h"
#include "ScriptingID.h"

//========================================================================================
// CLASS IScriptArgs
//========================================================================================

/** Set and get parameters that are accessible from scripts. There is a concept of a
	current context, where a context is simply a set of script parameters. When you
	save the current context, a new context is created and the existing one pushed on
	a stack of saved contexts. When a context is restored, the existing one is replaced
	by the top context on the saved context stack. This makes it easy to make nested
	calls to scripts with parameters. SaveContext/RestoreContext should be used in pairs.

	@ingroup scripting
*/
class IScriptArgs : public IPMUnknown
{
public:

public:
	enum { kDefaultIID = IID_ISCRIPTARGS };

		/** Set a scripting parameter in the current context.
			
			@param name of the parameter
			@param value of the parameter
		*/
	virtual void			Set( const PMString& name, const PMString& value) = 0;

		/** Get the value of a scripting parameter in the current context.
			
			@param name of scripting parameter to get
			@return the value of the scripting parameter.
		*/			
	virtual PMString		Get( const PMString& name ) const = 0;
	
		/** Determines whether a parameter is defined in the current context.
			
			@param name of scripting parameter
			@return true if the parameter is defined, otherwise false.
		*/			
	virtual bool			IsDefined( const PMString& name ) const = 0;

		/** Removes all scripting parameters, in the current context.
			
		*/			
	virtual void			Clear() = 0;

		/** Saves the current set of scripting parameters on the context stack and
			creates a new current context, that has no parameters set.
			
		*/			
	virtual void			Save() = 0;

		/** Replaces the current existing context with the top context on the
			stack of saved contexts.
			
		*/			
	virtual ErrorCode		Restore() = 0;
};


#endif // __IERRORLIST_h__
