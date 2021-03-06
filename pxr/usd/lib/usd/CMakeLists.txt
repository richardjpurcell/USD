set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE usd)

pxr_shared_library(usd
    LIBRARIES
        arch
        kind
        pcp
        sdf
        ar
        plug
        tf
        tracelite
        vt
        work
        ${Boost_PYTHON_LIBRARY}
        ${TBB_LIBRARIES}

    INCLUDE_DIRS
        ${Boost_INCLUDE_DIRS}
        ${TBB_INCLUDE_DIRS}

    PUBLIC_CLASSES
        attribute
        clipsAPI
        attributeQuery
        common
        conversions
        crateInfo
        debugCodes
        editContext
        editTarget
        inherits
        interpolation
        modelAPI
        notice
        object
        prim
        primData
        primDataHandle
        primFlags
        property
        references
        relationship
        resolveInfo
        resolver
        schemaBase
        schemaRegistry
        specializes
        stage
        stageCache
        stageCacheContext
        stagePopulationMask
        timeCode
        tokens
        treeIterator
        typed
        usdFileFormat
        usdaFileFormat
        usdcFileFormat
        variantSets

    PRIVATE_CLASSES
        clip
        clipCache
        crateData
        crateFile
        instanceCache
        instanceKey
        interpolators

    PUBLIC_HEADERS
        api.h

    PRIVATE_HEADERS
        crateDataTypes.h
        crateValueInliners.h
        wrapUtils.h

    CPPFILES
        moduleDeps.cpp

    PYMODULE_CPPFILES
        module.cpp
        wrapAttribute.cpp
        wrapAttributeQuery.cpp
        wrapClipsAPI.cpp
        wrapCommon.cpp
        wrapCrateInfo.cpp
        wrapEditContext.cpp
        wrapEditTarget.cpp
        wrapInherits.cpp
        wrapInterpolation.cpp
        wrapModelAPI.cpp
        wrapNotice.cpp
        wrapObject.cpp
        wrapPrim.cpp
        wrapPrimFlags.cpp
        wrapProperty.cpp
        wrapReferences.cpp
        wrapRelationship.cpp
        wrapResolveInfo.cpp
        wrapSchemaBase.cpp
        wrapSchemaRegistry.cpp
        wrapSpecializes.cpp
        wrapStage.cpp
        wrapStageCache.cpp
        wrapStageCacheContext.cpp
        wrapStagePopulationMask.cpp
        wrapTimeCode.cpp
        wrapTreeIterator.cpp
        wrapTyped.cpp
        wrapUtils.cpp
        wrapVariantSets.cpp

    PYTHON_FILES
        __init__.py

    RESOURCE_FILES
        plugInfo.json
        generatedSchema.usda
)

if (NOT JINJA2_FOUND)
    message(WARNING "Skipping building usdGenSchema due to missing dependency: Jinja2")
else()
    pxr_python_bins(
        usdGenSchema
    )
endif()
