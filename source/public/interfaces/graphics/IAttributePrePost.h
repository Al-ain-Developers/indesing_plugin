//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAttributePrePost.h $
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
//  Note:		This interface is optional on graphic and text attributes. If it is present, 
//  the apply attribute commands will call PreXxxxApply() before the attribute is 
//  applied and PostXxxxApply() afterwards.
//  For graphic attributes the IClassIDListData* is used to notify the graphic
//  state of the attributes that were changed within the Pre and Post member 
//  functions. It is a list of ClassIDs. If the implementation needs to process a
//  command to alter the page item, it should turn off that command's DoNotify()
//  and instead append its classID list to the passed in IClassIDListData*, using
//  TransferAttributesModified().
//  
//========================================================================================

#pragma once
	#ifndef _IAttributePrePost_
	#define _IAttributePrePost_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
	#include "UIDList.h"
	#include "K2Vector.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class IClassIDListData;
	class IDataBase;
	class IFocusCache;
	class ITextModel;
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/**	This interface is optional on the graphic and text attributes.
	If it is present, the apply attribute commands will call PreXxxxApply() before 
	the attribute is applied and PostXxxxApply() afterwards.	
*/
class IAttributePrePost : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IATTRIBUTE_PREPOST_ACTION };
	
		enum ActionType
				{
				/**	kAction_Nothing indicate no action has been taken.
				*/
				kAction_Nothing						= 0,
				/**	kAction_NothingLocalMetaData indicates attribute applied is local rendering object.
				*/
				kAction_NothingLocalMetaData,
				/**	kAction_AddOverride indicate an attribute override has been added.
				*/
				kAction_AddOverride,
				/**	kAction_RemoveOverride indicate an attribute has been removed.
				*/
				kAction_RemoveOverride,
				/**	kAction_ChangeOverride indicate an attribute override has been changed.
				*/
				kAction_ChangeOverride
				};
	//____________________________________________________________________________________
	//	Member Functions
	//____________________________________________________________________________________
	public:
		/**	Apply an action to a list of page items before the attributes are applied.
			@param newAttributeList specifies a list of attributes to be applied.
			@param actionList specifies a list actions corresponding to the attributes being applied.
			@param pageItemList specifies the list of pageitems the attributes wiill be applied.
			@param modifiedAttrClassList specifies the list of attribute classes that have been modified.
			@param origAttributeList specifies the list of original attributes corresponding to the pageitems.
		*/
		virtual void	PreGraphicApply		(K2Vector<IPMUnknown*>* newAttributeList, 
											 K2Vector<ActionType>* actionList, 
											 UIDList* pageItemList, 
											 IClassIDListData* modifiedAttrClassList, 
											 K2Vector<IPMUnknown*>* origAttributeList) = 0;
											 
		/**	Apply an action to a list page items after the attributes are applied.
			@param newAttributeList specifies a list of new attributes applied.
			@param actionList specifies a list actions corresponding to the attributes being applied.
			@param pageItemList specifies the list of pageitems the attributes are applied.
			@param modifiedAttrClassList specifies the list of attribute classes that have been modified.
			@param origAttributeList specifies the list of original attributes corresponding to the pageitems.
		*/
		virtual UIDList*PostGraphicApply	(K2Vector<IPMUnknown*>* newAttributeList, 
											 K2Vector<ActionType>* actionList, 
											 UIDList* pageItemList, 
											 IClassIDListData* modifiedAttrClassList, 
											 K2Vector<IPMUnknown*>* origAttributeList) = 0;

		/**	Apply an action to text before the attribute are applied.
			@param model specifies the text model the attributes are applied.
			@param start specifies the start of text index.
			@param len specifies the length of text.
			@param listOfAll specifies the affected text focus cahce
		*/
		virtual void	PreTextApply		(ITextModel *model, TextIndex start, int32 len, IFocusCache *listOfAll) const = 0;
		/**	Apply an action to text after the attribute are applied.
			@param model specifies the text model the attributes are applied.
			@param start specifies the start of text index.
			@param len specifies the length of text.
			@param listOfAll specifies the affected text focus cahce
		*/
		virtual void	PostTextApply		(ITextModel *model, TextIndex start, int32 len, IFocusCache *listOfAll) const = 0;
	};
	
	DECLARE_BASE_TYPE(IAttributePrePost::ActionType);
		
#endif // _IAttributePrePost_
