//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxRun.h $
//  
//  Owner: zwilliam
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
#ifndef __IWaxRun__
#define __IWaxRun__

#include "IPMUnknown.h"
#include "ITextAdornment.h"
#include "IWaxCollection.h"
#include "TextID.h"

class PMMatrix;

const double kTextMiterLimit = 4.0;

/** This interface manages the wax that makes up a wax line. The attributes of the run are relative to the position of the parent wax line.

	The waxRun is really a generic wax object. It can either be another collection (the waxLine has a collection, as do some J features) or be
	actual wax.  Most roman text will not have collections of wax, just simple wax runs.

	The run can hold glyphs or not, it can have rendering data or not. It all depends on the type of run and the type of glyphs within the run.
	See the Programming Guide for more information on the wax.

	@note All of the "set" methods are used only by wax-building code (i.e. a composer). Most use is accessing the static data set up by such code.
	It's extremely rare that any "set" methods will be used by external code.

	@ingroup text_wax
*/
class IWaxRun : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXRUN };

	/** The characteristics of a run. These provide easy access to some common attributes of the run. */
	typedef enum {
		kRunKinsoku_PushIn		= 0x01,
		kRunKinsoku_PushOut	= 0x02,
		kRunKinsoku_Any		= 0x03,

		kTOPRun				= 0x20,
		kEndsInHyphen			= 0x40,
		kVerticalWritingMode		= 0x80
	} RunCharacteristics;

	/** Return the number of chars represented by this wax.

		@note this is not necessarily the number of glyphs.
	 */
	virtual int32 GetCharCount() const = 0;

	/** Return either the number of chars or glyph represented by this wax.
		If using World Ready composer the span is number of glyphs. Otherwise
		it is the number of characters.
	 */
	virtual int32 GetWaxSpan() const = 0;

	/** Return the text index of this run.

		@note This is just a convenience method that asks the waxLine itself.
	 */
	virtual TextIndex TextOrigin() const = 0;

	/** Return the width of the entire run.
		The returned width is relative to the waxRun (i.e. GetXPosition() is the origin)

		@note if you have an IWaxGlyphs interface, you can use that too.
	 */
	virtual PMReal GetWidth(bool16 ignoreAllTrailing = kFalse) const = 0;

	/** Return the (EmBox) height of the entire run.
		The returned height is relative to the waxRun (i.e. GetYPosition() is the origin)

		@note if you have an IWaxGlyphs interface, you can use that too.
	 */
	virtual PMReal GetHeight() const = 0;

	/** Return the XPosition of the run. The glyphs will be drawn starting at this position.
		The returned position is relative to the waxLine
	 */
	virtual PMReal GetXPosition() const = 0;
	/** Specify the XPosition of the run.
		It must be relative to the waxLine.
	 */
	virtual void SetXPosition(const PMReal& xPos) = 0;

	/** Return the YPosition of the run. The glyphs will be drawn starting at this position.
		The returned position is relative to the waxLine
	 */
	virtual PMReal GetYPosition() const = 0;
	/** Specify the YPosition of the run.
		It must be relative to the waxLine
	 */
	virtual void SetYPosition(const PMReal& yPos) = 0;

	/** Return the transform matrix for this run.
		Each run in the collection is relative to its owner.
		This matrix can be used to translate the run (contents) out of its owner.

		@note This is just a convenience method for obtaining a matrix from the X and Y positions.
		The wax run does not support anything but x and y translation (no rotation, etc.) Thus, excluding those, the matrix should satisfy IsIdentity().

		@note These work with the [GS]et[XY]Position methods and those can be used instead.
	 */
	virtual PMMatrix GetTransform() const = 0;
	/** Specify the transform matrix for this run.
		It should only contain translations for the overall X and Y run offsets.

		@note This is just a convenience method for using a matrix containing the x and y translations.
		The wax run does not support anything but x and y translation (no rotation, etc.) Thus, excluding those, the matrix should satisfy IsIdentity().

		@note These work with the [GS]et[XY]Position methods and those can be used instead.
	 */
	virtual void	SetTransform(const PMMatrix& xForm) = 0;

	/** Convenience methods for transforming outside the wax. Namely, to the contents-of-the-parcel coordinate space (e.g. where in the parcel (column/cell) it is).
	 */
	virtual PMMatrix GetToParcelContentMatrix() const = 0;
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
	virtual IWaxCollection* GetOwner() const = 0;
	// This should really take const params, and the runs hand out const returns for GetOwner, GetWaxLine..
	/** Specify the owner of this run.
	 */
	virtual void SetOwner(IWaxCollection* owner) = 0;

	/** Returns the containing waxline for this run. */
	virtual const IWaxLine* GetWaxLine() const = 0;

	/** Returns the database containing this wax. */
	virtual IDataBase* GetDataBase() const = 0;

	/** Return whether or not this run will be drawn using vertical writing mode (CJK upright glyphs, vertical rotated Roman)
		@note Roman text drawn in a vertical line is horizontal writing mode
		@note TCY text is horizontal writing mode
	 */
	virtual bool16 IsVerticalWritingMode() const = 0;
	/** Specify vertical writing for this run.
	 */
	virtual void SetVerticalWritingMode(bool16 mode) = 0;

	/** Return whether or not this run is on a path
		@see Text-on-a-Path
	 */
	virtual bool16 IsTOPRun() const = 0;
	/** Specify whether or not this run is on a path.

		@note This should only be used by code that builds up the wax (i.e. a composer).

		@see Text-on-a-Path
	 */
	virtual void SetTOPRun(bool16 is) = 0;

	/** Get the set of characteristics for this run.

		@note Please note that in some cases (i.e. group runs) the above flags could ALL be set and include standard roman text (bits == 0).
		Thus, these only make sense on a leaf waxRun basis (in other words, only use this at draw time when given a run).
	 */
	virtual RunCharacteristics GetRunCharacteristics() const = 0;
	/** Set (overwrite) the characteristics for this run.

		@note Please note that in some cases (i.e. group runs) the above flags could ALL be set and include standard roman text (bits == 0).
		Thus, these only make sense on a leaf waxRun basis (in other words, only use this at draw time when given a run).
	 */
	virtual void SetRunCharacteristics(RunCharacteristics bits) = 0;

	/**
		Split this run at the specified offset.

		@return Whether or not the split was successful
	 */
	virtual bool16 SplitAt( int32 offsetInRun ) = 0 ;

	// ============================================
	// Adornments
	/**
		Get the list of adornments attached to this run.

		@see ITextAdornment, ITextAdornmentData, and, although not wax-related, IGlobalTextAdornment
	 */
	virtual void GetAdornments(int32 *num, const ClassID **iDs,
								const Text::DrawPriority **priority,
								const ITextAdornmentData ***data) const = 0;
	/**
		Set the list of adornments attached to this run.

		@see ITextAdornment, ITextAdornmentData, and, although not wax-related, IGlobalTextAdornment
	 */
	virtual void SetAdornments(int32 num, ClassID *iDs,
								Text::DrawPriority *priority,
								ITextAdornmentData **data) = 0;

	/**
		Find the adornment, if any, matching the given id.

		@param id IN The adorment to look for
		@param priority OUT The priority of the adornment
		@param data OUT The data associated with the adornment.

		@see ITextAdornment, ITextAdornmentData, and, although not wax-related, IGlobalTextAdornment
	 */
	virtual bool16 FindAdornment(ClassID id, Text::DrawPriority *priority, ITextAdornmentData **data) const = 0;
	/**
		Add the given adornment and associated information to this run.

		@param id The classID of the adorment itself.
		@param priority The drawing priority of the adornment (when it will draw).
		@param data The private data associated with the adornment.

		@see ITextAdornment, ITextAdornmentData, and, although not wax-related, IGlobalTextAdornment
	 */
	virtual void AddAdornment(ClassID id, Text::DrawPriority priority, ITextAdornmentData *data) = 0;

	/**
	Remove the adornment, if any, matching the given id.

	@param id IN The adorment to look for
	@see ITextAdornment, ITextAdornmentData, and, although not wax-related, IGlobalTextAdornment
	*/
	virtual void RemoveAdornment(ClassID id) = 0;

	//============================================
	/** Automatically called when the building of this collection is finished.
		This is an internal API for the wax code - DO NOT USE!
	 */
	virtual void ConstructionComplete() = 0;
};

#endif
