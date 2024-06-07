#include <iostream>
#include "mqtt/async_client.h"
#include "common.pb.h"
#include "vehicletelemetry.pb.h"
#include "vehicletelemetry_message.pb.h"
#define PROTOBUF_USE_DLLS

const std::string SERVER_ADDRESS = "ssl://a10suzhdnq8qws-ats.iot.ap-south-1.amazonaws.com:8883";
const std::string CLIENT_ID = "iTrams-Mqtt-client";
const std::string TOPIC = "devices/AWS IoT Certificate/device/FGQWE12343F90543/MQTTPROTOBUFF/telemetry";
const std::string kEnabledCipherSuites =
    "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-"
    "AES256-GCM-SHA384:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-CHACHA20-POLY1305"
    "ECDHE-RSA-AES256-GCM-SHA384";

// Define a callback class for handling incoming MQTT messages
class MyCallback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::string payload = msg->to_string();
        
        // Deserialize the received payload into a TelemetryMessage
        com::bosch::itrams_gen2e::TelemetryMessage received_message;
        received_message.ParseFromString(payload);

        // Display the deserialized telemetry message
        std::cout << "Received Telemetry Message:\n" << received_message.DebugString() << std::endl;

        // Serialize the deserialized message back to a string
        std::string reserialized_data;
        received_message.SerializeToString(&reserialized_data);

        // Print the reserialized data
        std::cout << "Reserialized Data:\n" << reserialized_data << std::endl;
    }
};


int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    mqtt::ssl_options ssl_options;
    mqtt::connect_options connOpts;

    std::cout << "--------1-----------" << std::endl;
    ssl_options.set_trust_store("/usrdata/certs/ca-crt.pem");
    std::cout << "--------2-----------" << std::endl;
    ssl_options.set_key_store("/usrdata/certs/client-crt.pem");
    std::cout << "--------3-----------" << std::endl;
    ssl_options.set_private_key("/usrdata/certs/client.pem");
    std::cout << "--------4-----------" << std::endl;
    ssl_options.set_enable_server_cert_auth(true);
    std::cout << "--------5-----------" << std::endl;
    ssl_options.set_ssl_version(MQTT_SSL_VERSION_TLS_1_2);
    std::cout << "--------6-----------" << std::endl;
    ssl_options.set_enabled_cipher_suites(kEnabledCipherSuites);
    std::cout << "--------7-----------" << std::endl;

    connOpts.set_ssl(ssl_options);
    std::cout << "--------8-----------" << std::endl;
    connOpts.set_keep_alive_interval(60);
    std::cout << "--------9-----------" << std::endl;
    connOpts.set_connect_timeout(60);
    std::cout << "--------10-----------" << std::endl;
    connOpts.set_automatic_reconnect(5, 600);
    std::cout << "--------11-----------" << std::endl;
    connOpts.set_clean_session(true);
    std::cout << "--------12-----------" << std::endl;

    try {
        
        // Establish MQTT connection
        std::cout << "--------13-----------" << std::endl;
        auto token = client.connect(connOpts);
        std::cout << "--------14-----------" << std::endl;
        token->wait();
        std::cout << "--------15-----------" << std::endl;

        // Display connection information
        std::cout << "Connected...... Client ID: " << CLIENT_ID << ", Server: " << SERVER_ADDRESS << std::endl;
        std::cout << "--------16-----------" << std::endl;

        // Subscribe to the MQTT topic
        auto subToken = client.subscribe(TOPIC, 1);
        std::cout << "--------17-----------" << std::endl;
        subToken->wait();
        std::cout << "--------18-----------" << std::endl;

        // Display subscription information
        std::cout << "Subscribed to topic: " << TOPIC << std::endl;
        std::cout << "--------19-----------" << std::endl;

        // Set up callback to handle incoming messages
        MyCallback callback;
        std::cout << "--------20-----------" << std::endl;
        client.set_callback(callback);
        std::cout << "--------21-----------" << std::endl;
        
        //Testing
        com::bosch::itrams_gen2e::TelemetryReading telemetry_data;
        telemetry_data.set_gpssignalquality(2);
        telemetry_data.set_gpslat(100);
        telemetry_data.set_gpslong(200);
        telemetry_data.set_gpsalt(300);
        telemetry_data.set_gpscourseangle(45.0);
        telemetry_data.set_gpsaccuracylat(10);
        telemetry_data.set_gpsaccuracylong(20);
        telemetry_data.set_gpsaccuracyalt(30);
        com::bosch::itrams_gen2e::TelemetryPayload* telemetryPayload = new com::bosch::itrams_gen2e::TelemetryPayload();
      // Add each TelemetryReading to the TelemetryPayload
        *telemetryPayload->add_measures() = telemetry_data;
        std::cout << "Publishing TelemetryPayload: " << telemetryPayload->DebugString() << std::endl;
      // Create TelemetryMessage and set TelemetryPayload
        auto telemetryMessageSharedPtr = std::make_shared<com::bosch::itrams_gen2e::TelemetryMessage>();
        com::bosch::itrams_gen2e::TelemetryMessage& telemetry_message = *telemetryMessageSharedPtr; // Access the actual instance

        telemetry_message.set_message_id("12345");
        telemetry_message.set_to("MQTT");
        telemetry_message.mutable_telemetrypayload()->CopyFrom(*telemetryPayload);
        // Display telemetry information before publishing
        std::cout << "Telemetry reading:\n" << telemetry_data.DebugString() << std::endl;
        std::cout << "Telemetry Message:\n" << telemetry_message.DebugString() << std::endl;


        std::string serialized_data;
        telemetry_message.SerializeToString(&serialized_data);

        // Print the serialized data
        std::cout << "Serialized Telemetry Message:\n" << serialized_data << std::endl;
        // Publish telemetry message
        mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, serialized_data);
        pubmsg->set_qos(1);

        // Publish telemetry message
        mqtt::delivery_token_ptr deliveryToken = client.publish(pubmsg);

        // Wait for the delivery to complete
        deliveryToken->wait();

        // Check the delivery status
        if (deliveryToken->get_message_id() != -1) {
            std::cout << "Telemetry message successfully delivered to topic: " << TOPIC << std::endl;
            // Display additional delivery information
            std::cout << "Delivery information - Message ID: " << deliveryToken->get_message_id() << std::endl;
        } else {
            std::cerr << "Failed to deliver telemetry message to topic: " << TOPIC << std::endl;
        }

        // Note: The QoS information is retrieved from the original message, not the delivery token
        std::cout << "Original message QoS: " << pubmsg->get_qos() << std::endl;


        // Display publishing information
        std::cout << "Telemetry message published to topic: " << TOPIC << std::endl;

        // Disconnect from MQTT broker
        token = client.disconnect();
        token->wait();

        // Display disconnection information
        std::cout << "Disconnected from the MQTT broker." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
