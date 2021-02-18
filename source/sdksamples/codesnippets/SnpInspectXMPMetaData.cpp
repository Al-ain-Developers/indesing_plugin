//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectXMPMetaData.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IDocument.h"
#include "IMetaDataAccess.h"
#include "IMetaDataIterator.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li Inspects XMP MetaData in a document, using the InDesign/InCopy API
 * 		wrappers for the XMP ToolKit.
 * 
 *  To find out if the code in this codesnippet will satisfy your use case, 
 * 	refer to the set of use cases documented in SnpPerformXMPCommands.
 * 
 * 	For XMP technical specifications, refer to the MetaDataToolkit PDF at 
 * 	the XMP Toolkit Download page:
 * 		http://partners.adobe.com/asn/developer/xmp/download/
 * 
 *  @ingroup sdk_snippet
 * 	@ingroup sdk_architecture
 *	
 */
class SnpInspectXMPMetaData
{
public:
	/** Shows how to navigate MetaData using the IMetaDataAccess interface.
	 * 
	 * 	This uses the following interfaces:
	 * 	\li IMetaDataAccess interface, which wraps MetaXAP (XMP toolkit).
	 * 	\li	IMetaDataPaths interface, which wraps XAPPaths (XMP toolkit).
	 * 
	 * 	@param[in] targetObject A pointer to an interface on a boss class with 
	 * 		the MetaData model (e.g. kDocBoss, kMetaDataBoss)
	 *  @param[in] namespaceToIterate (optional) Specifies the XMP namespace 
	 * 		to iterate. (Default: "", which means visit all nodes)
	 * 	@param[in] pathToIterate (optional) Specifies the XMP path to 
	 * 		iterate. (Default: "", which means visit all nodes)
	 *  @param[in] iterOptions (optional) Specifies the iterator options 
	 * 		(Default: IMetaDataAccess::kIterJustChildren) This is ignored if both namespace and path
	 * 		are empty.
	 *  @return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode InspectMetaData(IPMUnknown* targetObject, 
							  const PMString& namespaceToIterate = "", 
							  const PMString& pathToIterate = "", 
							  const IMetaDataAccess::IteratorOptions& iterOptions = IMetaDataAccess::kIterJustChildren);


	/** Inspects a specific node, identified by a namespace and path.
	 * 	@param[in] metaDataAccess The IMetaDataAcceess interface to use to 
	 * 		access metadata.
	 * 	@param[in] nspace The metadata namespace to inspect.
	 * 	@param[in] path The metadata path to inspect.
	 * 	@param[out] value The value at the namespace and path.
	 * 	@param[in] iterOptions Specifies the iterator options.
	 * 	@return kSuccess if success, kFailure otherwise.
	 */
	ErrorCode InspectNode(IMetaDataAccess* metaDataAccess, 
						  const PMString& nspace, const PMString& path,
						  PMString& value, const IMetaDataAccess::IteratorOptions& iterOptions = IMetaDataAccess::kIterJustChildren);

	/** Gets all XMP namespaces in the target object.
	 * 	@param targetObject IN A pointer to an interface on a boss class with 
	 * 		the MetaData model (e.g. kDocBoss, kMetaDataBoss)
	 * 	@return A list of namespaces. If empty, there was something wrong, 
	 * 		or there was no XMP metadata in this target object.
	 */
	K2Vector<PMString> GetAllXMPNameSpaces(IPMUnknown* targetObject);
	
	/** Gets all XMP paths in the target object.
	 * 	@param targetObject IN A pointer to an interface on a boss class with 
	 * 		the MetaData model (e.g. kDocBoss, kMetaDataBoss)
	 * 	@return A list of paths. If empty, there was something wrong, 
	 * 		or there was no XMP metadata in this target object.
	 */
	K2Vector<PMString> GetAllXMPPaths(IPMUnknown* targetObject);

};

/* InspectMetaData
*/
ErrorCode SnpInspectXMPMetaData::InspectMetaData(IPMUnknown* targetObject, 
												 const PMString& namespaceToIterate, 
												 const PMString& pathToIterate, 
												 const IMetaDataAccess::IteratorOptions& iterOptions)
{
	ErrorCode status = kFailure;
	do
	{
		int32 nodesVisited = 0;
		PMString value;

		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}
		
		InterfacePtr<IMetaDataAccess> metaDataAccess(targetObject, UseDefaultIID());
		if (metaDataAccess == nil)
		{
			ASSERT_FAIL("metaDataAccess is nil!");
			break;
		}
		

		if ( (namespaceToIterate.empty() == kFalse) &&
             (pathToIterate.empty() == kFalse) )
		{
			// visit a specific XMPPath 
			status = this->InspectNode(metaDataAccess, namespaceToIterate, pathToIterate, 
									   value,iterOptions);
		}
		else
		{
			// use the new XMP iterator		
		
			// visit all XMPPaths
			InterfacePtr<IMetaDataIterator> metaDataPaths(metaDataAccess->Enumerate());
			if (metaDataPaths == nil)
			{
				ASSERT_FAIL("metaDataPaths is nil!");
				break;
			}
	
			// now, assume success
			status = kSuccess;
	
			PMString nspace, path,value;
			IMetaDataAccess::IteratorOptions options;
			// iterate thru all paths
			while (metaDataPaths->Next(nspace,path,value,&options))
			{
				
				SNIPLOG("MetaData: (nspace, path, value, options) = [\"%s\", \"%s\", \"%s\", 0x%X]\n", 
						nspace.GetPlatformString().c_str(), path.GetPlatformString().c_str(), 
						value.GetPlatformString().c_str());
	
					++nodesVisited;
			}
			SNIPLOG("Number of nodes visited: %d", nodesVisited);
			
		}

	} while (false);
	return status;
}


ErrorCode SnpInspectXMPMetaData::InspectNode(IMetaDataAccess* metaDataAccess, 
											 const PMString& nspace, const PMString& path,
											 PMString& value,const IMetaDataAccess::IteratorOptions& iterOptions)
{
	ErrorCode status = kFailure;
	do {

		if (metaDataAccess == nil || 
			nspace.empty() || 
			path.empty()) 
		{
			ASSERT_FAIL("One or more preconditions not met - exiting");
			break;
		}

		// get the metadata value and features at that namespace and path (base case)
		if (metaDataAccess->Get(nspace, path, value))
		{
			// dump data
			SNIPLOG("MetaData: (ns, path, value, features) = [\"%s\", \"%s\", \"%s\"]\n", nspace.GetPlatformString().c_str(), path.GetPlatformString().c_str(), value.GetPlatformString().c_str());
			status = kSuccess;
			break;
		}

		// Get() returned an error - so this nspace/path might be a collection.
		// Iterate over just one level

		// Use the new XMP iterator		
		// visit all XMPPaths at this level
		InterfacePtr<IMetaDataIterator> metaDataIterator(metaDataAccess->Enumerate(nspace, path, iterOptions));
		if (metaDataIterator == nil)
		{
			ASSERT_FAIL("Could not get IMetaDataPaths");
			break;
		}	

		// now, assume success
		status = kSuccess;
		
		PMString nspace_inner, path_inner, val;
		IMetaDataAccess::IteratorOptions options;
		// iterate thru all paths
		while (metaDataIterator->Next(nspace_inner,path_inner,val,&options)) 
		{
			
			// dump data
			SNIPLOG("MetaData: (ns, path, value, features) = [\"%s\", \"%s\", \"%s\", 0x%X]\n", 
					nspace_inner.GetPlatformString().c_str(), path_inner.GetPlatformString().c_str(), 
					val.GetPlatformString().c_str());
			metaDataIterator->Skip(IMetaDataAccess::kIterSkipSubtree);
		}
	} while (false);
	return status;

}

/* GetAllXMPNameSpaces
 */
K2Vector<PMString> SnpInspectXMPMetaData::GetAllXMPNameSpaces(IPMUnknown* targetObject)
{
	K2Vector<PMString> namespaces;
	namespaces.clear();
	const int16 depthToIterate = 0;

	do
	{
		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}
		
		InterfacePtr<IMetaDataAccess> metaDataAccess(targetObject, UseDefaultIID());
		if (metaDataAccess == nil)
		{
			ASSERT_FAIL("metaDataAccess is nil!");
			break;
		}

		// Visit all namespaces
		// Use the new XMP iterartor		
		InterfacePtr<IMetaDataIterator> metaDataIterator(metaDataAccess->Enumerate());
		if (metaDataIterator == nil)
		{
			ASSERT_FAIL("metaDataIterator is nil!");
			break;
		}
		PMString nspace, path, value;
		IMetaDataAccess::IteratorOptions options;
		while (metaDataIterator->Next(nspace,path,value,&options)) 
		{
			K2Vector<PMString>::iterator b = namespaces.begin();
			K2Vector<PMString>::iterator e = namespaces.end();
			if (std::find(b, e, nspace) == e) 
			{
				// a new namespace! add it to the list
				namespaces.push_back(nspace);
			}
		}		
	} while(false);
	return namespaces;
}

/* GetAllXMPPaths
 */
K2Vector<PMString> SnpInspectXMPMetaData::GetAllXMPPaths(IPMUnknown* targetObject)
{
	K2Vector<PMString> paths;
	paths.clear();
	do
	{
		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}
		
		InterfacePtr<IMetaDataAccess> metaDataAccess(targetObject, UseDefaultIID());
		if (metaDataAccess == nil)
		{
			ASSERT_FAIL("metaDataAccess is nil!");
			break;
		}
		// Visit all namespaces
		// Use the new XMP iterator
		
		InterfacePtr<IMetaDataIterator> metaDataIterator(metaDataAccess->Enumerate());
		if (metaDataIterator == nil)
		{
			ASSERT_FAIL("metaDataIterator is nil!");
			break;
		}
		PMString nspace, path, value;
		IMetaDataAccess::IteratorOptions options;
		while (metaDataIterator->Next(nspace,path,value,&options)) 
		{
			K2Vector<PMString>::iterator b = paths.begin();
			K2Vector<PMString>::iterator e = paths.end();
			if (std::find(b, e, path) == e)
			{
				// a new namespace! add it to the list
				paths.push_back(path);
			}
		}
		
	} while(false);
	return paths;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpInspectXMPMetaData available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerInspectXMPMetaData : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerInspectXMPMetaData(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerInspectXMPMetaData(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
		
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Constructor.
*/
_SnpRunnerInspectXMPMetaData::_SnpRunnerInspectXMPMetaData(void) : SnpRunnable("InspectXMPMetaData")
{
	this->SetDescription("Inspects XMP MetaData on the front document");
	this->SetPreconditions("A front document must be open.");
	this->SetCategories("sdk_snippet, sdk_architecture");
}

/* Destructor.
*/
_SnpRunnerInspectXMPMetaData::~_SnpRunnerInspectXMPMetaData(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerInspectXMPMetaData::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
		if (doc == nil) 
		{
			break;
		}
		// if we got here, we can run.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInspectXMPMetaData::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
		if (doc == nil) 
		{
			SNIPLOG("You do not have a document open.  This snippet requires a front document.");
			break;
		}

		SnpInspectXMPMetaData instance;

		// get user choices
		Utils<ISnipRunParameterUtils> parameterUtils;

		PMString prompt = "Do you want to inspect all meta data on this document?";
		K2Vector<PMString> tfChoices;
		tfChoices.clear();
		tfChoices.push_back(PMString("No")); // kFalse
		tfChoices.push_back(PMString("Yes")); // kTrue
		bool16 inspectAll = (bool16)parameterUtils->GetChoice(prompt, tfChoices, (int32)kTrue);
		if (parameterUtils->WasDialogCancelled()) 
		{
			// cancelled
			break;
		}
		
		
		//int16 depthToIterate = 0;

		if (inspectAll == kTrue) 
		{
			// inspect all metadata
			prompt = "Specify a depth to inspect (0 = all the way to leaf).";
			//int32 defaultDepth = 0;
			//depthToIterate = (int16) parameterUtils->GetInt32(prompt, defaultDepth, 0, 9999);
			if (parameterUtils->WasDialogCancelled()) 
			{
				// cancelled
				break;
			}
			
			status = instance.InspectMetaData(doc, kNullString, kNullString, IMetaDataAccess::kIterOmitQualifiers);
		}
		else
		{
			// get the metadata namespace path from the user.
			prompt = "Specify metadata namespace to inspect.";
			K2Vector<PMString> namespaces = instance.GetAllXMPNameSpaces(doc);
			int32 defaultNSpace = 0; 
			int32 nspaceChoice = parameterUtils->GetChoice(prompt, namespaces, defaultNSpace);
			if (parameterUtils->WasDialogCancelled()) 
			{
				// cancelled
				break;
			}
			PMString nspace = namespaces[nspaceChoice];

			prompt = "Specify metadata path to inspect. (Hint: Inspect all metadata first to see available paths.)";
			PMString defaultPath(""); 
			PMString path = parameterUtils->GetPMString(prompt, defaultPath);
			if (parameterUtils->WasDialogCancelled()) 
			{
				// cancelled
				break;
			}
			if (path.empty()) 
			{
				// cancelled
				SNIPLOG("Path is empty - exiting...");
				break;
			}

			// inspect a specific metadata namespace and path
			status = instance.InspectMetaData(doc, nspace, path, IMetaDataAccess::kIterJustChildren);
		}

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerInspectXMPMetaData instance_SnpRunnerInspectXMPMetaData;
DEFINE_SNIPPET(_SnpRunnerInspectXMPMetaData) 	

// End, SnpInspectXMPMetaData.cpp

