//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GraphicsData.h $
//  
//  Owner: jargast
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
#ifndef __GraphicsData__
#define __GraphicsData__

#include "PMMatrix.h"
#include "IDrawOptions.h"

class IViewPort;
class ITransform;
class IControlView;
class IGraphicsPort;
class IRasterPort;
class IGraphicsContext;
class IDrwEvtDispatcher;
class IDrawMgr;
class ILayoutController;
class IViewPortAttributes;
class GraphicsData;
class TextDrawInfo;

#pragma export on

/**
 A simple wrapper for a GraphicsData object
 
 Use this to manage the lifetime of a GraphicsData which will be constructed
 for you from an IGraphicsContext.
 
 Warning: This does not support copy semantics and will crash if copy 
 constructed or assigned!
 
 @see IGraphicsContext
 @see GraphicsData
 */
class PUBLIC_DECL GraphicsDataPtr INHERITFROM
{
public:
	/**
	 Wrap the IGraphicsContext in a GraphicsData object
	 
	 @param gc		IN The graphics context to be wrapped
	 */
public:
	GraphicsDataPtr (IGraphicsContext* gc);
public:
	
	/**
	 Destructor
	 */
	~GraphicsDataPtr();
	
	/**
	 Allows calling GraphicsData methods through a GraphicsDataPtr
	 
	 @return the wrapped GraphicsData
	 */
	GraphicsData* operator->() const;

	/**
	 Implicit conversion to a GraphicsData *
	 
	 @return the wrapped GraphicsData
	 */
	operator GraphicsData*();
	
private:
	GraphicsData*		fGraphicsData;
};

//
// The internal class
//

/**
 GraphicsData is a data container interface which is passed into drawing code
 for shapes.  GraphicsData contains a set of the most commonly used interfaces
 for drawing. 
 
 @see IGraphicsPort
 @see IRasterPort
 @see IDrwEvtDispatcher
 @see IDrawMgr
 @see IControlView
 @see IViewPort
 @see IViewPortAttributes
 @see ILayoutController
 @see IGraphicsContext
 */  
class PUBLIC_DECL GraphicsData INHERITFROM
{
public:
	friend class GraphicsDataPtr;
	
private:
	GraphicsData(); //not implemented
	GraphicsData(GraphicsData* gd); //not implemented
	GraphicsData(const GraphicsData& gd); //not implemented
	GraphicsData(IGraphicsContext* gc); //only implemented constructor--called from GraphicsDataPtr constructor
	
	~GraphicsData();

	GraphicsData& operator=(const GraphicsData& gd);
	
public:
	/** 
	 Gets the graphics port for this graphics data
	 
	 Note: The graphics port will never be nil
	 
	 @see IGraphicsPort
	 @return an IGraphicsPort instance
	 */
	IGraphicsPort*			GetGraphicsPort() const;
	
	/**
	 Gets the raster port for this graphics data
	 
	 Note: The raster port may be nil if not drawing to the screen.
	 
	 @see IRasterPort
	 @return an IRasterPort instance, or nil
	 */
	IRasterPort*			GetRasterPort() const;
	
	/**
	 Gets the draw event dispatcher for this graphics data
	 
	 Note: The draw event dispatcher will never be nil
	 
	 @see IDrwEvtDispatcher
	 @return an IDrwEvtDispatcher instance
	 */
	IDrwEvtDispatcher*		GetDrawEventDispatcher() const;
	
	/**
	 Gets the draw manager for this graphics data
	 
	 Note: The draw manager will never be nil
	 
	 @see IDrawMgr
	 @return an IDrawMgr instance
	 */
	IDrawMgr*				GetDrawManager() const;
	
	/**
	 Gets the control view for this graphics data
	 
	 Note: The control view may be nil (nil indicates drawing to a printer or other 
	 non-screen device)
	 
	 @see IControlView
	 @return an IControlView instance, or nil
	 */
	IControlView*			GetView() const;
	
	/**
	 Gets the view port for this graphics data
	 
	 Note: The viewport will never be nil
	 
	 @see IViewPort
	 @return an IViewPort instance
	 */
	IViewPort*				GetViewPort() const;
	
	/**
	 Gets the view port attributes for this graphics data
	 
	 Note: Viewport attributes will never be nil
	 
	 @see IViewPortAttributes
	 @return an IViewPortAttributes instance
	 */
	IViewPortAttributes*	GetViewPortAttributes() const;
	
	/**
	 Gets the layout controller for this graphics data
	 
	 Note: The layout controller will not be nil during calls to inval, but may
	 be nil otherwise
	 
	 @see ILayoutController
	 @return an ILayoutController instance
	 */
	ILayoutController*		GetLayoutController() const;
	
	/**
	 Gets the transform matrix for converting from pasteboard to device coordinates
	 
	 @see PMMatrix
	 @return the CTM
	 */
	const PMMatrix&			GetContentToViewMatrix() const;
	
	/**
	 Gets the inverse transform matrix for converting from device to pasteboard coordinates
	 
	 @see PMMatrix
	 @return the inverse CTM
	 */
	const PMMatrix&			GetViewToContentMatrix() const;

	/**
	 Gets the graphics context for any that need it. 
	 
	 @see IGraphicsContext
	 @return an IGraphicsContext instance
	 */
	IGraphicsContext*		GetGraphicsContext() const;
	 
	/**
	 Gets the active draw options
	 If drawablePageItemInterface is non-nil AND we are not printing (see 
	 IViewPortAttributes::GetViewPortIsPrintingPort()) AND "Ignore Local Overrides"
	 is not set in the workspace's IDrawOptions settings, then drawablePageItemInterface
	 will be checked for local overrides.  If no local overrides exist or the argument is nil,
	 then the draw options will be based upon the ViewPortAttribute settings, the workspace's 
	 IDrawOptions settings and the view's IDrawOptionsSetID.
	 
	 @see DrawOptionsSet
	 @return the draw options to use
	 */
	DrawOptionsSet			GetDrawOptions(const IPMUnknown *drawablePageItemInterface = nil) const;

	/**
	 Gets the text draw info for this graphics data
	 
	 @see TextDrawInfo
	 @return a TextDrawInfo
	 */	 
	TextDrawInfo*			GetTextDrawInfo() const;
	
private:
	IGraphicsContext*		fContext;
	IGraphicsPort*			fGPort;
	IRasterPort*			fRPort;
	IDrwEvtDispatcher*		fDEDispatcher;
	IDrawMgr*				fDrawMgr;
	IControlView*			fCView;
	ILayoutController*		fController;
	IViewPort*				fViewPort;
	IViewPortAttributes*	fVPAttr;
	PMMatrix				fTransform;
	PMMatrix				fInvTransform;
	DrawOptionsSet			fDrawOptionsSet;
	bool8					fIgnoreDrawOptionOverrides;
	TextDrawInfo*			fTextDrawInfo;
};

#pragma export off

//
	
inline GraphicsData* GraphicsDataPtr::operator->() const
{
	return fGraphicsData;
}

inline GraphicsDataPtr::operator GraphicsData*()
{
	return fGraphicsData;
}

//

// The graphics port will never be nil.  
inline IGraphicsPort*		GraphicsData::GetGraphicsPort() const { return fGPort; }

// The rasterport may be nil if not drawing to the screen.
inline IRasterPort*			GraphicsData::GetRasterPort() const { return fRPort; }

// The draw event dispatcher will never be nil
inline IDrwEvtDispatcher*	GraphicsData::GetDrawEventDispatcher() const { return fDEDispatcher; }

// The draw manager will never be nil
inline IDrawMgr*			GraphicsData::GetDrawManager() const { return fDrawMgr; }

// The control view may be nil (nil indicates drawing to a printer or other 
// non-screen device)
inline IControlView*		GraphicsData::GetView() const { return fCView; }

// The layout controller will not be nil during calls to inval, but may
// be nil otherwise
inline ILayoutController*	GraphicsData::GetLayoutController() const { return fController; }

// The transform represents the matrix from pasteboard to device.  
inline const PMMatrix&		GraphicsData::GetContentToViewMatrix() const { return fTransform; }
inline const PMMatrix&		GraphicsData::GetViewToContentMatrix() const { return fInvTransform; }

// Code to get the graphics context for any that need it. 
inline IGraphicsContext*	GraphicsData::GetGraphicsContext() const { return fContext; }
 
inline IViewPort*			GraphicsData::GetViewPort() const { return fViewPort; }

inline IViewPortAttributes*	GraphicsData::GetViewPortAttributes() const { return fVPAttr; }

inline TextDrawInfo*		GraphicsData::GetTextDrawInfo() const { return fTextDrawInfo; } 

#endif
