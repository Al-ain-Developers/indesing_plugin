//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxIterator.h $
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
#ifndef __IWaxIterator__
#define __IWaxIterator__

#include "UIDRef.h"

class IWaxLine;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Used to iterate over IWaxLines An IWaxIterator is returned from 
	IWaxStrand::NewWaxIterator(). The returned object must be deleted.
	NOTE:  This is not derived from IPMUnknown.
	@ingroup text_wax
	@see IWaxLines
	@see IWaxStrand::NewWaxIterator
*/
class PUBLIC_DECL IWaxIterator
{
public:
	virtual ~IWaxIterator();
	
	/** Indicates which strand this class is iterating over.
		@return - A UIDRef from which you can get an IWaxStrand
		@see IWaxStrand
	*/
	virtual UIDRef GetStrandIterating() const = 0;
	
	/** Returns the IWaxLine at the given text index. This 
		WaxLine is only valid until the next GetxxxWaxLine method call or 
		the destruction of the IWaxIterator, whichever comes first.
		This method is also used to initialize the iterator.
		@param start - The text index containing the line you want
		@param *pOffset - Filled with the offset from the beginning of the line where start can be found
		@return - The wax line containing "start"
	*/
	virtual IWaxLine *	GetFirstWaxLine(TextIndex start, int32 * pOffset = nil) = 0;

	/** Returns the IWaxLine at the given text index. This 
		WaxLine is only valid until the next GetxxxWaxLine method call or 
		the destruction of the IWaxIterator, whichever comes first.
		This method is also used to initialize the iterator.
		@param start - The text index containing the line you want
		@param *pOffset - Filled with the offset from the beginning of the line where start can be found
		@return - The wax line containing "start"
	*/
	virtual const IWaxLine * GetFirstWaxLine(TextIndex start, int32 * pOffset = nil) const = 0;
		
	/** Returns either the next wax line or nil if the end of story is reached.
		@return - The next wax line or nil.
	*/
	virtual IWaxLine *	GetNextWaxLine() = 0;

	/** Returns either the next wax line or nil if the end of story is reached.
		@return - The next wax line or nil.
	*/
	virtual const IWaxLine * GetNextWaxLine() const = 0;
		
	/** Returns either the previous IWaxLine, or nil if the start of the story is reached.
		@return - The previous wax line or nil.
	*/
	virtual IWaxLine * GetPreviousWaxLine() = 0;

	/** Returns either the previous IWaxLine, or nil if the start of the story is reached.
		@return - The previous wax line or nil.
	*/
	virtual const IWaxLine * GetPreviousWaxLine() const = 0;

	/** Clears the cached current line. The current TextIndex stays the same
	and the next call to GetNextWaxLine(), GetPreviousWaxLine() or
	GetCurrentWaxLine() will restore a cached value.
	*/
	virtual void ClearCurrentLine() const = 0;

	/** Returns the WaxLine at the current iterator position.
		@return - The current wax line or nil.
	*/
	virtual IWaxLine*	GetCurrentWaxLine() = 0;

	/** Returns the WaxLine at the current iterator position.
		@return - The current wax line or nil.
	*/
	virtual const IWaxLine*	GetCurrentWaxLine() const = 0;

	/** Returns the current TextIndex of the the iterator.
		@return - The TextIndex of the iterator.
	*/
	virtual TextIndex	GetCurrentWaxLineOrigin() const = 0;

	/** Returns the span of the current WaxLine.
		@return - The span of the current WaxLine.
	*/
	virtual int32	GetCurrentWaxLineSpan() const = 0;

	/** Returns the end of the current WaxLine.
		@return - The end of the current WaxLine.
	*/
	virtual TextIndex	GetCurrentWaxLineEnd() const = 0;

};
#pragma export off
#endif
