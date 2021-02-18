//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __ILayerPrefs__
#define __ILayerPrefs__

#include "IPMUnknown.h"

/** Stores preferences relating to document-wide layers.
	@ingroup layout_layer
	@see kWorkspaceBoss
	@see kDocumentLayerBoss
    @see kSetLayerPrefsCmdBoss.	
*/
class ILayerPrefs : public IPMUnknown
{
public:	
	/**
	   Sets the session-level preference for preserving the layer(s) of page items on paste and duplicate operations.
	   @param bRemembers kTrue to preserve layers on paste, kFalse to put items on active layer.
	 */
	virtual void SetPasteRemembersLayers(const bool16 bRemembers) = 0;

	/**
	   Returns the session-level preference for preserving the layer(s) of page items on paste and duplicate operations.
	   @return kTrue to preserve layers on paste, kFalse to put items on active layer.
	 */
	virtual const bool16 GetPasteRemembersLayers() = 0;

};

#endif
