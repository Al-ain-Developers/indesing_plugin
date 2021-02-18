//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITypeContextualControlsPrefs.h $
//  
//  Owner: Reena Agrawal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __ITypeContextualControlsPrefs_h__
#define __ITypeContextualControlsPrefs_h__

#include "IPMUnknown.h"
#include "TextEditorID.h"

/**
	Interface for getting and setting preferences for the contextual
	type controls.
*/

class ITypeContextualControlsPrefs : public IPMUnknown
{
public:
	/** interface ID enum */
	enum { kDefaultIID = IID_ITYPECONTEXTUALCONTROLSPREFS };

	/**
		Set whether the context UI for OpenTypeFeature {Character Alternates, Fractions, Ordinals and Ligatures} should be shown
		@param showUIForOTFeature		Whether to show the context UI for Character Alternates, Fractions, Ordinals and Ligatures.
	*/
	virtual void SetShowUIForOTFeature(bool16 showUIForOTFeature) = 0;

	/**
		Set whether the Adornment on the frame selection should be shown .
		@param showUIForAdornment		Whether to show the context UI for fractions
	*/
	virtual void SetShowUIForAdornment(bool16 showUIForAdornment) = 0;


//	virtual void SetShowUIForHighLight(bool16 showUIForFractions) = 0;

	/*
	Get whether the context UI for OpenTypeFeature{Character Alternates, Fractions, Ordinals and Ligatures} should be shown
	@return Whether to show context UI for OpenTypeFeature{Character Alternates, Fractions, Ordinals and Ligatures}.
	*/
	virtual bool16 GetShowUIForOTFeature() const = 0;

	
	
	/*
	Get whether the adoprnment  should be shown
		@return Whether to show context UI for alternates
		*/
	virtual bool16 GetShowUIForAdornment() const = 0;

//	virtual bool16 GetShowUIForHighLight() const = 0;
};

#endif	// __ITypeContextualControlsPrefs_h__
