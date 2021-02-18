//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IWarichuStyle.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IWarichuStyle__
#define __IWarichuStyle__


#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "CJKID.h"


/**
	IWarichuStyle is one of the interfaces hanging off the kComposeStyleBoss object.
	As such, it is easily Queried from an IDrawingStyle interface.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text. IWarichuStyle lists character attributes
	associated with the Japanese Warichuu feature.
	IWarichuStyle should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves are the primary setters of the data.
	@see IDrawingStyle
	@see IMojikumiStyle
	@ingroup text_comp_style
*/
class IWarichuStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWARICHUSTYLE };

		// Warichu attributes

		/**	Turns Warichuu on or off
			@param flag 
		 */
		virtual void SetWarichuFlag(bool16 flag) = 0;

		/**	Accesses whether Warichuu is on or off
			@param none
			@return bool16 
		 */
		virtual bool16 GetWarichuFlag() const = 0;


		/**	Sets the number of warichuu lines
			@param num 
		 */
		virtual void SetWarichuNumOfLines(int16 num) = 0;

		/**	Gets the number of warichuu lines
			@param none
			@return int16 
		 */
		virtual int16 GetWarichuNumOfLines() const = 0;


		/**	Sets the relative size (e.g. 50% scale = 0.5) of the warichuu
			@param p 
		 */
		virtual void SetWarichuRelativeSize(PMReal p) = 0; 

		/**	Gets the warichuu relative size (e.g. 50% scale = 0.5)
			@param none
			@return PMReal 
		 */
		virtual PMReal GetWarichuRelativeSize() const = 0; 


		/**	Sets the space between each warichuu line in points
			@param p 
		 */
		virtual void SetWarichuLineSpacing(PMReal p) = 0;

		/**	Sets the space between each warichuu line in points
			@param none
			@return PMReal 
		 */
		virtual PMReal GetWarichuLineSpacing() const = 0;


		/**	will get base text's alignment if override is NOT set
			This means that usually the alignment of the warichuu matches that of the parent paragraph. 
			But if the user overrides that setting, the overridden setting will be returned.
			@param none
			@return ICompositionStyle::TextAlignment 
		 */
		virtual ICompositionStyle::TextAlignment GetWarichuAlignment() const = 0;

		/**	Sets the alignment of the warichuu (similar to paragraph alignment)
			@param align 
		 */
		virtual void SetWarichuAlignment(ICompositionStyle::TextAlignment align) = 0;

		/**	Returns if the alignment is local to the warichuu or if it matches that of the parent paragraph
			@param none
			@return bool16 
		 */
		virtual bool16 OverrideParagraphAlignment() const = 0;


		/**	Sets the minimum number of characters per warichuu line at the start of multi-line warichuu.
			@param num 
		 */
		virtual void SetMinCharsBeforeBreak(int16 num) = 0;

		/**	Gets the minimum number of characters per warichuu line at the start of multi-line warichuu.
			@param none
			@return int16 
		 */
		virtual int16 GetMinCharsBeforeBreak() const = 0;


		/**	Sets the minimum number of characters per warichuu line at the end of multi-line warichuu.
			@param num 
		 */
		virtual void SetMinCharsAfterBreak(int16 num) = 0;

		/**	Gets the minimum number of characters per warichuu line at the end of multi-line warichuu.
			@param none
			@return int16 
		 */
		virtual int16 GetMinCharsAfterBreak() const = 0;

		/** Sets flag for causing parentheses characters next to warichuu to be resized automatically,
			in composers that support this feature.
			@param flag
		*/
		virtual void SetAutoResizeParen(bool16 flag) = 0;

		/** Gets flag for causing parentheses characters next to warichuu to be resized automatically,
			in composers that support this feature.
			@param flag
		*/
		virtual bool16 GetAutoResizeParen() const = 0;

};


#endif		// __IWarichuStyle__
