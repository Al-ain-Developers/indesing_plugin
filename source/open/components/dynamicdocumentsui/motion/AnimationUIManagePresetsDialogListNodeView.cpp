//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIManagePresetsDialogListNodeView.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

#include "IIntData.h"
#include "IInterfaceColors.h"
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWidgetParent.h"
#include "CIDStaticTextView.h"
#include "TreeNodeControlView.h"
#include "DynamicDocumentsUIID.h"

#include "DVAPublicIncludes.h"
#include "DVPublicUtilities.h"

class AnimationUIManagePresetsDialogListNodeView : public TreeNodeControlView
{
	typedef TreeNodeControlView inherited;
	
public:
	AnimationUIManagePresetsDialogListNodeView(IPMUnknown *boss) : inherited(boss) { SetDrawNodeSeparatorOnOff(kFalse); }
	virtual ~AnimationUIManagePresetsDialogListNodeView() { ; }
};

#pragma mark AnimationUIManagePresetsDialogListNodeView implementation

CREATE_PERSIST_PMINTERFACE(AnimationUIManagePresetsDialogListNodeView, kAnimationUIManagePresetsDialogListNodeViewImpl)

class AnimationUIManagePresetsDialogStaticTextWidgetView : public CIDStaticTextView
{
	typedef CIDStaticTextView inherited;
	
public:
			 AnimationUIManagePresetsDialogStaticTextWidgetView(IPMUnknown *boss) : inherited (boss) {}
	virtual ~AnimationUIManagePresetsDialogStaticTextWidgetView() {}
	
	virtual void DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;
};

#pragma mark AnimationUIManagePresetsDialogStaticTextWidgetView implementation

CREATE_PERSIST_PMINTERFACE(AnimationUIManagePresetsDialogStaticTextWidgetView, kAnimationUIManagePresetsDialogStaticTextWidgetViewImpl)

void AnimationUIManagePresetsDialogStaticTextWidgetView::DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const
{
	// DV_Note: static text has already drawn when we get here
	inherited::DV_Draw(drawbotP); 
	
	// 	Draw underline after the last custom preset.	
	InterfacePtr<IWidgetParent> iWidgetParent(this, UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData> iNodeData((ITreeNodeIDData*)iWidgetParent->QueryParentFor(IID_ITREENODEIDDATA));
	InterfacePtr<ITextControlData>	iTextData (this, UseDefaultIID ());
	
	if (iNodeData && iNodeData->Get () != nil && !iTextData->GetString ().IsNull ())
	{
		InterfacePtr<const ITreeViewHierarchyAdapter> iTreeViewHierarchyAdapter((ITreeViewHierarchyAdapter*)iWidgetParent->QueryParentFor(IID_ITREEVIEWHIERARCHYADAPTER));
		
		NodeID rootNode = iTreeViewHierarchyAdapter->GetRootNode(); 
		NodeID	childNode = iNodeData->Get ();
		
		int32 childIndex = iTreeViewHierarchyAdapter->GetChildIndex(rootNode, childNode);
		
		// Compare the current node index with the cached last custom preset index.
		// If they are the same, then draw the underline after the last custom preset.
		InterfacePtr<IIntData> iLastCustomPresetIndex(iTreeViewHierarchyAdapter, IID_ILASTCUSTOMPRESETINDEX);
		if (iLastCustomPresetIndex && (childIndex == iLastCustomPresetIndex->GetInt()))
		{
			RealAGMColor separatorColor;
			InterfacePtr<IInterfaceColors> appColors(GetExecutionContextSession(), UseDefaultIID());
			appColors->GetRealAGMColor(kInterfaceSeparatorColor, separatorColor);
			
			PMRect frame( GetInnerContentFrame() );
			int32 adjustment( 1 );
			
#if CAN_USE_DRAWBOT_FROM_OPEN_PROJECT
			drawbotP->GetSurface()->SetAntiAliasPolicy(dvaui::drawbot::kAntiAliasPolicy_None);
			dvaui::drawbot::PenP	penP(*drawbotP, dv_utils::RealColorToColorRGBA(separatorColor), dv_utils::kDefaultStrokeWidth);
			dvaui::drawbot::PathP	pathP(*drawbotP);
			
			pathP->MoveTo(dv_utils::ToPointF32(frame.Left(), frame.Bottom() - adjustment));
			pathP->LineTo(dv_utils::ToPointF32(frame.Right(), frame.Bottom() - adjustment));
			drawbotP->GetSurface()->StrokePath(*penP, *pathP);
#else
			PMPointList pathPts;
			pathPts.push_back(PMPoint(frame.Left(), frame.Bottom() - adjustment));    //moveto
			pathPts.push_back(PMPoint(frame.Right(), frame.Bottom() - adjustment));   //lineto
			
			dv_utils::DVSaveAndRestoreStateStack(drawbotP, true); //FIXME_DV: See declaration: 2nd parameter is unused
			dv_utils::DVSetAntiAliasPolicy(drawbotP, dv_utils::kAntiAliasPolicy_None);
			
			dv_utils::DVStrokePath(drawbotP, separatorColor, pathPts, dv_utils::kDefaultStrokeWidth);
#endif
		}
	}
}


