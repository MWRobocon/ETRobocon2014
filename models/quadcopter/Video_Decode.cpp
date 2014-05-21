#define S_FUNCTION_NAME  Video_Decode
#define S_FUNCTION_LEVEL 2



#include "simstruc.h"
#include "ardrone/ardrone.h"
#include "ardrone/uvlc.h"



/*----------------Sfunc macros----------------------------------*/
#define NUM_INPUTS          2
/* Input Port  0 */
#define IN_PORT_0_NAME      u0_packets
#define INPUT_0_WIDTH       1
#define INPUT_DIMS_0_COL    40000
#define INPUT_0_DTYPE       uint8_T
#define INPUT_0_COMPLEX     COMPLEX_NO
#define IN_0_FRAME_BASED    FRAME_NO
#define IN_0_BUS_BASED      0
#define IN_0_BUS_NAME       
#define IN_0_DIMS           2-D
#define INPUT_0_FEEDTHROUGH 1
#define IN_0_ISSIGNED        0
#define IN_0_WORDLENGTH      8
#define IN_0_FIXPOINTSCALING 1
#define IN_0_FRACTIONLENGTH  9
#define IN_0_BIAS            0
#define IN_0_SLOPE           0.125
/* Input Port  1 */
#define IN_PORT_1_NAME      u1_packet_size
#define INPUT_1_WIDTH       1
#define INPUT_DIMS_1_COL    1
#define INPUT_1_DTYPE       uint32_T
#define INPUT_1_COMPLEX     COMPLEX_NO
#define IN_1_FRAME_BASED    FRAME_NO
#define IN_1_BUS_BASED      0
#define IN_1_BUS_NAME       
#define IN_1_DIMS           1-D
#define INPUT_1_FEEDTHROUGH 1
#define IN_1_ISSIGNED        0
#define IN_1_WORDLENGTH      8
#define IN_1_FIXPOINTSCALING 1
#define IN_1_FRACTIONLENGTH  9
#define IN_1_BIAS            0
#define IN_1_SLOPE           0.125

#define NPARAMS              0

#define SAMPLE_TIME_0        INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 1
#define SOURCEFILES "__SFB__"
#define PANELINDEX           6
#define USE_SIMSTRUCT        0
#define SHOW_COMPILE_STEPS   0                   
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0
/*--------------------------------------------------------------*/

/*Define some video format related stuff*/
#define format_width  640
#define format_height  360

int isInitialized = 0;

unsigned long int seq = 1;
char ip[16];
    


#define MDL_START                      /* Change to #undef to remove function */
#if defined(MDL_START)
static void mdlStart(SimStruct *S)
{

    
}
#endif /*  MDL_START */



/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Initialize the sizes array
 */
static void mdlInitializeSizes(SimStruct *S)
{
    
    /*-----Inputs-------------*/
    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);
     if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
	 return; /* Parameter mismatch will be reported by Simulink */
     }

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, 2)) return;
    /*Input Port 0 */
    inputDimsInfo.width = INPUT_0_WIDTH;
    ssSetInputPortDimensionInfo(S,  0, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 0, INPUT_0_WIDTH, INPUT_DIMS_0_COL);
    ssSetInputPortFrameData(S,  0, IN_0_FRAME_BASED);

    ssSetInputPortDataType(S, 0, SS_UINT8);
    ssSetInputPortComplexSignal(S,  0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /*Input Port 1 */
    ssSetInputPortWidth(S,  1, INPUT_1_WIDTH); /* */
    ssSetInputPortDataType(S, 1, SS_UINT32);
    ssSetInputPortComplexSignal(S,  1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/
    /*-----Outputs-------------*/
       
    /* Allow signal dimensions greater than 2 */
    ssAllowSignalsWithMoreThan2D(S);
    
    /* Set number of input and output ports */
    if (!ssSetNumOutputPorts(S,1)) return;
    
    /* Set dimensions of input and output ports */
    
        int_T my_dims[3]; //create a 3x3x3 matrix
   
        DECL_AND_INIT_DIMSINFO(di); /* Initializes structure */
            
        my_dims[0] = format_height;
        my_dims[1] = format_width;
        my_dims[2] = 3;
            
        di.width   = format_height*format_width*3;
        di.numDims = 3;
        di.dims    = my_dims;
        if(!ssSetOutputPortDimensionInfo(S, 0, &di)) return;
    
         
    ssSetNumSampleTimes(S, 1);
     
    /*----------*/
    
    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR | 
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
  
} /* end mdlInitializeSizes */


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
  ssSetInputPortDataType( S, 0, SS_DOUBLE);
 ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

/* Function: mdlOutputs =======================================================
 * Abstract:
 *   Compute the outputs of the S-function.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T            *y     = ssGetOutputPortRealSignal(S,0);
	unsigned char OutputValue;
    unsigned int total_packets;
    unsigned char fill_buffer[122880];
    int increment = 0;

    unsigned char  *u0_packets  = (unsigned char*) ssGetInputPortSignal(S,0); //packet vector
    unsigned int   *u1_packet_size  = (unsigned int*) ssGetInputPortSignal(S,1); //packet size
   
    
    total_packets = u1_packet_size[0]; //grab packet size

    // Video
    AVFormatContext *pFormatCtx;
    AVCodecContext  *pCodecCtx;
    AVFrame         *pFrame, *pFrameBGR;
    uint8_t  *bufferBGR;
    SwsContext      *pConvertCtx;

    pFormatCtx  = NULL;
    pCodecCtx   = NULL;
    pFrame      = NULL;
    pFrameBGR   = NULL;
    bufferBGR   = NULL;
    pConvertCtx = NULL;  

    // Initialize FFmpeg
    av_register_all();
    avformat_network_init();
    av_log_set_level(AV_LOG_QUIET);
     
     // Set codec
	pCodecCtx = avcodec_alloc_context3(NULL);
	pCodecCtx->width = format_width;
	pCodecCtx->height = format_height;
     
    bufferBGR = (uint8_t*)av_mallocz(avpicture_get_size(PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height) * sizeof(uint8_t));    


	if (total_packets > 0) {
    // Decode UVLC video
	 UVLC::DecodeVideo(u0_packets, total_packets, bufferBGR, &pCodecCtx->width, &pCodecCtx->height);
    }
    
    int BGRsize = avpicture_get_size(PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height) * sizeof(uint8_t);
    int total_count = 0;    

    
    for (int i = 0;i<format_height; i++) //height
    {
        for (int j=0;j<format_width;j++) //width
        {
            for (int k=2;k>=0;k--)//reverse order since output is BGR, very annoying
            {
            //*(output + k + j*3 +i*9) = total_count; //column wise
           // *(y + (format_height*format_width)*k + j*format_height + i) = *(bufferBGR + total_count);  //row wise
            *(y + (format_height*format_width)*k + j*format_height + i)  = *(bufferBGR + total_count);
                total_count = total_count + 1;
            }
        }
    
    }
    // Deallocate the buffer
    av_free(bufferBGR);
    bufferBGR = NULL;
    
    // Deallocate the codec
    avcodec_close(pCodecCtx);
    pCodecCtx = NULL;
    
    
  

} /* end mdlOutputs */





/* Function: mdlTerminate =====================================================
 * Abstract:
 *    Called when the simulation is terminated.
 */
static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S); /* unused input argument */

 
} /* end mdlTerminate */

#ifdef	MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif

/* [EOF] sfun_matadd.c */
