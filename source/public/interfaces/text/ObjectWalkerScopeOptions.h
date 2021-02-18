//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ObjectWalkerScopeOptions.h $
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

#ifndef __OBJECTWALKERSCOPEOPTIONS_H
#define __OBJECTWALKERSCOPEOPTIONS_H

#include "UIDList.h"
/** 
	ObjectWalkerScopeOptions provides a way to convey the options for consideration to 
	IObjectWalkerFactoryUtils while creating the IObjectWalker
*/

class ObjectWalkerScopeOptions
{
public:
	enum WalkType
	{
		/**
			This enumeration specifies All Splines for Walking
		 */
		kAllFrames,
		/**
			This enumeration specifies Text Frames for Walking
		 */
		kTextFrames,
		/**
			This enumeration specifies Graphic Frames for Walking
		 */
		kGraphicFrames,
		/**
			This enumeration specifies Unassigned Frames for Walking
		 */
		kUnassignedFrames,
	};
	
	enum SearchScopeType
	{
		/**
			This enumeration specifies All Documents to be searched
		 */
		 kAllDocuments,
		/**
			This enumeration specifies Document to be searched
		 */
		 kDocument,
		/**
			This enumeration specifies Selected page items to be searched
		 */
		 kSelection,
	};

	// default ctor
	ObjectWalkerScopeOptions() 
	{ 
		fIncludeMasterPages = kTrue; 
		fIncludeLockedLayers = kTrue; 
		fIncludeHiddenLayers = kTrue; 
		fIncludeLockedStories = kTrue; 
		fIncludeFootnotes = kTrue; 
		fWalkType = kAllFrames;
		fSearchScopeType = kDocument;
	}
	// default dtor
	~ObjectWalkerScopeOptions() 
	{
	}
	/**
		constructor

		@param includeMasterPages specifies whether to include master pages or not. kTrue to include and kFalse to exclude.
		@param includeLockedLayers specifies whether to include locked layers or not. kTrue to include and kFalse to exclude.
		@param includeHiddenLayers specifies whether to include hidden layers or not. kTrue to include and kFalse to exclude.
		@param includeLockedStories specifies whether to include locked stories or not. kTrue to include and kFalse to exclude.
		@param includeFootnotes specifies whether to include footnotes or not. kTrue to include and kFalse to exclude.
		@param walkType specifies which type of objects need to be searched. see @WalkType documentation.
		@param scopeType specifies the search scope. see @SearchScopeType documentation. 
	 */
	ObjectWalkerScopeOptions(bool16 includeMasterPages,bool16 includeLockedLayers,bool16 includeHiddenLayers,bool16 includeLockedStories,bool16 includeFootnotes,WalkType walkType,SearchScopeType scopeType)
	{ 
		fIncludeMasterPages = includeMasterPages; 
		fIncludeLockedLayers = includeLockedLayers; 
		fIncludeHiddenLayers = includeHiddenLayers; 
		fIncludeLockedStories = includeLockedStories; 
		fIncludeFootnotes = includeFootnotes; 
		fWalkType = walkType;
		fSearchScopeType = scopeType;
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
		Returns the value of walk type

		@return kAllFrames if all splines need to be searched
		        kTextFrames if all text frames need to be searched
				kGraphicFrames if all graphic frames need to be searched
				kUnassignedFrames if all unassigned frames need to be searched
	 */
	WalkType GetObjectWalkType() const 
	{ 
		return fWalkType; 
	}
	/**
		Sets the value of walk type for the walker

		@param inWalkType specifies the value for type of objects to be searched. It can be kAllFrames, kTextFrames, kGraphicFrames or kUnassignedFrames.
	 */
	void SetObjectWalkType(WalkType inWalkType) 
	{ 
		fWalkType = inWalkType; 
	}
	/**
		Returns the search scope type
		
		@return kAllDocuments if all documents need to be searched
				kDocument if single document need to be searched
				kSelection if only selected items need to be searched
	 */
	SearchScopeType GetSearchScopeType() const
	{
		return fSearchScopeType;
	}
	/**
		Sets the search scope type for the walker
		
		@param scopeType specifies the value for search scope. It can be kAllDocuments, kDocument or kSelection
	 */
	void SetSearchScopeType(SearchScopeType scopeType)
	{
		fSearchScopeType = scopeType;
	}
	/**
		Returns the UIDRef of the document that needs to be searched when scope type is document
	 */
	UIDRef GetDocumentToBeSearched() const
	{
		return fDocRef;
	}
	/**
		Sets the document that needs to be searched when scope type is document
	 */
	void SetDocumentToBeSearched(UIDRef inDocRef)
	{
		fDocRef = inDocRef;
	}
	/**
		Returns the list of UID's that needs to be searched when scope type is selection
	 */
	UIDList GetPageItemsToBeSearched() const
	{
		return fSelectedItemList;
	}
	/**
		Sets the list of UID's that needs to be searched when scope type is selection
	 */
	void SetPageItemsToBeSearched(UIDList inItemList)
	{
		fSelectedItemList = inItemList;
	}
private:
	bool16 fIncludeMasterPages;			// data member for storing include master pages option
	bool16 fIncludeLockedLayers;		// data member for storing include locked layers option
	bool16 fIncludeHiddenLayers;		// data member for storing include hidden layers option
	bool16 fIncludeLockedStories;		// data member for storing include locked stories option
	bool16 fIncludeFootnotes;			// data member for storing include footnotes option
	WalkType fWalkType;					// data member for storing walk type
	SearchScopeType fSearchScopeType;	// data member for storing search scope type
	UIDRef fDocRef;						// data member for storing the document that needs to be searched when search scope type is kDocument
	UIDList fSelectedItemList;			// data member for storing the items that needs to be searched when search scope type is kSelection
};

#endif
