//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPropertyMgr.h $
//  
//  Owner: 
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPropertyMgr__
#define __IPropertyMgr__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "IProperty.h"

/** Class to manage descriptive properties (name, description, timestamp, etc.).  Used by the
	library catalog to keep track of asset properties.
	@see IProperty
	@see IPropertyTable
*/
class IPropertyMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPROPERTYMGR };
	
	// ----- Add/Remove Properties -----
	/**	Add a property.
		@param name IN the name of the property (e.g., "Name," "Description," etc.)
		@param type IN the ClassID of the property type (e.g., kStringPropTabBoss)
		@return the UID of the new property
	*/
	virtual UID				NewProperty( const PMString& name, ClassID type ) = 0;

	/**	Delete a property.
		@param propertyUID IN the property to delete
		@return kTrue for success; kFalse for failure
	*/
	virtual bool16			DeleteProperty( UID propertyUID ) = 0;

	// ----- Iterating Properties -----
	/** Get the number of properties stored by the property manager.
		@return the number of properties.
	*/
	virtual int32			GetPropertyCount() const = 0;

	/**	Get a property.
		@param n IN the zero-based index of the property to get
		@return the UID of the property
	*/
	virtual UID				GetNthProperty(int32 n) const = 0;
															
	// ----- Find Properties -----
	/**	Find a property by its name
		@param name IN the name to search for
		@return the UID of the property found (or kInvalidUID for not found)
	*/
	virtual UID				FindProperty( const PMString& name ) const = 0;
															
};

#endif
