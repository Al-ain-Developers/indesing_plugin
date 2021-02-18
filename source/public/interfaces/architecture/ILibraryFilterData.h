//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryFilterData.h $
//  
//  Owner: Tim Gogolin
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  Store and retrieve information needed to create a Library query on a catalog
//  of assets.  The "Show Subset" dialog will fill in these fields and they can be
//  retrieved to create a database query.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryFilterData__
#define __ILibraryFilterData__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "ILibraryAssetMetaData.h"


class GlobalTime;


/** "SimpleFilter" corresponds to a single search specification line from the Library Show Subset dialog.
*/
class ILibrarySimpleFilterData : public IPMUnknown
{
	public:	
	
	/** Type of filter.  Need to keep these in sync with order defined by popup menu on dialog.
	*/
	typedef enum 
	{
		/** Type filter
		*/
		Field_Type,
		/** Date filter
		*/
		Field_Date,
		/** Name filter
		*/
		Field_Name,
		/** Description filter
		*/
		Field_Description
	} EField;
	
	/** Condition used in filter.
	*/
	typedef enum 
	{
		/** Equality comparison
		*/
		Condition_Equal,
		/** Inequality comparison
		*/
		Condition_NotEqual,
		/** Greater than comparison
		*/
		Condition_GreaterThan,
		/** Less than comparison
		*/
		Condition_LessThan,
		/** Containment comparison
		*/
		Condition_Contains,
		/** Exclusion comparison
		*/
		Condition_DoesNotContain,
		/** Sentinal value for storing at the end of arrays
		*/
		Condition_Undefined 
	} ECondition;
	
	/** Set the filter type to a name filter on the supplied name.
		@param inCondition IN condition to use
		@param inString IN value to compare to
	*/
	virtual void SetNameFilter(ECondition inCondition, const PMString& inString) = 0;

	/** Set the filter type to a description filter on the supplied description string.
		@param inCondition IN condition to use
		@param inString IN value to compare to
	*/
	virtual void SetDescriptionFilter(ECondition inCondition, const PMString& inString) = 0;

	/** Set the filter type to a date filter on the supplied time.
		@param inCondition IN condition to use
		@param inTime IN value to compare to
	*/
	virtual void SetDateFilter(ECondition inCondition, const GlobalTime& inTime) = 0;

	/** Set the filter type to a type filter on the supplied type.
		@param inCondition IN condition to use
		@param inType IN value to compare to
	*/
	virtual void SetTypeFilter(ECondition inCondition, ILibraryAssetMetaData::UserType inType) = 0;
	
	/** Gets the filter type.
		@return the type of filter
	*/
	virtual EField GetFilterField() = 0;
	
	/** Get the condition and name for the name filter.
		@param outCondition OUT the condition used
		@param outString OUT the name value used
	*/
	virtual void GetNameFilter(ECondition& outCondition, PMString& outString) = 0;
	
	/** Get the condition and data for the description filter.
		@param outCondition OUT the condition used
		@param outString OUT the description used
	*/
	virtual void GetDescriptionFilter(ECondition& outCondition, PMString& outString) = 0;
	
	/** Get the condition and date value for the date filter.
		@param outCondition OUT the condition used
		@param outTime OUT the date value used
	*/
	virtual void GetDateFilter(ECondition& outCondition, GlobalTime& outTime) = 0;
	
	/** Get the condition and type for the type filter.
		@param outCondition OUT the condition used
		@param outType OUT the user type used
	*/
	virtual void GetTypeFilter(ECondition& outCondition, ILibraryAssetMetaData::UserType& outType) = 0;
	
	/** Tests the asset data to see if it passes the filter criteria.
		@param inAssetData IN metadata to test
		@return kTrue if criteria is met, kFalse otherwise
	*/
	virtual bool16 PassFilter(ILibraryAssetMetaData* inAssetData) = 0;
};


/** "ComplexFilter" is a collection of "SimpleFilters" which corresponds to multiple search
	specification lines from the Library Show Subset dialog.
	@see ILibrarySimpleFilterData
*/
class ILibraryComplexFilterData : public IPMUnknown
{
	public:
	/** Conjunction to join the multiple tests.
	*/
	typedef enum 
	{
		/** Use AND
		*/
		Conjunction_And,
		/** Use OR
		*/
		Conjunction_Or
	} EConjunction;

	/** Set the logical conjuction of the multiple simple filters.
		@param inConjunction IN the conjunction to use
	*/
	virtual void SetConjunction(EConjunction inConjunction) = 0;

	/** Get the logical conjuction of the multiple simple filters.
		@return  the conjunction used
	*/
	virtual EConjunction GetConjunction() = 0;
	
	/** Create a new Simple Filer and append it to the complex filter.
		The caller must then initialize the new simple filter with the appropriate data.
		@return the filter boss UIDRef for a simple filter being added
	*/
	virtual UIDRef AppendNewSimpleFilter() = 0;
	
	/** Return the number of simple filters in this complex filter.
		@return the number of simple filters.
	*/
	virtual int32 GetNumSimpleFilters() = 0;
	
	/** Get the UIDRef of the simple filter at the specified index.
		@param i IN index of simple filter
		@return the filter boss UIDRef of the simple filter sought
	*/
	virtual UIDRef GetSimpleFilterAt(int32 i) = 0;
	
	/** Tests the asset data to see if it passes the filter criteria.
		@param inAssetData IN metadata to test
		@return kTrue if criteria met, kFalse otherwise
	*/
	virtual bool16 PassFilter(ILibraryAssetMetaData* inAssetData) = 0;
};

#endif // __ILibraryFilterData__
