//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDocumentPresentation.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IDOCUMENTPRESENTATION__
#define __IDOCUMENTPRESENTATION__

#include "IPMUnknown.h"
#include "PMTypes.h" //GSysRect
#include "AppUIID.h"
#include "ISelectionMessages.h"
#include "ScriptData.h"
#include "IWindow.h"

class IDocument;
class IControlView;
class ISelectionManager;

/** This interface represents a view onto a document, and exists on the document presentation boss, along with IActiveContext,
	to designate an InDesign document presentation. IDocumentPresentation replaces the IWindow and IDocumentWindow interfaces
	with methods more appropriate to the new world of OWL hosted document views.
	
	Note: In CS4 the IWindow interface on the presentation boss *must* not be used to manipulate the document view.
	
	The document presentation boss bridges the gap between InDesign document views, and the OWL Palette world.
*/

class IDocumentPresentation : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IDOCUMENTPRESENTATION};
	
	/** Get the document being viewed by this presentation.
	*/
	virtual IDocument*	GetDocument() const = 0;

	/** Get the document being viewed by this presentation.
	*/
	virtual UIDRef		GetDocumentUIDRef() const = 0;

	/** Get the PaletteRef corresponding to this document presentation. 
		This should return an object of type kDocumentPresentationType.
		
		@see PaletteRefUtils.h for tips on manipulating/traversing the PaletteRef object hierarchy. 
		@see PaletteRefUtils::GetDocumentPresentationFromPaletteRef, also related to IPanelMgr::GetPaletteRefContainingPanel.
	*/
	// virtual PaletteRef	GetPaletteRef() const = 0; // use PaletteRefUtils::GetPaletteRefFromDocumentPresentation(this) instead.


	/**	Is the presentation visible.
			Notes: 
				Even though a presentation is obscured by a window floating above it, it is still considered visible.
				If a presentation is in a tabgroup, it is considered visible only if it is the front tab in the group.
			
	*/
	virtual bool16  IsVisible() const = 0;

	/** Is this presentation contained in a floating container 
		(as opposed to being embedded inside the ApplicationContainer) 
	*/
	virtual bool16	IsFloating() const = 0;
	
	/** If this presentation is not contained in a floating container, 
		create a new floating document dock and reparent the presentation to it.
	*/
	virtual void	Float() = 0;
	
	/** Is this presentation contained in a floating container that is minimized 
		(presentations embedded inside the ApplicationContainer can't be minimized) 
	*/
	virtual bool16	IsMinimized() const = 0; 

	/** If this presentation is contained in a floating container,  toggle it's minimized state.
		(presentations embedded inside the ApplicationContainer can't be minimized) 
	*/
	virtual void	Minimize() = 0;

	/** Is this presentation contained in a floating container that is maximized.
		(presentations embedded inside the ApplicationContainer can't be maximized) 
	*/
	virtual bool16	IsMaximized() const = 0; 

	/** If this presentation is contained in a floating container,  toggle it's maximized state.
		(presentations embedded inside the ApplicationContainer can't be maximized) 
	*/
	virtual void	Maximize() = 0;

	/** Is this the active/target presentation */
	virtual bool16	IsActive() const = 0;
	
	/** Make this the active/target presentation */
	virtual void	MakeActive() = 0;

	/** Is this presentation active amongst it's siblings (same tab group)
		ActiveInContext maps to "frontmost in it's tab group" - 
			so the document is visible (if not obscured by something floating above it) 
	*/
	virtual bool16	IsFrontmostInTabGroup() const = 0;
	
	/** Make this presentation frontmost amongst it's siblings 
	*/
	virtual void	MakeFrontmostInTabGroup() = 0;
	
	/** Get the semantic bounds of this presentation.
		The semantic bounds may not match the current physical bounds if a layout in pending or in progress. 
	*/
	virtual SysRect GetPresentationBounds() const = 0;

	/** Get the current physical bounds of this presentation.
	 */
	virtual SysRect GetPresentationPlatformBounds() const = 0;

	/** Set/Change the preferred size, when floating, for this presentation.
	*/
	virtual SysSize GetPreferredSize() const = 0;
	virtual void ChangePreferredSize(const SysSize&) = 0;

	/** Set the preferred size, when constrained to fit within the application container, for this presentation.
	 */
	virtual SysSize GetPreferredConstrainedSize() const = 0;

	/** Change the preferred size, when constrained to fit within the application container, for this presentation.
	 */
	virtual void ChangePreferredConstrainedSize(const SysSize&) = 0;

	// Get/Change allowable size ranges associated with a document window
	//	(Prior to CS3, this was done with calls to IWindow::Get/SetLimits)

	/** Get allowable width range for this presentation */
	virtual void GetWidthRange(float* min, float* max) const = 0;
	/** Change allowable width range for this presentation */
	virtual void ChangeWidthRange(float min, float max) = 0;
	
	/** Get allowable height range for this presentation */
	virtual void GetHeightRange(float* min, float* max) const = 0;
	/** Change allowable height range for this presentation */
	virtual void ChangeHeightRange(float min, float max) = 0;

	/** Get the document's modified state as cached, and displayed, by the presentation. */
	virtual bool16	GetDocumentModifiedState() const = 0;
	
	/** Change the document's modified state as cached, and displayed, by the presentation.*/
	virtual void	ChangeDocumentModifiedState(bool16) = 0;
	
	/** CreationParentingPrefs allow a caller to specify how and where a new presentation will be created, 
		optionally in relation to an existing presentation
	*/
	enum  {	kDefaultParentingPref = 0, 
					kCreateNewFloatingDock = 1, 
					kCreateNewFloatingDock_ObscureRelative = 2, 
					kCreateNewFloatingDock_DontObscureRelative = 3, 
					kAsSiblingOfRelative = 4,				// add at end of same group as sibling
					kInNewTabGroupFromRelative = 5, 
					kInNewPaneFromRelative = 6,
					kAsSiblingToLeftOfRelative = 7, 
					kAsRightmostChildOfParent = 8, 
					
					kLastParentRelativePref = kAsRightmostChildOfParent,
					kParentingRelatedPrefMask = 255,		 // use this mask when comparing parent related prefs
					
					kDontMakeVisible = 512,  // by default the new presentation is made visible, set this bit to keep document hidden
					kDontBringToFront = 1024, // by default the new presentation is also brought to the front, set this bit to put the document behing the current front document
					
					kLastParentingFlag = kDontBringToFront,
				};
	typedef uint16 CreationParentingPrefs;

	/** Create a new document container like this one that views the specified document content.
			@param doc The document to view
			@param targetBossContentToSelect The content to view and select.
			@param parentPref    was: Either kOffsetFromCurrentWindow or kDirectlyOverCurrentWindow.
			@return the new presentation or nil if it failed. Caller is not responsible for releasing the returned presentation.
	*/
	virtual IDocumentPresentation* CreateNewPresentation( IDocument* doc, IPMUnknown* targetBossContentToSelect, CreationParentingPrefs parentPref = kCreateNewFloatingDock_ObscureRelative) const = 0;

	/** Create a new document container like this one that views the specified document content.
			@param withinBounds Constrains the extent of the new container. // FIXME_OWL2: are these bounds still used/relevant?
			@return a new container just like this one--same size, same document, same selection. Caller is not responsible for releasing the returned presentation.
	*/				
	virtual IDocumentPresentation* ViewInNewPresentation( GSysRect withinBounds, CreationParentingPrefs parentPref = kDefaultParentingPref) const = 0;

	/** Create the command needed to close this presentation. If closing this
		presentation would result in closing the document, don't hold a reference to
		the document when processing the returned command.
			@param allowCancel whether the command may be canceled
			@return a command which, when executed, will close this presentation
	*/
	virtual ICommand* CreateCloseCommand(bool16 allowCancel = kTrue) = 0;
	
	/** Fire the command used to close this presentation. If closing this
		presentation would result in closing the document, don't hold a reference to
		the document when calling this method.
			@param when whether to process the close command immediately or schedule it.
			@param allowCancel if closing the presentation would result in closing the document, can the close be cancelled.
			@return the result of processing the command to close this presentation.
	*/
	enum SchedulingBehavior {kProcessCommandBehavior = 0, kScheduleCommandBehavior = 1};
	virtual ErrorCode ClosePresentation(SchedulingBehavior when = kProcessCommandBehavior, bool16 allowCancel = kFalse) = 0;

	/** Can this presentation be the only presentation on a document?
		In other words, can this presentation "stand alone" for the document, if no such presentations are open the document must close.
		@return whether this presentation can be the only presentation open on the document.
	*/				
	virtual bool16 IsAutonomous() = 0;

	/** Presentation titles/labels. There are three labels for every presentation.
			titleLabel - the essential unshortenable form of the title
			extendedTitleLabel - an extended form of the title, which may include magnification, and other document state information. 
			toolTipLabel - the label used for the presentation's tab's tooltip
		
		For example:
			titleLabel:			"MyDocument.indd"
			extendedTitleLabel: "MyDocument.indd @ 100% [Converted]"
			toolTipLabel:		"C:\Users\joe\Documents\MyDocument.indd"
	 */

	/**	Get the labels for this presentation.
			@param titleLabel the essential unshortenable form of the title
			@param extendedTitleLabel an extended form of the title, which may include magnification, and other document state information. 
			@param toolTipLabel the label used for the presentation's tab's tooltip
	*/	
	virtual void GetPresentationLabels(PMString& titleLabel, PMString& extendedTitleLabel, PMString& toolTipLabel) const = 0;

	/**	Set the labels for this presentation.
			@param titleLabel the essential unshortenable form of the title
			@param extendedTitleLabel an extended form of the title, which may include magnification, and other document state information. 
			@param toolTipLabel the label used for the presentation's tab's tooltip
	*/	
	virtual void SetPresentationLabels(const PMString& titleLabel, const PMString& extendedTitleLabel, const PMString& toolTipLabel = kNullString) = 0;

	/** Update process for presentation titles/labels:

		Seems simple enough, but the subtlety is that some of the titles are numbered, based on how many presentations of each type are open on the document.
		 So for instance: StoryA 1, StoryA 2, StoryB 1, DocA 1, GalleyA 2, DocA 3, etc.
		 
		Steps:
			1) Update the labels (title, tooltip label, etc.) of any presentations from *begin to *end that this implementation can handle.
			2) Move the presentations that were updated to the front of the list 
			3) Return an iterator to the first presentations yet to have its title updated.
			
		@param begin the first presentation in the list needing its labels updated.
		@param end one past the last container in the list needing its labels updated.
		@return the first container in the rearranged list that still needs its labels updated.
	*/				
	virtual K2Vector<IDocumentPresentation*>::iterator UpdatePresentationLabels( K2Vector<IDocumentPresentation*>::iterator begin, K2Vector<IDocumentPresentation*>::iterator end) = 0;

	/** Helper called during construction of a new presentation instance. 
		Presentation subclasses should override this call to create and install their content view(s).
		For example the LayoutPresentation class creates the LayoutWidget boss, installs it into the presentation, and makes it ready to go.
			Any additional hookups at creation time can be performed by the creation command, or by the code that processes the creation command.
		
		@param doc The document to view
		@return whether or not installation was successful.
	*/
	virtual bool16 Helper_InstallPresentationContent( IDocument* doc, IPMUnknown* commandData, IControlView* mimicView = nil) = 0;

/** PresentationKind and PresentationContent types */

	/** Compare presentation kinds (layout vs. story)
	 */
	class SamePresentationKind 
	{
		public:
		virtual ~SamePresentationKind(){}
		virtual bool16 operator()(IDocumentPresentation* other) = 0;
	};

	/** Compare presentation content (are two presentations based on the same document)
	 */
	class SamePresentationContent
	{
		public:
		virtual ~SamePresentationContent(){}
		virtual bool16 operator()(IDocumentPresentation* other) = 0;
	};
	
	/** @return a function that can be used to check if other document presentationa are 
		the same kind as this one.  The caller is responsible for deleting the result
	*/				
	virtual SamePresentationKind* GetPresentationKind() = 0;


	/** @return a function that can be used to check if other document presentation are
		the same kind as this one and view the same document and document's content 
		as this one.  The caller is responsible for deleting the result
	*/				
	virtual SamePresentationContent* GetPresentationContent() = 0;

/** Miscellaneous other methods (formerly found in IDocumentWindow */
	
	/** Select the objects in the scriptList in the correct ASB of this window
		@param action How to extend the selection (valid values: en_Replace, en_AddTo, en_RemoveFrom, en_Nothing, en_All)
		@param scriptList The scripting objects to select
		@param context The context for the scripting request
		@return the errorcode for the action
	*/
	virtual ErrorCode SelectScriptObjects (const ScriptID& action, ScriptList& objectList, const ScriptInfo::RequestContext& context) = 0;

	/** Return the control view that owns an ASB subsystem
		@param iSelectionManager A reference to a ASB sub system
		@return the iControlView that owns the ASB
	*/
	virtual IControlView* QuerySelectableView (ISelectionManager* iSelectionManager) = 0;

	/** populate the targeting boss selectedContent with whatever is currently selected 
		in the presentation.
		@param selectedContent A boss containing all the available targeting interfaces.
		@return kTrue on success, kFalse on failure.
	*/				
	virtual bool16 SetupTarget( IPMUnknown* selectedContent) = 0;

	/** if this presentation cannot select any of the content on any of the targeting 
		interfaces of selectedContent then return kFalse.  Otherwise, remove the 
		content the presentation can select from the targeting boss selectedContent
		and return kTrue.  Further if menuString is nil, bring this presentation to 
		the front, restoring itself from a minimized state if necessary, and 
		select the specified content.  If menuString is non-nil, then simply 
		fill in an appropriate menu string without selecting the content.
		@param menuString The menu string used to invoke this action.
		@param selectedContent A boss containing the targets to be selected.
	*/				
	virtual bool16 EditTarget( PMString* menuString, IPMUnknown* selectedContent) = 0;

	/** Internal use only
	*/
	virtual void RegisterSelectableView (IControlView*) = 0;

	/** Internal use only
	*/
	virtual void UnregisterSelectableView (IControlView*) = 0;

	/** Internal use only
	*/
	virtual void GetSelectableViews (K2Vector<IControlView*>& views) = 0;

	/** Internal use only
	*/
	virtual bool16 IsPresentationActiveInTouchWorkspace() = 0;

	/** Internal use only
	*/
	virtual void SetPresentationActiveInTouchWorkspace(bool16 bFlag) = 0;
};

typedef bool (unary_presentation_predicate)(IDocumentPresentation*);
typedef bool (binary_presentation_predicate)(IDocumentPresentation*, IDocumentPresentation*);



#endif
