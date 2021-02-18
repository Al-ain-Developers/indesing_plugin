//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IEBookExport.h $
//  
//  Owner: Gang Xiao
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IEBookExport_h__
#define __IEBookExport_h__

//#include "IPMUnknown.h"

#include "EBookExportID.h"

// ----- Forward -----
class IDocument;
class IBook;

class IEBookExport : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEBOOKEXPORT };

	/**
		Export an indd document to either ePub or xhtml
		@param stream IN The stream to write output
		@param doc IN The document to be exported
		@param uiFlags IN UI Flags. Determines whether dialog boxes are displayed, etc.
		@return kSuccess, kCancel if aborted by user, or an error code kFailure 
	*/
	virtual ErrorCode ExportDocument(IPMStream *stream, IDocument * doc, UIFlags uiFlags = kFullUI) = 0;

	/**
		Export an indesign book to ePub.
		@param stream In The stream to write output
		@param book IN The book to be exported
		@param uiFlags IN UI Flags. Determines whether dialog boxes are displayed, etc.
		@return kSuccess, kCancel if aborted by user, or an error code kFailure 
	*/
	virtual ErrorCode ExportBook(IPMStream * stream, IBook * book, UIFlags uiFlags = kFullUI) = 0;
};

#endif
