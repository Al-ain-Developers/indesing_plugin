//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStyleInfo.h $
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
	#ifndef _IGRAPHIC_STYLE_INFO_
	#define _IGRAPHIC_STYLE_INFO_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//___________________________________________________________________________________
//	FORWARD CLASS DECLARATIONS
//___________________________________________________________________________________
	class PMString;
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATIONS
//___________________________________________________________________________________

/** A required graphic style interface.
*/
	class IGraphicStyleInfo : public IPMUnknown
		{
		
		enum { kDefaultIID = IID_IGRAPHICSTYLE_INFO };
		
		//___________________________________________________________________________
		//	Based-on hierarchy, which graphic style is this one based on.
		//___________________________________________________________________________
		public:
			/**	Get the style UID which this style is based on.
				@return the UID which this style is based on.
			*/
			virtual UID		GetBasedOn				(void) const = 0;

			/**	Set the style UID which this style is based on.
				@param newBaseStyleUID the style UID which this style is based on.
			*/
			virtual void 	SetBasedOn				(const UID& newBaseStyleUID) = 0;

		//___________________________________________________________________________
		//	Graphic Style's name
		//___________________________________________________________________________
		public:
			/**	Returns the style name.
				@return the PMString.
			*/
			virtual const 	PMString& GetName	(void) const = 0;

			/**	Set the style name.
				@param newStyleName the new style name.
			*/
			virtual void 	SetName					(const PMString& newStyleName) = 0;
		};

#endif // _IGRAPHIC_STYLE_INFO_