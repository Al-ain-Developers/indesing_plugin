/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/

/*************************************************************************************************/

#ifndef ADOBE_CONFIG_COMPILER_GCC_HPP
#define ADOBE_CONFIG_COMPILER_GCC_HPP

/*************************************************************************************************/

#ifndef ADOBE_CONFIG_HPP
    #error "This file is intended to be included by <adobe/config.hpp> -- please use that file directly."
#endif

/*************************************************************************************************/

#ifndef ADOBE_COMPILER_GCC
    #define ADOBE_COMPILER_GCC 1
#endif

/*************************************************************************************************/
#ifdef ASL_USE_LIB
#define ASL_DECL 
#else
#define ASL_DECL __attribute__ ((visibility("default")))
#endif

/*************************************************************************************************/

// test exceptions here

/*************************************************************************************************/

#endif

/*************************************************************************************************/
