//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextScrapData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __ITEXTSCRAPDATA__
#define __ITEXTSCRAPDATA__

#include "IPMUnknown.h"
#include "TextID.h"
#include "ITextModel.h"
#include "K2SmartPtr.h"


//========================================================================================
// CLASS ITextScrapData
//========================================================================================

/** 
	@ingroup text_other
*/
class ITextScrapData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTSCRAPDATA };

		enum { kScrapType = 'PMTX' };
	
		virtual void Initialize(const UID& story, bool16 ignoreAttributes) = 0;

		/** Empty the text scrap. **/
		virtual void Clear() = 0;

		/** Set replaces the current contents of the scrap with the text content in the PasteData. **/
		virtual void Set(IDataBase *sourceDB, const boost::shared_ptr<PasteData>& vasd, bool16 ignoreAttributes) = 0;
		virtual void Set(IDataBase *sourceDB, ITextModel *vasd, bool16 ignoreAttributes) = 0;

		/** Append appends the text content in the PasteData to the end of the story in the scrap. **/
		virtual void Append(IDataBase *db, const boost::shared_ptr<PasteData>& vasd, bool16 ignoreAttributes) = 0;
		
		virtual UIDRef GetStoryRef() const = 0;
		virtual void SetStoryRef(const UIDRef& storyRef) = 0;

		virtual RangeData GetRange() const = 0;
		virtual void SetRange(const RangeData& r) = 0;

		virtual bool16 GetIgnoreAttributes() const = 0;
		virtual uint32 GetLength() const = 0;
		virtual bool16 IsEmpty() const = 0;

		virtual boost::shared_ptr<PasteData> GetDataFor(const UIDRef& intoStory) const = 0;
		virtual bool16 NeedsExternalizing() const = 0;
};

#endif
