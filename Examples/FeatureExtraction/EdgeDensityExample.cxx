/*=========================================================================

Program:   ORFEO Toolbox
Language:  C++
Date:      $Date$
Version:   $Revision$


Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
See OTBCopyright.txt for details.


This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbImage.h"
#include "otbEdgeDensityImageFilter.h"
#include "otbBinaryImageDensityFunction.h"
#include "itkCannyEdgeDetectionImageFilter.h"

#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"



int main(int argc, char* argv[] )
{

  const  char *     infname       = argv[1];
  const  char *     outfname      = argv[2];

  /** Variables for the canny detector*/
  const double    upperThreshold   = atof(argv[3]);
  const double    lowerThreshold   = atof(argv[4]);
  const double    variance         = atof(argv[5]);
  const double    maximumError     = atof(argv[6]);
  /*--*/
    
  const   unsigned int                                      Dimension = 2;
  typedef float                                             PixelType;

  typedef otb::Image< PixelType, Dimension >                                      ImageType;
  typedef ImageType::IndexType                                                    IndexType;
  typedef otb::ImageFileReader<ImageType>                                         ReaderType;
  typedef otb::ImageFileWriter<ImageType>                                         WriterType;

  typedef otb::BinaryImageDensityFunction<ImageType>                              CountFunctionType;
  typedef itk::CannyEdgeDetectionImageFilter<ImageType , ImageType>               CannyDetectorType;

  typedef otb::EdgeDensityImageFilter<ImageType,CannyDetectorType  ,CountFunctionType , ImageType> EdgeDensityFilterType;

  /**Instancitation of an object*/
  EdgeDensityFilterType::Pointer    filter =      EdgeDensityFilterType::New();
  ReaderType::Pointer               reader =      ReaderType::New();
  CannyDetectorType::Pointer        CannyFilter = CannyDetectorType::New();

  /** Set The input*/
  reader->SetFileName(infname);
  filter->SetInput(reader->GetOutput());
  
  /** Update the Canny Filter Information*/
  CannyFilter->SetUpperThreshold(static_cast<ImageType::PixelType>(upperThreshold)); /** 30*/
  CannyFilter->SetLowerThreshold(static_cast<ImageType::PixelType>(lowerThreshold));/** 10*/
  CannyFilter->SetVariance(variance); //1.
  CannyFilter->SetMaximumError(maximumError); ///0.01f

  filter->SetDetector(CannyFilter);

  /** Write the output*/
  WriterType::Pointer          writer = WriterType::New();
  writer->SetFileName(outfname);
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

