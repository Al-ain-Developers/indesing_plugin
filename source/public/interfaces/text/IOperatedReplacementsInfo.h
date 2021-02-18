//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IOperatedReplacementsInfo.h $
//  
//  Owner: HabibK
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
#ifndef __OperatedReplacementsInfo__
#define __OperatedReplacementsInfo__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"
#include "ITextModel.h"

class WideString;

/** Used to hold the string to insert into a text story with the InsertTextCmd
	@ingroup text_find
*/
class IOperatedReplacementsInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOPERATEDREPLACEMENTSINFO };

		virtual void SetOperatedReplacementsInfo(const boost::shared_ptr<ITextModel::ReplacementList>& replacementList) = 0;
		virtual const boost::shared_ptr<ITextModel::ReplacementList>&  GetOperatedReplacementsInfo() const = 0;
};

#endif

