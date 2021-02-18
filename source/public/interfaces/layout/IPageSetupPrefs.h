//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageSetupPrefs.h $
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
//========================================================================================

#pragma once
#ifndef __IPageSetupPrefs__
#define __IPageSetupPrefs__

#include "IPMUnknown.h"
#include "PMPageSize.h"
#include "SpreadID.h"
#include "K2Pair.h" 

/** The document intent options
*/
typedef enum 
{
	kUnchangedIntent = -1,	/** Leave document intent unchanged (only for Set method)  */
	kPrintIntent = 0,		/** Document intent is for print output */
	kWebIntent,				/** Document intent is for web-based output */
	kMobileIntent,			/** Document intent for mobile (including AEM Mobile) */
} DocumentIntent;

class IPageSetupPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPAGEPREFERENCES } ;

	////
	//// Page Size Preferences
	////
	
	// Default page size
	virtual void SetPageSizePref(const PMPageSize& pageSize) = 0;
	virtual PMPageSize GetPageSizePref() const = 0;
	
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

	// Page orientation
	virtual void SetWideOrientationPref(bool16 bWide) = 0;
	virtual bool16 GetWideOrientationPref() const = 0;
	
	// Default number of pages
	virtual void SetNumPagesPref(int32 numPages) = 0;
	virtual int32 GetNumPagesPref() const = 0;
	
	// Default starting page number
	virtual void SetStartPageNumber(int32 startPageNumber) = 0;
	virtual int32 GetStartPageNumber() const = 0;

	/**	Set the document intent preference
		@param intent IN - the new setting
	 */
	virtual void SetIntent(DocumentIntent intent) = 0;

	/**	Get the document intent preference
		@param void 
		@return DocumentIntent enum 
	 */
	virtual DocumentIntent GetIntent() const = 0;

	// Pages per spread
	virtual void SetPagesPerSpreadPref(int32 numPagesPerSpread) = 0;
	virtual int32 GetPagesPerSpreadPref() const = 0;
	
	// Is pages per spread fixed, or can more be allowed
	virtual void SetAlwaysUsePagesPerSpreadPref(bool16 bAlways) = 0;
	virtual bool16 GetAlwaysUsePagesPerSpreadPref() const = 0;
	
	// Right to left page binding
	virtual void SetPageBindingPref(int32 pageBinding) = 0;
	virtual int32 GetPageBindingPref() const = 0;

	// Restart page numbering(Set this option only if the publication
	// will be part of a book and won't be numbered sequentially.
	virtual void SetRestartPageNum(bool16 bRestart) = 0;
	virtual bool16 GetRestartPageNum() const = 0;
	
	/**    Sets the bleed offsets.
	    @param offsets The bleed offsets, stored in a rect. Inside offset stored in left, outside in right.
	 */
	virtual void SetBleedBoxPref(PMRect offsets) = 0;

	/**    Gets the bleed offsets.
	    @param offsets The bleed offsets, stored in a rect. Inside offset stored in left, outside in right.
	 */
	virtual PMRect GetBleedBoxPref() const = 0;
	
	/**    Tells that all bleed values set from one value (top).
	    @param bUniform Whether to force all bleed values to be uniform, using Top value.
	 */
	virtual void SetUseUniformBleed(bool16 bUniform) = 0;

	/**    Tells whether all bleed values are set from one value (top).
	 */
	virtual bool16 GetUseUniformBleed() const = 0;
	

	/**    Sets the slug box offsets
	    @param offsets The slug offsets, stored in a rect. Inside offset stored in left, outside in right.
	 */
	virtual void SetSlugBoxPref(PMRect offsets) = 0;

	/**    Gets the slug box offsets
	    @param offsets The slug offsets, stored in a rect. Inside offset stored in left, outside in right.
	 */
	virtual PMRect GetSlugBoxPref() const = 0;
	
	/**    Tells that all slug values set from one value (top).
	    @param bUniform Whether to force all slug values to be uniform, using Top value.
	 */
	virtual void SetUseUniformSlug(bool16 bUniform) = 0;

	/**    Tells whether all slug values are set from one value (top).
	 */
	virtual bool16 GetUseUniformSlug() const = 0;
	
};

#endif
