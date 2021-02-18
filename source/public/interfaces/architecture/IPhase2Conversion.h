//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPhase2Conversion.h $
//  
//  Owner: Steve Pellegrin
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
//  Purpose of Interface:
//  Manages file format conversions between different versions of plug-ins.
//  
//========================================================================================

#pragma once
#ifndef __IPhase2Conversion__
#define __IPhase2Conversion__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----
#include "OMTypes.h"

// ----- ID.h files -----

#include "ShuksanID.h"


class FormatID;
class IDataBase;
class IPMStream;

/** This interface is passed to each Phase 2 conversion responder via the Respond method.
    The responder will probably need to use information provided by IPhase2Conversion 
    in order to perform its function.
*/

class  IPhase2Conversion : public IPMUnknown
{
// Methods for clients.
public:
	enum { kDefaultIID = IID_IPHASE2CONVERSION };

	/** Get the root object that is being converted.
	    This will typically be the document or workspace root, but may
	    be something else if a Library asset is being converted.
	    @return The root object UIDRef
	*/
	virtual UIDRef GetRootObject() const = 0;

	/** Identifies the type of object being converted.
	*/
	enum RootObjectType
	{
		/** Sorry, we can't figure it out */
		kUnknownType = 0,
		/** Root is a document */
		kDocumentType,
		/** Root is the workspace */
		kWorkspaceType,
		/** Root is a book */
		kBookType,
		/** Root is an asset from a library */
		kAssetType,
		/** Root is a printer preset (printer style) */
		kPrinterPresetType,
		/** Root is a PDFExport style */
		kPDFExportType,
		/** Root is a flattener style import/export */
		kFlattenerStyleType,
		/** Root is a document preset */
		kDocumentPresetType
	};
	
	/** Get the type of object being converted.
	    @return The root object type.
	*/
	virtual RootObjectType GetRootObjectType() const = 0;

	/** Determine which plugin supplied a particular class in the source document.
	    @param clsID IN The class in question.
	    @return The plugin that provided it, or kInvalidPlugin if not found.
	*/
	virtual PluginID GetSourcePluginIDForClass(ClassID clsID) = 0;

	/** Determine which plugin supplied a particular implementation in the source document.
	    @param implID IN The implementation in question.
	    @return The plugin that provided it, or kInvalidPlugin if not found.
	*/
	virtual PluginID GetSourcePluginIDForImplementation(ImplementationID implID) = 0;

	/** Get the source format number for a particular plugin.
	    @param plugin IN The plugin in question.
	    @param format OUT The plugin's source format number.
	    @return kTrue if the information was found, kFalse if not.
	*/
	virtual bool16 GetSourcePluginFormatNumber(PluginID plugin, FormatID &format) = 0;

	/** This method is not yet implemented
	*/
	virtual bool16 ReadSourceData(UID uid, ImplementationID implID, const FormatID &format, IPMStream *outStream) = 0;

	/** Determine which plugin will supply a particular class in the target document.
	    @param clsID IN The class in question.
	    @return The plugin that will provide it, or kInvalidPlugin if not found.
	*/
	virtual PluginID GetTargetPluginIDForClass(ClassID clsID) = 0;

	/** Determine which plugin will supply a particular implementation in the target document.
	    @param implID IN The implementation in question.
	    @return The plugin that will provide it, or kInvalidPlugin if not found.
	*/
	virtual PluginID GetTargetPluginIDForImplementation(ImplementationID implID) = 0;

	/** Get the target format number for a particular plugin.
	    @param plugin IN The plugin in question.
	    @param format OUT The plugin's target format number.
	    @return kTrue if the information was found, kFalse if not.
	*/
	virtual bool16 GetTargetPluginFormatNumber(PluginID plugin, FormatID &format) = 0;

	/** Notify the Conversion Manager that a class has
	    been completely removed from the database during Phase Two conversion.
	    NOTE: Removal is normally done during Phase One conversion.
	          This method is for unusual circumstances.
	    @param clsID IN The class in question
	*/
	virtual void RemoveClass(ClassID clsID) = 0;

	/** Notify the Conversion Manager that a implementation has
	    been completely removed from the database during Phase Two conversion.
	    NOTE: Removal is normally done during Phase One conversion.
	          This method is for unusual circumstances.
	    @param implID IN The implementation in question
	*/
	virtual void RemoveImplementation(ImplementationID implID) = 0;

public:
	/** Set the root object that is being converted.
	    Not for use by clients. Used to set up the interface prior to client use.
	    @param root IN The root object UIDRef.
	*/
	virtual void SetRootObject(const UIDRef &root) = 0;
};


#endif	// __IPhase2Conversion__

