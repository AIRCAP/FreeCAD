// SPDX-License-Identifier: LGPL-2.1-or-later

/***************************************************************************
 *   Copyright (c) 2024 Eric Price (CorvusCorax)                           *
 *                      <eric.price[at]tuebingen.mpg.de>                   *
 *                                                                         *
 *   This file is part of FreeCAD.                                         *
 *                                                                         *
 *   FreeCAD is free software: you can redistribute it and/or modify it    *
 *   under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation, either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   FreeCAD is distributed in the hope that it will be useful, but        *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with FreeCAD. If not, see                               *
 *   <https://www.gnu.org/licenses/>.                                      *
 *                                                                         *
 **************************************************************************/

/**
  * FCRepAlgoAPI provides a wrapper for various OCCT functions.
  */

#include <FCRepAlgoAPI_Section.h>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <FuzzyHelper.h>

FCRepAlgoAPI_Section::FCRepAlgoAPI_Section()
{
    SetFuzzyValue(Part::FuzzyHelper::getDefaultFuzzyValue(0.0));
    SetRunParallel(Standard_True);
}

FCRepAlgoAPI_Section::FCRepAlgoAPI_Section(const TopoDS_Shape& S1, const TopoDS_Shape& S2, const Standard_Boolean PerformNow)
: BRepAlgoAPI_Section(S1,S2,false) 
{
    setAutoFuzzy();
    SetRunParallel(Standard_True);
    if (PerformNow) Build();
}

FCRepAlgoAPI_Section::FCRepAlgoAPI_Section
(const TopoDS_Shape&    Sh,
const gp_Pln&          Pl,
const Standard_Boolean PerformNow)
: 
BRepAlgoAPI_Section(Sh,Pl,false) 
{
    setAutoFuzzy();
    SetRunParallel(Standard_True);
    if (PerformNow) Build();
}


void FCRepAlgoAPI_Section::setAutoFuzzy()
{
    Bnd_Box bounds;
    for (TopTools_ListOfShape::Iterator it(myArguments); it.More(); it.Next())
        BRepBndLib::Add(it.Value(), bounds);
    for (TopTools_ListOfShape::Iterator it(myTools); it.More(); it.Next())
        BRepBndLib::Add(it.Value(), bounds);
    SetFuzzyValue(Part::FuzzyHelper::getDefaultFuzzyValue(bounds.SquareExtent()));
}
