var app = angular.module('settingsModule', []);

app.controller('settingsController', ['$scope','$LStore','bleService',
            function($scope,$LStore,bleService) {
                $scope.init = function(){
                    $scope.settingsModel = {
                                            "selectedBLE":"",
                                            "blueToothList":[]
                                        }
                    $scope.settingsModel= $LStore.getObject("settingsModel",$scope.settingsModel);
                }
                $scope.init();

                bleService.listPorts().then(
                    function(list){
                        $scope.settingsModel.blueToothList = list;
                    },
                    function(){
                        console.log("error");
                    }
                );

                $scope.Bleconnect = function(){
                    $LStore.setObject("settingsModel",$scope.settingsModel);
                    bleService.deviceConnect($scope.settingsModel.selectedBLE.address).then(
                        function(list){
                            console.log("connected successfully");
                        },
                        function(){
                            console.log("error");
                        }
                    );
                }

            }
            ]);