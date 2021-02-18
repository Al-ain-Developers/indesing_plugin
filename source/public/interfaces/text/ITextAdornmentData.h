//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAdornmentData.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextAdornmentData__
#define __ITextAdornmentData__

#include "IPMUnknown.h"
#include "TextID.h"

class IDrawingStyle;
class IWaxRun;

/** 
	@ingroup text_adorn
*/
class ITextAdornmentData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTADORNMENTDATA };

	/**
	This method is called at WaxRun regen time to ask the adornment if it
	should be attached to WaxRuns. The adornment should use the data privately
	stored which was gathered from all its attributes that share the adornment
	and optionally the IDrawingStyle itself to make this decision. The
	implementation must NOT modify itself at this time.

	In general this call is only made once for all WaxRuns that share the
	common set of attributes that are associated with the adornment data but
	this is not always true. For example, if another attribute, unrelated to
	the adornment data becomes active, all present adornments will be asked
	if they are active again with potentially different IDrawingStyles.
	@param	draw	a pointer to the IDrawingStyle interface on the
					kComposeStyleBoss for the WaxRun being built.
	@return			kTrue if the adornment should be attached to a WaxRun
	*/
	virtual bool16 IsActive(const IDrawingStyle* draw) const = 0;

	/**
	This method is called when an implementation of the the adornment data is
	attached by reference to a particular WaxRun. Implementations have the
	opportunity to access private non-const interfaces on this WaxRun boss
	to store data that might be of interest from the IDrawingStyle.
	
	In general all WaxRuns that share a common set of attributes related to
	the adornment will share the same adornment data object, each holding an
	active reference, which is why it is important that an implementation
	should never change the contents of the adornment data boss outside an
	IAttrReport::TellComposition() call.
	@param	draw	a pointer to the IDrawingStyle interface on the
					kComposeStyleBoss for the WaxRun being built.
	@param	run		a pointer to the IWaxRun interface on the boss being built.
					Note that at this time the WaxRun has NOT been attached
					to the WaxLine boss so this information is not available to
					implementation. Implementations that need this information
					should simply wait until inkbounds are gather or the
					adornment is drawn.
	*/
	virtual void	Attached(const IDrawingStyle* draw, const IWaxRun* run) const = 0;

};

#endif

