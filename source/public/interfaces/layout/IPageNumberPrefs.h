//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageNumberPrefs.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPageNumberPrefs__
#define __IPageNumberPrefs__

#include "IPMUnknown.h"
#include "SectionID.h"

/** Stores session preferences relating how UI widgets display page numbers. This is a UI-only setting
	that doesn't affect how page number characters in text stories are computed/displayed.
	@see kWorkspaceBoss
    @see kSetPageNumberPrefsCmdCmdBoss
	@see IPageList.h
	@see ISection.h
	@see ISectionList.h
	@see Widgets.fh, PageNumEditBoxWidget, PageNumEditBoxWidget, and PageNumPlusMasterEditBoxWidget
*/
class IPageNumberPrefs : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IPAGENUMBERPREFS};

	/**	Set value for ordinal numbering (kTrue) or standard/section numbering (kFalse). When ordinal
		numbering is on, page number and page range widgets will display 1 for first page of document,
		2 for second page, etc. When standard numbering is used, the first page number will use its
		page number as determined by what section it is in.
		@param bool16 on, kTrue for ordinal, kFalse for section numbering (the default).
	 */
	virtual void SetOrdinalNumbering(bool16 on) = 0;

	/**	Return the value used for page numbering widgets.
		@param none
		@return kTrue for oridinal numbering, kFalse for standard/section numbering.
	 */
	virtual bool16	GetOrdinalNumbering() const= 0;
};

#endif
