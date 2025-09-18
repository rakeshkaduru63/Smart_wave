#include <stdio.h>
#include <unistd.h>
#include<stdio.h>
#include "client.h"              
void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *msg) {
    printf("Received on topic %s: %s\n", msg->topic, (char*)msg->payload);
}

int main() {
    const char *host = "broker.hivemq.com";   
    int port = 1883;
    const char *topic = "cavli/test";
    struct mosquitto *mosq = mqtt_client_init("test_client");
    mosquitto_message_callback_set(mosq, on_message);
    if(mqtt_client_connect(mosq, host, port) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to connect\n");
        mqtt_client_cleanup(mosq);
        return 1;
    }
    printf("Connected to broker %s:%d\n", host, port);
    mqtt_client_subscribe(mosq, topic);
    printf("Subscribed to topic: %s\n", topic);
    mqtt_client_publish(mosq, topic, "Hello MQTT!");
    printf("Published message\n");
    mosquitto_loop_start(mosq);
    sleep(2);
    mqtt_client_disconnect(mosq);
    printf("Disconnected from broker\n");
    mosquitto_loop_stop(mosq, true);
    mqtt_client_cleanup(mosq);

    return 0;
}
