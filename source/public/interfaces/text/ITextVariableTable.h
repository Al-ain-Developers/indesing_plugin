//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextVariableTable.h $
//  
//  Owner:
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
#ifndef __ICalcTextVarTable__
#define __ICalcTextVarTable__

#include "IPMUnknown.h"
#include "TextID.h"

class ITextVariable;
class WideString;
class VariableTypeInfo;
class AddVariableInfo;
class ChangeVariableInfo;

/**
	@ingroup text_layout
*/
class ITextVariableTable : public IPMUnknown							// ##rk: this can go to private..
{
public:
	enum { kDefaultIID = IID_ITEXTVARIABLETABLE };
	static const int32 kInvalidIndex = -1;

	/** Returns the UID of the variable
	*/
	virtual UID LookupVariableUID(const WideString& varName) = 0;

	/**
	@note Unlike QueryVariable, a variable of this type doesn't have to exist in the table. This is static data instrinsic the this type of variable.
	 */
	virtual bool16 GetBaseTypeInfo(ClassID variableClassID, VariableTypeInfo* varInfo) const = 0;

	/** Returns the number of variables in the table.
	 */
	virtual int32 GetNumVariables() const = 0;

	/** Returns the Nth variable in the table
	*/

	virtual ITextVariable* QueryNthVariable(int32 n) const = 0;

	/** Gets ITextVariable based on the name (names are unique within the table)
	 */
	virtual ITextVariable* QueryVariable(const WideString& varName) const = 0;

	/** Add a variable via the AddVariableInfo data
	 */
	virtual bool16 AddVariable(const AddVariableInfo& newInfo) = 0;

	/** Add a variable of the following UID
	*/
	virtual bool16 AddVariable(UID newUID) = 0;

	/** Remove the name variable (names are unique within the table)
	 */
	virtual bool16 RemoveVariable(const WideString& varName) = 0;

	/** Change a variable of the following name (names are unique within the table)
	 */
	virtual bool16 ChangeVariable(const WideString& varName, const ChangeVariableInfo& chgInfo) = 0;
	/** Returns the Nth variable in the table.  Deprecated.
	@note FOR INTERNAL USE ONLY.
	 */
	virtual bool16 GetNthVariableObsolete(int32 n, AddVariableInfo* varInfo) const = 0;
};

#endif // __ICalcTextVarTable__
