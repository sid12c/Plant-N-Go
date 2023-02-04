// In this file we will have it listen to the serial port 
// and make it print out to console anything it receives 
var SerialPort = require("serialport"); // load the serial port library


// Creating a parser
// using the parser will tell node.js how to interpret/receive data coming through the serial port
// We want to receive data anyime it receives a new line
const parsers = SerialPort.parsers
const parser = new parsers.Readline({
    delimeter: "\r\n"
});

// opening the port.
// steps: To obtain the port number
// 1.) Go to Arduino Code editor
// 2.) find something like /dev or com/...
// 3.) copy and paste it in the parentheses
var port = new SerialPort('paste here ', {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false});

// attach our port to our parsers object
port.pipe(parser);

// take the parser and add the ondataevent handler
// when the parser receives data, it's going to run the function
parser.on('data', function(data) {
    console.log(data)
});

// NOTES:
// Be sure to close the monitor for the arduino code editor so the serial port is free
// If you don't, it will throw error message
