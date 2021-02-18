//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SelectionASBTemplates.tpp $
//  
//  Owner: Michael Martz
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
//  
//  Note:		Most of the functions in an Integrator implementation simply dispatch to the
//  _same_ function on one or more CSBs with the _same_ parameters. A set of template files 
//  were created to eliminate the boilerplate code from the member functions of ASB implementations. 
//  
//  There are 2 pieces to the template solution. The first, is a Functor object,
//  which bundles the member function and the parameters for delayed invocation.  It is created with
//  the make_functor(). There are several overloaded versions of this routine that get initialized
//  with a member function (typically the same function that you are in within the ASB), a return 
//  type and a list of parameters (The details are in Functor.tpp and utilize templates extensively - you
//  shouldn't need to concern yourself with the details). The Functor object is then passed as a parameter
//  to one of the functions defined below along with a few other parameters (i.e. the "this" pointer and 
//  an interface IID).
//  
//  ASB member functions can usually be divided into 2 categoties Can..() and Do...(). The 
//  suite allows a client to ask wheter something is enabled or can be done (e.g. CanRotate()
//  HasSkewX_Ability()). Typically the ASB member function will use an "Any" or "All" policy. (An
//  Any policy returns true if any of the enabled CSBs can do what is asked. An All policy
//  requires that each enabled CSB returns true.
//  
//  For example:
//  bool16 GeometrySuiteASB::CanChangeHeight (bool16 param_1) has an "Any" policy.
//  
//  The first step is to create the Functor object:
//  f = make_functor(&IGeometrySuite_New::CanChangeHeight, param_1);
//  
//  Then call the template member fucntion for the proper policy:
//  return (AnyCSBSupports (f, this));
//  
//  It is strongly suggested that the Suite interface header support UseDefaultIID ().
//  Optionally, the IID can be pass in as the last parameter.
//  
//  Optimized to a single line:
//  return (AnyCSBSupports (make_functor(&IGeometrySuite_New::CanChangeHeight, param_1), this));
//  
//  Currently there are 4 functions:
//  AnyCSBSupports - Do any enabled CSBs return true for the specified member function.
//  AllCSBSupports - Do all enabled CSBs return true for the specified member function.
//  Process - Create a sequence and call each CSB to process it's commands.
//  CallEach - Call each enabled CSB's member function (e.g. TransformSuiteASB::GetRotation()).
//  
//========================================================================================

	#ifndef _Integrator_Templates_
	#define _Integrator_Templates_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "Functor.tpp"
	#include "IIntegratorTarget.h"
	#include "ErrorUtils.h"
//================================================================================================
//________________________________________________________________________________________________
//	TEMPLATE FUNCTIONS
//________________________________________________________________________________________________
//________________________________________________________________________________________________
//	DESCR:		Do any of the CSB's support this request? As soon as one if found, return.
//	
//	RETURNS:	kTrue / kFalse.
//________________________________________________________________________________________________
template <typename Functor>
typename Functor::result_type AnyCSBSupports (Functor f, typename Functor::argument_type object, PMIID iid)
	{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (object, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (iid));
	bool16											can = kFalse;

	if (!selectionSuites->empty())
		{
		for (int32 suitesIndex = selectionSuites->size () - 1; suitesIndex >= 0; suitesIndex--)
			{
			typedef typename Functor::argument_type argument_type;
			argument_type		iUnknown = static_cast<argument_type>(static_cast<IPMUnknown*>((*selectionSuites) [suitesIndex]));
			
			can = f(iUnknown);
			if (can)
				{
				break;
				}
			}
		}

	return (can);
	}

template <typename Functor>
typename Functor::result_type AnyCSBSupports (Functor f, typename Functor::argument_type object)
	{
	return (AnyCSBSupports (f, object, GetDefaultIID (object)));
	}
	
//________________________________________________________________________________________________
//	DESCR:		Do all of the CSB's support this request? As soon as one doesn't, return.
//	
//	RETURNS:	kTrue / kFalse.
//________________________________________________________________________________________________
template <typename Functor>
typename Functor::result_type AllCSBSupports (Functor f, typename Functor::argument_type object, PMIID iid)
	{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (object, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (iid));
	bool16											can = kTrue;

	if (!selectionSuites->empty())
		{
		for (int32 suitesIndex = selectionSuites->size () - 1; suitesIndex >= 0; suitesIndex--)
			{
			typedef typename Functor::argument_type argument_type;
			argument_type		iUnknown = static_cast<argument_type>(static_cast<IPMUnknown*>((*selectionSuites) [suitesIndex]));
			
			can = f(iUnknown);
			if (! can)
				{
				break;
				}
			}
		}

	return (can);
	}

template <typename Functor>
typename Functor::result_type AllCSBSupports (Functor f, typename Functor::argument_type object)
	{
	return (AllCSBSupports (f, object, GetDefaultIID (object)));
	}

//________________________________________________________________________________________________
//	DESCR:		Call each CSB suite to process the request, wrapping the entire call in a sequence.
//
//	NOTE:		Abort the sequence if there were any errors.
//	
//	RETURNS:	Error Code.
//________________________________________________________________________________________________
template <typename Functor>
typename Functor::result_type Process (Functor f, typename Functor::argument_type object, PMIID iid)
	{
	InterfacePtr<const IIntegratorTarget> 					iIntegratorTarget (object, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (iid));
	ErrorCode												errorCode = kSuccess;

	if (!selectionSuites->empty())
		{
		CmdUtils::SequenceContext		sequenceContext;
		
		for (int32 i = selectionSuites->size () - 1; i >= 0 && errorCode == kSuccess; i--)
			{
			typename Functor::argument_type		iUnknown = static_cast<typename Functor::argument_type>(static_cast<IPMUnknown*>((*selectionSuites) [i]));

			sequenceContext.State ();
			errorCode = f(iUnknown);
			ErrorUtils::PMSetGlobalErrorCode(errorCode);
			}
		}
			
	return (errorCode);
	}

template <typename Functor>
typename Functor::result_type Process (Functor f, typename Functor::argument_type object)
	{
	return (Process (f, object, GetDefaultIID (object)));
	}
	
//________________________________________________________________________________________________
//	DESCR:		Call each enabled CSB's like-named member function. 
//________________________________________________________________________________________________
template <typename Functor>
void CallEach (Functor f, typename Functor::argument_type object, PMIID iid)
	{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (object, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (iid));

	if (!selectionSuites->empty())
		{
		for (int32 i = selectionSuites->size () - 1; i >= 0; i--)
			{
			typename Functor::argument_type		iUnknown = static_cast<typename Functor::argument_type>(static_cast<IPMUnknown*>((*selectionSuites) [i]));
			
			f(iUnknown);
			}
		}
	}
	
template <typename Functor>
void CallEach (Functor f, typename Functor::argument_type object)
	{
	CallEach (f, object, GetDefaultIID (object));
	}

#endif // _Integrator_Templates_