var express = require('express'),
    mqtt = require('mqttjs'),
    app = express(),
    server = require('http').createServer(app);


    var socketsPort = 8081,
        mqttPort = 8080, // need to be diffrent to socketsPort
        serverAddress = "127.0.0.1";

        // Export earlier for mqqt client to connect on startup
        exports.serverAddress = serverAddress;
        exports.mqttPort = mqttPort;

    //modules
    var mqttBroker = require("./mqttbroker");

server.listen(socketsPort);

app.configure(function() {

        app.use(express.static(__dirname + '/public'));
});

app.get('/', function (req, res) {

        res.sendfile(__dirname + '/index.html');
});

