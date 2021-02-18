//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPluginIDList.h $
//  
//  Owner: jargast
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
#ifndef __IPluginIDList__
#define __IPluginIDList__

#include "IPMUnknown.h"
#include "AppFrameworkID.h"

/**  Data interface for storing a list of plug-in IDs values
*/
class IPluginIDList : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IPLUGINIDLIST };

	/** Copy list into this
		@param list - list to copy from.
	*/
	virtual void Set(const K2Vector<PluginID>& list) = 0;
	
	/** Add every plug-in the supplied list to this
		@param copyThis list to copy from.
	*/
	virtual void Add(IPluginIDList *copyThis) = 0;
	
	/** Add a new plug-in to the list
		@param addThis plug-in to add
	*/
	virtual void Add(PluginID addThis) = 0;
	
	/** Remove a plug-in from the list.
		@param removeThis plug-in to remove.
	*/
	virtual void Remove(PluginID removeThis) = 0;
	
	/** Empty the list.
	*/
	virtual void Clear() = 0;
	
	/** Returns whether the plug-in is in the list.
		@param pluginID plug-in to check
		@return kTrue if the plug-in is in the list, kFalse otherwise.
	*/
	virtual bool16 IsInList(PluginID pluginID) const = 0;
	
	/** Returns the number of plug-ins in the list.
		@return number of plug-ins in the list.
	*/
	virtual int32 Length() const = 0;
	
	/** Fetch a plug-in from the list by index.
		@param i index of the plug-in to fetch
		@return plug-in ID at the i'th position in the list.
	*/
	virtual PluginID GetNth(int32 i) const = 0;
};


#endif // __IPluginIDList__
