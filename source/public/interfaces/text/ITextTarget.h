//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextTarget.h $
//  
//  Owner: Richard Rodseth
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
	#ifndef _ITextTarget_
	#define _ITextTarget_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "TextID.h"

//================================================================================================



class ITextModel;
class ITextFocus;
class RangeData;

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________

/** ITextTarget (analogous to ILayoutTarget and ICellFocus) represents a range of a text model for 
	use by suites on the text suite boss (inherited by the text selection boss).
	
	The resemblance to ITextFocus is striking and ITextTarget currently stores and exposes an ITextFocus. 
	(formerly store in the IOldSelection implementation)
	Eventually the focus boss and concrete selection boss might become one, in which case one of these
	interfaces will be redundant. That is a larger refactoring than seemed prudent at this time. In
	the meantime this interface allows the kTextSuiteBoss to be self contained and lets us take another
	step towards getting rid of the IOldSelection on the text selection boss.
	
	[rrodseth]
	@ingroup text_select
	@ingroup text_targserv
*/
class ITextTarget : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ITEXTTARGET };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**
			Sets the text focus of the target
			@param	textModel		The text model
			@param	range		the range data to set it to
		*/
		virtual void				SetTextFocus( const UIDRef& textModel, const RangeData& range, bool16 doNotify = kTrue) = 0;
		
		/**
			Sets the text focus of the target but leaves it unmanaged by the text model so it doesn't get notification
			when model changes occur hense it isn't modified by deletes, inserts, etc.
			@param	textModel		The text model
			@param	range		the range data to set it to
		*/
		virtual void				SetTextUnmanaged( const UIDRef& textModel, const RangeData& range, bool16 doNotify = kTrue) = 0;
		/**
			Clears the text focus
		*/
		virtual void				ClearTextFocus(bool16 doNotify = kTrue) = 0;

		/**
			Initialize the text target with a text model. This must be done
			before a range can be set.
			@param	textModel		The text model
		*/
		virtual void				SetTextModel_Internal(const UIDRef& textModel, bool16 doNotify = kTrue) = 0;
			
		/**
			Set the range of text
			@param	r		the range data to set it to
		*/
		virtual void 				SetRange_Internal( const RangeData& r, bool16 doNotify = kTrue) = 0;

		/**
			Return the text model associated with this range
			@return 	ITextModel
		*/
		virtual ITextModel*			QueryTextModel() const = 0;
			
		/**
			Return the UIDRef of the text model associated with this range
			@return 	UIDRef
		*/
		virtual UIDRef				GetTextModel() const = 0;
		
		/**
			Return the range of text
			@return 	RangeData
		*/
		virtual RangeData 			GetRange() const = 0;
		
		/**
			Return the text focus, created when a range is first set.
			@return 	ITextFocus
		*/
		virtual ITextFocus*			QueryTextFocus() const = 0;

		/**
			Release the text focus.
		*/
		virtual void				Clear_Internal( bool16 doNotify = kTrue) = 0;

		/**
			Return the thread UID of the range's start index
			@return 	uid
		*/
		virtual UID					GetRangeThreadDictUID() const = 0;

		/**
			Return the thread dict key of the range's start index
			@return	uint32
		*/
		virtual uint32				GetRangeThreadDictKey() const = 0;
			
		/**
			Return whether or not the Text Target references text. 
			@return	bool16
		*/
		virtual bool16				HasContent(void) const = 0;


	/**     Initialize
			@param	db		Database the text target is associated with. 
	*/

        virtual void            Initialize      (IDataBase* db) = 0;
	};

#endif // _ITextTarget_
