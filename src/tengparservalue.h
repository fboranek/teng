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
 * $Id: tengparservalue.h,v 1.3 2007-05-21 15:43:28 vasek Exp $
 *
 * DESCRIPTION
 * Teng data types.
 *
 * AUTHORS
 * Vaclav Blazek <blazek@firma.seznam.cz>
 *
 * HISTORY
 * 2003-09-17  (vasek)
 *             Created.
 */

#ifndef TENGPARSERVALUE_H
#define TENGPARSERVALUE_H

#include <string>
#include <iostream>

#include <tengconfig.h>

namespace Teng {

class ParserValue_t {
public:

    /** Value types for string/numeric operations. */
    enum Type_t {
        TYPE_STRING, /**< Value in 'stringValue'. */
        TYPE_INT, /**< Value in 'integerValue'. */
        TYPE_REAL /**< Value in 'realValue'. */
    };

    ParserValue_t()
        : type(TYPE_STRING), stringValue(),
          integerValue(0), realValue(0.0)
    {}

    typedef IntType_t int_t;

    Type_t type;
    std::string stringValue;
    int_t integerValue;
    double realValue;

    /** Method sets type, stringValue, intValue and realValue.
      * If conversion to number fails, sets intValue and realValue to 0. */
    void setString(const std::string &val = std::string());
    /** Sets type, stringValue, intValue and realValue. */
    void setInteger(int_t val);
    /** Sets type, stringValue, intValue and realValue. */
    void setReal(double val);
    /** Sets type, stringValue, intValue and realValue. */
    void setReal(double val, int prec);
    /** If type==TYPE_STRING, try to convert string to a numeric value.
      * First, try to convert into real value, then integer value. */
    ParserValue_t validate() const;
    void validateThis();

    explicit operator bool() const {
        switch (type) {
        case TYPE_INT:
            return integerValue;

        case TYPE_REAL:
            return realValue;

        default:
            return !stringValue.empty();
        }
    }

    inline ParserValue_t operator-() const {
        if (type == TYPE_STRING) return *this;

        ParserValue_t result;
        result.type = type;
        result.integerValue = -integerValue;
        result.realValue = -realValue;
        result.stringValue.reserve(stringValue.length() + 1);
        result.stringValue.push_back('-');
        result.stringValue.append(stringValue);
        return result;
    }

    friend inline std::ostream& operator<<(std::ostream &o, ParserValue_t &v) {
        switch (v.type) {
        case TYPE_INT:
            o << "int(" << v.integerValue << ")";
            break;

        case TYPE_REAL:
            o << "real(" << v.realValue << ")";
            break;

        default:
            o << "string(" << v.stringValue << ")";
            break;
        }
        return o;
    }
};

} // namespace Teng

#endif // TENGPARSERVALUE_H

