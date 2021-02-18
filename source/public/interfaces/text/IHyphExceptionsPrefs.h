//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphExceptionsPrefs.h $
//  
//  Owner: hhorton
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
#ifndef _H_IHyphExceptionsPrefs
#define _H_IHyphExceptionsPrefs

#include "IPMUnknown.h"
#include "TextID.h"



/**
	Hyphenation Exceptions Preferences interface.
	@ingroup text_hyphen
*/
class IHyphExceptionsPrefs: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IHYPHEXCEPTIONPREFS };

		enum HyphPrefType
		{
			kUserDictionaryOnly = 0,
			kDocumentOnly,
			kBoth
		};

		/** GetHyphExceptionType.
			@return the preference for the user dictionary.
		*/
		virtual HyphPrefType 	GetHyphExceptionType(void) const = 0;

		/** SetHyphExceptionType. Set the preference for the user dictionary.
			@param hyphPrefType specifies the preference for the user dictionary.
		*/
		virtual void 	SetHyphExceptionType(HyphPrefType hyphPrefType) = 0;

		/** GetStoreInDocument.
			@return whether the user dictionary is stored in the document.
		*/
		virtual bool16 	GetStoreInDocument(void) const = 0;

		/** SetStoreInDocument. Set the preference for the user dictionary.
			@param inDoc specifies the preference for storing the user dictionary in the document.
		*/
		virtual void 	SetStoreInDocument(const bool16 inDoc) = 0;

		/** GetRecompose.
			@return the preference for recomposing when the user dictionary changes.
		*/
		virtual bool16 	GetRecompose(void) const = 0;

		/** SetRecompose. Set the preference for the user dictionary.
			@param recompose specifies the preference for recomposing when the user dictionary changes.
		*/
		virtual void 	SetRecompose(const bool16 recompose) = 0;
};

#endif /* _H_IHyphExceptionsPrefs */
