var http = require('http');
var fs = require('fs');
const { Server } = require("socket.io")

var index = fs.readFileSync('index.html');

const { SerialPort } = require('serialport')

const { ReadlineParser } = require('@serialport/parser-readline')
const port = new SerialPort({ path: 'COM5', baudRate: 9600 })

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end(index);
})

//var io = require('socket.io');
const io = new Server(app)

io.httpServer.on('connection', function(data){
    console.log('Node.js is listening!')
})

parser.on('data', function(data){
    console.log(data);
    io.emit('data', data);
});

app.listen(3000);