//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPanelBasedXMLGenerator.h $
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
//  
//  A base implementation of IXMLGenerator for panels involved in palette workspaces
//  Handles common implementation of panels, kits and control sets.
//  
//========================================================================================

#pragma once
#ifndef __CPanelBasedXMLGenerator__
#define __CPanelBasedXMLGenerator__

#include "CXMLGenerator.h"
#include "IControlView.h"
#include "IXMLOutStream.h"
#include "PaletteRef.h"

class IKit;

#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	The base class used to generate the xml-based workspace representation of palette based panels.
		CPanelBasedXMLGenerator contains the default implementation used to write panels into a palette workspace.
 
		Clients who need to override the default behavior provided here should subclass BasePanelXMLGenerator and
		include the implementation on their panel's boss as an IID_IXMLGENERATOR interface.
	
	@see IXMLGenerator, BasePanelXMLGenerator
*/

class WIDGET_DECL CPanelBasedXMLGenerator : public CXMLGenerator
{
	typedef CXMLGenerator inherited;
	
public:
	CPanelBasedXMLGenerator(IPMUnknown *boss);
	virtual ~CPanelBasedXMLGenerator();

	/** Should this particular panel be persisted. 
			Returns kTrue by default. Book panels (which are not persisted) provide their own XMLGenerator that returns kFalse.  */
	virtual bool16 ShouldPanelBePersisted(IControlView* panel);

	/** Writes the XML begin tag for a panel, including panel attributes, onto a stream  */
	virtual void GeneratePanelBeginTag(IXMLOutStream *s, IControlView* panel);

	/** Writes the XML representation of the panel content, onto a stream  */
	virtual void GeneratePanelContents(IXMLOutStream *s, IControlView* panel);

	/** Writes the XML end tag for a panel onto a stream  */
	virtual void GeneratePanelEndTag(IXMLOutStream *s, IControlView* panel);
	
protected:
	
	/** Collect the panel attributes (size, widgetID, detail level, etc. in an attribute list */
	virtual void PushPanelAttributes(IXMLOutStream::AttributeList& attrs, IControlView* panel);
		
	/** Writes the XML representation of a control set onto a stream  */
	virtual void GenerateControlSet(IXMLOutStream *s, IKit* panelKit);

	/** Utility method to add a boolean attribute to an attribute list */
	void PushBool(IXMLOutStream::AttributeList& attrs, const PMString& name, bool16 theBool);
	/** Utility method to add an integer attribute to an attribute list */
	void PushInt(IXMLOutStream::AttributeList& attrs, const PMString& name, int32 theInt);
	/** Utility method to add a string attribute to an attribute list */
	void PushString(IXMLOutStream::AttributeList& attrs, const PMString& name, const PMString& value);
};

#pragma export off

#endif //BasePaletteXMLGenerator
