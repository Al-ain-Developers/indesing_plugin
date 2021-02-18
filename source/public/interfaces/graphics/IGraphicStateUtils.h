//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IGraphicStateUtils__
#define __IGraphicStateUtils__

#include "GraphicsID.h"
#include "IPMUnknown.h"
#include "Utils.h"

//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
#include "IGraphicAttributeSuite.h"
#include "IGraphicAttrProxySuite.h"

//========================================================================================
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class IClassIDListData;
	class ICommand;
	class IDataBase;
	class IWorkspace;
	class IRenderObjectService;
	class IRenderingObject;
	class IGraphicStateAccessor;
	class ITextModel;
	class ITextFocus;
	class IPMUnknown;
	class ISelectionManager;

	class UIDList;
	class GraphicAttrMessage;
	class GraphicAttrCacheMessage;
	


/** Graphic state related utility functions.
*/
class IGraphicStateUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICSTATEUTILS };


	/**	Process either an Add or Change attribute command that is sent to 
		the graphic state. Depending on the state the attribute, will
		affect defaults or the current selection.
		@param iNewAttribute specifies the new attribute to apply.
		@param iSelectionMgr specifies the selection manager to use.
		@return kSuccess if no errors otherwise returns error code.
	*/
	virtual	ErrorCode ProcessGfxStateApplyAttribute (IPMUnknown* iNewAttribute, ISelectionManager* iSelectionMgr = nil) = 0;
	/**	Process either an Add or Change attribute command that is sent to 
		the graphic state. Depending on the state the attribute, will
		affect defaults or the current selection.
		@param iNewAttribute specifies the new attribute to apply.
		@param iGraphicAttrSuite specifies the graphic attribute suite to use.
		@return kSuccess if no errors otherwise returns error code.
	*/
	virtual	ErrorCode ProcessGfxStateApplyAttribute (IPMUnknown* iNewAttribute, IGraphicAttributeSuite* iGraphicAttrSuite = nil) = 0;

	/**	Apply multiple attributes to the graphic attribute suite.
		Depending on the state the attribute, will affect defaults or the current selection.
		@param iNewAttrList specifies the list of attributes to apply.
		@param iGraphicAttrSuite specifies the graphic attribute suite to use.
		@return kSuccess if no errors otherwise returns error code.
	*/
	virtual	ErrorCode ProcessGfxStateAddMultAttributes (IGraphicStyleAttributeBossList* iNewAttrList, IGraphicAttributeSuite* iGraphicAttrSuite = nil) = 0;
	/**	Remove multiple attributes from the graphic attribute suite.
		Depending on the state the attribute, will affect defaults or the current selection.
		@param pClassList specifies the list of attribute classes to remove.
		@param attributeCount specifies the number of attribute classes in the list.
		@param iGraphicAttrSuite specifies the graphic attribute suite to use.
		@return kSuccess if no errors otherwise returns error code.
	*/
	virtual	ErrorCode ProcessGfxStateRemoveAttributes (ClassID* pClassList, uint16 attributeCount, IGraphicAttributeSuite* iGraphicAttrSuite = nil) = 0;

	/**	Create an apply attribute command that applies "attribute" to the specified page items.
		Optionally, the attribute Pre/Post mechanism can be disabled. And the command's
		DoNotify() can be disabled.	
		@param attribute specifies the attribute to apply.
		@param pTargetItemList specifies the list of page items to apply attribute to.
		@param doPrePost is true if attribute prepost action is enabled.
		@param enableDoNotify is true if command notification is enabled.
		@return the attribute command inteface pointer.
	*/
	virtual ICommand* CreateAttributeCommand (const IPMUnknown *attribute, const UIDList *pTargetItemList, bool16 doPrePost, bool16 enableDoNotify) = 0;

	/**	Create clear attribute override command that removes an attribute of the
		specified class from the specified page items.
		Optionally, the command's DoNotify() can be disabled.	
		@param attributeClassID specifies the attribute class to to remove.
		@param pTargetItemList specifies the list of page items to clear attribute.
		@param enableDoNotify is true if command notification is enabled.
		@return the clear attribute override command inteface pointer.
	*/
	virtual ICommand* CreateGfxClearOverrideCommand (ClassID attributeClassID, const UIDList *targetItemList, bool16 enableDoNotify) = 0;

	/**	Create an apply rendering object attribute command that applies the render UID
		to the specified page items.
		Optionally, the attribute Pre/Post mechanism can be disabled. And the command's
		DoNotify() can be disabled.	
		@param renderObjectClassID specifies the rendering object class to apply.
		@param renderUID specifies the corresponding rendering object UID to apply.
		@param attributeClassID specifies the rendering attribute class.
		@param targetItemList specifies the list of page items to apply attribute to.
		@param doPrePost is true if attribute prepost action is enabled.
		@param enableDoNotify is true if command notification is enabled.
		@return the attribute command inteface pointer.
	*/
	virtual	ICommand* CreateGfxApplyOverrideCommand (ClassID renderObjectClassID, UID renderUID, ClassID attributeClassID, const UIDList&	targetItemList, bool16 doPrePost, bool16 enableDoNotify) = 0;

	/**	Create a swap stroke and fill command for the page items.
		@param targetItemList specifies the page items whose stroke and fill are swapped.
		@return the swap stroke and fill command pointer.
	*/
	virtual	ICommand* CreateGfxSwapStrokeAndFillCommand	(const UIDList&	targetItemList) = 0;
	/**	Create a swap stroke and fill command for the text.
		@param iTextModel specifies text model.
		@param iTextFocus specifies the affected text focus.
		@return the swap stroke and fill command pointer.
	*/
	virtual	ICommand* CreateTextSwapStrokeAndFillCommand (ITextModel* iTextModel, ITextFocus* iTextFocus) = 0;

	/**	Transfer the list of attributes modified in "iSourceCommand" into the
		class list interface, "iDestAttrModified".
		@param iSourceCommand specifies source command.
		@param iDestAttrModified specifies the class list interface receiving the attribute classes.
	*/
	virtual	void TransferAttributesModified	(ICommand *iSourceCommand, IClassIDListData *iDestAttrModified) = 0;

	/**	Append the attribute class to the class list interface, "iDestAttrModified".
		@param attributeModified specifies attribute class ID.
		@param iDestAttrModified specifies the class list interface receiving the attribute class.
	*/
	virtual	void AppendAttributesModified (ClassID attributeModified, IClassIDListData *iDestAttrModified) = 0;

	/**	Apply a list of attributes to the specified page items.
		Only those attributes whose class is in the given class list are applied.
		Optionally, the attribute Pre/Post mechanism can be disabled. And the command's
		DoNotify() can be disabled.	
		@param iNewAttrList specifies the list of attributes to apply.
		@param pClassList specifies the list of attribute classes in iNewAttrList to apply.
		If pClassList is nil, then all attributes are applied.
		@param attrCount specifies the number of attributes in pClassList.
		If attrCount is 0, then all attributes are applied.
		@param targetItemList specifies the list of page items to apply attributes to.
		@param doPrePost is true if attribute prepost action is enabled.
		@param enableDoNotify is true if command notification is enabled.
		@return kSuccess if no errors otherwise returns an error code.
	*/
	virtual ErrorCode ProcessApplyTargetAttributesToPageItems (IGraphicStyleAttributeBossList* iNewAttrList, ClassID* pClassList, int32 attrCount, const UIDList& targetItemList, bool16 doPrePost = kTrue, bool16 enableDoNotify = kTrue) = 0;

	/**	Swap stroke and fill for the selection specified by the graphic attribute suite.
		@param iGraphicAttrSuite specifies graphic attribute suite to use.
		@return kSuccess if no errors otherwise returns an error code.
	*/
	virtual	ErrorCode ProcessSwapStrokeAndFillCmdSequence (IGraphicAttributeSuite* iGraphicAttrSuite = nil) = 0;

	/**	Swap default stroke and fill for the selection specified by the graphic attribute suite.
		@param iGraphicAttrSuite specifies graphic attribute suite to use.
		@return kSuccess if no errors otherwise returns an error code.
	*/
	virtual	ErrorCode ProcessDefaultStrokeAndFillCmdSequence (IGraphicAttributeSuite* = nil) = 0;

	/**	Taggle stroke and fill proxy.
		@return kSuccess if no errors otherwise returns an error code.
	*/
	virtual ErrorCode ProcessToggleStrokeAndFillCmd	 (void) = 0;

	/**	Update rendering data in the given graphic state.	
		The render data to be updated is specified by (a) stroke or fill
		and (b) by render UID. The change will be forwarded to the Graphic State 
		Rendering Objects if necessary.
		@param renderObjectClassID specifies rendering class to update.
		@param renderUID specifies rendering UID.
		@param isFill is true if updating the fill proxy.
		@param iGfxAttrSuite specifies graphic attribute suite.
		@return kSuccess if no errors otherwise returns an error code.
	*/
	virtual ErrorCode ProcessUpdateDefinitionRenderDataCmdSequence
		(
		ClassID 							renderObjectClassID, 
		UID									renderUID, 
		bool16 								isFill,
		IGraphicAttributeSuite*				iGfxAttrSuite = nil
		) = 0;

	//________________________________________________________________________________________
	//	Graphic State object accessors
	//________________________________________________________________________________________
	/**	Return the active graphic state object pointer.	
		@param requestedIID specifies requested interface IID.
		@param iActiveContext specifies the active context.
		@return an IPMUnknown pointer to the requested interface IID.
	*/
	virtual	IPMUnknown*				QueryActiveGraphicState				(const PMIID& requestedIID = IID_IUNKNOWN, IActiveContext* iActiveContext = nil) = 0;
	/**	Return the graphic state object pointer for the specified database.	
		@param iDataBase specifies the database for the graphic state object.
		@param requestedIID specifies requested interface IID.
		@return an IPMUnknown pointer to the requested interface IID.
	*/
	virtual	IPMUnknown*				QueryGraphicState					(IDataBase* iDataBase, const PMIID& requestedIID = IID_IUNKNOWN) = 0;
	/**	Return the workspace of the specified database.	
		@param iDataBase specifies the database for the graphic state object.
		@return IWorkspace for the specified database.
	*/
	virtual	IWorkspace* 			QueryDataBaseWorkspace				(IDataBase* iDataBase) = 0;

	/**	This function is used by the graphic state and its commands to modify the 
		selection list as necessary for the processing of the selection.
			(a)	Remove any page item that does not have a GfxSelection interface
			(b)	Expand all containers so their children are in the returned list
			(c) Filter out any page items that do _not_ support "interfaceID" 
				(optional)
			(d)	Any duplicates are removed from the list
		@param pItemList specifies the page items from which to create the flattened list.
		@param interestedIID specifies the interface IID to collect.
		@param onlyIncludeGfxStateSelection is true it will only include items that
		have an IGraphicStateSelection interface.
	*/
	virtual UIDList* CreateFlattenedPageItemList (const UIDList* pItemList, const PMIID& interestedIID, bool16 onlyIncludeGfxStateSelection) = 0;
	
	//________________________________________________________________________________________
	//	Is stroke or fill active in the toolbox proxy. These accessors are a shortcut
	//	for querying the preference directly from the session workspace.
	//________________________________________________________________________________________
	/**	Return true if stroke proxy is active.
	*/
	virtual bool16 IsStrokeActive (void) = 0;
	/**	Return true if fill proxy is active.
	*/
	virtual bool16 IsFillActive (void) = 0;
	
	/**	Query the graphic attribute suite from the given selection manager or the
		active selection manager is ISelectionManager is nil.
		@param iSelectionMgr specifies the selection manager to use.
		@return the graphic suite interface pointer.
	*/
	virtual IGraphicAttributeSuite* QueryActiveGraphicAttrSuite	(ISelectionManager* iSelectionMgr = nil) = 0;

	/**	Use the state of the stroke/fill proxy to copy either the stroke or
		fill render data from the specified target into the render object's
		render data object.
		This is called when the underlying definition has changed and the Render
		Objects Interface needs to be updated.
		@param renderObjectClassID is the rendering class to update. If this is kInvalidClass,
		the target's current setting is used.
		@param iGfxAttrSuite specifies the affected graphic attribute suite.
		@param iGfxStateRenderObjects specifies the corresponding graphic state render objects.
		@param doNotify is true if graphic state should broadcast changed message.
	*/
	virtual void UpdateGfxStateRenderObjectsRenderData
		(
		ClassID								renderObjectClassID,
		IGraphicAttributeSuite*				iGfxAttrSuite,
		IGraphicStateRenderObjects*			iGfxStateRenderObjects,
		bool16								doNotify
		) = 0;

	/**	Returns a list of the installed rendering types.
	*/
	virtual const K2Vector<ClassID>* GetInstalledRenderingTypes (void) = 0;

	//________________________________________________________________________________________
	//	DESCR:		Proxy utilities
	//________________________________________________________________________________________

	/**	Return whether or not the specified proxy type can be swapped.
		@param proxyType is the proxy type.
		@return true if specified proxy type can be swapped.
	*/
	virtual bool16 CanSwapActiveProxyType(IGraphicAttrProxySuite::ActiveProxyType proxyType) = 0;
	/**	Swap the specified proxy type as active proxy type.
		@param proxyType is the proxy type.
	*/
	virtual void	  SwapActiveProxyType(IGraphicAttrProxySuite::ActiveProxyType proxyType) = 0;
	/**	Returns the active proxy type.
	*/
	virtual IGraphicAttrProxySuite::ActiveProxyType GetActiveProxyType() = 0;


	//________________________________________________________________________________________
	//	DESCR:		Graphic Attr message utilities
	//________________________________________________________________________________________
	/**	Create a graphic attribute suite message based of the given data.
		@param messageType is the attribute message type.
		@see also IGraphicAttrMessage.h
		@param pClassList s a list of affected class ID. These are attribute class IDs
		or rendering class IDs.
		@return a graphic attribute suite message.
	*/
	virtual GraphicAttrMessage*		CreateGraphicAttrMessage 
		(
		const IGraphicAttrMessage::MessageType& messageID,
		const K2Vector<ClassID>& pClassList
		) = 0;
		
	/**	Create a graphic attribute cache message based of the given data.
		@param messageID is the PMIID of the suite sending the message.
		@param messageType is the cache message type. @see also IGraphicAttrMessage.h
		@param pClassList s a list of affected class ID. These are attribute class IDs
		or rendering class IDs.
		@return a graphic attribute cache message.
	*/
	virtual GraphicAttrCacheMessage*	CreateGraphicAttrCacheMessage 
		(
		const PMIID&							messageID,
		const IGraphicAttrMessage::MessageType&	messageType,
		const K2Vector<ClassID>*				attrClassList
		) = 0;


	//________________________________________________________________________________________
	//	Graphic State Rendering object accessors
	//________________________________________________________________________________________
	/**	Return the rendering object service interface for the given rendering class ID.
		@param renderClassID specifies the rendering class ID.
		@return the IRenderObjectService* for the rendering class ID.
	*/
	virtual	IRenderObjectService*	QueryRenderObjectService			(ClassID renderClassID) = 0;
	/**	Create a temporary (in-memory) rendering object for the given rendering class ID.
		There is no database or UID associated with a temporary rendering object.
		@param renderClassID specifies the rendering class ID.
		@param iSourceRenderObject specifies the source rendering object to use for constructing
		the in-memory rendering object. If this is nil, default values are used.
		@return the IRenderingObject* for the rendering class ID.
	*/
	virtual	IRenderingObject*		CreateTemporaryRenderObject			(ClassID, const IRenderingObject* iSourceRenderObject = nil) = 0;


};


#endif	// __IGraphicStateUtils__
