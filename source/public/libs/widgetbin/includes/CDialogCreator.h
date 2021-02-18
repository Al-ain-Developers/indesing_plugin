//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CDialogCreator.h $
//  
//  Owner: Dave Burnard (was Tom Taylor)
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
#ifndef __CDialogCreator__
#define __CDialogCreator__

#include "IDialogCreator.h"
#include "HelperInterface.h"

// This is naughty, but Windows has defined CreateDialog to something,
// believe it or not!  I know I'll have to fix this.
#undef CreateDialog

#ifdef WIDGET_BUILD
#pragma export on
#endif

/** Basic implementation of the IDialogCreator interface, used to create selectable dialogs. 
		Implementors of IDialogCreator should derive from CDialogCreator. 
		
		@see IDialogCreator
*/
class WIDGET_DECL CDialogCreator : public IDialogCreator
{
public:
							CDialogCreator(IPMUnknown *boss);
	virtual					~CDialogCreator();

	/** Override this to create the dialog */
	virtual IDialog*		CreateDialog();

	/**	Override this to specify the Resource ID of the resource containing an ordered list of panel ids. 
			If order is not important, it's not necessary to override this function.

		@return the resource id (a "real" id will be non-zero, this implementation returns 0)
	*/
	virtual RsrcID			GetOrderedPanelsRsrcID() const;

	/** Get the ordered list of class IDs of selectable dialogs that are to be installed in this dialog.
			Classes that override this function can simply call the protected member GetOrderedPanelIDs 
			with the plug-in's ID from which to get resource data from within.

		@param classIDs OUT ordered list of class IDs of selectable dialogs
	*/
	virtual void			GetOrderedPanelIDs(K2Vector<ClassID>& classIDs);

protected:
	
	/** Generic form of the method to get the ordered list of class IDs of selectable dialogs 
	 that are to be installed in this dialog.  Classes should not override this function, and 
	 instead use the virtual public method if overriding is needed.
	 
	 @param pluginID IN  ID of the plugin to use when requesting resources
	 @param classIDs OUT ordered list of class IDs of selectable dialogs
	 */
	void					GetOrderedPanelIDs(const PluginID pluginID, K2Vector<ClassID>& classIDs);
	
	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
