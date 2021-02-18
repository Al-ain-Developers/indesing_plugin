//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IIMEAttrStyle.h $
//  
//  Owner: Michiko Jessett
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
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef __IIMEAttrStyle__
#define __IIMEAttrStyle__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "CJKID.h"


/** CJK IME support
*/
class IIMEAttrStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IIMEATTRSTYLE };

		typedef enum { kNoClauseBreak=0, kClauseBegin, kClauseEnd, kSimpleClause } IMEClauseMode;

		/** Set the IME composition clause mode.
			@param mode		new composition clause mode
		*/
		virtual void SetIMEClauseMode(IMEClauseMode mode) = 0;
		
		/** Get the IME composition clause mode.
			@return			current composition clause mode
		*/
		virtual IMEClauseMode GetIMEClauseMode() const = 0;

		typedef enum { kConfirmed=0, kUnconverted, kConverted, kSelected} IMECompMode;

		/** Set the IME composition mode.
			@param mode		new composition mode 
		*/
		virtual void SetIMECompMode(IMECompMode mode) = 0;

		/** Get the IME composition mode.
			@return			current composition mode
		*/
		virtual IMECompMode GetIMECompMode() const = 0;
};

#endif		// __IIMEAttrStyle__