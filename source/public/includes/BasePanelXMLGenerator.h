//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BasePanelXMLGenerator.h $
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
//  An implementation of IXMLGenerator used to allow palette based panels to override their xml-based workspace description.
//  
//========================================================================================

#pragma once
#ifndef __BasePanelXMLGenerator__
#define __BasePanelXMLGenerator__

#include "CPanelBasedXMLGenerator.h"
#include "IControlView.h"
#include "IXMLOutStream.h"

class IPanelControlData;

#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	This class is the base class used by palette based panels that need to override their xml-based workspace representation. 
		The default implementation provided here handles generating the begin and end tags (including default panel attributes),
		as well as a default content generator.
	 
		In order to change their XML content representation, clients can override GenerateContent.
			(there are 8 panels in CS3 that generate extra panel content - you can look inside a workspace file to see examples of this).
		In order to augment the XML attributes used in the panel's begin tag, clients can override PushPanelAttributes. 
			(this is uncommon - the only use within InDesign is by the library panel to distinguish multiple copies of a panel by adding attributes
			 that contain the name and path to the library being displayed).
	
	@see IXMLGenerator, CPanelBasedXMLGenerator
*/

class WIDGET_DECL BasePanelXMLGenerator : public CPanelBasedXMLGenerator
{
	typedef CPanelBasedXMLGenerator inherited;
	
public:
	BasePanelXMLGenerator(IPMUnknown *boss);
	virtual ~BasePanelXMLGenerator();

	/** Clients shouldn't need to override this */
	virtual void GenerateBeginTag(IXMLOutStream *s);
	/** Clients shouldn't need to override this */
	virtual void GenerateEndTag(IXMLOutStream *s);
	
	/** Override this to add panel specific attributes (must call the inherited version).
			Called by GenerateBeginTag above.*/
	virtual void PushPanelAttributes(IXMLOutStream::AttributeList& attrs, IControlView* panel);
	
	/** Override this to generate any panel specific content (must call the inherited version). */
	virtual void GenerateContent(IXMLOutStream *s, int32 beforeChildIndex = 0);
};

#pragma export off

#endif //PanelXMLGenerator