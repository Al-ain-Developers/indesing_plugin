//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyApp.h $
//  
//  Owner: Jon Pugh
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
#ifndef __IInCopyApp__
#define __IInCopyApp__


#include "IPMUnknown.h"
#include "ISession.h"
#include "InCopyCoreID.h"

class ITool;


/** Interface on the application providing app wide access methods.  Often
	queried to determine if running in InCopy - now can use LocaleSetting.
*/
class IInCopyApp : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYAPP };

	/** Interface query.
		@return IInCopyApp* ptr to IInCopyApp.
	*/
	static IInCopyApp*			Query() { return (IInCopyApp*) GetExecutionContextSession()->QueryInterface(IID_IINCOPYAPP); }

	/** Filters tools except kIBeamToolBoss, kZoomToolBoss, kLoupeToolBoss, kGrabberHandToolBoss,
		kNoteToolBoss, kCropToolBoss.  Called by ToolInitializer::RegisterByStream.
		@param ClassID class for tool to be filtered or not.
		@return bool whether or not tool was filtered.
	*/
	virtual bool			FilterThisTool( ClassID toolclass ) = 0;

#ifdef ID_DEPRECATED 
	/** Deprecated. Replaced by ShowTrackChangesPrefs::GetShowTrackChanges().
	*/
	virtual bool			ShowChanges() = 0;

	/** Deprecated. Replaced by ShowTrackChangesPrefs::SetShowTrackChanges().
	*/
	virtual void			ShowChanges( bool bDoIt ) = 0;
#endif
	
	/** Utility method to get a sysfile pointing to the current saveas folder. Typically this 
		will be the starting point in a save as dialog.
		@param docName name of document to get save as folder of
		@param useSystemDefaultDir will be kTrue on return if we are using the system default rather than application
		@return IDFile pointing to the correct starting directory to do the "save as" in.
	**/
	virtual IDFile 		GetDefaultFile(PMString docName, bool16 *useSystemDefaultDir) = 0;
};

//========================================================================================
#endif // __IInCopyApp__