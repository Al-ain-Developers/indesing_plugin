//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITextVariableSuite.h $
//  
//  Owner: rkamicar
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
//  
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _ITextVariableSuite_
#define _ITextVariableSuite_

#include "IPMUnknown.h"
#include "StyleClashResolutionTypes.h"
#include <map>

class ModelRange;
class UIDRef;
class IOwnedItem;
class AddVariableInfo;
class VariableTypeInfo;
class ChangeVariableInstanceInfo;
class ChangeVariableInfo;
class IDFile;
#include "ITextVariable.h"

/** ITextVariableSuite

	@note See IFootnoteSettings for descriptions of most of these methods as this is a mirror interface to that.
*/
class ITextVariableSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTVARIABLE_ISUITE };

	/** Can a variable be inserted?  (i.e. does the current selection make sense for it)
	*/
	virtual bool16 CanInsertTextVariable(void) const = 0;

	/** Can the options be set?  (i.e. does the current selection make sense for opening the dialog)
	*/
	virtual bool16 CanManageTextVariables(void) const = 0;

	/** Manage text variables.
	 */
	virtual ErrorCode ManageVariables() = 0;

	/** Return basic information on the given variable.
	*/
	virtual ErrorCode GetVariableTypeInfo(ClassID variableClassID, VariableTypeInfo* typeInfo) const = 0;

	/** Add a variable to the global variable table.
	@param newInfo The description of the new variable
	*/
	virtual ErrorCode AddVariable(const AddVariableInfo& newInfo) const = 0;

	/** Remove a variable from the global variable table.
	@param varName The name of the variable to remove.
	@note this only removes the variable from the table, any references to the variable in the text will remain (and result in an unreferenced variable).
	*/
	virtual ErrorCode RemoveVariable(const WideString& varName) const = 0;

	/** Insert a variable into the text.
	@param varName The name of the variable to insert.
	@param formatterClassID The format for the desired variable
	@param newVarInstance OUT if non-nil, will point to the UIDRef of the newly inserted variable
	*/
	virtual ErrorCode InsertVariable(const WideString& varName, UIDRef* newVarInstance) const = 0;

	/** Change one or more properties of a variable.
	@param chgInfo The desired changes
	*/
	virtual ErrorCode ChangeVariable(const WideString& varName, const ChangeVariableInfo& chgInfo) const = 0;

	/** Find one or more variables in a document or story.
	@param varName Match all variables with this name. If nil, matches all variables.
	@param searchRange Match all variables within this range (required).
	@param results Any variables found matching the given parameters.
	*/
	virtual ErrorCode FindLocationsUsed(const WideString* varName, const ModelRange* searchRange, bool16 hiddenStories, K2Vector<ModelRange>& results) const = 0;

	/** Change one or more properties of a variable.
	@param chgInfo The desired changes
	*/
	virtual ErrorCode ChangeVariableInstance(IOwnedItem* ownedItem, const ChangeVariableInstanceInfo& chgInfo) const = 0;

	/** Load variable from the given source file according to the other parameters.
		@param sourceFile		The file to load from
		@param importMap 		Import styles.
		@param clashMap 		Styles that are conflict with existing styles.
		@param resolveMap		Result styles after resolving the conflicts.
		@param gcrStrategy		The Global clash resolution strategy.
	*/
	virtual ErrorCode LoadVariables(const IDFile& sourceFile,
													const std::map<PMString, bool32>& importMap,
													const std::map<PMString, bool32>& clashMap,
													const std::map<PMString, StyleClashResolutionTypes::StyleClashResolutionStrategy>& resolveMap,
													const StyleClashResolutionTypes::GlobalClashResolutionStrategy& gcrStrategy) = 0;
};

#endif // _ITextVariableSuite_
