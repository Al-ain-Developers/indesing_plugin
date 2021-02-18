//========================================================================================
//  
//  File: IWRFontContext.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRFontContext__
#define __IWRFontContext__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRFontContextComponent.h"
#include "IWRFontAccess.h"
#include "IWRFontInfo.h"
#include "IWRFontCache.h"
#include "IWROptycaPool.h"
#include "IWRMultiProcessing.h"
#include "IWRClientSettings.h"
#include "IWRExtensions.h"

/// Abstract interface describing a font context
/** The instances of classes derived from this class (WRFontContext) describe font contexts; a font context is a set of objects related to each other
and dependent of a given state of the font system (list of installed fonts). The IWRFontContext defines the  domain of validity of WRFontDict* objects;
Many API of WRServices are accessible only va a IWRFontContext. 
There’s at least one global instance, accessible thru global functions(WRServicesFontContext() and more specialized shortcuts),
but the client may create more that one class and/or object for special purposes: 
usually the client will define one class for each font low-level library (CT, GDI, PDF) 
and within theses classes one object for each font context (CTFontContext, CCTFontSet, ...).

The instances are merely collections of pointer to other objects:
@li IWRFontAccess* is a callback class to acces the client font system (Cooltype, Freetype, ...)
@li IWRFontInfo* is a set of utilities for accessing to font properties
@li	IWRFontCache* is a cache of fonts' internal data, used to speedup shaping
@li IWROptycaPool* is a recycling pool for IWROptyca shaper objects
@li IWRMultiProcessing* is an set of data structure locking utilities, required only is WRServices is used in a multithreaded way; it's required, but a do nothing class is OK for non-multithreaded apps
@li IWRClientSettings* is a optional callback call for retrieving application wide settings
All those objects derive from WRFontContextComponent, allowing to navigate from one object to another inside the font context
When the corresponding font list is changed, Invalidate() must be called to invalidate all the internal cached data which could not valid anymore
@sa WRFontContext(), Invalidate(), IWRFontAccess, IWRFontInfo, IWRFontCache, IWROptycaPool, IWRMultiProcessing, IWRClientSettings, WRServicesFontContext()
*/

class WRSERVICES_DECL IWRFontContext : public WRClass
{
public:
	static IWRFontContext* Create();		// to create an object without the implementaion declaration
	static void Dispose(IWRFontContext*);

	virtual ~IWRFontContext() {}

	/// Initialize the WRFontContext
	/** This method sets most of the memebers of the WRFontContext. The IWRClientSettings was added recently to the class and cannot be set with Init(), for API stability.
	Use SetClientSettings() instead;
	@param access a pointer to a IWRFontAccess (required)
	@param info a pointer to a IWRFontInfo; client definition allowed, pass NULL to get a default implementation bound to Access/FontDatabase
	@param cache a pointer to a IWRFontCache; client definition NOT allowed at the present time, pass NULL
	@param optycaPool a pointer to a IWROptycaPool; client definition NOT allowed at the present time, pass NULL
	@param multi a pointer to a IWRMultiProcessing; required, but a do nothing class is OK for non-multithreaded apps
	@sa Settings(), Init()
	**/
	virtual void Init(
		IWRFontAccess* access,	
		IWRFontInfo* info,			
		IWRFontCache* cache,		
		IWROptycaPool* optycaPool,	
		IWRMultiProcessing*	multi	
		) = 0;

	
	virtual IWRFontAccess*		Access() = 0; /// returns a pointer to the underlying IWRFontAccess
	virtual IWRFontInfo*		Info() = 0; /// returns a pointer to the underlying IWRFontInfo
	virtual IWRFontCache*		Cache() = 0; /// returns a pointer to the underlying IWRFontCache
	virtual IWROptycaPool*		OptycaPool() = 0; /// returns a pointer to the underlying IWROptycaPool
	virtual IWRMultiProcessing* MultiProcessing() = 0; /// returns a pointer to the underlying IWROptycaPool
	virtual IWRFontContext*		Context() = 0; /// returns this
	virtual IWRClientSettings*	Settings() = 0 ;/// returns a pointer to the underlying IWRClientSettings
	virtual IWRExtensions*		Extensions() = 0 ;/// returns a pointer to the underlying IWRExtensions

	/// Set the client setting objects
	/** This method sets the client settings object. This member is a recent addition and its setting is not done in Init() for API stability 
	@param setting a pointer to a IWRClientSettings
	@sa Settings(), Init()
	**/
	virtual void SetClientSettings(IWRClientSettings* setting) = 0 ;

	/// Invalidate all internal caches dependent on the installed fonts
	/** This method must be called whenever the installed font list is changed, to avoid using outdated cached data.
	The condition can be detected by calling IWRFontAccess::CheckFontList(), as a relay towards the actual client implementation,
	assuming it provided one.
	@param rebuild a bool, if true the FontInfo data is fully rebuild by enumarating the installed fonts with the IWRFontAccess iterators; 
		otherwise the data are rebuilt incrementally with calls the IWRFontAccess::SearchFont (which must be fully functional in that case)
	@sa IWRFontAccess::SearchFont(), IWRFontAccess::CheckFontList()
	**/
	virtual void				Invalidate(bool rebuild) = 0;
};


#endif
