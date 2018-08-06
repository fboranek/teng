/*
 * Teng -- a general purpose templating engine.
 * Copyright (C) 2004  Seznam.cz, a.s.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Seznam.cz, a.s.
 * Naskove 1, Praha 5, 15000, Czech Republic
 * http://www.seznam.cz, mailto:teng@firma.seznam.cz
 *
 *
 * $Id: tengparservalue.cc,v 1.4 2008-11-14 11:00:04 burlog Exp $
 *
 * DESCRIPTION
 * Teng parser value data type.
 *
 * AUTHORS
 * Jan Nemec <jan.nemec@firma.seznam.cz>
 * Michal Bukovsky <michal.bukovsky@firma.seznam.cz>
 *
 * HISTORY
 * 2003-09-22  (jan)
 *             Created.
 * 2005-06-21  (roman)
 *             Win32 support.
 * 2018-06-07  (burlog)
 *             Make it more type safe.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <sstream>

#include "tengstructs.h"
#include "tengparservalue.h"
#include "tengplatform.h"

namespace Teng {
namespace Parser {
namespace {

// void Value_t::setReal(double val) {
//     char str[64];
//
//     int l = snprintf(str, sizeof(str), "%f", val);
//     if (!strstr(str, ".")) strcpy(str + l,".0");
//     else {
//         l--;
//         while (1) {
//             if (str[l-1] == '.' || str[l] != '0')
//                 break;
//             str[l] = 0;
//             l--;
//         }
//     }
//     stringValue = str;
//     integerValue = (int_t)val;
//     realValue = val;
//     type = TYPE_REAL;
// }
//
// void Value_t::setReal(double val, int prec) {
//     char str[64];
//
//     snprintf(str, sizeof(str), "%.*f", prec, val);
//     stringValue = str;
//     integerValue = (int_t)val;
//     realValue = val;
//     type = TYPE_REAL;
// }

} // namespace

std::string Value_t::to_string(const ptr_type &value) const {
    std::ostringstream os;
    os << '(' << value.ptr << ',' << value.type << ')';
    return os.str();
}

Value_t &Value_t::operator=(const FragmentValue_t &value) noexcept {
    switch (value.type()) {
    case FragmentValue_t::tag::fragments:
        *this = Undefined_t();
        break;
    case FragmentValue_t::tag::string:
        *this = value.str();
        break;
    case FragmentValue_t::tag::integral:
        *this = value.integral();
        break;
    case FragmentValue_t::tag::real:
        *this = value.real();
        break;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &o, const Value_t &v) {
    switch (v.tag_value) {
    case Value_t::tag::string:
        o << "string(" << v.string_value << ")";
        break;
    case Value_t::tag::integral:
        o << "integral(" << v.integral_value << ")";
        break;
    case Value_t::tag::real:
        o << "real(" << v.real_value << ")";
        break;
    case Value_t::tag::undefined:
        o << "undefined";
        break;
    case Value_t::tag::pointer:
        o << "ptr(" << v.ptr_value.ptr << ',' << v.ptr_value.type << ')';
        break;
    }
    return o;
}

} // namespace Parser
} // namespace Teng

