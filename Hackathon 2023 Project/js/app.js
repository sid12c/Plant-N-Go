var http = require('http');
var fs = require('fs'); // file system library
var index = fs.readFileSync('../index.html');

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
var port = new SerialPort('/dev/cu.usbmodem1412301', {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false});

port.on('error', function(err) { console.log('Error: ', err.message); }) // error handling

// attach our port to our parsers object
port.pipe(parser);

// NOTES:
// Be sure to close the monitor for the arduino code editor so the serial port is free
// If you don't, it will throw error message

// creating a server
var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end(index);
});

// passing the data from our arduino to the socket
// initialize socket to app
var io = require('socket.io').listen(app);
io.on('connection', function(socket) {
    console.log("Node.js is listening!");
})
 
// take the parser and add the ondataevent handler
// when the parser receives data, it's going to run the function
parser.on('data', function(data) {
    
    setTimeout(() => {
        console.log(data);
        console.log("Delayed for 1 seconds.");
        io.emit('data', data) // emitting the message with the data coming from the serial port
    }, 1000)

});

app.listen(3000);