//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideUIUtils.h $
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
#ifndef __IGuideUIUtils__
#define __IGuideUIUtils__

#include "LayoutUIID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "PMPoint.h"
#include "UIDRef.h"

class ICommand;
class IGuideData;
class IColorData;
class IShape;
class ColorizedIcon;


/** Utilites for answering questions about ruler guides when there is an open document window.
	Please use the IGuideUIUtils via kUtilsBoss (see Utils.h).
    <pre>Utils<IGuideUIUtils>()->SelectAllGuides( ... ) ;</pre>

	@ingroup layout_util
*/
class IGuideUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGUIDEUIUTILS };

	/**	Select all the visible, unlocked guides on the current spread.
	 */
	virtual void SelectAllGuides() = 0;

	/**	Helper function to show guides on the page if they are hidden. Guides may be hidden
		overall (IGuidePrefs, GetGuidesShown) or on the active layer (IDocumentLayer, IsGuideVisible).
		Useful for a tracker that creates guides.
	 */
	virtual  void ShowGuidesIfHidden() = 0;

	/**	Determines if any guides are currently hidden, either overall with IGuidePrefs (GetGuidesShown), or
		on the active layer (IDocumentLayer, IsGuideVisible).
		@return returns kTrue if guide is currently hidden, kFalse otherwise.
	 */
	virtual  bool16 IsGuideHidden() = 0;

	/** Given a guide shape, calculate the location of the given adornment rect. Used for guide type adornments.
		@param IShape*, the guide item's shape interface
		@param PMMatrix, the inner to window matrix for the item.
		@param ColorizedIcon, the png art for the adornment.
		@return PMRect, the window coordinate rectangle representing the screen location of the guide adornment. kEmptyRect if none.
	*/
	virtual PMRect CalculateGuideAdornmentRect(IShape* guideShape, const PMMatrix& innerToWindowMatrix, ColorizedIcon* pngArt) = 0;

	/**	Return the active guide for the guide type adornment the user clicked on. 
		@return a UIDRef for the guide the user clicked on its guide type adornment.
	*/
	virtual UIDRef GetActiveGuideAdornment() const = 0;

	/**	Set the active guide for the guide type adornment the user clicked on. 
		Generally for INTERNAL use only.
		@param a UIDRef for the guide the user clicked on its guide type adornment.
	*/
	virtual void SetActiveGuideAdornment(const UIDRef& guideRef) = 0;

};


#endif	// __IGuideUIUtils__
