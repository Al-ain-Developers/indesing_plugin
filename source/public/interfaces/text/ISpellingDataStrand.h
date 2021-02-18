//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISpellingDataStrand.h $
//  
//  Owner: hhorton
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

#ifndef _H_SPELLINGDATASTRAND
#define _H_SPELLINGDATASTRAND

#include "IPMUnknown.h"
#include "LinguisticID.h"

/** enum for valid spelling states */
typedef	enum SpellingState {kSpellingUnchecked = -1, kSpellingCorrect, kSpellingError, kIncorrectWord, kUncapitalizedWord,
    /** grammar errors */    kGrammarError, kRepeatedWord, kUncapitalizedStartOfSentence,
                            kNoteAnchor, kDeletedText} SpellingState;


class ITextModel;

/** 
	Interface for managing the text model's Spelling Data Strand
*/
class ISpellingDataStrand : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPELLINGDATASTRAND };

	/** mark insert damage for the spelling strand
		@param start				start text index
		@param length				character length
	*/
	virtual void MarkInsertDamage(TextIndex start, int32 length) = 0;

	/** mark delete damage for the spelling strand
		@param start				start text index
		@param length				character length
		@param paraStrandAfter		ignored
	*/
	virtual void MarkDeleteDamage(TextIndex start, int32 length, bool16 paraStrandAfter = kTrue) = 0;

	/** mark paste damage for the spelling strand
		@param start				start text index
		@param length				character length
		@return						pasted length
	*/
	virtual int32 MarkPasteDamage(TextIndex start, int32 length) = 0;

	/** mark change damage for the spelling strand
		@param start				start text index
		@param length				character length
		@param addOneToLength		ignored
	*/
	virtual void MarkChangeDamage(TextIndex start, int32 length, bool16 addOneToLength = kFalse) = 0;

	/** mark geometry damage for the spelling strand
		@param start				start text index
		@param length				character length
	*/
	virtual void MarkGeometryDamage(TextIndex start, int32 length) = 0;

	/** mark regen damage for the spelling strand
		@param start				start text index
		@param length				character length
	*/
	virtual void MarkRegenDamage(TextIndex start, int32 length) = 0;

	/** mark content damage for the spelling strand
		@param start				start text index
		@param length				character length
	*/
	virtual void MarkContentDamage(TextIndex start, int32 length) = 0;	

	/** set the spelling data state
		@param startpos				start text index
		@param numchars				character length
		@param spellingState		new spelling state
		@param model				text model
	*/
	virtual void SetSpellingDataState(TextIndex startpos, int32 numchars, SpellingState spellingState, ITextModel* model) = 0;

	/** get the spelling data run
		@param position		IN: start text index
		@param count		OUT: character length
		@param runBegin		OUT: run's start index
		@return				spelling state of the run
	*/
	virtual SpellingState GetSpellingDataRun(TextIndex position, int32 *count, TextIndex *runBegin = nil) = 0;

	/** set the damage start index
		@param model		text model
		@param t			start text index
	*/
	virtual void SetDamageStart(ITextModel* model, TextIndex t) = 0;

	/** get the damage start index
		@return  damage start index
	*/
	virtual TextIndex GetDamageStart(void) = 0;

	/** set the number of errors
		@param n		number of errors
	*/
	virtual void SetNumErrors(int32 n) = 0;

	/** mark paste damage for the spelling strand
		@return		number of errors
	*/
	virtual int32 GetNumErrors(void) = 0;
};

/** 
	Interface for getting/setting the Spelling State data in the Spelling Data Strand
*/

class ISpellingStateData : public IPMUnknown
{
public:
    enum { kDefaultIID = IID_ISPELLINGSTATECMDDATA };

 	/** Set the spelling state data
		@param spellingDataStrandRef			spelling data strand UIDRef
		@param modelRef							textmodel UIDRef
		@param spellingState					spelling state
		@param start							starting text index
		@param length							length of data
	*/
   virtual void Set(UIDRef& spellingDataStrandRef, UIDRef& modelRef, SpellingState spellingState, TextIndex start, int32 length) = 0;

	/** Get the state data's spelling strand's UIDRef
		@param ref		OUT: UIDRef of the spelling data strand
	*/
	virtual void GetSpellingStrandRef(UIDRef& ref) = 0;

	/** Get the state data's textmodel's UIDRef
		@param ref		OUT: text model's UIDRef
	*/
	virtual void GetModelRef(UIDRef& ref) = 0;

	/** Get the state data's SpellingState
		@param n		OUT: spelling state: spelling state
	*/
	virtual void GetSpellingState(SpellingState& spellingState) = 0;

	/** Get the state data's starting text index
		@param start	OUT: start index
	*/
	virtual void GetStartTextIndex(TextIndex& start) = 0;

	/** Get the state data's length
		@param length	OUT: character length
	*/
	virtual void GetLength(int32& length) = 0;
};

#endif
