//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/mresourcefilecache.h $
//  
//  Owner: David Burnard, Michael Burbidge
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
#ifndef __MResourceFileCache_h__
#define __MResourceFileCache_h__

#include "K2Vector.h"
#include "KeyValuePair.h"

//========================================================================================
//	STRUCT RFCacheKey
//========================================================================================

struct RFCacheKey
{
	typedef base_type data_type; // only on mac
	IDFile fSysFile;
	RFCacheKey() {} // required by K2Vector
	RFCacheKey(const IDFile&);
	bool16 operator==(const RFCacheKey&) const;
};

//========================================================================================
//	STRUCT BRMCacheKey
//========================================================================================

struct BRMCacheKey
{
	typedef base_type data_type; // only on mac
	CFBundleRef fBundleRef;
	BRMCacheKey() {} // required by K2Vector
	BRMCacheKey(const CFBundleRef);
	bool16 operator==(const BRMCacheKey&) const;
};

//========================================================================================
//	STRUCT RFCacheValue
//========================================================================================

struct RFCacheValue
{
	typedef base_type data_type;
	ResFileRefNum fRefNum;
	int16 fOpenCount;
	
	bool16 operator==(const RFCacheValue&) const;
};

//========================================================================================
//	Class MResourceFileCache

/** Implementation of a cache for open resource files
		This avoids repeated opening/closing of resource files during drawing/etc.
		Caching happens behind the scenes and is transparent to almost all clients.

		The one exception is that a bug in the Mac OS X Nav services dialogs can clobber
		one of our resource files if we have any unused but cached resource files.
		To avoid this call MResourceFileCache::fResourceFileCache.CloseUnusedFiles() to empty the cache of unused files
		just prior to using a Nav Services dialog, and at the end of any callbacks that might cause a resource file to be opened or closed.
		
		@see ResourceEnabler, MResourceAccess
*/
class PUBLIC_DECL MResourceFileCache
{
public:
	enum { kDefaultRFCacheLength = 8 };
	
	MResourceFileCache();
	~MResourceFileCache();

	/** open a resource file and return the refNum (it may already be open if cached) */	
	int16 OpenResourceFile(const IDFile&);
	/** close a resource file (it may be cached instead) */	
	void CloseResourceFile(const IDFile&);
	
	/** open a bundle resource map and return the refNum (it may already be open if cached) */	
	int16 OpenBundleResourceMap(const CFBundleRef);
	/** close a bundle resource map (it may be cached instead) */	
	void CloseBundleResourceMap(const CFBundleRef);
	
	/** close all cached but unused bundle resource maps and resource files */	
	void CloseUnusedFiles();
	
	/** Flag to disable unloading of cached but unused resource files and bundle maps. (unloading is not disabled by default) */	
	bool16 DisableUnloading(bool16 disable = kTrue);

	/** Provides access to the resource cache. 
	*/	
	static MResourceFileCache fResourceFileCache;
		
private:
	bool16 fUnloadingDisabled;
	K2Vector<KeyValuePair<RFCacheKey, RFCacheValue> >	fCache;
	K2Vector<KeyValuePair<BRMCacheKey, RFCacheValue> >	fBRMCache;
};

#endif // __MResourceFileCache_h__
