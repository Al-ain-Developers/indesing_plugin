//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageSizes.h $
//  
//  Owner: Tommy Donovan
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
//  IPageSizes is an interface that is part of allows for
//  installable page sizes. The installed page sizes will appear
//  in the Page Setup dialog popup list. Any number of page sizes
//  may be implemented in this interface.
//  
//========================================================================================

#pragma once
#ifndef __IPAGESIZES__
#define __IPAGESIZES__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "PMPageSize.h"
class PMString;

class IPageSizes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGESIZES };

	enum PageSizeIntent {
		kAll = -1,
		kPrintOnly = 1,
		kWebOnly = 2,
		kMobileOnly = 4,
		kDigital = kWebOnly + kMobileOnly
	};
	
	/**	Return the number of page sizes implemented in this class
	 */
	virtual int32 GetPageSizeCount() = 0;

	/**	Return the name of the page size--to be used in menus
	 */
	virtual void GetNthPageSizeName(int32 pageSizeIndex, PMString* pPageSizeName) = 0;

	/**	Return the page size
	 */
	virtual PMPageSize GetNthPageSize(int32 pageSizeIndex) = 0;
	
	/** Return the intent of the nth page size -- helps with page size filtering based on document intent
		@param pageSizeIndex [IN] The zero-based index
		@param intent [OUT] On return, will contain the intent for the targeted page size
	 */
	virtual void GetNthPageSizeIntent(int32 pageSizeIndex, PageSizeIntent* intent) = 0;
};


#endif // __IPAGESIZES__

