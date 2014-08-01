/*
 * zmq_receiver microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

/* includes types and type metadata */

ubx_type_t types[] = {
        { NULL },
};

/* block meta information */
char zmq_receiver_meta[] =
        " { doc='',"
        "   real-time=true,"
        "}";

/* declaration of block configuration */
ubx_config_t zmq_receiver_config[] = {
        { .name="connection_spec", .type_name = "char", .doc="Connection string that defines the ZMQ type of connection. E.g. tcp://localhost:11411" },
        { NULL },
};

/* declaration port block ports */
ubx_port_t zmq_receiver_ports[] = {
        { .name="zmq_in", .out_type_name="unsigned char", .in_data_len=1, .doc="Arbitrary byte stream as recieved by a ZMQ message."  },
        { NULL },
};

/* declare a struct port_cache */
struct zmq_receiver_port_cache {
        ubx_port_t* zmq_in;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct zmq_receiver_port_cache *pc)
{
        pc->zmq_in = ubx_port_get(b, "zmq_in");
}


/* for each port type, declare convenience functions to read/write from ports */
//def_read_fun(read_zmq_in, unsigned char)

/* block operation forward declarations */
int zmq_receiver_init(ubx_block_t *b);
int zmq_receiver_start(ubx_block_t *b);
void zmq_receiver_stop(ubx_block_t *b);
void zmq_receiver_cleanup(ubx_block_t *b);
void zmq_receiver_step(ubx_block_t *b);


/* put everything together */
ubx_block_t zmq_receiver_block = {
        .name = "zmq_receiver",
        .type = BLOCK_TYPE_COMPUTATION,
        .meta_data = zmq_receiver_meta,
        .configs = zmq_receiver_config,
        .ports = zmq_receiver_ports,

        /* ops */
        .init = zmq_receiver_init,
        .start = zmq_receiver_start,
        .stop = zmq_receiver_stop,
        .cleanup = zmq_receiver_cleanup,
        .step = zmq_receiver_step,
};


/* zmq_receiver module init and cleanup functions */
int zmq_receiver_mod_init(ubx_node_info_t* ni)
{
        DBG(" ");
        int ret = -1;
        ubx_type_t *tptr;

        for(tptr=types; tptr->name!=NULL; tptr++) {
                if(ubx_type_register(ni, tptr) != 0) {
                        goto out;
                }
        }

        if(ubx_block_register(ni, &zmq_receiver_block) != 0)
                goto out;

        ret=0;
out:
        return ret;
}

void zmq_receiver_mod_cleanup(ubx_node_info_t *ni)
{
        DBG(" ");
        const ubx_type_t *tptr;

        for(tptr=types; tptr->name!=NULL; tptr++)
                ubx_type_unregister(ni, tptr->name);

        ubx_block_unregister(ni, "zmq_receiver");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(zmq_receiver_mod_init)
UBX_MODULE_CLEANUP(zmq_receiver_mod_cleanup)
