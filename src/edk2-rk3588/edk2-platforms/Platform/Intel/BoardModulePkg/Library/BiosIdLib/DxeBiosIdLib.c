/** @file
  Boot service DXE BIOS ID library implementation.

  These functions in this file can be called during DXE and cannot be called during runtime
  or in SMM which should use a RT or SMM library.


Copyright (c) 2015 - 2023, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BiosIdLib.h>

#include <Guid/BiosId.h>

/**
  This function returns BIOS ID by searching HOB or FV.
  It also debug print the BIOS ID found.

  @param[out] BiosIdImage   The BIOS ID got from HOB or FV. It is optional,
                            no BIOS ID will be returned if it is NULL as input.

  @retval EFI_SUCCESS               BIOS ID has been got successfully.
  @retval EFI_NOT_FOUND             BIOS ID image is not found, and no parameter will be modified.

**/
EFI_STATUS
EFIAPI
GetBiosId (
  OUT BIOS_ID_IMAGE  *BiosIdImage OPTIONAL
  )
{
  EFI_STATUS     Status;
  BIOS_ID_IMAGE  TempBiosIdImage;
  VOID           *Address;
  UINTN          Size;

  Address = NULL;
  Size    = 0;

  if (BiosIdImage == NULL) {
    //
    // It is NULL as input, so no BIOS ID will be returned.
    // Use temp buffer to hold the BIOS ID.
    //
    BiosIdImage = &TempBiosIdImage;
  }

  Address = GetFirstGuidHob (&gBiosIdGuid);
  if (Address != NULL) {
    Size = sizeof (BIOS_ID_IMAGE);
    CopyMem ((VOID *)BiosIdImage, GET_GUID_HOB_DATA (Address), Size);

    DEBUG ((DEBUG_INFO, "DXE get BIOS ID from HOB successfully\n"));
    DEBUG ((DEBUG_INFO, "BIOS ID: %s\n", (CHAR16 *)(&(BiosIdImage->BiosIdString))));
    return EFI_SUCCESS;
  }

  Status = GetSectionFromAnyFv (
             &gBiosIdGuid,
             EFI_SECTION_RAW,
             0,
             &Address,
             &Size
             );
  if ((Status == EFI_SUCCESS) && (Address != NULL)) {
    //
    // BIOS ID image is present in FV.
    //
    Size = sizeof (BIOS_ID_IMAGE);
    CopyMem ((VOID *)BiosIdImage, Address, Size);
    //
    // GetSectionFromAnyFv () allocated buffer for Address, now free it.
    //
    FreePool (Address);

    DEBUG ((DEBUG_INFO, "DXE get BIOS ID from FV successfully\n"));
    DEBUG ((DEBUG_INFO, "BIOS ID: %s\n", (CHAR16 *)(&(BiosIdImage->BiosIdString))));
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_ERROR, "DXE get BIOS ID failed: %r\n", EFI_NOT_FOUND));
  return EFI_NOT_FOUND;
}
