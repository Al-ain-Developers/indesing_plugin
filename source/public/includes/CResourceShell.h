//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CResourceShell.h $
//  
//  Owner: Lance Bushore
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
#ifndef __CResourceShell_h__
#define __CResourceShell_h__

#include "RsrcSpec.h"
#include "PMLocaleId.h"

#pragma export on


/** This is a utility class for reading resources. Many of the methods are LocaleIndex resource aware. This means if you ask for some resource, this code will 
	first look to see if there is a matching LocaleIndex resource, and if there is it will look up the localized index of the resource and return that to you, instead of 
	blindly reading the resource you asked for. If you don't want this auto-localization behavior, don't use the methods that end with "LI"
*/
class PUBLIC_DECL CResourceShell
{
public:

	/** Simply reads the desired resource into a handle. Does NOT use the LocaleIndex resource to get an appropriate localized resource.
		@param spec which resource to read. @see RsrcSpec
		@return handle containing the resource data
	*/
	static SysHandle	GetResource(const RsrcSpec& spec);

	/** Counts how many resources there are of the given type in the currently open resource file.
		@param locale which locale we're reading resources for. This code will look for a LocaleIndex resource to determine the real localized resource to read for this locale.
		@param resType which resource kind to read
		@return count of resources of the desired type for the specified locale in the currently open resource file.
	*/
	static int16 		CountResourcesLI(const PMLocaleId& locale,RsrcType resType);

	/** Counts how many resources there are of the given type in the currently open resource file.
		@param spec which resource to read. @see RsrcSpec
		@return count of resources matching the RsrcSpec in the currently open resource file.
	*/
	static int16 		CountResourcesLI(const RsrcSpec& spec);

	/** Reads the requested resource into a handle. Does use the LocaleIndex resource to get an appropriate localized resource.
		@param spec which resource to read. @see RsrcSpec
		@return handle containing the resource data
	*/
	static SysHandle	GetResourceLI(const RsrcSpec& spec);

	/** typedef for the function signature required to do resource enumeration.
	*/
	typedef bool16 (*EnumResource)(IPMStream *s, void *enumData);
	
	/** Enumerate all the resources of a type. Stops iteration if EnumResource returns false. This function does find the appropriate localized resource using LocaleIndex resources if any.
		@param locale which locale to enumerating resources for.
		@param pluginID which plugin to enumerating resources for.
		@param resType which resource type to enumerating.
		@param func which function to call for each resource being enumerated.
		@param enumData private data which will be passed back to the enum function.
		@param resourceAlreadyOpened is the resource already opened or should this code do it?
	*/
	static void EnumerateResourcesLI(const PMLocaleId& locale, const PluginID& pluginID, RsrcType resType, EnumResource func, void *enumData,bool16 resourceAlreadyOpened = kFalse);

	/** Enumerate all the resources of a type. Stops iteration if EnumResource returns false. This function does NOT use LocaleIndex resources.
		@param pluginID which plugin to enumerating resources for.
		@param resType which resource type to enumerating.
		@param func which function to call for each resource being enumerated.
		@param enumData private data which will be passed back to the enum function.
	*/
	static void EnumerateResources(const PluginID& pluginID, RsrcType resType, EnumResource func, void *enumData);

private:
	static SysHandle	GetIndResourceLI(const RsrcSpec& spec);
	static void PrivateEnumerateResourcesLI(const PMLocaleId& locale,const PluginID& pluginID, RsrcType resType, EnumResource func, void *enumData);

};

#pragma export off

#endif // __CResourceShell_h__
