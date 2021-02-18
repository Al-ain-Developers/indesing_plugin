//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInCopyPDFNoteAnnotations.h $
//  
//  Owner: Tommy Donovan
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
//  Purpose:
//  The interface is for the pdf export to draw notes as annotations in layout mode in InCopy.	
//  
//========================================================================================

#pragma once
#ifndef __IInCopyPDFNoteAnnotations__
#define __IInCopyPDFNoteAnnotations__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "GraphicsID.h"
#include "PMRect.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "IGraphicsContext.h"

/** This interface draw Notes as PDF annotation when export PDF with Notes in layout view in InCopy
*/
class IInCopyPDFNoteAnnotations : public IPMUnknown
{
	public:

/**	Draw all notes belongs to the actualPageBounds as PDF annotation
	@param gc The PDF graphics context 
	@param actualPageBounds 
 */
		virtual void DrawNoteAnnotations(IGraphicsContext* gc, const PMRect& actualPageBounds = PMRect(0,0,0,0)) = 0;

};


#endif
