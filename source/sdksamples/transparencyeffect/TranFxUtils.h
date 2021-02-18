//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxUtils.h $
//  
//  Owner: Adobe Developer Technologies
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

//===========================
//  Interface includes:
//===========================

#include "IXPManager.h"

// Project includes:
// None

// Forward declarations
class PMReal;
class UIDList;

/** Facade that wraps the commands needed to manage this
	plug-in's adornment and the custom graphic attributes 
	that control it.

	The implementation techniques shown in this class allow
	client suites to be called from a previewable dialog.
	See the TransparencyEffectUI plug-in.

	Since all access to the custom graphic attributes that
	control this plug-in's transparency effect funnel through
	this class, their default value get applied here. 
	This plug-in's graphic attributes are only added to 
	a page item when the user overrides their value using the
	UI i.e. the custom graphic attributes are not applied to all 
	new page items, they are only applied as required to 
	plug-in's that have the effect.

	
	@ingroup transparencyeffect
	@see kTranFxAdornmentBoss
	@see kTranFxOffsetXAttrBoss
	@see kTranFxOffsetYAttrBoss
	@see kTranFxUseBlackAsOpaqueAttrBoss
	@see kTranFxUseAlphaAttrBoss
	@see kTranFxUseBlurAttrBoss
	@see kAddPageItemAdornmentCmdBoss
	@see kRemovePageItemAdornmentCmdBoss
	@see IGraphicStateUtils
	@see kXPItemXPPrePostCmdBoss
 */
class TranFxUtils
{
public:
	/** Constructor.
	 */
	TranFxUtils() {}

	/** Destructor.
	 */
	virtual     ~TranFxUtils() {}

public:
	/** Enumeration indicating whether all the selected objects
		have no value, a common value or a mixed number of different
		values for a given attribute.
	 */
	typedef enum
	{
		eNoValue, eCommonValue, eMixedValue
	} AttrState;

public:
	/** Indicate whether the given objects have kTranFxAdornmentBoss applied.
		@param itemList IN list of objects to be checked.
		@return eCommonValue all objects have the adornment, eMixedValue some objects have the adornment, eNoValue none of the objects have the adornment.
	 */
	AttrState       HasAdornment(const UIDList& itemList);

	/** Indicate state of kTranFxOffsetXAttrBoss value across the given objects.
		@param itemList IN list of objects to be checked.
		@param value OUT x offset  (default value 7.0 points).
		@return enum indicating state of the attribute value.
	 */
	AttrState       HasXOffset(const UIDList& itemList, PMReal& value);

	/** Indicate state of kTranFxOffsetYAttrBoss value across the given objects.
		@param itemList IN list of objects to be checked.
		@param value OUT y offset  (default value 7.0 points).
		@return enum indicating state of the attribute value.
	 */
	AttrState       HasYOffset(const UIDList& itemList, PMReal& value);

	/** Indicate state of kTranFxUseBlackAsOpaqueAttrBoss value across the given objects.
		@param itemList IN list of objects to be checked.
		@param value OUT kTrue if black pixels in the page item should be opaque in the effect, kFalse if transparent (default value kTrue).
		@return enum indicating state of the attribute value.
	 */
	AttrState       HasUseBlackAsOpaque(const UIDList& itemList, bool16& value);

	/** Indicate state of kTranFxUseAlphaAttrBoss value across the given objects.
		@param itemList IN list of objects to be checked.
		@param value OUT kTrue if alpha channel should be used, kFalse if not (default value kTrue).
		@return enum indicating state of the attribute value.
	 */
	AttrState       HasUseAlpha(const UIDList& itemList, bool16& value);

	/** Indicate state of kTranFxUseBlurAttrBoss value across the given objects.
		@param itemList IN list of objects to be checked.
		@param value OUT kTrue if blur should be applied and intensity reduced, kFalse if not (default value kTrue).
		@return enum indicating state of the attribute value.
	 */
	AttrState       HasUseBlur(const UIDList& itemList, bool16& value);

	/** Return kTrue if adornment can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if adornment can be applied, kFalse otherwise.
	 */
	bool16  CanApplyAdornment(const UIDList& itemList) const;

	/**	Return kTrue if attribute can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if attribute can be applied, kFalse otherwise.
	 */
	bool16  CanApplyXOffset(const UIDList& itemList) const;

	/** Return kTrue if attribute can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if attribute can be applied, kFalse otherwise.
	 */
	bool16  CanApplyYOffset(const UIDList& itemList) const; 

	/** Return kTrue if attribute can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if attribute can be applied, kFalse otherwise.
	 */
	bool16  CanApplyUseBlackAsOpaque(const UIDList& itemList) const;  

	/** Return kTrue if attribute can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if attribute can be applied, kFalse otherwise.
	 */
	bool16  CanApplyUseAlpha(const UIDList& itemList) const;    

	/** Return kTrue if attribute can be applied, kFalse otherwise.
		@param itemList list of objects to be checked.
		@return kTrue if attribute can be applied, kFalse otherwise.
	 */
	bool16  CanApplyUseBlur(const UIDList& itemList) const; 

	/** Add or remove kTranFxAdornmentBoss.
		@param itemList IN references the objects to be affected.
		@param isAdd IN kTrue to add adornment, kFalse to remove.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyAdornment(const UIDList& itemList, const bool16 isAdd);

	/** Change the value of kTranFxOffsetXAttrBoss.
		@param itemList IN references the objects to be affected.
		@param value IN the value to be applied.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyXOffset(const UIDList& itemList, const PMReal& value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change the value of kTranFxOffsetYAttrBoss.
		@param itemList IN references the objects to be affected.
		@param value IN the value to be applied.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyYOffset(const UIDList& itemList, const PMReal& value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change the value of kTranFxUseBlackAsOpaqueAttrBoss.
		@param itemList IN references the objects to be affected.
		@param value IN the value to be applied.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyUseBlackAsOpaque(const UIDList& itemList, const bool16 value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change the value of kTranFxUseAlphaAttrBoss.
		@param itemList IN references the objects to be affected.
		@param value IN the value to be applied.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyUseAlpha(const UIDList& itemList, const bool16 value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change the value of kTranFxUseBlurAttrBoss.
		@param itemList IN references the objects to be affected.
		@param value IN the value to be applied.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyUseBlur(const UIDList& itemList, const bool16 value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

private:
	/** Add adornment kTranFxAdornmentBoss.
		@param itemList IN references the objects to be affected.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   AddAdornment(const UIDList& itemList);

	/** Remove adornment kTranFxAdornmentBoss.
		@param itemList IN references the objects to be affected.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   RemoveAdornment(const UIDList& itemList);

	/** Trick to support usage of this facade from a previewable dialog.
		This trick returns the adornment state of each item to
		that which existed when the dialog was entered. It 
		forces any preceeding add or remove adornment command to 
		undo. To pull this trick our instances of add, remove and 
		null commands all share a common "creator id" 
		(see ICommand::SetCreatorID)
		@param itemList IN references the objects to be affected.
		@return kSuccess on success, other ErrorCode otherwise.
		@see ICommand::SetCreatorID
	 */
	//ErrorCode   UndoAdornment(const UIDList& itemList);

	/** Informs transparency about change to transparency state. A command
		kXPItemXPPrePostCmdBoss is used so that on undo and redo
		transparency gets updated.
		@param itemList IN references the objects to be affected.
		@param isPre IN set to kTrue before adding the adornment, kFalse otherwise.
		@param invalidateOnDo IN see IXPItemXPPrePostCmdData.
		@param changeTypeOnDo IN see IXPItemXPPrePostCmdData.
		@param invalidateOnUndo IN see IXPItemXPPrePostCmdData.
		@param changeTypeOnUndo IN see IXPItemXPPrePostCmdData.
		@see kXPItemXPPrePostCmdBoss.
	 */
	void        Inval(const UIDList& itemList, bool16 isPre, bool32 invalidateOnDo = kTrue, IXPManager::XPChangeType changeTypeOnDo = IXPManager::kXPC_NoChange, bool32 invalidateOnUndo  = kTrue, IXPManager::XPChangeType changeTypeOnUndo  = IXPManager::kXPC_NoChange);

	/** Indicate state of given int32 attribute value across the given objects.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be checked.
		@param value OUT value of attribute if a common value applies to all objects.
		@return enum indicating state of the attribute value.
	 */
	AttrState   HasInt32Attribute(const UIDList& itemList, const ClassID& attrClassID, int32& value);

	/** Indicate state of given bool16 attribute value across the given objects.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be checked.
		@param value OUT value of attribute if a common value applies to all objects.
		@return enum indicating state of the attribute value.
	 */
	AttrState   HasBooleanAttribute(const UIDList& itemList, const ClassID& attrClassID, bool16& value);

	/** Indicate state of given PMReal attribute value across the given objects.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be checked.
		@param value OUT value of attribute if a common value applies to all objects.
		@return enum indicating state of the attribute value.
	 */
	AttrState   HasPMRealAttribute(const UIDList& itemList, const ClassID& attrClassID, PMReal& value);

	/** Change value of given int32 attribute.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be affected.
		@param value IN desired value of attribute.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyInt32Attribute(const UIDList& itemList, const ClassID& attrClassID, const int32 value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change value of given bool16 attribute.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be affected.
		@param value IN desired value of attribute.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyBooleanAttribute(const UIDList& itemList, const ClassID& attrClassID, const bool16 value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Change value of given PMReal attribute.
		@param itemList IN list of objects to be affected.
		@param attrClassID IN identifies attribute to be affected.
		@param value IN desired value of attribute.
		@param doPrePost IN see IGraphicStateUtils::CreateAttributeCommand.
		@param enableDoNotify IN see IGraphicStateUtils::CreateAttributeCommand.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode   ApplyPMRealAttribute(const UIDList& itemList, const ClassID& attrClassID, const PMReal& value, bool16 doPrePost=kFalse, bool16 enableDoNotify=kFalse);

	/** Check the given items to see if the effect can be applied, currently you
		can't apply the effect to guides.
		@param itemList list of objects to be checked.
		@return kTrue if effect can be applied, kFalse otherwise.
	 */
	bool16      CanApplyEffect(const UIDList& itemList) const;
};

// End, TranFxUtils.h
