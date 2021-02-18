//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFilesChanging.h $
//  
//  Owner: lance bushore
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IFilesChanging__
#define __IFilesChanging__

#include "LinksUIID.h"

/** IFilesChanging stores a list of data links being edited by Edit Original.
	A IID_IFILESCHANGING interface is off the session.
*/
class IFilesChanging : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IFILESCHANGING };

	/** Add a LinkReference UIDRef to the list maintained by this interface.
		@param UIDRef of a LinkReference (ILinkReference).
	*/ 
	virtual void Append(UIDRef ref) = 0;

	/** Remove a LinkReference from the list maintained by this interface.
		@param index of a LinkReference
	*/ 
	virtual void Remove(int32 index) = 0;

	/** Get a LinkReference from the list.
		@param index of a LinkReference
		@return a UIDRef of a LinkReference.
	*/ 
	virtual UIDRef GetRef(int32 index) = 0;

	/** Get the number of LinkReferences in the list.
		@return number of LinkReferences.
	*/ 
	virtual int32 Length() = 0;

	/** Find a LinkReference in the list.
		@return the index to the LinkReference, or -1 when not found.
	*/ 
	virtual int32 Location(UIDRef ref) = 0;
};

#endif // __IFilesChanging__
