//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IApplyMotionToPageItemCmdData.h $
//  
//  Owner: SusanCL
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

#include "DynamicDocumentsID.h"

/**
 Data interface for apply motion preset command.
 */
class IApplyMotionToPageItemCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPLYMOTIONTOPAGEITEMCMDDATA };

	/** Sets the motion preset to apply
		@param presetRef is the UIDRef of the motion preset to apply
		@param whichAnimation is the animation to apply to.
	*/
	virtual void SetMotionPresetRef (const UIDRef& presetRef, uint32 whichAnimation = 0) = 0;

	/** Gets the motion preset to apply
		@return the presetRef to apply
	*/
	virtual UIDRef GetMotionPresetRef () const = 0;

	/**	Sets whether or not to force to create new document preset.
		By default, always use the one already exist in the document.
		@param doForceCreate is true if create new doc preset first.
	*/
	virtual void SetForceCreateNewPreset (bool doForceCreate) = 0;

	/**
	@return true if force to create new document preset regardless whether or similarly 
	named preset already exists.
	*/
	virtual bool GetForceCreateNewPreset () const = 0;

	/** Gets which animation to apply preset to.
		@return which animation.
	*/
	virtual uint32 GetWhichAnimation () const = 0;

	/**	Sets whether or not to automatically offset preset motion path.
		@param offsetPath is true if automatically offset motion path.
	*/
	virtual void SetAutoOffsetPath (bool offsetPath) = 0;

	/**
	@return true if offset path.
	*/
	virtual bool GetAutoOffsetPath () const = 0;
};
