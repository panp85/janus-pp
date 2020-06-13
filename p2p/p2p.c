#include <dlfcn.h>
#include <dirent.h>
#include <net/if.h>
#include <netdb.h>
#include <signal.h>
#include <getopt.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#ifdef HAVE_TURNRESTAPI
#include <curl/curl.h>
#endif

#include "janus.h"
#include "version.h"
#include "cmdline.h"
#include "config.h"
#include "apierror.h"
#include "debug.h"
#include "ip-utils.h"
#include "rtcp.h"
#include "auth.h"
#include "record.h"
#include "events.h"


#include "p2p.h"

GHashTable *p2p_rooms;

typedef struct room_one(
	char *room_id;
//	guint64 key;
	int peer_num;
	GHashTable *peers;
	
) room_one;

typedef struct peer_one{
	janus_session *session;
	janus_request *request;
	
} peer_one;

void free_room(gpointer data){
	g_free(data);
}

void free_peer(gpointer data){
	g_free(data);
}

void init(){
	if(p2p_rooms){
		return;
	}
	p2p_rooms = //g_hash_table_new_full(g_int64_hash, g_int64_equal, (GDestroyNotify)g_free,  (GDestroyNotify)free_room);
		g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, (GDestroyNotify)free_room);;
}
#if 0
room_one *room_create(guint64 session_id) {
	janus_session *session = NULL;
	if(session_id == 0) {
		while(session_id == 0) {
			session_id = janus_random_uint64();
			session = janus_session_find(session_id);
			if(session != NULL) {
				/* Session ID already taken, try another one */
				janus_refcount_decrease(&session->ref);
				session_id = 0;
			}
		}
	}
	session = (janus_session *)g_malloc(sizeof(janus_session));
	JANUS_LOG(LOG_INFO, "Creating new session: %"SCNu64"; %p\n", session_id, session);
	session->session_id = session_id;
	janus_refcount_init(&session->ref, janus_session_free);
	session->source = NULL;
	g_atomic_int_set(&session->destroyed, 0);
	g_atomic_int_set(&session->timeout, 0);
	g_atomic_int_set(&session->transport_gone, 0);
	session->last_activity = janus_get_monotonic_time();
	session->ice_handles = NULL;
	janus_mutex_init(&session->mutex);
	janus_mutex_lock(&sessions_mutex);
	g_hash_table_insert(sessions, janus_uint64_dup(session->session_id), session);
	janus_mutex_unlock(&sessions_mutex);
	return session;
}
#endif


peer_one* new_peer(janus_request *request, json_t *root){
	guint64 session_id;

	janus_session *session = janus_session_create(session_id);
	if(session == NULL) {
		janus_process_error(request, session_id, transaction_text, JANUS_ERROR_UNKNOWN, "Memory error");
		return;
	}
	//session_id = session->session_id;
	/* We increase the counter as this request is using the session */
	janus_refcount_increase(&session->ref);
	/* Take note of the request source that originated this session (HTTP, WebSockets, RabbitMQ?) */
	session->source = janus_request_new(request->transport, request->instance, NULL, FALSE, NULL);
	/* Notify the source that a new session has been created */
	request->transport->session_created(request->instance, session->session_id);

	peer_one *peer = (peer_one*)g_malloc(sizeof(peer_one));;
	peer.session = session;
	peer.request = request;
	//peer_one *peer = 
	//janus_session *session = g_hash_table_lookup(sessions, &session_id);
	return peer;
}

room_one* new_room(janus_request *request, json_t *root, char *room_id){
	//guint64 key = 0;
	room_one* room = (room_one*)g_malloc(sizeof(room_one));
	/*
	while(key == 0) {
		key = janus_random_uint64();
		room_one* r = g_hash_table_lookup(p2p_rooms, &key);
		if(r != NULL) {
			key = 0;
		}
	}
	
	room->key = key;
	*/
	char *key = g_strdup(room_id);
	g_hash_table_insert(p2p_rooms, key, room);

	room->peers = //g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, (GDestroyNotify)free_peer);
		g_hash_table_new_full(g_int64_hash, g_int64_equal, (GDestroyNotify)g_free,  (GDestroyNotify)free_peer);

	return room;
}

void message_process(janus_request *request, json_t *root, peer_on *peer){
/*
	json_t *session_id = json_object_get(root, "session_id");
	const char *sid = json_string_value(session_id);
	janus_session *session;
	
	session = janus_session_find(session_id);
*/
	json_t *command = json_object_get(root, "command");
	const gchar *command_text = json_string_value(command);

	if(!strcasecmp(command_text, "offer")) {
		
	}
	else if(!strcasecmp(command_text, "answer")){
	} 
	else if(!strcasecmp(command_text, "ice_candidate")){
	} 
}

void p2p_proces(janus_request *request, json_t *root) {
		init();
		json_t *transaction = json_object_get(root, "transaction");
		const gchar *transaction_text = json_string_value(transaction);
		json_t *room = json_object_get(root, "room");
		if(!room){
			JANUS_LOG(LOG_ERR, "no room.\n");
			janus_process_error(request, 0, transaction_text, 1000, "no room");
			return;
		}

		const char *r = json_string_value(room);
		peer_one* peer;
		room_one *room_ins = g_hash_table_lookup(p2p_rooms, r);
		if(room_ins){//
			json_t *session_id = json_object_get(root, "session_id");
			const guint64 sid = json_integer_value(session_id);
			if(sid){
				//session = janus_session_find(sed);
				peer = g_hash_table_lookup(room_ins->peers, sid);
				if(!peer){
					janus_process_error(request, sid, transaction_text, 1000, "no room");
				}
				message_process(request, root, peer);
			}
			else{
				peer = new_peer(request, root);
				peer->room_id = g_strdup(r);
				g_hash_table_insert(room_ins->peers, janus_uint64_dup(session->session_id), peer);
			}
		}
		else{
			room_ins = new_room(request, root, r);
			peer = new_peer(request, root);
			peer->root_id = g_strdup(r);
			g_hash_table_insert(room_ins->peers, janus_uint64_dup(session->session_id), peer);

			g_hash_table_insert(p2p_rooms, g_strdup(r), room_ins);
		}
		
		json_t *reply = janus_create_message("success", peer->session->session_id, transaction_text);
		json_t *data = json_object();
		json_object_set_new(data, "id", json_integer(handle_id));
		
		json_object_set_new(reply, "data", data);
		/* Send the success reply */
		int ret = janus_process_success(request, reply);
}

void p2p_free(guint64 session_id){
	GHashTableIter iter;
	gpointer value;
	
	g_hash_table_iter_init(&iter, p2p_rooms);
	while(g_hash_table_iter_next(&iter, NULL, &value)) {
		room_one *room = (room_one *) value;
		peer_one* peer = g_hash_table_lookup(room->peers, session_id);
	
		if(peer){
			GHashTableIter iter_peer;
			gpointer value_peer;
			
			g_hash_table_iter_init(iter_peer, room->peers);
			while(g_hash_table_iter_next(&iter_peer, NULL, &value_peer)){
				peer_one* peer_ = (peer_one *)value_peer;
				if(peer_ != peer){//todo 多对多
					json_t *reply = janus_create_message("hangup", 0, NULL);
					//json_object_set_new(reply, "data", data);
					int ret = janus_process_success(peer_->request, reply);
				}
			}
		}
	}
}

int isp2p(json_t *root){
	json_t *p2p = json_object_get(root, "p2p");
	int  = 0;
	//const gchar *transaction_text = json_string_value(transaction);
	if(p2p) {
		return 1;
	}
	return 0;
}

