//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpGraphicHelper.cpp $
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
#include "IGraphicAttributeUtils.h"
#include "ISwatchUtils.h"
#include "IGraphicAttrInt32.h"
#include "IPersistUIDData.h"
#include "IGraphicAttrClassID.h"
#include "IGraphicAttrRealNumber.h"
#include "IDashedAttributeValues.h"
#include "IApplyMultAttributesCmdData.h"
#include "IPMUnknown.h"
#include "IUIDData.h"
#include "IDocument.h"
#include "IImageDataAccess.h"
#include "IHierarchy.h"

// General includes:
#include "Utils.h"
#include "UIDList.h"
#include "CmdUtils.h"

//Project includes:
#include "SnpGraphicHelper.h"

/*
*/
SnpGraphicHelper::SnpGraphicHelper(const UIDList& itemList) : 
	fItemList(itemList),
	fIApplyMultAttributesCmdData(nil)
{
}

/*
*/
SnpGraphicHelper::SnpGraphicHelper(const UIDRef& itemRef) : 
	fItemList(itemRef),
	fIApplyMultAttributesCmdData(nil)

{
}

/*
*/
SnpGraphicHelper::~SnpGraphicHelper()
{
}

/*
*/
void SnpGraphicHelper::Reset(const UIDList& itemList)
{
	this->fItemList = itemList;
}

/*
*/
void SnpGraphicHelper::Reset(const UIDRef& itemRef)
{
	this->fItemList = UIDList(itemRef);
}

/*
*/
ErrorCode	SnpGraphicHelper::ApplyAttributes()
{
	ErrorCode status = kFailure;
	do {
		ASSERT(fIApplyMultAttributesCmdData);
		if (!fIApplyMultAttributesCmdData) {
			break;
		}
		InterfacePtr<ICommand> gfxApplyMultAttributesCmd(fIApplyMultAttributesCmdData, UseDefaultIID());
		ASSERT(gfxApplyMultAttributesCmd);
		if (!gfxApplyMultAttributesCmd) {
			break;
		}
		gfxApplyMultAttributesCmd->SetItemList(this->fItemList);
		status = CmdUtils::ProcessCommand(gfxApplyMultAttributesCmd);
		ASSERT_MSG(status == kSuccess, "kGfxApplyMultAttributesCmdBoss failed");
		if (status != kSuccess) {
			break;
		}
	} while(false);
	fIApplyMultAttributesCmdData.reset(nil);
	return status;
}

/*
*/
void SnpGraphicHelper::AddAnAttribute(IPMUnknown* attribute)
{
	do {
		if (fIApplyMultAttributesCmdData == nil) {
			// Create a command that can change graphic attributes.
			InterfacePtr<ICommand> gfxApplyMultAttributesCmd(CmdUtils::CreateCommand(kGfxApplyMultAttributesCmdBoss));
			ASSERT(gfxApplyMultAttributesCmd);
			if (!gfxApplyMultAttributesCmd) {
				break;
			}
			InterfacePtr<IApplyMultAttributesCmdData> applyMultAttributesCmdData(gfxApplyMultAttributesCmd, UseDefaultIID());
			ASSERT(applyMultAttributesCmdData);
			if (!applyMultAttributesCmdData) {
				break;
			}
			fIApplyMultAttributesCmdData = applyMultAttributesCmdData;
		}
		fIApplyMultAttributesCmdData->AddAnAttribute(attribute);
	} while(false);
}

/*
*/
void SnpGraphicHelper::AddStrokeWeight(const PMReal& strokeWeight)
{
	InterfacePtr<IGraphicAttrRealNumber> strokeWeightAttribute(Utils<IGraphicAttributeUtils>()->CreateStrokeWeightAttribute(strokeWeight));
	ASSERT(strokeWeightAttribute);
	if (strokeWeightAttribute) {
		this->AddAnAttribute(strokeWeightAttribute);
	}
}

/*
*/
UID SnpGraphicHelper::GetNamedSwatch(const PMString& swatchName, IDataBase* db)
{
	UID result = kInvalidUID;
	ASSERT(db);
	if (db) {
		result = Utils<ISwatchUtils>()->GetNamedSwatch(swatchName, db);
	}
	return result;
}

/*
*/
void SnpGraphicHelper::AddStrokeRendering(const UID& swatchUID)
{	
	InterfacePtr<IPersistUIDData> strokeRenderingAttribute(Utils<IGraphicAttributeUtils>()->CreateStrokeRenderingAttribute (swatchUID));
	ASSERT(strokeRenderingAttribute);
	if (strokeRenderingAttribute) {
		this->AddAnAttribute (strokeRenderingAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddFillRendering(const UID& swatchUID)
{
	InterfacePtr<IPersistUIDData> fillRenderingAttribute(Utils<IGraphicAttributeUtils>()->CreateFillRenderingAttribute(swatchUID));
	ASSERT(fillRenderingAttribute);
	if (fillRenderingAttribute) {
		this->AddAnAttribute (fillRenderingAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddLineEndEndImplementation(const ClassID& pathEndStrokerClassID)
{
	InterfacePtr<IGraphicAttrClassID> lineEndEndImplementationAttribute(Utils<IGraphicAttributeUtils>()->CreateLineEndEndImplementationAttribute(pathEndStrokerClassID));
	ASSERT(lineEndEndImplementationAttribute);
	if (lineEndEndImplementationAttribute) {
		this->AddAnAttribute(lineEndEndImplementationAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddCornerImplementation(const ClassID& pathCornerClassID)
{
	InterfacePtr<IGraphicAttrClassID> cornerEffectAttribute(Utils<IGraphicAttributeUtils>()->CreateCornerImplementationAttribute(pathCornerClassID));
	ASSERT(cornerEffectAttribute);
	if (cornerEffectAttribute) {
		this->AddAnAttribute(cornerEffectAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddCornerRadius(const PMReal& cornerRadius)
{
	InterfacePtr<IGraphicAttrRealNumber> cornerRadiusAttribute(Utils<IGraphicAttributeUtils>()->CreateCornerRadiusAttribute(cornerRadius));
	ASSERT(cornerRadiusAttribute);
	if (cornerRadiusAttribute) {
		this->AddAnAttribute(cornerRadiusAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddLineImplementation(const ClassID& pathStrokerClassID)
{
	InterfacePtr<IGraphicAttrClassID> lineImplementationAttribute(Utils<IGraphicAttributeUtils>()->CreateLineImplementationAttribute(pathStrokerClassID, kInvalidUID/*new for 2.0*/));
	ASSERT(lineImplementationAttribute);
	if (lineImplementationAttribute) {
		this->AddAnAttribute(lineImplementationAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddJoinType(const SnpGraphicHelper::JoinType joinType)
{
	InterfacePtr<IGraphicAttrInt32> joinTypeAttribute(Utils<IGraphicAttributeUtils>()->CreateJoinTypeAttribute(joinType));
	ASSERT(joinTypeAttribute);
	if (joinTypeAttribute) {
		this->AddAnAttribute(joinTypeAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddLineCap(const SnpGraphicHelper::LineCap lineCap)
{
	InterfacePtr<IGraphicAttrInt32> lineCapAttribute(Utils<IGraphicAttributeUtils>()->CreateLineCapAttribute(lineCap));
	ASSERT(lineCapAttribute);
	if (lineCapAttribute) {
		this->AddAnAttribute(lineCapAttribute);
	}
}

/*
*/
void SnpGraphicHelper::AddDashedValues(const K2Vector<PMReal>& dashAndGapValues)
{
	IDataBase* db = fItemList.GetDataBase();
	InterfacePtr<IDocument> theDocument(db, db->GetRootUID(), UseDefaultIID());
	InterfacePtr<IUIDData> uidData(::CreateObject2<IUIDData>(kDashedAttributeValuesBoss));
	ASSERT(uidData != nil);
	uidData->Set(::GetUIDRef(theDocument));
	InterfacePtr<IDashedAttributeValues> dashedAttributeValues(uidData, UseDefaultIID());
	if (dashedAttributeValues != nil && dashAndGapValues.size() > 0) {
		for (int32 i = 0; i < dashAndGapValues.size(); i++) {
			dashedAttributeValues->SetValue(i, dashAndGapValues[i]);
		}
		this->AddAnAttribute(dashedAttributeValues);
	}
}


/** We are not sure if the selection is the frame or the graphic item.
The following sample shows code segment returning an imagePtr 
pointing to the graphic item. This code checks for availability 
of IImageDataAccess, you are free to use other conditions, 
such as IID_IGRAPHICITEM.
*/
IImageDataAccess * SnpGraphicHelper::QueryImageDataAccess()
{
	// Firs item only
	UIDRef imageRef = this->fItemList.GetRef(0);

	IImageDataAccess *imagePtr = nil;
	InterfacePtr<IImageDataAccess> imageAccess(imageRef, IID_IIMAGEDATAACCESS);
	bool8 hasLowRes = imageAccess && imageAccess->GetLowResImageUID() != kInvalidUID;
	if ( hasLowRes ) {
		// If the UIDRef has IImageDataAccess interface, then it is the image
		imagePtr = imageAccess;
		imagePtr->AddRef();
	}
	else
	{	// otherwise this is a frame
		InterfacePtr<IHierarchy> itemHierarchy(imageRef, IID_IHIERARCHY);
		if ( itemHierarchy->GetChildCount() == 1 )
		{
			// Check if frame’s child
			IDataBase *db = imageRef.GetDataBase();
			UID childUID = itemHierarchy->GetChildUID(0);
			// Check for a proxy image.
			InterfacePtr<IImageDataAccess> childImageAccess(db, childUID, IID_IIMAGEDATAACCESS);
			if (childImageAccess && childImageAccess->GetLowResImageUID() != kInvalidUID ) 
			{
				imagePtr = childImageAccess;
				imagePtr->AddRef();
			}
		}
	}

	return imagePtr;
}
/** We are not sure if the selection is the frame or the graphic item.
The following sample shows code segment returning an UIDRef 
of the graphic frame no matter which is selected. 
A reverse of QueryImageDataAccess() method
*/
UIDRef SnpGraphicHelper::GetGraphicFrame()
{
	// Firs item only
	UIDRef itemRef = this->fItemList.GetRef(0);

	InterfacePtr<IImageDataAccess> imageAccess(itemRef, IID_IIMAGEDATAACCESS);
	bool8 hasLowRes = imageAccess && imageAccess->GetLowResImageUID() != kInvalidUID;
	if ( hasLowRes ) {
		// If the UIDRef has IImageDataAccess interface, then it is the graphic item
		InterfacePtr<IHierarchy> itemHierarchy(itemRef, IID_IHIERARCHY);
		UIDRef parent(itemRef.GetDataBase(),itemHierarchy->GetParentUID());
		return parent;
	}
	else
	{	// otherwise this is a frame
		return itemRef;
	}	
}


//End, SnpGraphicHelper.cpp
