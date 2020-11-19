const express = require('express');
const app = require('express')();
const socketIO = require('socket.io');
var path = require('path');
const PORT = process.env.PORT || 3000;

const server = express()
  .use(express.static('public'))
  .listen(PORT, () => console.log(`Listening on ${ PORT }`));




const io = socketIO(server);
io.on('connection', newConnection);

function newConnection(socket) {
    console.log('conectado!')
    socket.on('RGBValue', function(data){
        // recibimos un objeto con el rgb
        socket.broadcast.emit('REDValue', data.r);
        socket.broadcast.emit('GREENValue', data.g);
        socket.broadcast.emit('BLUEValue', data.b);

    })
}