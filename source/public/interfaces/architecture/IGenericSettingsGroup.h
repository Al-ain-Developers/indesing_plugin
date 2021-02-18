//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGenericSettingsGroup.h $
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
#ifndef __IGenericSettingsGroup__
#define __IGenericSettingsGroup__

#include "IPMUnknown.h"
#include "IPMUnknownIterator.h"
#include "IGenericSettingsAttribute.h"
#include "IGenericSettingsGroup.h"
#include "GenericSettingsID.h"

/** IGenericSettingsGroup is used to describe a group of preset preference values.
*/
class IGenericSettingsGroup: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERICSETTINGSGROUP };

public:
	/** Add a preference value to the group.
		@param pszName is the name of the preference.
        @param pszValue is the value of the preference.
        @param nFlags is an optional parameter whether to translate the name or value or both. The default is both.
        @param bLocked is an optional parameter of the preference's locked state.  The default is kFalse.
        @param bRelevant is an optional parameter whether the preference is relevant. The default is kTrue.
        @return a pointer to an IGenericSettingsAttribute interface.  It is
		is valid as long as this IGenericSettingsGroup interface is valid.
	*/ 
	virtual IGenericSettingsAttribute* AddAttribute( const PMString                           pszName,
							                         const PMString                           pszValue,
													 IGenericSettingsAttribute::AttributeFlags nFlags    = IGenericSettingsAttribute::AttrTranslateBoth,
						                             bool16                                    bLocked   = kFalse,
						                             bool16                                    bRelevant = kTrue ) = 0;

	/** Create a sub group.
		@param pszName is the name of the group.
        @param pszValue is the value of the group.
        @param nFlags is an optional parameter whether to translate the name or value or both. The default is both.
        @param bLocked is an optional parameter of the preference's locked state.  The default is kFalse.
        @param bRelevant is an optional parameter whether the preference is relevant. The default is kTrue.
        @return a pointer to an IGenericSettingsGroup interface.  The caller must release this interface
		when done.
	*/ 
	virtual IGenericSettingsGroup* AddGroup( const PMString                           pszName,
				                             const PMString                           pszValue,
											 IGenericSettingsAttribute::AttributeFlags nFlags    = IGenericSettingsAttribute::AttrTranslateBoth,
						                     bool16                                    bLocked   = kFalse,
						                     bool16                                    bRelevant = kTrue ) = 0;
	
	/** Rename the group.
		@param pszName is the name of the group.
        @param pszValue is the value of the group.
        @param nFlags is an optional parameter whether to translate the name or value or both. The default is both.
        @param bLocked is an optional parameter of the preference's locked state.  The default is kFalse.
        @param bRelevant is an optional parameter whether the preference is relevant. The default is kTrue.
        @return a pointer to an IGenericSettingsAttribute interface.  It is
		is valid as long as this IGenericSettingsGroup interface is valid.
	*/ 
	virtual IGenericSettingsAttribute* SetName( const PMString                           pszName,
				                                const PMString                           pszValue,
												IGenericSettingsAttribute::AttributeFlags nFlags    = IGenericSettingsAttribute::AttrTranslateBoth,
						                        bool16                                    bLocked   = kFalse,
						                        bool16                                    bRelevant = kTrue ) = 0;

public:
	/** Get an iterator to the list of attributes and sub-groups of this group.
        @return a pointer to an IPMUnknownIterator interface. The caller must release this interface
		when done.  The iterator returns IGenericSettingsAttribute interfaces.  These are valid as 
		long as this IGenericSettingsGroup interface is valid.
	*/
	virtual IPMUnknownIterator* GetAttributes() = 0;	

	/** Get the name of this group.
		@return a pointer to an IGenericSettingsAttribute interface. It is
		is valid as long as this IGenericSettingsGroup interface is valid.
	*/
	virtual IGenericSettingsAttribute* GetName() = 0;
};


#endif 
