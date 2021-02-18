//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PNGArt.h $
//  
//  Owner: kphilbri
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
#ifndef __PNGART_H__
#define __PNGART_H__

#include "BravoForwardDecl.h"
#include "IDFile.h"

class IGraphicsPort;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class  PUBLIC_DECL PNGArt 
{
public :
	PNGArt ();
	
	/** If a PNG resource has been loaded it deletes it.
	*/
	~PNGArt ();

	/** Deletes any currently loaded resource and loads a PNG image from a plugin's resource. This is the preferred approach.

		@param  PluginID:  PluginId to load the resource from
		@param  RsrcID:    Resource ID of the PNG
		@param  bool:      Rollover resource?
						   If false, then a resource type of "PNGA" will be loaded, else a resource type of "PNGR" will be loaded.
		@param  bool:      Dark UI resource?
						   If false, then a resource type of "PNGA" (or "PNGR" if isRollover is true) will be loaded, else a
						   resource type of "PNGD" (or "PNGK" if isRollover is true) will be loaded. Default is false.
		@return true if file / resource was loaded
	*/
	bool SetRsrc	(const PluginID & pid, const RsrcID & rid, const bool isRollOver, const bool isDark = false);
	bool SetRsrc	(const RsrcSpec& spec);	// all decisions (light/dark/rollover/hiRes/etc.) resolved by caller
	
	/** Deletes any currently loaded resource and loads a PNG image file resource in from the supplied file.
		@param  path to a PNG file
		@return true if file / resource was loaded
	*/
	bool SetFile	(const IDFile& idFile);

	/** Draw's the PNG to the supplied graphics port

		@param  IGraphicsPort:  IGraphicsPort to draw to
		@param  PMMatrix:		Transformation matrix to apply to the PNG, if no translation is desired use the idenity matrix or just a plain PMMatrix.
		@param  agmflags:       Any desired AGM flags, use 0 if none are desired.						   		
	*/
	void Draw		(IGraphicsPort * gPort, const PMMatrix &imMatrix, int32 agmflags);
	
	/** Draw's the PNG with a 50% transparensy see regular draw methode for more info.					   		
	*/
	void DrawDisabled (IGraphicsPort * gPort, const PMMatrix &imMatrix, int32 agmflags);
	
	/** Does the PNG have a a alpha?
		@return true if PNG contains pixels not totally opaque
	*/
	bool HasAlpha ();

	/** Did the PNG sucessfully load?
		@return true if loaded
	*/
	bool IsLoaded ();
	
	/** Deletes the PNG resource, this is done automatically when this class is destroyed		
	*/
	void Delete ();

	/** @return The height of the loaded PNG resource
	*/
	int GetHeight () const;
	
	/** @return The width of the loaded PNG resource
	*/
	int GetWidth  () const;

	/** Different instantiations of PNGArt may share a cached PNG reader.
		ReleaseCaches can be called to free these caches.
	*/
	static void ReleasePNGSharedCaches (void);

	/** @return A pointer to the AGMImageRecord for the loaded PNG resource
	*/
	AGMImageRecord* GetBitmap  () const;

private :	

	AGMImageRecord  *fBitmap;
	
	bool8 ReadPNGImage(IPMStream* iPMStream, AGMImageRecord * bitmap);
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif
