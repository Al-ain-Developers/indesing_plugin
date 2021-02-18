//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IExportProviderSignalData.h $
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
#ifndef __IExportProviderSignalData_h__
#define __IExportProviderSignalData_h__

#include "IPMUnknown.h"

#include "DocFrameworkID.h"

class IDocument ;
class URI;
typedef void* ExportSessionToken;

/**
	Data interface for Export Providers to use when signaling responders.
	@see IExportProvider.h
	@see CExportProvider.h
*/
class IExportProviderSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEXPORTPROVIDERSIGNALDATA };

	/** Set the document */
	virtual void			SetDocument(IDocument* document) = 0;
	/** Get the document */
	virtual IDocument*		GetDocument() const = 0;

	/** DEPRECATED: Use SetURI instead.
		Set the file */
	virtual void			SetFile(const IDFile& file) = 0;
	/** DEPRECATED: Use GetURI instead.
		Get the file */
	virtual IDFile			GetFile() const = 0;

	/** Set the format */
	virtual void			SetFormat(const PMString& format) = 0;
	/** Get the format */
	virtual PMString		GetFormat() const = 0;

	/** Set the UI flags */
	virtual void			SetUIFlags(UIFlags uiFlags) = 0;
	/** Get the UI flags */
	virtual UIFlags			GetUIFlags() const = 0;

	/** Set the unique resource identifier representing the export result.
	*/
	virtual void			SetURI(const URI& uri) = 0;

	/** Get the unique resource identifier representing the export result.
	*/
	virtual const URI&		GetURI() const = 0;

	/** A single export may produce a number of assets, and we need to 
	distinguish between the main export and the extra assets that need to
	be treated differently. 

	Defaults to True.
	*/	 
	virtual void			SetStandAlone(bool8 bIsStandAlone) = 0;
	/** Get the AssetType */
	virtual bool8			IsStandAlone() const = 0;

	/** A session token identifies an export of one or more documents. For
	 the standalone exports this is unused. For exports like JPEG we start
	 return the sessionToken from the standalone export signal and pass it
	 as an argument to the sub-exports.

	 Defaults to nil
	 */
	virtual void			SetSessionToken(ExportSessionToken sessionToken ) = 0;
	virtual ExportSessionToken GetSessionToken() const = 0;
};

#endif // __IExportProviderSignalData_h__
