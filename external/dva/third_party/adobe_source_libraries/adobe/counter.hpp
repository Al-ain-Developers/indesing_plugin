/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/

/******************************************************************************/

#ifndef ADOBE_COUNTER_HPP
#define ADOBE_COUNTER_HPP

/******************************************************************************/

#include <adobe/config.hpp>

#include <boost/noncopyable.hpp>

/* ASL_USE_THREADSAFE_COUNTER allows ASL users (especially Owl) to opt out of a
threadsafe counter. This is mainly an issue as long as the underlying implementation
uses tbb, as asl should not require tbb (Owl cannot require that its clients use
tbb)
Tur disable the tbb dependency, define ASL_USE_THREADSAFE_COUNTER to 0.
When.if asl migrate to std::atomicm, we can remove this pre-processor symbol
*/
#if !defined(ASL_USE_THREADSAFE_COUNTER)
#define ASL_USE_THREADSAFE_COUNTER 1
#endif

#if ASL_USE_THREADSAFE_COUNTER
#include <adobe/implementation/atomic_primitives.hpp>
#endif

/******************************************************************************/

namespace adobe {

/******************************************************************************/

/*!
\defgroup asl_counter Thread-safe counter
\ingroup thread

\class adobe::counter_t
\ingroup asl_counter 

\brief A thread safe counter

A counter_t is a noncopyable thread safe counter, useful for managing the reference count of a shared resource.

\par Rationale:

counter_t wraps reference count operations that require thread safety into a single class. While this does not guarantee client code will be thread safe, it helps to take a step in that direction. It also cleans up client code and keeps thread-handling scoped to a single file. Consider copy_on_write as an example class that leverages counter_t.

\note
The counter_t class is thread safe when compiled with BOOST_HAS_THREADS defined.
*/

/*!
\fn adobe::counter_t::counter_t()

Default constructor. The counter is initialized to 1.
*/

/*!
\fn void adobe::counter_t::increment()

Increments the counter by one.
*/

/*!
\fn bool adobe::counter_t::decrement()

Decrements the counter by one.

\return <code>true</code> if the counter is zero at the end of this operation; <code>false</code> otherwise.
*/

/*!
\fn bool adobe::counter_t::is_one() const

Checks to see if the counter is one.

\return <code>true</code> if the counter is one; <code>false</code> otherwise.
*/


class counter_t
#if !defined(ADOBE_NO_DOCUMENTATION)
    : boost::noncopyable
#endif
{
public:
    counter_t()
    {
#if ASL_USE_THREADSAFE_COUNTER
        count_m = implementation::atomic_t::value_type(1);
#else
        count_m = 1;
#endif
    }

    void increment()
    {
        ++count_m;
    }

    bool decrement()
    {
#if ASL_USE_THREADSAFE_COUNTER
        return --count_m == implementation::atomic_t::value_type(0);
#else
        return --count_m == 0;
#endif
    }

    bool is_one() const
    {
#if ASL_USE_THREADSAFE_COUNTER
        return count_m == implementation::atomic_t::value_type(1);
#else
        return count_m == 1;
#endif
    }

private:
#if ASL_USE_THREADSAFE_COUNTER
    implementation::atomic_t::type count_m;
#else
    std::size_t count_m;
#endif
};

/******************************************************************************/

} // namespace adobe

/******************************************************************************/
// ADOBE_COUNTER_HPP
#endif

/******************************************************************************/
