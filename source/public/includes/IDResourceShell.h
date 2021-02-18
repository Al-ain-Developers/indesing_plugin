//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDResourceShell.h $
//  
//  Owner: Vadim Tkachev
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
#ifndef __IDResourceShell_h__
#define __IDResourceShell_h__

#include "LocaleSetting.h"
#include <boost/function.hpp>
#include "RsrcSpec.h"

class PlugInData;

#pragma export on

/**	Base resource implementation
*/
namespace IDBaseResourceShell {
	
	/**	Informs the caller where the resource directory is for a given plugin
		@param pluginID [IN] id of desired plugin's path
		@param resourcesDir [OUT] will be populated with the correct path upon success
		@param pluginData [IN] [OPTIONAL] should be used when trying to get a path before the PlugInList is populated (very early startup)
		@return true on success, false on failure, caller should check for true or alternatively check for .Exists() on the IDFile
	*/
	PUBLIC_DECL bool GetPathToPluginResourcesDirectory(const PluginID & pluginID, IDFile & resourcesDir, const PlugInData* pluginData = nil);
	
} //namespace IDBaseResourceShell

class IDResourcePrivateWrapper; //forward declaration of private wrapper, this is a private implementation

/**	Struct to hold shared pointer to a resource wrapper so clients don't have to worry about memory management
*/
struct PUBLIC_DECL IDResource
{
	typedef base_type data_type; //simple shallow copies are sufficient
	
	/**	Constructor
		@param resource [IN] resource wrapper to manage
	*/
	IDResource(IDResourcePrivateWrapper* resource);
	
	/** Destructor
	 */
	virtual ~IDResource() {}
	
	/** Returns a pointer to the managed resource buffer
		@return pointer to the resource buffer
	*/
	void*	Get() const;
	
	/** Returns the length of the managed resource buffer
		@return length of the resource buffer
	*/
	size_t	Length() const;
	
	/** Returns true if this resource wrapper is wrapping an actual and valid resource
		@return true if wrapping a valid resource
	*/
	bool16	IsValid() const;
	
private:
	/** Implementation class for the resource wrapper that contains pointer specific semantics, including release.
		boost::shared_ptr is used here to handle the auto destruction of the IDResourcePrivateWrapper so the callers
		of this struct do not have to worry about memory management.
	*/
	boost::shared_ptr<IDResourcePrivateWrapper> fImpl;
};

namespace IDResourceShell
{
	/** This is a private function and should not be needed for new code - general use should be highly discouraged! [mm 06/08/2009]
	 Given a plugin ID and a resource Id, it returns a localized resource Id.
	 @param pluginId [IN] plugin Id for plugin containing resource to be localized
	 @param resourceId [IN] resource Id used to be localize 
	 @return localized resource Id if it exists or kInvalidRsrcID (0) if it doesn't exist
	 */
	 PUBLIC_DECL RsrcID			GetLocalizedResourceID(const PluginID pluginId, const RsrcID resourceId);

	/** Returns an IDResource corresponding to the given resource spec passed in
		@param spec [IN] unlocalized resource spec of the desired resource, spec must have a valid plugin id!
		@return resource if it exists, otherwise an empty resource
	*/
	PUBLIC_DECL IDResource		Get(const RsrcSpec & spec);
	
	/** Returns a localized IDResource corresponding to the given resource spec passed in, if there is no localized resource, will fall back to the original spec
		@param spec [IN] unlocalized resource spec of the desired resource, spec must have a valid plugin id!
		@return localized resource if it exists, otherwise non-localized resource if it exists, otherwise an empty resource
	*/
	PUBLIC_DECL IDResource		GetLocalized(const RsrcSpec & spec);
	
	/** Typedef for the enumeration callback function passed to the enumeration functions below. Function is in the format:
		@param r [IN] an IDResource of the requested resource type (see below)
		@param userDara [IN] the same user data that was passed into the enumeration function (see below)
		@param spec [IN] resource spec of the IDResource, only the resource type is guaranteed to be filled out correctly
		@return false will end the enumeration, true will continue until all resources of the requested type have been exhausted
		bool (IDResource r, void* userData)
	*/
	typedef boost::function<bool (IDResource r, void* userData, RsrcSpec spec)> ResourceEnumerationCallback;
	
	/** Will enumerate all of the resources of the given type
		@param pluginId [IN] plugin id of the plugin containing the desired resources
		@param resType [IN] resource type of the desired resource to be enumerated
		@param enumerate_callback [IN] function pointer described above that will be called for every resource of the given type
											the particular IDResource will be passed into this function as a parameter
		@param userData [IN] [OPTIONAL] user data that will be passed into the callback function for user use inside of the callback
	 */
	PUBLIC_DECL void			EnumerateResourcesByType(const PluginID & pluginId, const RsrcType & resType, ResourceEnumerationCallback enumerate_callback, void* userData = nil);
	
	/** Will enumerate all localized resources of the of the given type, if no localized resources of the given type exist,
		will try and enumerate all non-localized resources of the given type
	 @param pluginId [IN] plugin id of the plugin containing the desired resources
	 @param resType [IN] resource type of the desired resource to be enumerated
	 @param enumerate_callback [IN] function pointer described above that will be called for every resource of the given type
										the particular IDResource will be passed into this function as a parameter
	 @param userData [IN] [OPTIONAL] user data that will be passed into the callback function for user use inside of the callback
	 @param localeId [IN] [OPTIONAL] will be used when looking at localized resources to determine correct resource id, uses the current locale id if none was passed
	 */
	PUBLIC_DECL void			EnumerateLocalizedResourcesByType(const PluginID & pluginId, const RsrcType & resType, ResourceEnumerationCallback enumerate_callback, 
													  void* userData = nil, const PMLocaleId & localeId = LocaleSetting::GetLocale());
	
} //namespace IDResourceShell

#pragma export off

#endif // __IDResourceShell_h__
