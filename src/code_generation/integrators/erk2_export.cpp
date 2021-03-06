/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau, K.U.Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC) under
 *    supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



/**
 *    \file src/code_generation/erk2_export.cpp
 *    \author Rien Quirynen
 *    \date 2012
 */

#include <acado/code_generation/integrators/erk2_export.hpp>

#include <acado/code_generation/export_algorithm_factory.hpp>

BEGIN_NAMESPACE_ACADO


//
// PUBLIC MEMBER FUNCTIONS:
//

ExplicitRungeKutta2Export::ExplicitRungeKutta2Export(	UserInteraction* _userInteraction,
									const String& _commonHeaderName
									) : ExplicitRungeKuttaExport( _userInteraction,_commonHeaderName )
{
	numStages = 2;
}


ExplicitRungeKutta2Export::ExplicitRungeKutta2Export(	const ExplicitRungeKutta2Export& arg
									) : ExplicitRungeKuttaExport( arg )
{
	numStages = 2;
	copy( arg );
}


ExplicitRungeKutta2Export::~ExplicitRungeKutta2Export( )
{
	clear( );
}


// PROTECTED:

//
// Register the integrator
//

IntegratorExport* createExplicitRungeKutta2Export(	UserInteraction* _userInteraction,
													const String &_commonHeaderName)
{
	Matrix AA(2,2);
	Vector bb(2);
	Vector cc(2);

	AA(0,0) = 0.0;		AA(0,1) = 0.0;
	AA(1,0) = 1.0/2.0;	AA(1,1) = 0.0;

	bb(0) = 0.0;
	bb(1) = 1.0;

	cc(0) = 0.0;
	cc(1) = 1.0/2.0;

	ExplicitRungeKuttaExport* integrator = createExplicitRungeKuttaExport(_userInteraction, _commonHeaderName);
	integrator->initializeButcherTableau(AA, bb, cc);

	return integrator;
}

RegisterExplicitRungeKutta2Export::RegisterExplicitRungeKutta2Export()
{
	IntegratorExportFactory::instance().registerAlgorithm(INT_RK2, createExplicitRungeKutta2Export);
}

CLOSE_NAMESPACE_ACADO

// end of file.
