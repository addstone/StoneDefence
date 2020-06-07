
#pragma once

#include "CoreMinimal.h"
#include "CachePoolManagement.h"
#include "Core/ManageCore.h"
#include "GlobalManagement.h"

extern FManagementCore<FGlobalManagement> GManagement;
extern FManagementCore<FDollMeshPoolManage> GDollMeshPoolManage; 

#define GET_PTR() Get(GetWorld())

#define GLOBAL_MANAGEMENT_MACRO() GManagement.GET_PTR()
#define DOLL_MESH_POOL_MANAGE_MACRO() GDollMeshPoolManage.GET_PTR()