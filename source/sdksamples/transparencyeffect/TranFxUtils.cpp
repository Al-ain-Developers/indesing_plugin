//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxUtils.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IGraphicAttrRealNumber.h"
#include "IGraphicAttrInt32.h"
#include "IGraphicStateUtils.h"
#include "IGraphicAttrBoolean.h"
#include "IClassIDData.h"
#include "IPageItemAdornmentList.h"
#include "IGraphicStyleDescriptor.h"
#include "IXPItemXPPrePostCmdData.h"
#include "IPageItemTypeUtils.h"

// General includes:
#include "widgetid.h" // kNullCmdBoss 
#include "Utils.h"

// Project includes:
#include "TranFxID.h"
#include "TranFxUtils.h"

// Default attribute values. All access to attribute values funnels through
// this utility so we apply default values here.
const PMReal kTranFxXOffsetDefault = 7.0;
const PMReal kTranFxYOffsetDefault = 7.0;
const bool16 kTranFxUseBlackAsOpaqueDefault = kTrue;
const bool16 kTranFxUseAlphaDefault = kTrue;
const bool16 kTranFxUseBlurDefault = kTrue;

/*
*/
TranFxUtils::AttrState TranFxUtils::HasAdornment(const UIDList& itemList)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasAdornment-->In\n");   
	AttrState result = eNoValue;
	int32 adornmentCount  = 0;
	do
	{
		// Count the items that have the adornment.
		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(itemList.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
			ASSERT(pageItemAdornmentList);
			if(!pageItemAdornmentList) {
				continue;
			}
			if (pageItemAdornmentList->HasAdornment(kTranFxAdornmentBoss))
			{
				adornmentCount++;
			}
		}
		if (adornmentCount == itemList.Length())
		{
			// All items have the adornment
			result = eCommonValue;
		}
		else if (adornmentCount > 0)
		{
			result = eMixedValue;
		}

	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasAdornment-->Out result=%d, adornmentCount=%d\n",
			  result,
			  adornmentCount);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasXOffset(const UIDList& itemList, PMReal& value)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasXOffset-->In\n");
	value = kTranFxXOffsetDefault; // set a default return value
	TranFxUtils::AttrState result = this->HasPMRealAttribute(itemList, kTranFxOffsetXAttrBoss, value);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasXOffset-->Out result=%d, value=%f\n",
			  result,
			  ::ToDouble(value));
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasYOffset(const UIDList& itemList, PMReal& value)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasYOffset-->In\n");
	value = kTranFxYOffsetDefault; // set a default return value	
	TranFxUtils::AttrState result = this->HasPMRealAttribute(itemList, kTranFxOffsetYAttrBoss, value);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasYOffset-->Out result=%d, value=%f\n",
			  result,
			  ::ToDouble(value));
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasUseBlackAsOpaque(const UIDList& itemList, bool16& value)
{
	value = kTranFxUseBlackAsOpaqueDefault; // set a default return value
	TranFxUtils::AttrState result = this->HasBooleanAttribute(itemList, kTranFxUseBlackAsOpaqueAttrBoss, value);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasUseAlpha(const UIDList& itemList, bool16& value)
{
	value = kTranFxUseAlphaDefault;	// set a default return value
	TranFxUtils::AttrState result = this->HasBooleanAttribute(itemList, kTranFxUseAlphaAttrBoss, value);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasUseBlur(const UIDList& itemList, bool16& value)
{
	value = kTranFxUseBlurDefault; // set a default return value
	TranFxUtils::AttrState result = this->HasBooleanAttribute(itemList, kTranFxUseBlurAttrBoss, value);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasPMRealAttribute(const UIDList& itemList, 
													   const ClassID& attrClassID, 
													   PMReal& value)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasPMRealAttribute-->In\n");
	TranFxUtils::AttrState result = eNoValue;
	int32 attributeCount = 0;
	do
	{
		PMReal targetValue;

		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IGraphicStyleDescriptor> graphicStyleDescriptor(
																		itemList.GetRef(i), UseDefaultIID ());
			if (graphicStyleDescriptor == nil)
			{
				break;
			}
			InterfacePtr<IGraphicAttrRealNumber> attr (
													  (IGraphicAttrRealNumber*)graphicStyleDescriptor->QueryAttribute (
																													  attrClassID, 
																													  IID_IGRAPHICATTR_REALNUMBER));
			if (attr == nil)
			{
				continue;
			}
			if (attributeCount == 0)
			{
				targetValue = attr->GetRealNumber();
			}
			else if (targetValue != attr->GetRealNumber())
			{
				break;
			}
			attributeCount++;
		}

		if (attributeCount == itemList.Length())
		{
			result = eCommonValue;
			value = targetValue;
		}
		else if (attributeCount > 0)
		{
			result = eMixedValue;
		}
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasPMRealAttribute-->Out result=%d, value=%f, attributeCount=%d\n",
			  result,
			  ::ToDouble(value),
			  attributeCount);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasBooleanAttribute(const UIDList& itemList, 
														const ClassID& attrClassID, 
														bool16& value)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasBooleanAttribute-->In attrClassID=0x%x\n", attrClassID.Get());    
	TranFxUtils::AttrState result = eNoValue;
	int32 attributeCount = 0;
	do
	{
		bool16 targetValue = kFalse;	// add the initialization value

		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IGraphicStyleDescriptor> graphicStyleDescriptor(itemList.GetRef(i), UseDefaultIID ());
			if (graphicStyleDescriptor == nil)
			{
				break;
			}
			InterfacePtr<IGraphicAttrBoolean> attr((IGraphicAttrBoolean*)graphicStyleDescriptor->QueryAttribute (
																												 attrClassID, 
																												 IID_IGRAPHICATTR_BOOLEAN));
			if (attr == nil)
			{
				continue;
			}
			if (attributeCount == 0)
			{
				targetValue = attr->GetBoolean();
			}
			else if (targetValue != attr->GetBoolean())
			{
				break;
			}
			attributeCount++;
		}

		if (attributeCount == itemList.Length())
		{
			result = eCommonValue;
			value = targetValue;
		}
		else if (attributeCount > 0)
		{
			result = eMixedValue;
		}
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasBooleanAttribute-->Out result=%d, value=%d, attributeCount=%d\n",
			  result,
			  ::ToDouble(value),
			  attributeCount);
	return result;
}

/*
*/
TranFxUtils::AttrState TranFxUtils::HasInt32Attribute(const UIDList& itemList, const ClassID& attrClassID, int32& value)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasInt32Attribute-->In attrClassID=0x%x\n", attrClassID.Get());    
	TranFxUtils::AttrState result = eNoValue;
	int32 attributeCount = 0;
	do
	{
		int32 targetValue(0);

		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IGraphicStyleDescriptor> graphicStyleDescriptor(itemList.GetRef(i), UseDefaultIID ());
			if (graphicStyleDescriptor == nil)
			{
				break;
			}
			InterfacePtr<IGraphicAttrInt32> attr((IGraphicAttrInt32*)graphicStyleDescriptor->QueryAttribute(
																										   attrClassID, 
																										   IID_IGRAPHICATTR_INT32));
			if (attr == nil)
			{
				continue;
			}
			if (attributeCount == 0)
			{
				targetValue = attr->GetInt32();
			}
			else if (attr->GetInt32() != targetValue)
			{
				break;
			}
			attributeCount++;
		}

		if (attributeCount == itemList.Length())
		{
			// All the items have a common attribute value.
			result = eCommonValue;
			value = targetValue;
		}
		else if (attributeCount > 0)
		{
			result = eMixedValue;
		}
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::HasInt32Attribute-->Out result=%d, value=%d, attributeCount=%d\n",
			  result,
			  ::ToDouble(value),
			  attributeCount);
	return result;
}

/*
*/
bool16 TranFxUtils::CanApplyAdornment(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}

/*
*/
bool16 TranFxUtils::CanApplyUseBlackAsOpaque(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}

/*
*/
bool16 TranFxUtils::CanApplyUseBlur(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}

/*
*/
bool16 TranFxUtils::CanApplyUseAlpha(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}
/*
*/
bool16 TranFxUtils::CanApplyXOffset(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}

/*
*/
bool16 TranFxUtils::CanApplyYOffset(const UIDList& itemList) const
{
	return this->CanApplyEffect(itemList);
}

/*
*/
bool16 TranFxUtils::CanApplyEffect(const UIDList& itemList) const
{
	bool16 result = kFalse; // assume you can't apply the effect.
	Utils<IPageItemTypeUtils> pageItemTypeUtils;
	if (pageItemTypeUtils && itemList.Length() > 0)
	{
		// Now assume you can apply the effect and stop testing
		// the first time you find an item that can't take the effect.
		result = kTrue; 
		for (int32 i = 0; i < itemList.Length(); i++) 
		{
			// Can't apply the effect to guides.
 			if (pageItemTypeUtils->IsGuide(itemList.GetRef(i)))
			{
  				result = kFalse;
				break;
  			}
		}
	}
	return result;
}

/*
*/
ErrorCode TranFxUtils::ApplyAdornment(const UIDList& itemList, const bool16 isAdd)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyAdornment-->In\n"); 
	ErrorCode status = kFailure;
	if (isAdd)
	{
		status = this->AddAdornment(itemList);
	}
	else
	{
		status = this->RemoveAdornment(itemList);
	}
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyAdornment-->Out status=%d\n",
			  status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::AddAdornment(const UIDList& itemList)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::AddAdornment-->In\n");
	ErrorCode status = kFailure;
	do
	{
		// Build a list of items that don't have the adornment.
		UIDList unadornedItemList(itemList.GetDataBase());
		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(itemList.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
			ASSERT(pageItemAdornmentList);
			if(!pageItemAdornmentList) {
				continue;
			}	
			if (pageItemAdornmentList->HasAdornment(kTranFxAdornmentBoss) == kFalse)
			{
				unadornedItemList.Append(itemList [i]);
			}
		}
		if (unadornedItemList.Length() == 0)
		{
			status = kSuccess;
			break;
		}

		// If the adornment addition is undone update the item-has-xp list.  Note that this
		// only happens in the "reverse" (undo) direction.
		this->Inval(unadornedItemList, 
					kTrue, // pre adding the adornment.
					kFalse,
					IXPManager::kXPC_NoChange,
					kFalse,
					IXPManager::kXPC_RemovedSomeXP);

		// Add the adornment.
		InterfacePtr<ICommand>  addPageItemAdornmentCmd(CmdUtils::CreateCommand(kAddPageItemAdornmentCmdBoss));
		ASSERT(addPageItemAdornmentCmd);
		if (!addPageItemAdornmentCmd)
		{
			break;
		}

		InterfacePtr<IClassIDData>  classIDData(addPageItemAdornmentCmd, UseDefaultIID());
		ASSERT(classIDData);
		if (!classIDData)
		{
			break;
		}
		classIDData->Set(kTranFxAdornmentBoss);
		addPageItemAdornmentCmd->SetItemList(unadornedItemList);
		status = CmdUtils::ProcessCommand(addPageItemAdornmentCmd);
		ASSERT_MSG(status == kSuccess, "kAddPageItemAdornmentCmdBoss failed");

		// Now the adornment is added update the item-has-xp list.  Note that this
		// happens in the "forward" (do) direction.
		this->Inval(unadornedItemList, 
					kFalse,	// post adding the adornment.
					kFalse,
					IXPManager::kXPC_AddedSomeXP,
					kFalse,
					IXPManager::kXPC_NoChange);


	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::AddAdornment-->Out status=%d\n",
			  status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::RemoveAdornment(const UIDList& itemList)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::RemoveAdornment-->In\n");
	ErrorCode status = kFailure;
	do
	{
		// Build a list of items that have the adornment.
		UIDList adorneditemList(itemList.GetDataBase());
		for (int32 i = 0; i < itemList.Length(); i++)
		{
			InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(itemList.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
			ASSERT(pageItemAdornmentList);
			if(!pageItemAdornmentList) {
				continue;
			}
			if (pageItemAdornmentList->HasAdornment(kTranFxAdornmentBoss) == kTrue)
			{
				adorneditemList.Append(itemList [i]);
			}
		}
		if (adorneditemList.Length() == 0)
		{
			status = kSuccess;
			break;
		}

		// If the adornment removal is undone update the item-has-xp list.  Note that this
		// only happens in the "reverse" (undo) direction.
		this->Inval(adorneditemList, 
					kTrue, // pre removing the adornment.
					kFalse,
					IXPManager::kXPC_NoChange,
					kFalse,
					IXPManager::kXPC_AddedSomeXP);

		// Remove the adornment.
		InterfacePtr<ICommand>  removePageItemAdornmentCmd(CmdUtils::CreateCommand(kRemovePageItemAdornmentCmdBoss));
		ASSERT(removePageItemAdornmentCmd);
		if (!removePageItemAdornmentCmd)
		{
			break;
		}
		InterfacePtr<IClassIDData>  classIDData(removePageItemAdornmentCmd, UseDefaultIID());
		ASSERT(classIDData);
		if (!classIDData)
		{
			break;
		}
		classIDData->Set(kTranFxAdornmentBoss);
		removePageItemAdornmentCmd->SetItemList(adorneditemList);
		status = CmdUtils::ProcessCommand(removePageItemAdornmentCmd);
		ASSERT_MSG(status == kSuccess, "kRemovePageItemAdornmentCmdBoss failed");

		// Now the adornment is removed update the item-has-xp list.  Note that this
		// happens in the "forward" (do) direction.
		this->Inval(adorneditemList, 
					kFalse,	// post removing the adornment.
					kFalse,
					IXPManager::kXPC_RemovedSomeXP,
					kFalse,
					IXPManager::kXPC_NoChange);

	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::RemoveAdornment-->Out status=%d\n",
			  status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyXOffset(const UIDList& itemList, const PMReal& value, bool16 doPrePost, bool16 enableDoNotify)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyXOffset-->In\n");
	ErrorCode status = this->ApplyPMRealAttribute(itemList, kTranFxOffsetXAttrBoss, value, doPrePost, enableDoNotify);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyXOffset-->Out status=%d\n", status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyYOffset(const UIDList& itemList, const PMReal& value, bool16 doPrePost, bool16 enableDoNotify)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyYOffset-->In\n");
	ErrorCode status = this->ApplyPMRealAttribute(itemList, kTranFxOffsetYAttrBoss, value, doPrePost, enableDoNotify);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyYOffset-->Out status=%d\n", status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyUseBlackAsOpaque(const UIDList& itemList, 
									   const bool16 value, 
									   bool16 doPrePost, bool16 enableDoNotify)
{
	ErrorCode status = this->ApplyBooleanAttribute(itemList, kTranFxUseBlackAsOpaqueAttrBoss, value, doPrePost, enableDoNotify);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyUseAlpha(const UIDList& itemList, 
									 const bool16 value, 
									 bool16 doPrePost, bool16 enableDoNotify)
{
	ErrorCode status = this->ApplyBooleanAttribute(itemList, kTranFxUseAlphaAttrBoss, value, doPrePost, enableDoNotify);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyUseBlur(const UIDList& itemList, 
									const bool16 value, 
									bool16 doPrePost, bool16 enableDoNotify)
{
	ErrorCode status = this->ApplyBooleanAttribute(itemList, kTranFxUseBlurAttrBoss, value, doPrePost, enableDoNotify);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyPMRealAttribute(const UIDList& itemList, 
											const ClassID& attrClassID, 
											const PMReal& value, 
											bool16 doPrePost, bool16 enableDoNotify)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyPMRealAttribute-->In attrClassID=0x%x, value=%f\n",
			  attrClassID.Get(),
			  ::ToDouble(value));
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IGraphicAttrRealNumber> attr(::CreateObject2<IGraphicAttrRealNumber>(attrClassID));
		ASSERT(attr);
		if (!attr)
		{
			break;
		}
		attr->SetRealNumber(value);
		InterfacePtr<ICommand> createAttributeCmd(Utils<IGraphicStateUtils>()->CreateAttributeCommand(attr,
																									  &itemList, 
																									  doPrePost, 
																									  enableDoNotify));
		ASSERT(createAttributeCmd);
		if (!createAttributeCmd)
		{
			break;
		}
		// See comment in ApplyInt32Attribute.
		createAttributeCmd->SetCreatorID(attrClassID.Get());
		status = CmdUtils::ProcessCommand(createAttributeCmd);
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyPMRealAttribute-->Out status=%d\n",
			  status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyBooleanAttribute(const UIDList& itemList, 
											 const ClassID& attrClassID, 
											 const bool16 value, 
											 bool16 doPrePost, bool16 enableDoNotify)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyBooleanAttribute-->In\n attrClassID=0x%x, value=%d", attrClassID.Get(), value);
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IGraphicAttrBoolean > attr(::CreateObject2<IGraphicAttrBoolean >(attrClassID));
		ASSERT(attr);
		if (!attr)
		{
			break;
		}
		attr->SetBoolean(value);
		InterfacePtr<ICommand> createAttributeCmd(Utils<IGraphicStateUtils>()->CreateAttributeCommand(attr,
																									  &itemList, 
																									  doPrePost, 
																									  enableDoNotify));
		ASSERT(createAttributeCmd);
		if (!createAttributeCmd)
		{
			break;
		}
		createAttributeCmd->SetCreatorID(attrClassID.Get());
		status = CmdUtils::ProcessCommand(createAttributeCmd);
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyBooleanAttribute-->Out status=%d\n",
			  status);
	return status;
}

/*
*/
ErrorCode TranFxUtils::ApplyInt32Attribute(const UIDList& itemList, const ClassID& attrClassID, const int32 value, bool16 doPrePost, bool16 enableDoNotify)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyInt32Attribute-->In\n attrClassID=0x%x, value=%d", attrClassID.Get(), value);
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IGraphicAttrInt32> attr((IGraphicAttrInt32*) ::CreateObject (attrClassID, IID_IGRAPHICATTR_INT32));
		ASSERT(attr);
		if (!attr)
		{
			break;
		}
		attr->SetInt32(value);
		InterfacePtr<ICommand> createAttributeCmd(Utils<IGraphicStateUtils>()->CreateAttributeCommand(attr,
																									  &itemList, 
																									  doPrePost, 
																									  enableDoNotify));
		ASSERT(createAttributeCmd);
		if (!createAttributeCmd)
		{
			break;
		}
		// Set the command's creator id so that the attribute command
		// (kGfxApplyAttrOverrideCmdBoss) processed from the previewable 
		// dialog would not get replaced by the previewable dialog's command
		// handling.
		//
		// If a command, kGfxApplyAttrOverrideCmdBoss say, gets processed more
		// than once in a previewable dialog the previously fired command will
		// be undone and replaced by this new command. We use the same command
		// to change different attributes and don't want this to happen. 
		//
		// For example if the mode is changed more than once we want the last
		// change to be effected. Ditto for x offset and y offset. To achive
		// this we call ICommand::SetCreatorID to change the creator id from
		// kGfxApplyAttrOverrideCmdBoss to the ClassID of the attribute being
		// changed.
		// So if the attribute gets changed more than once the preceeding command
		// is undone and replaced by this one.
		createAttributeCmd->SetCreatorID(attrClassID.Get());
		status = CmdUtils::ProcessCommand(createAttributeCmd);
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::ApplyInt32Attribute-->Out status=%d\n",
			  status);
	return status;
}   

/*
*/
void TranFxUtils::Inval(const UIDList& itemList, 
						bool16 isPre,
						bool32 invalidateOnDo, 
						IXPManager::XPChangeType changeTypeOnDo,
						bool32 invalidateOnUndo, 
						IXPManager::XPChangeType changeTypeOnUndo)
{
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::Inval-->In invalidateOnDo=%d, changeTypeOnDo=%d, invalidateOnUndo=%d, changeTypeOnUndo=%d\n",
			  invalidateOnDo,
			  changeTypeOnDo,
			  invalidateOnUndo,
			  changeTypeOnUndo);
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<ICommand> invalCmd(CmdUtils::CreateCommand(kXPItemXPPrePostCmdBoss));
		if (!invalCmd)
		{
			break;
		}
		if (isPre)
		{
			// Pre adding the adornment bump the CreatorID so that
			// this command is not undone when the post adding the
			// adornment call is made.
			invalCmd->SetCreatorID(invalCmd->GetCreatorID()+1);
		}
		InterfacePtr<IXPItemXPPrePostCmdData> xpItemXPPrePostCmdData(invalCmd, UseDefaultIID());
		if (!xpItemXPPrePostCmdData)
		{
			break;
		}
		// On Do, you typically want to invalidate, but no xp-change.  This invals the effect
		// before its position may have changed (or it is going away).
		xpItemXPPrePostCmdData->SetDoBehavior(invalidateOnDo, changeTypeOnDo);

		// Typically on undo, you want to invalidate, AND do an xp-change, since on undo this
		// has to happen *after* the attributes changes that control the drawing have been undone.
		xpItemXPPrePostCmdData->SetUndoBehavior(invalidateOnUndo, changeTypeOnUndo);
		invalCmd->SetItemList(itemList);
		status = CmdUtils::ProcessCommand(invalCmd);
		ASSERT_MSG(status == kSuccess, "kXPItemXPPrePostCmdBoss failed");
	} while (false);
	TRACEFLOW(kTranFxPluginName, "TranFxUtils::Inval-->Out status=%d\n",
			  status);
}

// End, TranFxUtils.cpp.


