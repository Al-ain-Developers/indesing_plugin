//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWalkerScopeFactoryUtils.h $
//  
//  Owner: Habib Khalfallah	
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

#ifndef __IWalkerScopeFactoryUtils__
#define __IWalkerScopeFactoryUtils__
#include "TextWalkerServiceProviderID.h"
#include "PMTextUtils.h"
#include "WalkerScopeOptions.h"
class ITextWalkerScope;
class ITextWalker;
class IDocument;
class UIDList;
class ITextModel;
class ITextFocusList;
class ISelectionManager;
class RangeData;
class XMLReference;

/** 
	@ingroup text_util 

	IWalkerScopeFactoryUtils provides an interface for creating the appropriate ITextWalkerScope. 

	@see also WalkerScopeOptions.h
*/
class IWalkerScopeFactoryUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWALKERSCOPEFACTORYUTILS};
	
	enum		WalkScopeType	 
	{ 
		/**
			This enumeration specifies nothing for walking.
		 */
		kEmptyScope, 
		/**
			This enumeration specifies all documents for walking
		 */
		kAllDocumentScope, 
		/**
			This enumeration specifies the active document for walking
		 */
		kDocumentScope, 
		/**
			This enumeration specifies the selected story for walking
		 */
		kStoryScope, 
		/**
			This enumeration specifies the list of specified stories for walking
		 */
		kStoryListScope, 
		/**
			This enumertaion specifies the active selection for walking
		 */
		kSelectionScope, 
		/**
			This enumeration specifies the walking in the active
			story from current position to end of the story
		 */
		kToEndOfStoryScope 
	};

	/**
		Create the appropriate ITextWalkerScope for the given scope type and the current selection

		@param scopeType [IN] lets one specify various scope types
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the given scope type and the current selection
	 */
	virtual ITextWalkerScope *QueryWalkerScope_UsingSelections(WalkScopeType scopeType,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for the current selection

		@param pActiveSelection [IN] selection manager interface for determining the current selection
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the current selection
	 */
	virtual ITextWalkerScope *QueryActiveSelectionWalkerScope (ISelectionManager* pActiveSelection,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for the document specified

		@param doc [IN] UIDRef of the document in which the walker needs to walk
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the document specified
	 */
	virtual ITextWalkerScope *QueryDocumentWalkerScope(const UIDRef& doc,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for the supplied storylist

		@param storyList [IN] the list of UIDs of the stories in which the walker needs to walk
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the supplied storylist
	 */
	virtual ITextWalkerScope *QueryStoryListWalkerScope(const UIDList& storyList,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for the supplied focus list

		@param focusList [IN] a pointer to interface ITextFocusList containing the focus list which need to be walked
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
        @param collectStoryRanges[IN] (default value kFalse), pass kTrue only if we want to get sequential story ranges of table or other type of owned items like footnote within span of focus text.
		@return ITextWalkerScope created for the supplied focus list
	 */
	virtual ITextWalkerScope *QueryFocusListWalkerScope(const ITextFocusList* focusList,WalkerScopeOptions options = WalkerScopeOptions(),bool16 collectStoryRanges=kFalse) const = 0;

	/**
		Create the ITextWalkerScope for the specified story

		@param story [IN] UIDRef of the story that needs to be walked.
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the specified story
	 */
	virtual ITextWalkerScope *QueryStoryWalkerScope(const UIDRef& story,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for range that is supplied

		@param pModel [IN] ITextModel interface pointer to the story in which the range is supplied
		@param start [IN] the starting text index of the range
		@param length [IN] the range span starting from the starting index supplied
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the range that is supplied
	 */
	virtual ITextWalkerScope *QueryRangeWalkerScope(ITextModel *pModel, TextIndex start, int32 length,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for range that is supplied

		@param pModel [IN] ITextModel interface pointer to the story in which the range is supplied
		@param r [IN] Range information contained in RangeData class
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for range that is supplied
	 */
	virtual ITextWalkerScope *QueryRangeWalkerScope(ITextModel *pModel, const RangeData& r,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for all the documents that are open

		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for all the documents that are open
	 */
	virtual ITextWalkerScope *QueryAllOpenDocsWalkerScope(WalkerScopeOptions options = WalkerScopeOptions()) const = 0;


	// The range list argument in the following set of functions is used to get a scope that contains ordered
	// foci that start after the range list (inclusive) till the end, and loop back to the beginning up to start 
	// of range list. 
	/**
		Create the ITextWalkerScope from the current position to end of the story

		@param story [IN] the UIDRef of story that needs to be walked
		@param rangeList [IN] is used to get a scope that contains ordered foci that start after the range list(inclusive) till
		 the end, and loop back to the beginning up to start of range list
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created from the current position to end of the story
	 */
	virtual ITextWalkerScope *QueryToEndOfStoryWalkerScope(const UIDRef& story, const Text::StoryRangeList& rangeList,WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for all the active documents

		@param storyRef [IN] the UIDRef of story that needs to be walked first
		@param rangeList [IN] is used to get a scope that contains ordered foci that start after the range list(inclusive) till
		 the end, and loop back to the beginning up to start of range list
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for all the active documents
	 */
	virtual ITextWalkerScope *QueryAllOpenDocsWalkerScope(const UIDRef& storyRef,
														const Text::StoryRangeList& rangeList,
														WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for the supplied document

		@param doc [IN] UIDRef of document that needs to be walked
		@param storyRef [IN] UIDRef of the story that needs to be walked first
		@param rangeList [IN] is used to get a scope that contains ordered foci that start after the range list(inclusive) till
		 the end, and loop back to the beginning up to start of range list
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the supplied document
	 */
	virtual ITextWalkerScope *QueryDocumentWalkerScope(const UIDRef& doc, 
														const UIDRef& storyRef,
														const Text::StoryRangeList& rangeList,
														WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for all the active documents

		@param story [IN] UIDRef of story that needs to be walked
		@param rangeList [IN] is used to get a scope that contains ordered foci that start after the range list(inclusive) till
		 the end, and loop back to the beginning up to start of range list
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for all the active documents
	 */
	virtual ITextWalkerScope *QueryStoryWalkerScope(const UIDRef& story, 
													const Text::StoryRangeList& rangeList,
													WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Create the ITextWalkerScope for an XML element including linked story elements

		@param xmlElement [IN] the XMLReference of xml element that needs to be walked
		@param options [IN] lets one specify options like "include master pages" etc for the resultant walker
		@return ITextWalkerScope created for the XML element including linked story elements
	 */
	virtual ITextWalkerScope *QueryXMLElementWalkerScope(const XMLReference& xmlElement,
													WalkerScopeOptions options = WalkerScopeOptions()) const = 0;

	/**
		Does the necessary exclusions in the input range list as per the supplied options

		@param story [IN] UIDRef of story that needs to be walked
		@param inRangeList [IN] the input range list in which we need to carry out exclusions
		@param outRangeList [OUT] the output range list
		@param options [IN] the scope options based on which the exclusions will be carried out
	 */
	virtual void CarryoutAnyExclusions(const UIDRef& textStory,
									   const Text::StoryRangeList& inRangeList,
		                               Text::StoryRangeList& outRangeList,
									   const WalkerScopeOptions& options) const = 0;

	/**
		Looks at selections and decides what the scope is.
		@return the Walker scope type of the active selection scope
	 */
	virtual WalkScopeType GetActiveSelectionScope() const = 0;
	
	/**
		Lets one switch the scope type for the walker that is supplied.
		We only allow switches between kStoryScope and kToEndOfStoryScope.
		pScope(pScope is the pointer to ITextWalkerScope corresponding to pWalker) must not be locked.		

		@param pWalker [IN] the pointer to walker for which the scope type needs to be changed.
		@param type [IN] the scope type which needs to be set.
		@return Walker scope type of the walker of this set operation
	 */
	virtual WalkScopeType SetWalkScope(ITextWalker* pWalker, WalkScopeType type) = 0;	

	/**
		Lets one query the walker scope type for the supplied ITextWalkerScope

		@param pScope [IN] the pointer to ITextWalkerScope for which the scope type is being queried.
		@return Walker scope type of the scope supplied
	 */
	virtual WalkScopeType GetWalkScope(ITextWalkerScope* pScope) const  = 0;
};

#endif
