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
  * FCBRepAlgoAPI provides a wrapper for various OCCT functions.
  */

#include <FCBRepAlgoAPI_BooleanOperation.h>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <Precision.hxx>
#include <FuzzyHelper.h>

FCBRepAlgoAPI_BooleanOperation::FCBRepAlgoAPI_BooleanOperation()
{
    SetRunParallel(Standard_True);
}


FCBRepAlgoAPI_BooleanOperation::FCBRepAlgoAPI_BooleanOperation(const TopoDS_Shape& theS1,
                                               const TopoDS_Shape& theS2,
                                               const BOPAlgo_Operation theOperation)
: BRepAlgoAPI_BooleanOperation(theS1, theS2, theOperation)
{
    setAutoFuzzy();
    SetRunParallel(Standard_True);
}
  
void FCBRepAlgoAPI_BooleanOperation::setAutoFuzzy()
{
    Bnd_Box bounds;
    for (TopTools_ListOfShape::Iterator it(myArguments); it.More(); it.Next())
        BRepBndLib::Add(it.Value(), bounds);
    for (TopTools_ListOfShape::Iterator it(myTools); it.More(); it.Next())
        BRepBndLib::Add(it.Value(), bounds);
    SetFuzzyValue(Part::FuzzyHelper::getBooleanFuzzy() * sqrt(bounds.SquareExtent()) * Precision::Confusion());
}
