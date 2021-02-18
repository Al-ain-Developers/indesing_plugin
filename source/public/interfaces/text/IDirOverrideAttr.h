//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDirOverrideAttr.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __IDirOverrideAttr__
#define __IDirOverrideAttr__

#include "IPMUnknown.h"
#include "WorldReadyID.h"


/**	IDirOverrideAttr is a simple data interface that is used to hold the
	character level override of the writing direction used by the world ready composer.
	@ingroup text_attr
	@see IDrawingStyleME
*/
class IDirOverrideAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDIROVERRIDEATTR };

		enum DirOverride {
						kDirOverrideDefault = 0,
						kDirOverrideLTR,
						kDirOverrideRTL };

		typedef IDirOverrideAttr::DirOverride	ValueType;

		/** Set the writing direction override.
		@param val is the writing direction.
		*/
		virtual void Set(ValueType val) = 0;
		/** Get the writing direction override.
		@return the writing direction.
		*/
		virtual	ValueType Get() const = 0;
};

#endif
		// __IIDirOverrideAttr__
