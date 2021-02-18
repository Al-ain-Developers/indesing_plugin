//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITabRulerData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ITabRulerData__
#define __ITabRulerData__

#include "IPMUnknown.h"
#include "TabStop.h"
#include "K2Vector.h"
#include "ICompositionStyle.h"

//---------------------------------------------------------------
// Interface ITabRulerData
//---------------------------------------------------------------

class PMPoint;
class PMMatrix;
class TabStopTable;
class TabRulerItem;					// ##rk: This class is not public.
class TabRulerItemTable;			// ##rk: This class is not public.

const PMReal 	kTabRulerUnclearIndent = -1.0;


// @see TabRulerItem, TabRulerItemTable
/** Interface for working with the Tab Ruler.  Provides access to the TabStopTable, individual tab stops, margins and various other tab properties.
	@ingroup text_tab
	@see TabStopTable
*/
class ITabRulerData : public IPMUnknown
{
public:
			/**  the tabstate is used for displaying the tabstops. kMulti is for ambiguous selections. */
	enum		TabState { kOff, kOn, kMulti, kDragged, kSelected };
	virtual	void					SetTabStopTable( const TabStopTable &rTable ) = 0;
	virtual	bool16				GetTabStopTable( TabStopTable *pTable ) const = 0;

			/**  selects the nth tabstop of the TabStopTable. */
	virtual	void					SelectItem( const TabRulerItem *pItem ) = 0;
			/**  get the currently selected item (previously set by SelectItem) */
	virtual	const TabRulerItem*		GetSelectedItem() const = 0;
			/**  returns the selected item corresponding to the selected tabstop ##rk: */
	virtual	const TabRulerItem *	GetSelectedTabStop() const = 0;
			/**  get the tabstop at a position */
	virtual	const TabRulerItem*		GetTabRulerItem( const PMPoint &rPoint  ) const = 0;

			//  sets a new (already initialized) tabstop. A nil clears the new tabstop. */
			//  returns kFalse if the new tabstop does not keep the kMinTabDistance to its neighbors. */
	virtual	bool16				SetNewTabStop( const TabRulerItem &rNewTabStop, bool16 bSelect = kTrue, TabStopTable *pDeleted = nil ) = 0;
			/**  returns a tabstop for a position. */
	virtual	const TabRulerItem *	GetTabStopAt( PMReal nPosition ) const = 0;
			/**  moves an item to a new position. It only redraws if bDraw. It also returns the deleted tabstop. */
	virtual	bool16				MoveTabRulerItem(  const TabRulerItem &rItem, PMReal nNewPosition, bool16 bDraw = kTrue, TabStopTable *pDeleted = 0, bool16 bConstrainLeftIndent = kTrue ) = 0;
	virtual	bool16				RemoveTabStop( const TabRulerItem &rStop ) = 0;
	virtual	void					SetDefaultTabAlignment( TabStop::TabAlignment nAlignment ) = 0;
	virtual	TabStop::TabAlignment	GetDefaultTabAlignment() const = 0;
			/**  @note this only applies if the TabAlignment is kTabAlignChar */
	virtual	void					SetDefaultTabAlignChar( textchar c ) = 0;
			/**  @note this only applies if the TabAlignment is kTabAlignChar */
	virtual	textchar				GetDefaultTabAlignChar() const = 0;
		/** @see TabStop::SetLeader for details on leaders */
	virtual void					SetDefaultTabLeader(PMString string) = 0;
	virtual PMString				GetDefaultTabLeader() const = 0;
			/**  returns kTrue if you can place a new tab at that position. ##rk: as opposed to a default position? only kFalse if an existing tab is there? */
	virtual	bool16				IsNewTabPosition( PMReal nPosition ) const = 0;

	virtual	bool16 				SetFirstIndent( PMReal nNewFirst, bool16 bConstrainedByLeftIndent = kTrue ) = 0;
	virtual	PMReal 				GetFirstIndent() const = 0;
	virtual	bool16 				SetLeftIndent( PMReal nNew, bool16 bConstrainLeftIndent = kTrue ) = 0;
	virtual	PMReal 				GetLeftIndent() const = 0;
	virtual	bool16 				SetRightIndent( PMReal nNew ) = 0;
	virtual	PMReal 				GetRightIndent() const = 0;
	virtual	bool16 				SetLeftMargin( PMReal nNew ) = 0;
	virtual	PMReal 				GetLeftMargin() const = 0;
	virtual	bool16 				SetRightMargin( PMReal nNew ) = 0;
	virtual	PMReal 				GetRightMargin() const = 0;

			/**  the scaling has to be set independently because we have to draw in pixel device and the TextRuler cannot use a IPanorama
			@see TextRulerObserver.cpp . */
	virtual	void					SetScale( PMReal nScale ) = 0;
	virtual	PMReal				GetScale() const = 0;

			/**  sets and returns pMatrix, the matrix is used for hit testing and drawing of the TabRulerItem. */
	virtual	const PMMatrix &		GetTabRulerItemMatrix( PMMatrix *pMatrix ) const = 0;
			/**  returns kFalse if no item is selected. */
	virtual	bool16				RepeatTab() = 0;

			/**  show the original position */
	virtual	void					SetDragItem( const TabRulerItem *pItem ) = 0;
	virtual	const TabRulerItem *	GetDragItem() const = 0;

			/**  sets the TabRulerItem table. */
	virtual	void					SetTabRulerItemTable( const TabRulerItemTable &rTable ) = 0;
			/**  returns the TabRulerItem table. */
	virtual	const TabRulerItemTable &GetTabRulerItemTable() const = 0;

	/** @see TabStop::GetTabStopAfter()
	*/
	virtual	const TabRulerItem *	GetTabStopAfter( PMReal nPosition ) const = 0;

	/** for right-to-left versus left-to-right paragraphs -- tab locations are relative to the primary writing direction.
	*/
	virtual void						SetParagraphDirection(ICompositionStyle::ParagraphDirection nVal) = 0;
	/** for right-to-left versus left-to-right paragraphs -- tab locations are relative to the primary writing direction.
	*/
	virtual ICompositionStyle::ParagraphDirection	GetParagraphDirection() const = 0;

	virtual void		SetDiffFrames(PMReal diff) = 0;
	virtual PMReal		GetDiffFrames() const = 0;

	virtual void		SetFrameBoxWidth(PMReal width) = 0;
	virtual PMReal		GetFrameBoxWidth() const = 0;

};

DECLARE_BASE_TYPE(ITabRulerData::TabState);

const PMReal kTabRulerDefaultRightMargin = 216.0;

#endif
