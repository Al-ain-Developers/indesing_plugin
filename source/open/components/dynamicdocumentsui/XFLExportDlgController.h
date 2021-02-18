//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/XFLExportDlgController.h $
//  
//  Owner: DBerggren
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "CDialogController.h"

class IControlView;
class IDocument;
class IPageRange;
class IPanelControlData;

//========================================================================================
// CLASS SWFExportDlgController
//========================================================================================
class XFLExportDlgController : public CDialogController
{
	public:
		enum {
			// Export Intent
			kSmallestFileSizeIndex		= 0,
			kMediumFileSizeIndex,
			kHighestQualityIndex,

			// Fit To
			k1280x800Index				= 0,
			k1240x620Index,
			k1024x768Index,
			k984x588Index,
			k800x600Index,
			k760x420Index,
			k640x480Index,
			k600x300Index,

			// Scale
			k250Index					= 0,
			k200Index,
			k150Index,
			k100Index,
			k75Index,
			k50Index,
			k25Index,

			// Text
			kFlashTextIndex				= 0,
			kVellumTextIndex,
			kVectorTextIndex,
			kRasterTextIndex,

			// JPEG format
			kJPEGFormatIndex		= 0,
			kPNGFormatIndex,
			kAutomaticFormatIndex,

			// Quality
			kMinQualityIndex			= 0,
			kLowQualityIndex,
			kMedQualityIndex,
			kHighQualityIndex,
			kMaxQualityIndex
		};

		// ----- Initialization -----
		XFLExportDlgController(IPMUnknown *boss);
		virtual	~XFLExportDlgController();
	
		// ----- Dialog protocol -----
		virtual void InitializeDialogFields( IActiveContext* ac);
		virtual void ResetDialogFields(IActiveContext* ac);
		virtual WidgetID ValidateDialogFields(IActiveContext* ac);

		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

	private:

		void InitializeRangeEdit(IPageRange* iPageRange, IDocument* iDocument, IPanelControlData* iPanelControlData);
		bool16 InitRangeEditBox(IControlView* controlView, IDocument* iDocument, PMString& pageRangeText);

};


// End, XFLExportDlgController.h.
