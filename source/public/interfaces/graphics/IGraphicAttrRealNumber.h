//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrRealNumber.h $
//  
//  Owner: Michael_Martz
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
	#ifndef _IGraphicAttribute_RealNumber_
	#define _IGraphicAttribute_RealNumber_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A graphic attribute data interface for floating point numbers.
	*/
	class IGraphicAttrRealNumber : public IPMUnknown
		{
		public:
			enum {kDefaultIID = IID_IGRAPHICATTR_REALNUMBER};
					
		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________
		public:

			/**	Returns the floating point number.
			*/
			virtual PMReal		GetRealNumber				(void) const = 0;
			/**	Set the floating point number.
				@param realValue specifies the floating point number to set.
			*/
			virtual void		SetRealNumber				(const PMReal& realValue) = 0;
		};
		
#endif // _IGraphicAttribute_RealNumber_
