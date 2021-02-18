//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IReplaceAllTextData.h $
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
//  
//  Used to hold the string to insert into a text story with the InsertTextCmd
//  
//========================================================================================

#pragma once
#ifndef __IReplaceAllTextData__
#define __IReplaceAllTextData__

#include "TextWalkerServiceProviderID.h"
#include "WideString.h"
#include "AttributeBossList.h"
#include "K2SmartPtr.h"
#include "IFindChangeOptions.h"

class ITextModel;
class RangeProgressBar;

class IReplaceAllTextData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IREPLACEALLTEXTDATA};

		virtual void Clear() = 0;
		virtual bool16 SetNextReplacement (TextIndex pos, int32 len)	= 0;
		
		//virtual void SetSearchMode(IFindChangeOptions::SearchMode searchMode) = 0;
		//virtual IFindChangeOptions::SearchMode GetSearchMode() = 0;
		
		virtual void UseReplacementString (const boost::shared_ptr<WideString> &string) = 0;
		virtual void UseParaAppliedAttributes (const boost::shared_ptr<AttributeBossList>& pAttrList) = 0;
		virtual void UseCharAppliedAttributes (const boost::shared_ptr<AttributeBossList>& attrList) = 0;
		virtual void UseAppliedParaStyle (UID paraStyle) = 0;
		virtual void UseAppliedCharStyle (UID charStyle) = 0;
		virtual void UseCaseSensitivity(bool16 caseSensitive) = 0;
		virtual void UseGrep(bool16 grep) = 0;
		virtual void UseSearchMode(IFindChangeOptions::SearchMode searchMode) = 0;
		virtual void UseTagName (PMString tagName) = 0;
		virtual void UseOTFAppliedAttributes(const boost::shared_ptr<AttributeBossList>& attrList) = 0;	
		virtual void UseChangeConditionsMode(IFindChangeOptions::ChangeConditionsMode chgConditionsMode) = 0;
		
		virtual void SetTextModel(ITextModel* pModel)  = 0;
	
		virtual int32 GetReplacementCount () const = 0;
		virtual int32 GetNthReplacementLen (int32 replacementIdx)  const = 0;
		virtual TextIndex GetNthReplacementPosition (int32 replacementIdx)  const = 0;
		virtual const boost::shared_ptr<WideString> & GetNthReplacementString (int32 replacementIdx)  const = 0;
		virtual const boost::shared_ptr<AttributeBossList>& GetNthAppliedParaAttributes (int32 replacementIdx)  const = 0;
		virtual const boost::shared_ptr<AttributeBossList>& GetNthAppliedCharAttributes (int32 replacementIdx)  const = 0;
		virtual UID GetNthAppliedParaStyle (int32 replacementIdx)  const = 0;
		virtual UID GetNthAppliedCharStyle (int32 replacementIdx)  const = 0;
		virtual bool16 GetNthReplacementCaseSensitivity(int32 replacementIdx) const = 0;
		virtual bool16 GetNthReplacementGrep(int32 replacementIdx) const = 0;
		virtual PMString GetNthReplacementTagName(int32 replacementIdx) const = 0;
		virtual IFindChangeOptions::SearchMode GetNthReplacementSearchMode(int32 replacementIdx) const = 0;
		virtual const boost::shared_ptr<AttributeBossList>& GetNthAppliedOTFAttributes (int32 replacementIdx)  const = 0;
		virtual IFindChangeOptions::ChangeConditionsMode GetNthReplacementChangeConditionsMode(int32 replacementIdx) const = 0;

		virtual ITextModel* QueryTextModel() const = 0;

		virtual void SetWalkerProgressMonitor( RangeProgressBar* info)  = 0;
		virtual void SetRangeStartPrcnt( int32 prcnt)  = 0;
		virtual void SetRangeEndPrcnt( int32 prcnt)    = 0;

		virtual  RangeProgressBar* GetWalkerProgressMonitor()  = 0;
		virtual int32 GetRangeStartPrcnt()  = 0;
		virtual int32 GetRangeEndPrcnt()    = 0;
};
#endif

