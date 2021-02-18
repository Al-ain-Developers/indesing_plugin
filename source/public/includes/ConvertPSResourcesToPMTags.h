//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ConvertPSResourcesToPMTags.h $
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
#ifndef __ConvertPSResourcesToPMTags__
#define __ConvertPSResourcesToPMTags__

class IImageAttributes;
class IStringListControlData;
class PMString;

#pragma export on
bool16 PUBLIC_DECL ConvertPSResourcesToPMTags (const char* imageResources, 
								uint32 imageResourcesSize, 
								IImageAttributes* iImageAttributes);

bool16 PUBLIC_DECL ConvertPSResourcesToPMTags (const char* imageResources, 
								uint32 imageResourcesSize, 
								IImageAttributes* iImageAttributes,
								const PMString* resourceName,		// only convert resources with this name, if nil ignore
								int16 resourceID = 0				// ignore if 0
								);

// Returns the number of paths found.
// namesList can be nil
int16 PUBLIC_DECL GetPSEmbeddedPathNames(const char* imageResources,
								uint32 imageResourcesSize,
								IStringListControlData *namesList,
								PMString& clipName	// Designated clipping path name
								);

// Assigns the value of 'pathName' to the name associated with the embedded
// path refered to by 'zeroBasedPathIndex.'
// Returns kTrue if successful, kFalse otherwise
bool16 PUBLIC_DECL GetPSEmbeddedPathName(const char* imageResources,
								uint32 imageResourcesSize,
								uint16 zeroBasedPathIndex,
								PMString& pathName);
								
// Returns the number of alpha channel names found
// namesList can be nil
int16 PUBLIC_DECL GetPSAlphaNames(const char* imageResources,
								uint32 imageResourcesSize,
								IStringListControlData *namesList);

// Assigns the value of 'alphaName' to the name associated with the extra channel
// refered to by 'zeroBasedAlphaIndex.'
// Returns kTrue if successful, kFalse otherwise
int16 PUBLIC_DECL GetPSAlphaName(const char* imageResources,
								uint32 imageResourcesSize,
								uint16 zeroBasedAlphaIndex,
								PMString& alphaName);

// Returns kTrue if a resource was found within imageResources with the desiredID and desiredType
bool16 PUBLIC_DECL GetPSResource(const char	*imageResources,
					uint32	imageResourcesSize,
					int16	desiredID,
					OSType	desiredType,
					uint32	*pDataSize,
					const char	**pData,
					PMString *resourceName);
					
// Check the resource fork of the given sysfile for embedded photoshop paths
// and alpha channel names and store them in the kPMTagPhotoshop8BIM tag of 
// the provided IImageAttributes.
void PUBLIC_DECL GetPSResources(const IDFile &file, IImageAttributes *imageAttributes);

#pragma export off

#endif
