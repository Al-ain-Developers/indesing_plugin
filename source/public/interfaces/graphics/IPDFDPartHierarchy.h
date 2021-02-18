//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFDPartHierarchy.h $ 
//   
//  Owner: Sameer Manuja
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//   
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2010 Adobe Systems Incorporated. All Rights Reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//   
//======================================================================================== 

#pragma once
#ifndef __IPDFDPartHierarchy__
#define __IPDFDPartHierarchy__

#include "PDFID.h"

typedef K2Vector<PMString> NodeNameList;
typedef uint32 CosObjID;

// opaque types
typedef struct OPAQUE_64_BITS CosObj;
class DPartNode;

/* The PDF/VT DPart hierarchy */
class IPDFDPartHierarchy : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFDPARTHIERARCHY };

		/**
			Enumerates the types of DPart nodes.
		*/
		enum DPartNodeType
		{
			/** Non-leaf DPart node contains other DPart nodes as its children */
			kNonLeafNode = 0,
			/** Leaf DPart node contains a range of PDF pages.*/
			kLeafNode
		};

		/**
			This method is called to set the names of levels of the document part hierarchy.
			@param NodeNameList nodeNames: names of the levels of the document part hierarchy.
		*/
		virtual void SetNodeNameList(const NodeNameList &nodeNames) = 0;

		/**
			This method is called to set the record level of the document part hierarchy.
			The record level is the zero based level of the document part hierarchy where
			where each DPart node of that level corresponds to a recipient record.
			@param int32 recordLevel: record level of the document part hierarchy.
		*/
		virtual void SetRecordLevel(int32 recordLevel) = 0;

		/**
			This method is called to create the root node of the document part hierarchy.
			The memory for the node is owned by the core and clients MUST NOT free it.
			@param DPartNodeType nodeType: whether to create a non-leaf or leaf node.
			@return DPartNode: root node of the document part hierarchy.
		*/
		virtual DPartNode* CreateDPartRootNode(DPartNodeType nodeType) = 0;

		/**
			This method is called to create a child DPart node of a non-leaf DPart.
			The memory for the node is owned by the core and clients MUST NOT free it.
			@param DPartNode *parentNode: the parent DPart node.
			@param DPartNodeType nodeType: whether to create a non-leaf or leaf node.
			@return: DPartNode*: the newly created child DPart node.
		*/
		virtual DPartNode* CreateChildDPart(DPartNode *parentNode, DPartNodeType nodeType) = 0;

		/**
			This method is called to add a page to a leaf DPart node.
			@param DPartNode *leafNode: the leaf DPart node.
			@param int32 pageNum: the 0-based PDF page number.
			@param bool16 lastPage: kTrue if this is the last page for this DPart.
		*/
		virtual void AddPage(DPartNode *leafNode, int32 pageNum, bool16 lastPage) = 0;

		/**
			This method is called to set the DPart Metadata (DPM) of a DPart node.
			@param DPartNode *dpartNode: the DPart node to set metadata for.
			@param CosObjID dpmDict: the DPart metadata dictionary identifier.
		*/
		virtual void SetMetadata(DPartNode *dpartNode, CosObjID dpmDict) = 0;

		/** Adobe internal use only. */
		virtual CosObj GetDPartRootCosObj() = 0;
};

#endif
