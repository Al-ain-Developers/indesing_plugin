//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptObjectParent.h $
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
#ifndef __IScriptObjectParent__
#define __IScriptObjectParent__

#include "IPMUnknown.h"

#include "RequestContext.h"
#include "ScriptingID.h"

using namespace ScriptInfo ;

/**
	Interface for storing parent of a proxy script object. Works in tandem with
	parent database's IScriptObjectMgr interface to track proxy script objects for deletion.

	Most clients should use the default implementation (kScriptObjectParentImpl),
	along with the base proxy script object implementation (kCProxyScriptImpl) or a subclass
	thereof. The simplest approach is by boss inheritance (from kBaseProxyScriptObjectBoss).

	Except for calling SetParent during creation of a proxy object, methods on this interface 
	are generally for INTERNAL USE ONLY by the scripting architecture. Actual calls to this 
	interface should therefore be very rare.
	@see IScriptObjectMgr
*/  
class IScriptObjectParent : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTOBJECTPARENT } ;

	/**	Stores the parent. Called when creating a proxy object (e.g., from IScriptUtils::CreateProxyScriptObject). */
	virtual void SetParent( const IPMUnknown* parent, const RequestContext& context, bool16 notifyParent = kTrue ) = 0 ;

	/**	Clear the parent. */
	virtual void ClearParent( bool16 notifyParent = kTrue ) = 0 ;

	/**	Returns parent's true or de facto database (i.e., even if parent is not persistent). Use of IScript::GetDataBase() is preferred. */
	virtual IDataBase* GetParentDataBase() const = 0 ;

	/**	Queries the parent (will return nil if parent no longer exists). Use of IScript::QueryParent() is preferred. */
	virtual IPMUnknown* QueryParent( const PMIID& iid ) const = 0 ;

	/**	Returns kTrue if parent has been set. */
	virtual bool16 IsParentSet() const = 0 ;
} ;

#endif // __IScriptObjectParent__
