//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportProviderUtils.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IImportProviderUtils__
#define __IImportProviderUtils__

#include "IPMUnknown.h"

#include "AppFrameworkID.h"
#include "PMFlavorTypes.h"
#include "Utils.h"

class IDocument;
class IExportProvider;
class IImportProvider;
class IPlaceBehavior;
class URI;
typedef void* ExportSessionToken;

/** Utility interface for import and export providers. Providers are used to cnvert between internal and external data/file formats.

		@see IImportProvider, IExportProvider

	@ingroup layout_util
*/
class IImportProviderUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMPORTPROVIDERUTILS };


	/** Query for import provider to handle a data conversion. 

		@param fromWhichFlavor IN external data format the data is to be converted from
		@param toWhichInternalFlavor IN internal data format the data is to be converted to
		@return an import provider capable of performing the conversion, or nil.
	*/
	virtual IImportProvider* QueryImportProviderFor(
		const ExternalPMFlavor fromWhichFlavor, const PMFlavor toWhichInternalFlavor) = 0;

	/** Can a provider support conversion from a specific external flavor.

		@param provider IN the provider
		@param flavor IN the external flavor
		@return true if the provider can perform a conversion
	*/
	virtual bool16 DoesProviderSupportExternalFlavor(IImportProvider *provider, const ExternalPMFlavor flavor) = 0;
	
	/** Query for import provider to handle a file conversion. 

		@param fileType IN the type of the file
		@return an import provider capable of performing the conversion, or nil.
	*/
	virtual IImportProvider* QueryImportProviderForFileType(const SysOSType fileType) = 0;

	/** Can a provider support conversion from a specific file type.

		@param provider IN the provider
		@param fileType IN a file type
		@return true if the provider can perform a conversion
	*/
	virtual bool16 DoesProviderSupportFileType(IImportProvider *provider, const SysOSType fileType) = 0;
	
	/** Query for export provider to handle a data conversion. 

		@param fromWhichInternalFlavor IN internal data format the data is to be converted from
		@param toWhichFlavor IN external data format the data is to be converted to
		@return an export provider capable of performing the conversion, or nil.
	*/
	virtual IExportProvider* QueryExportProviderFor(
		const PMFlavor fromWhichInternalFlavor, const ExternalPMFlavor toWhichFlavor) = 0;

	/** Can a provider support conversion to a specific external flavor.

		@param provider IN the provider
		@param flavor IN the external flavor
		@return true if the provider can perform a conversion
	*/
	virtual bool16 DoesProviderSupportExternalFlavor(IExportProvider *provider, const ExternalPMFlavor flavor) = 0;
	
	/** Compute the list of external flavors that a given internal flavor can be converted to via exporters

		@param fromWhichInternalFlavor IN the internal data format
		@param toWhichFlavors OUT the list of flavors the data could be converted to
		@return the number of possible conversions
	*/
	virtual uint32 GetFlavorsForExport(const PMFlavor fromWhichInternalFlavor, ExternalPMFlavorList& toWhichFlavors) = 0;
	
	/** Compute the list of external flavors that a given internal flavor can be produced from via importers

		@param toWhichInternalFlavor IN the internal data format
		@param fromWhichFlavors IN the list of flavors the data could be produced from
		@return the number of possible conversions
	*/
	virtual uint32 GetFlavorsForImport(const PMFlavor toWhichInternalFlavor, ExternalPMFlavorList& fromWhichFlavors) = 0;

	/** Send an import or export signal to responders
		@param service IN is the signal's service ID
		@param document IN is the target document
		@param uri IN is the resource/file being im/exported. 
		@param formatName IN is the format being im/exported
		@param uiFlags IN/OUT are the ui flags, which could be changed by a responder
	    @param bIsStandAlone IN determines if this asset is a standalone asset or part of a group of assets
	    @param sessionToken IN/OUT an ExportSessionToken passed by reference. Updated by each call.
		@return global error code if set by a responder
	*/
	virtual ErrorCode SendImportExportSignal( const ServiceID& service, IDocument* document, const URI& uri, const PMString& formatName, UIFlags& uiFlags, bool8 bIsStandAlone = kTrue, ExportSessionToken* sessionToken = nil ) = 0 ;

	/** DEPRECATED: Use the version that passes a URI instead of an IDFile.
		Send an import or export signal to responders
		@param service IN is the signal's service ID
		@param document IN is the target document
		@param sysFile IN is the file being im/exported
		@param formatName IN is the format being im/exported
		@param uiFlags IN/OUT are the ui flags, which could be changed by a responder
		@param bIsStandAlone IN determines if this asset is a standalone asset or part of a group of assets
		@param sessionToken IN/OUT an ExportSessionToken passed by reference. Updated by each call.
		@return global error code if set by a responder
	*/
	virtual ErrorCode SendImportExportSignal( const ServiceID& service, IDocument* document, const IDFile& sysFile, const PMString& formatName, UIFlags& uiFlags, bool8 bIsStandAlone = kTrue, ExportSessionToken* sessionToken = nil ) = 0 ;

	/** Send an place or replace signal to responders
		@param service IN is the signal's service ID
		@param source IN is the source's IPlaceBehavior
		@param target IN is the target's IPlaceBehavior (may be nil, e.g., for a snippet)
		@param result IN is the placed items (may be empty, e.g., for before place)
		@return global error code if set by a responder
	*/
	virtual ErrorCode SendPlaceReplaceSignal( const ServiceID& service, IPlaceBehavior* source, IPlaceBehavior* target, const UIDList& result ) = 0 ;
};

#endif	// __IImportProviderUtils__
