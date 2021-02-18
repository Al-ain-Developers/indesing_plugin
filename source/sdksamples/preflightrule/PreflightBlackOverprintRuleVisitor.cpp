//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightrule/PreflightBlackOverprintRuleVisitor.cpp $
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
#include "IPreflightResultRecord.h"
#include "IPreflightAggregatedResultsUtils.h"
#include "IPreflightResultRecordTable.h"
#include "IPreflightVisitInfo.h"
#include "IPreflightProfile.h"
#include "IPreflightRuleVisitor.h"
#include "IPreflightResultNodeData.h"
#include "IPreflightArtworkContext.h"
#include "IPreflightArtworkPaintInfo.h"
#include "IPreflightArtworkMarkInfo.h"
#include "IPreflightArtworkCSInfo.h"
// General includes:
#include "CPMUnknown.h"
#include "StringUtils.h"
#include "CAlert.h"

// Project includes:
#include "PreflightRuleID.h"
#include "TemplateDefs.h"
#include "K2Vector.tpp"
#include "PreflightRuleDataHelper.h"

class PreflightBlackOverprintRuleVisitor : CPMUnknown<IPreflightRuleVisitor>
{


public:
    PreflightBlackOverprintRuleVisitor(IPMUnknown* iBoss)
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
	virtual bool IsBlack(IPreflightArtworkPaintInfo* iPaintInfo, const PMReal& tolerance = 0.001) const;

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PreflightBlackOverprintRuleVisitor, kPreflightBlackOverprintVisitorImpl)

void PreflightBlackOverprintRuleVisitor::UpdateRuleData()
{
}

ErrorCode PreflightBlackOverprintRuleVisitor::ValidateRuleData(const IPreflightRuleData::Key& key, const ScriptData& proposedValue) const
{
    return kSuccess;
}

PreflightObjectClassIDVector PreflightBlackOverprintRuleVisitor::GetClassesToVisit() const
{
    PreflightObjectClassIDVector classes;
	classes.push_back(kPreflightOM_ArtworkMark);
    return classes;
}

void PreflightBlackOverprintRuleVisitor::Visit(IPreflightVisitInfo* iVisit)
{
   do {
		InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());
		if (iObj == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::Visit: iObj == NULL!");			
			break;
		}
		
		InterfacePtr<IPreflightArtworkContext> iContext(iObj, UseDefaultIID());
		if (iContext == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::Visit: iContext == NULL!");			
			break;
		}

		 if (iContext->GetShapeContextDepth(kPreflightOSP_GraphicProxy) <= 0)
		{
			InterfacePtr<IPreflightArtworkMarkInfo> iMark(iObj, UseDefaultIID());
			if (iMark == nil)
			{
				ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::Visit: iMark == NULL!");			
				break;
			}
			
			InterfacePtr<IPreflightArtworkPaintInfo> iColor(iMark->QueryColorPaintInfo());
			if (iColor == nil)
			{
				ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::Visit: iColor == NULL!");			
				break;
			}
			//if the marking artworks are overprinted and with black color
			if (iMark->GetOverprint() && IsBlack(iColor))
			{
				InterfacePtr<IPreflightResultRecord> iRec(iVisit->CreateResultRecord());
				if (iRec == nil)
				{
					ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::Visit: iRec == NULL!");			
					break;
				}
				iRec->SetCriteria(kPreflightRC_Default);
			}
		}
	} while(false);
}

void PreflightBlackOverprintRuleVisitor::AggregateResults
    (
        const IPreflightProcess* iProcess,
        const IPreflightProcess::NodeIDVector& resultNodes,
        IPreflightAggregatedResults* iResults,
        IPreflightAggregatedResults::NodeID parentID
    ) const
{
    do {
		Utils<IPreflightAggregatedResultsUtils> iUtils;
		InterfacePtr<IPreflightRuleInfo> iRuleInfo(this, UseDefaultIID());
		if (iRuleInfo == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iRuleInfo == NULL!");			
			break;
		}
		
		PreflightRuleID ruleID = iRuleInfo->GetRuleID();

		InterfacePtr<const IPreflightResultRecordTable> iRawTable(iUtils->CreateTableFromNodes(iProcess, resultNodes));
		if (iRawTable == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iRawTable == NULL!");			
			break;
		}
		
		InterfacePtr<const IPreflightResultRecordTable> iTable(iUtils->ApplyAllStandardAggregations(iProcess, iRawTable));
		if (iTable == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iTable == NULL!");			
			break;
		}

		InterfacePtr<IPreflightResultRecordTable> iViolations(iUtils->CreateSubTableByCriteria(iTable, kPreflightRC_Default));
		if (iViolations)
		{
			IPreflightAggregatedResults::NodeID localParentID = iUtils->AddCriteriaNode(iResults, parentID, PMString(kSDKBlackOverprintCategoryKey), ruleID);
			if (localParentID == 0)
			{
				ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: localParentID == NULL!");			
				break;
			}

			IPreflightAggregatedResultsUtils::VectorOfTables byObject;
			iUtils->CreateTablesByObject(iTable, byObject);
			int32 i, n;

			for(i = 0; i < byObject.size(); i++)
			{
				IPreflightResultRecordTable* iObjTable = byObject[i];
				InterfacePtr<const IPreflightResultRecord> iRec(iObjTable->QueryNthRecord(0));
				if (iRec == nil)
				{
					ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iRec == NULL!");			
					break;
				}

				InterfacePtr<IPreflightResultNodeInfo> iNode(iUtils->CreateViolationNode(iRec->GetObjectID()));
				if (iNode == nil)
				{
					ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iNode == NULL!");			
					break;
				}

				InterfacePtr<IPreflightResultNodeData> iData(iNode, UseDefaultIID());
				if (iData == nil)
				{
					ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iData == NULL!");			
					break;
				}
				// For each subpart create its own Problem line.

				for(n = 0; n < iObjTable->GetRecordCount(); n++)
				{
					InterfacePtr<const IPreflightResultRecord> iSubPartRec(iObjTable->QueryNthRecord(n));
					if (iSubPartRec == nil)
					{
						ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::AggregateResults: iSubPartRec == NULL!");			
						break;
					}
					// Problem string
					PMString sProblem(kSDKBlackOverprintRuleProblem);
					sProblem.Translate();
					StringUtils::ReplaceStringParameters(&sProblem, iUtils->GetSubpartsDescription(iSubPartRec));
					

					iData->AddInfoString(IPreflightResultNodeData::kFieldProblem, sProblem);
				}

				iData->AddInfoString(IPreflightResultNodeData::kFieldFix, PMString(kSDKBlackOverprintRuleFix));
				iUtils->AddResultsNode(iResults, localParentID, iNode);
			}
		}
	} while(false);
}

 bool PreflightBlackOverprintRuleVisitor::IsBlack(IPreflightArtworkPaintInfo* iPaintInfo, const PMReal& tolerance) const
{
	bool16 isBlack = kFalse;
	do {
		int spatial = iPaintInfo->GetSpatialType();		
		InterfacePtr<IPreflightArtworkCSInfo> artworkCSInfo(iPaintInfo->QueryColorSpace());
		if (artworkCSInfo == nil)
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::IsBlack: artworkCSInfo == NULL!");			
			break;
		}
		if (spatial != IPreflightArtworkPaintInfo::kPaintSpatial_Constant) break;   
		
		//get color channel map
		const K2Vector<int32> comps = artworkCSInfo->GetColorChannelsMap();
		//get the color values	
		K2Vector<PMReal> constantComps;
		iPaintInfo->GetConstantColorValues(&constantComps);


		if (artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_Gray
			|| artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_RGB
            || artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_HSB
			|| artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_LAB)
		{
			// all components must be 0.
			isBlack = kTrue;
			for(int32 i = 0; i < comps.size() && isBlack; i ++)
			{		
				isBlack = (constantComps[comps[i]] <= tolerance);
			}
		}
		else if (artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_CMYK)          
		{
			// last components must be 1
			isBlack = (constantComps[3] >= (1.0 - tolerance));
	        
		}
		else if (artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_DeviceN
				||artworkCSInfo->GetType() == IPreflightArtworkCSInfo::kCS_NChannel)
		{
			// all components must be 1.
			CAlert::ModalAlert
			(
				kPreflightNotUsedColorSpaceStringKey,				// Alert string
				kOKString,							// OK button
				kNullString, 						// No second button
				kNullString, 						// No third button
				1,									// Set OK button to default
				CAlert::eInformationIcon			// Information icon.
			);
		}
		else
		{
			ASSERT_FAIL("PreflightBlackOverprintRuleVisitor::IsBlack: Unexpected colorspace.");
			break;
		}
	} while(false);

    return isBlack;
}
