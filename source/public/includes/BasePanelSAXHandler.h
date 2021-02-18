//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BasePanelSAXHandler.h $
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
//========================================================================================

#pragma once
#ifndef __BasePanelSAXHandler__
#define __BasePanelSAXHandler__

#include "CSAXContentHandler.h"
#include "PaletteRef.h"

class IControlView;
class ISAXServices;

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

class WIDGET_DECL BasePanelSAXHandler : public CSAXContentHandler
{
	typedef CSAXContentHandler inherited;
	
public:
	BasePanelSAXHandler(IPMUnknown *boss);
	virtual ~BasePanelSAXHandler();

	/** Override to register the content tags specific to your panel. Default implementation only caches saxServices into fSAXServices.*/
	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer);
	
  /** Override to handle one of the content tags you registered for. */
	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs) = 0;
	
  /** Override to handle the end tag. Default implementation does nothing, which is sufficient, unless the tag is a container for sub elements. */
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);
	
  /** Override to change handling of sub elements within your content data. Default is to handle sub elements. */
	virtual bool16 HandlesSubElements() const;

protected:

	ISAXServices*	fSAXServices;
};

#pragma export off

#endif //BasePaletteSAXHandler