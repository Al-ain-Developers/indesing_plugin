//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StyleSyncService.h $
//  
//  Owner: Yeming Liu
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
//  Comments: This class is used for book to synchronize styles. 
//  
//========================================================================================

#pragma once
#ifndef __STYLESYNCSERVICE__
#define __STYLESYNCSERVICE__

#include "IStyleSyncService.h"

#include "HelperInterface.h"
#include "ShuksanID.h"	

#ifdef PUBLIC_BUILD
#pragma export on
#endif

//----------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------
class PUBLIC_DECL StyleSyncService : public IStyleSyncService
{
	public:		
		StyleSyncService(IPMUnknown *boss)  
			: HELPER_METHODS_INIT(boss),fUseStyleMatchingStrategy(StyleClashResolutionTypes::kMatchStyleFullPath) { } 

		virtual ~StyleSyncService() { }

		virtual PMIID GetStyleInterfaceID() { return kInvalidInterfaceID; }

		virtual PMString GetGroupName() { return PMString(); }

		virtual PMString GetStyleName() { return PMString(); } 

		virtual bool16 IsCJKStyle() { return kFalse; }

		virtual bool16 IsOptionOnByDefault() { return kTrue; }

		virtual void DoSynchronization(IDFile sourceFile, IDocument* target);

		virtual void	SetStyleMatchingStrategy(StyleClashResolutionTypes::StyleMatchingStrategyEnum styleMatchingStrategy) 
			{ fUseStyleMatchingStrategy = styleMatchingStrategy; }

		virtual StyleClashResolutionTypes::StyleMatchingStrategyEnum		GetStyleMatchingStrategy () const 
			{ return fUseStyleMatchingStrategy;}
	
	private:
		StyleClashResolutionTypes::StyleMatchingStrategyEnum fUseStyleMatchingStrategy;

DECLARE_HELPER_METHODS()
};


#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif // __STYLESYNCSERVICE__