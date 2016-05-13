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
#include <com/sun/star/text/ControlCharacter.hpp>
#include <hwp.h>

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

/* HwpToTxt class ***********************************************************/
#define HWP_TYPE_TO_TXT             (hwp_to_txt_get_type ())
#define HWP_TO_TXT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), HWP_TYPE_TO_TXT, HwpToTxt))
#define HWP_TO_TXT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), HWP_TYPE_TO_TXT, HwpToTxtClass))
#define HWP_IS_TO_TXT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HWP_TYPE_TO_TXT))
#define HWP_IS_TO_TXT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), HWP_TYPE_TO_TXT))
#define HWP_TO_TXT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), HWP_TYPE_TO_TXT, HwpToTxtClass))

typedef struct _HwpToTxt      HwpToTxt;
typedef struct _HwpToTxtClass HwpToTxtClass;

struct _HwpToTxtClass
{
  GObjectClass parent_class;
};

struct _HwpToTxt
{
  GObject parent_instance;
};

GType hwp_to_txt_get_type (void) G_GNUC_CONST;

static void hwp_to_txt_iface_init (HwpListenableInterface *iface);

G_DEFINE_TYPE_WITH_CODE (HwpToTxt, hwp_to_txt, G_TYPE_OBJECT,
  G_IMPLEMENT_INTERFACE (HWP_TYPE_LISTENABLE, hwp_to_txt_iface_init))

static void hwp_to_txt_init (HwpToTxt *hwp_to_txt)
{
}

static void hwp_to_txt_finalize (GObject *object)
{
  G_OBJECT_CLASS (hwp_to_txt_parent_class)->finalize (object);
}

static void hwp_to_txt_class_init (HwpToTxtClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->finalize = hwp_to_txt_finalize;
}

HwpToTxt *hwp_to_txt_new ()
{
  return (HwpToTxt *) g_object_new (HWP_TYPE_TO_TXT, NULL);
}

typedef struct _Param
{
  Reference <XText> *xtext;
  Reference <XTextRange> *xtext_range;
} Param;

void listen_paragraph (HwpListenable *listenable,
                       HwpParagraph  *paragraph,
                       gpointer       user_data,
                       GError       **error)
{
  const gchar *text = hwp_paragraph_get_text (paragraph);

  Param *param = (Param *) user_data;

  if (g_strcmp0 (text, "") != 0)
  {
    OUString oustr = OStringToOUString(OString(text, strlen(text)),
                                       RTL_TEXTENCODING_UTF8 );
    (*(param->xtext))->insertString(*(param->xtext_range), oustr, false);
  }
  else
  {
    (*(param->xtext))->insertControlCharacter(*(param->xtext_range),
                                              com::sun::star::text::ControlCharacter::PARAGRAPH_BREAK,
                                              false);
  }
}

static void hwp_to_txt_iface_init (HwpListenableInterface *iface)
{
  iface->paragraph = listen_paragraph;
}

sal_Bool SAL_CALL
HwpImportFilter::filter( const Sequence< ::com::sun::star::beans::PropertyValue >& aDescriptor )
  throw (RuntimeException, std::exception)
{
  Reference <XTextDocument> xTextDocument (mxDoc, UNO_QUERY);
  Reference <XText> xText = xTextDocument->getText();
  Reference <XTextCursor> xTextCursor = xText->createTextCursor();
  Reference <XTextRange> xTextRange (xTextCursor, UNO_QUERY);

  sal_Int32 nLength = aDescriptor.getLength();
  const PropertyValue *pValue = aDescriptor.getConstArray();
  OUString url;
  OString  ostr;
  GError  *error = NULL;

  for ( sal_Int32 i = 0 ; i < nLength; i++)
    if ( pValue[i].Name == "URL" )
      pValue[i].Value >>= url;

  ostr = rtl::OUStringToOString(url, RTL_TEXTENCODING_UTF8);
  const char *uri = ostr.getStr();
  HwpFile *hwpfile = hwp_file_new_for_uri (uri, &error);

  if (error)
  {
    g_clear_error (&error);

    return sal_False;
  }

  HwpToTxt *hwp2txt = hwp_to_txt_new ();

  Param *param = g_slice_new (Param);
  param->xtext = &xText;
  param->xtext_range = &xTextRange;

  HwpParser *parser = hwp_parser_new (HWP_LISTENABLE (hwp2txt), param);
  hwp_parser_parse (parser, hwpfile, &error);

  g_slice_free (Param, param);
  g_object_unref (parser);
  g_object_unref (hwp2txt);
  g_object_unref (hwpfile);

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
