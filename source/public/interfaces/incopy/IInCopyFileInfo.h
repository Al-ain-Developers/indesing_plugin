//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyFileInfo.h $
//  
//  Owner: craig rainwater
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
#ifndef __IInCopyFileInfo__
#define __IInCopyFileInfo__

//#include "IPMUnknown.h"
#include "IXMLOutStream.h"

#include "InCopyWorkflowID.h"
#include "PMPageSize.h"

/** Represents the information known about the InCopy import file.
	This interface should be present on any story boss.
*/
class IInCopyFileInfo : public IPMUnknown
{
	public:
		//----------------------------------------------------------------------------------------
		//	Enumerations
		//----------------------------------------------------------------------------------------

		enum { kDefaultIID = IID_IINCOPYFILEINFO };

		/** */
		enum eInCopyFileType
		{
			/** */
			kTypeInvalid = 0,
			/** */
			kTypeInCopyStory,
			/** */
			kTypeXML,
			/** InCopy Interchange text story type */
			kTypeInCopyInterchangeTextStory,
			/** InCopy Interchange graphic story type */
			kTypeInCopyInterchangeGraphicStory
		};


		/** Specify the encoding used in this file.
			@param encoding The encoding type enumeration.
		*/
		virtual void Encoding(IXMLOutStream::eEncodingType encoding) = 0;
		/** Return the encoding used in the story's file.
			@return The encoding type enumeration.
		*/
		virtual IXMLOutStream::eEncodingType Encoding() const = 0;

		/** Specify the type of the file.
			@param type The file type enumeration.
		*/
		virtual void FileType(eInCopyFileType type) = 0;
		/** Return the type of the story's file.
			@return The file type enumeration
		*/
		virtual eInCopyFileType FileType() const = 0;

		/** Set the page size of the import file.
			@param rect The rectangle of page, initially {0,0,0,0}
		*/
		virtual void PageRect(const PMPageSize& rect) = 0;
		/** Get the page size.
			@return The page size rectangle.
		*/
		virtual PMPageSize PageRect() const = 0;
		
		/** Specify the version of the InCopy file for importing.
			@param vers The version, 2.0 or 3.0 typically.
		*/
		virtual void FileVersion(const PMReal& vers) = 0;
		/** Return the InCopy file's version number.
			@return The version.  If 0.0, then it was never set.
		*/
		virtual PMReal FileVersion() const = 0;
		
		
};

#endif	// __IInCopyFileInfo__