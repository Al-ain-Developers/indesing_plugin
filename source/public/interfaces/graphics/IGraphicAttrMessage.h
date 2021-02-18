//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrMessage.h $
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
//  
//  Desc:	Messages for graphic attributes.
//  
//========================================================================================

#pragma once
	#ifndef _IGraphicAttrMessage_
	#define _IGraphicAttrMessage_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h" 					// for the definition of INHERITFROM

	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
	#include "K2Vector.h"
	
	#include "ISelectionMessages.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
class	IGraphicStateRenderObjects;

//____________________________________________________________________________________
//	For external communication
//____________________________________________________________________________________

/**	A graphic attribute selection suite message. This message will be broadcast whenever
	selection attributes affecting graphic attributes are changed.
*/
class IGraphicAttrMessage : public SelectionSuiteData
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
						
		//____________________________________________________________________________________
		//	GraphicAttributeCache message Type
		//____________________________________________________________________________________

		/**	CSB messages for selection and selection attribute changes.
		*/
		enum MessageType
			{
			/**	kMsg_DefinitionChanged indicates that the whole or parts of definition
				changed in one or more ways (nil, one or more attr classes).
				The class list below can be empty, i.e. ClassID count is 0, 
				then the whole definition changes.
				If class list is > 0, then only those attributes included are affected.
			*/
			kMsg_DefinitionChanged = 3,			

			/**	kSwapStrokeAndFillMsg indicates the fill and stroke have been swapped.
				The class list will be nil.
			*/
			kSwapStrokeAndFillMsg = 6,			
			/**	kGraphicStateChangedChangeMsg indicates the graphic state object is changing.
				The class list will be nil.
			*/
			kGraphicStateChangedChangeMsg,

			/**	kMsg_SelectionChanged indicates a message broadcast from cache to suites.
				Client code should ignore.
			*/
			kMsg_SelectionChanged = 100,
			/**	kMsg_SelectionChanged indicates a message broadcast from cache to suites.
				Client code should ignore.
			*/
			kMsg_SelectionAttrChanged = 200,
			/**	kMsg_SelectionChanged indicates a message broadcast from cache to suites.
				Client code should ignore.
			*/
			kMsg_ProxyTypeChanged = 300,
			/**	kMsg_SelectionChanged indicates a message broadcast from cache to suites.
				Client code should ignore.
			*/
			kMsg_AttrsEnableStateChanged = 400

			};

	public:
	//____________________________________________________________________________________
	//	Accessors		
	//____________________________________________________________________________________
	
	/**	Returns the message type.
	*/
	virtual	MessageType							GetMessageType					(void) const = 0;
	/**	Returns the number of attribute class count in the list.
	*/
	virtual	int32								GetClassIDCount					(void) const = 0;
	/**	Returns the nth class ID.
	*/
	virtual	ClassID								GetClassID						(int32 index = 0) const = 0;
	/**	Returns whether or not the specified attribute class ID is affected.
		@param classID specifies the interested attribute class ID.
		@return true if class ID is in the list.
	*/
	virtual	bool16								IsClassAffected					(const ClassID& classID) const = 0;
	/**	Returns true if the result of the attribute changes also required all rendering blocks
		to be cleared.
	*/
	virtual	bool16								NeedClearAllBlocks				(void) const = 0;
	
	};
	
/**	This message class is for internal used only.
	This message will not be broadcast to clients.
*/
class IGraphicAttrCacheMessage INHERITFROM
	{
	public:
		/**	Returns the cache message's signature IID.
		*/
		virtual PMIID								GetMessageSignatureID	(void) const = 0;
		/**	Returns the cache message type.
		*/
		virtual IGraphicAttrMessage::MessageType	GetMessageType			(void) const = 0;
		/**	Returns the list of affected attribute classes.
		*/
		virtual const K2Vector<ClassID>*			GetAttrClassList		(void) const = 0;
		
	};

#endif // _IGraphicAttrMessage_
