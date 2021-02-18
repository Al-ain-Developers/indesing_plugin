//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDocumentSetupUtils.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __IDocumentSetupUtils__
#define __IDocumentSetupUtils__

#include "InCopyCoreID.h"
#include "Utils.h"
#include "IStoryPropertiesSuite.h"
#include "IGridAttributesPrefs.h"

class IDocument ;

/** Utilities related to document setup for InCopy.
*/
class IDocumentSetupUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCUMENTSETUPUTILS } ;

	/**		Resize all the stories' text frame to reflect the document setup changes
			@param doc The active document
	*/
	virtual ErrorCode ResizeAllStoryTextFrames( IDocument* doc ) = 0 ;
	
	/**		Get the text area width based on the preference's setting. 
			In InCopy J, the text area width is calculated based on the number of grid character in a line for frame grid text frame.
			@param doc The preference on the document is used to determin the width, if nil, the session's preference is used
			@return the text area width
	*/
	virtual PMReal GetDocumentSetupTextAreaLength ( IDocument * doc) = 0;

} ;

#endif	// __IDocumentSetupUtils__
