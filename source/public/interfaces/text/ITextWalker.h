//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextWalker.h $
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
#ifndef __ITextWalker__
#define __ITextWalker__

#include "IPMUnknown.h"
#include "TextWalkerServiceProviderID.h"
class IDocument;
class ITextModel;
class ITextWalkerClient;
class IProgressBarControlData;
class ITextWalkerScope;
class ITextFocus;
class IFindChangeOptions;

//----------------------------------------------------------------------------------------
// Interface ITextWalker
//----------------------------------------------------------------------------------------

/** 
	@ingroup text_find
*/
class ITextWalker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTWALKER};

	/** 
		Initializes text walker.
		
		@param pClient	Used to initialize text walker client .
		@param pScope	Used to initialize text walker scope.
		@param pOptions	Used to initialize find change options.
		@param token		Used to initialize cursor token.
	*/
	virtual void 		Initialize (ITextWalkerClient *pClient, 
									ITextWalkerScope* pScope, 
							 		IFindChangeOptions* pOptions, 
							 		void* token = nil) = 0;
	/** 
		Walks the text scope.
		
		@return bool16	kTrue if successfully walked the scope.
	*/
	virtual	bool16		Walk() = 0;
	
	/** 
		Moves the walker, returns the amount.

		@param nDelta	The distance to move the walker position.

		@return int32		real distance which walker position moved.
	*/
	virtual	int32		MoveBy( int32 nDelta ) = 0;				

	/** 
		Moves the walker.

		@param nPosition	Text index to move the walker position to.
	*/
	virtual	void		MoveTo( TextIndex nPosition ) = 0;			

	/** 
		Suspends the walking.
	*/
	virtual	void		Suspend() = 0;							

	/** 
		Halts the walking.
	*/
	virtual	void		Halt() = 0;		
	
	/** 
		Returns the suspend state.

		@return bool16	kTrue if the walker is suspended.
	*/
	virtual	bool16		IsSuspended() const = 0;					

	/** 
		Returns whether walking has been started.

		@return bool16	kTrue if the walker has been started.
	*/
	virtual	bool16		IsWalking() const = 0;						

	/** 
		Returns the last index of the current selection.

		@return TextIndex		last index of the current selection.
	*/
	virtual TextIndex	GetWalkerPosition() const = 0;				

	/** 
		Queries text walker scope.

		@return ITextWalkerScope*		text walker scope associated with text walker.
	*/
	virtual ITextWalkerScope*	QueryScope()  = 0;

	/** 
		Queries text walker client.

		@return ITextWalkerClient*		text walker client associated with text walker.
	*/
	virtual ITextWalkerClient*	QueryClient ()  = 0;

	/** 
		Returns current cursor token.

		@return void*		current cursor token.
	*/
	virtual void *		GetCursorToken() = 0;
	
	/** 
		Sets the client focus for current cursor token.

		@param nStart	start text index to set focus to.
		@param nLength	length of the text to set focus to.
	*/
	virtual	void		SetClientSelection( TextIndex nStart, int32 nLength ) = 0;

	/** 
		Gets the client focus for current cursor token.
		
		@param pStart		[OUT] start text index of retrieved focus.
		@param pLength		[OUT] length of the text of retrieved focus.

		@return ITextFocus*	Client focus retrieved.
	*/
	virtual	ITextFocus*	GetClientSelection(TextIndex *pStart, int32* pLength) const = 0;

	/** 
		Resets cursor range to start of the story.

		@param delta			Distance to advance for the cursor range.
		
		@return bool16	 	kTrue if range was adjusted successfully.
	*/
	virtual bool16		AdjustRangeToStoryStart(int32 delta) = 0;

	/** 
		Resets cursor range to end of the story.

		@param delta			Distance to recede for the cursor range.
		
		@return bool16	 	kTrue if range was adjusted successfully.
	*/
	virtual bool16		AdjustRangeToStoryEnd(int32 delta) = 0;

	/** 
		This method is called when we are a full story scope and we wish to
		limit the walk to the end of the story. In this regard we are really
		trying to interrupt the full walk and stop at the bottom.
		If we already have passed the end and are wrapping around then this does
		nothing.
	*/
	virtual void 		ExtendCurrentRangeToEndOfStory() = 0;

	/** 
		This method is called when we are a partial (end-of-story) scope and we
		wish to limit the walk to the end of the story. Although we expect to
		only be called with end-of-story scope, this algorithm will extend any
		scope to the full story.		
	*/
	virtual void 		ExtendCurrentRangeToStory() = 0;
	
	/** 
		Returns find change options.

		@return IFindChangeOptions*	 	find change options associated with text walker.
	*/
	virtual IFindChangeOptions* QueryFindChangeOptions() = 0;

	/** 
		This method is called when moving backward and change of current range is 
		undesirable. Via this function a lock can be enabled which will disable change 
		in the current range.
		Note: For every call for a lock there should be a corresponding call for the unlock too. 

		@param state	If value is kTrue, the lock is turned on and for the value kFalse, lock is turned off.
	*/
	virtual void 		SetStateForRangeLock(bool16 state) = 0;

	/**
		Returns whether walking has been completed.

		@return bool16	kTrue if the walker has been completed.
	*/

	virtual bool16  IsCompleted() const = 0;
};

/** 
	@ingroup text_find
*/
class ITextWalkerClient : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTWALKERCLIENT};

	/** 
		Client operation when text walker is starting.

		@param pWalker	text walker which is starting.
		@return bool16	kTrue if operation succeeded	.
	*/
	virtual	bool16	OnStart( ITextWalker *pWalker ) = 0;

	/** 
		Client operation when text walker is ending.

		@param pWalker	text walker which is ending.
		@return bool16	kTrue if operation succeeded	.
	*/
	virtual bool16	OnEnd( ITextWalker *pWalker ) = 0;
	
	/** 
		Client operation when text walker is resuming.

		@param pWalker	text walker which is resuming.
		@return bool16	kTrue if operation succeeded	.
	*/
	virtual	bool16	OnResume( ITextWalker *pWalker ) = 0;

	/** 
		Client operation when text walker is suspending.

		@param pWalker	text walker which is suspending.
		@return bool16	kTrue if operation succeeded	.
	*/
	virtual bool16	OnSuspend( ITextWalker *pWalker ) = 0;

	/**	
		Client operation when text walker moves to next position.

		@param pWalker	Text walker which moves to next position.
		@param pModel	Text model where moves happens.
		@param nPosition	Previous walker position.
		@param nStartRange	New start position of text walker.
		@param nEndRange	New end position of text walker.
		@param startRangePrcnt	Percentage of the distance where start position moved.
		@param endRangePrcnt		Percentage of the distance where end posistion moved.
		@param rangeAdjustable	To deal with problem of starting the search in the middle
								of a word we adjust the starting point to the first position
								we have found something. This allows the search to wrap
								around (if that's the scope) and find the word we started on.
	
		@return bool16	kTrue if the operation succeeded.
	 */
	virtual	bool16	OnNextPosition(ITextWalker *pWalker, ITextModel *pModel,
									TextIndex nPosition,
									TextIndex nStartRange, TextIndex nEndRange,
									int32 startRangePrcnt, int32 endRangePrcnt,
									bool16 rangeAdjustable) = 0;

	/**	
		Client operation for start of a story.

		@param pWalker	Text walker where the story starts.
		@param storyUID	story UID.
	
		@return bool16	kTrue if the operation succeeded.
	 */
	virtual	bool16	OnStoryStart( ITextWalker *pWalker, UID storyUID ) = 0;

	/**	
		Client operation for end of a story.

		@param pWalker	Text walker where the story ends.
	 */
	virtual	void	OnStoryEnd( ITextWalker *pWalker ) = 0;

	/**	
		Client operation for start of a document.

		@param pWalker	Text walker where the document starts.
		@param newDoc	document which started.

		@return bool16	kTrue if the operation succeeded.
	 */
	virtual	bool16	OnDocumentStart( ITextWalker *pWalker, const UIDRef &newDoc ) = 0;

	/**	
		Client operation for end of a document.

		@param pWalker	Text walker where the document ends.
	 */
	virtual	void	OnDocumentEnd( ITextWalker *pWalker) = 0;

	/**	
		Sets replacement count.

		@param count		Replacement count to set to.
	 */
	virtual void	SetReplacementCount(int32 count) = 0;

	/**	
		Gets replacement count.

		@return int32		Replacement count retrieved.
	 */
	virtual int32	GetReplacementCount() = 0;

	/**
		Does client want to update text range and wants to move text walker.
		If client will return kFalse, on next walk client will get same startIndex
		and endIndex. It's usefull for cases where client wants to check many attribute
		in same range.
		If you are not sure what to return, return kTrue.

		@return bool16	kTrue if the client wants to update text range and want to mo.
	 */

	virtual bool16  UpdateTextRange() = 0;
};

#endif
