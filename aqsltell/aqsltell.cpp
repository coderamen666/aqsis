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
		\brief A program to test libslxargs.
		\author Douglas Ward (dsward@vidi.com)
*/

#include "aqsis.h"

#ifdef	AQSIS_COMPILER_MSVC6
#pragma warning(disable : 4786 )
#endif //AQSIS_COMPILER_MSVC6

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "aqsis.h"
#include "file.h"

#if defined(AQSIS_SYSTEM_WIN32) || defined(AQSIS_SYSTEM_MACOSX)
#include "version.h"
#endif

#include <stdio.h>
#include "slx.h"
#include <argparse.h>


namespace Aqsis
{
struct IqRenderer;
extern IqRenderer* QGetRenderContextI();
}

bool g_pause = 0;
bool g_help = 0;
bool g_version = 0;


void version( std::ostream& Stream )
{
#if defined(AQSIS_SYSTEM_WIN32) || defined(AQSIS_SYSTEM_MACOSX)
    Stream << "aqsltell version " << VERSION_STR << std::endl;
#else
    Stream << "aqsltell version " << VERSION << std::endl;
#endif
}

/*
 *
 */
int main( int argc, const char** argv )
{
    Aqsis::QGetRenderContextI();
    ArgParse ap;
    ap.usageHeader( ArgParse::apstring( "Usage: " ) + argv[ 0 ] + " <shadername>" );
    ap.argFlag( "help", "\aprint this help and exit", &g_help );
    ap.argFlag( "version", "\aprint version information and exit", &g_version );
    ap.argFlag( "pause", "\await for a keypress on completion", &g_pause );

    if ( argc > 1 && !ap.parse( argc - 1, argv + 1 ) )
    {
        std::cerr << ap.errmsg() << std::endl << ap.usagemsg();
        exit( 1 );
    }

    if ( g_help )
    {
        std::cout << ap.usagemsg();
        exit( 0 );
    }

    if ( g_version )
    {
        version( std::cout );
        exit( 0 );
    }

    // Any leftovers are presumed to be shader names.
    if ( ap.leftovers().size() == 0 )     // If no files specified, take input from stdin.
    {
        std::cerr << ap.errmsg() << std::endl << ap.usagemsg();
        exit( 1 );
    }
    else
    {
        for ( ArgParse::apstringvec::const_iterator e = ap.leftovers().begin(); e != ap.leftovers().end(); e++ )
        {
            std::string shaderpath;
            shaderpath = Aqsis::CqFile::GetSystemSetting( "shaders" );

            SLX_SetPath( const_cast<char*>( shaderpath.c_str() ) );

            if ( SLX_SetShader( ( char* ) e->c_str() ) == 0 )
            {
                // SLX_SetShader successful
                int	nArgs;
                int i;
                SLX_VISSYMDEF * symPtr;

                char* currpath = SLX_GetPath();
                std::cout << SLX_TypetoStr( SLX_GetType() ) << " \"" << currpath;
                if ( strlen( currpath ) > 0 &&
                        ( currpath[ strlen( currpath ) - 1 ] != '/' ) &&
                        ( currpath[ strlen( currpath ) - 1 ] != '\\' ) )
                    std::cout << "/";
                std::cout << SLX_GetName() << "\"" << std::endl;
                nArgs = SLX_GetNArgs();

                for ( i = 0; i < nArgs; i++ )
                {
                    symPtr = SLX_GetArgById( i );
                    if ( symPtr != NULL )
                    {
                        TqInt arrayLen = 1;
                        if ( symPtr->svd_arraylen != 0 )
                            arrayLen = symPtr->svd_arraylen;

                        std::cout << "    \"" << symPtr->svd_name << "\" \"parameter " <<
                        SLX_DetailtoStr( symPtr->svd_detail ) << " " <<
                        SLX_TypetoStr( symPtr->svd_type );

                        if ( symPtr->svd_arraylen != 0 )
                            std::cout << "[" << arrayLen << "]";

                        std::cout << "\"" << std::endl;

                        TqInt arrayIndex;
                        for ( arrayIndex = 0; arrayIndex < arrayLen; arrayIndex++ )
                        {
                            std::cout << "\t\tDefault value: ";

                            if ( symPtr->svd_spacename != NULL )
                            {
                                if ( ( symPtr->svd_type == SLX_TYPE_POINT ) ||
                                        ( symPtr->svd_type == SLX_TYPE_NORMAL ) ||
                                        ( symPtr->svd_type == SLX_TYPE_VECTOR ) ||
                                        ( symPtr->svd_type == SLX_TYPE_MATRIX ) ||
                                        ( symPtr->svd_type == SLX_TYPE_COLOR ) )
                                    std::cout << "\"" << symPtr->svd_spacename << "\" ";
                            }

                            if ( symPtr->svd_default.stringval != NULL )
                            {
                                switch ( symPtr->svd_type )
                                {
                                case SLX_TYPE_UNKNOWN:
                                    std::cout << "unknown" << std::endl;
                                    break;
                                case SLX_TYPE_POINT:
                                case SLX_TYPE_NORMAL:
                                case SLX_TYPE_VECTOR:
                                    std::cout << "[" << symPtr->svd_default.pointval[ arrayIndex ].xval << " " <<
                                    symPtr->svd_default.pointval[ arrayIndex ].yval << " " <<
                                    symPtr->svd_default.pointval[ arrayIndex ].zval <<
                                    "]" << std::endl;
                                    break;
                                case SLX_TYPE_COLOR:
                                    std::cout << "[" << symPtr->svd_default.pointval[ arrayIndex ].xval << " " <<
                                    symPtr->svd_default.pointval[ arrayIndex ].yval << " " <<
                                    symPtr->svd_default.pointval[ arrayIndex ].zval <<
                                    "]" << std::endl;
                                    break;
                                case SLX_TYPE_SCALAR:
                                    std::cout << symPtr->svd_default.scalarval[ arrayIndex ] << std::endl;
                                    break;
                                case SLX_TYPE_STRING:
                                    std::cout << "\"" << symPtr->svd_default.stringval[ arrayIndex ] << "\"" << std::endl;
                                    break;
                                case SLX_TYPE_MATRIX:
                                    std::cout << "[" <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[0][0] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[0][1] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[0][2] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[0][2] << std::endl << "\t\t\t" <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[1][0] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[1][1] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[1][2] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[1][2] << std::endl << "\t\t\t" <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[2][0] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[2][1] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[2][2] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[2][3] << std::endl << "\t\t\t" <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[3][0] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[3][1] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[3][2] << " " <<
                                    symPtr->svd_default.matrixval[ arrayIndex ].val[3][3] <<
                                    "]" << std::endl;
                                    break;
                                default:
                                    std::cout << "unknown" << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        printf( "ERROR - null pointer to value" );
                    }
                    //std::cout << std::endl;
                }

                SLX_EndShader();
            }
        }
    }

    return ( 0 );
}

