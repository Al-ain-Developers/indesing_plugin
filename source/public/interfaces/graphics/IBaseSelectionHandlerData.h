//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IBaseSelectionHandlerData.h $
//  
//  Owner: rich gartland
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
#ifndef __IBASESELECTIONHANDLERDATA__
#define __IBASESELECTIONHANDLERDATA__

#include "IPMUnknown.h"
#include "LayoutUIID.h"
#include "PMRect.h"

/** 
	Class for setting and getting handler data for the target rectangle for hit-test handlers.
*/
class IBaseSelectionHandlerData : public IPMUnknown
{
	public:

		/**	Set the hit-test target rectangle.
			@param theRect the target rectangle in window coordinates.
		*/
		virtual void SetHitTestRectangle(PMRect theRect) = 0;

		/**	Get the hit-test target rectangle.
			@return the target rectangle in window coordinates
		*/
		virtual const PMRect& GetHitTestRectangle() const = 0; 
};


#endif

