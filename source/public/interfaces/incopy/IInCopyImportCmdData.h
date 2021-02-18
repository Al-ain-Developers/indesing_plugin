//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyImportCmdData.h $
//  
//  Owner: Frank Rubino
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
#ifndef __IInCopyImportCmdData__
#define __IInCopyImportCmdData__

#include "IPMUnknown.h"

class IPMStream;
class IInCopyImportOptions;

/** Command data interface for kInCopyImportCmdBoss and kInCopyImportMetaDataCmdBoss.
*/
class IInCopyImportCmdData : public IPMUnknown
{
public:

	/**	Get the import stream
		@param none
		@return IPMStream 
	*/
	virtual IPMStream *GetStream()=0;

	/**	Set the import stream
		@param s 
	 */
	virtual void SetStream(IPMStream *s)=0;

	/**	Get the import options interface pointer
		@param none
		@return IInCopyImportOptions* 
	 */
	virtual IInCopyImportOptions* GetOptions() const = 0;

	/**	Set the import options interface pointer
		@param options 
	 */
	virtual void SetOptions(IInCopyImportOptions* options) = 0;
	

	/**	Get the story that will be replaced by the import content
		@param none
		@return UIDRef 
	 */
	virtual UIDRef GetStoryToReplace() const = 0;

	/**	Set the story that replaced by the import content
		@param storyRef 
	 */
	virtual void SetStoryToReplace(const UIDRef& storyRef) = 0;
	
};

#endif
