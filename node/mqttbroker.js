var app = require("./app"),
    mqttController = require("./mqttcontroller"),
    mqtt = require('mqttjs');

var thisMqttServer = mqtt.createServer(function (client) {

    var self = this;

    if (self.clients === undefined) self.clients = {};

    client.on('connect', function (packet) {

            console.log(packet.client, ':  - MQTT Client has Connected');

                    client.connack({

                            returnCode: 0

                    });

            client.id = packet.client;

            self.clients[client.id] = client;

    });

    client.on('publish', function (packet) {

        for (var k in self.clients) {

                self.clients[k].publish({topic: packet.topic, payload: packet.payload});

                console.log( "TOPIC: " , packet.topic);
                console.log( "PACKET: " , packet.payload);

                console.log( mqttController.output )

        }
    });


    client.on('subscribe', function (packet) {

        var granted = [];

        for (var i = 0; i < packet.subscriptions.length; i++) {

                 granted.push(packet.subscriptions[i].qos);

        }

        client.suback({ granted: granted });

    });

    client.on('pingreq', function (packet) {

            client.pingresp();

    });

    client.on('disconnect', function (packet) {

            client.stream.end();
            console.log("MQTT Client disconnected - ", packet.client);

    });

    client.on('close', function (err) {

            delete self.clients[client.id];

    });

    client.on('error', function (err) {

            client.stream.end();

            console.log('error!');

    });

}).listen(app.mqttPort);
