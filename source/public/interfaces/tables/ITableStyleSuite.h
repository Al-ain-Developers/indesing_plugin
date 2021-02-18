//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableStyleSuite.h $
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

#ifndef ITABLESTYLESUITE_H
#define ITABLESTYLESUITE_H

#include "IPMUnknown.h"

#include "TabStyID.h"

class AttributeBossList;
class GridArea;

/**
 * Suite for table styles.  To obtain an instance of this suite:<br>
 * <code>ISelectionManager* selMgr = activeContext->GetContextSelection();</code>
 * <code>InterfacePtr<ITableStyleSuite> stylesSuite(static_cast<ITableStyleSuite*>(selMgr->QueryIntegratorSuite(IID_ITABLESTYLESUITE, ISelectionManager::kEnabledInterface)));</code>
 */
class ITableStyleSuite : public IPMUnknown
{
public:
	
	enum {kDefaultIID = IID_ITABLESTYLESUITE};
    
	/**
	 * Overloaded version of this function, this will only set the default
	 * cell style if <code>whichStyle</code> is not already the
	 * default style, or if the style of the current table selection is not
	 * already <code>whichStyle</code>
	 *
	 * @param whichStyle [IN] the style to try to apply
	 * @return <code>kTrue</code> if applying the style will either change
	 * the default style, or change the attributes displayed in the table,
	 * <code>kFalse</code> otherwise
	 */
	virtual bool16 CanApplyTableStyle(const UID& whichStyle) const = 0;
	
	/**
	 * Checks if table/cell styles are active.  This will return
	 * <code>kFalse</code> only when there is a text selection that is not
	 * within a table.
	 *
	 * @return <code>kTrue</code> if table styles are enabled,
	 * <code>kFalse</code> otherwise
	 */
	virtual bool16 AreTableStylesEnabled() const = 0;
	
    /**
     * Checks if there is a table selection such that regional cell styles can
     * be retrieved.
     *
     * @return <code>kTrue</code> if there is a table selection,
     * <code>kFalse</code> otherwise
     */
    virtual bool16 CanGetSelectedRegionalCellStyles() const = 0;
    
    /**
     * Gets the list of all selected regional cell styles.
     *
	 * @precondition <code>CanGetSelectedRegionalCellStyles</code> returns 
	 * <code>kTrue</code>
     * @param out_SelectedStyles [IN] the cell styles in the selection
     * @return <code>kSuccess</code> if the regional styles were retrieved,
	 * <code>kFailure</code> otherwise
     */
    virtual ErrorCode GetSelectedRegionalCellStyles(UIDList& out_SelectedStyles) const = 0;
    
	/**
	 * Tests if a table style can be applied.  If there is no table selection,
	 * this will still return true, but "applying" a table style means the 
	 * default style is set.
     *
     * @return <code>kTrue</code> if a table style can be applied, 
	 * <code>kFalse</code> otherwise
     */
	virtual bool16 CanApplyTableStyle() const = 0;
    
	/**
     * Applies the given table style to the current table selection.  If
     * local overrides exist on the current table, they will be deleted if
     * <code>removeOverrides</code> is kTrue, otherwise they will be
     * preserved.  If there is no selection that a table style can be applied
     * to, this function will simply set the default table style.  If
	 * <code>removeCellStyle</code> is true, then all the cell styles on the
	 * table will be removed.
     *
	 * @precondition <code>CanApplyTableStyle</code> returns <code>kTrue</code>
     * @param tableStyleRef [IN] the table style to apply to the table
     * @param removeOverrides [IN] optional,  <code>kTrue</code> if the local 
	 * overrides should be removed from the table, <code>kFalse</code> otherwise
     * @param removeCellStyle [IN] optional, flag for removing cell styles from 
	 * the entire table
     * @return <code>kSuccess</code> if the style was successfully applied to 
	 * the current table selection, <code>kFailure</code> otherwise
     */
	virtual ErrorCode ApplyTableStyle(const UIDRef& tableStyleRef,
									  const bool16 removeOverrides = kFalse, 
									  const bool16 removeCellStyle = kFalse) const = 0;
    
	/**
     * Tests if the current table selection has local overrides that can
	 * be cleared.
     *
     * @return <code>kTrue</code> if the current table selection has local 
	 * overrides that can be cleared, <code>kFalse</code> otherwise
     */
	virtual bool16 CanClearOverrides() const = 0;
    
	/**
     * Clears any local table overrides from the current table selection.
	 *
	 * @precondition <code>CanClearOverrides<code> returns <code>kTrue</code>
	 * @param clearCellStyles [IN] optional, set to <code>kTrue</code> to
	 * clear all cell style formatting
	 * @return <code>kSuccess</code> if the local overrides were cleared, 
	 * <code>kFailure</code> otherwise
	 */
	virtual ErrorCode ClearLocalOverrides(const bool16 clearCellStyles = kFalse) const = 0;
    
	/**
	 * Tests if we can perform a break link with style.  For this to be true, 
	 * the selection must not use the root table style
     *
     * @return <code>kTrue</code> if a break link with style can be performed,
	 * <code>kFalse</code> otherwise
     */
	virtual bool16 CanBreakLinkWithStyle() const = 0;
    
	/**
     * Break link with style will take all the table style attributes and apply
	 * them as local overrides, if any conflicts arise with existing local 
	 * overrides, the existing local overrides are preserved.  The root table 
	 * style is then applied.
     *
	 * @precondition <code>CanBreakLinkWithStyle</code> returns
	 * <code>kTrue</code>
     * @return <code>kSuccess</code> if the link between the table and style was
     * successfully broken, <code>kFailure</code> otherwise
     */
	virtual ErrorCode BreakLinkWithTableStyle() const = 0;
    
	/**
     * Tests if we can get a table style from the current selection.  This
     * function will return <code>kTrue</code> if the current selection is any 
	 * type of table selection, or if the current selection is a text selection
     * within a table.
     *
     * @return <code>kTrue</code> if a table style can be obtained from the 
	 * current selection, <code>kFalse</code> otherwise
     */
	virtual bool16 CanGetTableStyle() const = 0;
    
	/**
	 * Gets the table style of the current table selection.
     *
	 * @precondition <code>CanGetTableStyle</code> returns <code>kTrue</code>
     * @param out_UID [OUT] the style of the table
     * @return <code>kSuccess</code> if the UID of table's style was 
	 * successfully placed in <code>out_UID</code>, <code>kFailure</code> 
	 * otherwise
     */
	virtual ErrorCode GetSelectedTableStyle(UID& out_UID) const = 0;
    
	/**
	 * Tests the current table style can be redefined.  For this
     * to return true, there must be a table selected that
     * has both an editable table style and local overrides.
     *
     * @return <code>kTrue</code> if the "Redefine Table Style" operation is
     * permitted, <code>kFalse</code> otherwise
     */
	virtual bool16 CanRedefineTableStyle() const = 0;
    
	
	/**
	 * Tests if the selected table has any local cell style formatting
	 * anywhere in the table, ie. has a cell style applied other than
	 * the root cell style (or <code>kInvalidUID</code>, which is synonymous
	 * with the root cell style).
	 *
	 * @return <code>kTrue</code> if the table has any cell style applied to it
	 * other than the root cell style, <code>kFalse</code> otherwise
	 */
	virtual bool16 CanClearLocalCellStyleFormatting() const = 0;
	
    /**
	 * Redefines the table style of the given selection.  The style will
	 * have the selection's local overrides added to its attributes, with local
	 * overrides overwriting any current style attributes.
     *
     * @precondition <code>CanRedefineTableStyle</code> returns 
	 * <code>kTrue</code>
     * @return <code>kSuccess</code> if the table style was redefined,
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode RedefineStyle() const = 0;
    
    /**
	 * Tests if a new table style can be created.
	 *
	 * @return <code>kTrue</code> if a table style can be created,
	 * <code>kFalse</code> otherwise
	 */
	virtual bool16 CanCreateTableStyle() const = 0;
	
	/**
	 * Creates a new table style.
	 *
	 * @precondition <code>CanCreateTableStyle</code> returns <code>kTrue</code>
	 * @param parentHier [IN] optional, the parent hierarchy for the style
	 * @param position [IN] optional, the position for the new style within the
	 * parent hierarchy
	 * @param basedOn [IN] optional, the style the new style should be based on,
	 * this is only used if there is no table selection
	 * @return <code>kSuccess</code> if the table style was created,
	 * <code>kFailure</code> otherwise
	 */
	virtual ErrorCode CreateTableStyle(const UID* parentHier = nil, 
		const int32 position = -1, 
		const UID* basedOn = nil) = 0;
	
	/**
	 * Tests if the given table selection has any table overrides.
	 *
	 * @return <code>kTrue</code> if the current selection has any table overrides,
	 * <code>kFalse</code> otherwise
	 */
	virtual bool16 CanGetOverrides() const = 0;
	
    /**
     * Gets the local overrides applied to the selected table.
     *
     * @precondition <code>CanGetOverrides</code> returns <code>kTrue</code>
     * @param outLocalOverrides [OUT] the local overrides applied to the
     * selected table
     * @return <code>kSuccess</code> if the overrides were returned,
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode GetLocalOverrides(AttributeBossList& outLocalOverrides) const = 0;
};

#endif

