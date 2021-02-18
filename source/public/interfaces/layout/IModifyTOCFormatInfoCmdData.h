//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IModifyTOCFormatInfoCmdData.h $
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
//  Comments: This interface is used to access the command data related to ModifyTOCFormatInfoCmd.
//  
//========================================================================================

#pragma once
#ifndef __IMODIFYTOCFORMATINFOCMDDATA__
#define __IMODIFYTOCFORMATINFOCMDDATA__

#include "ICommand.h"
#include "TOCID.h"

/** This interface is for accessing command data related to ModifyTOCFormatInfoCmd.
    ModifyTOCFormatInfoCmd is used for repairing the format information for table of content 
	styles when those format table of content entry styles(paragraph or chracter styles) 
	are being deleted or modified. In future release, we will use reference index to do 
	the repair work and this interface may be obsolete. 
    @see kModifyTOCFormatInfoCmdBoss.
*/
class IModifyTOCFormatInfoCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMODIFYTOCFORMATINFOCMDDATA };

		/**	Set all the data for processing ModifyTOCFormatInfoCmd.
			@param target IN the session or document workspace where the format style resides on. 
			@param styleRef IN the UIDRef of the format style(paragraph style or character style)
			@param styleName IN the original name of the format style.
			@param isParaStyle IN flag indicates if it is paragraph style or not.
			@param isRename IN flag indicates if the edited style is renamed or not. This is to 
			       optimize certain action. For example, if the format style is a character style 
			       and we just rename the style, then we should not do anything since we cache the 
				   UID for character style and rename does not change UID.
			@param replaceUIDRef IN the UIDRef for the updated format style.
		*/
		virtual void Set
					(
						const UIDRef& target,
						const UIDRef& styleRef, 
						const PMString& styleName, 
						bool16 isParaStyle, 
						bool16 isRename,
						const UIDRef& replaceUIDRef //manojg
					) = 0;

		/**	Get the UIDRef for the session or document workspace which we use to instantiate 
		    corresponding the table of content style name table and other style name table.
			@param none
			@return const UIDRef& the UIDRef of session or document workspace.
		*/
		virtual const UIDRef& GetTarget() const = 0;

		/**	Set the target of the session or document workspace.
			@param target IN the UIDRef of session or document workspace to be set.
		*/
		virtual void SetTarget(const UIDRef& target) = 0;

		/**	Get the UIDRef of deleted or edited paragraph or character style.
			@param none
			@return const UIDRef& the delete or edited paragraph or character style.
		*/
		virtual const UIDRef& GetStyleRef() const = 0;

		/**	Set the UIDRef of deleted or edited paragraph or character style.
			@param styleRef IN UIDRef of the deleted or edited paragraph or character style.
		*/
		virtual void SetStyleRef(const UIDRef& styleRef) = 0;

		/**	Get the original name of deleted or edited paragraph or character style.
			@param none
			@return const PMString& the original name of deleted or edited paragraph or character style.
		*/
		virtual const PMString& GetStyleName() const = 0;

		/**	Set the original name of deleted or edited paragraph or character style.
			@param styleName IN the original name.
		*/
		virtual void SetStyleName(const PMString& styleName) = 0;

		/**	Get the boolean data about if the deleted or edited style is a paragraph style or not.
			@param none
			@return const bool16& kTrue means it is a paragraph style, otherwise kFalse.
		*/
		virtual const bool16& IsParaStyle() const = 0;

		/** Set the boolean flag regarding the deleted or edited style is a paragraph style or not.
			@param paraStyleFlag IN the boolean data to be set.
		*/
		virtual void SetParaStyleFlag(const bool16& paraStyleFlag) = 0;

		/**	Get the boolean data indicating if the edited style is just a rename action or not. 
			This flag is to optimize certain action. For example, if the format style is a character style 
			and we just rename the style, then we should not do anything since we cache the 
			UID for character style and rename does not change UID.
			@param none
			@return const bool16& kTrue means the style is renamed, otherwise kFalse.
		*/
		virtual const bool16& IsRename() const = 0;

		/**	Set the flag indicates if the edited style is renamed or not.
			@param renameFlag IN the boolean flag to be set.
		*/
		virtual void SetRenameFlag(const bool16& renameFlag) = 0;

		/**	Get the UIDRef of the updated format style.
			@param none
			@return const UIDRef& the updated format style.
		*/
		virtual const UIDRef& GetReplaceUIDRef() const = 0;

		/**	Set the updated format style.
			@param replaceUIDRef IN the style to be set.
		*/
		virtual void SetReplaceUIDRef(const UIDRef& replaceUIDRef) = 0;

		/**	This function is deprecated since InDesign 2.0. 
		    It is NOT used in InDesign's core code base.
			@param none
			@return ICommand::CommandState the command state. 
		*/
		virtual const ICommand::CommandState GetCmdState() const = 0;

		/**	This function is deprecated since InDesign 2.0. 
		    It is NOT used in InDesign's core code base.
			@param state the command state to be set.
		*/
  		virtual void SetCmdState(const ICommand::CommandState state) = 0;
};

#endif //__IMODIFYTOCFORMATINFOCMDDATA__
