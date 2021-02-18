//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchLibraryPanelHelper.h $
//  
//  Owner: SusanCL
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
#ifndef __ISwatchLibraryPanelHelper__
#define __ISwatchLibraryPanelHelper__

#include "SwatchLibPanelID.h"
#include "IPMUnknown.h"

class IPanelControlData;

/**	A helper interface for managing the loading, unloading, selecting, adding, and
	replacing swatches from the Adobe swatch libraries within the InDesign swatch
	option dialog.
*/
class ISwatchLibraryPanelHelper : public IPMUnknown
{
public:
	//___________________________________________________________________________________
	//	DataType
	//___________________________________________________________________________________
	enum { kDefaultIID = IID_ISWATCHLIBRARYPANELHELPER };
	
	/**	Preload the swatch library list from the preset folder.
		@return kSuccess if no errors, otherwise returns an error code.
	*/
	virtual ErrorCode		PreLoadLibraryList (void) = 0;
	
	/**	Create a new panel base on the preloaded swatch library list.
		Caller should keep the creation process going until all panels are created.
	 	Must call preloadLibraryList () first.
		Note also the panel is not populated with swatch list until it is actually shown.
		@param pPanelName the panel's name is returned if pPanelName is not nil.
		@return the panel's IControlView* if panel is created.
	*/
	virtual	IControlView*	NewPanel		(PMString* pPanelName= nil) = 0;


	/**	Build the library panel by populating the panel with the swatch list.
		This is usually called when the panel is to be shown.
		@param iLibPanelView specifies the library panel view.
		@return kSuccess if no errors, otherwise returns an error code.
	*/
	virtual	ErrorCode		BuildPanel		(IControlView* iLibPanelView) = 0;

	/**	Validate the library panel.
		This make sure that the library file associated with the panel still exists.
		(User might have moved or deleted the file.)
		@param iLibPanelView specifies the library panel view.
		@return kTrue if still valid, otherwise returns kFalse.
	*/
	virtual	bool16			ValidatePanel		(IControlView* iLibPanelView) = 0;

	/**	Load and build a library panel the user has explicitly selected via "Other..."
		@param widgetID will contain the new widget ID for this panel.
		@param pPanelName the panel's name is returned if pPanelName is not nil.
		@return the new panel's IControlView* if library is loaded and panel is created.
	*/
	virtual IControlView*	LoadOtherLibrary	(WidgetID& widgetID, PMString* pPanelName= nil) = 0;

	/**	Rescan the designated swatch library panel for new library files and return kTrue
		if at least one new library is found. Only rescan if library files already preloaded.
	
		If K2Vector<WidgetID>* is not nil, then it also returns a list of library panel
		widget ID that must be revalidated to ensure the library panel is up-to-date.
	
		Caller should call NewPanel to create a new panel based on the rescanned list.
		Continue until NewPanel returns an IControlView* = nil.
	
		If a non-empty K2Vector<WidgetID>* is returned, the caller should call Validate for
		each of the panel in the list.
		The validatation must be make by the caller since the caller has knowledge regarding
		how the library panel is being used.
	
		@param iPanelData contains the currently loaded library panels.
		@param pInvalPanelList If pInvalPanelList is not nil, then it also returns a 
		list of library panel widget ID that must be revalidated to ensure the library panel 
		is up-to-date.
		@return true if at least one new library is found.	
	*/
	virtual bool16			RescanLibraryList	(IPanelControlData* iPanelData, K2Vector<WidgetID>* pInvalPanelList = nil) = 0;


	/**	Returns the swatch library's panel name from the library's creator ID.
		@param iPanelData contains the currently loaded library panels.
		@param creatorID specifies the creator ID.
	*/
	virtual PMString		GetLibraryNameFromCreatorID	(IPanelControlData* iPanelData, int32 creatorID) = 0;
	/**	Returns the swatch library's panel name from the library's creator ID.
		@param creatorID specifies the creator ID.
	*/
	virtual PMString		GetLibraryNameFromCreatorID	(int32) = 0;

	/**	Select the swatch with swatchName in the specified swatch library's panel.
		@param iLibPanel specifies a library panel.
		@param swatchName is the swatch name to select.
	*/
	virtual void			SelectLibraryPanelSwatch	(IControlView* iLibPanel, const PMString& swatchName) = 0;
	
	/*	Return kTrue if the specified library swatch selection list is valid.
		@param iLibPanel specifies a library panel.
		@param selectList is the list of library swatch selection to check.
		@param validList A list of valid swatches in returned in the validList.
		@param conflictList A list of pantone conflict list is returned in pantoneList. 
		The UIDs in this list matches in position to UID in the validList which caused 
		the PANTONE conflicts. In position where swatch is not a PANTONE swatch, 
		it is set to kInvalidUID.
	*/
	virtual ErrorCode		IsLibraryPanelSwatchSelectionValid	(IControlView* iLibPanel, const UIDList& selectList, UIDList& validList, UIDList& conflictList) = 0;
	
	/**	Returns a list of library swatches selected.
		@param iLibPanel specifies a library panel.
		@param selectList is the list of new library swatch selection returned.
	*/
	virtual void			GetLibraryPanelSwatchSelections (IControlView* iLibPanel, UIDList& selectList) = 0;
};

#endif
