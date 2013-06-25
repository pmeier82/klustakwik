/*
 * parameters.h
 *
 * This file is just used to declare the parameters that are shared across
 * several files.
 *
 *  Created on: 11 Nov 2011
 *      Author: dan
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "numerics.h"

enum type_t {FLOAT = 'f', INT = 'd',  BOOLEAN = 'b', STRING = 's'};

#define FLOAT_PARAM(name) add_param(FLOAT, #name, &name)
#define INT_PARAM(name) add_param(INT, #name, &name)
#define BOOLEAN_PARAM(name) add_param(BOOLEAN, #name, &name)
#define STRING_PARAM(name) add_param(STRING, #name, name)

#define STRLEN 10000

// This parameters table gives the command line parameters that are loaded into
// global variables. The Param type is the macro used to load the parameter from
// the command line, defined above. The Name is the variable name. The
// Definition is the standard C++ definition of the variable without the default
// value which is given by Default. This table is used in three places, below
// the parameters are defined with an extern so that multiple files can access
// the same global variables, e.g. extern int ElecNo;. In parameters.cpp the
// variables are instantiated and given their default values, e.g.
// int ElecNo = 1;. In parameters.cpp the parameters are read from the command
// line, e.g. INT_PARAM(ElecNo).
//  F(Documentation,
//    Param type,    Name,                Definition,                Default)
#define PARAMETERS_TABLE(F)                                                    \
	F("Filename base, files are of the form FileBase.fet.ElecNo, etc.",        \
	  STRING_PARAM,  FileBase,            char FileBase[STRLEN],     "electrode")\
	F("Electrode number, files are of the form FileBase.fet.ElecNo, etc.",     \
	  INT_PARAM,     ElecNo,              int ElecNo,                1        )\
	F("Minimum number of clusters to be used without splitting.",              \
	  INT_PARAM,     MinClusters,         int MinClusters,           20       )\
	F("Maximum number of clusters to be used without splitting.",              \
	  INT_PARAM,     MaxClusters,         int MaxClusters,           30       )\
	F("Maximum possible number of clusters to be used after splitting.",       \
	  INT_PARAM,     MaxPossibleClusters, int MaxPossibleClusters,   100      )\
	F("Number of times to start count from each number of clusters.",          \
	  INT_PARAM,     nStarts,             int nStarts,               1        )\
	F("Specify random seed for reproducible results, or leave for random.",    \
	  INT_PARAM,     RandomSeed,          int RandomSeed,            1        )\
	F("Whether or not to run in debug mode (prints lots of detail). 0 = None, 1 = Partial info, 2=Full Info",          \
	  INT_PARAM, Debug,                   char Debug,                0        )\
	F("Whether or not to print information as the program runs.",              \
	  INT_PARAM,     Verbose,             int Verbose,               1        )\
	F("String of 0s and 1s indicating which features to use.",                 \
	  STRING_PARAM,  UseFeatures,         char UseFeatures[STRLEN],  "11111111111100001")\
	F("???",                                                                   \
	  INT_PARAM,     DistDump,            int DistDump,              0        )\
	F("Points this far from best do not get an E step recomputation.",         \
	  FLOAT_PARAM,   DistThresh,          scalar DistThresh,         (scalar)log(1000))\
	F("There is a full E step recomputation at least after this many iterations.",\
	  INT_PARAM,     FullStepEvery,       int FullStepEvery,         20       )\
	F("If this fraction of points changed class last time, do a full step.",   \
	  FLOAT_PARAM,   ChangedThresh,       scalar ChangedThresh,      .05      )\
	F("Whether or not to save information to a log file.",                     \
	  BOOLEAN_PARAM, Log,                 char Log,                  1        )\
	F("Log output to screen.",                                                 \
	  BOOLEAN_PARAM, Screen,              char Screen,               1        )\
	F("Maximum number of iterations.",                                         \
	  INT_PARAM,     MaxIter,             int MaxIter,               500      )\
	F("An intermediate cluster file to use as a starting point.",              \
	  STRING_PARAM,  StartCluFile,        char StartCluFile[STRLEN], ""       )\
	F("Allow cluster splitting after this many iterations.",                   \
	  INT_PARAM,     SplitEvery,          int SplitEvery,            40       )\
	F("Coefficient of 2*num_params to use in penalty (1 for AIC).",            \
	  FLOAT_PARAM,   PenaltyK,            scalar PenaltyK,           0.0      )\
	F("Coefficient of num_params*log(num_points)/2 to use in penalty (1 for BIC).",\
	  FLOAT_PARAM,   PenaltyKLogN,         scalar PenaltyKLogN,      1.0      )\
	F("Do clustering on 1/Subset points, and then generalise to whole set.",   \
	  INT_PARAM,     Subset,              int Subset,                1        )\
	F("Number of 'PriorPoints'",                                               \
	  INT_PARAM,   PriorPoint,            int PriorPoint,            1        )\
	F("Save FileBase.sorted.*.ElecNo data files (data in sorted order).",      \
	  BOOLEAN_PARAM, SaveSorted,          char SaveSorted,           false    )\
	F("Save covariance and means",                                             \
	  BOOLEAN_PARAM, SaveCovarianceMeans, char SaveCovarianceMeans,  false    )\
	F("Use mask based initial conditions",                                     \
	  BOOLEAN_PARAM, UseMaskedInitialConditions, char UseMaskedInitialConditions, false)\
	F("Assign to first closest mask in mask based initial conditions",         \
	  BOOLEAN_PARAM, AssignToFirstClosestMask, char AssignToFirstClosestMask, false)\
	F("Use distributional EM steps",                                           \
	  BOOLEAN_PARAM, UseDistributional,   char UseDistributional,    false    )  

//TODO: Implement the two Debug modes, one less verbose than the other

#define STRINGIFY(x) #x

// These four lines define how to make the extern definitions, the full
// instantiation of the variables, the inputting of the
// parameters and the documentation (in parameters.cpp)
#define EXTERN_PARAMETERS(DOC, TYPE, NAME, DEF, VAL) extern DEF;
#define DEFINE_PARAMETERS(DOC, TYPE, NAME, DEF, VAL) DEF = VAL;
#define INPUT_PARAMETERS(DOC, TYPE, NAME, DEF, VAL) TYPE(NAME);
#define PRINT_PARAMETERS(DOC, TYPE, NAME, DEF, VAL) \
	fprintf(stderr, "- " STRINGIFY(NAME) " = " STRINGIFY(VAL) "\n" \
		    "  " DOC "\n\n");

PARAMETERS_TABLE(EXTERN_PARAMETERS)

//////////// FUNCTIONS TO READ PARAMETERS FROM COMMAND LINE ////////////////////

void add_param(int t, char *name, void *addr);
int change_param(char *name, char *value);
void init_params(int argc, char **argv);
void print_params(FILE *fp);
void SetupParams(int argc, char **argv);

#endif /* PARAMETERS_H_ */