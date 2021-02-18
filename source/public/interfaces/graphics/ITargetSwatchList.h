//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITargetSwatchList.h $
//  
//  Owner: Paul Ronan
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
#ifndef __ITargetSwatchList__
#define __ITargetSwatchList__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "ISwatchList.h"
#include "IInkList.h"

/**	This is a helper interface which sets the target swatch list and ink list for 
	swatches reference conversion. If target swatch or ink list is not set, the
	default swatch or ink list corresponding to the reference converter's target database
	should be used.
*/
class ITargetSwatchList : public IPMUnknown	{
	public:
		enum {kDefaultIID = IID_ITARGETSWATCHLIST};

		/**	Returns the target swatch list to use.
		*/
		virtual ISwatchList* QuerySwatchList() = 0;

		/**	Set the target swatch list to the specified list.
			@param iTargetSwatchList specifies the swatch list to set.
		*/
		virtual void SetSwatchList(ISwatchList* iTargetSwatchList) = 0;

		/**	Returns the target ink list to use.
		*/
		virtual IInkList* QueryInkList() = 0;

		/**	Set the target ink list to the specified list.
			@param iTargetInkList specifies the ink list to set.
		*/
		virtual void SetInkList(IInkList* iTargetInkList) = 0;
};

#endif // __ITargetSwatchList__
