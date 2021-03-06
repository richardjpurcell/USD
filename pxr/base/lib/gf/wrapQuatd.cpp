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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// wrapQuat.template.cpp file to make changes.

#include "pxr/pxr.h"
#include "pxr/base/gf/quatd.h"
#include "pxr/base/gf/quatf.h"
#include "pxr/base/gf/quath.h"

#include "pxr/base/tf/pyUtils.h"
#include "pxr/base/tf/wrapTypeHelpers.h"
#include "pxr/base/tf/pyContainerConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/return_arg.hpp>

#include <string>

using namespace boost::python;

using std::string;

PXR_NAMESPACE_OPEN_SCOPE

static string __repr__(GfQuatd const &self) {
    return TF_PY_REPR_PREFIX + "Quatd(" +
        TfPyRepr(self.GetReal()) + ", " +
        TfPyRepr(self.GetImaginary()) + ")";
}

// Zero-initialized default ctor for python.
static GfQuatd *__init__() { return new GfQuatd(0); }

void wrapQuatd()
{    
    object getImaginary =
        make_function(&GfQuatd::GetImaginary,
                      return_value_policy<return_by_value>());

    object setImaginaryVec =
        make_function((void (GfQuatd::*)(const GfVec3d &))
                      &GfQuatd::SetImaginary);

    object setImaginaryScl =
        make_function((void (GfQuatd::*)(double, double, double))
                      &GfQuatd::SetImaginary,
                      default_call_policies(),
                      (arg("i"), arg("j"), arg("k")));

    def("Slerp",
        (GfQuatd (*)(double, const GfQuatd&, const GfQuatd&))
        GfSlerp);
    
    class_<GfQuatd>("Quatd", no_init)
        .def("__init__", make_constructor(__init__))
                          
        .def(TfTypePythonClass())

        .def(init<double>(arg("real")))
        .def(init<double, const GfVec3d &>(
                 (arg("real"), arg("imaginary"))))
        .def(init<double, double, double, double>(
                 (arg("real"), arg("i"), arg("j"), arg("k"))))

        .def("GetIdentity", &GfQuatd::GetIdentity)
        .staticmethod("GetIdentity")

        .def("GetReal", &GfQuatd::GetReal)
        .def("SetReal", &GfQuatd::SetReal)
        .add_property("real", &GfQuatd::GetReal, &GfQuatd::SetReal)

        .def("GetImaginary", getImaginary)
        .def("SetImaginary", setImaginaryVec)
        .def("SetImaginary", setImaginaryScl)
        .add_property("imaginary", getImaginary, setImaginaryVec)

        .def("GetLength", &GfQuatd::GetLength)

        .def("GetNormalized", &GfQuatd::GetNormalized,
             (arg("eps")=GF_MIN_VECTOR_LENGTH))
        .def("Normalize", &GfQuatd::Normalize,
             (arg("eps")=GF_MIN_VECTOR_LENGTH), return_self<>())

        .def("GetConjugate", &GfQuatd::GetConjugate)
        .def("GetInverse", &GfQuatd::GetInverse)

        .def(str(self))
        .def(-self)
        .def(self == self)
        .def(self != self)
        .def(self *= self)
        .def(self *= double())
        .def(self /= double())
        .def(self += self)
        .def(self -= self)
        .def(self + self)
        .def(self - self)
        .def(self * self)
        .def(self * double())
        .def(double() * self)
        .def(self / double())

        .def("__repr__", __repr__)

        ;

    implicitly_convertible<GfQuatf, GfQuatd>();
    implicitly_convertible<GfQuath, GfQuatd>();

    to_python_converter<std::vector<GfQuatd>,
        TfPySequenceToPython<std::vector<GfQuatd> > >();
    
}

PXR_NAMESPACE_CLOSE_SCOPE
