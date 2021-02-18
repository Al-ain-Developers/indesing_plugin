//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextEditor.h $
//  
//  Owner: EricM and Michael Burbidge
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
#ifndef __ITEXTEDITOR__
#define __ITEXTEDITOR__

#include "IPMUnknown.h"
#include "TextEditorID.h"

//========================================================================================
// Forward declarations
//========================================================================================

class IFrameList;
class ITextCaret;
class ITextFocus;
class ILayoutControlData;
class RangeData;
class IConcreteSelection;
class ITextModel;


//========================================================================================
// CLASS ITextEditor
//========================================================================================

/** Interface for kTextEditorBoss, to active/deactivate the text editor and to get text caret information
	@ingroup text_editor
*/
class ITextEditor : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTEDITOR };

	// ----- Selection
//	enum { kDontDrawTextSelection = 0, kDrawTextSelection = 1, kDontGrabFocus = 0, kGrabFocus = 1};

/**	Activate the text editor
	@param IConcreteSelection* The IConcreteSelection in the view
 */
	virtual void ActivateTextEditor( IConcreteSelection*) = 0;

/**	Deactivate the text editor
	@param none
 */
	virtual void DeactivateTextEditor() = 0;

/**	Query the text focus on the text editor 
	@param none
	@return  
 */
	virtual ITextFocus* 			QueryTextFocus() = 0;

/**	Query the text caret on the text editor
	@param none
	@return  
 */
	virtual ITextCaret* 			QueryTextCaret() = 0;

/**	Query the layout control data on the text editor
	@param none
	@return * 
 */
	virtual	ILayoutControlData *	QueryLayoutControlData() = 0;

/**	Query the text model's frame list in the text editor
	@param none
	@return IFrameList * 
 */
	virtual IFrameList *			QueryFrameList() = 0;

/**	Is the text editor active?
	@param none
	@return bool16 kTrue means the text editor is active
 */
	virtual bool16					IsActive() = 0;
};


#endif
