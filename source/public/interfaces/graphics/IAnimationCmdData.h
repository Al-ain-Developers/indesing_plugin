//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationCmdData.h $
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
#ifndef __IAnimationCmdData__
#define __IAnimationCmdData__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"
#include "IAnimationData.h"


class IAnimationCmdData : public IPMUnknown
{
public:

	/** Bitfield of options for setting animation data.
		Sets the bit for the corresponding data set.
	*/
	enum AnimationDataFlags
	{
		kNoDataSet =			0x00000000,
		
		kPresetSet =			0x00000001,
		kDurationSet =			0x00000002,
		kTransformOffsetSet =	0x00000004,
		kMotionPathSet =		0x00000008,
		kOpacitySet =			0x00000010,
		kRotationSet =			0x00000020,
		kScaleXSet =			0x00000040,
		kScaleYSet =			0x00000080,
		kPlaySet =				0x00000100,
		kSimpleEaseTypeSet =	0x00000200,
		kPlaysLoopSet =			0x00000400,
		kAnimateOptionSet =		0x00000800,
		kHideInitiallySet =		0x00001000,
		kHideAfterSet =			0x00002000,
		
		kAllDataSet =			0xffffffff,

		kMaxAnimationDataSetFlags =	0xffffffff
	};

	enum {kDefaultIID = IID_IANIMATIONCMDDATA};

	/**	Set the command data flags.
		@param cmdFlags is the command data flags indicating the animation data to apply.
	*/
	virtual void SetAnimationDataFlags (const uint32& cmdFlags) = 0;
	
	/**	@return the command data set flags.
	*/
	virtual uint32 GetAnimationDataFlags () const = 0;

	/**	Set to true if to preserve animation settings that are non-preset related when reapplying a preset.
		This includes number of plays, loop, hidden initially setting, and animation options.
		The default is to preserve these data.
		@param preserveData is set to true if preserve data.
	*/
	virtual void SetPreserveNonePresetSettings (bool preserveData) = 0;

	/**	@return whether or not to preserve some animation data when reapplying a preset.
	*/
	virtual bool GetPreserveNonePresetSettings () const = 0;
};

#endif	// __IAnimationCmdData__
