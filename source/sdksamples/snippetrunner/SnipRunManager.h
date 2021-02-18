//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunManager.h $
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

#ifndef _SnipRunManager_
#define _SnipRunManager_

// Interface includes:

// General includes:
#include "KeyValuePair.h"

// Forward declarations:
class PMString;
class SnpRunnable;

/**
	Manages all registered snippets. Singleton class that is instantiated when the first
	SnipRun object constructs. The SnipRun constructor adds each registered
	snippet to the list of SnipRun objects held by SnipRunManager.

	@ingroup snippetrunner
	
*/
class SnipRunManager
{
protected:
	/**
		Constructor is protected because this is a singleton.
	*/
	SnipRunManager();
	
public:
	/**
		Returns the global instance of this singleton, call like this SnipRunManager::Instance().
		@return the global instance of this singleton class.
	*/
	static SnipRunManager* Instance();

	/**
		Destroys the single global instance of this singleton.
	*/
	void DeleteInstance();

	/**
	*/
	virtual ~SnipRunManager();

	/**
		Snippet dictionary element, key is the name
		of the snippet, value is a pointer to its registered
		SnipRun object.
	*/
	typedef	KeyValuePair<PMString, SnpRunnable*> Snippet;	

	/**
		Dictionary of registered snippets.
	*/
	typedef	K2Vector<Snippet> SnippetDict; 

	/**
		Add snippet to list of registered snippets. If a snippet is
		already registered under this name the request will be ignored.
		@param runnable snippet to be registered.
	*/
	void AddSnippet(SnpRunnable* runnable);

	/**
		Remove snippet from list of registered snippets.
		@param runnable snippet to be removed.
	*/
	void RemoveSnippet(SnpRunnable* runnable);

	/**
		Get the number of registered snippets.
		@return the number of registered snippets.
	*/
	int32 GetNumberOfSnippets() const {return fSnippetDict.size();};

	/** Return a dictionary of registered snippets.
		@return a dictionary of registered snippets.
	*/
	const SnippetDict& GetSnippets() const {return fSnippetDict;};

	/**
		Lookup the named snippet in the list of registered snippets.
		@param snippetName
	*/
	SnpRunnable* FindSnippet(const PMString& snippetName) const;

	/**
		Sort the list of registered snippets.
	*/
	void SortSnippets(void);
	
private:
	static SnipRunManager* gSnipRunManager;
	SnippetDict fSnippetDict;
};

#endif // _SnipRunManager_


