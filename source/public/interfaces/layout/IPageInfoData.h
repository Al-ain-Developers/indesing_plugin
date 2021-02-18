//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageInfoData.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IPAGEINFODATA__
#define __IPAGEINFODATA__

#include "IPMUnknown.h"
#include "K2Vector.h"

/** This interface stores the page info for printing a book (kBookBoss). 

	@ingroup layout_book
	@see kBookContentBoss
	@see kBookBoss
*/
class IPageInfoData : public IPMUnknown
{
	public:

		virtual K2Vector<int32>& GetPageRange() = 0;

		virtual void SetPageRange(K2Vector<int32>& pageInfo) = 0;

		// If IncludeAllPage is set to kTrue, it means that we need to print 
		// the whole document.
		virtual bool16 IsIncludeAllPage() = 0;

		virtual void SetIncludeAllPage(bool16 includeAll) = 0;
};


#endif //__IPAGEINFODATA__