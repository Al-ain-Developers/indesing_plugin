//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxCollection.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __IWaxCollection__
#define __IWaxCollection__

#include "IPMUnknown.h"
#include "IWaxLine.h"
#include "TextID.h"

class IWaxRun;
class PMLineSeg;
class IWaxGlyphIterator;
class IWaxRunIterator;

/** Data repository for the various groups of runs (WaxLine, Warichu, TCY).

	A collection is a set of wax objects.<br>
	A wax object is a waxRun or a waxCollection, both of which implement the IWaxRun interface.

	Collections orientate their objects either horizontally (adjacent) or vertically (stacked).<br>
	Stacked objects typically have the same x origin, and adjacent objects typically start
	their x-offset at the end of the previous object.

	@ingroup text_wax
*/
class IWaxCollection : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXCOLLECTION };

	/**
		Return the number of wax objects in this collection.
	*/
	virtual int32		Count() const = 0;

	/**
		Return the (reference-counted) IWaxRun representing the object at the given index (index to object conversion)
	*/
	virtual IWaxRun*	QueryRun(int32 index) const = 0;						// index to WaxRun
	/**
		Return the index for the given object in the collection (object to index conversion)
	*/
	virtual int32		GetRunIndex(const IWaxRun * run) const = 0;				// WaxRun to index

	/**
		Return the TextIndex for the start of this collection.
	*/
	virtual TextIndex TextOrigin() const = 0;

	/**
		Return the overall collection's height. - relative to the baseline
	*/
	virtual void GetHeight(PMLineSeg* pHeight) const = 0;

	/**
		Return the database associated with the objects in the collection.
	*/
	virtual IDataBase* GetDataBase() const = 0;

	/**
		Return the (unreference-counted) IWaxLine in which this collection resides.
	*/
	virtual const IWaxLine* GetWaxLine() const = 0;
	/**
		Set the IWaxLine in which this collection resides.

		The line is NOT reference counted.
	*/
	virtual void SetWaxLine(const IWaxLine * waxLine) = 0;

	/**
		Add the given wax object to the collection.

		@note The run should be fully initialized before adding to the collection.<br>
		These methods also set the owner and waxLine references.  (Thus, SetWaxLine() must already have been called).<br>
		These methods may also query the run or any other interfaces for information (e.g. positioning, xForms, etc.)
	*/
	virtual void		AddRun(IWaxRun* run) = 0;
	/**
		Add the given wax object to the collection at the specified location (this object becomes that index).

		@note The run should be fully initialized before adding to the collection.<br>
		These methods also set the owner and waxLine references.  (Thus, SetWaxLine() must already have been called).<br>
		These methods may also query the run or any other interfaces for information (e.g. positioning, xForms, etc.)
	*/
	virtual void		AddRunAt(IWaxRun* run, int32 at) = 0;

	/**
		Remove all wax objects from this collection.
	*/
	virtual void		RemoveAllRuns() = 0;

	/**
		Return the (reference-counted) neighbor that resides (logically) prior to this object.  Return nil if at beginning of collection.
	*/
	virtual IWaxRun*	QueryPreviousNeighbor(const IWaxRun* waxRun) const = 0;	// Previous in collection or nil
	/**
		Return the (reference-counted) neighbor that resides (logically) after to this object.  Return nil if at end of collection.
	*/
	virtual IWaxRun*	QueryNextNeighbor(const IWaxRun* waxRun) const = 0;		// Next in collection or nil

	/**
		The orientation specifies how neighbors are related. Currently neighbors are stacked on top of each other, or placed next to each other.
	*/
	enum WaxCollectionOrientation {
		kWCOAdjacent,
		kWCOStacked
	} ;

	/**
		Return the orientation of this collection.
	*/
	virtual enum WaxCollectionOrientation GetOrientation() const = 0;
	/**
		Set the orientation of this collection.
	*/
	virtual void SetOrientation(enum IWaxCollection::WaxCollectionOrientation orientation) = 0;

	/** QueryWaxGlyphIterator provides iteration through all the glyphs in this collection.
		It may not visit every run, since not all runs contain glyphs.
		if includeCollection is true, then the Matrix will include the collection's transform (thereby converting to parcel coordinates if this collection was a WaxLine)
	*/
	virtual IWaxGlyphIterator* QueryWaxGlyphIterator(bool16 includeCollection = kFalse) const = 0;

	/** QueryWaxRunIterator only iterates the leaf waxRuns - basically it just hides the wax
		hierarchy, providing access to the glyphs (or other "drawn" data).
		if includeCollection is true, then the Matrix will include the collection's transform (thereby converting to parcel coordinates if this collection was a WaxLine)
	*/
	virtual IWaxRunIterator* QueryWaxRunIterator(bool16 includeCollection = kFalse) const = 0;

	/** Return the transform matrix for this Owner.
		Each run in the collection is relative to its owner.
		This matrix can be used to translate the run (contents) out of its owner.
	 */
	virtual PMMatrix GetTransform() const = 0;

	/** Convenience methods for transforming outside the wax. Namely, to the position-of-the-parcel (column/cell) coordinate space (e.g. where in the table it is).
	 */
	virtual PMMatrix GetToParcelMatrix() const = 0;

	/** Convenience methods for transforming outside the wax. Namely, to the position-of-the-frame coordinate space (e.g. where on the page it is).
	 */
	virtual PMMatrix GetToFrameMatrix() const = 0;

	/** Convenience methods for transforming outside the wax. Namely, to the spread coordinate space.
	 */
	virtual PMMatrix GetToSpreadMatrix() const = 0;

	/** Convenience methods for transforming outside the wax. Namely, to the pasteboard coordinate space (the global namespace).
	 */
	virtual PMMatrix GetToPasteboardMatrix() const = 0;

	/** GetOwner returns an IWaxCollection relating this run to its position in the wax, or nil for such "runs" as
		ruby and kenten, which are not part of the formal hierarchy. (Those "runs" look like wax objects, because they
		are compatible with the drawing code, but they are not within the wax hierarchy - they are adornments).

		@note For roman and most J text, this will return the waxLine's collection. For some J features, it'll return an intermediate collection.
	 */
	//============================================
	/**
		Construction of this object is done. Performs any post processing necessary (including notifying other objects).

		Call when the building of this collection is finished.
		Some collections would like to use a cache for heights and other things. This tells them when they can build it.

		@note this is NOT optional - you must call this after the last object has been added to the collection.
	*/
	virtual void ConstructionComplete() = 0;
};

#endif

