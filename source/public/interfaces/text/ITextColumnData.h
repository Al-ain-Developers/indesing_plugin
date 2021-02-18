//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextColumnData.h $
//  
//  Owner: Kevin Van Wiel
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

#include "IPMUnknown.h"
#include "PMRect.h"
#include "TextID.h"
#include "UIDList.h"

#pragma once
#ifndef __ITextColumnData__
#define __ITextColumnData__

/**
	Interface to manage columns within a text frame.

	@note Only applies to a multi-column frame boss. That boss also supports the IMultiColumnTextFrame interface. This object (the multi-column frame)
	is a container for columns. Each column also supports the ITextFrameColumn interface. The columns also appear in the associated frame
	list (IFrameList). See the Programming Guide for more information on the text frame hierarchy.

	@ingroup text_layout
*/
class ITextColumnData : public IPMUnknown		// ##rk: replace as default Impl for ITextColumnManager (ITextColumnProvider)?
{
public:
		enum { kDefaultIID = IID_ITEXTCOLUMNDATA };

		/**
			Set the number of columns in the frame (default parameter of 1 column)
		 */
		virtual void SetNumberOfColumns(int32 columns = 1) = 0;

		/**
			Get the number of columns in the frame.
		 */
		virtual int32 GetNumberOfColumns() const = 0;

		/**
			Get the gutter width for the frame.
		 */
		virtual PMReal GetGutterWidth() const = 0;

		/**
			Set the gutter width for the frame.
		 */
		virtual void SetGutterWidth(PMReal width) = 0;

		/**
			Set whether or not the columns should be a fixed size or not.
		 */
		virtual void UseFixedColumnSizing(int16 fixedSize = kTrue) = 0;

		/**
			Check whether or not the columns are a fixed size or not.
		 */
		virtual int16 IsFixedColumnSizing() const = 0;

		/**
			Set the width of the (fixed) column(s).

			@note valid with fixed column sizes only
		 */
		virtual void SetFixedWidth(const PMReal &width) = 0;

		/**
			Get the width of the (fixed) column(s).

			@note valid with fixed column sizes only
		 */
		virtual PMReal GetFixedWidth() const = 0;

		/**
			Set the height of all column(s).
		 */
		virtual void SetHeight(const PMReal &height) = 0;

		/**
			Get the height of the column(s).
		 */
		virtual PMReal GetHeight() const = 0;

		/**
			Set whether or not the columns should be a flexible size or not.
		 */
		virtual void UseFlexibleColumnSizing(int16 flexibleSize = kTrue) = 0;

		/**
			Check whether or not the columns are a flexible size or not.
		 */
		virtual int16 IsFlexibleColumnSizing() const = 0;

		/**
			Set the maximum width of a column.

			@note valid with flexible column sizes only
		 */
		virtual void SetFlexibleWidthMax(const PMReal &max) = 0;

		/**
			Get the maximum width of a column(s).

			@note valid with flexible column sizes only
		 */
		virtual PMReal GetFlexibleWidthMax() const = 0;
};

#endif // __ITextColumnsizer__
