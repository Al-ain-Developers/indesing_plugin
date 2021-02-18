//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxMatteFactory.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes
#include "IGraphicStyleDescriptor.h"
#include "IGraphicAttrRealNumber.h"
#include "IShape.h"
#include "ISpread.h"
#include "IGeometry.h"
#include "IDataBase.h"
#include "IPMStream.h"
#include "IGraphicsContext.h"
#include "GraphicsData.h"
#include "IViewPortAttributes.h"
#include "IDrawOptions.h"
#include "ICommand.h"
#include "ISetDrawOptionsCmdData.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "IImageCacheMgr.h"
#include "IImageCache.h"
#include "IWorkspace.h"
#include "ITOPFrameData.h"
#include "IGraphicFrameData.h"
#include "IPageItemTypeUtils.h"
#include "IRenderingObject.h"
#include "IColorSystemUtils.h"
#include "IColorData.h"
#include "IGraphicAttributeUtils.h"
#include "UIDList.h"
#include "PreferenceUtils.h"
#include "GraphicsExternal.h"	// _t_AGM...
#include "ImageID.h"			// IID_IIMAGECACHEMGR
#include "SystemUtils.h"		// TickCount
#include "SnapshotUtilsEx.h"
#include "Utils.h"
#include "IViewPortAttributes.h"
#include "IDrawOptions.h"

// Other API includes
#include "K2SmartPtr.h"
#include "XPID.h"
#include "TransformUtils.h"

// Project includes
#include "TranFxMatteFactory.h"
#include "TranFxID.h"
#include "TranFxUtils.h"
#include "TranFxConvolutionFilter.h"

const static  int32 TranFxHelper_kMaxChildrenToCheckForSafety = 16;

// Key used to uniquely identify the effect images that we 
// cache using IImageCacheMgr.
const static uint32 kTranFxEffectSelector = kTranFxPrefixNumber;

/*
*/
TranFxMatteFactory::TranFxMatteFactory() : fMaskImage(nil)
{
}

/*
*/
TranFxMatteFactory::~TranFxMatteFactory()	
{
	this->SetMaskImage(nil);
}

/*
*/
IDThreading::ThreadLocal<int32> tl_PaintedBBoxDepth(0);

bool16 TranFxMatteFactory::GetPaintedBBoxWithoutMatte(IShape* iShape, PMRect& bounds) const
{
	bool16 isPaintedBBox = kFalse;
	// This avoids infinite recursion (TranFxAdornment::GetPaintedBBox will
	// call back in here) ...
	if (tl_PaintedBBoxDepth.Get() == 0)
	{
		tl_PaintedBBoxDepth.Set(tl_PaintedBBoxDepth.Get() + 1);
		isPaintedBBox = kTrue; 
		bounds = iShape->GetPaintedBBox(PMMatrix(), Transform::SpreadCoordinates());
		tl_PaintedBBoxDepth.Set(tl_PaintedBBoxDepth.Get() - 1);
	}
	return isPaintedBBox;
}

/*
*/
PMRect TranFxMatteFactory::GetBoundingBox(IShape* iShape) const
{
	PMRect result;
	if (this->GetPaintedBBoxWithoutMatte(iShape, result) == kFalse)
	{
		// If for any reason the painted bounds are not available
		// use the stroke bounds instead.
		InterfacePtr<IGeometry> geometry(iShape, UseDefaultIID());
		ASSERT(geometry);
		if (geometry)
		{
			PMMatrix inner2pb = ::InnerToSpreadMatrix(iShape);
			result = geometry->GetStrokeBoundingBox(inner2pb);
		}
	}
	return result;
}

/*
*/
const AGMImageAccessor*  TranFxMatteFactory::MakeMatte(IShape* iShape, const PMReal& resolution, const DrawOptionsSet& drawOptionsSet, const bool16 enableCaching) 
{
	TRACEFLOW(kTranFxPluginName, "TranFxMatteFactory::MakeMask-->In\n");
	AGMImageAccessor* result = nil;
	do
	{
		// Get a reference to the object the effect is being applied to.
		UIDRef currentShapeRef = ::GetUIDRef(iShape);

		// Calculate the effective checksum used for verifying the display conditions used
		// for creating a cache entry by combining the display settings into a single number.
		uint32 cacheChecksum = (uint32)drawOptionsSet.xp + (256 * (uint32)drawOptionsSet.vector) + (65536 * drawOptionsSet.raster);

		// Check if we have a ready made cached matte image.
		if (enableCaching)
		{
			result = const_cast<AGMImageAccessor*>(this->FindInCache(currentShapeRef, resolution, cacheChecksum));
			if (result != nil)
			{
				// Cache hit. We use the cached effect as the user changes the view zoom
				// percentage or when windows are maximised, minimised or resized. If you
				// want to redraw your effect to get the best resolution for the view you'll
				// need to invalidate the cache when these kind of events occur.
				break;
			}
		}

		// Use SnapshotUtilsEx to create a greyscale image of the page item.

		// Examine the display draw options to determine if
		// we need to draw with full res graphics.
		bool8 fullResolutionGraphics = kFalse;
		if (drawOptionsSet.raster == IDrawOptions::kRasterHighRes ||
			drawOptionsSet.vector == IDrawOptions::kDisplayList)
		{
			fullResolutionGraphics = kTrue;
		}

		// Take the transparency quality from the draw options.
		const SnapshotUtils::Transparencies transparencyQuality = (SnapshotUtils::Transparencies)(drawOptionsSet.xp);

		// Take the greek text below setting from the draw options.
		const PMReal greekBelowPtSize = drawOptionsSet.greekBelow;

		// Turn anti aliasing on or off based on the draw options.
		// Note: When anti-aliasing is turned on, the alpha channel
		// for a rectangle with a 1 point black stroke and no
		// fill will *not* be solidly opaque for the stroke. You can
		// work around this by turning anti-aliasing off.
		const bool8 antiAliasing = drawOptionsSet.antiAlias;

		// Draw the page item as a grey level image into an offscreen
		// buffer using SnapshotUtilsEx.
		// Note that we use the SnapshotUtilsEx constructor that lets
		// us control when drawing occurs. We need to
		// set the kXPSuppressEffectsVPAttr flag so that when we draw
		// into the offscreen scnapshot this effect does not draw 
		// This flag prevents recursion and suppresses
		// effects like drop shadows. We don't want to
		// apply our effect to other effects.
		uint32 startTime = SystemUtils::TickCount();
		PBPMRect matteBounds = this->GetBoundingBox(iShape);
		SnapshotUtilsEx greyscaleSnapshot(matteBounds, PMMatrix(),
										currentShapeRef.GetDataBase(),
										1.0, // scale-x
										1.0, // scale-y
										resolution,
										resolution,
										0.0,	// bleed
										SnapshotUtilsEx::kCsGray,
										kTrue);// //addAlpha
		VPAttrMap vpAttrs;
		vpAttrs[kXPSuppressEffectsVPAttr] = kTrue;
		greyscaleSnapshot.Draw(currentShapeRef.GetUID(), 
							IShape::kNoFlags, 
							fullResolutionGraphics, 
							greekBelowPtSize,
							antiAliasing,
							transparencyQuality,
							nil,
							&vpAttrs
							);

		// Process the greyscale input image to create the effect's output image.

		// Get the flags that control the matte image that is generated.
		TranFxUtils tranFxUtils;
		bool16 useBlackAsOpaque = kFalse;
		tranFxUtils.HasUseBlackAsOpaque(UIDList(iShape), useBlackAsOpaque);
		// The useBlackAsOpaque flag is set to kTrue when the user wants 
		// dark pixels in the grey level image to be more opaque in the
		// effect and to kFalse when dark pixels should be more transparent.
		// See the documentation for kTranFxUseBlackAsOpaqueAttrBoss.
		//
		// This flag controls whether or not we invert the grey level
		// values when creating the matte. We do this because the matte
		// is used as an alpha paint server (255 means opaque, 0 means transparent).
		// This is the inverse of a grey level image where 0 means black
		// and 255 means white. So if the user wants dark pixels to be more
		// opaque we have to invert the grey level values from the Snapshot
		// of the page item.
		bool16 invertGrey = useBlackAsOpaque;
		bool16 useAlpha = kFalse;
		tranFxUtils.HasUseAlpha(UIDList(iShape), useAlpha);
		bool16 useBlur = kFalse;
		tranFxUtils.HasUseBlur(UIDList(iShape), useBlur);

		// Create the matte output image.
		AGMImageAccessor* input = greyscaleSnapshot.CreateAGMImageAccessor();
		TranFxConvolutionFilter imageOp(input, invertGrey, useAlpha);
		if (useBlur)
		{
			imageOp.ApplyBlur();
		}
		AGMImageRecord mask;
		AGMImageAccessor* output = imageOp.CreateOutputAccessor(mask);
		ASSERT(output);
		if (!output)
		{
			break;
		}

		// Cache the output image if possible.
		if (enableCaching && this->InkingIsSafeToCache(iShape))
		{
			// Since we don't store an actual profile with the cache, we instead
			// use the profileChecksum field of an image cache to store the view
			// setting that was used to draw create the mask.  If the view setting
			// of the cache is not the same as the current setting, then
			// regenerate the cache.
			//
			// For this purpose we use a combination of the transparency, vector
			// and raster display setting (see cacheChecksum above).
			this->AddToCache(output, startTime, currentShapeRef, resolution, cacheChecksum);
			result = const_cast<AGMImageAccessor*>(this->FindInCache(currentShapeRef, resolution, cacheChecksum));
			if (result != nil)
			{
				break;
			}
		}

		// We couldn't cache the image so keep hold of it for the lifetime
		// of this TranFxMatteFactory object. When the object goes out of scope
		// the image will be deleted.
		this->SetMaskImage(output);
		result = output;

	} while (false);

	TRACEFLOW(kTranFxPluginName, "TranFxMatteFactory::MakeMask-->Out\n");
	return result;
}

/*
*/
void TranFxMatteFactory::SetMaskImage(const AGMImageAccessor* matte)
{
	if (fMaskImage != nil)
	{
		delete fMaskImage;
	}
	this->fMaskImage = const_cast<AGMImageAccessor*>(matte);
}

/*
*/
void TranFxMatteFactory::AddToCache(const AGMImageAccessor* mattRec, uint32 startTime, const UIDRef& uidRef, const PMReal& resolution, uint32 checksum) 
{
	do
	{
		InterfacePtr<IWorkspace>    workspace (GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if (!workspace)
		{
			break;
		}
		InterfacePtr<IImageCacheMgr> imageCacheMgr(workspace, IID_IIMAGECACHEMGR);
		ASSERT(imageCacheMgr);
		if (!imageCacheMgr)
		{
			break;
		}
		InterfacePtr<IImageCache> imageCache((IImageCache*) ::CreateObject(kImageCacheBoss, IID_IIMAGECACHE));
		ASSERT(imageCache);
		if (!imageCache)
		{
			break;
		}
		imageCache->Init(const_cast<AGMImageAccessor*>(mattRec), ::ToUInt32(resolution), SystemUtils::TickCount() - startTime, checksum);
		imageCacheMgr->Add(uidRef, 
						   imageCache, 
						   kTrue,					   // purgeFirst.
						   kTranFxEffectSelector);	   // Use the plug-in prefix to specify the kind of cached image.
	} while (false);
}

/*
*/
const AGMImageAccessor* TranFxMatteFactory::FindInCache(const UIDRef& currentShapeRef, const PMReal& resolution, uint32 checksum)
{
	AGMImageAccessor* result = nil;
	do
	{
		InterfacePtr<IWorkspace> workspace (GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if (!workspace)
		{
			break;
		}
		InterfacePtr<IImageCacheMgr> imageCacheMgr(workspace, IID_IIMAGECACHEMGR);
		ASSERT(imageCacheMgr);
		if (!imageCacheMgr)
		{
			break;
		}
		InterfacePtr<IImageCache> imageCache(imageCacheMgr->QueryClosestResolution(currentShapeRef, 
																				   resolution, 
																				   kTranFxEffectSelector));
		if (!imageCache)
		{
			break;
		}
		PMReal cacheResolution = imageCache->GetResolution();
		uint32 cacheChecksum = imageCache->GetProfileChecksum();
		if (cacheChecksum == checksum && cacheResolution == resolution)
		{
			result = imageCache->GetImageAccessor();
		}
	} while (false);
	return result;
}

/*
*/
void TranFxMatteFactory::PurgeWholeCache(const UIDRef& documentUIDRef)
{
	do
	{
		InterfacePtr<IWorkspace>    workspace (GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if (!workspace)
		{
			break;
		}
		InterfacePtr<IImageCacheMgr> imageCacheMgr(workspace, IID_IIMAGECACHEMGR);
		ASSERT(imageCacheMgr);
		if (!imageCacheMgr)
		{
			break;
		}
		imageCacheMgr->Purge(documentUIDRef.GetDataBase(),  kTranFxEffectSelector); 
	} while (false);
}

/*
*/
void TranFxMatteFactory::PurgeImageCache(const UIDList& itemList)
{
	do
	{
		InterfacePtr<IWorkspace>    ws(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(ws);
		if (!ws)
		{
			break;
		}
		InterfacePtr<IImageCacheMgr> imageCacheMgr(ws, IID_IIMAGECACHEMGR);
		ASSERT(imageCacheMgr);
		if (!imageCacheMgr)
		{
			break;
		}
		TranFxUtils tranFxUtils;
		for (int32 i = 0; i < itemList.Length(); i++)
		{
			// Check the item and all its children for our effect.
			UIDRef itemRef = itemList.GetRef(i);
			InterfacePtr<IShape> iShape(itemRef, UseDefaultIID());
			if (!iShape)
			{
				continue;
			}
			if (tranFxUtils.HasAdornment(UIDList(iShape)) == TranFxUtils::eCommonValue)
			{
				// The adornment is present so the effect is active.
				imageCacheMgr->Purge(itemRef, kTranFxEffectSelector);
			}
		}
	} while (false);
}

/*
*/
bool16 TranFxMatteFactory::InkingIsSafeToCache(IShape* iShape)
{
	int32 childCount = 0;
	InterfacePtr<IHierarchy> iHier(iShape, UseDefaultIID());
	ASSERT(iHier);
	if (!iHier)
	{
		return kFalse;
	}
	return this->InkingIsSafeToCacheRecursive(iHier, childCount);
}

/*
*/
bool16 TranFxMatteFactory::InkingIsSafeToCacheRecursive(IHierarchy* iPageItem, int32& childCount)
{
	childCount++;
	if (childCount > TranFxHelper_kMaxChildrenToCheckForSafety)
	{
		// We don't want to spend an inordinately long time checking 
		// children; once we get to this upper limit, just assume
		// we can't cache.
		return kFalse;
	}

	if (!iPageItem)
	{
		return kFalse;
	}
	Utils<IPageItemTypeUtils> pageItemTypeUtils;
	ASSERT(pageItemTypeUtils);
	if (!pageItemTypeUtils)
	{
		return kFalse;  
	}

	// Don't cache text frames; they can draw outside of their bounds in 
	// ways that we can't detect.
	if (pageItemTypeUtils->IsTextFrame(iPageItem))
	{
		return kFalse;
	}
	// Ditto for any text-on-path.
	if (pageItemTypeUtils->IsTextOnAPath(iPageItem))
	{
		return kFalse;
	}
	// If it's a graphic frame with a solid fill then we're fine -- all children
	// are clipped to this frame so they cannot affect the shadow.
	if (pageItemTypeUtils->IsGraphicFrame(iPageItem))
	{
		InterfacePtr<IGraphicStyleDescriptor> iFrameGSDesc(iPageItem, UseDefaultIID());
		if (iFrameGSDesc && !this->ObjectHasNoColor(iFrameGSDesc))
			return kTrue;
	}

	// Otherwise it's OK as long as none of its children are themselves unsafe.
	for (int32 n = iPageItem->GetChildCount(); n--;)
	{
		InterfacePtr<IHierarchy> iChild(iPageItem->QueryChild(n));
		ASSERT(iChild);
		if (!this->InkingIsSafeToCacheRecursive(iChild, childCount))
		{
			return kFalse;
		}
	}

	return kTrue;
}

/*
*/
bool16 TranFxMatteFactory::ObjectHasNoColor(IGraphicStyleDescriptor *gsDesc)
{
	InterfacePtr<IRenderingObject> renderObj(Utils<IGraphicAttributeUtils>()->QueryFillRenderingObject(gsDesc));
	if (renderObj)
	{
		InterfacePtr<IColorData> colorData(static_cast<IColorData *>(
																	Utils<IColorSystemUtils>()->QueryBaseRenderObject(renderObj, IColorData::kDefaultIID)));
		return(colorData == nil);
	}

	return kTrue;
}

// End, TranFxMatteFactory.cpp.
