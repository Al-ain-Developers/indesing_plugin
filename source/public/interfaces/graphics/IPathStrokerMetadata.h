//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStrokerMetadata.h $
//  
//  Owner: Greg St. Pierre
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPathStrokerMetadata__
#define __IPathStrokerMetadata__

#include "InstStrokeFillID.h"

class IPathStroker;

/**
 Class for storing information about a class of path strokers
 */

class IPathStrokerMetadata : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKERMETADATA };

	/**
	 Retrieves the name of the path stroker 'class'

	 @param OUT name	The name of the class
	 */
	virtual void GetName(PMString &name) const = 0;

	/**
	 Retrieves default base name for new instances of the path stroker class

	 @param OUT name	The default base name for new instances
	 */
	virtual void GetDefaultInstanceName(PMString &name) const = 0;

	/**
	 Retrieves the panel - identified as a plugin/rsrc ID pair - to be used
	 to configure path strokers of this class

	 @param OUT plugin	The plugin that contains the panel to be used
	 @param OUT panelID	The resource ID of the panel
	 */
	virtual void GetConfigurationPanel(PluginID &plugin, RsrcID &panelID) const = 0;

	/**
	 Creates a default instance of this path stroker

	 @param db IN	The database in which to create the stroker
	 @return The new path stroker, or nil if fails
	 */
	virtual IPathStroker *CreateInstance(IDataBase *db) const = 0;

	/**
	 Clones the specified path stroker instance, in the specified database. 
	 The path stroker can be assumed to be associated with this metadata.

	 @param stroker		The stroker to clone
	 @param db			The database in which to clone the stroker
	 @return The new path stroker instance
	 */
	virtual IPathStroker *CloneInstance(IPathStroker const *stroker, IDataBase *db) const = 0;
};

#endif //!def __IPathStrokerMetadata__
