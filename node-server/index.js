var http = require('http');
var fs = require('fs');

var index = fs.readFileSync('index.html');

const { SerialPort } = require('serialport')

const { ReadlineParser } = require('@serialport/parser-readline')
const port = new SerialPort({ path: 'COM5', baudRate: 9600 })

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

parser.on('data', function(data){
    console.log(data);
});

var app = http.createServer(function(req,res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end(index);
})

app.listen(3000);