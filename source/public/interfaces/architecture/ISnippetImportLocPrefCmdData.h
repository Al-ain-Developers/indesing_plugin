//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISnippetImportLocPrefCmdData.h $
//  
//  Owner: Rich Gartland
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
#ifndef __ISNIPPETIMPORTLOCATIONPREFCMDDATA__
#define __ISNIPPETIMPORTLOCATIONPREFCMDDATA__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"
#include "UIDRef.h" 

/** A class to tell whether batch-place (or snippet) import/place operations should use the original (stored)
	location of the item('s) in the file for placement, or load the placegun to allow the user to place
*/
class ISnippetImportLocationPrefCmdData : public IPMUnknown
{
public:
	/** Set the values
		@param doc IN the document
		@param in bUseOriginalLocation IN kTrue = use original; kFalse = allow placegun
	*/
	virtual void Set(const	UIDRef&	doc, const	bool16	bUseOriginalLocation) = 0;

	/** Get the document
		@return the document UIDRef
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/** Get the original/placegun preference value
		@return kTrue = use the original spread location(s) for placed item(s); kFalse = enable placegun
	*/
	virtual const bool16 GetSnippetImportUsesOriginalLocation() const = 0;
};


#endif
