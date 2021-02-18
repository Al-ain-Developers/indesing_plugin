//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IConversionMgr.h $
//  
//  Owner: Robin Briggs
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
#ifndef __IConversionMgr__
#define __IConversionMgr__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "FormatNumber.h"
#include "K2Vector.h"

// ----- ID.h files -----

#include "ShuksanID.h"


class FormatID;
class VersionID;
class IDataBase;
class IPMStream;
class IContentMgr;
class IConversionProvider;

/**
    IConversionMgr is the key interface in the binary database conversion process.
	Although it is public, you are unlikely to need to call it directly. Conversion
	is a complex process. The methods in this interface must be called in a particular
	context and in a particular order. Caution is advised.
*/
class  IConversionMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONVERSIONMGR };

	/** Values returned by GetStatus() */
	enum ConversionStatus
	{
		/** Conversion not yet initialized */
		kUnknownConvert,
		/** Conversion is not necessary */
		kDontConvert,
		/** Conversion is necessary: call ConvertDocument */
		kMustConvert,
		/** Conversion is not possible (converters are missing) */
		kCantConvert
	};

	/** This method is used to determine whether conversion is necessary and possible.
	    Each plug-in's source format number can be found in the document's Content Manager.
		@param contentMgr IN The Content Manager associated with the database to be checked.
		@return An enum value that indicates whether the database should be (and can be) converted
		@see IContentMgr
	*/
	virtual ConversionStatus GetStatus(IContentMgr *contentMgr) = 0;

	/** This method must be called after GetStatus. It returns a list of plugins that
	    would be removed by the conversion if ConvertDocument is called.
		@param list OUT A list of the IDs of plugins that would be removed.
	*/
	virtual void GetRemovedPlugins(K2Vector<PluginID> &list) = 0;

	/** This method must be called after GetStatus. It returns a list of plugins that
	    would have their priority reset to "Ignore" by the conversion if ConvertDocument is called.
		@param list OUT A list of the IDs of plugins that would be ignored.
	*/
	virtual void GetIgnoredPlugins(K2Vector<PluginID> &list) = 0;
	
	/** Performs any neccessary conversion from the existing database format to the most recent format.
	    @param dbToConvert IN A pointer to the database to be converted.
	*/
	virtual void ConvertDocument(IDataBase *dbToConvert) = 0;

	/** Open a session on the conversion manager. Compiles information about what
	    data needs to be converted. 
		@param contentMgr IN The Content Manager associated with the database to be checked.
	*/
	virtual void Open(IContentMgr *contentMgr) = 0;

	/** Close the conversion session. Call this to complete a conversion session.
	*/
	virtual void Close() = 0;
  
  	/** ConvertClass converts from the original format in the document to the current
  	    running format. No conversion is performed if the classID does not need conversion. 
  	    @param inClass IN ClassID of the data in the stream
  	    @param parentContext IN	Containing context, or kInvalidImpl if it is in a UID
  	    @param inStream IN Stream containing data to be converted
  	    @param outStream IN Converted data is streamed out here
  	    @param length IN Number of bytes of incoming data
  	    @return The converted ClassID. Usually this is the same as inClass, but may be a
  	    different ClassID if inClass has been renumbered, or kInvalidClass if the
  	    class should be deleted.
	*/
  	virtual ClassID ConvertClass(ClassID inClass, ImplementationID parentContext, IPMStream *inStream, IPMStream *outStream, int32 length) = 0;
  	
  	/** Copies a Class' data from the input to the output stream, converting embedded objects, if necessary.
	    @param inClass IN ClassID of the data in the stream
		@param version IN Version of the data
		@param isEmbedded IN kTrue if this data is embedded inside of another object
		@param inLength IN Number of bytes of incoming data
  	    @param inStream IN Stream containing data to be copied
  	    @param outStream IN Data is copied here
		@return kTrue if the copy operation required the use of a Content Iterator, kFalse if not.
	*/
	virtual bool16 CopyClassData(ClassID inClass, const VersionID &version, bool16 isEmbedded, uint32 inLength, IPMStream *inStream, IPMStream *outStream) = 0;
	 
  	/** ConvertTag converts from the original format in the document to the current
  	    running format. No conversion is performed if the ImplementationID does not need conversion. 
  	    @param inTag IN ImplementationID of the data in the stream
  	    @param parentContext IN	Containing context
  	    @param inStream IN Stream containing data to be converted
  	    @param outStream IN Converted data is streamed out here
  	    @param length IN Number of bytes of incoming data
  	    @return The converted ImplementationID. Usually this is the same as inTag, but may be a
  	    different ImplementationID if inTag has been renumbered, or kInvalidImpl if the
  	    implementation should be deleted.
	*/
  	virtual ImplementationID ConvertTag(ImplementationID inTag, ClassID parentContext, IPMStream *inStream, IPMStream *outStream, int32 length) = 0;
  	
  	/** Copies an Implementation's data from the input to the output stream, converting embedded objects, if necessary.
	    @param inImpl IN ImplementationID of the data in the stream
		@param version IN Version of the data
		@param inLength IN Number of bytes of incoming data
  	    @param inStream IN Stream containing data to be copied
  	    @param outStream IN Data is copied here
		@return kTrue if the copy operation required the use of a Content Iterator, kFalse if not.
	*/
	virtual bool16 CopyTagData(ImplementationID inImpl, const VersionID &version, uint32 inLength, IPMStream *inStream, IPMStream *outStream) = 0;
	
	/** Gets a pointer to the database that is currently being converted, or nil if
	    there is no conversion session active.
		@return The database, or nil
	*/
	virtual IDataBase *GetConvertingDataBase() = 0;

	/** Gets the UID of the object currently being converted, or kInvalidUID. Note that
	    this will return the enclosing UID even if the object currently being converted
	    is an embedded object inside a UID.
		@return The UID or kInvalidUID
	*/
	virtual UID GetConvertingUID() = 0;

	/** Get the number of plugins that can't be converted.
	    @return The count
	*/
	virtual int32 CountConversionFailures() = 0;

	/** Get the n-th plugin that can't be converted.
	    @param n IN Which plugin
		@return The plugin ID, or kInvalidPlugin if n is invalid
	*/
	virtual PluginID GetNthFailedConversion(int32 n) = 0;

	/** Determine which plugin supplied a particular class in the source document.
	    @param id IN The class ID
		@return The plugin ID, or kInvalidPlugin if the class was not in the source document
	*/
	virtual PluginID GetSourcePluginIDForClass(ClassID id) = 0;

	/** Determine which plugin supplied a particular implementation in the source document.
	    @param id IN The implementation ID
		@return The plugin ID, or kInvalidPlugin if the implementation was not in the source document
	*/
	virtual PluginID GetSourcePluginIDForImplementation(ImplementationID id) = 0;

	/** Get the source format number for a particular plugin.
	    @param plugin IN The plugin
		@param format OUT The source format number
		@return kTrue if the plugin was in the source document, kFalse if not.
	*/
	virtual bool16 GetSourcePluginFormatNumber(PluginID plugin, FormatID &format) const = 0;

	/** Fill a stream with an object's data as it existed prior to the start of conversion.
		@param uid IN The object's UID
		@param implID IN Which implementation
		@param format IN Which format
		@param outStream IN The stream that will receive the data
	    @return kTrue if successful, kFalse if the object/instance isn't found, or conversion to the desired format number is not possible
	*/
	virtual bool16 ReadSourceData(UID uid, ImplementationID implID, const FormatID &format, IPMStream *outStream) = 0;

	/** Determine which plugin will supply a particular class in the target document.
	    @param id IN The class ID
		@return The plugin ID, or kInvalidPlugin if the class will not be in the target document
	*/
	virtual PluginID GetTargetPluginIDForClass(ClassID id) = 0;

	/** Determine which plugin will supply a particular implementation in the target document.
	    @param id IN The implementation ID
		@return The plugin ID, or kInvalidPlugin if the implementation will not be in the target document
	*/
	virtual PluginID GetTargetPluginIDForImplementation(ImplementationID id) = 0;

	/** Get the target format number for a particular plugin.
	    @param plugin IN The plugin
		@param format OUT The target format number
		@return kTrue if the plugin will bein the target document, kFalse if not.
	*/
	virtual bool16 GetTargetPluginFormatNumber(PluginID plugin, FormatID &format) = 0;

	/** Notify the Conversion Manager that a Class has been
	    completely removed from the database during Phase Two conversion.
	    NOTE: Removal is normally done during Phase One conversion.
	          This method is for unusual circumstances.
	    @param clsID IN The class that was removed
	*/
	virtual void RemoveClass(ClassID clsID) = 0;

	/** Notify the Conversion Manager that an Implementation has been
	    completely removed from the database during Phase Two conversion.
	    NOTE: Removal is normally done during Phase One conversion.
	          This method is for unusual circumstances.
	    @param implID IN The implementation that was removed
	*/
	virtual void RemoveImplementation(ImplementationID implID) = 0;
	
#if defined(DEBUG)
	/** Internal method used for testing. Do not use. */
	virtual void OverrideRunningVersion(const VersionID& substitueVersion) = 0;
#endif
};


#endif	// __IConversionMgr__
