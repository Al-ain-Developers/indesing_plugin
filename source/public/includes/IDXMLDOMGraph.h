//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDXMLDOMGraph.h $
//  
//  Owner: Will Lin
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

#ifndef __IDXMLDOMGraph__
#define __IDXMLDOMGraph__

#include "boost/graph/graph_traits.hpp"
#include "boost/iterator/iterator_facade.hpp"
#include "boost/iterator_adaptors.hpp"
#include "DepthFirstTreeIterator.h"

#include "IIDXMLDOMNode.h"



#if 0
struct IDXMLDOMIteratorPolicies : public boost::default_iterator_policies
{
    IDXMLDOMIteratorPolicies() {}

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
void IDXMLDOMIteratorPolicies::advance(IteratorAdaptor& x, DifferenceType n)
{ 
	ASSERT_MSG(n == 1, "IDXMLDOMIteratorPolicies::advance: only single step forward iterator for now");
	ASSERT_MSG(x.base(), "IDXMLDOMIteratorPolicies::advance: cannot advance end iterator");
	if (x.base())
	{
		x.base() = x.base()->GetNextSibling();
	}
}
#endif


class IDXMLDOMIterator : public boost::iterator_facade<
	IDXMLDOMIterator, // derived
	IIDXMLDOMNode*, // value
	boost::forward_traversal_tag, // category
	IIDXMLDOMNode*, // reference
	int32 // difference
	>
{
public:
	IDXMLDOMIterator() : 
	  fData()
	{}

	explicit IDXMLDOMIterator(IIDXMLDOMNode *other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(IDXMLDOMIterator const& other) const { return fData == other.fData; }

	IIDXMLDOMNode*& dereference() const { ASSERT(fData); return const_cast<IIDXMLDOMNode*&>(fData); }

	void advance(int32 n)
	{
		ASSERT_MSG(n > 0, "IDXMLDOMIterator::advance: only positive increments are supported right now");
		ASSERT_MSG(fData, "IDXMLDOMIterator::advance: cannot advance end iterator");
		while (--n >= 0 && fData) {
			fData = fData->GetNextSibling();
			ASSERT_MSG(n == 0 || fData, "IDXMLDOMIterator::advance: attempt advance past end iterator");
		}
	}

	// member data
	IIDXMLDOMNode *fData;
};


#if 0
struct IDXMLDOMInEdgeIteratorPolicies : public boost::default_iterator_policies
{
    IDXMLDOMInEdgeIteratorPolicies() {}

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
void IDXMLDOMInEdgeIteratorPolicies::advance(IteratorAdaptor& x, DifferenceType n)
{
	x.base() = nil;
}
#endif


class IDXMLDOMInEdgeIterator : public boost::iterator_facade<
	IDXMLDOMInEdgeIterator, //derived
	IIDXMLDOMNode*, // value
	boost::forward_traversal_tag, // category
	IIDXMLDOMNode*, // reference
	int32 // difference
	>
{
public:
	IDXMLDOMInEdgeIterator() : 
	  fData()
	{}

	explicit IDXMLDOMInEdgeIterator(IIDXMLDOMNode *other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(IDXMLDOMInEdgeIterator const& other) const { return fData == other.fData; }

	IIDXMLDOMNode*& dereference() const { ASSERT(fData); return const_cast<IIDXMLDOMNode*&>(fData); }

	void advance(int32 n)
	{
		ASSERT_MSG(n == 1, "IDXMLDOMInEdgeIterator::advance: can only do 1 advance");
		ASSERT_MSG(fData, "IDXMLDOMInEdgeIterator::advance: cannot advance end iterator");
		fData = nil;
	}

	// member data
	IIDXMLDOMNode* fData;
};

struct IDXMLDOMGraph {

	IDXMLDOMGraph(IIDXMLDOMNode * const rootVertex) :
		fRootVertex(rootVertex)
	{}

	IIDXMLDOMNode *RootVertex(void) const { return fRootVertex; }

private:
    IIDXMLDOMNode *fRootVertex; 
};


namespace boost {

template<>
struct graph_traits<IDXMLDOMGraph> {
	typedef IIDXMLDOMNode *vertex_descriptor;
	typedef IIDXMLDOMNode *edge_descriptor;
	typedef void adjacency_iterator;
	typedef IDXMLDOMIterator out_edge_iterator;
	typedef IDXMLDOMInEdgeIterator in_edge_iterator;
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


typedef boost::graph_traits<IDXMLDOMGraph>::out_edge_iterator IDXMLDOMOutEdgeIterator;


PUBLIC_DECL std::pair<IDXMLDOMOutEdgeIterator, IDXMLDOMOutEdgeIterator>
out_edges(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);

PUBLIC_DECL boost::graph_traits<IDXMLDOMGraph>::degree_size_type
out_degree(const IIDXMLDOMNode *v, const IDXMLDOMGraph& g);

PUBLIC_DECL boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor
source(const boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& e, const IDXMLDOMGraph& g);

PUBLIC_DECL boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor
target(const boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& e, const IDXMLDOMGraph& g);

PUBLIC_DECL std::pair<boost::graph_traits<IDXMLDOMGraph>::in_edge_iterator, boost::graph_traits<IDXMLDOMGraph>::in_edge_iterator>
in_edges(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);

//PUBLIC_DECL boost::graph_traits<IDXMLDOMGraph>::degree_size_type
//in_degree(const boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor& v, const IDXMLDOMGraph& g);

//PUBLIC_DECL boost::graph_traits<IDXMLDOMGraph>::degree_size_type
//degree(const boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor& v, const IDXMLDOMGraph& g);
/*
boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor
rootX(const IDXMLDOMGraph& g);
*/
IDXMLDOMOutEdgeIterator
incoming_edge(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


#if 0
struct IDXMLDOMStructureOnlyIteratorPolicies : public boost::default_iterator_policies
{
    IDXMLDOMStructureOnlyIteratorPolicies() {}

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
void IDXMLDOMStructureOnlyIteratorPolicies::advance(IteratorAdaptor& x, DifferenceType n)
{ 
	ASSERT_MSG(n == 1, "IDXMLDOMStructureOnlyIteratorPolicies::advance: only single step forward iterator for now");
	ASSERT_MSG(x.base(), "IDXMLDOMStructureOnlyIteratorPolicies::advance: cannot advance end iterator");
	if (x.base())
	{
		x.base() = x.base()->GetNextSibling();

		// skip over all content nodes
		while (x.base() && x.base()->GetNodeType() == IIDXMLDOMNode::kText)
			x.base() = x.base()->GetNextSibling();
	}
}
#endif


class IDXMLDOMStructureOnlyIterator : public boost::iterator_facade<
	IDXMLDOMStructureOnlyIterator, //derived
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor, // value
	boost::forward_traversal_tag, // category
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor, // reference
	int32 // difference
	>
{
public:
	IDXMLDOMStructureOnlyIterator() : 
	  fData()
	{}

	explicit IDXMLDOMStructureOnlyIterator(const boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(IDXMLDOMStructureOnlyIterator const& other) const { return fData == other.fData; }

	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& dereference() const { return const_cast<boost::graph_traits<IDXMLDOMGraph>::edge_descriptor&>(fData); }

	void advance(int32 n)
	{
		ASSERT_MSG(n > 0, "IDXMLDOMStructureOnlyIterator::advance: only positive increments are supported right now");
		ASSERT_MSG(fData, "IDXMLDOMStructureOnlyIterator::advance: cannot advance end iterator");
		while (--n >= 0 && fData) {
			fData = fData->GetNextSibling();

			// skip over all content nodes
			while (fData && fData->GetNodeType() == IIDXMLDOMNode::kText) {
				fData = fData->GetNextSibling();
			}

			ASSERT_MSG(n == 0 || fData, "IDXMLDOMStructureOnlyIterator::advance: attempt to advance end iterator");
		}
	}

	// member data
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor fData;
};


struct IDXMLDOMVisitAllPred {
    bool operator()(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph&) const
    { 
		return true;
	}
};


class IDXMLDOMDepthFirstTreeIterator : public boost::iterator_facade<
	IDXMLDOMDepthFirstTreeIterator, // derived
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor, // value
	boost::forward_traversal_tag, // category
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor/*&*/, // reference
	int32 // difference
	>
{
public:
	IDXMLDOMDepthFirstTreeIterator() : 
	  fData()
	{}

	explicit IDXMLDOMDepthFirstTreeIterator(const boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& other) :
	  fData(other)
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		advance(1);
	}

	bool equal(IDXMLDOMDepthFirstTreeIterator const& other) const { return fData == other.fData; }

	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor& dereference() const { return const_cast<boost::graph_traits<IDXMLDOMGraph>::edge_descriptor&>(fData); }

	void advance(int32 n)
	{
		ASSERT_FAIL("IDXMLDOMDepthFirstTreeIterator::advance: not yet implemented");
	}

	// member data
	boost::graph_traits<IDXMLDOMGraph>::edge_descriptor fData;
};


template <class T>
PUBLIC_DECL std::pair<T, T>
virtual_out_edges(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


template <>
PUBLIC_DECL std::pair<IDXMLDOMOutEdgeIterator, IDXMLDOMOutEdgeIterator>
virtual_out_edges<IDXMLDOMOutEdgeIterator>(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


template <>
PUBLIC_DECL std::pair<IDXMLDOMStructureOnlyIterator, IDXMLDOMStructureOnlyIterator>
virtual_out_edges<IDXMLDOMStructureOnlyIterator>(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


template <class T>
PUBLIC_DECL T
virtual_make_iterator(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


template <>
PUBLIC_DECL IDXMLDOMOutEdgeIterator
virtual_make_iterator<IDXMLDOMOutEdgeIterator>(boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor v, const IDXMLDOMGraph& g);


// To get the root property from the graph
inline boost::graph_traits<IDXMLDOMGraph>::vertex_descriptor
get(boost::graph_tree_root_t, const IDXMLDOMGraph& g)
{
	return g.RootVertex();;
}


#endif //__IDXMLDOMGraph__


