//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunManager.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"


// General includes:
#include "ShuksanID.h"
#include "PMString.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes:
#include "SnpRunnable.h"
#include "SnipRunManager.h"
#include "SnipRunLog.h"
#include "SnipRunID.h"

/*
	Factory methods. Single instance used.
*/
SnipRunManager* SnipRunManager::gSnipRunManager  = nil;

/*
*/
SnipRunManager* SnipRunManager::Instance()
{
	if (gSnipRunManager == nil)
	{
		gSnipRunManager = new SnipRunManager;
//		ASSERT_MSG(gSnipRunManager != nil, "new SnipRunManager failed");
	}

	return gSnipRunManager;
}

/*
*/
void SnipRunManager::DeleteInstance()
{
//	ASSERT_MSG(gSnipRunManager != nil, "no gSnipRunManager available for deletion");
	// make sure snippet look up table is purged.
	fSnippetDict.erase(fSnippetDict.begin(), fSnippetDict.end());

	if (gSnipRunManager != nil)
		delete gSnipRunManager;
	gSnipRunManager = nil;
	// aolenski - tying the life of the log in with the manager.
	// this fixes quite a few bugs
	// Destroy the log.
	SnipRunLog::DeleteInstance();

}

/*
*/
SnipRunManager::SnipRunManager()
{
}

/*
*/
SnipRunManager::~SnipRunManager()
{
}

/*
*/
void SnipRunManager::AddSnippet(SnpRunnable* runnable)
{
	do {
		PMString key(runnable->GetName());
		key.SetTranslatable(kFalse);
		if (key.empty()) {
			ASSERT_FAIL("You need to name your snippet before it can be runnable");
			break;
		}
		SnpRunnable* collisionCheck = this->FindSnippet(key);
		if (collisionCheck) {
			ASSERT_FAIL(FORMAT_ARGS("A snippet with named %s is already registered, either you have a name clash or you are mistakenly creating your own instance of the snippet", collisionCheck->GetName()));
			break;
		}
//		TRACE("AddSnippet %s 0x%x", runnable->GetName(), runnable);
		fSnippetDict.push_back(Snippet(key, runnable));
	} while(false);
}

/*
*/
void SnipRunManager::RemoveSnippet(SnpRunnable* runnable)
{
	PMString key(runnable->GetName());
	key.SetTranslatable(kFalse);
//	TRACE("RemoveSnippet %s 0x%x", runnable->GetName(), runnable);
	int32 index = FindLocation(fSnippetDict, key);	
	if (index >= 0)
	{
		fSnippetDict.erase(fSnippetDict.begin() + index, fSnippetDict.begin() + index + 1);
	}
}

/* 
*/
SnpRunnable* SnipRunManager::FindSnippet(const PMString& snippetName) const
{
	SnpRunnable* result = nil;
	int32 index = FindLocation(fSnippetDict, snippetName);
	if (index >= 0)
	{
		result = fSnippetDict[index].Value();
	}	
	return result;
}

/* 
*/
void SnipRunManager::SortSnippets(void)
{
	std::sort(fSnippetDict.begin(), fSnippetDict.end());
}

// End, SnipRunManager.cpp.


