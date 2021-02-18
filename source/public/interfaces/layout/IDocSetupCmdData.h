//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDocSetupCmdData.h $
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
//  Data interface for document setup commands.
//  includes : 	page size
//  number of pages
//  number of pages per spread
//  
//========================================================================================

#pragma once
#ifndef __IDocSetupCmdData__
#define __IDocSetupCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMRect.h"
#include "PMReal.h"
#include "IPageSetupPrefs.h"
#include "K2Pair.h"

class IDataBase;

/**
   This interface is used to cache data for document set up related commands including 
   kSetPageSizeCmdBoss, kSetPageSetupPrefsCmdBoss and kSetPageBindingCmdBoss.
*/
class IDocSetupCmdData : public IPMUnknown
{
public:
	/**
		Set the document attributes.

		Note: new bleed and slug parameters are NOT in Set function. Please see below.

		@param doc refers to which document to affect. 
		@param newPageSize refers to dimensions of the new page size.
		@param newNPages refers to how many pages should exist.
		@param newNPagesPerSpread refers to how many pages should be in each spread.
		@param bWide refers to the orientation of page in document.
		@param pageBinding refers to if pages read from right to left or left to right or something else. 
		       Currently page binding could be kDefaultBinding(-1), kLeftToRightBinding(0), kRightToLeftBinding(1).
		@param bRestartPageNum refers to if page number needs to be restart or not.
		@return void.
	*/
	virtual void SetDocSetupCmdData(	const	UIDRef&	doc, 			/* which document to affect */
						const	PMPageSize&	newPageSize, 	/* dimensions of the new page size */
								int16	newNPages, 		/* how many pages should exist */
								int16	newNPagesPerSpread,	/* how many pages should be in each spread */
								bool16	bWide,			/* is page tall or wide?	*/
								int32	pageBinding,	/* do pages read from right to left? */
								bool16  bRestartPageNum = kFalse) = 0; /* restart page number or not */
								/* Note: new bleed and slug parms NOT in Set rtn.  See below */

	/**
		Set the document which is affected. 

		@param doc refers to which document to affect. 
		@return void.
	*/
	virtual void SetDocument(const UIDRef& doc) = 0;

	/**
		Set the dimensions of the new page size. 

		@param newPageSize refers to the new page size. 
		@return void.
	*/
	virtual void SetDocumentPageSize(const PMPageSize& newPageSize) = 0;

	/**
		Set the number of pages the document will have. 

		@param newNPages refers to number of pages. 
		@return void.
	*/
	virtual void SetNPages(const int16 newNPages) = 0;

	/**
		Set the number of pages each spread will have.

		@param newNPagesPerSpread refers to the number of pages per spread. 
		@return void.
	*/
	virtual void SetNPagesPerSpread(const int16 newNPagesPerSpread) = 0;

	/**
		Set the orientation of the document.

		@param bWide refers to if the document is wide or tall(kTrue if it is wide, kFalse if it is tall). 
		@return void.
	*/
	virtual void SetPageOrientationIsWide(const bool16 bWide) = 0;

	/**
		Set the binding of the pages in the document. Currently page binding could be kDefaultBinding(-1), kLeftToRightBinding(0), kRightToLeftBinding(1).

		@param pageBinding refers to binding setting. 
		@return void.
	*/
	virtual void SetPageBinding(const int32 pageBinding) = 0;

	/**
		Set the flag determining if page number needs to be restart or not. 

		@param bRestartPageNum a flag determining if page number needs to be restart or not. 
		@return void.
	*/
	virtual void SetRestartPageNum(const bool16 bRestartPageNum) = 0;

	/**    
		Set the bleed offsets.

	    @param offsets the bleed offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
		@return void.
	 */
	virtual void SetBleedBox(const PMRect& offsets) = 0;

	/**    
		Tell whether a change to any bleed value change them all to that value.

	    @param bUniform is a flag determining a change to any bleed value change them all to that value.
		@return void.
	 */
	virtual void SetUseUniformBleed(bool16 bUniform) = 0;

	/**    
		Set the slug box offsets.

	    @param offsets refers to the slug offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
		@return void.
	 */
	virtual void SetSlugBox(const PMRect& offsets) = 0;

	/**    
		Tell whether a change to any slug value changes them all to that value.

	    @param bUniform is a flag determining a change to any slug value changes them all to that value.
		@return void.
	 */
	virtual void SetUseUniformSlug(bool16 bUniform) = 0;

	/**    
		Set the starting page number for the document.

	    @param startPageNumber the number for the first page of the document. Defaults to -1 if not set by client, which means leave unchanged.
		@return void.
	 */
	virtual void SetStartPageNumber(int32 startPageNumber) = 0;

	/**	Set the document intent preference
		@param intent IN - the new setting
		@see IPageSetupPrefs.h
	 */
	virtual void SetIntent(DocumentIntent intent) = 0;

	/**
		Get the document which is affected.
			
		@return const UIDRef the UIDRef of the document.
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/**
		Get the dimensions of the new page size.
			
		@return const PMRect refers to the new page dimension.
	*/
	virtual const PMPageSize& GetDocumentPageSize() const = 0;

	/**
		Get the number of pages the document will have. 
			
		@return const int16 the number of pages for the document.
	*/
	virtual const int16 GetNPages() const = 0;

	/**
		Get the number of pages each spread will have.
			
		@return const int16 the number of pages for each spread.
	*/
	virtual const int16 GetNPagesPerSpread() const = 0;

	/**
		Get the orientation of the document.
		
		@return const bool16 kTrue if the orientation is wide, kFalse if it is not.
	*/
	virtual const bool16 GetPageOrientationIsWide() const = 0;

	/**
		Get the page binding setting. 
			
		@return const int32 indicating kDefaultBinding(-1), kLeftToRightBinding(0), kRightToLeftBinding(1).
	*/
	virtual const int32 GetPageBinding() const = 0;

	/**
		Get the flag if page number needs to be restart or not.
			
		@return const bool16 kTrue if page number needs to be restart, kFalse if it is not.
	*/
	virtual const bool16 GetRestartPageNum() const = 0;

	/**    
		Get the bleed offsets.

	    @return const PMRect the bleed offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
	 */
	virtual const PMRect& GetBleedBox() const = 0;

	/** 
		Check whether a change to any bleed value changes them all to that value.

		@return const bool16 kTrue indicating use uniform bleed, kFalse indicating not use uniform bleed. 
	 */
	virtual const bool16 GetUseUniformBleed() const = 0;
	
	/**    
		Get the slug box offsets.

	    @return const PMRect the slug offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
	 */
	virtual const PMRect& GetSlugBox() const = 0;

	/**    
		Check whether a change to any slug value changes them all to that value.

		@return const bool16 kTrue indicating use uniform slug, kFalse indicating not use uniform slug. 
	 */
	virtual const bool16 GetUseUniformSlug() const = 0;
	
	/**    
		Get the starting page number for the document.

		@return const int32 the starting page number for the first page of the document.
	 */
	virtual const int32 GetStartPageNumber() const = 0;

	/**	Get the document intent preference
		@param void 
		@return DocumentIntent 
		@see IPageSetupPrefs.h, DocumentIntent enum
	 */
	virtual const DocumentIntent GetIntent() const = 0;

	/**
		Set the default scale to apply to new spreads. We typically apply scaling to spreads based on the ppi of the pages that will be in the spread.
		@param scale [IN] The x and y scale to apply to the spread.
	*/
	virtual void SetSpreadScale(const K2Pair<PMReal, PMReal>& scale) = 0;

	/** Return the width scale to apply to the spread.
	*/
	virtual PMReal GetSpreadWidthScale() const = 0;

	/** Return the height scale to apply to the spread.
	*/
	virtual PMReal GetSpreadHeightScale() const = 0;

};




#endif // __IDocSetupCmdData__
