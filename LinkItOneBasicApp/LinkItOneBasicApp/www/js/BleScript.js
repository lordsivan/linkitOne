/*
    SimpleSerial index.js
    Created 7 May 2013
    Modified 9 May 2013
    by Tom Igoe
*/


var appBLE = {
    macAddress: "2c:f7:f1:81:39:d6",  // get your mac address from bluetoothSerial.list
    chars: "",

    /*
        Application constructor
     */
    initialize: function () {
        this.bindEvents();
        console.log("Starting SimpleSerial app");
    },
    /*
        bind any events that are required on startup to listeners:
    */
    bindEvents: function () {
        document.addEventListener('deviceready', this.onDeviceReady, false);
        connectButton.addEventListener('touchend', appBLE.manageConnection, false);
    },

    /*
        this runs when the device is ready for user interaction:
    */
    onDeviceReady: function () {
        // check to see if Bluetooth is turned on.
        // this function is called only
        //if isEnabled(), below, returns success:
        var listPorts = function () {
            // list the available BT ports:
            bluetoothSerial.list(
                function (results) {
                    appBLE.display(JSON.stringify(results));
                },
                function (error) {
                    appBLE.display(JSON.stringify(error));
                }
            );
        }

        // if isEnabled returns failure, this function is called:
        var notEnabled = function () {
            appBLE.display("Bluetooth is not enabled.")
        }

        // check if Bluetooth is on:
        bluetoothSerial.isEnabled(
            listPorts,
            notEnabled
        );
    },
    /*
        Connects if not connected, and disconnects if connected:
    */
    manageConnection: function () {

        // connect() will get called only if isConnected() (below)
        // returns failure. In other words, if not connected, then connect:
        var connect = function () {
            // if not connected, do this:
            // clear the screen and display an attempt to connect
            appBLE.clear();
            appBLE.display("Attempting to connect. " +
                "Make sure the serial port is open on the target device.");
            // attempt to connect:
            bluetoothSerial.connect(
                appBLE.macAddress,  // device to connect to
                appBLE.openPort,    // start listening if you succeed
                appBLE.showError    // show the error if you fail
            );
        };

        // disconnect() will get called only if isConnected() (below)
        // returns success  In other words, if  connected, then disconnect:
        var disconnect = function () {
            appBLE.display("attempting to disconnect");
            // if connected, do this:
            bluetoothSerial.disconnect(
                appBLE.closePort,     // stop listening to the port
                appBLE.showError      // show the error if you fail
            );
        };

        // here's the real action of the manageConnection function:
        bluetoothSerial.isConnected(disconnect, connect);
    },
    /*
        subscribes to a Bluetooth serial listener for newline
        and changes the button:
    */
    openPort: function () {
        // if you get a good Bluetooth serial connection:
        appBLE.display("Connected to: " + appBLE.macAddress);
        // change the button's name:
        connectButton.innerHTML = "Disconnect";
        // set up a listener to listen for newlines
        // and display any new data that's come in since
        // the last newline:
        bluetoothSerial.subscribe('\n', function (data) {
            appBLE.clear();
            appBLE.display(data);
        });
    },

    /*
        unsubscribes from any Bluetooth serial listener and changes the button:
    */
    closePort: function () {
        // if you get a good Bluetooth serial connection:
        appBLE.display("Disconnected from: " + appBLE.macAddress);
        // change the button's name:
        connectButton.innerHTML = "Connect";
        // unsubscribe from listening:
        bluetoothSerial.unsubscribe(
                function (data) {
                    appBLE.display(data);
                },
                appBLE.showError
        );
    },
    /*
        appends @error to the message div:
    */
    showError: function (error) {
        appBLE.display(error);
    },

    /*
        appends @message to the message div:
    */
    display: function (message) {
        var display = document.getElementById("message"), // the message div
            lineBreak = document.createElement("br"),     // a line break
            label = document.createTextNode(message);     // create the label

        display.appendChild(lineBreak);          // add a line break
        display.appendChild(label);              // add the message node
    },
    /*
        clears the message div:
    */
    clear: function () {
        var display = document.getElementById("message");
        display.innerHTML = "";
    }
};      // end of app

