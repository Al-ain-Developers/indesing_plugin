//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkState.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __ILinkState__
#define __ILinkState__

#include "IPMUnknown.h"
#include "LinksID.h"

/**  This class defines the interface for obtaining or setting link state information.
*/
class ILinkState : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKSTATE };
	
    /** Persistence related method; reads from or writes to given stream
        @param iPMStream [IN] the persistent in and out stream.
        @param id [IN] the implementation ID
    */ 
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;
	
    /** Returns the edit status of the internal data associated with the page item.
    	The link information dialog shows this state in the Edited field.  The user is 
		prompted before updating since updating will blow away their changes.
        @return true when the internal data associated with the page item has been edited.
    */ 
	virtual bool16 HasChanged() = 0;
	
    /** This method is deprecated in CS3. The ILinkResource reports whether the data 
    	for the page item is local (cached or embedded). See ILinkResource::GetStoreState.

       Returns the status of if the link is necessary or if the internal data keeps all
    	the information necessary for the page item.  It is always false for text since all
    	the data is stored internal.  When the link is not needed, the user can unlink
    	without storing anything else in the publication.
        @return false when the external data associated with the page item is not needed.
    */ 
	virtual bool16 IsLinkNeeded() = 0; 
	
	/** Set link changed state.
		@param value [IN] set to true if the link has been changed.
	*/
	virtual void SetHasChanged(bool16 value) = 0;
	
	/** Set link needed state.
		@param value [IN] set to false if the internal data keeps all the information for
			the link and the link is not needed.
	*/
	virtual void SetIsLinkNeeded(bool16 value) = 0;
	
	/** Get the size threshold used to determine whether to store the complete image in the
		publication or to subsample.
		@return the file size limit for auto-embedding
	*/
	virtual uint32 GetEmbedSize() = 0;
	
	/** Set link wanted state.
		@param value [IN] set to false if you do not want a link created with the page item.
	*/
	virtual void SetIsLinkWanted(bool16 value) = 0;
	
	/** Return link wanted state.
		@return false if the link should not be created with the page item.
	*/
	virtual bool16 IsLinkWanted() = 0;
	
	/** Set the provider used to import the page item.
		@param id[in]- the ClassID of the provider used to import the page item.
	*/
	virtual void SetProviderClass(ClassID id) = 0;
	
	/** Get and Set the provider used to import the page item.
		@return the ClassID of the provider used to import the page item.
	*/
	virtual ClassID GetProviderClass() = 0;
};

#endif // __ILinkState__
