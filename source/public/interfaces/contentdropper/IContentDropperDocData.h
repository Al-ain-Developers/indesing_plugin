//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/contentdropper/IContentDropperDocData.h $ 
//   
//  Owner: vaggarwa 
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
#ifndef __IContentDropperDocData__ 
#define __IContentDropperDocData__ 

// ----- Includes -----
#include "CCollection.h"
#include "UIDList.h"

// ----- ID.h files -----
#include "ContentDropperID.h"


//======================================================================================== 
// class IContentDropperDocData 
//======================================================================================== 

class IContentDropperDocData : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_ICONTENTDROPPERDOCDATA }; 


	//Checks if the UID is already grabbed.
	virtual bool16	Find(UID uid) const = 0;
	
	//Removes collection with capture order passed here.
	virtual void Remove(int32 order)  = 0;
	
	virtual void RemoveChildColl(int32 parentOrder, int32 childIndex)  = 0;

	//Removes specific UID from the captures items.Just modifies the data structure at document level.
	virtual bool16 Remove(UID uid)  = 0;

	virtual void	GrabItemCollection( CCollection* collection) = 0;

	virtual CCollection*	GetCollectionForOrder(int32 order) const = 0;
	
	//Returns the Capture Order for Collection at the nth index. -1 if no collection at nth.
	virtual int32	GetCaptureOrderForNth(int32 nth) const = 0;

	// returns number of top level collections in the document. Does not count collections that are nested 
	virtual int32	GetNumberOfCollections() const = 0;

	virtual void	CleanUp() = 0;

	virtual const CCollection* CollectionAtIndex(int32 at) const = 0;
};




#endif
