//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IFlashXFLExportFacade.h $
//  
//  Owner: Yeming Liu
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

#pragma once
#ifndef __IFlashXFLExportFacade__
#define __IFlashXFLExportFacade__

// ----- Interface files -----

#include "IPageRange.h"
#include "IPMUnknown.h"
#include "ISWFExportPreferences.h"
#include "IXFLExportPreferences.h"

// ----- Include files -----

#include "DynamicDocumentsTypes.h"

// ----- ID files -----

#include "DynamicDocumentsID.h"

// ===================================================================================
//	class IFlashXFL_ExportFacade 
// ===================================================================================
namespace Facade
{
	/** This facade provides services for obtaining and modifying the preference settings for  
		XFL export that is new to InDesign CS4. The preference is on the application workspace 
		boss and the main interfaces in the preference are:
			@see IXFLExportPreferences
			@see IPageRange
	*/
	class IFlashXFL_ExportFacade : public IPMUnknown 
	{
		public:
			// ----- Constants -----
			enum {kDefaultIID = IID_IFLASHXFLEXPORTFACADE};

			/**
			 Gets the size selection setting for the export file.
			 	 
			 @param ws [IN]: The workspace where we get SWF export preferences from.
			 @return SizeSelection: the size selection.
			 */
			virtual flash_export::SizeSelection GetSizeSelection(IWorkspace* ws) const = 0;

			/**
			 Gets the fit to selection setting for the exported file.
			 	 
			 @param ws [IN]: The workspace where we get SWF export preferences from.
			 @return FitToSelection: the fit to selection.
			 */
			virtual flash_export::FitToSelection GetFitToSelection(IWorkspace* ws) const = 0;

			/**
			 Gets the width and height for the file to be exported.
			 	 
			 @param ws [IN]: The workspace where we get SWF export preferences from.
			 @param settings [OUT]: the width and height for the export file.
			 */
			virtual void GetWidthHeight(IWorkspace* ws, uint32& width, uint32& height) const = 0;

			/**
			 Gets the scale amount for the file to be exported.
			 	 
			 @param ws [IN]: The workspace where we get SWF export preferences from.
			 @return PMReal: the scale amount for the xport file.
			 */
			virtual PMReal GetScale(IWorkspace* ws) const = 0;

			/**
			 Gets the page range information from the session preferences.
			 	 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @param pageRange [OUT]: contains string of page range.
			 @param pageRangeFormat [OUT]: contains enum value of page range format.
			 */
			virtual void GetPageRangeInfo(IWorkspace* ws, PMString &pageRange, IPageRange::RangeFormat &pageRangeFormat) const = 0;

			/**
			 Gets whether to export as reader's spreads.
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return kTrue if exporting as reader's spreads; otherwise kFalse.
			 */
			virtual bool ReadersSpreads(IWorkspace* ws) const = 0;

			/**
			 Gets whether to rasterize each page/spread
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return kTrue if pages/spreads are to be rasterized.
			 */
			virtual bool RasterizePages(IWorkspace* ws) const = 0;

			/**
			 Gets the dynamic media handling policy.
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return One of the DynamicMediaHandling (kIncludeAll, kAppearanceOnly).
			 */
			virtual flash_export::DynamicMediaHandling GetDynamicMediaHandling(IWorkspace* ws) const = 0;

			/**
			 Gets the transparency handling policy.
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return One of the TransparencyHandling (kIgnoreTransparency, kFlattenTransparency, kNativeTransparency).
			 */
			virtual flash_export::TransparencyHandling GetTransparencyHandling(IWorkspace* ws) const = 0;

			/**
			 Gets the text export policy for all text frame dictating how text is to be represented in the exported file.
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return One of the TextExportPolicy (kLive, kRasterize, kVectorize).
			 */
			virtual flash_export::TextExportPolicy GetTextExportPolicy(IWorkspace* ws) const = 0;

			/**
			 Gets whether to insert discretionary hyphenation points for TLF text. Only relevant when
			 Flash TLF Text is the text export policy.
			 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @return kTrue if if discretionary hyphenation points are included.
			 */
			virtual bool InsertHyphensForTLF(IWorkspace* ws) const = 0;

			/**
			 Gets the XFL export session workspace preferences.
			 	 
			 @param ws [IN]: The workspace where we get XFL export preferences from.
			 @param iPrefsData [OUT]: the IXFLExportPreferences interface contains XFL export preferences.
			 */
			virtual void GetWorkspacePreferences(IWorkspace* ws, IXFLExportPreferences* iPrefsData) const = 0;

			/**
			 Set the XFL export preferences for the session workspace.
			 	 
			 @param iPrefsData [IN]: The XFL general preference data where we use for setting export preferences.
			 @param iPageRangeData [IN]: The page preference data where we use for setting export preferences.
			 */
			virtual ErrorCode SetWorkspacePreferences(IXFLExportPreferences* iPrefsData, IPageRange* iPageRangeData) = 0;

	};
}
#endif // define

