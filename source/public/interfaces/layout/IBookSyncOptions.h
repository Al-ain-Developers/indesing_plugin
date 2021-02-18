//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookSyncOptions.h $
//  
//  Owner: Yeming Liu
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
//  Comments: This interface is used to define the synchronization options for book  . 
//  
//========================================================================================

#pragma once
#ifndef __IBOOKSYNCOPTIONS__
#define __IBOOKSYNCOPTIONS__

#include "IPMUnknown.h"
#include "IPMStream.h"
#include "KeyValuePair.h"
#include "K2Vector.h"
#include "BookID.h"

/**
	This is a helper class used for cache the synchronization style information.
*/
class SyncStyleIDInfo
{
	public:
		typedef object_type data_type;

		/**
			Default constructor.
		*/
		SyncStyleIDInfo() : fTurnOn(kFalse) {}

		/**
			Constructor with given values.
		*/
		SyncStyleIDInfo(
				const PMIID     styleID,	// sync style interface id
				const PMString& styleName,  // style name
				const bool16    turnOn) :	// turn on/off flag
			fStyleID(styleID),
			fStyleName(styleName),
			fTurnOn(turnOn) {}
	
		/**
			Equal operator.
			@param other IN the object to compare with.
		*/
		bool16 operator==(const SyncStyleIDInfo& other) const
		{ 
			return ( (fStyleID == other.fStyleID) && 
				     (fStyleName == other.fStyleName) && 
				     (fTurnOn == other.fTurnOn) ); 
		}

		/**
			Read/write object from stream.
			@param s IN the given stream.
		*/
		void ReadWrite(IPMStream *s)
		{
			int32 styleID(0);
			if (s->IsReading())
			{
				s->XferInt32(styleID);
				fStyleID = (PMIID)styleID;
			}
			else
				s->XferInt32((int32&)fStyleID);

			fStyleName.ReadWrite(s);
			s->XferBool(fTurnOn);
		}

		PMIID	 fStyleID;		// synchronization style interface id
		PMString fStyleName;	// style name
		bool16   fTurnOn;		// flag indicates if style is turned on or not, if it is turned on, we should synchronize it.
};

/** Options relating to book synchronization.
	@ingroup layout_book
	@see kBookBoss 
	@see kBookSyncCmdBoss 
*/
class IBookSyncOptions : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKSYNCOPTIONS };

		/**	Get the synchronization style map from the book.
			@param none
			@return const: the synchronization style map in the book.
		*/
		virtual const K2Vector<KeyValuePair<PMString, K2Vector<SyncStyleIDInfo> > >& GetSyncStyleMap() = 0;


		/**	Set the synchronization style map in the book.
			@param styleMap IN: the style map that is used to set in the book.
		*/
		virtual void SetSyncStyleMap(const K2Vector<KeyValuePair<PMString, K2Vector<SyncStyleIDInfo> > >& styleMap) = 0;
};


#endif //__IBOOKSYNCOPTIONS__