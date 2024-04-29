const express = require('express');
const http = require('http');
const fs = require('fs');
const { Server } = require("socket.io")

const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')

const port = new SerialPort({ path: 'COM5', baudRate: 9600 })
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

const app = express();
const server = http.createServer(app);

const io = new Server(server)

app.use(express.static('css'));

app.get('/', (req, res) => {
    const index = fs.readFileSync('index.html', 'utf8');
    res.send(index);
});

io.on('connection', function(socket){
    socket.on('mode', function(data){
        port.write(data.status);
        console.log(data);
    })
})

parser.on('data', function(data){
    console.log(data);
    io.emit('data', data);
});

server.listen(3000, () => {
    console.log('Server is listening on port 3000');
});
