//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTagSuite.h $
//  
//  Owner: Ryan Gano
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
#ifndef _IXMLTagSuite_
#define _IXMLTagSuite_

#include "XMediaUIID.h"
	
class UIDList;
class XMLReference;
class IXMLDTDInsertElementListData;
class IXMLDTDReplaceElementListData;

/** Suite to manipulate tag (IXMLTag) properties in active selection; Provides clean, high level API to use from client code 
	to access and change markup properties of selection.  
	Aggregated on concrete selection bosses
	for selection formats such as text, layout and 'structure' (selections in the structure view).
	
*/
class IXMLTagSuite : public IPMUnknown
{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		/** States in which selection can be. */
		enum AddOrRetagState
			{
			kAddEnabled,
			kRetagEnabled,
			kAddDisabled,
			kRetagDisabled,
			kNeitherDisabled
			};
		enum { kDefaultIID = IID_IXMLTAGSUITE };

		/** Which type of dynamic menu will be added */
		enum MenuType
		{
			/** Element will be a child of the selection */
			kInsertChildMenu,
			/** Element will be an after sibling of the selection */
			kInsertSiblingAfterMenu
		}; 

		/**	Returns a list of tags in the selection; ask each of the enabled CSBs for the XML Tags used,
			so can return a fairly lengthy list of tags depending on the selection itself.
			
			@return UIDList containing tags used in the active selection 
		 */
		virtual UIDList				GetTags() = 0;

		/**	Applies a tag to the selection; will process e.g. IXMLElementCommands::CreateElement or a
			low-level command to change the tag associated with an element (kXMLSetElementTagCmdBoss).
		
			You should check the AddOrRetagState first,
			to determine whether retag makes sense, to determine what to set for this parameter.
			If there's a text selection in an untagged frame, then the frame itself would need a tag,
			and a dialog will appear soliciting a tag for the frame.

			Selections in the structure-view are simpler to understand; the subtree of nodes selected get the tag
			applied (through kXMLSetElementTagCmdBoss).
		
			@param tag specifies tag (IXMLTag) to apply to current selection
			@param retag kTrue if retag intended outcome
			@param allowPresetUI kTrue if the client doesn't mind if UI pops up during this action.
			@return  kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode			SetTag(const UIDRef& tag, bool16 retag, bool16 allowPresetUI = kTrue) = 0;				

		/**	Determine state of the selection; if something's tagged already, then
			kRetagEnabled would be returned, or if it could be tagged, kAddEnabled.

			@return  AddOrRetagState specifying state of selection
		 */
		virtual AddOrRetagState		GetAddOrRetagState() = 0;
	
		/**	Determine whether or not the current selection can have a tag applied
			regular elements can but Comments, PIs and DTDs cannot..

			@return  kTrue if selection contains elements - kFalse if not
		 */
		virtual bool16				CanTag() = 0;

		/** Determine whether or not the current selection can be autotagged.
			Autotagging means that default tags are chosen for the selection
			rather than the user picking a specfic tag to use.

			@return kTrue if selection can be autotagged (only if there are
					presets available.
		*/
		virtual bool16				CanAutoTag() = 0;

		/** Autotag the selected objects.

			In the Tables case we would chose a default tag for story, table,
			cells. and the clients text selection would not be tagged.

			@param allowPresetUI - kTrue if the client doesn't mind if UI pops up during this action
			@return whether or not this action succeeded.
		*/
		virtual ErrorCode				AutoTag(bool16 allowPresetUI = kTrue) = 0;

		/**	Determine if abstract selection supports the capability to Untag it.
			
			@return  kTrue if selection can be untagged, kFalse otherwise
		 */
		virtual bool16				CanUnTag() = 0;		

		/**	Remove tag(s) associated with active selection; can take out a whole chunk of the structure
			tree, as IXMLElementCommands::DeleteElement may be processed by this method call.
			@return kSuccess if un-tagging operation could be completed successfully, kFailure otherwise 
		 */
		virtual ErrorCode			UnTag() = 0;

		/**	This is what would appear in the context sensitive menu (once translated) for instance, Untag Text
			@param untagStr [OUT] parameter holding what would get translated for the end-user to see
		 */
		virtual void				GetUnTagString( PMString* untagStr ) = 0;

		/**	Get a list of menus that should have tags added to them. This allows the CSB to determine
			which menus get tag actions added to them rather than letting the client code try to figure
			out who to add tags for.
			@param *menuList - This is filled with a list of menus that need entries added to them
			@param whichAction - The action for which we are adding new menu items
		 */
		virtual void				GetMenuNamesForTags(K2Vector<PMString> *menuList, ActionID whichAction) const = 0;
		
		/**	Determine if abstract selection supports the capability to add a comment.
			
			@return  kTrue if selection can have a comment, kFalse otherwise
		 */
		virtual bool16				CanAddComment() = 0;

		/**	Create a comment element for the selection
			@param comment specifies the text to use for the comment
			@return kSuccess if comment could be added successfully, kFailure otherwise 
		 */
		virtual ErrorCode			AddComment(const PMString &comment) = 0;

		/**	Modify the selected comment to use the new string
			@param comment specifies the text to use for the comment
			@return kSuccess if comment could be added successfully, kFailure otherwise 
		 */
		virtual ErrorCode			ChangeComment(const PMString &comment) = 0;

		/**	Determine if abstract selection supports the capability to add a processing instruction
			
			@return  kTrue if selection can have a processing instruction, kFalse otherwise
		 */
		virtual bool16				CanAddProcessingInstruction() = 0;

		/**	Create a processing instruction for the selection
			@param target specifies the text to use for the target of the PI
			@param data specifies the text to use for the data of the PI
			@return kSuccess if processing instruction could be added successfully, kFailure otherwise 
		 */
		virtual ErrorCode			AddProcessingInstruction(const PMString &target, const PMString &data) = 0;
		
		/**	Modify the selected PI to use the new string
			@param target specifies the text to use for the target of the PI
			@param data specifies the text to use for the data of the PI
			@return kSuccess if PI could be added successfully, kFailure otherwise 
		 */
		virtual ErrorCode			ChangeProcessingInstruction(const PMString &target, const PMString &data) = 0;

		/** Fill an insert dynamic menu with tag names based on the current selection
			@param insertElementListData - A list used to store elements referenced by menu items
			@param menuList - The list of menus to be filled. A menu is denoted by its name (InsertChildTagPopup)
			@param menuType - The type of menu we are building (child or sibling)
			#return - The number of items added to the menu
		*/
		virtual int32			FillInsertDynamicMenu(IXMLDTDInsertElementListData *insertElementListData, const K2Vector<PMString> &menuList, MenuType menuType) = 0;

		/** Fill a replace dynamic menu with tag names based on the current selection
			@param replaceElementListData - A list used to store elements referenced by menu items
			@param menuList - The list of menus to be filled. A menu is denoted by its name (InsertChildTagPopup)
			#return - The number of items added to the menu
		*/
		virtual int32			FillReplaceDynamicMenu(IXMLDTDReplaceElementListData *ReplaceElementListData, const K2Vector<PMString> &menuList) = 0;

		/** Can the current selection be tagged via Style to Tag Mapping?
			return -- kTrue - The selection can be tagged, kFalse - The selection cannot be tagged
		*/
		virtual bool16			CanMapSelectedStoriesStyles() const = 0;

		/** Tag the current selection be tagged via Style to Tag Mapping
			return -- kSuccess - the tagging succeeded
		*/
		virtual ErrorCode		MapSelectedStoriesStyles() const = 0;
};



#endif // _IXMLTagSuite_
