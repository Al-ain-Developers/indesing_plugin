//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICatalogData.h $
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
#ifndef __ICatalogData__
#define __ICatalogData__

#include "IPMUnknown.h"

#include "ICatalog.h"

/** Provides access to the catalog used by a Library boss.
	@see ICatalog
*/
class ICatalogData : public IPMUnknown
{
public:
	enum	{ kDefaultIID = IID_ICATALOGDATA };
	/** Sets the Catalog this Library Boss is to use.
		@param pCatalog IN ICatalog interface pointer for this library boss to use.
	*/
	virtual void SetCatalog(ICatalog* pCatalog) = 0;
		
	/** Gets the Catalog this Library Boss is using.
		@return ICatalog interface pointer of the Library Boss's catalog.
	*/
	virtual ICatalog* GetCatalog() const = 0;

};


#endif