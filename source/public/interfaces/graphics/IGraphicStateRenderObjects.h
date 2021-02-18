//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateRenderObjects.h $
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
	#ifndef _IGraphicStateRenderObjects_
	#define _IGraphicStateRenderObjects_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"

//========================================================================================
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class	ICommand;
	class 	IRenderingObject;
	class 	IWorkspace;
	class	IGraphicAttributeSuite;
	class	IGraphicStateData;
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/**	This is a peresistent interface for the graphic state object.
	It manages changes to the graphic state's currently active rendering object.
*/
class IGraphicStateRenderObjects : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IGRAPHICSTATE_RENDEROBJECTS};
		
		/**	
			Returns the persistent data base associated with this interface.
		*/
		virtual IDataBase*	GetDataBase						(void) = 0;

		/**	
			Initialized the graphic rendering objects with the data specified by
			IGrahicStateData interface. This is called only when the graphic state is
			created without app defaults.
			@param iGraphicStateData specifies the graphic state data to update with.
		*/
		virtual	void		Initialize						(IGraphicStateData* iGraphicStateData) = 0;	
		/**	
			Register the specified rendering object class.
			@param renderClassID the new rendering class ID to register.
			@param renderUID the rendering UID for renderClassID to register.
			@return error code (kSuccess or kFailure).
		*/
		virtual ErrorCode	RegisterNewRenderObjectClass	(ClassID renderClassID, UID renderUID) = 0;

		//____________________________________________________________________________________
		//	Rendering class Block utilities
		//____________________________________________________________________________________
		/**	
			Set block for the specified rendering class.
			@param renderClassID the rendering class set block.
			@param blockFlag the flag to set the rendering class block state.
			@return error code (kSuccess or kFailure).
		*/
		virtual ErrorCode 	SetBlock						(ClassID renderClassID, bool16 blockFlag) = 0;
		/**	
			Return kTrue if the specified rendering class is blocked.
			@param renderClassID the rendering class to query.
			@param blockFlag the flag is set to kTrue if the rendering object is blocked.
			Otherwise it is set to kFalse.
			@return error code (kSuccess or kFailure).
		*/
		virtual ErrorCode	IsBlocked						(ClassID renderClassID, bool16* blockFlag) const = 0;
		/**	
			Clear all blocks for all registered rendering classes.
		*/
		virtual void		ClearEveryBlock					(void) = 0;
	
		//____________________________________________________________________________________
		//	Rendering object utilities
		//____________________________________________________________________________________
		/**	
			Return the current IRenderingObject interface for the spcified rendering class.
			@param renderClassID the rendering class to query.
			@return IRenderingObject*.
		*/
		virtual const IRenderingObject*	QueryRenderObject	(ClassID renderClassID) const = 0;
		/**	
			Return the current rendering UID for the spcified rendering class.
			@param renderClassID the rendering class to query.
			@return UID
		*/
		virtual UID			GetRenderObjectUID				(ClassID renderClassID) const = 0;
		/**	
			Change the current rendering UID for the given rendering class to the specified rendering UID.
			@param renderClassID the rendering class to change.
			@param renderUID the rendering UID to change.
			@param doBroadcast the flag indicating whether or not the change should be broadcasted.
			@return error code (kSuccess or kFailure).
		*/
		virtual ErrorCode	ChangeRenderObject				(ClassID renderClassID, UID renderUID, bool16 doBroadcast = kTrue) = 0;	// kTrue broadcast change; other don't
		/**	
			Returns kTrue if the specified render class is currently indeterminant. This means that
			there are more than one dis-similar objects of the same rendering class in the graphic state.
			@param renderClassID the rendering class to query.
			@return kTrue if rendering class is indeterminant.
		*/
		virtual	bool16		IsRenderingObjectIndeterminant	(ClassID renderClassID) const = 0;

		/**	
			Returns a list of the currently registered rendering classes.
			@param renderClassCount the number of rendering class in the list.
			@return the list of rendering classes.
		*/
		virtual ClassID*	CreateRenderObjectClassList		(int32* renderClassCount) const = 0;
		/**	
			Returns the currently active rendering class in the graphic state.
			@return the active rendering class.
		*/
		virtual ClassID		GetCurrentRenderObjectClass		(void) const = 0;
		
		/**	
			Broadcast a render object changed message.
			@param renderClassID the rendering class to change.
			@param doForwardToDefinition when this is set to kTrue, then the
			change is forwarded to the current definition.
		*/
		virtual void		RenderObjectChanged				(ClassID renderClassID, bool16 doForwardToDefinition) = 0;
		
		/**	
			Broadcast a color management changed message.
		*/
		virtual void		ColorManagementChanged			(void) = 0;
		/**	
			Broadcast a change message indicating the changes in the rendering type's
			enabling state.
			@param disabledList the list of currently disabled rendering classes.
		*/
		virtual void		EnabledRenderingTypesHaveChanged(const K2Vector<ClassID>* disabledList) = 0;
		/**	
			Returns kTrue if the specified rendering class is currently disabled.
			@param renderClassID the rendering class to query.
			@return kTrue if the given rendering class is currently disabled.
		*/
		virtual bool16 		IsRenderingObjectDisabled		(const ClassID& renderClassID) = 0;

		/**	
			Updates the interface's persistent data interface. This is called by the
			graphic state's private commands. Client should not make this call directly.
			To change the graphic states render object, use ChangeRenderObject().
			Calling this directly will cause database transaction errors.
			@param renderClassID the rendering class to update.
			@param renderUID the new UID for the corresponding class.
			@return kSuccess if the UID for given rendering class is updated successfully.
			Otherwise, return kFailure.
		*/
		virtual ErrorCode	UpdateRenderData				(ClassID renderClassID, UID renderUID) = 0;
	};

/**	Abstract message for used with GfxStateRenderObjectChangeMsg 
*/
class GfxStateAbstractROChangeMsg
	{
	};
	
/**	Abstract message for rendering object changed message.
	@param classID specifies the rendering class ID affected.
*/
class GfxStateGenericROChangeMsg : public GfxStateAbstractROChangeMsg
	{
	public:
		ClassID			 classID;
	};
	
/**	Abstract message for rendering objects enabling state changes.
	@param disabledRenderingTypes specifies the list of rendering classes
	that have become disabled.
*/
class GfxStateEnabledROChangeMsg : public GfxStateAbstractROChangeMsg
	{
	public:
		const K2Vector<ClassID>	*disabledRenderingTypes;
	};

/**	A message class for broadcasting graphic state rendering object changed message.
*/
class GfxStateRenderObjectChangeMsg
	{
	//________________________________________________________________________________
	//	Data Types
	//________________________________________________________________________________
	public:
		enum MessageType
			{
			/**	kMsg_RenderObjectChanged indicates a render object changed.
				The abstract message has been set to GfxStateGenericROChangeMsg.
			*/
			kMsg_RenderObjectChanged 	= 0,
			/**	kMsg_BlockChanged indicates a render object block has changed.
				The abstract message has been set to GfxStateGenericROChangeMsg.
			*/
			kMsg_BlockChanged,
			/**	kMsg_ClearEveryBlock indicates all render object blocks have been cleared.
				The abstract message has been set to nil.
			*/
			kMsg_ClearEveryBlock,
			/**	kColorTransformChangedMsg indicates the color management system has changed transforms.
				The abstract message has been set to nil.
			*/
			kColorTransformChangedMsg,	
			/**	kEnabledRenderingTypeMsg indicates the list of disabled rendering types has changed.
				The abstract message has been set to GfxStateEnabledROChangeMsg.
			*/
			kEnabledRenderingTypeMsg,
			/** kGraphicStateChangMsg indicates the whole graphic state environment has changed.
				The abstract message has been set to nil.
			*/
			kGraphicStateChangMsg
			};
	
	//________________________________________________________________________________
	//	Data Members		
	//________________________________________________________________________________
	public:
		/**	Specfies the message type.
		*/
		MessageType		 				 type;						
		/**	This is the abstract message and is determined by "MessageType".
		*/
		GfxStateAbstractROChangeMsg		*message;
		/**	This is the graphic state object sending the message.
		*/
		IGraphicStateRenderObjects		*iGfxStateRenderObjects;
		/**	This is the corresponding graphic attribute suite.
		*/
		IGraphicAttributeSuite			*iGfxAttrSuite;
	};

	
#endif // _IGraphicStateRenderObjects_
