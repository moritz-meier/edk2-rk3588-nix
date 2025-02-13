/** @file
  Platform PEI module include file.

  Copyright (c) 2022 Loongson Technology Corporation Limited. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <IndustryStandard/Pci22.h>

/**
  Create system type  memory range hand off block.

  @param  MemoryBase    memory base address.
  @param  MemoryLimit  memory length.

  @return  VOID
**/
VOID
AddMemoryBaseSizeHob (
  EFI_PHYSICAL_ADDRESS        MemoryBase,
  UINT64                      MemorySize
  );

/**
  Create  memory range hand off block.

  @param  MemoryBase    memory base address.
  @param  MemoryLimit  memory length.

  @return  VOID
**/
VOID
AddMemoryRangeHob (
  EFI_PHYSICAL_ADDRESS        MemoryBase,
  EFI_PHYSICAL_ADDRESS        MemoryLimit
  );

/**
  Create Reserved type memory range hand off block.

  @param  MemoryBase    memory base address.
  @param  MemoryLimit  memory length.

  @return  VOID
**/
VOID
AddReservedMemoryBaseSizeHob (
  EFI_PHYSICAL_ADDRESS        MemoryBase,
  UINT64                      MemorySize
  );
/**
  Publish PEI core memory

  @return EFI_SUCCESS     The PEIM initialized successfully.
**/
EFI_STATUS
PublishPeiMemory (
  VOID
  );
/**
  Publish system RAM and reserve memory regions

  @return  VOID
**/
VOID
InitializeRamRegions (
  VOID
  );

/**
  Publish PEI & DXE (Decompressed) Memory based FVs to let PEI
  and DXE know about them.

  @retval EFI_SUCCESS   Platform PEI FVs were initialized successfully.
**/
EFI_STATUS
PeiFvInitialization (
  VOID
  );

#endif // PLATFORM_H_
