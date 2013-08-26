/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2011-2013 Kouhei Sutou <kou@clear-code.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MRN_MYSQL_H_
#define MRN_MYSQL_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
/* We need to undefine them because my_config.h defines them. :< */
#  undef VERSION
#  undef PACKAGE
#  undef PACKAGE_BUGREPORT
#  undef PACKAGE_NAME
#  undef PACKAGE_STRING
#  undef PACKAGE_TARNAME
#  undef PACKAGE_VERSION
#endif

#include <mrn_version.h>

#ifdef FORCE_FAST_MUTEX_DISABLED
#  ifdef MY_PTHREAD_FASTMUTEX
#    undef MY_PTHREAD_FASTMUTEX
#  endif
#endif

#define MYSQL_SERVER 1
#include <mysql_version.h>

#if MYSQL_VERSION_ID < 50500
#  include <mysql_priv.h>
#  include <mysql/plugin.h>
#else
#  include <sql_priv.h>
#  include <sql_class.h>
#  include <probes_mysql.h>
#  include <sql_partition.h>
#endif
#include <rpl_filter.h>

#ifdef MARIADB_BASE_VERSION
#  define MRN_MARIADB_P 1
#endif

#if MYSQL_VERSION_ID >= 50607
#  if !defined(MRN_MARIADB_P)
#    define MRN_HAVE_SQL_OPTIMIZER_H
#  endif
#endif

#define MRN_MESSAGE_BUFFER_SIZE 1024

#define MRN_DBUG_ENTER_FUNCTION() DBUG_ENTER(__FUNCTION__)

#if !defined(DBUG_OFF) && !defined(_lint)
#  define MRN_DBUG_ENTER_METHOD()                 \
    char method_name[MRN_MESSAGE_BUFFER_SIZE];    \
    method_name[0] = '\0';                        \
    strcat(method_name, MRN_CLASS_NAME);          \
    strcat(method_name, "::");                    \
    strcat(method_name, __FUNCTION__);            \
    DBUG_ENTER(method_name)
#else
#  define MRN_DBUG_ENTER_METHOD() MRN_DBUG_ENTER_FUNCTION()
#endif

#endif /* MRN_MYSQL_H_ */
