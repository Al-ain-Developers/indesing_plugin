//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrPoint.h $
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
//========================================================================================

#pragma once
#ifndef _IGraphicAttribute_Point_
#define _IGraphicAttribute_Point_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"

class PMPoint;
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A graphic attribute data interface for x-y point data.
	*/
	class IGraphicAttrPoint : public IPMUnknown
	{
		public:
			enum {kDefaultIID = IID_IGRAPHICATTR_POINT};
			
		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________
		public:
			
			/**	Returns the point data.
			*/
			virtual PMPoint		GetPoint				(void) const = 0;

			/**	Set the point data.
				@param thePoint specifies the point to set.
			*/
			virtual void		SetPoint				(const PMPoint& thePoint) = 0;
	};
		
#endif // _IGraphicAttribute_Point_
