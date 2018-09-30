/*
 * probes/lttng-probe-xfs.c
 *
 * LTTng xfs probes.
 *
 * Copyright (C) 2018 Souvik Banerjee <souvik1997@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; only
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/dcache.h>
#include <lttng-tracer.h>

#include <../fs/xfs/xfs.h>
#include <../fs/xfs/xfs_linux.h>
#include <../fs/xfs/libxfs/xfs_log_format.h>
#include <../fs/xfs/libxfs/xfs_format.h>
#include <../fs/xfs/libxfs/xfs_trans_resv.h>
#include <../fs/xfs/libxfs/xfs_da_format.h>
#include <../fs/xfs/libxfs/xfs_da_btree.h>
#include <../fs/xfs/xfs_inode.h>
#include <../fs/xfs/xfs_attr.h>
#include <../fs/xfs/xfs_trans.h>
#include <../fs/xfs/xfs_buf_item.h>
#include <../fs/xfs/xfs_mount.h>
#include <../fs/xfs/xfs_filestream.h>
#include <../fs/xfs/libxfs/xfs_quota_defs.h>
#include <../fs/xfs/xfs_dquot_item.h>
#include <../fs/xfs/xfs_dquot.h>
#include <../fs/xfs/xfs_log.h>
#include <../fs/xfs/xfs_log_priv.h>
#include <../fs/xfs/libxfs/xfs_btree.h>
#include <../fs/xfs/libxfs/xfs_alloc.h>
#include <../fs/xfs/libxfs/xfs_log_recover.h>
#include <../fs/xfs/libxfs/xfs_defer.h>
#include <../fs/xfs/xfs_fsmap.h>
/*
 * Create the tracepoint static inlines from the kernel to validate that our
 * trace event macros match the kernel we run on.
 */
#include <../fs/xfs/xfs_trace.h>

/*
 * Create LTTng tracepoint probes.
 */
#define LTTNG_PACKAGE_BUILD
#define CREATE_TRACE_POINTS
#undef TRACE_INCLUDE_FILE
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH instrumentation/events/lttng-module

/* deferred ops */
struct xfs_defer_pending;
struct xfs_defer_ops;

#include <instrumentation/events/lttng-module/xfs.h>

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Souvik Banerjee <souvik1997@gmail.com>");
MODULE_DESCRIPTION("LTTng xfs probes");
MODULE_VERSION(__stringify(LTTNG_MODULES_MAJOR_VERSION) "."
  __stringify(LTTNG_MODULES_MINOR_VERSION) "."
  __stringify(LTTNG_MODULES_PATCHLEVEL_VERSION)
  LTTNG_MODULES_EXTRAVERSION);
