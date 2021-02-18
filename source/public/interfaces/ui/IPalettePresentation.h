//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPalettePresentation.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IPALETTEPRESENTATION__
#define __IPALETTEPRESENTATION__

#include "IPMUnknown.h"
#include "AppUIID.h"
#include "PaletteRef.h"

class IDocument;
class IControlView;
class ISelectionManager;

/** This interface, exists on the palette wrapper boss to designate that it represents InDesign palette presentation.
		The palette wrapper boss bridges the gap between InDesign palette panels, and the OWL Palette world.
		@see PaletteRef.h, PaletteRefUtils.h, IPanelMgr.h
		
		One can look up the widget hierarchy for this interface (vs IDocumentPresentation) to determine the type of presentation.
		
		The interface is intended to be sparce, but sufficient to allow further calls to PaletteRefUtils or IPanelMgr.
*/

class IPalettePresentation : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IPALETTEPRESENTATION};

	/** Get the palette panel this palette contains
	*/
	virtual IControlView*	GetPalettePanel() const = 0;

	/** Get the PaletteRef representation for this palette
	*/
	virtual PaletteRef	GetPaletteRef() const = 0;

	/** Bring this palette to the front
	*/
	virtual void	BringToFront() = 0;

	/** Is this palette floating
	*/
	virtual bool16	IsFloating() const = 0; // is it in a floating window (as opposed to being inside the ApplicationContainer)	
};

#endif
