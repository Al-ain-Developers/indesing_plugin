//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradFillGraphicStateData.h $
//  
//  Owner: Thanh Nguyen
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
//  Interface for set/get data which is used by GradFillGfxStateObserver.cpp.
//  
//========================================================================================

#pragma once
#ifndef __IGradFillGraphicStateData__
#define __IGradFillGraphicStateData__


#include "IPMUnknown.h"

/**	A data interface to bridge between the gradient slider tracker and the
	gradient graphic state observer for updating gradient color stops.
*/
class IGradFillGraphicStateData : public IPMUnknown
{
	public:
		/**	Set the current color stop index to block color update to graphic state.
			@param blockIndex is the color stop index blocking color update.
		*/
		virtual void SetGradientColorBlockIndex(int16 blockIndex) = 0;

		/**	Return the color stop index blocking the color update to graphic state.
		*/
		virtual int16 GetGradientColorBlockIndex() = 0;

		/**	Set to true is color block state is being updated.
			@param isColorChange is true if updating color block state.
		*/
		virtual void SetColorBlockChange(bool16 isColorChange) = 0;

		/**	Return true if color block state is updated.
		*/
		virtual bool16 GetColorBlockChange() = 0;

		/**	This method is obosolete and is not supported.
		*/
		virtual void SetIamInSelectableDialog(bool16 inDialog) = 0;

		/**	This method is obosolete and is not supported.
		*/
		virtual bool16 GetIamInSelectableDialog() = 0;
};

#endif // __IGradFillGraphicStateData__