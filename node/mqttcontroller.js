var needle = require('needle');
var output = "this is an mqtt ouput";

var tagNumber = 2;
var message = {
    "location" : 1,
    "user" : tagNumber
}

needle.post('http://192.168.1.69/rest-api/api/user/id/' + tagNumber + '/format/json', message , { username: '4ark4ble', password: 'remarkable'} ,
    function( err, resp, body){

    console.log("statusCode: ", resp.statusCode);
    console.log("response: " + JSON.stringify(body));

    }
);

exports.output = output;