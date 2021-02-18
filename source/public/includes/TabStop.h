//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TabStop.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __TabStop__
#define __TabStop__

#include "WideString.h"
#include "TextChar.h"		// for kTextChar_Period, the default align to char
#include "K2Vector.h"

class IPMStream;

#pragma export on

/** The object representing a tab stop.
*/
class  TabStop
{
	public:
		typedef base_type data_type;

		/** The maximum length of a set of tab leader characters. */
		enum { kMaximumLeaderCount = 8 };

		/** How to align text after the tab. */
		enum TabAlignment
			{ kTabAlignLeft, kTabAlignCenter, kTabAlignRight, kTabAlignChar };

		/** */
		TabStop() :fAlignment(kTabAlignLeft), fActualLeaderCount(0), fDefaultTab(kFalse),
					fLocation(0.0), fAlignToChar(tl_DefaultAlignChar.Get())
			{}

		/** Reset the tab location and leader.  (Alignment remains intact) */
		void Reset()
			{ fLocation = 0.0; fActualLeaderCount = 0; }

		/** */
		void SetPosition(const PMReal& pos)
			{ fLocation = pos; }
		/** */
		void SetAlignment(TabAlignment align)
			{ fAlignment = align; }
		/** Property Accessor for the kTabAlignChar alignment option */
		void SetAlignment(TabAlignment align, UTF32TextChar c)
			{ fAlignment = align; fAlignToChar = c; tl_DefaultAlignChar.Set(c); }

		/**
		@note Leaders can be any string up to kMaximumLeaderCount in length.
		@note A leader that consists of space(s) is ignored. (But spaces may be included with other characters).
		*/
		PUBLIC_DECL void SetLeader(const WideString* leaders = nil);
		void ClearLeader()
			{ fActualLeaderCount = 0; }
		/** */
		const textchar* GetLeaders() const
			{ return fLeaders; }
		/** */
		int16 GetLeaderCount() const
			{ return fActualLeaderCount; }

		/** */
		PMReal GetPosition() const
			{ return fLocation; }
		/** */
		TabAlignment GetAlignment() const
			{ return fAlignment; }
		/** */
		UTF32TextChar GetAlignToChar() const
			{ return fAlignToChar; }

		PUBLIC_DECL void ReadWrite(IPMStream *stream);

		/** @note performs the operation based strictly on the location of the tabstop */
		bool16 operator==(const TabStop& other) const
			{ return fLocation == other.fLocation; }
		/** @note performs the operation based strictly on the location of the tabstop */
		bool16 operator>(const TabStop& other) const
			{ return fLocation > other.fLocation; }
		/** @note performs the operation based strictly on the location of the tabstop */
		bool16 operator<(const TabStop& other) const
			{ return fLocation < other.fLocation; }

		/** Return whether or not this is a default tab (a tab stop not set by the user, but governed by the default tab interval)
		@see ITabSettings
		*/
		bool16 IsDefaultTab() const
			{ return fDefaultTab; }
		/** Set whether or not this is a default tab. */
		void SetDefaultTab( bool16 toDefault = kTrue )
			{ fDefaultTab = toDefault; }

	private:
		textchar				fLeaders[kMaximumLeaderCount];
		PMReal				fLocation;
		TabAlignment			fAlignment;
		int16				fActualLeaderCount;
		UTF32TextChar		fAlignToChar;
		bool16				fDefaultTab;

		PUBLIC_DECL static IDThreading::ThreadLocal<UTF32TextChar>	tl_DefaultAlignChar;
};


/** The table of tab stops for this paragraph.
*/
class TabStopTable
{
public:
	typedef const TabStop* 			const_iterator;

		/** */
	 PUBLIC_DECL TabStopTable();

	/** Get the default interval between tabs.
	*/
	PUBLIC_DECL PMReal GetDefaultTabInterval() const;

	/** Find the first tab stop after the given offset, if any.
	@return nil if there are no default and other tabs.
	*/
	PUBLIC_DECL const TabStop* GetTabStopAfter( PMReal offset ) const;

	/** */
	inline int32 size() const
		{ return fSortedTable.size(); }
	/** */
	inline void clear()
		{ fSortedTable.clear(); }

	/** */
	const TabStop* begin() const
		{ return fSortedTable.begin(); }
	/** */
	const TabStop* end() const
		{ return fSortedTable.end(); }

	/** */
	inline const TabStop& operator[] (int32 index) const
		{ return fSortedTable.operator[] (index); }

	/** Insert the given tab stop.  If the tab stop is not a default tab, it will replace all prior default tabs. */
	PUBLIC_DECL void Insert(const TabStop& stop);

	/** Remove the tabstop at the given index */
	inline void Remove(int32 index)
		{ fSortedTable.erase(fSortedTable.begin() + index); }

	PUBLIC_DECL void ReadWrite(IPMStream *stream);

protected:
	/** The table of tab stops, sorted by position. */
	K2Vector<TabStop>		fSortedTable;
	/** A tab stop that is (re)used each time a default tab should be returned.  The position is updated each time. */
	TabStop					fDefaultTab;
	/** Cached value of the current document settings.
	@see ITabSettings
	*/
	PMReal					fDefaultTabInterval;
};

#pragma export off

#endif
		//__TabStop__
