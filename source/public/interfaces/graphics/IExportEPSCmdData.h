//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IExportEPSCmdData.h $
//  
//  Owner: David Berggren
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
//  Command data for exporting an EPS or SEP file. Used for
//  the kExportEPSCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __IExportEPSCmdData__
#define __IExportEPSCmdData__

#include "IPMUnknown.h"
#include "IDocument.h"
#include "IDFile.h"
#include "PrintID.h"
typedef void* ExportSessionToken;

/** Command data interface for exporting to EPS.
	@see IEPSExportPreferences
*/
class IExportEPSCmdData : public IPMUnknown
{
public:
	/** Default enum
	*/
	enum { kDefaultIID = IID_IEXPORTEPSCMDDATA };

	/**	Set method for exporting to a file, or multiple files if EPS format
		@param fileToExportTo IN the file to export to
		@param iDoc IN the IDocument interface for the pub
		@param format IN should be kExportEPSFile, as defined in IEPSExportPreferences.h
		@param sessionToken IN an identifier for the export session. Used to group files for workgroup checkins
	 */
	virtual void Set(const IDFile& fileToExportTo, IDocument* iDoc, const int32 format, ExportSessionToken sessionToken) = 0;

	/** Get the file to export to
		@param fileToExportTo OUT the file to export to
	*/
	virtual void GetFile(IDFile* fileToExportTo) const = 0;

	/** Get the IDocument interface for the pub
		@return IDocument pointer
	*/
	virtual IDocument* GetIDoc() const = 0;

	/** Get the export format
		@return int32 should be should be kExportEPSFile, as defined in IEPSExportPreferences.h
	*/
	virtual int32 GetFormat() const = 0;

	/** Set method for exporting to a stream, NOTE: if exporting to EPS and there
		are multiple pages, only the first page will export to the stream.
		@param iStream IN the stream to export to 
		@param iDoc IN the IDocument interface for the pub
		@param format IN should be kExportEPSFile, as defined in IEPSExportPreferences.h
	 */
	virtual void SetWithStream(IPMStream *iStream, IDocument* iDoc, const int32 format) = 0;

	/** Get the stream to export to
		@return IPMStream pointer to the export stream
	*/
	virtual IPMStream* GetStream() const = 0;

	/** Get the export session identifier
		@return the ExportSessionToken that identifies this export
	*/
	virtual ExportSessionToken GetSessionToken() const = 0;
};

#endif
