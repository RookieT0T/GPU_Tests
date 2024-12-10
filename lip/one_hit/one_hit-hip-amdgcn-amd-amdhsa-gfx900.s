	.text
	.amdgcn_target "amdgcn-amd-amdhsa--gfx900"
	.protected	_Z6kernelPi             ; -- Begin function _Z6kernelPi
	.globl	_Z6kernelPi
	.p2align	8
	.type	_Z6kernelPi,@function
_Z6kernelPi:                            ; @_Z6kernelPi
_Z6kernelPi$local:
; %bb.0:
	s_load_dwordx2 s[0:1], s[4:5], 0x0
	s_waitcnt lgkmcnt(0)
	s_add_u32 s2, s0, 0x40000
	s_addc_u32 s3, s1, 0
	s_add_u32 s4, s0, 0x80000
	v_mov_b32_e32 v2, s2
	s_addc_u32 s5, s1, 0
	v_mov_b32_e32 v3, s3
	s_add_u32 s2, s0, 0xc0000
	s_addc_u32 s3, s1, 0
	v_mov_b32_e32 v4, s4
	v_mov_b32_e32 v5, s5
	s_add_u32 s4, s0, 0x100000
	s_addc_u32 s5, s1, 0
	v_mov_b32_e32 v7, s3
	v_mov_b32_e32 v6, s2
	s_add_u32 s2, s0, 0x140000
	s_addc_u32 s3, s1, 0
	s_add_u32 s6, s0, 0x180000
	s_addc_u32 s7, s1, 0
	s_add_u32 s8, s0, 0x1c0000
	s_addc_u32 s9, s1, 0
	s_add_u32 s10, s0, 0x200000
	s_addc_u32 s11, s1, 0
	s_add_u32 s12, s0, 0x240000
	s_addc_u32 s13, s1, 0
	s_add_u32 s14, s0, 0x280000
	s_addc_u32 s15, s1, 0
	s_add_u32 s16, s0, 0x2c0000
	s_addc_u32 s17, s1, 0
	s_add_u32 s18, s0, 0x300000
	s_addc_u32 s19, s1, 0
	s_add_u32 s20, s0, 0x340000
	s_addc_u32 s21, s1, 0
	s_add_u32 s22, s0, 0x380000
	s_addc_u32 s23, s1, 0
	s_add_u32 s24, s0, 0x3c0000
	s_addc_u32 s25, s1, 0
	s_add_u32 s26, s0, 4
	s_addc_u32 s27, s1, 0
	s_add_u32 s28, s0, 0x400000
	s_addc_u32 s29, s1, 0
	v_mov_b32_e32 v0, s0
	v_mov_b32_e32 v1, s1
	s_add_u32 s0, s0, 8
	s_addc_u32 s1, s1, 0
	v_mov_b32_e32 v9, s5
	v_mov_b32_e32 v11, s3
	v_mov_b32_e32 v13, s7
	v_mov_b32_e32 v15, s9
	v_mov_b32_e32 v17, s11
	v_mov_b32_e32 v19, s13
	v_mov_b32_e32 v21, s15
	v_mov_b32_e32 v23, s17
	v_mov_b32_e32 v25, s19
	v_mov_b32_e32 v27, s21
	v_mov_b32_e32 v29, s23
	v_mov_b32_e32 v31, s25
	v_mov_b32_e32 v33, s27
	v_mov_b32_e32 v35, s29
	v_mov_b32_e32 v37, s1
	v_mov_b32_e32 v8, s4
	v_mov_b32_e32 v10, s2
	v_mov_b32_e32 v12, s6
	v_mov_b32_e32 v14, s8
	v_mov_b32_e32 v16, s10
	v_mov_b32_e32 v18, s12
	v_mov_b32_e32 v20, s14
	v_mov_b32_e32 v22, s16
	v_mov_b32_e32 v24, s18
	v_mov_b32_e32 v26, s20
	v_mov_b32_e32 v28, s22
	v_mov_b32_e32 v30, s24
	v_mov_b32_e32 v32, s26
	v_mov_b32_e32 v34, s28
	v_mov_b32_e32 v36, s0
	;;#ASMSTART
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	buffer_wbinvl1
	flat_load_dwordx2 v[0:1], v[0:1] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[2:3], v[2:3] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[4:5], v[4:5] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[6:7], v[6:7] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[8:9], v[8:9] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[10:11], v[10:11] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[12:13], v[12:13] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[14:15], v[14:15] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[16:17], v[16:17] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[18:19], v[18:19] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[20:21], v[20:21] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[22:23], v[22:23] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[24:25], v[24:25] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[26:27], v[26:27] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[28:29], v[28:29] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[30:31], v[30:31] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[32:33], v[32:33] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[34:35], v[34:35] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	flat_load_dwordx2 v[36:37], v[36:37] glc
	s_waitcnt vmcnt(0) & lgkmcnt(0)
	s_nop 0
	
	;;#ASMEND
	s_endpgm
	.section	.rodata,#alloc
	.p2align	6
	.amdhsa_kernel _Z6kernelPi
		.amdhsa_group_segment_fixed_size 0
		.amdhsa_private_segment_fixed_size 0
		.amdhsa_user_sgpr_private_segment_buffer 1
		.amdhsa_user_sgpr_dispatch_ptr 0
		.amdhsa_user_sgpr_queue_ptr 0
		.amdhsa_user_sgpr_kernarg_segment_ptr 1
		.amdhsa_user_sgpr_dispatch_id 0
		.amdhsa_user_sgpr_flat_scratch_init 0
		.amdhsa_user_sgpr_private_segment_size 0
		.amdhsa_system_sgpr_private_segment_wavefront_offset 0
		.amdhsa_system_sgpr_workgroup_id_x 1
		.amdhsa_system_sgpr_workgroup_id_y 0
		.amdhsa_system_sgpr_workgroup_id_z 0
		.amdhsa_system_sgpr_workgroup_info 0
		.amdhsa_system_vgpr_workitem_id 0
		.amdhsa_next_free_vgpr 38
		.amdhsa_next_free_sgpr 30
		.amdhsa_reserve_vcc 0
		.amdhsa_reserve_flat_scratch 0
		.amdhsa_float_round_mode_32 0
		.amdhsa_float_round_mode_16_64 0
		.amdhsa_float_denorm_mode_32 3
		.amdhsa_float_denorm_mode_16_64 3
		.amdhsa_dx10_clamp 1
		.amdhsa_ieee_mode 1
		.amdhsa_fp16_overflow 0
		.amdhsa_exception_fp_ieee_invalid_op 0
		.amdhsa_exception_fp_denorm_src 0
		.amdhsa_exception_fp_ieee_div_zero 0
		.amdhsa_exception_fp_ieee_overflow 0
		.amdhsa_exception_fp_ieee_underflow 0
		.amdhsa_exception_fp_ieee_inexact 0
		.amdhsa_exception_int_div_zero 0
	.end_amdhsa_kernel
	.text
.Lfunc_end0:
	.size	_Z6kernelPi, .Lfunc_end0-_Z6kernelPi
                                        ; -- End function
	.section	.AMDGPU.csdata
; Kernel info:
; codeLenInByte = 704
; NumSgprs: 30
; NumVgprs: 38
; ScratchSize: 0
; MemoryBound: 0
; FloatMode: 240
; IeeeMode: 1
; LDSByteSize: 0 bytes/workgroup (compile time only)
; SGPRBlocks: 3
; VGPRBlocks: 9
; NumSGPRsForWavesPerEU: 30
; NumVGPRsForWavesPerEU: 38
; Occupancy: 6
; WaveLimiterHint : 0
; COMPUTE_PGM_RSRC2:USER_SGPR: 6
; COMPUTE_PGM_RSRC2:TRAP_HANDLER: 0
; COMPUTE_PGM_RSRC2:TGID_X_EN: 1
; COMPUTE_PGM_RSRC2:TGID_Y_EN: 0
; COMPUTE_PGM_RSRC2:TGID_Z_EN: 0
; COMPUTE_PGM_RSRC2:TIDIG_COMP_CNT: 0
	.ident	"clang version 12.0.0 (/src/external/llvm-project/clang 1100ebe275a9dcc79a9abbda902b6f10738f2f5d)"
	.section	".note.GNU-stack"
	.addrsig
	.amdgpu_metadata
---
amdhsa.kernels:
  - .args:
      - .address_space:  global
        .offset:         0
        .size:           8
        .value_kind:     global_buffer
      - .offset:         8
        .size:           8
        .value_kind:     hidden_global_offset_x
      - .offset:         16
        .size:           8
        .value_kind:     hidden_global_offset_y
      - .offset:         24
        .size:           8
        .value_kind:     hidden_global_offset_z
      - .address_space:  global
        .offset:         32
        .size:           8
        .value_kind:     hidden_none
      - .address_space:  global
        .offset:         40
        .size:           8
        .value_kind:     hidden_none
      - .address_space:  global
        .offset:         48
        .size:           8
        .value_kind:     hidden_none
      - .address_space:  global
        .offset:         56
        .size:           8
        .value_kind:     hidden_multigrid_sync_arg
    .group_segment_fixed_size: 0
    .kernarg_segment_align: 8
    .kernarg_segment_size: 64
    .language:       OpenCL C
    .language_version:
      - 2
      - 0
    .max_flat_workgroup_size: 256
    .name:           _Z6kernelPi
    .private_segment_fixed_size: 0
    .sgpr_count:     30
    .sgpr_spill_count: 0
    .symbol:         _Z6kernelPi.kd
    .vgpr_count:     38
    .vgpr_spill_count: 0
    .wavefront_size: 64
amdhsa.version:
  - 1
  - 0
...

	.end_amdgpu_metadata
