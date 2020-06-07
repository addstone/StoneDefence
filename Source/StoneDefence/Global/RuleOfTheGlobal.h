
#pragma once

#include "CoreMinimal.h"
#include "CachePoolManagement.h"
#include "Core/ManageCore.h"

//FManagementCore<FGlobalManagement> GManagement;
FManagementCore<FDollMeshPoolManage> GDollMeshPoolManage; 

#define GET_PTR() Get(GetWorld())

//#define GLOBAL_MANAGEMENT_MACRO() GManagement.GET_PTR()
#define DOLL_MESH_POOL_MANAGE_MACRO() GDollMeshPoolManage.GET_PTR()