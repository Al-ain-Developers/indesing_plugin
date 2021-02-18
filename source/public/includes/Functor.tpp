//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Functor.tpp $
//  
//  Owner: ???
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

#ifndef _Functor_Templates_
#define _Functor_Templates_

#if defined(WINDOWS)		// so mmarcus will look into re-enabling the code.
#pragma warning (push)
#pragma warning (disable: 4530)
#endif

//________________________________________________________________________________________________________________________________________________________________________
// We're using a boost which is unware of the MWERKS 2407 bugs so we temporarily pose as 2406

#if __MWERKS__ == 0x2407
  #define __OLDMWERKS__ 0x2407
  #undef __MWERKS__ 
  #define __MWERKS__ 0x2406
#endif

#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat_2nd.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>


#ifdef __OLDMWERKS__
  #undef __MWERKS__ 
  #define __MWERKS__ __OLDMWERKS__
#endif  

//________________________________________________________________________________________________________________________________________________________________________
//Generate make_functor function templates
#include "boost/bind.hpp"
#include "boost/function.hpp"
#if 0
long int BOOST_START_;
// we set max to eight for now since boost::bind is limited to 8
#define K2_MAX_MAKE_FUNCTOR_PARAMS 8


#define K2_TYPED_PARAM(z, INDEX,DATA)\
  BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,DATA),INDEX),&) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,1,DATA),INDEX)

#define K2_REF_PARAM(z, INDEX,DATA)\
  ::boost::ref(BOOST_PP_CAT(DATA,INDEX))

#define K2_MAKE_FUNCTOR(z, N,_)\
  template<typename Obj, typename Ret BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg) BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename B)>  \
  ::boost::function1<Ret, USE_CONST Obj*> make_functor(Ret (Obj::*mfp)(BOOST_PP_ENUM_PARAMS(N, Arg)) USE_CONST BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM(N,K2_TYPED_PARAM,(B,a))          \
  )                                                                                                                                                         \
  {                                                                                                                                                         \
  	return ::boost::bind(boost::mem_fn(mfp), _1 BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM(N,K2_REF_PARAM, a));                                                  \
  }
  
  



#define USE_CONST 
BOOST_PP_REPEAT_2ND(BOOST_PP_INC(K2_MAX_MAKE_FUNCTOR_PARAMS),K2_MAKE_FUNCTOR,_)
#undef USE_CONST

#define USE_CONST const
BOOST_PP_REPEAT_2ND(BOOST_PP_INC(K2_MAX_MAKE_FUNCTOR_PARAMS),K2_MAKE_FUNCTOR,_)
#undef USE_CONST

#undef K2_MAKE_FUNCTOR
#undef K2_TYPED_PARAM
#undef K2_REF_PARAM
long int BOOST_END_;
#endif

	/* The above lines (to the #if 0) pre-process down to the following two lines */
#if 1
template<typename Obj, typename Ret > ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)() ) { return ::boost::bind(boost::mem_fn(mfp), _1 ); } template<typename Obj, typename Ret , typename Arg0 , typename B0> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0) , B0& a0 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename B0 , typename B1> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1) , B0& a0 , B1& a1 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename B0 , typename B1 , typename B2> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2) , B0& a0 , B1& a1 , B2& a2 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename B0 , typename B1 , typename B2 , typename B3> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3) , B0& a0 , B1& a1 , B2& a2 , B3& a3 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4) , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5) , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6) , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 , B6& a6 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5) , ::boost::ref( a6)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7> ::boost::function1<Ret, Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7) , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 , B6& a6 , B7& a7 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5) , ::boost::ref( a6) , ::boost::ref( a7)); }
template<typename Obj, typename Ret > ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)() const ) { return ::boost::bind(boost::mem_fn(mfp), _1 ); } template<typename Obj, typename Ret , typename Arg0 , typename B0> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0) const , B0& a0 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename B0 , typename B1> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1) const , B0& a0 , B1& a1 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename B0 , typename B1 , typename B2> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2) const , B0& a0 , B1& a1 , B2& a2 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename B0 , typename B1 , typename B2 , typename B3> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3) const , B0& a0 , B1& a1 , B2& a2 , B3& a3 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4) const , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5) const , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6) const , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 , B6& a6 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5) , ::boost::ref( a6)); } template<typename Obj, typename Ret , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename B0 , typename B1 , typename B2 , typename B3 , typename B4 , typename B5 , typename B6 , typename B7> ::boost::function1<Ret, const Obj*> make_functor(Ret (Obj::*mfp)( Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7) const , B0& a0 , B1& a1 , B2& a2 , B3& a3 , B4& a4 , B5& a5 , B6& a6 , B7& a7 ) { return ::boost::bind(boost::mem_fn(mfp), _1 , ::boost::ref( a0) , ::boost::ref( a1) , ::boost::ref( a2) , ::boost::ref( a3) , ::boost::ref( a4) , ::boost::ref( a5) , ::boost::ref( a6) , ::boost::ref( a7)); }
#endif
//________________________________________________________________________________________________________________________________________________________________________

template <class T>
inline PMIID GetDefaultIID(T t) //Need to write it like this for bugs in Metrowerks < 8
{
  return t->kDefaultIID;
}


//________________________________________________________________________________________________________________________________________________________________________
/*
	Sample client code:
	
	void client() {
		result = sub(make_functor(IFoo::DoIt, somearg, anotherarg));
	}
	
	template <typename Functor>
	typename Functor::Ret sub(Functor f)
	{
		// ...
		IGS* igs = //....
		return f(igs, arg1, arg2);
	}

*/

#if defined(WINDOWS)
#pragma warning (pop)
#endif


#endif //_Functor_Templates_






