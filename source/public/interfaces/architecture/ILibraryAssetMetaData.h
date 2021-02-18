//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetMetaData.h $
//  
//  Owner: Mark VerMurlen
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  This interface is a secondary interface to the LibraryAsset Boss.  This interface
//  controls reading and writing of the "Meta" data of the asset.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetMetaData__
#define __ILibraryAssetMetaData__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "GlobalTime.h"
#include "PMPoint.h"

static const GlobalTime kNULLTIME = GlobalTime(uint64(0));

/** This secondary interface on the LibraryAsset boss controls reading and writing
	of the "meta" data of the asset (name, description, etc.). Note that this is NOT
	XMP data, but instead a format used internally by the Library palette.
*/
class ILibraryAssetMetaData : public IPMUnknown
{
public:

	// The popup menus that let the user change the "type" of an asset
	// rely on this ordering. If you add enums or change the ordering,
	// you must change the popup menu resource to match (or else use a 
	// more complicated association between menu items and enum vals) (tjg)
	/** What type an asset is.  Determined by a heuristic algorithm, and ca
		be reassigned by the user.  Do not change the order of the items
		in this enum, or logic that handles the dropdown menu will break.
	*/
	typedef enum {
		/** Asset is an image
		*/
		kImageType = 0,
		/** Asset is an EPS
		*/
		kEPSType,
		/** Asset is a PDF
		*/
		kPDFType,
		/** Asset is a non-placed graphic pageitem (line, box, oval...)
		*/
		kGeometryType,
		/** Asset is an entire page of items
		*/
		kPageType,
		/** Asset is a textframe
		*/
		kTextType,
		/** Asset is an item from the structure panel
		*/
		kStructureType,
		/** Asset is a placed InDesign file
		*/
		kInDesignFileType
	} UserType;
	
	/** Set the asset's name.
		@param name IN string containing a new name for the asset
	*/
	virtual void SetName(const PMString &name) = 0;
	
	/** Get the asset's name.
		@return the name given the asset
	*/
	virtual PMString GetName() const = 0;
	
	/** Set the asset's User Type 
		@param userType IN User Type to assign to the asset
	*/
	virtual void SetUserType(const UserType userType) = 0;
	
	/** Get the asset's User Type.
		NOTE: User Type is just for user classification.  It may or may not be accurate.
		@return the UserType given the asset
	*/
	virtual UserType GetUserType() const = 0;
	
	/** Sets the asset's description.
		@param description IN string containing a new description for the asset
	*/
	virtual void SetDescription(const PMString &description) = 0;
	
	/** Get the asset's description.
		@return the description given the asset
	*/
	virtual PMString GetDescription() const = 0;
	
	/** Get the creation time (and date) of the asset
		@return the timestamp for the asset's creation
	*/
	virtual GlobalTime GetCreationTime() const = 0;
	
	// Sets the creation time (and date) of the asset.Added for Converter support
	// Clients are requested to make doubly sure if they want to use this method
	// as creation date is set only once
	/** Set the creation time of the asset.  This method is intended for use by 
		code converters; clients in general should not re-set an existing creation time for an 
		asset.
		@param t IN the time to assign to the asset's creation time
	*/
	virtual void SetCreationTime(GlobalTime t) = 0;
	
	/** Get the asset's position on page when it was created. DEPRECATED
		@return the position associated with the asset
	*/
	virtual PMPoint	GetPosition() const = 0;

	/** Assign the asset's position on page when it was created.  DEPRECATED
		@param pt IN the position (upper left) of the item
	*/
	virtual void SetPosition(PMPoint& pt) = 0;

	/** Set a generic property for the asset.  The property must have previously been created.
		@param propName IN the name of the property
		@param propValue IN UIDRef for the property value
	*/
	virtual void	SetGenericProperty(PMString& propName,UIDRef& propValue) = 0;

	/** Get a generic property.
		@param propName IN the name of the property
		@return a UIDRef ro the property value
	*/
	virtual UIDRef	GetGenericProperty(PMString& propName) = 0;

	
	//-------------- For Internal Use Only -------------------------
	
	/** Initializes the creation time (and date) of the asset to the current date and time. * For Internal Use Only *
	*/
	virtual void InitializeCreationTime() = 0;
		
};


#endif
