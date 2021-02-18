//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorOverrides.h $
//  
//  Owner: SusanCL
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
#ifndef __IColorOverrides__
#define __IColorOverrides__

#include "ColorSystemID.h"
#include "IPMUnknown.h"
#include "PMReal.h"

class IColorOverrides : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOLOROVERRIDES };
		
		/**	Returns the tint percentage in the range of [0, 100), not including 100.
			Returns -1 if tint is not set.
		*/
		virtual PMReal GetTint () const = 0;
		
		/**	Sets the tint percentage in the range of [0, 100), not including 100.
			The default value is -1 which means the tint value is not set.
			@param tint tint value
		*/
		virtual void SetTint (const PMReal& tint) = 0;
		
		/**	This enumerate the special type information for the color swatch.
		*/			
		enum {
				/** kNormal indicates a normal color swatch */
				kNormal = 0,
				/** kSpecialPaper indicates the reserved paper swatch */
				kSpecialPaper,
				/** kSpecialBlack indicates the reserved black swatch */
				kSpecialBlack,
				/** kSpecialRegistration indicates the reserved registration swatch */
				kSpecialRegistration,
				/** kHiddenReserved indicates the hidden reserved swatches. Currently there are three
					hidden reserved swatches: process "Cyan", process "Magenta", and process "Yellow" swatches
				*/
				kHiddenReserved,
				/** kMixedInkParent indicates the mixed ink group's parent swatch.
					There should at least one mixed ink swatch based on this parent.
				*/
				kMixedInkParent
			 };
		
		/**	Returns the special color type information.
		*/ 
		virtual const int32 GetColorRemark () const = 0;

		/**	Sets the special color type information for this swatch. Client should only set
			swatches to kNormal or kMixedInkParent.
			@param remark the special color type for this swatch.
		*/ 
		virtual void SetColorRemark (const int32 remark) = 0;

};
#endif
