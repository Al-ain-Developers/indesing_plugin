//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IGuidesFacade.h $
//  
//  Owner: Dave Stephens
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
#ifndef __IGuidesFacade__
#define __IGuidesFacade__

#include "IPMUnknown.h"
#include "SpreadUIID.h"

/**	
	IGuidesFacade is an interface used to set the prefs that control the behavior of smart guides.
*/
class IGuidesFacade : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IGUIDESFACADE };
	
	/**	Set whether or not to show smart guides at the center of page items.
		@param bool32 [IN]: kTrue to enable smart guides at the center of existing page items. kFalse to disable.
	 */
	virtual void EnableCenterSmartGuides(bool32 bEnable) = 0;

	/**	Get whether or not smart guides at the center of page items is enabled.
		@return kTrue if center smart guides are enabled, kFalse otherwise
	 */
	virtual bool32 GetCenterSmartGuidesEnabled(void) const = 0;


	/**	Set whether or not to show smart guides at the edges of page items.
		@param bool32 [IN]: kTrue to enable smart guides at the edges of existing page items. kFalse to disable.
	 */
	virtual void EnableEdgeSmartGuides(bool32 bEnable) = 0;

	/**	Get whether or not smart guides at the edges of page items is enabled.
		@return kTrue if edge smart guides are enabled, kFalse otherwise
	 */
	virtual bool32 GetEdgeSmartGuidesEnabled(void) const = 0;
	
	/**	Set the UI color UID for the smart guide color.
		@param uiColorUID - UID of the new UI color
	 */
	virtual void SetSmartGuideColor(const UID uiColorUID) = 0;

	/** Get the UI color UID for the smart guide color.
		@param none
		@return UIDRef - UIDRef of the current UI color used for smart guides 
	 */
	virtual const UIDRef GetSmartGuideColor() const = 0;
};

#endif
