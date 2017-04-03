// file will all configuration variables
const config = require('./config.json');
// serial port communication
const SerialPort = require('serialport');


var port = new SerialPort(config.serial.port, {
    baudRate: config.serial.baud_rate
});

// Test a simple go home command
port.on('open', function() {
    port.write('G28\n', function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written');
    });
});

// open errors will be emitted as an error event
port.on('error', function(err) {
    console.log('Error: ', err.message);
})