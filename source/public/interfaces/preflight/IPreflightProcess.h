//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProcess.h $
//  
//  Owner: Matt Phillips
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

#include "IPreflightObject.h"
#include "IPMUnknown.h"
#include "IPreflightProfile.h"
#include "IPreflightRuleInfo.h"
#include "PackageAndPreflightID.h"

class IdleTimer; // See IIdleTask.h
class IDocument;
class IPreflightAggregatedResults;
class IPreflightOptions;
class IPreflightSettingsChangeInfo;
class IPreflightResultRecordTable;

/** This interface sits on a preflight process boss and tracks the status of a particular
	preflight operation (either the background process we use in the UI or a synchronous
	one you create yourself via IPreflightProcessManager).

	In addition to the state/status, it also maintains a database of raw results. This
	database tracks not only the results but the entire preflight DOM used for the process.
	Normally you don't inspect the raw results directly (though you can) but rather use
	the aggregated results, which are a prettified version with user-facing strings and
	organization.

	You normally get this interface from IPreflightProcessManager. To find the processes
	for a given document, for example, use IPreflightProcessManager::GetProcessesForDocument
	or use IPreflightUtils::QueryProcessForDocument() if you want the process for the 
	document that the preflight UI is using.
*/

class IPreflightProcess : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROCESS };

	/** States a process can be in at any point in time (see GetState()).
	*/
	enum OperatingState
	{
		/** The process isn't set up with any document, or the profile has no rules active. */
		kNothingToDo,			
		/** Starting up (initially or after a clear-everything change). */
		kInitializing,
		/** To avoid thrashing, processes wait until composition is complete. */
		kWaitingForComposition,
		/** Walking DOM and building graph of object relationships. */
		kExpandingTree,
		/** Actually visiting DOM elements. */
		kVisitingTree,
		/** Results are up to date. */
		kResultsComplete
	};

	/** Processes can be paused; they still get invalidated but they won't get validation
		cycles until they're unpaused.
	*/
	enum PauseState
	{
		/** Ie not paused. */
		kRunning = 0,

		/** Document is no longer open. (This applies when book preflighting.) */
		kDocumentClosed,

		/** Preflighting is paused because the user paused it. */
		kUserPaused
	};

	/** Processes can have differing priorities depending on their state.
		See GetPriority().
	*/
	enum PriorityType
	{
		/** All results are current or there is nothing to do or the process is paused.
			No point in calling AdvanceState.
		*/
		kInactive,

		/** In a holding pattern, waiting for text composition or delayed expansion. Should
			be called on a regular basis but not with high frequency because it'll simply
			return.
		*/
		kLowPriority,

		/** There is work to be done. The higher the callback frequency, the more work will
			get done in the same amount of time.
		*/
		kHighPriority
	};

public:
	//////////////////////////////////////////////////////////////////////////////////////////

	/** Get the unique ID of this process. This number is generated automatically by the
		process manager in all cases where the process is created via the manager.

		@return The process's unique ID. This is unique within a given ID session.
	*/
	virtual uint32 GetUniqueID() const = 0;

	/** Set the unique ID of the process. This should not be called for any process that is
		created by the process manager, as changing it will affect all kinds of caches.

		@param id IN The new unique ID.
	*/
	virtual void SetUniqueID(uint32 id) = 0;

	/** Returns the modification 'time stamp' -- not really a time at all, but a change number
		that indicates whether the state of the database is the same as the last time you checked.
		Every time there's a change this number is bumped by one.

		@return The current "time stamp" identifier.
	*/
	virtual uint32 GetTimeStamp() const = 0;

	/** Gets the selector ID for the process. This is simply a way of tagging the owner of the
		process so the owner can find it later. For example preflight uses the 
		kPreflightContinuousProcessSelectorID selector to indicate the current continous 
		(background) preflighting process, as opposed to some ad-hoc process it might create 
		for other reasons.

		Note that this is purely a tagging mechanism. The process doesn't do anything with the
		selector ID except store it. 

		@return The selector.
	*/
	virtual ClassID GetSelector() const = 0;

	/** Sets the selector ID for the process. @see GetSelector for what this is.
		@param selID IN The new selector ID.
	*/
	virtual void SetSelector(ClassID selID) = 0;

	/** @return The document this preflight is associated with. Note that this does NOT use 
		IDocument because the life cycle of the process may or may not correspond to the 
		open document.
		@see IPreflightManager for document ID mapping services.
		@return The ID of the associated document. All preflight processes need a document.
	*/
	virtual PreflightDocumentID GetDocumentID() const = 0;

	/** Set the document this preflight is associated with. This is typically done only when
		the process is first created. Note that this does NOT use IDocument because the life
		cycle of the process may or may not correspond to the open document.

		@see IPreflightManager for document ID mapping services. 
		@param newDocID IN The new document ID.
	*/
	virtual void SetDocumentID(const PreflightDocumentID& newDocID) = 0;

	/** Set whether there are books associated with this process. That is, this process's
		results are used (either actively or not, in the case of a closed document) to 
		provide the current preflight errors for a document associated with a book. 
		Note that a process can in theory be associated with more than one book (if it
		happens to match multiple books' settings). Also, note that this boolean doesn't 
		mean that it isn't the active preflight for a document as well. The impetus for
		this flag is that when a process is associated with a book and the document is
		closed, the process is not automatically destroyed.

		@param newState IN kTrue if the process is book-affiliated; kFalse otherwise.
	*/
	virtual void SetIsBookProcess(bool newState) = 0;

	/** Get whether there are books associated with this process. 
		@see SetIsBookProcess.

		@return kTrue if the process is book-affiliated; kFalse otherwise.
	*/
	virtual bool IsBookProcess() const = 0;

	/** Get the auto-delete property. If true the process will be deleted automatically if the
		document (or book, if the process is associated with a book) is closed. If false, the
		process is not automatically deleted.

		@return The auto-delete state.
	*/
	virtual bool GetAutoDelete() const = 0;

	/** Set the auto-delete property. If true the process will be deleted automatically if the
		document (or book, if the process is associated with a book) is closed. If false, the
		process is not automatically deleted.

		@param newState IN The new auto-delete state.
	*/
	virtual void SetAutoDelete(bool newState) = 0;

	/** Clear all tasks, the database, everything.
	*/
	virtual void Clear() = 0;

	/** Set the options to use for this process. This method makes a COPY of the options.
		@param iOptions IN The options. Can't be nil. A copy is made so refcount is unchanged.
	*/
	virtual void SetOptions(const IPreflightOptions* iOptions) = 0;

	/** Query the current options. Note that you can't modify these options, just look at them.
		@return The current options, refcounted.
	*/
	virtual const IPreflightOptions* QueryOptions() const = 0;

	/** Get the profile used for this preflight process. Const because it may come from someplace
		that wouldn't want it to be modified.
		@return A refcounted profile interface.
	*/
	virtual const IPreflightProfile* QueryProfile() const = 0;

	/** Set the profile used for this preflight process. This references the profile, unless the
		profile is one associated with a document (as opposed to the application), in which case
		a copy of the profile is made so that the process (and all its associated data) can still 
		live with the document closed. (This is needed for book preflight, for example.)

		@param iProfile IN The profile to use.
	*/
	virtual void SetProfile(IPreflightProfile* iProfile) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////

	/** Get the current state of the process.
		@return The state.
	*/
	virtual OperatingState GetState() const = 0;

	/** Gets whether the process is paused, and if so, why.
		@return The pause state.
	*/
	virtual PauseState GetPaused() const = 0;

	/** Sets whether the process is paused, and if so, why.
		@param newState The new paused state.
	*/
	virtual void SetPaused(PauseState newState) = 0;

	/** Same as checking for 
			state != kResultsComplete 
			&& state != kNothingToDo 
			&& paused == kRunning.
		@return True if the process has something to do; False if complete or nothing to do.
	*/
	virtual bool IsActive() const = 0;

	/** Checks the current state and returns a performance priority.
		@return The priority code.
	*/
	virtual PriorityType GetPriority() const = 0;
	
	/** Give a time slice to do some work.
		@param timer IN The timer which tells the process how much time it can use. Can be nil, 
			indicating the process should work synchronously.
		@param synchronous IN Set this to true if you are calling this in a tight loop where (for
			example) the text composer will not be given any time to work; otherwise the process
			will never (or only extremely slowly) complete. When true, text composition will
			be forced synchronously prior to preflight expansion and visitation. Set this parameter
			to false if you're calling it from an idle loop where the text composer has a chance
			to operate efficiently.
	*/
	virtual void AdvanceState(IdleTimer* timer, bool synchronous) = 0;

	/** Create an aggregated version of the results. This is the version that drives the UI,
		and rules are given the opportunity to condense all results into an "aggregated" form.

		@return A refcounted aggregated results, or nil if some kind of error occurs.
	*/
	virtual IPreflightAggregatedResults* CreateAggregatedResults() const = 0;

	/** Nodes in the database. Zero means invalid. */
	typedef uint32 NodeID;

	/** A vector of node IDs, used for various "get all of X" methods. */
	typedef K2Vector<NodeID> NodeIDVector;

	/** Links are a parent-child data structure that also maintain next- and prev- of same
		parent node, and next- and prev- of same child node. Ie an arbitrary graph of nodes.
		Each link also has a type (ownership vs reference).
	*/
	typedef uint32 LinkID;

	/** This enum identifies the node category. Depending on the category you can ask
		different questions.
	*/
	typedef enum
	{
		/** General failure/invalid case. */
		kInvalidNodeType,
		/** The root of all nodes in the database. */
		kRoot,
		/** A preflight object. */
		kObject,
		/** A result node. */
		kResult,
		/** A directory node, ie children are bird of some kind of feather. */
		kDirectory
	} NodeType;

	/** This enum identifies the link type.
	*/
	typedef enum
	{
		/** General failure/invalid case. */
		kInvalidLinkType,
		/** The parent object owns the child. A node can actually have multiple owners. The
			idea is that if a node runs out of ownership parents, it is deleted. */
		kOwnership,
		/** The parent only references the child, so it won't protect it from deletion. */
		kReference,
		/** Temporary links are used for bookkeeping during the object discovery (expansion) phase. */
		kTemporary
	} LinkType;

	/** Get the root node in the database -- note that this is NOT the same as the root
		object node! The root node is a logical root, whereas the root object (ie, the document
		object) sits under the root. Remember, the database contains more than just object nodes.
		@return The ID of the root node. This is a node of type kRoot.
	*/
	virtual NodeID GetRootNode() const = 0;

	/** Get the root OBJECT node in the database -- note that this is NOT the same as the root
		node! The root node is a logical root, whereas the root object (ie, the document
		object) sits under the root. Remember, the database contains more than just object nodes.
		@return The ID of the root object node, ie the document object. This is a node of type kObject.
	*/
	virtual NodeID GetRootObjectNode() const = 0;

	/** Given a node, get its type.
		@param node IN THe node you're interested in.
		@return The node type, or kInvalidNodeType if node is invalid or error occurs.
	*/
	virtual NodeType GetNodeType(NodeID node) const = 0;

	/** Given a link, get its type.
		@param link IN THe link you're interested in.
		@return The link type, or kInvalidLinkType if link ID is invalid or error occurs.
	*/
	virtual LinkType GetLinkType(LinkID link) const = 0;

	/** Get all the parent nodes of a given node.
		@param node IN The node for which you want the parents.
		@param parents OUT Receives the list of parent nodes.
	*/
	virtual void GetParentNodes(NodeID node, NodeIDVector& parents) const = 0;

	/** Get all the child nodes of a given node.
		@param node IN The node for which you want the children.
		@param parents OUT Receives the list of child nodes.
	*/
	virtual void GetChildNodes(NodeID node, NodeIDVector& children) const = 0;

	/** Get the first parent link of a given node (note that nodes can have multiple parents).
		Once you have the link you can look "up" to the parent node, or "over" to the next parent.
		@param node IN The child node whose first parent you want.
		@return The NodeID of the parent node, or 0 if the child has no parent.
	*/
	virtual LinkID GetFirstParentLink(NodeID node) const = 0;

	/** Get the next parent link of the same child node.
		@param node IN The current parent link.
		@return The LinkID of the next parent link, or 0 if the link has no next parent sibling.
	*/
	virtual LinkID GetNextParentLink(LinkID link) const = 0;

	/** Get the first child link of a given node.
		@param node IN The node you want the first child of.
		@return The NodeID of the parent node, or 0 if the node has no children.
	*/
	virtual LinkID GetFirstChildLink(NodeID node) const = 0;

	/** Get the next child link (ie same parent, a different child).
		@param link IN The 'current' link, the one you want the next sibling of.
		@return The LinkID of the next child link, or 0 if the link has no next sibling.
	*/
	virtual LinkID GetNextChildLink(LinkID link) const = 0;

	/** Given a parent-child link, get the parent node.
		@param link IN The link you want the parent node for.
		@return The NodeID of the parent node. Will only be zero if the link is invalid (valid
			links always connect valid nodes).
	*/
	virtual NodeID GetLinkParentNode(LinkID link) const = 0;

	/** Given a parent-child link, get the child node.
		@param link IN The link you want the child node for.
		@return The NodeID of the child node. Will only be zero if the link is invalid (valid
			links always connect valid nodes).
	*/
	virtual NodeID GetLinkChildNode(LinkID link) const = 0;

	/** For object nodes, get the preflight object ID.
		@param node IN The object node you're interested in.
		@param objID OUT Receives the object ID, or an invalid ID if the node isn't valid,
			or isn't an object node.
	*/
	virtual void GetObjectNodeObjectID(NodeID node, PreflightObjectID& objID) const = 0;

	/** Obtains a vector of all results nodes.
		@param results OUT Receives the vector of result node IDs.
	*/
	virtual void GetResultNodes(NodeIDVector& results) const = 0;

	/** For a given result node ID, obtain the rule ID of that node.
	*/
	virtual PreflightRuleID GetResultNodeRuleID(NodeID resultNode) const = 0;

	/** For a given result node ID, obtain the table of recorded results.
	*/
	virtual IPreflightResultRecordTable* QueryResultNodeTable(NodeID resultNode) const = 0;

	//////////////////////////////////////////////////////////////////////////////////////////

	/** Invalidate the specified object in the process (if that object exists). This clips the
		subtree below the node and adds the node to the expansion and visitation list.

		@param objID IN The object to invalidate.
	*/
	virtual void InvalidateObject(const PreflightObjectID& objID) = 0;

	/** Invalidate the root document object. This clears out the document tree and forces a 
		complete rebuild of all results. Same result as if you got the document object ID
		and called InvalidateObject.
	*/
	virtual void InvalidateDocument() = 0;

	/** Called on a process via the process manager (usually) to indicate that settings may
		have changed for the given database. (Profile change, deleted profile, options, etc.)
		Process needs to double-check settings and/or invalidate as appropriate.

		@param iInfo IN The event information to respond to.
	*/
	virtual void OnSettingsChange(const IPreflightSettingsChangeInfo* iInfo) = 0;

	//////////////////////////////////////////////////////////////////////////////////////////

	/** This is for debugging purposes.
		@return A string describing the state of the process. Not localized.
	*/
	virtual PMString GetDescription() const = 0;

	/** This is for debugging purposes.
		@return A string describing the errors found. Not (or only partially) localized.
	*/
	virtual PMString GetResults() const = 0;

	/** This is for debugging purposes.
		@return A string containing a dump of the entire database. Not/partially localized.
	*/
	virtual PMString GetInventory() const = 0;
};

