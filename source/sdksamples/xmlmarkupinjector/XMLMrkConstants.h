//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/XMLMrkConstants.h $
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

#ifndef __XMLMrkConstants_H_DEFINED__
#define __XMLMrkConstants_H_DEFINED__

/** Encapsulates the names of the docbook elements and attributes that we're using. 
	@ingroup xmlmarkupinjector
*/
class XMLMrkConstants
{

public:
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/article.html">on-line definition</a>.*/ 
	static const WideString k_ARTICLE_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/informaltable.html">on-line definition</a>.*/ 
	static const WideString k_INFORMALTABLE_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/tgroup.html">on-line definition</a>.*/ 
	static const WideString k_TGROUP_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/thead.html">on-line definition</a>.*/ 
	static const WideString k_THEAD_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/tbody.html">on-line definition</a>.*/ 
	static const WideString k_TBODY_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/row.html">on-line definition</a>.*/ 
	static const WideString k_ROW_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/entry.html">on-line definition</a>.*/ 
	static const WideString k_ENTRY_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/keywordset.html">on-line definition</a>.*/ 
	static const WideString k_KEYWORDSET_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/keyword.html">on-line definition</a>.*/ 
	static const WideString k_KEYWORD_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/itemizedlist.html">on-line definition</a>.*/ 
	static const WideString k_ITEMIZEDLIST_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/listitem.html">on-line definition</a>.*/ 
	static const WideString k_LISTITEM_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/para.html">on-line definition</a>.*/ 
	static const WideString k_PARA_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/section.html">on-line definition</a>.*/ 
	static const WideString k_SECTION_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/title.html">on-line definition</a>.*/ 
	static const WideString k_TITLE_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/mediaobject.html">on-line definition</a>.*/ 
	static const WideString k_MEDIAOBJECT_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/imageobject.html">on-line definition</a>.*/ 
	static const WideString k_IMAGEOBJECT_TAG;
	/** Constant value. See the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/imagedata.html">on-line definition</a>.*/ 
	static const WideString k_IMAGEDATA_TAG;


	/** Constant value. An attribute of imagedata; see the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/imagedata.html">on-line definition</a>.*/ 
	static const WideString k_FILEREF_ATTR;
	/** Constant value. An attribute of tgroup; see the <a href="http://www.oasis-open.org/docbook/xml/simple/sdocbook/elements/tgroup.html">on-line definition</a>.*/ 
	static const WideString k_COLS_ATTR;
};

#endif // __XMLMrkConstants_H_DEFINED__




