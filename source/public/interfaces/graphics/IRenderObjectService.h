//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRenderObjectService.h $
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
	#ifndef __IRenderObjectService__
	#define __IRenderObjectService__
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

/** Abstract interface to directly create, delete, duplicate one or more rendering objects. 
	In practice client code would use ISwatchUtils or create corresponding command
	to provide for undo-able change to the swatches.
*/
class  IRenderObjectService : public IPMUnknown
	{
	public:

		enum { kDefaultIID = IID_IRENDEROBJECTSERVICE };		

	public:
		/**	Returns the rendering object class ID of this render class provider.
		*/
		virtual ClassID			GetRenderObjectClassID				(void) const = 0;
		
		/**	Create a temporary memory-based rendering object based on the specified rendering object.
			The caller is responsible for deleting this object when done.
			@param iSourceRenderObject the rendering object this temporary object will copy the rendering properties.
			@returns temporary IRenderingObject*.
		*/
		virtual IRenderingObject*	CreateTemporaryRenderObject		(const IRenderingObject* iSourceRenderObject) = 0;
		
		/**	Create a default rendering object in the specified data base.
		*/
		virtual UID				CreateDefaultRenderObject			(IWorkspace*) = 0;
		
		/**	Create a new rendering object in the specified data base using the specified rendering object attributes.
			@param iTargetDB the target data base in which the new rendering object is created.
			@param iNewRenderObject a memory copy of the rendering attributes which specifies how the new rendering
			object should be created.
		*/
		virtual UID				CreateNewNamedRenderObject			(IDataBase* iTargetDB, const IRenderingObject* iNewRenderData) = 0;
		virtual UID				CreateNewUnnamedRenderObject		(IDataBase* iTargetDB, const IRenderingObject* iNewRenderData) = 0;
		
		/** Delete the specified rendering objects matching the render class.
			This method is called from the DeleteSwatchCommand to perform rendering objecct specific tasks.
			Client should not call this directly to delete a swatch.
			@param itemList the list of item UID to be deleted.
			@returns remainderList containing those item UID not mathcing the render class and therefore not deleted.
		*/
		virtual ErrorCode		DeleteRenderObjects					(const UIDList& itemList, UIDList& remainderList) = 0;	

		/** Duplicate the specified rendering objects matching the render class.
			This method is called from the DuplicateSwatchCommand to perform rendering objecct specific tasks.
			Client should not call this directly to duplicate a swatch.
			@param iTargetDB the target data base in which the duplicated objects are created.
			@param itemList the list of item UID to be duplicated.
			@returns remainderList containing those item UID not mathcing the render class and therefore not duplicated.
			@returns a UIDList* of new UIDs.
		*/
		virtual UIDList*		DuplicateRenderObjects				(IDataBase* iTargetDB, const UIDList& itemList, UIDList& remainderList, ICommand* iCallingCommand, bool16 doUnlock, bool16 doConvertToUnnamed, bool16 doConvertToProcess) = 0;	
	};
		

#endif // __IRenderObjectService__
