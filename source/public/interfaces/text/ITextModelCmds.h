//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextModelCmds.h $
//  
//  Owner: EricM
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
#ifndef __ITEXTMODELCMDS__
#define __ITEXTMODELCMDS__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2SmartPtr.h"
#include "ITextModel.h"
#include "IFontLockingData.h"

class ICommand;
class WideString;
class AttributeBossList;
class ReplaceInfo;
class VOS_SavedData;
class PasteData;
class ILanguage;
class IParcel;
class ITextStoryThread;
class ITextParcelList;
class IFrameList;
class TextEditAction;

/** This is a Text story interface. It serves to query for text
	edit commands to operate on the story. The functions in this
	interface used to be part of the ITextModel interface.
	@ingroup text_story
*/

class ITextModelCmds : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTMODELCMDS };

		/**
			@return a new command that pastes text into a story.
			@param position IN insert position.
			@param data IN pasted text data. data is gathered by the
			caller as the result of calling ITextModel::CopyRange or ITextModel::Cut.
			This is a shared pointer. @see K2SmartPtr for usage of shared_ptr.
			@param ignoreAttributes to indicate ignore attributes when paste
		 */
		virtual ICommand* PasteCmd(TextIndex position, const boost::shared_ptr<PasteData>& data, bool16 ignoreAttributes = kFalse) = 0;

		/**
			For internal use only.
		*/
		virtual ICommand* PasteCmd(const RangeData& r, const boost::shared_ptr<PasteData>& data, bool16 ignoreAttributes = kFalse) = 0;


		/**
			@return a new  command that inserts text into the story.
			@param position IN text index where to insert text.
			@param data IN text to insert. This is a shared pointer. @see K2SmartPtr for usage of shared_ptr.
			@param language IN language of inserted text.
		*/
		virtual ICommand* InsertCmd(TextIndex position, const boost::shared_ptr<WideString>& data, const ILanguage *language = nil ) = 0;

		/**
			For internal use only.
		*/
		virtual ICommand* InsertCmd(const RangeData& r, const boost::shared_ptr<WideString>& data, const ILanguage *language = nil ) = 0;
		/**
			@return a new delete text command.
			@param start IN start of delete range.
			@param length IN length of delete range.
			@param ignoreLock IN will bypass checking for locked story
		*/
		virtual ICommand* DeleteCmd(TextIndex start, int32 length, bool16 ignoreLock=kFalse) = 0;

		/**
			@return a new delete text command.
			@param range IN delete range.
			@param ignoreLock IN will bypass checking for locked story
		*/
		virtual ICommand* DeleteCmd( const RangeData& range, bool16 ignoreLock=kFalse) = 0;

		/**
			@return a new Replace Text command.
			@param start IN start of replace range.
			@param length IN length of replace range.
			@param insert IN replacement text. This is a shared pointer. @see K2SmartPtr for usage of shared_ptr.
			@param language IN language of inserted text.
			@param clearNonContinuingAttrs IN clear non continuing attributes after doing the replace.
		*/
		virtual ICommand* ReplaceCmd(TextIndex start,
									int32 length,
									const boost::shared_ptr<WideString> &insert,
									const ILanguage *language = nil,
									bool16 clearNonContinuingAttrs = kTrue) = 0;

		/**
			@return a new type text command. If the length of the range passed in is greater than zero the text
			in the range is actually deleted.
			@param startPosition IN start of range.
			@param endPosition IN end of range.
			@param insert IN  is a shared pointer that constitutes what actually gets
			inserted into the story. @see K2SmartPtr for usage of shared_ptr.
			@param language IN language of inserted text.
		*/
		virtual ICommand* TypeTextCmd(TextIndex startPosition, TextIndex endPosition, const boost::shared_ptr<WideString>& insert, const ILanguage *language = nil ) = 0;

		/**
			@return a new type text command. If the length of the range passed in is greater than zero the text
			in the range is actually deleted.
			@param range IN range.
			@param insert IN  is a shared pointer that constitutes what actually gets
			inserted into the story. @see K2SmartPtr for usage of shared_ptr.
			@param language IN language of inserted text.
		*/
		virtual ICommand* TypeTextCmd(const RangeData& range, const boost::shared_ptr<WideString>& insert, const ILanguage *language = nil ) = 0;

		/**
			@return a new apply attributes command.
			@param start IN start of apply range.
			@param length IN length of apply range.
			@param list IN shared pointer of attribute boss list to apply. @see K2SmartPtr for usage of shared_ptr.
			@param whichStrand IN whether the attributes applied are paragraph or a character attributes.
		*/
		virtual ICommand* ApplyCmd(TextIndex start, int32 length, const boost::shared_ptr<AttributeBossList>& list, ClassID whichStrand) = 0;

		/**
			@return a new apply attributes command.
			@param range IN apply range.
			@param list IN shared pointer of attribute boss list to apply.
			@see K2SmartPtr for usage of shared_ptr.
			@param whichStrand IN whether the attributes applied are paragraph or a character attributes.
		*/
		virtual ICommand* ApplyCmd( const RangeData& range, const boost::shared_ptr<AttributeBossList>& list, ClassID whichStrand) = 0;

		/**
			@return a new apply style command which applies a style.
			@param start IN start of apply range.
			@param length IN length of apply range.
			@param stylerefid IN style to apply.
			@param whichStrand IN whether the attributes applied are paragraph or a character attributes.
			@param replaceOverrides IN whether to clear the overrides.
			@param keepOldStyleAsOverrides IN whether to apply the old style as overrides before setting new style.
						This variable is only used if stylerefid is the root style.
		*/
		virtual ICommand* ApplyStyleCmd(TextIndex start, int32 length, UID stylerefid, ClassID whichStrand, bool16 replaceOverrides = kTrue, bool16 autoNextStyle = kFalse, bool16 keepOldStyleAsOverrides = kTrue) = 0;

		/**
			@return a new command which removes all applied styles within a range.
			@param start IN start of range.
			@param length IN length of range.
			@param whichStrand IN whether paragraph or character styles need to be removed.
		*/
		virtual ICommand* UnapplyStyleCmd(TextIndex start, int32 length, ClassID whichStrand) = 0;

		/**
			@return a new  command which clears specific attributes from a range
			@param start IN start of clear range.
			@param length IN length of clear range.
			@param these IN attributes to clear.
			@param whichStrand IN whether paragraph or character attributes need to be cleared.
		*/
		virtual ICommand* ClearOverridesCmd(TextIndex start, int32 length, const boost::shared_ptr<AttributeBossList>& these, ClassID whichStrand) = 0;

		/**
			@return a new  apply attributes command which applies attributes to a range.
			@param start IN start of apply range.
			@param length IN length of apply range.
			@param list IN shared pointer of attribute boss list to apply.@see K2SmartPtr for usage of shared_ptr.
			@param whichStrand IN whether the attributes applied are paragraph or a character attributes.
		*/
		virtual ICommand* UserApplyCmd(TextIndex start, int32 length, const boost::shared_ptr<AttributeBossList>& list, ClassID whichStrand) = 0;

		/**
			@return a new command which registers a strand with the text model.
			@param strand IN strand uid.
		*/
		virtual ICommand* RegisterStrandCmd(UID strand) = 0;

		/**
			@return a new  command which unregisters a strand from the text model.
			@param strand IN strand uid
		*/
		virtual ICommand* UnregisterStrandCmd(UID strand) = 0;

		/**
			@return a new  multiple replacement Text command.
			@param replList IN is a shared pointer and constitutes the requested list of replacements.
			This is an optimized way to do more than one replacement at a time.
			The replacement list must be in assending order of text indices (@see ITextModel).
			@see K2SmartPtr for usage of shared_ptr.
			@param language IN indicates the language of the replacement text.
			@param clearNonContinuingAttrs IN clear non continuing attributes after doing each replacement.
		*/
		virtual ICommand* ReplaceCmd(const boost::shared_ptr<ITextModel::ReplacementList>& replacementList,
									const ILanguage *language = nil,
 									bool16 clearNonContinuingAttrs = kTrue) = 0;

		/**
			For internal use only.
		*/
		virtual TextEditAction* GetApplyTextStyle_Action (TextIndex start,
														int32	len,
														UID style,
														const boost::shared_ptr<AttributeBossList>&overrides,
														ClassID which,
														bool16 destroyOverrides,
														bool16 autoNextStyle, bool16 keepOldStyleAsOverrides = kTrue) = 0;

		virtual TextEditAction* GetReplaceText_Action (TextIndex start,
														int32	oldLen,
														const boost::shared_ptr<WideString>&	insertData,
														ILanguage	*pLanguage,
														bool16 clearNonContinuingAttrs = kTrue) = 0;

		virtual	TextEditAction* GetUserApplyAttr_Action(TextIndex start,
														int32	len,
														UID		style,
														const boost::shared_ptr<AttributeBossList>&	over,
														ClassID		which,
														bool16		destroyLocalOverrides,
														bool16 autoNextStyle,
														bool16 keepOldStyleAsOverrides = kTrue,
														IFontLockingData::FontLockLevel fontLocking = IFontLockingData::kAllowFontLockingWithOverride) = 0;

};
#endif