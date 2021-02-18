//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightAggregatedResultsExport.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "IPreflightAggregatedResults.h"
#include "PackageAndPreflightID.h"
#include "ScriptData.h"

/** This helper interface handles export functions for aggregated results. It sits on the 
	same boss as IPreflightAggregatedResults. Since these methods don't really have anything 
	to do with the model, we don't want to clutter up the IPreflightAggregatedResults
	interface.

	@see IPreflightAggregatedResults

	Typical usage:

		DoExport(IPreflightAggregatedResults* iResults)
		{
			InterfacePtr<IPreflightAggregatedResultsExport> iExport(iResults, UseDefaultIID());
			ReportFileTypeInfoVector types;
			iExport->GetExportFileParameters(docName, kFalse, profileName, defFile, &types);

			// Set up your save-as dialog with 'types' or however you intend to use it
			IDFile destFile = AskUserForDestination(types);

			iExport->ExportToFile(docName, kFalse, profileName, destFile, kTrue);
		}

	See also the preflight export generating script found in the scripts/preflight folder.
*/

class IPreflightAggregatedResultsExport : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTAGGREGATEDRESULTSEXPORT };

public:
	/** A file type that the report can support. A vector of these is returned 
		by GetExportFileParameters. 
	*/
	class ReportFileTypeInfo
	{
	public:
		/** For K2Vector's benefit */
		typedef object_type data_type;

		/** The extension, eg "pdf" */
		PMString fExtension;

		/** Describes the type, eg "Portable Document Format (*.pdf)" */
		PMString fDescription;

		ReportFileTypeInfo(){}
	};

	typedef K2Vector<ReportFileTypeInfo> ReportFileTypeInfoVector;

	/** Gets the parameters needed to produce a save-as dialog for the report.
		@see ExportToFile.

		@param sDocName IN The name of the document that was preflighted.
		@param isBook IN True if the 'document' is a book; False if it's an INDD.
		@param sProfileName IN The name of the profile that was used.
		@param defaultFile OUT Receives the IDFile representing the default save-as file name/location.
		@param sDesc OUT Receives the description of the file type.
		@param fileType OUT Receives the file type ID (MacOS)
		@param creatorType OUT Receives the file creator type (MacOS)
		@param sExtension OUT Receives the extension to use.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode GetExportFileParameters
		(
			const PMString& sDocName, 
			bool isBook, 
			const PMString& sProfileName, 
			IDFile& defaultFile, 
			ReportFileTypeInfoVector& fileTypes
		) const = 0;

	/** Exports the report to the specified file. Note that the supported output types may
		vary depending on the script providing that capability; to be sure you can export to
		the file, @see GetExportFileParameters.

		@param sDocName IN The name of the document that was preflighted.
		@param isBook IN True if the 'document' is a book; False if it's an INDD.
		@param sProfileName IN The name of the profile that was used.
		@param exportFile IN The file to export to.
		@param openAfterCreate IN True to open (display) the file after creation.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode ExportToFile
		(
			const PMString& sDocName,
			bool isBook, 
			const PMString& sProfileName,
			const IDFile& exportFile,
			bool openAfterCreate
		) const = 0;

	/*	Package the preflight result associated with this document's active process and returns the result as a list of script data.
		@param sDocName IN The name of the document that was preflighted.
		@param sProfileName IN The name of the profile that was used.
		@param resultEntries OUT The preflight results.
	*/
	virtual void PackageResults
		(
			const PMString& sDocName, 
			const PMString& sProfileName, 
			ScriptListData& resultEntries 
		) const = 0;

};

