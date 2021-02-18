//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ImageDataTypes.h $
//
//  Owner: Ashish Jain
//
//  $Author: pmbuilder $
//
//  $DateTime: 2020/11/06 13:08:29 $
//
//  $Revision: #2 $
//
//  $Change $
//  ___________________
//
//  ADOBE CONFIDENTIAL
//
//  Copyright 2020 Adobe
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe .
//  
//  A Generic class that contains Raw Image Data Structure and its Pointers which can
//  be used anywhere for image processing.
//  
//========================================================================================

#pragma once
#ifndef __ImageDataTypes__
#define __ImageDataTypes__


namespace ImagingTypes
{

	typedef std::shared_ptr<char>   ImageBufferPtr;

    // Data Structures that can be used while handling Image data.
    // This DataStructure can be used to do some processing on the image buffer easily.
	struct ImageData
	{
		size_t          fLength;
		ImageBufferPtr  fBufferPtr;
		ImageData() : fLength(0), fBufferPtr(nil) {}
        
        //Creating ImageData from a std::string
		ImageData(const std::string& bufferString)
		{
			fLength = bufferString.length();
			char* buffer = new char[fLength];
			fBufferPtr.reset(buffer);
			std::copy(bufferString.begin(), bufferString.end(), buffer);
		}
        
        //Creating ImageData from a buffer ptr
		ImageData(ImageBufferPtr bufferPtr, size_t len)
		{
			fLength = len;
			fBufferPtr = bufferPtr;
		}
	};

    // shared_ptr for handling ImageData for a single image
	typedef std::shared_ptr<ImageData>  ImageDataPtr;
    
    // std::vector for handling ImageData for multiple images
	typedef std::vector<ImageDataPtr>   ImageDataPtrList;
    
	typedef std::shared_ptr<ImageDataPtrList>       ImageDataPtrListPtr;
}

#endif
