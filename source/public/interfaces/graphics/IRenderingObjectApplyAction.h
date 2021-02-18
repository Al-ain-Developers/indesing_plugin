//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRenderingObjectApplyAction.h $
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
	#ifndef _RenderingObjectApplyAction_
	#define _RenderingObjectApplyAction_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "IAttributePrePost.h"
	#include "IPersistUIDData.h"
	#include "GraphicStylesID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class IClassIDListData;
	class ITextModel;
	class IFocusCache;
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/**	This interface is required on rendering objects. The rendering attribute's 
	PrePost interface will call PreGraphicApply() before the attribute is applied
	and PostGraphicApply() afterwards. If the original and new rendering classIDs
	are different it will call CleanUpPageItemAttr() in PostGraphicApply().

	The SwapGraphicStrokeAndFill function is called anytime that a page item's
	stroke and fill need to be swapped and the rendering object _class_ is used
	for one or both of the rendering objects involved.
	
	The IClassIDListData* is used to notify the graphic state of the attributes
	that were changed within the Pre and Post member functions. It is a list of 
	ClassIDs. The implementations should check to see the class they are modifying
	is already list (using GetIndex()). If it is not currently listed use 
	Append(modifiedClassID) for the attribute's classID.
*/

class IRenderingObjectApplyAction : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Member Functions
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IRENDERINGOBJECTAPPLYACTION };

		/**	Apply whatever updates are neccessary before rendering attribute is applied.
			@param newAttr is the new rendering attribute that will be applied.
			@param attrActionType specifies the attribute action type.
			@see also IAttributePrePost.h
			@param pageItem specifies the page item UIDRef that the attribute will be applied to.
			@param origRendObjClassID is the corresponding orginal rendering type for the attribute.
			@param newRendObjClassID is the corresponding new rendering type for the attribute.
		*/
		virtual void	PreGraphicApply		(IPMUnknown* newAttr, IAttributePrePost::ActionType attrActionType, 
											UIDRef pageItem, IClassIDListData*, IPMUnknown* origAttr, 
											ClassID origRendObjClassID, ClassID newRendObjClassID) const = 0;
		/**	Apply whatever updates are neccessary after rendering attribute is applied.
			@param newAttr is the new rendering attribute applied.
			@param attrActionType specifies the attribute action type.
			@see also IAttributePrePost.h
			@param pageItem specifies the page item UIDRef that the attribute is applied to.
			@param origRendObjClassID is the corresponding orginal rendering type for the attribute.
			@param newRendObjClassID is the corresponding new rendering type for the attribute.
		*/
		virtual void	PostGraphicApply	(IPMUnknown* newAttr, IAttributePrePost::ActionType, 
											UIDRef pageItem, IClassIDListData*, IPMUnknown* origAttr, 
											ClassID origRendObjClassID, ClassID newRendObjClassID) const = 0;
		
		/**	This is called only if original attributes exist and are different from the 
			ones replacing them. This is when the rendering object can clean up those
			attributes on the page item that are no longer needed.
			@param origAttrs specifies the list of original attributes. This should be all of the
			same attribute class and same rendering class.
			@param newAttrs specifies the list of new attributes. This should be all of the
			same attribute class and same rendering class.
			@param iClassIDList contains a list of attribute class ID that were modified.
		*/
		virtual	void	CleanUpPageItemAttr	(K2Vector<IPMUnknown*>* origAttrs, K2Vector<IPMUnknown*>* newAttrs, 
											UIDList* pageItemList, IClassIDListData* iClassIDList) = 0;			
		/**	Apply whatever updates are neccessary before rendering attribute is applied to text.
			@param model is the affected text model.
			@param start specifies starting index in the text model.
			@param len specifies length of the text affected in the text model.
			@param textRenderAttrClass specifies the text rendering attribute class being applied.
			@param listOfAll is the text focus cache.
		*/
		virtual void	PreTextApply		(ITextModel *model, TextIndex start, int32 len, ClassID textRenderAttrClass, IFocusCache *listOfAll) const = 0;
		/**	Apply whatever updates are neccessary after rendering attribute is applied to text.
			@param model is the affected text model.
			@param start specifies starting index in the text model.
			@param len specifies length of the text affected in the text model.
			@param textRenderAttrClass specifies the text rendering attribute class being applied.
			@param listOfAll is the text focus cache.
		*/
		virtual void	PostTextApply		(ITextModel *model, TextIndex start, int32 len, ClassID textRenderAttrClass, IFocusCache *listOfAll) const = 0;
	
		/**	Called when the stroke and fill rendering objects are swapped. The rendering
			object must make sure the page item is in the correct state. One or both of
			the rendering objects may be of the classID of the implementor. Any attributes
			that are added/changed/deleted must be added to the "iAttributesModified" list.
			If the stroke and fill rendering classes are the same this function will only
			be called once. It is called twice only if the rendering classes are different.
			@param iFillRenderingObject is the fill rendering object to swap with.
			@param fillRenderingClassID is the fill rendering class ID corresponding to iFillrenderingObject.
			@param iStrokeRenderingObject is the stroke rendering object to swap with.
			@param strokeRenderingClassID is the stroke rendering class ID corresponding to iStrokeRenderingObject.
			@param pageItem specifies the page item UIDRef whose fill and stroke are being swapped.
			@param iAttributesModified specifies the list of attribute modified.
		*/
		virtual void 	SwapGraphicStrokeAndFill	(IPMUnknown*		iFillRenderingObject, 
													 ClassID			fillRenderingClassID, 
													 IPMUnknown*		iStrokeRenderingObject, 
													 ClassID			strokeRenderingClassID, 
													 UIDRef				pageItem, 
													 IClassIDListData*	iAttributesModified) const = 0;
	};
			
#endif
		// _RenderingObjectApplyAction_
