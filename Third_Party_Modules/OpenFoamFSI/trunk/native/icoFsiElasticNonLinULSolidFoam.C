/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     |
    \\  /    A nd           | For copyright notice see file Copyright
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Application
    icoFsiElastciNonLinSolidFoam

Description
    Transient solver for fluid-solid interaction for an incompressible
    fluid and a large strain solid
    solid mesh is moved using U interpolated using least squares method

Author
    Zeljko Tukovic FSB Zagreb
    adapted by Philip Cardiff

\*---------------------------------------------------------------------------*/

#include "fsiFOAM.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

  fsifoam_module fsifoam(argc,argv);

  fsifoam.InitFluidMesh();
  fsifoam.InitTransportProperties();
  fsifoam.CreateFluidFields();
  fsifoam.InitStructuresMesh();
  fsifoam.CreateStructuresFields();
  fsifoam.ReadCouplingProperties();
  fsifoam.CreateInterZoneInterpolators();
  fsifoam.FindGlobalFaceZones();

  Foam::Time &runTime(fsifoam.RunTime());

  //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
  Info << "\nicoFsiElasticNonLinULSolidFoam:main: Starting time loop\n" << endl;
  
  
  while(!runTime.end()){
    Info << "icoFsiElasticNonLinULSolidFoam:main: Time = " << runTime.timeName() << nl << endl;
    fsifoam.Step();
    Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << endl << endl;
    if (runTime.outputTime())
      fsifoam.Dump();
  }
  
  Info<< "icoFsiElasticNonLinULSolidFoam:main: End\n" << endl;
  
  return(0);
}

// ************************************************************************* //
