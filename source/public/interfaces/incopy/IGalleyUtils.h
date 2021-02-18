//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleyUtils.h $
//  
//  Owner: 
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
#ifndef __IGALLEYUTILS__
#define __IGALLEYUTILS__

#include "WritingModeID2.h"
#include "IFontMgr.h"

class IPanelControlData;
class IControlView;
class IDocumentPresentation;
class IFontInstance;
class IDocument;
class IGraphicsContext;
class IGraphicsPort;
class RealAGMColor;
class ITextModel;
class ITextLines;
class IDrawingStyle;

namespace InDesign{ class TextRange;}
class ITextTarget;
class ILayoutTarget;
class ITableTarget;
class IViewColorScheme;

#include "IPMUnknown.h"
#include "UIDList.h"
#include "ITextDataValidation.h"
#include "IInCopyViewPrefs.h"
#include "K2Vector.h"
#include "RangeData.h"
#include "Utils.h"

/**	IGalleyUtils is an aggregrate of many different utility functions centered
	around the document window and galley sub window.

	A writing widget is identified by having a ITEXTLINES and IQUICKCOMPOSER interface
	The user interface shows three tabs in the document window, one layout, one galley,
	and one story.  But the widget hierarchy actually only contains a layout view and
	a writing widget that has two modes:  Accurate line endings (Galley) and 
	innaccurate line endings (Story).  Some of the helper functions below attempt to
	mimic what the user sees rather than how it is implemented, i.e. there are 
	three constants for the view, kLayout, kStory, kGalley.

	All references to the writing widget really refer to the composite widget that can
	either be showing accurate line endings or innaccurate line endings.

	A writing widget can contain multiple stories but only one story has text focus
	at a time.  The story with text focus is the active story.
*/

class IGalleyUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGALLEYUTILS };

	/**	Type definitions for some of the methods below is in IInCopyViewPrefs.
		The document window is either in kGalley, kStory, or kLayout.  kGalley 
		is the accurate line endings mode with copyfit. kStory is the innaccurate 
		line endings mode without copyfit. kLayout is the InDesign layou preview mode.
	*/
	
	/**	Returns the writing widget that has the passed in story ref. If a writing widget
		is not found it returns nil.  
		@param panelData The panel control data of the document window
		@param storyRef The story reference the caller wants to find the writing widget for
		@return The writing widget
	*/
	virtual IControlView *GetWritingWidget(IPanelControlData *panelData, UIDRef storyRef) = 0;

	/**	Returns the active story for the given writing widget.
		@param writingWidget The writing widget used to get the active story.
		@return The active story.
	*/
	virtual UIDRef GetStoryRef(IControlView *writingWidget) = 0;

	/**	Returns the frame corresponding to the given writing widget.  If the
		text is threaded through several frames then this is the first frame in
		the thread.
		@param writingWidget The writing widget used to get the active story and then frame.
		@return The frame that corresponds to the active story.
	*/
	virtual UIDRef GetFrameRef(IControlView *writingWidget) = 0;

	/** Get the story index for a galley/story editor story.
	@param textLines IN the ITextLines interface.
	@param textModel IN the text model.
	@return story index for this story. -1 if not found.
	*/
	virtual int32 GetStoryIndex(ITextLines* textLines, ITextModel* textModel) = 0;

	/**	Finds the writing widget in the front most document window of the passed in
		document. This method does not AddRef the writing widget.
		@param document The document to find the widget from.
		@return The writing widget.  Caller does not need to release the writing widget.
	*/
	virtual IControlView *FindGalleyView(IDocument *document) = 0;

	/**	A mechanism to measure interface text that does not rely on an AGMGraphicsContext.
		@param fontInstance The font used to measure with.
		@param data The string of text to measure.
		@param xWidth OUT The returned width in pixels.
		@param yWidth OUT The returned height in pixels.
	*/
	virtual void MeasureText(IFontInstance *fontInstance, const PMString& data, PMReal* xWidth, PMReal* yWidth) = 0;

	/**	Returns the front most document window associated with the document. If 
		document is nil then it finds the window associated with the front
		most document.  If the front most window of the document is in kLayout mode
		then this function will return nil.  In other words, this method is a combination
		InGalleyOrStory and FindGalleyView.
		@param document The document to find the front most document window. If 
		document is nil then it uses the front most document window 
		@return The front most document window of document.  Nil if the front most
		document window is in kLayout mode.
	*/
	//virtual IWindow *FindFrontmostGalleyWindow( IDocument *document = nil ) = 0;
	virtual IDocumentPresentation *FindFrontmostGalleyPresentation( IDocument *document = nil ) = 0;

	/**	Returns the front most layout window associated with the document. If 
		document is nil then it finds the frontmost layout window associated with the 
		active context document.  If there are no layout windows open this function
		will return nil.
		@param document The document to find the front most layout window.
		@return The front most layout window of document.  Nil if there are no layout windows.
	*/
	//virtual IWindow *FindFrontmostLayoutWindow( IDocument *document = nil ) = 0;
	virtual IDocumentPresentation *FindFrontmostLayoutPresentation( IDocument *document = nil ) = 0;

	/**	Returns a list of writing widgets for the dococument.  This is a list
		because there can be more than one document window open and therefore more
		than one writing widget.  If there are N document windows open then there
		will be N writing widgets in the return value.
		@param onDocRef The document to find the writing widgets.  If empty then the
		method gets the front most document.
		@return A UIDList of the writing widgets.  
	*/
	virtual UIDList GetGalleyPanels( UIDRef onDocRef = UIDRef() ) = 0;

	/**	
		@deprecated This API is deprecated. Please use GetFontOfStyleStdStr() instead.
		Returns the name of the font given the family name and style.  Fonts often 
		have font variants for the bold, italic, bolditalic, all caps, and small caps.
		For example, Times and Times Bold are two different fonts but you may only
		want to refer to Times and ask for the variant by ID (fontStyle).  This method
		will attempt to find the variant that contains the style asked for.
		@param fontFamilyName The font family name.
		@param fontStyle The style of the font such as kBold.
		@return The postscript name of the font having the style.
	*/
	virtual PMString GetFontOfStyle(PMString fontFamilyName, IFontMgr::FontStyleBits fontStyle) = 0;

	/**	Platform neutral way to get the interface font.  Windows, Mac OS 9, and Mac OS X all
		have different interface fonts.  This method allows client code to remain platform
		agnostic.
		@param hilite Indicates whether to get the normal (kFalse) or bold (kTrue) interface font.
		@return The corresponding interface font.  
	*/
	virtual	IPMFont*	QueryInterfaceFont(bool16 hilite) = 0;

	/**	Draws a string in the interface font appropriate for the platform. This is necessary 
		because agm doesn't render the interface font properly. textBounds is the area the 
		string draws into in gPorts coordinates. textLoc specifies the baseline in relation 
		to text bounds. 0,0 would put the baseline at the top left of textBounds.
		@param string The text string to render.
		@param drawInView The view we are drawing the string in. All coordinates are local to this view.
		@param gPort The graphics port to render into.
		@param textBounds The area the string draws in the port.
		@param textLoc The baseline in relation to textBounds.  0,0 would be at the top left of textBounds.
		@param textColor The color to render the string in.
		@param backgroundColor The color to fill behind the text.
		@param hilite Indicates whether to use the normal (kFalse) or bold (kTrue) interface font.
	*/
	virtual	void	DrawInterfaceString(const PMString& string, IControlView *drawInView, IGraphicsPort* gPort, const PMRect& textBounds,
	                                 const PMPoint& textLoc, const RealAGMColor& textColor,
	                                 const RealAGMColor& backgroundColor, bool16 hilite = kFalse) = 0;
	
	/**	Returns the ClassID list of x measure unit, with kRulerCustomMSBoss in the last item.
		@param unitList OUT the x measure unit list.
	*/
	virtual void GetXMeasureUnitList(K2Vector<ClassID>& unitList) = 0;

	/**	Returns the indices of the text lines specified in rangeText that is between start and end.
		@param rangeList OUT The list of lines.
		@param rangeText The text the user entered in the print or PDF dialog to specify a range
		@param start The starting index within which to search
		@param end The ending index within which to search
		@return Returns whether the passed in arguments are valid or not. See ITextDataValidation.
	*/
	virtual ITextDataValidation::RangeError ParseLineRange(K2Vector<int32>& rangeList, PMString rangeText, int32 start, int32 end) =0;


	/**	
		@deprecated This API is deprecated. Please use GetFontNameStdStr() instead
		A more generic way to find a font and style.  Some fonts have non-standard styles that
		can only be specified by a string.  This method finds the font fontFamilyName of style
		style and returns it.
		@param fontName OUT The returned postscript font name if a font is found.
		@param fontFamilyName The font family name such as Times.
		@param style The font style such as Bold.
	*/
	virtual void GetFontName(PMString &fontName, PMString &fontFamilyName, PMString &style) = 0;


	/**	Returns the entire font family given a family name.  
		@param StyleList OUT The list of fonts that are in the family.
		@param fontFamily The font family such as Times.
	*/
	virtual void GetFontStyleList(K2Vector<PMString>& StyleList, PMString &fontFamily) = 0;
	

	/**	Returns a list of all the fonts installed in the font manager.
		@param List OUT The list of all the fonts.
		@param filterSymbolFonts if True it will filter out some known symbol fonts otherwise it will return a full list
		@param translatedFontList will return a list of the fonts with translated names for ui display
	*/
	virtual void GetFontNameList(K2Vector<PMString>& fontList, bool16 filterSymbolFonts = kTrue, K2Vector<PMString> *translatedFontList = nil) = 0;


	/**	Given a full font name return the family and style.
		@param fontName The font name to look up the family and style for.
		@param fontFamily OUT The family of the specified font.
		@param fontStyle OUT The style of the specified font.
	*/
	virtual void GetFontFamilyAndStyle(PMString &fontName, PMString &fontFamily, PMString &fontStyle) = 0;

	/**	Returns kTrue if the window has the writing widget active, i.e. in kGalley or kStory mode.
		@param window The window to check.  If nil this method uses the front most document window.
	*/
	virtual	bool16 InGalleyOrStory ( IDocumentPresentation* pres = nil ) = 0;

	/**	Returns kTrue if the window is in kGalley mode.
		@param window The window to check.  If nil this method uses the front most document window.
	*/
	virtual	bool16 InGalley ( IDocumentPresentation* pres = nil ) = 0;

	/**	Returns kTrue if the window is in kStory mode.
		@param window The window to check.  If nil this method uses the front most document window.
	*/
	virtual	bool16 InStory ( IDocumentPresentation* pres = nil ) = 0;

	/**	Returns kTrue if the window is in kLayout mode.
		@param window The window to check.  If nil this method uses the front most document window.
	*/
	virtual	bool16 InLayout ( IDocumentPresentation* pres = nil ) = 0;

	/**	Returns the ViewMode (kStory, kGalley, or kLayout) of the window.
		@param window The window to check.  If nil this method uses the front most document window.
	*/
	//virtual	IInCopyViewPrefs::ActiveView GetDocWindowView ( IWindow* window = nil ) = 0;
	virtual	IInCopyViewPrefs::ActiveView GetViewMode ( IDocumentPresentation* pres = nil ) = 0;

	/**	Sets the current view of the given document window.  If there are no InCopy stories
		in the InCopy story list this method will force the window into kLayout mode only.
		@param window The window to set the view mode on.
		@param viewMode The view mode to use (kStory, kGalley, kLayout).
	*/
	//virtual	void SetDocWindowView ( IWindow* window, IInCopyViewPrefs::ActiveView viewMode ) = 0;
	virtual	void SetViewMode ( IDocumentPresentation* pres, IInCopyViewPrefs::ActiveView viewMode ) = 0;


	/**	Set the selection in the Galley or Story mode.
		@param nStart The start index of the selection to set.
		@param nEnd The end index of the selection to set.
		@param storyRef The story to make active and to set the selection in.
		@param ownedItemAllowed kTrue to set selection in the owned item story thread,
		kFalse to convert selection in owned item story thread into its anchor position
		and set it as the current selection.
	*/
	virtual void SetGalleyTextSelection(TextIndex nStart, TextIndex nEnd, UIDRef storyRef, IControlView *forView = nil, bool16 ownedItemAllowed = kFalse) = 0;

	/**	Set the selection in the Layout mode.
		@param nStart The start index of the selection to set.
		@param nEnd The end index of the selection to set.
		@param storyRef The story  to set the selection in.
		@param ownedItemAllowed kTrue to set selection in the owned item story thread,
		kFalse to convert selection in owned item story thread into its anchor position
		and set it as the current selection.
	*/
	virtual void SetLayoutTextSelection(TextIndex nStart, TextIndex nEnd, UIDRef storyRef, bool16 ownedItemAllowed = kFalse) = 0;

	/**	Get the current selection regardless of which mode the document window is in.
		@param nStart OUT The start index of the selection.
		@param nEnd OUT The end index of the selection.
		@param storyRef OUT The story the selection is in.
	*/
	virtual void GetCurrentTextSelection(TextIndex& nStart, TextIndex& nEnd, UIDRef* storyRef, IControlView *view = nil) = 0;


	/**	Returns the list of InCopy stories in the document.  This method uses the
		InCopy story list but filters out any InCopy stories which are inline stories
		of other InCopy stories.
		@param document The document to get the stories for.
		@param stories OUT The return list of stories.
		@param stripGraphicStoris IN A flag to indicate if graphic stories should be stripped.
	*/
	virtual void GetListOfUserStories(IDocument *document, UIDList &stories, bool16 stripGraphicStories = kFalse) = 0;


	/**	This checks the front most documet window to see if the given story is
		collapsed. Each writing widget can have a different list of collapsed and
		not collapsed stories.  Returns kFalse if the front most window is in kLayout
		mode.
		@param storyRef The Story to check if it is collapsed.
	*/
	virtual bool16 IsStoryCollapsedInGalley(const UIDRef &storyRef) = 0;
	

	/**	For the given document window return the list of expanded stories.
		@param window The window from which to find the writing widget. Can be the
		document window or the galley window.
		@param storyList OUT Returns the list of expanded stories.
	*/
	virtual void GetNonCollapsedStoryList(IDocumentPresentation * pres, UIDList &storyList) = 0;
	

	/**	Returns the page number string for the given index.  Essentially maps the index
		to a frame and computes the page that frame is on.
		Assumes that we have the position of a page number character. If this is true then it will
		return the string representation of the page number this character is on. Only will work
		in galley or layout. Story does not have the information available to calculate page numbers.
		Routine IS NOT fast don't call it unnecessarily.  
		@param pageNumberCharIndex The text index to check.
		@param model The text model to check in.
		@return The page number string.
	*/
	virtual PMString GetPageNumberString(TextIndex pageNumberCharIndex, ITextModel *model) = 0;
	

	/**	Calculates the overset line lengths.
		@param model The text model to compute from.
		@param startModelOffset The text index to start from.
		@param averageLineLength The average line length to use computing the line lengths.
		@param primarySpan The length of the primary span.
		@param endsInForceBreak Returns whether the line ends because of a break character or not.
		@return Returns the index of where the line broke.
	*/
	virtual int32 GetTrueOversetLineLength(ITextModel *model, TextIndex startModelOffset, int32 averageLineLength, 
											int32 primarySpan, bool16 &endsInForceBreak) = 0;

	/**	Estimates the average line length the normal composer used when composing this text model.
		@param model The text model to use.
		@return The average line length.
	*/
	virtual int32 EstimateOversetLineLengths(ITextModel *model) = 0;

	/**	Returns if the given character is a break character or no. e.g. a carraige return.
		@param character The text character to check in UTF32 format. Note, unless it's a J paragraph this is all that is really is needed to get a break point
		@param forceBreak OUT Whether this is a force break character or not.
		@param drawStyle used to determine whether this is a J paragraph which needs additional break rules applied
		@param model if this is a J paragraph then the routine needs to look at surrounding characters to determine legal breaks
		@param position text index within the story to look for legal break points
		@return Returns kTrue if this is a bream character, kFalse if not.
	*/
	virtual bool16 IsBreakCharacter(const UTF32TextChar &character, bool16 &forceBreak, 
									IDrawingStyle *drawStyle = nil, ITextModel *model = nil, TextIndex position = 0L) = 0;
	
	/** Recreate textlines or simply redraw the text dependent on flags.
		@param writingView The writing control view.
		@param justInval kFalse means to recompose the text.
		@param ignoreILE kTrue measn to ignore the text when the mode is ILE
		@param backgroundCompose when justInval is kFalse, backgroundCompose is kTure means to compose starting first line.
	*/
	virtual void RefreshAllText(IControlView* writingView, bool16 justInval, bool16 ignoreILE, bool16 backgroundCompose = kFalse) = 0;
	
	
	/** Redraw the info column.
	*/
	virtual void InvalInfoColumn(IControlView* writingView) = 0;

	/**	This is a helper method that wraps the command to suspend play pending invals (drawing)
		for the text lines associated with the specified window.
		@param window The window to suspend.  If nil this method uses the front most document window.
		@return Returns kTrue if suspend was successful.
	*/
	virtual bool16 SuspendPlayPendingInvals(IDocumentPresentation* pres = nil) = 0;

	/**	This is a helper method that wraps the command to resume play pending invals (drawing)
		for the text lines associated with the specified window.
		@param window The window to resume.  If nil this method uses the front most document window.
		@return Returns kTrue if resume was successful.
	*/
	virtual bool16 ResumePlayPendingInvals(IDocumentPresentation* pres = nil) = 0;

	/**	This is a helper method that wraps the command to suspend play pending invals (drawing)
		for the text lines associated with the specified window.
		@param viewRef The control view UIDRef to suspend.  If nil this method uses the front most document window.
		@return Returns kTrue if suspend was successful.
	*/
	virtual bool16 SuspendPlayPendingInvals(UIDRef viewRef = UIDRef::gNull) = 0;

	/**	This is a helper method that wraps the command to resume play pending invals (drawing)
		for the text lines associated with the specified window.
		@param viewRef The control view UIDRef to resume.  If nil this method uses the front most document window.
		@return Returns kTrue if resume was successful.
	*/
	virtual bool16 ResumePlayPendingInvals(UIDRef viewRef = UIDRef::gNull) = 0;

	/**	This is a helper method that will give back widths of different types of space characters.
		You may pass any character to it if the character is not of a type this routine knows something
		about the charWidth parameter will not be adjusted if it is then the charWidth parameter may be
		modified to give the width of the special type space character. Faked space characters are things
		like emspace, enspace, thinspace etc.
		@param character Character code of the character to check
		@param ptSize display font point size (used to determine m space widths and other spaces based on m spaces)
		@param fontInstance instance of font that we are displaying text with.
		@param charWidth the width of the space character is returned in this parameter. This value is not changed
		if the character is not recognized by this routine.
		@return Returns kTrue if resume was successful.
	*/
	virtual void CorrectFakedSpaceWidth(const UTF32TextChar &character, PMReal ptSize, IFontInstance *fontInstance, PMReal &charWidth) = 0;

	/**	This routine will scroll the view to the current cursor location. It will be scrolled so that the cursor is
		visible not centered.
		@param writingView the gallay or story view to scroll to the cursor on.
		@param forceScroll force the view to scroll to so that cursor is at the view top even if the cursor is already visible
		@return none
	**/
	virtual void ScrollToCursor(IControlView *writingView, bool16 forceScroll = kFalse) = 0;

	/**	Get the stories to display in the galley and story views while running in InCopy.
		@param theDoc document to retrieve stories for
		@param filteredStories list of stories to display in story and galley is returned in this variable
		@param stripGraphicStories want to pass true for this parameter story and galley don't support graphic stories.
		@return none
	**/
	virtual void GetInCopyStoriesForGalley(IDocument *theDoc, UIDList& filteredStories, bool16 stripGraphicStories) = 0;

	/** Create if necessary and write out a story list file. Document will be created
		in the same directory as the parent document. Parent document must have been previously 
		been saved to disk for this to work. This routine is currently only relevant for INCOPY.
		Because only InCopy supports multiple stories in a view.
		@param document to create the story list file from (parent document).
		@return - kTrue if successful
	*/
	virtual bool16 WriteStoryListFile(const UIDRef &docRef) = 0;
	
	/** Read an existing story list file and apply the results to all galley and story views.
		This routine is only relevant for INCOPY and will not work for InDesign. Because only 
		InCopy supports multiple stories in a view. Assumes the story list file exists next to the InDesign
		document as would be created by the WriteStoryListFile() routine.
		@param document associated with the story list file from (parent document).
		@return - kTrue if successful
	*/
	virtual bool16 ReadStoryListFile(const UIDRef &docRef) = 0;

	/**	Returns the name of the font given the family name and style.  Fonts often 
		have font variants for the bold, italic, bolditalic, all caps, and small caps.
		For example, Times and Times Bold are two different fonts but you may only
		want to refer to Times and ask for the variant by ID (fontStyle).  This method
		will attempt to find the variant that contains the style asked for.
		@param fontFamilyName The font family name.
		@param fontStyle The style of the font such as kBold.
		@return The postscript name of the font having the style.
	*/
	virtual std::string GetFontOfStyleAsStdStr(PMString fontFamilyName, IFontMgr::FontStyleBits fontStyle) = 0;

	/**	A more generic way to find a font and style.  Some fonts have non-standard styles that
		can only be specified by a string.  This method finds the font fontFamilyName of style
		style and returns it.
		@param fontName OUT The returned postscript font name if a font is found.
		@param fontFamilyName The font family name such as Times.
		@param style The font style such as Bold.
	*/
	virtual void GetFontNameAsStdStr(std::string &fontName, PMString &fontFamilyName, PMString &style) = 0;


};

#endif // __IGALLEYUTILS__
