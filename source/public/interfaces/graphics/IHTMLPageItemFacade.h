//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IHTMLPageItemFacade.h $
//  
//  Owner: David Stephens
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
#ifndef __IHTMLPageItemFacade__
#define __IHTMLPageItemFacade__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "Utils.h"
#include "HTMLPGTID.h"

class IPMStream;

namespace Facade
{
// Please use the IHTMLPageItemFacade directly via the UtilsBoss if possible, see Utils.h:
//		i.e. Utils<Facade::IHTMLPageItemFacade>()->GetHTMLContent( ... );
// Or, you can simply include HTMLPageItemFacade.h (instead of IHTMLPageItemFacade.h) and then use
//		HTMLPageItemFacade::GetHTMLContent( ... );

	/**   A high level API for dealing with images.  Please use the IHTMLPageItemFacade 
		directly via the UtilsBoss if possible, see Utils.h:
		i.e. Utils<IHTMLPageItemFacade>()->GetHTMLContent( ... ) ;
		  @author David Stephens
	   */
	class IHTMLPageItemFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IHTMLPAGEITEMFACADE };

		/**	Is the given string HTML content?
			@param text IN a pointer to a string of text which may be HTML
			@return true if the text is HTML
		 */
		virtual bool32 IsHTMLContent(const WideString& text) const  = 0;

		/**	Get the HTML content associated with an embedded HTML page item.
			@param GetHTMLContent IN a pointer to any of the page item's interfaces.
			@return the HTML content as a WideString. 
		 */
		virtual WideString GetHTMLContent(const IPMUnknown* pageItem) const  = 0;

		/**	Given some embedded HTML content, create an embedded HTML page item. Note that the poster image is generated asynchronously so the
			page item that is returned likely will not contain a poster and will not be the correct size.
			@param db IN The database 
			@param html IN The HTML content.
			@param bAddParentFrame IN If true, add a parent container. If false, create only the html page item.
			@param newPageItemOrParentFrame OUT The UIDRef of the new html page item or its parent frame if bAddParentFrame is true.
			@return ErrorCode 
		 */
		virtual ErrorCode CreateHTMLPageItem(IDataBase *db, const WideString& html, bool32 bAddParentFrame, UIDRef& newPageItemOrParentFrame) const  = 0;

		/**	Set new HTML content
			@param pageItem [IN] The UIDRef of the page item
			@param html [IN] new HTML content
			@return ErrorCode 
		 */
		virtual ErrorCode SetHTMLContent(
			const UIDRef& pageItem,
			const WideString& html			// new HTML content
			) const = 0; 

		/**	Force the poster to be regenerated from the current HTML
			@param pageItem IN The UIDRef of the HTML page item to update.
			@param bAutoResizeParentFrame IN If true, then the parent container will be resized to fit the HTML page item after the poster generation is complete.
			@return ErrorCode 
		 */
		virtual ErrorCode UpdatePoster (const UIDRef& pageItem, bool32 bAutoResizeParentFrame) const = 0;

		/** Placed HTML comes into InDesign as a packaged file where the actual HTML file is embedded somewhere
		 within the package. On HTML export, we need to build a relative POSIX path to the HTML file to use as the 'src' of
		 an 'iframe'. This field helps us to do that. 
		
		 @param pageItem [IN] The UIDRef of the page item
		 @param relativePosixPath [IN] subpath within the placed package to the actual HTML file, relative to the uncompressed 
			package folder.
		 @return an ErrorCode (kSuccess if successful).
		 */
		virtual ErrorCode SetRelativeURIToHTMLFile(const UIDRef& pageItem, const WideString* relativePosixPath) = 0;

		/** Placed HTML comes into InDesign as a packaged file where the actual HTML file is embedded somewhere
		 within the package. On HTML export, we need to build a relative path to the HTML file to use as the 'src' of
		 an 'iframe'. This field helps us to do that. 
		
		 @param pageItem [IN] The UIDRef of the page item
		 @param relativePosixPath [OUT] a Posix subpath within the placed package to the actual HTML file, relative to the uncompressed 
			package folder.
		 */
		virtual void GetRelativeURIToHTMLFile(const UIDRef& pageItem, WideString& relativePosixPath) const = 0;
		
		/** Set whether or not this HTML is resizable. That is, does it know how to adapt when its container's size changes in the HTML runtime,
			or is it a fixed size and needs to be scaled in order to adapt?
		 
			@param pageItem [IN] The UIDRef of the page item
			@param resizable [IN] true if resizable, false if it needs to be scaled 
			@return ErrorCode
		 */
		virtual ErrorCode SetResizable(const UIDRef& pageItem, bool32 isResizable) = 0;
		
		
		/** Get whether or not this HTML is resizable. That is, does it know how to adapt when its container's size changes in the HTML runtime,
		 or is it a fixed size and needs to be scaled in order to adapt?
		 
		 @param pageItem [IN] The UIDRef of the page item
		 @return true if resizable, false if it needs to be scaled 
		 */
		virtual bool32 GetResizable(const UIDRef& pageItem) const = 0;
	};
}

#endif	// __IHTMLPageItemFacade__
