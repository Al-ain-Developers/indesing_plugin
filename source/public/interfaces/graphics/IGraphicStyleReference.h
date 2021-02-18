//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStyleReference.h $
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
	#ifndef _IGRAPHIC_STYLE_REFERENCE_
	#define _IGRAPHIC_STYLE_REFERENCE_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS FORWARDS
//___________________________________________________________________________________
	class IGraphicStyleDescriptor;
//___________________________________________________________________________________
//	CLASS DECLARATIONS
//___________________________________________________________________________________

/**	An interface for getting and setting the graphic style.
*/
	class IGraphicStyleReference : public IPMUnknown
		{
		public:
			enum {kDefaultIID = IID_IGRAPHICSTYLE_REFERENCE};

		//___________________________________________________________________________
		//	Each PageItem has a GraphicStyle reference.
		//___________________________________________________________________________
		public:
			
			/**	Returns the graphic style UID.
				@return the graphic style UID.
			*/
			virtual UID		GetReference			(void) const = 0;

			/**	Sets the new graphic style UID.
				@param newStyleUID the new graphic style UID to set.
			*/
			virtual void 	SetReference			(const UID& newStyleUID) = 0;
			
			
			/**	Returns the graphic style descriptor associated with this graphic style UID.
				@return IGraphicStyleDescriptor* or nil.
			*/
			virtual IGraphicStyleDescriptor*	GetDescriptor (void) const = 0;
			/**	Sets the new graphic style UID using the specified new style descriptor.
				@param iNewStyleDescriptor the new graphic style descriptor to set.
			*/
			virtual void						SetDescriptor (IGraphicStyleDescriptor* iNewStyleDescriptor) = 0;			
		};

#endif // _IGRAPHIC_STYLE_REFERENCE_