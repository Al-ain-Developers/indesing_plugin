//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDialogCreator.h $
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
#ifndef __IDialogCreator__
#define __IDialogCreator__

#include "IPMUnknown.h"
#include "K2Vector.h"

class IDialog;

// This is naughty, but Windows has defined CreateDialog to something,
// believe it or not!  I know I'll have to fix this. - TT
#undef CreateDialog

/** Interface usedto create selectable dialogs. 
		The IDialogCreator appears on selectable dialog service bosses, and is used to create a selectable dialog 
		(a dialog, like the preference dialog, that switches between two or more panels by selecting fr0m a list on the left).

		@see CDialogCreator
*/
class IDialogCreator : public IPMUnknown
{
public:
	/** Create the dialog */
	virtual IDialog*		CreateDialog() = 0;
								
	/**	Get the Resource ID of the resource containing an ordered list of panel ids. If order is not important,
			it's not necessary to override this function.

		@return the resource id 
	*/
	virtual RsrcID			GetOrderedPanelsRsrcID() const = 0;

	/** Get the ordered list of class IDs of selectable dialogs that are to be installed in this dialog.
			It's ok to leave the classIDs vector empty.  In that case, the panels will be added to the
			dialog in random order.  

		@param classIDs OUT ordered list of class IDs of selectable dialogs
	*/
	virtual void			GetOrderedPanelIDs(K2Vector<ClassID>& classIDs) = 0;
};

#endif
