//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableLayout.h $
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
#ifndef __ITableLayout__
#define __ITableLayout__

#include "TableTypes.h"
#include "TablesID.h"
#include "PMReal.h"
#include "ParcelKey.h"
#include "K2SmartPtr.h"

class IParcelList;
class ITableFrame;


class ITableLayout : public IPMUnknown
{
	public:
		enum  { kDefaultIID = IID_ITABLELAYOUT };

		/**
		Layout Parcels hold information about the IParcel objects owned by the
		Cells which are what the TableComposer manipulates during composition.
		*/
		class Parcel
		{
		protected:
			PUBLIC_DECL Parcel();

		private:
			PUBLIC_DECL Parcel(const Parcel& copy);
			PUBLIC_DECL Parcel& operator=(const Parcel& copy);

		public:
			virtual ~Parcel() { }

			/// @doc comparison operators
			///
			virtual bool16 operator ==(const Parcel& other) const = 0;
			///
			virtual bool16 operator !=(const Parcel& other) const = 0;

			/**
			Returns the GridAddress of the Cell that owns this Parcel. Note
			that because of vertically merged Cells, this may NOT be the same
			as the ModelRow of the Layout Row this Parcel is part of.
			*/
			virtual GridAddress		GetGridAddress() const = 0;

			/**
			Parcel keys are only unique for a given Cell. Keys may not be asked
			for if the containing Row is damaged.
			*/
			virtual ParcelKey		GetParcelKey() const = 0;

			///
			enum Damage {
				///
				pdt_none			= 0x00,
				/// The content has become damaged and requires that the Parcel needs to be re-composed.  The Parcel as a whole has NOT been Inval()ed although parts of it may have been.
				pdt_content			= 0x01,
				/// A Cell attribute which pertains to content has been changed. The Parcel has NOT been Inval()ed.
				pdt_content_attr	= 0x02,
				/// The XPosition of the Parcel is in doubt because the width of a column to the left of the Parcel has been changed. The Parcel HAS been Inval()ed.
				pdt_x_offset		= 0x08,
				/// Requires that the size and XYOffset be recomputed. The Parcel HAS been Inval()ed.
				pdt_structure		= 0x10,
				///

				pdt_all				= 0x1b
			};
			
			/**
			Parcel damage is NOT hierarchical, unlike Frame and Row damage.
			In addition, unlike Rows, the information available here is
			still valid for damaged Parcels.
			*/
			virtual Damage			GetDamage() const = 0;

			/**
			The XYOffset of the Parcel is measured from the Top Left of
			of the Path bounds of the containing Row.
			*/
			virtual PMPoint			GetXYOffset() const = 0;

		};


		/**
		Layout Rows represent the composed state of Model rows. There is
		one or more for each Model row. Each Row is mapped to one and only
		one Frame regardless of the damage state. However, when damaged the
		the location of the Row relative to the containing Frame becomes
		unknown.

		Each Row contains information for each Parcels that is owned by a
		TableCell which is anchored (or vertically merged through) the
		ModelRow. The implementation will take responsibility for ensuring
		that only those Parcels that map to column containing anchored Cells
		appear in the Row.
		*/
		class Row
		{
		protected:
			PUBLIC_DECL Row();

		private:
			PUBLIC_DECL Row(const Row& copy);
			PUBLIC_DECL Row& operator=(const Row& copy);

		public:
			virtual ~Row() { }

			/// @doc comparison operators
			///
			virtual bool16 operator ==(const Row& other) const = 0;
			///
			virtual bool16 operator !=(const Row& other) const = 0;

			/// @doc Returns the underlying Model Row this Layout Row maps to and an indication in regards to whether it is the first and/or last Layout Row for the Model Row. Do not assume that all Parcels on this Row are also part of this Model Row.

			///
			virtual GridCoord		GetModelRowNum() const = 0;

			/**
			Return kTrue if the Row is not a Header, Footer, or SubHeader. Note that SubHeaders are really Body Rows as the Table Model sees them, but we describe the Row in terms with how the Frame sees it.
			*/
			virtual bool16			GetIsBodyRow() const = 0;

			///
			virtual bool16			GetIsFirstForRow() const = 0;

			///
			virtual bool16			GetIsLastForRow() const = 0;
			
			/**
			Rows are mapped to a single Frame.
			@returns UID of the TableFrame
			*/
			virtual UID				GetTableFrameUID() const = 0;

			///
			enum Damage {
				/// no damage
				rdt_none				= 0,
				/// the row needs to compute new ink bounds.
				rdt_inval				= 1,
				/// The YPosition of the Row is in doubt. The not Row has NOT been inval()ed.
				rdt_geometry_noinval	= 2,
				/// The YPosition of the Row is in doubt. The row *was* inval()ed.
				rdt_geometry			= 3
			};

			/**
			Rows are damaged when the location specified by the
			TableFrameUID or PathXYOffset is no longer valid. This might occur
			when a Row above has been moved down which requires that the
			Row below it must be reposition. In this regard this behavior
			is analogous to the geometry damage of a WaxLine.
			Note that this damage state is independent of the damage state
			of the Parcels on the Row.
			@returns Damage
			*/
			virtual Damage			GetDamage() const = 0;

			/**
			If this Row is a Body Row, and GetDamage() returns
			rdt_geometry_noinval or rdt_geometry and GetIsFirstForRow() returns
			kTrue then this method will return kTrue if the Row is Keeps
			damaged, kFalse otherwise.
			*/
			virtual bool16			GetIsKeepsDamaged() const = 0;

			/**
			The PathXYOffset places the Top Left Path corner of the Row
			relative to the Top Left Stroke corner of the containing Frame.
			*/
			virtual PMPoint			GetPathXYOffset() const = 0;

			/**
			*/
			virtual PMReal			GetPathHeight() const = 0;

			/**
			Ink Bounds are relative to the Row Path bounds.
			*/
			virtual PMRect			GetInkBounds() const = 0;

			/**
			At a minimum the Row contains one Parcel for each Cell which is
			anchored on the ModelRow that this Row is associated with. In
			addition, it may optionally contain Parcels for vertically merged
			Cells that are anchored on previous ModelRows.
			*/
			virtual int32			GetParcelCount() const = 0;
			virtual Parcel*			GetNthParcel(int32 n) const = 0;
			virtual int32 			GetParcelColIndex(GridCoord col) const = 0;

			/**
			Returns kTrue if any Parcels on this Row are damaged in any way.
			*/
			virtual bool16			GetAreAnyParcelsDamaged() const = 0;

			/**
			Returns the Effective SubHeadLevel (0-3) for the ModelRow, 0 equals
			none (which will be the value also returned for header and footer
			Rows).
			*/
			virtual uint32			GetEffectiveSubHeaderLevel() const = 0;

		};

		///
		class row_iterator;

		/// @doc These iterators iterate over Rows in Model Row order.

		/**
		Returns an iterator of Rows which will increment in model order.
		@param row grid coordinate of Model Row to start the iteration at. Must e within the range defined by ITableModel::GetTotalRows().
		@param skipSubHeaders If kTrue, only the first Row will be returned for those which have an non-zero effective subheader level.
		*/
		virtual row_iterator	begin_row_iterator(GridCoord row, bool16 skipSubHeaders = kTrue) const = 0;
		/**
		Returns an copy of the specified iterator.
		*/
		virtual row_iterator	begin_row_iterator(const row_iterator& iter) const = 0;
		/**
		Returns an iterator of Rows which will increment in model order.
		@param row grid coordinate of Model Row to start the iteration at. Must e within the range defined by ITableModel::GetTotalRows().
		@param skipSubHeaders If kTrue, only the first Row will be returned for those which have an non-zero effective subheader level.
		*/
		virtual row_iterator	end_row_iterator(GridCoord row, bool16 skipSubHeaders = kTrue) const = 0;

		/// @doc These iterators iterate over Rows mapped to the specified Frame.
		///
		virtual row_iterator	begin_row_iterator(UID tableFrameUID) const = 0;
		///
		virtual row_iterator	begin_row_iterator(UID tableFrameUID, GridCoord row) const = 0;
		///
		virtual row_iterator	end_row_iterator(UID tableFrameUID) const = 0;
		///
		virtual row_iterator	end_row_iterator(UID tableFrameUID, GridCoord row) const = 0;

		///
		class row_iterator_helper;
		class row_iterator
		{
		public:
			typedef Row								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const Row*						pointer;
			typedef const Row&						reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			explicit row_iterator(row_iterator_helper* helper) :
				fHelper(helper)
				{ }
		
			row_iterator(const row_iterator& copy) :
				fHelper(copy.fHelper->copy())
				{ }

			row_iterator& operator=(const row_iterator& copy)
				{
				fHelper.reset(copy.fHelper->copy());
				return *this;
				}

			Row&					operator*() const
				{ return *(fHelper->dereference()); }
	
			Row*					operator->() const
				{ return fHelper->dereference(); }
	
			row_iterator&			operator++()
				{
				fHelper->increment();
				return *this;
				}

			row_iterator			operator++(int)
				{
				row_iterator tmp = *this;
				fHelper->increment();
				return tmp;
				}

			row_iterator&			operator--()
				{
				fHelper->decrement();
				return *this;
				}

			row_iterator			operator--(int)
				{
				row_iterator tmp = *this;
				fHelper->decrement();
				return tmp;
				}

			bool16					operator==(const row_iterator& rhs) const
				{ return fHelper->equal(rhs.fHelper.get()); }
	
			bool16					operator!=(const row_iterator& rhs) const
				{ return !(*this == rhs); }

		protected:
			K2::scoped_ptr<row_iterator_helper>	fHelper;

		};

		typedef row_iterator	const_row_iterator;

		/// @doc Implementation must supply a helper to assist the common iterator code above. Note that this method returns a class from the heap that must be deleted by the caller.

		///
		class row_iterator_helper
		{
		protected:
			PUBLIC_DECL		row_iterator_helper();
		public:
			virtual			~row_iterator_helper() { }
			virtual Row*	dereference() const = 0;
			virtual bool16	equal(const row_iterator_helper* rhs) const = 0;
			virtual void	increment() = 0;
			virtual void	decrement() = 0;
			virtual row_iterator_helper* copy() const = 0;

		};

		/**
		Layout Frames contain one more Body Rows and zero or more Header and/or Footer Rows. Each Frame is mapped to a single persistent kTableFrameBoss object.
		*/
		class Frame
		{
		protected:
			PUBLIC_DECL Frame();

		private:
			PUBLIC_DECL Frame(const Frame& copy);
			PUBLIC_DECL Frame& operator=(const Frame& copy);

		public:
			virtual ~Frame() { }

			/// @doc comparison operators

			///
			virtual bool16 operator ==(const Frame& other) const = 0;
			///
			virtual bool16 operator !=(const Frame& other) const = 0;

			/// @doc The kTableFrameBoss.

			///
			virtual UIDRef		GetFrameRef() const = 0;
			///
			virtual ITableFrame* QueryFrame() const = 0;

			/// @doc Indicates if the Frame is the first and/or last Layout Frame.

			//
			virtual bool16		GetIsFirst() const = 0;
			///
			virtual bool16		GetIsLast() const = 0;

			///
			enum Damage {
				/// None of the Rows or Parcels are Damaged.
				fdt_none		= 0,
				/// One or more Rows or Parcels were invalidated due to an attribute change which does not require composition but due to Text system limitations we need to trigger composition of the underlying Story so invalidation will occur.
				fdt_inval    = 1,
				/// The same as fdt_content except that the WaxLine containing the Frame has NOT been damaged. This state only occurs when the Frame is in overset.
				fdt_content_notnotified = 2,
				/// One or more Rows or Parcels have some type of damage (rdt_geometry, pdt_content, etc). Frames with this damage state have a trustworthy ParcelKey and the WaxLine containing the Frame has been damaged.
				fdt_content	= 3,
				/// The location of Frame anchor has been changed and the ParcelKey is no longer trusted.
			   fdt_geometry	= 4
			};

			/**
			Frames which are damaged require recomposition.
			*/
			virtual Damage		GetDamage() const = 0;

			/**
			Row spans are ordered and in terms of Model Rows. Since a Model
			Row can only appear once in any Layout Row this is sufficient to
			uniquely identify the Layout Row.
			*/
			virtual RowRange	GetHeaderRows() const = 0;
			///
			virtual bool16		GetHasAnySubHeaderRows() const = 0;
			///
			virtual bool16		GetIsASubHeaderRow(GridCoord mR) const = 0;
			///
			virtual RowRange	GetBodyRows() const = 0;
			///
			virtual RowRange	GetFooterRows() const = 0;
			///
			virtual bool16		GetAreRowsInSameRange(GridCoord mR1,
													GridCoord mR2) const = 0;

			/**
			The ParcelKey is for the containing ParcelList.
			*/
			virtual ParcelKey	GetParcelKey() const = 0;

			/**
			Returns the XYOffset from the Parcel Content Bounds, which are
			the same as returned by ITextTiler, to the Left Top corner of the
			Frame.
			*/
			virtual PMPoint		GetStrokeXYOffset() const = 0;

			/**
			*/
			virtual PMMatrix	GetToParcelMatrix() const = 0;

			/**
			*/
			virtual PMMatrix	GetToTextFrameMatrix() const = 0;

			/**
			*/
			virtual PMMatrix	GetToPasteboardMatrix() const = 0;

			/**
			The Frame coordinate system has (0,0) as the value at
			the top left corner of the Stroke Bounds.
			*/
			virtual PMRect		GetStrokeBounds() const = 0;

			/**
			In Frame coordinates.
			*/
			virtual PMRect		GetPathBounds() const = 0;

			/**
			In Frame coordinates.
			*/
			virtual PMRect		GetInkBounds() const = 0;

		};

		/**
		Frame iterators.
		*/
		class frame_iterator;
		///
		virtual frame_iterator	begin_frame_iterator() const = 0;
		///
		virtual frame_iterator	begin_frame_iterator(UID tableFrameUID) const = 0;
		///
		virtual frame_iterator	end_frame_iterator() const = 0;
		///
		virtual frame_iterator	end_frame_iterator(UID tableFrameUID) const = 0;

		///
		class frame_iterator_helper;
		class frame_iterator
		{
		public:
			typedef Frame								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const Frame*						pointer;
			typedef const Frame&						reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			frame_iterator(frame_iterator_helper* helper) :
				fHelper(helper)
				{ }
		
			frame_iterator(const frame_iterator& copy) :
				fHelper(copy.fHelper->copy())
				{ }	

			frame_iterator& operator=(const frame_iterator& copy)
				{
				fHelper.reset(copy.fHelper->copy());
				return *this;
				}

			Frame&					operator*() const
				{ return *(fHelper->dereference()); }
	
			Frame*					operator->() const
				{ return fHelper->dereference(); }
	
			frame_iterator&			operator++()
				{
				fHelper->increment();
				return *this;
				}

			frame_iterator			operator++(int)
				{
				frame_iterator tmp = *this;
				fHelper->increment();
				return tmp;
				}

			frame_iterator&			operator--()
				{
				fHelper->decrement();
				return *this;
				}

			frame_iterator			operator--(int)
				{
				frame_iterator tmp = *this;
				fHelper->decrement();
				return tmp;
				}

			bool16					operator==(const frame_iterator& rhs) const
				{ return fHelper->equal(rhs.fHelper.get()); }
	
			bool16					operator!=(const frame_iterator& rhs) const
				{ return !(*this == rhs); }

		protected:
			K2::scoped_ptr<frame_iterator_helper>	fHelper;

		};

		typedef frame_iterator	const_frame_iterator;

		/// @doc Implementation must supply a helper to assist the common iterator code above. Note that this method returns a class from the heap that must be deleted by the caller.

		///
		class frame_iterator_helper
		{
		protected:
			PUBLIC_DECL		frame_iterator_helper();
		public:
			virtual			~frame_iterator_helper() { }
			virtual Frame*	dereference() const = 0;
			virtual bool16	equal(const frame_iterator_helper* rhs) const = 0;
			virtual void	increment() = 0;
			virtual void	decrement() = 0;
			virtual frame_iterator_helper* copy() const = 0;

		};

		/// Recompose all Rows upto and including all the layout rows for the the specified mode row. If the row specified is a Header or Footer row then all Frames will be composed.
		virtual void		RecomposeThruModelRow(const GridCoord modelRow) = 0;

		/**
		Returns the height of the model row. If this is a Body Row then it is
		the sum of all the Rows mapped to the Model Row. Otherwise it is the
		greatest of all of the Row heights for this Model Row.
		*/
		virtual PMReal		GetRowHeight(GridCoord modelRow) const = 0;

		/// @doc These methods provide efficient ways to determine the starting or last Row of a vertically merged "group". Due to merging in this way, these Rows must be composed in one Frame.
		///
		virtual GridCoord	GetRowVMergeStart(GridCoord modelRow) const = 0;
		///
		virtual GridCoord	GetRowVMergeLast(GridCoord modelRow) const = 0;
		///
		virtual GridCoord	GetRowKeepsStart(GridCoord modelRow) const = 0;
		///
		virtual GridCoord	GetRowKeepsLast(GridCoord modelRow) const = 0;

		///
		virtual ParcelKey	GetCellParcelKey(const GridAddress& ga,
												UID tableFrameUID) const = 0;

		/// @doc Returns geometry in Parcel coordinates which has the left top corner of the Parcel Bounds set at (0,0). The Frame, Row and Parcel must not be damaged. To convert from Parcel coordinates to Frame coordinates use the GetParcelToFrameMatrix() method below.
		///
		virtual PMRect		GetCellParcelOuterStrokeBounds(const GridAddress& ga,
												ParcelKey key) const = 0;
		///
		virtual PMRect		GetCellParcelPathBounds(const GridAddress& ga,
												ParcelKey key) const = 0;
		///
		virtual PMRect		GetCellParcelInnerStrokeBounds(const GridAddress& ga,
												ParcelKey key) const = 0;

		/**
		Returns the UID of the ITableLayout::Frame that the Parcel is mapped to.
		@param ga
		@param key
		*/
		virtual UID			GetParcelFrameUID(GridAddress ga,
													ParcelKey key) const = 0;

		/**
		Returns the PMMatrix required to map coordinates relative to the Parcel to coordinates relative to the ITableLayout::Frame the Parcel is mapped to.  If the Row is damaged, returns the identity matrix.
		@param ga
		@param key
		*/
		virtual PMMatrix	GetParcelToFrameMatrix(GridAddress ga,
													ParcelKey key) const = 0;

		/// @doc These methods are provided as hooks for the Cells to get the information they need to place themselves relative to the containing TextFrame and to notify the implementation that their content has become damaged.

		/// Returns the UID of the TextFrame the Parcel is mapped to. If the Row is damaged, returns kInvalidUID.
		virtual UID			GetParcelTextFrameUID(GridAddress ga,
													ParcelKey key) const = 0;

		/**
		Returns the PMMatrix required to map coordinates relative to the Parcel to coordinates relative to the TextFrame the Parcel is mapped to.  If the Row is damaged, returns the identity matrix.
		@param ga
		@param key
		*/
		virtual PMMatrix	GetParcelToTextFrameMatrix(GridAddress ga,
													ParcelKey key) const = 0;

		/**
		Returns kTrue if the content of the may generate view invalidations for
		the TextFrame.
		*/
		virtual bool16		GetParcelAcceptingInvals(GridAddress ga,
													ParcelKey key) const = 0;

		/**
		The Parcel-relative inval rect is forwarded to the containing Parcel
		and will eventually end up at the IPendingInvals interface of the
		TextFrame the Parcel is mapped to.
		*/
		virtual void		AddParcelPendingInval(GridAddress ga, ParcelKey key,
												const PMRect& invalRect) = 0;

		/**
		Hook for ICellContent implementations to notify the TableLayout
		implementation that their content damage state has changed.
		*/
		virtual void		NotifyParcelContentDamageChanged(GridAddress ga,
													ParcelKey key,
													bool16 isDamaged) = 0;

		/**
		Hook for ICellContent implementations to notify the TableLayout
		implementation that their Parcel now contains position dependent
	 	content.
		*/
		virtual void		NotifyParcelPositionDependentContentSet(GridAddress ga, ParcelKey key) = 0;

		/**
		Hook for ICellContent implementation to notify the TableLayout
		implementation that the inkBounds of the Parcel have been changed
		outside of composition.
		*/
		virtual void		NotifyParcelInkBoundsChanged(GridAddress ga,
														ParcelKey key) = 0;
		/**	Called before the type of cell is going to be modify
		@param: cells	The cells whose type is going to be modified
		*/
		virtual void		PreNotifyCellTypeChanged(const GridArea& cells) = 0;

		/**	Called after the type of cells have changed
		@param: cells	The cells whose type have changed
		*/
		virtual void		NotifyCellTypeChanged(const GridArea& cells) = 0;
};

#endif	//__ITableLayout__

