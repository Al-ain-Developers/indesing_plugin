//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxGlyphIterator.h $
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
#ifndef __IWaxGlyphIterator__
#define __IWaxGlyphIterator__

#include "CTextEnum.h"

class PMMatrix;
class IWaxGlyphs;
class IWaxRun;
class PMPoint;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Interface for iterating through glyphs - returned via IWaxLine -
	this object must be delete'd when finished.

	This is not derived from IPMUnknown. It is allocated on the heap so the caller is responsible for deleting the object
		once it is no longer required.

	An IWaxGlyphIterator is returned from IWaxLine::QueryWaxGlyphIterator().
	The returned object must be delete'd.
	Typical usage is:
	<pre>
	K2::scoped_ptr<IWaxGlyphIterator> iter(waxLine->QueryWaxGlyphIterator());
	</pre>

	@note  This iterator cannot be used to navigate the wax, you have no idea where in the wax hierarchy this glyph or
		set of glyphs is. It should only be used to visit each glyph. Note also that there may be no glyphs for a given text index
		(e.g. ILG) or there may be several (e.g. the hypen at end of line).

	@see IWaxRun
	@see IWaxGlyphs

	@ingroup text_wax
*/
class PUBLIC_DECL IWaxGlyphIterator
{
public:
	virtual ~IWaxGlyphIterator();

	/**
		Reset to the first glyph.
	 */
	virtual void Reset() = 0;

	/**
		Advance to the next glyph

		@note The IWaxGlyphs interfaces returned by these methods are only
		valid until the next Advance* method call, Recede* method call or the destruction
		of the IWaxGlyphIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.

		@return the container (IWaxGlyphs object) for this glyph position, nil if at end of glyphs.
	 */
	virtual IWaxGlyphs* Advance() = 0;

	/**
		Recede to the previous glyph

		@note The IWaxGlyphs interfaces returned by these methods are only
		valid until the next Advance* method call, Recede* method call or the destruction
		of the IWaxGlyphIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.

		@return the container (IWaxGlyphs object) for this glyph position, nil if at end of glyphs.
	 */
	virtual IWaxGlyphs* Recede() = 0;

	/**
		Advance to the given container.

		@return kTrue if successful
		@return kFalse probably means waxGlyphs isn't in this waxLine.
	 */
	virtual bool16 AdvanceToContainer(const IWaxGlyphs* waxGlyphs) = 0;

	/**
		Return the (un-reference counted) container for this glyph position.

		@note The IWaxGlyphs interfaces returned by these methods are only
		valid until the next Advance* method call or the destruction
		of the IWaxGlyphIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.

		@return the container, or nil if at end of glyphs.
	 */
	virtual IWaxGlyphs* GetWaxGlyphsContainer() = 0;

	/**
		Return the (un-reference counted) wax run associated with this glyph position.

		@note The IWaxRun interfaces returned by these methods are only
		valid until the next Advance* method call or the destruction
		of the IWaxRunIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.

		@return the object, or nil if at end of glyphs.
	 */
	virtual IWaxRun* GetWaxRun() = 0;

	/**
		Return the given matrix to represent the current glyph in this run relative to the waxLine.
		This matrix incorporates the EachGlyphMatrix and the position of the glyph in the run.

		For instance, the XPosition value of the matrix represents the x-offset of this glyph from the start of the line.
	 */
	virtual void GetGlyphMatrix(PMMatrix * matrix, PMPoint * penCorrection) = 0;

	/**
		Return the given matrix to represent the transformation of this run relative to the line.

		For instance, the XPosition value of the matrix represents the x-offset of this run from the start of the line.
	 */
	virtual void GetRunMatrix(PMMatrix * matrix) = 0;

	/**
	*/
	virtual Text::GlyphID GetGlyphID() const = 0;

	/**
		@return The offset within the WaxGlyphs container of the current position.
	*/
	virtual uint32 GetGlyphOffset() const = 0;

	/**
		@return The TextIndex associated with the current glyph position. Note
				that due to glyph mapping the order of the TextIndexes returned
				may not be the monotonically increasing nor will they
				necessarily change for every call to Advance().
	*/
	virtual TextIndex GetGlyphTextIndex() const = 0;

	/**
		Update the per-glyph's matrix to this - it is an independent modification of the AllGlyphsMatrix.
		Matrix must be line relative (e.g. GetGlyphMatrix's includeLine parameter was kFalse).
	 */
	virtual void SetPerGlyphMatrix(PMMatrix mat, PMPoint penCorrection) = 0;
};

#pragma export off
#endif
