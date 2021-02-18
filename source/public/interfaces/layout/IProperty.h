//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IProperty.h $
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
#ifndef __IProperty__
#define __IProperty__

#include "IPMUnknown.h"

//Interfaces

//Utils & IDs
#include "LibraryProviderID.h"
#include "PMString.h"

class PMDate
{
	int32 year:23;
	int32 month:4;
	int32 day:5;
};

/** A generic interface for keeping a piece of descriptive information.
	A property is like a type; for example, a name property, or a description property.  A property
	also has a storage class, such as string.  Properties
	are managed for a catalog by the IID_IPROPERTYMGR interface.  Instances of properties are kept
	in IID_IPROPERTYTABLE, where each table stores the properties of a given storage class.  The
	IID_IPROPERTY interface and IID_IPROPERTYTABLE interface are aggregated on the same boss, so that
	the IID_IPROPERTY tells the name of the property, and the IID_IPROPERTYTABLE holds instances of
	that property.  For example, there exists a boss in the library catalog for the name string property,
	and another for the description string property.  The IID_IPROPERTYMGR keeps track of each of these
	bosses.  Used for library asset properties.
	@see IPropertyMgr
	@see IPropertyTable
*/
class IProperty : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPROPERTY };
	
	// ----- Name -----
	/** Set the name of a property.
		@param name IN the name to give the property
	*/
	virtual void				SetName( const PMString& name ) = 0;

	/** Get the name of the property.
		@return the name of the property.
	*/
	virtual PMString			GetName(  )  const = 0;

	// ----- Is this a property that can be searched for? -----
	/** Get whether the property can be searched for.  An example of a non-searchable property might be a thumbnail image.
		@return kTrue for a searchable property; kFalse for a non-searchable property
	*/
	virtual bool16				CanSearchFor() const = 0;

	/** Set whether the property can be searched for.
		@param canSearchFor IN kTrue for searchable; kFalse otherwise
	*/
	virtual void				SetCanSearchFor(bool16 canSearchFor ) = 0;										
};

#endif
