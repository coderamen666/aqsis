// Aqsis
// Copyright (C) 1997 - 2010, Paul C. Gregory
//
// Contact: pgregory@aqsis.org
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "varspec.h"
#include "fixedstrings.h"

namespace Stdvar
{
#   define DEFINE_STD_VAR(type, count, name)                          \
        const VarSpec name(VarSpec::type, count, ustring(#name))

    DEFINE_STD_VAR(Point, 1, P);
    DEFINE_STD_VAR(Color, 1, Cs);
    DEFINE_STD_VAR(Color, 1, Ci);
    DEFINE_STD_VAR(Color, 1, Os);
    DEFINE_STD_VAR(Color, 1, Oi);
    DEFINE_STD_VAR(Float, 2, st);
    DEFINE_STD_VAR(Float, 1, s);
    DEFINE_STD_VAR(Float, 1, t);
    DEFINE_STD_VAR(Vector, 1, I);
    DEFINE_STD_VAR(Normal, 1, N);
    DEFINE_STD_VAR(Normal, 1, Ng);

    DEFINE_STD_VAR(Float, 1, z);

#undef DEFINE_STD_VAR
}

