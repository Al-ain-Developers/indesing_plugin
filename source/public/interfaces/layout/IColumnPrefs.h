//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IColumnPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IColumnPrefs__
#define __IColumnPrefs__

#include "IPMUnknown.h"
#include "IColumns.h"
#include "SpreadID.h"

	/** Interface to column preferences for document or application.

		@author Paul Sorrick
		@ingroup layout_column
		@see IColumn
		@see kDocWorkspaceBoss
		@see kWorkspaceBoss
		@see kSetColumnPrefsCmdBoss 

	*/
class IColumnPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ICOLUMNPREFERENCES };

	/**	Set the default number of columns per page.
		@param numColumns 
	 */
	virtual void SetNumColumns(const int32& numColumns) = 0;

	/**	Get the number of columns. Will be at least 1.
		@return int32
	 */
	virtual int32 GetNumColumns() = 0;

	/**	Set the default gutter value (in points).
		@param gutter the PMReal value to use.
	 */
	virtual void SetGutter(const PMReal& gutter) = 0;

	/**	Get the gutter value (in points). This is the space between adjacent columns.
		Must have 2 or more columns for the gutter value to actually matter since one column won't have a gutter.
		@return PMReal the gutter value for the columns use.
	 */
	virtual PMReal GetGutter() = 0;

	/**	Set the default column direction (J feature set). kTrue == vertical, kFalse == horizontal.
		@param direction kTrue for J columns, kFalse for Roman style. 
	 */
	virtual void SetColumnOrientation_2( IColumns::ColumnOrientation direction) = 0;

	/**	Get the default column direction for columns on page (J feature set). kTrue == vertical, kFalse == horizontal.
		@return bool16 kTrue for J columns, kFalse for Roman style.
	 */
	virtual IColumns::ColumnOrientation GetColumnOrientation_2() = 0;

	/**	Set the UI color by UID for the columns.
		@param uiColorUID the UID of the UI color to use for drawing the column lines.
		@see IUIColorUtils.h
	 */
	virtual void SetColor(const UID uiColorUID) = 0;

	/**	Get the UIColorRef for the columns to be drawn with.
		@return UIDRef of the color to use.
		@see IUIColorUtils.h
	 */
	virtual UIDRef GetColor() = 0;

	/**	Set whether columns are locked (kTrue) or not (kFalse). When locked, prevents user from dragging with the pointer tool.
		@param bLocked a bool16 value (kTrue or kFalse)
	 */
	virtual void SetLocked(const bool16 bLocked) = 0;

	/**	Get if columns are locked (kTrue) or not (kFalse). When locked, prevents user from dragging with the pointer tool.
		@return bool16 the lock state
	 */
	virtual bool16 GetLocked() = 0;

	/**	Get the lock state for the columns. DO NOT USE, used for conversion only.
	 */
	virtual bool16 GetLocked_DURING_CONVERSION_ONLY() = 0;

	/**	Get the UI color index for the columns. DO NOT USE, used for conversion only.
		@return int32 index of the color in the IID_IUICOLORLIST.
	 */
	virtual int32 GetColorIndex_DURING_CONVERSION_ONLY() = 0;


};

#endif
