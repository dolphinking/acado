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
 *    \file include/acado/code_generation/export_arithmetic_statement.hpp
 *    \author Hans Joachim Ferreau, Boris Houska
 *    \date 2010-2011
 */


#ifndef ACADO_TOOLKIT_EXPORT_ARITHMETIC_STATEMENT_HPP
#define ACADO_TOOLKIT_EXPORT_ARITHMETIC_STATEMENT_HPP

#include <acado/utils/acado_utils.hpp>
#include <acado/code_generation/export_statement.hpp>
#include <acado/code_generation/export_variable.hpp>
#include <acado/code_generation/export_function.hpp>



BEGIN_NAMESPACE_ACADO

/** 
 *	\brief Allows to export code of different arithmetic statements.
 *
 *	\ingroup AuxiliaryFunctionality
 *
 *	The class ExportArithmeticStatement allows to export code of different arithmetic 
 *	statements of the form:
 *
 *	lhs <op0> rhs1 <op1> rhs2 <op2> rhs3,
 *
 *	where <op0> can be "=", "+=" or "-=",
 *	<op1> can be "+", "-" or "*" and
 *	<op2> can be "+" or "-".
 *
 *	\author Hans Joachim Ferreau, Boris Houska
 */
class ExportArithmeticStatement : public ExportStatement
{
	friend class ExportVariable;

    //
    // PUBLIC MEMBER FUNCTIONS:
    //
    public:

		/** Default constructor. 
		 */
        ExportArithmeticStatement( );

		/** Constructor which takes all expressions and operators of the arithmetic statement.
		 *
		 *	@param[in] _lhs			Left-hand side expressions
		 *	@param[in] _op0			Operator between left- and right-hand side expression.
		 *	@param[in] _rhs1		First right-hand side expression.
		 *	@param[in] _op1			Operator between first and second right-hand side expression.
		 *	@param[in] _rhs2		Second right-hand side expression of arithmetic statement.
		 *	@param[in] _op2			Operator between second and third right-hand side expression.
		 *	@param[in] _rhs3		Third right-hand side expression.
		 */
		ExportArithmeticStatement(	const ExportVariable& _lhs,
									ExportStatementOperator _op0,
									const ExportVariable& _rhs1,
									ExportStatementOperator _op1,
									const ExportVariable& _rhs2,
									ExportStatementOperator _op2 = ESO_UNDEFINED,
									const ExportVariable& _rhs3 = 0
									);

		/** Copy constructor (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
        ExportArithmeticStatement(	const ExportArithmeticStatement& arg
									);

		/** Destructor.
		 */
		virtual ~ExportArithmeticStatement( );

		/** Assignment operator (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
		ExportArithmeticStatement& operator=(	const ExportArithmeticStatement& arg
												);

		/** Clone constructor (deep copy).
		 *
		 *	\return Pointer to cloned object.
		 */
		virtual ExportStatement* clone( ) const;


		/** Returns number of rows of arithmetic statement.
		 *
		 *	\return Number of rows of arithmetic statement
		 */
		uint getNumRows( ) const;

		/** Returns number of columns of arithmetic statement.
		 *
		 *	\return Number of columns of arithmetic statement
		 */
		uint getNumCols( ) const;


		/** Exports data declaration of the statement into given file. Its appearance can 
		 *  can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue exportDataDeclaration(	FILE *file,
													const String& _realString = "real_t",
													const String& _intString = "int",
													int _precision = 16
													) const;

		/** Exports source code of the statement into given file. Its appearance can 
		 *  can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue exportCode(	FILE* file,
										const String& _realString = "real_t",
										const String& _intString = "int",
										int _precision = 16
										) const;

		 returnValue allocate( memoryAllocatorPtr allocator );

	//
    // PROTECTED MEMBER FUNCTIONS:
    //
    protected:

		/** Exports source code for an addition or subtraction to given file. 
		 *  Its appearance can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement.
		 *	@param[in] _sign			String of the operation ("+" or "-").
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue exportCodeAddSubtract(	FILE* file,
											const String& _sign = "+",
											const String& _realString = "real_t",
											const String& _intString = "int",
											int _precision = 16
											) const;

		/** Exports source code for a multiplication to given file.
		 *  Its appearance can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement.
		 *	@param[in] transposeRhs1	Flag indicating whether rhs1 shall be transposed.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue exportCodeMultiply(	FILE* file,
										BooleanType transposeRhs1 = BT_FALSE,
										const String& _realString = "real_t",
										const String& _intString = "int",
										int _precision = 16
										) const;

		/** Exports source code for an assignment to given file. 
		 *  Its appearance can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement.
		 *	@param[in] _op				String of the assignment operation ("=", "+=" or "-=").
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue exportCodeAssign(	FILE* file,
										const String& _op = "=",
										const String& _realString = "real_t",
										const String& _intString = "int",
										int _precision = 16
										) const;

		/** Returns string containing the assignment operation.
		 *
		 *	@param[out] _assignString	String containing the assignment operation.
		 *
		 *	\return SUCCESSFUL_RETURN, \n
		 *	        RET_UNABLE_TO_EXPORT_STATEMENT
		 */
		returnValue getAssignString(	String& _assignString
										) const;


    protected:

		// Refactor this guys as shared pointers
		ExportVariable lhs;						/**< Left-hand side expression of arithmetic statement. */
		ExportVariable rhs1;					/**< First right-hand side expression of arithmetic statement. */
		ExportVariable rhs2;					/**< Second right-hand side expression of arithmetic statement. */
		ExportVariable rhs3;					/**< Third right-hand side expression of arithmetic statement. */

		ExportStatementOperator op0;			/**< Operator between left- and right-hand side expression of arithmetic statement. */
		ExportStatementOperator op1; 			/**< Operator between first and second right-hand side expression of arithmetic statement. */
		ExportStatementOperator op2;			/**< Operator between second and third right-hand side expression of arithmetic statement. */

		memoryAllocatorPtr memAllocator;
};


CLOSE_NAMESPACE_ACADO


#endif  // ACADO_TOOLKIT_EXPORT_ARITHMETIC_STATEMENT_HPP

// end of file.
