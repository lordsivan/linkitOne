var app = angular.module('wifiModule', [ 'ionic', 'ionic.utils']);

app.controller('wifiController', ['$scope','$LStore','bleService',
            function($scope,$LStore,bleService) {
                $scope.init = function(){
                    $scope.wifiModel = {
                        "accessPoint":"",
                        "password":"",
                        "connectionStatus":false,
                        "ipAddress":"...",
                        "subnetMask":"...",
                        "gatewayIP":"...",
                        "signalStrength":"..."
                    }
                    $scope.wifiModel= $LStore.getObject("wifiModel",$scope.wifiModel);
                }
                $scope.init();

                $scope.changeWifi = function(){
                    var wifiCommand= {"command":"configureWifi", "data":{
                        "accessPoint":$scope.wifiModel.accessPoint,
                        "password":$scope.wifiModel.password
                        }
                    }
                    bleService.configureWifi(wifiCommand).then(
                        function(){   /// success handler for configureWifi
                            }
                        ,
                        function(){   /// Error handler for configureWifi
                            console.log("ConfigureWifi failed");
                            }
                        )
                };
                $scope.doRefresh = function(){
                    console.log("---------------------------");
                    alert("refresh");
                     $scope.$broadcast('scroll.refreshComplete');
                }
                bleService.getConfigurationDetail().then(
                    function(){   /// success handler for configureWifi
                        console.log("command send success");
                        }
                    ,
                    function(){   /// Error handler for configureWifi
                        console.log("command send failed");
                        }
                    );
                $scope.$on('configureWifi', function (event, msgJson) {
                    $scope.wifiModel.accessPoint=msgJson.data.accessPoint;
                    $scope.wifiModel.password=msgJson.data.password;
                    console.log(msgJson);
                    $scope.$apply();
                 });
                 $scope.$on('getWifiStatus', function (event, msgJson) {
                     $scope.wifiModel.accessPoint=msgJson.data.SSID;
                     $scope.wifiModel.ipAddress=msgJson.data.ipAddress;
                     $scope.wifiModel.subnetMask=msgJson.data.subnetMask;
                     $scope.wifiModel.gatewayIP=msgJson.data.gatewayIP;
                     $scope.wifiModel.signalStrength=msgJson.data.signalStrength;
                     $scope.wifiModel.connectionStatus=msgJson.data.connectionStatus==1?true:false;
                     console.log(msgJson);
                     $scope.$apply();
                  });
            }
            ]
            );