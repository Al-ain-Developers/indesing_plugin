//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextScriptUtils.h $
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
#ifndef __ITextScriptUtils__
#define __ITextScriptUtils__

#include "K2SmartPtr.h"
#include "RangeData.h"
#include "ScriptData.h"
#include "ShuksanID.h"
#include "TextID.h"
#include "Utils.h"
#include "IPMFont.h"
#include "IAnchoredObjectData.h"

class ITextModel;
class ITableModel;
class IDocument	;
class IStyleInfo;
class ICommand;
class IScript;
class IAttrReport;
class AttributeBossList;
class IStyleNameTable;
class IHierarchy;
class IScriptCellRef;
class WideString;
class GridAddress;
class RangeData;
class IFontFamily;
class ITextTarget;
class IScriptRequestData;
class ITextFrameColumn;
class ITextVariable;
class ITextVariableTable;

typedef boost::shared_ptr<AttributeBossList>	AddAttributeList ;
typedef K2Vector<ClassID>					RemoveAttributeList ;

/** Utilities related to text scripting, also contains general text and text frame utilities.
	e.g.
	<pre>Utils&;t;ITextScriptUtils&gt;()->SpellingIsWordChar( ... ) ;</pre>
	@ingroup text_util
*/
class ITextScriptUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTSCRIPTUTILS };

	virtual ScriptID GetTextType( IScript* script ) = 0;

	/** Create a new text script object
		@param textModel is the parent story
		@param range is the text target range
		@param type is the object type, if known
	*/
	virtual IScript* QueryTextObject( const RequestContext& context, ITextModel* model, const RangeData& range, const ScriptID& type = kInvalidScriptID ) = 0;

	virtual ICommand* CreateEditFindChangePrefCmd( const ScriptID& propID,
													IDataBase* targetDB,
													const IPMUnknown* addAttribute = nil,
													ClassID removeAttribute = kInvalidClass ) = 0;

	virtual ICommand* CreateEditFindChangePrefCmd( const ScriptID& propID,
													IDataBase* targetDB,
													const AddAttributeList& addAttrList,
													const RemoveAttributeList& removeAttrList ) = 0;

	virtual ICommand* CreateEditFindChangePrefCmd( const ScriptID& propID,
													const ScriptID& objectType,
													IDataBase* targetDB,
													const UID& styleUID ) = 0 ;

	virtual ITextModel* QueryTextModel(IScript* script) = 0;

	//!	Notes:'Text frames' are comprised of a number of levels.
	//!	The top level is a GraphicFrame. The GraphicFrame
	//!	contains a MultiColumnTextFrame. The MultiColumnTextFrame
	//!	contains 1 or more TextFrames (1 frame for each column). The
	//!	TextFrames contain the story text. Each level has its own
	//!	UIDRef. These functions are used for getting from level to another.
	//! (Adapted from utilities in QATextObject class by Stan Somers)

	/** Return kTrue if this script object is a c_TextFrame or a c_TOP. Use:
			ITextScriptUtils::IsTextFrame( script, context ) - if your query is in the context of a scripting DOM
			IPageItemTypeUtils::IsTextFrame( pageitem ) - if your query is in the context of the InDesign object model
	*/
	virtual bool16 IsTextFrame( const IScript* script, const RequestContext& context ) = 0;

	/** Get a graphic frame's first text frame (grandchild) */
	virtual IPMUnknown* QueryFirstTextFrame ( const IPMUnknown* gframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a graphic frame's last text frame (grandchild) */
	virtual IPMUnknown* QueryLastTextFrame ( const IPMUnknown* gframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a text frame's graphic frame (grandparent) */
	virtual IPMUnknown* QueryGraphicFrame( const IPMUnknown* tframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a graphic frame's multi-column frame (child) */
	virtual IPMUnknown* QueryChildMultiColFrame( const IPMUnknown* gframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a multi-column frame's first text frame (child) */
	virtual IPMUnknown* QueryFirstChildTextFrame( const IPMUnknown* mcframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a multi-column frame's last text frame (child) */
	virtual IPMUnknown* QueryLastChildTextFrame( const IPMUnknown* mcframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a text frame's multi-column frame (parent) */
	virtual IPMUnknown* QueryParentMultiColFrame( const IPMUnknown* tframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Get a multi-column frame's graphic frame (parent) */
	virtual IPMUnknown* QueryParentGraphicFrame( const IPMUnknown* mcframe, PMIID iid = IID_IUNKNOWN ) const = 0;

	/** Given a text model and index, get the text frame the text resides in, or the last frame in the story's frame list.
		This api causes composition to the index specified. This means it will
		compose from intermediate states to completion.
	
		@param textModel - the story
		@param index - the text location
		@param ifNoneReturnLastFrame - if kTrue and the text is overset, returns the last frame in the story's frame list (instead of nil)
	*/
	virtual ITextFrameColumn* QueryTextFrameColumnContaining( ITextModel* textModel, TextIndex index, bool16 ifNoneReturnLastFrame = kFalse ) = 0;

	/** Given a text target, get the text frames the text resides in.
		@param textTarget - the text script object to use
		@param parentList - the list of parent text frames [out]
	*/
	virtual ErrorCode GetParentTextFrames( IScript* script, ScriptList& parentList ) = 0;

	/** Given a text target, get the text frame the text resides in. If the text is not in a frame or if it extends across frames, nil is returned
		@param textTarget - the text target to use
	*/
	virtual IScript* QueryParentTextFrame( IScript* textTarget ) = 0;

	/** Given a text model and a character index, get the text frame the text resides in. If the text is not in a frame, nil is returned
		@param textModel - the text model to use
		@param index - the text index to use
		@param iid - the iid of the interface to query on the text frame
	*/
	virtual IPMUnknown* QueryParentTextFrame( const ITextModel* textModel, TextIndex index, PMIID iid = IID_IUNKNOWN ) = 0;

	/**	Recompose the text in/upto the object */
	virtual ErrorCode Recompose( IScript* script ) = 0;

	virtual bool16 DefaultIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 TestIsSpace( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 TestIsPunctuation( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;

	/** Returns kTrue if the attributes of the two text runs are identical */
	virtual bool16 AreTextRunAttributesEqual( ITextModel* model1, TextIndex start1, ITextModel* model2, TextIndex start2 ) = 0;

	/** Used to query attribute information about a Text property that is implemented as an object (e.g., TabStop, RunInStyle) */
	virtual const IAttrReport* QueryChildTextAttribute( const RequestContext& context, IScript* script, const ScriptID& childType, const ClassID& attrID, AttributeBossList* attrList ) = 0;

	/** Used to to query a command to set a Text property that is implemented as an object (e.g., TabStop, RunInStyle) */
	virtual ICommand* QueryChildTextCommand( IScriptRequestData* data, IScript* script, const ScriptID& childType, const IAttrReport* attrReport ) = 0;

	virtual ErrorCode GetFrameStartEnd(const IHierarchy* hierarchy, UIDRef& textModel, TextIndex& frameStart, TextIndex& frameEnd) = 0;

	virtual ErrorCode GetCellStartEnd(const InterfacePtr<ITableModel>& table, GridAddress cellAddress, InterfacePtr<ITextModel>& textModel, TextIndex& cellStart, TextIndex& cellEnd, bool16 includeOverset = kTrue) const = 0;

	/** Convert text script data containing a special characters enum or a string to a wide string */
	virtual ErrorCode ConvertEnumToWideString( const RequestContext& context, const ScriptData& scriptData, WideString& outString ) = 0 ;
	/** Convert a wide string to text script data containing a special characters enum or a string */
	virtual ErrorCode ConvertWideStringToEnum( const RequestContext& context, const WideString& inString, ScriptData& scriptData ) = 0 ;

	/** Get the text from a particular text location into a ScriptData accounting for any special characters */
	virtual ErrorCode GetSpecialChar( IScriptRequestData* data, ScriptData& scriptData, IScript* script, ITextModel* model, TextIndex start, int32 length ) = 0 ;
	/** Insert some text at a particular location accounting for any special characters
		@param scriptData - the character data to be set (string or special characters enum)
		@param model - the text model in which to insert the text
		@param start - the location at which to insert the text
		@param length - the length of existing text to replace; will be modified to the length of the inserted text
	*/
	virtual ErrorCode SetSpecialChar( IScriptRequestData* data, const ScriptData& scriptData, ITextModel* model, TextIndex start, int32& length ) = 0 ;

	/**  Convert text offset and length to exclude non-user accessible (e.g., table anchor) characters */
	virtual void ExcludeNUACharacters( ITextModel* model, int32& start, int32& length, const RequestContext& context ) const = 0 ;

	/**  Convert text offset and length to include related non-user accessible (e.g., table anchor) characters */
	virtual void IncludeNUACharacters( ITextModel* model, int32& start, int32& length, const RequestContext& context ) const = 0 ;

	/**  Strip out non-user accessible (e.g., table anchor) characters */
	virtual int32 StripNUACharacters( PMString& string, const RequestContext& context ) const = 0 ;

	/**  Given the IScript on a scripting font object get the IPMFont* */
	virtual IPMFont* QueryFont (const RequestContext& context, IScript* script) = 0 ;

	/**  Given a family name, a style name and a parent, create a font proxy script object
		@param familyName - family name of font
		@param styleName - style name of font
		@param parent - parent
		@param psName - if non nil and string is not empty this is used to find font instead of family and style.
	*/
	virtual IScript* QueryFontObject( const RequestContext& context, const PMString& familyName, const PMString& styleName, IScript* parent, PMString *psName = nil, IPMFont::FontType fontType = IPMFont::kUnknownFontType ) = 0;

	/**  Given an IScript on an story or text object, delete the text */
	virtual ErrorCode DeleteText( IScriptRequestData* data, IScript* script ) = 0 ;

	/**  Access overset property on a text frame, cell, or story object */
	virtual ErrorCode AccessOverset( IScriptRequestData* data, IScript* script, const ScriptID& propID ) = 0 ;

	/**  Retrieve the range from a text script object */
	virtual RangeData GetScriptTextRange( IScript* script ) = 0 ;

	/** Handle the get/set of the p_Contents property */
	virtual ErrorCode AccessTextContents( IScriptRequestData* data, IScript* script, const ScriptID& propID ) = 0 ;
	virtual ErrorCode AccessFrameTextContents( IScriptRequestData* data, IScript* script, const ScriptID& propID ) = 0 ;

	/** Release the anchored objects. This means to detach them from the text and make them stand alone page items.
	*/
	virtual ErrorCode ReleaseAnchoredObjects(const UIDList& anchors) = 0;

	/** Convert a character to text script data containing a special characters enum or a string 
		@param content - the scripting request context
		@param inChar - the character to convert
		@param scriptData - the script data to contain the converted enum or string
		@param model - the text model that contains the character
		@param start - the location of the character
	*/
	virtual ErrorCode ConvertCharacterToEnum( const RequestContext& context, const UTF32TextChar inChar, ScriptData& scriptData, ITextModel* model, TextIndex start ) = 0 ;

	/*
		Given a text variable script proxy script object, query the associated text variable table in the object model
		@param script is the proxy object
		@param context is the request context
		@return the text variable table
	*/
	virtual ITextVariableTable* QueryTextVariableTableFromScript( const IScript* script, const RequestContext& context ) const = 0 ;
	/*
		Given a text variable script proxy script object, query the associated text variable in the object model
		@param script is the proxy object
		@param context is the request context
		@return the text variable
	*/
	virtual ITextVariable* QueryTextVariableFromScript( const IScript* script, const RequestContext& context ) const = 0 ;
	/*
		Given a text variable script proxy script object, return the associated text variable name in the object model
		@param script is the proxy object
		@param context is the request context
		@return the text variable name
	*/
	virtual PMString GetTextVariableNameFromScript( const IScript* script, const RequestContext& context ) const = 0 ;

	/*
		Return the text model and text range for the parent of an object being created in text
		@param data is the script event data for the create event IN
		@param parent is the parent for the create event IN
		@param modelRange is the result OUT
	*/
	virtual ErrorCode GetModelRangeFromParent( const IScriptRequestData* data, const IScript* parent, const ScriptID& insertionLocation, ModelRange& modelRange ) const = 0 ;

	/*
		Handles scripting support for MultiColumnTextFrame linking/unlinking. Works for
		both regular and TextOnPath.
	*/
	virtual ErrorCode AccessLinkedTextFrame(IScriptRequestData* data, const IScript* script, const ScriptID propID) = 0;

	/*
		Convert the passed in pageitem into an anchored object or inline
		@param objectToAnchorUIDRef	pageItem to convert. can be inline already.
		@param destStoryUIDRef		story to anchor into.
		@param textRange			text index to place anchor
		@param anchorPosition		inline, aboveline or anchor.
		@return						kCannotReAnchorMemberOfGroupError, kRequestNotHandledError or kSuccess
	*/
	virtual ErrorCode ConvertToAnchoredObject(UIDRef objectToAnchorUIDRef, UIDRef destStoryUIDRef, const RangeData& textRange, IAnchoredObjectData::AnchoredPosition anchorPosition) const = 0;

	/*
		Return true if it is valid anchor destination
		@param objectToAnchorUIDRef	pageItem to anchor. can be inline already.
		@param destStoryUIDRef		story to anchor into.
		@param destTextIndex		text index to place anchor
		@param anchorPosition		inline, aboveline or anchor.
		@return						kTrue if valid anchor destination
	*/
	virtual bool16 IsValidAnchorDestination(UIDRef objectToAnchorUIDRef, UIDRef destStoryUIDRef, TextIndex destTextIndex, IAnchoredObjectData::AnchoredPosition anchorPosition) const = 0;
};

#endif	// __ITextScriptUtils__
