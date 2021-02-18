//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISelectionUtils.h $
//  
//  Owner: Michael Martz
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
#ifndef __ISelectionUtils__
#define __ISelectionUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IConcreteSelection.h"
#include "UIDList.h"
#include "ICommand.h"
#include "ILayoutTarget.h"

class ISelectionManager;
class ITextSelectionSuite;
class ITextFocus;
class ITableSelectionSuite;		
class IPathSelectionSuite;
class IDocument;
class IPageHitTestSuite;
class IPathSelectionSuite;
class ISuite;
class ILayoutHitTestSuite;
class ILayoutSelectionSuite;
class IActiveContext;
class IWindow;

/**
	Utility methods related to selection. 
	<pre>
	Utils&lt;IPathPointUtils&gt;()->CopyObjects(...) ;
	</pre>
	@ingroup layout_util
	@ingroup layout_select
	@ingroup arch_select
*/
class ISelectionUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISELECTIONUTILS };

	/** Get the abstract selection manager out of the active context and return it
		to the caller. The reference count is NOT incremented.
		@return ISelectionManager* or nil	
	*/
	virtual ISelectionManager* 	GetActiveSelection		(void) = 0;

	/** Query the abstract selection manager out of the active context and return
		it to the caller. The reference count is incremented. The caller is responsible 
		for calling Release().
		@return ISelectionManager* or nil	
	*/
	virtual ISelectionManager* 	QueryActiveSelection	(void) = 0;

	/** Query a suite on the abstract selection boss. The reference count is incremented. 
		The caller is responsible for calling Release().
		@return IPMUnknown* or nil	
	*/
	virtual IPMUnknown* QuerySuite (const PMIID&, ISelectionManager* selectionManager = nil) = 0;

	/** Given a database, return a document if possible. The reference count is incremented. 
		The caller is responsible for calling Release().
		@return IDocument* or nil	
	*/
	virtual IDocument* QueryDocument (IDataBase*) = 0;

	/** Query the text selection suite from the specified selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ITextSelectionSuite* or nil	
	*/
	virtual ITextSelectionSuite* QueryTextSelectionSuite	(ISelectionManager* iSelectionManager) = 0;
	/** Query the text selection suite from the active selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ITextSelectionSuite* or nil	
	*/
	virtual ITextSelectionSuite* QueryActiveTextSelectionSuite (void) = 0;

	/** Query the table selection suite from the specified selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ITableSelectionSuite* or nil	
	*/
	virtual ITableSelectionSuite* QueryTableSelectionSuite	(ISelectionManager* iSelectionManager) = 0;
	/** Query the table selection suite from the active selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ITableSelectionSuite* or nil	
	*/
	virtual ITableSelectionSuite* QueryActiveTableSelectionSuite	(void) = 0;
	
	/** Query the layout selection suite from the specified (selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ILayoutSelectionSuite* or nil	
	*/
	virtual ILayoutSelectionSuite* QueryLayoutSelectionSuite (ISelectionManager* iSelectionManager) = 0;
	/** Query the layout selection suite from the active selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ILayoutSelectionSuite* or nil	
	*/
	virtual ILayoutSelectionSuite* QueryActiveLayoutSelectionSuite (void) = 0;

	/** Query the path selection suite from the specified selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return IPathSelectionSuite* or nil	
	*/
	virtual IPathSelectionSuite* QueryPathSelectionSuite	(ISelectionManager* iSelectionManager) = 0;
	/** Query the path selection suite from the active selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return IPathSelectionSuite* or nil	
	*/
	virtual IPathSelectionSuite* QueryActivePathSelectionSuite (void) = 0;

	/** Query the layout hit test suite from the specified selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ILayoutHitTestSuite* or nil	
	*/
	virtual ILayoutHitTestSuite* QueryLayoutHitTestSuite	(ISelectionManager* iSelectionManager) = 0;
	
	/** Query the layout hit test suite from the active selection manager. 
		The reference count is incremented. The caller is responsible for 
		calling Release().
		@return ILayoutHitTestSuite* or nil	
	*/
	virtual ILayoutHitTestSuite* QueryActiveLayoutHitTestSuite (void) = 0;

	/** Query the page hit test suite from the specified selection manager. 
	 The reference count is incremented. The caller is responsible for 
	 calling Release().
	 @return IPageHitTestSuite* or nil	
	 */
	virtual IPageHitTestSuite* QueryPageHitTestSuite	(ISelectionManager* iSelectionManager) = 0;

	/** Given an UIDRef, returns its abstract selection, ISelectionManager.
		The UIDRef could be either a workspace selection or a view selection.
		The reference count is incremented. The caller is responsible for calling Release().
		@return ISelectionManager*, or nil
	*/
	virtual ISelectionManager* QueryOwnerSelectionManager (const UIDRef& selectionOwnerRef) = 0;
	/** Given an IPMUnknown, returns its abstract selection, ISelectionManager.
		The IPMUnknown could be either a workspace selection or a view selection.
		The reference count is incremented. The caller is responsible for calling Release().
		@return ISelectionManager*, or nil
	*/
	virtual ISelectionManager* QueryViewSelectionManager ( const IPMUnknown* that) = 0;

	/** Given an interface pointer will compare the context selection to the
		view selection. If the two do not match the Active selection will be
		changed to reflect the given view selection.
		@return void
	*/
	virtual IActiveContext*	ActivateView(IPMUnknown *view) const = 0;

	virtual IWindow* QuerySelectionManagerOwnerWindow(const UIDRef& selectionOwner) const = 0;

	/** Given an interface pointer will determine if it lies within the hierarchy of the active selection
		of the window/presentation. Use for determining if a view in a presentation is the "active" from a
		selection point of view. e.g. LayoutPresentations may have structure, layout, and a split layout view all
		visible at once, but only one is active.
		@return bool16 kTrue if view is part of the active selection for this presentation, kFalse otherwise.
	*/
	virtual bool16 IsWithinActivatedView(IPMUnknown *view) const = 0;
};

#endif	// __ISelectionUtils__
