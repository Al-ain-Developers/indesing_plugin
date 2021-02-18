//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UTF16TextCharTraits.h $
//  
//  Owner: Chris Parrish
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
#ifndef __UTF16TextCharTraits__
#define __UTF16TextCharTraits__

#if defined(WINDOWS) || defined(__GLIBCXX__)
#error This file is only for Mac libc++
#endif

#if !defined(_LIBCPP_VERSION)
#error This file is only for Mac libc++
#endif

#include <string> // for char_traits
#include <locale> // for codecvt
#include <climits>

namespace std
{
    template<>
    struct char_traits<UTF16TextChar>
    {
        typedef UTF16TextChar		char_type;
        typedef unsigned short        int_type;
        typedef streampos 	pos_type;
        typedef streamoff off_type;
        typedef mbstate_t state_type;
        
        static void
        assign(char_type& c1, const char_type& c2)
        { c1 = c2; }
        
        static bool
        eq(const char_type& c1, const char_type& c2)
        { return c1 == c2; }
        
        static bool
        lt(const char_type& c1, const char_type& c2)
        { return c1 < c2; }
        
        
        static int
        compare(const char_type* s1, const char_type* s2, size_t n)
        {
            for (size_t i = 0; i < n; ++i)
            {
                if (lt(s1[i], s2[i]))
                    return -1;
                else if (lt(s2[i], s1[i]))
                    return 1;
            }
            return 0;
        }
        
        static size_t
        length(const char_type* s)
        {
            size_t n = 0;
            while (!eq(s[n], char_type()))
                ++n;
            return n;
        }
        
        
        static const char_type*
        find(const char_type* s, size_t n, const char_type& a)
        {
            for (size_t i = 0; i < n; ++i)
            {
                if (eq(s[i], a))
                    return s + i;
            }
            return NULL;
        }
        
        static char_type*
        move(char_type* s1, const char_type* s2, size_t n)
        {
            if (s1 > s2)
            {
                for (size_t i = 0; i < n; ++i)
                    assign(s1[n - i - 1], s2[n - i - 1]);
            }
            else
            {
                for (size_t i = 0; i < n; ++i)
                    assign(s1[i], s2[i]);
            }
            return s1;
        }
        
        static char_type*
        copy(char_type* s1, const char_type* s2, size_t n)
        {
            for (size_t i = 0; i < n; ++i)
                assign(s1[i], s2[i]);
            return s1;
        }
        
        static char_type*
        assign(char_type* s, size_t n, char_type a)
        {
            for (size_t i = 0; i < n; ++i)
                assign(s[i], a);
            return s;
        }
        
        static int_type
        not_eof(const int_type& c)
        {
            if (eq_int_type(c, eof()))
                return 0;
            return c;
        }
        
        static char_type
        to_char_type(const int_type& c)
        {
            char_type ret;
            ret = c;
            return ret;
        }
        
        static int_type
        to_int_type(const char_type& c)
        {
            return c;
        }
        
        static bool
        eq_int_type(const int_type& c1, const int_type& c2)
        { return c1 == c2; }
        
        
        static int_type
        eof() { return static_cast<int_type>(WEOF); }
        
    };

    template<>
    class __attribute__((visibility("default"))) ctype<UTF16TextChar> : public locale::facet, public ctype_base
    {
    public:
        typedef UTF16TextChar char_type;
        
        explicit ctype(size_t refs  = 0): locale::facet(refs) { }
        
        /**
         *  @brief  Test char classification.
         *
         *  This function compares the mask of c to @a m.
         *
         *  @param c  The char to compare the mask of.
         *  @param m  The mask to compare against.
         *  @return  True if m & table[c] is true, false otherwise.
         */
        bool is(mask m, char_type c) const
        { return this->do_is(m,c); }
        
        /**
         *  @brief  Return a mask array.
         *
         *  This function finds the mask for each char in the range [lo, hi) and
         *  successively writes it to vec.  vec must have as many elements as
         *  the char array.
         *
         *  @param lo  Pointer to start of range.
         *  @param hi  Pointer to end of range.
         *  @param vec  Pointer to an array of mask storage.
         *  @return  @a hi.
         */
        const char_type* is(const char_type* low, const char_type* high, mask* vec) const
        {
            return this->do_is(low,high,vec);
        }
        
        /**
         *  @brief  Find char matching a mask
         *
         *  This function searches for and returns the first char in [lo,hi) for
         *  which is(m,char) is true.
         *
         *  @param m  The mask to compare against.
         *  @param lo  Pointer to start of range.
         *  @param hi  Pointer to end of range.
         *  @return  Pointer to a matching char if found, else @a hi.
         */
        const char_type* scan_is(mask m, const char_type* low, const char_type* high) const
        {return this->do_scan_is(m,low,high);}
        
        /**
         *  @brief  Find char not matching a mask
         *
         *  This function searches for and returns a pointer to the first char
         *  in [lo,hi) for which is(m,char) is false.
         *
         *  @param m  The mask to compare against.
         *  @param lo  Pointer to start of range.
         *  @param hi  Pointer to end of range.
         *  @return  Pointer to a non-matching char if found, else @a hi.
         */
        const char_type* scan_not(mask m, const char_type* low, const char_type* high) const
        {return this->do_scan_not(m,low,high);}
        
        /**
         *  @brief  Convert to uppercase.
         *
         *  This function converts the char argument to uppercase if possible.
         *  If not possible (for example, '2'), returns the argument.
         *
         *  @param c  The char to convert.
         *  @return  The uppercase char if convertible, else @a c.
         */
        char_type toupper(char_type c) const
        { return this->do_toupper(c); }
        
        /**
         *  @brief  Convert array to uppercase.
         *
         *  This function converts each char in the range [lo,hi) to uppercase
         *  if possible.  Other chars remain untouched.
         *
         *  @param lo  Pointer to first char in range.
         *  @param hi  Pointer to end of range.
         *  @return  @a hi.
         */
        const char_type* toupper(char_type* low, const char_type* high) const
        { return this->do_toupper(low, high); }
        
        /**
         *  @brief  Convert to lowercase.
         *
         *  This function converts the char argument to lowercase if possible.
         *  If not possible (for example, '2'), returns the argument.
         *
         *  @param c  The char to convert.
         *  @return  The lowercase char if convertible, else @a c.
         */
        char_type tolower(char_type c) const
        { return this->do_tolower(c); }
        
        /**
         *  @brief  Convert array to lowercase.
         *
         *  This function converts each char in the range [lo,hi) to lowercase
         *  if possible.  Other chars remain untouched.
         *
         *  @param lo  Pointer to first char in range.
         *  @param hi  Pointer to end of range.
         *  @return  @a hi.
         */
        const char_type* tolower(char_type* low, const char_type* high) const
        { return this->do_tolower(low, high); }
        
        /**
         *  @brief  Widen char
         *
         *  This function converts the char to char_type using the simplest
         *  reasonable transformation.  For an underived ctype<char> facet, the
         *  argument will be returned unchanged.
         *
         *  Note: this is not what you want for codepage conversions.  See
         *  codecvt for that.
         *
         *  @param c  The char to convert.
         *  @return  The converted character.
         */
        char_type widen(char c) const
        { return this->do_widen(c); }
        
        /**
         *  @brief  Widen char array
         *
         *  This function converts each char in the input to char using the
         *  simplest reasonable transformation.  For an underived ctype<char>
         *  facet, the argument will be copied unchanged.
         *
         *  Note: this is not what you want for codepage conversions.  See
         *  codecvt for that.
         *
         *  @param lo  Pointer to first char in range.
         *  @param hi  Pointer to end of range.
         *  @param to  Pointer to the destination array.
         *  @return  @a hi.
         */
        const char* widen(const char* low, const char* high, char_type* to) const
        { return this->do_widen(low, high, to); }
        
        /**
         *  @brief  Narrow char
         *
         *  This function converts the char to char using the simplest
         *  reasonable transformation.  If the conversion fails, dfault is
         *  returned instead.  For an underived ctype<char> facet, @a c
         *  will be returned unchanged.
         *
         *  Note: this is not what you want for codepage conversions.  See
         *  codecvt for that.
         *
         *  @param c  The char to convert.
         *  @param dfault  Char to return if conversion fails.
         *  @return  The converted character.
         */
        char narrow(char_type c, char dfault) const
        { return this->do_narrow(c, dfault); }
        
        /**
         *  @brief  Narrow char array
         *
         *  This function converts each char in the input to char using the
         *  simplest reasonable transformation and writes the results to the
         *  destination array.  For any char in the input that cannot be
         *  converted, @a dfault is used instead.  For an underived ctype<char>
         *  facet, the argument will be copied unchanged.
         *
         *  Note: this is not what you want for codepage conversions.  See
         *  codecvt for that.
         *
         *  @param lo  Pointer to start of range.
         *  @param hi  Pointer to end of range.
         *  @param dfault  Char to use if conversion fails.
         *  @param to  Pointer to the destination array.
         *  @return  @a hi.
         */
        const char_type* narrow(const char_type* low, const char_type* high, char dfault, char* to) const
        { return this->do_narrow(low, high, dfault, to); }
        
        static locale::id id;
        
    protected:
        ~ctype();
        
        virtual bool do_is(mask m, char_type c) const;
        
        virtual const char_type* do_is(const char_type* low, const char_type* high, mask* vec) const;
        
        virtual const char_type* do_scan_is(mask m, const char_type* low, const char_type* high) const;
        
        virtual const char_type* do_scan_not(mask m, const char_type* low, const char_type* high) const;
        
        virtual char_type do_toupper(char_type c) const;
        
        virtual const char_type* do_toupper(char_type*  low, const char_type*  high) const;
        
        virtual char_type do_tolower(char_type c) const;
        
        virtual const char_type* do_tolower(char_type*  low, const char_type*  high) const;
        
        virtual char_type do_widen(char c) const;
        
        virtual const char*  do_widen(const char* low, const char* high, char_type* dest) const;
        
        virtual char do_narrow(char_type, char dfault) const;
        
        virtual const char_type* do_narrow(const char_type* low, const char_type* high,
                                           char dfault, char*  dest) const;
    };
    
#pragma GCC visibility push(default)

    extern template class std::basic_string<UTF16TextChar>;
    //extern template class std::basic_filebuf<UTF16TextChar>;

    template <>
    class numpunct<UTF16TextChar>
    : public locale::facet
    {
    public:
        typedef UTF16TextChar char_type;
        typedef basic_string<char_type> string_type;
        
        explicit numpunct(size_t __refs = 0);
        
        char_type decimal_point() const {return do_decimal_point();}
        char_type thousands_sep() const {return do_thousands_sep();}
        string grouping() const         {return do_grouping();}
        string_type truename() const    {return do_truename();}
        string_type falsename() const   {return do_falsename();}
        
        static locale::id id;
        
    protected:
        ~numpunct();
        virtual char_type do_decimal_point() const;
        virtual char_type do_thousands_sep() const;
        virtual string do_grouping() const;
        virtual string_type do_truename() const;
        virtual string_type do_falsename() const;
    };
    
    extern template class std::num_get<UTF16TextChar>;
    extern template class std::num_put<UTF16TextChar>;
    extern template class std::numpunct<UTF16TextChar>;
    extern template class std::num_get<UTF16TextChar>;
    extern template class std::num_put<UTF16TextChar>;
    extern template class std::numpunct<UTF16TextChar>;
#pragma GCC visibility pop

    template <>
    class  __attribute__((visibility("default"))) codecvt<UTF16TextChar, char, mbstate_t>
    : public locale::facet,
    public codecvt_base
    {
    public:
        typedef UTF16TextChar  intern_type;
        typedef char      extern_type;
        typedef mbstate_t state_type;
        
        
        explicit codecvt(size_t __refs = 0)
        : locale::facet(__refs) {}
        
        
        result out(state_type& __st,
                   const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
                   extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
            return do_out(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }
        
        
        result unshift(state_type& __st,
                       extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
            return do_unshift(__st, __to, __to_end, __to_nxt);
        }
        
        
        result in(state_type& __st,
                  const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
                  intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const
        {
            return do_in(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }
        
        
        int encoding() const  _NOEXCEPT
        {
        return do_encoding();
    }
    
    
    bool always_noconv() const  _NOEXCEPT
    {
    return do_always_noconv();
}


int length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const
{
    return do_length(__st, __frm, __end, __mx);
}


int max_length() const  _NOEXCEPT
{
return do_max_length();
}

static locale::id id;

protected:

explicit codecvt(const char*, size_t __refs = 0)
: locale::facet(__refs) {}

~codecvt();

virtual result do_out(state_type& __st,
                      const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
                      extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
virtual result do_in(state_type& __st,
                     const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
                     intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const;
virtual result do_unshift(state_type& __st,
                          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
virtual int do_encoding() const  _NOEXCEPT;
virtual bool do_always_noconv() const  _NOEXCEPT;
virtual int do_length(state_type&, const extern_type* __frm, const extern_type* __end, size_t __mx) const;
virtual int do_max_length() const  _NOEXCEPT;
};

}

#endif //__UTF16TextCharTraits__

