//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CursorSpec.h $
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
#ifndef __CursorSpec__
#define __CursorSpec__

#include "PMTypes.h"
#include "PMString.h"
#include "GetPlugIn.h"
#include "IPlugIn.h"
#include "CursorDefs.h"

/**  Callback for custom cursors. Creates RGB bitmap(with pad bytes at end,if needed) of the desired image to turn into a cursor.
	@param bitmapBuffer IN buffer to hold the bitmap data. Allocated by caller to be at least (max cursor thumbnail size) * (max cursor thumbnail size) * 4 big.
	@param width OUT will be populated with bitmap width. Initialized to max cursor thumbnail size.
	@param height OUT will be populated with bitmap height. Initialized to max cursor thumbnail size.
	@param hasAlpha OUT will be populated with whether or not the returned bitmap includes alpha. If true, bitmap is assumed to be 32 bit ARGB, else 24 bit RGB
	@param hiRes IN if true, buffer was created at 2x normal resolution, and width/height are doubled from their usual value. Clients can use this flag to determine the correct base cursor resource ID for compositing with an image, or to create a correctly scaled AGM drawing world on the bitmap with ICursorUtils::QueryGraphicsPortForBitmap
	  */
typedef void (*CreateCursorBitmapProc)(uchar* bitmapBuffer,uint32* width, uint32* height, bool16 *hasAlpha, bool16 hiRes);

/** Data type used to refer to cursor resources. Contains both a PluginID and a CursorID
		to avoid potential conflicts between plugins. Can also contain a reference to a separate resource file.
*/
class CursorSpec
{
	public:
		typedef object_type data_type;
		
		/** Empty constructor */
		CursorSpec() : fID(kCrsrNone), fPlugInID(kInvalidPlugin),fCustomCursorBitmapCallback(nil), fDynamicBitmap(kFalse)
		{
		}
		
		/** constructor for cursors with image data */
		CursorSpec(CreateCursorBitmapProc customDrawCallback,CursorID id) : 
			fCustomCursorBitmapCallback(customDrawCallback), 
			fDynamicBitmap(kFalse),
			fID(id), 
			fPlugInID(kInvalidPlugin)
		{
		}

		/** Constructor: CursorID only */
		CursorSpec(CursorID id) : fID(id), fPlugInID(kInvalidPlugin),fCustomCursorBitmapCallback(nil), fDynamicBitmap(kFalse)
		{
		}
		
		/** Constructor: PluginID and CursorID */
		CursorSpec(const PluginID& plugInId, CursorID id) :
			fPlugInID(plugInId), fID(id),fCustomCursorBitmapCallback(nil), fDynamicBitmap(kFalse)
		{
		}
		
		/** Constructor: IDFile and CursorID */
		CursorSpec(const IDFile& resFile, CursorID id) :
			fResourceFile(resFile), fID(id), fPlugInID(kInvalidPlugin),fCustomCursorBitmapCallback(nil), fDynamicBitmap(kFalse)
		{
		}
		
		/** Copy Constructor */
		CursorSpec(const CursorSpec& spec) :
			fPlugInID(spec.fPlugInID), fID(spec.fID), fResourceFile(spec.fResourceFile),
			fCustomCursorBitmapCallback(spec.fCustomCursorBitmapCallback), fDynamicBitmap(spec.fDynamicBitmap)
		{
		}
		
		/** Constructor: PluginID, IDFile and CursorID (not sure why is this needed)
			@param customDrawCallback [IN]: Pointer to a callback routine for the generation of a custom cursor.
			@param bDynamicBitmap [IN]: If kTrue, then the customDrawCallback might return a different cursor every time it is called.
				For example, if the cursor shows the X, Y position of the mouse, then kTrue should be passed to ensure that the callback
				gets a chance to be called.
		*/
		CursorSpec(const PluginID& plugInId, const IDFile& resFile, CursorID id,CreateCursorBitmapProc customDrawCallback, bool32 bDynamicBitmap = kFalse) :
			fPlugInID(plugInId), fID(id), fResourceFile(resFile),fCustomCursorBitmapCallback(customDrawCallback),fDynamicBitmap(bDynamicBitmap)
		{
		}

		/** assignment operator */
		CursorSpec& operator=(const CursorSpec& spec)
		{
			if (this != &spec)
			{
				fID = spec.fID;
				fPlugInID = spec.fPlugInID;
				fResourceFile = spec.fResourceFile;
				fCustomCursorBitmapCallback = spec.fCustomCursorBitmapCallback;
				fDynamicBitmap = spec.fDynamicBitmap;
			}
			return *this;
		}
		
		/** equality operator */
		bool operator==(const CursorSpec& spec) const
		{
			if (this == &spec)
				return kTrue;
			else if ((fID == spec.fID) && (fPlugInID == spec.fPlugInID) && (fCustomCursorBitmapCallback == spec.fCustomCursorBitmapCallback)
				&& (fDynamicBitmap == spec.fDynamicBitmap))
				return kTrue;
			else 
				return kFalse;
		}
		
		/** Get the PluginID */
		PluginID 		GetPlugInID() const { return fPlugInID; }
		/** Get the IDFile */
		IDFile 		GetResourceFile() const { return fResourceFile; }
		/** Get the CursorID */
		CursorID 		GetID() const { return fID; }
		/** Get the custom draw proc, if any */
		CreateCursorBitmapProc		GetCustomBitmapCreationProc() const { return fCustomCursorBitmapCallback; }
		/** Get whether or not the custom draw proc's results are dynamic. */
		bool32		GetDynamicCallback() const { return fDynamicBitmap; }
		
	private:
		CursorID					fID;
		PluginID					fPlugInID;
		IDFile						fResourceFile;
		CreateCursorBitmapProc		fCustomCursorBitmapCallback;
		bool32						fDynamicBitmap;
};

/** @name PluginCursorSpec(cursorID)
		Use this macro to create a CursorSpec local to the plugin containing the code of the callsite.
		This obviates the need to bury PluginID constants in code, but be careful when moving code between plugins.
*/
#define PluginCursorSpec(cursorID) CursorSpec(GetPlugIn()->GetPluginID(), cursorID)

#endif
