//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptTagCmdData.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __IScriptTagCmdData__
#define __IScriptTagCmdData__

#include "IPMUnknown.h"
#include "IScriptLabel.h"
#include "ScriptData.h"

using namespace ScriptInfo ;

/**
	An interface used by the kSetScriptingTagCmdBoss. Use IScriptUtils::SetScriptingTag() 
	or IScriptUtils::SetScriptingTags() to access this command. This interface is included in the SDK
	for reference purposes only and plug-in developers should not invoke any of the "Set" APIs
	in this interface.
*/  
class IScriptTagCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTTAGCMDDATA };

	/** Set the target object(s) and context
	*/
	virtual void SetScriptList( const ScriptList& scriptList, const EngineContext& context ) = 0 ;

	/** Set a label
	*/
	virtual void SetTag( const IScriptLabel::ScriptLabelValue& label, const IScriptLabel::ScriptLabelKey& key = IScriptLabel::kDefaultScriptLabelKey ) = 0 ;

	/** Set multiple labels
		@param replaceExistingLabels if kTrue instructs command to replace any and all existing labels with the newly supplied ones
	*/
	virtual void SetTags( const IScriptLabel::ScriptLabelKeyValueList& labels, bool16 replaceExistingLabels = kFalse ) = 0 ;

	/** Return the script list
	*/
	virtual ErrorCode GetScriptList( ScriptList& scriptList ) const = 0 ;

	/** Return the request context
	*/
	virtual const RequestContext& GetRequestContext() const = 0 ;

	/** Return the label
	*/
	virtual const IScriptLabel::ScriptLabelKeyValueList& GetTags() const = 0 ;

	/** Return whether to replace existing labels
	*/
	virtual bool16 GetReplaceExistingLabels() const = 0 ;
};

#endif
