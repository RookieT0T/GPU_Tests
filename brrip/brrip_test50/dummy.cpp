#include "hip/hip_runtime.h"
#define HCC_ENABLE_PRINTF
#include <stdio.h>
#include <stdlib.h>

// define enough entries to fit all of addresses we want to access
#define CACHE_ENTRIES 512

// Access pattern: A, C, E, G, A, I, G, E, K, A, I
// Each letter represents a 64-byte address range, 16 integers
/*
arr[0]  ->  arr[15]:  Cache Line A
arr[16] ->  arr[31]:  Cache Line B
arr[32] ->  arr[47]:  Cache Line C
arr[48] ->  arr[63]:  Cache Line D
arr[64] ->  arr[79]:  Cache Line E
arr[80] ->  arr[95]:  Cache Line F
arr[96] ->  arr[111]: Cache Line G
arr[112] -> arr[127]: Cache Line H
arr[128] -> arr[143]: Cache Line I
arr[144] -> arr[159]: Cache Line J
arr[160] -> arr[175]: Cache Line K
arr[176] -> arr[191]: Cache Line L
arr[192] -> arr[207]: Cache Line M
arr[208] -> arr[223]: Cache Line N
arr[224] -> arr[239]: Cache Line O
arr[240] -> arr[255]: Cache Line P
*/

// The [] indicate two different sets, and each set has four ways.
// [set0way0, set0way1, set0way2, set0way3],
// [set1way0, set1way1, set1way2, set1way3],
// If you have a 512B cache with 4-way associativity, and each cache line is 64B with BRRIP replacement policy, you will observe:
// m, m, m, m, --> first 4 accesses A C E G
// h, m, h, m, m, m, m --> the next 7 accesses A I G E K A I

// Explanation of this result:
// A, C, E, G are misses, now the cache stores
// ([A_3*, C_2, E_3, G_2],[ , , ,])
// Number after the underscore is the BRRIP vals of the corresponding cache line; *indicates the candidate for the replacement
// A hits
// Now the cache stores ([A_2, C_2, E_3*, G_2],[ , , ,]).
// I misses
// Now the cache stores ([A_2, C_2, I_3*, G_2],[ , , ,]).
// G hits
// Now the cache stores ([A_2, C_2, I_3*, G_1],[ , , ,]).
// E misses
// Now the cache stores ([A_2*, C_2, E_2, G_1],[ , , ,]).
// K misses
// Now the cache stores ([K_3*, C_3, E_3, G_2],[ , , ,]).
// A misses
// Now the cache stores ([A_2, C_3*, E_3, G_2],[ , , ,]).
// I misses
// Now the cache stores ([A_2, I_3*, E_3, G_2],[ , , ,]).

__global__ void kernel(int * arr, uint64_t * dummy) {
  // every array location is 4B wide, so given a cache of size N and associativity M, we can figure out which addresses map to which indices
  uint64_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0;
  asm volatile(                                       // asm for assembly code, volatile for no compiler optimizations
	       "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
	       "buffer_wbinvl1\n\t"
                // use placeholders (%[name]) to refer to input and output operands
                // flat_load_dwordx2, 64 bits or 8 bytes? the first two integers at each cache line?
               "flat_load_dwordx2 %[out0], %[in1] glc\n\t"    // access A
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out2], %[in3] glc\n\t"    // access C
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out4], %[in5] glc\n\t"    // access E
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out6], %[in7] glc\n\t"    // access G
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out8], %[in9] glc\n\t"    // access A
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out10], %[in11] glc\n\t"  // access I
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out12], %[in13] glc\n\t"  // access G
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out14], %[in15] glc\n\t"  // access E
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out16], %[in17] glc\n\t"  // access K
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out18], %[in19] glc\n\t"  // access A
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out20], %[in21] glc\n\t"  // access I
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "s_nop 0\n\t"
    : [out0]"=v"(a), [out2]"=v"(b), [out4]"=v"(c), [out6]"=v"(d), [out8]"=v"(e), [out10]"=v"(f), [out12]"=v"(g), [out14]"=v"(h), [out16]"=v"(i), [out18]"=v"(j), [out20]"=v"(k)
	  
    : [in1]"v"((uint64_t *)&arr[0]), [in3]"v"((uint64_t *)&arr[32]), [in5]"v"((uint64_t *)&arr[64]), [in7]"v"((uint64_t *)&arr[96]), [in9]"v"((uint64_t *)&arr[1]),
		  [in11]"v"((uint64_t *)&arr[128]), [in13]"v"((uint64_t *)&arr[97]), [in15]"v"((uint64_t *)&arr[65]), [in17]"v"((uint64_t *)&arr[160]), [in19]"v"((uint64_t *)&arr[2]),
      [in21]"v"((uint64_t *)&arr[129])
    
    :"memory"
              );
}

int main(){
    int *arr = (int *)calloc(sizeof(int), CACHE_ENTRIES);         // with initiaization to 0s, allocated memory space for emulating the interactions to the caches
    uint64_t *dummy = (uint64_t *)calloc(sizeof(uint64_t), 1);

    int *arr_g;
    uint64_t *dummy_g;

    hipMallocManaged(&arr_g, CACHE_ENTRIES*sizeof(int));          // allocates a block of memory that is accessible from both the CPU and GPU
    hipMallocManaged(&dummy_g, CACHE_ENTRIES*sizeof(uint64_t));

    // initialize arr_g with arr
    hipMemcpy(arr_g, arr, CACHE_ENTRIES*sizeof(int), hipMemcpyHostToDevice);

    // just want 1 GPU thread to run our kernel
    // kernel: name of the kernel function to be executed on the GPU
    // gridDim, dim3(1): number of thread blocks
    // blockDim, dim3(1): the number of threads in each thread block
    // sharedMem: 0
    // stream: 0
    // args of calling the kernel functions
    hipLaunchKernelGGL(kernel, dim3(1), dim3(1), 0, 0, arr_g, dummy_g);   // The kernel operates on the data in dummy_g, 
                                                                          // possibly updating its value based on computations or memory accesses.

    // copy dummy value back to ensure compiler doesn't optimize out anything because instructions in the kernel
    // are just loading & results of computations are not used
    hipMemcpy(dummy, dummy_g, 1*sizeof(uint64_t), hipMemcpyDeviceToHost);
    printf("Dummy value = %lu\n", dummy[0]);

    hipFree(arr_g);
    hipFree(dummy_g);
    free(arr);
    free(dummy);
    return 0;
}
