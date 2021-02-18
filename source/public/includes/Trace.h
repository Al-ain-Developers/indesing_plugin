//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Trace.h $
//  
//  Owner: EricM
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
#ifndef __TRACE_H__
#define __TRACE_H__

// Trace takes the same arguments as printf and uses vsprintf
// to create a buffer that is then sent to the trace log,
// eventually to appear in the log or the window.


#include "PMTypes.h"

#if defined(DEBUG)
#ifndef ID_ENABLE_DEBUGGING
#error ID_ENABLE_DEBUGGING is not defined in DEBUG.
#endif
#endif

#if defined(ID_ENABLE_DEBUGGING)
	#include <string>
	#include <boost/mpl/or.hpp>
	#include <boost/utility/enable_if.hpp>
	#include <boost/type_traits.hpp>
	#include <utility>	// For std::pair
	#include <vector>

	namespace Trace
	{
		/** This is the actual trace implementation. The other TRACExxx macros use this.
            @param checkCategory [IN] - whether to check the category.
            @param category [IN] - category of the trace.
			@param format [IN] - format for TRACE. Accepts the same format specifiers as printf.
		*/
		RUNTIME_DECL void TraceImpl(bool16 checkCategory, const char* category, const char* filename, const int32 lineNo, const char* format, ...);

		// get_return_type helpers deduce the return type from the argument
		template<typename A, typename Enabler = void>
		struct get_return_type;

		// Generic implementation for built-in types.
		template<typename A>
		struct get_return_type<A,
			typename boost::enable_if<boost::mpl::or_<boost::is_arithmetic<A>, boost::is_pointer<A>, boost::is_enum<A> > >::type >
		{
			typedef A type;
		};

		// Specialization for std::string
		template<>
		struct get_return_type<std::string>
		{
			typedef const char* type;
		};

		// Specialization for UID
		template<>
		struct get_return_type<UID>
		{
			typedef uint32 type;
		};



		// format_arg helpers: extract the correct value from the argument

		// Generic form for built in types
		template<typename A>
		inline typename get_return_type<A>::type format_arg(A const& a)
		{
			return a;
		}

		// Specialization for std::string
		template<>
		inline const char* format_arg<std::string>(std::string const& a)
		{
			return a.c_str();
		}

		// Specialization for UID
		template<>
		inline uint32 format_arg<UID>(UID const& a)
		{
			return a.Get();
		}

		//-----------------------

		/** Category of a trace. Utility class used by TraceFlow.
		*/
		class RUNTIME_DECL TraceCategory
		{
		public:
			~TraceCategory();

			TraceCategory();
			explicit TraceCategory(const char* str);
			TraceCategory(const TraceCategory& rhs);

			TraceCategory& operator=(TraceCategory rhs);

		public:
			inline const char* c_str() const
			{
				return fText;
			}

			inline friend void swap(TraceCategory& left, TraceCategory& right){
				using std::swap;
				swap(left.fText, right.fText);
				swap(left.fLen, right.fLen);
			}
			
			bool16 		operator==(const TraceCategory& rhs) const;
			bool16 		operator<(const TraceCategory& rhs) const;

		protected:
			char*	fText;
			size_t	fLen;
		};

	
		/** Utility class used by TRACEFLOW macro. Keeps track which categories of trace are enabled.
		*/
		class RUNTIME_DECL TraceFlow
		{
		public:
			typedef std::pair<TraceCategory, bool16> SEntry;
			typedef std::vector<SEntry> SEntryArray;

			enum {kMaxCategories = 512};

			//	API
		public:
			static	void 		EnableCategory(const char* category, bool16 enable = true);
			static 	bool16 		IsCategoryEnabled(const char* category);
			static void			ClearAll();
			static void			RemoveAllDisabled();

			// Retrieves an alphabetically sorted copy of the registered entries with the Traceflow
			static void GetEntries(SEntryArray& entries);

			//	Internal API
		protected:
			
			typedef SEntry*		iterator;
		
			static void AddCategory(TraceCategory const& newCategory, bool16 enable);
			static void RemoveCategory(iterator category);
			
			static 	iterator 	__begin();
			static 	iterator 	__end();
		};


	} // End namespace Trace

	// This line kicks off the Trace overloads generator
//	#include "TraceGenerator.h"

	// To shorten the compilation time, we include the generated (pre-processed) file here
	#include "TraceOverloads.h"

	//Function to validate predicate datatype in Macro usage
	inline bool16 CheckPredicateInTrace(bool16 predicate)
	{
		return predicate;
	}

    #define TRACE(...)                              TRACE_INTERNAL(kFalse, "No_Category", __FILE__, __LINE__, __VA_ARGS__ )
    #define TRACEFLOW_WITH_FILE(category, file, lineno, ...) \
                                                    TRACE_INTERNAL(kTrue, category, file, lineno, __VA_ARGS__ )

    #define TRACEFLOW(category, ...)                TRACE_INTERNAL(kTrue, category, __FILE__, __LINE__, __VA_ARGS__ )

    #define TRACE_IF(predicate, ...)                CheckPredicateInTrace(predicate) ? TRACE_INTERNAL(kFalse, "No_Category", __FILE__, __LINE__, __VA_ARGS__ ) : (void)0

    #define TRACEFLOW_IF(predicate, category, ...)  CheckPredicateInTrace(predicate) ? TRACE_INTERNAL(kTrue, category, __FILE__, __LINE__, __VA_ARGS__ ) : (void)0

	// Same definition as release(does nothing)
	#define TRACEFLOW_OBSOLETE(...)				((void) 0)

#else // !defined(ID_ENABLE_DEBUGGING)
	#define TRACE(...)							((void) 0)
	#define TRACEFLOW(...)						((void) 0)
	#define TRACEFLOW_OBSOLETE(...)				((void) 0)
	#define TRACE_IF(...)						((void) 0)
	#define TRACEFLOW_IF(...)					((void) 0)
#endif // defined(ID_ENABLE_DEBUGGING)

#endif  // __TRACE_H__

