//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleUtils.h $
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
#ifndef __IStyleUtils__
#define __IStyleUtils__

#include "IPMUnknown.h"

#include "AttributeBossList.h"
#include "K2SmartPtr.h"
#include "RequestContext.h"
#include "TextID.h"
#include "Utils.h"

class IScript ;
class IScriptRequestData ;
class IStyleInfo ;
class IStyleNameTable ;
class IStyleGroupManager;
class IStyleGroupHierarchy;

typedef boost::shared_ptr<AttributeBossList>	AddAttributeList ;
typedef K2Vector<ClassID>					RemoveAttributeList ;

/** Utilities related to styles (Paragraph, Character, Table, Object...)
e.g.
	<pre>Utils&;t;IStyleUtils&gt;()->MethodName( ... ) ;</pre>
	@ingroup text_util
*/
class IStyleUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTYLEUTILS };

	/**
		Return a unique style name within the specified style name table.
		@param pStyleTable is the style name table in which to make sName unique
		@param sName is the base name("My Para "), a number is appended to make the name unique like "My Para 1".
		@param appendCopy is set to true if translated "Copy" should be appended to the sName separated by a space
		before making the name unquie by appending a number.
		Example: "My copy Para" -> "My copy Para copy n",
		         "My Para copy" -> "My Para copy n",
				  where n is a number appended.

	*/
	virtual void CreateUniqueName( IStyleNameTable* pStyleTable, PMString& sName, bool16 appendCopy = kFalse) = 0 ;

	/**
		Returns a unique style name with in immediate children of a hierarchy.
		@param hierarchy [IN] Style set hierarchy which is to be searched.
		@param sName [INOUT] sName is the base name(My Para), a number is appended to make the name unique like My Para 1.
	*/
	virtual void CreateUniqueName(const IStyleGroupHierarchy* hierarchy, PMString& sName ) = 0 ;

	/** DEPRECATED: Use the version that doesn't pass ScriptInfo::RequestContext as a parameter.
		Create a command to change the attributes of a style
		@param context - the scripting request context
		@param style - the style to edit
		@param addAttribute - an attribute to add (or nil for none)
		@param removeAttribute - an attribute to remove (or kInvalidClass for none)
	*/
	virtual ICommand* CreateEditStyleCmd( const ScriptInfo::RequestContext& context, const IStyleInfo* style, const IPMUnknown* addAttribute = nil, ClassID removeAttribute = kInvalidClass ) = 0 ;
	virtual ICommand* CreateEditStyleCmd( const ScriptInfo::RequestContext& context, const IStyleInfo* style, const AddAttributeList& addAttrList, const RemoveAttributeList& removeAttrList ) = 0 ;

	
	/**
		Query the appropriate style name table
	*/
	virtual IStyleNameTable* QueryStyleNameTable( const IScript* script, const ScriptInfo::RequestContext& context, const ScriptID& desiredType ) = 0 ;

	/**
		Query the appropriate style set manager
	*/
	virtual IStyleGroupManager* QueryStyleGroupManager(const IScript* script, const ScriptInfo::RequestContext& context, const ScriptID& desiredType ) = 0 ;

	/**
		Get the applied style
	*/
	virtual ErrorCode GetStyleRef( const ScriptInfo::RequestContext& context, IScript* script, const ScriptID& propID, UIDRef& styleRef ) = 0 ;

	/**
		Handle the applied style properties
	*/
	virtual ErrorCode AccessStyle( IScriptRequestData* data, IScript* script, const ScriptID& propID, ScriptID dataLocation, bool16 clearOverrides = kTrue ) = 0 ;

	/**
		CopyStyle -- copy the info and the attributes from pFrom to pTo.
		if bCopyInherited is true, then the attributes will contain all attributes of the
		style plus what it is based on. StyleInfo is still from pFrom itself.
		@param pFrom - the style to copy
		@param pTo - the style to copy to
		@param bCopyInherited - whether to copy based on style
		@return false if pFrom == pTo already.
	*/
	virtual bool16 CopyStyle(const IStyleInfo *pFrom, IStyleInfo *pTo,  bool16 bCopyInherited ) = 0;

	/**
		CopyStyleInfo -- copy JUST the style info fields from pFrom to pTo.
		@param pFrom - the style to copy
		@param pTo - the style to copy to
	*/
	virtual void CopyStyleInfo(const IStyleInfo *pFrom, IStyleInfo *pTo) = 0;

	/**
	 Create a command to change the attributes of a style
	 @param style - the style to edit
	 @param addAttribute - an attribute to add (or nil for none)
	 @param removeAttribute - an attribute to remove (or kInvalidClass for none)
	 */	
	virtual ICommand* CreateEditStyleCmd( const IStyleInfo* style, const IPMUnknown* addAttribute = nil, ClassID removeAttribute = kInvalidClass ) = 0 ;
	virtual ICommand* CreateEditStyleCmd( const IStyleInfo* style, const AddAttributeList& addAttrList, const RemoveAttributeList& removeAttrList ) = 0 ;
    /**
        LogStyleApplied -- logs the highbeam data that a paragraph style is applied
        @param db - style data base
        @styleUIS - style UID
     */
    virtual void LogStyleApplied(IDataBase* db, const UID styleUID) = 0 ;
	
};

#endif	// __IStyleUtils__

