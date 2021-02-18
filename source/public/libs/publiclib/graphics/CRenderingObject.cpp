//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/graphics/CRenderingObject.cpp $
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

#include "VCPublicHeaders.h"

#include "CRenderingObject.h"

#include "IGraphicsPort.h"

#include "IWaxRun.h"
#include "IGeometry.h"
#include "ITOPFrameData.h"
#include "IGraphicStyleDescriptor.h"
#include "IWaxRenderData.h"
#include "ITextStoryThread.h"
#include "IParcelList.h"
#include "IPrivateScriptUtils.h"

#include "LocaleSetting.h"
#include "ISwatchUtils.h"

DEFINE_HELPER_METHODS(CRenderingObject)

CRenderingObject::CRenderingObject(IPMUnknown *boss)
	: HELPER_METHODS_INIT(boss),
	fRenderingFlag(0L)
{
	fRenderingFlag |= CRenderingObject::kVisibleFlag;
	fRenderingFlag |= CRenderingObject::kDeleteFlag;
	fRenderingFlag |= CRenderingObject::kEditFlag;
	//fRenderingFlag |= CRenderingObject::kGlobalFlag;
	
}

CRenderingObject::~CRenderingObject()
{}

void CRenderingObject::ReadWrite(IPMStream *s, ImplementationID prop)
{
	fRenderName.ReadWrite(s);
	s->XferInt32(fRenderingFlag);
}

#pragma mark -

void CRenderingObject::Install ( IGraphicsPort *gPort, const PMRect& r ) const
{
}

void CRenderingObject::Install ( IGraphicsPort* gPort, IGraphicAttributeSuite* iGfxAttrSuite, InstallAction theAction, const PMRect& r ) const
{
	// default unless the sub classes do something else
	Install (gPort, r);		
}

void CRenderingObject::Install ( IGraphicsPort* gPort, IGraphicStyleDescriptor* iGSDesc, InstallAction theAction ) const
{
	// default unless the sub classes do something else
	InterfacePtr<IGeometry> geometry (iGSDesc, IID_IGEOMETRY);
	if ( geometry )
		Install (gPort, geometry->GetStrokeBoundingBox());		
}

void CRenderingObject::Install ( IGraphicsPort* gPort, IWaxRenderData* iWaxData, InstallAction theAction ) const
{
	// default unless the sub classes do something else
	InterfacePtr<IWaxRun> waxRun (iWaxData, UseDefaultIID());
	if ( waxRun )
	{
		UID frameUID;
		{
			const IWaxLine* waxLine = waxRun->GetWaxLine();
			ParcelKey	parcelKey = waxLine->GetParcelKey();

			InterfacePtr<ITextStoryThread> thread(waxLine->QueryStoryThread());
			InterfacePtr<IParcelList> pl(thread->QueryParcelList());

			frameUID = pl->GetParcelFrameUID(parcelKey);
		}
		IDataBase * db = waxRun->GetDataBase();
		InterfacePtr<IGeometry> geometry (db , frameUID, UseDefaultIID());
		
			// Yes, this is a "Path Type" specific hack, but it seemed like
			// the safest and most expedient way to go about getting gradients
			// set up correctly for text on a path.  - Zak
		InterfacePtr<ITOPFrameData> topFrameData(geometry, IID_ITOPFRAMEDATA);
		if ( topFrameData )
			{
			InterfacePtr<IGeometry> topSplineGeometry(db, topFrameData->GetMainSplineItemUID(), UseDefaultIID());
				// Move the ownership of the reference from one InterfacePtr to the other.
			geometry.reset(topSplineGeometry);
			topSplineGeometry.forget();
			}

		if (geometry) {
			// The bounding box retrieved from the wax data is in the frame coordinates 
			PMRect strokeBoundingBox = geometry->GetStrokeBoundingBox();
			strokeBoundingBox.Right() -= strokeBoundingBox.Left();
			strokeBoundingBox.Left() = 0.0;
			Install (gPort, strokeBoundingBox);
		}
	}
}

void CRenderingObject::Install ( IGraphicsPort* gPort, const AttributeBossList& attrs, const PMRect& r, InstallAction theAction ) const
{
	this->Install (gPort, r);		
}

void CRenderingObject::Install (IGraphicsPort* gPort, RenderingObjectInstallData *data, const PMRect& r, InstallAction theAction) const
{
	this->Install (gPort, r);		
}

#pragma mark -

void CRenderingObject::SetSwatchName(const PMString& newName)
{
	if (fRenderName != newName)
	{
		PreDirty();
		fRenderName = newName;
		fRenderName.SetTranslatable(kFalse);
	}
}

void CRenderingObject::SetVisibility(const bool16 visibility)
{

	if ( visibility )
	{
		if ((fRenderingFlag & CRenderingObject::kVisibleFlag) == 0)
		{
			PreDirty();
			fRenderingFlag |= CRenderingObject::kVisibleFlag;
		}
		// Now: set to global if visible.
		// Future: consistent with Illustrator.
		SetIsGlobal (kTrue);
	}
	else
	{
		if ((fRenderingFlag & CRenderingObject::kVisibleFlag) != 0)
		{
			PreDirty();
			fRenderingFlag &= ~CRenderingObject::kVisibleFlag;
		}
		SetIsGlobal (kFalse);
	}

}


void CRenderingObject::SetCanDelete(const bool16 canDelete)
{
	if ( canDelete && ((fRenderingFlag & CRenderingObject::kDeleteFlag) == 0) )
	{
		PreDirty();
		fRenderingFlag |= CRenderingObject::kDeleteFlag;
	}
	else if ( !canDelete && ((fRenderingFlag & CRenderingObject::kDeleteFlag) != 0) )
	{
		PreDirty();
		fRenderingFlag &= ~CRenderingObject::kDeleteFlag;
	}

}


void CRenderingObject::SetCanEdit(const bool16 canEdit)
{

	if ( canEdit && ((fRenderingFlag & CRenderingObject::kEditFlag) == 0) )
	{
		PreDirty();
		fRenderingFlag |= CRenderingObject::kEditFlag;
	}
	else if ( !canEdit && ((fRenderingFlag & CRenderingObject::kEditFlag) != 0) )
	{
		PreDirty();
		fRenderingFlag &= ~CRenderingObject::kEditFlag;
	}
}

// A private method for now
void CRenderingObject::SetIsGlobal(const bool16 isGlobal)
{

	if ( isGlobal && ((fRenderingFlag & CRenderingObject::kGlobalFlag) == 0) )
	{
		PreDirty();
		fRenderingFlag |= CRenderingObject::kGlobalFlag;
	}
	else if ( !isGlobal && ((fRenderingFlag & CRenderingObject::kGlobalFlag) != 0) )
	{
		PreDirty();
		fRenderingFlag &= ~CRenderingObject::kGlobalFlag;
	}
}


void CRenderingObject::SetSpecialEditInfo( const int32 editInfo )
{
}

void CRenderingObject::SetSwatchAliasUID (UID newAliasUID)
{
	ASSERT_FAIL ("CRenderingObject::SetSwatchAliasUID, overwrite this to support swatch aliasing.");
}

void CRenderingObject::SetCreatorID (int32 newCreatorID)
{
	ASSERT_FAIL ("CRenderingObject::SetCreatorID, overwrite this to support tracking of swatch creator.");
}

#pragma mark -

PMString CRenderingObject::GetTipText() const
{
	return PMString();
}

PMString CRenderingObject::GetTipText( const int32& colorSpace, const ColorArray& colorComponents ) const
{
	return PMString();
}

const PMString& CRenderingObject::GetSwatchName() const
{
	return fRenderName;
}

bool16 CRenderingObject::GetVisibility() const
{
	return (((fRenderingFlag & CRenderingObject::kVisibleFlag) > 0) ? kTrue : kFalse);
}

bool16 CRenderingObject::GetCanDelete() const
{
	return (((fRenderingFlag & CRenderingObject::kDeleteFlag) > 0) ? kTrue : kFalse);
}

bool16 CRenderingObject::GetCanEdit() const
{
// InCopy: Cannot edit spot colors
	bool16 isInCopy = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);
	if (isInCopy && !Utils<IPrivateScriptUtils>()->IsINX())
	{
		InterfacePtr<IColorData> colorData(this, UseDefaultIID());
		if (colorData && colorData->GetColorSpace() == kPMCsDeviceN)
			return kFalse;
		InterfacePtr<IInkData> inkData(this, IID_IINKDATA);
		if (inkData && inkData->GetInkType() == IInkData::kSpotInk)
			return kFalse;
	}

	return (((fRenderingFlag & CRenderingObject::kEditFlag) > 0) ? kTrue : kFalse);
}

bool16 CRenderingObject::IsGlobal() const
{
#if 1
	// Use flag when we actually make distinction between visible and global swatches as in Illustrator.
	// Otherwise, we introduce unnecessary format changes.
	return (GetVisibility () && !(GetSwatchName ().empty ()));
#else
	return (((fRenderingFlag & CRenderingObject::kGlobalFlag) > 0) ? kTrue : kFalse);
#endif
}

int32 CRenderingObject::GetSpecialEditInfo() const
{
	return 0;
}

UID CRenderingObject::GetSwatchAliasUID () const
{
	return kInvalidUID;
}

int32 CRenderingObject::GetCreatorID () const
{
	return kInDesignNativeSwatchCreatorID;
}


#pragma mark -
//========================================================================================
// Private Methods
//========================================================================================

const PMString& CRenderingObject::GetSwatchUIName() const
{ 
	return GetSwatchName(); 
}

bool16 CRenderingObject::NeedUpdate( UID interestedUID ) const
{ 
	return kFalse;
}

UID	CRenderingObject::DuplicateAsLocal( const IGraphicStyleDescriptor* iGSDesc, InstallAction theAction) const
{
	return this->DuplicateAsLocal();
}

UID	CRenderingObject::DuplicateAsLocal( const AttributeBossList* overrideAttrs, InstallAction theAction) const
{
	return this->DuplicateAsLocal();
}

UID	CRenderingObject::DuplicateAsLocal(const PMReal& tint) const
{
	return this->DuplicateAsLocal();	
}

UID	CRenderingObject::DuplicateAsLocal(void) const
{
	IDataBase*	db = ::GetDataBase(this);
	UIDList		newItemList = Utils<ISwatchUtils>()->DuplicateSwatches( UIDList( db, ::GetUID(this) ), nil, kTrue, kTrue, kFalse );

	ASSERT_MSG ( newItemList[0] != kInvalidUID, "DuplicateAsLocal Falied.\n");
	return newItemList[0];
}

bool16 CRenderingObject::IsEqual (const IRenderingObject* iRenderObject2 ) const
{ 
	bool16	areEqual = kFalse;
	
	if (GetRenderClass() == iRenderObject2->GetRenderClass())
	{
#if 1
		//	We really want to ignore delete/edit/special edit info.
		//	This change only affects locked swatches comparison.
		areEqual = (GetVisibility () == iRenderObject2->GetVisibility ());
#else
		areEqual = (GetVisibility () == iRenderObject2->GetVisibility ()) &&
					(GetCanDelete() == iRenderObject2->GetCanDelete ()) &&
					(GetCanEdit() == iRenderObject2->GetCanEdit ()) &&
					(GetSpecialEditInfo() == iRenderObject2->GetSpecialEditInfo ());
#endif
	}
	
	return areEqual;
}

