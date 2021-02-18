//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IVendorList.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IVendorList__
#define __IVendorList__

#include "IPMUnknown.h"


//----------------------------------------------------------------------------------------
// Interface IVendorList
//----------------------------------------------------------------------------------------
class IK2ServiceProvider;

/** Currently only used internaly in the linguistic project...
	@ingroup text_ling
*/
class IVendorList : public IPMUnknown
{
public:
	virtual	int32					GetVendorCount() const = 0;
	virtual	IK2ServiceProvider *	QueryNthVendor( int32 nNthVendor ) = 0;
	virtual	IK2ServiceProvider *	QueryVendor( ClassID nVendorBoss ) = 0;
	virtual	IK2ServiceProvider *	QueryVendor( const PMString& vendorName ) = 0;
	virtual	IK2ServiceProvider *	QueryDefaultVendor() = 0;
	virtual	bool16					SetDefaultVendor( ClassID nVendorBoss ) = 0;
	
	virtual	bool16					AddVendor( ClassID nVendorBoss  ) = 0;
	virtual	bool16					RemoveVendor(  ClassID nVendorBoss  ) = 0;
	virtual	void					ClearVendor() = 0;
	
	virtual	bool16					GetVendorPathList(ClassID nVendorBoss, K2Vector<PMString>& pathList) = 0;	/** get path list for vendor, kInvalidClass will use DEFAULT vendor */
	virtual	bool16					SetVendorPathList(ClassID nVendorBoss, const K2Vector<PMString>& pathList) = 0;	/** set path list for vendor, kInvalidClass will use DEFAULT vendor */
	virtual bool16					AppendPathToVendorList(ClassID nVendorBoss, const PMString& path) = 0;				/** add path to vendor, kInvalidClass will use DEFAULT vendor */
	virtual bool16					RemovePathFromVendorList(ClassID nVendorBoss, const PMString& path) = 0;				/** add path to vendor, kInvalidClass will use DEFAULT vendor */
};

/** 
	@ingroup text_ling
*/
class VendorData
{
public:
	VendorData();
	VendorData(const VendorData& vendorData);
	~VendorData();

	typedef object_type	data_type;	/* for K2Vector, change from base_type to object_type */

	ClassID				fClass;
	int32				fNthService;
	K2Vector<PMString>	fPathList;

	VendorData&		operator=(const VendorData& other);
	inline bool16 	operator==( const VendorData &rData ) const { return fClass == rData.fClass && fNthService == rData.fNthService; }
};


#endif
