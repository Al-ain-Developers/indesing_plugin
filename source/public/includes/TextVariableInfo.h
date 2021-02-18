//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextVariableInfo.h $
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
#ifndef _TextVariableInfo_
#define _TextVariableInfo_

/** Variable information for adding a new variable to the table of variables.
*/
class PUBLIC_DECL AddVariableInfo
{
private:
	/** Initialize */
	void Init();

	friend class TextVariableImpl;

	/** The name of the variable.
	*/
	WideString	name;
	/** The contents of the variable.
	@note This is often empty.
	*/
	WideString	contents;
	/** The class id of the base variable (e.g. Custom Text Variable, Date Variable, etc)
	*/
	ClassID		baseTypeID;
	/** The class that can format this variable - is a member of formattingID
	*/
	ClassID		formatterID;
	/** uid of the char/para running header/footer if applicable
	*/
	UID			fuid;
	/** Quick access private data for this variable, if any
	*/
	int32		flags;
	/** The string to place before the calculated part of the variable.
	*/
	WideString	textBefore;
	/** The string to place after the calculated part of the variable.
	*/
	WideString	textAfter;

	void ReadWrite(IPMStream *s, ImplementationID prop);

public:
	/** */
	AddVariableInfo();

	/** equality */
	bool16 operator== (const AddVariableInfo &other) const;
	bool16 operator!= (const AddVariableInfo &other) const;

	/** Helper enum for the scope types of the TotalPagesVariable's flags
	*/
	enum ScopeStyles
	{
		kSection = 0,
		kDocument
	};

	/** Helper enum for the bit types of the Char/ParaVariable's flags
	*/
	enum UseStyles
	{
		kFirstInPage = 0,
		kLastInPage,
	};

 	const WideString& GetName() const {return name;}
 	/** Sets name
 	 */
 	void SetName(const WideString &s) {name = s;}
 	/** Gets contents
 		@note Often empty
 	*/
 	const WideString& GetContents() const {return contents;}
 	/** Sets contents
 	 */
 	void SetContents(const WideString &s) {contents = s;}
 	/** Get class id of the base variable (e.g. Custom Text Variable, Date Variable, etc)
 	 */
 	const ClassID GetBaseTypeID() const {return baseTypeID;}
 	/** Set class id of the base variable (e.g. Custom Text Variable, Date Variable, etc)
 	 */
 	void SetBaseTypeID(ClassID id) {baseTypeID = id;}
 	/** Get class that can format this variable
 	 */
 	const ClassID GetFormatterID() const {return formatterID;}
 	/** Set formmater ID
 	 */
 	void SetFormatterID(ClassID id) {formatterID = id;}
	/** Get uid of desired style (running header footer only)
	 */
	const UID GetUID() const {return fuid;}
	/** Set uid of desired style (running header footer only)
	 */
	void SetUID(UID uid) {fuid = uid;}
	/** Get Flags (generally recommend using flag getters instead as this contains variable specific flags)
	 */
	int32 GetFlags() const {return flags;}
	/** Set Flags (generally recommend using flag setters instead)
	 */
	void SetFlags(int32 b) {flags = b;}
 	/** Get string to place before the calculated part of the variable.
	 */
 	const WideString& GetTextBefore() const {return textBefore;}
 	/** Set string to place before the calculated part of the variable.
	 */
 	void SetTextBefore(const WideString &s) {textBefore = s;}
 	/** Get string to place after the calculated part of the variable.
	 */
 	const WideString& GetTextAfter() const {return textAfter;}
 	/** Set string to place after the calculated part of the variable.
	 */
 	void SetTextAfter(const WideString &s) {textAfter = s;}
	/** Get Scope
	 */
	ScopeStyles GetScope() const;
	/** Set Scope
	 */
	void SetScope(AddVariableInfo::ScopeStyles scope);
	/** Get Use
	 */
	UseStyles GetUse() const;
	/** Set Use
	 */
	void SetUse(AddVariableInfo::UseStyles use);
	/* Get Delete End Punctuation
	 */
	bool16 GetDeleteEndPunctuation() const;
	/* Set Delete End Punctuation
	 */
	void SetDeleteEndPunctuation(bool16 b);
	/** Get Include path extension
	 */
	bool16 GetIncludeExtension() const;
	/** Set Include path extension
	 */
	void SetIncludePath(bool16 b);
	/** Get Include Path
	 */
	bool16 GetIncludePath() const;
	/** Set Include Path
	 */
	void SetIncludeExtension(bool16 b);
	/** Get Emperor Date
	 */
	bool16 GetEmperorDate() const;
	/** Set Emperor Date
	 */
	void SetEmperorDate(bool16 b);

	typedef object_type data_type;
};

#endif // _TextVariableInfo_

