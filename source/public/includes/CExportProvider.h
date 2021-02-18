//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CExportProvider.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __CExportProvider_h__
#define __CExportProvider_h__

#include "IExportProvider.h"
#include "IDocument.h"
#include "URI.h"

struct UserTaskJobSpec;
typedef void* ExportSessionToken;
#ifdef PUBLIC_DECL
#pragma export on
#endif

/**
	Core base class implementation for IExportProvider
*/

class PUBLIC_DECL CExportProvider : public CPMUnknown<IExportProvider>
{			
public:
	CExportProvider(IPMUnknown* boss);
	virtual ~CExportProvider();

	/**@name  File Export  */
	//@{-----------------------------------------------------------------------------

	/** Export to a file. Default implementation calls ExportToStream. */
	virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags);
	
	/** The provider indicates whether it can do normal file based exports. */
	virtual bool16 CanExportToFile() const;

	/** Export to a file asynchronously and return. Default implementation is Unimplemented. */
	virtual TaskInfo AsynchronousExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI);

	/**	 The provider indicates whether it can do asynchronous file based exports */
	virtual bool16 CanExportToFileAsynchronously() const;

	//@}-----------------------------------------------------------------------------

	/**@name  Clipboard/DragDrop Export  */
	//@{-----------------------------------------------------------------------------

	//	Stub this out since only a few ExportProviders actually support this type of export
	
	/** The provider indicates whether it can do normal file-based exports. */
	virtual bool16 CanExportForExternalize() const;

	/** For Clip/Drag operations, what internal flavor does this exporter operate on? */
	virtual PMFlavor GetInternalFlavor() const;
	
	/** For Clip/Drag operations, what external flavors can this exporter produce? */
	virtual int32 CountExternalFlavors() const;
	virtual ExternalPMFlavor GetExternalFlavor(int32 n) const;

	/** For Clip/Drag operations, what format type, if any, would be used to produce the desired external flavor? */
	virtual bool16 CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const;
		
	/** Externalize the given data to a stream. */
	virtual ErrorCode ExportForExternalize(IDataExchangeHandler *handler, const ExternalPMFlavor toWhichFlavor, IPMStream* stream);

	//@}-----------------------------------------------------------------------------

protected:
	
	/** Send an export signal to responders
		@param service IN is the signal's service ID
		@param document IN is the target document
		@param sysFile IN is the file being exported
		@param formatName IN is the format being exported
		@param uiFlags IN are the ui flags
		@param bIsStandAlone IN is this a single-file export (kTrue), or part of a multi-file export(kFalse)
	*/
	virtual ErrorCode SendSignal( const ServiceID& service, IDocument* document, const IDFile& sysFile, const PMString& formatName, UIFlags uiFlags, bool8 bIsStandAlone = kTrue ) ;

	/** Check for export file conflicts
		
		@param sysFile IN is the file being exported
		@return kTrue if an AsynchronousExport is exporting to the same file
	*/
	virtual bool16 IsTargetFileInUseByBGTasks(const IDFile& sysFile) const ;

	/** Construct an AsyncWorkPacketJobSpec for a particular export
		@param sysFile IN is the file being exported
		@param document IN is the document being exported
		@param formatName IN is the format being exported
		
		@return an object that represents the export for the sake of the TaskMonitor
	*/
	virtual UserTaskJobSpec CreateExportJobSpec(const IDFile& sysFile, IDocument* document, const PMString& formatName ) const ;

protected:
	ExportSessionToken fSessionToken;
};

#pragma export off

#endif // __CExportProvider_h__
