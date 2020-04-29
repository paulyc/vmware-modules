/*********************************************************
 * Copyright (C) 2017 VMware, Inc. All rights reserved.
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
 * vmciKernelAPI3.h --
 *
 *    Kernel API (v3) exported from the VMCI host and guest drivers.
 */

#ifndef __VMCI_KERNELAPI_3_H__
#define __VMCI_KERNELAPI_3_H__

#define INCLUDE_ALLOW_MODULE
#define INCLUDE_ALLOW_VMK_MODULE
#define INCLUDE_ALLOW_VMKERNEL
#include "includeCheck.h"

#include "vmciKernelAPI2.h"

#if defined __cplusplus
extern "C" {
#endif


/* Define version 3. */

#undef  VMCI_KERNEL_API_VERSION
#define VMCI_KERNEL_API_VERSION_3 3
#define VMCI_KERNEL_API_VERSION   VMCI_KERNEL_API_VERSION_3


/* VMCI Detach Cause API (only available in vmkernel). */

#define VMCI_DETACH_REGULAR  0
#define VMCI_DETACH_VMOTION  1

int vmci_qpair_get_detach_cause(VMCIQPair *qpair, uint8 *cause);

#if defined __cplusplus
} // extern "C"
#endif

#endif /* !__VMCI_KERNELAPI_3_H__ */
