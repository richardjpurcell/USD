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
#ifndef HD_RPRIM_COLLECTION_H
#define HD_RPRIM_COLLECTION_H

#include "pxr/pxr.h"
#include "pxr/imaging/hd/version.h"
#include "pxr/usd/sdf/path.h"
#include "pxr/base/tf/token.h"

#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class HdRprimCollection
///
/// A named, semantic collection of objects.
///
/// Note that the collection object itself doesn't hold HdRprim objects, rather
/// it acts and addressing mechanism to identify a specific group of HdRprim 
/// objects that can be requested from the HdRenderIndex.
///
class HdRprimCollection {
public:
    HdRprimCollection();

    /// Constructs an rprim collection with \p reprName. \p if forcedRepr is
    /// set to true, prims authored repr will be ignored.
    HdRprimCollection(TfToken const& name,
                      TfToken const& reprName,
                      bool forcedRepr=false);

    /// Constructs an rprim collection, excluding all Rprims not prefixed by \p
    /// rootPath. \p if forcedRepr is set to true, prims authored repr will be
    /// ignored.
    HdRprimCollection(TfToken const& name,
                      TfToken const& reprName,
                      SdfPath const& rootPath,
                      bool forcedRepr=false);

    // Destructor.
    virtual ~HdRprimCollection();

    /// Returns the semantic name of this collection.
    ///
    /// The semantic name represents the entire collection of prims, for
    /// example "visible", "selected", etc.
    TfToken const& GetName() const {
        return _name;
    }

    /// Sets the semantic name of this collection.
    void SetName(TfToken const& name) {
        _name = name;
    }

    /// Returns the representation name.
    ///
    /// The repr name corresponds to specific aspects of the requested set of 
    /// Rprims, for example one can request "hullAndPoints" repr which
    /// would cause both the hull and points representations of all prims named
    /// by the collection to be included.
    TfToken const& GetReprName() const {
        return _reprName;
    }

    void SetReprName(TfToken const &reprName) {
        _reprName = reprName;
    }

    bool IsForcedRepr() const {
        return _forcedRepr;
    }

    void SetForcedRepr(bool flag) {
        _forcedRepr = flag;
    }

    /// Returns the paths at which all Rprims must be rooted to be included in
    /// this collection. Defaults to a vector containing only
    /// SdfPath::AbsoluteRootPath().
    ///
    /// Note that this vector is always sorted.
    SdfPathVector const& GetRootPaths() const;

    /// Sets all root paths for this collection, replacing any existing paths
    /// that were present previously. All paths must be absolute. Duplicate
    /// paths are allowed, but may result in peformance degradation.
    void SetRootPaths(SdfPathVector const& rootPaths);

    /// Sets the path at which all Rprims must be rooted to be included in this
    /// collection, replacing any existing root paths that were previously
    /// specified.
    void SetRootPath(SdfPath const& rootPath);

    /// Sets all exclude paths for this collection. All paths must be absolute. 
    /// Duplicate paths are allowed, but may result in peformance degradation.
    void SetExcludePaths(SdfPathVector const& excludePaths);

    /// Returns the excluded paths
    ///
    /// Note that this vector is always sorted.
    SdfPathVector const& GetExcludePaths() const;

    size_t ComputeHash() const;

    struct Hash {
        size_t operator()(HdRprimCollection const& value) const {
            return value.ComputeHash();
        }
    };

    bool operator==(HdRprimCollection const & lhs) const;
    bool operator!=(HdRprimCollection const & lhs) const;

private:
    friend std::ostream & operator <<(std::ostream &out, 
        HdRprimCollection const & v);

    TfToken _name;
    TfToken _reprName;
    bool _forcedRepr;
    SdfPathVector _rootPaths;
    SdfPathVector _excludePaths;
};

typedef std::vector<HdRprimCollection> HdRprimCollectionVector;

// VtValue requirements
std::ostream& operator<<(std::ostream& out, HdRprimCollection const & v);

// Overload hash_value for HdRprimCollection.  Used by things like boost::hash.
size_t hash_value(HdRprimCollection const &col);


PXR_NAMESPACE_CLOSE_SCOPE

#endif //HD_RPRIM_COLLECTION_H
