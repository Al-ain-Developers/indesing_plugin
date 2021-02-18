//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicMetaConverter.h $
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
//  Review Date:	
//  
//  Purpose:		Common interface for all rendering object providers for
//  creation of meta data object, conversion of meta data objec to
//  rendering object, and comparison of meta data and rendering objects.
//  
//========================================================================================

#pragma once
	#ifndef _IGraphicMetaConverter_
	#define _IGraphicMetaConverter_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//___________________________________________________________________________________
//	CLASS FORWARDS
//___________________________________________________________________________________
	class IWorkspace;
	class ICommand;
	class IRenderingObject;
	class UIDList;
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________
	/**	This interface is obsolete and is deprecated.
		Concept of graphic meta data is no longer supported.
		Similar functionality is now provided by another interface, IRenderingObjectService.
		@see also IRenderObjectService.h
	*/
	class IGraphicMetaConverter : public IPMUnknown
		{
		public:
			enum preserveReference {kPreserveNone = 0, kPreserveGlobals, kPreserveAll};

		//___________________________________________________________________________
		//	Utilities
		//___________________________________________________________________________
		public:
			virtual ClassID			GetRenderObjectClassID				(void) = 0;
			virtual ClassID			GetMetaObjectClassID				(void) = 0;
			virtual ClassID			GetRenderObjectDeleteCommandClassID	(void) = 0;
			
			// This method is only called once when the graphic state intializes for
			// the first time.  It should not be called from anywhere else.
			virtual IPMUnknown*		CreateInitialMetaData		(IWorkspace*) = 0;
			
			// This method fills in default values for a rendering object.  
			virtual void			InitializeRenderObject		(IPMUnknown*, IWorkspace*) = 0;
			
		//___________________________________________________________________________
		//	Conversion Utilities
		//___________________________________________________________________________
		public:
			virtual IPMUnknown*		CreateDuplicateMetaData		(IPMUnknown*, bool16) = 0;

			virtual IPMUnknown*		CreateMetaData				(IPMUnknown*, IGraphicMetaConverter::preserveReference) = 0;
			virtual IPMUnknown*		CreateMetaData				(IPMUnknown*, bool16 ) = 0;
			virtual IPMUnknown*		CreateMetaData				(void) = 0;

			virtual UID				GetRenderObjectUID			(const IPMUnknown*, IWorkspace*) = 0;

			virtual UIDList*		CreateRenderObjectUIDList	(const IPMUnknown*, ClassID, const UIDList*, IWorkspace*) = 0;

			//	This method creates a new rendering object matching the meta data object in the
			//	given workspace. The attributes/data that are used to create the new render
			//	object should be completely described by the meta data object.
			//	It returns the new UID of the render object
			virtual UID				CreateNewRenderObject		(IPMUnknown*, IWorkspace*) = 0;
			
			//	This method creates a new rendering object matching the meta data object and the
			//	current attributes in the graphic state. The render object is created in the
			//	current active workspace.
			//	It returns a list of relevant UIDs for the new objects created.
			//	For most render objects, the UIDList contains one item. An example where
			//	a render object might returns more than one UID in the list is the color
			//	render object. In this case, depending on the current graphic state, it might
			//	returns two UIDs - one is a new base color UID and the other is a tinted color
			//	of the base color. In this case, the base color is hidden and the tinted color
			//	is visible.
			virtual UIDList			CreateNewRenderObject		(IPMUnknown*) = 0;

		//___________________________________________________________________________
		//	Copmare Utilities
		//___________________________________________________________________________
		public:
			virtual bool16			RenderingObjectsEqual		(IRenderingObject*, IRenderingObject*) = 0;
			virtual bool16			MetaDataObjectsEqual		(IPMUnknown*, IPMUnknown*) = 0;
		
		};
		
#endif // _IGraphicMetaConverter_
