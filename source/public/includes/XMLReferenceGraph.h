//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLReferenceGraph.h $
//  
//  Owner: Mat Marcus
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

#ifndef __XMLReferenceGraph__
#define __XMLReferenceGraph__


#include "boost/graph/graph_traits.hpp"
#include "boost/iterator/iterator_facade.hpp"
#include "boost/iterator_adaptors.hpp"

#include "DepthFirstTreeIterator.h"
#include "InterfacePtr.h"
#include "IIDXMLElement.h"
#include "K2Assert.h" 


class XMLReferenceGraphEdge
{
public:
	XMLReferenceGraphEdge() :
	  fTargetXMLRef(),
	  fTrueParentXMLRef()
	{}

	XMLReferenceGraphEdge(const XMLReference& targetXMLRef, const XMLReference& trueParentXMLRef = kInvalidXMLReference) :
	  fTargetXMLRef(targetXMLRef),
	  fTrueParentXMLRef(trueParentXMLRef)
	{
		if (fTargetXMLRef != kInvalidXMLReference && fTrueParentXMLRef == kInvalidXMLReference) {
			// calculate the true parent
			InterfacePtr<IIDXMLElement> element(fTargetXMLRef.Instantiate());
			fTrueParentXMLRef = element->GetParent();
		}

		ASSERT_MSG(fTargetXMLRef != kInvalidXMLReference || fTrueParentXMLRef != kInvalidXMLReference, "XMLReferenceGraphEdge::XMLReferenceGraphEdge: true parent should be specified when target is kInvalidXMLReference");
	}

	XMLReferenceGraphEdge(const XMLReferenceGraphEdge& other) :
	  fTargetXMLRef(other.fTargetXMLRef),
	  fTrueParentXMLRef(other.fTrueParentXMLRef)
	{}

	const XMLReference& GetTargetXMLReference() const { return fTargetXMLRef; }

	const XMLReference& GetTrueParentXMLReference() const { return fTrueParentXMLRef; }

	bool16 operator==(const XMLReferenceGraphEdge& copy) const
	{
		return (fTargetXMLRef == copy.fTargetXMLRef && fTrueParentXMLRef == copy.fTrueParentXMLRef) ? kTrue : kFalse;
	}

private:
	XMLReference fTargetXMLRef;		// target XMLReference
	XMLReference fTrueParentXMLRef;	// true parent of target, not necessarily the same as source()
};


#if 0
struct XMLReferenceIteratorPolicies : public boost::default_iterator_policies
{
    XMLReferenceIteratorPolicies() {}

    template <class IteratorAdaptor>
    typename IteratorAdaptor::reference dereference(const IteratorAdaptor& x) const
    { return x.base(); }

    template <class IteratorAdaptor>
    void increment(IteratorAdaptor& x) { advance(x, 1); }

    //template <class IteratorAdaptor>
    //void decrement(IteratorAdaptor& x) { advance(x, -1); }

    template <class IteratorAdaptor, class DifferenceType>
    void advance(IteratorAdaptor& x, DifferenceType n);

private:
    template <class IteratorAdaptor>
    XMLReference GetParentRef(IteratorAdaptor& x); 
};

template <class IteratorAdaptor, class DifferenceType>
void XMLReferenceIteratorPolicies::advance(IteratorAdaptor& x, DifferenceType n)
{ 
	ASSERT_MSG(n==1, "XMLReferenceIteratorPolicies::advance: only single step forward iterator for now");
	ASSERT_MSG(x.base().GetTargetXMLReference() != kInvalidXMLReference, "XMLReferenceIteratorPolicies::advance: cannot advance kInvalidXMLReference");
	if (x.base().GetTargetXMLReference() != kInvalidXMLReference)
	{
		InterfacePtr<IIDXMLElement> parent(GetParentRef(x).Instantiate());
		int32 index = parent->FindChild(x.base().GetTargetXMLReference()) + n;
		ASSERT(index <= parent->GetChildCount());
		x.base() = (index >= parent->GetChildCount()) ? XMLReferenceGraphEdge(kInvalidXMLReference, parent->GetXMLReference()) : XMLReferenceGraphEdge(parent->GetNthChild(index));
	}
}

template <class IteratorAdaptor>
XMLReference XMLReferenceIteratorPolicies::GetParentRef(IteratorAdaptor& x)
{
	return (x.base().GetTargetXMLReference() != kInvalidXMLReference) ? InterfacePtr<IIDXMLElement> (x.base().GetTargetXMLReference().Instantiate())->GetParent() : x.base().GetTrueParentXMLReference();
}
#endif



/**	Iterator class for the direct children of an XML reference (a vertex node).
	Use the helper function out_edges() to construct an iterator range for children of an XML reference.
	Incrementing the iterator moves to the next child.
*/
class XMLReferenceIterator : public boost::iterator_facade<
	XMLReferenceIterator, // derived
	XMLReferenceGraphEdge, // value
	boost::forward_traversal_tag, // category
	XMLReferenceGraphEdge, // reference
	int32 // difference
	>
{
public:
	XMLReferenceIterator() : 
	  fData()
	{}

	explicit XMLReferenceIterator(const XMLReferenceGraphEdge& other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(XMLReferenceIterator const& other) const { return (fData == other.fData); }

	// |||WLin 6/12/2005: the default prototype for dereference() doesn't seem right. You'd be 
	//	returning a non-const reference to a member data but yet the method is const. This may 
	//	work with pointers but that seems to be easier to deal with using const_cast. For 
	//	objects to work it takes more. Currently no clients are making non-const calls from the 
	//	return value of this method, so I made the return value const. If this changes, then 
	//	we'll have to make a different change instead, either make this method non-const or the 
	//	member data mutable (yuck)
//	XMLReferenceGraphEdge& dereference() const { return reinterpret_cast<XMLReferenceGraphEdge>(fData); }
	const XMLReferenceGraphEdge& dereference() const { return fData; }

	void advance(int32 n)
	{
		ASSERT_MSG(n >= 0, "XMLReferenceIterator::advance: only positive increments are supported right now");
		ASSERT_MSG(n == 1, "XMLReferenceIterator::advance: warning: only single increment is implemented. large advances are done in a loop and may be inefficient");
		ASSERT_MSG(fData.GetTargetXMLReference() != kInvalidXMLReference, "XMLReferenceIterator::advance: cannot advance kInvalidXMLReference");
		while (--n >= 0 && fData.GetTargetXMLReference() != kInvalidXMLReference) {
			InterfacePtr<IIDXMLElement> parent(GetParentXMLRef().Instantiate());
			int32 index(parent->FindChild(fData.GetTargetXMLReference())+1);
			ASSERT(index <= parent->GetChildCount());
			fData = (index >= parent->GetChildCount()) ? XMLReferenceGraphEdge(kInvalidXMLReference, parent->GetXMLReference()) : XMLReferenceGraphEdge(parent->GetNthChild(index));
		}
	}

	XMLReference GetParentXMLRef() const
	{
		return (fData.GetTargetXMLReference() != kInvalidXMLReference) ? InterfacePtr<IIDXMLElement> (fData.GetTargetXMLReference().Instantiate())->GetParent() : fData.GetTrueParentXMLReference();
	}

	XMLReferenceGraphEdge fData;
};

#if 0
struct XMLInEdgeIteratorPolicies : public boost::default_iterator_policies
{
    XMLInEdgeIteratorPolicies() {}

    template <class IteratorAdaptor>
    typename IteratorAdaptor::reference dereference(const IteratorAdaptor& x) const
    { return x.base(); }

    template <class IteratorAdaptor>
    void increment(IteratorAdaptor& x) { advance(x, 1); }

    //template <class IteratorAdaptor>
    //void decrement(IteratorAdaptor& x) { advance(x, -1); }

    template <class IteratorAdaptor, class DifferenceType>
    void advance(IteratorAdaptor& x, DifferenceType n);
};

template <class IteratorAdaptor, class DifferenceType>
void XMLInEdgeIteratorPolicies::advance(IteratorAdaptor& x, DifferenceType n)
{
	x.base() = XMLReferenceGraphEdge(x.base().GetTrueParentXMLReference(), kInvalidXMLReference);
}
#endif



/** Iterator class for getting the parent node of an XML reference (iterates up the hierarchy towards the root).
	Use the helper function in_edges() to get an iterator range for parents of an XML reference.
*/
class XMLInEdgeIterator : public boost::iterator_facade<
	XMLInEdgeIterator, //derived
	XMLReferenceGraphEdge, //value
	boost::forward_traversal_tag, // category
	XMLReferenceGraphEdge, // reference
	int32 // difference
	>
{
public:
	XMLInEdgeIterator() : 
	  fData()
	{}

	explicit XMLInEdgeIterator(const XMLReferenceGraphEdge& other) :
		fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(XMLInEdgeIterator const& other) const { return (fData == other.fData); }

	// |||WLin 6/12/2005: the default prototype for dereference() doesn't seem right. You'd be 
	//	returning a non-const reference to a member data but yet the method is const. This may 
	//	work with pointers but that seems to be easier to deal with using const_cast. For 
	//	objects to work it takes more. Currently no clients are making non-const calls from the 
	//	return value of this method, so I made the return value const. If this changes, then 
	//	we'll have to make a different change instead, either make this method non-const or the 
	//	member data mutable (yuck)
	// XMLReferenceGraphEdge& dereference() const { return reinterpret_cast<XMLReferenceGraphEdge>(fData); }
	const XMLReferenceGraphEdge& dereference() const { return fData; }

	void advance(int32 n)
	{
		ASSERT_MSG(n >= 0, "XMLInEdgeIterator::advance: only positive increments are supported right now");
		ASSERT_MSG(fData.GetTargetXMLReference() != kInvalidXMLReference, "XMLInEdgeIterator::advance: cannot advance past end iterator");
		while (--n >= 0 && fData.GetTargetXMLReference() != kInvalidXMLReference) {
			fData = XMLReferenceGraphEdge(fData.GetTrueParentXMLReference(), kInvalidXMLReference);
			ASSERT_MSG(n == 0 || fData.GetTargetXMLReference() != kInvalidXMLReference, "XMLInEdgeIterator::advance: cannot advance past end iterator");
		}
	}

	// member data
	XMLReferenceGraphEdge fData;
};


struct XMLReferenceGraph {

    XMLReferenceGraph(const XMLReference& rootVertex = kInvalidXMLReference,
                      const XMLReference& preorderEndEdge = kInvalidXMLReference) 
                      : fRootVertex(rootVertex), fPreorderEndEdge(preorderEndEdge) {}
	const XMLReference& RootVertex() const {return fRootVertex; }
	const XMLReference& PreorderEndEdge() const {return fPreorderEndEdge; }
private:
    XMLReference  fRootVertex; 
    XMLReference  fPreorderEndEdge;
};


namespace boost {
template<>
struct graph_traits<XMLReferenceGraph> {
	typedef XMLReference vertex_descriptor;
	typedef XMLReferenceGraphEdge edge_descriptor;
	typedef void adjacency_iterator;
	typedef XMLReferenceIterator out_edge_iterator;
	typedef XMLInEdgeIterator in_edge_iterator;
	typedef void edge_iterator;
	typedef void vertex_iterator;
	typedef int32 degree_size_type;
	typedef int32 vertices_size_type;
	typedef int32 edges_size_type;
	typedef boost::directed_tag directed_category;
	typedef boost::disallow_parallel_edge_tag edge_parallel_category;
	typedef boost::bidirectional_graph_tag traversal_category;
};
}

typedef boost::graph_traits<XMLReferenceGraph>::out_edge_iterator XMLOutEdgeIterator;


/** Helper function: Constructs an iterator range [beg, end) for the children of the specified vertex (XML reference).
*/
PUBLIC_DECL std::pair<XMLOutEdgeIterator, XMLOutEdgeIterator>
out_edges(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

PUBLIC_DECL boost::graph_traits<XMLReferenceGraph>::degree_size_type
out_degree(const XMLReference& v, const XMLReferenceGraph& g);

PUBLIC_DECL boost::graph_traits<XMLReferenceGraph>::vertex_descriptor
source(const boost::graph_traits<XMLReferenceGraph>::edge_descriptor& e, const XMLReferenceGraph& g);

PUBLIC_DECL boost::graph_traits<XMLReferenceGraph>::vertex_descriptor
target(const boost::graph_traits<XMLReferenceGraph>::edge_descriptor& e, const XMLReferenceGraph& g);

/** Helper function: Constructs an iterator range [beg, end) for the parents of the specified vertex (XML reference).
*/
PUBLIC_DECL std::pair<boost::graph_traits<XMLReferenceGraph>::in_edge_iterator, boost::graph_traits<XMLReferenceGraph>::in_edge_iterator>
in_edges(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

//PUBLIC_DECL boost::graph_traits<XMLReferenceGraph>::degree_size_type
//in_degree(const boost::graph_traits<XMLReferenceGraph>::vertex_descriptor& v, const XMLReferenceGraph& g);

//PUBLIC_DECL boost::graph_traits<XMLReferenceGraph>::degree_size_type
//degree(const boost::graph_traits<XMLReferenceGraph>::vertex_descriptor& v, const XMLReferenceGraph& g);

/*
boost::graph_traits<XMLReferenceGraph>::vertex_descriptor
rootX(const XMLReferenceGraph& g);
*/

PUBLIC_DECL XMLOutEdgeIterator
incoming_edge(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);


#if 0
class XMLDepthFirstTreeIterator: boost::iterator_adaptor<
	XMLDepthFirstTreeIterator, //derived
	boost::optional<boost::graph_traits<XMLReferenceGraph>::out_edge_iterator>, // base
	boost::graph_traits<XMLReferenceGraph>::edge_descriptor, // value
	boost::forward_traversal_tag, // category
	boost::graph_traits<XMLReferenceGraph>::edge_descriptor/*&*/, // reference
	int32 // distance
	>
{
public:
	XMLDepthFirstTreeIterator() : 
	  XMLDepthFirstTreeIterator::iterator_adaptor_()
	{}

	explicit XMLDepthFirstTreeIterator(const XMLReferenceGraphEdge& other) :
	  XMLDepthFirstTreeIterator::iterator_adaptor_(other)
	{}

	XMLReferenceGraphEdge const& base() const { return base(); }

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		ASSERT_FAIL("XMLDepthFirstTreeIterator::increment: not yet implemented");
	}
};
#endif


class XMLVirtualDepthFirstTreeIterator : public boost::iterator_facade<
	XMLVirtualDepthFirstTreeIterator, // derived
	boost::graph_traits<XMLReferenceGraph>::edge_descriptor, // value
	boost::forward_traversal_tag, // category
	boost::graph_traits<XMLReferenceGraph>::edge_descriptor/*&*/, // reference
	int32 // difference
	>
{
public:
	XMLVirtualDepthFirstTreeIterator() : 
	  fData()
	{}

	explicit XMLVirtualDepthFirstTreeIterator(const boost::graph_traits<XMLReferenceGraph>::edge_descriptor& other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(XMLVirtualDepthFirstTreeIterator const& other) const { return (fData == other.fData); }

	// |||WLin 6/12/2005: the default prototype for dereference() doesn't seem right. You'd be 
	//	returning a non-const reference to a member data but yet the method is const. This may 
	//	work with pointers but that seems to be easier to deal with using const_cast. For 
	//	objects to work it takes more. Currently no clients are making non-const calls from the 
	//	return value of this method, so I made the return value const. If this changes, then 
	//	we'll have to make a different change instead, either make this method non-const or the 
	//	member data mutable (yuck)
//	boost::graph_traits<XMLReferenceGraph>::edge_descriptor& dereference() const { return reinterpret_cast<boost::graph_traits<XMLReferenceGraph>::edge_descriptor>(fData); }
	const boost::graph_traits<XMLReferenceGraph>::edge_descriptor& dereference() const { return fData; }

	void advance(int32 n)
	{
		ASSERT_FAIL("XMLVirtualDepthFirstTreeIterator::increment: not yet implemented");
	}

	// member data
	boost::graph_traits<XMLReferenceGraph>::edge_descriptor fData;
};


//template <class T>
//PUBLIC_DECL std::pair<T, T>
//virtual_out_edges(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

//template <>
//PUBLIC_DECL std::pair<XMLVirtualDepthFirstTreeIterator, XMLVirtualDepthFirstTreeIterator>
//virtual_out_edges<XMLVirtualDepthFirstTreeIterator>(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

//template <>
//PUBLIC_DECL std::pair<XMLOutEdgeIterator, XMLOutEdgeIterator>
//virtual_out_edges<XMLOutEdgeIterator>(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

template <class T>
PUBLIC_DECL T
virtual_make_iterator(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

template <>
PUBLIC_DECL XMLVirtualDepthFirstTreeIterator
virtual_make_iterator<XMLVirtualDepthFirstTreeIterator>(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);

template <>
PUBLIC_DECL XMLOutEdgeIterator
virtual_make_iterator<XMLOutEdgeIterator>(boost::graph_traits<XMLReferenceGraph>::vertex_descriptor v, const XMLReferenceGraph& g);


// To get the root property from the graph
inline boost::graph_traits<XMLReferenceGraph>::vertex_descriptor
get(boost::graph_tree_root_t, const XMLReferenceGraph& g)
{
	return g.RootVertex();;
}


#if DEBUG
void TraceElementInfo(const XMLReference& v);
#endif


#endif //__XMLReferenceGraph__


