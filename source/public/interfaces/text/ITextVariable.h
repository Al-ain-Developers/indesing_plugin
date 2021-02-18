//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextVariable.h $
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
//  The ITextVariable interface allows installable text variables.
//  
//========================================================================================

#pragma once
#ifndef __ITEXTVARIABLE__
#define __ITEXTVARIABLE__

#include "IPMUnknown.h"
#include "TextID.h"
#include "RequestContext.h"
#include "TextVariableInfo.h"

class PMString;
class IDataBase;

/** A Text Variable. This is a representation of a variable within the variable table. It is the definition of the variable
	and can, with some added information (namely positioning information) produce a text string that should be used as a
	substitute for the marker within the story.
	<br>
	Each text variable contains a base type name, whether it's visible in the UI or not, and a formatting service type (e.g. number, date or string).
	These are the intrinsic properties of a variable of a specific type.
	<br>
	Added to it at creation time are a set of properties that further define this type of variable. These are the variable name itself,
	a formatter specific to the formatting service type, a string representing the contents of the variable, and a UID to a piece of private data specific
	to this variable.  For example, the TotalPagesVariable is a Number Variable using a NumberingService and is visible in the UI. Furthermore, the user can
	specify that it has the name "Roman Page Count", it's formatted with the Upper Case Roman Numeral number formatter, and has no private data, nor contents.
	<br>
	To create this object, the ITextVariableTable can be queried with the name of the variable. It returns the fully realized object variable instance that can produce
	the "value" of the variable.  The value of the variable is the unformatted, native representation of the variable. For instance, for the TotalPagesVariable, it could be
	the number 7, for the CreateDateVariable it will be an IDTime.
	<br>
	The value of the variable is used to produce the result, which is a string representation of the value.  For instance, using the above example for the TotalPagesVariable,
	the would be the string "5" if the Arabic Number Formatter was used, or "V" if the Upper Case Roman Number Formatter was used.
	<br>
	To produce the result, dynamic information is given and the resulting string returned.
	The dynamic information consists of: the "contents" of the variable (representing either nothing, the value or the code to be processed,
	depending on the variable type), the formatter type (which converts it to a string), and positional information (in the form of a UIDRef
	to an IOwnedItem).
	<br>
	A variable lives in the variable table. A variable instance (or a reference to a variable) lives in the story and points to a variable in the variable table.
*/
class ITextVariable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTVARIABLE };

	/** Helper enum for the scope types of the TotalPagesVariable's last page number
	*/
	enum ScopeStyles
	{
		kSection = 0,
		kDocument
	};

	/** Helper enum for the bit types of the Char/ParaVariable's running header/footer
	*/
	enum UseStyles
	{
		kFirstInPage = 0,
		kLastInPage,
	};

	/** Returns the *translated* name of the variable.
	@return Reference to WideString
	*/
 	virtual const WideString& GetName() const =0;

 	/** Sets translated name of variable
 	 */
 	virtual void SetName(const WideString &s) =0;

 	/** Gets contents(currently only used in format string for dates and custom text contents)
 		@note Often empty
 	*/
 	virtual const WideString& GetContents() = 0;

 	/** Sets contents (currently only used in format string for dates and custom text contents)
  		@note Often empty
	 */
 	virtual void SetContents(const WideString &s) = 0;

 	/** Get class id of the base variable (e.g. Custom Text Variable, Date Variable, etc)
 	 */
 	virtual const ClassID GetBaseTypeID() const  = 0;

 	/** Set class id of the base variable (e.g. Custom Text Variable, Date Variable, etc)
 	 */
 	virtual void SetBaseTypeID(ClassID id)  = 0;

 	/** Get class that can format this variable
 	 */
 	virtual const ClassID GetFormatterID() = 0;

 	/** Set formmater ID
 	 */
 	virtual void SetFormatterID(ClassID id)= 0;

	/** Get uid of desired style (running header footer only)
	 */
	virtual const UID GetUID() const  = 0;

	/** Set uid of desired style (running header footer only)
	 */
	virtual void SetUID(UID uid) =0;

	/** Get the string to place before the calculated part of the variable
	*/
 	virtual const WideString& GetTextBefore() = 0;

 	/** Set string to place before the calculated part of the variable.
	 */
 	virtual void SetTextBefore(const WideString &s)  = 0;

 	/** Get string to place after the calculated part of the variable.
	 */
 	virtual const WideString& GetTextAfter() = 0;

 	/** Set string to place after the calculated part of the variable.
	 */
 	virtual void SetTextAfter(const WideString &s) = 0;

	/** Get Scope
	 */
	virtual ScopeStyles GetScope() const = 0;

	/** Set Scope
	 */
	virtual void SetScope(ScopeStyles scope) = 0;

	/** Get Use
	 */
	virtual UseStyles GetUse() const = 0;

	/** Set Use
	 */
	virtual void SetUse(UseStyles use) = 0;

	/* Get Delete End Punctuation
	 */
	virtual bool16 GetDeleteEndPunctuation() const = 0;

	/* Set Delete End Punctuation
	 */
	virtual void SetDeleteEndPunctuation(bool16 b) = 0;

	/** Get Include path extension
	 */
	virtual bool16 GetIncludeExtension() const = 0;

	/** Set Include path extension
	 */
	virtual void SetIncludePath(bool16 b) = 0;

	/** Get Include Path
	 */
	virtual bool16 GetIncludePath() const = 0;

	/** Set Include Path
	 */
	virtual void SetIncludeExtension(bool16 b) = 0;

	/** Get Emperor Date
	 */
	virtual bool16 GetEmperorDate() const = 0;

	/** Set Emperor Date
	 */
	virtual void SetEmperorDate(bool16 b) = 0;

	/** Get all flags
	@return all boolean flags for a given variable
	*/
	virtual int32 GetFlags() const = 0;

	/** Get all flags
	@return all boolean flags for a given variable
	*/
	virtual void SetFlags(int32 flags) = 0;

 	/** Convert the variable to a string.
 	@param target - the owned item that refers to this variable.  Can also be a non-owned item, in which case an approximate result will be returned - useful for example text.
 	@param s - out: the formatted string representation of the variable's value.
	@param uniformApproximateWidth - if kTrue, the target is possibly not the context in which the variable will be used.
	The variable will return a representative string based on the variable's current information (e.g. trial file name).
	*/
	virtual void VariableToString(const UIDRef& target, WideString& s, bool16 uniformApproximateWidth = kFalse) = 0;

	/** Get the base type name for a given variable
	@param typeName returned base type name for the variable
	*/
	virtual void GetVariableTypeName(WideString &typeName) const = 0;

	/**
		Returns the script enumerator corresponding to this type of variable in the given scripting DOM
	*/
	virtual ScriptID GetTextVariableTypeScriptID( const ScriptInfo::RequestContext& context ) const = 0;

	/**
		Returns the options object associated with this type of variable in the given scripting DOM
	*/
	virtual ScriptID GetTextVariableOptionsScriptID( const ScriptInfo::RequestContext& context ) const = 0;

	/**
		Returns the Service ID of the service that's used for formatting the value of the variable, if any.
	@return kInvalidService if there is no formatter for this variable, else the appropriate ServiceID
	@note Primarily used for scripting and UI, since the formatting is automatically applied.
	*/
	virtual ServiceID GetFormatterServiceProviderID() const = 0;

	/** Tells caller if two variables are conceptually equal
	@param other variable to compare with
	@return kTrue if equivalent
	*/
	virtual bool16 IsEquivalent(const ITextVariable *other) const = 0;

	/**
	A variable is private if it does not appear in the UI to the user. The
	variables will have an escape character as the first character in their
	name - something that the UI won't let you put in.
	@return kTrue if the Variable is private.
	*/
	virtual bool16 IsPrivate() const = 0;

	/** Avoid this call if possible - this is legacy and is deprecated.
	@param info information in the CS3 version of the text variable.
	@note This may be a subset in the future and should be avoided.
	*/
	virtual void Get(AddVariableInfo& info) const = 0;

	/** Avoid this call if possible - this is legacy and is deprecated.
	@param info information needed to fill out the CS3 text variable.
	@note This can change in the future and should be avoided.
	*/
	virtual void Set(const AddVariableInfo& info) = 0;

};

#endif // __ITEXTVARIABLE__
