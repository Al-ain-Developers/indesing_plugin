//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CSequenceItem.h $
//  
//  Owner: Gregor Kaplan
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
#ifndef __CSequenceItem__
	#define __CSequenceItem__
	
#include "ISequenceItem.h"
#include "AATDataTypes.h"
#include <map>
#include <string>
	
class ISequenceList;

#define  kSequenceItemVersion 2



class AATLIB_DECL CSequenceItem : public ISequenceItem
{
	public:
		CSequenceItem(IPMUnknown *boss);
		virtual ~CSequenceItem() {}
		
		//return a : delimited string indicating desired location in default Editor Source Tree
		virtual ProdString	GetDefaultTreeLocation(void) { return fDefaultTreeLoc.Get(); }
		virtual void		SetDefaultTreeLocation(const ProdString &str) { fDefaultTreeLoc.Set(str); }
		
		virtual eReorderFlags	GetReorderFlag(void);
		virtual void			SetReorderFlag(eReorderFlags flag);
		
		virtual eSeqItemType	GetItemType(void) { return (eSeqItemType)fSeqType.Get(); }
		virtual void			SetItemType(eSeqItemType type) { fSeqType = type; }
		
		virtual void		SetParent(ISequenceList *seq);
		virtual ISequenceList* GetParent(void);
		
		virtual ProdString	GetUIString(void);
		
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version);
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil);
		virtual void		GetConvertedTags(K2Vector<ProdString> &tags);
		
		virtual ProdUInt32	GetItemUID(void) { return fItemUID; }
		virtual void		SetItemUID(ProdUInt32 id) { fItemUID = id; }
		
		virtual int32		GetSourceBuildNumber(void) { return fSrcBuildNum.Get(); }
		virtual void		SetSourceBuildNumber(int32 buildNum) { fSrcBuildNum = buildNum; }
		
		virtual PMReal		GetSourceProdVersion(void) { return fSrcProdVers.Get(); }
		virtual void		SetSourceProdVersion(const PMReal &prod) { fSrcProdVers = prod; }
				
		//Note that base impl only converts it's own UID NOT any refs!
		virtual void		ConvertItemUIDRefs(const K2Vector< K2Pair<ProdUInt32, ProdUInt32> >&oldIDs);
		
	protected:
		
		virtual void	CollectReadWriteParams(void);
		
		ISequenceList 	*fParent;
		qaString		fReorderString;
		qaUInt32		fSeqType;
		eReorderFlags	fReorderFlag;
		qaString		fDefaultTreeLoc;
		ProdUInt32		fItemUID;
		qaInt32			fSrcBuildNum;
		qaReal			fSrcProdVers;
};



#endif //__ISequenceItem__







