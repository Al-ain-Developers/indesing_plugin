//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicme/BscMEInvertFacade.cpp $
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
#include "IDocument.h"
#include "ISpreadList.h"
#include "IStoryList.h"
#include "IComposeScanner.h"
#include "ITextModel.h"
#include "IStoryOptions.h"
#include "IBoolData.h"
#include "ISetMEFrameCmdData.h"
#include "ITableModel.h"
#include "ITableCommands.h"
#include "ITableModelList.h"
#include "ISpread.h"
#include "IGeometry.h"
#include "IPageItemTypeUtils.h"
#include "ITransformFacade.h"
#include "TransformTypes.h"
#include "IStandOffMarginCmdData.h"
#include "IStandOffData.h"
#include "ITransformCmdData.h"
#include "ITransformPanelPrefs.h"
#include "IGraphicFrameData.h"
#include "IReferencePointData.h"
#include "IGraphicStyleDescriptor.h"
#include "IGraphicAttributeUtils.h"
#include "IDocSetupCmdData.h"
#include "IMasterSpreadList.h"

// General includes:
#include "WorldReadyID.h"
#include "TransformUtils.h"
#include "SplineID.h"
#include "PMPolygon4.h"
#include "PreferenceUtils.h"

// Project includes:
#include "IBscMEInvertFacade.h"
#include "BscMEID.h"

/** Facade provides methods to invert document.
 
 @ingroup basicme
*/
class BscMEInvertFacade : public CPMUnknown<IBscMEInvertFacade>
{
public:
	/** Constructor.
	 @param boss interface ptr from boss object on which this interface is aggregated.
	 */
	BscMEInvertFacade(IPMUnknown* boss) : CPMUnknown<IBscMEInvertFacade>(boss)
	{
	}
	
	/** See IBscMEInvertFacade::InvertDocument
	 */
	virtual void InvertDocument(IDocument* doc, const InvertOptions& invertOptions);
		
private:
	void InvertStoriesDirection(IDocument *doc);
	void ChangeTablesDirection(IDocument *doc);
	void ChangeTablesDirection(UIDRef& story);
	void InvertPageItemsOfSpread(IDocument* doc, UID spreadUID, const InvertOptions& invertOptions);
	void MovePageItem(const UIDRef& pageItem, const PMRect& pageBounds);
	void SetDocumentPageBinding(IDocument* doc, DocPageBinding pageBinding);	
	void InvertAngleOfObject(const UIDRef& pageItem);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
 */
CREATE_PMINTERFACE(BscMEInvertFacade, kBscMEInvertFacadeImpl)

void BscMEInvertFacade::InvertDocument(IDocument* doc, const InvertOptions& invertOptions)
{
	if (invertOptions.invertStories)
		this->InvertStoriesDirection(doc);
	
	if(invertOptions.changeTableDir)
		this->ChangeTablesDirection(doc);
	
	InterfacePtr<ISpreadList> spreadList(doc, IID_ISPREADLIST);
	if (spreadList)
	{
		// need to iterate through the existing spreads & change the
		// location of each page
		uint32 spreadCount = spreadList->GetSpreadCount();
		for (uint32 i = 0; i < spreadCount; i++)
		{
			UID spreadUID = spreadList->GetNthSpreadUID(i);
			ASSERT(spreadUID != kInvalidUID);
			this->InvertPageItemsOfSpread(doc, spreadUID, invertOptions);
		}
	}
		
	// now do the same for the master pages
	InterfacePtr<IMasterSpreadList> masterSpreadList(doc, IID_IMASTERSPREADLIST);	
	if (masterSpreadList)
	{
		// need to iterate through the existing master spreads & invert items of each master page
		uint32 spreadCount = masterSpreadList->GetMasterSpreadCount();
		for (uint32 i = 0; i < spreadCount; i++)
		{			
			UID	masterSpreadUID = masterSpreadList->GetNthMasterSpreadUID(i);
			ASSERT(masterSpreadUID != kInvalidUID);
			this->InvertPageItemsOfSpread(doc, masterSpreadUID, invertOptions);
		}
	}
	
	// Change the binding of the publication if user choose it
	if (Utils<ILayoutUtils>()->GetDocumentPageBinding(::GetUIDRef(doc)) != invertOptions.pageBinding)
	{
		this->SetDocumentPageBinding(doc, invertOptions.pageBinding);
	}
}

void BscMEInvertFacade::SetDocumentPageBinding(IDocument* doc, DocPageBinding pageBinding)
{
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetPageSetupPrefsCmdBoss));
		if(cmd == nil)
		{
			ASSERT_FAIL("BscMEInvertFacade::SetDocumentPageBinding - cmd is nil");
			break;
		}
		
		InterfacePtr<IDocSetupCmdData> cmdData(cmd, IID_IDOCSETUPCMDDATA);
		if(cmdData == nil)
		{
			break;
		}
		
		InterfacePtr<IPageSetupPrefs> pageSetupPrefs(doc->GetDocWorkSpace(), UseDefaultIID());
		if(pageSetupPrefs == nil)
		{
			break;
		}
		
		cmdData->SetDocSetupCmdData(::GetUIDRef(doc), 
					 pageSetupPrefs->GetPageSizePref(), 
					 pageSetupPrefs->GetNumPagesPref(), 
					 pageSetupPrefs->GetPagesPerSpreadPref(), 
					 pageSetupPrefs->GetWideOrientationPref(), 
					 pageBinding);
		CmdUtils::ProcessCommand(cmd);
	} while(false);
}

void BscMEInvertFacade::InvertStoriesDirection(IDocument *doc)
{
	IDataBase *db = ::GetDataBase(doc);
	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
	if(!storyList)
		return;
	
	//look through the doc's storylist for framelists
	for (int32 i = 0; i < storyList->GetUserAccessibleStoryCount(); i++)
	{
		UIDRef	storyRef = storyList->GetNthUserAccessibleStoryUID(i);
		if (storyRef == kInvalidUIDRef)
		{
			ASSERT_FAIL("BscMEInvertFacade::InvertStoriesDirection - storyRef is nil");
			continue;
		}
		
		InterfacePtr<ITextModel> textModel(storyList->GetNthUserAccessibleStoryUID(i), UseDefaultIID());
		InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
		
		ASSERT_MSG(frameList != nil, "BscMEInvertFacade::InvertStoriesDirection - frameList is nil");
		
		if (frameList && frameList->GetFrameCount() > 0)
		{
			InterfacePtr<IStoryOptions> storyOptions(textModel, UseDefaultIID());
			InterfacePtr<ICommand> setRTLCmd(CmdUtils::CreateCommand(kSetRToLFrameCmdBoss));
			setRTLCmd->SetItemList(UIDList(frameList));
			InterfacePtr<IBoolData> boolData(setRTLCmd, UseDefaultIID());
			InterfacePtr<ISetMEFrameCmdData> meFrameCmdData(setRTLCmd, UseDefaultIID());
			if (boolData && meFrameCmdData)
			{
				boolData->Set(!storyOptions->IsRightToLeft());
				meFrameCmdData->SetType(storyOptions->IsRightToLeft() ? ISetMEFrameCmdData::kLeft : ISetMEFrameCmdData::kRight);
				CmdUtils::ProcessCommand(setRTLCmd);
			}
		}
	}
}

void BscMEInvertFacade::ChangeTablesDirection(IDocument *doc)
{
	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
	if (storyList)
	{
		//look through the doc's storylist for framelists
		for (int32 i = 0; i < storyList->GetUserAccessibleStoryCount(); i++)
		{
			UIDRef storyRef = storyList->GetNthUserAccessibleStoryUID(i);
			if (storyRef == kInvalidUIDRef)
			{
				ASSERT_FAIL("BscMEInvertFacade::ChangeTableDirection - storyRef is nil");
				continue;
			}
			
			this->ChangeTablesDirection(storyRef);
		}
	}
}

void BscMEInvertFacade::ChangeTablesDirection(UIDRef& story)
{
	do
	{
	    InterfacePtr<ITextModel> textModel(story, UseDefaultIID());
		if(textModel == nil)
			break;
		
		// Get the table model list on kTextStoryBoss.
		InterfacePtr<ITableModelList> tableModelList(story, UseDefaultIID());
		if(tableModelList == nil)
			break;
		
		for(int32 i = 0; i < tableModelList->GetModelCount(); i++)
		{
			InterfacePtr<ITableModel> tableModel(tableModelList->QueryNthModel(i));
			if(tableModel != nil)
			{
				InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
				ASSERT_MSG(tableCommands != nil, "BscMEInvertFacade::IterateAllTablesInStory nil table model");
				Tables::EDirection tableDir = tableModel->GetTableDirection();
				tableCommands->ChangeTableDirection(tableDir == Tables::eLTR ? Tables::eRTL : Tables::eLTR);
			}
		}
	} while (kFalse);
}

void BscMEInvertFacade::InvertPageItemsOfSpread(IDocument* doc, UID spreadUID, const InvertOptions& invertOptions)
{
	do {
		IDataBase* db = ::GetDataBase(doc);

		InterfacePtr<ISpread> spread(db, spreadUID, UseDefaultIID());
		if(spread == nil)
		{
			ASSERT_FAIL("BscMEInvertFacade::InvertPageItemsOfSpread - spread is nil");
			break;
		}
		
		int32 numPages = spread->GetNumPages();		
		for (int32 i = 0; i < numPages; i++)
		{
			UID pageUID = spread->GetNthPageUID(i);
			InterfacePtr<IGeometry> pageGeometry(db, pageUID, UseDefaultIID());
			ASSERT(pageGeometry);
			
			UIDList pageItems(db);
			// Get UIDList of items geographically "owned by" page
			spread->GetItemsOnPage(i, &pageItems, kFalse);
			PMRect pageBounds(pageGeometry->GetStrokeBoundingBox(::InnerToParentMatrix(pageGeometry)));
			
			for (int32 j = pageItems.Length() - 1; j >= 0; j--)
			{
				UIDRef itemRef(pageItems.GetRef(j));
				if (invertOptions.movePageItem)
				{
					this->MovePageItem(itemRef, pageBounds);
				}

				// Object angle flip
				if (invertOptions.flipObjectAngle)
				{
					this->InvertAngleOfObject(itemRef);
				}				
			}
		}
		
	} while(false);
}

void BscMEInvertFacade::InvertAngleOfObject(const UIDRef& pageItem)
{
	do {
		InterfacePtr<ITransform> itemTrans(pageItem, IID_ITRANSFORM);
		if(itemTrans == nil)
		{
			ASSERT_FAIL("BscMEInvertFacade::InvertAngleOfObject - itemTrans is nil");
			break;
		}
		
		PMReal angle = itemTrans->GetItemRotationAngle();
		if(angle == 0)
			break;
		
		angle = 360.0 - angle;
		// Compute the center of the item from where rotate will be process
		InterfacePtr<ITransformPanelPrefs> transforPrefs((ITransformPanelPrefs*)::QuerySessionPreferences(IID_ITRANSFORMPANELPREFERENCES));		
		Geometry::BoundsKind useStroke = transforPrefs != nil ? transforPrefs->GetShowStrokeBounds() : Geometry::PathBounds();
		
		InterfacePtr<IGeometry> itemGeo(pageItem, IID_IGEOMETRY);
		const PMRect bounds = itemGeo->GetBoundingBox(useStroke);
		PBPMPolygon4 bounds4(bounds);
		::TransformInnerPolyToPasteboard(itemGeo, &bounds4);
		
		PMPoint refPoint((bounds4[0] + bounds4[2]) / 2);
		Utils<Facade::ITransformFacade>()->TransformItems(pageItem,
														  Transform::PasteboardCoordinates(), 
														  refPoint,
														  Transform::RotateBy(-2.0 * angle));
	} while(false);
}

void BscMEInvertFacade::MovePageItem(const UIDRef& pageItem, const PMRect& pageBounds)
{
	do {
		InterfacePtr<IGeometry> itemGeometry(pageItem, UseDefaultIID());
		ASSERT(itemGeometry);
		if(itemGeometry == nil)
		{
			ASSERT_FAIL("BscMEInvertFacade::MovePageItem - itemGeometry is nil");
			break;
		}
		
		PMRect itemBounds = itemGeometry->GetStrokeBoundingBox(InnerToParentMatrix(itemGeometry));
		
		// Compute the new values where items have to be shift
		PMPoint orginPoint(0, 0);
		const PMReal& pageLeft = pageBounds.Left();
		const PMReal& pageRight = pageBounds.Right();
		
		const PMReal& itemLeft = itemBounds.Left();
		const PMReal& itemRight = itemBounds.Right();
		
		Transform::TransformValue transformValue = Transform::TranslateBy(
																		  (pageRight - itemBounds.Width() - (itemLeft - pageLeft)) - itemLeft,
																		  0);
		
		Utils<Facade::ITransformFacade>()->TransformItems(pageItem,
														  Transform::SpreadCoordinates(), 
														  orginPoint,
														  transformValue);
		
		// look to the wrapping attributes and invert them if required
		InterfacePtr<IStandOffData> pStandOffData(pageItem, UseDefaultIID());
		if (pStandOffData == nil || !pStandOffData->IsActive())
			break;
		
		PMReal leftMargin = pStandOffData->GetMargin(PMRect::kLeftMiddle);
		PMReal rightMargin = pStandOffData->GetMargin(PMRect::kRightMiddle);
		if ((leftMargin != 0) || (rightMargin != 0))
		{
			{
				InterfacePtr<ICommand> marginCmd(CmdUtils::CreateCommand(kStandOffMarginCmdBoss));
				InterfacePtr<IStandOffMarginCmdData> cmdData(marginCmd, UseDefaultIID());
				marginCmd->SetItemList(UIDList (pStandOffData));
				cmdData->SetMargins(IStandOffMarginCmdData::kUnchanged,
									leftMargin,
									IStandOffMarginCmdData::kUnchanged,
									rightMargin);	
				
				CmdUtils::ProcessCommand(marginCmd);
			}
			
			{
				InterfacePtr<ICommand> marginCmd(CmdUtils::CreateCommand(kStandOffMarginCmdBoss));
				InterfacePtr<IStandOffMarginCmdData> cmdData(marginCmd, UseDefaultIID());
				marginCmd->SetItemList(UIDList (pStandOffData));
				cmdData->SetMargins(IStandOffMarginCmdData::kUnchanged,
									PMRect::kLeftMiddle,
									IStandOffMarginCmdData::kUnchanged,
									rightMargin);
				
				CmdUtils::ProcessCommand(marginCmd);
			}
		}

	} while(false);
}
