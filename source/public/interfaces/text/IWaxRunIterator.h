//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxRunIterator.h $
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
#ifndef __IWaxRunIterator__
#define __IWaxRunIterator__

class IWaxRun;
class PMMatrix;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Interface for iterating through waxRuns on a waxLine - returned via IWaxLine -
	this object must be delete'd when finished.

	This is not derived from IPMUnknown. It is allocated on the heap so the caller is responsible for deleting the object
		once it is no longer required.

	An IWaxRunIterator is returned from IWaxLine::QueryWaxRunIterator().
	Typical usage is:
	<pre>
	K2::scoped_ptr&lt;IWaxRunIterator&gt; iter(waxLine->QueryWaxRunIterator());
	</pre>

	@see IWaxRun

	@ingroup text_wax
*/
class PUBLIC_DECL IWaxRunIterator
{

public:
	virtual ~IWaxRunIterator();


	/**
		Reset to the first run and return it, return nil at end of runs.

		@note The IWaxRun interfaces returned by these methods are only
		valid until the next GetxxxRun method call or the destruction
		of the IWaxRunIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.
	 */
	virtual IWaxRun* GetFirstRun() = 0;

	/**
		Advance to the next run, and return it, return nil at end of runs.

		@note that this works on characters, not glyphs.  For characters that result in multiple glyphs, the
				group of glyphs is treated as a single glyph.

		@note The IWaxRun interfaces returned by these methods are only
		valid until the next GetxxxRun method call or the destruction
		of the IWaxRunIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.
	 */
	virtual IWaxRun* GetNextRun() = 0;

	/**
		Backup to the previous run, and return it, returns nil at beginning of runs - expensive method.

		@note The IWaxRun interfaces returned by these methods are only
		valid until the next GetxxxRun method call or the destruction
		of the IWaxRunIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.
	 */
	virtual IWaxRun* GetPrevRun() = 0;

	/**
		Return current run, returns nil at end of runs or if GetFirstRun was never called.

		@note The IWaxRun interfaces returned by these methods are only
		valid until the next GetxxxRun method call or the destruction
		of the IWaxRunIterator, whichever comes first. <br>
		IN OTHER WORDS, the returned interface is not reference counted.
	 */
	virtual IWaxRun* PeekRun() const = 0;

	/**
		Advance to the given run.

		@return kTrue if successful
		@return kFalse probably means waxGlyphs isn't in this waxLine.
	 */
	virtual bool16 AdvanceToRun(const IWaxRun* waxRun) = 0;

	/**
		Return the given matrix to represent the transformation of this run relative to the line.

		For instance, the XPosition value of the matrix represents the x-offset of this run from the start of the line.
	 */
	virtual PMMatrix GetRunMatrix() const = 0;
};

#pragma export off

#endif
