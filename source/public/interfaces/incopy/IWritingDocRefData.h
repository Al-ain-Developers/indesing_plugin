//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IWritingDocRefData.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IWritingDocRefData__
#define __IWritingDocRefData__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "UIDRef.h"

/** 
	This interface is used by story, galley, notes and text macro views to hold a reference to
	the document they are viewing. It also is used to track invaling for undo screen redrawing.
*/
class IWritingDocRefData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWRITINGDOCREFDATA };
		
		/**
			Get the document uid reference being viewed in the view.
			@return An uidRef of the document being viewed.
		*/
		virtual const UIDRef &GetDocRef() const = 0;
		
		/**
			Set the document uid reference for the view. This shouldn't normally be called by
			third parties.
			@param docRef reference of document to view
			@param duringResetView is an undo/redo detail external use false (the default)
			@return none
		*/
		virtual void SetDocRef(const UIDRef &docRef, bool16 duringResetView = kFalse) = 0;
		
		/**
			Used by the undo to reset inval handler information. Internal use.
			@param duringResetView is an undo/redo detail external use false (the default)
			@return none
		*/
		virtual void ResetDocRef(bool16 duringResetView = kFalse) = 0;
		
		/**
			Tell inval handler to start collecting invals if it isn't alread doing so.
			@return none
		*/
		virtual void ActivateInvalHandler() = 0;
};

#endif 		// __IWritingDocRefData__