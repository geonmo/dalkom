/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * dalkom-generic-filter.cxx
 *
 * This file is part of the Dalkom project.
 *
 * Copyright (C) 2016 Hodong Kim <cogniti@gmail.com>
 */

#include <cppuhelper/implementationentry.hxx>
#include "dalkom-hwp-import-filter.hxx"

namespace {

static cppu::ImplementationEntry const services[] = {
  { &HwpImportFilter_createInstance,
    &HwpImportFilter_getImplementationName,
    &HwpImportFilter_getSupportedServiceNames,
    &cppu::createSingleComponentFactory, 0, 0 },
  { 0, 0, 0, 0, 0, 0 } };

}

extern "C" SAL_DLLPUBLIC_EXPORT void * SAL_CALL
component_getFactory(
  char const * pImplName, void * pServiceManager, void * pRegistryKey)
{
  return cppu::component_getFactoryHelper(
    pImplName, pServiceManager, pRegistryKey, services);
}

extern "C" SAL_DLLPUBLIC_EXPORT sal_Bool SAL_CALL
component_writeInfo(void *pServiceManager, void *pRegistryKey)
{
  return cppu::component_writeInfoHelper(pServiceManager, pRegistryKey, services);
}
