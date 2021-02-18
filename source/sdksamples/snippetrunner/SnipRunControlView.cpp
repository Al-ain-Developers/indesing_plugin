//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunControlView.cpp $
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

#include "CIDErasablePanelView.h"

// Plug-in includes
#include "SnipRunID.h"
#include "SnipRunLog.h"


/** Overrides the ConstrainDimensions to control the maximum and minimum width 
	and height of panel when it is resized.

	@ingroup snippetrunner
	
*/
class  SnipRunControlView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;

public:
		/** 
			Constructor.
		*/
		SnipRunControlView(IPMUnknown* boss) : inherited(boss) { ; }

		/** 
			Destructor.
		*/
		virtual ~SnipRunControlView() { ; }

		/** Allows the panel size to be constrained.  
			@param dimensions OUT specifies the maximum and minimum width and height of the panel
				when it is resized.
		*/
		virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;

		/**	Clear the SnippetRunner framework log when resizing. 
			The multi line widget log gives some odd behaviour if we don't. 
			Means you lose the log contents when you resize.
			@param newDimensions
			@param invalidate
		*/
		virtual  void Resize(const PMPoint& newDimensions, bool16 invalidate);
};

// define the max/min width and height for the panel
const int kMinimumPanelWidth	=	207;
const int kMaximumPanelWidth	=	500;
const int kMinimumPanelHeight	=	290;
const int kMaximumPanelHeight	=	600;

#pragma mark SnipRunControlView implementation

/* Make the implementation available to the application.
*/
CREATE_PERSIST_PMINTERFACE(SnipRunControlView, kSnipRunControlViewImpl)


/* Allows the panel size to be constrained.  
*/
PMPoint SnipRunControlView::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinimumPanelWidth, kMinimumPanelHeight, kMaximumPanelWidth, kMaximumPanelHeight) );

	return constrainedDim;
}

/*
*/
void SnipRunControlView::Resize(const PMPoint& newDimensions, bool16 invalidate)
{
	// Clear the log during resize to workaround the fact that
	// if we don't the static multiline widget gets messed up.
	// SnipRunLog will arrange that the contents of the log get
	// restored once resize is complete.
	if (SnipRunLog::PeekAtSnipRunLog() != nil) 
	{
		SnipRunLog::Instance()->Resize();
	}

	inherited::Resize(newDimensions, invalidate);
}

// End SnipRunControlView.cpp
