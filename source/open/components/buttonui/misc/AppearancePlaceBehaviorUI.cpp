//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/misc/AppearancePlaceBehaviorUI.cpp $
//  
//  Owner: Lonnie Millett
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
//  code was taken from SplinePlaceBehavior.cpp and modified to form field page items
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IHierarchy.h"
#include "IPlaceBehavior.h"

// ----- Includes -----

#include "CGraphicPlaceBehaviorUI.h"
#include "CursorDefs.h"
#include "CursorSpec.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

class AppearancePlaceBehaviorUI : public CGraphicPlaceBehaviorUI
{
	typedef CGraphicPlaceBehaviorUI Inherited;
	
public:	
	AppearancePlaceBehaviorUI(IPMUnknown *boss);
	virtual ~AppearancePlaceBehaviorUI();

	virtual CursorSpec	GetCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;
	virtual CursorSpec	GetDropCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;

private:
	virtual CursorSpec	GetPlaceIntoCursor() const;
	virtual CursorSpec	GetPlaceCursor() const;
	CursorSpec CommonGetCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers, bool16 dropCursor = kFalse) const;
};

CREATE_PMINTERFACE(AppearancePlaceBehaviorUI, kAppearancePlaceBehaviorUIImpl);

#pragma exceptions on

// -----------------------------------------------------------------------------


AppearancePlaceBehaviorUI::AppearancePlaceBehaviorUI(IPMUnknown *boss) :
	CGraphicPlaceBehaviorUI(boss)
{
}


// -----------------------------------------------------------------------------

AppearancePlaceBehaviorUI::~AppearancePlaceBehaviorUI()
{
}

// -----------------------------------------------------------------------------

CursorSpec AppearancePlaceBehaviorUI::GetCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const
{
	return CommonGetCursor(globalLocation, modifiers, kFalse);
}

CursorSpec AppearancePlaceBehaviorUI::CommonGetCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers, bool16 dropCursor) const
{
	CursorSpec cursor = GetPlaceCursor();

	InterfacePtr<IHierarchy> sourceItem(const_cast<AppearancePlaceBehaviorUI*>(this), UseDefaultIID());
	InterfacePtr<IHierarchy> parentItem(sourceItem->QueryParent());
	InterfacePtr<IPlaceBehavior> parentBehavior(parentItem, UseDefaultIID());
	if (parentBehavior == nil)
	{
		InterfacePtr<IHierarchy> sourceContent(sourceItem->GetChildCount() ? sourceItem->QueryChild(0) : nil);
		if (sourceContent)
		{
			InterfacePtr<IPlaceBehaviorUI> sourceBehaviorUI(sourceContent, UseDefaultIID());
			cursor = dropCursor ? sourceBehaviorUI->GetDropCursor(globalLocation, modifiers) : sourceBehaviorUI->GetCursor(globalLocation, modifiers);
		}
		else
		{
			//exception
			//ASSERT_FAIL("AppearancePlaceBehavior::GetCursor: can't place empty frame");
			// we seem to temporarily reach this point when undoing so we comment out the assert
		}
	}
	else
		cursor = dropCursor ? Inherited::GetDropCursor(globalLocation, modifiers) : Inherited::GetCursor(globalLocation, modifiers);

	return cursor;
}

CursorSpec	AppearancePlaceBehaviorUI::GetDropCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const
{
	return CommonGetCursor(globalLocation, modifiers, kTrue);
}

// -----------------------------------------------------------------------------

CursorSpec AppearancePlaceBehaviorUI::GetPlaceIntoCursor() const
{
	return PluginCursorSpec(kCrsrPlaceImageInto);
}


// -----------------------------------------------------------------------------

CursorSpec AppearancePlaceBehaviorUI::GetPlaceCursor() const
{
	return PluginCursorSpec(kCrsrPlaceGraphic);
}


