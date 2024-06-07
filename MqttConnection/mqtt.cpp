#include <iostream>
#include <mqtt/async_client.h>
 
// MQTT broker details
const std::string broker_address = "ssl://a10suzhdnq8qws-ats.iot.ap-south-1.amazonaws.com:8883";
const std::string client_id = "example_cpp_client";
const std::string topic = "example_topic";
 
// SSL/TLS configuration
const std::string ca_file = "/usrdata/certs/ca-crt.pem";
const std::string cert_file = "/usrdata/certs/client-crt.pem";
const std::string private_key_file = "/usrdata/certs/client.pem";
 
int main() {
    // Create an MQTT client
    mqtt::async_client client(broker_address, client_id);
    
    mqtt::ssl_options ssl_options;
    mqtt::connect_options connOpts;
    ssl_options.set_trust_store("/usrdata/certs/ca-crt.pem");
    std::cout << "--------2-----------" << std::endl;
    ssl_options.set_key_store("/usrdata/certs/client-crt.pem");
    std::cout << "--------3-----------" << std::endl;
    ssl_options.set_private_key("/usrdata/certs/client.pem");
    std::cout << "--------4-----------" << std::endl;
    // Set up SSL/TLS options
    connOpts.set_ssl(ssl_options);
    std::cout << "--------5-----------" << std::endl;
 
    // Set SSL/TLS options to the client
    // client.set_ssl(sslopts);
 
    // Connect options
    // mqtt::connect_options conn_opts;
    connOpts.set_clean_session(true);
    std::cout << "--------6-----------" << std::endl;
 
    try {
        // Connect to the broker
        std::cout << "--------7-----------" << std::endl;
        client.connect(connOpts)->wait();
        std::cout << "--------8-----------" << std::endl;
 
        // Publish a message
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, "Hello, MQTT!");
        std::cout << "--------9-----------" << std::endl;
        client.publish(pubmsg)->wait();
        std::cout << "--------10-----------" << std::endl;
 
        // Disconnect from the broker
        client.disconnect()->wait();
        std::cout << "--------11-----------" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
 
    return 0;
}