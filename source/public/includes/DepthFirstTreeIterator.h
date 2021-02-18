//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DepthFirstTreeIterator.h $
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

#ifndef __DepthFirstTreeIterator__
#define __DepthFirstTreeIterator__


#include "boost/graph/graph_traits.hpp"
#include "boost/graph/properties.hpp"
#include "boost/iterator_adaptors.hpp"
#include "boost/optional.hpp"

#ifndef ASSERT
#include <cassert>
#define ASSERT assert
#endif


namespace boost {
	enum graph_tree_root_t { graph_tree_root = 9901 };
	enum graph_tree_end_t  { graph_tree_end  = 9902 };

	BOOST_INSTALL_PROPERTY(graph, tree_root);
	BOOST_INSTALL_PROPERTY(graph, tree_end);
} 


#if 0
/** A class to decribe the policies for a given iterator
	Templated values:
	Graph - the graph to create the iterator policies for
	VisitChildrenPredicate - In what order should this iterator visit the children
	VisitNodePredicate - Should this iterator visit itself?
*/
template <class Graph, class VisitChildrenPredicate, class VisitNodePredicate>
struct DepthFirstTreeIteratorPolicies : public boost::default_iterator_policies
{
    DepthFirstTreeIteratorPolicies() : fGraph(NULL) {}
    DepthFirstTreeIteratorPolicies(const Graph& g ) : fGraph(&g) {}

	/** use to dereference an iterator object 
		@param x - The object to dereference.
		@return - the object  this iterator points to*/
    template <class IteratorAdaptor>
    typename IteratorAdaptor::reference dereference(IteratorAdaptor x) const
    { return *get(x.base()); }

	/** Use to increment an iterator
		@param x - The object to increment*/
    template <class IteratorAdaptor>
    void increment(IteratorAdaptor& x) { advance(x, 1); }

	/** Use to advance an iterator by a given amount
		@param x - The object to advance
		@param n - The number of advancements you want to make
	*/
    template <class IteratorAdaptor, class DifferenceType>
    void advance(IteratorAdaptor& x, DifferenceType n) const;

	/*template <class IteratorAdaptor1, class IteratorAdaptor2>
    bool equal(const IteratorAdaptor1& x, const IteratorAdaptor2& y) const
    { return x.base() == y.base() && x.policies().fGraph == y.policies().fGraph; }
	*/


private:
    template <class IteratorAdaptor>
    typename boost::graph_traits<Graph>::vertex_descriptor getParentVertex(IteratorAdaptor x) const
    {
        return source(*get(x.base()), *fGraph);
    }
 
    const Graph*   fGraph;
};


/** Used to advance a graph using depth first policies.
	Depth first means that the children of a node will be
	iterated to before siblings following that node.

	  a       b
	 / \	 / \
	c   d   e   f 
	In this example (assuming that a and b have the same parent)
	the iteration order would be:
	a - c - d - b - e - f
*/
template <class Graph, class VisitChildrenPredicate, class VisitNodePredicate>
template <class IteratorAdaptor, class DifferenceType>
void DepthFirstTreeIteratorPolicies<Graph, VisitChildrenPredicate, VisitNodePredicate>::advance(IteratorAdaptor& x, DifferenceType n) const
{ 
    //
    //extern const char *name[];
    VisitChildrenPredicate should_visit_children;
    VisitNodePredicate should_visit_me;
    using namespace boost;
    //bool at_end(false);
    bool done(false);
    bool ranOutOfCandidates(false);
    while(!done){
        typename boost::graph_traits<Graph>::out_edge_iterator e, end; //a.k.a IteratorAdaptor::value_type
        boost::tie(e, end) = out_edges(target(*get(x.base()), *fGraph), *fGraph);
        ranOutOfCandidates = false;
        if(e != end && should_visit_children(target(*get(x.base()), *fGraph), *fGraph)){ //has children
            //std::cout << "x.base() 0.5 is " << name[target(get(x.base()), fGraph)] << std::endl;
            get(x.base()) = e;
            //std::cout << "x.base() 1 is " << name[target(get(x.base()), fGraph)] << std::endl;
        }else {
            bool parentIsRoot(false);
            bool foundNonSingularCandidate(false);
            ranOutOfCandidates = false;
            typename boost::graph_traits<Graph>::vertex_descriptor parentVertex;
            while(!(foundNonSingularCandidate || ranOutOfCandidates)){
                typename boost::graph_traits<Graph>::out_edge_iterator parentEndEdge(out_edges(getParentVertex(x), *fGraph).second);
                foundNonSingularCandidate = boost::next(get(x.base())) != parentEndEdge;
                if(foundNonSingularCandidate){
                    //std::cout << "x.base() 1.5 is " << name[target(get(x.base()), fGraph)] << std::endl;
                    ++get(x.base());
                    //std::cout << "x.base() 2 is " << name[target(get(x.base()), fGraph)] << std::endl;
               }else{
                    parentVertex = getParentVertex(x);
                    parentIsRoot = parentVertex == get(boost::graph_tree_root, *fGraph);
                    if(!parentIsRoot){
                        // then move up to parent and go around again
                        //std::cout << "x.base() 2.5 is " << name[target(get(x.base()), fGraph)] << std::endl;
                        typename boost::graph_traits<Graph>::in_edge_iterator in_i, in_end;
						tie(in_i, in_end) = in_edges(parentVertex, *fGraph);
						ASSERT(in_i != in_end && boost::next(in_i) == in_end);
                        typename boost::graph_traits<Graph>::out_edge_iterator out_i, out_end;
						tie(out_i, out_end) = out_edges(source(*in_i, *fGraph), *fGraph);					
						get(x.base()) = std::find(out_i, out_end, *in_i);
						ASSERT(get(x.base()) != out_end);
                        //std::cout << "x.base() 3 is " << name[target(get(x.base()), fGraph)] << std::endl;
                    }else{
                        ranOutOfCandidates = true;
                        //std::cout << "x.base() 3.5 is " << name[target(get(x.base()), fGraph)] << std::endl;
                        //++x.base();
                        //std::cout << "x.base() 4 is " << "end" << std::endl;
                   }
                }
            }
        }
        done = ranOutOfCandidates || should_visit_me(target(*get(x.base()), *fGraph), *fGraph); 
    }
    if(ranOutOfCandidates){
        /*boost::graph_traits<Graph>::out_edge_iterator e,end;
        boost::tie(e, end) = out_edges(get(boost::graph_tree_root_t(), *fGraph), *fGraph);
        x.base() = end;
		*/
		x.policies() = DepthFirstTreeIteratorPolicies<Graph, VisitChildrenPredicate, VisitNodePredicate>();
		x.base().reset();
    }


}
#endif


/** Basic object used to indicate that something (either children or self) in the graph
	should be visited. Pass this in as the template argument for objects that need this
	information.
*/
template <class Graph>
struct VisitTruePred {
    bool operator()(typename boost::graph_traits<Graph>::vertex_descriptor v, const Graph&)
    { return true; }
};


/** A default Depth first iterator

	  a       b
	 / \	 / \
	c   d   e   f 
	In this example (assuming that a and b have the same parent)
	the iteration order would be:
	a - c - d - b - e - f
*/
template <class Graph, class VisitChildrenPred =  VisitTruePred<Graph>, class VisitElementPred = VisitTruePred<Graph> >
struct DepthFirstTreeIterator {
    typedef boost::iterator_adaptor<
		    boost::optional<typename boost::graph_traits<Graph>::out_edge_iterator> /* DepthFirstTreeIterator */, // derived (???)
		    boost::optional<typename boost::graph_traits<Graph>::out_edge_iterator>, // base
            typename boost::graph_traits<Graph>::edge_descriptor ,  // value
            boost::forward_traversal_tag, // category or traversal
            typename boost::graph_traits<Graph>::edge_descriptor /*&*/, // reference
            size_t // difference
        > type;
};


#endif //__DepthFirstTreeIterator__


