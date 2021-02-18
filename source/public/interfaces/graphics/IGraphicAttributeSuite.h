//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttributeSuite.h $
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
	#ifndef _IGraphicAttributeSuite_
	#define _IGraphicAttributeSuite_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
	#include "K2Vector.h"
	
	#include "IGraphicAttrMessage.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
class ICommand;
class IGraphicStyleAttributeBossList;
class IGraphicStateRenderObjects;

/** This is a general graphic attribute suite interface for getting and setting of
	graphic attributes. A graphic attribute object must support the interface,
	IGraphicAttributeInfo. It usually has a persistent data interface as well. Currently these
	basic data interfaces are provided:
	@see IGraphicAttrBoolean.h for a boolean data interface.
	@see IGraphicAttrInt16.h for a int16 data interface.
	@see IGraphicAttrInt32.h for a int32 data interface.
	@see IGraphicAttrClassID.h for a ClassID data interface.
	@see IGraphicAttrRealNumber.h for a PMReal data interface.
	@see IGraphicAttrPoint.h for a PMPoint data interface.
	@see IGraphicAttributeInfo.h for information on IGraphicAttributeInfo.
	@see GraphicStylesID.h for a list of required graphic attribute classes supported by InDesign.
	
	Other attribute classes supported by InDesign are defined in
	GradientFillID.h, XPID.h, and InstStrokeFillID.h
	New attribute classes and attribute data interfaces can be added.
*/
class IGraphicAttributeSuite : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICATTRIBUTESUITE };

	//____________________________________________________________________________________
	//	Attribute Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of unique attribute count of the specified attribute class in the selection.
		*/
		virtual uint16 				GetAttributeCount			(ClassID attrClassID) = 0;

		/** Returns the number of nth attribute value of the specified attribute class specified by whichAttribute in the selection.
		*/
		virtual int16				GetAttributeValueCount 		(ClassID attrClassID, uint32 whichAttribute) = 0;
		
		/** Query the nth attribute for the specified IID in the selection.
			@param whichAttribute the nth attribute index starting from 0.
			@param attrClassID the attribute class ID.
			@param interfaceID the requested interface IID on the attribute boss.
			@return the requested Interface pointer (as IPMUnknown*) or nil.
			The result may be cast to the 'type' identified by IID.
		*/
		virtual const IPMUnknown*	QueryAttribute				(uint32 whichAttribute, ClassID attrClassID, const PMIID& interfaceID = IID_IUNKNOWN) = 0;

		/** Create a copy of the nth attribute and returns the specified IID in the selection.
			@param whichAttribute the nth attribute index starting from 0.
			@param attrClassID the attribute class ID.
			@param interfaceID the requested interface IID on the attribute boss.
			@return the requested Interface pointer (as IPMUnknown*) or nil.
			The result may be cast to the 'type' identified by IID.
		*/
		virtual IPMUnknown*			CreateAttributeCopy			(uint32 whichAttribute, ClassID attrClassID, const PMIID& = IID_IUNKNOWN) = 0;
		
		/** Add the specified attribute, "iNewAttribute", to the attribute boss list in
			the current selection.
			@param iNewAttribute the attribute to add.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			AddAttribute				(const IPMUnknown* iNewAttribute) = 0;

		/** Copy the content of the specified attribute, "iNewAttribute", into the nth attribute of the same
			attribute class in the current selection.
			@param whichAttribute the nth attribute index starting from 0.
			@param iNewAttribute the attribute to copy.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			CopyIntoAttribute			(uint32 whichAttribute, IPMUnknown* iNewAttribute) = 0;

		/** Remove all attributes of attribute classID in the current selection.
			@param attrClassID the attribute class ID.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			RemoveAttribute				(ClassID attrClassID) = 0;

		/** Remove all attributes of the specified attribute classes in the current selection.
			@param pAttrClassList the list of attribute class IDs.
			@param count the number attribute classes in pAttrClassList.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			RemoveAllAttributes			(ClassID* pAttrClassList, uint16 count) = 0;

		/** Add the attributes in the list, "iAttrList", to the attribute boss list in
			the current selection.
			@param iAttrList the list of attributes to add.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			AddMultAttributes			(IGraphicStyleAttributeBossList* iAttrList) = 0;

		/** Returns a copy of the list of attributes in the current selection.
			@return a copy of the current attribute list.
		*/
		virtual IGraphicStyleAttributeBossList* CreateAttributeListCopy		(void) = 0;

		/** Swap stroke and fill rendering attributes in the current selection.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			SwapStrokeAndFill			(void) = 0;
	//____________________________________________________________________________________
	//	Render Object Utilities 
	//____________________________________________________________________________________
	public:

		// The following two methods update data in the graphic definition

		/** Change the stroke rendering attributes in the current selection to the specified rendering class and UID.
			@param renderingClass the stroke rendering class.
			@param renderingUID the  rendering UID.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			ChangeStrokeRenderObject		(ClassID renderingClass, UID renderingUID) = 0;

		/** Change the fill rendering attributes in the current selection to the specified rendering class and UID.
			@param renderingClass the fill rendering class.
			@param renderingUID the rendering UID.
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			ChangeFillRenderObject			(ClassID renderingClass, UID renderingUID) = 0;

		/** Returns the fill renderingClass rendering UID of the specified rendering class in the current selection.
			@param renderingClass the fill rendering class.
			@return the renderingClass rendering UID of the specified rendering class
		*/
		virtual UID					GetFillRenderObjectUID			(ClassID) = 0;

		/** Returns the stroke rendering UID of the specified rendering class in the current selection.
			@param renderingClass the fill rendering class.
			@return the stroke rendering UID of the specified rendering class
		*/
		virtual UID					GetStrokeRenderObjectUID		(ClassID) = 0;

		/** Returns kTrue if the specified fill rendering class is indeterminant in the current selection.
			@param renderingClass the fill rendering class.
			@return kTrue if the specified fill rendering class is indeterminant
		*/
		virtual bool16				IsFillRenderObjectIndeterminant		(ClassID) = 0;

		/** Returns kTrue if the specified stroke rendering class is indeterminant in the current selection.
			@param renderingClass the fill rendering class.
			@return kTrue if the specified stroke rendering class is indeterminant
		*/
		virtual bool16				IsStrokeRenderObjectIndeterminant	(ClassID) = 0;
				
	//____________________________________________________________________________________
	//	Other Utilities 
	//____________________________________________________________________________________
	public:
		/** Apply the specified rendering class and UID to specified renderint attribute in the current selection.
			@param renderingClass the rendering class.
			@param renderingUID the rendering UID.
			@param renderingAttrClass the rendering rendering class
			(kGraphicStyleFillRenderingAttrBoss or kGraphicStyleStrokeRenderingAttrBoss).
			@return kSuccess if successful, else an error code
		*/
		virtual ErrorCode			ApplyRenderUIDToSelection		(ClassID renderingClass, UID renderingUID, ClassID renderingAttrClass) = 0;

		/** Returns the active rendering class in the current selection.
			@return active rendering ClassID in the current selection
		*/
		virtual ClassID				GetCurrentRenderObjectClass		(void) = 0;

		/** Returns the current fill rendering class in the current selection.
			@return fill rendering ClassID in the current selection
		*/
		virtual ClassID				GetFillClass					(void) = 0;

		/** Returns the current stroke rendering class in the current selection.
			@return stroke rendering ClassID in the current selection
		*/
		virtual ClassID				GetStrokeClass					(void) = 0;

		/** Returns kTrue if the specified attribute class is enabled in the current selection.
			@param attributeClass the attribute class.
			@return kTrue if the specified attribute class is enabled
		*/
		virtual bool16				IsAttributeEnabled				(ClassID attributeClass) = 0;
		
		/** Returns kTrue if the specified line type is enabled in the current selection.
			@param attributeClass the ClassID of the line type.
			@return kTrue if the specified line type is enabled
		*/
		virtual bool16				IsLineTypeEnabled				(ClassID attributeClass) = 0;

	//____________________________________________________________________________________
	//	Directly update graphic states rendering objects
	//	CSB should not use.
	//____________________________________________________________________________________
	public:

		/** Directly update the graphic state IGraphicStateRenderObjects interface to the current proxy state
			in the current selection.
		*/
		virtual void				UpdateRenderObjectsToProxyState	(void) = 0;
		
	//____________________________________________________________________________________
	//	Get current disabled attribute class IDs and rendering types in the list.
	//____________________________________________________________________________________

		/** Returns a list of disabled attributes in the current selection.
			@param pDisabledAttrClassList list of disabled attribute class list.
		*/
		virtual void				GetDisabledAttributesList		(K2Vector<ClassID>* pDisabledAttrClassList) = 0;

		/** Returns a list of disabled rendering types in the current selection.
			@param pDisabledFillRenderClassList list of disabled fill rendering class list.
			@param pDisabledStrokeRenderClassList list of disabled stroke rendering list.
		*/
		virtual void				GetDisabledRenderingTypesList	(K2Vector<ClassID>* pDisabledFillRenderClassList, K2Vector<ClassID>* pDisabledStrokeRenderClassList) = 0;
	};

#endif // _IGraphicAttributeSuite_
