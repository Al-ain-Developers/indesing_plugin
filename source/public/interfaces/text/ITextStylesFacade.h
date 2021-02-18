//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextStylesFacade.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __ITEXTSTYLESFACADE__
#define __ITEXTSTYLESFACADE__

#include "IPMUnknown.h"
#include "TextID.h"

#include "IStyleRemapData.h"
#include "IStyleGroupHierarchy.h"
#include "keyboarddefs.h"
//-----------------------------------
//	Forward References
//
class AttributeBossList;
class IWorkspace;
class IStyleInfo;

// ===================================================================================
//	class ITextStylesFacade
// ===================================================================================
/** This facade is used for manipulating Text (paragraph and character) styles and groups. 
	Please use the ITextStylesFacade directly via the UtilsBoss, see Utils.h.
    e.g.Utils<Facade::ITextStylesFacade>()->MethodName( ... );
*/
namespace Facade
{
	class ITextStylesFacade : public IPMUnknown
	{

	//-----------------------------------
	//	API
	//
	public:
		// ----- Constants -----
		enum {kDefaultIID = IID_ITEXTSTYLESFACADE };

		/**
			Creates a new paragraph style on the workspace provided with the name and other parameters passed.
			@param attributeBossList	[IN]	The attributes for the new style to be created.
			@param ws					[IN]	Workspace where to create the paragraph style.
			@param newStyleName			[IN]	The name of the new style.
			@param basedOnUID			[IN]	The UID this style is based on.
			@param parent				[IN]	UID of the parent style group where the style is to be created, kInvalidUID to create a root level
			@param newStyleUID			[OUT]	If passed pointer is non nil and the command is successful, it will contain the UID of newly created style.

			@note The default value assumed for parameter not specified here are following.
				nextStyle				: Self style
				useDefaultsAttribute	: kFalse
				isImported				: kFalse
				virtualKey				: 0
				modifier				: 0
				position				: -1, style will be added at the end of the parent specified

		*/
		virtual ErrorCode CreateNewParagraphStyle(	const AttributeBossList* attributeBossList,
													IWorkspace* ws,
													const PMString& newStyleName,
													UID basedOnUID,
													UID parent,
													UID* newStyleUID ) = 0;

		/**
			Creates a new paragraph style on the workspace provided with the name and other parameters passed.
			@param attributeBossList	[IN]	The attributes for the new style to be created.
			@param ws					[IN]	Workspace where to create the paragraph style.
			@param newStyleName			[IN]	The name of the new style.
			@param basedOnUID			[IN]	The UID this style is based on.
			@param nextStyle			[IN]	The UID of next style. if kInvalidUID then self style is assumed to be next style.
			@param useDefaultsAttributes [IN]	Apply defaults attribute to this newly created style.
			@param isImported			[IN]	Pass kTrue if the style is imported from some other document.
			@param virtualKey			[IN]	The virtualKey for KBSC.
			@param modifier				[IN]	The modifier for KBSC.
			@param parent				[IN]	The UID of the parent, kInvalidUID to create at root level.
			@param newStyleUID			[OUT]	If passed pointer is non nil and the command is successful, it will contain the UID of newly created style.
			@param position				[IN]	Position at which the new UID to be created, -1 to create at the end.
		*/
		virtual ErrorCode CreateNewParagraphStyle(	const AttributeBossList* attributeBossList,
													IWorkspace* ws,
													const PMString& newStyleName,
													UID basedOnUID,
													UID nextStyle,
													bool16 useDefaultsAttributes,
													bool16 isImported,
													const VirtualKey virtualKey,
													const int16 modifier,
													UID parent,
													UID* newStyleUID = nil,
													const int32 position = -1 ) = 0;

		/**
			Creates a new character style on the workspace provided with the name and other parameters passed.
			@param attributeBossList	[IN]	The attributes for the new style to be created.
			@param ws					[IN]	Workspace where to create the character style.
			@param newStyleName			[IN]	The name of the new style.
			@param basedOnUID			[IN]	The UID this style is based on.
			@param parent				[IN]	UID of the parent style group where the style is to be created, kInvalidUID to create a root level
			@param newStyleUID			[OUT]	If passed pointer is non nil and the command is successful, it will contain the UID of newly created style.

			@note The default value assumed for parameter not specified here are following.
				useDefaultsAttribute	: kFalse
				isImported				: kFalse
				virtualKey				: 0
				modifier				: 0
				position				: -1, style will be added at the end of the parent specified

		*/
		virtual ErrorCode CreateNewCharacterStyle(	const AttributeBossList* attributeBossList,
													IWorkspace* ws,
													const PMString& newStyleName,
													UID basedOnUID,
													UID parent,
													UID* newStyleUID ) = 0;

		/**
			Creates a new character style on the workspace provided with the name and other parameters passed.
			@param attributeBossList	[IN]	The attributes for the new style to be created.
			@param ws					[IN]	Workspace where to create the character style.
			@param newStyleName			[IN]	The name of the new style.
			@param basedOnUID			[IN]	The UID this style is based on.
			@param useDefaultsAttributes [IN]	Apply defaults attribute to this newly created style.
			@param isImported			[IN]	Pass kTrue if the style is imported from some other document.
			@param virtualKey			[IN]	The virtualKey for KBSC.
			@param modifier				[IN]	The modifier for KBSC.
			@param parent				[IN]	The UID of the parent, kInvalidUID to create at root level.
			@param newStyleUID			[OUT]	If passed pointer is non nil and the command is successful, it will contain the UID of newly created style.
			@param position				[IN]	Position at which the new UID to be created, -1 to create at the end.
		*/
		virtual ErrorCode CreateNewCharacterStyle(	const AttributeBossList* attributeBossList,
													IWorkspace* ws,
													const PMString& newStyleName,
													UID basedOnUID,
													bool16 useDefaultsAttributes,
													bool16 isImported,
													const VirtualKey virtualKey ,
													const int16 modifier ,
													UID parent ,
													UID* newStyleUID = nil,
													const int32 position = -1 ) = 0;

		/** Creates a new paragraph style group.
			@param ws					[IN] Workspace where to create the group.
			@param newStyleGroupName	[IN] New style group name.
			@param parent				[IN] UID of parent to create new group. kInvalidUID for root level
			@param position				[IN] Postion to create new style, pass -1 for last
			@param newStyleGroupUID		[OUT] UID of newly created style group.
		*/
		virtual ErrorCode CreateNewParagraphStyleGroup(IWorkspace* ws,
													const PMString newStyleGroupName,
													UID parent,
													UID* newStyleGroupUID = nil,
													const int32 position = -1
													) = 0;
		/** Creates a new character style group.
			@param ws					[IN] Workspace where to create the group.
			@param newStyleGroupName	[IN] New style group name.
			@param parent				[IN] UID of parent to create new group. kInvalidUID for root level
			@param position				[IN] Postion to create new style, pass -1 for last
			@param newStyleGroupUID		[OUT] UID of newly created style group.
		*/
		virtual ErrorCode CreateNewCharacterStyleGroup(IWorkspace* ws,
													const PMString newStyleGroupName,
													UID parent,
													UID* newStyleGroupUID = nil,
													const int32 position = -1
													) = 0;

		/**
			Renames a text style (Para and Char style) to a new name.
			@param ws		[IN]	The workspace that contains the styles.
			@param style	[IN]	Style UID which is to be renamed.
			@param newName	[IN]	New name of the style.
		*/
		virtual ErrorCode RenameTextStyle(	IWorkspace* ws,
											UID style,
											const PMString& newName) = 0;

		/**
			Renames a text style group (Para and Char style group) to a new name.
			@param ws			[IN]	The workspace that contains the style groups.
			@param styleGroup	[IN]	Style group which is to be renamed.
			@param newName		[IN]	New name of the style group.
		*/
		virtual ErrorCode RenameTextStyleGroup(	IWorkspace* ws,
												UID styleGroup,
												const PMString& newName) = 0;

		/** Deletes a paragraph style.
			@param ws					[IN]	The workspace that contains the paragraph styles.
			@param styleToDelete		[IN]	Style to delete.
			@param styleToReplaceWith	[IN]	Style to be replaced with. if kInvalidUID is
												passed then root style is used for replacement.
			@param preserveFormatting	[IN]	If replacing with root style then formatting should
												be preserved or not.
		*/
		virtual ErrorCode DeleteParagraphStyle(	IWorkspace* ws,
												UID styleToDelete,
												UID styleToReplaceWith = kInvalidUID,
												bool16 preserveFormatting = kTrue) = 0;

		/** Deletes a character style.
			@param ws					[IN] The workspace that contains the character styles.
			@param styleToDelete		[IN] Style to delete.
			@param styleToReplaceWith	[IN] Style to be replaced with. if kInvalidUID is
											 passed then root style is used for replacement.
			@param preserveFormatting	[IN] If replacing with root style then formatting should
											 be preserved or not.
		*/
		virtual ErrorCode DeleteCharacterStyle(	IWorkspace* ws,
												UID styleToDelete,
												UID styleToReplaceWith = kInvalidUID,
												bool16 preserveFormatting = kTrue) = 0;

		/** Deletes a list of paragraph style groups.
			@param ws			[IN] The workspace that contains the paragraph style groups.
			@param styleGroups	[IN] List of paragraph style groups to be deleted.
			@param remaplist	[IN] Remapping for the style inside the groups being deleted.
		*/
		virtual ErrorCode DeleteParagraphStyleGroups(	IWorkspace* ws,
														const K2Vector<UID>& styleGroups,
														const RemappingList& remaplist) = 0;

		/** Deletes a list of character style groups.
			@param ws			[IN] The workspace that contains the character style groups.
			@param styleGroups	[IN] List of character style groups to be deleted.
			@param remaplist	[IN] Remapping for the style inside the groups being deleted.
		*/
		virtual ErrorCode DeleteCharacterStyleGroups(	IWorkspace* ws,
														const K2Vector<UID>& styleGroups,
														const RemappingList& remaplist) = 0;

		/** Moves a list of styles to new parent and position.
			@param ws			[IN] The workspace that contains the styles.
			@param styles		[IN] List of styles to be moved.
			@param newParent	[IN] UID of the new parent.
			@param position		[IN] New position.
			@param remapList	[IN] Remapping in case a style is being overwritten due to move.
			@param conflictFlag [IN] What to do incase of conflict.
		*/
		virtual ErrorCode MoveTextStyles(	IWorkspace* ws,
											const K2Vector<UID>& styles,
											UID newParent,
											const int32 position,
											const RemappingList& remapList,
											const IStyleRemapData::ConflictFlagEnum conflictFlag) = 0;

		/** Moves a list of style groups to new parent and position.
			@param ws			[IN] The workspace that contains the style groups.
			@param styleGroups	[IN] List of style groups to be moved.
			@param newParent	[IN] UID of the new parent.
			@param position		[IN] New position.
			@param remapList	[IN] Remapping in case a style is being overwritten due to move.
			@param conflictFlag [IN] What to do incase of conflict.
		*/
		virtual ErrorCode MoveTextStyleGroups(	IWorkspace* ws,
												const K2Vector<UID>& styleGroups,
												UID newParent,
												const int32 position,
												const RemappingList& remapList,
												const IStyleRemapData::ConflictFlagEnum conflictFlag) = 0;

		/**
			Changes the data of a Text style to reflect what was passed in
			@param newAtributeBossList	[IN]	New attributes.
			@param newStyleInfo			[IN]	The new style info for the style
			@param ws					[IN]	The workspace containing the text styles.
			@param styleToEdit			[IN]	UID of the style to edit.
			@param bNotify				[IN]	If we should notify the ref index notifier. We should notify most of the time.
		*/
		virtual ErrorCode EditTextStyle(const AttributeBossList* newAtributeBossList,
										const IStyleInfo* newStyleInfo,
										const IWorkspace* ws,
										UID styleToEdit,
										const bool16 bNotify = kTrue) = 0;

		/**
			Sorts the paragraph styles.
			@param ws		[IN] The workspace that contains the paragraphs styles.
			@param sortFlag	[IN] How to sort.
			@see IStyleGroupHierarchy::SortFlag for more flags.
		*/
		virtual ErrorCode SortParagraphStyles(	IWorkspace *ws,
												IStyleGroupHierarchy::SortFlag sortFlag = IStyleGroupHierarchy::kSortAscendingHierarchy ) = 0;

		/**
			Sorts the character styles.
			@param ws		[IN] The workspace that contains the character styles.
			@param sortFlag	[IN] How to sort.
			@see IStyleGroupHierarchy::SortFlag for more flags.
		*/
		virtual ErrorCode SortCharacterStyles(	IWorkspace *ws,
												IStyleGroupHierarchy::SortFlag sortFlag = IStyleGroupHierarchy::kSortAscendingHierarchy ) = 0;


		/**
			Changes the default paragraph style
			@param ws					[IN]	The workspace that contains the paragraph styles.
			@param newDefaultStyleUID	[IN]	The new default paragraph style UID.
		*/
		virtual ErrorCode ChangeDefaultParagraphStyle(	IWorkspace* ws,
														UID newDefaultStyleUID) = 0;

		/**
			Changes the default character style
			@param ws					[IN]	The workspace that contains the character styles.
			@param newDefaultStyleUID	[IN]	The new default character style UID.
		*/
		virtual ErrorCode ChangeDefaultCharacterStyle(	IWorkspace* ws,
														UID newDefaultStyleUID) = 0;

		/**
			Duplicates a list of text styles (para and char styles).
			@param ws					[IN]	The workspace that contains the styles.
			@param stylesToDuplicate	[IN]	List of styles to duplicate.
		*/
		virtual ErrorCode DuplicateTextStyles(	IWorkspace* ws,
												const K2Vector<UID>& stylesToDuplicate) = 0;

		/**
			Duplicates a list of text styles groups (para and char style groups).
			@param ws						[IN]	The workspace that contains the style groups.
			@param styleGroupsToDuplicate	[IN]	List of style groups to duplicate.
		*/
		virtual ErrorCode DuplicateTextStyleGroups(	IWorkspace* ws,
													const K2Vector<UID>& styleGroupsToDuplicate) = 0;

	};
}
#endif // define __ITEXTSTYLESFACADE__

