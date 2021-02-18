//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlacePIData.h $
//  
//  Owner: eric_kenninga
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
#ifndef __IPlacePIData__
#define __IPlacePIData__

#include "IPMUnknown.h"
#include "GenericID.h"

#include "PMPoint.h"
/** Interface used to specify data for a variety of Import and Place commands.
*/
class IPlacePIData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPLACEPIDATA };

	/** Initialize the interface.

		@param parent IN specify the target of the command
		@param initialPoints IN where should the item be placed
		@param usePlaceGunContents IN true to use content of place gun, fasse to use item list from the command
		@param usePlaceGunRoute IN true to use place gun route, false to simply create graphicframe and append items to it
	*/
	virtual void Set(const UIDRef& parent,
					 const PMPointList* initialPoints,
					 bool16 usePlaceGunContents = kTrue,
					 bool16 usePlaceGunRoute = kTrue) = 0;

	/** Get the target for the command */
	virtual const UIDRef& GetParent() = 0;
	/** Get the pageitem to place. Returns either the contents of place gun or command's item list, depending on "usePlaceGunContents" flag. */
	virtual UID GetNewItem() const = 0;		
	/** Get the point list */
	virtual const PMPointList* GrabPointList() const = 0;
	/** Should we use the place gun content or lok at the item list on the command? */
	virtual bool16 UsePlaceGunContents() const = 0;
	/** Should we use the place gun route or use for simply creating graphicframe and append items to it  */
	virtual bool16 UsePlaceGunRoute() const = 0;
};


#endif

