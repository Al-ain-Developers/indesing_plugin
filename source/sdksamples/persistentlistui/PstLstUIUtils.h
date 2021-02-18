//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUIUtils.h $
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

#ifndef __PstLstUIUtils_h__
#define __PstLstUIUtils_h__

// Enumerations:
typedef enum {
	kPstLstNew        = 1,
	kPstLstModify     = 2
} PstLstDialogMode;

/** PstLstUIUtils
	PstLstUIUtils implements some user-interface specific methods that can be 
	shared by different source files in this plug-in.
	
	NOTE: The methods in this class used to be part of PstLstUtils, however, splitting the
	utility methods between user-interface specific and core methods allows for easier
	separation of model and UI components, especially when we need to split this plug-in
	for use under InDesign Server.
	
	@ingroup persistentlist
*/
class PstLstUIUtils 
{
public:
	/**
		InvokePstLstDialog creates a dialog that can be used by both Modify and New menu
		items.
			
		@param mode is used to identify the purpose of the dialog, so the dialog knows
		what string to display.
	*/
	static void InvokePstLstDialog(int32 mode, UIDList* &list);
};

#endif // __PstLstUIUtils_h__

// End, PstLstUIUtils.h

