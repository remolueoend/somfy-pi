#!/usr/bin/env node

const SerialPort = require('serialport')
const pathHelper = require('path')
const fs = require('fs')

const Readline = SerialPort.parsers.Readline
const parser = new Readline()

function hex2a(hexx) {
  var hex = hexx.toString() //force conversion
  var str = ''
  for (var i = 0; i < hex.length; i += 2)
    str += String.fromCharCode(parseInt(hex.substr(i, 2), 16))
  return str
}

const port = new SerialPort('/dev/cu.usbmodem1411', {
  baudRate: 9600,
})

port.pipe(parser)

port.on('open', () => {
  console.log('serial port opened.')
})
port.on('error', err => {
  console.error(err.message)
})

port.on('data', data => {
  process.stdout.write(data && data.toString())
})
