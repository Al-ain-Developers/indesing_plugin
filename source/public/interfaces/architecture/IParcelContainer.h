//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IParcelContainer.h $
//  
//  Owner: dwaterfa
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
#ifndef __IParcelContainer__
#define __IParcelContainer__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "ITextColumnSizer.h"

#include "ShuksanID.h"
#include "ParcelKey.h"

class IParcelList;


class PUBLIC_DECL IParcelContainer : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPARCELCONTAINER };

		/**
		The IParcelList our Parcels are associated with.
		*/
		virtual IParcelList *	QueryParcelList() const = 0;

		/**
		All Parcel content bounds will be within the bounds of the Container.
		*/
		virtual PMRect			GetBounds() const = 0;

		/**
		Callers would like to know if the base tiled shape, separate from the
		external wraps, of the ParcelContainer is a rectangle.
		
		This is an important performance benefit because it means that all the
		Parcels will thus tile rectangular, unless there are wraps which are
		known to the ITextParcelListData for the Parcel.

		Also, note that the Parcel do have a to-(wax)Content-Matrix which might
		make the *effective* tileable area non-rectangular even though the
		Parcel was rectangular.

		No attempt is made to separate out if individual Parcels are rectangular
		or not - if the Container is then the ContainerComposer will assume that
		any of them could be an act accordingly.

		@return kTrue if the tileable shape is rectangular.
		*/
		virtual bool16			GetIsRectangular(bool16 checkCornerRadius = kFalse) const = 0;

		/**
		The number of columns in the Container.
		*/
		virtual uint32			GetColumnCount() const = 0;

		/**
		*/
		virtual PMRect			GetNthColumnBBox(uint32 n) const = 0;

		/**
		The number of Parcels in the container.
		*/
		virtual uint32			GetParcelCount() const = 0;

		/**
		Returns the ParcelKey of the nTH Parcel in the Container.
		*/
		virtual ParcelKey		GetNthParcelKey(uint32 containerIndex) const = 0;

		/**
		Returns the index of the Parcel in the Container. It is
		permissable to pass in a key which is NOT in the container
		which will result in a -1 being returned. This is sometime
		useful.
		*/
		virtual int32			GetParcelIndex(ParcelKey key) const = 0;

		/**
		Returns the first ParcelKey of the Container. This is equivalent to
		calling GetNthParcelKey(0).
		*/
		virtual ParcelKey		GetFirstParcelKey() const = 0;

		/**
		Returns the last ParcelKey of the Container. This is equivalent to
		calling GetNthParcelKey(GetParcelCount() - 1).
		*/
		virtual ParcelKey		GetLastParcelKey() const = 0;

		/**
		This helper class specifies the span data for a Parcel.
		*/
		class PUBLIC_DECL ParcelSpanData
		{
		public:
			/**
			Default constructor. Does not create anything useful but needed as
			a placeholder. All members will be undefined.
			*/
			ParcelSpanData();

			/**
			Constructs a single at the specified column index
			*/
			ParcelSpanData(uint32 columnIndexStart) :
				fSpanType(ICompositionStyle::kSingleColumn),
				fPColIndexStart(columnIndexStart),
				fPColIndexEnd(columnIndexStart + 1),
				fDesiredSpan(1),
				fSplitIndex(0),
				fSplitCount(0),
				fSplitInsideGutter(0.0),
				fSplitOutsideGutter(0.0)
				{ }

			/**
			Constructs a span at the specified column index range
			*/
			ParcelSpanData(uint32 columnIndexStart,
							uint32 columnIndexEnd,
							uint32 desiredSpan) :
				fSpanType(ICompositionStyle::kSpanColumn),
				fPColIndexStart(columnIndexStart),
				fPColIndexEnd(columnIndexEnd),
				fDesiredSpan(desiredSpan),
				fSplitIndex(0),
				fSplitCount(0),
				fSplitInsideGutter(0.0),
				fSplitOutsideGutter(0.0)
				{ }

			/**
			Constructs a split at the specified column index
			*/
			ParcelSpanData(uint32 columnIndexStart,
							uint32 splitIndex,
							uint32 splitCount,
							PMReal splitInsideGutter,
							PMReal splitOutsideGutter) :
				fSpanType(ICompositionStyle::kSplitColumn),
				fPColIndexStart(columnIndexStart),
				fPColIndexEnd(columnIndexStart + 1),
				fDesiredSpan(1),
				fSplitIndex(splitIndex),
				fSplitCount(splitCount),
				fSplitInsideGutter(splitInsideGutter),
				fSplitOutsideGutter(splitOutsideGutter)
				{ }

			/**
			Copy constructor
			*/
			ParcelSpanData(const ParcelSpanData& other) :
				fSpanType(other.fSpanType),
				fPColIndexStart(other.fPColIndexStart),
				fPColIndexEnd(other.fPColIndexEnd),
				fDesiredSpan(other.fDesiredSpan),
				fSplitIndex(other.fSplitIndex),
				fSplitCount(other.fSplitCount),
				fSplitInsideGutter(other.fSplitInsideGutter),
				fSplitOutsideGutter(other.fSplitOutsideGutter)
				{ }

			/**
			This equality operator only checks that the column type information
			is the same, NOT that the column indexes and effective top
			adjustments are the same.
			*/
			bool operator==(const ParcelSpanData& other) const
				{
				//
				// Non conforming bit is NOT part of the comparison.
				//
				if (fSpanType == ICompositionStyle::kSingleColumn)
				{
					return (other.fSpanType == fSpanType);
				}
				else if (fSpanType == ICompositionStyle::kSpanColumn)
				{
					return ((other.fSpanType == fSpanType) &&
							(other.GetDesiredColumnSpan() == GetDesiredColumnSpan()));
				}
				else	// kSplitColumn
				{
					return ((other.fSpanType == fSpanType) &&
							(other.fSplitCount == fSplitCount) &&
							(other.fSplitInsideGutter == fSplitInsideGutter) &&
							(other.fSplitOutsideGutter == fSplitOutsideGutter));
				}
				}

			bool operator!=(const ParcelSpanData& other) const
				{ return !(*this == other); }
	
			ICompositionStyle::SpanColumnsTypeOptions	GetColumnType() const
				{ return fSpanType; }

			/**
			Returns kTrue if the Parcel maps one to one with a column.
			*/
			bool16		GetIsSingleColumn() const
				{ return (fSpanType == ICompositionStyle::kSingleColumn); }

			/**
			Returns kTrue if the Parcel spans two or more columns
			*/
			bool16		GetSpansColumns() const
				{ return (fSpanType == ICompositionStyle::kSpanColumn); }

			/**
			Returns kTrue if the Parcel shares in the split of a column
			*/
			bool16		GetSplitsColumn() const
				{ return (fSpanType == ICompositionStyle::kSplitColumn); }

			/**
			Returns the index (0-n) of the column where the Parcel starts.
			For splits this will be the column which is split.
			*/
			uint32		GetColumnIndexStart() const
				{ return fPColIndexStart; }

			/**
			Returns the index (0-n) of the column where the Parcel ends. This
			will be one past the last column spanned by the Parcel. For example
			a single column and a split would have (start,end) of
			(#index,#index+1), and a full straddle would be (0, #span).
			*/
			uint32		GetColumnIndexEnd() const
				{ return fPColIndexEnd; }

			/**
			This is the actual number of physical columns this Parcel spans.
			*/
			uint32		GetPhysicalColumnSpan() const
				{ return (fPColIndexEnd - fPColIndexStart); }

			/**
			This is the desired column span specified by the controlling
			attributes. Typically this exactly the same as the physical column
			span but in the case of 'all' or the number of desired columns
			exceeds the available physical columns in the container this number
			will be greater.

			This is an important value because it allows us to keep separate 
			Parcels (and their content) which may have the same physical span
			but due to limitations of the container have different desired
			spans and the rule being that all content associated with one span
			must be fully resolved before starting the next span.

			255 == 'all'
			*/
			uint32		GetDesiredColumnSpan() const
				{ return fDesiredSpan; }

			/**
			Returns the index within the split of the Parcel or zero if it is
			not a split.
			*/
			uint32		GetSplitIndex() const
				{
				if (fSpanType == ICompositionStyle::kSplitColumn)
					return fSplitIndex;

				ASSERT_FAIL("Not a split");
				return  0;
				}

			/**
			Returns the split count that the Parcel is associated with or zero
			if it is not a split. All Parcels which are part of the same split
			return the same number.
			*/
			uint32		GetSplitCount() const
				{
				if (fSpanType == ICompositionStyle::kSplitColumn)
					return fSplitCount;

				ASSERT_FAIL("Not a split");
				return  0;
				}

			PMReal		GetSplitInsideGutter() const
				{
				if (fSpanType == ICompositionStyle::kSplitColumn)
					return fSplitInsideGutter;

				ASSERT_FAIL("Not a split");
				return  0.0;
				}

			PMReal		GetSplitOutsideGutter() const
				{
				if (fSpanType == ICompositionStyle::kSplitColumn)
					return fSplitOutsideGutter;

				ASSERT_FAIL("Not a split");
				return  0.0;
				}

			ICompositionStyle::SpanColumnsTypeOptions	fSpanType;
			uint32										fPColIndexStart;
			uint32										fPColIndexEnd;
			uint32										fDesiredSpan;
			uint32										fSplitIndex;
			uint32										fSplitCount;
			PMReal										fSplitInsideGutter;
			PMReal										fSplitOutsideGutter;

		};

		virtual ParcelSpanData	GetNthParcelSpanData(uint32 n) const = 0;

		/**
		Sets an effective ceiling and floor to the Parcel which will
		affect the placement of bottom hung WAEs (such as footnotes).
		Without any changes this is expected to be the Bottom() of
		ContentBounds unless we have manipulated them for hard
		balacing (such as for straddles).
		*/
		virtual PMReal			GetNthParcelEffectiveTopAdj(uint32 containerParcelIndex) const = 0;

		/**
		*/
		virtual void			SetNthParcelEffectiveTopAdj(uint32 containerParcelIndex,
															PMReal effectiveTopAdj) = 0;

		/**
		*/
		virtual PMReal			GetNthParcelEffectiveBottomAdj(uint32 containerParcelIndex,
																PMReal* pBalanceOffset) const = 0;

		/**
		*/
		virtual void			SetNthParcelEffectiveBottomAdj(uint32 containerParcelIndex,
															PMReal effectiveBottomAdj,
															PMReal balanceOffset) = 0;

		/**
		A Parcel is considered non-conforming when as created it does not
		fully match the values specified in its ParcelSpanData.

		For example, a split which has a large gutter in a small column might
		result in a physical Parcel width of impossible size, or an
		implementation such as TextOnPath which does not support more than one
		column or splits so its single Parcel always takes on whatever is asked
		of it even though it is not doing what the user wanted.

		When this occurs the Parcel implementor will typically create a Parcel
		that it CAN support but it will leave it marked here with the desired
		results.

		@return kTrue if nth Parcel is nonconforming, kFalse otherwise
		*/
		virtual bool16 			GetNthParcelIsNonConforming(int32 n) const = 0;

		/**
		*/
		struct PUBLIC_DECL ParcelAllData
		{
			typedef base_type	data_type;

			ParcelAllData(); // does nothing

			ParcelAllData(ParcelKey key,
							const ParcelSpanData& spanData,
							PMReal effectiveTopAdj,
							PMReal effectiveBottomAdj,
							PMReal effectiveBottomAdjBalanceOffset) :
				fKey(key), fSpanData(spanData),
				fEffectiveTopAdj(effectiveTopAdj),
				fEffectiveBottomAdj(effectiveBottomAdj),
				fEffectiveBottomAdjBalanceOffset(effectiveBottomAdjBalanceOffset)
				{ }

			ParcelKey		fKey;
			ParcelSpanData	fSpanData;
			PMReal			fEffectiveTopAdj;
			PMReal			fEffectiveBottomAdj;
			PMReal			fEffectiveBottomAdjBalanceOffset;
			
		};

		virtual void			GetAllParcelData(std::vector<ParcelAllData>& list) const = 0;

		/**
		Caller is responsible for all damage. The ParcelContainer is free to
		reject this request by returning an invalid key (eg TextOnPath).
		*/
		virtual ParcelKey		AppendParcel(const ParcelSpanData& spanData) = 0;

		/**
		Caller is responsible for all damage.
		@return kTrue if the Parcel can accept then change, kFalse otherwise. Currently the only reasons that change will not be accepted if it is a split and the resulting Parcel will be too narrow (~3pt)
		*/
		virtual bool16			ChangeNthParcelTo(uint32 containerParcelIndex,
												const ParcelSpanData& spanData) = 0;

		/**
		Destroys the last Parcel in the Container.
		The callee needs to be responsible for calling the TextParcelList to
		properly damage the content. It is an error to attempt to destroy the
		first Parcel in the Container.
		*/
		virtual void			RemoveLastParcel() = 0;

};

#endif	// __IParcelContainer__

