//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/pxr.h"
#include "usdMaya/query.h"

#include "usdMaya/usdPrimProvider.h"
#include "usdMaya/util.h"

#include "pxr/base/arch/systemInfo.h"
#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/resolverContext.h"
#include "pxr/usd/ar/resolverContextBinder.h"
#include "pxr/usd/usd/prim.h"

#include <maya/MDagPath.h>
#include <maya/MFnDagNode.h>
#include <maya/MPxNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

#include <string>

PXR_NAMESPACE_OPEN_SCOPE



UsdPrim
PxrUsdMayaQuery::GetPrim(const std::string& shapeName)
{
    UsdPrim usdPrim;

    MObject shapeObj;
    MStatus status = PxrUsdMayaUtil::GetMObjectByName(shapeName, shapeObj);
    CHECK_MSTATUS_AND_RETURN(status, usdPrim);
    MFnDagNode dagNode(shapeObj, &status);
    CHECK_MSTATUS_AND_RETURN(status, usdPrim);

    if (const PxrUsdMayaUsdPrimProvider* usdPrimProvider =
            dynamic_cast<const PxrUsdMayaUsdPrimProvider*>(dagNode.userNode())) {
        return usdPrimProvider->usdPrim();
    }

    return usdPrim;
}

std::string
PxrUsdMayaQuery::ResolvePath(const std::string &filePath)
{
    ArResolver& resolver = ArGetResolver();

    ArResolverContext ctx = 
        resolver.CreateDefaultContextForDirectory(ArchGetCwd());
    resolver.RefreshContext(ctx);

    ArResolverContextBinder boundCtx(ctx);
    return resolver.Resolve(filePath);
}

void
PxrUsdMayaQuery::ReloadStage(const std::string& shapeName)
{
    MStatus status;

    if (UsdPrim usdPrim = PxrUsdMayaQuery::GetPrim(shapeName)) {
        if (UsdStagePtr stage = usdPrim.GetStage()) {
            stage->Reload();
        }
    }
}


PXR_NAMESPACE_CLOSE_SCOPE

