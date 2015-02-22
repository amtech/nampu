#include <pthread.h>
#include <unistd.h>
#include "nmp_mod_tw.h"
#include "nmp_debug.h"
#include "nmp_errno.h"
#include "nmp_ports.h"
#include "nmp_proto.h"
#include "nmp_message.h"
#include "nmp_msg_share.h"
#include "nmp_msg_struct.h"
#include "nmp_shared.h"
#include "nmp_memory.h"
#include "nmp_internal_msg.h"
#include "nmp_msg_tw.h"


pthread_t tw_tid;
#define TW_WORK_TIME	(200)	//200 ms
static JpfModTw *g_jpf_mod_tw;
//static guint msg_seq_generator = 0;


G_DEFINE_TYPE(JpfModTw, jpf_mod_tw, JPF_TYPE_APPMOD);

void
jpf_mod_tw_register_msg_handler(JpfModTw *self);


JpfModTw *jpf_get_mod_tw()
{
	return g_jpf_mod_tw;
}


void *jpf_mod_tw_work(void *arg)
{
	while (1)
	{
		jpf_tw_tvwall_work();
		usleep(TW_WORK_TIME * 1000);
	}
//	jpf_tw_tvwall_clear();
//	pthread_detach(pthread_self());
	return ((void *)1);
}


gint
jpf_mod_tw_setup(JpfAppMod *am_self)
{
	JpfModTw *self;
	G_ASSERT(am_self != NULL);

	self = (JpfModTw*)am_self;

	jpf_app_mod_set_name(am_self, "MOD-TW");
	jpf_mod_tw_register_msg_handler(self);
	return 0;
}


static void
jpf_mod_tw_init(JpfModTw *self)
{
	jpf_mod_tw_func_begin("\n");
	int ret;

	g_jpf_mod_tw = self;
	jpf_tw_set_event_handler(jpf_mod_tw_event_handler);
	ret = pthread_create(&tw_tid, NULL, jpf_mod_tw_work, NULL);
	if (ret != 0)
		jpf_warning("pthread_create failed\n");
}


static void
jpf_mod_tw_class_init(JpfModTwClass *k_class)
{
	JpfAppModClass *am_class = (JpfAppModClass*)k_class;

	am_class->setup_mod	= jpf_mod_tw_setup;
}


static gint jpf_mod_tw_get_tour(tw_tour_msg_request *in_parm,
	tw_tour_msg_response *out_parm)
{
	jpf_mod_tw_func_begin("\n");

	gint err = -1;
	JpfSysMsg *msg;
	tw_tour_msg_response *res_info;
	G_ASSERT(out_parm);

	msg = jpf_sysmsg_new_2(MSG_TW_INFO_GET_TOUR, in_parm,
		sizeof(tw_tour_msg_request), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	err = jpf_app_mod_sync_request((JpfAppMod*)jpf_get_mod_tw(), &msg);
	if (G_UNLIKELY(err))	/* send failed */
	{
		jpf_warning(
			"<JpfModTw> request tw tour info failed!"
		);
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		jpf_warning(
			"<JpfModTw> request tw tour info timeout!"
		);
		return -E_TIMEOUT;
	}

	res_info = MSG_GET_DATA(msg);
	BUG_ON(!res_info);
	if (res_info->result < 0 || res_info->step_count <= 0 || res_info->steps == NULL)	//Ѳ�ز���Ϊ0����Ϊʧ��
	{
		err = -2;
		goto end;
	}

	memcpy(out_parm, res_info, sizeof(tw_tour_msg_response));
	out_parm->steps =
		(tw_tour_step_response *)jpf_mem_kalloc(sizeof(tw_tour_step_response) *
		out_parm->step_count);
	memcpy(out_parm->steps, res_info->steps, sizeof(tw_tour_step_response) *
		out_parm->step_count);

end:
	jpf_sysmsg_destroy(msg);
	return err;
}


static gint jpf_mod_tw_get_group(tw_group_msg_request *in_parm,
    tw_group_msg_response *out_parm)
{
	jpf_mod_tw_func_begin("\n");

	gint err = -1;
	JpfSysMsg *msg;
	tw_group_msg_response *res_info;
	G_ASSERT(out_parm);

	msg = jpf_sysmsg_new_2(MSG_TW_INFO_GET_GROUP, in_parm,
		sizeof(tw_group_msg_request), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	err = jpf_app_mod_sync_request((JpfAppMod*)jpf_get_mod_tw(), &msg);
	if (G_UNLIKELY(err))	/* send failed */
	{
		jpf_warning(
			"<JpfModTw> request tw group info failed!"
		);
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		jpf_warning(
			"<JpfModTw> request tw group info timeout!"
		);
		return -E_TIMEOUT;
	}

	res_info = MSG_GET_DATA(msg);
	BUG_ON(!res_info);
	if (res_info->result < 0 || res_info->step_count <= 0)	//Ⱥ�鲽��Ϊ0����Ϊʧ��
	{
		err = -2;
		goto end;
	}
	memcpy(out_parm, res_info, sizeof(tw_group_msg_response));

end:
	jpf_sysmsg_destroy(msg);
	return err;
}


static gint jpf_mod_tw_get_group_step_n(tw_group_step_n_request *in_parm,
	tw_group_step_n_response *out_parm)
{
	jpf_mod_tw_func_begin("\n");

	gint err = -1;
	JpfSysMsg *msg;
	tw_group_step_n_response *res_info;
	G_ASSERT(out_parm);

	msg = jpf_sysmsg_new_2(MSG_TW_INFO_GET_GROUP_STEP_N, in_parm,
		sizeof(tw_group_step_n_request), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	err = jpf_app_mod_sync_request((JpfAppMod*)jpf_get_mod_tw(), &msg);
	if (G_UNLIKELY(err))	/* send failed */
	{
		jpf_warning(
			"<JpfModTw> request tw group step info failed!"
		);
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		jpf_warning(
			"<JpfModTw> request tw group step info timeout!"
		);
		return -E_TIMEOUT;
	}

	res_info = MSG_GET_DATA(msg);
	BUG_ON(!res_info);
	if (res_info->result < 0 || res_info->screen_sum < 0)	//Ⱥ��ĳһ������Ϊ0����Ϊ�ɹ�
	{
		err = -2;
		goto end;
	}

	memcpy(out_parm, res_info, sizeof(tw_group_step_n_response));
	out_parm->screens =
		(tw_group_screen_response *)jpf_mem_kalloc(sizeof(tw_group_screen_response) *
		out_parm->screen_sum);
	if (res_info->screen_sum != 0)
		memcpy(out_parm->screens, res_info->screens,
		sizeof(tw_group_screen_response) * out_parm->screen_sum);

end:
	jpf_sysmsg_destroy(msg);
	return err;
}


static gint jpf_mod_tw_get_dis_guid(tw_dis_guid_request *in_parm,
	tw_dis_guid_response *out_parm)
{
	jpf_mod_tw_func_begin("\n");

	gint err = -1;
	JpfSysMsg *msg;
	tw_dis_guid_response *res_info;
	G_ASSERT(out_parm);

	msg = jpf_sysmsg_new_2(MSG_TW_INFO_GET_DIS_GUID, in_parm,
		sizeof(tw_dis_guid_request), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	err = jpf_app_mod_sync_request((JpfAppMod*)jpf_get_mod_tw(), &msg);
	if (G_UNLIKELY(err))	/* send failed */
	{
		jpf_warning(
			"<JpfModTw> request display guid failed!"
		);
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		jpf_warning(
			"<JpfModTw> request display guid timeout!"
		);
		return -E_TIMEOUT;
	}

	res_info = MSG_GET_DATA(msg);
	BUG_ON(!res_info);
	if (res_info->result < 0)
	{
		err = res_info->result;
		goto end;
	}

	memcpy(out_parm, res_info, sizeof(tw_dis_guid_response));

end:
	jpf_sysmsg_destroy(msg);
	return err;
}


static gint jpf_mod_tw_get_ec_url(tw_ec_url_request *in_parm,
	tw_ec_url_response *out_parm)
{
	jpf_mod_tw_func_begin("\n");

	gint err = -1;
	JpfSysMsg *msg;
	tw_ec_url_response *res_info;
	G_ASSERT(out_parm);

	msg = jpf_sysmsg_new_2(MSG_TW_INFO_GET_EC_URL, in_parm,
		sizeof(tw_ec_url_request), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	err = jpf_app_mod_sync_request((JpfAppMod*)jpf_get_mod_tw(), &msg);
	if (G_UNLIKELY(err))	/* send failed */
	{
		jpf_warning(
			"<JpfModTw> request encoder URL failed!"
		);
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		jpf_warning(
			"<JpfModTw> request encoder URL timeout!"
		);
		return -E_TIMEOUT;
	}

	res_info = MSG_GET_DATA(msg);
	BUG_ON(!res_info);
	if (res_info->result < 0)
	{
		err = res_info->result;
		goto end;
	}
	jpf_mod_tw_log("************ get ec_url:%s ***********\n", res_info->ec_url);

	memcpy(out_parm, res_info, sizeof(tw_ec_url_response));

end:
	jpf_sysmsg_destroy(msg);
	return err;
}


static gint jpf_mod_tw_query_if_update_ec_url(tw_update_url *in_parm)
{
	JpfSysMsg *msg;
	JpfModTw *self;

	self = jpf_get_mod_tw();
	msg = jpf_sysmsg_new_2(MSG_TW_INFO_CHECK_EC_URL_UPDATE, in_parm,
		sizeof(tw_update_url), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
	{
		jpf_warning("jpf_sysmsg_new_2 failed, no memory\n");
		return -1;
	}

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


/*
 *	ע��:in_parm��ָ���ڴ��ɱ���������
 */
static gint jpf_mod_tw_send_screen_to_dec(tw_screen_to_decoder_with_seq *in_parm)
{
	jpf_mod_tw_func_begin("\n");

	JpfSysMsg *msg;
	JpfModTw *self;

	self = jpf_get_mod_tw();
	msg = jpf_sysmsg_new(MESSAGE_TW_PLAY, &in_parm->screen_to_dec,
		sizeof(tw_screen_to_decoder), in_parm->seq,
		(JpfMsgPrivDes)jpf_tw_destroy_screen_to_dec);	//ע�⣬�������ٺ���ָ��
	if (G_UNLIKELY(!msg))
	{
		jpf_warning("jpf_sysmsg_new failed, no memory\n");
		return -1;
	}

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_PU);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


static gint jpf_mod_tw_send_screen_to_cu(tw_screen_to_cu *in_parm)
{
	jpf_mod_tw_func_begin("\n");

	JpfSysMsg *msg;
	JpfModTw *self;

	self = jpf_get_mod_tw();

	msg = jpf_sysmsg_new_2(MESSAGE_TW_PLAY_NOTIFY, in_parm,
		sizeof(tw_screen_to_cu), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_CU);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


static gint jpf_mod_tw_run_res_to_cu(tw_run_res *in_parm)
{
	jpf_mod_tw_func_begin("\n");

	JpfSysMsg *msg = NULL;
	JpfModTw *self;
	JpfCuExecuteRes res_info;

	self = jpf_get_mod_tw();

 	memset(&res_info, 0, sizeof(res_info));
 	SET_CODE(&res_info, in_parm->result);
 	strncpy(res_info.session, in_parm->session_id, SESSION_ID_LEN - 1);

	if (in_parm->tw_cmd_type == TW_RUN_STEP)
	{
		if (in_parm->cu_seq == TW_ILLEGAL_SEQ_NUM)
		{
			jpf_print("<JpfModTw> link step return, result = %d.", in_parm->result);
			return 0;
		}
		msg = jpf_sysmsg_new_2(MESSAGE_TW_RUN_STEP, &res_info,
			sizeof(res_info), in_parm->cu_seq);
	}
	else
		return -1;
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_CU);
	MSG_SET_RESPONSE(msg);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


static gint jpf_mod_tw_operate_to_dec(tw_operate_to_decoder_with_seq *in_parm,
	int operate_type)
{
	jpf_mod_tw_func_begin("\n");

	JpfSysMsg *msg;
	JpfModTw *self;

	self = jpf_get_mod_tw();

	msg = jpf_sysmsg_new_2(operate_type, &in_parm->operate_to_dec,
		sizeof(tw_operate_to_decoder), in_parm->seq);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_PU);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


static gint jpf_mod_tw_operate_result_to_cu(tw_operate_result_to_cu_with_seq *in_parm,
	int operate_type)
{
	jpf_mod_tw_func_begin("\n");

	JpfSysMsg *msg;
	JpfSysMsg *res_msg;
	JpfModTw *self;
	JpfCuExecuteRes res;

	self = jpf_get_mod_tw();

	//operate result
	memset(&res, 0, sizeof(res));
	SET_CODE(&res, in_parm->to_cu.result);
	strncpy(res.session, in_parm->to_cu.session_id, SESSION_ID_LEN - 1);
	res_msg = jpf_sysmsg_new_2(operate_type, &res, sizeof(res), in_parm->seq);
	if (G_UNLIKELY(!res_msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(res_msg, BUSSLOT_POS_CU);
	MSG_SET_RESPONSE(res_msg);
	jpf_app_obj_deliver_out((JpfAppObj *)self, res_msg);


	if (in_parm->to_cu.result != 0)
	{
		jpf_warning("<JpfModTw> operate result=%d, not to notify.",
			in_parm->to_cu.result);
		return 0;
	}
	//ͨ��
	msg = jpf_sysmsg_new_2(MESSAGE_TW_OPERATE_NOTIFY, &in_parm->to_cu,
		sizeof(tw_operate_result_to_cu), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_CU);
	jpf_app_obj_deliver_out((JpfAppObj *)self, msg);

	return 0;
}


gint jpf_mod_tw_event_handler(TW_INFO_TYPE cmd, void *in_parm, void *out_parm)
{
	gint err = -1;
	G_ASSERT(jpf_get_mod_tw() != NULL);
	G_ASSERT(in_parm);

	switch (cmd)
	{
	case TW_INFO_GET_TOUR:
		{
			err = jpf_mod_tw_get_tour((tw_tour_msg_request *)in_parm,
				(tw_tour_msg_response *)out_parm);
			break;
		}
	case TW_INFO_GET_GROUP:
		{
			err = jpf_mod_tw_get_group((tw_group_msg_request *)in_parm,
				(tw_group_msg_response *)out_parm);
			break;
		}
	case TW_INFO_GET_GROUP_STEP_N:
		{
			err = jpf_mod_tw_get_group_step_n((tw_group_step_n_request *)in_parm,
				(tw_group_step_n_response *)out_parm);
			break;
		}
	case TW_INFO_GET_DIS_GUID:
		{
			err = jpf_mod_tw_get_dis_guid((tw_dis_guid_request *)in_parm,
				(tw_dis_guid_response *)out_parm);
			break;
		}
	case TW_INFO_GET_EC_URL:
		{
			err = jpf_mod_tw_get_ec_url((tw_ec_url_request *)in_parm,
				(tw_ec_url_response *)out_parm);
			break;
		}
	case TW_INFO_QUERY_IF_UPDATE_URL:
		{
			err = jpf_mod_tw_query_if_update_ec_url((tw_update_url *)in_parm);
			break;
		}
	case TW_INFO_SEND_SCREEN_TO_DEC:
		{
			err = jpf_mod_tw_send_screen_to_dec((tw_screen_to_decoder_with_seq *)in_parm);
			break;
		}
	case TW_INFO_SEND_SCREEN_TO_CU:
		{
			err = jpf_mod_tw_send_screen_to_cu((tw_screen_to_cu *)in_parm);
			break;
		}
	case TW_INFO_SEND_CMD_RES_TO_CU:
		{
			err = jpf_mod_tw_run_res_to_cu((tw_run_res *)in_parm);
			break;
		}
	case TW_CLEAR_TO_DEC:
		{
			err = jpf_mod_tw_operate_to_dec((tw_operate_to_decoder_with_seq *)in_parm,
				MESSAGE_TW_CLEAR_DIVISION);
			break;
		}
	case TW_CLEAR_RESULT_TO_CU:
		{
			err = jpf_mod_tw_operate_result_to_cu((tw_operate_result_to_cu_with_seq *)in_parm,
				MESSAGE_TW_CLEAR_DIVISION);
			break;
		}
	case TW_CHANGE_DIVISION_MODE_TO_DEC:
		{
			err = jpf_mod_tw_operate_to_dec((tw_operate_to_decoder_with_seq *)in_parm,
				MESSAGE_CHANGE_DIV_MODE);
			break;
		}
	case TW_CHANGE_DIVISION_MODE_RESULT_TO_CU:
		{
			err = jpf_mod_tw_operate_result_to_cu((tw_operate_result_to_cu_with_seq *)in_parm,
				MESSAGE_CHANGE_DIV_MODE);
			break;
		}
	case TW_FULL_SCREEN_TO_DEC:
		{
			err = jpf_mod_tw_operate_to_dec((tw_operate_to_decoder_with_seq *)in_parm,
				MESSAGE_FULL_SCREEN);
			break;
		}
	case TW_FULL_SCREEN_RESULT_TO_CU:
		{
			err = jpf_mod_tw_operate_result_to_cu((tw_operate_result_to_cu_with_seq *)in_parm,
				MESSAGE_FULL_SCREEN);
			break;
		}
	case TW_EXIT_FULL_SCREEN_TO_DEC:
		{
			err = jpf_mod_tw_operate_to_dec((tw_operate_to_decoder_with_seq *)in_parm,
				MESSAGE_EXIT_FULL_SCREEN);
			break;
		}
	case TW_EXIT_FULL_SCREEN_RESULT_TO_CU:
		{
			err = jpf_mod_tw_operate_result_to_cu((tw_operate_result_to_cu_with_seq *)in_parm,
				MESSAGE_EXIT_FULL_SCREEN);
			break;
		}
	default:
		{
			jpf_mod_tw_log("error:cmd = %d\n", cmd);
		}
	}
	return err;
}

