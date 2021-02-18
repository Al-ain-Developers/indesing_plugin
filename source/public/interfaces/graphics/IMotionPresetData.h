//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionPresetData.h $
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
//  ADOBE CONFIDENTIAL
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

#include "WideString.h"
#include "BravoForwardDecl.h"

class IMotionPresetData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOTIONPRESETDATA };
		
		/** @return true if the data is valid.
		*/
		virtual bool IsValid () const = 0;

		/** @return the raw motion data as a wide string.
		*/
		virtual const WideString& GetRawMotionData() const = 0;

		/** Sets the raw motion preset data as a wide string.
			@param ss the the wide string containing the raw motion data.
		*/
		virtual void SetRawMotionData (const WideString& ss) = 0;

		/**	Set the size and the buffer containing the motion XML for SWF.
			@param data is the buffer containing the motion XML.
			@param count is the size of the buffer.
		*/
		virtual void Set(uint8 const *data, size_t count) = 0;

		/**	Returns the buffer the size of the buffer containing the motion XML.
			@param cout is the size of the buffer.
			@return the pointer to the buffer.
		*/
		virtual uint8 const *Get(size_t &count) const = 0;

		/** @return the buffer containing the motion XML for SWF.
		*/
		virtual BIBSharedBuffer *GetBuffer() const = 0;

		/** Sets the blend mode
			@param blenmode is the blend mode to set.
		*/
		virtual void SetBlendMode (int32 blendmode) = 0;

		/** @return the blending mode.
		*/
		virtual int32 GetBlendMode () const = 0;

		/** Set the description for the preset.
			@param description is the preset description to set.
		*/
		virtual void SetDescription (const PMString& description) = 0;

		/** @return the description for this preset.
		*/
		virtual PMString GetDescription () const = 0;

		/** Sets the name of the preset. This will modify the preset name in the xml data as well.
			@param name is the preset name to set.
		*/
		virtual void SetName (const PMString& name) = 0;

		/**	@return the name of the preset
		*/
		virtual PMString GetName () const = 0;
};

