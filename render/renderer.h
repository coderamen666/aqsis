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
		\brief Declares the base CqRenderer class which is the central core of the rendering main loop.
		\author Paul C. Gregory (pgregory@aqsis.com)
*/

//? Is renderer.h included already?
#ifndef RENDERER_H_INCLUDED 
//{
#define RENDERER_H_INCLUDED 1

#include	<vector>
#include	<iostream>
#include	<time.h>

#include	"aqsis.h"

#include	"ri.h"
#include	"context.h"
#include	"stats.h"
#include	"vector2d.h"
#include	"semaphore.h"
#include	"messages.h"
#include	"shaders.h"
#include	"symbols.h"
#include	"iddmanager.h"
#include	"irenderer.h"
#include	"log.h"

#define		_qShareName	CORE
#include	"share.h"

START_NAMESPACE( Aqsis )

class CqImageBuffer;

struct SqCoordSys
{
	SqCoordSys( const char* strName, const CqMatrix& matToWorld, const CqMatrix& matWorldTo ) :
			m_matWorldTo( matWorldTo ),
			m_matToWorld( matToWorld ),
			m_strName( strName )
	{ m_hash = CqParameter::hash((char *) strName);}
	SqCoordSys()
	{}

	CqMatrix	m_matWorldTo;
	CqMatrix	m_matToWorld;
	CqString	m_strName;
	TqUlong         m_hash;
};

enum EqCoordSystems
{
    CoordSystem_Camera = 0,
    CoordSystem_Current,
    CoordSystem_World,
    CoordSystem_Screen,
    CoordSystem_NDC,
    CoordSystem_Raster,

    CoordSystem_Last,
};

enum EqRenderMode
{
    RenderMode_Image = 0,

    RenderMode_Shadows,
    RenderMode_Reflection,
};


//----------------------------------------------------------------------
/** \class  CqRenderer
 * The main renderer control class.  Contains all information relating to
 * the current image being rendered.  There is only ever one of these,
 * statically defined in the CPP file for this class, and globally available.
 */

class CqRenderer;
_qShareM extern CqRenderer* pCurrRenderer;
_qShareM extern CqOptions	goptDefault;					///< Default options.

class CqRenderer : public IqRenderer
{
	public:
		CqRenderer();
		virtual	~CqRenderer();

		virtual	CqModeBlock*	BeginMainModeBlock();
		virtual	CqModeBlock*	BeginFrameModeBlock();
		virtual	CqModeBlock*	BeginWorldModeBlock();
		virtual	CqModeBlock*	BeginAttributeModeBlock();
		virtual	CqModeBlock*	BeginTransformModeBlock();
		virtual	CqModeBlock*	BeginSolidModeBlock( CqString& type );
		virtual	CqModeBlock*	BeginObjectModeBlock();
		virtual	CqModeBlock*	BeginMotionModeBlock( TqInt N, TqFloat times[] );

		virtual	void	EndMainModeBlock();
		virtual	void	EndFrameModeBlock();
		virtual	void	EndWorldModeBlock();
		virtual	void	EndAttributeModeBlock();
		virtual	void	EndTransformModeBlock();
		virtual	void	EndSolidModeBlock();
		virtual	void	EndObjectModeBlock();
		virtual	void	EndMotionModeBlock();

		virtual	CqOptions&	optCurrent() const;
		virtual	const CqAttributes*	pattrCurrent();
		virtual	CqAttributes*	pattrWriteCurrent();
		virtual	const CqTransform*	ptransCurrent();
		virtual	CqTransform*	ptransWriteCurrent();

		virtual	TqFloat	Time() const;
		virtual	void	AdvanceTime();

		/** Get a pointer to the current context.
		 * \return Pointer to a CqModeBlock derived class.
		 */
		virtual	CqModeBlock*	pconCurrent()
		{
			return ( m_pconCurrent );
		}
		/** Get a erad only pointer to the current context.
		 * \return Pointer to a CqModeBlock derived class.
		 */
		virtual const	CqModeBlock*	pconCurrent() const
		{
			return ( m_pconCurrent );
		}
		/** Get a pointer to the current image buffer.
		 * \return A CqImageBuffer pointer.
		 */
		virtual CqImageBuffer* pImage()
		{
			return ( m_pImageBuffer );
		}
		/** Set the pointer to the current image buffer.
		 */
		virtual	void	SetImage( CqImageBuffer* pImage )
		{
			m_pImageBuffer = pImage;
		}

		// Handle various coordinate system transformation requirements.
		virtual	CqMatrix	matSpaceToSpace	( const char* strFrom, const char* strTo, const CqMatrix& matShaderToWorld = CqMatrix(), const CqMatrix& matObjectToWorld = CqMatrix(), TqFloat time = 0.0f );
		virtual	CqMatrix	matVSpaceToSpace	( const char* strFrom, const char* strTo, const CqMatrix& matShaderToWorld = CqMatrix(), const CqMatrix& matObjectToWorld = CqMatrix(), TqFloat time = 0.0f );
		virtual	CqMatrix	matNSpaceToSpace	( const char* strFrom, const char* strTo, const CqMatrix& matShaderToWorld = CqMatrix(), const CqMatrix& matObjectToWorld = CqMatrix(), TqFloat time = 0.0f );

		virtual	const	TqFloat*	GetFloatOption( const char* strName, const char* strParam ) const;
		virtual	const	TqInt*	GetIntegerOption( const char* strName, const char* strParam ) const;
		virtual	const	CqString* GetStringOption( const char* strName, const char* strParam ) const;
		virtual	const	CqVector3D*	GetPointOption( const char* strName, const char* strParam ) const;
		virtual	const	CqColor*	GetColorOption( const char* strName, const char* strParam ) const;

		virtual	TqFloat*	GetFloatOptionWrite( const char* strName, const char* strParam );
		virtual	TqInt*	GetIntegerOptionWrite( const char* strName, const char* strParam );
		virtual	CqString* GetStringOptionWrite( const char* strName, const char* strParam );
		virtual	CqVector3D*	GetPointOptionWrite( const char* strName, const char* strParam );
		virtual	CqColor*	GetColorOptionWrite( const char* strName, const char* strParam );

		virtual	void	PrintString( const char* str )
		{
			std::cout << str;
		}

		virtual	IqTextureMap* GetTextureMap( const CqString& strFileName );
		virtual	IqTextureMap* GetEnvironmentMap( const CqString& strFileName );
		virtual	IqTextureMap* GetShadowMap( const CqString& strFileName );
		virtual	IqTextureMap* GetLatLongMap( const CqString& strFileName );

		virtual	TqBool	GetBasisMatrix( CqMatrix& matBasis, const CqString& name );


		/** Get a read only reference to the current transformation matrix.
		 * \return A constant reference to a CqMatrix.
		 */
		virtual const	CqMatrix&	matCurrent( TqFloat time = 0.0f ) const
		{
			return ( pconCurrent() ->matCurrent( time ) );
		}

		virtual	TqBool	SetCoordSystem( const char* strName, const CqMatrix& matToWorld );

		// Function which can be overridden by the derived class.
		virtual	void	Initialise();
		virtual	void	RenderWorld();

		virtual	void	AddDisplayRequest( const TqChar* name, const TqChar* type, const TqChar* mode, TqInt compression, TqInt quality );
		virtual	void	ClearDisplayRequests();
		virtual	IqDDManager*	pDDmanager()
		{
			return ( m_pDDManager );
		}

		virtual	void	Quit();
		virtual	void	UpdateStatus()
		{}
		/** Get the global statistics class.
		 * \return A reference to the CqStats class on this renderer.
		 */
		virtual	CqStats&	Stats()
		{
			return ( m_Stats );
		}
		/** Print a message to stdout, along with any relevant message codes.
		 * \param msg A SqMessage structure to print.
		 */
		virtual	void	PrintMessage( const SqMessage& msg )
		{
			if ( msg.Code() > 0 )
				std::cout << msg.Code() << " : " <<
				msg.Severity() << " : ";
			std::cout << msg.strMessage().c_str() << std::endl;
		}
		virtual	IqLog*	Logger()
		{
			return( &m_theLog );
		}
		// Contect change callbacks
		virtual	SqParameterDeclaration FindParameterDecl( const char* strDecl );
		virtual	void	AddParameterDecl( const char* strName, const char* strType );
		virtual	void	ClearSymbolTable()
		{
			m_Symbols.clear();
		}

		/** Get the list of currently registered shaders.
		 * \return A reference to a list of CqShaderRegister classes.
		 */
		virtual	IqShader* CreateShader( const char* strName, EqShaderType type );

		/** Flush any registered shaders.
		 */
		virtual	void	FlushShaders()
		{
			while ( m_Shaders.pFirst() != 0 )
				delete( m_Shaders.pFirst() );
		}

		/** Set the world to screen matrix.
		 * \param mat The new matrix to use as the world to screen transformation.
		 */
		virtual	void	SetmatScreen( const CqMatrix& mat )
		{
			m_aCoordSystems[ CoordSystem_Screen ].m_matWorldTo = mat;
		}
		/** Set the world to NDC matrix.
		 * \param mat The new matrix to use as the world to NDC transformation.
		 */
		virtual	void	SetmatNDC( const CqMatrix& mat )
		{
			m_aCoordSystems[ CoordSystem_NDC ].m_matWorldTo = mat;
		}
		/** Set the world to raster matrix.
		 * \param mat The new matrix to use as the world to raster transformation.
		 */
		virtual	void	SetmatRaster( const CqMatrix& mat )
		{
			m_aCoordSystems[ CoordSystem_Raster ].m_matWorldTo = mat;
		}
		/** Set the world to camera matrix.
		 * \param mat The new matrix to use as the world to camera transformation.
		 */
		virtual	void	SetmatCamera( const CqTransform* ptrans )
		{
			m_transCamera = *ptrans;
			//m_aCoordSystems[ CoordSystem_Camera ] .m_matWorldTo =
			//m_aCoordSystems[ CoordSystem_Current ].m_matWorldTo = ptrans->GetMotionObjectInterpolated(0);
			//m_aCoordSystems[ CoordSystem_Camera ] .m_matToWorld =
			//m_aCoordSystems[ CoordSystem_Current ].m_matToWorld = ptrans->GetMotionObjectInterpolated(0).Inverse();
		}
		/** Get the current transformation stack.
		 * \return A reference to a vector of CqTransform class pointers.
		 */
		virtual std::vector<CqTransform*>&	TransformStack()
		{
			return ( m_TransformStack );
		}

		void	RegisterShader( const char* strName, EqShaderType type, IqShader* pShader );
		CqShaderRegister* FindShader( const char* strName, EqShaderType type );

		/** Set the locally stored render time.
		 * \param time System time value representing the seconds taken to render.
		 */ 
		//						void	SettimeTaken(time_t time)	{m_timeTaken=time;}
		/** Get the time taken to complete the last render in seconds.
		 */ 
		//						time_t	timeTaken() const			{return(m_timeTaken);}

		//						void		PrintStats(TqInt level);

	private:
		CqModeBlock*	m_pconCurrent;					///< Pointer to the current context.
		CqStats	m_Stats;						///< Global statistics.
		CqAttributes	m_attrDefault;					///< Default attributes.
		CqTransform	m_transDefault;					///< Default transformation.
		CqImageBuffer*	m_pImageBuffer;					///< Pointer to the current image buffer.

		IqDDManager*	m_pDDManager;

		EqRenderMode	m_Mode;
		CqList<CqShaderRegister> m_Shaders;				///< List of registered shaders.
		TqBool	m_fSaveGPrims;
		std::vector<CqTransform*>	m_TransformStack;	///< The global transformation stack.
		CqTransform	m_transCamera;					///< The camera transform.
		std::vector<SqParameterDeclaration>	m_Symbols;	///< Symbol table.

		void WhichMatWorldTo(CqMatrix &a, TqUlong thash);
		void WhichMatToWorld(CqMatrix &b, TqUlong thash);

		CqLog			m_theLog;
		CqMessageTable	m_theTable;
	public:
		std::vector<SqCoordSys>	m_aCoordSystems;		///< List of reistered coordinate systems.
}
;


inline CqRenderer* QGetRenderContext()
{
	return ( pCurrRenderer );
}


_qShareM	void	QSetRenderContext( CqRenderer* pRenderer );


//-----------------------------------------------------------------------

END_NAMESPACE( Aqsis )

//}  // End of #ifdef RENDERER_H_INCLUDED
#endif
