//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTreeViewMgr.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __CTreeViewMgr_h__
#define __CTreeViewMgr_h__


#include "ITreeViewMgr.h"
#include "IControlView.h"

#include "K2Vector.h"
#include "KeyValuePair.h"
#include "NodeID.h"
#include <map>

class ITreeViewHierarchyAdapter;
class ITreeViewController;
class ITreeViewWidgetMgr;

#pragma export on

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
class DV_WIDGET_DECL CTreeViewMgr : public ITreeViewMgr
{
public:
	CTreeViewMgr(IPMUnknown *boss);
	~CTreeViewMgr();
	
	virtual void		ChangeRoot( bool16 widgetHeightIsConstant );		

	virtual void		NodeAdded( const NodeID& nodeAdded );		
	virtual void		NodesAdded( const NodeIDList&	nodesAdded );		
	virtual void		BeforeNodeDeleted( const NodeID& nodeDeleted );		
	virtual void		BeforeNodesDeleted( NodeIDList& nodesDeleted );		
	virtual void		NodeMoved( const NodeID& nodeMoved, const NodeID& oldParent  );		
	virtual void		NodeChanged( const NodeID& nodeChanged, bool16 childrenChangedAlso, int32 message = 0 );		
	virtual void		ScrollToNode( const NodeID& nodeDeleted, ScrollWhere	whereToScroll );		

	virtual bool16		IsNodeExpanded( const NodeID& nodeInQuestion ) const;	
	virtual bool16		IsNodeExpanded(IControlView* widget) const;	
	virtual void		ExpandNode( const NodeID& nodeToExpand, bool16 expandAllDescendants = kFalse );	
	virtual void		CollapseNode( const NodeID& nodeToCollapse, bool16 collapseAllDescendants = kFalse );	

	virtual void		HandleScroll( int32 amount, bool16 scrollVertical );
	virtual	void		HandleResize();

	virtual	void		ScrollUp();
	virtual	void		ScrollDown();

	virtual NodeID_rv	Search( const PMString& partialNodeName ) const;
	virtual NodeID_rv	Search( const NodeID& nodeToSearch ) const;

	virtual IControlView* QueryWidgetFromNode( const NodeID& node ) const;	

	virtual	void		Purge(int32 level);

	virtual	void		ClearTree(bool16 clearExpandedNodeList);
	virtual	void		ReadWrite(IPMStream *s, ImplementationID prop);

	enum { kAbove = 1, kBelow = -1 };
	static	int32 		AboveOrBelow(ITreeViewHierarchyAdapter* adapter, const NodeID& referenceNode, const NodeID& nodeInQuestion);
	static void			PurgeMemory(int32 level, void *refPtr);
	virtual	void		ArrangeWidgets();

	virtual	void		RefreshSubTree(const NodeID& subTreeRoot, bool16 includeEntireHier);
	virtual PMRect 		GetViewableArea();
	virtual PMPoint		GetSizeNeededWihtoutScrollbar();
    enum { kNodeChangedMsgNotSet = 0, kNodeChangedMsgChangeAll = -1 };

	void AllowPurge()
		{ ++fAllowPurge; }
	void DisallowPurge()
		{ --fAllowPurge; }
	bool IsPurgeAllowed() const
		{ return (fAllowPurge == 0); }

protected:
	bool16					ExpandNodeRecurse( const NodeID& nodeToExpand, bool16 expandAllDescendants = kFalse);	
	bool16					CollapseNodeRecurse( const NodeID& nodeToCollapse, bool16 collapseAllDescendants = kFalse );
	void					PlaceWidgets(  );
								// framePositionLookup sorted
	void 					DeselectNode(  const NodeID& nodeToDeselect, ITreeViewController* controller, const ITreeViewHierarchyAdapter* adapter, bool16 notifyOfChange = kTrue);
	virtual void			ScrollHorizontal( int32 amount, bool16 forceRedraw = kTrue );
	virtual void			ScrollVertical( int32 amount, bool16 forceRedraw = kTrue );
	virtual void	 		AdjustTreeScrollerSize( PMPoint scrollerSize );
	virtual PMReal 			AdjustScrollIncrements( WidgetID whichScrollBar, const PMReal& scrollerTop, const PMReal& scrollerBottom, const PMReal& viewSize );
	void					AdjustScrollValue(bool16 vertical = kTrue);
	PMReal					AdjustScrollerPosition( );
//	PMPoint 				RecursiveGetSize( const NodeID& node, bool16 includeThisNodeInSize = kTrue, const NodeIDList* ignoreTheseNodes = nil  );
	IControlView*			QueryWidgetForNode(const NodeID& node);
	IControlView*			QueryCachedWidget( WidgetID typeOfWidget );
	void 					AdjustHorizSize( IControlView* widget );
	void					DisposeWidget(IControlView*);
	void 					DeleteWidget(IControlView*	widget);
	NodeID_rv				GetNodeIDFromInterface(IControlView*	widget) const;
	bool16 					AncestorsAreExpanded(const NodeID& node);
	bool16					IsAncestor(const NodeID& possibleAncestor, const NodeID& possibleDescendant) const;
	typedef enum { kNodeAdded, kNodeChanged, kNodeDeleted } ChangeType;
	PMReal					GetNewScrollerWidth( const PMReal& sizeOfChangingNode, const NodeIDList* changingNodes, ChangeType typeOfChange );
	void					ExpandToShowNode( const NodeID& scrollToNode );
	virtual void			MoveScroller( const PMPoint& moveTo );
	class TreeNode;
	TreeNode*				GetTreePtrFromNodeID( const NodeID& node, bool16 buildTreeToIncludeNode = kFalse ) const;
	void					SetRepositionWidgetsFlag( bool16 reposition );

#ifdef DEBUG
	void  					TestTree( const NodeID& node);
	void					CheckNode(const NodeID& node, const char *calledFrom, int32 i = -1) const;
#else
	inline void  			TestTree( const NodeID& ) {}
	inline void				CheckNode(const NodeID& , const char *, int32 = -1) const {}
#endif			

#ifdef TESTCODE
	void 					CheckWidgetPtrs( ) const;
#else
	inline void 			CheckWidgetPtrs( ) const {}
#endif			


	IControlView*			fTreeScrollerView;
	IControlView*			fVScrollBarView;
	IControlView*			fHScrollBarView;
	int32					fVThumbScrollIncrement;

private:

//	K2Vector<KeyValuePair<NodeID, int32> >	fNodeToWidgetPositionLookup;	// sorted
//	NodeIDList	fExpansionLookup;	// sorted
	bool16							fDisplayRootNode;	
	bool16					fRootIsValid;  //We use this so that flag that calls after ClearTree() will fail until ChangeRoot is called,
											//specifically, we want to ignore resize calls.  We can't set the root to invalid because that
											// would cause ChangeRoot() calls with the same root to lose the expansion info
	bool16					fRepositionWidgetsFlag;
	bool16					fSomeNodesChangedFlag;
	bool16					fDirtyScrollerSize;
	bool16					fCheckForReentry;
	int32					fAllowPurge;
	DECLARE_HELPER_METHODS()

	//Widget Cache
	typedef K2Vector<IControlView*> WidgetList;
	K2Vector<KeyValuePair<WidgetID, WidgetList> >	fWidgetCache;		// sorted
		
	friend	class TreeNodeTraverser;
	friend	class TreeNodeHelper;
	
	class TreeNode
	{
		public:
			TreeNode(const NodeID& nodeID);
			TreeNode(const NodeID& nodeID, const PMPoint& nodeSize);
			TreeNode(IPMStream* stream, TreeNode* parent );
			// use this as the Destuctor
			void	Delete( bool16 deselect = kTrue );

			TreeNode* 			AddChild( int32	childIndex, const NodeID& node, bool16 ignoreExpandedState = kFalse);
			void	 			AddChild( int32	childIndex, TreeNode* node );
			TreeNode* 			Remove( );
			TreeNode* 			RemoveChild( int32 childIndex );
			TreeNode* 			GetParent( ) const { return fParent; }
			
			void				Expand();
			void				Collapse();
			bool16				IsExpanded() const { return fFlags & kExpanded; }
			
            enum { kInvalidSize = -1 };
			virtual const PMPoint&		GetSize() const;  // Dimensions of this node alone, not including child widgets
			const PMPoint&		GetFamilySize() const;	// Dimension of this parent widget, including child widgets
			void				DirtyFamilySize();
			void				DirtySize();
			const PMReal&		GetIndent() const;  // overall indent
			void				SetIndent(const PMReal& newIndent) { fIndent = newIndent; }
			
			void				PlaceWidgets( const PMRect& viewableArea );
			bool16				PositionWidgets( PMReal& location, const PMRect& viewableArea, K2Vector<IControlView*>& reusedViewList, K2Vector<KeyValuePair<TreeNode*, PMReal> >&	needWidgetList );
			PMReal 				GetVerticalPosition( ) const;
			IControlView*		QueryWidget( ) const;
			void 				ClearWidgets( bool16 recursive = kFalse);
			void				RemoveFromLookup( bool16 recursive = kFalse );

			bool16				HasSubTree() const { return fChildren.size() > 0; }
			void				BuildSubtree();
			const NodeID&		GetNodeID() const { return fNodeID; }
			void 				ReconcileTreeChanges( bool16 includeEntireHier = kTrue );

			void				DirtyWidgetData(int32 messageToWidgetMgr = kNodeChangedMsgNotSet);
			void				RecursiveDirtyWidgetData( int32 messageToWidgetMgr = kNodeChangedMsgNotSet );
			bool16				IsWidgetDataDirty() const { return fFlags & kDirtyWidgetData; }
			void				ReapplyWidgetData( );

			void				ReadWrite(IPMStream* stream);
			void 				CheckWidgetPtrs(  ) const;

			virtual CTreeViewMgr*				GetTreeViewMgr() const;
			virtual const ITreeViewWidgetMgr*	GetTreeViewWidgetMgr() const;
						
		protected:
			TreeNode();
			~TreeNode();
			
			NodeID	fNodeID;
            enum { kExpanded = 1, kDirtyFamilySize = 2, kDirtyWidgetData = 4, kDirtySize = 8 };
			mutable int16	fFlags;
			mutable PMPoint	fMySize;
			mutable PMPoint	fFamilySize;
			PMReal	fIndent;
			K2Vector<TreeNode*>	fChildren;
			TreeNode*	fParent;
			IControlView*	fMyWidget;
	
	};
	
	class RootTreeNode : public TreeNode
	{
		public:
			RootTreeNode(const NodeID& nodeID, CTreeViewMgr* widgetMgr, bool16 isHiddenRootNode);
			RootTreeNode(IPMStream* stream, CTreeViewMgr* widgetMgr);
		
			const PMPoint&				GetSize() const;  // Dimensions of this node alone, not including child widgets
			CTreeViewMgr*				GetTreeViewMgr() const { return fTreeViewMgr; }
			const ITreeViewWidgetMgr*	GetTreeViewWidgetMgr() const { return fTreeViewWidgetMgr; }
			
		protected:
			CTreeViewMgr*				fTreeViewMgr;
			const ITreeViewWidgetMgr*	fTreeViewWidgetMgr;
	};
	
	friend	class TreeNode;
	friend class CheckReentryUtility;
	TreeNode*		fRootNode;
	mutable K2Vector< KeyValuePair<PMString, NodeID> >	fTreeNodeNameList;
	mutable std::map<NodeID, TreeNode*>	fNodeToTreeLookup;	

	public:
		virtual void		ScrollVerticalAbsoluteAmount(int32 amount, bool16 forceRedraw = kTrue);
};

#pragma export off

#endif
