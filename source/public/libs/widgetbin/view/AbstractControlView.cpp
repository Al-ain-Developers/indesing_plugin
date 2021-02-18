//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/view/AbstractControlView.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
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

#include "DV_VCWidgetHeaders.h"
#include "AbstractControlView.h"

#include "IPMStream.h"
#include "IChangeManager.h"
#include "IControlViewObservers.h"
#include "IObserver.h"
#include "IPanelControlData.h"
#include "ITouchWSUtils.h"
#include "IWidgetParent.h"

#include "IWindow.h"

#include "PMPolygon4.h"
#ifdef DEBUG
#	include "DebugClassUtils.h"
#endif

#include   "IDVUINodeRef.h"

const PMRect kMaxRect16(-kMaxInt16,-kMaxInt16,kMaxInt16,kMaxInt16);

static bool16 MoveAndPositiveScaleOnly(const PMMatrix& m)
{
	return (m[0] > 0 && m[1] == 0 && m[2] == 0 && m[3] > 0);
}

static void transform_rect(const PMMatrix& m, PMRect * r)
{
	ASSERT_MSG( MoveAndPositiveScaleOnly(m), "This won't remain a rectangle...");
	PMPoint lt = r->LeftTop();
	PMPoint rb = r->RightBottom();
	m.Transform(&lt);
	m.Transform(&rb);
	r->LeftTop(lt);
	r->RightBottom(rb);
}




DEFINE_HELPER_METHODS(AbstractControlView)

AbstractControlView::AbstractControlView(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fWidgetId(kDefaultWidgetId),
	fFrameBinding(0),
	fFrame(0, 0, 0, 0),
	fContentTransform(nil)
{
	fRsrcId.fId = 0;
	fRsrcId.fPluginId = kInvalidPlugin;
}

AbstractControlView::~AbstractControlView()
{
	DestroyContentTransform();
}

void AbstractControlView::ReadWrite(IPMStream *s, ImplementationID prop)
{
	s->XferID(fWidgetId);
	s->Comment("\t// Widget ID\n");

	s->XferInt32((int32&)fRsrcId.fId);
	s->Comment("\t// Resource ID\n");

	s->XferID(fRsrcId.fPluginId);
	s->Comment("\t// Resource Plugin ID\n");

	s->XferInt16((int16&) fFrameBinding);
	s->Comment("\t// Frame binding\n");

	s->Comment("Frame(");
	fFrame.ReadWrite(s);
	s->Comment(")\t\t// Frame\n");

	bool16 aBool;
	if (s->IsReading())
	{
		s->XferBool(aBool);
		SetVisibleState(aBool);
		s->XferBool(aBool);
		SetEnableState(aBool);
	}
	else
	{
		aBool = GetVisibleState();
		s->XferBool(aBool);
		aBool = GetEnableState();
		s->XferBool(aBool);
	}

	s->Comment("\t// Visible, Enabled\n");

}

void AbstractControlView::Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID)
{
	PreDirty ();
	fWidgetId = widgetId;
	fFrame = frame;
	fRsrcId.fId = rsrcID;

	
}

void AbstractControlView::DoPostCreate()
{
	InvalidateTransform();
}

RsrcID AbstractControlView::GetRsrcID() const
{
	return fRsrcId.fId;
}

void AbstractControlView::SetRsrcID(const RsrcID &id)
{
	if(fRsrcId.fId != id)
	{
		PreDirty ();
		fRsrcId.fId = id;		
	}
}

PluginID AbstractControlView::GetRsrcPluginID() const
{
	return fRsrcId.fPluginId;
}

void AbstractControlView::SetRsrcPluginID(const PluginID &id)
{
	if ( fRsrcId.fPluginId != id ) {
		PreDirty ();
		fRsrcId.fPluginId = id;
	}
}

WidgetID AbstractControlView::GetWidgetID() const
{
	return fWidgetId;
}

void AbstractControlView::SetWidgetID(const WidgetID &id)
{
	if(fWidgetId != id)
	{
		PreDirty ();
		fWidgetId = id;
	}
}

void AbstractControlView::SetFrameBinding(const FrameBinding& binding)
{
	PreDirty ();
	fFrameBinding = binding;
	
}

FrameBinding AbstractControlView::GetFrameBinding() const
{
	return fFrameBinding;
}

PMPoint AbstractControlView::ConstrainDimensions(const PMPoint& dimensions) const
{
	return dimensions;
}

SysRect AbstractControlView::GetBBox() const
{
#if DEBUG
	DebugClassUtilsBuffer buf;
	const char* p = DebugClassUtils::GetIDName( &buf, this->GetWidgetID());
#endif

	PMRect frame = GetFrame();

	InterfacePtr<IControlView> parent((IControlView*) QueryParentFor(IID_ICONTROLVIEW));
	if (parent)
	{
#if DEBUG
		p = DebugClassUtils::GetIDName( &buf, parent->GetWidgetID()); 
#endif
		PMMatrix m = parent->GetContentToWindowMatrix();
		transform_rect( m, &frame);
	}

	// prevent overflow of SysRect
	frame = ::Intersection( frame, kMaxRect16, PMRect(0, 0, 0, 0) );

	return ToSys(frame);
}

PMRect AbstractControlView::GetContentBounds_() const
{
	PMRect viewBounds = this->GetBBox();
	this->WindowToContentTransform(&viewBounds);
	return viewBounds;
}

void AbstractControlView::ContentToWindowTransform( PMPoint * point) const
{
	this->GetContentToWindowMatrix().Transform( point);
}

void AbstractControlView::WindowToContentTransform( PMPoint * point) const
{
	PMMatrix m = this->GetContentToWindowMatrix();
	m.Invert();
	m.Transform( point);
}


static void transform_poly( const PMMatrix& m, PMPolygon4 * poly)
{
	m.Transform(&((*poly)[0]));
	m.Transform(&((*poly)[1]));
	m.Transform(&((*poly)[2]));
	m.Transform(&((*poly)[3]));
}

void AbstractControlView::ContentToWindowTransform( PMPolygon4 * poly) const
{
	PMMatrix m = this->GetContentToWindowMatrix();
	transform_poly( m, poly);
}

void AbstractControlView::WindowToContentTransform( PMPolygon4 * poly) const
{
	PMMatrix m = this->GetWindowToContentMatrix();
	transform_poly( m, poly);
}





//----------------------------------------------------------------------------------------
// The following two routines assume the PMRect remains a normalized
// rectangle after the transform (only guaranteed for translation
// and scaling values > 0).
//----------------------------------------------------------------------------------------

void AbstractControlView::ContentToWindowTransform( PMRect * rect) const
{
	PMMatrix m = this->GetContentToWindowMatrix();
	transform_rect( m, rect);
}

void AbstractControlView::WindowToContentTransform( PMRect * rect) const
{
	PMMatrix m = this->GetWindowToContentMatrix();
	transform_rect( m, rect);
}



PMMatrix AbstractControlView::GetContentToWindowMatrix() const
{
	return *this->GetContentToWindowTransform();
}

PMMatrix AbstractControlView::GetWindowToContentMatrix() const
{
	PMMatrix m = this->GetContentToWindowMatrix();
	m.Invert();
	return m;
}


PMMatrix* AbstractControlView::GetContentToWindowTransform() const
{
	AbstractControlView* ncThis = const_cast<AbstractControlView*>(this);

	if (fContentTransform == nil) //sylvia perhaps kill this cache
		ncThis->fContentTransform = ncThis->GetUpdatedContentToWindowTransform();

	return fContentTransform;
}

void AbstractControlView::InvalidateTransform()
{
	DestroyContentTransform();
	DeleteDrawRegion();
}

int32 AbstractControlView::HitTest(const SysPoint& where)
{
	SysRect bbox = GetBBox();

	return ::SysPointInSysRect(where, bbox);
}

void AbstractControlView::ParentsVisibleStateChanged(bool16 visible)
{
	if (visible)
		HandleAutoAttach();
	else
		HandleAutoDetach();
}

void AbstractControlView::WindowActivated()
{
}

void AbstractControlView::WindowDeactivated()
{
}

void AbstractControlView::WindowShown()
{
	HandleAutoAttach();
}

void AbstractControlView::WindowHidden()
{
	HandleAutoDetach();
}

void AbstractControlView::WindowChanged()
{
	IWindow* window = (IWindow*) QueryParentFor(IID_IWINDOW);
	if (window == nil)
		window = (IWindow*) QueryInterface(IID_IWINDOW);

	InterfacePtr<IWindow> cleanUpWindow(window);

	InvalidateTransform();

	dvaui::ui::OS_View* topLevelOSView = nil;
	if (Utils<ITouchWSUtils>()->IsAppInTouchWSMode())
	{
		InterfacePtr<IDV_UI_NodeRef> nodeRef(this, UseDefaultIID());
		dvaui::ui::UI_Node* current_UI_Node = nodeRef->Get_UI_Node();

		while (current_UI_Node != nil)
		{
			topLevelOSView = IDV_UI_NodeRef::Get_UI_Node_As<dvaui::ui::OS_View>(current_UI_Node);
			if (topLevelOSView == nil)
			{
				current_UI_Node = current_UI_Node->UI_GetParentNode();
			}
			else
				break;
		}
	}

	if (window || topLevelOSView)
		HandleAutoAttach();
	else
	{
		HandleAutoDetach();
		
		DestroyWrappedSystemControls();
	}
}

void AbstractControlView::WindowClosed()
{
	DestroyWrappedSystemControls();
	
	// Reset the state of the control back to the stone age
	DeleteDrawRegion();
	DestroyContentTransform();
}

void AbstractControlView::ParentPurged()
{
	DestroyWrappedSystemControls();
	
	// Reset the state of the control back to the stone age
	DeleteDrawRegion();
	DestroyContentTransform();
}

bool16 AbstractControlView::AncestorsAreEnabled() const
{
	InterfacePtr<IControlView> ancestor((AbstractControlView*) QueryParentFor(IID_ICONTROLVIEW));
	return ( ancestor == nil ? kTrue : ancestor->IsEnabled() );
}

IPMUnknown* AbstractControlView::QueryParentFor(const PMIID& interfaceID) const
{
	IPMUnknown* parent = nil;

	InterfacePtr<IWidgetParent> parentLink((AbstractControlView*) this, IID_IWIDGETPARENT);
	if (parentLink)
		parent = parentLink->QueryParentFor(interfaceID);

	return parent;
}

void AbstractControlView::NotifyParent(const WidgetAttributeID& id)
{
	InterfacePtr<IPanelControlData> panel((IPanelControlData*) QueryParentFor(IID_IPANELCONTROLDATA));
	if (panel)
		panel->WidgetAttributeChanged(this, id);
}

PMMatrix* AbstractControlView::CreateTransform()
{
	return new PMMatrix();
}

void AbstractControlView::DestroyContentTransform()
{
	if (fContentTransform)
		delete fContentTransform;
		
	fContentTransform = nil;
}

void AbstractControlView::HandleAutoAttach()
{
	if (!IsAutoAttached() && IsVisible(kTrue))
		DoAutoAttach();
}

void AbstractControlView::HandleAutoDetach()
{
	IWindow* window = (IWindow*) QueryParentFor(IID_IWINDOW);
	if (window == nil)
		window = (IWindow*) QueryInterface(IID_IWINDOW);

	InterfacePtr<IWindow> cleanupWindow(window);
	
	if (IsAutoAttached() && (!window || !window->IsVisible() || !GetVisibleState() || !AncestorsAreVisible(kFalse)))
		DoAutoDetach();
}

void AbstractControlView::DoAutoAttach()
{
	SetIsAutoAttached();

	InterfacePtr<IObserver> observer(this, IID_IOBSERVER);
	InterfacePtr<IControlViewObservers> observers(this, IID_ICONTROLVIEWOBSERVERS);

	if (observers)
		observers->OnDoAutoAttach(this);
	else
	{
		if (observer)
			observer->AutoAttach();
	}
}

void AbstractControlView::DoAutoDetach()
{
	SetIsAutoAttached(kFalse);

	InterfacePtr<IObserver> observer(this, IID_IOBSERVER);
	InterfacePtr<IControlViewObservers> observers(this, IID_ICONTROLVIEWOBSERVERS);

	if (observers)
		observers->OnDoAutoDetach(this);
	else
	{
		if (observer)
		{
			observer->AutoDetach();
	#ifdef DEBUG
			PMIID observerStillAttached = GetExecutionContextSession()->GetChangeManager()->IsObserverAttached(observer,IID_IOBSERVER);
			if(	observerStillAttached != kInvalidInterfaceID )
			{
				ClassID classId = ::GetClass(observer);
				// exclude the ones I know about and can't fix.
				if(classId != kTabAreaWidgetBoss && classId != kClusterPanelWidgetBoss)
				{
					DebugClassUtilsBuffer classBuf,iidBuf;
						TRACEFLOW("Widgets", "Observer classID %s still attached to IID %s after AutoDetach\n",
						DebugClassUtils::GetIDName(&classBuf,classId),DebugClassUtils::GetIDName(&iidBuf,observerStillAttached));

					// Note: I'd like to make this an assert, but there are too many things that hit it right now...
					//char assertStr[1024];
					//sprintf(assertStr,"Observer classID %s still attached to IID %s after AutoDetach",
					//	DebugClassUtils::GetClassIDName(&classBuf,::GetClass(observer)),DebugClassUtils::GetInterfaceIDName(&iidBuf,observerStillAttached));
					//ASSERT_FAIL(assertStr);
				}
			}
	#endif
		}
	}
}


void AbstractControlView::DestroyWrappedSystemControls()
{
}

