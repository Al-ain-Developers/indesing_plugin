//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/WalkerScopeOptions.h $
//  
//  Owner: Raveendra Madala	
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

#ifndef __WALKERSCOPEOPTIONS_H
#define __WALKERSCOPEOPTIONS_H

/** 
	WalkerScopeOptions provides a way to convey the options for consideration to 
	IWalkerScopeFactoryUtils while creating the ITextWalkerScope
*/

class WalkerScopeOptions
{
public:
	// default ctor
	WalkerScopeOptions() 
	{ 
		fIncludeMasterPages = kTrue; 
		fIncludeLockedLayers = kTrue; 
		fIncludeHiddenLayers = kTrue; 
		fIncludeLockedStories = kTrue; 
		fIncludeFootnotes = kTrue; 
		fSearchBackwards = kFalse;
	}
	// default dtor
	~WalkerScopeOptions() 
	{
	}
	/**
		constructor

		@param includeMasterPages specifies whether to include master pages or not. kTrue to include and kFalse to exclude.
		@param includeLockedLayers specifies whether to include locked layers or not. kTrue to include and kFalse to exclude.
		@param includeHiddenLayers specifies whether to include hidden layers or not. kTrue to include and kFalse to exclude.
		@param includeLockedStories specifies whether to include locked stories or not. kTrue to include and kFalse to exclude.
		@param includeFootnotes specifies whether to include footnotes or not. kTrue to include and kFalse to exclude.
		@param searchBackwards specifies whether to search backwards or not. kTrue for backwards and kFalse for forward search.
	 */
	WalkerScopeOptions(bool16 includeMasterPages,bool16 includeLockedLayers,bool16 includeHiddenLayers,bool16 includeLockedStories,bool16 includeFootnotes, bool16 searchBackwards)
	{ 
		fIncludeMasterPages = includeMasterPages; 
		fIncludeLockedLayers = includeLockedLayers; 
		fIncludeHiddenLayers = includeHiddenLayers; 
		fIncludeLockedStories = includeLockedStories; 
		fIncludeFootnotes = includeFootnotes; 
		fSearchBackwards = searchBackwards;
	}
	/**
		Returns the value of include master pages option

		@return kTrue if "include master pages" is on else kFalse
	 */
	bool16 GetIncludeMasterPages() const
	{ 
		return fIncludeMasterPages; 
	}
	/**
		Sets the value of include master pages option

		@param inIncludeMasterPages specifies the value for "include master pages" option. It can be kTrue/kFalse.
	 */
	void SetIncludeMasterPages(bool16 inIncludeMasterPages) 
	{ 
		fIncludeMasterPages = inIncludeMasterPages; 
	}
	/**
		Returns the value of include locked layers option

		@return kTrue if "include locked layers" is on else kFalse
	 */
	bool16 GetIncludeLockedLayers() const
	{ 
		return fIncludeLockedLayers; 
	}
	/**
		Sets the value of include locked layers option

		@param inIncludeLockedLayers specifies the value for "include locked layers" option. It can be kTrue/kFalse.
	 */
	void SetIncludeLockedLayers(bool16 inIncludeLockedLayers) 
	{ 
		fIncludeLockedLayers = inIncludeLockedLayers; 
	}
	/**
		Returns the value of include hidden layers option

		@return kTrue if "include hidden layers" is on else kFalse
	 */
	bool16 GetIncludeHiddenLayers() const
	{ 
		return fIncludeHiddenLayers; 
	}
	/**
		Sets the value of include hidden layers option

		@param inIncludeHiddenLayers specifies the value for "include hidden layers" option. It can be kTrue/kFalse.
	 */
	void SetIncludeHiddenLayers(bool16 inIncludeHiddenLayers) 
	{ 
		fIncludeHiddenLayers = inIncludeHiddenLayers; 
	}
	/**
		Returns the value of include locked stories option

		@return kTrue if "include locked stories" is on else kFalse
	 */
	bool16 GetIncludeLockedStories() const
	{ 
		return fIncludeLockedStories; 
	}
	/**
		Sets the value of include locked stories option

		@param inIncludeLockedStories specifies the value for "include locked stories" option. It can be kTrue/kFalse.
	 */
	void SetIncludeLockedStories(bool16 inIncludeLockedStories) 
	{ 
		fIncludeLockedStories = inIncludeLockedStories; 
	}
	/**
		Returns the value of include footnotes option

		@return kTrue if "include footnotes" is on else kFalse
	 */
	bool16 GetIncludeFootnotes() const 
	{ 
		return fIncludeFootnotes; 
	}
	/**
		Sets the value of include footnotes option

		@param inIncludeFootnotes specifies the value for "include footnotes" option. It can be kTrue/kFalse.
	 */
	void SetIncludeFootnotes(bool16 inIncludeFootnotes) 
	{ 
		fIncludeFootnotes = inIncludeFootnotes; 
	}
	/**
		Returns the value of search backwards option

		@return kTrue if "search backwards" is on else kFalse
	 */
	bool16 GetSearchBackwards() const 
	{ 
		return fSearchBackwards; 
	}
	/**
		Sets the value of search backwards option

		@param inSearchBackwards specifies the value for "search backwards" option. It can be kTrue/kFalse.
	 */
	void SetSearchBackwards(bool16 inSearchBackwards) 
	{ 
		fSearchBackwards = inSearchBackwards; 
	}
private:
	bool16 fIncludeMasterPages;			// data member for storing include master pages option
	bool16 fIncludeLockedLayers;		// data member for storing include locked layers option
	bool16 fIncludeHiddenLayers;		// data member for storing include hidden layers option
	bool16 fIncludeLockedStories;		// data member for storing include locked stories option
	bool16 fIncludeFootnotes;			// data member for storing include footnotes option
	bool16 fSearchBackwards;			// data member for storing search direction
};

#endif
