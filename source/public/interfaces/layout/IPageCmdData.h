//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageCmdData.h $
//  
//  Owner: robin briggs
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
//  Data interface for new/delete pages.
//  
//========================================================================================

#pragma once
#ifndef __IPageCmdData__
#define __IPageCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMRect.h" 
#include "PMPageSize.h" 
#include "PMMatrix.h" 
//#include "IPageSetupPrefs.h"
#include "ILayoutUtils.h"	// for kDefaultBinding

/** Command data interface associated with commands to create pages (kPageBoss). 
	@see kNewPageCmdBoss 
	@see kNewPageSetSpreadCmdBoss 
	@see kPageBoss
	@ingroup layout_spread
*/
class IPageCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGECMDDATA };
	
	inline void SetNewPageCmdData( const UIDRef& spreadToAddTo, int32 numberOfPagesToInsert, int32 insertPosition /*zero-based*/, const PMPageSize& pageSize = kPMPageSizeNeighbor)	/* kPMPageSizeNeighbor means use the page size of location where spread is inserting. kPMPageSizeDefault means use document default page size. */
	{
		SetNewPageCmdData_( spreadToAddTo, numberOfPagesToInsert, insertPosition, nil, nil, pageSize);

	}
	inline void SetNewPageCmdData(const UIDRef& spreadToAddTo, int32 numberOfPagesToInsert, int32 insertPosition /*zero-based*/,
					const K2Vector< PMRect>* pageBoundingBoxes, const K2Vector<PMMatrix>* pageTransforms)
	{
		SetNewPageCmdData_(spreadToAddTo, numberOfPagesToInsert, insertPosition, pageBoundingBoxes, pageTransforms, kPMPageSizeDefine /*use pageBoundingBoxes and pageTransforms*/);
	}



	virtual UIDRef GetNewPageSpread() const = 0;
	virtual int32 GetNewPageInsertCount() const = 0;
	virtual int32 GetNewPageInsertPosition() const = 0;
	virtual const K2Vector<PMRect>* GetNewPageBoundingBoxes() const = 0;
	virtual const K2Vector<PMMatrix>* GetNewPageTransforms() const = 0;
	virtual PMPageSize GetNewPageSize() const = 0;

	// TEMPORARY api
	virtual void SetNewPageCmdData_(const UIDRef& spreadToAddTo, int32 numberOfPagesToInsert, int32 insertPosition /*zero-based*/,
					const K2Vector< PMRect>* pageBoundingBoxes /* nil for default size*/, const K2Vector<PMMatrix>* pageTransforms /*nil for default placement*/, const PMPageSize& pageSize) = 0;
};



#endif // __IPageCmdData__
