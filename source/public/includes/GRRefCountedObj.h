//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GRRefCountedObj.h $
//  
//  Owner: ?
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
#ifndef __REFCOUNTEDOBJ__
#define __REFCOUNTEDOBJ__

#ifndef _BASETYPE_
#include "BaseType.h"
#endif

#pragma export on

/**
 grRefCountedObj is the base class for various objects that require reference
 counting to control their lifetimes. Objects of this kind should typically be
 created on the heap using new, rather than on the stack.

 @see IPlatformOffscreen
 @see IFontGroup
 @see IFontGroupId
 @see IFontInstance
 @see IHypenatedWord
 @see IkfStyle
 @see IPMFont
 */
class    PUBLIC_DECL   grRefCountedObj
{
	public:
		/**
		 Simple constructor. Creates object with ref count of 1.
		 */
		grRefCountedObj() : fRefCount(1)
			{}

		/**
		 Destructor.
		 */
		virtual ~grRefCountedObj() = 0;

		/**
		 Increases ref count by 1.
		 */
		virtual void AddRef() const;

		/**
		 Decreases ref count by 1. If ref count becomes zero, deletes the object.
		 */
		virtual void Release() const;

	protected:
		mutable int32 fRefCount;

          private:
		// not defined
		grRefCountedObj(const grRefCountedObj &obj);
		grRefCountedObj &operator=(const grRefCountedObj &obj);
};

#pragma export off

#endif