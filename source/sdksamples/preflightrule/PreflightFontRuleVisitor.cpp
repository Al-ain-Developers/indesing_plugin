//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightrule/PreflightFontRuleVisitor.cpp $
//  
//  Owner: InDesign Developer Technologies
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
#include "ITextModel.h"
#include "IWaxRun.h"
#include "IWaxRenderData.h"
#include "IPMFont.h"
#include "IAttributeStrand.h"
#include "IFontNames.h"
#include "IFontGroup.h"
#include "IPMStream.h"
#include "IPreflightResultRecord.h"
#include "IPreflightAggregatedResultsUtils.h"
#include "IPreflightResultRecordTable.h"
#include "IPreflightTextRangeInfo.h"
#include "IPreflightVisitInfo.h"
#include "IPreflightProfile.h"
#include "IPreflightRuleVisitor.h"
#include "IPreflightWaxInfo.h"
#include "IPreflightResultNodeData.h"

// General includes:
#include "K2Vector.tpp"
#include "CPMUnknown.h"
#include "Utils.h"

// Project includes:
#include "PreflightRuleID.h"
#include "PreflightRuleDataHelper.h"
#include "PreflightRuleConsts.h"

class PreflightFontRuleVisitor : CPMUnknown<IPreflightRuleVisitor>
{
private:

public:
    PreflightFontRuleVisitor(IPMUnknown* iBoss)
        : CPMUnknown<IPreflightRuleVisitor>(iBoss) {}

	/** See IPreflightRuleVisitor::GetClassesToVisit
	*/
    virtual PreflightObjectClassIDVector GetClassesToVisit() const;

	/** See IPreflightRuleVisitor::Visit
	*/
    virtual void Visit(IPreflightVisitInfo* iVisit);

	/** See IPreflightRuleVisitor::AggregateResults
	*/
    virtual void AggregateResults
        (
            const IPreflightProcess* iProcess,
            const IPreflightProcess::NodeIDVector& resultNodes,
            IPreflightAggregatedResults* iResults,
            IPreflightAggregatedResults::NodeID parentID
        ) const;
		
		
	/** See IPreflightRuleVisitor::UpdateRuleData
	*/
	virtual void UpdateRuleData();
	
	/** See IPreflightRuleVisitor::ValidateRuleData
	*/
	virtual ErrorCode ValidateRuleData(const IPreflightRuleData::Key& key, const ScriptData& proposedValue) const;

private:

	void VisitWaxRun(IPreflightVisitInfo* iVisit);
	
	void VisitEmbedDocument(IPreflightVisitInfo* iVisit);

	bool16 IsAllowed(IPreflightRuleData* ruleData, const WideString& fontName);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PreflightFontRuleVisitor, kPreflightFontVisitorImpl)

PreflightObjectClassIDVector PreflightFontRuleVisitor::GetClassesToVisit() const
{
	PreflightObjectClassIDVector classes;
	classes.push_back(kPreflightOM_WaxRun);
	//Process the import file, indd, eps, and pdf
	classes.push_back(kPreflightOM_PDF);
	classes.push_back(kPreflightOM_EPS);
	classes.push_back(kPreflightOM_SVG);
	classes.push_back(kPreflightOM_INDD);
	return classes;
}

void PreflightFontRuleVisitor::Visit(IPreflightVisitInfo* iVisit)
{
	if (iVisit->GetObjectID().GetClassID() == kPreflightOM_WaxRun)
	{
		this->VisitWaxRun(iVisit);
	}
	else 
	{
		this->VisitEmbedDocument(iVisit);
	}
}

void PreflightFontRuleVisitor::AggregateResults
	(
		const IPreflightProcess* iProcess,
		const IPreflightProcess::NodeIDVector& resultNodes,
		IPreflightAggregatedResults* iResults,
		IPreflightAggregatedResults::NodeID parentID
	) const
{
	do {
		Utils<IPreflightAggregatedResultsUtils> iUtils;
		InterfacePtr<const IPreflightResultRecordTable> iRawTable(iUtils->CreateTableFromNodes(iProcess, resultNodes)); 
		if (iRawTable == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iRawTable == NULL!");			
			break;
		}
		
		InterfacePtr<const IPreflightResultRecordTable> iTable(iUtils->ApplyAllStandardAggregations(iProcess, iRawTable));
		if (iTable == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iTable == NULL!");			
			break;
		}

		IPreflightAggregatedResultsUtils::VectorOfTables byObject;
		iUtils->CreateTablesByAuxString(iTable, byObject);
		
		for(int32 i = 0; i < byObject.size(); i++)
		{
			IPreflightResultRecordTable* iObjTable = byObject[i];
			InterfacePtr<const IPreflightResultRecord> iRec(iObjTable->QueryNthRecord(0));
			if (iRec == nil)
			{
				ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iRec == NULL!");			
				break;
			}
			
			PMString fontFamilyName = iRec->GetAuxString();		
			InterfacePtr<IPreflightResultNodeInfo> iNode(iUtils->CreateGenericNode(fontFamilyName,PreflightRuleID()));
			if (iNode == nil)
			{
				ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iNode == NULL!");			
				break;
			}
			
			IPreflightAggregatedResults::NodeID nodeID = iUtils->AddResultsNode(iResults,parentID, iNode);	

			for(int32 j = 0; j < iObjTable->GetRecordCount(); j++) {
				InterfacePtr<const IPreflightResultRecord> iSubRec(iObjTable->QueryNthRecord(j));
				if (iSubRec == nil)
				{
					ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iSubRec == NULL!");			
					break;
				}
				
				InterfacePtr<IPreflightResultNodeInfo> iSubNode(iUtils->CreateViolationNode(iSubRec->GetObjectID()));
				if (iSubRec == nil)
				{
					ASSERT_FAIL("PreflightFontRuleVisitor::AggregateResults: iSubRec == NULL!");			
					break;
				}

				InterfacePtr<IPreflightResultNodeData> iData(iSubNode, UseDefaultIID());
				iData->AddInfoString(IPreflightResultNodeData::kFieldProblem, kProblemMessageKey);
				iData->AddInfoString(IPreflightResultNodeData::kFieldFix, kFixMessageKey);
				
				iUtils->AddResultsNode(iResults, nodeID, iSubNode);	
			}
		}	
	} while(false);	
}

void PreflightFontRuleVisitor::UpdateRuleData()
{
	InterfacePtr<IPreflightRuleData> ruleData(this, UseDefaultIID());
	if(ruleData == nil)
	{
		ASSERT_FAIL("Miss IPreflightRuleData interface");
		return;
	}
	
	bool exist = false;
	ScriptData data;
	ruleData->GetData (kSDKFontRuleParameter, ScriptData(), data, &exist);
	if(!exist)
	{
		ScriptListData scrListData;
		data.SetList(scrListData);
		ruleData->SetData(kSDKFontRuleParameter, data);
	}
}

void PreflightFontRuleVisitor::VisitWaxRun(IPreflightVisitInfo* iVisit)
{
	do{			
		PreflightObjectID id = iVisit->GetObjectID();
		InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());
		if (iObj == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: IPreflightObject == NULL!");			
			break;
		}
		
		InterfacePtr<IPreflightWaxInfo>	iWax(iObj, UseDefaultIID());
		if (iWax == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: IPreflightWaxInfo == NULL!");			
			break;
		}

		InterfacePtr<const IWaxRun> iRun(iWax->QueryRun());
		if (iRun == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: IWaxRun == NULL!");			
			break;
		}
		
		InterfacePtr<const IWaxRenderData> iRender(iRun, UseDefaultIID());
		if (iRender == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: iRender == NULL!");			
			break;
		}


		InterfacePtr<IPMFont> font(iRender->QueryFont());
		if (font == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: font == NULL!");			
			break;
		}

		PMString fontFamilyName;
		font->AppendFamilyName(fontFamilyName);

		InterfacePtr<IPreflightRuleData>	iRuleData (this, UseDefaultIID ());

		WideString wsFontFamilyName(fontFamilyName);
		if(IsAllowed(iRuleData, wsFontFamilyName)) {
			break;
		}

		const IWaxLine* waxLine = iRun->GetWaxLine();
		InterfacePtr<ITextModel> textModel(waxLine->QueryTextModel());
		if (textModel == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: textModel == NULL!");			
			break;
		}
		
		TextIndex startIndex = iRun->TextOrigin();

		InterfacePtr<IAttributeStrand> strand( (IAttributeStrand*)textModel->QueryStrand( kCharAttrStrandBoss, IID_IATTRIBUTESTRAND ) ) ;
		if (strand == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: strand == NULL!");			
			break;
		}
		//variable "start" store the same value for jointed text runs with same font attribute 
		TextIndex start = 0;
		int32 length = 0;
		strand->GetStyleUID( startIndex, &length, &start );	
			
		InterfacePtr<IPreflightResultRecord> iRec(iVisit->CreateResultRecord());
		if (iRec == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: iRec == NULL!");			
			break;
		}
			
		iRec->SetCriteria(kPreflightRC_Default);
		iRec->SetAuxString(fontFamilyName);		
		iRec->AddValue(start);
		
	} while(false);
}
	
void PreflightFontRuleVisitor::VisitEmbedDocument(IPreflightVisitInfo* iVisit)
{
	do{			
		PreflightObjectID id = iVisit->GetObjectID();
		InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());
		if (iObj == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: IPreflightObject == NULL!");			
			break;
		}
		
		InterfacePtr<IFontNames> iFontNames(iObj->GetModelRef(), UseDefaultIID());
		if (iFontNames == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: iFontNames == NULL!");			
			break;
		}
		
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), IID_IFONTMGR);
		if (fontMgr == nil)
		{
			ASSERT_FAIL("PreflightFontRuleVisitor::Visit: fontMgr == NULL!");			
			break;
		}

		InterfacePtr<IPreflightRuleData>	iRuleData (this, UseDefaultIID ());

		K2Vector<PMString> fonts;
		iFontNames->FontsNeeded(fonts);
		for(K2Vector<PMString>::iterator f = fonts.begin(), l = fonts.end(); f != l; ++f) {		
			InterfacePtr<IPreflightResultRecord> iRec(iVisit->CreateResultRecord());	
			if (iRec == nil)
			{
				ASSERT_FAIL("PreflightFontRuleVisitor::Visit: iRec == NULL!");			
				break;
			}
			
			InterfacePtr<IPMFont> embededFont(fontMgr->QueryFont(*f));
			PMString embededFontFamilyName; 
			embededFont->AppendFamilyName(embededFontFamilyName);
			WideString wsEmbededFontFamilyName(embededFontFamilyName);
			if(!IsAllowed(iRuleData, wsEmbededFontFamilyName))
			{
				iRec->SetCriteria(kPreflightRC_Default);
				iRec->SetAuxString(embededFontFamilyName);		
			}
		}
		
	} while(false);
}

ErrorCode PreflightFontRuleVisitor::ValidateRuleData(const IPreflightRuleData::Key& key, const ScriptData& proposedValue) const
{
	return kSuccess;
}


bool16 PreflightFontRuleVisitor::IsAllowed(IPreflightRuleData* ruleData, const WideString& fontName)
{
	do {	
		if(ruleData == nil)
		{
			ASSERT_FAIL("Miss IPreflightRuleData interface");
			break;
		}
		
		bool exist = false;
		ScriptData data;
		ruleData->GetData (kSDKFontRuleParameter, ScriptData(), data, &exist);
		if(!exist || data.GetType() != ScriptData::s_list)
			break;
			
		ScriptListData scrListData;
		data.GetList(scrListData);
		WideString disallowedName;
		for(int32 i = 0; i < scrListData.size(); ++i)
		{			
			scrListData[i].GetWideString(disallowedName);
			if(fontName == disallowedName)
				return kFalse;
		}
	} while(false);

	return kTrue;
}
