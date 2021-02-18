//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IConversionProvider.h $
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
#ifndef __IConversionProvider__
#define __IConversionProvider__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "ShuksanID.h"


class FormatID;
class VersionID;


/**
    IConversionProvider is a key interface in the binary database conversion process.
	Although it is public, you are unlikely to need to call it directly. If you are writing
	a "code converter", you must implement this interface. However, it recommended that you
	base your converter on the CConversionProvider base class instead.
	@see CConversionProvider
*/
class  IConversionProvider : public IPMUnknown
{
public:
	/** Return the number of conversions this converter can convert.
	    @return The count
	*/
	virtual int32 CountConversions() const = 0;

	/** Return the n'th conversion supported by this converter.
	    The answer is in the form of a pair of VersionIDs. You might think of it as meaning
		"The i-th conversion transforms data in the format 'fromVersion' to format 'toVersion'"
	    @param i IN Which conversion
		@param fromVersion OUT The source version of this conversion
		@param toVersion OUT The target version of this conversion
	*/
	virtual void GetNthConversion(int32 i, VersionID *fromVersion, VersionID *toVersion) const = 0;

	/** Return the number of plugins removed between the specified range of format numbers.
	    @param fromVersion IN The source version
		@param toVersion IN The target version
		@return The count
	*/
	virtual int32 CountRemovedPlugins(const VersionID &fromVersion, const VersionID &toVersion) const = 0;

	/** Return the n'th removed plugin.
	    @param fromVersion IN The source version
		@param toVersion IN The target version
		@param n IN Which plugin
		@return The removed plugin ID, or kInvalidPlugin if n is invalid
	*/
	virtual PluginID GetNthRemovedPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const = 0;

	/** Return the number of plugins set to "Ignore" between the specified range of format numbers.
	    @param fromVersion IN The source version
		@param toVersion IN The target version
		@return The count
	*/
	virtual int32 CountIgnoredPlugins(const VersionID &fromVersion, const VersionID &toVersion) const = 0;

	/** Return the n'th ignored plugin.
	    @param fromVersion IN The source version
		@param toVersion IN The target version
		@param n IN Which plugin
		@return The ignored plugin ID, or kInvalidPlugin if n is invalid
	*/
	virtual PluginID GetNthIgnoredPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const = 0;

	/** Return the number of "aliases" (Created when a Class is moved from one Plugin to another).
	    @return The count
	*/
	virtual int32 CountClassAliases() const = 0;

	/** Return the number of "aliases" (Created when an Implementation is moved from one Plugin to another).
	    @return The count
	*/
	virtual int32 CountImplementationAliases() const = 0;
	
	/** Return the n'th class alias.
	    @param n IN Which alias
		@param fromID OUT The source class ID
		@param fromVersion OUT The source version
		@param toID OUT The target class ID
		@param toVersion OUT The target version
	*/
	virtual void GetNthClassAlias(int32 n, ClassID &fromID, VersionID &fromVersion, ClassID &toID, VersionID &toVersion) const = 0;
	
	/** Return the n'th implementation alias.
	    @param n IN Which alias
		@param fromID OUT The source implementation ID
		@param fromVersion OUT The source version
		@param toID OUT The target implementation ID
		@param toVersion OUT The target version
	*/
	virtual void GetNthImplementationAlias(int32 n, ImplementationID &fromID, VersionID &fromVersion, ImplementationID &toID, VersionID &toVersion) const = 0;

	/** Return the number of plugins that this converter represents.
	    @return The count
	*/
	virtual int32 CountPlugins() const = 0;
	
	/** Return the Nth plugin.
		@param n IN Which plugin
		@return The plugin ID, or kInvalidPlugin if n is invalid
	*/
	virtual PluginID GetNthPlugin(int32 n) const = 0;

	/** Would this conversion renumber a class?
	    @param conversionIndex IN Which conversion (in this conversion provider's list)
		@return kTrue if the conversion would renumber a class
	*/
	virtual bool16 DoesConversionRenumberClass(int32 conversionIndex) const = 0;

	/** Would this conversion renumber an implementation?
	    @param conversionIndex IN Which conversion (in this conversion provider's list)
		@return kTrue if the conversion would renumber an implementation
	*/
	virtual bool16 DoesConversionRenumberImplementation(int32 conversionIndex) const = 0;

	/** This enum is used to tell the Conversion Manager what the conversion provider would
	    do to a specific class or implementation
	*/
	enum ConversionStatus
	{
		/** Conversion is not necessary */
		kNothingToConvert,
		/** Conversion is necessary: content will be modified */
		kMustConvert,
		/** Conversion is necessary: content will be removed */
		kMustRemove,
		/** Conversion is not possible */
		kCantConvert
	};

	/** Returns whether the implementation must be run through the converter to update from one version to another.
	    @param tag IN Which implementation
		@param context IN In which context, kInvalidClass means "in any context"
	    @param conversionIndex IN Which conversion (in this conversion provider's list)
		@return The conversion status
	*/
	virtual ConversionStatus ShouldConvertImplementation(ImplementationID tag, ClassID context, int32 conversionIndex) const = 0;

	/** Returns whether the class must be run through the converter to update from one version to another.
	    @param clsID IN Which class
		@param context IN In which context, kInvalidImpl means "in any context"
	    @param conversionIndex IN Which conversion (in this conversion provider's list)
		@return The conversion status
	*/
	virtual ConversionStatus ShouldConvertClass(ClassID clsID, ImplementationID context, int32 conversionIndex) const = 0;

	/** Any conversion could require multiple calls to the converter: for instance, converting from
	    1->3 could turn into two calls, 1->2 and 2->3. It is important that if there is any embedded
	    data (data that will require a callback into the ConversionMgr to convert) that it be 
	    converted only once for any given conversion. The IterationStatus flag tells the conversion
	    provider what place in the overall conversion process it is being called in.
	*/
	enum IterationStatus
	{
		/** First of multiple */
		kFirstIteration,
		/** Any middle conversion of multiple */
		kMiddleIteration,
		/** Last or only conversion */
		kLastIteration
	};	

	/** Convert the contents of the implementation from the 
	    old format to the new . The incoming contents from 
	    inStream will be whatever was written by the ReadWrite 
	    function in version inVersion. The outgoing contents into 
	    outStream should be whatever will be expected by ReadWrite 
	    for the output version. Returns the new ImplementationID, 
	    which will be the same as the tag parameter, unless the 
	    implementation was renumbered.
	   
	    If ConvertTag doesn't write any data to the output stream, the
	    ImplementationID and associated data are removed from the UID.
		@param tag IN The ID of the implementation to be converted
		@param forClass IN The ID of the class that contains the implementation
		@param conversionIndex IN The index (in this conversion provider's list of possible conversions) to be performed
		@param inLength IN Byte length of the incoming data to be converted
		@param inStream IN Stream that contains the data to be converted
		@param outStream IN Stream that will contain the converted data
		@param whichIteration IN Which conversion is this in a series of conversion steps
		@return The post-conversion ID of the implementation, or kInvalidImpl if the implementation was removed
	*/
	virtual ImplementationID ConvertTag(ImplementationID tag, ClassID forClass, int32 conversionIndex,
			int32 inLength, IPMStream *inStream, IPMStream *outStream, IterationStatus whichIteration) = 0;

	/** Convert the contents of the class from the old format to the new.
	    Returns the new ClassID, which will be the same as the 
	    clsID parameter, unless the class was renumbered.
		
		If kInvalidClass is returned, the UID will be deleted from the database.
		@param clsID IN The ID of the class to be converted
		@param embeddedContext IN The ID of the implementation that contains the class, or kInvalidImpl
		@param conversionIndex IN The index (in this conversion provider's list of possible conversions) to be performed
		@param inLength IN Byte length of the incoming data to be converted
		@param inStream IN Stream that contains the data to be converted
		@param outStream IN Stream that will contain the converted data
		@param whichIteration IN Which conversion is this in a series of conversion steps
		@return The post-conversion ID of the class, or kInvalidClass if the class was removed
	*/
	virtual ClassID ConvertClass(ClassID clsID, ImplementationID embeddedContext, int32 conversionIndex,
			int32 inLength, IPMStream *inStream, IPMStream *outStream, IterationStatus whichIteration) = 0;
};


#endif	// __IConversionProvider__
