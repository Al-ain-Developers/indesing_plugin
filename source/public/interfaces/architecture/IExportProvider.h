//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IExportProvider.h $
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
//========================================================================================

#pragma once
#ifndef __IExportProvider__
#define __IExportProvider__

#include "IPMUnknown.h"
#include "PMString.h"
#include "PMFlavorTypes.h"
#include "RequestContext.h"
#include "DocFrameworkID.h"

class TaskInfo;
class IDocument;
class IDataExchangeHandler;

/**
 IExportProvider is the main interface an export filter has to implement.
 Export filters provide export functionality from InDesign native formats
 to some other format(s).
 @see IExportManager
 */
class IExportProvider : public IPMUnknown
{
	public:
	enum { kDefaultIID = IID_IEXPORTPROVIDER };
	
	/**@name  Export  */
	//@{-----------------------------------------------------------------------------
	
		/**
		 Exports the current selection to the given file, which must have a valid path.
		 The provider will generate the specified file format. \\
		 The calling code must verify that the given file does not exist. \\
		 Note: Some export providers may display UI and may export more than just
			   the current selection (i.e. PDF export, EPS export, etc.)
		 @param sysFile		IN File to export to.
		 @param doc			IN Document we're exporting from.
		 @param targetboss	IN Target boss.
		 @param formatName	IN Name of the format we're exporting.
		 @param uiFlags		IN UI flags denoting how to handle UI events. (see BaseType.h)
		 */
		virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI) = 0;

		/**
		 Exports the current selection to the given stream.
		 The provider will generate the specified file format. \\
		 Note: Some export providers may display UI and may export more than just
			   the current selection (i.e. PDF export, EPS export, etc.).
		 @param stream		IN Streaam to export to.
		 @param doc			IN Document we're exporting from.
		 @param targetboss	IN Target boss.
		 @param formatName	IN Name of the format we're exporting.
		 @param uiFlags		IN UI flags denoting how to handle UI events. (see BaseType.h)
		 */
		virtual void ExportToStream(IPMStream* stream, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI) = 0;
				
		/**
		 The provider indicates whether it can perform exports to a file.
		 @return kTrue if the provider can export to a file, else false.
		 */
		virtual bool16 CanExportToFile() const = 0;

		/**
		 The export provider indicates whether it can export the current selection in the
		 specified file format (i.e. a text export file would return kFalse for a page item selection
		 and kTrue for a text selection).
		 @param doc			IN Document we're exporting from.
		 @param targetboss	IN Target boss.
		 @param formatName	IN Name of the format we're exporting.
		 @return kTrue if the provider supports exporting in the current context, else kFalse.
		 */
		virtual bool16 CanExportThisFormat(IDocument* doc, IPMUnknown* targetboss, const PMString& formatName) = 0;

		/**
		Exports the current selection asynchronously to the given file, which must have a valid path.
		The provider will generate the specified file format. \\
		The calling code must verify that the given file does not exist and that no running exports \\
		are targeting the same file.

		The asynchronous nature of this call means that operations that rely on the outcome of the
		export can no longer happen right after the call. Instead these operations should be moved
		into a signal responder that responds to two signals:

			kAfterExportSignalResponderService    (signaled on kSuccess)
			kFailedExportSignalResponderService   (signaled on any other error code)

		Note: Some export providers may use the task monitor for UI	and may export more than just the \\
		current selection (i.e. PDF export, EPS export, etc.)

		@param sysFile		IN File to export to.
		@param doc		    IN Document we're exporting from.
		@param targetboss	IN Target boss.
		@param formatName	IN Name of the format we're exporting.
		@param uiFlags		IN UI flags denoting how to handle UI events. (see BaseType.h) \\
		FullUI means that progress and alert UI events will be handled \\
		by the task monitor.

		@return TaskInfo representing the export task. The caller must not use the destination file\\
		until TI.GetCurrentState() == TaskInfo::kCompleted.  (where TI is the TaskInfo)

		*/
		virtual TaskInfo AsynchronousExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI) = 0;

		/**
		 The provider indicates whether it can perform asynchronous exports to a file.
		 @return kTrue if the provider can export asynchronously to a file, else false.
		 */
		virtual bool16 CanExportToFileAsynchronously() const = 0;

	//@}-----------------------------------------------------------------------------

	/**@name  Clipboard/DragDrop Export  */
	//@{-----------------------------------------------------------------------------

		/**
		 The provider indicates whether it can export to the clipboard.
		 @return kTrue if the provider supports exporting to the clipboard, else kFalse.
		*/
		virtual bool16 CanExportForExternalize() const = 0;

		/**
		 For Clip/Drag operations, returns the internal flavor the provider can operate on.
		 @return Internal flavor the provider can operate on.
		 */
		virtual PMFlavor GetInternalFlavor() const = 0;
		
		/**
		 For Clip/Drag operations, returns the number of external flavors the provider can export to.
		 @return Number of external flavors the provider can export to.
		 */
		virtual int32 CountExternalFlavors() const = 0;

		/**
		 For Clip/Drag operations, returns the n'th flavor the provider can export to.
		 @param n	IN Index of the external flavor to return.
		 @return N'th external flavor the provider can export to.
		 */
		virtual ExternalPMFlavor GetExternalFlavor(int32 n) const = 0;

		/**
		 For Clip/Drag operations, what format type, if any, would the provider use
		 to produce the desired external flavor.
		 @param flavor			IN External flavor to export.
		 @param outFormatName	OUT Format type the provider would export for the given external flavor.
		 @return kTrue if the provider can export the external flavor, else kFalse.
		 */
		virtual bool16 CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const = 0;
			
		/**
		 Externalize the given data to a stream.
		 @param handler			IN Handler to use to exchange the data.
		 @param toWhichFlavor	IN External flavor to export.
		 @param stream			IN Stream to export to.
		 @return kSuccess if the export succeeds, else an error code.
		 */
		virtual ErrorCode ExportForExternalize(IDataExchangeHandler *handler, const ExternalPMFlavor toWhichFlavor, IPMStream* stream) = 0;
			
	//@}-----------------------------------------------------------------------------

	/**@name  Internal File Based Formats  */
	//@{-----------------------------------------------------------------------------
	
		/**
		 Returns the number of file formats supported by this export provider.
		 @return Number of file formats supported.
		 */
		virtual int32 CountFormats() = 0;
			
		/**
		 Returns the name (non-localized string) of the n'th file format supported by this export provider.
		 @param n	IN Index of the format name to return.
		 @return Name of the n'th format.
		 */
		virtual PMString GetNthFormatName(int32 n) = 0;
			
		/**
		 Returns the preferred file extension of the format name.
		 @param formatName	IN Format name whose preferred file extension to return.
		 @return Preferred file extension of the format name.
		 */
		virtual PMString GetExtensionForFormatName(const PMString& formatName) = 0;

		/**
		 Returns the ScriptID for the given format's enumerator in the kExportFormatEnumScriptElement
		 @param formatName	IN Format name whose ScriptID to return
		 @param context is the scripting request context
		 @return the ScriptID (or kInvalidScriptID if this format is not supported by enum)
		 */
		virtual ScriptID GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context) = 0 ;
	//@}-----------------------------------------------------------------------------
};

#endif
