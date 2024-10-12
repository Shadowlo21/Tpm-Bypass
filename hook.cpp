#include "global.h"
#define FILE_DEVICE_TPM 0x00000101
#define FILE_DEVICE_TPM 0x00000101
#define IOCTL_TPM_QUERY_CAPABILITIES CTL_CODE(FILE_DEVICE_TPM, 0x0001, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TPM_SEND_COMMAND CTL_CODE(FILE_DEVICE_TPM, 0x0002, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TPM_SEND_COMMAND CTL_CODE(FILE_DEVICE_TPM, 0x0002, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define STATUS_INVALID_DATA_ISSUE (0xC0000008)
TPM2B_PUBLIC_KEY_RSA Hook::generatedKey = { 0 };
PDRIVER_DISPATCH Hook::originalDispatch = nullptr;
NTSTATUS Hook::Dispatch(PDEVICE_OBJECT device, PIRP irp)
{
    const PIO_STACK_LOCATION ioc = IoGetCurrentIrpStackLocation(irp);
    if (ioc->Parameters.DeviceIoControl.IoControlCode == IOCTL_TPM_SUBMIT_COMMAND)
    {
        irp->IoStatus.Status = STATUS_INVALID_DATA_ISSUE;
        irp->IoStatus.Information = 0; 
        IofCompleteRequest(irp, IO_NO_INCREMENT);
        return STATUS_INVALID_DATA_ISSUE;
    }
    return originalDispatch(device, irp);
}