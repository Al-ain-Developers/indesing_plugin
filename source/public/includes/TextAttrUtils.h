//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextAttrUtils.h $
//  
//  Owner: eric_kenninga
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
#ifndef __TextAttrUtils__
#define __TextAttrUtils__

#include "ITextAttrUtils.h"

// fill out the story, the range, an interface from the attribute, and the classID of the strand you're applying to: char, para, etc.
// char = kCharAttrStrandBoss, para = kParaAttrStrandBoss. If you want to apply more than 1 attr at a time, you can, but you must
// access the IApplyStyleData interface of the command you get back.
inline ICommand* BuildApplyTextAttrCmd(ITextModel *mod, TextIndex start, uint32 len, const IPMUnknown *attr, const ClassID& which)
	{ return Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd( mod, start, len, attr, which ); }

// The "attrList" is owned by the returned command.
	inline ICommand* BuildApplyTextAttrCmd(ITextModel *mod, TextIndex start, uint32 len, const ClassID& which, const boost::shared_ptr<AttributeBossList>& attrList)
	{ return Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd( mod, start, len, which, attrList ); }

// Unlike BuildApplyTextAttrCmd, BuildApplyUserTextAttrCmd will first check to see if the text model content is locked and return nil if this is true.
inline ICommand* BuildApplyUserTextAttrCmd(ITextModel *mod, TextIndex start, uint32 len, const IPMUnknown *attr, const ClassID& which)
	{ return Utils<ITextAttrUtils>()->BuildApplyUserTextAttrCmd(mod, start, len, attr,  which ); }
inline ICommand* BuildClearTextAttrCmd( ITextModel *mod, TextIndex start, uint32 len, const ClassID& attrClass, const ClassID& which )
	{ return Utils<ITextAttrUtils>()->BuildClearTextAttrCmd(mod, start, len, attrClass, which); }

	// NOTE: It is the responsibility of the caller to ensure that all Text
	// within the range is fully composed as possible BEFORE calling. In
	// practice the top level container, usually the MultiColumnFrame should
	// be the only one required to force composition.
inline ErrorCode ProcessScaleTextMeasures( ITextModel *model, TextIndex start, TextIndex endPosition, PMReal xScale, PMReal yScale )
	{ return Utils<ITextAttrUtils>()->ProcessScaleTextMeasures( model, start, endPosition, xScale, yScale ); }
inline void GetTotalAttributesAtIndex(ITextModel * model, TextIndex index, bool16 includeTextState,  bool16 leanleft,
											AttributeBossList & results, int32 * start, int32 * end,
											UID * paraStyle, int32 * plen, bool16 * paraStyleOverridden,
											UID * charStyle, int32 * clen, bool16 * charStyleOverridden
										    )
	{ Utils<ITextAttrUtils>()->GetTotalAttributesAtIndex(model, index, includeTextState, leanleft, results, start, end, paraStyle, plen, paraStyleOverridden, charStyle, clen, charStyleOverridden); }
#endif		//  __TextAttrUtils__
