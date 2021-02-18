//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextState.h $
//  
//  Owner: emenning
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
#ifndef __ITextState__
#define __ITextState__

#include "IPMUnknown.h"
#include "TextID.h"

class AttributeBossList;


/**	The ITextState interface is used to store information about attributes that are applied
	to the "insertion point" or the "text caret".  The next insertion will use these attributes.
	However, if the selection is changed, then these attributes are lost forever.
	The ITextState interface is off the document. Each document has only 1 set of attributes
	active on an insertion point. It could be argued that each window could have it's own, but
	that is not true at this time.
	@ingroup text_story
*/
class ITextState: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTSTATE };

		/** Is there information in this object for this story and position?
			@param charStrand is the UID of the character strand of the story in question.
			@param pos is the absolute position in the story in question.
			@return kTrue if this interface has information stored for the position in question.
		*/
		virtual bool16 HasStateInfoFor(UID charStrand, TextIndex pos) const = 0;

		/** Is there a character style stored in this object for this story and position?
			@param charStrand is the UID of the character strand of the story in question.
			@param pos is the absolute position in the story in question.
			@return kTrue if this interface has a style stored for the position in question.
		*/
		virtual bool16 HasStateStyleFor(UID charStrand, TextIndex pos) const = 0;

		/** Where was the last position? Used as a shortcut when determining whether to
			look at this object's data further.
			@return the absolute position in whatever story.
		*/
		virtual TextIndex LastStateInfoFor() const = 0;

		/** Clear the information in the "caret". The data is cleared after it is used during insert, for example.
		*/
		virtual void ClearStateInfo() = 0;

		/** Upon delete, we automatically set the text state with the delete attributes so the next insertion
			looks like the deleted text. There are minor behavior differences.
			@return kTrue if the ITextState was loaded by a delete (instead of applying to the caret).
		*/
		virtual bool16 WasDeleteState() const = 0;

		/** Set the flag specifying whether we are loaded due to a delete.
			@param b specifies whether the data was due to a delete.
		*/
		virtual void IsDeleteState(bool16 b) = 0;


		/** Apply attributes to the caret for the a particular story and position.
			@param charStrandUID is the character strand's UID in the story being set.
			@param where is the absolute position.
			@param over is a list of attributes to store at the location.
		*/
		virtual void ApplyToState(UID charStrandUID, TextIndex where, const AttributeBossList* over) = 0;

		/** Apply a character style to the caret for the a particular story and position.
			@param charStrandUID is the character strand's UID in the story being set.
			@param where is the absolute position.
			@param style is the character style UID to store at the location.
		*/
		virtual void ApplyToStateStyle(UID charStrandUID, TextIndex where, UID style) = 0;

		/** Get the character style applied to the ITextState object.
			@return the UID of the character style stored on the "caret".
		*/
		virtual UID GetStateStyle() const = 0;

		/** Get the character attributes (local overrides) applied to the ITextState object.
			@return a pointer to the list of character attributes stored on the "caret".
		*/
		virtual const AttributeBossList* PeekStateOverrides() const = 0;

		/** What is the character strand UID that we are set for?
			@return the UID of the character strand of the story for which we are set.
		*/
		virtual UID GetStateCharStrand() const = 0;

		/** What is the location of the data stored here?
			@return the absolute position in the story of the data stored.
		*/
		virtual TextIndex GetStatePosition() const = 0;
};

#endif
		// __ITextState__

