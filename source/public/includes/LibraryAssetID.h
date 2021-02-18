//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LibraryAssetID.h $
//  
//  Owner: Tim Gogolin
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
//  Reviewed: 9/28/98
//  
//  Purpose:
//  This class is used to represent an "ID" of a Library Asset.
//  
//  NOTE: The LibraryAssetID is NOT similar to UID's or other shuksan ID's and
//  is used only with the Library.
//  
//========================================================================================

#ifndef __LibraryAssetID__
#define __LibraryAssetID__


#include "K2Vector.h"
#include "K2Vector.tpp"


class LibraryAssetID
{
public:
	typedef base_type data_type;
	// Creates a an invalid Asset ID.
	LibraryAssetID(); 
	
	// Create an Asset ID given a numerical equivalent value
	static LibraryAssetID CreateLibraryAssetID(int32 i);
	
	// Return a numerical equivalent value for an Asset ID
	int32 GetAssetIDNumericValue() const;

	bool16 IsValid() const;
	bool16 operator==(const LibraryAssetID& id) const;
	
private:
	LibraryAssetID(int32 i);
	int32 fID;	
};


typedef  K2Vector<LibraryAssetID> AssetIDList;



#endif