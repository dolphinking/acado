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
 *    \file include/acado/integrator/integrator_export.hpp
 *    \author Hans Joachim Ferreau, Boris Houska, Rien Quirynen
 *    \date 2010-2011
 */


#ifndef ACADO_TOOLKIT_INTEGRATOR_EXPORT_HPP
#define ACADO_TOOLKIT_INTEGRATOR_EXPORT_HPP

#include <acado/utils/acado_utils.hpp>
#include <acado/matrix_vector/matrix_vector.hpp>
#include <acado/code_generation/export_algorithm.hpp>
#include <acado/code_generation/model_data.hpp>


BEGIN_NAMESPACE_ACADO


/** 
 *	\brief Allows to export a tailored integrator for fast model predictive control.
 *
 *	\ingroup NumericalAlgorithms
 *
 *	The class IntegratorExport allows to export a tailored integrator
 *	for fast model predictive control.
 *
 *	\author Hans Joachim Ferreau, Boris Houska, Rien Quirynen
 */
class IntegratorExport : public ExportAlgorithm
{
    //
    // PUBLIC MEMBER FUNCTIONS:
    //

    public:

		/** Default constructor. 
		 *
		 *	@param[in] _userInteraction		Pointer to corresponding user interface.
		 *	@param[in] _commonHeaderName	Name of common header file to be included.
		 */
        IntegratorExport(	UserInteraction* _userInteraction = 0,
							const String& _commonHeaderName = ""
							);

		/** Copy constructor (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
        IntegratorExport(	const IntegratorExport& arg
							);

        /** Destructor. 
		 */
        virtual ~IntegratorExport( );

		/** Assignment operator (deep copy).
		 *
		 *	@param[in] arg		Right-hand side object.
		 */
		IntegratorExport& operator=(	const IntegratorExport& arg
										);


		/** Initializes export of a tailored integrator.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setup( ) = 0;


		/** Assigns Differential Equation to be used by the integrator.
		 *
		 *	@param[in] rhs		Right-hand side expression.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		
		virtual returnValue setDifferentialEquation( const Expression& rhs ) = 0;


		/** .
		 *
		 *	@param[in] 		.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setLinearInput( const Matrix& M1, const Matrix& A1, const Matrix& B1 );


		/** .
		 *
		 *	@param[in] 		.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setLinearOutput( const Matrix& M3, const Matrix& A3, const Expression& rhs );


		/** .
		 *
		 *	@param[in] 		.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setLinearOutput( const Matrix& M3, const Matrix& A3, const String& _rhs3, const String& _diffs_rhs3 );


		/** Assigns the model to be used by the integrator.
		 *
		 *	@param[in] _name_ODE			Name of the function, evaluating the ODE right-hand side.
		 *	@param[in] _name_diffs_ODE		Name of the function, evaluating the derivatives of the ODE right-hand side.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */

		virtual returnValue setModel( 	const String& _name_ODE,
										const String& _name_diffs_ODE );


		/** Sets a polynomial NARX model to be used by the integrator.
		 *
		 *	@param[in] delay		The delay for the states in the NARX model.
		 *	@param[in] parms		The parameters defining the polynomial NARX model.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */

		virtual returnValue setNARXmodel( const uint delay, const Matrix& parms ) = 0;


		/** Passes all the necessary model data to the integrator.
		 *
		 *	@param[in] data			The model data.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setModelData( 	const ModelData& data  );


		/** Exports the code needed to update the sensitivities of the states, defined by the linear input system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue updateInputSystem( 	ExportStatementBlock* block,
												const ExportIndex& index1,
												const ExportIndex& index2,
												const ExportIndex& tmp_index  	);


		/** Exports the code needed to propagate the sensitivities of the states, defined by the linear input system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue propagateInputSystem( 	ExportStatementBlock* block,
													const ExportIndex& index1,
													const ExportIndex& index2,
													const ExportIndex& index3,
													const ExportIndex& tmp_index  	);


		/** Exports the code needed to update the sensitivities of the states defined by the nonlinear, fully implicit system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue updateImplicitSystem( 	ExportStatementBlock* block,
													const ExportIndex& index1,
													const ExportIndex& index2,
													const ExportIndex& tmp_index  	);


		/** Exports the code needed to propagate the sensitivities of the states defined by the nonlinear, fully implicit system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue propagateImplicitSystem( 	ExportStatementBlock* block,
														const ExportIndex& index1,
														const ExportIndex& index2,
														const ExportIndex& index3,
														const ExportIndex& tmp_index  	);


		/** Exports the code needed to update the sensitivities of the states, defined by the linear output system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue updateOutputSystem( 	ExportStatementBlock* block,
													const ExportIndex& index1,
													const ExportIndex& index2,
													const ExportIndex& tmp_index  	);


		/** Exports the code needed to propagate the sensitivities of the states, defined by the linear output system.
		 *
		 *	@param[in] block			The block to which the code will be exported.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue propagateOutputSystem( 	ExportStatementBlock* block,
													const ExportIndex& index1,
													const ExportIndex& index2,
													const ExportIndex& index3,
													const ExportIndex& tmp_index  	);


		/** Sets integration grid (this grid is expected to be non equidistant, otherwise use the other setGrid function).
		 *
		 *	@param[in] _grid		integration grid
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue setGrid(	const Grid& _grid   );


		/** Adds all data declarations of the auto-generated integrator to given list of declarations.
		 *
		 *	@param[in] declarations		List of declarations.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getDataDeclarations(	ExportStatementBlock& declarations,
													ExportStruct dataStruct = ACADO_ANY
													) const = 0;


		/** Adds all function (forward) declarations of the auto-generated integrator to given list of declarations.
		 *
		 *	@param[in] declarations		List of declarations.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getFunctionDeclarations(	ExportStatementBlock& declarations
														) const = 0;



		/** Exports source code of the auto-generated integrator into the given directory.
		 *
		 *	@param[in] code				Code block containing the auto-generated integrator.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue getCode(	ExportStatementBlock& code
										) = 0;
							
        
        /** Sets up the output with the grids for the different output functions.									\n
		*                                                                      										\n
		*  \param outputGrids_	  	The vector containing a grid for each output function.			  				\n
		*  \param rhs 	  	  		The expressions corresponding the output functions.								\n
		*                                                                      										\n
		*  \return SUCCESSFUL_RETURN
		*/
		virtual returnValue setupOutput( const std::vector<Grid> outputGrids_,
									  const std::vector<Expression> rhs ) = 0;


        /** Sets up the output with the grids for the different output functions.									\n
		*                                                                      										\n
		*  \param outputGrids_	  		The vector containing a grid for each output function.			  			\n
		*  \param _outputNames 	  		The names of the output functions.									  		\n
		*  \param _diffs_outputNames 	The names of the functions, evaluating the derivatives of the outputs.		\n
		*  \param _dims_output 			The dimensions of the output functions.										\n
		*                                                                      										\n
		*  \return SUCCESSFUL_RETURN
		*/
		virtual returnValue setupOutput(  const std::vector<Grid> outputGrids_,
									  	  const std::vector<String> _outputNames,
									  	  const std::vector<String> _diffs_outputNames,
										  const std::vector<uint> _dims_output ) = 0;


		/** Sets up the output with the grids for the different output functions.										\n
		 *                                                                      										\n
		 *  \param outputGrids_	  			The vector containing a grid for each output function.			  			\n
		 *  \param _outputNames 	  		The names of the output functions.									  		\n
		 *  \param _diffs_outputNames 		The names of the functions, evaluating the derivatives of the outputs.		\n
		 *  \param _dims_output 			The dimensions of the output functions.										\n
		 *  \param _outputDependencies		A separate dependency matrix for each output.								\n
		 *                                                                      										\n
		 *  \return SUCCESSFUL_RETURN
		 */
		virtual returnValue setupOutput(  const std::vector<Grid> outputGrids_,
									  	  const std::vector<String> _outputNames,
									  	  const std::vector<String> _diffs_outputNames,
										  const std::vector<uint> _dims_output,
										  const std::vector<Matrix> _outputDependencies ) = 0;


		/** Returns the grid of the integrator. 	\n
		* 
		*  \return SUCCESSFUL_RETURN          		\n
		*/
		virtual returnValue getGrid( Grid& grid_ ) const;


		/** Returns the number of integration steps along the prediction horizon. 	\n
		* 
		*  \return SUCCESSFUL_RETURN          		\n
		*/
		virtual returnValue getNumSteps( Vector& _numSteps ) const;
		
		
		/** Returns the output expressions. 	\n
		* 
		*  \return SUCCESSFUL_RETURN          	\n
		*/
		virtual returnValue getOutputExpressions( std::vector<Expression>& outputExpressions_ ) const;


		/** Returns the output grids. 			\n
		* 
		*  \return SUCCESSFUL_RETURN          	\n
		*/
		virtual returnValue getOutputGrids( std::vector<Grid>& outputGrids_ ) const;


		/** Returns whether the grid is equidistant.	\n
		 *  
		 * \return BT_TRUE  iff the grid is equidistant, BT_FALSE otherwise. \n
		 */
		virtual BooleanType equidistantControlGrid( ) const;


		const String getNameRHS() const;
		const String getNameDiffsRHS() const;
		virtual const String getNameFullRHS() const;

		const String getNameOutputRHS() const;
		const String getNameOutputDiffs() const;

		const String getNameOUTPUT( uint index ) const;
		const String getNameDiffsOUTPUT( uint index ) const;
		uint getDimOUTPUT( uint index ) const;



	protected:


		/** .
		 *
		 *	@param[in] A3			.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		Matrix expandOutputMatrix( const Matrix& A3 );


		/** Copies all class members from given object.
		 *
		 *	@param[in] arg		Right-hand side object.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue copy(	const IntegratorExport& arg
							);


		/** Frees internal dynamic memory to yield an empty function.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue clear( );


		/** Prepares a function that evaluates the complete right-hand side.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue prepareFullRhs( );


		/**	Get the index of the integration interval, corresponding a certain time.
		 *
		 * 	@param[in] time		The time.
		 *
		 *	\return The index of the integration interval.
		 */
		uint getIntegrationInterval( double time );


		/** Returns the largest global export variable.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual ExportVariable getAuxVariable() const = 0;


    protected:

		uint NX1;
		uint NX2;
		uint NX3;
		uint NDX3;
		uint NXA3;

		BooleanType timeDependant;

		Matrix M11, A11, B11;
		Matrix A33, M33;

        BooleanType exportRhs;				/**< True if the right-hand side and their derivatives should be exported too. */
        BooleanType crsFormat;				/**< True if the CRS format is used for the jacobian of output functions. */
        String name_rhs;					/**< The name of the function evaluating the ODE right-hand side, if provided. */
        String name_diffs_rhs;				/**< The name of the function evaluating the derivatives of the ODE right-hand side, if provided. */
        String name_rhs3;					/**< The name of the nonlinear function in the linear output system, if provided. */
        String name_diffs_rhs3;				/**< The name of the function evaluating the derivatives for the linear output system, if provided. */

		Grid grid;							/**< Evaluation grid along the prediction horizon. */
		Vector numSteps;					/**< The number of integration steps per shooting interval. */

		ExportFunction fullRhs;				/**< Function that evaluates the full right-hand side. */
		ExportVariable	rhs_in;
		ExportVariable	rhs_out;
		
		ExportFunction integrate;			/**< Function that integrates the exported ODE. */
		ExportODEfunction rhs;				/**< Module to export ODE. */
		ExportODEfunction diffs_rhs;		/**< Module to export the evaluation of the derivatives of the ordinary differential equations. */

		ExportODEfunction lin_input;

		ExportODEfunction rhs3;
		ExportODEfunction diffs_rhs3;

		ExportVariable  error_code;			/**< Variable containing the error code, returned by the integrator. */
		ExportVariable  reset_int;			/**< Variable containing the number of the current integration step. */
		ExportVariable  rk_index;			/**< Variable containing the number of the current shooting interval. */
		ExportVariable 	rk_ttt;				/**< Variable containing the integration time. */
		ExportVariable 	rk_xxx;				/**< Variable containing the current integrator state. */
		ExportVariable 	rk_eta;				/**< Variable containing the inputs or the results of the integrator. */

		ExportVariable	rk_diffsPrev1;
		ExportVariable	rk_diffsNew1;
		
		ExportVariable  rk_diffsPrev2;			/**< Variable containing the sensitivities from the previous integration step. */
		ExportVariable  rk_diffsNew2;			/**< Variable containing the derivatives wrt the previous values. */

		ExportVariable	rk_diffsNew3;
		ExportVariable	rk_diffsPrev3;

		DifferentialState 			x;		/**< The differential states in the model. */
		DifferentialStateDerivative dx;		/**< The differential state derivatives in the model. */
		AlgebraicState	  			z;		/**< The algebraic states in the model. */
		Control           			u;		/**< The control inputs in the model. */
		Parameter         			p;		/**< The parameters in the model. */

        std::vector<Grid> outputGrids;					/**< A separate grid for each output. */
        std::vector<Expression> outputExpressions;		/**< A separate expression for each output. */
        std::vector<Matrix> outputDependencies;			/**< A separate dependency matrix for each output. */
        std::vector<ExportODEfunction> outputs;			/**< Module to export output functions. */
        std::vector<ExportODEfunction> diffs_outputs;	/**< Module to export the evaluation of the derivatives of the output functions. */
		
        std::vector<String> name_outputs;				/**< A separate function name for each output. */
        std::vector<String> name_diffs_outputs;			/**< A separate function name for evaluating the derivatives of each output. */
        std::vector<uint> num_outputs;					/**< A separate dimension for each output. */
};


/** Summarizes all available integrators for code generation.  */
enum ExportIntegratorType{

     INT_EX_EULER,         	/**< Explicit Euler method.           */
     INT_RK2,         	 	/**< Explicit Runge-Kutta integrator of order 2.           */
     INT_RK3,         	 	/**< Explicit Runge-Kutta integrator of order 3.           */
     INT_RK4,         	 	/**< Explicit Runge-Kutta integrator of order 4.           */
     INT_IRK_GL2,			/**< Gauss-Legendre integrator of order 2 (Continuous output Implicit Runge-Kutta). */
     INT_IRK_GL4,			/**< Gauss-Legendre integrator of order 4 (Continuous output Implicit Runge-Kutta). */
     INT_IRK_GL6,			/**< Gauss-Legendre integrator of order 6 (Continuous output Implicit Runge-Kutta). */
     INT_IRK_GL8,			/**< Gauss-Legendre integrator of order 8 (Continuous output Implicit Runge-Kutta). */

     INT_IRK_RIIA1,			/**< Radau IIA integrator of order 1 (Continuous output Implicit Runge-Kutta). */
     INT_IRK_RIIA3,			/**< Radau IIA integrator of order 3 (Continuous output Implicit Runge-Kutta). */
     INT_IRK_RIIA5,			/**< Radau IIA integrator of order 5 (Continuous output Implicit Runge-Kutta). */

     INT_DIRK3,				/**< Diagonally Implicit 2-stage Runge-Kutta integrator of order 3 (Continuous output). */
     INT_DIRK4,				/**< Diagonally Implicit 3-stage Runge-Kutta integrator of order 4 (Continuous output). */
     INT_DIRK5,				/**< Diagonally Implicit 5-stage Runge-Kutta integrator of order 5 (Continuous output). */

     INT_DT,				/**< An algorithm which handles the simulation and sensitivity generation for a discrete time state-space model. */
     INT_NARX				/**< An algorithm which handles the simulation and sensitivity generation for a NARX model. */
};


/**  Summarizes all possible sensitivity generation types for exported integrators.  */
enum ExportSensitivityType{

	NO_SENSITIVITY, 				/**< No sensitivities are computed, if possible. 		  					 */
    FORWARD,    					/**< Sensitivities are computed in forward mode.                             */
    BACKWARD,    					/**< Sensitivities are computed in backward mode.                            */
    FORWARD_OVER_BACKWARD         	/**< Sensitivities (first and second order) are computed.					 */
};


CLOSE_NAMESPACE_ACADO


#endif  // ACADO_TOOLKIT_INTEGRATOR_EXPORT_HPP

// end of file.
