//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITOCDataLinkHelper.h $
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
//  Comments: This is a helper interface to attach/remove TOC datalink.
//  
//========================================================================================

#pragma once
#ifndef __ITOCDATALINKHELPER__
#define __ITOCDATALINKHELPER__

#include "IPMUnknown.h"

#include "UIDList.h"
#include "TOCID.h"

/** This is a helper interface to attach/remove data link related to table of content from the story. 

    @see kAttachTOCDataLinkCmdBoss and kRemoveTOCDataLinkCmdBoss.
*/
class ITOCDataLinkHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOCDATALINKHELPER };

		/**	This is a helper interface to add an table of content(TOC) link to the story and have the 
		    story back reference to the datalink. This is all through the AttachTOCDataLinkCmd.
			@param datalinkRef IN UIDRef of datalink to be attached to the TOC style's link manager.
			@param storyRef IN UIDRef of story stored in the datalink.
			@param tocStyleRef IN UIDRef o TOC style.
			@return ErrorCode the result of the operation. By default, it return kSuccess.
		*/
		virtual ErrorCode AddTOCDataLink(const UIDRef& datalinkRef, const UIDRef& storyRef, const UIDRef& tocStyleRef) = 0;

		/**	This is a helper interface to add an table of content(TOC) link to the story and have the 
		    story back reference to the datalink. This is all through the AttachTOCDataLinkCmd.
			@param itemList IN the list of datalinks to be attached to the TOC style's link manager.
			@return ErrorCode the result of the operation. By default, it return kSuccess. 
		*/
		virtual ErrorCode AddTOCDataLink(const UIDList* itemList) = 0;

		/**	This is a helper interface to remove the table of content(TOC) link from the story and 
		    from the TOC style's link manager too. This is all through the RemoveTOCDataLinkCmd.
			@param datalinkRef IN UIDRef of datalink to be removed from the TOC style's link manager.
			@param storyRef IN UIDRef of story stored in the datalink.
			@param tocStyleRef IN UIDRef o TOC style.
			@return ErrorCode the result of the operation. 
		*/
		virtual ErrorCode RemoveTOCDataLink(const UIDRef& datalinkRef, const UIDRef& storyRef, const UIDRef& tocStyleRef) = 0;

		/**	This is a helper interface to remove the table of content(TOC) link from the story and 
		    from the TOC style's link manager too. This is all through the RemoveTOCDataLinkCmd.
			@param itemList IN the list of datalinks to be removed from the TOC style's link manager.
			@return ErrorCode the result of the operation. By default, it return kSuccess. 
		*/
		virtual ErrorCode RemoveTOCDataLink(const UIDList* itemList) = 0;
};

#endif // __ITOCDATALINKHELPER__
