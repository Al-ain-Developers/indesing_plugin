//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvUtils.h $
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

#ifndef __PnlTrvUtils_H_DEFINED__
#define __PnlTrvUtils_H_DEFINED__

class IDocument;
class IControlView;

/** A collection of miscellaneous utility methods used by this plug-in.
@ingroup paneltreeview
*/
class PnlTrvUtils
{

public:
	/** Return a version of the supplied path which consists only of the 
		file 'name', removing everything up to and including the last path separator.
		@param fromthis [IN] path of interest
		@return string containing the path-part minus the last segment
	*/
	static PMString TruncatePath(const PMString& fromthis);
	
	/** Attempt to import item (which can be any format) from path; loads
		place gun if item can be imported.
		@param docUIDRef [IN] specifies document into which item would be placed
		@param fromPath [IN] specifies the path in the local filesystem of the item to attempt to import
		@return UIDRef of item imported, or UIDRef::gNull otherwise
	*/
	static UIDRef ImportImageAndLoadPlaceGun(
		const UIDRef& docUIDRef, const PMString& fromPath);

	/**	Get a widget from the specified panel by WidgetID, returning nil if it can't be found.
		@param panelWidgetID [IN] specifies the parent widget
		@param widgetID [IN] sought dependent widget
		@return interface ptr to widget found or nil if it can't be found; not a reference incremented one though.
	 */
	static IControlView* GetWidgetOnPanel(
		const WidgetID& panelWidgetID, const WidgetID& widgetID);

	/** Get path the user has chosen, if it exists
		@return PMString containing path selected by user, empty if none chosen
	*/
	static PMString GetFolderSelectedPath();

};

#endif // __PnlTrvUtils_H_DEFINED__

