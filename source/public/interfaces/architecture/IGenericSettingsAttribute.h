//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGenericSettingsAttribute.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  Programmatically accessible list of preferences/settings.
//  
//========================================================================================

#pragma once
#ifndef __IGenericSettingsAttribute__
#define __IGenericSettingsAttribute__

#include "IPMUnknown.h"
#include "IPMUnknownIterator.h"
#include "GenericSettingsID.h"

/** This holds the name, value and other state of a preset preference.
*/
class IGenericSettingsAttribute: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERICSETTINGSATTRIBUTE };
	enum AttributeFlags
	{
		AttrTranslateNone  = 0x00,
		AttrTranslateName  = 0x01,
		AttrTranslateValue = 0x02,
		AttrTranslateBoth  = 0x03
	};

public:
	/** Initialize the name, value and state of this preference.
		@param pszName is the name of the preference.
        @param pszValue is the value of the preference.
        @param nFlags is an optional parameter whether to translate the name or value or both. The default is both.
        @param bLocked is an optional parameter of the preference's locked state.  The default is kFalse.
        @param bRelevant is an optional parameter whether the preference is relevant. The default is kTrue.
	*/
	virtual void Initialize( const PMString pszName,
		                     const PMString strValue,
							 AttributeFlags  nFlags = AttrTranslateBoth,
							 bool16          bLocked = kFalse,
							 bool16          bRelevant = kTrue ) = 0;

	/** Set the relevant flag of this preference.
        @param bRelevant is the preference's is relevant state.
	*/
	virtual void SetRelevant( bool16 bRelevant ) = 0;

	/** Set the locked flag of this preference.
        @param bLocked is the preference's is locked state.
	*/
	virtual void SetLocked(   bool16 bLocked )   = 0;

public:
	/** Get the preference's name.
		@param pszName filled in with the name.
	*/
	virtual void   GetName( PMString& strName )   = 0;

	/** Get the preference's value.
		@param strValue filled in with the value string.
	*/
	virtual void   GetValue( PMString& strValue ) = 0;

	/** Get the preference's locked state.
		@return the locked state.
	*/
	virtual bool16 GetLocked()                    = 0;

	/** Get the preference's relevant state.
		@return the relevant state.
	*/
	virtual bool16 GetRelevant()                  = 0;
};


#endif 
