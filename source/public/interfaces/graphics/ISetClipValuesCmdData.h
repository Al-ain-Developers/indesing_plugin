//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISetClipValuesCmdData.h $
//  
//  Owner: Dave Stephens
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
//  
//  Purpose:
//  Command data interface for the ISetClipValuesCmd.  This command is used to save off
//  the clipping path settings used to create a Clipping Path frame using edge detection
//  algorithms.
//  
//========================================================================================

#pragma once
#ifndef __ISetClipValuesCmdData__
#define __ISetClipValuesCmdData__

#include "IPMUnknown.h"
#include "IClipSettings.h"

/** 
	ISetClipValuesCmdData
	Description: Data interface for the kSetClipValuesCmdBoss command, which is used
	to store the current clipping path settings for a given image or the default clip
	settings for given document or the default clip settings for all new documents.
*/
class ISetClipValuesCmdData : public IPMUnknown
{
public:
	/**
		SetImageItem
		Sets the given UID as the target of the SetClipValuesCmd.  If the target
		is the document or the application, then do not call this method.
		@param db	- IN: the IDataBase of the document containing the image.
		@param id	- IN: the image.
	*/
	virtual void SetImageItem(IDataBase *db, UID id) = 0;

	/**
		SetDocument
		Sets the given UID as the target of the SetClipValuesCmd.  If the target
		is the application, then do not call this method.
		@param document	- IN: the UIDRef of the IDocument for which all newly placed
			images will have these clip settings by default.
	*/
	virtual void SetDocument(UIDRef& document) = 0;

	/**
		Set
		This method is used to set the clipping values which will be applied to the target.
		@param clipType	- IN: the kind of clipping to apply.  @See IClipSettings
		@param index	- IN: If the clipType is kClipAlpha or kClipEmbeddedPath, then index
			is the zero based index of the alpha channel or embedded path to use for the clipping.
			If kDefaultClipIndex is passed, then the default alpha or default embedded path are used.  If a default
			cannot be determined, then the first is used.
		@param Tolerance - IN: Tolerance is a measure, in points, of how closely the smoothed clipping path
			must approximate the original.  The higher the tolerance, the fewer the total number of points.
		@param Inset	- IN: Inset is a measure in points, of how far to inset the resulting clipping path.  Use
			a negative value to outset.
		@param Threshold	- IN: If the clipType is kClipAlpha or kClipEdgeDetection, then the threshold determines
			how dark a pixel must be before it can be included in the clipping.
		@param Invert	- IN: Should the resulting path be inverted?  That is, should it be treated as a hole in the
			image?
		@param UseHighRes	- IN: If the clipType is kClipAlpha or kClipEdgeDetection, should the clipping be calculated
			using the high res data or is the proxy image good enough?  Using high res data results in more accurate results
			but takes longer to compute.
		@param AllowHoles	- IN: Is it okay to have holes in the clipping?
		@param restrict	- IN: Should the clipping path be computed on the currently visible portion of the image?
	*/
	virtual void Set(IClipSettings::ClipType clipType, 
										int16 index, 
										PMReal Tolerance, 
										PMReal Inset, 
										uint8 Threshold, 
										bool8 Invert, 
										bool8 UseHighRes, 
										bool8 AllowHoles, 
										bool8 restrict) = 0;
				
	/**
		GetDataBase
		@return Returns the IDataBase that was set via SetImageItem or SetDocument
	*/
	virtual IDataBase* GetDataBase() const = 0;

	/**
		GetImageUID
		@return Returns the UID of the image that was set via SetImageItem
	*/
	virtual UID GetImageUID() const = 0;

	/**
		GetDocument
		@return Returns the UIDRef of the document that was set via SetDocument
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/**
		GetClipType
		@return Returns the ClipType that was set via Set
	*/
	virtual IClipSettings::ClipType GetClipType() const = 0;

	/**
		GetTolerance
		@return Returns the tolerance that was set via Set
	*/
	virtual PMReal GetTolerance() const = 0;

	/**
		GetInset
		@return Returns the inset that was set via Set
	*/
	virtual PMReal GetInset() const = 0;

	/**
		GetThreshold
		@return Returns the threshold that was set via Set
	*/
	virtual uint8 GetThreshold() const = 0;

	/**
		GetInvert
		@return Returns whether or not to invert the result.  Set via Set.
	*/
	virtual bool8 GetInvert() const = 0;

	/**
		GetUseHighRes
		@return Returns whether or not to use the High Res image instead of the proxy.  Set via Set.
	*/
	virtual bool8 GetUseHighRes() const = 0;

	/**
		GetAllowHoles
		@return Returns whether or not holes are allowed in the resulting path.  Set via Set.
	*/
	virtual bool8 GetAllowHoles() const = 0;
					
	/**
		GetRestrictToFrame
		@return Returns whether or not to restrict computations to the currently visible portion of the image.  Set via Set.
	*/
	virtual bool8 GetRestrictToFrame() const = 0;
	
	/**
		GetIndex
		@return Returns the index of the alpha channel or embedded path to use if the clipType is kClipAlpha or kClipEmbeddedPath.
	*/
	virtual int16 GetIndex() const = 0;	
};

#endif // __ISetClipValuesCmdData__