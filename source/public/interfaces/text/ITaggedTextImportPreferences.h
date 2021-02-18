//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITaggedTextImportPreferences.h $
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
#ifndef __ITaggedTextImportPreferences__
#define __ITaggedTextImportPreferences__


#include "IPMUnknown.h"
#include "TaggedTextTypes.h"
#include "TaggedTextFiltersID.h"

/** 
	Interface to get and set the tagged text import preferences.
*/
class ITaggedTextImportPreferences : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ITAGGEDTEXTIMPORTPREFERENCES };

	/**
	   Set warning options which indicates whether warning should be 
	   suppressed or not while importing the tagged text file.

	   @param warningOption IN Warning options
	*/
	virtual void   SetWarningOption(SuppressWarning warningOption) = 0;

	/**
	   Set style conflict options which indicates that which definition 
	   Publication/Tagged Text should be used in case of Style conflict.

	   @param styleOption IN Style conflict options
	*/	
	virtual void   SetStyleConflictOption(StyleConflictAction styleOption) = 0;
	
	/**
	   Set the encoding of the tagged text file.

	   @param impEncodingPref IN Encoding of the tagged text file
	*/
	virtual void   SetImportEncodingPref(EncodingType impEncodingPref) = 0;

	/**
	   Set the flag which indicates whether to use Typographer's quotes or not.

	   @param bUseTypographersQuotes IN Whether to use Typographer's quotes or not
	*/
	virtual void   SetUseTypographersQuotes(bool16 bUseTypographersQuotes) = 0;

	/**
	   Set the flag which indicates whether to remove Character/Paragraph formatting or not.

	   @param bRemoveFormatting IN Whether to remove formatting or not
	*/
	virtual void   SetRemoveFormatting(bool16 bRemoveFormatting) = 0;
	
	/**
	   Get warning options which indicates whether warning should be 
	   suppressed or not while importing the tagged text file

	   @param none
	   @return Warning Option
	*/
	virtual SuppressWarning GetWarningOption() = 0;
	
	/**
	   Get style conflict options which indicates that which definition 
	   Publication/Tagged Text should be used in case of Style conflict.

	   @param none
	   @return Style conflict Option
	*/
	virtual StyleConflictAction  GetStyleConflictOption() = 0;

	/**
	   Get the encoding of the tagged text file.

	   @param none
	   @return Encoding of the tagged text file
	*/
	virtual EncodingType  GetImportEncodingPref() = 0;	
	
	/**
	   Get the flag which indicates whether to use Typographer's quotes or not.

	   @param none
	   @return use typographer's quote flag
	*/
	virtual bool16   GetUseTypographersQuotes() = 0;
	
	/**
	   Get the flag which indicates whether to remove Character/Paragraph formatting or not.

	   @param none
	   @return remove formatting flag
	*/
	virtual bool16   GetRemoveFormatting() = 0;
	
	/**
	   Copy the tagged text import preferences

	   @param copy IN tagged text import preferences
	*/
	virtual void    CopyPrefs(ITaggedTextImportPreferences* copy) = 0;
};

#endif
