/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * dalkom-hwp-import-filter.hxx
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

#ifndef __DALKOM_HWP_IMPORT_FILTER_HXX__
#define __DALKOM_HWP_IMPORT_FILTER_HXX__

#include <com/sun/star/document/XFilter.hpp>
#include <com/sun/star/document/XImporter.hpp>
#include <com/sun/star/document/XExtendedFilterDetection.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase5.hxx>

using namespace ::rtl; // for OUString

class HwpImportFilter : public cppu::WeakImplHelper5
  < com::sun::star::document::XFilter,
    com::sun::star::document::XImporter,
    com::sun::star::document::XExtendedFilterDetection,
    com::sun::star::lang::XInitialization,
    com::sun::star::lang::XServiceInfo >
{
protected:
  ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > mxDoc;

public:
  HwpImportFilter( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > &rxContext)
  {}
  virtual ~HwpImportFilter() {}

  // XFilter
  virtual sal_Bool SAL_CALL
  filter( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor )
    throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  virtual void SAL_CALL
  cancel(  )
    throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  // XImporter
  virtual void SAL_CALL
  setTargetDocument( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& xDoc )
    throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  //XExtendedFilterDetection
  virtual OUString SAL_CALL
  detect( com::sun::star::uno::Sequence< com::sun::star::beans::PropertyValue >& Descriptor )
    throw( com::sun::star::uno::RuntimeException, std::exception ) SAL_OVERRIDE;

  // XInitialization
  virtual void SAL_CALL
  initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments )
    throw (::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  // XServiceInfo
  virtual OUString SAL_CALL
  getImplementationName(  )
    throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  virtual sal_Bool SAL_CALL
  supportsService( const OUString &ServiceName )
    throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

  virtual ::com::sun::star::uno::Sequence< OUString > SAL_CALL
  getSupportedServiceNames(  )
    throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
};

OUString
HwpImportFilter_getImplementationName()
  throw ( ::com::sun::star::uno::RuntimeException );

bool SAL_CALL
HwpImportFilter_supportsService( const OUString &ServiceName )
  throw ( ::com::sun::star::uno::RuntimeException );

::com::sun::star::uno::Sequence< OUString > SAL_CALL
HwpImportFilter_getSupportedServiceNames(  )
  throw ( ::com::sun::star::uno::RuntimeException );

::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL
HwpImportFilter_createInstance( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > & rContext)
  throw ( ::com::sun::star::uno::Exception );

#endif
