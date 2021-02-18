//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellStyleSuite.h $
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

#ifndef ICELLSTYLESUITE_H
#define ICELLSTYLESUITE_H

#include "IPMUnknown.h"

#include "CelStyID.h"

class AttributeBossList;
class GridArea;

/**
 * Suite for cell styles.  To obtain an instance of this suite:<BR>
 * <code>ISelectionManager* selMgr = activeContext->GetContextSelection();</code>
 * <BR>
 * <code>InterfacePtr<ICellStyleSuite> stylesSuite(static_cast<ICellStyleSuite*>(selMgr->QueryIntegratorSuite(IID_ICELLSTYLESUITE, ISelectionManager::kEnabledInterface)));</code>
 */
class ICellStyleSuite : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ICELLSTYLESUITE};
	
	/**
	 * Tests if a new cell style can be created.
     *
     * @return <code>kTrue</code> if a cell style can be created, 
	 * <code>kFalse</code> otherwise
     */
	virtual bool16 CanCreateCellStyle() const = 0;
    
	/**
     * Creates a new cell style.  If there is an active table selection and a 
	 * single cell style is selected, then the new style will be based on that 
	 * single cell style and its attributes will be the overrides of the top 
	 * left cell of the selection.  If there is no table selection the 
	 * <code>basedOn</code> parameter will be used as the parent.
     *
     * @precondition <code>CanCreateCellStyle</code> returns <code>kTrue</code>
	 * @param parentHier [IN] optional, the parent hierarchy for the style, if
	 * this is not provided, the parent becomes the root hierarchy
	 * @param position [IN] optional, the position for the new style within the
	 * parent hierarchy
     * @param basedOn [IN] optional, the style the new style should be based on, 
	 * this is only used if there is no table selection
     * @return <code>kSuccess</code> if a new cell style was created, 
	 * <code>kFailure</code> otherwise
     */
	virtual ErrorCode CreateCellStyle(const UID* parentHier = nil, 
		const int32 position = -1, 
		const UID* basedOn = nil) = 0;
    
	/**
	 * Tests if the current selection supports the "Break Link with Style" 
	 * action. For this to be true, there must be a table selection, or a text
	 * selection within a table, and the style of that cell selection must not 
	 * be the root cell style.
     *
     * @return <code>kTrue</code> if the break link with style command is 
	 * available, <code>kFalse</code> otherwise
     */
	virtual bool16 CanBreakLinkWithCellStyle() const = 0;
    
	/**
	 * Breaks the link with the cell style for the currently selected cell area.
	 * Any cell style attributes are applied as local overrides.  If there are 
	 * any conflicts between the style attributes and local overrides, the local
	 * overrides always win.  The root style is applied to all selected cells.
     *
     * @precondition <code>CanBreakLinkWithCellStyle</code> returns 
	 * <code>kTrue</code>
     * @return <code>kSuccess</code> if the link between the cells and style was
     * successfully broken, <code>kFailure</code> otherwise
     */
	virtual ErrorCode BreakLinkWithCellStyle() const = 0;
    
	/**
	 * Tests if a cell style can be applied.  If there is no table selection,
	 * this will still return true, but "applying" a cell style means the 
	 * default style is set.
     *
     * @return <code>kTrue</code> if a cell style can be applied, 
	 * <code>kFalse</code> otherwise
     */
	virtual bool16 CanApplyCellStyle() const = 0;
    
	/**
	 * Overloaded version of this function, this will only set the default
	 * cell style if <code>whichStyle</code> is not already the
	 * default style, or if the applying the cell style will change the 
	 * appearance of the selection.
	 *
	 * @param whichStyle [IN] the style to try to apply
	 * @return <code>kTrue</code> if applying the style will either change
	 * the default style, or change the attributes displayed in the table,
	 * <code>kFalse</code> otherwise
	 */
	virtual bool16 CanApplyCellStyle(const UID& whichStyle) const = 0;
	
	/**
	 * Applies the given cell style to the current cell selection.  If 
     * local overrides exist on any of the cells in the selection they
     * will be removed if <code>removeOverrides</code> is <code>kTrue</code>.  
	 * If there is no table selection, the default style is set to 
	 * <code>cellStyle</code> and the <code>removeOverrides</code> parameter is 
	 * ignored.
     *
     * @precondition <code>CanApplyCellStyle</code> returns <code>kTrue</code>
     * @param cellStyle [IN] the cell style to apply to the cell selection
     * @param removeOverrides [IN] optional, <code>kTrue</code> if the local 
	 * overrides should  be removed from the cell, <code>kFalse</code> otherwise
     * @return <code>kSuccess</code> if the style was successfully applied,
	 * <code>kFailure</code> otherwise
     */
	virtual ErrorCode ApplyCellStyle(const UIDRef& cellStyle,
									 const bool16 removeOverrides = kFalse) const = 0;
    
	/**
	 * Applies the given cell style and clears out any overrides in the
	 * selected area.
	 *
	 * @precondition <code>CanApplyCellStyle</code> returns <code>kTrue</code>
	 * @precondition <code>CanGetAllOverrides</code> returns <code>kTrue</code>
	 * @param cellStyle [IN] the cell style to apply to the cell selection
     * @return <code>kSuccess</code> if the style was successfully applied,
	 * <code>kFailure</code> otherwise
	 */
    virtual ErrorCode ApplyCellStyleAndClearAllFormatting(const UIDRef& cellStyle) const = 0;
	
	/**
	 * Tests if there exists a table selection.
	 *
	 * @return <code>kTrue</code> if there is a table selection,
	 * <code>kFalse</code> otherwise
     */
	virtual bool16 CanGetCellStyle() const = 0;
    
	/**
	 * Gets the cell styles of the selection.  The selection may contain 
	 * multiple cell styles, so we return all of them.  The parameter 
	 * <code>out_SelectedStyles</code> will contain each cell style used in the 
	 * selection exactly once.
     * 
     * @precondition <code>CanGetCellStyle</code> returns <code>kTrue</code>
     * @param out_SelectedStyles [OUT] a list containing all the styles used in
	 * the selection
     * @return <code>kSuccess</code> if the UIDs of selected cells style(s) were
	 * returned in <code>out_SelectedStyles</code>, <code>kFailure</code>
	 * otherwise
     */
	virtual ErrorCode GetSelectedCellStyles(UIDList& out_SelectedStyles) const = 0;
    
    /**
     * Tests if the table selection is in exactly one cell that contains
     * paragraph styles other than the one defined in the given cell style.
     * If the cell style is the root cell style, or if the cell style's 
	 * paragraph style is undefined, this function will return 
	 * <code>kFalse</code>.
     *
     * @return <code>kTrue</code> if there is a single cell selected with 
	 * paragraph overrides, <code>kFalse</code> otherwise
     */
    virtual bool16 CanGetOverridingParagraphStyles() const = 0;
    
    /**
     * Returns a list of all paragraph styles used within a cell that does not 
	 * match the paragraph style defined in the cell style.
     *
     * @precondition <code>CanGetOverridingParagraphStyles</code> returns 
	 * <code>kTrue</code>
     * @param out_OverridingParaStyles [OUT] a <code>UIDList</code> for storing 
	 * the paragraph style overrides
     * @return <code>kSuccess</code> if the paragraph overrides were retrieved, 
	 * <code>kFailure</code> otherwise
     */
    virtual ErrorCode GetOverridingParagraphStyles(UIDList& out_OverridingParaStyles) const = 0;
    
	/**
	 * Tests if we can redefine the current cell style.  For this
     * to return true, there must be a single cell selected that
     * has both an editable cell style and local cell overrides.  This will
	 * also be enabled if either the cell style defines a paragraph style that
	 * is overridden, or the cell style does not define a paragraph style at
	 * all.
     *
     * @return <code>kTrue</code> if the "Redefine Cell Style" operation is
     * permitted, <code>kFalse</code> otherwise
     */
	virtual bool16 CanRedefineCellStyle() const = 0;
    
	/**
	 * Redefines the cell style of the given selection.  The style will
	 * have the selection's local overrides added to its attributes, with local
	 * overrides overwriting any current style attributes.  Additionally, the
	 * first paragraph style used in the cell will be used as the paragraph
	 * style for the cell style.
     *
     * @precondition <code>CanRedefineCellStyle</code> returns 
	 * <code>kTrue</code>
     * @return <code>kSuccess</code> if the cell style was redefined,
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode RedefineCellStyle() const = 0;
    
	/**
	 * Tests if we can clear overrides.  For this to return
     * <code>kTrue</code>, a cell or cells must be selected that have
     * local overrides that conflict with the style's definition or
	 * any override when the style is the root cell style.
     *
	 * @param styleToCheck [IN] optional if we apply this style, are there overrides
	 * of this style on the selected style that can be cleared? If
	 * set to its default, <code>UIDRef::gNull</code>, we check against the 
	 * style currently applied to the selection.
     * @return <code>kTrue</code> if the "Clear Cell Overrides" operation
     * is permitted, <code>kFalse</code> otherwise
     */
	virtual bool16 CanClearOverrides(const UIDRef& styleToCheck = UIDRef::gNull) const = 0;
    
	/**
	 * Tests if there are any cell overrides that can be cleared on the
	 * given selection.
	 *
	 * @return <code>kTrue</code> if there are any cell overrides on the
	 * current selection
	 */
	virtual bool16 CanClearAllOverrides() const = 0;
	
	/**
	 * Clears out all cell overrides from the given selection.
	 *
	 * @return <code>kSuccess</code> if the overrides were cleared,
	 * <code>kFailure</code> otherwise
	 */
	virtual ErrorCode ClearAllOverrides() const = 0;
	
	/**
	 * Clears cell overrides from the given selection that conflict with
	 * the applied style's definition.  If the applied style is the root
	 * cell style, then all overrides will be cleared.
     *
     * @precondition <code>CanClearOverrides</code> returns <code>kTrue</code>
     * @return <code>kSuccess</code> if the cell overrides were cleared, 
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode ClearOverrides() const = 0;

	 /**
     * Gets the local cell overrides applied on the selected table.  
	 * Since there can be multiple cells selected, each with different
	 * overrides, the parameter <code>out_IsMixed</code> can be used to
	 * determine if there are mixed overrides on the selection.  This
	 * function will always return the overrides applied to the first
	 * cell of the selection.
     *
     * @precondition <code>CanGetCellStyleOverrides</code> returns <code>kTrue</code>
     * @param outLocalOverrides [OUT] the local overrides applied to the
     * selected table
	 * @param out_IsMixed [OUT] optional, if this is not nil, then entire
	 * selected area will be examined to see if all the overrides are equivalent
     * @return <code>kSuccess</code> if the overrides were returned,
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode GetLocalOverrides(AttributeBossList& outLocalOverrides, 
		bool16* out_IsMixed = nil) const = 0;
		
	/**
	 * Tests if the current selection has any overrides that intersects with
	 * the style's definition.
	 *
	 * @return <code>kTrue</code> if the selection contains any overrides that
	 * intersects with the style's definition
	 */
	virtual bool16 CanGetCellStyleOverrides() const = 0;
	
	/**
	 * Tests if the current selection has any overrides.
	 *
	 * @return <code>kTrue</code> if the selection contains any overrides
	 */
	virtual bool16 CanGetAllOverrides() const = 0;
	
	/**
     * Gets all cell overrides from the first cell selected in the table.
     *
     * @precondition <code>CanGetAllOverrides</code> returns <code>kTrue</code>
     * @param outLocalOverrides [OUT] the local overrides applied to the
     * first cell of the selected table
     * @return <code>kSuccess</code> if the overrides were returned,
     * <code>kFailure</code> otherwise
     */
	virtual ErrorCode GetAllOverrides(AttributeBossList& outLocalOverrides) const = 0;
};

#endif
