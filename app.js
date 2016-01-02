
 var mra = require('mraa');
 var gpio0 = new mra.Gpio(0);

 var mcs = require('mcsjs');
 var myApp = mcs.register({
     deviceId: 'Dl6JwRAp',
     deviceKey: 'W9aheePifDQqUHbP',
 });

 myApp.on('Relay_Control', function(data, time) {
     if(Number(data) === 1){
        console.log('Relay: On');
        gpio0.dir(0);
        gpio0.write(1);
     } else {
        console.log('Relay: Off');
        gpio0.dir(0);
        gpio0.write(0);
     }
 });


 var serialport = require("serialport");
 var SerialPort = serialport.SerialPort;

 var serialPort = new SerialPort("/dev/ttyS0", {
        baudrate: 57600,
        parser: serialport.parsers.readline("\n")
 });

 serialPort.on('error', function(err)
 {
        console.log(err);
 });

 serialPort.on("open", function () {
        serialPort.on('data', function(data)
         {
                if(data[0] == 'H')
                {
                        console.log('Humid: ');
                        console.log(parseInt(data.substr(2)));
                        myApp.emit('Humid_Sensor','', parseInt(data.substr(2)));
                }
                else if(data[0] == 'L')
                {
                        console.log('Lumi: ');
                        console.log(parseInt(data.substr(2)));
                        myApp.emit('Light_Sensor','', parseInt(data.substr(2)));

                }
                else if(data[0] == 'T')
                {
                        console.log('Temperture: ');
                        console.log(parseInt(data.substr(2)));
                        myApp.emit('Temperture_Sensor','', parseInt(data.substr(2)));
                }
                else if(data[0] == 'M')
                {
                        console.log('Moisture: ');
                        console.log(parseInt(data.substr(2)));
                        myApp.emit('Moisture_Sensor','', parseInt(data.substr(2)));
                }
        });
 });
