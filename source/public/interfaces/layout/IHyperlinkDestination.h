//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkDestination.h $
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
//========================================================================================

#pragma once
#ifndef __IHyperlinkDestination__
#define __IHyperlinkDestination__

// Includes:
#include "HyperlinkID.h"

// Classes:
class ISpread;
class IDocument;
class IHierarchy;
class IPMStream;

/**
	@ingroup layout_hyper
*/
class IHyperlinkDestination : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKDESTINATION };

	enum DestType
	{
		kTextAnchorDestination = 0,
		kPageDestination,
		kURLDestination,
		kExternalPageDestination,
	};

	/**	Show the destination in the Layout Window
		@param none
	 */
	virtual void	GoToHyperlinkDestination() const = 0;


	/**	Set whether this destination should be visible in the UI (panel)
		@param bIsHidden - kTrue == Hidden
	 */
	virtual void SetHidden(bool16 bIsHidden) = 0;	

	/**	Get whether this destination should be visible in the UI (panel)
		@param none
		@return bool16 - kTrue == Hidden
	 */
	virtual bool16 IsHidden() const = 0;	


	/**	Get the destination name
		@param destName - Will be filled with the name
	 */
	virtual void	GetName(PMString *destName) const = 0;

	/**	Set the destination name
		@param destName - The new name of the destination
	 */
	virtual void	SetName(const PMString &destName) = 0;

	/**	Get the destination key
		@return uint32 - destination unique key value
	 */
	virtual uint32	GetKey() const = 0;

	/**	Set the destination unique key
		@param destKey - The new key of the destination
	 */
	virtual void	SetKey(uint32 destKey) = 0;
	
	// The following methods are included for extensibility
	// They are intended as ways for current dialogs to be able
	// to give users basic information about destination types that
	// may be added in the future.

	/**	Get an icon to give a pictoral representation of this destination to the user
		@param *iconID - Will be filled with the ID of the icon to use
		@param *pluginID - Will be filled with the ID of the panel to use
	 */
	virtual void	GetIcon(RsrcID *iconID, PluginID *pluginID) = 0;

	// Get this destination's type as a string ("Page", "Text Anchor", "URL")

	/**	Get this destination's type as a string
		@param destType - ("Page", "Text Anchor", "URL")
	 */
	virtual void	GetType(PMString *destType) const = 0;

	// Get this destination's type as a DestType enum

	/**	Get this destination's type as an enum
		@return DestType - type of the destination
	 */
	virtual DestType GetType() const = 0;

	// Get information about this destination (Page it is on, URL it points to, etc)

	/**	Get information about this destination (Page it is on, URL it points to, etc)
		@param destInfo - Will be filled with the information 
	 */
	virtual void	GetInfo(PMString *destInfo) const = 0;
};

#endif // __IHyperlinkDestination__
