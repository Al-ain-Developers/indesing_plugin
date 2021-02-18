//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookRef.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPMStream.h"

class IPreflightBookData;

/**	When we preflight or package a book we create a book preflight boss. We need some way to
	associate that boss with the book that 'owns' it, which is the purpose of this interface.
	It sits on the book itself and maintains the short list of book-preflight bosses. This 
	way we know that when the book is closed we're also going to get rid of any related
	preflight data.

*/
class IPreflightBookRef: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKREF };

public:
	/** Query the current/active preflight for this book. This is the preflight that is 
		created as a consequence of the user requesting preflight for a book.

		@return The refcounted data interface for the book preflight boss.
	*/
	virtual IPreflightBookData* QueryActivePreflight() const = 0;

	/** Set the current/active preflight for this book. The existing data is released (and
		therefore typically deleted since these are nonpersistent bosses).

		@param The data interface for the book-preflight boss. This is refcounted by this method.
	*/
	virtual void SetActivePreflight(IPreflightBookData* iData) = 0;

	/** Create a new current/active preflight for this book. The existing data is released (and
		therefore typically deleted since these are nonpersistent bosses). The new interface
		is initialized with a pointer back to the book but no content data is configured.

		@return A refcounted preflight book data, which is also the new preflight book data
			(ie, this is the same interface that would then be returned by QueryActivePreflight).
	*/
	virtual IPreflightBookData* CreateActivePreflight() = 0;
};

