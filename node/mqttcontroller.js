var needle = require('needle');
var output = "this is an mqtt ouput";

var tagNumber = '4400E6A02A28';
var message = {
    location : 1,
    user : tagNumber
}


function postRfid (tagId, location){

    var loc = location;
    var id  = tagId;

    var message = {
        location : loc,
        user : id
    }
    console.log("message to send: ", message);

    needle.post('http://192.168.1.69/rest-api/api/user/id/' + id + '/format/json', message , { username: '4ark4ble', password: 'remarkable'} ,

        function( err, resp, body){
        console.log("statusCode: ", resp.statusCode);
        console.log("response: " + JSON.stringify(body));

        }
    );
}

exports.output = output;
exports.postRfid = postRfid;