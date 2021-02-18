//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IShuffleCmdData.h $
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
//  Data interface for shuffling pages.
//  
//========================================================================================

#pragma once
#ifndef __ISHUFFLECMDDATA__
#define __ISHUFFLECMDDATA__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 


/** Data interface for the kShufflePagesCmdBoss for shuffling pages in a document when pages are inserted,
	delete, duplicated, etc. Also can happen during section changes or page binding changes
	Typically this interface is used indirectly, use ILayoutUtils->MakeShuffleCmd(document) instead.
*/
class IShuffleCmdData : public IPMUnknown
{
public:		

	/**	Set the starting and ending spread for a page shuffle command (kShufflePagesCmdBoss). All spreads
		between and including these two spreads will be shuffled so that they layout out in a traditional
		manner. Document and page binding, page numbers, "keep together" spreads can all affect how many pages
		end up in a particular spread.
		@param startSpread the first spread to staring shuffling, often the first spread of the document, but
				for performance reasons make be some other spread if it is known.
		@param endSpread the last spread to end shuffling, typically the last spread of the document.
		@param pagesPerSpread value. Typically use -1 to that the publication setting for pages per spread will be used. 
		@see IPageSetupPrefs, GetPagesPerSpreadPref
	 */
	virtual void Set(const UIDRef& startSpread,
					const UIDRef& endSpread,
					int32 pagesPerSpread = -1) = 0;

	/**	Return the first spread to start shuffling
		@param none
		@return a UIDRef to the first spread to shuffle.
	 */
	virtual const UIDRef& GetStartSpread() const = 0;

	/**	Return the last spread to shuffle
		@param none
		@return a UIDRef to the last spread to shuffle.
	 */
	virtual const UIDRef& GetEndSpread() const = 0;

	/**	Return the value for pages per spread.
		@param none
		@return the int32 value for pages per spread 
	 */
	virtual const int32 GetPagesPerSpread() const = 0;
};



#endif // __ISHUFFLECMDDATA__
