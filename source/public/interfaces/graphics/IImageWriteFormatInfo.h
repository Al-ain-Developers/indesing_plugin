//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageWriteFormatInfo.h $
//  
//  Owner: jargast
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
#ifndef __IImageWriteFormatInfo__
#define __IImageWriteFormatInfo__

#include "IPMUnknown.h"
#include "IDocument.h"

const uint32 kMaxNumberOfBitDepths = 8;
/** ImageColorSpaceSupportInfo */
typedef struct {
	uint8	supportPlanar;									// kPMChunky and/or kPMPlanar
	uint8	supportNumberOfIndexedBitDepths;				// Could be zero
	uint8	supportIndexedBitDepths[kMaxNumberOfBitDepths];	// The index bitdepths
	uint8	supportNumberOfBitDepths;
	uint8	supportBitDepths[kMaxNumberOfBitDepths];		// pixel bitdepths
	uint8	supportMaxIndexedChannels;						// Some formats might not support extra channels for indexed images
	uint8	supportMaxChannels;								// default is 3 for rgb, 4 for cmyk, etc.
	uint8	supportMaxLayers;								// default is 1.
} ImageColorSpaceSupportInfo;

	
	
class PMString;
class IImageAttributes;

/**
 Interface that provides additional data about the capabilities of an
 IImageWriteFormat implementation.
 
 @see IImageWriteFormat
 */ 
class IImageWriteFormatInfo : public IPMUnknown
{
public:
	/**
	 Returns the file type that should be used when creating a new file to 
	 contain the image data.
	 
	 @return The file type for the new file
	 */
	virtual OSType GetFileType() = 0;

	/**
	 Returns the creator that should be used when creating a new file to 
	 contain the image data.
	 
	 @return The file creator type for the new file
	 */
	virtual OSType GetCreator() = 0;
	
	/**
	 Returns the extension that should be used when creating a new file to 
	 contain the image data.
	 
	 @param extension	OUT Pointer to the PMString to fill with the file extension for the new file
	 */
	virtual void GetExtension(PMString* extension) = 0;

	/**
	 Returns the format name for this filter.
	 
	 @param formatName	OUT Pointer to the PMString to fill with the format name
	 */
	virtual void GetFormatName(PMString* formatName) = 0;
	
	/**
	 Returns kTrue if the requested colorspace is supported, else kFalse. If 
	 kTrue is returned, then the supportInfo structure contains valid information
	 regarding the requested colorspace.
	 
	 @param colorSpace	IN The colorspace for which support information is requested
	 @param supportInfo	OUT On successful calls, filled with information about the nature of support
	 @return kTrue if the colorspace is supported by the filter, else kFalse
	 */
	virtual bool16 GetImageColorSpaceSupportInfo (uint32 colorSpace, ImageColorSpaceSupportInfo* supportInfo) = 0;
	 
	/**
	 Returns the maximum image width supported by the filter
	 
	 @return The maximum supported width
	 */
	virtual uint32 GetMaxWidth() = 0;
	
	/**
	 Returns the maximum image height supported by the filter
	 
	 @return The maximum supported height
	 */
	virtual uint32 GetMaxHeight() = 0;
	
	/**
	 Returns kTrue if the filter can write every attribute in the image, else 
	 kFalse. 
	 
	 Note: If a filter returns kFalse but the caller still uses it to create 
	 an image, then those tags that are not supported will be dropped by the 
	 filter.
	 
	 @param iImageAttributes		IN The attributes to use for the write
	 @return kTrue if every attribute in the image can be written, else kFalse
	 */
	virtual bool16 CanWriteAll(IImageAttributes* iImageAttributes) = 0;
	
	/**
	 Returns the WidgetID of the panel to add to the Export Preferences dialog,
	 if any. 
	 
	 The filter is responsible for setting the panel's parent to 'ImageExportUI'
	 via the IDListPair resource definition of the panel and the 'Visible' field
	 of the panel's resource definition to kFalse. 
	 
	 At export time, the export provider will ask the filter for its WidgetID.
	 If the WidgetID is valid, the provider will use the WidgetID to query for 
	 the panel's IID_IUIDDATA and use it to set the source UID to be used to 
	 initialize the panel. Afterwards, the provider will show the panel, 
	 allowing the IntializeFields() method of the IDialogController for the 
	 panel to be called.
	 
	 @return The WidgetID of the filter's preferences panel, or kInvalidWidgetID if it doesn't have one
	 */
	virtual WidgetID GetPreferencesPanel() = 0;
		
};

#endif
