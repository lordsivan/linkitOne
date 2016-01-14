var app = angular.module('terminalModule', []);

app.controller('terminalController', ['$scope','$LStore','bleService',
            function($scope,$LStore,bleService) {
                $scope.init=function(){
                    $scope.terminalModel = {
                        "displayText":"",
                        "sendText":""
                    }
                    $scope.terminalModel= $LStore.getObject("terminalModel",$scope.terminalModel);
                }
                $scope.init();
                $scope.send = function(){
                    bleService.sendSerial($scope.terminalModel.sendText);
                }

            }
            ]
            );