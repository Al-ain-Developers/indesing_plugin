//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/incopy/IInCopySharedUtils.h $
//  
//  Owner: Cindy Chen
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
#ifndef __IInCopySharedUtils__
#define __IInCopySharedUtils__

#include "InCopySharedID.h"

//-----------------------------------
//	Forward References
//
class ITextModel;
class StatsScope;
class IDataBase;

#include "KeyValuePair.h"

class IInCopySharedUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINCOPYSHAREDUTILS };

		virtual ErrorCode RemoveUnwantedData(ITextModel* textModel,
											TextIndex start, int32 len) = 0;
		// remove unwanted owned item in the specified range with a single
		// story thread.
		// TextModel->Paste() calls this already...

		virtual bool16	MoveOwnedItem(ITextModel* textModel, TextIndex start,  int32 length,
						   TextIndex& newStart, int32& newLength, K2Vector<ClassID>& ownedItemClasses) = 0;
		// Move an owned item of type "ownedItemClass" (i.e. kNoteDataBoss) that are found from start to start+length to
		// the beginning of the surrounding word.  Returns newStart and its changed length due to the move.
	
		virtual PMReal CalculateStoryDepth(ITextModel *textModel, StatsScope &scope) = 0;
		// Called from GalleyInfoUtils and frome DepthRuler.cpp to get the depth of a character or depth of 
		// a range of characters.
		
		virtual void RunUpdateAction(ActionID actionID, bool16 forceUpdate = kFalse) = 0;
		// Update text stats called from GalleyInfoIdleTask.

		virtual PMString StripAllWhiteSpace(const PMString inString) = 0;
		// Returns string stripped of white space.  Called by text macro, username,
		// assignment ui to prevent spaces in macro name or user/assignment name with
		// only spaces.

		virtual ErrorCode SetStoryLabel(const UIDRef& pageItem, const PMString& label) = 0;
		// Sets the pageItem (will look up to the hier to parent graphic frame) story label.

		virtual IDFile GetUniqueFileName(const UIDRef& storyRef, const IDFile& baseFile, PMString* storyName = nil, K2Vector<PMString>* listOfFilenamesUsed = nil) const = 0;
		// Generates a unique file name, returned in storyName.  The name we try to use is BaseName-Text(or Graphic)-<n>.incx 
		// where Text(or Graphic) can be text from the story or graphic datalink.

		/**
			Helper that checks if styles in the specified database can be edited.  Returns kTrue unless
			in InCopy and the document is not stand-alone or doc is stand-alone but story is locked (or no stories).
			@param db the database to check
			@return bool16 whether or not styles can be edited for the specified database
		*/
		virtual bool16 StylesEditable( IDataBase *db ) = 0;
		
		/**
			Helper that checks if the specified username is valid.  That is, the name is not empty nor the default "Unknown User Name".
			@param nameToCheck the username to validate
			@return bool16 whether the username is valid
		*/
		virtual bool16 IsValidUsername(const PMString nameToCheck) = 0;

		/**
			Helper that calls a wrapper command to schedule DocumentUtils::DoSave.
			@param doc the document to save
		*/
		virtual void ScheduleDoSave(const UIDRef& docRef) = 0;

		/** Sets options for InCopy Interchange Export.
			@param item target to be changed - kWorkspaceBoss, kTextStoryBoss, kSplineItemBoss (or the descendant object on IHierarchy)
			@param changeIncludeProxies kTrue to set IncludeGraphicProxyData option, kFalse otherwise
			@param includeProxies whether graphic proxy data is included
			@param changeIncludeAllResources kTrue to set IncludeAllResources option, kFalse otherwise
			@param includeAllResources whether all resources  of interest to InCopy (such as fonts, styles and swatches) should be forced to export
		*/
		virtual ErrorCode SetInCopyInterchangeExportOptions(const UIDRef& item, 
			bool16 changeIncludeProxies,
			bool16 includeProxies, 
			bool16 changeIncludeAllResources,
			bool16 includeAllResources) = 0;

		/**
		 Performs a form C string normalization (canonical composition) on the given string's path.
		 @param s [IN] PMString whose path to compose..
		 @return True if the string's path needed normalization; else false.
		 */
		virtual bool ComposePath(PMString& s) = 0;

		/**	This function export (update) existing InCopy stories. It tries to use available cores to export different story 
			in parallel but keeps synchronous behavior.
			@param db [IN] database which conatins stories
			@param storyList [IN, OUT] UID list of stories to be updated, error code sends back export status
			@param nThread number of thread to be used in export. If 0, number of thread is determined by computer
		*/
		virtual void UpdateInCopyStoriesMTSync(IDataBase * db, K2Vector<KeyValuePair<UID, ErrorCode> > & storyList, size_t nThread = 0) = 0;

};

#endif // __IInCopySharedUtils__
