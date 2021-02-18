//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IKinsokuTable.h $
//  
//  Owner: emenning
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
#ifndef __IKinsokuTable__
#define __IKinsokuTable__


#include "IPMUnknown.h"
#include "CJKID.h"

class WideString;

/** The Kinsoku Table contains characters in four categories: Characters that cannot begin a line,
	characters that cannot end a line, characters that are inseparable (no-break, no-justify) and 
	characters that can hang outside the right margin.
*/
class IKinsokuTable : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IKINSOKUTABLE };

		typedef enum {	kKinsoku_CannotBeginLine = 0,
						kKinsoku_CannotEndLine,
						kKinsoku_Hanging,
						kKinsoku_Nonseparatable
					} KinsokuCharType;
		
		/** Add characters that cannot begin a line to the table
		@param characters [IN] cannot begin line characters
		*/
		virtual void AddKinsokuBefore(const WideString& characters) = 0;
		/** Add characters that cannot end a line to the table
		@param characters [IN] cannot end line characters
		*/
		virtual void AddKinsokuAfter(const WideString& characters) = 0;
		/** Add characters that can hang off line end to the table
		@param characters [IN] hanging characters
		*/
		virtual void AddKinsokuHanging(const WideString& characters) = 0;
		/** Add characters that cannot be separated or justified
		@param characters [IN] inseparable characters
		*/
		virtual void AddKinsokuNotSeparate(const WideString& characters) = 0;
		
		/** Get characters that cannot begin a line
		@param characters [OUT] cannot begin line characters
		*/
		virtual void GetKinsokuBefore(WideString& characters) const = 0;
		/** Get characters that cannot end a line
		@param characters [OUT] cannot end line characters
		*/
		virtual void GetKinsokuAfter(WideString& characters) const = 0;
		/** Get characters that can hang off the end of a line
		@param characters [OUT] hanging characters
		*/
		virtual void GetKinsokuHanging(WideString& characters) const = 0;
		/** Get characters that cannot be separated or justified
		@param characters [OUT] inseparable characters
		*/
		virtual void GetKinsokuNotSeparate(WideString& characters) const = 0;

		/** Get whether or not a character is in the cannot end line character table
		@param c [IN] character
		@return kTrue if character is found in the table
		*/
		virtual bool16 NoBreakBefore(UTF32TextChar c) const = 0;
		/** Get whether or not a character is in the cannot begin line character table
		@param c [IN] character
		@return kTrue if character is found in the table
		*/
		virtual bool16 NoBreakAfter(UTF32TextChar c) const = 0;
		/** Get whether or not a character is in the hanging character table
		@param c [IN] character
		@return kTrue if character is found in the table
		*/
		virtual bool16 IsHangingCharacter(UTF32TextChar c) const = 0;
		/** Get whether or not a character is in the inseparables character table
		@param c [IN] character
		@return kTrue if character is found in the table
		*/
		virtual bool16 IsNotSeparateCharacter(UTF32TextChar c) const = 0;

		/** Get number of kinsoku characters that cannot end a line
		@return number of kinsoku characters that cannot end a line
		*/
		virtual int32 KinsokuBeforeNum() const = 0;
		/** Get number of kinsoku characters that cannot begin a line
		@return number of kinsoku characters that cannot begin a line
		*/
		virtual int32 KinsokuAfterNum() const = 0;
		/** Get number of kinsoku characters that can hang at line end
		@return number of kinsoku characters that can hang at line end
		*/
		virtual int32 KinsokuHangingNum() const = 0;
		/** Get number of kinsoku characters that cannot be separated or justified
		@return number of kinsoku characters that cannot be separated or justified
		*/
		virtual int32 KinsokuNotSeparateNum() const = 0;

		/** Clear the contents of the table
		*/
		virtual void Clear() = 0;
		/** Clear the contents of the no-break before table
		*/
		virtual void ClearKinsokuBefore() = 0;
		/** Clear the contents of the no-break after table
		*/
		virtual void ClearKinsokuAfter() = 0;
		/** Clear the contents of the kinsoku hanging table
		*/
		virtual void ClearKinsokuHanging() = 0;
		/** Clear the contents of the inseparables table
		*/
		virtual void ClearKinsokuNotSeparate() = 0;

		/** Get a single kinsoku character of the requested type
		@param index [IN] index into the buffer of kinsoku characters
		@param type [IN] which buffer
		@return the kinsoku character
		*/
		virtual UTF32TextChar GetOneKinsokuCharacter(const int32 index, KinsokuCharType type) const = 0;
		/** Add a single kinsoku character of the requested type to that buffer
		@param ch [IN] the kinsoku character to add
		@param type [IN] which buffer
		*/
		virtual void AppendOneKinsokuCharacter(const UTF32TextChar ch, KinsokuCharType type) = 0;

		/** Copy Kinsoku table data from other table
		@param from [IN] table to copy from
		*/
		virtual void CopyKinsokuTableData(const IKinsokuTable *from) = 0;

		/**
		@return kTrue if this Kinsoku table is editable
		*/
		virtual bool16 GetEditability() const = 0;
		/**
		@param editability [IN] sets whether or not the table is user-editable
		*/
		virtual void SetEditability(bool16 editability) = 0;

		// Unused (for now)
		virtual void AddKinsokuBetween(const textchar *characters1, const textchar *characters2, int32 number) = 0;
		virtual bool16 NoBreakBetween(UTF32TextChar c1, UTF32TextChar c2) const = 0;
		virtual int32 NoBreakBetweenNum() const = 0;
		virtual void ClearNoBreakBetween() = 0;
};



#endif
		// __IKinsokuTable__
		
		
