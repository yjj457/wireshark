/* packet-dcerpc-nt.h
 * Routines for DCERPC over SMB packet disassembly
 * Copyright 2001-2003 Tim Potter <tpot@samba.org>
 *
 * $Id: packet-dcerpc-nt.h,v 1.36 2003/01/28 06:27:01 tpot Exp $
 *
 * Ethereal - Network traffic analyzer
 * By Gerald Combs <gerald@ethereal.com>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __PACKET_DCERPC_NT_H
#define __PACKET_DCEPRC_NT_H

/*
 * ett_ value for Unicode strings.
 */
extern gint ett_nt_unicode_string;

/* Parse some common RPC structures */

char *fake_unicode(tvbuff_t *tvb, int offset, int len);

/* Routines for handling deferral of referants in NDR */

#define ALIGN_TO_4_BYTES \
	{ dcerpc_info *xzdi; \
	  xzdi=pinfo->private_data; \
	  if(!xzdi->conformant_run) { \
		if(offset&0x03) { \
			offset=(offset&0xfffffffc)+4; \
		} \
	  } \
	}

int
dissect_ndr_nt_UNICODE_STRING_str(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *tree,
			char *drep);
int
dissect_ndr_nt_UNICODE_STRING_cb(tvbuff_t *tvb, int offset,
				 packet_info *pinfo, proto_tree *parent_tree,
				 char *drep, int hf_index, 
				 dcerpc_callback_fnct_t *callback,
				 void *callback_args);

int
dissect_ndr_nt_UNICODE_STRING(tvbuff_t *tvb, int offset,
			      packet_info *pinfo, proto_tree *parent_tree,
			      char *drep, int hf_index);

int
dissect_ndr_nt_STRING_string(tvbuff_t *tvb, int offset,
                             packet_info *pinfo, proto_tree *tree,
                             char *drep);
int
dissect_ndr_nt_STRING_cb(tvbuff_t *tvb, int offset,
			 packet_info *pinfo, proto_tree *parent_tree,
			 char *drep, int hf_index, 
			 dcerpc_callback_fnct_t *callback, 
			 void *callback_args);

int
dissect_ndr_nt_STRING(tvbuff_t *tvb, int offset,
		      packet_info *pinfo, proto_tree *parent_tree,
		      char *drep, int hf_index);

int
dissect_ndr_nt_acct_ctrl(tvbuff_t *tvb, int offset, packet_info *pinfo,
			proto_tree *parent_tree, char *drep);
int
dissect_ndr_nt_NTTIME (tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *tree,
			char *drep, int hf_index);
int
dissect_ndr_nt_LOGON_HOURS(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *parent_tree,
			char *drep);
int
dissect_ndr_nt_SID(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *tree,
			char *drep);
int
dissect_ndr_nt_PSID(tvbuff_t *tvb, int offset,
                             packet_info *pinfo, proto_tree *parent_tree,
                             char *drep);
int
dissect_ndr_nt_PSID_ARRAY(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *parent_tree,
			char *drep);

int
dissect_ndr_nt_SID_AND_ATTRIBUTES_ARRAY(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *parent_tree,
			char *drep);
int
dissect_ndr_nt_SID_AND_ATTRIBUTES(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *parent_tree,
			char *drep);

/*
 * Policy handle hashing
 */

/* Store open and close packet numbers for a policy handle */

void
dcerpc_smb_store_pol_pkts(e_ctx_hnd *policy_hnd, guint32 open_frame,
			  guint32 close_frame);

/* Store a name with a policy handle */

void
dcerpc_smb_store_pol_name(e_ctx_hnd *policy_hnd, char *name);

/* Fetch details stored with a policy handle */

gboolean
dcerpc_smb_fetch_pol(e_ctx_hnd *policy_hnd, char **name,
		     guint32 *open_frame, guint32 *close_frame);

/* Check for unparsed data at the end of a frame */

void
dcerpc_smb_check_long_frame(tvbuff_t *tvb, int offset,
			    packet_info *pinfo, proto_tree *tree);

/* Dissect NT specific things */

int
dissect_ntstatus(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		 proto_tree *tree, char *drep,
		 int hfindex, guint32 *pdata);

int
dissect_doserror(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		 proto_tree *tree, char *drep,
		 int hfindex, guint32 *pdata);

int
dissect_nt_policy_hnd(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		      proto_tree *tree, char *drep, int hfindex,
		      e_ctx_hnd *pdata, gboolean is_open, gboolean is_close);

int
dissect_nt_GUID(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *parent_tree,
			char *drep);

int
dissect_nt_LUID(tvbuff_t *tvb, int offset,
			packet_info *pinfo, proto_tree *tree,
			char *drep);

/* Stored here instead of packet-dcerpc{,-ndr}.c as they are probably not
   official NDR representations. */

int dissect_dcerpc_uint8s(tvbuff_t *tvb, gint offset, packet_info *pinfo,
                          proto_tree *tree, char *drep,
                          int hfindex, int length, const guint8 **pdata);

int dissect_ndr_uint8s(tvbuff_t *tvb, gint offset, packet_info *pinfo,
                       proto_tree *tree, char *drep,
                       int hfindex, int length, const guint8 **pdata);

int dissect_dcerpc_uint16s(tvbuff_t *tvb, gint offset, packet_info *pinfo,
			   proto_tree *tree, char *drep,
			   int hfindex, int length);

int dissect_ndr_uint16s(tvbuff_t *tvb, gint offset, packet_info *pinfo,
			proto_tree *tree, char *drep,
			int hfindex, int length);

/* Dissect an NT access mask */

typedef void (nt_access_mask_fn_t)(tvbuff_t *tvb, gint offset,
				   proto_tree *tree, guint32 access);

int
dissect_nt_access_mask(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		       proto_tree *tree, char *drep, int hfindex,
		       nt_access_mask_fn_t *specific_rights_fn);

int dissect_ndr_str_pointer_item(tvbuff_t *tvb, gint offset, 
				 packet_info *pinfo, proto_tree *tree, 
				 char *drep, int type, char *text, 
				 int hf_index);

/*
 * Helper routines for dissecting NDR strings
 */

#define CB_STR_COL_INFO 1	/* Append string to COL_INFO */
#define CB_STR_ITEM     2	/* Append string to pointer item */
#define CB_STR_SAVE     4	/* Save string to dcv->private_data */

void cb_str_postprocess(packet_info *pinfo, proto_tree *tree _U_,
			proto_item *item, tvbuff_t *tvb, 
			int start_offset, int end_offset,
			void *callback_args);

/* Initialise DCERPC over SMB */

void dcerpc_smb_init(int proto_dcerpc);

#endif /* packet-dcerpc-nt.h */
