//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITaggedTextExportPreferences.h $
//  
//  Owner: Abhishek Kumar Mishra
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
#ifndef __ITaggedTextExportPreferences__
#define __ITaggedTextExportPreferences__

#include "IPMUnknown.h"

#include "TaggedTextTypes.h"
#include "TaggedTextFiltersUIID.h"

/** 
	Interface to get and set the tagged text export preferences.
*/
class ITaggedTextExportPreferences : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ITAGGEDTEXTEXPORTPREFERENCES };

	/**
	   Sets the encoding in which the tagged text file would be exported
	   @param expEncodingPref IN Encoding to be used
	*/
	virtual void SetExportEncodingPref(EncodingType expEncodingPref) = 0;
	
	/**
	   Sets the export tag form  - Verbose or Abbreviated
	   @param tagType IN Form of the tag
	*/
	virtual void SetExportTagForm(TagNameForm tagType) = 0;
	
	/**
	   Get the encoding in which the tagged text file would be exported
	   @param none
	   @return EncodingType Encoding of the tagged text file
	*/
	virtual EncodingType GetExportEncodingPref() = 0;

	/**
	   Get the export tag form  - Verbose or Abbreviated
	   @param none
	   @return TagNameForm Form of the tag
	*/
	virtual TagNameForm  GetExportTagForm() = 0;
};

#endif
