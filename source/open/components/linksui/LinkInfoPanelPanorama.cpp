//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoPanelPanorama.cpp $
//  
//  Owner: lance bushore
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

// ----- Interface Includes -----
#include "IControlView.h"
#include "IIntData.h"

// ----- Implementation Includes -----
#include "CPanorama.h"
#include "LinksUIID.h"

class LinkInfoPanelPanorama : public CPanorama
{
public:
	LinkInfoPanelPanorama(IPMUnknown *boss);	
	virtual ~LinkInfoPanelPanorama();

// ----- Panorama attribtues
public:
	virtual PMRect		GetBounds() const;
//	virtual PMRect		GetCentralBounds() const;
	virtual PMReal		GetCentralBorderWhiteSpace() const;
	virtual void 		GetPanoramaDelta(PMPoint& delta) const;
	virtual PBPMPoint	ScrollBy(const PBPMPoint& by, bool16 bForceRedraw = kTrue, SysRgn InvalRgnCopy = nil);

	virtual PBPMPoint	ConstrainTo(const PBPMPoint& value) const;
	virtual PBPMPoint	ConstrainBy(const PBPMPoint& delta) const;
// ----- Persistence
public:
	virtual void		SavePerspective() const;
	virtual void		RestorePerspective();
};

CREATE_PMINTERFACE(LinkInfoPanelPanorama, kLinkInfoPanelPanoramaImpl)

LinkInfoPanelPanorama::LinkInfoPanelPanorama(IPMUnknown *boss) :
	CPanorama(boss, kTrue /*push panorama changes into drover*/)
{
}

LinkInfoPanelPanorama::~LinkInfoPanelPanorama()
{
}

PMRect LinkInfoPanelPanorama::GetBounds() const
{
	InterfacePtr<const IControlView> myView(this, IID_ICONTROLVIEW);
	PMRect frame = myView->GetFrame();	

	InterfacePtr<const IIntData> totalInfoHeightData(this,IID_ITOTALINFOAREAHEIGHT);
	int32 measuredHeight = totalInfoHeightData->GetInt();
	frame.Bottom() = frame.Top() + measuredHeight;
	frame.Top() = 0;
//	TRACEFLOW("Links:LinksUI","LinkInfoPanelPanorama::GetBounds(): saved panel height was %d. returning %d,%d,%d,%d\n",measuredHeight,::ToInt32(frame.Left()),::ToInt32(frame.Top()),::ToInt32(frame.Right()),::ToInt32(frame.Bottom()));
	return frame;
}
													   

PBPMPoint LinkInfoPanelPanorama::ScrollBy(const PBPMPoint& to, bool16 forceRedraw, SysRgn InvalRgnCopy)
{
	PBPMPoint newPoint = CPanorama::ScrollBy(to, forceRedraw, InvalRgnCopy);
//	TRACEFLOW("Links:LinksUI","LinkInfoPanelPanorama::ScrollBy %d,%d. Y offset is now %d\n",::ToInt32(to.X()),::ToInt32(to.Y()),::ToInt32(GetScrollOffset().Y()));
	return newPoint;
}


PMReal LinkInfoPanelPanorama::GetCentralBorderWhiteSpace() const
{
	return 0.0;			// Seven point whitespace
}
void LinkInfoPanelPanorama::SavePerspective() const
{
}
void LinkInfoPanelPanorama::RestorePerspective()
{
}
void LinkInfoPanelPanorama::GetPanoramaDelta(PMPoint& delta) const
{
	delta.X(1);// shouldn't ever scroll in x direction
	delta.Y(20); 
}

//----------------------------------------------------------------------------------------
// CPanorama::ConstrainTo
//----------------------------------------------------------------------------------------

PBPMPoint LinkInfoPanelPanorama::ConstrainTo(const PBPMPoint& value) const
{
	PBPMPoint constrainedPt(0,value.Y());
	
//	PMRect bounds = GetBounds();
//	InterfacePtr<const IControlView> view(this,UseDefaultIID());
//	PMRect showingBounds = view->GetFrame();
//	PMReal maxScrollAmt = bounds.Height() - showingBounds.Height();
//	if(constrainedPt.Y() > maxScrollAmt)
//		constrainedPt.Y() = maxScrollAmt;
//
//	TRACEFLOW("Links:LinksUI","LinkInfoPanelPanorama::ConstrainTo. value is %d,%d. constrainedPt is %d,%d. maxScrollAmount is %d\n",
//		::ToInt32(value.X()),::ToInt32(value.Y()),::ToInt32(constrainedPt.X()),::ToInt32(constrainedPt.Y()),::ToInt32(maxScrollAmt));

	return constrainedPt;
}

//----------------------------------------------------------------------------------------
// CPanorama::ConstrainBy
//----------------------------------------------------------------------------------------

PBPMPoint LinkInfoPanelPanorama::ConstrainBy(const PBPMPoint& delta) const
{
	PMPoint offsetPt = GetScrollOffset_neg();
	PMReal offsetAmt = -1 * offsetPt.Y();
	
	PMPoint constrainedDelta(0,delta.Y());

	PMRect bounds = GetBounds();
	InterfacePtr<const IControlView> view(this,UseDefaultIID());
	PMRect showingBounds = view->GetFrame();
	PMReal maxScrollAmt = bounds.Bottom() - showingBounds.Height();

	if(offsetAmt + constrainedDelta.Y() > maxScrollAmt)
		constrainedDelta.Y() = maxScrollAmt - offsetAmt;
	else if(offsetAmt + constrainedDelta.Y() < 0)
		constrainedDelta.Y() = 0 - offsetAmt;
	
	TRACEFLOW("Links:LinksUI","LinkInfoPanelPanorama::ConstrainBy. offsetPt.Y is %d, deltaY is %d. constrainedDeltaY is %d. maxScrollAmount is %d, bounds(%d,%d,%d,%d), showingBounds (%d,%d,%d,%d)\n",
		::ToInt32(offsetAmt),::ToInt32(delta.Y()),::ToInt32(constrainedDelta.Y()),::ToInt32(maxScrollAmt),::ToInt32(bounds.Left()),::ToInt32(bounds.Top()),::ToInt32(bounds.Right()),::ToInt32(bounds.Bottom()),
		::ToInt32(showingBounds.Left()),::ToInt32(showingBounds.Top()),::ToInt32(showingBounds.Right()),::ToInt32(showingBounds.Bottom()));
	return constrainedDelta;
}

