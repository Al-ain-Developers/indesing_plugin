//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/hacks/Templates_FormFieldUI.cpp $
//  
//  Owner: Tim Wright
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
//  Adapted from templates_group.cpp
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "PMPoint.h"
#include "K2Vector.tpp"
#include "K2Pair.h"

#include "FormFieldTypes.h"
#include "NodeID.h"

#include "OrderListElement.h"
#include "IDocumentFieldOrder.h"
#include "PersistObjectCollection.tpp"
#include "setspaneldetailcontroller.h"


#ifdef WINDOWS
#pragma warning (disable:4660)
#endif

template class PersistObjectCollection<WidgetIDHolder>;
template class PersistObjectCollection<PersistObjectCollection<WidgetIDHolder> >;
template class K2Vector<WidgetIDHolder>;
template class K2Vector<OrderListElement>;

template class K2Vector<Form::DefinedAppearanceState>;
template class K2Vector< K2Pair<PMString, PMString> >;

#ifdef MACINTOSH
template class K2Vector<NodeID>;
#endif

template class K2Vector<IDocumentFieldOrder::ItemInstance>;

#ifdef WINDOWS
#pragma warning(default:4660)
#endif
