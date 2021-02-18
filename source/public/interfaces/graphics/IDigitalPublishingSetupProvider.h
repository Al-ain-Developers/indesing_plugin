//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDigitalPublishingSetupProvider.h $
//  
//  Owner: Adobe Systems Inc.
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once

#include "DigitalPublishingID.h"

#include "DigitalPublishingDictionary.h"
#include "MiniFolioOptions.h"

class IDocument;

/**
 Simple C++ service to be implemented by anyone wishing to be notified as events
 occur during the creation of a digital publishing folio file. Implementors can
 use these notifications to control how the folio file is created, including how
 interactive overlay instances are created.

 ***NOTES:

 Accessing the provider MUST be done using the new utility 
 digpub::QueryIDigitalPublishingSetupProvider defined below because it determines
 which version of the provider interface to use: IDigitalPublishingSetupProvider 
 or IDigitalPublishingSetupProvider2.
 
 Usage example:
	...
	InterfacePtr<IK2ServiceProvider> service(registry->QueryNthServiceProvider(kDigitalPublishingSetupService, i));
	InterfacePtr<IDigitalPublishingSetupProvider> provider(digpub::QueryIDigitalPublishingSetupProvider(service));
	...

 */
class IDigitalPublishingSetupProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIGITALPUBLISHINGSETUPPROVIDER };
	
	/**
	 Interface to be used to create instances of interactive overlays
	 during creation of a folio file.
	 
	 Note: This is *not* a standard InDesign interface and does not
	 have AddRef/Release or QueryInterface methods. This implies that
	 instances *cannot* be safely stored between method invocations.
	 */
	class OverlayCreator
	{
	public:
		virtual ~OverlayCreator() {}
		
		/**
		 Factory method for creating an instance of an empty overlay dictionary.
		 The dictionary should be populated using the Object interface and then
		 passed to CreateOverlay.
		 
		 @return a new instance of an empty dictionary object
		 */
		virtual id_digpub::ObjectPtr CreateEmptyOverlayDictionary() const = 0;
		
		/**
		 Creates a new overlay based on the parameters passed in.
		 
		 @param overlayParams		A dictionary defining the parameter for the overlay
		 @return an ErrorCode indicating the success/failure of the call
		 */
		virtual ErrorCode CreateOverlay(id_digpub::ObjectPtr const &overlayParams) = 0;
	};
	
	/**
	 Notification that a folio is about to be created. Called prior to exporting
	 any of the content stacks that make up the folio.
	 
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode BeginFolioCreation() = 0;
	
	/**
	 Notification that folio creation has completed. This is called even if the
	 folio creation encountered an error or was aborted by a setup provider.
	 
	 @param folioWasCreated		true if the folio was created, otherwise false
	 */
	virtual void EndFolioCreation(bool folioWasCreated) = 0;
	
	/**
	 Notification that overlay collection is about to occur. This is called 
	 when the system needs to determine the list of overlays outside the 
	 context of folio generation. For example, this will be called if the 
	 getAllOverlays  scripting API is used. It will *not* be called during 
	 normal folio generation.
	 
	 @return kSuccess if the overlay collection should continue, or an error code to abort it
	 */
	virtual ErrorCode BeginOverlayCollection() = 0;
	
	/**
	 Notification that overlay collection has completed. Like the matching
	 BeginOverlayCollection call, this is only called when the system needs
	 to determine the list of overlays outside the context of folio generation.
	 */
	virtual void EndOverlayCollection() = 0;

	/**
	 Orientation for a content stack
	 */
	enum Orientation
	{
		kPortraitOrientation,
		kLandscapeOrientation,
		
		kInvalidOrientation = 0xffffffff
	};
	
	/**
	 Notification that a content stack is about to be generated. These are generated 
	 from a source document in separate passes for portrait and landscape orientations.
	 
	 @param doc				The document representing the content stack
	 @param orientation		The orientation being generated
	 @param folioOptions	The options for this folio. This includes wide and narrow dimension for the folio,
							asset format and quality, smooth scrolling, ect.
							@see MiniFolioOptions.h
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode BeginContentStack(IDocument const *doc, Orientation orientation, const MiniFolioOptions& folioOptions) = 0;
	
	/**
	 Notification that generation of a content stack has completed.

	 @param doc				The document representing the content stack
	 @param orientation		The orientation being generated
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode EndContentStack(IDocument const *doc, Orientation orientation) = 0;
	
	/**
	 Notification that a page in a content stack is about to be generated.
	 
	 Note: In current implementation, spreads are exported a page at a time. This
	 will likely change in the future. When this occurs - and the options selected 
	 for folio generation indicate that we should generate stack pages from spreads
	 instead of pages -  the 'page' and 'index' parameters will point to the spread 
	 and spread index, rather than page and page index as they do now. For the
	 kPDFGenerationPass, only one page per spread is supported, and the page parameter
	 is a UIDRef to that page.
	 
	 @param doc				The document representing the content stack
	 @param page			Reference to the page or spread for the content stack page (see note above)
	 @param index			Index of the page or spread, starting from zero
	 @param overlayCreator	An instance of an overlay creator that can be used to generate overlay instances for the page
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode BeginPage(
		IDocument const *doc,
		UIDRef const &page,
		uint32 index,
		OverlayCreator *overlayCreator
	) = 0;
	
	/**
	 Notification that a page in a content stack has been generated.
	 
	 Note: In current implementation, spreads are exported a page at a time. This
	 will likely change in the future. When this occurs - and the options selected 
	 for folio generation indicate that we should generate stack pages from spreads
	 instead of pages -  the 'page' and 'index' parameters will point to the spread 
	 and spread index, rather than page and page index as they do now. For the
	 kPDFGenerationPass, only one page per spread is supported, and the page parameter
	 is a UIDRef to that page.
	 
	 @param doc				The document representing the content stack
	 @param page			Reference to the page or spread for the content stack page (see note above)
	 @param index			Index of the page or spread, starting from zero
	 @param overlayCreator	An instance of an overlay creator that can be used to generate overlay instances for the page
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode EndPage(
		IDocument const *doc,
		UIDRef const &page,
		uint32 index,
		OverlayCreator *overlayCreator
	) = 0;
		
	/**
	 Drawing passes. The folio generation code will make multiple passes
	 over the content. This specifies which pass is being done.
	 */
	enum DrawPass
	{
		kScrubberDrawPass,
		kAssetDrawPass,
		kThumbnailDrawPass,
		
		// Note: This pass will occur outside the normal BeginPage/EndPage
		// pair of notifications.
		kTOCImageDrawPass,
		
		kOverlayCollectionPass,
		
		kPDFGenerationPass,
		
		kInvalidDrawPass = 0xffffffff
	};
	
	/**
	 Notification that a drawing pass is about to begin. Note that this will 
	 occur within a BeginPage/EndPage block for asset and thumbnail passes but 
	 *not* for the scrubber pass.
	 
	 Note: In current implementation, spreads are exported a page at a time. This
	 will likely change in the future. When this occurs - and the options selected 
	 for folio generation indicate that we should generate stack pages from spreads
	 instead of pages -  the 'page' and 'index' parameters will point to the spread 
	 and spread index, rather than page and page index as they do now. For the
	 kPDFGenerationPass, only one page per spread is supported, and the page parameter
	 is a UIDRef to that page.

	 @param doc				The document representing the content stack
	 @param page			Reference to the page or spread for the content stack page (see note above)
	 @param pass			The drawing pass that is about to begin
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode BeginDrawingPass(
		IDocument const *doc,
		UIDRef const &page,
		DrawPass pass
	) = 0;

	/**
	 Notification that a drawing pass has ended. Note that this will occur 
	 within a BeginPage/EndPage block for asset and thumbnail passes but *not*
	 for the scrubber pass.
	 
	 Note: In current implementation, spreads are exported a page at a time. This
	 will likely change in the future. When this occurs - and the options selected 
	 for folio generation indicate that we should generate stack pages from spreads
	 instead of pages -  the 'page' and 'index' parameters will point to the spread 
	 and spread index, rather than page and page index as they do now. For the
	 kPDFGenerationPass, only one page per spread is supported, and the page parameter
	 is a UIDRef to that page.

	 @param doc				The document representing the content stack
	 @param page			Reference to the page or spread for the content stack page (see note above)
	 @param pass			The drawing pass that is about to begin
	 @return kSuccess if the folio creation should continue, or an error code to abort it
	 */
	virtual ErrorCode EndDrawingPass(
		IDocument const *doc,
		UIDRef const &page,
		DrawPass pass
	) = 0;

	/**
	 Called for each content stack page, after a call to BeginPage has occurred, but
	 before any content generation has occurred. This allows the setup provider to
	 hook into the drawing code and determine whether or not particular page items
	 are drawn during content generation.
	 
	 @return true if the set up provider should be notified as page items draw in the given pass
	 */
	virtual bool GetShouldNotifyOnPageItemDraw(DrawPass pass) const = 0;
	
	/**
	 Options for controlling how page items should be drawn during content generation
	 */
	enum DrawBehavior
	{
		kDrawBehaviorIncludeItem,
		kDrawBehaviorOmitItem,
		kDrawBehaviorAbortDrawing,
		
		kDrawBehaviorInvalidOption = 0xffffffff
	};
	
	/**
	 Called if GetShouldNotifyOnPageItemDraw returned true for the current pass, 
	 indicating that the setup provider wants to hook into the page item 
	 drawing pipeline for assets.
	 
	 Note: The overlayCreator parameter may be nil if overlay creation is not
	 supported in the given pass. In current implementation, overlay creation is
	 only supported in the kAssetDrawPass and kOverlayCollectionPass passes.
	 
	 @param thisThing		The page item being drawn. Use ::GetUIDRef(pageitem) to get the UIDRef this page item.
							Note that for text, this may not be an UID-based item, so UIDRef may be null.
	 @param pass			The current DrawPass.
	 @param overlayCreator	An instance of an overlay creator that can be used to generate overlay instances for the page, or nil if not supported
	 @return one of the DrawBehavior values indicating how to handle the page item
	 */
	virtual DrawBehavior HandlePageItemDraw(
		IPMUnknown const *thisThing,
		DrawPass pass,
		OverlayCreator *overlayCreator
	) = 0;
};

class IDigitalPublishingSetupProvider2 : public IDigitalPublishingSetupProvider
{
public:
	enum { kDefaultIID = IID_IDIGITALPUBLISHINGSETUPPROVIDER2 };	

	/**
	 Called if GetShouldNotifyOnPageItemDraw returned true for the overlay collection pass, 
	 indicating that the setup provider wants to hook into the page item drawing pipeline for assets.
	 This will only be called for DrawPass kOverlayCollectionPass pass.
	 
	 The overlayCreator parameter is set for overlay collection pass.
	 
	 @param thisThing		The page item being drawn. Use ::GetUIDRef(pageitem) to get the UIDRef this page item.
							Note that for text, this may not be an UID-based item, so UIDRef may be null.
	 @param pass			The current DrawPass. This should be set to kOverlayCollectionPass.
	 @param overlayCreator	An instance of an overlay creator that can be used to generate overlay instances for the page, or nil if not supported
	 @param contextData		An data interface for the draw event context. NOTE: This is optional and to be used internally only.
	 @return one of the DrawBehavior values indicating how to handle the page item
	 */
	virtual DrawBehavior HandlePageItemOverlayCollection(
		IPMUnknown const *thisThing,
		DrawPass pass,
		OverlayCreator *overlayCreator,
		IPMUnknown *contextData = nil
	) = 0;
};

namespace digpub
{

inline InterfacePtr<IDigitalPublishingSetupProvider> QueryIDigitalPublishingSetupProvider(IPMUnknown *boss)
{
	InterfacePtr<IDigitalPublishingSetupProvider> provider(boss, UseDefaultIID());
	
	if (!provider)
	{
		provider = InterfacePtr<IDigitalPublishingSetupProvider2>(boss, UseDefaultIID());
	}
	
	return provider;
}

}
