#undef TRACE_SYSTEM
#define TRACE_SYSTEM xfs

#if !defined(LTTNG_TRACE_XFS_H) || defined(TRACE_HEADER_MULTI_READ)
#define LTTNG_TRACE_XFS_H

#include <probes/lttng-tracepoint-event.h>

#ifndef _TRACE_XFS_DEF_
#define _TRACE_XFS_DEF_
struct xfs_agf;
struct xfs_alloc_arg;
struct xfs_attr_list_context;
struct xfs_buf_log_item;
struct xfs_da_args;
struct xfs_da_node_entry;
struct xfs_dquot;
struct xfs_log_item;
struct xlog;
struct xlog_ticket;
struct xlog_recover;
struct xlog_recover_item;
struct xfs_buf_log_format;
struct xfs_inode_log_format;
struct xfs_bmbt_irec;
struct xfs_btree_cur;
struct xfs_refcount_irec;
struct xfs_fsmap;
struct xfs_rmap_irec;
#endif

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_attr_list_class,
  TP_PROTO(struct xfs_attr_list_context *ctx),
  TP_ARGS(ctx),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ctx->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ctx->dp->i_ino)
    ctf_integer(u32, hashval, ctx->cursor->hashval)
    ctf_integer(u32, blkno, ctx->cursor->blkno)
    ctf_integer(u32, offset, ctx->cursor->offset)
    ctf_integer(void *, alist, ctx->alist)
    ctf_integer(int, bufsize, ctx->bufsize)
    ctf_integer(int, count, ctx->count)
    ctf_integer(int, firstu, ctx->firstu)
    ctf_integer(int, dupcnt, ctx->dupcnt) /* NOTE: not present in original xfs_trace.h */
    ctf_integer(int, flags, ctx->flags)
  )
)

#undef DEFINE_ATTR_LIST_EVENT
#define DEFINE_ATTR_LIST_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_attr_list_class, name, \
  TP_PROTO(struct xfs_attr_list_context *ctx), \
  TP_ARGS(ctx))
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_sf)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_sf_all)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_leaf)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_leaf_end)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_full)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_add)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_wrong_blk)
DEFINE_ATTR_LIST_EVENT(xfs_attr_list_notfound)
DEFINE_ATTR_LIST_EVENT(xfs_attr_leaf_list)
DEFINE_ATTR_LIST_EVENT(xfs_attr_node_list)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_perag_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, int refcount,
     unsigned long caller_ip),
  TP_ARGS(mp, agno, refcount, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, refcount, refcount)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_PERAG_REF_EVENT
#define DEFINE_PERAG_REF_EVENT(name)	\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_perag_class, name,	\
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, int refcount,	\
     unsigned long caller_ip),					\
  TP_ARGS(mp, agno, refcount, caller_ip))
DEFINE_PERAG_REF_EVENT(xfs_perag_get)
DEFINE_PERAG_REF_EVENT(xfs_perag_get_tag)
DEFINE_PERAG_REF_EVENT(xfs_perag_put)
DEFINE_PERAG_REF_EVENT(xfs_perag_set_reclaim)
DEFINE_PERAG_REF_EVENT(xfs_perag_clear_reclaim)
DEFINE_PERAG_REF_EVENT(xfs_perag_set_eofblocks)
DEFINE_PERAG_REF_EVENT(xfs_perag_clear_eofblocks)
DEFINE_PERAG_REF_EVENT(xfs_perag_set_cowblocks)
DEFINE_PERAG_REF_EVENT(xfs_perag_clear_cowblocks)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_ag_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno),
  TP_ARGS(mp, agno),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
  )
)

#undef DEFINE_AG_EVENT
#define DEFINE_AG_EVENT(name)	\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_ag_class, name,	\
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno),	\
  TP_ARGS(mp, agno))

DEFINE_AG_EVENT(xfs_read_agf)
DEFINE_AG_EVENT(xfs_alloc_read_agf)
DEFINE_AG_EVENT(xfs_read_agi)
DEFINE_AG_EVENT(xfs_ialloc_read_agi)

LTTNG_TRACEPOINT_EVENT(xfs_attr_list_node_descend,
  TP_PROTO(struct xfs_attr_list_context *ctx,
     struct xfs_da_node_entry *btree),
  TP_ARGS(ctx, btree),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ctx->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ctx->dp->i_ino)
    ctf_integer(u32, hashval, ctx->cursor->hashval)
    ctf_integer(u32, blkno, ctx->cursor->blkno)
    ctf_integer(u32, offset, ctx->cursor->offset)
    ctf_integer(void *, alist, ctx->alist)
    ctf_integer(int, bufsize, ctx->bufsize)
    ctf_integer(int, count, ctx->count)
    ctf_integer(int, firstu, ctx->firstu)
    ctf_integer(int, dupcnt, ctx->dupcnt) /* NOTE: not present in original xfs_trace.h */
    ctf_integer(int, flags, ctx->flags)
    ctf_integer(u32, bt_hashval, be32_to_cpu(btree->hashval))
    ctf_integer(u32, bt_before, be32_to_cpu(btree->before))
  )
)

#ifdef DEBUG
LTTNG_TRACEPOINT_EVENT_CLASS_CODE(xfs_bmap_class,
  TP_PROTO(struct xfs_inode *ip, struct xfs_iext_cursor *cur, int state,
     unsigned long caller_ip),
  TP_ARGS(ip, cur, state, caller_ip),
  TP_locvar(
    struct xfs_ifork	*ifp;
    struct xfs_bmbt_irec	r;
  ),
  TP_code_pre(
    tp_locvar->ifp = xfs_iext_state_to_fork(ip, state);
    xfs_iext_get_extent(tp_locvar->ifp, cur, &tp_locvar->r);
  ),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(void *, leaf, cur->leaf)
    ctf_integer(int, pos, cur->pos)
    ctf_integer(xfs_fileoff_t, startoff, tp_locvar->r.br_startoff)
    ctf_integer(xfs_fsblock_t, startblock, tp_locvar->r.br_startblock)
    ctf_integer(xfs_filblks_t, blockcount, tp_locvar->r.br_blockcount)
    ctf_integer(xfs_exntst_t, state, tp_locvar->r.br_state)
    ctf_integer(int, bmap_state, state)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  ),
  TP_code_post()
)


#undef DEFINE_BMAP_EVENT
#define DEFINE_BMAP_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_bmap_class, name, \
  TP_PROTO(struct xfs_inode *ip, struct xfs_iext_cursor *cur, int state, \
     unsigned long caller_ip), \
  TP_ARGS(ip, cur, state, caller_ip))
DEFINE_BMAP_EVENT(xfs_iext_insert)
DEFINE_BMAP_EVENT(xfs_iext_remove)
DEFINE_BMAP_EVENT(xfs_bmap_pre_update)
DEFINE_BMAP_EVENT(xfs_bmap_post_update)
DEFINE_BMAP_EVENT(xfs_read_extent)
DEFINE_BMAP_EVENT(xfs_write_extent)
#endif /* DEBUG */

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_buf_class,
  TP_PROTO(struct xfs_buf *bp, unsigned long caller_ip),
  TP_ARGS(bp, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, bp->b_target->bt_dev)
    ctf_integer(xfs_daddr_t, bno, bp->b_bn)
    ctf_integer(int, nblks, bp->b_length)
    ctf_integer(int, hold, atomic_read(&bp->b_hold))
    ctf_integer(int, pincount, atomic_read(&bp->b_pin_count))
    ctf_integer(unsigned, lockval, bp->b_sema.count)
    ctf_integer(unsigned, flags, bp->b_flags)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_BUF_EVENT
#define DEFINE_BUF_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_buf_class, name, \
  TP_PROTO(struct xfs_buf *bp, unsigned long caller_ip), \
  TP_ARGS(bp, caller_ip))
DEFINE_BUF_EVENT(xfs_buf_init)
DEFINE_BUF_EVENT(xfs_buf_free)
DEFINE_BUF_EVENT(xfs_buf_hold)
DEFINE_BUF_EVENT(xfs_buf_rele)
DEFINE_BUF_EVENT(xfs_buf_iodone)
DEFINE_BUF_EVENT(xfs_buf_submit)
DEFINE_BUF_EVENT(xfs_buf_submit_wait)
DEFINE_BUF_EVENT(xfs_buf_lock)
DEFINE_BUF_EVENT(xfs_buf_lock_done)
DEFINE_BUF_EVENT(xfs_buf_trylock_fail)
DEFINE_BUF_EVENT(xfs_buf_trylock)
DEFINE_BUF_EVENT(xfs_buf_unlock)
DEFINE_BUF_EVENT(xfs_buf_iowait)
DEFINE_BUF_EVENT(xfs_buf_iowait_done)
DEFINE_BUF_EVENT(xfs_buf_delwri_queue)
DEFINE_BUF_EVENT(xfs_buf_delwri_queued)
DEFINE_BUF_EVENT(xfs_buf_delwri_split)
DEFINE_BUF_EVENT(xfs_buf_delwri_pushbuf)
DEFINE_BUF_EVENT(xfs_buf_get_uncached)
DEFINE_BUF_EVENT(xfs_buf_item_relse)
DEFINE_BUF_EVENT(xfs_buf_item_iodone_async)
DEFINE_BUF_EVENT(xfs_buf_error_relse)
DEFINE_BUF_EVENT(xfs_buf_wait_buftarg)
DEFINE_BUF_EVENT(xfs_trans_read_buf_shut)

/* not really buffer traces, but the buf provides useful information */
DEFINE_BUF_EVENT(xfs_btree_corrupt)
DEFINE_BUF_EVENT(xfs_reset_dqcounts)

/* pass flags explicitly */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_buf_flags_class,
  TP_PROTO(struct xfs_buf *bp, unsigned flags, unsigned long caller_ip),
  TP_ARGS(bp, flags, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, bp->b_target->bt_dev)
    ctf_integer(xfs_daddr_t, bno, bp->b_bn)
    ctf_integer(size_t, buffer_length, BBTOB(bp->b_length))
    ctf_integer(int, hold, atomic_read(&bp->b_hold))
    ctf_integer(int, pincount, atomic_read(&bp->b_pin_count))
    ctf_integer(unsigned, lockval, bp->b_sema.count)
    ctf_integer(unsigned, flags, flags)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_BUF_FLAGS_EVENT
#define DEFINE_BUF_FLAGS_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_buf_flags_class, name, \
  TP_PROTO(struct xfs_buf *bp, unsigned flags, unsigned long caller_ip), \
  TP_ARGS(bp, flags, caller_ip))
DEFINE_BUF_FLAGS_EVENT(xfs_buf_find)
DEFINE_BUF_FLAGS_EVENT(xfs_buf_get)
DEFINE_BUF_FLAGS_EVENT(xfs_buf_read)

LTTNG_TRACEPOINT_EVENT(xfs_buf_ioerror,
  TP_PROTO(struct xfs_buf *bp, int error, xfs_failaddr_t caller_ip),
  TP_ARGS(bp, error, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, bp->b_target->bt_dev)
    ctf_integer(xfs_daddr_t, bno, bp->b_bn)
    ctf_integer(size_t, buffer_length, BBTOB(bp->b_length))
    ctf_integer(unsigned, flags, bp->b_flags)
    ctf_integer(int, hold, atomic_read(&bp->b_hold))
    ctf_integer(int, pincount, atomic_read(&bp->b_pin_count))
    ctf_integer(unsigned, lockval, bp->b_sema.count)
    ctf_integer(int, error, error)
    ctf_integer(xfs_failaddr_t, caller_ip, caller_ip)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_buf_item_class,
  TP_PROTO(struct xfs_buf_log_item *bip),
  TP_ARGS(bip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, bip->bli_buf->b_target->bt_dev)
    ctf_integer(xfs_daddr_t, buf_bno, bip->bli_buf->b_bn)
    ctf_integer(size_t, buf_len, BBTOB(bip->bli_buf->b_length))
    ctf_integer(int, buf_hold, atomic_read(&bip->bli_buf->b_hold))
    ctf_integer(int, buf_pincount, atomic_read(&bip->bli_buf->b_pin_count))
    ctf_integer(int, buf_lockval, bip->bli_buf->b_sema.count)
    ctf_integer(unsigned, buf_flags, bip->bli_buf->b_flags)
    ctf_integer(unsigned, bli_recur, bip->bli_recur)
    ctf_integer(int, bli_refcount, atomic_read(&bip->bli_refcount))
    ctf_integer(unsigned, bli_flags, bip->bli_flags)
    ctf_integer(void *, li_desc, bip->bli_item.li_desc)
    ctf_integer(unsigned, li_flags, bip->bli_item.li_flags)
  )
)

#undef DEFINE_BUF_ITEM_EVENT
#define DEFINE_BUF_ITEM_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_buf_item_class, name, \
  TP_PROTO(struct xfs_buf_log_item *bip), \
  TP_ARGS(bip))
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size_ordered)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_size_stale)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_format)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_format_stale)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_ordered)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_pin)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unpin)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unpin_stale)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unlock)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_unlock_stale)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_committed)
DEFINE_BUF_ITEM_EVENT(xfs_buf_item_push)
DEFINE_BUF_ITEM_EVENT(xfs_trans_get_buf)
DEFINE_BUF_ITEM_EVENT(xfs_trans_get_buf_recur)
DEFINE_BUF_ITEM_EVENT(xfs_trans_getsb)
DEFINE_BUF_ITEM_EVENT(xfs_trans_getsb_recur)
DEFINE_BUF_ITEM_EVENT(xfs_trans_read_buf)
DEFINE_BUF_ITEM_EVENT(xfs_trans_read_buf_recur)
DEFINE_BUF_ITEM_EVENT(xfs_trans_log_buf)
DEFINE_BUF_ITEM_EVENT(xfs_trans_brelse)
DEFINE_BUF_ITEM_EVENT(xfs_trans_bjoin)
DEFINE_BUF_ITEM_EVENT(xfs_trans_bhold)
DEFINE_BUF_ITEM_EVENT(xfs_trans_bhold_release)
DEFINE_BUF_ITEM_EVENT(xfs_trans_binval)

#ifdef DEBUG
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_filestream_class,
  TP_PROTO(struct xfs_mount *mp, xfs_ino_t ino, xfs_agnumber_t agno),
  TP_ARGS(mp, ino, agno),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_ino_t, ino, ino)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, streams, xfs_filestream_peek_ag(mp, agno))
  )
)


#undef DEFINE_FILESTREAM_EVENT
#define DEFINE_FILESTREAM_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_filestream_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_ino_t ino, xfs_agnumber_t agno), \
  TP_ARGS(mp, ino, agno))
DEFINE_FILESTREAM_EVENT(xfs_filestream_free)
DEFINE_FILESTREAM_EVENT(xfs_filestream_lookup)
DEFINE_FILESTREAM_EVENT(xfs_filestream_scan)

LTTNG_TRACEPOINT_EVENT(xfs_filestream_pick,
  TP_PROTO(struct xfs_inode *ip, xfs_agnumber_t agno,
     xfs_extlen_t free, int nscan),
  TP_ARGS(ip, agno, free, nscan),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, streams, xfs_filestream_peek_ag(ip->i_mount, agno))
    ctf_integer(xfs_extlen_t, free, free)
    ctf_integer(int, nscan, nscan)
  )
)
#endif /* DEBUG */

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_lock_class,
  TP_PROTO(struct xfs_inode *ip, unsigned lock_flags,
     unsigned long caller_ip),
  TP_ARGS(ip,  lock_flags, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(int, lock_flags, lock_flags)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_LOCK_EVENT
#define DEFINE_LOCK_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_lock_class, name, \
  TP_PROTO(struct xfs_inode *ip, unsigned lock_flags, \
     unsigned long caller_ip), \
  TP_ARGS(ip,  lock_flags, caller_ip))
DEFINE_LOCK_EVENT(xfs_ilock)
DEFINE_LOCK_EVENT(xfs_ilock_nowait)
DEFINE_LOCK_EVENT(xfs_ilock_demote)
DEFINE_LOCK_EVENT(xfs_iunlock)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_inode_class,
  TP_PROTO(struct xfs_inode *ip),
  TP_ARGS(ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
  )
)

#undef DEFINE_INODE_EVENT
#define DEFINE_INODE_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_inode_class, name, \
  TP_PROTO(struct xfs_inode *ip), \
  TP_ARGS(ip))
DEFINE_INODE_EVENT(xfs_iget_skip)
DEFINE_INODE_EVENT(xfs_iget_reclaim)
DEFINE_INODE_EVENT(xfs_iget_reclaim_fail)
DEFINE_INODE_EVENT(xfs_iget_hit)
DEFINE_INODE_EVENT(xfs_iget_miss)

DEFINE_INODE_EVENT(xfs_getattr)
DEFINE_INODE_EVENT(xfs_setattr)
DEFINE_INODE_EVENT(xfs_readlink)
DEFINE_INODE_EVENT(xfs_inactive_symlink)
DEFINE_INODE_EVENT(xfs_alloc_file_space)
DEFINE_INODE_EVENT(xfs_free_file_space)
DEFINE_INODE_EVENT(xfs_zero_file_space)
DEFINE_INODE_EVENT(xfs_collapse_file_space)
DEFINE_INODE_EVENT(xfs_insert_file_space)
DEFINE_INODE_EVENT(xfs_readdir)
#ifdef CONFIG_XFS_POSIX_ACL
DEFINE_INODE_EVENT(xfs_get_acl)
#endif
DEFINE_INODE_EVENT(xfs_vm_bmap)
DEFINE_INODE_EVENT(xfs_file_ioctl)
DEFINE_INODE_EVENT(xfs_file_compat_ioctl)
DEFINE_INODE_EVENT(xfs_ioctl_setattr)
DEFINE_INODE_EVENT(xfs_dir_fsync)
DEFINE_INODE_EVENT(xfs_file_fsync)
DEFINE_INODE_EVENT(xfs_destroy_inode)
DEFINE_INODE_EVENT(xfs_update_time)

DEFINE_INODE_EVENT(xfs_dquot_dqalloc)
DEFINE_INODE_EVENT(xfs_dquot_dqdetach)

DEFINE_INODE_EVENT(xfs_inode_set_eofblocks_tag)
DEFINE_INODE_EVENT(xfs_inode_clear_eofblocks_tag)
DEFINE_INODE_EVENT(xfs_inode_free_eofblocks_invalid)
DEFINE_INODE_EVENT(xfs_inode_set_cowblocks_tag)
DEFINE_INODE_EVENT(xfs_inode_clear_cowblocks_tag)
DEFINE_INODE_EVENT(xfs_inode_free_cowblocks_invalid)

LTTNG_TRACEPOINT_EVENT(xfs_filemap_fault,
  TP_PROTO(struct xfs_inode *ip, enum page_entry_size pe_size,
     bool write_fault),
  TP_ARGS(ip, pe_size, write_fault),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(enum page_entry_size, pe_size, pe_size)
    ctf_integer(bool, write_fault, write_fault)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_iref_class,
  TP_PROTO(struct xfs_inode *ip, unsigned long caller_ip),
  TP_ARGS(ip, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(int, count, atomic_read(&VFS_I(ip)->i_count))
    ctf_integer(int, pincount, atomic_read(&ip->i_pincount))
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_iomap_prealloc_size,
  TP_PROTO(struct xfs_inode *ip, xfs_fsblock_t blocks, int shift,
     unsigned int writeio_blocks),
  TP_ARGS(ip, blocks, shift, writeio_blocks),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fsblock_t, blocks, blocks)
    ctf_integer(int, shift, shift)
    ctf_integer(unsigned int, writeio_blocks, writeio_blocks)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_irec_merge_pre,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, xfs_agino_t agino,
     uint16_t holemask, xfs_agino_t nagino, uint16_t nholemask),
  TP_ARGS(mp, agno, agino, holemask, nagino, nholemask),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agino_t, agino, agino)
    ctf_integer(uint16_t, holemask, holemask)
    ctf_integer(xfs_agino_t, nagino, nagino)
    ctf_integer(uint16_t, nholemask, holemask)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_irec_merge_post,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, xfs_agino_t agino,
     uint16_t holemask),
  TP_ARGS(mp, agno, agino, holemask),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agino_t, agino, agino)
    ctf_integer(uint16_t, holemask, holemask)
  )
)


#undef DEFINE_IREF_EVENT
#define DEFINE_IREF_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_iref_class, name, \
  TP_PROTO(struct xfs_inode *ip, unsigned long caller_ip), \
  TP_ARGS(ip, caller_ip))
DEFINE_IREF_EVENT(xfs_irele)
DEFINE_IREF_EVENT(xfs_inode_pin)
DEFINE_IREF_EVENT(xfs_inode_unpin)
DEFINE_IREF_EVENT(xfs_inode_unpin_nowait)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_namespace_class,
  TP_PROTO(struct xfs_inode *dp, struct xfs_name *name),
  TP_ARGS(dp, name),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, dp_ino, dp->i_ino)
    ctf_integer(int, namelen, name->len)
    ctf_sequence_hex(char, name, name->name, u32, name->len)
  )
)

#undef DEFINE_NAMESPACE_EVENT
#define DEFINE_NAMESPACE_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_namespace_class, name, \
  TP_PROTO(struct xfs_inode *dp, struct xfs_name *name), \
  TP_ARGS(dp, name))
DEFINE_NAMESPACE_EVENT(xfs_remove)
DEFINE_NAMESPACE_EVENT(xfs_link)
DEFINE_NAMESPACE_EVENT(xfs_lookup)
DEFINE_NAMESPACE_EVENT(xfs_create)
DEFINE_NAMESPACE_EVENT(xfs_symlink)

LTTNG_TRACEPOINT_EVENT(xfs_rename,
  TP_PROTO(struct xfs_inode *src_dp, struct xfs_inode *target_dp,
     struct xfs_name *src_name, struct xfs_name *target_name),
  TP_ARGS(src_dp, target_dp, src_name, target_name),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(src_dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, src_dp_ino, src_dp->i_ino)
    ctf_integer(xfs_ino_t, target_dp_ino, target_dp->i_ino)
    ctf_integer(int, src_namelen, src_name->len)
    ctf_integer(int, target_namelen, target_name->len)
    ctf_sequence_hex(char, src_name, src_name->name, u32, src_name->len)
    ctf_sequence_hex(char, target_name, target_name->name, u32, target_name->len)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_dquot_class,
  TP_PROTO(struct xfs_dquot *dqp),
  TP_ARGS(dqp),
  TP_FIELDS(
    ctf_integer(dev_t, dev, dqp->q_mount->m_super->s_dev)
    ctf_integer(u32, id, be32_to_cpu(dqp->q_core.d_id))
    ctf_integer(unsigned, flags, dqp->dq_flags)
    ctf_integer(unsigned, nrefs, dqp->q_nrefs)
    ctf_integer(unsigned long long, res_bcount, dqp->q_res_bcount)
    ctf_integer(unsigned long long, bcount, be64_to_cpu(dqp->q_core.d_bcount))
    ctf_integer(unsigned long long, icount, be64_to_cpu(dqp->q_core.d_icount))
    ctf_integer(unsigned long long, blk_hardlimit, be64_to_cpu(dqp->q_core.d_blk_hardlimit))
    ctf_integer(unsigned long long, blk_softlimit, be64_to_cpu(dqp->q_core.d_blk_softlimit))
    ctf_integer(unsigned long long, ino_hardlimit, be64_to_cpu(dqp->q_core.d_ino_hardlimit))
    ctf_integer(unsigned long long, ino_softlimit, be64_to_cpu(dqp->q_core.d_ino_softlimit))
  )
)

#undef DEFINE_DQUOT_EVENT
#define DEFINE_DQUOT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_dquot_class, name, \
  TP_PROTO(struct xfs_dquot *dqp), \
  TP_ARGS(dqp))
DEFINE_DQUOT_EVENT(xfs_dqadjust)
DEFINE_DQUOT_EVENT(xfs_dqreclaim_want)
DEFINE_DQUOT_EVENT(xfs_dqreclaim_dirty)
DEFINE_DQUOT_EVENT(xfs_dqreclaim_busy)
DEFINE_DQUOT_EVENT(xfs_dqreclaim_done)
DEFINE_DQUOT_EVENT(xfs_dqattach_found)
DEFINE_DQUOT_EVENT(xfs_dqattach_get)
DEFINE_DQUOT_EVENT(xfs_dqalloc)
DEFINE_DQUOT_EVENT(xfs_dqtobp_read)
DEFINE_DQUOT_EVENT(xfs_dqread)
DEFINE_DQUOT_EVENT(xfs_dqread_fail)
DEFINE_DQUOT_EVENT(xfs_dqget_hit)
DEFINE_DQUOT_EVENT(xfs_dqget_miss)
DEFINE_DQUOT_EVENT(xfs_dqget_freeing)
DEFINE_DQUOT_EVENT(xfs_dqget_dup)
DEFINE_DQUOT_EVENT(xfs_dqput)
DEFINE_DQUOT_EVENT(xfs_dqput_free)
DEFINE_DQUOT_EVENT(xfs_dqrele)
DEFINE_DQUOT_EVENT(xfs_dqflush)
DEFINE_DQUOT_EVENT(xfs_dqflush_force)
DEFINE_DQUOT_EVENT(xfs_dqflush_done)

LTTNG_TRACEPOINT_EVENT_CLASS_CODE(xfs_loggrant_class,
  TP_PROTO(struct xlog *log, struct xlog_ticket *tic),
  TP_ARGS(log, tic),

  TP_locvar(
    int grant_reserve_cycle;
    int grant_reserve_bytes;
    int grant_write_cycle;
    int grant_write_bytes;
  ),
  TP_code_pre(
    xlog_crack_grant_head(&log->l_reserve_head.grant,
                          &tp_locvar->grant_reserve_cycle,
                          &tp_locvar->grant_reserve_bytes);
    xlog_crack_grant_head(&log->l_write_head.grant,
                          &tp_locvar->grant_write_cycle,
                          &tp_locvar->grant_write_bytes);
  ),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(char, ocnt, tic->t_ocnt)
    ctf_integer(char, cnt, tic->t_cnt)
    ctf_integer(int, curr_res, tic->t_curr_res)
    ctf_integer(int, unit_res, tic->t_unit_res)
    ctf_integer(unsigned int, flags, tic->t_flags)
    ctf_integer(int, reserveq, list_empty(&log->l_reserve_head.waiters))
    ctf_integer(int, writeq, list_empty(&log->l_write_head.waiters))
    ctf_integer(int, grant_reserve_cycle, tp_locvar->grant_reserve_cycle)
    ctf_integer(int, grant_reserve_bytes, tp_locvar->grant_reserve_bytes)
    ctf_integer(int, grant_write_cycle, tp_locvar->grant_write_cycle)
    ctf_integer(int, grant_write_bytes, tp_locvar->grant_write_bytes)
    ctf_integer(int, curr_cycle, log->l_curr_cycle)
    ctf_integer(int, curr_block, log->l_curr_block)
    ctf_integer(xfs_lsn_t, tail_lsn, atomic64_read(&log->l_tail_lsn))
  ),
  TP_code_post()
)

#undef DEFINE_LOGGRANT_EVENT
#define DEFINE_LOGGRANT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_loggrant_class, name, \
  TP_PROTO(struct xlog *log, struct xlog_ticket *tic), \
  TP_ARGS(log, tic))
DEFINE_LOGGRANT_EVENT(xfs_log_done_nonperm)
DEFINE_LOGGRANT_EVENT(xfs_log_done_perm)
DEFINE_LOGGRANT_EVENT(xfs_log_umount_write)
DEFINE_LOGGRANT_EVENT(xfs_log_grant_sleep)
DEFINE_LOGGRANT_EVENT(xfs_log_grant_wake)
DEFINE_LOGGRANT_EVENT(xfs_log_grant_wake_up)
DEFINE_LOGGRANT_EVENT(xfs_log_reserve)
DEFINE_LOGGRANT_EVENT(xfs_log_reserve_exit)
DEFINE_LOGGRANT_EVENT(xfs_log_regrant)
DEFINE_LOGGRANT_EVENT(xfs_log_regrant_exit)
DEFINE_LOGGRANT_EVENT(xfs_log_regrant_reserve_enter)
DEFINE_LOGGRANT_EVENT(xfs_log_regrant_reserve_exit)
DEFINE_LOGGRANT_EVENT(xfs_log_regrant_reserve_sub)
DEFINE_LOGGRANT_EVENT(xfs_log_ungrant_enter)
DEFINE_LOGGRANT_EVENT(xfs_log_ungrant_exit)
DEFINE_LOGGRANT_EVENT(xfs_log_ungrant_sub)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_log_item_class,
  TP_PROTO(struct xfs_log_item *lip),
  TP_ARGS(lip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, lip->li_mountp->m_super->s_dev)
    ctf_integer(void *, lip, lip)
    ctf_integer(uint, type, lip->li_type)
    ctf_integer(uint, flags, lip->li_flags)
    ctf_integer(xfs_lsn_t, lsn, lip->li_lsn)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_log_force,
  TP_PROTO(struct xfs_mount *mp, xfs_lsn_t lsn, unsigned long caller_ip),
  TP_ARGS(mp, lsn, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_lsn_t, lsn, lsn)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_LOG_ITEM_EVENT
#define DEFINE_LOG_ITEM_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_log_item_class, name, \
  TP_PROTO(struct xfs_log_item *lip), \
  TP_ARGS(lip))
DEFINE_LOG_ITEM_EVENT(xfs_ail_push)
DEFINE_LOG_ITEM_EVENT(xfs_ail_pinned)
DEFINE_LOG_ITEM_EVENT(xfs_ail_locked)
DEFINE_LOG_ITEM_EVENT(xfs_ail_flushing)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_ail_class,
  TP_PROTO(struct xfs_log_item *lip, xfs_lsn_t old_lsn, xfs_lsn_t new_lsn),
  TP_ARGS(lip, old_lsn, new_lsn),
  TP_FIELDS(
    ctf_integer(dev_t, dev, lip->li_mountp->m_super->s_dev)
    ctf_integer(void *, lip, lip)
    ctf_integer(uint, type, lip->li_type)
    ctf_integer(uint, flags, lip->li_flags)
    ctf_integer(xfs_lsn_t, old_lsn, old_lsn)
    ctf_integer(xfs_lsn_t, new_lsn, new_lsn)
  )
)

#undef DEFINE_AIL_EVENT
#define DEFINE_AIL_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_ail_class, name, \
  TP_PROTO(struct xfs_log_item *lip, xfs_lsn_t old_lsn, xfs_lsn_t new_lsn), \
  TP_ARGS(lip, old_lsn, new_lsn))
DEFINE_AIL_EVENT(xfs_ail_insert)
DEFINE_AIL_EVENT(xfs_ail_move)
DEFINE_AIL_EVENT(xfs_ail_delete)

LTTNG_TRACEPOINT_EVENT(xfs_log_assign_tail_lsn,
  TP_PROTO(struct xlog *log, xfs_lsn_t new_lsn),
  TP_ARGS(log, new_lsn),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(xfs_lsn_t, new_lsn, new_lsn)
    ctf_integer(xfs_lsn_t, old_lsn, atomic64_read(&log->l_tail_lsn))
    ctf_integer(xfs_lsn_t, last_sync_lsn, atomic64_read(&log->l_last_sync_lsn))
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_file_class,
  TP_PROTO(struct xfs_inode *ip, size_t count, loff_t offset),
  TP_ARGS(ip, count, offset),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fsize_t, size, ip->i_d.di_size)
    ctf_integer(loff_t, offset, offset)
    ctf_integer(size_t, count, count)
  )
)

#undef DEFINE_RW_EVENT
#define DEFINE_RW_EVENT(name)		\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_file_class, name,	\
  TP_PROTO(struct xfs_inode *ip, size_t count, loff_t offset),	\
  TP_ARGS(ip, count, offset))
DEFINE_RW_EVENT(xfs_file_buffered_read)
DEFINE_RW_EVENT(xfs_file_direct_read)
DEFINE_RW_EVENT(xfs_file_dax_read)
DEFINE_RW_EVENT(xfs_file_buffered_write)
DEFINE_RW_EVENT(xfs_file_direct_write)
DEFINE_RW_EVENT(xfs_file_dax_write)

#ifdef DEBUG
LTTNG_TRACEPOINT_EVENT_CLASS_CODE(xfs_page_class,
  TP_PROTO(struct inode *inode, struct page *page, unsigned long off,
     unsigned int len),
  TP_ARGS(inode, page, off, len),
  TP_locvar(
    int delalloc;
    int unwritten;
  ),

  TP_code_pre(
    tp_locvar->delalloc = -1;
    tp_locvar->unwritten = -1;

    if (page_has_buffers(page)) {
      xfs_count_page_state(page, &tp_locvar->delalloc, &tp_locvar->unwritten);
    }
  ),

  TP_FIELDS(
    ctf_integer(dev_t, dev, inode->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, XFS_I(inode)->i_ino)
    ctf_integer(pgoff_t, pgoff, page_offset(page))
    ctf_integer(loff_t, size, i_size_read(inode))
    ctf_integer(unsigned long, offset, off)
    ctf_integer(unsigned int, length, len)
    ctf_integer(int, delalloc, tp_locvar->delalloc)
    ctf_integer(int, unwritten, tp_locvar->unwritten)
  ),
  TP_code_post()
)

#undef DEFINE_PAGE_EVENT
#define DEFINE_PAGE_EVENT(name)		\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_page_class, name,	\
  TP_PROTO(struct inode *inode, struct page *page, unsigned long off, \
     unsigned int len),	\
  TP_ARGS(inode, page, off, len))
DEFINE_PAGE_EVENT(xfs_writepage)
DEFINE_PAGE_EVENT(xfs_releasepage)
DEFINE_PAGE_EVENT(xfs_invalidatepage)
#endif /* DEBUG */

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_readpage_class,
  TP_PROTO(struct inode *inode, int nr_pages),
  TP_ARGS(inode, nr_pages),
  TP_FIELDS(
    ctf_integer(dev_t, dev, inode->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, inode->i_ino)
    ctf_integer(int, nr_pages, nr_pages)
  )
)

#undef DEFINE_READPAGE_EVENT
#define DEFINE_READPAGE_EVENT(name)		\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_readpage_class, name,	\
  TP_PROTO(struct inode *inode, int nr_pages), \
  TP_ARGS(inode, nr_pages))
DEFINE_READPAGE_EVENT(xfs_vm_readpage)
DEFINE_READPAGE_EVENT(xfs_vm_readpages)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_imap_class,
  TP_PROTO(struct xfs_inode *ip, xfs_off_t offset, ssize_t count,
     int type, struct xfs_bmbt_irec *irec),
  TP_ARGS(ip, offset, count, type, irec),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(loff_t, size, ip->i_d.di_size)
    ctf_integer(loff_t, offset, offset)
    ctf_integer(size_t, count, count)
    ctf_integer(int, type, type)
    ctf_integer(xfs_fileoff_t, startoff, irec ? irec->br_startoff : 0)
    ctf_integer(xfs_fsblock_t, startblock, irec ? irec->br_startblock : 0)
    ctf_integer(xfs_filblks_t, blockcount, irec ? irec->br_blockcount : 0)
  )
)

#undef DEFINE_IOMAP_EVENT
#define DEFINE_IOMAP_EVENT(name)	\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_imap_class, name,	\
  TP_PROTO(struct xfs_inode *ip, xfs_off_t offset, ssize_t count,	\
     int type, struct xfs_bmbt_irec *irec),		\
  TP_ARGS(ip, offset, count, type, irec))
DEFINE_IOMAP_EVENT(xfs_map_blocks_found)
DEFINE_IOMAP_EVENT(xfs_map_blocks_alloc)
DEFINE_IOMAP_EVENT(xfs_get_blocks_found)
DEFINE_IOMAP_EVENT(xfs_get_blocks_alloc)
DEFINE_IOMAP_EVENT(xfs_get_blocks_map_direct)
DEFINE_IOMAP_EVENT(xfs_iomap_alloc)
DEFINE_IOMAP_EVENT(xfs_iomap_found)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_simple_io_class,
  TP_PROTO(struct xfs_inode *ip, xfs_off_t offset, ssize_t count),
  TP_ARGS(ip, offset, count),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(loff_t, isize, VFS_I(ip)->i_size)
    ctf_integer(loff_t, disize, ip->i_d.di_size)
    ctf_integer(loff_t, offset, offset)
    ctf_integer(size_t, count, count)
  )
)

#undef DEFINE_SIMPLE_IO_EVENT
#define DEFINE_SIMPLE_IO_EVENT(name)	\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_simple_io_class, name,	\
  TP_PROTO(struct xfs_inode *ip, xfs_off_t offset, ssize_t count),	\
  TP_ARGS(ip, offset, count))
DEFINE_SIMPLE_IO_EVENT(xfs_delalloc_enospc)
DEFINE_SIMPLE_IO_EVENT(xfs_unwritten_convert)
DEFINE_SIMPLE_IO_EVENT(xfs_get_blocks_notfound)
DEFINE_SIMPLE_IO_EVENT(xfs_setfilesize)
DEFINE_SIMPLE_IO_EVENT(xfs_zero_eof)
DEFINE_SIMPLE_IO_EVENT(xfs_end_io_direct_write)
DEFINE_SIMPLE_IO_EVENT(xfs_end_io_direct_write_unwritten)
DEFINE_SIMPLE_IO_EVENT(xfs_end_io_direct_write_append)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_itrunc_class,
  TP_PROTO(struct xfs_inode *ip, xfs_fsize_t new_size),
  TP_ARGS(ip, new_size),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fsize_t, size, ip->i_d.di_size)
    ctf_integer(xfs_fsize_t, new_size, new_size)
  )
)

#undef DEFINE_ITRUNC_EVENT
#define DEFINE_ITRUNC_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_itrunc_class, name, \
  TP_PROTO(struct xfs_inode *ip, xfs_fsize_t new_size), \
  TP_ARGS(ip, new_size))
DEFINE_ITRUNC_EVENT(xfs_itruncate_extents_start)
DEFINE_ITRUNC_EVENT(xfs_itruncate_extents_end)

LTTNG_TRACEPOINT_EVENT(xfs_pagecache_inval,
  TP_PROTO(struct xfs_inode *ip, xfs_off_t start, xfs_off_t finish),
  TP_ARGS(ip, start, finish),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fsize_t, size, ip->i_d.di_size)
    ctf_integer(xfs_off_t, start, start)
    ctf_integer(xfs_off_t, finish, finish)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_bunmap,
  TP_PROTO(struct xfs_inode *ip, xfs_fileoff_t bno, xfs_filblks_t len,
     int flags, unsigned long caller_ip),
  TP_ARGS(ip, bno, len, flags, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fsize_t, size, ip->i_d.di_size)
    ctf_integer(xfs_fileoff_t, bno, bno)
    ctf_integer(xfs_filblks_t, len, len)
    ctf_integer(unsigned long, caller_ip, caller_ip)
    ctf_integer(int, flags, flags)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_extent_busy_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_extlen_t len),
  TP_ARGS(mp, agno, agbno, len),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
  )
)

#undef DEFINE_BUSY_EVENT
#define DEFINE_BUSY_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_extent_busy_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     xfs_agblock_t agbno, xfs_extlen_t len), \
  TP_ARGS(mp, agno, agbno, len))
DEFINE_BUSY_EVENT(xfs_extent_busy)
DEFINE_BUSY_EVENT(xfs_extent_busy_enomem)
DEFINE_BUSY_EVENT(xfs_extent_busy_force)
DEFINE_BUSY_EVENT(xfs_extent_busy_reuse)
DEFINE_BUSY_EVENT(xfs_extent_busy_clear)

LTTNG_TRACEPOINT_EVENT(xfs_extent_busy_trim,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_extlen_t len,
     xfs_agblock_t tbno, xfs_extlen_t tlen),
  TP_ARGS(mp, agno, agbno, len, tbno, tlen),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(xfs_agblock_t, tbno, tbno)
    ctf_integer(xfs_extlen_t, tlen, tlen)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_agf_class,
  TP_PROTO(struct xfs_mount *mp, struct xfs_agf *agf, int flags,
     unsigned long caller_ip),
  TP_ARGS(mp, agf, flags, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, be32_to_cpu(agf->agf_seqno))
    ctf_integer(int, flags, flags)
    ctf_integer(__u32, length, be32_to_cpu(agf->agf_length))
    ctf_integer(__u32, bno_root, be32_to_cpu(agf->agf_roots[XFS_BTNUM_BNO]))
    ctf_integer(__u32, cnt_root, be32_to_cpu(agf->agf_roots[XFS_BTNUM_CNT]))
    ctf_integer(__u32, bno_level, be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]))
    ctf_integer(__u32, cnt_level, be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]))
    ctf_integer(__u32, flfirst, be32_to_cpu(agf->agf_flfirst))
    ctf_integer(__u32, fllast, be32_to_cpu(agf->agf_fllast))
    ctf_integer(__u32, flcount, be32_to_cpu(agf->agf_flcount))
    ctf_integer(__u32, freeblks, be32_to_cpu(agf->agf_freeblks))
    ctf_integer(__u32, longest, be32_to_cpu(agf->agf_longest))
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_AGF_EVENT
#define DEFINE_AGF_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_agf_class, name, \
  TP_PROTO(struct xfs_mount *mp, struct xfs_agf *agf, int flags, \
     unsigned long caller_ip), \
  TP_ARGS(mp, agf, flags, caller_ip))
DEFINE_AGF_EVENT(xfs_agf)
DEFINE_AGF_EVENT(xfs_agfl_reset)

LTTNG_TRACEPOINT_EVENT(xfs_free_extent,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, xfs_agblock_t agbno,
     xfs_extlen_t len, enum xfs_ag_resv_type resv, int haveleft,
     int haveright),
  TP_ARGS(mp, agno, agbno, len, resv, haveleft, haveright),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(int, resv, resv)
    ctf_integer(int, haveleft, haveleft)
    ctf_integer(int, haveright, haveright)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_alloc_class,
  TP_PROTO(struct xfs_alloc_arg *args),
  TP_ARGS(args),
  TP_FIELDS(
    ctf_integer(dev_t, dev, args->mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, args->agno)
    ctf_integer(xfs_agblock_t, agbno, args->agbno)
    ctf_integer(xfs_extlen_t, minlen, args->minlen)
    ctf_integer(xfs_extlen_t, maxlen, args->maxlen)
    ctf_integer(xfs_extlen_t, mod, args->mod)
    ctf_integer(xfs_extlen_t, prod, args->prod)
    ctf_integer(xfs_extlen_t, minleft, args->minleft)
    ctf_integer(xfs_extlen_t, total, args->total)
    ctf_integer(xfs_extlen_t, alignment, args->alignment)
    ctf_integer(xfs_extlen_t, minalignslop, args->minalignslop)
    ctf_integer(xfs_extlen_t, len, args->len)
    ctf_integer(short, type, args->type)
    ctf_integer(short, otype, args->otype)
    ctf_integer(char, wasdel, args->wasdel)
    ctf_integer(char, wasfromfl, args->wasfromfl)
    ctf_integer(int, resv, args->resv)
    ctf_integer(int, datatype, args->datatype)
    ctf_integer(xfs_fsblock_t, firstblock, args->firstblock)
  )
)


#undef DEFINE_ALLOC_EVENT
#define DEFINE_ALLOC_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_alloc_class, name, \
  TP_PROTO(struct xfs_alloc_arg *args), \
  TP_ARGS(args))
DEFINE_ALLOC_EVENT(xfs_alloc_exact_done)
DEFINE_ALLOC_EVENT(xfs_alloc_exact_notfound)
DEFINE_ALLOC_EVENT(xfs_alloc_exact_error)
DEFINE_ALLOC_EVENT(xfs_alloc_near_nominleft)
DEFINE_ALLOC_EVENT(xfs_alloc_near_first)
DEFINE_ALLOC_EVENT(xfs_alloc_near_greater)
DEFINE_ALLOC_EVENT(xfs_alloc_near_lesser)
DEFINE_ALLOC_EVENT(xfs_alloc_near_error)
DEFINE_ALLOC_EVENT(xfs_alloc_near_noentry)
DEFINE_ALLOC_EVENT(xfs_alloc_near_busy)
DEFINE_ALLOC_EVENT(xfs_alloc_size_neither)
DEFINE_ALLOC_EVENT(xfs_alloc_size_noentry)
DEFINE_ALLOC_EVENT(xfs_alloc_size_nominleft)
DEFINE_ALLOC_EVENT(xfs_alloc_size_done)
DEFINE_ALLOC_EVENT(xfs_alloc_size_error)
DEFINE_ALLOC_EVENT(xfs_alloc_size_busy)
DEFINE_ALLOC_EVENT(xfs_alloc_small_freelist)
DEFINE_ALLOC_EVENT(xfs_alloc_small_notenough)
DEFINE_ALLOC_EVENT(xfs_alloc_small_done)
DEFINE_ALLOC_EVENT(xfs_alloc_small_error)
DEFINE_ALLOC_EVENT(xfs_alloc_vextent_badargs)
DEFINE_ALLOC_EVENT(xfs_alloc_vextent_nofix)
DEFINE_ALLOC_EVENT(xfs_alloc_vextent_noagbp)
DEFINE_ALLOC_EVENT(xfs_alloc_vextent_loopfailed)
DEFINE_ALLOC_EVENT(xfs_alloc_vextent_allfailed)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_da_class,
  TP_PROTO(struct xfs_da_args *args),
  TP_ARGS(args),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(args->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, args->dp->i_ino)
    ctf_sequence_hex(char, name, args->name, u32, args->namelen)
    ctf_integer(int, namelen, args->namelen)
    ctf_integer(xfs_dahash_t, hashval, args->hashval)
    ctf_integer(xfs_ino_t, inumber, args->inumber)
    ctf_integer(int, op_flags, args->op_flags)
  )
)

#undef DEFINE_DIR2_EVENT
#define DEFINE_DIR2_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_da_class, name, \
  TP_PROTO(struct xfs_da_args *args), \
  TP_ARGS(args))
DEFINE_DIR2_EVENT(xfs_dir2_sf_addname)
DEFINE_DIR2_EVENT(xfs_dir2_sf_create)
DEFINE_DIR2_EVENT(xfs_dir2_sf_lookup)
DEFINE_DIR2_EVENT(xfs_dir2_sf_replace)
DEFINE_DIR2_EVENT(xfs_dir2_sf_removename)
DEFINE_DIR2_EVENT(xfs_dir2_sf_toino4)
DEFINE_DIR2_EVENT(xfs_dir2_sf_toino8)
DEFINE_DIR2_EVENT(xfs_dir2_sf_to_block)
DEFINE_DIR2_EVENT(xfs_dir2_block_addname)
DEFINE_DIR2_EVENT(xfs_dir2_block_lookup)
DEFINE_DIR2_EVENT(xfs_dir2_block_replace)
DEFINE_DIR2_EVENT(xfs_dir2_block_removename)
DEFINE_DIR2_EVENT(xfs_dir2_block_to_sf)
DEFINE_DIR2_EVENT(xfs_dir2_block_to_leaf)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_addname)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_lookup)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_replace)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_removename)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_to_block)
DEFINE_DIR2_EVENT(xfs_dir2_leaf_to_node)
DEFINE_DIR2_EVENT(xfs_dir2_node_addname)
DEFINE_DIR2_EVENT(xfs_dir2_node_lookup)
DEFINE_DIR2_EVENT(xfs_dir2_node_replace)
DEFINE_DIR2_EVENT(xfs_dir2_node_removename)
DEFINE_DIR2_EVENT(xfs_dir2_node_to_leaf)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_attr_class,
  TP_PROTO(struct xfs_da_args *args),
  TP_ARGS(args),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(args->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, args->dp->i_ino)
    ctf_sequence_hex(char, name, args->name, u32, args->namelen)
    ctf_integer(int, namelen, args->namelen)
    ctf_integer(int, valuelen, args->valuelen)
    ctf_integer(xfs_dahash_t, hashval, args->hashval)
    ctf_integer(int, op_flags, args->op_flags)
  )
)

#undef DEFINE_ATTR_EVENT
#define DEFINE_ATTR_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_attr_class, name, \
  TP_PROTO(struct xfs_da_args *args), \
  TP_ARGS(args))
DEFINE_ATTR_EVENT(xfs_attr_sf_add)
DEFINE_ATTR_EVENT(xfs_attr_sf_addname)
DEFINE_ATTR_EVENT(xfs_attr_sf_create)
DEFINE_ATTR_EVENT(xfs_attr_sf_lookup)
DEFINE_ATTR_EVENT(xfs_attr_sf_remove)
DEFINE_ATTR_EVENT(xfs_attr_sf_to_leaf)

DEFINE_ATTR_EVENT(xfs_attr_leaf_add)
DEFINE_ATTR_EVENT(xfs_attr_leaf_add_old)
DEFINE_ATTR_EVENT(xfs_attr_leaf_add_new)
DEFINE_ATTR_EVENT(xfs_attr_leaf_add_work)
DEFINE_ATTR_EVENT(xfs_attr_leaf_addname)
DEFINE_ATTR_EVENT(xfs_attr_leaf_create)
DEFINE_ATTR_EVENT(xfs_attr_leaf_compact)
DEFINE_ATTR_EVENT(xfs_attr_leaf_get)
DEFINE_ATTR_EVENT(xfs_attr_leaf_lookup)
DEFINE_ATTR_EVENT(xfs_attr_leaf_replace)
DEFINE_ATTR_EVENT(xfs_attr_leaf_remove)
DEFINE_ATTR_EVENT(xfs_attr_leaf_removename)
DEFINE_ATTR_EVENT(xfs_attr_leaf_split)
DEFINE_ATTR_EVENT(xfs_attr_leaf_split_before)
DEFINE_ATTR_EVENT(xfs_attr_leaf_split_after)
DEFINE_ATTR_EVENT(xfs_attr_leaf_clearflag)
DEFINE_ATTR_EVENT(xfs_attr_leaf_setflag)
DEFINE_ATTR_EVENT(xfs_attr_leaf_flipflags)
DEFINE_ATTR_EVENT(xfs_attr_leaf_to_sf)
DEFINE_ATTR_EVENT(xfs_attr_leaf_to_node)
DEFINE_ATTR_EVENT(xfs_attr_leaf_rebalance)
DEFINE_ATTR_EVENT(xfs_attr_leaf_unbalance)
DEFINE_ATTR_EVENT(xfs_attr_leaf_toosmall)

DEFINE_ATTR_EVENT(xfs_attr_node_addname)
DEFINE_ATTR_EVENT(xfs_attr_node_get)
DEFINE_ATTR_EVENT(xfs_attr_node_replace)
DEFINE_ATTR_EVENT(xfs_attr_node_removename)

DEFINE_ATTR_EVENT(xfs_attr_fillstate)
DEFINE_ATTR_EVENT(xfs_attr_refillstate)

DEFINE_ATTR_EVENT(xfs_attr_rmtval_get)
DEFINE_ATTR_EVENT(xfs_attr_rmtval_set)
DEFINE_ATTR_EVENT(xfs_attr_rmtval_remove)


#undef DEFINE_DA_EVENT
#define DEFINE_DA_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_da_class, name, \
  TP_PROTO(struct xfs_da_args *args), \
  TP_ARGS(args))
DEFINE_DA_EVENT(xfs_da_split)
DEFINE_DA_EVENT(xfs_da_join)
DEFINE_DA_EVENT(xfs_da_link_before)
DEFINE_DA_EVENT(xfs_da_link_after)
DEFINE_DA_EVENT(xfs_da_unlink_back)
DEFINE_DA_EVENT(xfs_da_unlink_forward)
DEFINE_DA_EVENT(xfs_da_root_split)
DEFINE_DA_EVENT(xfs_da_root_join)
DEFINE_DA_EVENT(xfs_da_node_add)
DEFINE_DA_EVENT(xfs_da_node_create)
DEFINE_DA_EVENT(xfs_da_node_split)
DEFINE_DA_EVENT(xfs_da_node_remove)
DEFINE_DA_EVENT(xfs_da_node_rebalance)
DEFINE_DA_EVENT(xfs_da_node_unbalance)
DEFINE_DA_EVENT(xfs_da_node_toosmall)
DEFINE_DA_EVENT(xfs_da_swap_lastblock)
DEFINE_DA_EVENT(xfs_da_grow_inode)
DEFINE_DA_EVENT(xfs_da_shrink_inode)
DEFINE_DA_EVENT(xfs_da_fixhashpath)
DEFINE_DA_EVENT(xfs_da_path_shift)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_dir2_space_class,
  TP_PROTO(struct xfs_da_args *args, int idx),
  TP_ARGS(args, idx),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(args->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, args->dp->i_ino)
    ctf_integer(int, op_flags, args->op_flags)
    ctf_integer(int, idx, idx)
  )
)


#undef DEFINE_DIR2_SPACE_EVENT
#define DEFINE_DIR2_SPACE_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_dir2_space_class, name, \
  TP_PROTO(struct xfs_da_args *args, int idx), \
  TP_ARGS(args, idx))
DEFINE_DIR2_SPACE_EVENT(xfs_dir2_leafn_add)
DEFINE_DIR2_SPACE_EVENT(xfs_dir2_leafn_remove)
DEFINE_DIR2_SPACE_EVENT(xfs_dir2_grow_inode)
DEFINE_DIR2_SPACE_EVENT(xfs_dir2_shrink_inode)

LTTNG_TRACEPOINT_EVENT(xfs_dir2_leafn_moveents,
  TP_PROTO(struct xfs_da_args *args, int src_idx, int dst_idx, int count),
  TP_ARGS(args, src_idx, dst_idx, count),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(args->dp)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, args->dp->i_ino)
    ctf_integer(int, op_flags, args->op_flags)
    ctf_integer(int, src_idx, src_idx)
    ctf_integer(int, dst_idx, dst_idx)
    ctf_integer(int, count, count)
  )
)

#undef XFS_SWAPEXT_INODES
#define XFS_SWAPEXT_INODES \
  { 0,	"target" }, \
  { 1,	"temp" }

#undef XFS_INODE_FORMAT_STR
#define XFS_INODE_FORMAT_STR \
  { 0,	"invalid" }, \
  { 1,	"local" }, \
  { 2,	"extent" }, \
  { 3,	"btree" }

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_swap_extent_class,
  TP_PROTO(struct xfs_inode *ip, int which),
  TP_ARGS(ip, which),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(int, which, which)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(int, format, ip->i_d.di_format)
    ctf_integer(int, nex, ip->i_d.di_nextents)
    ctf_integer(int, broot_size, ip->i_df.if_broot_bytes)
    ctf_integer(int, fork_off, XFS_IFORK_BOFF(ip))
  )
)

#undef DEFINE_SWAPEXT_EVENT
#define DEFINE_SWAPEXT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_swap_extent_class, name, \
  TP_PROTO(struct xfs_inode *ip, int which), \
  TP_ARGS(ip, which))

DEFINE_SWAPEXT_EVENT(xfs_swap_extent_before)
DEFINE_SWAPEXT_EVENT(xfs_swap_extent_after)

LTTNG_TRACEPOINT_EVENT(xfs_log_recover,
  TP_PROTO(struct xlog *log, xfs_daddr_t headblk, xfs_daddr_t tailblk),
  TP_ARGS(log, headblk, tailblk),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(xfs_daddr_t, headblk, headblk)
    ctf_integer(xfs_daddr_t, tailblk, tailblk)
  )
)

LTTNG_TRACEPOINT_EVENT(xfs_log_recover_record,
  TP_PROTO(struct xlog *log, struct xlog_rec_header *rhead, int pass),
  TP_ARGS(log, rhead, pass),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(xfs_lsn_t, lsn, be64_to_cpu(rhead->h_lsn))
    ctf_integer(int, len, be32_to_cpu(rhead->h_len))
    ctf_integer(int, num_logops, be32_to_cpu(rhead->h_num_logops))
    ctf_integer(int, pass, pass)
  )
)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_log_recover_item_class,
  TP_PROTO(struct xlog *log, struct xlog_recover *trans,
    struct xlog_recover_item *item, int pass),
  TP_ARGS(log, trans, item, pass),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(unsigned long, item, (unsigned long)item)
    ctf_integer(xlog_tid_t, tid, trans->r_log_tid)
    ctf_integer(xfs_lsn_t, lsn, trans->r_lsn)
    ctf_integer(int, type, ITEM_TYPE(item))
    ctf_integer(int, pass, pass)
    ctf_integer(int, count, item->ri_cnt)
    ctf_integer(int, total, item->ri_total)
  )
)

#undef DEFINE_LOG_RECOVER_ITEM
#define DEFINE_LOG_RECOVER_ITEM(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_log_recover_item_class, name, \
  TP_PROTO(struct xlog *log, struct xlog_recover *trans, \
    struct xlog_recover_item *item, int pass), \
  TP_ARGS(log, trans, item, pass))

DEFINE_LOG_RECOVER_ITEM(xfs_log_recover_item_add)
DEFINE_LOG_RECOVER_ITEM(xfs_log_recover_item_add_cont)
DEFINE_LOG_RECOVER_ITEM(xfs_log_recover_item_reorder_head)
DEFINE_LOG_RECOVER_ITEM(xfs_log_recover_item_reorder_tail)
DEFINE_LOG_RECOVER_ITEM(xfs_log_recover_item_recover)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_log_recover_buf_item_class,
  TP_PROTO(struct xlog *log, struct xfs_buf_log_format *buf_f),
  TP_ARGS(log, buf_f),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(int64_t, blkno, buf_f->blf_blkno)
    ctf_integer(unsigned short, len, buf_f->blf_len)
    ctf_integer(unsigned short, flags, buf_f->blf_flags)
    ctf_integer(unsigned short, size, buf_f->blf_size)
    ctf_integer(unsigned int, map_size, buf_f->blf_map_size)
  )
)


#undef DEFINE_LOG_RECOVER_BUF_ITEM
#define DEFINE_LOG_RECOVER_BUF_ITEM(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_log_recover_buf_item_class, name, \
  TP_PROTO(struct xlog *log, struct xfs_buf_log_format *buf_f), \
  TP_ARGS(log, buf_f))

DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_not_cancel)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_cancel)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_cancel_add)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_cancel_ref_inc)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_recover)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_skip)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_inode_buf)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_reg_buf)
DEFINE_LOG_RECOVER_BUF_ITEM(xfs_log_recover_buf_dquot_buf)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_log_recover_ino_item_class,
  TP_PROTO(struct xlog *log, struct xfs_inode_log_format *in_f),
  TP_ARGS(log, in_f),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(xfs_ino_t, ino, in_f->ilf_ino)
    ctf_integer(unsigned short, size, in_f->ilf_size)
    ctf_integer(int, fields, in_f->ilf_fields)
    ctf_integer(unsigned short, asize, in_f->ilf_asize)
    ctf_integer(unsigned short, dsize, in_f->ilf_dsize)
    ctf_integer(int64_t, blkno, in_f->ilf_blkno)
    ctf_integer(int, len, in_f->ilf_len)
    ctf_integer(int, boffset, in_f->ilf_boffset)
  )
)

#undef DEFINE_LOG_RECOVER_INO_ITEM
#define DEFINE_LOG_RECOVER_INO_ITEM(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_log_recover_ino_item_class, name, \
  TP_PROTO(struct xlog *log, struct xfs_inode_log_format *in_f), \
  TP_ARGS(log, in_f))

DEFINE_LOG_RECOVER_INO_ITEM(xfs_log_recover_inode_recover)
DEFINE_LOG_RECOVER_INO_ITEM(xfs_log_recover_inode_cancel)
DEFINE_LOG_RECOVER_INO_ITEM(xfs_log_recover_inode_skip)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_log_recover_icreate_item_class,
  TP_PROTO(struct xlog *log, struct xfs_icreate_log *in_f),
  TP_ARGS(log, in_f),
  TP_FIELDS(
    ctf_integer(dev_t, dev, log->l_mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, be32_to_cpu(in_f->icl_ag))
    ctf_integer(xfs_agblock_t, agbno, be32_to_cpu(in_f->icl_agbno))
    ctf_integer(unsigned int, count, be32_to_cpu(in_f->icl_count))
    ctf_integer(unsigned int, isize, be32_to_cpu(in_f->icl_isize))
    ctf_integer(xfs_agblock_t, length, be32_to_cpu(in_f->icl_length))
    ctf_integer(unsigned int, gen, be32_to_cpu(in_f->icl_gen))
  )
)

#undef DEFINE_LOG_RECOVER_ICREATE_ITEM
#define DEFINE_LOG_RECOVER_ICREATE_ITEM(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_log_recover_icreate_item_class, name, \
  TP_PROTO(struct xlog *log, struct xfs_icreate_log *in_f), \
  TP_ARGS(log, in_f))

DEFINE_LOG_RECOVER_ICREATE_ITEM(xfs_log_recover_icreate_cancel)
DEFINE_LOG_RECOVER_ICREATE_ITEM(xfs_log_recover_icreate_recover)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_discard_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_extlen_t len),
  TP_ARGS(mp, agno, agbno, len),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
  )
)


#undef DEFINE_DISCARD_EVENT
#define DEFINE_DISCARD_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_discard_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     xfs_agblock_t agbno, xfs_extlen_t len), \
  TP_ARGS(mp, agno, agbno, len))
DEFINE_DISCARD_EVENT(xfs_discard_extent)
DEFINE_DISCARD_EVENT(xfs_discard_toosmall)
DEFINE_DISCARD_EVENT(xfs_discard_exclude)
DEFINE_DISCARD_EVENT(xfs_discard_busy)

/* btree cursor events */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_btree_cur_class,
  TP_PROTO(struct xfs_btree_cur *cur, int level, struct xfs_buf *bp),
  TP_ARGS(cur, level, bp),
  TP_FIELDS(
    ctf_integer(dev_t, dev, cur->bc_mp->m_super->s_dev)
    ctf_integer(xfs_btnum_t, btnum, cur->bc_btnum)
    ctf_integer(int, level, level)
    ctf_integer(int, nlevels, cur->bc_nlevels)
    ctf_integer(int, ptr, cur->bc_ptrs[level])
    ctf_integer(xfs_daddr_t, daddr, bp ? bp->b_bn : -1)
  )
)


#undef DEFINE_BTREE_CUR_EVENT
#define DEFINE_BTREE_CUR_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_btree_cur_class, name, \
  TP_PROTO(struct xfs_btree_cur *cur, int level, struct xfs_buf *bp), \
  TP_ARGS(cur, level, bp))
DEFINE_BTREE_CUR_EVENT(xfs_btree_updkeys)
DEFINE_BTREE_CUR_EVENT(xfs_btree_overlapped_query_range)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_defer_class,
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_ops *dop),
  TP_ARGS(mp, dop),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp ? mp->m_super->s_dev : 0)
    ctf_integer(void *, dop, dop)
    ctf_integer(char, committed, dop->dop_committed)
    ctf_integer(char, low, dop->dop_low)
  )
)

#undef DEFINE_DEFER_EVENT
#define DEFINE_DEFER_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_defer_class, name, \
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_ops *dop), \
  TP_ARGS(mp, dop))

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_defer_error_class,
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_ops *dop, int error),
  TP_ARGS(mp, dop, error),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp ? mp->m_super->s_dev : 0)
    ctf_integer(void *, dop, dop)
    ctf_integer(char, committed, dop->dop_committed)
    ctf_integer(char, low, dop->dop_low)
    ctf_integer(int, error, error)
  )
)

#undef DEFINE_DEFER_ERROR_EVENT
#define DEFINE_DEFER_ERROR_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_defer_error_class, name, \
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_ops *dop, int error), \
  TP_ARGS(mp, dop, error))

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_defer_pending_class,
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_pending *dfp),
  TP_ARGS(mp, dfp),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp ? mp->m_super->s_dev : 0)
    ctf_integer(int, type, dfp->dfp_type->type)
    ctf_integer(void *, intent, dfp->dfp_intent)
    ctf_integer(char, committed, dfp->dfp_done != NULL)
    ctf_integer(int, nr, dfp->dfp_count)
  )
)

#undef DEFINE_DEFER_PENDING_EVENT
#define DEFINE_DEFER_PENDING_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_defer_pending_class, name, \
  TP_PROTO(struct xfs_mount *mp, struct xfs_defer_pending *dfp), \
  TP_ARGS(mp, dfp))

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_phys_extent_deferred_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     int type, xfs_agblock_t agbno, xfs_extlen_t len),
  TP_ARGS(mp, agno, type, agbno, len),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, type, type)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
  )
)

#undef DEFINE_PHYS_EXTENT_DEFERRED_EVENT
#define DEFINE_PHYS_EXTENT_DEFERRED_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_phys_extent_deferred_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     int type, \
     xfs_agblock_t bno, \
     xfs_extlen_t len), \
  TP_ARGS(mp, agno, type, bno, len))

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_map_extent_deferred_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     int op,
     xfs_agblock_t agbno,
     xfs_ino_t ino,
     int whichfork,
     xfs_fileoff_t offset,
     xfs_filblks_t len,
     xfs_exntst_t state),
  TP_ARGS(mp, agno, op, agbno, ino, whichfork, offset, len, state),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_ino_t, ino, ino)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(int, whichfork, whichfork)
    ctf_integer(xfs_fileoff_t, l_loff, offset)
    ctf_integer(xfs_filblks_t, l_len, len)
    ctf_integer(xfs_exntst_t, l_state, state)
    ctf_integer(int, op, op)
  )
)

#undef DEFINE_MAP_EXTENT_DEFERRED_EVENT
#define DEFINE_MAP_EXTENT_DEFERRED_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_map_extent_deferred_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     int op, \
     xfs_agblock_t agbno, \
     xfs_ino_t ino, \
     int whichfork, \
     xfs_fileoff_t offset, \
     xfs_filblks_t len, \
     xfs_exntst_t state), \
  TP_ARGS(mp, agno, op, agbno, ino, whichfork, offset, len, state))

DEFINE_DEFER_EVENT(xfs_defer_init)
DEFINE_DEFER_EVENT(xfs_defer_cancel)
DEFINE_DEFER_EVENT(xfs_defer_trans_roll)
DEFINE_DEFER_EVENT(xfs_defer_trans_abort)
DEFINE_DEFER_EVENT(xfs_defer_finish)
DEFINE_DEFER_EVENT(xfs_defer_finish_done)

DEFINE_DEFER_ERROR_EVENT(xfs_defer_trans_roll_error)
DEFINE_DEFER_ERROR_EVENT(xfs_defer_finish_error)

DEFINE_DEFER_PENDING_EVENT(xfs_defer_intake_work)
DEFINE_DEFER_PENDING_EVENT(xfs_defer_intake_cancel)
DEFINE_DEFER_PENDING_EVENT(xfs_defer_pending_cancel)
DEFINE_DEFER_PENDING_EVENT(xfs_defer_pending_finish)
DEFINE_DEFER_PENDING_EVENT(xfs_defer_pending_abort)

#undef DEFINE_BMAP_FREE_DEFERRED_EVENT
#define DEFINE_BMAP_FREE_DEFERRED_EVENT DEFINE_PHYS_EXTENT_DEFERRED_EVENT
DEFINE_BMAP_FREE_DEFERRED_EVENT(xfs_bmap_free_defer)
DEFINE_BMAP_FREE_DEFERRED_EVENT(xfs_bmap_free_deferred)

/* rmap tracepoints */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_rmap_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_extlen_t len, bool unwritten,
     struct xfs_owner_info *oinfo),
  TP_ARGS(mp, agno, agbno, len, unwritten, oinfo),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(uint64_t, owner, oinfo->oi_owner)
    ctf_integer(uint64_t, offset, oinfo->oi_offset)
    ctf_integer(unsigned long, flags, oinfo->oi_flags | (unwritten ? 0 : XFS_RMAP_UNWRITTEN))
  )
)

#undef DEFINE_RMAP_EVENT
#define DEFINE_RMAP_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_rmap_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     xfs_agblock_t agbno, xfs_extlen_t len, bool unwritten, \
     struct xfs_owner_info *oinfo), \
  TP_ARGS(mp, agno, agbno, len, unwritten, oinfo))

/* simple AG-based error/%ip tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_ag_error_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, int error,
     unsigned long caller_ip),
  TP_ARGS(mp, agno, error, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, error, error)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)


#undef DEFINE_AG_ERROR_EVENT
#define DEFINE_AG_ERROR_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_ag_error_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, int error, \
     unsigned long caller_ip), \
  TP_ARGS(mp, agno, error, caller_ip))

DEFINE_RMAP_EVENT(xfs_rmap_unmap)
DEFINE_RMAP_EVENT(xfs_rmap_unmap_done)
DEFINE_AG_ERROR_EVENT(xfs_rmap_unmap_error)
DEFINE_RMAP_EVENT(xfs_rmap_map)
DEFINE_RMAP_EVENT(xfs_rmap_map_done)
DEFINE_AG_ERROR_EVENT(xfs_rmap_map_error)
DEFINE_RMAP_EVENT(xfs_rmap_convert)
DEFINE_RMAP_EVENT(xfs_rmap_convert_done)
DEFINE_AG_ERROR_EVENT(xfs_rmap_convert_error)
DEFINE_AG_ERROR_EVENT(xfs_rmap_convert_state)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_rmapbt_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_extlen_t len,
     uint64_t owner, uint64_t offset, unsigned int flags),
  TP_ARGS(mp, agno, agbno, len, owner, offset, flags),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(uint64_t, owner, owner)
    ctf_integer(uint64_t, offset, offset)
    ctf_integer(unsigned int, flags, flags)
  )
)

#undef DEFINE_RMAPBT_EVENT
#define DEFINE_RMAPBT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_rmapbt_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     xfs_agblock_t agbno, xfs_extlen_t len, \
     uint64_t owner, uint64_t offset, unsigned int flags), \
  TP_ARGS(mp, agno, agbno, len, owner, offset, flags))


#undef DEFINE_RMAP_DEFERRED_EVENT
#define DEFINE_RMAP_DEFERRED_EVENT DEFINE_MAP_EXTENT_DEFERRED_EVENT
DEFINE_RMAP_DEFERRED_EVENT(xfs_rmap_defer)
DEFINE_RMAP_DEFERRED_EVENT(xfs_rmap_deferred)

DEFINE_BUSY_EVENT(xfs_rmapbt_alloc_block)
DEFINE_BUSY_EVENT(xfs_rmapbt_free_block)
DEFINE_RMAPBT_EVENT(xfs_rmap_update)
DEFINE_RMAPBT_EVENT(xfs_rmap_insert)
DEFINE_RMAPBT_EVENT(xfs_rmap_delete)
DEFINE_AG_ERROR_EVENT(xfs_rmap_insert_error)
DEFINE_AG_ERROR_EVENT(xfs_rmap_delete_error)
DEFINE_AG_ERROR_EVENT(xfs_rmap_update_error)

DEFINE_RMAPBT_EVENT(xfs_rmap_find_left_neighbor_candidate)
DEFINE_RMAPBT_EVENT(xfs_rmap_find_left_neighbor_query)
DEFINE_RMAPBT_EVENT(xfs_rmap_lookup_le_range_candidate)
DEFINE_RMAPBT_EVENT(xfs_rmap_lookup_le_range)
DEFINE_RMAPBT_EVENT(xfs_rmap_lookup_le_range_result)
DEFINE_RMAPBT_EVENT(xfs_rmap_find_right_neighbor_result)
DEFINE_RMAPBT_EVENT(xfs_rmap_find_left_neighbor_result)

/* deferred bmbt updates */
#undef DEFINE_BMAP_DEFERRED_EVENT
#define DEFINE_BMAP_DEFERRED_EVENT	DEFINE_RMAP_DEFERRED_EVENT
DEFINE_BMAP_DEFERRED_EVENT(xfs_bmap_defer)
DEFINE_BMAP_DEFERRED_EVENT(xfs_bmap_deferred)

/* per-AG reservation */
LTTNG_TRACEPOINT_EVENT_CLASS_CODE(xfs_ag_resv_class,
  TP_PROTO(struct xfs_perag *pag, enum xfs_ag_resv_type resv,
     xfs_extlen_t len),
  TP_ARGS(pag, resv, len),
  TP_locvar(
    struct xfs_ag_resv	*r;
  ),
  TP_code_pre(
    tp_locvar->r = xfs_perag_resv(pag, resv);
  ),
  TP_FIELDS(
    ctf_integer(dev_t, dev, pag->pag_mount->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, pag->pag_agno)
    ctf_integer(int, resv, resv)
    ctf_integer(xfs_extlen_t, freeblks, pag->pagf_freeblks)
    ctf_integer(xfs_extlen_t, flcount, pag->pagf_flcount)
    ctf_integer(xfs_extlen_t, reserved, tp_locvar->r ? tp_locvar->r->ar_reserved : 0)
    ctf_integer(xfs_extlen_t, asked, tp_locvar->r ? tp_locvar->r->ar_asked : 0)
    ctf_integer(xfs_extlen_t, len, len)
  ),
  TP_code_post()
)

#undef DEFINE_AG_RESV_EVENT
#define DEFINE_AG_RESV_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_ag_resv_class, name, \
  TP_PROTO(struct xfs_perag *pag, enum xfs_ag_resv_type type, \
     xfs_extlen_t len), \
  TP_ARGS(pag, type, len))

/* per-AG reservation tracepoints */
DEFINE_AG_RESV_EVENT(xfs_ag_resv_init)
DEFINE_AG_RESV_EVENT(xfs_ag_resv_free)
DEFINE_AG_RESV_EVENT(xfs_ag_resv_alloc_extent)
DEFINE_AG_RESV_EVENT(xfs_ag_resv_free_extent)
DEFINE_AG_RESV_EVENT(xfs_ag_resv_critical)
DEFINE_AG_RESV_EVENT(xfs_ag_resv_needed)

DEFINE_AG_ERROR_EVENT(xfs_ag_resv_free_error)
DEFINE_AG_ERROR_EVENT(xfs_ag_resv_init_error)

/* refcount tracepoint classes */

/* reuse the discard trace class for agbno/aglen-based traces */
#undef DEFINE_AG_EXTENT_EVENT
#define DEFINE_AG_EXTENT_EVENT(name) DEFINE_DISCARD_EVENT(name)

/* ag btree lookup tracepoint class */
#undef XFS_AG_BTREE_CMP_FORMAT_STR
#define XFS_AG_BTREE_CMP_FORMAT_STR \
  { XFS_LOOKUP_EQ,	"eq" }, \
  { XFS_LOOKUP_LE,	"le" }, \
  { XFS_LOOKUP_GE,	"ge" }
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_ag_btree_lookup_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     xfs_agblock_t agbno, xfs_lookup_t dir),
  TP_ARGS(mp, agno, agbno, dir),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_lookup_t, dir, dir)
  )
)

#undef DEFINE_AG_BTREE_LOOKUP_EVENT
#define DEFINE_AG_BTREE_LOOKUP_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_ag_btree_lookup_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     xfs_agblock_t agbno, xfs_lookup_t dir), \
  TP_ARGS(mp, agno, agbno, dir))

/* single-rcext tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_refcount_extent_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     struct xfs_refcount_irec *irec),
  TP_ARGS(mp, agno, irec),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, startblock, irec->rc_startblock)
    ctf_integer(xfs_extlen_t, blockcount, irec->rc_blockcount)
    ctf_integer(xfs_nlink_t, refcount, irec->rc_refcount)
  )
)

#undef DEFINE_REFCOUNT_EXTENT_EVENT
#define DEFINE_REFCOUNT_EXTENT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_refcount_extent_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     struct xfs_refcount_irec *irec), \
  TP_ARGS(mp, agno, irec))

/* single-rcext and an agbno tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_refcount_extent_at_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     struct xfs_refcount_irec *irec, xfs_agblock_t agbno),
  TP_ARGS(mp, agno, irec, agbno),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, startblock, irec->rc_startblock)
    ctf_integer(xfs_extlen_t, blockcount, irec->rc_blockcount)
    ctf_integer(xfs_nlink_t, refcount, irec->rc_refcount)
    ctf_integer(xfs_agblock_t, agbno, agbno)
  )
)

#undef DEFINE_REFCOUNT_EXTENT_AT_EVENT
#define DEFINE_REFCOUNT_EXTENT_AT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_refcount_extent_at_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     struct xfs_refcount_irec *irec, xfs_agblock_t agbno), \
  TP_ARGS(mp, agno, irec, agbno))

/* double-rcext tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_refcount_double_extent_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2),
  TP_ARGS(mp, agno, i1, i2),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, i1_startblock, i1->rc_startblock)
    ctf_integer(xfs_extlen_t, i1_blockcount, i1->rc_blockcount)
    ctf_integer(xfs_nlink_t, i1_refcount, i1->rc_refcount)
    ctf_integer(xfs_agblock_t, i2_startblock, i2->rc_startblock)
    ctf_integer(xfs_extlen_t, i2_blockcount, i2->rc_blockcount)
    ctf_integer(xfs_nlink_t, i2_refcount, i2->rc_refcount)
  )
)

#undef DEFINE_REFCOUNT_DOUBLE_EXTENT_EVENT
#define DEFINE_REFCOUNT_DOUBLE_EXTENT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_refcount_double_extent_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2), \
  TP_ARGS(mp, agno, i1, i2))

/* double-rcext and an agbno tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_refcount_double_extent_at_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2,
     xfs_agblock_t agbno),
  TP_ARGS(mp, agno, i1, i2, agbno),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, i1_startblock, i1->rc_startblock)
    ctf_integer(xfs_extlen_t, i1_blockcount, i1->rc_blockcount)
    ctf_integer(xfs_nlink_t, i1_refcount, i1->rc_refcount)
    ctf_integer(xfs_agblock_t, i2_startblock, i2->rc_startblock)
    ctf_integer(xfs_extlen_t, i2_blockcount, i2->rc_blockcount)
    ctf_integer(xfs_nlink_t, i2_refcount, i2->rc_refcount)
    ctf_integer(xfs_agblock_t, agbno, agbno)
  )
)

#undef DEFINE_REFCOUNT_DOUBLE_EXTENT_AT_EVENT
#define DEFINE_REFCOUNT_DOUBLE_EXTENT_AT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_refcount_double_extent_at_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2, \
     xfs_agblock_t agbno), \
  TP_ARGS(mp, agno, i1, i2, agbno))

/* triple-rcext tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_refcount_triple_extent_class,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2,
     struct xfs_refcount_irec *i3),
  TP_ARGS(mp, agno, i1, i2, i3),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_agblock_t, i1_startblock, i1->rc_startblock)
    ctf_integer(xfs_extlen_t, i1_blockcount, i1->rc_blockcount)
    ctf_integer(xfs_nlink_t, i1_refcount, i1->rc_refcount)
    ctf_integer(xfs_agblock_t, i2_startblock, i2->rc_startblock)
    ctf_integer(xfs_extlen_t, i2_blockcount, i2->rc_blockcount)
    ctf_integer(xfs_nlink_t, i2_refcount, i2->rc_refcount)
    ctf_integer(xfs_agblock_t, i3_startblock, i3->rc_startblock)
    ctf_integer(xfs_extlen_t, i3_blockcount, i3->rc_blockcount)
    ctf_integer(xfs_nlink_t, i3_refcount, i3->rc_refcount)
  )
)

#undef DEFINE_REFCOUNT_TRIPLE_EXTENT_EVENT
#define DEFINE_REFCOUNT_TRIPLE_EXTENT_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_refcount_triple_extent_class, name, \
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno, \
     struct xfs_refcount_irec *i1, struct xfs_refcount_irec *i2, \
     struct xfs_refcount_irec *i3), \
  TP_ARGS(mp, agno, i1, i2, i3))

/* refcount btree tracepoints */
DEFINE_BUSY_EVENT(xfs_refcountbt_alloc_block)
DEFINE_BUSY_EVENT(xfs_refcountbt_free_block)
DEFINE_AG_BTREE_LOOKUP_EVENT(xfs_refcount_lookup)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_get)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_update)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_insert)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_delete)
DEFINE_AG_ERROR_EVENT(xfs_refcount_insert_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_delete_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_update_error)

/* refcount adjustment tracepoints */
DEFINE_AG_EXTENT_EVENT(xfs_refcount_increase)
DEFINE_AG_EXTENT_EVENT(xfs_refcount_decrease)
DEFINE_AG_EXTENT_EVENT(xfs_refcount_cow_increase)
DEFINE_AG_EXTENT_EVENT(xfs_refcount_cow_decrease)
DEFINE_REFCOUNT_TRIPLE_EXTENT_EVENT(xfs_refcount_merge_center_extents)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_modify_extent)
DEFINE_REFCOUNT_EXTENT_EVENT(xfs_refcount_recover_extent)
DEFINE_REFCOUNT_EXTENT_AT_EVENT(xfs_refcount_split_extent)
DEFINE_REFCOUNT_DOUBLE_EXTENT_EVENT(xfs_refcount_merge_left_extent)
DEFINE_REFCOUNT_DOUBLE_EXTENT_EVENT(xfs_refcount_merge_right_extent)
DEFINE_REFCOUNT_DOUBLE_EXTENT_AT_EVENT(xfs_refcount_find_left_extent)
DEFINE_REFCOUNT_DOUBLE_EXTENT_AT_EVENT(xfs_refcount_find_right_extent)
DEFINE_AG_ERROR_EVENT(xfs_refcount_adjust_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_adjust_cow_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_merge_center_extents_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_modify_extent_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_split_extent_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_merge_left_extent_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_merge_right_extent_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_find_left_extent_error)
DEFINE_AG_ERROR_EVENT(xfs_refcount_find_right_extent_error)

/* reflink helpers */
DEFINE_AG_EXTENT_EVENT(xfs_refcount_find_shared)
DEFINE_AG_EXTENT_EVENT(xfs_refcount_find_shared_result)
DEFINE_AG_ERROR_EVENT(xfs_refcount_find_shared_error)
#undef DEFINE_REFCOUNT_DEFERRED_EVENT
#define DEFINE_REFCOUNT_DEFERRED_EVENT DEFINE_PHYS_EXTENT_DEFERRED_EVENT
DEFINE_REFCOUNT_DEFERRED_EVENT(xfs_refcount_defer)
DEFINE_REFCOUNT_DEFERRED_EVENT(xfs_refcount_deferred)

LTTNG_TRACEPOINT_EVENT(xfs_refcount_finish_one_leftover,
  TP_PROTO(struct xfs_mount *mp, xfs_agnumber_t agno,
     int type, xfs_agblock_t agbno, xfs_extlen_t len,
     xfs_agblock_t new_agbno, xfs_extlen_t new_len),
  TP_ARGS(mp, agno, type, agbno, len, new_agbno, new_len),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(int, type, type)
    ctf_integer(xfs_agblock_t, agbno, agbno)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(xfs_agblock_t, new_agbno, new_agbno)
    ctf_integer(xfs_extlen_t, new_len, new_len)
  )
)

/* simple inode-based error/%ip tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_inode_error_class,
  TP_PROTO(struct xfs_inode *ip, int error, unsigned long caller_ip),
  TP_ARGS(ip, error, caller_ip),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(int, error, error)
    ctf_integer(unsigned long, caller_ip, caller_ip)
  )
)

#undef DEFINE_INODE_ERROR_EVENT
#define DEFINE_INODE_ERROR_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_inode_error_class, name, \
  TP_PROTO(struct xfs_inode *ip, int error, \
     unsigned long caller_ip), \
  TP_ARGS(ip, error, caller_ip))

/* reflink tracepoint classes */

/* two-file io tracepoint class */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_double_io_class,
  TP_PROTO(struct xfs_inode *src, xfs_off_t soffset, xfs_off_t len,
     struct xfs_inode *dest, xfs_off_t doffset),
  TP_ARGS(src, soffset, len, dest, doffset),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(src)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, src_ino, src->i_ino)
    ctf_integer(loff_t, src_isize, VFS_I(src)->i_size)
    ctf_integer(loff_t, src_disize, src->i_d.di_size)
    ctf_integer(loff_t, src_offset, soffset)
    ctf_integer(size_t, len, len)
    ctf_integer(xfs_ino_t, dest_ino, dest->i_ino)
    ctf_integer(loff_t, dest_isize, VFS_I(dest)->i_size)
    ctf_integer(loff_t, dest_disize, dest->i_d.di_size)
    ctf_integer(loff_t, dest_offset, doffset)
  )
)

#undef DEFINE_DOUBLE_IO_EVENT
#define DEFINE_DOUBLE_IO_EVENT(name)	\
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_double_io_class, name,	\
  TP_PROTO(struct xfs_inode *src, xfs_off_t soffset, xfs_off_t len, \
     struct xfs_inode *dest, xfs_off_t doffset), \
  TP_ARGS(src, soffset, len, dest, doffset))

/* inode/irec events */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_inode_irec_class,
  TP_PROTO(struct xfs_inode *ip, struct xfs_bmbt_irec *irec),
  TP_ARGS(ip, irec),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fileoff_t, lblk, irec->br_startoff)
    ctf_integer(xfs_extlen_t, len, irec->br_blockcount)
    ctf_integer(xfs_fsblock_t, pblk, irec->br_startblock)
    ctf_integer(int, state, irec->br_state)
  )
)

#undef DEFINE_INODE_IREC_EVENT
#define DEFINE_INODE_IREC_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_inode_irec_class, name, \
  TP_PROTO(struct xfs_inode *ip, struct xfs_bmbt_irec *irec), \
  TP_ARGS(ip, irec))

/* refcount/reflink tracepoint definitions */

/* reflink tracepoints */
DEFINE_INODE_EVENT(xfs_reflink_set_inode_flag)
DEFINE_INODE_EVENT(xfs_reflink_unset_inode_flag)
DEFINE_ITRUNC_EVENT(xfs_reflink_update_inode_size)
DEFINE_IOMAP_EVENT(xfs_reflink_remap_imap)
LTTNG_TRACEPOINT_EVENT(xfs_reflink_remap_blocks_loop,
  TP_PROTO(struct xfs_inode *src, xfs_fileoff_t soffset,
     xfs_filblks_t len, struct xfs_inode *dest,
     xfs_fileoff_t doffset),
  TP_ARGS(src, soffset, len, dest, doffset),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(src)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, src_ino, src->i_ino)
    ctf_integer(xfs_fileoff_t, src_lblk, soffset)
    ctf_integer(xfs_filblks_t, len, len)
    ctf_integer(xfs_ino_t, dest_ino, dest->i_ino)
    ctf_integer(xfs_fileoff_t, dest_lblk, doffset)
  )
)
LTTNG_TRACEPOINT_EVENT(xfs_reflink_punch_range,
  TP_PROTO(struct xfs_inode *ip, xfs_fileoff_t lblk,
     xfs_extlen_t len),
  TP_ARGS(ip, lblk, len),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fileoff_t, lblk, lblk)
    ctf_integer(xfs_extlen_t, len, len)
  )
)
LTTNG_TRACEPOINT_EVENT(xfs_reflink_remap,
  TP_PROTO(struct xfs_inode *ip, xfs_fileoff_t lblk,
     xfs_extlen_t len, xfs_fsblock_t new_pblk),
  TP_ARGS(ip, lblk, len, new_pblk),
  TP_FIELDS(
    ctf_integer(dev_t, dev, VFS_I(ip)->i_sb->s_dev)
    ctf_integer(xfs_ino_t, ino, ip->i_ino)
    ctf_integer(xfs_fileoff_t, lblk, lblk)
    ctf_integer(xfs_extlen_t, len, len)
    ctf_integer(xfs_fsblock_t, new_pblk, new_pblk)
  )
)
DEFINE_DOUBLE_IO_EVENT(xfs_reflink_remap_range)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_remap_range_error)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_set_inode_flag_error)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_update_inode_size_error)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_remap_blocks_error)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_remap_extent_error)

/* dedupe tracepoints */
DEFINE_DOUBLE_IO_EVENT(xfs_reflink_compare_extents)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_compare_extents_error)

/* ioctl tracepoints */
LTTNG_TRACEPOINT_EVENT(xfs_ioctl_clone,
  TP_PROTO(struct inode *src, struct inode *dest),
  TP_ARGS(src, dest),
  TP_FIELDS(
    ctf_integer(dev_t, dev, src->i_sb->s_dev)
    ctf_integer(unsigned long, src_ino, src->i_ino)
    ctf_integer(loff_t, src_isize, i_size_read(src))
    ctf_integer(unsigned long, dest_ino, dest->i_ino)
    ctf_integer(loff_t, dest_isize, i_size_read(dest))
  )
)

/* unshare tracepoints */
DEFINE_SIMPLE_IO_EVENT(xfs_reflink_unshare)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_unshare_error)

/* copy on write */
DEFINE_INODE_IREC_EVENT(xfs_reflink_trim_around_shared)
DEFINE_INODE_IREC_EVENT(xfs_reflink_cow_alloc)
DEFINE_INODE_IREC_EVENT(xfs_reflink_cow_found)
DEFINE_INODE_IREC_EVENT(xfs_reflink_cow_enospc)
DEFINE_INODE_IREC_EVENT(xfs_reflink_convert_cow)

DEFINE_RW_EVENT(xfs_reflink_reserve_cow)

DEFINE_SIMPLE_IO_EVENT(xfs_reflink_bounce_dio_write)
DEFINE_IOMAP_EVENT(xfs_reflink_find_cow_mapping)
DEFINE_INODE_IREC_EVENT(xfs_reflink_trim_irec)

DEFINE_SIMPLE_IO_EVENT(xfs_reflink_cancel_cow_range)
DEFINE_SIMPLE_IO_EVENT(xfs_reflink_end_cow)
DEFINE_INODE_IREC_EVENT(xfs_reflink_cow_remap)

DEFINE_INODE_ERROR_EVENT(xfs_reflink_cancel_cow_range_error)
DEFINE_INODE_ERROR_EVENT(xfs_reflink_end_cow_error)


DEFINE_INODE_IREC_EVENT(xfs_reflink_cancel_cow)

/* rmap swapext tracepoints */
DEFINE_INODE_IREC_EVENT(xfs_swap_extent_rmap_remap)
DEFINE_INODE_IREC_EVENT(xfs_swap_extent_rmap_remap_piece)
DEFINE_INODE_ERROR_EVENT(xfs_swap_extent_rmap_error)

/* fsmap traces */
LTTNG_TRACEPOINT_EVENT_CLASS(xfs_fsmap_class,
  TP_PROTO(struct xfs_mount *mp, u32 keydev, xfs_agnumber_t agno,
     struct xfs_rmap_irec *rmap),
  TP_ARGS(mp, keydev, agno, rmap),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(dev_t, keydev, new_decode_dev(keydev))
    ctf_integer(xfs_agnumber_t, agno, agno)
    ctf_integer(xfs_fsblock_t, bno, rmap->rm_startblock)
    ctf_integer(xfs_filblks_t, len, rmap->rm_blockcount)
    ctf_integer(uint64_t, owner, rmap->rm_owner)
    ctf_integer(uint64_t, offset, rmap->rm_offset)
    ctf_integer(unsigned int, flags, rmap->rm_flags)
  )
)

#undef DEFINE_FSMAP_EVENT
#define DEFINE_FSMAP_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_fsmap_class, name, \
  TP_PROTO(struct xfs_mount *mp, u32 keydev, xfs_agnumber_t agno, \
     struct xfs_rmap_irec *rmap), \
  TP_ARGS(mp, keydev, agno, rmap))
DEFINE_FSMAP_EVENT(xfs_fsmap_low_key)
DEFINE_FSMAP_EVENT(xfs_fsmap_high_key)
DEFINE_FSMAP_EVENT(xfs_fsmap_mapping)

LTTNG_TRACEPOINT_EVENT_CLASS(xfs_getfsmap_class,
  TP_PROTO(struct xfs_mount *mp, struct xfs_fsmap *fsmap),
  TP_ARGS(mp, fsmap),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(dev_t, keydev, new_decode_dev(fsmap->fmr_device))
    ctf_integer(xfs_daddr_t, block, fsmap->fmr_physical)
    ctf_integer(xfs_daddr_t, len, fsmap->fmr_length)
    ctf_integer(uint64_t, owner, fsmap->fmr_owner)
    ctf_integer(uint64_t, offset, fsmap->fmr_offset)
    ctf_integer(uint64_t, flags, fsmap->fmr_flags)
  )
)

#undef DEFINE_GETFSMAP_EVENT
#define DEFINE_GETFSMAP_EVENT(name) \
LTTNG_TRACEPOINT_EVENT_INSTANCE(xfs_getfsmap_class, name, \
  TP_PROTO(struct xfs_mount *mp, struct xfs_fsmap *fsmap), \
  TP_ARGS(mp, fsmap))
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_low_key)
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_high_key)
DEFINE_GETFSMAP_EVENT(xfs_getfsmap_mapping)

LTTNG_TRACEPOINT_EVENT(xfs_trans_resv_calc,
  TP_PROTO(struct xfs_mount *mp, unsigned int type,
     struct xfs_trans_res *res),
  TP_ARGS(mp, type, res),
  TP_FIELDS(
    ctf_integer(dev_t, dev, mp->m_super->s_dev)
    ctf_integer(int, type, type)
    ctf_integer(uint, logres, res->tr_logres)
    ctf_integer(int, logcount, res->tr_logcount)
    ctf_integer(int, logflags, res->tr_logflags)
  )
)

#endif /* LTTNG_TRACE_XFS_H */

/* This part must be outside protection */
#include <probes/define_trace.h>
