//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateData.h $
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
	#ifndef _IGraphicStateData_
	#define _IGraphicStateData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
	
//========================================================================================
	#include "IGraphicAttributeSuite.h"

//________________________________________________________________________________________
//	Interface CLASS DECLARATIONS
//________________________________________________________________________________________
class GraphicTarget;
class IWorkspace;

class IGraphicStateData : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICSTATE_DATA };

		enum TargetType
			{
			kCurrentTarget		= -1,
			kDefaultTarget		= 0,
			kEyedropperTarget
			};

	public:
		//____________________________________________________________________________________
		//	Initialization
		//____________________________________________________________________________________
		/**
			Initializes the graphic state data in the specified workspace.
			Used during graphic state creation.
			@param workspace the workspace to create the persistent graphic state data.
			@return kSucess if succeed or an error code.
		*/
		virtual ErrorCode			Initialize						(IWorkspace*) = 0;

		/**
			Called to initialize the default rendering data for a specific rendering object class
			in an existing workspace.  This is useful when a new type of rendering object has been
			added to the document.
			@param workspace the workspace to operate on
			@param classid the class id of the kRenderClassProviderImpl to create default rendering UID.
			@return kSucess if succeed or an error code.
		 */
		virtual ErrorCode           Initialize                      (IWorkspace*, ClassID) = 0;

		/**
			Initialize the default fill rendering object for the specified rendering class.
			@param renderClassID the rendering object class.
			@param renderUID the rendering UID for the renderClassID.
			@precondition renderClassID must be one of the rendering classes initialized during 
			Initialize(). 
		*/
		virtual	void				InitializeDefaultFillRenderData		(ClassID, UID) = 0;

		/**
			Initialize the default fill rendering object for the specified rendering class.
			@param renderClassID the rendering object class.
			@param renderUID the rendering UID for the renderClassID.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual	void				InitializeDefaultStrokeRenderData	(ClassID, UID) = 0;

		/**
			Initialize the default attributes for the graphic state.
		*/
		virtual	void				InitializeDefaultAttributes		(void) = 0;

		//____________________________________________________________________________________
		//	Defaults
		//____________________________________________________________________________________
		/**
			Add current graphic default attributes, including rendering attributes to the specified
			page items.
			@param pageItemList the page item UID list.
		*/
		virtual ErrorCode			AddGraphicDefaults				(const UIDList*) = 0;
		/**
			Add graphic default attributes, including rendering attributes for the specified
			text frame items.
			@param itemList the UID list specifying the text frame UID items.
		*/
		virtual ErrorCode			AddTextFrameDefaults			(const UIDList*) = 0;
		/**
			Add graphic default attributes, including rendering attributes for the specified
			graphic frame items.
			@param graphicFrametemList the graphic frame item UID list.
		*/
		virtual ErrorCode			AddGraphicFrameDefaults			(const UIDList*) = 0;
		/**
			Add graphic default attributes, including rendering attributes for the specified
			group items.
			@param grouptemList the group item UID list.
		*/
		virtual ErrorCode			AddGroupDefaults				(const UIDList*) = 0;

		//____________________________________________________________________________________
		//	Attribute Utilities.
		//____________________________________________________________________________________
		/**
			Return the attribute of a given target type. The caller is responsible for releasing the
			attribute when done.
			@param attrClassID the attribute class to be returned.
			@param attrInterfaceIID the attribute's interface IID to be returned.
			@param targetType the target type from which the attribute is should be returned.
			@return IPMUnknown* of the attribute.
		*/
		virtual IPMUnknown*			QueryAttribute				(ClassID, const PMIID&, TargetType) = 0;
		/**
			Add the specified the attribute in the given target type.
			@param iAttribute the attribute object to be added. A copy is made of the specified attribute.
			@param targetType the target type from which the attribute is should be returned.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			AddAttribute				(IPMUnknown*, TargetType) = 0;
		/**
			Copy the specified the attribute in the given target type. If the attribute already exists,
			the content is copied. If attribute does not exist, it is added.
			@param iAttribute the attribute object to be copied.
			@param targetType the target type from which the attribute is should be returned.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			CopyIntoAttribute			(IPMUnknown*, TargetType) = 0;
		/**
			Remove the attribute from the given target type.
			@param iAttribute the attribute object to be removed.
			@param targetType the target type from which the attribute is should be returned.
			@return errorCode (kSuccess or an error code).
			@precondition iAttribute must already exist in the target type. If attribute does not
			exist, an error code is returned.
		*/
		virtual ErrorCode			RemoveAttribute				(ClassID, TargetType) = 0;

		/**
			Remove all specified attributes. If the list is nil, then all attributes in the target
			are removed. 
			@param attrClassList the attribute class list specified the attribute classes to be removed.
			@param attrCount the number attributes in the attrClassList.
			@param targetType the target type from which the attributes are to be removed.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			RemoveAllAttributes			(ClassID*, uint16, TargetType) = 0;
		/**
			Add all specified attributes in the target.
			@param iAttributeBossList the attribute list specified the attributes to be added.
			@param targetType the target type the attributes are to be added.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			AddMultAttributes			(IGraphicStyleAttributeBossList*, TargetType) = 0;
		/**
			Swap the current stroke and fill rendering data in the target.
			@param targetType the target type the rendering data should be swapped.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			SwapStrokeAndFill			(TargetType) = 0;
		/**
			Replace the attributes in the target with the given attribute boss list.
			@param iAttributeBossList the attribute list specified the attributes to replace.
			@param targetType the target type the rendering data should be swapped.
			@return errorCode (kSuccess or an error code).
		*/
		virtual ErrorCode			SetAttributeList 			(IGraphicStyleAttributeBossList*, TargetType) = 0;
		/**
			return a copy of the attributes in the given target. Caller should release the attribute
			boss list when done.
			@param targetType the target type the rendering data should be swapped.
			@return IGraphicStyleAttributeBossList* or nil.
		*/
		virtual IGraphicStyleAttributeBossList*	CreateAttributeListCopy (TargetType) = 0;
				
		//____________________________________________________________________________________
		//	Stroke/Fill utiltites
		//____________________________________________________________________________________
		/**
			Set the current fill rendering class for the given target.
			@param renderClassID the fill rendering class ID to set.
			@param targetType the target type the rendering data should be set.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual void				SetFillClass				(ClassID, TargetType) = 0;
		/**
			Returns the current rendering class for the given target.
			@param targetType the target type the rendering data should be returned.
			@return renderClassID
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual ClassID				GetFillClass				(TargetType) = 0;
		/**
			Set the current stroke rendering class for the given target.
			@param renderClassID the stroke rendering class ID to set.
			@param targetType the target type the rendering data should be set.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual void				SetStrokeClass				(ClassID, TargetType) = 0;
		/**
			Returns the current rendering class for the given target.
			@param targetType the target type the rendering data should be returned.
			@return renderClassID
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual ClassID				GetStrokeClass				(TargetType) = 0;

		/**
			Update the fill rendering data of the specified rendering class in the target.
			@param renderUID the fill rendering UID to update to.
			@param renderClassID the fill rendering class ID to update.
			@param targetType the target type the rendering data should be updated.
			@return kSuccess or kFailure.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual ErrorCode			UpdateFillRenderObjectUID	(ClassID, UID, TargetType) = 0;
		/**
			Update the stroke rendering data of the specified rendering class in the target.
			@param renderUID the stroke rendering UID to update to.
			@param renderClassID the stroke rendering class ID to update.
			@param targetType the target type the rendering data should be updated.
			@return kSuccess or kFailure.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual ErrorCode			UpdateStrokeRenderObjectUID	(ClassID, UID, TargetType) = 0;
		/**
			Returns the fill rendering UID of the specified rendering class in the target.
			@param renderClassID the fill rendering class ID to update.
			@param targetType the target type the rendering data should be updated.
			@return renderUID the fill rendering UID returned.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual UID					GetFillRenderObjectUID		(ClassID, TargetType) = 0;
		/**
			Returns the stroke rendering UID of the specified rendering class in the target.
			@param renderClassID the stroke rendering class ID to update.
			@param targetType the target type the rendering data should be updated.
			@return renderUID the stroke rendering UID returned.
			@precondition renderClassID must be one of the rendering classes initialized during
			Initialize(). 
		*/
		virtual UID					GetStrokeRenderObjectUID	(ClassID, TargetType) = 0;

		//____________________________________________________________________________________
		//	The following two calls are used internally.
		//____________________________________________________________________________________
		/**
			Returns the GraphicTarget for the specified target type.
			@param targetType the target type to get.
			@return the pointer to the graphic target.
		*/
		virtual GraphicTarget*		GetTarget						(TargetType) = 0;

		/**
			Mark data dirty.
		*/
		virtual void				MarkPreDirty					(void) = 0;
		
	};
#endif // _IGraphicStateData_


