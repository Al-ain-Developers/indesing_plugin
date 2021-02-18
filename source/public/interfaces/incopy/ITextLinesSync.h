//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextLinesSync.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ITextLinesSync__
#define __ITextLinesSync__

#include "IPMUnknown.h"

#include "WritingModeID2.h"

class IDataBase;

class ITextLinesSync : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTLINESSYNC };

		/**
			Method to sync galley lines to layout composition.
			@param atIndex TextIndex of waxline changed
			@param waxDb database of the wax
			@return void
		*/	
		virtual void SyncLines(TextIndex at, IDataBase *waxDb) = 0;
		
		/**
			Method to sync galley lines in special case where a frame break character is involved. This routine
			is really for internal use and shouldn't be called otherwise.
			@param atIndex TextIndex just after break character
			@param waxDb database of the wax
			@return void
		*/	
		virtual void BreakSync(TextIndex atIndex, IDataBase *waxDb) = 0;
		
		/**
			Used internally to clean up some text lines after composition mainly in cases where frame break
			characters are in the text.
			@return void
		*/	
		virtual void PostComposeSync() = 0;

};

#endif 		// __ITextLinesSync__