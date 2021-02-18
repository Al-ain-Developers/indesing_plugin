//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IIDXMLElement.h $
//  
//  Owner: robin briggs
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
#ifndef __IIDXMLElement__
#define __IIDXMLElement__

#include "K2Iterator.h"
#include "TextRange.h"
#include "XMLContentReference.h"
#include "XMLID.h"
#include "XMLReference.h"		// for LSID

#include "IPMUnknown.h"


typedef int32 LayoutSelector;
const LayoutSelector kStandardLayout = 1;


class ITextStoryThread;
class XMLContentIterator;
class XMLDTDInsertElementList;
class XMLDTDReplaceElementList;

/** This interface is for elements on the logical structure tree; 
	from client code- don't call mutators on this interface, instead use IXMLElementCommands, IXMLAttributeCommands etc.

	See the <a href="http://www.w3.org/TR/2000/REC-xml-20001006#dt-element">element definition in XML 1.0 specification</a>.
	An element will have at least a name (see IXMLTag), possibly some attributes and perhaps some content.
	The content and attributes if present are represented through this class.

	There are methods that return iterators (of type XMLContentIterator) that can be used to iterate over the contents 
	of an element in the order of the DOM. What these are doing is iterating over the children of a given XML element, not
	traversing the sub-tree.

*/
class IIDXMLElement : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IIDXMLELEMENT };

	/** Index in parent constants, for AddChildAt() method */
	enum _Placement { /** */ kEndIndex = -2 };

		// Typedefs for content iteration
	/** Typedef for content iteration. When iterating the children of an element, the children can (perhaps) be characterised by text ranges; if you have an element within one story,
		say, section, with some dependents like 'title' and 'para' then these will lie within the text range of the parent, and
		each be characterised by a TextRange in the text model.*/
	typedef InDesign::TextRange	value_type;
	/** Typedef for content iteration. */
	typedef XMLContentIterator		iterator;
	/** Typedef for content iteration. */
	typedef XMLContentIterator		const_iterator;
	/** Typedef for content iteration. */
	typedef const value_type* 	pointer;
	/** Typedef for content iteration. */
	typedef const value_type* 	const_pointer;
	/** Typedef for content iteration. */
	typedef const value_type& 	reference;
	/** Typedef for content iteration. */
	typedef const value_type& 	const_reference;
	/** Typedef for content iteration. */
	typedef K2Reverse_iterator<iterator, value_type, std::ptrdiff_t, pointer, reference> reverse_iterator;
	/** Typedef for content iteration.*/
	typedef K2Reverse_iterator<const_iterator, value_type, std::ptrdiff_t, const_pointer, const_reference>	const_reverse_iterator;

	/**	Return a persistent reference (XMLReference) to this element.
	   
	   @return XMLReference to this element 
	 */
	virtual const XMLReference& GetXMLReference() const = 0;

	/**	Mutator to set a new persistent reference (XMLReference) for this element.
	   @param newXMLRef specifies the reference for this element.
	 */
	virtual void SetXMLReference(const XMLReference& newXMLRef) = 0;

	/**	Return the number of children this element has.
	   
	   @return int32 number of children
	 */
	virtual int32 GetChildCount() const = 0;
	
	/**	Return the n'th child of the element; note that you can also use iterators rather than this mechanism
		to iterate over the children. Index is zero-based index that should be in range [0..GetChildCount()-1] 
	   @return persist reference to child at given index
	 */
	virtual XMLReference GetNthChild(int32) const = 0;
	
	/**	Return the parent element.	
	   
	   @return XMLReference to the parent 
	 */
	virtual const XMLReference& GetParent() const = 0;
	

	/**	Mutator for the parent element (moves the element to a new location on the hierarchy);
		use IXMLElementCommands::MoveElement instead from client code.

	   @param newParent specifies new parent element to set for this element
	 */
	virtual void SetParent(const XMLReference& newParent) = 0;

	/**	Return the n'th child that has the specified tag applied.
	   @param tag name of the tag (IXMLTag) associated with this element
	   @param index specifies index of child of interest
	   @return XMLReference to the given child 
	 */
	virtual XMLReference FindChild(const WideString& tag, int32 index) const = 0;

	/**	Find index of child
	   @param childToFind persistent reference for child of interest
	   @return int32 zero-based index of child with given XMLReference, -1 if
	   child does not exist
	 */
	virtual int32 FindChild(const XMLReference& childToFind) const = 0;


	/** Mutator, to add child at given index.
	   @param newChild child to add
	   @param indexAt specifies desired new index for child (or kEndIndex if no pref.)
	   @param setChildsParent if kTrue, set the child's parent to point back to this	 
	 */
	virtual void AddChildAt(const XMLReference& newChild, int32 indexAt, bool16 setChildsParent = kTrue) = 0;


	/** Mutator; has the effect of  removing given child, 
	   @param childToRemove specifies child to remove
	   @param resetChild if kTrue also sets the child's parent to invalid (i.e. kInvalidXMLReference).
	 */
	virtual void RemoveChild(const XMLReference& childToRemove, bool16 resetChild = kTrue) = 0;

	/**
	   Remove child at given index
	   @param indexAt specifies zero based index of child to remove
	   @param resetChild if kTrue also sets the child's parent to invalid (i.e. kInvalidXMLReference).

	 */
	virtual void RemoveChild(int32 indexAt, bool16 resetChild = kTrue) = 0;

	/**	Mutator to set the specified child's XMLReference
	   @param newChildXMLRef specifies new child
	   @param indexAt specifies index where child should be changed
	 */
	virtual void SetChildAt(const XMLReference& newChildXMLRef, int32 indexAt) = 0;


	/** Return UID for tag (IXMLTag) associated with this element
	   
	   @return UID which can be used to instantiate IXMLTag given database 
	   of this element
	 */
	virtual UID GetTagUID() const = 0;

	/**
	   Accessor for tag-name of this element
	    @return WideString giving tag-name of element
	 */
	virtual WideString GetTagString() const = 0;

	/** Mutator for tagname of this element; use IXMLElementCommands::SetElement rather
		than this from client code. Uses an IXMLTag, 
		created perhaps with IXMLTagCommands method.
	   @param newTag specifies UID of an IXMLTag that contains new name for this element
	 */
	virtual void SetTag(UID newTag) = 0;

	/** Mutator for tagname, but use IXMLElementCommands::SetElement rather
		than this from client code.
	   @param newTag specifies new tagname to set for this element
	 */
	virtual void SetTag(const WideString& newTag) = 0;
	
	/** Return the item in layout where content will appear, if there is one.
	   @param selector identifies what layout content should appear in (param reserved for future use)
	   @return UID of content item associated
	 */
	virtual UID GetContentItem(LayoutSelector selector = kStandardLayout) const = 0;

	/** Mutator for content item associated with this element
	   @param contentItem 
	   @param selector default kStandardLayout (param reserved for future use)
	 */
	virtual void SetContentItem(UID contentItem, LayoutSelector selector = kStandardLayout) = 0;

	/** Return the content reference associated with this element
		@return content reference associated with this element
	*/
	virtual const XMLContentReference& GetContentReference(void) const = 0;

	/** Mutator for content reference associated with this element
		@param contentReference new content reference
	*/
	virtual void SetContentReference(const XMLContentReference& contentReference) = 0;

	/** Query ITextStoryThread associated with the content, if applicable
		@return ref-incremented ITextStoryThread interface of the content, if applicable; nil otherwise
	*/
	virtual ITextStoryThread *QueryContentTextStoryThread(void) const = 0;
	
	/** Add an attribute, optionally specifying that it can be removed later.
	   @param name identifies the attribute
	   @param value initial value for this attribute
	   @param removable if set to kTrue, then the attribute can't be removed by later calls (i.e. RemoveAttribute will fail)
	 */
	virtual void AddAttribute(const WideString& name, const WideString& value, bool16 removable = kTrue) = 0;

	/** Remove named attribute, unless added as non-removable; use IXMLElementCommands rather than this mutator from client code.
	   @param name identifies attribute to be removed
	 */
	virtual void RemoveAttribute(const WideString& name) = 0;

	/** Mutator for an attribute name; from client code, 
		use IXMLAttributeCommands method from client code.
	   @param name specifies existing name for attribute of interest
	   @param newName specifies the new name to change it to
	 */
	virtual void SetAttributeName(const WideString& name, const WideString& newName) = 0;

	/**
	   Mutator; for attribute value, but
	   use IXMLAttributeCommands method from client code.
	   @param name identifies attribute of interest
	   @param newValue specifies new value
	 */
	virtual void SetAttributeValue(const WideString& name, const WideString& newValue) = 0;


	/**
	   Accessor for attribute count on this element
	   @return size of attribute list
	 */
	virtual int32 GetAttributeCount() const = 0;

	/** Determine if this element has named attribute
	   @param name name of attribute
	   @return bool16 kTrue if it has, kFalse otherwise
	 */
	virtual bool16 HasAttribute(const WideString& name) const = 0;

	/** Accessor for attribute at given index
	   @param pos zero-based index in attribute list, 0 <= pos < GetAttributeCount()
	   @return WideString giving attribute name
	 */
	virtual WideString GetAttributeNameAt(int32 pos) const = 0;

	/** Accessor for attrib-value, given its name.
	   NOTE: calling this method with an attribute name that does not exist on 
	   the element technically is an undefined operation, even though this method 
	   will return an empty WideString. In DEBUG, this method will fire an assert 
	   if it is called with an attribute that does not exist, although it is safe 
	   to continue. Please use HasAttribute() first to make sure the attribute exists.
	   @see HasAttribute
	   @param name specifies attribute of interest
	   @return WideString containing attrib value 
	 */
	virtual WideString GetAttributeValue(const WideString& name) const = 0;

	/** Accessor for attribute at given index
	   @param pos zero-based index in attribute list, 0 <= pos < GetAttributeCount()
	   @return WideString the attribute value
	 */
	virtual WideString GetAttributeValueAt(int32 pos) const = 0;

	/** Determine if attribute has been created as removable or not
	   @param name identifies attribute of interest
	   @return bool16 kTrue if can be removed by client code, kFalse otherwise
	 */
	virtual bool16 IsAttributeRemovable(const WideString& name) const = 0;


	/**	Get iterator for iterating through children of this element
	   @return iterator to mark start of forward iteration over all children 
	 */
	virtual const_iterator		begin() const = 0;

	/** Get iterator for ending iteration (one of end of children)
	   @return  iterator to mark limit for forward iteration 
	 */
	virtual const_iterator		end() const = 0;

	/** Get forward iterator for iterating through children of this element starting
		at arbitrary position in the children list
	   @param position specifies location where the iterator should start from
	   @return  iterator that can be used to traverse children from given position
		to 'end'
	 */
	virtual const_iterator		make_iterator(int32 position) const = 0;


	/** Get iterator for backward iteration through children
	   @return  iterator for marking start of reverse iteration through children
	 */
	virtual const_reverse_iterator		rbegin() const = 0;

	/**	Get iterator to mark end of backward iteration process
	   @return  iterator for marking end of reverse iteration through children
	 */
	virtual const_reverse_iterator		rend() const = 0;

	/**	Make reverse iterator, for backward iteration from arbitrary position
	   @param position where iteration should start from
	   @return iteration that can be used from this start point to 'rend'
	 */
	virtual const_reverse_iterator		rmake_iterator(int32 position) const = 0;
	
	/**	get a list of first child elements the DTD will allow to insert
	   @param childElementList [OUT] receives the list of child elements the DTD will allow to 
	   insert for this element
	 */
	virtual void GetInsertChildElementList(XMLDTDInsertElementList& childElementList)  const = 0;
	
	/**	get a list of sibling after elements the DTD will allow to insert
	   @param childElementList [OUT] receives the list of sibling after elements the DTD will 
	   allow to insert
	 */
	virtual void GetInsertSiblingAfterList(XMLDTDInsertElementList& siblingAfterList)  const = 0;
	
	/** get a list of possible replacement tags which the DTD will allow for this element
		@param replaceElementList [OUT] receives the list of replacements tags the DTD will allow
	*/
	virtual void GetReplaceElementList(XMLDTDReplaceElementList& replaceElementList) const = 0;
};


#endif // __IIDXMLElement__

