//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptClientObject.h $
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
#ifndef __ScriptClientObject__
#define __ScriptClientObject__

class IScript ;

/**
	A mixin class for scripting client object classes. This interface is used to inform
	a scripting client object that the InDesign object model boss that the client object 
	represents is being deleted. See @IScript
*/
class ScriptClientObject
{
public:
	/**
		Increment the number of references held by the object model on this ScriptClientObject. Typically 
		calls the object's AddRef() method, but may increment a separate reference count in order to 
		distinguish references held by the client from references held by the object model.
	*/
	virtual void AddRefFromObjectModel() const = 0;
		
	/**
		Decrement the number of references held by the object model on this ScriptClientObject. Typically 
		calls the object's Release() method, but may decrement a separate reference count in order to 
		distinguish references held by the client from references held by the object model.
	*/
	virtual void ReleaseRefFromObjectModel() const = 0;

	/**
		Release all InDesign object model boss references that are being held by this client
		object (possibly including any child collection client objects) on the passed in boss.
		@param script is the IScript interface on the boss making the request. Typically the
		client object will call "script->UnregisterClientObject( this )" as part of its 
		implementation of this method.
	*/
	virtual void ReleaseReferencesToObjectModel( IScript* script ) = 0 ;
} ;

#endif
