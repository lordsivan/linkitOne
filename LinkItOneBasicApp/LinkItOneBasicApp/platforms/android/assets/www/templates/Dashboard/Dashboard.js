var app = angular.module('dashboardModule', []);

app.controller('dashboardController', ['$scope','$LStore','bleService',
            function($scope,$LStore,bleService) {
                $scope.ultrasonic= {
                    "distance":25,
                    "tempCoefficient":29.1
                };
                $scope.water= {
                    "level":25,
                    "range":25
                };
                $scope.lux = {
                    "level":250,
                    "range":750,
                    "connectionStatus":false
                }
                $scope.foodFeed = {
                    "status":false
                }
                $scope.luxChange= function(){
                        $scope.lux.connectionStatus;
                }

                 $scope.luxChange = function(){
                    var action=0
                    if($scope.lux.connectionStatus){
                        action=1;
                    }
                    var command= {"command":"commandLed", "data":{
                        "switchAction":action
                        }
                    }
                    bleService.commandLed(command).then(
                        function(){   /// success handler for configureWifi
                            console.log("commandLed success");
                            }
                        ,
                        function(){   /// Error handler for configureWifi
                            console.log("commandLed failed");
                            }
                        )
                 };


                $scope.foodFeedChange = function(){
                                 var action=0
                                 if($scope.foodFeed.status){
                                    action=1;
                                 }
                                    var command= {"command":"commandFoodFeed", "data":{
                                        "switchAction":action
                                        }
                                    }
                                    bleService.commandLed(command).then(
                                        function(){   /// success handler for configureWifi
                                            console.log("commandLed success");
                                            }
                                        ,
                                        function(){   /// Error handler for configureWifi
                                            console.log("commandLed failed");
                                            }
                                        )
                                };

                $scope.setTempCoefficient = function(){
                                                    var command= {"command":"commandChangeTempCoefficient", "data":{
                                                        "tempCoefficient":$scope.ultrasonic.tempCoefficient
                                                        }
                                                    }
                                                    bleService.commandLed(command).then(
                                                        function(){   /// success handler for configureWifi
                                                            console.log("commandLed success");
                                                            }
                                                        ,
                                                        function(){   /// Error handler for configureWifi
                                                            console.log("commandLed failed");
                                                            }
                                                        )
                                                };

                $scope.$on('luxStatus', function (event, msgJson) {
                                     $scope.lux.range=msgJson.data.level;
                                     console.log("-------------------------------------->"+msgJson.data);
                                     $scope.$apply();
                                  });

                $scope.$on('UltrasonicStatus', function (event, msgJson) {
                                      $scope.ultrasonic.distance=msgJson.data.distance;
                                      $scope.$apply();
                                   });


            }
            ]);