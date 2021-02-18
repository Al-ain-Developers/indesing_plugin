//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideUtils.h $
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
#ifndef __IGuideUtils__
#define __IGuideUtils__

#include "GuideID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "PMPoint.h"
#include "UIDRef.h"

class ICommand;
class IGuideData;
class IColorData;

/** Guide-related utilities on model side.
	@see kUtilsBoss
	@see IGuideUIUtils for answers about ruler-guide related questions.
*/
class IGuideUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGUIDEUTILS };

	/**	With the given guide data and a point, get the owner of the guide which it will reside on. 
	    The owner is either a page or spread/pasteboard. If command/ctrl key is pressed, 
		we will force the guide to be a pasteboard guide by setting the spread as its parent.
		@param guideData IN the given guide data interface.
		@param locationPoint IN the given point usually it is the mouse location in spread coordinates.
		@return UID the UID of a page or a spread, by default it is kInvalidUID.
	*/
	virtual UID GetNewOwnerUID(IGuideData *guideData, const PMPoint &locationPoint) = 0;

	/** Given a page, return a sorted list of slice guides
		@param pageRef [IN] UIDRef of the page
		@param horizontalGuides [OUT] On return, will contain the horizontal page and spread guides sorted top to bottom
		@param verticalGuides [OUT] On return, will contain the vertical page and spread guides sorted left to right
	*/
	virtual void GetSortedSliceGuides(const UIDRef& pageRef, UIDList& horizontalGuides, UIDList& verticalGuides) const = 0;
	virtual void GetSortedSliceGuides( const UIDRef& pageRef, const PMRect& pageBoundsSpreadCoordinates, UIDList& horizontalGuides, UIDList& verticalGuides) const = 0;

	typedef enum
	{
		kMaskNothing		= 0x00000000,
		kMaskHiddenLayers	= 0x00000001,
		kMaskLockedLayers	= 0x00000002,
		kMaskHiddenAndLockedLayers = kMaskHiddenLayers + kMaskLockedLayers
	} LayerMaskFlags;

	virtual UIDList GetGuidesOnSpread(const UIDRef& spreadRef, const LayerMaskFlags flags) const = 0;

	/**	Given a  list of page items, strip the non guides out. 
		@param list IN/OUT the UIDList for the list to process.
	*/
	virtual void FilterNonGuides(UIDList& list) = 0;

};

#endif	// __IGuideUtils__
