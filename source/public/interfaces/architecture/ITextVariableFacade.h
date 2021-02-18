//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITextVariableFacade.h $
//  
//  Owner: David Stephens
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
#ifndef __ITextVariableFacade__
#define __ITextVariableFacade__

#include "IPMUnknown.h"
#include <map>
#include "StyleClashResolutionTypes.h"

class ITextVariableTable;
class ITextModel;
class IOwnedItem;
class VariableTypeInfo;
class AddVariableInfo;
class ChangeVariableInfo;
class ChangeVariableInstanceInfo;
//class StoryRange;
class UIDRef;
class ModelRange;
class ITextVariable;

/** A high level API for dealing with Text Variables.  To use this Facade, include
	this header file and the use the following example syntax:
	Utils<ITextVariableFacade>()->XXX( yyy );

	@note See ITextVariableSuite for descriptions of these methods as this is a mirror interface to that, with the exception that this takes a target ITextVariableTable
	<br>The Scripting module uses this interface directly, and the UI module(s) use this indirectly via the ITextVariableSuite, both of which determine and provide the varTable parameters
*/
class ITextVariableFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTVARIABLEFACADE };

	virtual ErrorCode GetVariableTypeInfo(ITextVariableTable* varTable, ClassID variableClassID, VariableTypeInfo* typeInfo) const = 0;

	virtual ErrorCode GetNumVariables(ITextVariableTable* varTable, int32* n) const = 0;

	virtual ErrorCode QueryNthVariable(ITextVariableTable* varTable, int32 n, ITextVariable *&var) const = 0;

	virtual ErrorCode AddVariable(ITextVariableTable* varTable, const AddVariableInfo& newInfo) const = 0;

	virtual ErrorCode RemoveVariable(ITextVariableTable* varTable, const WideString& varName) const = 0;

	virtual ErrorCode InsertVariable(ITextVariableTable* varTable, const WideString& varName, const ModelRange& insertAt, UIDRef* newVarInstance, bool16 isINXContext=kFalse) const = 0;

	virtual ErrorCode ChangeVariable(ITextVariableTable* varTable, const WideString& varName, const ChangeVariableInfo& chgInfo) const = 0;

	virtual ErrorCode FindLocationsUsed(ITextVariableTable* varTable, const WideString* varName, const ModelRange* searchRange, bool16 hiddenStories, K2Vector<ModelRange>& results) const = 0;

	virtual ErrorCode ChangeVariableInstance(IOwnedItem* ownedItem, const ChangeVariableInstanceInfo& chgInfo) const = 0;

	virtual ErrorCode LoadVariables(ITextVariableTable* varTable, const IDFile& sourceFile,
													const std::map<PMString, bool32>& importMap,
													const std::map<PMString, bool32>& clashMap,
													const std::map<PMString, StyleClashResolutionTypes::StyleClashResolutionStrategy>& resolveMap,
													const StyleClashResolutionTypes::GlobalClashResolutionStrategy& gcrStrategy) const = 0;
};

#endif	// __IFootnoteFacade__
