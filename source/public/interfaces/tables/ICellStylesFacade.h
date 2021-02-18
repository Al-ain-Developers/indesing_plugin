//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellStylesFacade.h $
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

#ifndef ICELLSTYLESFACADE_H
#define ICELLSTYLESFACADE_H

#include "IPMUnknown.h"

#include "CelStyID.h"
#include "TableTypes.h"
#include "keyboarddefs.h"

class IStyleGroupHierarchy;
class ITableModel;
class IWorkspace;

class AttributeBossList;
class GlobalTime;

namespace Facade
{
	/**
	* Utility functions for working with cell styles.  To use these functions use
	 * the <code>Utils</code> boss:<BR>
	 * <code>Utils<Facade::ICellStylesFacade>()->CreateCellStyle(...);</code>
	 *
	 */
	class ICellStylesFacade : public IPMUnknown
	{
	public:
		enum {kDefaultIID = IID_ICELLSTYLESFACADE};
		 
		/**
		 * Copies the cell styles and groups given in <code>whichStyles</code> 
		 * into the group given by <code>whichGroup</code>.
		 *
		 * @param whichGroup [IN] the group to copy the styles/groups into
		 * @param whichStyles [IN] a list of cell styles and/or cell style groups 
		 * to copy into the other cell style group
		 * @return <code>kSuccess</code> if the groups were successfully copied, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode CopyStylesToGroup(const UIDRef& whichGroup, 
			const UIDList& whichStyles) const = 0;

		/**
		 * Goes through the cell style hierarchy and looks for the desired 
		 * attribute.  The interface returned by this function must be released by 
		 * the caller.
		 *
		 * @param db [IN] the database
		 * @param startingStyle [IN] the style to start with
		 * @param whichAttr [IN] which cell attribute
		 * @param iid [IN] the <code>PMIID</code> of the attribute, should be 
		 * something like <code>IID_ITABLEATTRUID</code>, use
		 * <code>IID_UNKNOWN</code> if you don't know
		 * @return the value of the attribute, if it exists
		 */
		virtual const IPMUnknown* QueryCellStyleHier(IDataBase* db, 
			const UID& startingStyle, 
			const ClassID& whichAttr, 
			const PMIID& iid
			/* const PMIID& cellAttrType = IID_ITABLEATTRIBUTES or IID_IVERTICALCELLSTYLEATTRIBUTES*/) const = 0;
		
		/**
		 * Resolves the style hierarchy for the given cell style.  All cell styles 
		 * are descendants of the root cell style, so starting at the root, each 
		 * style in the branch leading to <code>cellStyle</code> will be queried for
		 * their attributes, with any conflicts between nodes resolved by using the 
		 * value of the style farther down the branch .
		 *
		 * @param cellStyle [IN] the table style
		 * @param out_ResolvedAttrs [OUT] the resolved cell style attributes
		 * @param attributeType [IN] the type of cell style attributes you want, for the
		 * horizontal table version use <code>IID_ITABLEATTRIBUTES</code>, for the
		 * vertical table version use <code>IID_IVERTICALCELLSTYLEATTRIBUTES</code>
		 * @return <code>kSuccess</code> if the attributes were resolved, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetCellStyleAttrsResolved(const UIDRef& cellStyle, 
													AttributeBossList& resolvedAttrs,
													const PMIID& attributeType) const = 0;
		
		/**
		 * Gets the paragraph style associated with the given cell style.  This 
		 * function will go up the cell style hierarchy to find the paragraph style.
		 *
		 * @param styleRef [IN] the cell style to get the pargraph style from
		 * @return the <code>UID</code> of the paragraph style associated with the
		 * cell style, or <code>kInvalidUID</code> if there is no associated 
		 * paragraph style
		 */
		virtual UID GetCellStyleParagraphStyle(const UIDRef& styleRef) const = 0;
		
		/**
		 * Goes through the given cell, checking all the paragraph styles used in 
		 * that cell.  If the used paragraph styles do not match the paragraph style
		 * defined by the cell style then those paragraph styles are returned in 
		 * <code>out_OverridingParaStyles</code>.  If the applied cell style does 
		 * not define a paragraph style, then no applied paragraph style is 
		 * considered an override.
		 *
		 * @param tableModel [IN] the table to examine
		 * @param cellAnchor [IN] the grid address of the cell to examine
		 * @param out_OverridingParaStyles [OUT] the list of overriding paragraph 
		 * styles
		 * @param styleToCheck [IN] optional the style that will be checked
		 * against when searching for overrides.  If left to its default, this
		 * function will check against the style currently applied to the cell.
		 * @return <code>kSuccess</code> if the cell was examined and all overriding
		 * paragraph style were returned, <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetOverridingParagraphStyles(const ITableModel* tableModel, 
													   const GridAddress& cellAnchor, 
													   UIDList& out_OverridingParaStyles,
													   const UIDRef& styleToCheck = UIDRef::gNull) const = 0;
		
		/**
		 * Gets all the cell overrides applied to the given cell that conflict
		 * with either the applied cell style or the style passed into the function.  
		 * If the passed in style is its default and the applied cell style is the 
		 * root cell style, then all overrides will be returned by this function.
		 *
		 * @param tableModel [IN] the table to examine
		 * @param whichCell [IN] the grid address of the cell to get the overrides 
		 * from
		 * @param out_Overrides [OUT] container where any local overrides will be 
		 * placed
		 * @param styleToCheck [IN] optional the style that will be checked
		 * against when searching for a paragraph style override.  If left to its 
		 * default, this function will check against the style currently applied 
		 * to the cell.
		 * @return <code>kSuccess</code> if all local overrides were placed into
		 * <code>out_Overrides</code>, <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetCellOverrides(const ITableModel* tableModel, 
										   const GridAddress& whichCell, 
										   AttributeBossList& out_Overrides,
										   const UIDRef& styleToCheck = UIDRef::gNull) const = 0;
		
		/**
		 * Gets all the cell overrides applied to the given cell, regardless of the
		 * applied style.
		 *
		 * @param tableModel [IN] the table to examine
		 * @param whichCell [IN] the grid address of the cell to get the overrides 
		 * from
		 * @param out_Overrides [OUT] container where any local overrides will be 
		 * placed
		 * @return <code>kSuccess</code> if all local overrides were placed into
		 * <code>out_Overrides</code>, <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetAllCellOverrides(const ITableModel* tableModel, 
										   const GridAddress& whichCell, 
										   AttributeBossList& out_Overrides) const = 0;
										   
		/**
		 * Creates a new cell style group.
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
		 * Returns the root cell style for the given database.
		 *
		 * @param db [IN] the <code>IDataBase</code> to get the root style from
		 * @return the root cell style
		 */
		virtual UID GetRootCellStyle(IDataBase* db) const = 0;
		
		/**
		 * Creates and returns an instance of <code>kEditCellStyleCmdBoss</code>.  
		 * The command's interfaces will be set to edit the cell style given by
		 * <code>cellStyleRef</code>.  The <code>ICommand</code> returned by this
		 * function should be wrapped in an <code>InterfacePtr</code>:<BR>
		 * <code>InterfacePtr<ICommand> editCmd(Utils<ICellStylesFacade>()->CreateEditCellStyleCmd(cellStyleRef));</code>
		 *
		 * @param cellStyleRef [IN] the <code>UIDRef</code> of a cell style
		 * @return the command used to edit a cell style
		 */
		virtual ICommand* CreateEditCellStyleCmd(const UIDRef& cellStyleRef) const = 0;
		
		/**
		 * Renames a single cell style.
		 *
		 * @param whichStyle [IN] the cell style to rename
		 * @param newName [IN] a valid, unique (within the style group context) name
		 * for the cell style
		 * @return <code>kSuccess</code> if the style was renamed, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode RenameCellStyle(const UIDRef& whichStyle, 
			const PMString& newName) const = 0;
		
		/**
		 * Duplicates a single cell style.
		 *
		 * @param whichStyle [IN] the cell style to duplicate
		 * @param out_NewStyle [OUT] the <code>UIDRef</code> of the duplicate style
		 * @return <code>kSuccess</code> if the style was duplicated, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode DuplicateCellStyle(const UIDRef& whichStyle, 
			UIDRef& out_NewStyle) const = 0;
		
		/**
		 * Duplicates multiple cell styles.  The duplicated styles will
		 * have the same attributes, but names that end with "copy", or
		 * "copy 1", "copy 2", etc.
		 *
		 * @param stylesToDuplicate [IN] a list of cell styles to duplicate
		 * @return <code>kSuccess</code> if the styles were duplicated, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode DuplicateCellStyles(const UIDList& stylesToDuplicate) const = 0;
		
		/**
		 * Sets the default cell style.  Currently the default cell style is not
		 * used.
		 *
		 * @param defaultStyle [IN] the cell style to use as the default
		 * @return <code>kSuccess</code> if the default style was set, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode SetDefaultStyle(const UIDRef& defaultStyle) const = 0;
		
		/** 
		 * Applies a cell style to the given area of the table.
		 *
		 * @param whichStyle [IN] the cell style to apply
		 * @param tableModelRef [IN] the <code>UIDRef</code> of the 
		 * <code>kTableModelBoss</code> to apply the style to
		 * @param whichArea [IN] the <code>GridArea</code> to apply the style to
		 * @param removeOverrides [IN] optional, <code>kTrue</code> if cell 
		 * overrides should be  removed, <code>kFalse</code> otherwise
		 * @param applyParaStyle [IN] optional, <code>kTrue</code> if the cell
		 * style should apply its paragraph style, <code>kFalse</code> otherwise.  
		 * The removeOverrides option is not affected by this flag.
		 * does not affect remove overrides.
		 * @return <code>kSuccess</code> if the cell style was applied, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode ApplyCellStyle(const UIDRef& whichStyle, 
										 const UIDRef& tableModelRef, 
										 const GridArea& whichArea, 
										 const bool16 removeOverrides = kFalse,
										 const bool16 applyParaStyle = kTrue) const = 0;
		
		/** 
		 * Applies a cell style to the given area of the table and removes any
		 * local overrides.
		 *
		 * @param whichStyle [IN] the cell style to apply
		 * @param tableModelRef [IN] the <code>UIDRef</code> of the 
		 * <code>kTableModelBoss</code> to apply the style to
		 * @param whichArea [IN] the <code>GridArea</code> to apply the style to
		 * @return <code>kSuccess</code> if the cell style was applied, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode ApplyCellStyleAndClearAll(const UIDRef& whichStyle, 
										 const UIDRef& tableModelRef, 
										 const GridArea& whichArea) const = 0;
		
		/**
		 * Edits a cell style with the given parameters.
		 *
		 * @param styleName [IN] the style name
		 * @param styleAttrList [IN] the cell attributes to use for the style
		 * @param workspace [IN] the workspace the cell style lives on
		 * @param styleUID [IN] the <code>UID</code> of the cell style
		 * @param basedOnStyleUID [IN] the cell style that the style should
		 * be based on
		 * @param shortcutKey [IN] optional, the shortcut key
		 * @param modifiers [IN] optional, the shortcut modifiers
		 * @param shortcutTime [IN] optional, the shortcut timestamp
		 * @return <code>kSuccess</code> if the cell style was applied, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode EditCellStyle(const PMString& styleName, 
									  const AttributeBossList* styleAttrList, 
									  IWorkspace* workspace, 
									  const UID& styleUID,
									  const UID& basedOnStyleUID,
									  const VirtualKey shortcutKey = kVirtualNullKey, 
									  const int16 modifiers = 0,
									  const GlobalTime* shortcutTime = nil) const = 0;
		
		/**
		 * Deletes the given cell style.  If the parameter <code>replacementStyle</code>
		 * is provided, it will be used to replace all instances of the deleted style.
		 * The <code>preserveFormatting</code> parameter is only relevent if the
		 * replacement style is the root style (or not provided).
		 *
		 * @param styleToDelete [IN] the <code>UIDRef</code> of the style to delete
		 * @param replacementStyle [IN] optional, the style to use as a replacement,
		 * defaults to the root cell style
		 * @param preserveFormatting [IN] optional, if <code>replacementStyle</code> is the
		 * root cell style, or <code>kInvalidUID</code> then if this parameter is
		 * <code>kTrue</code>, all cell style formatting will be applied as local overrides
		 * on any cell using the style that will be deleted.
		 * @return <code>kSuccess</code> if the cell style was deleted, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode DeleteCellStyle(const UIDRef& styleToDelete,
										  const UID& replacementStyle = kInvalidUID,
										  const bool16 preserveFormatting = kFalse) const = 0;
		
		/**
		 * Creates a cell style on the given workspace.  The style will be named the
		 * given name (with a number after the name if a style already exists with 
		 * the desired name) and if <code>styleAttrs</code> is not nil, with those 
		 * attributes.  If <code>styleAttrs</code> is nil, the style will not have
		 * any attributes, so its probably best to get the 
		 * <code>AttributeBossList</code> of an existing cell style, or any table 
		 * cell to duplicate.
		 *
		 * @param workspace [IN] the workspace to create the cell style on.
		 * @param syleName [IN] the name for the cell style
		 * with a number
		 * @param parentHier [IN] the hierarchy to place the style under
		 * @param position [IN] the position within the parent hierarchy
		 * @param outStyleRef [OUT] the <code>UIDRef</code> of the new style
		 * @param basedOnStyle [IN] optional the style this style is based on, if
		 * this parameter is not provided, the new style will be based on the root style
		 * @param styleAttrs [IN] optional, an <code>AttributeBossList</code> for the 
		 * cell style, if this is nil the style will have no attributes
		 * @param shortcutKey [IN] optional, the shortcut key for the style
		 * @param modifiers [IN] optioanl, modifiers for the shortcut key
		 * @param shortcutTime [IN] optional, the shortcut timestamp
		 * @return <code>kSuccess</code> if the style was created, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode CreateCellStyle(IWorkspace* workspace, 
										  const IStyleGroupHierarchy* parentHier, 
										  const int32 position,
										  const PMString& syleName, 
										  UIDRef& outStyleRef, 
										  const UID& basedOnStyle = kInvalidUID,
										  const AttributeBossList* styleAttrs = nil,
										  const VirtualKey shortcutKey = kVirtualNullKey, 
										  const int16 modifiers = 0,
										  const GlobalTime* shortcutTime = nil) const = 0;
		
		/**
		 * Creates a cell style that will be based on the cell style at the give
		 * address, and whose attributes will be the overrides of the cell at that
		 * address.
		 *
		 * @param tableModelRef [IN] the table model to examine
		 * @param selectedAddress[IN] the address of the cell to examine for 
		 * overrides and the parent style
		 * @param parentHier [IN] the style hierarchy to place the new style under,
		 * if this is not defined the root hierarchy is used
		 * @param stylePosition [IN] the position under the parent hierarchy
		 * @return <code>kSuccess</code> if the style was created, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode CreateCellStyle(const UIDRef& tableModelRef, 
										  const GridAddress& selectedAddress,
										  const IStyleGroupHierarchy* parentHier = nil,
										  const int32 stylePosition = -1) const = 0;
		
		/**
		 * Tests if the break link with cell style command can be executed on the 
		 * given area of the table.  For this to return true, the selected area must
		 * have styles other than the root cell style (or <code>kInvalidUID</code>) 
		 * applied to them.
		 *
		 * @param tableModel [IN] the table to examine
		 * @param whichArea [IN] the area to examine
		 * @return <code>kTrue</code> if the break link command can be executed,
		 * <code>kFalse</code> otherwise
		 */
		virtual bool16 CanBreakLinkWithCellStyle(const ITableModel* tableModel, 
			const GridArea& whichArea) const = 0;
		
		/**
		 * Breaks the link with the cell style for the given area.  When the break
		 * link command is executed, the style for the cells in 
		 * <code>whichArea</code> will be set to the root cell style, while all 
		 * style attributes will be  applied as local overrides.  Any preexisting 
		 * local overrides will take precedence over the style attributes being 
		 * applied as local overrides.
		 *
		 * @precondition <code>CanBreakLinkWithCellStyle</code> returns 
		 * <code>kTrue</code>
		 * @param tableModelRef [IN] the table to examine
		 * @param whichArea [IN] the grid area to break the link
		 * @return <code>kSuccess</code> if the link with the cell style was broken, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode BreakLinkWithStyle(const UIDRef& tableModelRef, 
											 const GridArea& whichArea) const = 0;
		
		/**
		 * Determines if the redefine cell style command can be executed.
		 * For this function to return true, the cell at the given address must have
		 * a style other than the root cell style applied to it (or 
		 * <code>kInvalidUID</code>) and there must be cell overrides, 
		 * or there is a cell style that does not define a paragraph style, or the
		 * cell style's paragraph style is overridden.
		 *
		 * @param tableModel [IN] the table model
		 * @param whichAddress [IN] the address of the cell
		 * @return <code>kTrue</code> if the break link command can be executed,
		 * <code>kFalse</code> otherwise
		 */
		virtual bool16 CanRedefineCellStyle(const ITableModel* tableModel, 
			const GridAddress& whichAddress) const = 0;
		
		/**
		 * Redefines the cell style at the given address to use the style attributes
		 * along with any local overrides as the style's new attributes.  Local 
		 * overrides will take precedence whenever any conflicts exist.  The
		 * paragraph style of the first paragraph in the cell will be used as the
		 * cell style's paragraph style.
		 *
		 * @param tableModelRef [IN] the table to examine
		 * @param whichAddress [IN] the <code>GridAddress</code> of a cell anchor
		 * whose local overrides will used to redefine the style
		 * @return <code>kSuccess</code> if the style was redefined, 
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode RedefineStyle(const UIDRef& tableModelRef, 
										const GridAddress& whichAddress) const = 0;
		
		/**
		 * Clears all cell overrides from the given areathat conflict with the 
		 * applied cell style.  If the root cell style is the applied style, then
		 * all overrides will be cleared.  This will also clear out
		 * any overriding paragraph styles, returning the text within the cell to 
		 * the style's paragraph style.  If there is no cell style applied, or the
		 * applied cell style does not define the cell style, then the paragraphs
		 * are left alone.
		 *
		 * @param tableModelRef [IN] the table model
		 * @param whichArea [IN] the <code>GridArea</code> to clear conflicting 
		 * overrides from
		 * @return <code>kSuccess</code> if the conflicting cell overrides were 
		 * cleared, <code>kFailure</code> otherwise
		 */
		virtual ErrorCode ClearCellStyleOverrides(const UIDRef& tableModelRef, 
										 const GridArea& whichArea) const = 0;
		
		
		/**
		 * Clears out all cell attributes from the given cell area.
		 *
		 * @param tableModelRef [IN] the table model
		 * @param whichArea [IN] the <code>GridArea</code> to clear local overrides
		 * from
		 * @return <code>kSuccess</code> if the local overrides were cleared,
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode ClearAllCellOverrides(const UIDRef& tableModelRef, 
										 const GridArea& whichArea) const = 0;
		/**
		 * Gets all the cell styles used in the selected area.  The parameter
		 * <code>out_SelectedStyles</code> will be filled with the styles that
		 * are being used in <code>whichArea</code>, each style will only appear
		 * once.
		 *
		 * @param tableModelRef [IN] the table
		 * @param whichArea [IN] the <code>GridArea</code> to examine
		 * @param out_SelectedStyles [IN] a list containing all the styles
		 * used in the selected area
		 * @return <code>kSuccess</code> if the used styles were returned,
		 * <code>kFailure</code> otherwise
		 */
		virtual ErrorCode GetSelectedCellStyles(const UIDRef& tableModelRef, 
												const GridArea& whichArea, 
												UIDList& out_SelectedStyles) const = 0;

		/**
		 * Clears out the paragraph style cell attribute from the given cell address.
		 *
		 * @param tableModel [IN] the table model
		 * @param whichCell [IN] the <code>GridAddress</code> to clear local overrides
		 * from
		 * @return <code>kTrue</code> if there were any local overrides to be were cleared 
		 * and clearance work done <code>kFalse</code> otherwise
		 */
		virtual bool16 ClearParaStyleOverride(const ITableModel* tableModel,
												const GridAddress& whichCell) const = 0;
	};
}
#endif
