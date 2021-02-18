//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableStylesFacade.h $
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

#ifndef ITABLESTYLESFACADE_H
#define ITABLESTYLESFACADE_H

#include "IPMUnknown.h"
#include "TableTypes.h"
#include "TabStyID.h"
#include "keyboarddefs.h"

class IStyleGroupHierarchy;
class ITableModel;
class IWorkspace;

class AttributeBossList;
class GlobalTime;
/**
 * Utility functions for working with table styles.  To use these functions use
 * the <code>Utils</code> boss:<br>
 * <code>Utils<Facade::ITableStylesFacade>()->CreateTableStyle(...);</code>
 *
 */
namespace Facade
{
	class ITableStylesFacade : public IPMUnknown
	{
	public:
		enum {kDefaultIID = IID_ITABLESTYLESFACADE};

		/**
		 * Gets the [Basic Table] style for the given database.
		 *
		 * @param db [IN] the database of the workspace to get the basic table style
		 * from
		 * @return the basic table style
		 */
		virtual UID GetBasicTableStyle(IDataBase* db) const = 0;
		
		/**
		 * Copies the table styles and groups given in <code>whichStyles</code> 
		 * into the group given by <code>whichGroup</code>.
		 *
		 * @param whichGroup [IN] the group to copy the styles/groups into
		 * @param whichStyles [IN] a list of table styles and/or table style groups 
		 * to copy into the other table style group
		 * @return <code>kSuccess</code> if the groups were successfully copied, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode CopyStylesToGroup(const UIDRef& whichGroup, 
			const UIDList& whichStyles) const = 0;

		/**
		 * Gets the regional cell style for the given cell.  The regional style is
		 * dependent on where <code>address</code> lies in the table.
		 *
		 * @param tableModelBoss [IN] any interface on <code>kTableModelBoss</code>
		 * @param address [IN] the cell to get the regional style for
		 * @param runArea [OUT] optional, the regional style area
		 * @return the regional cell style
		 */
		virtual UID GetRegionalStyle(const IPMUnknown* tableModelBoss, 
			const GridAddress& address, 
			GridArea* runArea = nil) const = 0;
		
		/**
		 * Gets a set of regional styles used for the given <code>GridArea</code>.
		 *
		 * @param tableModelRef [IN] the table to examine
		 * @param whichArea [IN] the grid area to get regional styles from
		 * @param out_RegionalStyleSet [OUT] a list which has the set property of 
		 * regional styles used in the given grid area
		 * @return <code>kSuccess</code> if the regional styles (if any) were 
		 * returned, <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetRegionalStylesInArea(const UIDRef& tableModelRef, 
			const GridArea& whichArea, 
			UIDList& out_RegionalStyleSet) const = 0;
			
		/**
		 * Resolves the style hierarchy for the given table style.  All table styles
		 * are descendants of the root table style, so starting at the root, each 
		 * style in the branch leading to <code>tableStyle</code> will be queried 
		 * for their attributes, with any conflicts between nodes resolved by using 
		 * the value of the style farther down the branch.
		 *
		 * @param tableStyle [IN] the table style
		 * @param out_ResolvedAttrs [OUT] the resolved table style attributes
		 * @return <code>kSuccess</code> if the attributes were resolved, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetTableStyleAttrsResolved(const UIDRef& tableStyle,
													 AttributeBossList& out_ResolvedAttrs) const = 0;
		
		/**
		 * Returns the root table style for the given database.
		 *
		 * @param db [IN] the <code>IDataBase</code> to get the root style
		 * @return the root table style
		 */
		virtual UID GetRootTableStyle(IDataBase* db) const = 0;
		
		/**
		 * Creates and returns an instance of <code>kEditTableStyleCmdBoss</code>.  
		 * The command's interfaces will be set to edit the table style given by
		 * <code>tableStyleRef</code>.  The <code>ICommand</code> returned by this
		 * function should be wrapped in an <code>InterfacePtr</code>:<br>
		 * <code>InterfacePtr<ICommand> editCmd(Utils<ITableStylesFacade>()->CreateEditTableStyleCmd(tableStyleRef));</code>
		 *
		 * @param tableStyleRef [IN] the <code>UIDRef</code> of a table style
		 * @return the command used to edit a table style
		 */
		virtual ICommand* CreateEditTableStyleCmd(const UIDRef& tableStyleRef) const = 0;
		
		/**
		 * Sets the default table style.  The default table style in the insert
		 * table dialog.
		 *
		 * @param defaultStyle [IN] the <code>UIDRef</code> pointing to the table 
		 * style to be used as the default.
		 * @return <code>kSuccess</code> if the default table style was set,
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode SetDefaultStyle(const UIDRef& defaultStyle) const = 0;
		
		/**
		 * Creates a new table style group.
		 *
		 * @param workspace [IN] the workspace to create the style group on
		 * @param groupName [IN] the name of the style group, this should be a valid
		 * group name and be unique within the style group's parent
		 * @param parentUID [IN] the parent style group
		 * @param position [IN] the position within the parent group
		 * @param out_NewGroup [OUT] optional, use a valid pointer to get the
		 * <code>UID</code> of the new style group
		 * @return <code>kSuccess</code> if the new style group was created,
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode CreateNewStyleGroup(IWorkspace* workspace,
											  const PMString& groupName, 
											  const UID& parentUID, 
											  const int32 position, 
											  UID* out_NewGroup = nil) const = 0;
			
		/**
		 * Renames a single table style.
		 *
		 * @param whichStyle [IN] the table style to rename
		 * @param newName [IN] a valid, unique (within the style group context) name
		 * for the cell style
		 * @return <code>kSuccess</code> if the style was renamed, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode RenameTableStyle(const UIDRef& whichStyle, 
										   const PMString& newName) const = 0;

		/**
		 * Duplicates multiple table styles.  The duplicated styles will
		 * have the same attributes, but names that end with "copy", or
		 * "copy 1", "copy 2", etc.
		 *
		 * @param stylesToDuplicate [IN] a list of table styles to duplicate
		 * @return <code>kSuccess</code> if the styles were duplicated, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode DuplicateTableStyles(const UIDList& stylesToDuplicate) const = 0;

		/**
		 * Determines if the break link with style command can be executed for the 
		 * given table.  This will return true if the table has any table style 
		 * other than the root table style applied to it.
		 *
		 * @param tableModelRef [IN] the table model to examine
		 * @return <code>kTrue</code> if the break link with style command can be 
		 * executed on the given table, <code>kFalse</code> otherwise
		 */
		virtual bool16 CanBreakLinkWithStyle(const UIDRef& tableModelRef) const = 0;
		
		/**
		 * Determines if the break link with style command can be executed for the 
		 * given table.  This will return true if the table has any table style 
		 * other than the root table style applied to it.
		 *
		 * @precondition <code>CanBreakLinkWithStyle<code> returns 
		 * <code>kTrue</code>
		 * @param tableModel [IN] the table model to examine
		 * @return <code>kTrue</code> if the break link with style command can be 
		 * executed on the given table, <code>kFalse</code> otherwise
		 */
		virtual bool16 CanBreakLinkWithStyle(const ITableModel* tableModel) const = 0;
		
		/**
		 * Takes the given table and applies all its table style attributes
		 * as local overrides.  The table will then have the root table style
		 * applied to it.  If there are any conflicts between the style attributes
		 * and the local overrides, the local overrides will always win.
		 *
		 * @param tableModel [IN] the table to break the style link
		 * @return <code>kSucess</code> if the link was severed, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode BreakLinkWithStyle(const UIDRef& tableModel) const = 0;

		/**
		* Applies a table style to the given table.  The table style must
		* exist on the same database as the table.  This function can also
		* optionally remove any table overrides or any cell styles applied
		* to the table.
		*
		* @param whichStyle [IN] the style to apply
		* @param tableModelRef [IN] the table to apply the style to
		* @param removeTableOverrides [IN] if local table overrides should be 
		* removed
		* @param removeCellStyle [IN] flag for removing all cell style information
		* from the table
		* @return <code>kSuccess</code> if the style was applied, 
		* <code>kFailure</code> otherwise
		*/
		virtual ErrorCode ApplyTableStyle(const UIDRef& whichStyle,
			const UIDRef& tableModelRef, 
			const bool16 removeTableOverrides = kFalse,
			const bool16 removeCellStyle = kFalse) const = 0;

		/**
		* Edits an existing table style to match the given attributes.
		* If you don't need to update everything, see 
		* <code>CreateEditTableStyleCmd</code> in this class.
		*
		* @param styleName [IN] the new name for the style
		* @param attrList [IN] the new table attributes
		* @param workspace [IN] the workspace the style lives on
		* @param styleUID [IN] the <code>UID</code> of the style being updated
		* @param basedOn [IN] the new parent style
		* @param shortcutKey [IN] optional, the shortcut for the table style
		* @param modifiers [IN] optional, the modifiers for the shortcut
		* @param shortcutTime [IN] optional, the shortcut timestamp
		* @param preserveRegionalFormatting [IN] optional, if a regional cell style
		* is changed to the root cell style this flag is used to determine if 
		* regional cell style formatting should be preserved
		* @return <code>kSuccess</code> if the user was able to edit the style, 
		* <code>kFailure</code> otherwise
		*/
		virtual ErrorCode EditTableStyle(const PMString& styleName, 
			const AttributeBossList* attrList, 
			IWorkspace* workspace, 
			const UID& styleUID,
			const UID& basedOn,
			const VirtualKey shortcutKey = kVirtualNullKey, 
			const int16 modifiers = 0,
			const GlobalTime* shortcutTime = nil,
			const bool16 preserveRegionalFormatting = kFalse) const = 0;
		
		/**
		* Creates a table style on the given workspace.
		*
		* @param workspace [IN] the workspace to create the style on
		* @param parentHier [IN] the parent style group
		* @param position [IN] the position within the parent
		* @param styleName [IN] the name for the style, this name should be unique
		* within the <code>parentHier</code>
		* @param out_StyleRef [OUT] the <code>UIDRef</code> of the 
		* <code>kTableStyleBoss</code> that corresponds to the new style
		* @param basedOnStyle [IN] optional,the UID of the style the new style 
		* should be based on, if this parameter is not provided, the style will be
		* based on the root table style
		* @param attrList, optional attributes for the table style
		* @param shortcut [IN] optional, the shortcut key
		* @param modifiers [IN] optional, the shortcut modifier
		* @param shortcutTime [IN] optional, the shortcut timestamp
		* @return <code>kSuccess</code> if the table style was created, 
		* <code>kFailure</code> otherwise
		*/
		virtual ErrorCode CreateTableStyle(IWorkspace* workspace, 
			const IStyleGroupHierarchy* parentHier, 
			const int32 position,
			const PMString& styleName, 
			UIDRef& out_StyleRef,
			const UID& basedOnStyle = kInvalidUID, 
			const AttributeBossList* attrList = nil,
			const VirtualKey shortcut = kVirtualNullKey, 
			const int16 modifiers = 0,
			const GlobalTime* shortcutTime = nil) const = 0;

		/**
		* Creates a new table style using the table style and attributes of
		* the given table.  The new style will be based on the style of the
		* given table and contain as attributes any overrides on the table.
		*
		* @param tableModel [IN] the table whose attributes should be used for the
		* new table style
		* @param parentHier [IN] optional, the style hierarchy to place the new 
		* style under, if this is not defined the root hierarchy is used
		* @param stylePosition [IN] optional, the position under the parent 
		* hierarchy
		* @return <code>kSuccess</code> if the table style was created, 
		* <code>kFailure</code> otherwise
		*/
		virtual ErrorCode CreateNewTableStyle(const UIDRef& tableModel,
			const IStyleGroupHierarchy* parentHier = nil, 
			const int32 stylePosition = -1) const = 0;

		/**
		* Deletes a table style.
		*
		* @param styleToDelete [IN] the style to delete
		* @param replacementStyle [IN] the replacement style UID
		* @param preserveFormatting [IN] only used if the replacement
		* style is the root style, in which case it will do a break link
		* with style if this is set to kTrue
		* @return <code>kSuccess</code> if the style was deleted, 
		* <code>kFailure</code> otherwise
		*/
		virtual ErrorCode DeleteTableStyle(const UIDRef& styleToDelete,
			const UID& replacementStyle, 
			const bool16 preserveFormatting = kFalse) const = 0;

		/**
		 * Gets the local table overrides from the given table model.
		 *
		 * @param tableModel [IN] the table to examine
		 * @param out_LocalOverrides [OUT] any local overrides on the table
		 * @return <code>kSuccess</code> if the local overrides were retrieved,
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetLocalOverrides(const UIDRef& tableModel, 
			AttributeBossList& out_LocalOverrides) const = 0;

		/**
		 * Clears any local table style overrides on the given table.
		 *
		 * @see HasLocalOverrides
		 * @param tableModel [IN] the table to clear the overrides from
		 * @param clearCellStyles [IN] optional, set to <code>kTrue</code> to
		 * clear all local cell styles
		 * @return <code>kSuccess</code> if the overrides were cleared, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode ClearLocalOverrides(const UIDRef& tableModel,
			const bool16 clearCellStyles = kFalse) const = 0;

		/**
		 * Returns the table style for the table.
		 *
		 * @param tableModel [IN] the table to clear the overrides from
		 * @param out_TableStyle [OUT] the table style of the given table
		 * @return <code>kSuccess</code> if the table style was retrieved, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetTableStyle(const UIDRef& tableModel, 
			UID& out_TableStyle) const = 0;

		/**
		 * Tests if the given table has any local table overrides.
		 *
		 * @param tableModel [IN] the table model to examine
		 * @return <code>kTrue</code> if the table has local table overrides, 
		 * <code>kFalse</code> otherwise.
		 */
		virtual bool16 HasLocalOverrides(const UIDRef& tableModel) const = 0;

		/**
		 * Tests if the redefine table style command can be executed on the given 
		 * table.  To run the redefine style command the table must have overrides 
		 * and any style other than the root style applied to it.
		 *
		 * @param tableModelRef [IN] the table to examine
		 * @return <code>kTrue</code> if the applied style can be redefined,
		 * <code>kFalse</code> otherwise
		 */
		virtual bool16 CanRedefineTableStyle(const UIDRef& tableModelRef) const = 0;
		
		/**
		 * Tests if the redefine table style command can be executed on the given 
		 * table.  To run the redefine style command the table must have overrides 
		 * and any style other than the root style applied to it.
		 *
		 * @param tableModel [IN] the table to examine
		 * @return <code>kTrue</code> if the applied style can be redefined,
		 * <code>kFalse</code> otherwise
		 */
		virtual bool16 CanRedefineTableStyle(const ITableModel* tableModel) const = 0;
		
		/**
		 * Redefines the table style of the given table to contain its present 
		 * attributes, along with any table overrides currently applied on the 
		 * table.  If there are conflicts between the style attributes and its 
		 * overrides, the overrides will always take precedence.
		 *
		 * @param tableModel [IN] the table to examine
		 * @return <code>kSuccess</code> if the style was redefined, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode RedefineTableStyle(const UIDRef& tableModel) const = 0;

		/**
		 * Duplicates a single table style, and returns the newly created style.
		 *
		 * @param styleToDup [IN] the style to duplicate
		 * @param out_NewStyleRef [OUT] the duplicate style
		 * @return <code>kSuccess</code> if the style was duplicated, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode DuplicateStyle(const UIDRef& styleToDup, 
			UIDRef& out_NewStyleRef) const = 0;
	};
}
#endif
