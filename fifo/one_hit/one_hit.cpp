#include "hip/hip_runtime.h"
#define HCC_ENABLE_PRINTF
#include <stdio.h>
#include <stdlib.h>

// define enough entries to fit all of addresses we want to access
#define CACHE_ENTRIES 4194304

// kernel code
// Access pattern: a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, a
// Access count: 17
// If you have a 4MB cache with 16-way associativity, and each cache
// line is 64B with FIFO replacement policy, you will observe:
// a to p will be all misses, a will hit
// 16 misses, 1 hit

__global__ void kernel(int * arr) {
  // every array location is 4B wide, so given a cache of size N and associativity M, we can figure out which addresses map to which indices

  uint64_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
  asm volatile(
	  /*
		Ensure any initializing code is not being cached before code we care about.
    */
    // load all entries with wait between each
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "buffer_wbinvl1\n\t"
    "flat_load_dwordx2 %[out0], %[in1] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out2], %[in3] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out4], %[in5] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out6], %[in7] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out8], %[in9] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out10], %[in11] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out12], %[in13] glc\n\t" 
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out14], %[in15] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out16], %[in17] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out18], %[in19] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out20], %[in21] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out22], %[in23] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out24], %[in25] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out26], %[in27] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out28], %[in29] glc\n\t" 
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out30], %[in31] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out32], %[in33] glc\n\t"
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "s_nop 0\n\t"

    : 
    [out0]"=v"(a), [out2]"=v"(b), [out4]"=v"(c), [out6]"=v"(d), 
    [out8]"=v"(e), [out10]"=v"(f), [out12]"=v"(g), [out14]"=v"(h), 
    [out16]"=v"(i), [out18]"=v"(j), [out20]"=v"(k), [out22]"=v"(l), 
    [out24]"=v"(m), [out26]"=v"(n), [out28]"=v"(o), [out30]"=v"(p), 
    [out32]"=v"(q)
    
    /*each entry is 64b, so 64*1024 = 65536, and 0 represents first entry a, 
    65536 represents second entry b, 131072 represents entry c and so on*/
    : 
    [in1]"v"((uint64_t *)&arr[0]), [in3]"v"((uint64_t *)&arr[65536]), 
    [in5]"v"((uint64_t *)&arr[131072]), [in7]"v"((uint64_t *)&arr[196608]), 
    [in9]"v"((uint64_t *)&arr[262144]), [in11]"v"((uint64_t *)&arr[327680]), 
    [in13]"v"((uint64_t *)&arr[393216]), [in15]"v"((uint64_t *)&arr[458752]), 
    [in17]"v"((uint64_t *)&arr[524288]), [in19]"v"((uint64_t *)&arr[589824]),
    [in21]"v"((uint64_t *)&arr[655360]), [in23]"v"((uint64_t *)&arr[720896]), 
    [in25]"v"((uint64_t *)&arr[786432]), [in27]"v"((uint64_t *)&arr[851968]),
    [in29]"v"((uint64_t *)&arr[917504]), [in31]"v"((uint64_t *)&arr[983040]), 
    [in33]"v"((uint64_t *)&arr[1])

    :"memory"
               );
}

// host code
int main(){
    int *arr = (int *)calloc(sizeof(int), CACHE_ENTRIES);
    //uint64_t *dummy = (uint64_t *)calloc(sizeof(uint64_t), 1);

    int *arr_g;
    //uint64_t *dummy_g;

    hipMallocManaged(&arr_g, CACHE_ENTRIES*sizeof(int));
    //hipMallocManaged(&dummy_g, CACHE_ENTRIES*sizeof(uint64_t));

    // initialize arr_g with arr
    hipMemcpy(arr_g, arr, CACHE_ENTRIES*sizeof(int), hipMemcpyHostToDevice);

    // just want 1 GPU thread to run our kernel
    hipLaunchKernelGGL(kernel, dim3(1), dim3(1), 0, 0,  arr_g);

    // copy dummy value back to ensure compiler doesn't optimize out anything
    //hipMemcpy(dummy, dummy_g, 1*sizeof(uint64_t), hipMemcpyDeviceToHost);
    //printf("Dummy value = %lu\n", dummy[0]);

    hipFree(arr_g);
    //hipFree(dummy_g);
    free(arr);
    //free(dummy);
    return 0;
}
