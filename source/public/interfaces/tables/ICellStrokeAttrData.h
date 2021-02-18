//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellStrokeAttrData.h $
//  
//  Owner: Joe Shankar
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

#pragma once
#ifndef __ICellStrokeAttrData__
#define __ICellStrokeAttrData__

#include "IPMUnknown.h"
#include "TableTypes.h"
#include "ITableLineType.h"

/**
	Carries cell stroke attribute information. Data indicates
	the attributes being carried, the sides of the cell to which
	they apply e.g. the top or bottom and their values. This interface 
	is used to manipulate cell stroke attributes efficiently as a set, 
	rather than having to operate on them individually. 
*/
class ICellStrokeAttrData : public IPMUnknown
{
public:
	enum  { kDefaultIID = IID_CELLSTROKEATTRIBUTEDATA };

	/**
		Types of attribute the data interface can carry. 
		Enumerators can be OR'd into a bitmask if more than 
		one attribute is to be operated on.
	*/
	enum EAttributes
	{
		/** */
		eNoAttrs		= 0,
		/** */
		eWeight			= 1,
		/** */
		eColor			= 2,
		/** */
		eLineType		= 4,
		/** */
		eTint			= 8,
		/** */
		eOverprint		= 16,
		/** */
		eGapColor		= 32,
		/** */
		eGapTint		= 64,
		/** */
		eGapOverprint	= 128,
		/** */
		eAllAttrs	 	= 255
	};

	/**
		Stores the types of attribute being carried.
	*/
	class Attributes
	{
	public:
		explicit Attributes(EAttributes a) : attrs(a) {}
		Attributes() : attrs(eNoAttrs) {}

		/**
			Adds the given attribute to those being carried.
		*/
		void Add(EAttributes other)
		{
			ASSERT(other >= eNoAttrs && other <= eAllAttrs );

			attrs = (EAttributes)((uint32)attrs | (uint32)other);
			ASSERT(attrs >= eNoAttrs && attrs <= eAllAttrs);
		};

		/**
			Removes the given attribute from those being carried.
		*/
		void Remove(EAttributes remove)
		{
			ASSERT(remove >= eNoAttrs && remove <= eAllAttrs);

			EAttributes mask = (EAttributes)(~(uint32)remove);
			attrs = (EAttributes)((uint32)attrs & (uint32)mask);
			
			ASSERT(attrs >= eNoAttrs && attrs <= eAllAttrs);
		}

		/**
			Returns the attributes currenly being carried.
		*/
		operator EAttributes() const { return attrs; }

		/**
			Returns true if the given attributes are being carried.
		*/
		bool IsSet(EAttributes other) const
		{
			ASSERT(other >= eNoAttrs && other <= eAllAttrs );
			return ((uint32)attrs & (uint32)other) != 0;
		};

		/**
			Set the attributes being carried, overwrites any
			previous state.
		*/
		void Set(EAttributes other)
		{
			ASSERT(other >= eNoAttrs && other <= eAllAttrs );
			attrs = other;
		};
	
	private:
		EAttributes attrs;
	};

	/**
		Indicates the sides of the cell, the attributes being carried and their data values.
	*/
	struct Data
	{
		Data() : 
			sides(Tables::eNoSides),
			attrs(eNoAttrs),
			weight(0.0),
			color(kInvalidUID),
			tintPercent(100.0),
			overprint(kFalse),
			gapColor(kInvalidUID),
			gapTintPercent(100.0),
			gapOverprint(kFalse),
			lineType(kSolidPathStrokerBoss, kInvalidUID) { }
		/** Enumerators can be OR'd into a bitmask to indicate the sides to be operated on. */
		Tables::ESelectionSides	sides;
		/** Enumerators can be OR'd into a bitmask to indicate the attributes to be operated on. */
		Attributes				attrs;
		/** */
		PMReal					weight;
		/** UID of stroke color can be used to instantiate IColorData 
		or to find the swatch by UID in ISwatchList. */
		UID						color;
		/** */
		PMReal					tintPercent;
		/** */
		bool16					overprint;
		/** */
		UID						gapColor;
		/** */
		PMReal					gapTintPercent;
		/** */
		bool16					gapOverprint;
		/** */
		ITableLineType::SType	lineType;		
	};

	/**
		Get the data being carried.
		@return description of cell stroke attribute data being carried.
	*/
	virtual Data Get(void) const = 0;

	/**
		Set the data being carried.
		@param strokeData cell stroke attribute data to be carried.
	*/
	virtual void Set(const Data& strokeData) = 0;
};




#endif