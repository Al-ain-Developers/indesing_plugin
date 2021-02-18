//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchUtils.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __DocWchUtils_h__
#define __DocWchUtils_h__

// Interface includes
#include "IDocument.h"

/** DocWchUtils
	provides a set of utility methods for tracking which demo
	mode is active as well as formatting alerts.

	@ingroup docwatch
	
*/
class DocWchUtils
{
	public:
		static void GetDefaultDocFileHandler();
		
		/** Constructor */
		DocWchUtils() {};

		/** Methods to find out what mode we're in. */
		static bool16 QueryDocResponderMode() {return fDocResponder;};

		/** 
		Show an information alert 
			@param document ptr to document that is subject of file action.
			@param txtMsg ptr to null terminated char array.  If it
			contains ^1, this method will replace it with the document name.
		*/
		static void DwAlert(UIDRef document, char* txtMsg);

		/** Initializes the static variables. */
		static void InitDocWchModes();

		/** Controls the document Responder mode variable. */
		static void StartDocResponderMode() { fDocResponder = kTrue; };
		static void StopDocResponderMode() { fDocResponder = kFalse; };

	private:
		/** Returns whether the document Responder is in use */
		static bool16 fDocResponder;
};

#endif // __DocWchUtils_h__

// End, DocWchUtils.h.


