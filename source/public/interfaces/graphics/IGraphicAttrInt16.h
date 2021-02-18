//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrInt16.h $
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
	#ifndef _IGraphicAttribute_Int16_
	#define _IGraphicAttribute_Int16_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A graphic attribute data interface for 16-bit integer values.
	*/
	class IGraphicAttrInt16 : public IPMUnknown
		{
		public:
			enum {kDefaultIID = IID_IGRAPHICATTR_INT16};

		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________

			/**	Returns the 16-bit integer value.
			*/
			virtual int16		GetInt16				(void) = 0;

			/**	Set the 16-bit integer value.
				@param int16Value specifies the 16-bit integer value to set.
			*/
			virtual void		SetInt16				(const int16& int16Value) = 0;
		};
		
#endif // _IGraphicAttribute_Int16_
