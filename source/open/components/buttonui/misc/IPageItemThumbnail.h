//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/misc/IPageItemThumbnail.h $
//  
//  Owner: Tim Wright
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
//  Base type for FormField.
//  
//  A form page item is identified as a form using this interface.
//  A form page item supports form-specific graphic attributes,
//  and is exported as an annotation in a PDF file.
//  
//========================================================================================

#pragma once
#ifndef __IPageItemThumbnail_h__
#define __IPageItemThumbnail_h__

#include "FormFieldUIID.h"
#include "IPMUnknown.h"
#include "BravoForwardDecl.h"

class UIDList;

//=============================================================================

class IPageItemThumbnail : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMTHUMBNAIL };

	// inPageItems should be in drawing order
	virtual ErrorCode Build(const UIDList &inPageItems, int32 inMaxWidth, int32 inMaxHeight) = 0;
	virtual void Get(AGMImageRecord* outAGMRecord) const = 0;
	virtual void Dispose() = 0;
};

//=============================================================================

#endif // __IPageItemThumbnail_h__

//  IPageItemThumbnail.h.
