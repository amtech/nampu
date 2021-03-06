#include "nmp_message.h"
#include "nmp_internal_msg.h"
#include "nmp_xml.h"
#include "nmp_sysmsg.h"
#include "nmp_mysql_fun.h"
#include "nmp_mod_dbs.h"
#include "nmp_dbs_fun.h"
#include "nmp_memory.h"
#include "nmp_share_debug.h"
#include "db_connect_pool.h"
#include "nmp_share_errno.h"
#include "message/nmp_msg_ams.h"
#include "nmp_shared.h"
#include "nmp_list_head.h"
#include "nmp_xml_interface.h"


extern gchar g_domain_id[DOMAIN_ID_LEN];



static __inline__ gint
nmp_get_ams_register_info(NmpMysqlRes *mysql_result, NmpAmsRegisterRes*res_info)
{
    G_ASSERT(mysql_result != NULL && res_info != NULL);

    unsigned long field_num;
    NmpMysqlField *mysql_fields;    //modify: mysql_fields -> *msql_fields
    NmpMysqlRow mysql_row;
    char *value, *name;
    int j,row_num;

    row_num = nmp_sql_get_num_rows(mysql_result);
    if (row_num == 0)
    {
        nmp_warning("<ModDdbAms>No such record entry in database");
        return -E_NODBENT;
    }
    else
    {
        field_num = nmp_sql_get_num_fields(mysql_result);
        while ((mysql_row = nmp_sql_fetch_row(mysql_result)))
        {
            nmp_sql_field_seek(mysql_result, 0);
            mysql_fields = nmp_sql_fetch_fields(mysql_result);

            for (j = 0; j < field_num; j++)
            {
                name = nmp_sql_get_field_name(mysql_fields, j);
                if (!strcmp(name,"ams_keep_alive_freq"))
                {
                    value = nmp_sql_get_field_value(mysql_row, j);
                    res_info->keep_alive_time = atoi(value);
                }
                else
                    cms_debug(
                         "Ignore table field %s while getting user info",name
                    );
            }
        }

         return 0;
    }
}


NmpMsgFunRet
nmp_dbs_ams_register_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	G_ASSERT(app_obj != NULL && msg != NULL);

	NmpAmsRegister *req_info;
	NmpAmsRegisterRes res_info;
	NmpMysqlRes *mysql_res;
	char query_buf[QUERY_STR_LEN] = {0};
	int code = 0;

	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	memset(&res_info, 0, sizeof(res_info));
	snprintf(
		query_buf, QUERY_STR_LEN,
		"select ams_keep_alive_freq from %s where ams_id='%s'",
		AMS_TABLE, req_info->ams_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		code = nmp_get_ams_register_info(mysql_res, &res_info);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

	nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	SET_CODE(&res_info, code);
	nmp_dbs_modify_sysmsg_2(msg, &res_info, sizeof(res_info),
		BUSSLOT_POS_DBS, BUSSLOT_POS_AMS
	);

	return MFR_DELIVER_BACK;
}


NmpMsgFunRet
nmp_mod_dbs_change_ams_online_state_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	G_ASSERT(app_obj != NULL && msg != NULL);

	NmpMsgAmsOnlineChange *req_info;
	char query_buf[QUERY_STR_LEN] = {0};
	NmpMsgErrCode mysql_res;
	glong affect_num = 0;

	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	snprintf(
		query_buf, QUERY_STR_LEN,
		"update %s set ams_state=%d where ams_id='%s'",
		AMS_TABLE, req_info->new_status, req_info->ams_id
	);

	memset(&mysql_res, 0, sizeof(mysql_res));
	nmp_dbs_do_query_code(app_obj, msg, query_buf, &mysql_res, &affect_num);
	nmp_sysmsg_destroy(msg);
	return MFR_ACCEPTED;
}




static __inline__ gint
nmp_get_ams_time_policy(NmpMysqlRes *mysql_result, gchar *time_policy)
{
    G_ASSERT(mysql_result != NULL && time_policy != NULL);

    unsigned long field_num;
    NmpMysqlField *mysql_fields;    //modify: mysql_fields -> *msql_fields
    NmpMysqlRow mysql_row;
    char *value, *name;
    int j,row_num;

    row_num = nmp_sql_get_num_rows(mysql_result);
    if (row_num == 0)
    {
        nmp_warning("<ModDdbAms>No such record entry in database");
        return -E_NODBENT;
    }
    else
    {
        field_num = nmp_sql_get_num_fields(mysql_result);
        while ((mysql_row = nmp_sql_fetch_row(mysql_result)))
        {
            nmp_sql_field_seek(mysql_result, 0);
            mysql_fields = nmp_sql_fetch_fields(mysql_result);

            for (j = 0; j < field_num; j++)
            {
                name = nmp_sql_get_field_name(mysql_fields, j);
                if (!strcmp(name, "time_policy"))
                {
                    value = nmp_sql_get_field_value(mysql_row, j);
                    if(value)
                    {
                        time_policy[POLICY_LEN - 1] = 0;
    		           memset(time_policy, 0, POLICY_LEN);
                        strncpy(
                            time_policy,
                            value, POLICY_LEN - 1
                        );
                    }
                }
                else
                    cms_debug(
                         "Ignore table field %s while getting user info",name
                    );
            }
        }

         return 0;
    }
}


void
nmp_mod_dbs_ams_get_time_policy(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpActionPolicy *res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	gchar time_policy[POLICY_LEN] = {0};
	NmpMysqlRes *mysql_res;
	int code = 0;

	snprintf(
	    query_buf, QUERY_STR_LEN,
	    "select time_policy from %s where gu_id='%s' and domain_id='%s'",
	    LINK_TIME_POLICY_TABLE,
	    req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		code = nmp_get_ams_time_policy(mysql_res, time_policy);
		if (strlen(time_policy))
		    nmp_parse_ams_time_policy(time_policy, res_info);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

	nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
}


void
nmp_cpy_link_record_info(gint *gu_num, NmpMsgActionRecordGu *tmp,
	NmpMsgActionRecordGu *record_info)
{
	gint end_gu, exit = 0, i = 0, num;

	num = *gu_num;
	end_gu = *gu_num - 1;
	if (*gu_num == 0)
	{
	     memcpy(record_info, tmp, sizeof(NmpMsgActionRecordGu));
	     record_info->mss_count = 1;
	     num++;
	     *gu_num = num;
	     return;
	}

	while (end_gu >= 0)
	{
		if (memcmp(&record_info[end_gu].action_guid, &tmp->action_guid, sizeof(NmpShareGuid)))
		{
			end_gu--;
			continue;
		}

		exit = 1;//exit same gu
		break;
	}

      if (exit)
      {
      		while (strlen(record_info[end_gu].mss_id[i].mss_id))
      		{
			i++;
			if (i >= AMS_MAX_MSS_COUNT)
				return;
      		}
      		memcpy(&record_info[end_gu].mss_id[i], &tmp->mss_id[0], sizeof(NmpShareMssId));
      		record_info[end_gu].mss_count = i + 1;
      		return;
      	}

	memcpy(&record_info[num], tmp, sizeof(NmpMsgActionRecordGu));
	num++;
	*gu_num = num;
}


static __inline__ void
nmp_dbs_ams_get_link_record(NmpMysqlRes *result,
                   NmpMsgActionRecord *query_res
                  )
{
    G_ASSERT(query_res != NULL);

    gint info_no = 0, field_no =0;
    NmpMysqlRow mysql_row;
    NmpMysqlField* mysql_fields;
    gchar *name;
    gchar *value;
    unsigned int row_num;
    unsigned int field_num;
    NmpMsgActionRecordGu tmp;
    gint gu_num = 0;

    row_num = nmp_sql_get_num_rows(result);
    field_num = nmp_sql_get_num_fields(result);

    memset(&tmp, 0, sizeof(tmp));
    while ((mysql_row = nmp_sql_fetch_row(result)))
    {
        nmp_sql_field_seek(result, 0);
        mysql_fields = nmp_sql_fetch_fields(result);
        for(field_no = 0; field_no < field_num; field_no++)
        {
            name = nmp_sql_get_field_name(mysql_fields,field_no);
           if (!strcmp(name, "link_domain_id"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                {
                    tmp.action_guid.domain_id[DOMAIN_ID_LEN - 1] = 0;
                    strncpy(
                        tmp.action_guid.domain_id,
                        value, DOMAIN_ID_LEN - 1
                    );
                }
            }
	     else if (!strcmp(name, "link_guid"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                {
                    tmp.action_guid.guid[MAX_ID_LEN - 1] = 0;
                    strncpy(
                        tmp.action_guid.guid,
                        value, MAX_ID_LEN - 1
                    );
                }
            }
            else if (!strcmp(name, "level"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                	tmp.level = atoi(value);
            }
            else if (!strcmp(name, "mss_id"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                {
                    tmp.mss_id[0].mss_id[MSS_ID_LEN - 1] = 0;
                    strncpy(tmp.mss_id[0].mss_id, value, MSS_ID_LEN - 1);
                }
            }
            else if (!strcmp(name, "time_len"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                	tmp.time_len = atoi(value);
            }
            else if (!strcmp(name, "alarm_type"))
            {
                value = nmp_sql_get_field_value(mysql_row, field_no);
                if(value)
                    tmp.alarm_type= atoi(value);
            }
            else
                cms_debug("no need mysql name %s \n", name);
        }

        nmp_cpy_link_record_info(&gu_num, &tmp, &query_res->action_gu[0]);
        info_no++;
    }
}

void
nmp_mod_dbs_ams_get_link_record(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionRecord **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res;
	gint code = 0, total_num, ret, size;

	snprintf(query_buf, QUERY_STR_LEN,
		"select  count(distinct link_guid,link_domain_id) as count from %s \
		where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_RECORD_TABLE, req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj,query_buf);
	if (total_num == 0)
	{
		ret = 0;
		*res_info = NULL;
		return ;
	}

	size = sizeof(NmpMsgActionRecord) + total_num * sizeof(NmpMsgActionRecordGu);
	*res_info = nmp_mem_kalloc(size);
	memset(*res_info, 0, size);
	(*res_info)->action_gu_count = total_num;
	snprintf(
		query_buf, QUERY_STR_LEN,
		"select * from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_RECORD_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_record(mysql_res, *res_info);
		int i = (*res_info)->action_gu_count - 1;
		int j;
		while(i >=0)
		{
			printf("---@@@@--%s,%d,%s\n",(*res_info)->action_gu[i].action_guid.guid,
			(*res_info)->action_gu[i].mss_count,(*res_info)->action_gu[i].mss_id[0].mss_id);
			for (j = 0; j < (*res_info)->action_gu[i].mss_count; j++)
			printf("-----&&&&--%s\n",(*res_info)->action_gu[i].mss_id[j].mss_id);
			i--;

		}
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
}


static __inline__ void
nmp_dbs_ams_get_link_io(NmpMysqlRes *result, NmpMsgActionIO *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpMsgActionIOGu *cur_gu;
	gint gu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		if (gu_num >= query_res->action_gu_count)
			break;
		cur_gu = &query_res->action_gu[gu_num];

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "link_domain_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.domain_id[DOMAIN_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.domain_id, value, DOMAIN_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "link_guid"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.guid[MAX_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.guid, value, MAX_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "time_len"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->time_len = atoi(value);
			}
			else if (!strcmp(name, "alarm_type"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->alarm_type= atoi(value);
			}
			else if (!strcmp(name, "IO_value"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->io_value[IO_VALUE_LEN - 1] = 0;
					strncpy(cur_gu->io_value, value, IO_VALUE_LEN - 1);
				}
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		gu_num++;
	}

	query_res->action_gu_count = gu_num;
}


void
nmp_mod_dbs_ams_get_link_io(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionIO **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res = NULL;
	gint code = 0, total_num, size;
	NmpMsgActionIO *res = NULL;

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(*) as count from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_IO_TABLE, req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}

	size = sizeof(NmpMsgActionIO) + total_num * sizeof(NmpMsgActionIOGu);
	res = nmp_mem_kalloc0(size);
	if (!res)
		goto end;
	res->action_gu_count = total_num;

	snprintf(query_buf, QUERY_STR_LEN,
		"select * from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_IO_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_io(mysql_res, res);
		/******************* zyt test *********************/
		/*
		int i;
		for (i = 0; i < res->action_gu_count; i++)
		{
			NmpMsgActionIOGu *gu = &res->action_gu[i];
			nmp_print("<zyt_test> guid:%s, domain_id:%s", gu->action_guid.guid,
				gu->action_guid.domain_id);
		}
		*/
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

end:
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	*res_info = res;
	return ;
}


static __inline__ void
nmp_dbs_ams_get_link_step(NmpMysqlRes *result, NmpMsgActionStep *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpMsgActionStepGu *cur_gu;
	gint gu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		if (gu_num >= query_res->action_gu_count)
			break;
		cur_gu = &query_res->action_gu[gu_num];

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "alarm_type"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->alarm_type= atoi(value);
			}
			else if (!strcmp(name, "tw_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->tw_id = atoi(value);
			}
			else if (!strcmp(name, "screen_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->screen_id = atoi(value);
			}
			else if (!strcmp(name, "division_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->division_id = atoi(value);
			}
			else if (!strcmp(name, "division_num"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->division_num = atoi(value);
			}
			else if (!strcmp(name, "level"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->level = atoi(value);
			}
			else if (!strcmp(name, "gu_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->ec_name[TW_MAX_VALUE_LEN - 1] = 0;
					strncpy(cur_gu->ec_name, value, TW_MAX_VALUE_LEN - 1);
				}
			}
			else if (!strcmp(name, "enc_domain_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->ec_domain_id[TW_ID_LEN - 1] = 0;
					strncpy(cur_gu->ec_domain_id, value, TW_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "enc_guid"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->ec_guid[TW_ID_LEN - 1] = 0;
					strncpy(cur_gu->ec_guid, value, TW_ID_LEN - 1);
				}
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		gu_num++;
	}

	query_res->action_gu_count = gu_num;
}


void
nmp_mod_dbs_ams_get_link_step(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionStep **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res = NULL;
	gint code = 0, total_num, size;
	NmpMsgActionStep *res = NULL;

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(*) as count from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_STEP_TABLE, req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}

	size = sizeof(NmpMsgActionStep) + total_num * sizeof(NmpMsgActionStepGu);
	res = nmp_mem_kalloc0(size);
	if (!res)
		goto end;
	res->action_gu_count = total_num;

	snprintf(query_buf, QUERY_STR_LEN,
		"select t1.*,t2.gu_name from %s as t1, %s as t2 where t1.gu_id='%s' and " \
		"t1.domain_id='%s' and t1.enc_domain_id=t2.gu_domain and t1.enc_guid=t2.gu_id",
		ALARM_LINK_STEP_TABLE, GU_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_step(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

end:
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	*res_info = res;
	return ;
}


static __inline__ void
nmp_dbs_ams_get_link_preset(NmpMysqlRes *result, NmpMsgActionPreset *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpMsgActionPresetGu *cur_gu;
	gint gu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		if (gu_num >= query_res->action_gu_count)
			break;
		cur_gu = &query_res->action_gu[gu_num];

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "link_domain_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.domain_id[DOMAIN_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.domain_id, value, DOMAIN_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "link_guid"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.guid[MAX_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.guid, value, MAX_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "preset_no"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->preset_num = atoi(value);
			}
			else if (!strcmp(name, "alarm_type"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->alarm_type= atoi(value);
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		gu_num++;
	}

	query_res->action_gu_count = gu_num;
}


void
nmp_mod_dbs_ams_get_link_preset(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionPreset **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res = NULL;
	gint code = 0, total_num, size;
	NmpMsgActionPreset *res = NULL;

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(*) as count from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_PRESET_TABLE, req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}

	size = sizeof(NmpMsgActionPreset) + total_num * sizeof(NmpMsgActionPresetGu);
	res = nmp_mem_kalloc0(size);
	if (!res)
		goto end;
	res->action_gu_count = total_num;

	snprintf(query_buf, QUERY_STR_LEN,
		"select * from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_PRESET_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_preset(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

end:
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	*res_info = res;
	return ;
}


static void nmp_dbs_stor_link_snapshot_info(NmpMsgActionSnapshot *res,
	NmpMsgActionSnapshotGu *gu, gint *gu_count)
{
	G_ASSERT(res != NULL && gu != NULL);

	NmpMsgActionSnapshotGu *cur_gu = NULL;
	gint i;

	if (*gu_count > res->action_gu_count)
	{
		nmp_warning("<NmpDbsMhAms> error: gu_count(%d) > " \
			"res->action_gu_count(%d)", *gu_count, res->action_gu_count);
		return ;
	}

	for (i = 0; i < *gu_count; i++)
	{
		cur_gu = &res->action_gu[i];
		if (strcmp(gu->action_guid.guid, cur_gu->action_guid.guid) == 0 &&
			strcmp(gu->action_guid.domain_id, cur_gu->action_guid.domain_id) == 0)
		{
			guint mss_count = cur_gu->mss_count;
			if (mss_count >= AMS_MAX_MSS_COUNT)
			{
				nmp_warning("<NmpDbsMhAms> error:mss_count(%u) >= %d, return.",
					mss_count, AMS_MAX_MSS_COUNT);
				return ;
			}
			cur_gu->mss_id[mss_count] = gu->mss_id[0];
			cur_gu->mss_count++;
			return ;
		}
	}

	if (*gu_count == res->action_gu_count)
	{
		nmp_warning("<NmpDbsMhAms> error:gu_count = res->action_gu_count = %d",
			*gu_count);
		return ;
	}

	cur_gu = &res->action_gu[*gu_count];

	memcpy(cur_gu, gu, sizeof(NmpMsgActionSnapshotGu));
	cur_gu->mss_count = 1;

	(*gu_count)++;
}


static __inline__ void
nmp_dbs_ams_get_link_snapshot(NmpMysqlRes *result, NmpMsgActionSnapshot *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpMsgActionSnapshotGu tmp_gu;
	gint gu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "link_domain_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					tmp_gu.action_guid.domain_id[DOMAIN_ID_LEN - 1] = 0;
					strncpy(tmp_gu.action_guid.domain_id, value, DOMAIN_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "link_guid"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					tmp_gu.action_guid.guid[MAX_ID_LEN - 1] = 0;
					strncpy(tmp_gu.action_guid.guid, value, MAX_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "level"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					tmp_gu.level = atoi(value);
			}
			else if (!strcmp(name, "picture_num"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					tmp_gu.picture_count = atoi(value);
			}
			else if (!strcmp(name, "alarm_type"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					tmp_gu.alarm_type= atoi(value);
			}
			else if (!strcmp(name, "mss_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					tmp_gu.mss_id[0].mss_id[MSS_ID_LEN - 1] = 0;
					strncpy(tmp_gu.mss_id[0].mss_id, value, MSS_ID_LEN - 1);
				}
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		nmp_dbs_stor_link_snapshot_info(query_res, &tmp_gu, &gu_num);
	}

	query_res->action_gu_count = gu_num;
}


void
nmp_mod_dbs_ams_get_link_snapshot(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionSnapshot **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res = NULL;
	gint code = 0, total_num, size;
	NmpMsgActionSnapshot *res = NULL;

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(distinct link_guid,link_domain_id) as count from %s " \
		"where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_SNAPSHOT_TABLE, req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}

	size = sizeof(NmpMsgActionSnapshot) + total_num * sizeof(NmpMsgActionSnapshotGu);
	res = nmp_mem_kalloc0(size);
	if (!res)
		goto end;
	res->action_gu_count = total_num;

	snprintf(query_buf, QUERY_STR_LEN,
		"select * from %s where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_SNAPSHOT_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);

	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_snapshot(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

end:
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	*res_info = res;
	return ;
}


static __inline__ void
nmp_dbs_ams_get_cu_list(NmpMysqlRes *result, NmpMsgActionMap *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpAllCuOwnPu *cur_gu;
	gint cu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		if (cu_num >= query_res->cu_count)
			break;
		cur_gu = &query_res->cu_list[cu_num];

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "user_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->username[USER_NAME_LEN - 1] = 0;
					strncpy(cur_gu->username, value, USER_NAME_LEN - 1);
				}
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		cu_num++;
	}

	query_res->cu_count = cu_num;
}


static __inline__ void
nmp_dbs_ams_get_link_map(NmpMysqlRes *result, NmpMsgActionMap *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;
	NmpMsgActionMapGu *cur_gu;
	gint gu_num = 0;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		if (gu_num >= AMS_MAX_LINK_MAP_GU)
			break;
		cur_gu = &query_res->action_gu[gu_num];

		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "link_domain_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.domain_id[DOMAIN_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.domain_id, value, DOMAIN_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "link_guid"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->action_guid.guid[MAX_ID_LEN - 1] = 0;
					strncpy(cur_gu->action_guid.guid, value, MAX_ID_LEN - 1);
				}
			}
			else if (!strcmp(name, "gu_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->gu_name[GU_NAME_LEN - 1] = 0;
					strncpy(cur_gu->gu_name, value, GU_NAME_LEN - 1);
				}
			}
			else if (!strcmp(name, "map_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->map_id = atoi(value);
			}
			else if (!strcmp(name, "map_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					cur_gu->map_name[MAP_NAME_LEN - 1] = 0;
					strncpy(cur_gu->map_name, value, MAP_NAME_LEN - 1);
				}
			}
			else if (!strcmp(name, "alarm_type"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->alarm_type= atoi(value);
			}
			else if (!strcmp(name, "level"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					cur_gu->level = atoi(value);
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}

		gu_num++;
	}

	query_res->action_gu_count = gu_num;
}


static __inline__ void
nmp_dbs_ams_get_alarm_info(NmpMysqlRes *result, NmpMsgActionMap *query_res)
{
	G_ASSERT(query_res != NULL);

	gint field_no =0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		for(field_no = 0; field_no < field_num; field_no++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_no);
			if (!strcmp(name, "gu_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					query_res->gu_name[GU_NAME_LEN - 1] = 0;
					strncpy(query_res->gu_name, value, GU_NAME_LEN - 1);
				}
			}
			else if (!strcmp(name, "map_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					query_res->map_id = atoi(value);
			}
			else if (!strcmp(name, "pu_area"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
					query_res->defence_id = atoi(value);
			}
			else if (!strcmp(name, "area_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					query_res->defence_name[AREA_NAME_LEN - 1] = 0;
					strncpy(query_res->defence_name, value, AREA_NAME_LEN - 1);
				}
			}
			else if (!strcmp(name, "map_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_no);
				if(value)
				{
					query_res->map_name[MAP_NAME_LEN - 1] = 0;
					strncpy(query_res->map_name, value, MAP_NAME_LEN - 1);
				}
			}
			else
				cms_debug("no need mysql name %s \n", name);
		}
	}
}

void
nmp_mod_dbs_ams_get_link_map(NmpAppObj *app_obj,
	NmpMsgAmsGetActionInfo *req_info, NmpMsgActionMap **res_info)
{
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_res = NULL;
	gint code = 0, total_num, size;
	NmpMsgActionMap *res = NULL;

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(distinct link_guid,link_domain_id) as count from %s " \
		"where gu_id='%s' and domain_id='%s'",
		ALARM_LINK_MAP_TABLE, req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);

	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}

	snprintf(query_buf, QUERY_STR_LEN,
        "select count(distinct user_name) as count from %s where user_guid='%s' and \
        user_guid_domain='%s'",
        USER_OWN_GU_TABLE, req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
    );
    total_num = nmp_get_record_count(app_obj, query_buf);
    if (total_num == 0)
	{
		res = NULL;
		nmp_warning("<ModDdbAms> nmp_get_record_count = 0.");
		goto end;
	}
    size = sizeof(NmpMsgActionMap) + total_num*sizeof(NmpAllCuOwnPu);
    res = nmp_mem_kalloc(size);
    memset(res, 0, size);
	res->cu_count = total_num;

	snprintf(query_buf, QUERY_STR_LEN,
        "select distinct user_name from %s where user_guid='%s' and \
        user_guid_domain='%s'",
        USER_OWN_GU_TABLE, req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
    );
	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_cu_list(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));

		snprintf(query_buf, QUERY_STR_LEN,
		"select t1.*,t2.gu_name,t3.map_id,t4.map_name from %s as t1,%s as t2,%s as t3,%s as t4 " \
		"where t1.gu_id='%s' and t1.domain_id='%s' and t1.link_guid=t2.gu_id "\
		"and t1.link_domain_id=t2.gu_domain and t1.link_guid=t3.gu_id and "\
		"t1.link_domain_id=t3.gu_domain and t3.map_id=t4.map_id",
		ALARM_LINK_MAP_TABLE, GU_TABLE, MAP_GU_TABLE, DEFENCE_MAP_TABLE,
		req_info->alarm_guid.guid, req_info->alarm_guid.domain_id
	);
	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_link_map(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);

	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));

	snprintf(query_buf, QUERY_STR_LEN,
		"select t1.gu_name,t2.pu_area,t3.map_id,t4.area_name,t5.map_name from "\
		"%s as t1,%s as t2,%s as t3,%s as t4,%s as t5  " \
		"where t1.gu_id='%s' and t1.gu_domain='%s' and t1.gu_puid=t2.pu_id "\
		"and t1.gu_domain=t2.pu_domain and t1.gu_id=t3.gu_id and "\
		"t1.gu_domain=t3.gu_domain and t2.pu_area=t4.area_id and t3.map_id=t5.map_id",
		GU_TABLE, PU_TABLE, MAP_GU_TABLE,AREA_TABLE,DEFENCE_MAP_TABLE,req_info->alarm_guid.guid,
		req_info->alarm_guid.domain_id
	);
	mysql_res = nmp_dbs_do_query_res(app_obj, query_buf);
	BUG_ON(!mysql_res);
	if (G_LIKELY(!MYSQL_RESULT_CODE(mysql_res)))  //success:0 fail:!0
	{
		nmp_dbs_ams_get_alarm_info(mysql_res, res);
	}
	else
		code = MYSQL_RESULT_CODE(mysql_res);
end:
	if (mysql_res)
		nmp_sql_put_res(mysql_res, sizeof(NmpMysqlRes));
	*res_info = res;

	return ;
}


void
nmp_mem_kfree_action_policy(gpointer p, gint size)
{
	NmpMsgAmsGetActionInfoRes *action_policy;
	gint i;

	action_policy = (NmpMsgAmsGetActionInfoRes *)p;
	for (i = 0; i < AMS_ACTION_MAX; i++)
	{
		if (action_policy->actions[i])
		{
			nmp_mem_kfree(action_policy->actions[i], -1);
		}
	}
	nmp_mem_kfree(action_policy, sizeof(NmpMsgAmsGetActionInfoRes));
}


NmpMsgFunRet
nmp_mod_dbs_get_action_info_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	G_ASSERT(app_obj != NULL && msg != NULL);

	NmpMsgAmsGetActionInfo *req_info;
	NmpMsgAmsGetActionInfoRes *res_info = NULL;

	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	res_info = nmp_mem_kalloc(sizeof(NmpMsgAmsGetActionInfoRes));
	if (!res_info)
	{
		nmp_sysmsg_destroy(msg);
		return MFR_ACCEPTED;
	}
	memset(res_info, 0, sizeof(NmpMsgAmsGetActionInfoRes));
	nmp_mod_dbs_ams_get_time_policy(app_obj, req_info, &res_info->action_policy);

	nmp_mod_dbs_ams_get_link_record(app_obj, req_info,
		(NmpMsgActionRecord **)(&res_info->actions[AMS_ACTION_RECORD]));

	nmp_mod_dbs_ams_get_link_io(app_obj, req_info,
		(NmpMsgActionIO **)(&res_info->actions[AMS_ACTION_IO]));

	nmp_mod_dbs_ams_get_link_step(app_obj, req_info,
		(NmpMsgActionStep **)(&res_info->actions[AMS_ACTION_STEP]));

	nmp_mod_dbs_ams_get_link_preset(app_obj, req_info,
		(NmpMsgActionPreset **)(&res_info->actions[AMS_ACTION_PRESET]));

	nmp_mod_dbs_ams_get_link_snapshot(app_obj, req_info,
		(NmpMsgActionSnapshot **)(&res_info->actions[AMS_ACTION_SNAPSHOT]));

	nmp_mod_dbs_ams_get_link_map(app_obj, req_info,
		(NmpMsgActionMap **)(&res_info->actions[AMS_ACTION_MAP]));

	nmp_dbs_modify_sysmsg(msg, res_info, sizeof(NmpMsgAmsGetActionInfoRes),
		BUSSLOT_POS_DBS, BUSSLOT_POS_AMS,
		(NmpMsgPrivDes)nmp_mem_kfree_action_policy);

	return MFR_DELIVER_BACK;
}


static __inline__ void
nmp_dbs_ams_get_device_info(NmpMysqlRes *result, NmpAmsGetDeviceInfoRes *query_res)
{
	G_ASSERT(query_res != NULL);

	gint info_i = 0, field_i = 0;
	NmpMysqlRow mysql_row;
	NmpMysqlField* mysql_fields;
	gchar *name;
	gchar *value;
	unsigned int row_num;
	unsigned int field_num;

	row_num = nmp_sql_get_num_rows(result);
	field_num = nmp_sql_get_num_fields(result);

	while ((mysql_row = nmp_sql_fetch_row(result)))
	{
		nmp_sql_field_seek(result, 0);
		mysql_fields = nmp_sql_fetch_fields(result);
		NmpAmsDeviceInfo *dev = &query_res->dev_info[info_i];

		for(field_i = 0; field_i < field_num; field_i++)
		{
			name = nmp_sql_get_field_name(mysql_fields, field_i);

			if (!strcmp(name, "pu_id"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if (value)
					NMP_COPY_VAL(dev->puid, value,
					MAX_ID_LEN);
			}
			else if (!strcmp(name, "pu_domain"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if (value)
					NMP_COPY_VAL(dev->domain, value,
					DOMAIN_ID_LEN);
			}
			else if (!strcmp(name, "dev_name"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if (value)
					NMP_COPY_VAL(dev->dev_name, value,
					AMS_DEV_NAME_LEN);
			}
			else if (!strcmp(name, "dev_passwd"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if (value)
					NMP_COPY_VAL(dev->dev_passwd, value,
					AMS_DEV_PASSWD_LEN);
			}
			else if (!strcmp(name, "dev_ip"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if (value)
					NMP_COPY_VAL(dev->dev_ip, value,
					MAX_IP_LEN);
			}
			else if (!strcmp(name, "dev_port"))
			{
				value = nmp_sql_get_field_value(mysql_row, field_i);
				if(value)
					dev->dev_port = atoi(value);
			}
		}

		info_i++;
		if (info_i >= query_res->back_count)
			break;
	}
}


static __inline__ NmpAmsGetDeviceInfoRes *
nmp_dbs_ams_get_device(NmpMysqlRes *mysql_res, gint *size)
{
	gint row_num, len;
	NmpAmsGetDeviceInfoRes *query_res;

	row_num = nmp_sql_get_num_rows(mysql_res);
	if (row_num == 0)
	{
		len = sizeof(NmpAmsGetDeviceInfoRes);
		query_res = nmp_mem_kalloc(len);
		if (G_UNLIKELY(!query_res))
			return NULL;

		memset(query_res, 0, len);
		SET_CODE(query_res, E_NODBENT);
		query_res->total_count = 0;
		query_res->back_count = 0;
	}
	else
	{
		len = sizeof(NmpAmsGetDeviceInfoRes) + row_num * sizeof(NmpAmsDeviceInfo);
		query_res = nmp_mem_kalloc(len);
		if (G_UNLIKELY(!query_res))
			return NULL;

		memset(query_res, 0, len);
		query_res->back_count = row_num;
		SET_CODE(query_res, 0);
		nmp_dbs_ams_get_device_info(mysql_res, query_res);
	}
	*size = len;

	return query_res;
}


static NmpMsgFunRet
nmp_dbs_ams_get_device_info_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	G_ASSERT(app_obj != NULL && msg != NULL);
	NmpAmsGetDeviceInfo *req_info = NULL;
	NmpAmsGetDeviceInfoRes *res_info = NULL;
	gchar query_buf[QUERY_STR_LEN] = {0};
	NmpMysqlRes *mysql_result = NULL;
	gint row_num;
	gint total_num;
	gint ret = 0, size;

	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	snprintf(query_buf, QUERY_STR_LEN,
		"select count(*) as count from %s where ams_id='%s'",
		AMS_CONFIGURE_TABLE, req_info->ams_id
	);
	total_num =  nmp_get_record_count(app_obj, query_buf);
	if (total_num == 0)
	{
		ret = 0;
		goto end;
	}

	snprintf(query_buf, QUERY_STR_LEN,
		"select * from %s where ams_id='%s' limit %d,%d",
		AMS_CONFIGURE_TABLE, req_info->ams_id,
		req_info->start_num, req_info->req_num
	);

	mysql_result = nmp_dbs_do_query_res(app_obj, query_buf);
	NMP_DBS_CHECK_MYSQL_RESULT(mysql_result, ret, row_num, end);

	res_info = nmp_dbs_ams_get_device(mysql_result, &size);
	if (G_UNLIKELY(!res_info))
	{
		nmp_warning("<NmpModDbs> alloc error");
		nmp_sysmsg_destroy(msg);
		return MFR_ACCEPTED;
	}
	if (total_num <= res_info->back_count)
		res_info->total_count = res_info->back_count;
	else
		res_info->total_count = total_num;

end:
	if(mysql_result)
		nmp_sql_put_res(mysql_result, sizeof(NmpMysqlRes));

	if (res_info == NULL)
	{
		size = sizeof(NmpAmsGetDeviceInfoRes);
		res_info = nmp_mem_kalloc(size);
		if (!res_info)
		{
			nmp_warning("<NmpModDbs> alloc error");
			nmp_sysmsg_destroy(msg);
			return MFR_ACCEPTED;
		}

		memset(res_info, 0, size);
		res_info->total_count = 0;
		res_info->back_count = 0;
	}

	SET_CODE(res_info, ret);
	NMP_COPY_VAL(res_info->ams_id, req_info->ams_id, AMS_ID_LEN);

	nmp_dbs_modify_sysmsg(msg, res_info, size, BUSSLOT_POS_DBS,
		BUSSLOT_POS_AMS, nmp_mem_kfree);

	return MFR_DELIVER_BACK;
}


void
nmp_mod_dbs_register_ams_msg_handler(NmpModDbs *self)
{
    NmpAppMod *super_self = (NmpAppMod*)self;

    nmp_app_mod_register_msg(
        super_self,
        MESSAGE_AMS_REGISTER,
        NULL,
        nmp_dbs_ams_register_b,
        0
    );

    nmp_app_mod_register_msg(
        super_self,
    	 MSG_AMS_ONLINE_CHANGE,
    	 NULL,
    	 nmp_mod_dbs_change_ams_online_state_b,
    	 0
    );

    nmp_app_mod_register_msg(
        super_self,
    	 MSG_AMS_GET_ACTION_INFO,
    	 NULL,
    	 nmp_mod_dbs_get_action_info_b,
    	 0
    );

	nmp_app_mod_register_msg(
		super_self,
		MESSAGE_AMS_GET_DEVICE_INFO,
		NULL,
		nmp_dbs_ams_get_device_info_b,
		0
	);
}

