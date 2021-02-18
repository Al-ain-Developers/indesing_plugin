//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellContent.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Provides access to cell content in an opaque wrapper.
//  
//========================================================================================

#pragma once
#ifndef __ICellContent__
#define __ICellContent__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "ParcelKey.h"
#include "OwnedItemDataList.h"


//-----------------------------------
//	Forward References
//
class TableMementoPiece;
class PMMatrix;
class TableLayout;


// ===================================================================================
//	class ICellContent		
// ===================================================================================
class ICellContent : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ICELLCONTENT};
	enum GrowableDirection { kNone = 0, kLeft = 0x01, kTop = 0x02,
									kRight = 0x04, kBottom = 0x08 };

	// ----- API -----
	virtual void		SetTableModel(const UIDRef& tableModelRef) = 0;
	virtual UIDRef		GetTableModel() const = 0;
	virtual void		SetGridID(const GridID& gridID) = 0;
	virtual GridID		GetGridID() const = 0;
	virtual void		SetGridAddress(const GridAddress& gridAddress) = 0;
	virtual GridAddress	GetGridAddress() const = 0;

	/**
	Convenience methods. See ITableLayout for more information.
	*/
	virtual PMRect		GetCellPathBounds(ParcelKey key) const = 0;
	virtual UID			GetParcelFrameUID(ParcelKey key) const = 0;
	virtual PMMatrix	GetParcelToFrameMatrix(ParcelKey key) const = 0;
	virtual bool16		GetParcelAcceptingInvals(ParcelKey key) const = 0;
	virtual void		AddParcelPendingInval(ParcelKey key,
												const PMRect& invalRect) = 0;
	/**
	Notifies the Table Layout that the Parcel content damage state has changed.
	*/
	virtual void		NotifyLayoutParcelDamageChanged(ParcelKey key,
														bool16 isDamaged) = 0;

	/**
	This method should be calleed when a Parcel which has content which was
	not previously position dependent is now position dependent.
	*/
	virtual void		NotifyLayoutParcelPosDependentContentSet(ParcelKey key) = 0;

	/**
	If the inkBounds of the Parcel changes outside of composition this method
	should be called.
	*/
	virtual void		NotifyLayoutParcelInkBoundsChanged(ParcelKey key) = 0;

	/**
	Cell Content Type (eg kTextContentType)

	This method is used by Table Model to determine which Content Manager
	should handle the content of the cell during certain model operations.
	*/
	virtual CellType	GetCellType() const = 0;

	/**
	Cells support two "types": 1) 'regular', that is for each Layout Row a
	Parcel is created and the text flows into it as if it was linked, and
	2) 'repeat' in which the text composes only in the first Parcel and all
	the other Parcels simply draw the contents of the first Parcel.

	The latter is used to support Header/Footer and SubHeader. The language here
	is not that a cell "is a header or footer" but rather what its type is.

	This method will be called when: 1)  a new Header or Footer Row containing
	the Cell is created, 2) an existing Body Row is about to change type to
	Header or Footer, and 3) a Body row is set to be a sub-head.

	No call will be made when a Body Row is created as the default is 'regular'.

	The callee must be careful to not ask the Model what the current type is
	since this method is sometimes called during pre-notification.

	lRowCount indicates how many LayoutRows exist for the ModelRow. The cell
	needs to ensure that it does not have more Parcels than this number.
	*/
	virtual void		NotifyRowTypeChanging(bool16 repeat,
												int32 lRowCount) = 0;

	virtual void		InvalCellContent(ParcelKey key) = 0;

	/**
	This method will be called when the Cell has been duplicated or otherwise
	moved between (or even within the same) story. The callee should simply
	remove all the Parcels and reset all other state as if the cell had never
	been composed. The ContentManager for the particular cell is responsible
	for damaging
	*/
	virtual void		ResetCompositionState() = 0;

	/**
	*/
	virtual int32		GetParcelCount() const = 0;

	/**
	*/
	virtual int32		GetParcelIndex(ParcelKey key) const = 0;

	/**
	*/
	virtual ParcelKey	GetNthParcelKey(int32 n) const = 0;

	/**
	Creates a new Parcel at the specified index within the ParcelList.
	*/
	virtual ParcelKey	CreateParcelAt(int32 index) = 0;

	/**
	The specified Parcel is removed from the ParcelList.
	*/
	virtual void		RemoveParcel(int32 index) = 0;

	/**
	This method is called by the TableComposer to define the size and
	position of the Parcel. Typically this is only called when the size
	of the Parcel changes.
	
	cellPathBounds		This area is the path bounding box of the cell "piece" containing the Parcel and is provided to allow the Parcel to draw indicators (such as overset text) within the boundry of the cell piece but not necessarily within the Parcel itself.
	
	bounds				The bounds of the Parcel. These bounds differ from the cellPathBounds because of insets and strokes on the cell. The top left corner of will be (0.0, 0.0).
	
	maxGrowBounds		Specifies the maximum amount that a Parcel's bounds may grow. This value works in concert with growDir. The cell is allowed to ignore this value AND retain the previous value if growDir is set to kNone.

	growDir				Tells the cell that the Parcel is allowed to grow in the specified direction upto the maximum specified as maxGrowBounds.
	
	contentAttributeChanged	Setting this value to kTrue is the same as calling NotifyContentAttributeChanged(). Combining actions in this way improves performace.
	*/
	virtual void		SetParcelGeometry(ParcelKey key,
											const PMRect& cellPathBounds,
											const PMRect& parcelBounds,
											const PMRect& maxGrowBounds,
											GrowableDirection growDir,
											bool16 contentAttributeChanged) = 0;

	///
	virtual void		SetParcelGrowDir(ParcelKey key, 
											GrowableDirection growDir) = 0;

	/**
	*/
	virtual void		SetParcelHeight(ParcelKey key, PMReal height) = 0;

	/**
	This method is called by the TableComposer when a Cell attribute which is
	marked as being a content attribute has been changed. The callee should
	examine all the content attributes that affect the cell and damage the
	content appropriately in the normal way. Note that for performance reasons
	this method should only be called when the composer knows that it does
	not need to call SetParcelGeometry().
	*/
	virtual void		NotifyContentAttributeChanged(ParcelKey key) = 0;

	/**
	Called by the TableComposer when the specified Parcel has position
	dependent content (see IParcelList) and the Layout Row containing the
	Parcel is moved without the Parcel being resized.
	*/
	virtual void		NotifyParcelMoved(ParcelKey key) = 0;

	/**
	Retrurns kTrue if the specified Parcel OR any Parcel at a lower index
	needs to be composed.
	*/
	virtual bool16		GetParcelNeedsComposition(ParcelKey key) const = 0;

	/**
	*/
	virtual void		RecomposeThruParcel(ParcelKey key) = 0;

	/**
	*/
	virtual PMRect		GetParcelContentInkBounds(ParcelKey key) const = 0;

	/**
	Some types of content may be positioned within the Parcel relative
	to some thing outside the Parcel, say the TextFrame or the
	Pasteboard. When the Parcel is moved it will require recomposition.
	
	Only meaningful if the Parcel is fully composed, if called when
	it is not composed it will likely return kTrue.
	*/
	virtual bool16		GetParcelHasPositionDependentContent(ParcelKey key) const = 0;

	/**
	These bounds are NOT necessarily the bounds of the ink, they reflect
	the "squishable" size of the content or, in other words, the minimum
	size of the composed content.
	
	For example, consider a TextCell which contains text that has 
	Vertical Justification set to Fully Justified. The ink for this
	content fills the entire Parcel but the GrowableHeight is far less.
	As the Parcel is made shorter the spacing between the lines added
	by the Vertical Justification also shortens until there is no longer
	any added space. This final height is the GrowableHeight.
	
	Growable Height/Width is only valid if the growable direction of the
	Parcel is compatible with the growable direction of the content.
	Consider a TextCell which has 90 degree content rotation. If the
	GrowableDirection of the Parcel is vertical then the value returned
	for GrowableHeight() will be zero. This prevents Parcels with this type
	of orientation from "ratcheting" up the height of the row and never
	allowing it to shrink.
	
	TopHungComposedBottom()	Returns the Parcel Bottom required to fit the bottom ofthe content without causing the top of the Parcel to change.
	
	BottomHungComposedTop()	Returns the Parcel Top required to fit the top of the content without causing the bottom of the Parcel to change.
	*/
	virtual PMReal		GetParcelTopHungComposedBottom(ParcelKey key) const = 0;
	virtual PMReal		GetParcelBottomHungComposedTop(ParcelKey key) const = 0;
	virtual PMReal		GetParcelComposedGrowableHeight(ParcelKey parcelKey) const = 0;

	/**	
	Appends the list of OwnedItems that are associated with the specified
	Parcel. Only those OwnedItems that are actually composed within the
	Parcel are added. Note that because of the presence of WaxAnchorPts and
	WaxAnchoredElements it is not sufficient to use the span of the
	Parcel to compute this.
	@param key
	@param rList The results are appended to the list.
	*/
	virtual void		CollectParcelOwnedItems(ParcelKey key,
											OwnedItemDataList* rList) const = 0;

	/**
	Internal method. Do not call.
	*/
	virtual void		ConvertFromAnna(TableLayout* layout) = 0;

	/**
	@return bool16	kTure if the cell is empty. No text in case of text cell and empty graphic frame in case of graphic cell
	 */
	virtual bool16		IsEmpty() const = 0;

	/**
	@param	key	parcel key to be queried for
	@return	PMRect	painted bounding box of the parcel. Refer to IShape for more details on paintedBBox
	*/
	virtual PMRect		GetParcelPaintedBBox(ParcelKey key) const = 0;

};

#endif // __ICellContent__

