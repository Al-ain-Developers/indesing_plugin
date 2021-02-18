//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewSpreadCmdData.h $
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
//  Command data interface for new spreads.
//  
//========================================================================================

#pragma once
#ifndef __INewSpreadCmdData__
#define __INewSpreadCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMRect.h" 
#include "PMPageSize.h" 

class IDataBase;

/** Data interface for the kNewSpreadCmdBoss to insert spreads into a document.
*/
class INewSpreadCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INEWSPREADCMDDATA };

	/**	Set up the command data for the kNewSpreadCmdBoss command.
		@param UIDRef& doc set the document to create/insert the spreads in
		@param int32 count how many spreads to create
		@param int32 the position where to insert the spreads. 0 means start of document before
					any other spreads. Use ISpreadList::kAtTheEnd for end of document. Otherwise it's the
					index position the spread(s) will be after the command.
		@param PMRect& pageSize the page size for the newly inserted spreads, typically PMRect(0,0,0,0) to use document value
		@param int32 pagesPerSpread typically use -1 to that the publication setting for pages per spread will be used. 
		@param bool16 bIslandSpread set to kTrue if the newly created spreads should be "island" spreads (shuffling won't affect them)
		@see IPageSetupPrefs, GetPagesPerSpreadPref, IApplyMasterCmdData
	 */
	enum SpreadIsIslandChoice { kPagesMayShuffleThroughNewSpread, kPreventPagesFromShufflingThroughNewSpread};

	inline void SetNewSpreadCmdData(
					const UIDRef& doc,
					int32 numberOfSpreadsToAdd,
					int32 spreadIndexForInsertion /* the value ISpreadList::kAtTheEnd == -1 is allowed*/, 
					SpreadIsIslandChoice bIslandSpread /*= kPagesMayShuffleThroughNewSpread*/,
					int32 pagesPerNewSpread /* -1 means use default (i.e., 2 for a facing page document, 1 otherwise)*/,
					const K2Vector<PMRect>* pageBoundingBoxes /* nil for default size, otherwise a K2Vector with pagesPerNewSpread PMRects*/,
					const K2Vector<PMMatrix>* pageTransforms /*nil for default placement, otherwise a K2Vector with pagesPerNewSpread PMMatrices*/,
					const K2Vector<PMMatrix>* spreadTransforms /* nil for default placement, otherwise a K2Vector with numberOfSpreadsToAdd PMMatrices */)
	{
		SetNewSpreadCmdData_(
					doc, numberOfSpreadsToAdd, spreadIndexForInsertion,bIslandSpread /*= kPagesMayShuffleThroughNewSpread*/,
					pagesPerNewSpread, pageBoundingBoxes, pageTransforms, spreadTransforms, pageBoundingBoxes && pageTransforms ? kPMPageSizeDefine : kPMPageSizeDefault /*use pageBoundingBoxes and pageTransforms*/);
	}



	inline void SetNewSpreadCmdData( const UIDRef& doc,
					int32 numberOfSpreadsToAdd,
					int32 spreadIndexForInsertion /* the value ISpreadList::kAtTheEnd == -1 is allowed*/,
					SpreadIsIslandChoice bIslandSpread,
					int32 pagesPerNewSpread,
					const PMPageSize& pageSize /* = kPMPageSizeNeighbor*/ /* kPMPageSizeNeighbor means use the page size of location where spread is inserting. kPMPageSizeDefault means use document default page size. */,
					const PMMatrix* spreadTransform = nil )
	{
		if ( spreadTransform )
		{
			K2Vector<PMMatrix> spreadTransforms;
			spreadTransforms.push_back(*spreadTransform);
			SetNewSpreadCmdData_(doc, numberOfSpreadsToAdd, spreadIndexForInsertion, bIslandSpread, pagesPerNewSpread, nil, nil, &spreadTransforms, pageSize);
		}
		else
			SetNewSpreadCmdData_(doc, numberOfSpreadsToAdd, spreadIndexForInsertion, bIslandSpread, pagesPerNewSpread, nil, nil, nil, pageSize);
	}
	

	/**	Return the document to insert the spread(s).
		@param none
		@return const UIDRef& a reference to the document
	 */
	virtual const UIDRef& GetNewSpreadDocument() const = 0;

	/**	Return the number of spreads to create
		@param none
		@return const int32 the number of spreads to create
	 */
	virtual const int32 GetNewSpreadInsertCount() const = 0;

	/**	Return the data member for the index position of the inserted spreads. 0 means start of document before
		any other spreads. Use ISpreadList::kAtTheEnd for end of document.
		@param none
		@return const int32 the position value
		@see ISpreadList.h
	 */
	virtual const int32 GetNewSpreadInsertPosition() const = 0;

	/**	Return the data member for how many pages each inserted spread should have
		@param none
		@return const int32 the number of pages
	 */
	virtual const int32 GetPagesPerNewSpread() const = 0;

	/**	Return the data member for page size.
		@param none
		@return const PMRect& the page size
	 */
	virtual const K2Vector<PMRect>* GetNewSpreadPageBoundingBoxes() const = 0;
	virtual const K2Vector<PMMatrix>* GetNewSpreadPageTransforms() const = 0;
	virtual PMPageSize GetNewSpreadPageSize() const = 0;
	virtual const K2Vector<PMMatrix>* GetNewSpreadTransforms() const = 0;

	/**	Return the data member for if the newly created spreads should be "island" spreads. This is the same as
		"Keep Spread Together" or "Allow Pages to Shuffle" (actually the opposite meaning for "Allow Pages to Shuffle")
		@param none
		@return const bool16 kTrue if new spreads should be islands (shuffling won't affect them), or kTrue for standard spreads.
	 */
	virtual const SpreadIsIslandChoice GetNewSpreadIsIslandSpread() const = 0;

	// TEMPORARY api
	virtual void SetNewSpreadCmdData_(
					const UIDRef& doc,
					int32 numberOfSpreadsToAdd,
					int32 spreadIndexForInsertion /* the value ISpreadList::kAtTheEnd == -1 is allowed*/, 
					SpreadIsIslandChoice bIslandSpread /*= kPagesMayShuffleThroughNewSpread*/,
					int32 pagesPerNewSpread /* -1 means use default (i.e., 2 for a facing page document, 1 otherwise)*/,
					const K2Vector<PMRect>* pageBoundingBoxes /* nil for default size, otherwise a K2Vector with pagesPerNewSpread PMRects*/,
					const K2Vector<PMMatrix>* pageTransforms /*nil for default placement, otherwise a K2Vector with pagesPerNewSpread PMMatrices*/,
					const K2Vector<PMMatrix>* spreadTransforms /* nil for default placement, otherwise a K2Vector with numberOfSpreadsToAdd PMMatrices */,
					const PMPageSize& pageSize) = 0;

};




#endif // __INewSpreadCmdData__
