//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextColumnSizer.h $
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


#pragma once
#ifndef __ITextColumnSizer__
#define __ITextColumnSizer__

#define kIgnoreFlexibleColumnValue		0.0

#ifndef __ODFRC__   // when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "PMRect.h"
#include "TextID.h"
#include "UIDList.h"

class ITextFrameColumn;

/**
	Interface to manage columns within a text frame.

	@note Only applies to a multi-column frame boss with a
	IMultiColumnTextFrame interface. This object (the multi-column frame) is a 
	for columns. Each column also supports the ITextFrameColumn interface. The
	columns also appear in the associated frame list (IFrameList).
	See the Programming Guide for more information on the text frame hierarchy.

	@ingroup text_layout
*/
class ITextColumnSizer : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTCOLUMNSIZER };

		/**
			This is the minimum width and height a text frame can be set to.
			Prior to CS4 this was set to 12 but it was easy to specify a J
			FrameGrid based on a point size of 9. The value here is somewhat
			arbitrary - it needs to be greater than one in order to avoid
			problems with loaded placeguns which have a spline size of 1x1.
		 */
		enum minimumColumnWidth { kMinimumValidInUIColumnWidth = 3};
		enum minimumColumnHeight { kMinimumValidInUIColumnHeight = 3};

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
		virtual void UseFixedColumnSizing(bool16 fixedSize = kTrue) = 0;

		/**
			Check whether or not the columns are a fixed size or not.
		 */
		virtual bool16 IsFixedColumnSizing() const = 0;

		/**
			Set the width of the (fixed) column(s).

			@note valid with fixed column sizes only
		 */
		virtual void SetFixedWidth(PMReal width) = 0;

		/**
			Get the width of the (fixed) column(s).

			@note valid with fixed column sizes only
		 */
		virtual PMReal GetFixedWidth() const = 0;

		/**
			Set the height of all column(s).
		*/
		virtual void SetHeight(PMReal height) = 0;

		/**
			Get the height of all column(s).
		*/
		virtual PMReal GetHeight() const = 0;

		/**
			Set whether or not the columns should use the min and max sizes or not.
		 */
		virtual void UseFlexibleColumnSizing(bool16 flexibleSize = kTrue) = 0;

		/**
			Check whether or not the columns are a flexible size or not.
		 */
		virtual bool16 IsFlexibleColumnSizing() const = 0;

		/**
			Set the maximum width of the column(s).

			@note valid with flexible column sizing only
		 */
		virtual void SetFlexibleWidthMax(PMReal maxWidth) = 0;

		/**
			Get the min width of the flexible-sizing column(s).

			@note valid with flexible column sizes only
		 */
		virtual PMReal GetFlexibleWidthMax() const = 0;
};

#endif  // __ODFRC__

#endif // __ITextColumnsizer__
