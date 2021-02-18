//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectStylesFacade.h $
//  
//  Owner: Danielle Darling
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
#ifndef __IOBJECTSTYLESFACADE__
#define __IOBJECTSTYLESFACADE__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMString.h"
#include "AttributeBossList.h"
#include "IObjectAttributeList.h"	// for ObjectStyleTarget
#include "IStyleNameTable.h"
#include "IObjectStyleInfo.h"
#include "StyleClashResolutionTypes.h"
#include "IStyleRemapData.h"
#include "keyboarddefs.h"

#include <map>

//-----------------------------------
//	Forward References
//

// ===================================================================================
//	class IObjectStylesUtils 
// ===================================================================================
namespace Facade
{
	class IObjectStylesFacade : public IPMUnknown 
	{

	//-----------------------------------
	//	API
	//
	public:
		// ----- Constants -----
		enum {kDefaultIID = IID_IOBJECTSTYLESFACADE};

			/**
			CreateNewObjectStyle: Creates a new object style on the workspace provided with the name and based on UID passed in
			@param objectStyleTarget	The target containing the attributes of the object style
			@param ws	The workspace the object style name table is on to add the new style to
			@param newStyleName	The name of the new style
			@param basedOnUID the UID this style is based on
			@param bStyleNameTranslatable the bool flag indicates if the style name is translatable or not
			@param virtualKey the virtualKey for KBSC
			@param modifier the modifier for KBSC
			@param parentUID the UID of the parent, kInvalidUID to create at root level
			@param position	position at which the new UID to be created, -1 to create at the end.
		*/
		virtual ErrorCode CreateNewObjectStyle(IPMUnknown* objectStyleTarget, IWorkspace* ws, const PMString& newStyleName, 
											  const UID basedOnUID, const bool16& bStyleNameTranslatable = kFalse, 
											  const VirtualKey virtualKey = kVirtualNullKey, const int16 modifier = 0, 
											  const UID parentUID = kInvalidUID, const int32 position = -1) = 0;


		/**
			ApplyObjectStyleToUIDList: Applys the object style to the specified UIDList
			@param list	The list of UIDs to apply this style to
			@param ws	The workspace the object style name table containing the style
			@param overrideCategories	K2Vector<ClassID> of categories to clear (clear all overrides means all of the active categories in the style)
			@param applyEmptyCatWithRoot	true if we are applying empty (unchecked) cateogories from the root style
		*/
		virtual ErrorCode ApplyObjectStyleToUIDList(const UIDList& list, IWorkspace* ws, UID uidOfStyle, K2Vector<ClassID>& categoriesToOverride, bool16 applyEmptyCatWithRoot) = 0;
		/**
			EditObjectStyle: Changes the data of the object style to reflect what was passed in
			@param objectStyleTarget	The target containing the new attributes of the object style
			@param iObjectStyleInfo	The new name and based on UID for the style
			@param ws	The workspace the object style name table containing the style
			@param originalStyleName the style's original name
			@param numApplies IN:		used only by the dialog, set to the number of times we have applied this command
			@param bNotify IN: used to command indicating if we should do notification or not.
		*/
		virtual ErrorCode EditObjectStyle(IPMUnknown *objectStyleTarget, IObjectStyleInfo* iObjectStyleInfo, const IWorkspace* ws, 
										  const PMString& originalStyleName, int32 numApplies = 0, const bool16 bNotify = kTrue) = 0;
		/**
			ReplaceObjectStyles: Replaces the object styles in the stylesToBeReplaced list with the new style sourceStyleName
			@param ws	The workspace the object style name table containing the style
			@param stylesToBeReplaced	The list of styles to be replaces
			@param sourceStyleName	The name of the style to replace them with
		*/
		virtual ErrorCode ReplaceObjectStyles(IWorkspace* ws, const K2Vector<PMString>& stylesToBeReplaced, const PMString& sourceStyleName) = 0;

		/**
			BreakLinkFromProvidedObjectStyles: perserve item's original formatting and set none style as its object style.
			@param ws	The workspace the object style name table containing the style
			@param styleNames	The list of styles to be disassociated from
		*/
		virtual ErrorCode BreakLinkFromProvidedObjectStyles(IWorkspace* ws, const K2Vector<PMString>& styleNames) = 0;

		// Modified the style list, don't affect the selection.
		/**
			DeleteObjectStyles: Deletes the styles in the list
			@param ws					The workspace the object style name table containing the style
			@param styleNames			The list of styles to be deleted
			@param styleToReplaceWith	The style used to replace with the deleted styles.
			@param bPerserveFormat      The flag for perserve format setting.
		*/
		virtual ErrorCode DeleteObjectStyles(IWorkspace* ws, const K2Vector<PMString>& styleNames, const PMString& styleToReplaceWith, const bool16& bPerserveFormat = kFalse) = 0;
		/**
			LoadObjectStyles: Loads the styles from the sourceFile
			@param ws	The workspace the object style name table containing the style
			@param overrideLocal	True if the local styles with the same name are just overwritten
			@param sourceFile		The file to load from
			@param importMap 		Import styles.
			@param clashMap 		Styles that are conflict with existing styles.
			@param resolveMap		Result styles after resolving the conflicts.
			@param globalClashResolutionStrategy IN: global clash resolution strategy.
		*/
		virtual ErrorCode LoadObjectStyles(IWorkspace *ws, const bool16& overrideLocal, const IDFile& sourceFile,
										   std::map<PMString,bool32> importMap,
										   std::map<PMString,bool32> clashMap,
										   std::map<PMString,StyleClashResolutionTypes::StyleClashResolutionStrategy> resolveMap,
										   const StyleClashResolutionTypes::GlobalClashResolutionStrategy& globalClashResolutionStrategy) = 0;

		/**
			ExportObjectStyles: Export the styles from the targetFile
			@param ws	The workspace the object style name table containing the style
			@param targetFile	The file to load from
			@param objectStyles	The styles to be exported.
		*/
		virtual ErrorCode ExportObjectStyles(IWorkspace *ws, const IDFile& targetFile, const K2Vector<PMString>& objectStyles) = 0;

		/**
			ImportObjectStyles: Import the styles from the sourceFile
			@param ws	The workspace the object style name table containing the style
			@param sourceFile	The file to load from
		*/
		virtual ErrorCode ImportObjectStyles(IWorkspace *ws, const IDFile& sourceFile) = 0;

		/**
			DeleteObjectStyles:Sorts the styles
			@param ws	The workspace the object style name table containing the styles to sort
		*/
		virtual ErrorCode SortObjectStyles(IWorkspace *ws) = 0;
		
		/**
			MoveObjectStyles: Moves the styles in the list to a new location before dropBefore
			@param ws	The workspace the object style name table containing the style
			@param selectedObjectStylesName	The list of styles paths to be moved
			@param dropBefore 	The style to move before.
			@param newParent	UID of the new parent.
			@param RemappingList remapping list in case of overwrite.
			@param ConflictFlagEnum what to do incase of conflict.
		*/
		virtual ErrorCode MoveObjectStyles(	IWorkspace* ws, 
											const K2Vector<PMString>& selectedObjectStylesPaths, 
											const int32& dropBefore, 
											const UID newParent,			
											const RemappingList& remaplist,
											const IStyleRemapData::ConflictFlagEnum conflictFlag) = 0;

		/**
			MoveObjectStyles: Moves the styles in the list to a new location before dropBefore
			@param ws	The workspace the object style name table containing the style
			@param selectedObjectStyles	The list of styles UIDs to be moved
			@param dropBefore 	The style to move before.
			@param newParent	UID of the new parent.
			@param RemappingList remapping list in case of overwrite.
			@param ConflictFlagEnum what to do incase of conflict.
		*/
		virtual ErrorCode MoveObjectStyles(	const UIDList& selectedObjectStyles, 
											const int32& dropBefore, 
											const UID newParent,			
											const RemappingList& remaplist,
											const IStyleRemapData::ConflictFlagEnum conflictFlag) = 0;
		/**
			ChangeDefaultTextStyle: Changes the default text style
			@param ws	The workspace the object style name table containing the styles to sort
			@param newDefaultStyleUID	The new text style UID
			@param applyAttrs   True if we should apply the attrs from the style, this is not true when creating the style
			@param clearOverrides True if we want to clear overrides, otherwise kFalse.
		*/
		virtual ErrorCode ChangeDefaultTextStyle(IWorkspace* ws, UID newDefaultStyleUID, bool16 bApplyAttrs = kFalse, bool16 bClearOverrides = kFalse) = 0;

		/**
			ChangeDefaultFrameGridStyle: Changes the default frame grid style
			@param ws	The workspace the object style name table containing the styles to sort
			@param newDefaultStyleUID	The new text style UID
			@param applyAttrs   True if we should apply the attrs from the style, this is not true when creating the style
			@param clearOverrides True if we want to clear overrides, otherwise kFalse.
		*/
		virtual ErrorCode ChangeDefaultFrameGridStyle(IWorkspace* ws, UID newDefaultStyleUID, bool16 bApplyAttrs = kFalse, bool16 bClearOverrides = kFalse) = 0;

		/**
			RenameObjectStyle: Renames the given object style
			@param ws	The workspace the object style name table containing the style
			@param styleUID	The style to rename
			@param newName	The new name of the style
			@param bNotify  Flag indicates if we should do notify or not.
		*/
		virtual ErrorCode RenameObjectStyle(IWorkspace* ws, const UID styleUID, const PMString& newName, const bool16 bNotify = kTrue) = 0;
		/**
			DuplicateObjectStyles: Duplicates the object styles in the stylesToBeReplaced list 
			@param ws	The workspace the object style name table containing the style
			@param styleNames	The list of styles to be duplicate
			@param namesCreated	The names of the newly created styles
		*/
		virtual ErrorCode DuplicateObjectStyles(IWorkspace* ws, const K2Vector<PMString>& styleNames, K2Vector<PMString>& namesCreated) = 0;
		/**
			ChangeDefaultGraphicStyle: Changes the default graphic style
			@param ws	The workspace the object style name table containing the styles to sort
			@param newDefaultStyleUID	The new graphic style UID
			@param applyAttrs   True if we should apply the attrs from the style, this is not true when creating the style
			@param clearOverrides True if we want to clear overrides, otherwise kFalse.

		*/
		virtual ErrorCode ChangeDefaultGraphicStyle(IWorkspace* ws, UID newDefaultStyleUID, bool16 bApplyAttrs = kFalse, bool16 bClearOverrides = kFalse) = 0;	

		/**
			Returns the default graphics style
			@return PMString
		*/
		virtual PMString GetDefaultGraphicStyle(IWorkspace* ws) = 0;

		/**
			Returns the default text style
			@return PMString
		*/
		virtual PMString GetDefaultTextStyle(IWorkspace* ws) = 0;

		/**
			Returns the default frame grid style
			@return PMString
		*/
		virtual PMString GetDefaultFrameGridStyle(IWorkspace* ws) = 0;

		/** Creates a new style group.
			@param ws [IN] Workspace where to create the group.
			@param newStyleGroupName [IN] new style group name.
			@param parent [IN] UID of parent to create new group.
			@param position [IN] postion to create new style, pass -1 for last
		*/
		virtual ErrorCode CreateNewObjectStyleGroup(IWorkspace* ws, 
													const PMString newStyleGroupName, 
													const UID parent, 
													const int32 position) = 0;


		/** Renames a style group.
			@param ws [IN] workspace
			@param styleGroupUID [IN] style group UID.
			@param newName [IN] new style group name.
		*/
		virtual ErrorCode RenameObjectStyleGroup(IWorkspace* ws, 
												const UID styleGroupUID, 
												const PMString& newName) = 0;

		/** Duplicates a list of style groups.
			@param styleGroups [IN] list of style groups to be duplicated.
		*/
		virtual ErrorCode DuplicateObjectStyleGroups(const UIDList& styleGroups) = 0;

		/** Deletes a list of style groups.
			@param styleGroups [IN] list of object style groups to be deleted.
			@param remapList [IN] remapping for the style inside the groups being deleted.
		*/
		virtual ErrorCode DeleteStyleGroups(const UIDList& styleGroups, const RemappingList& remaplist) = 0;


		/** Moves a list of style groups to new parent and position.
			@param styleGroups [IN] list of style groups.
			@param newParent [IN] UID of the new parent.
			@param position [IN] new position.
			@param remapList [IN] remapping in case a style is being overwritten due to move.
			@param conflictFlag [IN] what to do incase of conflict.
		*/
		virtual ErrorCode MoveStyleGroups(	const UIDList& styleGroups,
											const UID newParent, 
											const int32 position, 
											const RemappingList& remaplist, 
											const IStyleRemapData::ConflictFlagEnum conflictFlag) = 0;

	};
}
#endif // define

