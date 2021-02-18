//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IExportManager.h $
//  
//  Owner: Yeming
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
//  Comment:	Declaration of interface IID_IEXPORTMANAGER
//  
//========================================================================================

#pragma once
#ifndef __IExportManager__
#define __IExportManager__

#include "IPMUnknown.h"
#include "IPrintContentPrefs.h"
#include "TaskInfo.h"

class IDocument;
/**
 Interface used to export documents and books from InDesign native formats
 to some other format(s).
 @see IExportProvider
 @see IPrintContentPrefs
 */
class IExportManager : public IPMUnknown
{
	public:
		/**
		 Exports the front document to a user selectable format.
		 @param printContent	IN Optional pointer to a structure describing what
								   document content to include in the export.
		 */
		virtual void DoExport(IPrintContentPrefs * printContent = nil) = 0;

		/**
		 Exports a book to a user selectable format.
		 @param printContent	IN Optional pointer to a structure describing what
								   book content to include in the export.
		 */
		virtual void ExportBook(IPrintContentPrefs *printContent = nil) = 0;

		/**
		 Directly exports the document to PDF. If no document is specified, export front document \\
		 No other export formats are available to choose from when exporting
		 to PDF via this method. \\
		 Note: If bShowUI is kFalse and uidStyle is kInvalidUID, then the current 
			   custom app PDF settings will be used when exporting.
		 @param uiFlags			IN Denotes setting to show UI.
		 @param uidStyle		IN UID of the PDF Export style to use when exporting.
		 @param printContent	IN Optional pointer to a structure describing what
								   document content to include in the export.
		 @param sysFilePath		IN Optional pointer to path where exported file should be saved.
		 @param taskInfo		OUT Optional pointer to get TaskInfo if export is background process.
		 @param document		IN  Optional pointer to document to be converted to PDF.
		 */
		virtual void ExportPDFDirect(UIFlags uiFlags, UIDRef& uidStyle, IPrintContentPrefs *printContent = nil, const IDFile* sysFilePath = nil, TaskInfo *taskInfo = nil, IDocument *document = nil) = 0;

		/**
		 Directly exports the specified document to IDML. \\
		 No other export formats are available to choose from when exporting
		 to IDML via this method. \\
		 @param docRef IN UIDRef of the document to export
		 @param destFile IN The destination file to export to
		 @param bShowUI	IN Denotes whether to show UI.
		 @param taskInfo	OUT Optional pointer to get TaskInfo if export is background process.
		 */
		virtual void ExportIDMLDirect(const UIDRef& docRef, const IDFile* destFile, bool16 bShowUI, TaskInfo *taskInfo = nil) = 0;
};

#endif

