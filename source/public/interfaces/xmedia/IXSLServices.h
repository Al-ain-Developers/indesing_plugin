//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXSLServices.h $
//  
//  Owner: Robin Briggs
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

#ifndef __IXSLServices_h__
#define __IXSLServices_h__

#include "XMLParserID.h"
#include <vector>

class IIDXMLDOMDocument;
class IPMStream;
class IIDXMLDOMNode;

/** Class responsible for XSL Transformation.

*/
class IXSLServices : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXSLSERVICES };
	
		// Could later add support for compiled stylesheets.
		
		typedef std::vector< std::pair<PMString, PMString> > Params;
		
        /**
        Transform from a DOM source to a DOM result using an XSL
        stream. The result is a new DOM document.

        Apply the stylesheet provided as an XSL stream to the input
        DOM document and write the transformation result to the
        provided DOM document, document fragment, or element.

        This signature of transform is useful for transforming
        a single DOM source tree into another DOM tree, when
        the stylesheet is most conveniently input as a stream.

        <i>XSL Output Error</i> Since the output to the resultDOM
        must be well-formed XML, any xsl stylesheet that only 
        outputs text nodes to a resultDOM that does not already 
        contain a root element will cause an error.

        @param srcDOM           DOM document to transform.  Must not
                                be nil.

        @param srcXSLT          XSL stylesheet stream to use in the
                                transformation. Must not be nil.

        @param resultDOM        An output parameter that will contain 
        						the result of the transformation. This
        						can be the same as the srcDOM.
        						Must not be nil.

        @return                 Returns 'kTrue' if the transformation
                                successfully completed, otherwise
                                'kFalse' and 'resultDOM' is left
                                unchanged.

        */
	virtual bool16 Transform(IIDXMLDOMDocument *srcDOM, IPMStream *srcXSLT, const Params& params, IIDXMLDOMDocument *resultDOM) = 0;
};


#endif //__IXSLServices_h__

