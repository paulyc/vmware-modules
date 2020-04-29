/*********************************************************
 * Copyright (C) 1998-2019 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 *********************************************************/

/*
 * includeCheck.h --
 *
 *      Restrict include file use.
 *
 * In every .h file, define one or more of these
 *
 *      INCLUDE_ALLOW_VMX
 *      INCLUDE_ALLOW_USERLEVEL
 *      INCLUDE_ALLOW_VMCORE
 *      INCLUDE_ALLOW_MODULE
 *      INCLUDE_ALLOW_VMKERNEL
 *      INCLUDE_ALLOW_DISTRIBUTE
 *      INCLUDE_ALLOW_VMK_MODULE
 *      INCLUDE_ALLOW_VMKDRIVERS
 *      INCLUDE_ALLOW_MKS
 *
 * Then include this file.
 *
 * Any file that has INCLUDE_ALLOW_DISTRIBUTE defined will potentially
 * be distributed in source form along with GPLed code.  Ensure
 * that this is acceptable.
 */


#if defined VMCORE && \
    !(defined VMX86_VMX || defined VMM || \
      defined MONITOR_APP || defined VMMON)
#error "Makefile problem: VMCORE without VMX86_VMX or \
        VMM or MONITOR_APP or MODULE."
#endif

#if defined VMCORE && !defined INCLUDE_ALLOW_VMCORE
#error "The surrounding include file is not allowed in vmcore."
#endif
#undef INCLUDE_ALLOW_VMCORE

#if defined VMX86_VMX && !defined VMCORE && \
    !defined INCLUDE_ALLOW_VMX && !defined INCLUDE_ALLOW_USERLEVEL && \
    !defined INCLUDE_ALLOW_MKS
#error "The surrounding include file is not allowed in the VMX."
#endif
#undef INCLUDE_ALLOW_VMX

#if defined USERLEVEL && !defined VMX86_VMX && !defined VMCORE && \
    !defined ULM && !defined INCLUDE_ALLOW_USERLEVEL && \
    !defined INCLUDE_ALLOW_MKS
#error "The surrounding include file is not allowed at userlevel."
#endif
#undef INCLUDE_ALLOW_USERLEVEL

#if defined MODULE && !defined VMKERNEL_MODULE && \
    !defined VMMON && !defined INCLUDE_ALLOW_MODULE
#error "The surrounding include file is not allowed in driver modules."
#endif
#undef INCLUDE_ALLOW_MODULE

#if defined VMMON && !defined INCLUDE_ALLOW_VMMON
#error "The surrounding include file is not allowed in vmmon."
#endif
#undef INCLUDE_ALLOW_VMMON

#if defined VMKERNEL && !defined INCLUDE_ALLOW_VMKERNEL
#error "The surrounding include file is not allowed in the vmkernel."
#endif
#undef INCLUDE_ALLOW_VMKERNEL

#if defined GPLED_CODE && !defined INCLUDE_ALLOW_DISTRIBUTE
#error "The surrounding include file is not allowed in GPL code."
#endif
#undef INCLUDE_ALLOW_DISTRIBUTE

#if defined VMKERNEL_MODULE && !defined VMKERNEL && \
    !defined INCLUDE_ALLOW_VMK_MODULE && !defined INCLUDE_ALLOW_VMKDRIVERS
#error "The surrounding include file is not allowed in vmkernel modules."
#endif
#undef INCLUDE_ALLOW_VMK_MODULE
#undef INCLUDE_ALLOW_VMKDRIVERS

#if defined INCLUDE_ALLOW_MKS && !(defined COREMKS)
#error "The surrounding include file is not allowed outside of the MKS."
#endif
#undef INCLUDE_ALLOW_MKS
