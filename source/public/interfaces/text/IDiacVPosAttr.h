//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDiacVPosAttr.h $
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

#ifndef __IDiacVPosAttr__
#define __IDiacVPosAttr__

#include "IPMUnknown.h"
#include "WorldReadyID.h"


/**	IDiacVPosAttr is a simple data interface that is used to hold the
	desired vertical adjustment position to be used on diacritics
	by the world ready composer.
	@ingroup text_attr
*/
class IDiacVPosAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDIACVPOSATTR };

	    typedef enum {	kDiacVPosOff = 0,
						kDiacVPosLoose,
						kDiacVPosMedium,
						kDiacVPosTight,
						kDiacVPosOpenType,
						kDiacVPosOTFromBaseline} DiacPosition;

		typedef IDiacVPosAttr::DiacPosition		ValueType;

		/** Set the diacritic vertical position preference.
		@param val is the diacritic's vertical position preference.
		*/
		virtual void Set(ValueType val) = 0;
		/** Get the diacritic vertical position preference.
		@return the diacritic's vertical position preference.
		*/
		virtual	ValueType Get() const = 0;
};

#endif
		// __IIDiacVPosAttr__
