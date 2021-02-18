//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrInt32.h $
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
	#ifndef _IGraphicAttribute_Int32_
	#define _IGraphicAttribute_Int32_
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

	/**	A graphic attribute data interface for 32-bit integer values.
	*/
	class IGraphicAttrInt32 : public IPMUnknown
		{
		public:
			enum {kDefaultIID = IID_IGRAPHICATTR_INT32};

		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________
			
			/**	Returns the 32-bit integer value.
			*/
			virtual int32		GetInt32				(void) const = 0;

			/**	Set the 32-bit integer value.
				@param int32Value specifies the 32-bit integer value to set.
			*/
			virtual void		SetInt32				(const int32& int32Value) = 0;
		};
		
#endif // _IGraphicAttribute_Int32_
