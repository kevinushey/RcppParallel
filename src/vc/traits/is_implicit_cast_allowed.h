/*  This file is part of the Vc library. {{{
Copyright © 2015 Matthias Kretz <kretz@kde.org>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef VC_TRAITS_IS_IMPLICIT_CAST_ALLOWED_H_
#define VC_TRAITS_IS_IMPLICIT_CAST_ALLOWED_H_

namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template <typename From, typename To, bool = std::is_integral<From>::value>
struct is_implicit_cast_allowed
    : public std::integral_constant<
          bool, std::is_same<From, To>::value ||
                    (std::is_integral<To>::value &&
                     (std::is_same<typename std::make_unsigned<From>::type, To>::value ||
                      std::is_same<typename std::make_signed<From>::type, To>::value))> {
};

template <typename From, typename To>
struct is_implicit_cast_allowed<From, To, false> : public std::is_same<From, To>::type {
};

template <typename From, typename To>
struct is_implicit_cast_allowed_mask : public is_implicit_cast_allowed<From, To> {
};

static_assert(is_implicit_cast_allowed<float, float>::value, "");
static_assert(!is_implicit_cast_allowed<float, double>::value, "");
static_assert(is_implicit_cast_allowed< int64_t, uint64_t>::value, "");
static_assert(is_implicit_cast_allowed<uint64_t,  int64_t>::value, "");
static_assert(is_implicit_cast_allowed< int32_t, uint32_t>::value, "");
static_assert(is_implicit_cast_allowed<uint32_t,  int32_t>::value, "");
static_assert(is_implicit_cast_allowed< int16_t, uint16_t>::value, "");
static_assert(is_implicit_cast_allowed<uint16_t,  int16_t>::value, "");
static_assert(is_implicit_cast_allowed<  int8_t,  uint8_t>::value, "");
static_assert(is_implicit_cast_allowed< uint8_t,   int8_t>::value, "");

}  // namespace Traits
}  // namespace Vc

#endif  // VC_TRAITS_IS_IMPLICIT_CAST_ALLOWED_H_

// vim: foldmethod=marker
