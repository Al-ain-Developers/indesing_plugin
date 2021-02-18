//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateDefinition.h $
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
	#ifndef _IGraphicStateDefinition_
	#define _IGraphicStateDefinition_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"

//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
class ICommand;
class IGraphicStyleAttributeBossList;
class GraphicSelectionTarget;
class UIDList;
class IGraphicStateRenderObjects;
class IWorkspace;
class GfxStateReplacementData;

/**	This inteface is obsolete and will not be supported.
	This has been replaced by the graphic attribute suites.
	@see IGraphicAttributeSuite.h
*/
class IGraphicStateDefinition : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum TargetType
			{
			kCurrentTarget		= -1,
			kDefaultTarget		= 0,
			kSelectionTarget,
			kEyedropperTarget
			};
			
		enum RenderingType
			{
			kNothing			= 0,
			kStroke,
			kFill,
			kBoth
			};
			
	//____________________________________________________________________________________
	//	Attribute Utilities 
	//____________________________________________________________________________________
	public:
		virtual uint16 				GetAttributeCount			(ClassID, TargetType = kCurrentTarget) = 0;
		virtual int16				GetAttributeValueCount 		(ClassID, uint32 whichAttribute, TargetType) = 0;
		
		virtual ErrorCode			AddAttribute				(IPMUnknown*, ICommand*, TargetType) = 0;
		virtual ErrorCode			CopyIntoAttribute			(uint32, IPMUnknown*, ICommand*, TargetType) = 0;
		virtual ErrorCode			RemoveAttribute				(ClassID, ICommand*, TargetType) = 0;

		virtual IPMUnknown*			QueryAttribute				(uint32, ClassID, const PMIID& = IID_IUNKNOWN, TargetType = kCurrentTarget) = 0;
		virtual IPMUnknown*			CreateAttributeCopy			(uint32, ClassID, const PMIID& = IID_IUNKNOWN, TargetType = kCurrentTarget) = 0;
		
		virtual ErrorCode			SwapStrokeAndFill			(ICommand*, TargetType) = 0;
	//____________________________________________________________________________________
	//	Meta Data Utilities 
	//____________________________________________________________________________________
	public:
		virtual ErrorCode			Initialize						(IWorkspace*) = 0;
		virtual ErrorCode			RegisterMetaDataObject			(IDataBase*, ClassID, IPMUnknown*) = 0;
		virtual ErrorCode			InitializeRenderObjects			(IGraphicStateRenderObjects*) = 0;

		// The following two methods update data in the graphic definition
		virtual ErrorCode			ChangeFillMetaDataObject		(ClassID, IPMUnknown*, TargetType) = 0;
		virtual ErrorCode			ChangeStrokeMetaDataObject		(ClassID, IPMUnknown*, TargetType) = 0;

		// The following three methods are for INTERNAL USE ONLY
		virtual ErrorCode			UpdateFillMetaDataObject		(ClassID, IPMUnknown*, TargetType) = 0;
		virtual ErrorCode			UpdateStrokeMetaDataObject		(ClassID, IPMUnknown*, TargetType) = 0;
		virtual void				UpdateRenderObjectsToProxyState	(void) = 0;
		
		virtual IPMUnknown*			CreateFillMetaDataCopy			(ClassID, TargetType) = 0;
		virtual IPMUnknown*			CreateStrokeMetaDataCopy		(ClassID, TargetType) = 0;

		virtual IPMUnknown*			QueryFillMetaData				(ClassID, TargetType) = 0;
		virtual IPMUnknown*			QueryStrokeMetaData				(ClassID, TargetType) = 0;

		virtual void				CreateDefaultStrokeAndFillMetaDataCopy	(IPMUnknown**, IPMUnknown**) = 0;

		virtual	void				InitializeDefaultFillMetaData	(IPMUnknown*,ClassID) = 0;
		virtual	void				InitializeDefaultStrokeMetaData	(IPMUnknown*,ClassID) = 0;
		
		//................................................................................
		//	Replace selection/default meta data within the graphic state whose meta data
		//	is dependent on the data contained by the rendering object specified by UID.
		//	It is assumed that this member function is called within a transaction and
		//	that the caller is responsible for undo and redo. None and multiple meta 
		//	data objects are not searched. Returns what was actually replaced.
		//................................................................................
		virtual void		ReplaceDefaultMetaData		(UID uidToReplace, IPMUnknown *newMetaData, ClassID renderingObjectClass, GfxStateReplacementData*) = 0;
		virtual void		ReplaceSelectionMetaData	(UID uidToReplace, IPMUnknown *newMetaData, ClassID renderingObjectClass, GfxStateReplacementData*) = 0;

		//................................................................................
		//	Replace selection/default meta data within the graphic state whose UID equals 
		//	"uidToReplace" with the meta data provided.  It is assumed that this 
		//	member function is called within a transaction and that the caller is
		//	responsible for undo and redo. None and multiple meta data objects are
		//	not searched. Returns what was actually replaced.
		//................................................................................
		virtual void				ReplaceDefaultMetaData		(GfxStateReplacementData *original, GfxStateReplacementData *newData) = 0;
		virtual void				ReplaceSelectionMetaData	(GfxStateReplacementData *original, GfxStateReplacementData *newData) = 0;

		//................................................................................
		//	If the content of a rendering object has changed outside of the graphic
		//	state, use this member function to force the graphic state to regenerate
		//	its meta data based on the current set of attributes. Works on the 
		//	selection defintion only.
		//................................................................................
		virtual ErrorCode			SyncMetaDataObjectsWithAttributes (RenderingType) = 0;
				
	
	//____________________________________________________________________________________
	//	Default/Selection (Target) Utilities 
	//____________________________________________________________________________________
	public:
		virtual void				ApplyMetaDataToSelection		(ClassID, IPMUnknown*, ClassID) = 0;
		virtual ClassID				GetCurrentRenderObjectClass		(void) const = 0;

		virtual ClassID				GetFillClass					(TargetType) = 0;
		virtual ClassID				GetStrokeClass					(TargetType) = 0;

		virtual void				SetFillClass					(TargetType, ClassID) = 0;
		virtual void				SetStrokeClass					(TargetType, ClassID) = 0;

		virtual void				SetCurrentTarget				(TargetType) = 0;
		virtual TargetType			GetCurrentTarget				(void) = 0;

		virtual GraphicSelectionTarget*	GetSelectionTarget				(void) = 0;
		virtual void					SelectionTargetChanged			(ClassID) = 0;

		//................................................................................
		//	DESCR:		Return a descriptor from the cache.
		//
		//	NOTE:		The descriptor should not be held onto. It may be changed or released with
		//				the next selection change. Clients should not modify it or its contents.
		//
		//	RETURNS:	iDescriptor or nil
		//................................................................................
		virtual const IGraphicStyleAttributeBossList* GetPageItemDescriptorFromCache (int32) = 0;
		
		virtual void					EnabledAttributesHaveChanged		(TargetType, K2Vector<ClassID>*) = 0;
		virtual void					EnabledRenderingTypesHaveChanged	(TargetType, const K2Vector<ClassID>*, const K2Vector<ClassID>*) = 0;
		virtual bool16					IsAttributeEnabled					(ClassID) = 0;
		virtual bool16					IsStrokeRenderTypeEnabled			(ClassID) = 0;
		virtual bool16					IsFillRenderTypeEnabled				(ClassID) = 0;
		
		virtual	void 					ApplyTargetAttributesToPageItems 	(TargetType, const UIDList&, ClassID*, uint16) = 0;
		virtual ErrorCode				RemoveAllAttributes					(ICommand*, TargetType,  ClassID*, uint16) = 0;

		virtual IGraphicStyleAttributeBossList* CreateAttributeListCopy		(TargetType) = 0;
		virtual ErrorCode						SetTargetAttributeList 		(TargetType, IGraphicStyleAttributeBossList*, ICommand*) = 0;
		virtual ErrorCode				AddMultAttributes					(IGraphicStyleAttributeBossList*, ICommand*, TargetType) = 0;

	//____________________________________________________________________________________
	//	Defaults
	//____________________________________________________________________________________
	public:
		virtual ErrorCode			AddGraphicDefaults			(const UIDList*) = 0;
		virtual ErrorCode			AddTextFrameDefaults		(const UIDList*) = 0;
		virtual ErrorCode			AddGraphicFrameDefaults		(const UIDList*) = 0;
	};
/** This is obsolete. */
class GfxStateAbstractDefnChangeMsg
	{
	};
	
/** This is obsolete. */
class GfxStateGenericDefnChangeMsg : public GfxStateAbstractDefnChangeMsg
	{
	public:
		ClassID			 classID;
	};
	
/** This is obsolete. */
class GfxStateEnabledDefnChangeMsg : public GfxStateAbstractDefnChangeMsg
	{
	public:
		const K2Vector<ClassID>*		disabledClasses;
	};

/** This is obsolete. */
class GfxStateDefintionChangeMsg
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum MessageType
			{
			kMsg_AttributeChanged 	= 0,		// An attribute was changed (GfxStateGenericDefnChangeMsg)
			kMsg_AttributeAdded,				// An attribute was added (GfxStateGenericDefnChangeMsg)
			kMsg_AttributeRemoved,				// An attribute was removed (GfxStateGenericDefnChangeMsg)
			kMsg_DefinitionChanged,				// The whole definition changed in one or more ways (nil)
			kMsg_FillMetaDataChanged,			// The fill meta data changed (GfxStateGenericDefnChangeMsg)
			kMsg_StrokeMetaDataChanged,			// The stroke meta data changed (GfxStateGenericDefnChangeMsg)
			kCurrentFillChangedMsg,				// The current fill rendering type has changed (GfxStateGenericDefnChangeMsg)
			kCurrentStrokeChangedMsg,			// The current stroke rendering type has changed (GfxStateGenericDefnChangeMsg)
			kSwapStrokeAndFillMsg,				// The fill and stroke have been swapped (nil)
			kEnabledAttributesMsg,				// The attribute which are enabled have changed (GfxStateEnabledDefnChangeMsg)
			kEnabledFillRenderingTypesMsg,		// The fill rendering types which are enabled have changed (GfxStateEnabledDefnChangeMsg)
			kEnabledStrokeRenderingTypesMsg,	// The stroke rendering types which are enabled have changed (GfxStateEnabledDefnChangeMsg)
			kGraphicStateChangedChangeMsg		// The graphic state object is changing (used to use a message of nil)
			};
	
	//____________________________________________________________________________________
	//	Data Members		
	//____________________________________________________________________________________
	MessageType								 type;
	GfxStateAbstractDefnChangeMsg			*message;				// Value determined by "type"
	IGraphicStateDefinition::TargetType		 target;			
	bool16									 inCurrentTarget;
	IGraphicStateDefinition					*iGfxStateDefintion;	// Gfx State sending the message
	
	ICommand*								 command;				// deprecated, use information in "message"
	ClassID									 classID;				// deprecated, use information in "message"
	};
	
/** This is obsolete. */
class GfxStateReplacementData
	{
	//____________________________________________________________________________________
	//	Data Members		
	//____________________________________________________________________________________
	public:
		IPMUnknown			*iSolidColorFillMD;
		IPMUnknown			*iSolidColorStrokeMD;
		IPMUnknown			*iGradientFillMD;
		IPMUnknown			*iGradientStrokeMD;

		IPMUnknown			*iSolidColorRObjMD;
		IPMUnknown			*iGradientRObjMD;
	};

#endif // _IGraphicStateDefinition_
