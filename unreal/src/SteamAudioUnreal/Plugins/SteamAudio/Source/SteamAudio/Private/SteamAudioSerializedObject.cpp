//
// Copyright 2017-2023 Valve Corporation.
//

#include "SteamAudioSerializedObject.h"
#include "AssetRegistry/AssetRegistryModule.h"
#if ((ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 0) || (ENGINE_MAJOR_VERSION > 5))
#include "UObject/SavePackage.h"
#endif
#include "UObject/UObjectGlobals.h"

// ---------------------------------------------------------------------------------------------------------------------
// USteamAudioSerializedObject
// ---------------------------------------------------------------------------------------------------------------------

USteamAudioSerializedObject* USteamAudioSerializedObject::SerializeObjectToPackage(IPLSerializedObject SerializedObject, const FString& AssetName)
{
    int DataSize = iplSerializedObjectGetSize(SerializedObject);
    uint8* DataBuffer = iplSerializedObjectGetData(SerializedObject);

    FString PackageName;
    FString ObjectName;
    if (!AssetName.Split(".", &PackageName, &ObjectName))
        return nullptr;

    // Create an empty package.
    UPackage* Package = CreatePackage(*PackageName);
    if (!Package)
        return nullptr;

    Package->FullyLoad();

    // Create a new UObject in the package that will hold the data from the IPLSerializedObject.
    USteamAudioSerializedObject* Object = NewObject<USteamAudioSerializedObject>(Package, *ObjectName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
    if (!Object)
        return nullptr;

    // Copy the data into the UObject.
    Object->Data.SetNum(DataSize);
    FMemory::Memcpy(Object->Data.GetData(), DataBuffer, DataSize);

    // Save the package.
    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(Object);
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
#if ((ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 0) || (ENGINE_MAJOR_VERSION > 5))
    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.SaveFlags = RF_Public | RF_Standalone;
    if (!UPackage::SavePackage(Package, Object, *PackageFileName, SavePackageArgs))
        return nullptr;
#else
    if (!UPackage::SavePackage(Package, Object, RF_Public | RF_Standalone, *PackageFileName))
        return nullptr;
#endif

    return Object;
}
