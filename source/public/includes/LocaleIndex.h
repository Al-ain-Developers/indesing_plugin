//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LocaleIndex.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __LocaleIndex_h__
#define __LocaleIndex_h__

#include "CoreResTypes.h"
#include "PMTypes.fh"

#ifdef __ODFRC__
/**	This is the resource definition for LocaleIndex resources, which allow us to load the proper localized resource
	depending on what Product FeatureSet + Language FeatureSet + UI language we're runing in. @see PMLocaleId.h
*/
type LocaleIndex (kLocaleIndexRsrcType)
{
	/** Resource type, i.e. kStringTableRsrcType
	*/
	longint;					
	
	/** Resource compiler generated count of array entries
	*/	
	longint = $$CountOf(LocaleEntries);
	array LocaleEntries
	{
	/** Feature Set Locale Id - combination of product FS and Language FS. 
		@see PMLocaleId.h for an explanation. @see FeatureSets.h for the set of constants
	*/
		integer;
						
	/** UI language, i.e. k_enUS. @see PMLocaleId.h for an explanation. @see PMLocaleId.h for the set of constants
	*/
		integer;				
		
	/** Resource id - which localized resource to load for the locale described by the previous 2 entries.
	*/
		longint;				
	}
};

#else

#include "PMLocaleId.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class PUBLIC_DECL PMLocaleIdEndianWrapper
{
public:
	typedef base_type data_type;
	
	operator PMLocaleId () const
	{
		return PMLocaleId (fFeatureSetId, fUserInterfaceId);
	}

private:
	ResourceEndianWrapper16<int16> fFeatureSetId;
	ResourceEndianWrapper16<int16> fUserInterfaceId;
};

/**	The class declaration for one entry in a locale index table.
*/
struct LocaleIndexEntry
{
	/** Locale Id - combination of product FS, Language FS, and UI Language. @see PMLocaleId.h
	*/
	PMLocaleIdEndianWrapper				fLocaleId;
	ResourceEndianWrapper32<RsrcID>		fRsrcId;
};

/**	This is the C++ definition for LocaleIndex resources, which allow us to load the proper localized resource
	depending on what Product FeatureSet + Language FeatureSet + UI language we're runing in. @see PMLocaleId.h
	The layout of this class must match the layout of the resource declaration. 
	NO VIRTUAL METHODS!
*/
class PUBLIC_DECL LocaleIndex
{
public:
/**	Get the resource type, i.e. kStringTableRsrcType
	@return the resource type
*/
	RsrcType			GetRsrcType() const					{ return fRsrcType; }
	
/**	Get the number of entries in this table
	@return count of locale/resource entries
*/
	int32				GetLength() const					{ return fLength; }
	
/**	Get locale id for a specific entry in the table
	@param the requested index into the list
	@return the requested locale id
*/
	PMLocaleId			GetLocaleId(int32 index) const		{ return fIndexEntry[index].fLocaleId; }

/**	Get localized resource id for a specific entry in the table
	@param the requested index into the list
	@return the requested resource id
*/
	RsrcID				GetRsrcId(int32 index) const		{ return fIndexEntry[index].fRsrcId; }
	
/**	Check if this locale index object has an entry for a localized resource id for the given locale. Does wildcard matching.
	@param the locale we're interested in
	@return kTrue if there is an entry in the list that matches the passed in locale.
*/
	bool16				HasRsrcForLocale(const PMLocaleId& localeId) const;

/**	Get the localized resource id for the given locale. Does wildcard matching.
	@param the locale we're interested in
	@return the requested resource id
*/
	RsrcID				GetRsrcIdForLocale(const PMLocaleId& localeId) const;
	
private:
	ResourceEndianWrapper32<RsrcType>			fRsrcType;
	ResourceEndianWrapper32<int32>				fLength;
	LocaleIndexEntry							fIndexEntry[1];
};


#pragma export off

#endif // __ODFRC__

#endif // __LocaleIndex_h__
