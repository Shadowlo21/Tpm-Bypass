#include "global.h"
EXTERN_C NTSTATUS Entry()
{

	NTSTATUS status;
	UNICODE_STRING driverName;
	RtlInitUnicodeString(&driverName, L"\\Driver\\TPM");
	PDRIVER_OBJECT driverObject;
	status = Utils::ObReferenceObjectByName(&driverName, OBJ_CASE_INSENSITIVE, nullptr, 0,
		*Utils::IoDriverObjectType, KernelMode, nullptr,
		reinterpret_cast<PVOID*>(&driverObject));
	if (!NT_SUCCESS(status))
		return status;
	Hook::originalDispatch = driverObject->MajorFunction[0];
	for (DWORD i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		driverObject->MajorFunction[i] = &Hook::Dispatch;

	return STATUS_SUCCESS;
}