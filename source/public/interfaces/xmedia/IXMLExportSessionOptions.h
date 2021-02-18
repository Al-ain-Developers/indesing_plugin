//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLExportSessionOptions.h $
//  
//  Owner: Bruce Linker
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
#ifndef __IXMLExportSessionOptions__
#define __IXMLExportSessionOptions__

#include "XMLID.h"
#include "IPMUnknown.h"

//========================================================================================
// CLASS IXMLExportSessionOptions
//========================================================================================
/** Interface storing XML export options. Mutate the options stored on the session workspace t
	through the command kChangeXMLExportSOptionsCmdBoss rather than directly on the interface 
	on the session workspace.
*/
class IXMLExportSessionOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLEXPORTSESSIONOPTIONS };


	/**	Accessor for property specifying whether to view after exporting
		
		@return bool16 specifying whether end-user wants to view exported XML-based content
	 */
	virtual bool16 	GetViewAfterExport() const = 0;

	/**	Mutator for property specifying whether to view after exporting
		@param viewAfterExport kTrue if should view after export, kFalse otherwise
	 */
	virtual void 	SetViewAfterExport( bool16 viewAfterExport ) = 0;


	/**	Accessor for viewer that is current user default

		NOTE: This is a reference to internal data. Be sure to not
		let this interface go out of scope before you are done
		using the IDFile
		 
		@return IDFile giving path to exec browser 
	 */
	virtual const IDFile &GetXMLPreferredBrowser(void) = 0;

	/**	Mutator for viewer that's user's current default
		@param pBrowser specifies new browser to set as preferred by end-user
	 */
	virtual void SetXMLPreferredBrowser (const IDFile &pBrowser) = 0;


	/**	Accessor for viewer set by end-user

		NOTE: This is a reference to internal data. Be sure to not
		let this interface go out of scope before you are done
		using the IDFile
		@param indx specifies index in browser-list of interest
		@return IDFile giving path to exec user defined XML viewer 
	 */
	virtual const IDFile &GetXMLUserDefinedBrowser(int32 indx) = 0;

	/**	Mutator for viewer set by end-user
		@param indx location to add this browser in list stored
		@param pBrowser specifies new browser to store on this interface 
	 */
	virtual void SetXMLUserDefinedBrowser(int32 indx, const IDFile &pBrowser) = 0;
	

	/**	Mutate contents of this interface by copying state from another 
		@param otherOptions specifies other interface whose state we'll copy from
	 */
	virtual void Copy( IXMLExportSessionOptions* otherOptions ) = 0;
};


#endif
