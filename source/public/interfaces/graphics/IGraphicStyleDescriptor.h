//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStyleDescriptor.h $
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
//  
//  Note:			This interface is used by clients of graphic attributes to ascertain
//  which attributes are present on a page item. This interface will resolve
//  any applied graphic style and override and return the requested attribute.
//  
//========================================================================================

#pragma once
	#ifndef _IGRAPHIC_STYLE_DESCRIPTOR_
	#define _IGRAPHIC_STYLE_DESCRIPTOR_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
class IGraphicStyleAttributeBossList;

/**	This interface should be used whenever there's a need to determine which attributes are
	applied. It will resolve between any applied graphic style and overrides.
*/
class IGraphicStyleDescriptor : public IPMUnknown
	{
	//________________________________________________________________________________
	//	Data Types
	//________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICSTYLE_DESCRIPTOR };
	
	//___________________________________________________________________________
	//	Attribute access
	//___________________________________________________________________________
	public:
		/**	Returns the requested interface pointer of the specified attribute.
			@param attrClass the class ID of the attribute requested.
			@param interfaceID the requested interface IID.
			@return the interface pointer IPMUnknown* or nil.
		*/
		virtual IPMUnknown*		QueryAttribute			(ClassID attrClass, const PMIID& interfaceID = IID_IUNKNOWN) = 0;

		/**	Creates a copy of the specified attribute and returns the requested interface pointer
			to the attribute copy.
			@param attrClass the class ID of the attribute requested.
			@param interfaceID the requested interface IID.
			@return the interface pointer IPMUnknown* or nil.
		*/
		virtual IPMUnknown*		CreateAttributeCopy		(ClassID attrClass, const PMIID& interfaceID = IID_IUNKNOWN) = 0;

		/**	Creates a copy of the list of the current attributes associated with the graphic style and overrides.
			@return a list of attribute objects.
		*/
		virtual	IGraphicStyleAttributeBossList*		CreateDescriptorCopy		(void) = 0;
		
		/**	Creates a copy of the list of the current attributes classes associated with the graphic style and overrides.
			@return a list of attribute classes.
		*/
		virtual	K2Vector<ClassID>*					CreateDescriptorClassList	(void) = 0;
	};

#endif // _IGRAPHIC_STYLE_DESCRIPTOR_