//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectTreeViewWidgetMgr.cpp $
//  
//  Owner: Heath Horton
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

#include "CTreeViewWidgetMgr.h"

#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITextControlData.h"
#include "IWidgetParent.h"
#include "ITriStateControlData.h"
#include "IAutoCorrectPrefs.h"

#include "CmdUtils.h"
#include "CoreResTypes.h"
#include "SpellPanelID.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "AutoCorrectNodeID.h"

#define INHERITED	CTreeViewWidgetMgr

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
class AutoCorrectTreeViewWidgetMgr : public INHERITED
{
public:
	AutoCorrectTreeViewWidgetMgr(IPMUnknown *boss);
	~AutoCorrectTreeViewWidgetMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const {return kAutoCorrectTreeWidgetNodeRsrcID;}
	virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const;

};

CREATE_PMINTERFACE(AutoCorrectTreeViewWidgetMgr, kAutoCorrectTreeViewWidgetMgrImpl)

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
AutoCorrectTreeViewWidgetMgr::AutoCorrectTreeViewWidgetMgr(IPMUnknown *boss) 
	: INHERITED(boss)
{
}


//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewWidgetMgr::~AutoCorrectTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
AutoCorrectTreeViewWidgetMgr::~AutoCorrectTreeViewWidgetMgr()
{
}


//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewWidgetMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------
bool16 AutoCorrectTreeViewWidgetMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 ) const
{	
	// Call base class for hilite selection
	INHERITED::ApplyNodeIDToWidget( node, widget );

#if 1
	TreeNodePtr<AutoCorrectNodeID> nodeID(node);
	const PMString correctedName = nodeID->GetCorrectedName();
	const PMString misspelledName = nodeID->GetMisspelledName();
	
#if 0
	bool16 bChecked = this->GetNodeCheckState(misspelledName, correctedID, correctedName, isMisspelledNode);
	
	InterfacePtr<IPanelControlData>	iPanelData(widget, UseDefaultIID());	
	InterfacePtr<IControlView> iCheckBoxView(iPanelData->FindWidget(kSynCorrectedCheckBoxWidgetID), IID_ICONTROLVIEW);

	if ( !isMisspelledNode)
	{
		// This is a leaf node, then set the corrected name for the text of checkbox
		InterfacePtr<ITextControlData> iCorrectedName(iCheckBoxView, IID_ITEXTCONTROLDATA);
		iCorrectedName->SetString(correctedName);	

		// Set the state for checkbox
		InterfacePtr<ITriStateControlData> iStateData(iCheckBoxView, IID_ITRISTATECONTROLDATA);
		iStateData->SetState(bChecked ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue, kFalse);
	}
	else
	{
		// This is a misspelled node, then set the misspelled name for the text of checkbox
		InterfacePtr<ITextControlData> iMisspelledName(iCheckBoxView, IID_ITEXTCONTROLDATA);
		iMisspelledName->SetString(misspelledName);

		InterfacePtr<ITriStateControlData> iStateData(iCheckBoxView, IID_ITRISTATECONTROLDATA);
		if (bChecked)
		{
			bool16 allChildrenChecked = kFalse; //this->AreAllChildrenChecked(misspelledName);
			if (allChildrenChecked)
				iStateData->Select(kTrue, kFalse);
			else
				iStateData->SetUnknown(kTrue, kFalse);
		}
		else 
		{
			iStateData->Deselect(kTrue, kFalse);
		}
	}

	// Adjust the size. 
	PMReal indent = this->GetIndent(node);
	PMRect widgetFrame = widget->GetFrame( );

	PMReal newWidth = iCheckBoxView->GetFrame().Right();
	widgetFrame.Left() = indent;
	widgetFrame.SetWidth( newWidth );
	widget->SetFrame( widgetFrame );
#endif
#endif

	return kTrue;
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewWidgetMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------
IControlView* AutoCorrectTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	IControlView* nodeView = nil;

	TreeNodePtr<AutoCorrectNodeID> nodeID(node);
	
	nodeView = (IControlView*) ::CreateObject(::GetDataBase(this),
			RsrcSpec(LocaleSetting::GetLocale(), kSpellPanelPluginID, kViewRsrcType, kAutoCorrectTreeWidgetNodeRsrcID),IID_ICONTROLVIEW);

	InterfacePtr<IPanelControlData> iPanelData(::GetDataBase(this), ::GetUID(nodeView),IID_IPANELCONTROLDATA);
	InterfacePtr<IControlView> iMisspelledStatTextView(iPanelData->FindWidget(kAutoCorrectMisspelledStaticTextWidgetID), IID_ICONTROLVIEW);
	InterfacePtr<IControlView> iCorrectedStatTextView(iPanelData->FindWidget(kAutoCorrectCorrectedStaticTextWidgetID), IID_ICONTROLVIEW);
	
	InterfacePtr<ITextControlData> iMisspelledTextControlData(iMisspelledStatTextView, IID_ITEXTCONTROLDATA);
	InterfacePtr<ITextControlData> iCorrectedTextControlData(iCorrectedStatTextView, IID_ITEXTCONTROLDATA);

	PMString misspelledName;
	PMString correctedName;

	if (nodeID)
	{
		misspelledName = nodeID->GetMisspelledName();
		correctedName = nodeID->GetCorrectedName();
	}

	misspelledName.SetTranslatable(kFalse);
	correctedName.SetTranslatable(kFalse);

	iMisspelledTextControlData->SetString(misspelledName, kTrue, kFalse);
	iCorrectedTextControlData->SetString(correctedName, kTrue, kFalse);	
	
	return nodeView;
}


