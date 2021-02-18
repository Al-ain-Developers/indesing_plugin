//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideSelectionUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IGuideSelectionUtils__
#define __IGuideSelectionUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class UIDList;


/** Utilities relating to selections over guides.
<pre>Utils<IGuideSelectionUtils>()->GetGuideSelectionType( ... ) ;</pre>
	@ingroup layout_select
	@ingroup layout_util
*/
class IGuideSelectionUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGUIDESELECTIONUTILS };

	/** Enum values of guide's selection type.
		kNone: no guide is selected.
		kVertical: only vertical guide is selected.
		kHorizontal: only horizontal guide is selected.
		kMixed: both horizontal and vertical guides are selected.
	*/
	enum GuideSelectionType
	{
		kNone,	
		kVertical,
		kHorizontal,
		kMixed
	};

	/**	Get guide's selection type for the given items. The result could be 
	    no guide selected, only vertical guide selected, only horizontal guide 
		selected or both horizontal and vertical guide selected.
		@param items IN the items for checking selection type.
		@return GuideSelectionType the selection type.
	*/
	virtual GuideSelectionType GetGuideSelectionType(const UIDList& items) const = 0;	

	/**	Count how many horizontal and vertical guides are selected for the given items.
		@param items IN the total items to check.
		@param nVertical OUT the number of selected vertical guides.
		@param nHorizontal OUt the number of selected horizontal guides.
	*/
	virtual void CountGuides(const UIDList& items, int32& nVertical, int32& nHorizontal) const = 0;
};


#endif	// __IGuideSelectionUtils__
