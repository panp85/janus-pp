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

GHashTable *p2p_room;

struct room(
	char *room_id;
	int room_num;
	
)

void free_room(gpointer data){
	g_free(data);
}

void init(){
	p2p_room = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, (GDestroyNotify)free_room);
	
	
}

void add_peer(){
	
}

void new_root(char* t){

}

void p2p_proces(janus_request *request, json_t *root) {
		init();
		json_t *room = json_object_get(root, "room");
		if(!room){
			JANUS_LOG(LOG_ERR, "no room.\n");
			janus_process_error(request, session_id, transaction_text, 1000, "no room");
		}

		const char *t = json_string_value(room);
		struct room *room_ins = g_hash_table_lookup(p2p_room, t);
		if(room_ins){
			add_peer();
			return;
		}
		else{
			new_root(t);
		}
		
		g_hash_table_insert(p2p_room, );
		json_t *reply = janus_create_message("success", session_id, transaction_text);
		json_t *data = json_object();
		//json_object_set_new(data, "id", json_integer(handle_id));
		
		json_object_set_new(reply, "data", data);
		/* Send the success reply */
		ret = janus_process_success(request, reply);
}


