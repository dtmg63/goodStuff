//  New benchmark for both a 1D and 2D forward and backward in-place complex FFT benchmark
//  using cuFFT and g++


// Includes, system
#include <iostream>
#include <cmath>

// Includes, project
#include <cufft.h>
#include <helper_cuda.h>

#define FFT_SIZE   65536
#define BATCH_SIZE 1

using namespace std;

//==========================================================================================

int main(int argc, char** argv)
{

    std::cout << "........ Starting cuFFT benchmark" << std::endl;
    
    //---- Step 1: Check for system GPU(s)
    //----------------------------------------------------------     
    int device_count = 0, device = -1;
    checkCudaErrors(cudaGetDeviceCount(&device_count) );
    std::cout << "......... Found " << device_count << " devices" << std::endl;
    
    if (device_count > 0) {
        device = 0;
        checkCudaErrors(cudaSetDevice(device));
    }
    else {
        std::cout << "Found error: No cuda devices present. Stopping." << std::endl;
        return(0);
    }
    
    
    //---- Step 2: Use only 1 GPU; set up cuda timers
    //----------------------------------------------------------
    cudaEvent_t startF, stopF, startB, stopB;
    
    checkCudaErrors(cudaEventCreate(&startF));
    checkCudaErrors(cudaEventCreate(&stopF));     
    checkCudaErrors(cudaEventCreate(&startB));
    checkCudaErrors(cudaEventCreate(&stopB));   
    
    //---- Step 3: Set up the cufft plan; allocate host and device memory. 
    //----------------------------------------------------------   
    cufftComplex *d_array = NULL;
    cufftComplex *h_array = new cuComplex[FFT_SIZE];
    checkCudaErrors(cudaMalloc((void**)&d_array, FFT_SIZE * sizeof(cufftComplex)));
    
    cufftHandle plan;
    checkCudaErrors( cufftPlan1d(&plan, FFT_SIZE, CUFFT_C2C, BATCH_SIZE) );
    
        
    //---- Step 4: Fill the allocated memory with values
    //----------------------------------------------------------
    for (int i = 0; i < FFT_SIZE; ++i) {
        h_array[i].x = 1.0;
        h_array[i].y = 1.0;
    }
       
    checkCudaErrors(cudaMemcpy(d_array, h_array, FFT_SIZE * sizeof(cufftComplex), cudaMemcpyHostToDevice));
    
    //---- Step 5: Run the forward inplace FFT, check the values
    //----------------------------------------------------------    
    checkCudaErrors(cudaEventRecord(startF, 0));
    
      checkCudaErrors(cufftExecC2C(plan, d_array, d_array, CUFFT_FORWARD));
        
    checkCudaErrors(cudaEventRecord(stopF, 0));
    checkCudaErrors(cudaDeviceSynchronize());
    
    // copy back to host; check answer
    checkCudaErrors(cudaMemcpy(h_array, d_array, FFT_SIZE*sizeof(cufftComplex), cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaEventSynchronize(stopF));

    
    if (h_array[0].x != FFT_SIZE && h_array[0].y != FFT_SIZE ) {
        std::cout << " Error in forward FFT result: values returned are: (" << h_array[0].x << ", " << h_array[0].y << ")" << std::endl;
    }
    else {
        std::cout << "For now let's assume the forward FFT is ok...check to make certain everything else is 0.0 " << std::endl;
    }
    
    //---- Step 6: Run the backward inplace FFT, check the values (normalize?)
    //----------------------------------------------------------     
    checkCudaErrors(cudaEventRecord(startB, 0));
    
      checkCudaErrors(cufftExecC2C(plan, d_array, d_array, CUFFT_INVERSE));
        
    checkCudaErrors(cudaEventRecord(stopB, 0));
    checkCudaErrors(cudaDeviceSynchronize());
    
    // copy back to host; check answer
    checkCudaErrors(cudaMemcpy(h_array, d_array, FFT_SIZE*sizeof(cufftComplex), cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaEventSynchronize(stopB)); 
    
    int numErrors = 0;
    for (int i = 0; i< FFT_SIZE; ++i){ 
        if (h_array[i].x != FFT_SIZE) numErrors+=1;  // Remember...we didn't normalize.
        if (h_array[i].y != FFT_SIZE) numErrors+=1;   
    }
    if (numErrors > 0)
        std::cout << " !!!! Found " << numErrors << " errors in Backward FFT !!!!! " << std::endl;
        
/*        
    for (int i = 0; i < 10; ++i) {
       std::cout << "( " << (float)h_array[i].x << " , " << (float)h_array[i].y << " )" << std::endl;
    }
*/
    
    //---- Step 7: Timing results
    //----------------------------------------------------------    
    float millisecsF = 0.;
    float millisecsB = 0.;
    cudaEventElapsedTime(&millisecsF, startF, stopF);
    cudaEventElapsedTime(&millisecsB, startB, stopB);
    
    
    std::cout << "...... Forward FFT:   " << millisecsF * 1.e3 << " microsecs" << std::endl;
    std::cout << "...... Backward FFT:  " << millisecsB * 1.e3 << " microsecs" << std::endl;
    
    int nFLOPS = 5 * FFT_SIZE * BATCH_SIZE * log2( FFT_SIZE * BATCH_SIZE);
    
    std::cout << ".....  Forward computational throughput:  " << (float)nFLOPS/(millisecsF * 1.e-3) * 1.e-9 << " GFlops" << std::endl;
    std::cout << ".....  Inverse computational throughput:  " << (float)nFLOPS/(millisecsB * 1.e-3) * 1.e-9 << " GFlops" << std::endl;
    
    //---- Step 8: Cleanup allocated memory
    //---------------------------------------------------------- 
    delete[]  h_array;
    checkCudaErrors(cudaFree(d_array));
    checkCudaErrors(cufftDestroy(plan));
    
    
    
    std::cout << "........ Finishing cuFFT benchmark" << std::endl;
    return( 0 );
}

