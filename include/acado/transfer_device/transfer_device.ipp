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
 *    \file include/acado/transfer_device/transfer_device.ipp
 *    \author Hans Joachim Ferreau, Boris Houska
 */



BEGIN_NAMESPACE_ACADO


//
// PUBLIC MEMBER FUNCTIONS:
//

inline uint TransferDevice::getDim( ) const
{
	return lastSignal.getNumValues( );
}


inline BooleanType TransferDevice::isEmpty( ) const
{
	if ( getDim( ) == 0 )
		return BT_TRUE;
	else
		return BT_FALSE;
}



inline BooleanType TransferDevice::hasNoise( ) const
{
	if ( additiveNoise == 0 )
		return BT_FALSE;
	else
	{
		for( uint i=0; i<getDim(); ++i )
			if ( additiveNoise[i] != 0 )
				return BT_TRUE;
	}

	return BT_FALSE;
}


inline BooleanType TransferDevice::hasDeadTime( ) const
{
	if ( deadTimes.getDim() == 0 )
		return BT_FALSE;

	if ( deadTimes.isNegative( ) == BT_TRUE )
		return BT_FALSE;
	else
		return BT_TRUE;
}



//
// PROTECTED MEMBER FUNCTIONS:
//



CLOSE_NAMESPACE_ACADO



/*
 *	end of file
 */
