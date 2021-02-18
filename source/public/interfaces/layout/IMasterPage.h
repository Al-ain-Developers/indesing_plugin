//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterPage.h $
//  
//  Owner: Brendan O'Shea
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
//  An interface for a page which defines the master associated with that page. 
//  
//========================================================================================

#pragma once
#ifndef __IMASTERPAGE__
#define __IMASTERPAGE__

#include "IPMUnknown.h"
#include "MasterPageID.h"


// AdobePatentID="B1114" (sheridan 30 Nov 2009 - Master page overlay (InDesign))


/**
	IMasterPage is an interface on a page boss (kPageBoss) which holds the UID of the
	IMasterSpread that is used for the particular page.
	@see kPageBoss
	@ingroup layout_spread
 */
class IMasterPage : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMASTERPAGE };
	enum { kPositionDependant = kMaxUInt16 };

	/**
		GetMasterSpreadUID - get the UID of the spread that contains the master page assigned to this page.
		@return	UID - the UID of this page's master spread.
	*/
	virtual UID GetMasterSpreadUID() const = 0;

	/**
		SetMasterPageData - set the master spread and page index within that master spread associated with this page. 	
		@param	mpUID - the UID of the SPREAD that contains the master assigned to the page. 
		@param	mpIndex - historical, ignored
	*/
	virtual void SetMasterPageData( UID masterspreadUID, uint16 mpIndex = IMasterPage::kPositionDependant) = 0;

	/**
		GetMasterSpreadPageIndex - get the index of the page on the master spread that this page has assigned to it.
		@param	alternateMasterSpreadUID - if not kInvalidUID, GetMasterSpreadPageIndex returns the page index within
				some other master spread if that master were applied to this page. 
		@return	uint16
	*/
	virtual uint16 GetMasterSpreadPageIndex( UID alternateMasterSpreadUID = kInvalidUID) const = 0;

	/**
		IsValid - since anytime a page is queried for an IID_IMASTERPAGE interface, it will get *some*
			valid object back, this flag says if that is a 'valid' master (i.e. if it has been
			previously explicitly assigned to the page, instead of just created via QueryInterface
		@return	bool16
	*/
	virtual bool16 IsValid() const = 0;
	
	virtual void SetMasterPageTransform( const PMMatrix& m) = 0;
	virtual bool16 GetMasterPageTransform( PMMatrix* mp) const = 0; //return whether the matrix is identity
	
};

#endif
