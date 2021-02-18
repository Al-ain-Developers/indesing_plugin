//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrUtils.h $
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
#ifndef __ITextAttrUtils__
#define __ITextAttrUtils__

#include "TextID.h"
#include "IPMUnknown.h"
#include "IRunInStylesUtils.h"
#include "Utils.h"

#include "BaseType.h"
#include "K2SmartPtr.h"

class IPMUnknown;
class ITextModel;
class ICommand;
class AttributeBossList;
class RangeData;


/** Utilities for getting and setting text attributes.
	e.g.
	<pre>Utils&lt;ITextAttrUtils&gt;()->BuildApplyTextAttrCmd( ... ) ;</pre>
	@ingroup text_attr
	@ingroup text_util
*/
class ITextAttrUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTATTRUTILS };

	/**	 Builds and returns an apply text attributes command setup to apply the given text attribute to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::ApplyCmd().
		@param model IN the text model to apply the attribute to.
		@param start IN the starting TextIndex for the apply.
		@param len	IN the length of the span of text to apply to.
		@param attr	IN an interface of the attribute to be applied.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.
	 */
	virtual ICommand* BuildApplyTextAttrCmd(ITextModel *model, TextIndex start, uint32 len, const IPMUnknown *attr, const ClassID& which) = 0;


	/**	 Builds and returns an apply text attributes command setup to apply the given text attribute to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::ApplyCmd().
		@param model IN the text model to apply the attribute to.
		@param range IN the range of text in the story to apply to.
		@param attr	IN an interface of the attribute to be applied.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.
	 */
	virtual ICommand* BuildApplyTextAttrCmd(ITextModel *model, const RangeData& range, const IPMUnknown *attr, const ClassID& which) = 0;


	/**	 Builds and returns an apply text attributes command setup to apply the given text attributes to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::ApplyCmd().
		@param model IN the text model to apply the attribute to.
		@param start IN the starting TextIndex for the apply.
		@param len	IN the length of the span of text to apply to.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@param attrList the list of text attributes to be applied.  These must either all be character attributes or all be paragraph attributes.
		@return The built command.
	 */
	virtual ICommand* BuildApplyTextAttrCmd(ITextModel *model, TextIndex start, uint32 len, const ClassID& which, const boost::shared_ptr<AttributeBossList>& attrList) = 0;


	/**	 Builds and returns an apply text attributes command setup to apply the given text attributes to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::ApplyCmd().
		@param model IN the text model to apply the attribute to.
		@param range IN the range of text in the story to apply to.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@param attrList the list of text attributes to be applied.  These must either all be character attributes or all be paragraph attributes.
		@return The built command.
	 */
	virtual ICommand* BuildApplyTextAttrCmd(ITextModel *mod, const RangeData& range, const ClassID& which, const boost::shared_ptr<AttributeBossList>& attrList) = 0;


	/**	 Builds and returns a user apply text attributes command setup to apply the given text attribute to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::UserApplyCmd().
		 NOTE: Unlike the BuildApplyTextAttrCmd and BuildApplyUserTextAttrCmd above, this method will return nil if the target story is locked.
		@param model IN the text model to apply the attribute to.
		@param start IN the starting TextIndex for the apply.
		@param len	IN the length of the span of text to apply to.
		@param attr	IN an interface of the attribute to be applied.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.  nil if the target ITextModel is locked.
	 */
	virtual ICommand* BuildApplyUserTextAttrCmd(ITextModel *mod, TextIndex start, uint32 len, const IPMUnknown *attr, const ClassID& which) = 0;


	/**	 Builds and returns a user apply text attributes command setup to apply the given text attribute to a range in a story.
		 This is just a thin wrapper on ITextModelCmds::UserApplyCmd().
		 NOTE: Unlike the BuildApplyTextAttrCmd and BuildApplyUserTextAttrCmd above, this method will return nil if the target story is locked.
		@param model IN the text model to apply the attribute to.
		@param range IN the range of text in the story to apply to.
		@param attr	IN an interface of the attribute to be applied.
		@param which IN the ClassID of the attribute strand to apply to (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.  nil if the target ITextModel is locked.
	 */
	virtual ICommand* BuildApplyUserTextAttrCmd(ITextModel *mod, const RangeData& range, const IPMUnknown *attr, const ClassID& which) = 0;


	/**	 Builds and returns a clear text attributes command setup to clear the given text attribute over the given range of a story.
		 This is just a thin wrapper on ITextModelCmds::ClearOverridesCmd().
		@param model IN the text model to clear the attribute in.
		@param start IN the starting TextIndex for the clear.
		@param len	IN the length of the span of text to clear.
		@param attr	IN an interface of the attribute to be cleared.
		@param which IN the ClassID of the attribute strand to clear the attribute from (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.
	 */
	virtual ICommand* BuildClearTextAttrCmd(ITextModel *mod, TextIndex start, uint32 len, const ClassID& attrClass, const ClassID& which) = 0;


	/**	 Builds and returns a clear text attributes command setup to clear the given text attribute over the given range of a story.
		 This is just a thin wrapper on ITextModelCmds::ClearOverridesCmd().
		@param model IN the text model to clear the attribute in.
		@param range IN the range of text in the story to apply to.
		@param attr	IN an interface of the attribute to be cleared.
		@param which IN the ClassID of the attribute strand to clear the attribute from (either kCharAttrStrandBoss or kParaAttrStrandBoss).
		@return The built command.
	 */
	virtual ICommand* BuildClearTextAttrCmd(ITextModel *mod, const RangeData& range, const ClassID& attrClass, const ClassID& which) = 0;


	// NOTE: It is the responsibility of the caller to ensure that all Text
	// within the range is fully composed as possible BEFORE calling. In
	// practice the top level container, usually the MultiColumnFrame should
	// be the only one required to force composition.
	/**	 Generates and processes all the commands necessary to scale the text attributes of the given range of text by the given
		 x and y scale factors.  All the commands are incapsulated in a single command sequence.
		 NOTE: It is the callers responsibility to ensure the range of text is fully composed before calling this method.  (In some
		 cases the composed state of the text must be known in order to correctly apply scaling.)
		 @param model IN the story containing the text to be scaled.
		 @param start IN the starting index of the text to be scaled.
		 @param endPosition IN the ending index of the text to be scaled.  (One beyond the last character to be scaled.)
		 @param xScale IN the horizontal scaling percentage to apply.
		 @param yScale IN the vertical scaling percentage to apply.
		 @return errCode kSuccess, or a failure code if one of the subcommands failed (in which case all other commands would have been rolled back).
	 */
	virtual ErrorCode ProcessScaleTextMeasures( ITextModel *model, TextIndex start, TextIndex endPosition, PMReal xScale, PMReal yScale) = 0;


	/**  Fills results with the total attributes at index, accounting for story thread attributes, paragraph styles, paragaph overrides,
		 nested styles, character styles, and character overrides.
		Returns additional information in optional variables.
		@param model IN relevant text model.
		@param index IN position in model we want the attribute for.
		@param includeTextState IN should we use the text state.
		@param leanleft IN gather attributes to the left of the index.
		@param results OUT effective attributes.
		@param start OUT If non-nil returns starting index for the resulting run.
		@param end OUT If non-nil returns ending index for the resulting run.
		@param paraStyle OUT If non-nil returns the paragraph style applied to this run.
		@param plen OUT If non-nil returns the remaining text the paragraph style is applied to.
		@param paraStyleOverridden OUT If non-nil returns kTrue if this paragraph style been overridden.
		@param charStyle OUT If non-nil returns character style applied to this run.
		@param clen OUT If non-nil returns the remaining text the character style is applied to.
		@param charStyleOverridden OUT If non-nil returns kTrue if this character style been overridden.
		@param nestedStyle OUT If non-nil returns character style applied via nested style.
		@param nestedStyleLen OUT If non-nil returns the remaining text the nested character style is applied to.
		@param nestedStyleOverridden OUT If non-nil returns kTrue if the nested style is overridden by character
		 attributes applied directly to the text or by attributes of the character style of the text.
		@precondition model must be a non-nil ITextModel.
		@precondition index must be a valid position in the model.
		@return void

	*/
	virtual void GetTotalAttributesAtIndex(	ITextModel * model, TextIndex index, bool16 includeTextState,  bool16 leanleft,
											AttributeBossList & results, int32 * start = nil, int32 * end = nil,
											UID * paraStyle = nil, int32 * plen = nil, bool16 * paraStyleOverridden = nil,
											UID * charStyle = nil, int32 * clen = nil, bool16 * charStyleOverridden = nil,
											RunInStyleResult::CharStyleList * nestedStyles = nil, int32 * nestedStyleLen = nil, bool16 * nestedStyleOverridden = nil
										    )= 0;
};


#endif	// __ITextAttrUtils__
