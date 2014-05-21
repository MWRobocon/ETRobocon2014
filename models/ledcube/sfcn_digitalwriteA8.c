
#define S_FUNCTION_NAME  sfcn_digitalwriteA8
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

/*================*
 * Build checking *
 *================*/
/*
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
static void mdlCheckParameters(SimStruct *S)
{
    // size_t    nu;
    // char_T    *plusMinusStr;
    
    //*plusMinusStr = ssGetSFcnParam(S,0);
    // nu=mxGetNumberOfElements(SIGNS_PARAM(S));
    //ssPrintf(*plusMinusStr);

}
#endif
*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 1);
//	ssSetSFcnParamTunable(S, 0, 1);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    
    if (!ssSetNumInputPorts(S, 1)) return;
    
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    ssSetInputPortDataType(S, 0, DYNAMICALLY_TYPED);
    
    if (!ssSetNumOutputPorts(S,0)) return;

    ssSetNumSampleTimes(S, 1);
 }

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy that we inherit our sample time from the driving block.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S); 
    ssSetSFcnParamTunable(S,0,false);
}

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{
}

void mdlOutputs(SimStruct *S, int_T tid)
{
}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
