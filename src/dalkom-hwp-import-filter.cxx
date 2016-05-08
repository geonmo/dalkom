/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * dalkom-hwp-import-filter.cxx
 *
 * This file is part of the Dalkom project.
 *
 * Copyright (C) 2016 Hodong Kim <cogniti@gmail.com>
 */

#include <cppuhelper/supportsservice.hxx>

#include "dalkom-hwp-import-filter.hxx"

#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include <com/sun/star/text/XTextRange.hpp>

#define SERVICE_NAME1 "dalkom.HwpImportFilter"
#define SERVICE_NAME2 "dalkom.HwpExtendedTypeDetection"

using com::sun::star::text::XText;
using com::sun::star::text::XTextDocument;
using com::sun::star::text::XTextCursor;
using com::sun::star::text::XTextRange;
using namespace ::com::sun::star::uno;
using com::sun::star::uno::Reference;
using com::sun::star::uno::Sequence;
using com::sun::star::uno::Any;
using com::sun::star::uno::UNO_QUERY;
using com::sun::star::uno::XInterface;
using com::sun::star::uno::Exception;
using com::sun::star::uno::RuntimeException;
using com::sun::star::beans::PropertyValue;

sal_Bool SAL_CALL
HwpImportFilter::filter( const Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor )
  throw (RuntimeException, std::exception)
{
  Reference <XTextDocument> xTextDocument (mxDoc, UNO_QUERY);
  Reference <XText> xText = xTextDocument->getText();
  Reference <XTextCursor> xTextCursor = xText->createTextCursor();
  Reference <XTextRange> xTextRange (xTextCursor, UNO_QUERY);
  xText->insertString(xTextRange, OUString::createFromAscii("Hello World"), false);

  return sal_True;
}

void SAL_CALL
HwpImportFilter::cancel(  )
  throw (RuntimeException, std::exception)
{
}

// XImporter
void SAL_CALL
HwpImportFilter::setTargetDocument( const Reference< ::com::sun::star::lang::XComponent >& xDoc )
  throw (::com::sun::star::lang::IllegalArgumentException, RuntimeException, std::exception)
{
  mxDoc = xDoc;
}

// XExtendedFilterDetection
OUString SAL_CALL
HwpImportFilter::detect( com::sun::star::uno::Sequence< PropertyValue >& Descriptor )
  throw( com::sun::star::uno::RuntimeException, std::exception )
{
  const OUString sTypeName("Hwp Document");

  return sTypeName;
}

// XInitialization
void SAL_CALL
HwpImportFilter::initialize( const Sequence< Any >& aArguments )
  throw (Exception, RuntimeException, std::exception)
{
}

OUString
HwpImportFilter_getImplementationName ()
  throw (RuntimeException)
{
  return OUString ( SERVICE_NAME1 );
}

Sequence< OUString > SAL_CALL
HwpImportFilter_getSupportedServiceNames(  )
  throw (RuntimeException)
{
  Sequence < OUString > aRet(2);
  OUString *pArray = aRet.getArray();
  pArray[0] = OUString ( SERVICE_NAME1 );
  pArray[1] = OUString ( SERVICE_NAME2 );
  return aRet;
}

Reference< XInterface > SAL_CALL
HwpImportFilter_createInstance( const Reference< XComponentContext > & rContext)
  throw( Exception )
{
  return (cppu::OWeakObject *) new HwpImportFilter( rContext );
}

// XServiceInfo
OUString SAL_CALL
HwpImportFilter::getImplementationName(  )
  throw (RuntimeException, std::exception)
{
  return HwpImportFilter_getImplementationName();
}

sal_Bool SAL_CALL
HwpImportFilter::supportsService( const OUString &rServiceName )
  throw (RuntimeException, std::exception)
{
  return cppu::supportsService(this, rServiceName);
}

Sequence< OUString > SAL_CALL
HwpImportFilter::getSupportedServiceNames(  )
  throw (RuntimeException, std::exception)
{
  return HwpImportFilter_getSupportedServiceNames();
}
