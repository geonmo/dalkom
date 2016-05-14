/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * dalkom-generic-filter.cxx
 *
 * This file is part of the Dalkom project.
 *
 * Copyright (C) 2016 Hodong Kim <cogniti@gmail.com>
 *
 * Dalkom is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Dalkom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;  If not, see <http://www.gnu.org/licenses/>.
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
