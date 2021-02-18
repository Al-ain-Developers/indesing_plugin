//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tableattributes/TblAttQueryMutHelper.cpp $
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
// Interface includes
#include "ITableAttrRealNumber.h"
#include "ISelectionManager.h"
#include "ITableSuite.h"
#include "ISelectionUtils.h"
// Impl includes
#include "AttributeBossList.h"
// project related includes

#include "TblAttQueryMutHelper.h"

/* Constructor
*/
TblAttQueryMutHelper::TblAttQueryMutHelper()
{
}

/* Destructor
*/
TblAttQueryMutHelper::~TblAttQueryMutHelper()
{
}

/* IsValidCondition
*/
bool16 TblAttQueryMutHelper::IsValidCondition()
{
	bool16 retval = kFalse;
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite* >
											 ( Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}

		if (tableSuite->CanApplyCellOverrides())
		{
			retval=kTrue;
		}
	} while (kFalse);
	return retval;
}

/* SetCellAttributeReal
*/
void TblAttQueryMutHelper::SetCellAttributeReal(const ClassID& classID, const PMReal realParam)
{
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite* >
											 ( Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}

		if (tableSuite->CanApplyCellOverrides())
		{
			InterfacePtr<ITableAttrRealNumber> realNumber(::CreateObject2<ITableAttrRealNumber>(classID));
			ASSERT(realNumber);
			if (realNumber==nil)
			{
				break;
			}
			realNumber->Set( realParam );

			AttributeBossList attrs;
			attrs.ApplyAttribute(realNumber);

			tableSuite->ApplyCellOverrides(&attrs);
		}

	} while (kFalse);
}

/* SetTableAttributeReal
*/
void TblAttQueryMutHelper::SetTableAttributeReal(const ClassID& classID, const PMReal realParam)
{
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite* >
											 ( Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}
		if (tableSuite->CanApplyTableOverrides())
		{
			InterfacePtr<ITableAttrRealNumber> realNumber(::CreateObject2<ITableAttrRealNumber>(classID));
			ASSERT(realNumber);
			if (realNumber==nil)
			{
				break;
			}
			realNumber->Set( realParam );

			AttributeBossList attrs;
			attrs.ApplyAttribute(realNumber);

			tableSuite->ApplyTableOverrides(&attrs);
		}

	} while (kFalse);
}

/* SetCellStroke
*/
void TblAttQueryMutHelper::SetCellStroke(const Tables::ESelectionSides sides, const PMReal strokeWeight)
{
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite*>
											 (Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}

		// Be extremely paranoid; we shouldn't be in here if we can't do this but check again.
		if (!tableSuite->CanApplyCellOverrides())
		{
			break;
		}

		ICellStrokeAttrData::Data data;
		data.sides = sides;
		data.attrs.Set(ICellStrokeAttrData::eWeight);
		data.weight = strokeWeight;
		bool16 canApplyStrokes = tableSuite->CanApplyCellStrokes(data);
		if (canApplyStrokes == kTrue)
		{
			tableSuite->ApplyCellStrokes(data);
		}
		else
		{
			ASSERT_FAIL("Could not apply cell strokes!");
		}
	} while (false);
}

/*	GetCellAttributeReal
*/
PMReal TblAttQueryMutHelper::GetCellAttributeReal(const ClassID& classID)
{
	PMReal retval = (-1.0f);
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite* >
											 ( Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}
		// Be extremely paranoid; we shouldn't be in here if we can't do this but check again.
		if (!tableSuite->CanApplyCellOverrides())
		{
			break;
		}

		ASSERT(classID.IsValid());
		if (!classID.IsValid())
		{
			break;
		}

		bool16 uniqueAttributeValue = tableSuite->CanGetCellAttribute(classID);

		if (uniqueAttributeValue == kTrue)
		{
			InterfacePtr<const IPMUnknown> attr(tableSuite->QueryCellAttribute(classID));
			ASSERT(attr);
			if (attr== nil)
			{
				break;
			}

			InterfacePtr<const ITableAttrRealNumber> weight(attr, UseDefaultIID());
			ASSERT(weight);
			if (weight == nil)
			{
				break;
			}
			retval = weight->Get();
		}
	} while (kFalse);
	return retval;
}

/* GetTableAttributeReal
*/
PMReal TblAttQueryMutHelper::GetTableAttributeReal(const ClassID& classID)
{
	PMReal retval = (-1.0f);
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite* >
											 ( Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}

		// Be extremely paranoid
		if (!tableSuite->CanApplyTableOverrides())
		{
			break;
		}

		ASSERT(classID.IsValid());
		if (!classID.IsValid())
		{
			break;
		}

		InterfacePtr<const IPMUnknown> attr(tableSuite->QueryTableAttribute(classID));
		ASSERT(attr);
		if (attr==nil) break;

		InterfacePtr<const ITableAttrRealNumber> weight(attr, UseDefaultIID());
		ASSERT(weight);
		if (weight==nil) break;
		retval = weight->Get();
	} while (kFalse);

	return retval;
}

/* GetCellStroke
*/
PMReal TblAttQueryMutHelper::GetCellStroke(const Tables::ESelectionSides sides)
{
	PMReal strokeWeight = (-1.0f);
	do
	{
		InterfacePtr<ITableSuite> tableSuite(static_cast<ITableSuite*>
											 (Utils<ISelectionUtils>()->QuerySuite(ITableSuite::kDefaultIID))); 
		if (tableSuite == nil)
		{
			break;
		}

		// Be extremely paranoid; we shouldn't be in here if we can't do this but check again.
		if (!tableSuite->CanApplyCellOverrides())
		{
			break;
		}

		ICellStrokeAttrData::Data data;
		data.sides = sides;
		data.attrs.Set(ICellStrokeAttrData::eWeight);
		data.weight = strokeWeight; // set the default
		bool16 canGetStrokes = tableSuite->CanGetCellStrokes(data);
		if (canGetStrokes == kTrue)
		{
			tableSuite->GetCellStrokes(data);
			strokeWeight = data.weight;
		}

	} while (false);
	return strokeWeight;
}

// End, TblAttQueryMutHelper.cpp.
