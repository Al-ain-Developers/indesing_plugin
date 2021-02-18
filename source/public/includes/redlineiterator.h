//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/redlineiterator.h $
//  
//  Owner: Eric Menninga
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __RedlineIterator__
#define __RedlineIterator__

#include "IPMFont.h"

class VOSRedlineChange;
class VOS_RedlineObject;
class RangeData;

/**	This class provides a way to iterate thru tracked changes.  Create a new iterator using IRedlineDataStrand::NewRedlineIterator(), 
	the caller is responsible for destroying the iterator.
	@see IRedlineDataStrand
	@see VOSRedline.h

	When text is deleted, a change record is placed on a vos redline object on the character that followed the deleted text and the text
	is copied to a story thread so that it can be retrieved and displayed in galley view.  When text is inserted, a change record is placed
	on a vos redline object in place and it's length is the number of characters inserted.

	If the character following text that is deleted is an insert change then we have a situation where the insert change is nested.  In this 
	case, it is possible to iterate thru changes and the current position would be the same even though the iterator incremented/ecremented.
	Calling the accessor methods will return the appropriate change record information given the state of an internal flag or the useUI flag if
	passed when the iterator was constructed (via newredlineiterator).  Accepting a nested insert will not affect the delete change; however,
	rejecting a nested insert will also reject the delete change.
*/
class RedlineIterator
{
	public:
		/** Destructor */
		virtual ~RedlineIterator();
		
		/**	Move iterator to beginning of the story, text position = 0.
		*/
		virtual void MoveToBeginning();
		/**	Move iterator to specified text position at the first change record (default)
			or the change specified, returns false if text position is off the end of the story.
			@param t IN the text index to move to
			@param c IN the change index to move to
			@return kTrue if moved the iterator
		*/
		virtual bool16 MoveToPosition(TextIndex t, int32 c = -1) = 0;
		/**	Returns current text position of the iterator.
			@param changePos OUT position of the change at this text index
			@param numChanges OUT number of changes at this text position
			@return current change text index
		*/
		virtual TextIndex GetCurrentPosition(int32 *changePos = nil, int32 *numChanges = nil) = 0;
		/**	Returns the length of the vos redline object.
			Note: for delete changes this is always 1, to get the length of the delete 
			text use DescribeChangeContent() and examine the PMString.
			@return length of the vos redline object
		*/
		virtual int32 GetCurrentLength() = 0;

		/**	Accepts the current change record, returns kFalse if no change to accept or
			there was error processing accept command.
			@param range IN the text range to accept, nil means accept current change only
			@param doingAcceptAll IN whether or not accepting all changes, passed to command
			@param restoreSelection IN whether or not selection should restore, passed to command
			@return kTrue if successfully accepted the change
		*/
		virtual bool16 ProcessAccept(const RangeData* range = nil, bool16 doingAcceptAll = kFalse, bool16 restoreSelection = kFalse);
		/**	Rejects the current change record, returns kFalse if no change to reject or
			there was error processing reject command.
			@param range IN the text range to reject, nil means reject current change only
			@param doingRejectAll IN whether or not rejecting all changes, passed to command
			@param restoreSelection IN whether or not selection should restore, passed to command
			@return kTrue if successfully rejected the change
		*/
		virtual bool16 ProcessReject(const RangeData* range = nil, bool16 doingRejectAll = kFalse, bool16 restoreSelection = kFalse);

		/**	Accepts the current change record and increments to the next change record,
			returns false if there were not records beyond the accepted change.	
			@param range IN the text range to accept, nil means accept current change only
			@param doingAcceptAll IN whether or not accepting all changes, passed to command
			@param restoreSelection IN whether or not selection should restore, passed to command
			@return kTrue if incremented the iterator
		*/
		virtual bool16 ProcessAcceptIncrement(const RangeData* range = nil, bool16 doingAcceptAll = kFalse, bool16 restoreSelection = kFalse);
		/**	Rejects the current change record and increments to the next change record,
			returns false if there are no records beyond the rejected change.
			@param range IN the text range to reject, nil means reject current change only
			@param doingRejectAll IN whether or not rejecting all changes, passed to command
			@param restoreSelection IN whether or not selection should restore, passed to command
			@return kTrue if incremented the iterator
		*/
		virtual bool16 ProcessRejectIncrement(const RangeData* range = nil, bool16 doingRejectAll = kFalse, bool16 restoreSelection = kFalse);
		/**	Rejects the current change record and decrements to the previous change record,
			returns false if there are no records before the rejected change.
			@param range IN the text range to reject, nil means reject current change only
			@param doingRejectAll IN whether or not rejecting all changes, passed to command
			@param restoreSelection IN whether or not selection should restore, passed to command
			@return kTrue if decremented the iterator
		*/
		virtual bool16 ProcessRejectDecrement(const RangeData* range = nil, bool16 doingRejectAll = kFalse, bool16 restoreSelection = kFalse);
		/**	Increments to the next change record, returns false if there are
			no records beyond the current record.
			@param skipUnchanged IN whether or not to skip vos redline object without a change record
			@return kTrue if incremented the iterator
		*/
		virtual bool16 Increment(bool16 skipUnchanged) = 0;
		/**	Decrements to the previous change record, returns false if there are no
			previous records.
			@param skipUnchanged IN whether or not to skip vos redline object without a change record
			@return kTrue if decremented the iterator
		*/
		virtual bool16 Decrement(bool16 skipUnchanged) = 0;
		
		/**	Returns the current change record, nil if there is no current change record,
			and sets pPosition equal to GetCurrentPosition and pLength equal to GetCurrentLength.
			Note: the item pointed to by the returned value from is allocated with new, 
			the caller is responsible for deallocating the memory.
			@param pPosition OUT current change's text index
			@param pLength OUT current change's length
			@return current redline object
		*/
		virtual const VOSRedlineChange* GetCurrentChangeRecord(TextIndex *pPosition = nil, int32 *pLength = nil);
		/**	Returns the current vos redline object, nil if there is no current object.
			@return current redline object
		*/
		virtual const VOS_RedlineObject* QueryCurrentObject();

		/**	Sets user equal to the author of the current change record.
			@param user OUT current user name
		*/
		virtual void DescribeUser(PMString& user);
		/**	Sets type equal to the type of the current change record.
			Current values are "RL Insert" or "RL Delete"; to determine if the change
			is moved text versus added text check for type of "RL Insert" and use
			the GetIsMovedText() method for VOSRedlineChange objects.
			@param type OUT current change type
		*/
		virtual void DescribeType(PMString& type);
		/**	Sets time equal to the time stamp of the current change record.
			@param time OUT current change time stamp
		*/
		virtual void DescribeTimeStamp(PMString& time);
		/**	Sets detail equal to the deleted text string of the current delete text
			change record (if any), constrained by the maxLength.
			@param detail OUT current deleted text content string
			@param maxLength IN constrain detail param to this length
			@return UIDRef of the deleted text owned item
		*/
		virtual UIDRef DescribeChangeContent(PMString& detail, int32 maxLength = 32);
};

#endif	// __RedlineIterator__
		
