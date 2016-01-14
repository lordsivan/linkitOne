    var bleServiceModule = angular.module('bleServiceModule', [])

    bleServiceModule.service('bleService', function($q, $location, $window, $rootScope) {


    this.commandLed =
            function(command) {
                var deferred = $q.defer();
                var me=this;
                me.sendSerial("^"+JSON.stringify(command)+"$").then(function() {
                                                                                    deferred.resolve();
                                                                               },
                                                                    function() {
                                                                                    deferred.reject();
                                                                               });
                return deferred.promise;
            };


        this.configureWifi =
            function(command) {
                var deferred = $q.defer();
                var me=this;
                me.sendSerial("^"+JSON.stringify(command)+"$").then(function() {
                                                                                    deferred.resolve();
                                                                               },
                                                                    function() {
                                                                                    deferred.reject();
                                                                               });
                return deferred.promise;
            };
        this.getConfigurationDetail =
            function() {
                var deferred = $q.defer();
                var me=this;
                var command= {
                "command":"getConfigurationDetail"
                }
                me.sendSerial("^"+JSON.stringify(command)+"$").then(function() {
                                                                                    deferred.resolve();
                                                                               },
                                                                    function() {
                                                                                    deferred.reject();
                                                                               });
                return deferred.promise;
            };
        this.sendSerial = function(commandJson){
            var deferred = $q.defer();
            bluetoothSerial.write(commandJson,  function() {
                                                                deferred.resolve();
                                                           },
                                                function() {
                                                                deferred.reject();
                                                           });
            return deferred.promise;
        }
        this.listPorts = function () {
                var deferred = $q.defer();
                // check if Bluetooth is on:
                bluetoothSerial.isEnabled(
                    function () {
                                    // list the available BT ports:
                                    bluetoothSerial.list(
                                        function (results) {
                                            console.log("Ble results"+JSON.stringify(results));
                                            deferred.resolve(results);
                                        },
                                        function (error) {
                                           deferred.reject(JSON.stringify(error));
                                        }
                                    );
                                 },
                    function() {  deferred.reject(); }    // Not enabled error
                );
                return deferred.promise;
        }

        this.deviceDisconnect = function () {
            var deferred = $q.defer();
            bluetoothSerial.disconnect(
               function() {
                               closePort(deferred);
                         },    // start listening if you succeed
               function() {
                               deferred.reject();
                         }    // show the error if you fail
            );
            return deferred.promise;
       };

        this.deviceConnect = function (address) {
               var me=this;
               var deferred = $q.defer();
               bluetoothSerial.connect(
                   address,  // device to connect to
                   function() {
                                    me.openPort();
                                    deferred.resolve();
                              },    // start listening if you succeed
                   function() {
                                    deferred.reject();
                              }    // show the error if you fail
               );
               return deferred.promise;
        };

        // Internal support function
       this.openPort= function () {
            var me =this;
            bluetoothSerial.subscribe('\n', function (data) {
                me.receiveData(data);
            });
       }
       this.receiveData= function(data){
           var dataJson = JSON.parse(data);
           console.log("Command+++++++++++++++++++++++++++->"+dataJson);
           $rootScope.$broadcast(dataJson.command, dataJson);
       }

       this.closePort= function (deferred) {
           bluetoothSerial.unsubscribe(
                   function (data) {
                       deferred.resolve();
                   },
                   function() {
                          deferred.reject();
                    }    // show the error if you fail
           );
       }

    });