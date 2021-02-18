//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlink.h $
//  
//  Owner: Brendan O'Shea
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
//  IHyperlink is the abstract interface to a hyperlink
//  
//========================================================================================

#pragma once
#ifndef __IHyperlink__
#define __IHyperlink__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

class PMString;

class IHyperlink : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IHYPERLINK };

	/**	Get the name of the hyperlink (Translated)
		@param *pName - Pointer that will be filled with the name
	 */
	virtual void GetName(PMString *pName) const = 0;
	
	/**	Set the name of the hyperlink
		@param newName - Name to use
	 */
	virtual void SetName(const PMString& newName) = 0;

	/**	Get the display name of the hyperlink for UI (Translated)
		@param *pName - Pointer that will be filled with the name
	 */
	virtual void GetDisplayName(PMString *pName) const = 0;

	/**	Set the display name of the hyperlink for UI
		@param newName - Name to use
	 */
	virtual void SetDisplayName(const PMString& newName) = 0;
	
	/**	Get the UID of the source this hyperlink points to
		@param none
		@return const UID& - UID of the source 
	 */
	virtual const UID& GetSourceUID() const = 0;

    /**
      * @deprecated This API is deprecated, don't use it!
	  * USE SAFER GetDestinationUIDRef
      */
	virtual UID GetDestinationUID() const = 0;
	
	/**	Get the unique key of the destination this hyperlink points to
		@return uint32 - unique key of the destination 
	 */
	virtual uint32 GetDestinationUniqueKey() const = 0;

	/**	Set the UID of the source this hyperlink points to
		@param newSourceUID - UID of the source
	 */
	virtual void SetSourceUID(const UID newSourceUID) = 0;

	/**	Set the unique key of the destination this hyperlink points to
		@param newDestKey - unique key of the destination
	 */
	virtual void SetDestinationUniqueKey(uint32 newDestKey) = 0;

	/**	Set whether or not this hyperlink is hidden in the UI
		@param bIsHidden - kTrue == Hide in the UI
	 */
	virtual void SetHidden(bool16 bIsHidden) = 0;	

	/**	Get whether or not this hyperlink is hidden in the UI 
		@param none
		@return bool16 - kTrue = Hidden in the UI
	 */
	virtual bool16 IsHidden() const = 0;	

	/**	Set whether the destination is external to this document or not
		@param bIsDestinationExternal - kTrue means the destination is in another document
	 */
	virtual void SetExternalDestination(bool16 bIsDestinationExternal) = 0;	

	/**	Get whether the destination is external to this document or not
		@param none
		@return bool16 - kTrue means the destination is in another document
	 */
	virtual bool16 IsExternalDestination() const = 0;	

	/**	Get whether the destination file is external to this document or not
		@param none
		@return bool16 - kTrue means the destination file is another document
	 */
	virtual bool16 IsDestInExternalFile() const = 0;	

	/**	Show the Hyperlink Source
		@param none
	 */
	virtual void GoToSource() const = 0;

	/**	Show the hyperlink Destination
		@param none
	 */
	virtual void GoToDestination() const = 0;

	// For getting and setting the destination Icons

	/**	For getting the destination Icons
		@param *iconID - ID of the Icon
		@param *pluginID - ID of the plugin
	 */
	virtual void GetIcon(RsrcID *iconID, PluginID *pluginID) const = 0;

	/**	For setting the destination Icons
		@param iconID - ID of the Icon
		@param pluginID - ID of the plugin
	 */
	virtual void SetIcon(RsrcID iconID, PluginID pluginID) = 0;

	/**	Returns kTrue if this is an destination marker or file is missing
	 */
	virtual bool16 IsUnresolvedLink() const = 0;
	/**	Returns kTrue if the destination is in hidden layer
	 */
	virtual bool16 destInHiddenLayer() const = 0;
	/**	Returns kTrue if x-ref source is out of date
	 */
	virtual bool16 IsOutOfDateLink() const = 0;

	/**	Get the UID of the destination this hyperlink points to
		@return UID - UID of the destination 
	*/
	virtual UIDRef GetDestinationUIDRef() const = 0;
};

#endif
