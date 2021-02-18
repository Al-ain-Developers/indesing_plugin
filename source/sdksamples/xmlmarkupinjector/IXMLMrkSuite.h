//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/IXMLMrkSuite.h $
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

#ifndef _IXMLMrkSuite_
#define _IXMLMrkSuite_

// Interface includes:
#include "IPMUnknown.h"
#include "XMLMrkID.h"


/** From SDK sample; abstract suite to allow marking up text selection as one of a variety of different XML based sub-trees. 
	For example, the informaltable sub-tree (from DocBook XML)can consist of:
	<pre>
	&lt;informaltable&gt;
		&lt;tgroup&gt;
			&lt;tbody&gt;
				&lt;row&gt;
					&lt;entry&gt;
					...
				&lt;/row&gt;
				....
			&lt;/tbody&gt;
		&lt;/tgroup&gt;
	&lt;/informaltable&gt;
	</pre>

	To create such a rich sub-tree by hand is relatively difficult and tedious within the user-interface.
	The use of this plug-in would be when the content is already within InDesign and the objective is to
	mark up the content automatically and as quickly and accurately as possible, rather than relying on manual
	cutting and pasting into an empty structured template.

	See XMLMrkConstants for more detail on the different elements and for references to the Web based documentation
	about the XML language that these elements were drawn from.

	
	@ingroup xmlmarkupinjector
*/
class IXMLMrkSuite : public IPMUnknown
{
public:
	/** kDefaultIID */
	enum { kDefaultIID = IID_IXMLMrkSUITE };

	/** Determine if abstract selection supports making a informaltable sub-tree.
	   @param none
	   @return 	kTrue if the abstraction selection supports making an informaltable subtree, kFalse otherwise  
	 */
	virtual bool16 CanMakeTable() const=0;

	/**
	   If CanMakeTable returned true, then proceed to make the informaltable subtree.
	   @param hasHeaderRow kTrue to make an informaltable with a thead row, kFalse otherwise
	   @return ErrorCode kSuccess if operation completed, kFailure otherwise
	 */
	virtual ErrorCode MakeTable(bool16 hasHeaderRow)=0;


	/**
	   Determine if abstract selection supports making a keywordset sub-tree with keyword dependents.
	   @param none
	   @return bool16 kTrue if the current selection format supports the operation, kFalse otherwise
	 */
	virtual bool16 CanMakeKeywordSet() const=0;

	/** If CanMakeKeywordSet returned true, then proceed to make the keywordset subtree.
	   @return ErrorCode kSuccess if operation completed, kFailure otherwise
	*/
	virtual ErrorCode MakeKeywordSet()=0;

	/**
	   Determine if abstract selection supports making an itemizedlist sub-tree with listitem/para dependents.
	   @return bool16 kTrue if the current selection format supports the operation, kFalse otherwise
	*/
	virtual bool16 CanMakeItemizedList() const=0;

	/**
		If CanMakeItemizedList returned true, then proceed to make the itemizedlist subtree.
		@return ErrorCode kSuccess if operation completed, kFailure otherwise
	*/
	virtual ErrorCode MakeItemizedList()=0;

	/**
	   Determine if abstract selection supports making a section sub-tree with title/para dependents.
	   @return bool16 kTrue if the current selection format supports the operation, kFalse otherwise
	*/
	virtual bool16 CanMakeSectionComposite() const=0;

	/** If CanMakeSectionComposite returned true, then proceed to make the section subtree.
		@return ErrorCode kSuccess if operation completed, kFailure otherwise
	*/
	virtual ErrorCode MakeSectionComposite()=0;

	/**
	   Determine if abstract selection supports making a mediaobject sub-tree indicated.
	   @return bool16 kTrue if the current selection format supports the operation, kFalse otherwise
	*/
	virtual bool16 CanMakeMediaObject() const=0;

	/** If CanMakeMediaObject returned true, then proceed to make the mediaobject subtree.
		@return ErrorCode kSuccess if operation completed, kFailure otherwise
	*/
	virtual ErrorCode MakeMediaObject()=0;


};

#endif // _IXMLMrkSuite_


