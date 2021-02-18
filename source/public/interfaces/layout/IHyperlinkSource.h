//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkSource.h $
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
//========================================================================================

#pragma once
#ifndef __IHyperlinkSource__
#define __IHyperlinkSource__

// Includes:
#include "HyperlinkID.h"

// Classes:
class ISpread;
class IHierarchy;
class IPMStream;
class IDocument;

/**
	@ingroup layout_hyper
	@see kHyperlinkTextSourceBoss 
	@see kHyperlinkTextSourceBoss 
*/
class IHyperlinkSource : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKSOURCE };


	/**	Show this source in the layout window
		@param none
	 */
	virtual void	GoToHyperlinkSource() const = 0;

		// Get & Set the name of the hyperlink source

	/**	Get the name of this source
		@param *pName - Will be filled with the name of this source
	 */
	virtual void	GetName(PMString *pName) const = 0;
	
		// Get & Set the base name of this Hyperlink source

	/**	Set the name of this source
		@param newName - The new name of the source
	 */
	virtual void	SetName(const PMString& newName) = 0;


	/**	Set whether or not this source is hidden in the UI (Panel)
		@param bIsHidden - kTrue == Hidden
	 */
	virtual void	SetHidden(bool16 bIsHidden) = 0;

	/**	Get whether or not this source is hidden in the UI (Panel)
		@param none
		@return bool16 - kTrue == Hidden
	 */
	virtual bool16	IsHidden() const = 0;
	

	/**	Set the UID of the hyperlink that "owns" this source
		@param owningHyperlink - UID of the hyperlink
	 */
	virtual void	SetOwningHyperlink(UID owningHyperlink) = 0;

	/**	Get the UID of the hyperlink that "owns" this source
		@param none
		@return UID - UID of the hyperlink
	 */
	virtual UID		GetOwningHyperlink() const = 0;


	/**	Set the UID of the bookmark that is associated with this source (Used by TOC)
		@param bookmarkUID - UID of the bookmark (kInvalid is possible)
	 */
	virtual void	SetBookmarkUID(UID bookmarkUID) = 0;

	/**	Get the UID of the bookmark that is associated with this source
		@param none
		@return UID - UID of the bookmark (kInvalid is possible)
	 */
	virtual UID		GetBookmarkUID() const = 0;
};

#endif //__IHyperlinkSource__
