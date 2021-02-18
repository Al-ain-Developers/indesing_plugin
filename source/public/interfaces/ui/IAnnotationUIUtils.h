//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IAnnotationUIUtils.h $
//  
//  Owner: anagarw
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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
#ifndef __IANNOTATIONUIUTILS__
#define __IANNOTATIONUIUTILS__
//-----------------------------------
//	Forward References
//

#include "IPMUnknown.h"
#include "PDFID.h"

class IControlView;
class IDocument;
class IImportPDFAnnotation;
class IRCAnnotation;

class IAnnotationUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANNOTATIONUIUTILS };
	
    /** Provides the PDF comment that has been imported and has been hit in the layout.
     @param layoutView : THe IControlView* for the layout.
     @param mousePBPoint : Point where mouse is clicked.
     @param itemUID : The reference to the UID of the page or page item that has been hit.
     @return UID of the comment that has been hit in the view.
     */
    virtual UID GetHitPDFCommentAdornment(IControlView* layoutView, PBPMPoint mousePBPoint, UID& itemUID) = 0;
    
    /** Invalidates all pdf comment drawings areas present in the document. Invalidating this area will triggers the re-drawing of adornment.
     Called after ImpoerPDFComments.
     */
    virtual void InvalidateAllCommentAdornmentArea(const IDocument* document) = 0;
    
    /** Invalidates given pdf comment drawing area. Invalidating this area will triggers the re-drawing of adornment.
     Called after enable/disable of comment drawing
     */
    virtual void InvalidateGivenPDFCommentAdornmentArea(const IImportPDFAnnotation* annot) = 0;
    
    /** Invalidates all comment drawing areas of given pageItem. Invalidating this area will triggers the re-drawing of adornment.
     */
    virtual void InvalidateCommentAdornmentAreaOfGivenPageItem(const UIDRef &pageItem) = 0;
    
    /** Invalidates given review collaboration comment drawing area. Invalidating this area will triggers the re-drawing of adornment.
     Called after enable/disable of comment drawing
     */
    virtual void InvalidateGivenRCCommentAdornmentArea(const IRCAnnotation* annot) = 0;
};

#endif // __IANNOTATIONUIUTILS__
