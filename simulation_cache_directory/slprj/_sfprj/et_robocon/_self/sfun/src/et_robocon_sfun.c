/* Include files */

#include "et_robocon_sfun.h"
#include "et_robocon_sfun_debug_macros.h"
#include "c1_et_robocon.h"
#include "c3_et_robocon.h"
#include "c5_et_robocon.h"
#include "c6_et_robocon.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _et_roboconMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void et_robocon_initializer(void)
{
}

void et_robocon_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_et_robocon_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_et_robocon_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_et_robocon_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_et_robocon_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_et_robocon_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_et_robocon_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1672790321U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1855544311U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2578566411U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3066133057U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2060979339U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1636334390U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1606571439U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2217122078U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_et_robocon_get_check_sum(mxArray *plhs[]);
          sf_c1_et_robocon_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_et_robocon_get_check_sum(mxArray *plhs[]);
          sf_c3_et_robocon_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_et_robocon_get_check_sum(mxArray *plhs[]);
          sf_c5_et_robocon_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_et_robocon_get_check_sum(mxArray *plhs[]);
          sf_c6_et_robocon_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3061339410U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1991824845U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3599338742U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2357874978U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(995180232U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1124554616U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(255601431U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(411628822U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_et_robocon_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "RxviHg1rywCTsDUVT4QDRE") == 0) {
          extern mxArray *sf_c1_et_robocon_get_autoinheritance_info(void);
          plhs[0] = sf_c1_et_robocon_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "RxviHg1rywCTsDUVT4QDRE") == 0) {
          extern mxArray *sf_c3_et_robocon_get_autoinheritance_info(void);
          plhs[0] = sf_c3_et_robocon_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "qNFFu9jZEgkqjbMsk9ENiG") == 0) {
          extern mxArray *sf_c5_et_robocon_get_autoinheritance_info(void);
          plhs[0] = sf_c5_et_robocon_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "jnUWg4NzD0rcvza4KUhmPH") == 0) {
          extern mxArray *sf_c6_et_robocon_get_autoinheritance_info(void);
          plhs[0] = sf_c6_et_robocon_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_et_robocon_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_et_robocon_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_et_robocon_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_et_robocon_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_et_robocon_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_et_robocon_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_et_robocon_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_et_robocon_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_et_robocon_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_et_robocon_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c1_et_robocon_third_party_uses_info(void);
          plhs[0] = sf_c1_et_robocon_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c3_et_robocon_third_party_uses_info(void);
          plhs[0] = sf_c3_et_robocon_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "4si99QGgkJlWQnRBQM6VmC") == 0) {
          extern mxArray *sf_c5_et_robocon_third_party_uses_info(void);
          plhs[0] = sf_c5_et_robocon_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "v7AKAthIgjmREtY1dlgLkH") == 0) {
          extern mxArray *sf_c6_et_robocon_third_party_uses_info(void);
          plhs[0] = sf_c6_et_robocon_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_et_robocon_jit_fallback_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c1_et_robocon_jit_fallback_info(void);
          plhs[0] = sf_c1_et_robocon_jit_fallback_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c3_et_robocon_jit_fallback_info(void);
          plhs[0] = sf_c3_et_robocon_jit_fallback_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "4si99QGgkJlWQnRBQM6VmC") == 0) {
          extern mxArray *sf_c5_et_robocon_jit_fallback_info(void);
          plhs[0] = sf_c5_et_robocon_jit_fallback_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "v7AKAthIgjmREtY1dlgLkH") == 0) {
          extern mxArray *sf_c6_et_robocon_jit_fallback_info(void);
          plhs[0] = sf_c6_et_robocon_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_et_robocon_updateBuildInfo_args_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c1_et_robocon_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_et_robocon_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
          extern mxArray *sf_c3_et_robocon_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_et_robocon_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "4si99QGgkJlWQnRBQM6VmC") == 0) {
          extern mxArray *sf_c5_et_robocon_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_et_robocon_updateBuildInfo_args_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "v7AKAthIgjmREtY1dlgLkH") == 0) {
          extern mxArray *sf_c6_et_robocon_updateBuildInfo_args_info(void);
          plhs[0] = sf_c6_et_robocon_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void sf_et_robocon_get_post_codegen_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  unsigned int chartFileNumber = (unsigned int) mxGetScalar(prhs[0]);
  char tpChksum[64];
  mxGetString(prhs[1], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  switch (chartFileNumber) {
   case 1:
    {
      if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
        extern mxArray *sf_c1_et_robocon_get_post_codegen_info(void);
        plhs[0] = sf_c1_et_robocon_get_post_codegen_info();
        return;
      }
    }
    break;

   case 3:
    {
      if (strcmp(tpChksum, "uN34Br7YX6RGoYgHO4VLjD") == 0) {
        extern mxArray *sf_c3_et_robocon_get_post_codegen_info(void);
        plhs[0] = sf_c3_et_robocon_get_post_codegen_info();
        return;
      }
    }
    break;

   case 5:
    {
      if (strcmp(tpChksum, "4si99QGgkJlWQnRBQM6VmC") == 0) {
        extern mxArray *sf_c5_et_robocon_get_post_codegen_info(void);
        plhs[0] = sf_c5_et_robocon_get_post_codegen_info();
        return;
      }
    }
    break;

   case 6:
    {
      if (strcmp(tpChksum, "v7AKAthIgjmREtY1dlgLkH") == 0) {
        extern mxArray *sf_c6_et_robocon_get_post_codegen_info(void);
        plhs[0] = sf_c6_et_robocon_get_post_codegen_info();
        return;
      }
    }
    break;

   default:
    break;
  }

  plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
}

void et_robocon_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _et_roboconMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "et_robocon","sfun",0,4,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_et_roboconMachineNumber_,
    0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_et_roboconMachineNumber_,0);
}

void et_robocon_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_et_robocon_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("et_robocon",
      "et_robocon");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_et_robocon_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
