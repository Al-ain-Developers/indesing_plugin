//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextTiler.h $
//  
//  Owner: bparadie, ekenning, zwilliam
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
#ifndef __ITextTiler__
#define __ITextTiler__

#include "IPMUnknown.h"

#include "CTextEnum.h"
#include "PMRect.h"
#include "ParcelKey.h"
#include "TextID.h"
#include "TextWrapRef.h"


/**
	@ingroup text_comp
*/
class PUBLIC_DECL ITextTiler : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTTILER };

		/**
		Closed shapes (polygons, circles, etc) are areas, open shapes
		(lines/strokes, i.e. TextOnPath frames) are not areas.
		*/
		virtual bool16		GetIsAnArea() const = 0;

		/**
		Returns true if the parcel may appear more than one place: like
		header/footer rows, master page items
		*/
		virtual bool16		GetAppearsMultiplePlaces() const = 0;

		/**
		*/
		virtual PMMatrix	GetToContentMatrix() const = 0;

		/**
		Content bounds are also known as Wax bounds are simply the bounds of
		the Parcel transformed by the ToContentMatrix. To get the bounds of
		the tileable area call GetNetContentAreaBounds().
		*/
		virtual PMRect		GetContentBounds() const = 0;

		/**
		*/
		class PUBLIC_DECL Tiler
		{
		protected:
			///
			Tiler();

		private:
			///
			Tiler(const Tiler&);
			///
			Tiler& operator=(const Tiler&);

		public:
			virtual	~Tiler();

			/**
			Returns the bounds of the current tileable area as represented by
			the current state of the Tiler. If there are no StandOffs in effect
			the value returned is the same as GetContentBounds().
			@return the bounds of the tileable area
			*/
			virtual PMRect		GetNetContentAreaBounds() const = 0;

			/**
			Returns kTrue if the current tileable area as represented by the
			current state of the Tiler is a single rectangle.
			@return kTrue is tileable area is a single rectangle
			*/
			virtual bool16		GetIsNetContentAreaASingleRectangle() const = 0;

			/**
			Find a tile of the specfied height with the specfied minimum width
			starting at the specfied yPosition.
			@return kTrue if a tile found, kFalse otherwise.
			*/
			virtual bool16		GetTilesAt(PMReal yPosition,
											PMReal minWidth,
											PMReal height,
											Text::GridAlignmentMetric alignmentMetric,
											PMReal alignmentMetricOffset,
											PMReal heightLeadingDiff,
											PMRectCollection& tiles,
											bool16 *pParcelPositionDependent,
											PMReal *pLeftMargin,
											PMReal *pRightMargin) const = 0;

			/**
			@return kTrue if a tile found, kFalse otherwise.
			*/
			virtual bool16		GetMarginsAt(PMReal yPosition,
											PMReal& leftMargin,
											PMReal& rightMargin) const = 0;

#ifdef NOT_YET
			/**
			Return a "slice" across the tileable area of the Parcel at the
			specified yPosition with the specified height.
			@return kTrue if a tile found, kFalse otherwise.
			*/
			virtual bool16		GetSliceAt(PMReal yPosition,
											PMReal height,
											PMRectCollection& tiles,
											PMReal& leftMargin,
											PMReal& rightMargin) const = 0;

#endif

			/**
			Forces the Tiler to forget about all local wraps.
			*/
			virtual void		ClearLocalWraps() = 0;

			/**
			Adds a local Wrap to the Tiler. The caller may call this multiple
			times with new wraps since the last call to ClearLocalWraps().
			@param wrapRef Reference to TextWrapRef.
			*/	
			virtual void		AddLocalWrap(const TextWrapRef& wrapRef) = 0;

		};

		/**
		Instantiates an instance of a Tiler initialized to represent the base
		Parcel content path, text inset path (if any) and all external wraps.

		If includeExternalInlineWraps is kTrue, then inline wraps which can be
		treated as external (anchored in a different Parcel) based on the
		values registered with the controlling ITextParcelListData are added
		as external (base) wraps.

		If includeInternalInlineWraps is kTrue, then inline wraps which can be
		treated as internal (anchored in the Parcel) based on the values
		registered with the controlling ITextParcelListData are added as
		external (base) wraps.

		@param includeExternalInlineWraps
		@param includeInternalInlineWraps
		@return Pointer to new ITiler instance which must be deleted by the caller.
		*/
		virtual Tiler*	NewTiler(bool16 includeExternalInlineWraps = kTrue,
								bool16 includeInternalInlineWrap = kFalse) const = 0;

#ifdef ID_DEPRECATED	// ParagraphComposer, Galley, GalleyInfo
		/**
		Returns the bounds of the tileable area. If there are no non-local
		StandOffs then the value returned is the same as GetContentBounds().
		@return the bounds of the tileable area
		*/
		virtual PMRect	GetNetContentAreaBounds() const;

		/**
		Returns kTrue if the base path of the Tileable area is a single
		rectangle. Not that this does NOT include the effect of any local
		StandOffs.
		@return kTrue is tileable area is a single rectangle
		*/
		virtual bool16	GetIsNetContentAreaASingleRectangle() const;

		/**
		Find a tile of the specfied height with the specfied minimum width
		starting at the specfied yPosition.
		@param nCurrentPosition TextIndex of the tiling context. Must be greater than or equal to the start of the Thread and less than *or equal* to the end of the thread.
		@return kTrue if a tile found, kFalse otherwise.
		*/
		virtual bool16	GetLocalTiles(PMReal yPosition,
										PMReal minWidth,
										PMReal height,
										Text::GridAlignmentMetric alignmentMetric,
										PMReal alignmentMetricOffset,
										PMReal heightLeadingDiff,
										TextIndex nCurrentPosition,
										PMRectCollection& tiles,
										bool16 *pParcelPositionDependent,
										PMReal *pLeftMargin,
										PMReal *pRightMargin) const;
#endif

};

#endif
