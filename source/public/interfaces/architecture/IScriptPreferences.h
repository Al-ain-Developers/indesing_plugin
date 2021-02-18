//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptPreferences.h $
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
#ifndef __IScriptPreferences__
#define __IScriptPreferences__

#include "IPMUnknown.h"
#include "RequestContext.h"
#include "ScriptingID.h"

using namespace ScriptInfo ;

/**
	Preferences for the client when executing a script.
*/
class IScriptPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTPREFERENCES } ;

	/**
		Returns the version of the script info resources used for scripting requests
	*/
	virtual const ScriptVersion&	GetVersion() const = 0 ;
	/**
		Sets the version of the script info resources used for scripting requests
	*/
	virtual void					SetVersion( const ScriptVersion& ) = 0 ;

	/**
		Returns the locale of the script info resources used for scripting requests
	*/
	virtual const PMLocaleId&		GetLocale() const = 0 ;
	/**
		Sets the locale of the script info resources used for scripting requests
	*/
	virtual void					SetLocale( const PMLocaleId& ) = 0 ;

	/**
		Levels of UI interaction with the user during script execution
	*/
	enum InteractionLevel
	{
		kNeverInteract			= en_NeverInteract,
		kInteractWithAlerts		= en_InteractWithAlerts,
		kInteractWithAll		= en_InteractWithAll
	} ;
	/**
		Returns the current level of UI interaction
	*/
	virtual InteractionLevel		GetInteractionLevel() const = 0 ;
	/**
		Sets the level of UI interaction
	*/
	virtual void					SetInteractionLevel( InteractionLevel ) = 0 ;

	/**	Gets the class id of the measurement system. e.g. kPointsBoss, kMillimetersBoss
		If the class id is valid, it is used when converting script data to/from unit type.
		@return ClassID 
	 */
	virtual ClassID		GetUnitOfMeasure() const = 0;
	/**	Sets the class id of the measurement system.
		This is used when converting script data to/from unit type. @see ScriptData.
		@param bossId - the classID of the measurement system. Pass in kInvalidClass to clear the unit. 
	 */
	virtual void		SetUnitOfMeasure(const ClassID& bossId) = 0;
} ;

/**
	Preferences for the application environment when executing scripts.
*/
class IGlobalScriptPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGLOBALSCRIPTPREFERENCES } ;

	/**
		Returns whether to allow redraw while executing scripts
	*/
	virtual bool16					GetEnableRedraw() const = 0 ;
	/**
		Sets whether to allow redraw while executing scripts
	*/
	virtual void					SetEnableRedraw( bool16 ) = 0 ;
} ;

#endif	// __IScriptPreferences__
