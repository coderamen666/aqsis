// Aqsis
// Copyright � 1997 - 2001, Paul C. Gregory
//
// Contact: pgregory@aqsis.com
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


/** \file
		\brief Declares CqSemaphire class which encapsulates the system specific semaphore.
		\author Paul C. Gregory (pgregory@aqsis.com)
*/

#ifndef SEMAPHORE_H_INCLUDED
#define SEMAPHORE_H_INCLUDED

//--------------------------------------------------------------------------
/** \class CqSemaphore
 * Wrapper around the system specific semaphore implementation.
 */

class CqSemaphore
{
public:
    CqSemaphore();
    ~CqSemaphore();

    void Signal();
    void Wait();

protected:
    void* m_pNativeSemaphore;	///< Pointer to the system specific semaphore implementation.
}
;


#endif // SEMAPHORE_H_INCLUDED

